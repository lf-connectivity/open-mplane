/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwareSlotMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <set>
#include <utility>
#include <map>

#include "stringfunc.hpp"
#include "Path.h"
#include "IImageManagement.h"

#include "SoftwarePackage.h"
#include "SoftwareSlot.h"
#include "SoftwareSlotConstants.h"

#include "SoftwareSlotMgr.h"

using namespace Mplane;

#define DEBUG_SWJOB

//=============================================================================================================
// Job
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class SoftwareSlotMgr::SwJob {
public:

	enum JobType {
		JOB_INSTALL,
		JOB_ACTIVATE,
	};

	SwJob() :
		mSlotName(""),
		mType(JOB_INSTALL),
		mError("")
	{}
	virtual ~SwJob() {}

	void show() const
	{
#ifdef DEBUG_SWJOB
		std::cerr << "JOB " ;

		std::cerr << std::endl ;
#endif
	}

	void showStatus() const
	{
#ifdef DEBUG_SWJOB
		std::cerr << "JOB " ;
		if (mError.empty())
		{
			std::cerr << "OK" ;
		}
		else
		{
			std::cerr << "ERROR:" << mError ;
		}

		std::cerr << std::endl ;
#endif
	}

	// common parameters
	std::string mSlotName ;
	JobType mType ;
	std::string mError ;

};

//-------------------------------------------------------------------------------------------------------------
class SoftwareSlotMgr::SwInstallJob : public SoftwareSlotMgr::SwJob {
public:
	SwInstallJob() :
		SwJob(),
		mFiles(),
		mManifest(),
		mCallback()
	{
		mType = JOB_INSTALL ;
	}
	virtual ~SwInstallJob() {}

	void show() const
	{
	}

	// Install parameters
	std::vector< std::pair<std::string, std::string> > mFiles ;
	std::string mManifest ;
	ISoftwareSlotMgr::InstallCallback mCallback ;
};

//-------------------------------------------------------------------------------------------------------------
class SoftwareSlotMgr::SwActivateJob : public SoftwareSlotMgr::SwJob {
public:
	SwActivateJob() :
		SwJob(),
		mCallback(),
		mTimeoutSecs(0)
	{
		mType = JOB_ACTIVATE ;
	}
	virtual ~SwActivateJob() {}

	void show() const
	{
	}

	// Activation parameters
	ISoftwareSlotMgr::ActivateCallback mCallback ;
	unsigned mTimeoutSecs ;
};

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::map<ISoftwareSlotMgr::InstallStatus, std::string> INSTALL_STATUS{
	{ISoftwareSlotMgr::INSTALL_COMPLETED,	"COMPLETED"},
	{ISoftwareSlotMgr::INSTALL_FILE_ERROR,	"FILE_ERROR"},
	{ISoftwareSlotMgr::INSTALL_INTEGRITY_ERROR,	"INTEGRITY_ERROR"},
	{ISoftwareSlotMgr::INSTALL_APPLICATION_ERROR,	"APPLICATION_ERROR"},
} ;

