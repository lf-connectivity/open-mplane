/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CalDownload.cpp
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

#include "CalDownload.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Usual (max) time for a download
static const unsigned DEFAULT_DOWNLOAD_TIME(2) ;

// Time out if download takes longer than this
static const unsigned DOWNLOAD_TIMEOUT_TIME(8) ;

std::string CalDownload::CAL_TYPE_SUFFIX{"CalDownload"} ;

//-------------------------------------------------------------------------------------------------------------
static const std::string TEMPDIR{"/tmp/cal"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CalDownload::CalDownload(const std::string& name)  :
	Loggable(name, "CAL"),

	mMutex(),
	mTypeName(""),
	mStatus(CalDownloadStatus::CALDOWNLOAD_IDLE),
    mServerUrl(""),
    mRemoteFileName(""),
    mInstallDir(""),
    mInstallFileName(""),
    mCalDataName(name),
    mStatusObject(IFileStatus::nullObject()),
	mFileMgr(IFileMgr::factory()),
	mTcpTransfer(),
	mPathDates()
{
}

//-------------------------------------------------------------------------------------------------------------
CalDownload::~CalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string CalDownload::getName() const
{
    return mCalDataName;
}

//-------------------------------------------------------------------------------------------------------------
std::string CalDownload::getTypeName() const
{
	if (mTypeName.empty())
	{
		mTypeName = getName() ;

    	// if type name ends with "CalDownload" then remove it
    	std::size_t pos(mTypeName.find(CAL_TYPE_SUFFIX)) ;
    	if (pos != std::string::npos)
    		mTypeName.resize(pos) ;
	}
    return mTypeName;
}


//-------------------------------------------------------------------------------------------------------------
bool CalDownload::initialise(std::string& failReason)
{
	if (!mFileMgr->setTempDir(TEMPDIR, true, true))
	{
		failReason = "Unable to initialise temporary directory " + TEMPDIR ;
		return false ;
	}

	if (!setInstallDir("/nandflash/caldata", failReason))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownload::getAndInstall(const std::string& remoteFilename, std::string& failReason)
{
	return getAndInstall(remoteFilename, IFileStatus::nullObject(), failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownload::getAndInstall(const std::string& remoteFilename, std::shared_ptr<IFileStatus> status, std::string& failReason)
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
	setStatus(CALDOWNLOAD_RUNNING) ;
	{
		// Set the status callback
		setStatusObject(status) ;

		// set remote filename
		mRemoteFileName = remoteFilename ;

		// download the file(s)
		ok = downloadFile(failReason) ;
	}
	setStatus(CALDOWNLOAD_IDLE) ;

	return ok ;
}


//-------------------------------------------------------------------------------------------------------------
bool CalDownload::isRunning() const
{
	CalDownloadStatus status = getStatus() ;
	if (status == CALDOWNLOAD_RUNNING)
		return true ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownload::setRemoteUrl(const std::string& url, std::string& failReason)
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
std::string CalDownload::getInstallFilePath() const
{
	return getInstallDir() + "/" + getInstallFileName() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string CalDownload::getInstallFileName() const
{
	return mInstallFileName ;
}


//-------------------------------------------------------------------------------------------------------------
void CalDownload::show(std::ostream& os) const
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
bool CalDownload::testInjectInstallDir(const std::string& path, std::string& failReason)
{
	return setInstallDir(path, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
void CalDownload::setStatusObject(std::shared_ptr<IFileStatus> status)
{
	mStatusObject = status ;
}

//-------------------------------------------------------------------------------------------------------------
void CalDownload::addPath(unsigned path, const std::string& calDate)
{
	mPathDates[path] = calDate ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::CalDownload::addTemperature(unsigned path, const float& calInitialTemp)
{
	mPathInitialTemps[path] = calInitialTemp ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgrWriter> CalDownload::getCalFileWriter(
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
void CalDownload::startTcpTransfer(TcpCalTransfer calTransfer)
{
	mTcpTransfer = calTransfer ;
}

//-------------------------------------------------------------------------------------------------------------
void CalDownload::endTcpTransfer()
{
	mTcpTransfer = TcpCalTransfer() ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool CalDownload::setInstallFileName(const std::string& name, std::string& failReason)
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
bool CalDownload::setInstallDir(const std::string& dir,
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
std::shared_ptr<IFileStatus> CalDownload::getStatusObject(void) const
{
	return mStatusObject ;
}

//-------------------------------------------------------------------------------------------------------------
CalDownload::CalDownloadStatus CalDownload::getStatus() const
{
	Mutex::Lock lock(mMutex) ;
	return mStatus ;
}

//-------------------------------------------------------------------------------------------------------------
void CalDownload::setStatus(const CalDownloadStatus& status)
{
	Mutex::Lock lock(mMutex) ;
	mStatus = status ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownload::downloadFile(std::string& failReason)
{
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;

	// TCP transfer
	if (mTcpTransfer)
	{
//		std::cerr << "CalDownload::downloadFile() - start TCP transfer..." << std::endl ;

		// do the transfer
		std::string tempFilename = TEMPDIR + "/" + mInstallFileName ;
		statusObj->start("TCP", tempFilename) ;
		bool ok = mTcpTransfer() ;
//		keepAlive() ;

//		std::cerr << "CalDownload::downloadFile() - TCP transfer done ok=" << ok << std::endl ;

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

//std::cerr << "CalDownload::downloadFile() file=" << mInstallFileName <<
//	" dir=" << mInstallDir <<
//	" url=" << url <<
//	" FileMgr.dir=" << mFileMgr->getDir() <<
//	" FileMgr.tempDir=" << mFileMgr->getTempDir() <<
//	std::endl ;

	if (!mFileMgr->download(url, mInstallFileName, statusObj))
	{
		failReason = mFileMgr->getError() ;
		return false ;
	}
//	keepAlive() ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CalDownload::checkData(const std::string& remoteFilename, std::string& failReason) const
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

void Mplane::CalDownload::showTemperatures(std::ostream& os) const
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
	}
	else
	{
		os << "(No file)" ;
	}

	os << std::endl ;

	// Show initial temperatures for each path
	for (auto entry : mPathInitialTemps)
	{
		std::string initTemperature = std::to_string(entry.second);

		os << "  Path " << entry.first << ": " <<  initTemperature << " degC"<< std::endl ;
	}
}
