/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CalDownloadManagement.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <vector>

#include "stringfunc.hpp"

#include "CalDownload.h"
#include "CalDownloadManagement.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Set the priority of the task to 1 above lowest
static constexpr int MANAGER_PRIORITY = Task::PRIORITY_MIN + 1 ;

// tick time in ms
static const unsigned TASK_TICK_MS = 500 ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CalDownloadManagement::CalDownloadManagement() :
	Task(MANAGER_PRIORITY, Task::MEDIUM_STACK, "Cal Download Mgr", "CAL"),

	mTaskRunning(true),
	mServerUrl(""),
	mInjectedInstallDir(""),
	mMutex(),
	mIsDownloading(false),
	mTypeDownloading(),
	mFileName(""),
	mCondEnd( std::shared_ptr<Conditional>() ),
	mDownload( std::shared_ptr<ICalDownload>() ),
	mDownloadOk(true),
	mDownloadFailReason(""),
	mStatusObject( IFileStatus::nullObject() ),
    mDownloadDoneCallback(),

	mCondStart()
{
}


//-------------------------------------------------------------------------------------------------------------
CalDownloadManagement::~CalDownloadManagement()
{
	shutdown() ;
}

//-------------------------------------------------------------------------------------------------------------
void CalDownloadManagement::shutdown(void)
{
	mTaskRunning = false ;
	msSleep(2*TASK_TICK_MS) ;
}