const std::map<ISoftwareSlotMgr::ActivateStatus, std::string> ACTIVATE_STATUS{
	{ISoftwareSlotMgr::ACTIVATE_COMPLETED,	"COMPLETED"},
	{ISoftwareSlotMgr::ACTIVATE_APPLICATION_ERROR,	"APPLICATION_ERROR"},
} ;


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string ISoftwareSlotMgr::installStatusString(ISoftwareSlotMgr::InstallStatus status)
{
	return INSTALL_STATUS.at(status) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ISoftwareSlotMgr::activateStatusString(ISoftwareSlotMgr::ActivateStatus status)
{
	return ACTIVATE_STATUS.at(status) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SoftwareSlotMgr::SoftwareSlotMgr(unsigned maxSlots,
		const std::string &mgmtPath,
		const std::string &appsPath,
		const std::string &osPath) :
	mNumSlots(maxSlots),
	mMgrPath(mgmtPath),
	mAppsPath(appsPath),
	mOsPath(osPath),
	mPackages(),
	mSlots(),
	mMutex(),
	mJobs()
{
	// Ensure directories are all present
	createDirectories() ;

	// create the packages
	createPackages() ;

	// create the slots
	createSlots() ;
}

//-------------------------------------------------------------------------------------------------------------
SoftwareSlotMgr::SoftwareSlotMgr() :
	SoftwareSlotMgr(SoftwareSlotConstants::DefaultNumSlots,
			SoftwareSlotConstants::MgmtDir,
			IImageManagement::getInstance()->getImage(IImageTypes::IMAGE_APPLICATION)->installDir(),
			IImageManagement::getInstance()->getImage(IImageTypes::IMAGE_ROS)->installDir())
{
}

//-------------------------------------------------------------------------------------------------------------
SoftwareSlotMgr::SoftwareSlotMgr(unsigned maxSlots) :
	SoftwareSlotMgr(maxSlots,
			SoftwareSlotConstants::MgmtDir,
			IImageManagement::getInstance()->getImage(IImageTypes::IMAGE_APPLICATION)->installDir(),
			IImageManagement::getInstance()->getImage(IImageTypes::IMAGE_ROS)->installDir())
{
}

//-------------------------------------------------------------------------------------------------------------
SoftwareSlotMgr::~SoftwareSlotMgr()
{
}


//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<ISoftwareSlot> > SoftwareSlotMgr::slots() const
{
	std::vector<std::shared_ptr<ISoftwareSlot> > list ;
	for (auto entry : mSlots)
	{
		list.push_back(entry.second) ;
	}
	return list ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlotMgr::install(const std::string &slotName,
		const std::vector<std::string> &files, ISoftwareSlotMgr::InstallCallback func,
		std::string &error)
{
	// Installation involves moving the downloaded files to their correct positions

	// check slot name valid
	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	if (mSlots.find(slotName) == mSlots.end())
	{
		error = "Invalid slot name" ;
		return false ;
	}
	}

	// Reject if slot is read only
	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	if (mSlots[slotName]->isReadOnly())
	{
		error = "Slot is read-only" ;
		return false ;
	}
	}

	// First make sure we have the requisite set of files for the package
	std::string manifestFile ;
	std::string appFile ;
	std::string osFile ;
	for (auto file : files)
	{
		// Assign
		if (toLower(file).find("manifest") != std::string::npos)
		{
			manifestFile = file ;
			continue ;
		}

		if (toUpper(file).find("APP") != std::string::npos)
		{
			appFile = file ;
			continue ;
		}

		if (toUpper(file).find("OS") != std::string::npos)
		{
			osFile = file ;
			continue ;
		}
	}

	if (manifestFile.empty() || appFile.empty() || osFile.empty())
	{
		std::string missing ;
		if (manifestFile.empty())
			missing += "manifest" ;

		if (appFile.empty())
		{
			if (!missing.empty())
				missing += ", " ;
			missing += "application" ;
		}

		if (osFile.empty())
		{
			if (!missing.empty())
				missing += ", " ;
			missing += "OS" ;
		}

		error = "Install is missing vital files: " + missing ;
		return false ;
	}

	// Check files exist
	if (!Path::isFile(manifestFile))
	{
		error = "Invalid manifest file: does not exist" ;
		return false ;
	}
	if (!Path::isFile(appFile))
	{
		error = "Invalid application file: does not exist" ;
		return false ;
	}
	if (!Path::isFile(osFile))
	{
		error = "Invalid OS file: does not exist" ;
		return false ;
	}

	// Make sure no other slot is already allocated to this package
	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	for (auto entry : mSlots)
	{
		// skip this one
		if (entry.first == slotName)
			continue ;

		// skip any not allocated
		if (!entry.second->isAllocated())
			continue ;

		// check manifest
		auto pkg(entry.second->package()) ;
		if ( Path::basename(pkg->manifestPath()) != Path::basename(manifestFile) )
			continue ;

		// already allocated so stop with error
		error = "Package already allocated to slot " + entry.first ;
		return false ;

	}
	}

	std::string movedManifestFile(mMgrPath + "/" + SoftwareSlotConstants::ManifestsSubdir + "/" + Path::basename(manifestFile)) ;
	std::string movedAppFile(mAppsPath + "/" + Path::basename(appFile)) ;
	std::string movedOsFile(mOsPath + "/" + Path::basename(osFile)) ;

	// Start the install job
	std::shared_ptr<SwInstallJob> job(std::make_shared<SwInstallJob>()) ;
	job->mSlotName = slotName ;
	job->mCallback = func ;
	job->mManifest = movedManifestFile ;
	job->mFiles.push_back( std::make_pair(manifestFile, movedManifestFile) ) ;
	job->mFiles.push_back( std::make_pair(appFile, movedAppFile) ) ;
	job->mFiles.push_back( std::make_pair(osFile, movedOsFile) ) ;

	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	mJobs.push_back(job) ;
	}

	// start job processing
	event() ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlotMgr::activate(const std::string &slotName, unsigned& requiredTimeoutSecs,
		ISoftwareSlotMgr::ActivateCallback func, std::string &error)
{
	// check slot name valid
	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	if (mSlots.find(slotName) == mSlots.end())
	{
		error = "Invalid slot name" ;
		return false ;
	}

	std::shared_ptr<ISoftwareSlot> slot(mSlots[slotName]) ;
	std::shared_ptr<ISoftwarePackage> pkg(slot->package()) ;
	if (!pkg)
	{
		error = "Slot does not have any allocated package" ;
		return false ;
	}

	// get the package to tell us how much time it needs to install these files
	requiredTimeoutSecs = pkg->requiredInstallTimeSecs() ;

	}

	// Start the activation job
	std::shared_ptr<SwActivateJob> job(std::make_shared<SwActivateJob>()) ;
	job->mSlotName = slotName ;
	job->mCallback = func ;
	job->mTimeoutSecs = requiredTimeoutSecs ;

	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	mJobs.push_back(job) ;
	}

	// start job processing
	event() ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void SoftwareSlotMgr::show(std::ostream &os)
{
	std::unique_lock<std::mutex> lock(mMutex) ;

	os << "SLOTS" << std::endl ;
	std::set<std::string> seenPackages ;
	for (auto entry : mSlots)
	{
		entry.second->show(os) ;

		auto pkg(entry.second->package()) ;
		if (!pkg)
			continue ;

		seenPackages.insert(pkg->buildName()) ;
	}
	os << std::endl ;

	os << "PACKAGES" << std::endl ;
	for (auto pkg : mPackages)
	{
		if (seenPackages.find(pkg->buildName()) != seenPackages.end())
			continue ;

		pkg->show(os) ;
	}
}


