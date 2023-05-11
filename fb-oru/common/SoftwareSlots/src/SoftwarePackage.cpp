/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwarePackage.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <fstream>
#include <set>

#include "IImageManagement.h"
#include "IOsImage.h"

#include "stringfunc.hpp"
#include "Path.h"
#include "Md5Sum.h"

#include "SoftwareSlotConstants.h"
#include "SoftwarePackage.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Required keywords
//
//vendor=FB
//code=FBOR-12345678
//buildName=ZCU111-FBC-ORANRRH-1.0.0.4#240
//buildId=240
//buildVersion=1.0.0.4
//
//[os]
//fileName=os.ZCU111-local-123-0.0.tgz
//fileVersion=0.0
//path=os.ZCU111-local-123-0.0.tgz
//checksum=993b9a047b5f0b2c9235ded1d6e0c0fc
//
//[app]
//fileName=ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz
//fileVersion=1.0.0.4
//path=ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz
//checksum=76b645e28b0b53122b4428f4ab9eb4b9

std::set<std::string> COMMON_REQUIRED{
	"vendor",
	"code",
	"buildName",
	"buildId",
	"buildVersion",
} ;

std::set<std::string> FILES_REQUIRED{
	"fileName",
	"fileVersion",
	"path",
	"checksum",
} ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SoftwarePackage::SoftwarePackage(const std::string& mgmtPath, const std::string& apps_path, const std::string& os_path,
		const std::string& manifestFile) :
	mMgmtPath(mgmtPath),
	mAppsPath(apps_path),
	mOsPath(os_path),
	mManifestPath(manifestFile),
	mReadOnlyLink(mMgmtPath + "/" + SoftwareSlotConstants::ReadonlySubdir + "/" +Path::basename(mManifestPath)),
	mRunning(false),
	mManifest(mManifestPath),
	mManifestValid(false),
	mMarkedInvalid(false),
	mAppIntegrity(false),
	mOsIntegrity(false)
{
	// check "current" link - the startup setting gives us the current running package
	if (isActive())
		mRunning = true ;

	// Now check for any invalidity link created by the app startup script
	checkValidityLinks() ;


	// Ensure manifest is valid
	checkManifest() ;

	// stop now if not valid
	if (!mManifestValid)
		return ;

	// Calculate the integrity of the files - we need to do this once and cache the results
	// because it takes a few seconds to perform

	Md5Sum appMd5(appPath()) ;
	if ( appMd5.sum() == appChecksum() )
		mAppIntegrity = true ;

	Md5Sum osMd5(osPath()) ;
	if ( osMd5.sum() == osChecksum() )
		mOsIntegrity = true ;

}