//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::getAndInstall(const std::string& typeName,
		const std::string& _fileName, std::shared_ptr<IFileStatus> status,
		std::string& failReason, std::shared_ptr<Conditional> endSignal)
{
	if (_fileName.empty())
	{
		failReason = "Filename not set" ;
		return false ;
	}

	// If image name contains a url, then set url
	std::string fileName(_fileName);
	std::size_t pos(fileName.find_last_of('/')) ;
	if (pos != std::string::npos)
	{
		if (!setRemoteUrl( fileName.substr(0, pos), failReason ))
			return false ;

		fileName = fileName.substr(pos+1) ;
	}

	Mutex::Lock lock(mMutex) ;

	// check settings
	if (mServerUrl.empty())
	{
		failReason = "Remote URL not set" ;
		return false ;
	}


	// Get state and mark as downloading if idle
	if (mIsDownloading)
	{
		failReason = "Cannot start a new download until existing download completes" ;
		return false ;
	}

	auto calDownload(getCalDownload(typeName)) ;
	if (!calDownload)
	{
		failReason = "Cal type " + typeName + " not installed" ;
		return false ;
	}

	mTypeDownloading = typeName ;
	mIsDownloading = true ;

	// Grab settings for download task
	mFileName = fileName ;
	mCondEnd = endSignal ;
	mDownloadOk = true ;
	mDownloadFailReason.clear() ;
	mDownload = calDownload ;
	mDownloadDoneCallback = std::function<void(void)>() ;

	// Set up the status reporting object
	setStatusObject(status) ;
	status->restart(1) ;

	// Initiate download
	Conditional::Lock condLock(mCondStart) ;
	mCondStart.signal() ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::getAndInstall(const std::string& typeName,
		std::shared_ptr<IFileStatus> status,
		std::string& failReason, std::shared_ptr<Conditional> endSignal)
{
	return getAndInstall(typeName, getInstallFileName(typeName), status, failReason, endSignal) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::getAndInstall(const std::string& typeName,
		const std::string& fileName, std::string& failReason,
		std::shared_ptr<Conditional> endSignal)
{
	return getAndInstall(typeName, fileName, IFileStatus::nullObject(), failReason, endSignal) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::getAndInstall(const std::string& typeName,
		std::string& failReason,
		std::shared_ptr<Conditional> endSignal)
{
	return getAndInstall(typeName, getInstallFileName(typeName), IFileStatus::nullObject(), failReason, endSignal) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::getAndInstall(const std::string& typeName,
		const std::string& fileName, std::shared_ptr<IFileStatus> status,
		std::string& failReason)
{
	// Create Conditional
    std::shared_ptr<Conditional> endSignal(new Conditional) ;

	// run download
	if (!getAndInstall(typeName, fileName, status, failReason, endSignal))
		return false ;

	// Wait for completion
    endSignal->wait() ;

    // Check for error
    return isDownloadOk(failReason) ;

}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::getAndInstall(const std::string& typeName,
		std::shared_ptr<IFileStatus> status,
		std::string& failReason)
{
	// Create Conditional
    std::shared_ptr<Conditional> endSignal(new Conditional) ;

	// run download
	if (!getAndInstall(typeName, getInstallFileName(typeName), status, failReason, endSignal))
		return false ;

	// Wait for completion
    endSignal->wait() ;

    // Check for error
    return isDownloadOk(failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::getAndInstall(const std::string& typeName,
		const std::string& fileName, std::string& failReason)
{
	// Create Conditional
    std::shared_ptr<Conditional> endSignal(new Conditional) ;

	// run download
	if (!getAndInstall(typeName, fileName, IFileStatus::nullObject(), failReason, endSignal))
		return false ;

	// Wait for completion
    endSignal->wait() ;

    // Check for error
    return isDownloadOk(failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::getAndInstall(const std::string& typeName,
		std::string& failReason)
{
	// Create Conditional
    std::shared_ptr<Conditional> endSignal(new Conditional) ;

	// run download
	if (!getAndInstall(typeName, getInstallFileName(typeName), IFileStatus::nullObject(), failReason, endSignal))
		return false ;

	// Wait for completion
    endSignal->wait() ;

    // Check for error
    return isDownloadOk(failReason) ;
}



//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::isDownloading(void) const
{
	Mutex::Lock lock(mMutex) ;
	return mIsDownloading ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::isDownloadOk(std::string& failReason) const
{
	Mutex::Lock lock(mMutex) ;
	if (!mDownloadOk)
		failReason.assign(mDownloadFailReason) ;
	return mDownloadOk ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::setRemoteUrl(const std::string& url, std::string& failReason)
{
	Mutex::Lock lock(mMutex) ;
	if (mIsDownloading)
	{
		failReason = "Unable to change server url while download is in progress" ;
		return false ;
	}

	return setRemoteUrlNoMutex(url, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string CalDownloadManagement::getRemoteUrl()
{
	return mServerUrl ;
}

//-------------------------------------------------------------------------------------------------------------
void CalDownloadManagement::showDetail(std::ostream& os) const
{
}

//-------------------------------------------------------------------------------------------------------------
void CalDownloadManagement::show(std::ostream& os) const
{
	for (auto cs : mCalDownloadMap)
	{
		cs.second->show(os) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void CalDownloadManagement::show(const std::string& typeName, std::ostream& os) const
{
	auto calDownload(getCalDownload(typeName)) ;
	if (!calDownload)
		return ;
	calDownload->show(os) ;
}

void Mplane::CalDownloadManagement::showTemperatures(std::ostream& os) const
{
	for (auto cs : mCalDownloadMap)
	{
		cs.second->showTemperatures(os) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
std::string CalDownloadManagement::getInstallFileName(const std::string& typeName) const
{
	auto calDownload(getCalDownload(typeName)) ;
	if (!calDownload)
		return "";
	return calDownload->getInstallFileName() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string CalDownloadManagement::getInstallFilePath(const std::string& typeName) const
{
	auto calDownload(getCalDownload(typeName)) ;
	if (!calDownload)
		return "";
	return calDownload->getInstallFilePath() ;
}



//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::testInjectInstallDir(const std::string& path, std::string& failReason)
{
	Mutex::Lock lock(mMutex) ;
	mInjectedInstallDir = path ;
	for (auto& cs : mCalDownloadMap)
	{
		if (!cs.second->testInjectInstallDir(path, failReason))
			return false ;
	}
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::addCalDownloadType( std::shared_ptr<ICalDownload> calDownLoad )
{
	Mutex::Lock lock(mMutex) ;
    mCalDownloadMap[ toUpper(calDownLoad->getName()) ] = calDownLoad;
    std::string failReason ;
    bool ok ;
    ok = calDownLoad->initialise(failReason) ;

    if (!mInjectedInstallDir.empty())
    	if (!calDownLoad->testInjectInstallDir(mInjectedInstallDir, failReason))
    		return false ;

    return ok;
}


//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<ICalDownload> > CalDownloadManagement::getCalDowloadObjects()
{
    std::vector<std::shared_ptr<ICalDownload>> calDownloads;
    calDownloads.reserve( mCalDownloadMap.size() );

    for( auto calDownload : mCalDownloadMap)
    {
        calDownloads.push_back( calDownload.second );
    }

    return calDownloads;
}

//-------------------------------------------------------------------------------------------------------------
std::set<std::string> CalDownloadManagement::getTypes() const
{
    std::set<std::string> types;

    for( auto calDownload : mCalDownloadMap)
    {
        types.insert(calDownload.second->getTypeName());
    }
    return types;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgrWriter> CalDownloadManagement::getCalFileWriter(
		const std::string& typeName, std::shared_ptr<IFileStatus> statusObj,
		unsigned fileSize, std::string& failReason)
{
	auto icalDownload( getCalDownload(typeName) ) ;
	if (!icalDownload)
	{
		failReason = "Invalid type" ;
		return std::shared_ptr<IFileMgrWriter>() ;
	}

	std::shared_ptr<CalDownload> calDownload(std::dynamic_pointer_cast<CalDownload>(icalDownload)) ;
	return calDownload->getCalFileWriter(statusObj, fileSize, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::calInstall(const std::string& typeName,
		std::shared_ptr<IFileStatus> status, ImageCalWrite calWriteFunc,
		ImageCalComplete calCompleteFunc, std::string& failReason)
{
	Mutex::Lock lock(mMutex) ;

	// Get state and mark as downloading if idle
	if (mIsDownloading)
	{
		failReason = "Cannot start a new download until existing download completes" ;
		return false ;
	}

	if (!calWriteFunc)
	{
		failReason = "Internal error" ;
		return false ;
	}

	// Ensure that the url is set - if we set a dummy, clean up afterwards
	bool cleanUrl(false) ;
	if (mServerUrl.empty())
	{
		if (!setRemoteUrlNoMutex( "tcp-download", failReason ))
			return false ;
		cleanUrl = true ;
	}

	auto calDownload(getCalDownload(typeName)) ;
	if (!calDownload)
	{
		failReason = "Cal type " + typeName + " not installed" ;
		return false ;
	}


	mTypeDownloading = typeName ;
	mIsDownloading = true ;

	// Grab settings for download task
	mFileName = "dummy.xml" ;
	mDownloadOk = true ;
	mDownloadFailReason.clear() ;
	mDownload = calDownload ;
	mStatusObject = status ;

	// Tell cal to use TCP to transfer data
//	std::shared_ptr<CalDownload> calDownload(std::dynamic_pointer_cast<CalDownload>(mDownload)) ;
	mDownloadDoneCallback = [this, calCompleteFunc, cleanUrl](void) {
		// Tell cal to stop TCP transfer
		mDownload->endTcpTransfer() ;

		// Clean up url if required
		std::string dummy ;
		if (cleanUrl)
			setRemoteUrlNoMutex( "", dummy ) ;

		// Call callback
		if (calCompleteFunc)
			calCompleteFunc() ;
	} ;

	// Tell cal object to use TCP to transfer data
	mDownload->startTcpTransfer(calWriteFunc) ;

	// Set up the status reporting object
	setStatusObject(status) ;
	status->restart(1) ;

	// Initiate download
	Conditional::Lock condLock(mCondStart) ;
	mCondStart.signal() ;

	return true ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int CalDownloadManagement::run()
{
	/*
	 * Now our thread is running we just enter an infinite loop so we never end.
	 * ALl image management is triggered by invocation of class methods, which are explicit action requests.
	 */
	while (mTaskRunning)
	{
		// keep this task alive
		kickSoftwareWatchdog();

		// Wait for timeout or start of download
		if (mCondStart.wait(TASK_TICK_MS) == true)
		{
            logDebugNormal("CalDownloadManagement - start download : Type=%s", mTypeDownloading.c_str()) ;

			// run download
			mDownloadOk = mDownload->getAndInstall(mFileName, mStatusObject, mDownloadFailReason) ;

        	// Finish with status
        	if (mDownloadOk)
        		mStatusObject->success() ;
        	else
        		mStatusObject->fail(mDownloadFailReason) ;

        	// run the callback if set
        	if (mDownloadDoneCallback)
        		mDownloadDoneCallback() ;

        	// tidy up
        	setStatusObject(IFileStatus::nullObject()) ;

        	// Signal end
        	if (mCondEnd.get())
        	{
        		Conditional::Lock lock(*mCondEnd) ;
        		mCondEnd->signal() ;
        	}

			// Switch back to idle state
			setState(false, "") ;

			logDebugNormal("CalDownloadManagement - download complete ok=%d (%s)", mDownloadOk, mDownloadFailReason.c_str() ) ;
		}
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::getState(std::string& typeName) const
{
	Mutex::Lock lock(mMutex) ;
	typeName = mTypeDownloading ;
	return mIsDownloading ;
}

//-------------------------------------------------------------------------------------------------------------
void CalDownloadManagement::setState(bool downloading, const std::string& typeName)
{
	Mutex::Lock lock(mMutex) ;
	mTypeDownloading = typeName ;
	mIsDownloading = downloading ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICalDownload> CalDownloadManagement::getCalDownload(const std::string& typeName) const
{
	// ICalDownload name suffix - can be stripped off
	static const std::string CAL_SUFFIX_UC{toUpper(CalDownload::CAL_TYPE_SUFFIX)} ;

	std::string ucTypeName(toUpper(typeName)) ;

	// See if uppercase version of the specified type is in the map
	auto cd(mCalDownloadMap.find(ucTypeName)) ;
	if (cd != mCalDownloadMap.end())
		return mCalDownloadMap.at( ucTypeName ) ;

	// Not present so attempt to find <name>Download
	ucTypeName += CAL_SUFFIX_UC ;
	cd = mCalDownloadMap.find(ucTypeName) ;
	if (cd != mCalDownloadMap.end())
		return mCalDownloadMap.at( ucTypeName ) ;

	return std::shared_ptr<ICalDownload>() ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownloadManagement::setRemoteUrlNoMutex(const std::string& url, std::string& failReason)
{
	mServerUrl = url ;
	for (auto& cs : mCalDownloadMap)
	{
		cs.second->setRemoteUrl(url, failReason) ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::CalDownloadManagement::setStatusObject(std::shared_ptr<IFileStatus> status)
{
    mStatusObject = status ;
	for (auto& cs : mCalDownloadMap)
	{
		cs.second->setStatusObject(status) ;
	}
}