//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlotMgr::clean(std::string &error)
{
	std::unique_lock<std::mutex> lock(mMutex) ;

	// Start by clearing out any packages that are not allocated to slots
	std::set<std::string> allocated ;
	for (auto entry : mSlots)
	{
		if (!entry.second->isAllocated())
			continue ;

		auto pkg(entry.second->package()) ;
		allocated.insert(pkg->buildName()) ;
	}

	std::vector<std::shared_ptr<ISoftwarePackage>> packageList(mPackages) ;
	mPackages.clear() ;
	for (auto pkg : packageList)
	{
		if (allocated.find(pkg->buildName()) != allocated.end())
		{
			// this is allocated, so keep it
			mPackages.push_back(pkg) ;
			continue ;
		}

		// Not allocated, so clear it
		Path::remove(pkg->manifestPath()) ;

//std::cerr << "DELETE PACKAGE " << pkg->buildName() << std::endl ;
	}

	// Now work through the app & os directories, deleting any files that are not part of an allocated package
	cleanDir(mAppsPath) ;
	cleanDir(mOsPath) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlotMgr::setReadonly(const std::string &slotName, bool readOnly, std::string &error)
{
	// check slot name valid
	std::unique_lock<std::mutex> lock(mMutex) ;
	if (mSlots.find(slotName) == mSlots.end())
	{
		error = "Invalid slot name" ;
		return false ;
	}

	if (!mSlots[slotName]->setReadOnly(readOnly))
	{
		error = "Unable to change read-only setting" ;
		return false ;
	}

	return true ;
}

//=============================================================================================================
// PROTECTED THREAD
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlotMgr::runEvent()
{
	bool done(true) ;
	do
	{
		// get next job
		std::shared_ptr<SwJob> job ;
		{
			std::unique_lock<std::mutex> lock(mMutex) ;

#ifdef DEBUG_SWJOB
			std::cerr << "-- JOBS --" << std::endl ;
			for (auto j : mJobs)
			{
				j->show() ;
			}
			std::cerr << "----------" << std::endl ;
#endif

			if (mJobs.empty())
				break ;

			job = mJobs.front() ;
			mJobs.pop_front() ;

			// see if more to do
			if (!mJobs.empty())
				done = false ;
		}

		// Process this job
		if (job->mType == SwJob::JOB_INSTALL)
		{
			handleInstall(std::dynamic_pointer_cast<SwInstallJob>(job)) ;
			job->showStatus() ;
			continue ;
		}

		if (job->mType == SwJob::JOB_ACTIVATE)
		{
			handleActivate(std::dynamic_pointer_cast<SwActivateJob>(job)) ;
			job->showStatus() ;
			continue ;
		}

		// WTF?!
		std::cerr << "Unexpected job" << std::endl ;

	} while(!done) ;

	return true ;

}

//-------------------------------------------------------------------------------------------------------------
void SoftwareSlotMgr::handleInstall(std::shared_ptr<SwInstallJob> job)
{
	if (!job)
	{
		return ;
	}

	// Move the files
	for (auto pair : job->mFiles)
	{
		if (!Path::fileCopy(pair.first, pair.second))
		{
			job->mError = "Error moving file to install directory" ;
std::cerr << "SoftwareSlotMgr::handleInstall move error " << pair.first << " -> " << pair.second << std::endl ;
			job->mCallback(job->mSlotName, ISoftwareSlotMgr::INSTALL_FILE_ERROR, job->mError) ;
			return ;
		}

		Path::remove(pair.first) ;
	}

	// Create new package & check validity
	std::shared_ptr<SoftwarePackage> pkg( std::make_shared<SoftwarePackage>(mMgrPath, mAppsPath, mOsPath, job->mManifest) ) ;
	if (!pkg->isValid())
	{
		job->mError = "Invalid manifest: software package invalid" ;
		job->mCallback(job->mSlotName, ISoftwareSlotMgr::INSTALL_INTEGRITY_ERROR, job->mError) ;
		return ;
	}

	// Get the package to create md5 files
	if (!pkg->createMd5Files(job->mError))
	{
		job->mCallback(job->mSlotName, ISoftwareSlotMgr::INSTALL_FILE_ERROR, job->mError) ;
		return ;
	}


	// update the package
	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	mPackages.push_back(pkg) ;
	}

	// Update the slot
	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	auto entry(mSlots.find(job->mSlotName)) ;
	if (entry == mSlots.end())
	{
		job->mError = "Slot name became invalid" ;
		job->mCallback(job->mSlotName, ISoftwareSlotMgr::INSTALL_APPLICATION_ERROR, job->mError) ;
		return ;
	}
	std::shared_ptr<ISoftwareSlot> slot(entry->second) ;
	slot->allocatePackage(pkg) ;
	}

	// Call callback notifying that we're complete
	job->mCallback(job->mSlotName, ISoftwareSlotMgr::INSTALL_COMPLETED, "") ;
}

