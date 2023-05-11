/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileMgr.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <string.h>

#include <stdexcept>
#include <algorithm>

#include "stringfunc.hpp"
#include "SystemTask.h"
#include "Path.h"
#include "FileMgr.h"

using namespace Mplane;

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgr> IFileMgr::factory()
{
	return std::make_shared<FileMgr>() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgr> IFileMgr::factory(const std::string& dir)
{
	return std::make_shared<FileMgr>(dir) ;
}


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Usual (max) time for a download
static const unsigned DEFAULT_DOWNLOAD_TIME(10) ;

// Time out if download takes longer than this
static const unsigned DOWNLOAD_TIMEOUT_TIME(60) ;

// Where to download temp files
static const std::string TEMP_DIR{"/tmp"} ;


//=============================================================================================================
// CLASSES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// File writer
class FileMgrWriter : public virtual IFileMgrWriter {
public:
	FileMgrWriter(const std::string& filepath,
			unsigned fileSize,
			std::shared_ptr<IFileStatus> fileStatus = IFileStatus::nullObject()) :
		mFd(-1),
		mFileSize(fileSize),
		mFileStatus(fileStatus),
		mTotalWritten(0)
	{
		mFd = ::open(filepath.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) ;
	}

	virtual ~FileMgrWriter()
	{
		if (mFd > 0)
			::close(mFd) ;
	}

	/**
	 * Append new data to the file
	 * @return false on error
	 */
	virtual bool addData(const std::vector<uint8_t>& data) override
	{
		if (mFd <= 0)
			return false ;

		unsigned size(data.size()) ;
		unsigned written = ::write(mFd, &data[0], size) ;
		mTotalWritten += written ;

//std::cerr << "Written " << mTotalWritten << " / " << mFileSize << std::endl ;

		mFileStatus->progress(mTotalWritten * 100 / mFileSize) ;

		if (written < size)
		{
			mFileStatus->fail("Failed to write file") ;
			return false ;
		}

		if (mTotalWritten >= mFileSize)
			mFileStatus->end() ;

		return true ;
	}

	/**
	 * Change the status object used during the file write
	 * @param status
	 */
	virtual void setStatusObject(std::shared_ptr<IFileStatus> status) override
	{
		mFileStatus = status ;
	}

private:
	int mFd ;
	unsigned mFileSize ;
	std::shared_ptr<IFileStatus> mFileStatus ;
	unsigned mTotalWritten ;
};


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FileMgr::FileMgr() :
	mDir(""),
	mTempDir(TEMP_DIR),
	mError(""),
	mFilename(""),
	mUrl(""),
	mTempFilepath(""),
	mDestFilepath("")
{
}

//-------------------------------------------------------------------------------------------------------------
FileMgr::FileMgr(const std::string& dir) :
	mDir(dir),
	mTempDir(TEMP_DIR),
	mError(""),
	mFilename(""),
	mUrl(""),
	mTempFilepath(""),
	mDestFilepath("")
{
	if (!Path::isDir(mDir))
		throw std::runtime_error(mDir + " is not a valid directory") ;
}

//-------------------------------------------------------------------------------------------------------------
FileMgr::~FileMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
bool FileMgr::setDir(const std::string& dir, bool mkdir)
{
	// create path if necessary
	if (mkdir)
	{
		if (!Path::exists(dir))
		{
			if (Path::mkpath(dir) != 0)
			{
				setError("Unable to create path " + dir) ;
				return false ;
			}
		}
	}

	// check path
	if (!Path::isDir(dir))
	{
		setError(dir + " is not a valid directory") ;
		return false ;
	}

	// Set
	mDir = dir ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileMgr::setTempDir(const std::string& dir, bool mkdir, bool clear)
{
	// create path if necessary
	if (mkdir)
	{
		if (!Path::exists(dir))
		{
			if (Path::mkpath(dir) != 0)
			{
				setError("Unable to create temporary path " + dir) ;
				return false ;
			}
		}
	}

	// check path
	if (!Path::isDir(dir))
	{
		setError(dir + " is not a valid directory") ;
		return false ;
	}

	// Clear out contents if necessary
	if (clear)
	{
		if (!Path::removeDirContents(dir, true))
		{
			setError("Unable to clear temporary directory " + dir) ;
			return false ;
		}
	}

	// Set
	mTempDir = dir ;
	return true ;
}



//-------------------------------------------------------------------------------------------------------------
std::string FileMgr::getDir() const
{
	return mDir ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileMgr::getTempDir() const
{
	return mTempDir ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> FileMgr::listFiles()
{
	if (mDir.empty())
	{
		setError("Directory not set") ;
		return std::vector<std::string>() ;
	}

	// get dir contents
	std::vector<std::string> contents(Path::dirContents(mDir)) ;
	std::sort(contents.begin(), contents.end()) ;

	// scan contents
	std::vector<std::string> files ;
	for (auto content : contents)
	{
		// only report files
		if (!Path::isFile(content))
			continue ;

		// save filename base
		files.push_back(Path::basename(content)) ;
	}


	return files ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileMgr::delfile(const std::string& name)
{
	std::vector<std::string> files(listFiles()) ;
	if (files.empty())
	{
		setError("No files to delete") ;
		return false ;
	}

	// Special case of '*'
	if (name == "*")
	{
		// delete all
		for (auto file : files)
		{
			// keep deleting the first file in the list
			if (!del(0))
				return false ;
		}
		return true ;
	}

	// Handle regexp - only handle the use of '*' as wildcard at end of name
	if (name.find("*") != std::string::npos)
	{
		// What I should be able to do here is create a std::regex string and use it, but there's a bug
		// in libstdc++ regex anchor handling (though not in the C lib suprisingly!) so I can't use
		// regex like "^LTE_.*$". Turns out they've known about it since 2012 - see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=53631
		//
		// Basically they've deleted all bugs related to the piss poor regex implementation as being a duplicate of this one
		// and then marked this as being "RESOLVED FIXED" because they can't be arsed to actually implement the required code.
		// Wish we could get away with that sort of nonsense!
		//
		// As such the regex is f**king useless! So, to save us from wantonly deleting everything I've limited
		// support to just matching with the start of a string.
		//
		// I've added all this guff in the comments because I've just p*ssed away around an hour of my life trying to work out
		// what I was doing wrong, only to find out it's the library. Not that I'm at all annoyed about this!
		//
		std::size_t pos(name.find("*")) ;
		std::string regexpStr(name.substr(0, pos)) ;
		regexpStr = toLower(regexpStr) ;

		if (!name.substr(pos+1).empty())
		{
			setError("Invalid wildcard expression, must be of the form: <name>*") ;
			return false ;
		}

		std::vector<std::string> toDelete ;
		for (auto file : files)
		{
			std::string lcfile(toLower(file)) ;
			if (lcfile.find(regexpStr) == 0)
				toDelete.push_back(file) ;
		}

		// Stop now if empty
		if (toDelete.empty())
		{
			setError("No matching files") ;
			return false ;
		}

		// Delete them
		for (auto file : toDelete)
		{
			if (!del(file))
				return false ;
		}

		return true ;
	}

	// Just treat the name as a full filename for now
	return del(name) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileMgr::del(unsigned fileIndex)
{
	std::string filename(indexToFilename(fileIndex)) ;
	if (filename.empty())
		return false ;

	return del(filename) ;
}


//-------------------------------------------------------------------------------------------------------------
bool FileMgr::del(const std::string& filename)
{
	if (mDir.empty())
	{
		setError("Directory not set") ;
		return false ;
	}

	std::string path(Path::join(mDir, filename)) ;
	if (!Path::isFile(path))
	{
		setError("Invalid filename") ;
		return false ;
	}

	if (::unlink(path.c_str()) != 0)
	{
		setError("Unable to delete file") ;
		return false ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileMgr::getError()
{
	std::string error("") ;
	std::swap(error, mError) ;
	return error ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileMgr::download(const std::string& url, const std::string& filename)
{
	return download(url, filename, IFileStatus::nullObject());
}

//-------------------------------------------------------------------------------------------------------------
bool FileMgr::download(const std::string& url, const std::string& filename, std::shared_ptr<IFileStatus> status)
{
	if (!downloadStart(filename))
		return false ;

	// create the wget command
	mUrl = url ;
	std::string wgetCmd = std::string("wget -q -O ") + mTempFilepath + " " + mUrl ;

	// do the download
	status->operation("Download") ;
	status->start(filename) ;

	bool timedOut(false) ;
    std::shared_ptr<SystemTask> systemTask(std::make_shared<SystemTask>() ) ;
    systemTask->start();

	int ret = systemTask->runCmd(wgetCmd,
		[status](unsigned progress) {
			status->progress(progress) ;
		},
		DEFAULT_DOWNLOAD_TIME,
		DOWNLOAD_TIMEOUT_TIME,
		timedOut);

	status->end() ;

	bool error(ret != 0) ;
	return downloadComplete(error, timedOut) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgrWriter> FileMgr::portTransferStart(const std::string& filename, unsigned fileSize)
{
	return portTransferStart(filename, fileSize, IFileStatus::nullObject()) ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgrWriter> FileMgr::portTransferStart(const std::string& filename,
		unsigned fileSize, std::shared_ptr<IFileStatus> fileStatus)
{
	// if not enough space then stop now
	if (!isFreeFileSpace(mDir, fileSize))
		return std::shared_ptr<IFileMgrWriter>() ;

	// initiate download - removes any existing files
	if (!downloadStart(filename))
		return std::shared_ptr<IFileMgrWriter>() ;

	// Create the file writer
	std::shared_ptr<IFileMgrWriter> fileWriter(std::make_shared<FileMgrWriter>(mTempFilepath, fileSize, fileStatus)) ;
	return fileWriter ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileMgr::portTransferEnd(bool ok)
{
	return downloadComplete(!ok, false) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned long long FileMgr::dirFreeSpace() const
{
	if (mDir.empty())
		return 0 ;

	return Path::freeSpace(mDir) ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string FileMgr::indexToFilename(unsigned index)
{
	std::vector<std::string> files(listFiles()) ;
	if (files.empty() || index >= files.size())
	{
		setError("File index not found") ;
		return "" ;
	}

	return files[index] ;
}

//-------------------------------------------------------------------------------------------------------------
void FileMgr::setError(const std::string& error)
{
	if (!mError.empty())
		mError.append("\n") ;
	mError.append(error) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileMgr::isFreeFileSpace(const std::string& dir, unsigned requiredSize)
{
	unsigned long long freeSpace = Path::freeSpace(dir) ;
	if (static_cast<unsigned long long>(requiredSize) >= freeSpace)
	{
// HACK: For /tmp
if (dir.find("/tmp") == 0)
	return true ;

		setError("Insufficient disk space to save file in " + dir) ;
		return false ;
	}
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool FileMgr::downloadStart(const std::string& filename)
{
	if (mDir.empty())
	{
		setError("Directory not set") ;
		return false ;
	}

	mUrl = "" ;
	mFilename = filename ;
	mTempFilepath = mTempDir + "/" + filename ;
	mDestFilepath = mDir + "/" + filename ;

	// remove any existing file
	if (Path::exists(mTempFilepath))
	{
		if (::remove(mTempFilepath.c_str()) != 0)
		{
			setError(std::string("Unable to remove file ") + mTempFilepath + " " + strError(errno)) ;
			return false ;
		}
	}
	if (Path::exists(mDestFilepath))
	{
		if (::remove(mDestFilepath.c_str()) != 0)
		{
			setError(std::string("Unable to remove file ") + mDestFilepath + " " + strError(errno)) ;
			return false ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileMgr::downloadComplete(bool error, bool timedOut)
{
	if (error)
	{
		if (timedOut)
		{
			setError("Timed out while downloading " + mUrl) ;
			return false ;
		}

		setError("Failed to download " + mUrl) ;
		return false ;
	}

	// See if we are now ok to move this file to it's destination

	// check for enough file space
	unsigned fileSize = Path::fileSize(mTempFilepath) ;
	if (fileSize == 0)
	{
		setError(mFilename + " download has zero size") ;
		Path::remove(mTempFilepath) ;
		return false ;
	}

	// Can skip check/move if dest dir == temp dir
	if (mTempDir != mDir)
	{
		// if not enough space then stop
		if (!isFreeFileSpace(mDir, fileSize))
		{
			Path::remove(mTempFilepath) ;
			return false ;
		}

		// Move file
		bool ok = Path::fileCopy(mTempFilepath, mDestFilepath) ;
		Path::remove(mTempFilepath) ;
		if (!ok)
		{
			setError(std::string("Failed to save file ") + mFilename) ;
			return false ;
		}
	}

	mFilename.clear() ;
	mTempFilepath.clear() ;
	mDestFilepath.clear() ;

	return true ;
}
