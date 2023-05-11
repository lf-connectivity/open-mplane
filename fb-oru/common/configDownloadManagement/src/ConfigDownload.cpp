/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ConfigDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>
#include <string.h>

#include <set>
#include <memory>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <string>

#include "stringfunc.hpp"
#include "Path.h"
#include "SystemTask.h"

#include "ConfigDownload.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Usual (max) time for a download
static const unsigned DEFAULT_DOWNLOAD_TIME(2) ;

// Time out if download takes longer than this
static const unsigned DOWNLOAD_TIMEOUT_TIME(8) ;

std::string ConfigDownload::CONFIG_TYPE_SUFFIX{"ConfigDownload"} ;

//-------------------------------------------------------------------------------------------------------------
static const std::string TEMPDIR{"/tmp/config"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ConfigDownload::ConfigDownload(const std::string& name)  :
	Loggable(name, "CONFIG"),

	mMutex(),
	mTypeName(""),
	mStatus(ConfigDownloadStatus::CONFIGDOWNLOAD_IDLE),
    mServerUrl(""),
    mRemoteFileName(""),
    mInstallDir(""),
    mInstallFileName(""),
    mConfigDataName(name),
    mStatusObject(IFileStatus::nullObject()),
	mFileMgr(IFileMgr::factory()),
	mTcpTransfer(),
	mPathDates()
{
}

//-------------------------------------------------------------------------------------------------------------
ConfigDownload::~ConfigDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string ConfigDownload::getName() const
{
    return mConfigDataName;
}

//-------------------------------------------------------------------------------------------------------------
std::string ConfigDownload::getTypeName() const
{
	if (mTypeName.empty())
	{
		mTypeName = getName() ;

    	// if type name ends with "ConfigDownload" then remove it
    	std::size_t pos(mTypeName.find(CONFIG_TYPE_SUFFIX)) ;
    	if (pos != std::string::npos)
    		mTypeName.resize(pos) ;
	}
    return mTypeName;
}


//-------------------------------------------------------------------------------------------------------------
bool ConfigDownload::initialise(std::string& failReason)
{
	if (!mFileMgr->setTempDir(TEMPDIR, true, true))
	{
		failReason = "Unable to initialise temporary directory " + TEMPDIR ;
		return false ;
	}

	if (std::string(CFG_DATA_PATH).empty())
		throw std::runtime_error("CFG_DATA_PATH must be set in the projects CMakeLists.txt file.");

	if (!setInstallDir(CFG_DATA_PATH, failReason))
	{
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ConfigDownload::getAndInstall(const std::string& remoteFilename, std::string& failReason)
{
	return getAndInstall(remoteFilename, IFileStatus::nullObject(), failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ConfigDownload::getAndInstall(const std::string& remoteFilename, std::shared_ptr<IFileStatus> status, std::string& failReason)
{
	// reject download if currently running
	if (isRunning())
	{
		failReason.assign("Another download already running");
		return false ;
	}

	logDebugVerbose("getAndInstall %s", remoteFilename.c_str()) ;

	// check that required values have been set
	if (!checkData(remoteFilename, failReason))
		return false ;

	// Mark this section as running so that no other instance can interrupt
	bool ok = true ;
	setStatus(CONFIGDOWNLOAD_RUNNING) ;
	{
		// Set the status callback
		setStatusObject(status) ;

		// set remote filename
		mRemoteFileName = remoteFilename ;

		// download the file(s)
		ok = downloadFile(failReason) ;
	}
	setStatus(CONFIGDOWNLOAD_IDLE) ;

	return ok ;
}


//-------------------------------------------------------------------------------------------------------------
bool ConfigDownload::isRunning() const
{
	ConfigDownloadStatus status = getStatus() ;
	if (status == CONFIGDOWNLOAD_RUNNING)
		return true ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool ConfigDownload::setRemoteUrl(const std::string& url, std::string& failReason)
{
	if (isRunning())
	{
		failReason.assign("Download currently running");
		return false ;
	}

	mServerUrl.assign(url) ;
	logDebugVerbose("Remote url=%s", mServerUrl.c_str()) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ConfigDownload::getInstallFilePath() const
{
	return getInstallDir() + "/" + getInstallFileName() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ConfigDownload::getInstallFileName() const
{
	return mInstallFileName ;
}


//-------------------------------------------------------------------------------------------------------------
void ConfigDownload::show(std::ostream& os) const
{
	std::string type(getTypeName()) ;
	static const unsigned TYPE_WIDTH{15} ;
	os << padLeft(type, TYPE_WIDTH, '.') << ": " ;

	std::string path(getInstallFilePath()) ;
	if (Path::exists(path))
	{
		static const unsigned FILE_WIDTH{30} ;
		std::string filename(getInstallFileName()) ;
		os << padLeft(filename, FILE_WIDTH, ' ') << " " ;
		os << Path::fileSize(path) << " bytes" ;
	}
	else
	{
		os << "(No file)" ;
	}

	os << std::endl ;

	// Show date for each path
	for (auto entry : mPathDates)
	{
		os << "  Path " << entry.first << ": " << entry.second << std::endl ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool ConfigDownload::testInjectInstallDir(const std::string& path, std::string& failReason)
{
	return setInstallDir(path, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
void ConfigDownload::setStatusObject(std::shared_ptr<IFileStatus> status)
{
	mStatusObject = status ;
}

//-------------------------------------------------------------------------------------------------------------
void ConfigDownload::addPath(unsigned path, const std::string& calDate)
{
	mPathDates[path] = calDate ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgrWriter> ConfigDownload::getConfigFileWriter(
		std::shared_ptr<IFileStatus> statusObj, unsigned fileSize,
		std::string& failReason)
{
	// Start the TCP port transfer using default name. If IFileMgrWriter is null then there's an error
	std::shared_ptr<IFileMgrWriter> fileWriter( mFileMgr->portTransferStart(mInstallFileName, fileSize, statusObj) ) ;
	if (!fileWriter)
		failReason = mFileMgr->getError() ;
	return fileWriter ;
}

//-------------------------------------------------------------------------------------------------------------
void ConfigDownload::startTcpTransfer(TcpConfigTransfer configTransfer)
{
	mTcpTransfer = configTransfer ;
}

//-------------------------------------------------------------------------------------------------------------
void ConfigDownload::endTcpTransfer()
{
	mTcpTransfer = TcpConfigTransfer() ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool ConfigDownload::setInstallFileName(const std::string& name, std::string& failReason)
{
	if (isRunning())
	{
		failReason.assign("Download currently running");
		return false ;
	}

	mInstallFileName.assign(name) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ConfigDownload::setInstallDir(const std::string& dir,
		std::string& failReason)
{
	if (isRunning())
	{
		failReason.assign("Download currently running");
		return false ;
	}

	mInstallDir.assign(dir) ;
	if (!mFileMgr->setDir(mInstallDir, true))
	{
		failReason = "Unable to initialise install directory " + mInstallDir ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileStatus> ConfigDownload::getStatusObject(void) const
{
	return mStatusObject ;
}

//-------------------------------------------------------------------------------------------------------------
ConfigDownload::ConfigDownloadStatus ConfigDownload::getStatus() const
{
	Mutex::Lock lock(mMutex) ;
	return mStatus ;
}

//-------------------------------------------------------------------------------------------------------------
void ConfigDownload::setStatus(const ConfigDownloadStatus& status)
{
	Mutex::Lock lock(mMutex) ;
	mStatus = status ;
}

//-------------------------------------------------------------------------------------------------------------
bool ConfigDownload::downloadFile(std::string& failReason)
{
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;

	// TCP transfer
	if (mTcpTransfer)
	{
		// do the transfer
		std::string tempFilename = TEMPDIR + "/" + mInstallFileName ;
		statusObj->start("TCP", tempFilename) ;
		bool ok = mTcpTransfer() ;

		if (!ok)
		{
			failReason = "Unable to transfer file over TCP" ;
			statusObj->fail(failReason) ;
			return false ;
		}

		// Move file
		std::string destFilename = mInstallDir + "/" + mInstallFileName ;
		ok = Path::fileCopy(tempFilename, destFilename) ;
		Path::remove(tempFilename) ;
		if (!ok)
		{
			failReason = std::string("Failed to save file ") + mInstallFileName ;
			statusObj->fail(failReason) ;
			return false ;
		}

		statusObj->end() ;
		return true ;
	}

	// Normal url download
	std::string url = mServerUrl + "/" + mRemoteFileName ;

	if (!mFileMgr->download(url, mInstallFileName, statusObj))
	{
		failReason = mFileMgr->getError() ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ConfigDownload::checkData(const std::string& remoteFilename, std::string& failReason) const
{
	if (remoteFilename.empty())
	{
		failReason = "Remote file name not set" ;
		return false ;
	}
	if (mInstallFileName.empty())
	{
		failReason = "Install file name not set" ;
		return false ;
	}
	if (mInstallDir.empty())
	{
		failReason = "Install directory not set" ;
		return false ;
	}
	if (mServerUrl.empty())
	{
		failReason = "Server URL not set" ;
		return false ;
	}

	return true ;
}