//-------------------------------------------------------------------------------------------------------------
void SoftwareSlotMgr::handleActivate(std::shared_ptr<SwActivateJob> job)
{
	if (!job)
	{
		return ;
	}

	// get the slot & installed files
	std::shared_ptr<ISoftwareSlot> slot ;
	std::shared_ptr<ISoftwarePackage> pkg ;
	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	auto entry(mSlots.find(job->mSlotName)) ;
	if (entry == mSlots.end())
	{
		job->mError = "Slot name became invalid" ;
		job->mCallback(job->mSlotName, ISoftwareSlotMgr::ACTIVATE_APPLICATION_ERROR, 1, job->mError) ;
		return ;
	}
	slot = entry->second ;
	pkg = slot->package() ;

	if (!pkg)
	{
		job->mError = "Slot does not have any allocated package" ;
		job->mCallback(job->mSlotName, ISoftwareSlotMgr::ACTIVATE_APPLICATION_ERROR, 1, job->mError) ;
		return ;
	}
	}

	// Do the loading of these software files
	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	if (!pkg->installImage(job->mTimeoutSecs, job->mError))
	{
		job->mCallback(job->mSlotName, ISoftwareSlotMgr::ACTIVATE_APPLICATION_ERROR, 1, job->mError) ;
		return ;
	}
	}

	// Activate slot
	{
	std::unique_lock<std::mutex> lock(mMutex) ;

	// NOTE: "activating" the slot/package automatically makes any other slot/package inactive
	if (!slot->activate())
	{
		job->mError = "Unable to activate slot" ;
		job->mCallback(job->mSlotName, ISoftwareSlotMgr::ACTIVATE_APPLICATION_ERROR, 1, job->mError) ;
		return ;
	}
	}

	// completed the activation
	job->mCallback(job->mSlotName, ISoftwareSlotMgr::ACTIVATE_COMPLETED, 0, "") ;
	return ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void SoftwareSlotMgr::createDirectories()
{
	Path::mkpath(mAppsPath) ;
	Path::mkpath(mOsPath) ;
	Path::mkpath(mMgrPath) ;
	Path::mkpath(mMgrPath + "/" + SoftwareSlotConstants::ManifestsSubdir) ;
	Path::mkpath(mMgrPath + "/" + SoftwareSlotConstants::SlotsSubdir) ;
	Path::mkpath(mMgrPath + "/" + SoftwareSlotConstants::InvalidSubdir) ;
	Path::mkpath(mMgrPath + "/" + SoftwareSlotConstants::ReadonlySubdir) ;
}