//-------------------------------------------------------------------------------------------------------------
SoftwarePackage::~SoftwarePackage()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::manifestPath() const
{
	return mManifestPath ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::activate()
{
	if (appPath().empty())
		return false ;

	auto appImage(IImageManagement::getInstance()->getImage(IImageTypes::IMAGE_APPLICATION)) ;
	return appImage->setCurrent(appFileName()) ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::isActive() const
{
	// check "current" link...
	auto appImage(IImageManagement::getInstance()->getImage(IImageTypes::IMAGE_APPLICATION)) ;
	bool active(appImage->current() == appFileName()) ;

	return active ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::isValid() const
{
	if (! mManifestValid )
	{
		return false ;
	}

	if (! appIntegrity() )
	{
		return false ;
	}

	if (! osIntegrity() )
	{
		return false ;
	}

	if (mMarkedInvalid)
	{
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::isReadOnly() const
{
	if (!Path::isLink(mReadOnlyLink))
	{
		return false ;
	}

	std::string link ;
	if (!Path::readLink(mReadOnlyLink, link))
	{
		return false ;
	}

	if (link != mManifestPath)
	{
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::setReadOnly(bool readOnly)
{
	if (!readOnly)
	{
		// remove any link
		Path::remove(mReadOnlyLink) ;
		return true ;
	}

	// Create link
	return Path::createLink(mReadOnlyLink, mManifestPath) ;
}


//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::isRunning() const
{
	return mRunning ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SoftwarePackage::requiredInstallTimeSecs() const
{
	std::string error ;

	// APP
	auto appImage(IImageManagement::getInstance()->getImage(IImageTypes::IMAGE_APPLICATION)) ;
	appImage->setImageName(appFileName(), error) ;
	unsigned installSecs = appImage->installTimeSecs() ;

	// OS
	auto osImage(IImageManagement::getInstance()->getImage(IImageTypes::IMAGE_ROS)) ;
	osImage->setImageName(osFileName(), error) ;
	std::dynamic_pointer_cast<IOsImage>(osImage)->setUbootInstall(true, error) ;
	installSecs += osImage->installTimeSecs() ;

	return installSecs ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::installImage(unsigned timeoutSecs, std::string &error)
{
	// NOTE: We reuse all the IIimageManagement code. We set the download url to a dummy, just so that it is set to something
	// to prevent errors, but it should never be used as the files are already downloaded and ready to install
	//

	// APP
	auto appImage(IImageManagement::getInstance()->getImage(IImageTypes::IMAGE_APPLICATION)) ;
	if (!appImage->setRemoteUrl("dummy", error))
		return false ;
	if (!appImage->setImageName(appFileName(), error))
		return false ;
	if (!appImage->getAndInstall(error))
		return false ;

	// OS
	auto osImage(IImageManagement::getInstance()->getImage(IImageTypes::IMAGE_ROS)) ;
	if (!osImage->setRemoteUrl("dummy", error))
		return false ;
	if (!osImage->setImageName(osFileName(), error))
		return false ;
	if (!std::dynamic_pointer_cast<IOsImage>(osImage)->setUbootInstall(true, error))
		return false ;
	if (!osImage->getAndInstall(error))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::createMd5Files(std::string &error)
{
	// App
	if (!createMd5(mAppsPath, appFileName(), appChecksum(), error))
		return false ;

	// OS
	if (!createMd5(mOsPath, osFileName(), osChecksum(), error))
		return false ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
void SoftwarePackage::show(std::ostream &os)
{
	os << "PACKAGE " << mManifestPath << std::endl ;
	os << "Build Name.......: " << buildName() << std::endl ;
	os << "Build Id.........: " << buildId() << std::endl ;
	os << "Build Version....: " << buildVersion() << std::endl ;
	os << "Validity.........: " << (isValid() ? "VALID" : "INVALID") << std::endl ;
	os << "Access...........: " << (isReadOnly() ? "READ-ONLY" : "READ-WRITE") << std::endl ;
	os << "Marked Invalid...: " << (mMarkedInvalid ? "INVALID" : "VALID") << std::endl ;
	os << "Vendor Code......: " << vendorCode() << std::endl ;
	os << "Product Code.....: " << productCode() << std::endl ;
	os << "Active...........: " << (isActive() ? "ACTIVE" : "INACTIVE") << std::endl ;
	os << "Running..........: " << (isRunning() ? "RUNNING" : "NOT RUNNING") << std::endl ;
	os << "[app]" << std::endl ;
	os << "File.............: " << appFileName() << std::endl ;
	os << "Version..........: " << appFileVersion() << std::endl ;
	os << "Path.............: " << appPath() << std::endl ;
	os << "Checksum.........: " << appChecksum() << std::endl ;
	os << "Integrity........: " << (appIntegrity() ? "VALID" : "INVALID") << std::endl ;
	os << "[os]" << std::endl ;
	os << "File.............: " << osFileName() << std::endl ;
	os << "Version..........: " << osFileVersion() << std::endl ;
	os << "Path.............: " << osPath() << std::endl ;
	os << "Checksum.........: " << osChecksum() << std::endl ;
	os << "Integrity........: " << (osIntegrity() ? "VALID" : "INVALID") << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::vendorCode() const
{
	return value("vendor") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::productCode() const
{
	return value("code") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::buildName() const
{
	return value("buildName") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::buildId() const
{
	return value("buildId") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::buildVersion() const
{
	return value("buildVersion") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::osFileName() const
{
	return value("os", "fileName") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::osFileVersion() const
{
	return value("os", "fileVersion") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::osPath() const
{
	std::string path( value("os", "path") ) ;
	if (path.empty())
		return "" ;

	return mOsPath + "/" + path ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::osChecksum() const
{
	return toLower(value("os", "checksum")) ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::osIntegrity() const
{
	return mOsIntegrity ;
}


//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::appFileName() const
{
	return value("app", "fileName") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::appFileVersion() const
{
	return value("app", "fileVersion") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::appPath() const
{
	std::string path( value("app", "path") ) ;
	if (path.empty())
		return "" ;

	return mAppsPath + "/" + path ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::appChecksum() const
{
	return toLower(value("app", "checksum")) ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::appIntegrity() const
{
	return mAppIntegrity ;
}



//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void SoftwarePackage::checkManifest()
{
	if (!mManifest.isValid())
		return ;

	// Ensure we have the required fields
	for (auto var : COMMON_REQUIRED)
	{
		if (!mManifest.isVariable(var))
			return ;
	}

	for (auto section : std::set<std::string>{"app", "os"})
	{
		for (auto var : FILES_REQUIRED)
		{
			if (!mManifest.isVariable(section, var))
				return ;
		}
	}

	mManifestValid = true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::value(const std::string &variable) const
{
	if (!mManifest.isValid())
		return "" ;

	return mManifest.value(variable) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwarePackage::value(const std::string &section, const std::string &variable) const
{
	if (!mManifest.isValid())
		return "" ;

	return mManifest.value(section, variable) ;
}

//-------------------------------------------------------------------------------------------------------------
void SoftwarePackage::checkValidityLinks()
{
	// If we don't valid a valid manifest then stop
	if (!mManifest.isValid())
		return ;

	// read the "invalid links" subdirectory and see if any of these link to our app
	std::vector<std::string> contents(Path::dirContents(mMgmtPath + "/" + SoftwareSlotConstants::InvalidSubdir)) ;
	for (auto f : contents)
	{
		if (!Path::isLink(f))
			continue ;

		std::string link ;
		Path::readLink(f, link) ;
		if (!Path::isFile(link))
		{
			// remove broken link
			Path::remove(f) ;
			continue ;
		}

		// Check link for a match with our app
		if (link != appPath())
			continue ;

		// link matches so this app is marked invalid. Final sanity check: if we
		// are the current running app then the link must be bad so remove it
		if (mRunning)
		{
			Path::remove(f) ;
			continue ;
		}

		// definitely marked as bad
		mMarkedInvalid = true ;
	}

}

//-------------------------------------------------------------------------------------------------------------
bool SoftwarePackage::createMd5(const std::string &dir,
		const std::string &packageFile,
		const std::string &md5, std::string &error)
{
	std::string md5File(dir + "/"+ packageFile + ".md5") ;
	if (Path::exists(md5File))
		return true ;

	std::ofstream ofile(md5File, std::ios::trunc) ;
	if (!ofile.is_open())
	{
		error = "Unable to write to MD5 file" ;
		return false ;
	}
	ofile << md5 << " " << packageFile << std::endl ;
	ofile.close() ;

	return true ;
}