//-------------------------------------------------------------------------------------------------------------
void SoftwareSlotMgr::createPackages()
{
	// Read the manifests directory and create a package for each file
	std::vector<std::string> manifests(Path::dirContents(mMgrPath + "/" + SoftwareSlotConstants::ManifestsSubdir)) ;
	for (auto f : manifests)
	{
		if (!Path::isFile(f))
			continue ;

		std::shared_ptr<SoftwarePackage> pkg( std::make_shared<SoftwarePackage>(mMgrPath, mAppsPath, mOsPath, f) ) ;

		// skip invalid manifest files
		if (!pkg->isValid())
		{
			continue ;
		}

		mPackages.push_back(pkg) ;
	}


}

//-------------------------------------------------------------------------------------------------------------
void SoftwareSlotMgr::createSlots()
{
	// Create the set of empty slots
	for (unsigned i=1; i<=mNumSlots; ++i)
	{
		std::string name("slot" + std::to_string(i)) ;
		std::shared_ptr<SoftwareSlot> slot(std::make_shared<SoftwareSlot>(name, mMgrPath)) ;
		slot->initialise(mPackages) ;
		mSlots[name] = slot ;
	}

	// Check the validity of the slots - make sure each slot is allocated to a unique package
	std::set<std::string> seenPackages ;
	for (auto entry : mSlots)
	{
		if (!entry.second->isAllocated())
			continue ;

		auto pkg(entry.second->package()) ;
		std::string name(pkg->buildName()) ;

		auto seen(seenPackages.find(name)) ;
		seenPackages.insert(name) ;
		if (seen == seenPackages.end())
			continue ;

		// already allocated to this package, so clear
		entry.second->clearPackage() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void SoftwareSlotMgr::cleanDir(const std::string &dir)
{
	std::vector<std::string> contents(Path::dirContents(dir)) ;
	for (auto f : contents)
	{
		// only look at files
		if (!Path::isFile(f))
			continue ;

		// skip md5
		if (f.find(".md5") != std::string::npos)
			continue ;

		// Is this file in any of the packages?
		bool found(false) ;
		for (auto pkg : mPackages)
		{
			if (f == pkg->appPath())
			{
				found = true ;
				break ;
			}
			if (f == pkg->osPath())
			{
				found = true ;
				break ;
			}
		}

		// if it's part of the package then move on
		if (found)
			continue ;

		// Not part of a package so delete it and any md5
//std::cerr << "DELETE FILE: " << f << std::endl ;
		Path::remove(f) ;
		Path::remove(f + ".md5") ;
	}
}
