/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageBase.cpp
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

#include "stringfunc.hpp"
#include "Path.h"
#include "IAppSettingsFactory.h"
#include "AppSettings.h"

#include "ImageBase.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

static const std::string currentLink("current") ;
static const std::string previousLink("previous") ;

// Usual (max) time for a download
static const unsigned DEFAULT_DOWNLOAD_TIME(5) ;

// Time out if download takes longer than this
static const unsigned DOWNLOAD_TIMEOUT_TIME(20) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ImageBase::ImageBase(ImageTask& task, const std::string& name) :
	ImageFundamental(task, name),
    mMd5Name(""),
    mMd5ListName("")
{
}

//-------------------------------------------------------------------------------------------------------------
ImageBase::~ImageBase()
{
}


//-------------------------------------------------------------------------------------------------------------
bool ImageBase::initialise(std::string& failReason)
{
	defaultDownloadFunction() ;
	return this->super::initialise(failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::getAndInstall(std::string& failReason)
{
	// reject download if currently running
	if (isRunning())
	{
		failReason.assign("Another download already running");
		return false ;
	}

	logDebugVerbose("getAndInstall %s", getImageName().c_str()) ;

	// check that required values have been set
	if (!checkData(failReason))
		return false ;

	// Mark this section as running so that no other instance can interrupt
	bool ok = true ;
	setStatus(IMAGE_RUNNING) ;
	{
		// Skip if already installed
		if (alreadyInstalled())
		{
			skipFiles() ; // update file progress
			setStatus(IMAGE_IDLE) ;
			return true ;
		}

		// skip download if already downloaded
		if (!alreadyDownloaded())
		{
			// download the file(s)
			ok = download(failReason) ;

			// check file
			if (ok)
				ok = check(failReason) ;
		}
		else
		{
			skipFiles() ; // update file progress
		}

		// install file(s)
		if (ok)
			ok = install(failReason) ;

	}
	setStatus(IMAGE_IDLE) ;

	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::clean(std::string& failReason)
{
	std::string installDir(getInstallDir()) ;
	if (installDir.empty())
	{
		failReason = "Install directory not set to valid directory" ;
		return false ;
	}

	if (!Path::isDir(installDir))
	{
		// Path is set but directory doesn't yet exist, so silently skip clean
		return true ;
	}

	// get the directory contents
	std::vector<std::string> dirContents = Path::dirContents(installDir) ;


	// Create hash of those files which have a link
	std::set<std::string> linkedFiles ;
	for (auto linkFile : dirContents)
	{
		logDebugVerbose("Link file=%s", linkFile.c_str()) ;

		std::string link ;
		if (Path::readLink(linkFile, link))
		{
			logDebugVerbose("Linked: %s link name=%s", link.c_str(), linkFile.c_str()) ;
			if (Path::exists(link))
			{
				// keep the link and the file linked to
				linkedFiles.insert(link) ;
				linkedFiles.insert(linkFile) ;
			}
		}
	}


	// Clean out all files that aren't being linked to

	// Create a list of candidate file, but exclude any being linked to
	std::vector<std::string> deleteList ;
	for (auto file : dirContents)
	{
		logDebugVerbose("%s isDir=%d isFile=%d isLink=%d", file.c_str(), Path::isDir(file), Path::isFile(file), Path::isLink(file)) ;

		if (Path::isDir(file))
			continue ;

		// scan the list of files to keep - see if this is the file or a file related
		bool deleteFile = true ;
		for (auto linkFile : linkedFiles)
		{
			// link name must match the start of the filename (related files just have additional extensions)
			if (file.find(linkFile) == 0)
			{
				// keep this file
				logDebugVerbose(" !! KEEP !! link=%s", linkFile.c_str()) ;
				deleteFile = false ;
				break ;
			}
		}

		if (deleteFile)
		{
			deleteList.push_back(file) ;
			logDebugVerbose(" ** Add to delete ** ") ;
		}
	}

	// delete these files
	for (auto file : deleteList)
	{
		logDebugVerbose("DELETE: %s", file.c_str()) ;
		if (Path::remove(file) != 0)
		{
			failReason = "Unable to delete file " + file ;
			return false ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::isRunning() const
{
	return this->super::isRunning() ;
}


//-------------------------------------------------------------------------------------------------------------
bool ImageBase::setRemoteUrl(const std::string& url, std::string& failReason)
{
	return this->super::setRemoteUrl(url, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::setInstallDir(const std::string& dir, std::string& failReason)
{
	return this->super::setInstallDir(dir, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::setImageName(const std::string& name, std::string& failReason)
{
	if (!this->super::setImageName(name, failReason))
		return false ;

	std::string md5( md5Filename(name) ) ;

	mMd5Name.assign(md5) ;
	mMd5ListName.clear() ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
std::string ImageBase::formatName(const std::string& version, const std::string& buildNumber)
{
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;

	std::string name =
		appSettings->getBoardString() + "-" +
		appSettings->getCustomerString() + "-" +
		appSettings->getAppString() + "-" +
		version + "-" +
		buildNumber ;

	return name ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::isDownloaded(void)
{
	return alreadyDownloaded() ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::isInstalled(void)
{
	return alreadyInstalled() ;
}


//-------------------------------------------------------------------------------------------------------------
void ImageBase::show(std::ostream& os) const
{
	// Just show directory contents & links
	std::vector<std::string> contents(Path::dirContents(getInstallDir())) ;

	// sort
	std::sort(contents.begin(), contents.end()) ;

	// count entries
	unsigned numLinks = 0 ;
	unsigned numFiles = 0 ;
	for (auto file : contents)
	{
		if (Path::isLink(file))
		{
			++numLinks;
			continue ;
		}

		if (Path::isFile(file))
		{
			++numFiles;
			continue ;
		}

	}


	// start with showing links
	if (numLinks)
	{
		os << "Links:" << std::endl ;
		for (auto file : contents)
		{
			if (!Path::isLink(file))
				continue ;

			// read link
			std::string link ;
			Path::readLink(file, link) ;

			// format output
			showPadValue(os, Path::basename(file), Path::basename(link)) ;
		}
		os << std::endl ;
	}

	// show files
	if (numFiles)
	{
		os << "Contents:" << std::endl ;
		for (auto file : contents)
		{
			if (!Path::isFile(file))
				continue ;

			// format output
			os << "  " << Path::basename(file) << std::endl ;
		}
		os << std::endl ;
	}
}


//-------------------------------------------------------------------------------------------------------------
std::string ImageBase::info() const
{
	// Default behaviour is to read the 'current' link and return the base filename pointed at
	if (getInstallDir().empty())
		return "" ;

	std::string currentPath(getInstallDir() + "/" + currentLink) ;
	std::string link ;
	if (!Path::exists(currentPath) || !Path::readLink(currentPath, link))
		return "" ;

	return Path::basename(link) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::setCurrent(const std::string &filename)
{
	std::string failReason ;

	// Set the image name to this and then "install" the existing file
	if (!setImageName(filename, failReason))
		return false ;

	if (!install(failReason))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ImageBase::current() const
{
	if (getInstallDir().empty())
		return "" ;

	std::string currentPath(getInstallDir() + "/" + currentLink) ;
	std::string link ;
	if (!Path::exists(currentPath) || !Path::readLink(currentPath, link))
		return "" ;

	return Path::basename(link) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ImageBase::previous() const
{
	if (getInstallDir().empty())
		return "" ;

	std::string previousPath(getInstallDir() + "/" + previousLink) ;
	std::string link ;
	if (!Path::exists(previousPath) || !Path::readLink(previousPath, link))
		return "" ;

	return Path::basename(link) ;
}


//-------------------------------------------------------------------------------------------------------------
bool ImageBase::usePrevious(std::string failReason)
{
	logDebugVerbose("usePrevious %s", getImageName().c_str()) ;

	// Default behaviour is to keep a 'current' and 'previous' set of links pointing at the latest 2 images
	// Need to ensure that there isn't a window where the 'current' link points at the wrong file
	//
	std::string currentPath = getInstallDir() + "/" + currentLink ;
	std::string previousPath = getInstallDir() + "/" + previousLink ;

	if (!Path::exists(previousPath))
	{
		failReason = "No previous install to roll back to" ;
		return false ;
	}
	if (Path::exists(currentPath))
	{
		Path::remove(currentPath) ;
	}

	std::string link ;
	if (!Path::readLink(previousPath, link))
	{
		failReason = "Unable to determine previous install" ;
		return false ;
	}

	Path::createLink(currentPath, link) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageBase::defaultDownloadFunction()
{
	this->super::setDownloadFunction(
		[this](const std::string& filename,
				const std::string& serverUrl,
				const std::string& saveDir,
				std::string& failReason)->bool
		{
			return downloadFile(filename, serverUrl, saveDir, failReason) ;
		}
	) ;
}

//=============================================================================================================
// PROTECTED ALGORITHMS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::alreadyDownloaded()
{
	// use checkFile to test that files are present and run the MD5 sum
	std::string failReason ;
	std::string md5file = md5Filename(getImageName()) ;

	return checkFile(getInstallDir(), getImageName(), md5file, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::alreadyInstalled()
{
	std::string imagePath = getInstallDir() + "/" + getImageName() ;
	std::string currentPath = getInstallDir() + "/" + currentLink ;

	return linkCurrent(currentPath, imagePath) ;
}


//-------------------------------------------------------------------------------------------------------------
bool ImageBase::download(std::string& failReason)
{
	// ensure install directory is present
	if (!Path::exists(getInstallDir()))
	{
		if (Path::mkpath(getInstallDir()) != 0)
		{
			failReason = std::string("Unable to create directory path ") + getInstallDir() + " " + strError(errno) ;
			return false ;
		}
	}

	logDebugVerbose("Download %s url=%s", getImageName().c_str(), getServerUrl().c_str()) ;

	// download files
	keepAlive() ;
	if (!downloadFileSpaceCheck(getImageName(), getServerUrl(), getInstallDir(), failReason))
		return false ;

	keepAlive() ;
	if (!downloadFileSpaceCheck(mMd5Name, getServerUrl(), getInstallDir(), failReason))
		return false ;

	keepAlive() ;
	if (!mMd5ListName.empty())
		if (!downloadFileSpaceCheck(mMd5ListName, getServerUrl(), getInstallDir(), failReason))
			return false ;


	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::check(std::string& failReason)
{
	bool ok = checkFile(getInstallDir(), getImageName(), mMd5Name, failReason) ;

	logDebugVerbose("Check %s", getImageName().c_str()) ;

	keepAlive() ;

	// If check failed then we need to remove the image and MD5 so that we can re-download them
	if (!ok)
	{
		Path::remove(getInstallDir() + "/" + getImageName()) ;
		Path::remove(getInstallDir() + "/" + mMd5Name) ;
	}

	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::install(std::string& failReason)
{
	keepAlive() ;

	logDebugVerbose("Install %s", getImageName().c_str()) ;

	// Default behaviour is to keep a 'current' and 'previous' set of links pointing at the latest 2 images
	// Need to ensure that there isn't a window where the 'current' link points at the wrong file
	//
	std::string imagePath = getInstallDir() + "/" + getImageName() ;
	std::string currentPath = getInstallDir() + "/" + currentLink ;
	std::string previousPath = getInstallDir() + "/" + previousLink ;

	if (Path::exists(previousPath))
	{
		Path::remove(previousPath) ;
	}
	if (Path::exists(currentPath))
	{
		Path::move(currentPath, previousPath) ;
	}

	Path::createLink(currentPath, imagePath) ;

	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
bool ImageBase::downloadFile(const std::string& filename, const std::string& serverUrl,
		const std::string& saveDir, std::string& failReason)
{
	// Look at the protocol
	std::string dir(serverUrl) ;
	std::size_t pos(dir.find("://")) ;
	bool fileCopy(false) ;
	if (pos == std::string::npos)
	{
		fileCopy = true ;
	}
	else
	{
		if (dir.substr(0, pos) == "file")
		{
			fileCopy = true ;
			dir = dir.substr(pos+3) ;
		}
	}


	// create the wget command
	std::string destFilename = saveDir + "/" + filename ;
	std::string url = serverUrl + "/" + filename ;
	std::string wgetCmd = std::string("wget -q -O ") + destFilename + " " + url ;

	// remove any existing file
	if (Path::exists(destFilename))
	{
		if (remove(destFilename.c_str()) != 0)
		{
			failReason = std::string("Unable to remove file ") + destFilename + " " + strError(errno) ;
			return false ;
		}
	}

	// do the download
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;
	statusObj->start("Download", filename) ;

	// If we're just doing a file copy rather than a remote get, then handle it and stop
	if (fileCopy)
	{
		bool ok = Path::fileCopy(dir + "/" + filename, destFilename) ;
		statusObj->end() ;

		if (!ok)
		{
			failReason = std::string("Failed to copy ") + filename ;
			statusObj->fail(failReason) ;
			return false ;
		}

		statusObj->success() ;
		return true ;
	}

	// Remote transfer
	bool timedOut(false) ;
    std::shared_ptr<SystemTask> systemTask( new SystemTask() ) ;
    systemTask->start();

	int ret = systemTask->runCmd(wgetCmd,
		[statusObj](unsigned progress) { statusObj->progress(progress); },
		DEFAULT_DOWNLOAD_TIME,
		DOWNLOAD_TIMEOUT_TIME,
		timedOut);
	statusObj->end() ;
	if (ret != 0)
	{
		if (timedOut)
		{
			failReason = std::string("Timed out while downloading ") + filename ;
			statusObj->fail(failReason) ;
			return false ;
		}

		failReason = std::string("Failed to download ") + filename ;
		statusObj->fail(failReason) ;
		return false ;
	}
	keepAlive() ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool ImageBase::downloadFileSpaceCheck(const std::string& filename, const std::string& serverUrl,
		const std::string& saveDir, std::string& failReason)
{
	std::string tmpDir("/tmp") ;

	// Download to temp file
	IImage::DownloadFunction downloadFunc(getDownloadFunction()) ;
	if (!downloadFunc(filename, serverUrl, tmpDir, failReason))
		return false ;

	std::string destFilename = saveDir + "/" + filename ;
	std::string tempFilename = tmpDir + "/" + filename ;

	// check for enough file space
	unsigned fileSize = Path::fileSize(tempFilename) ;
	if (fileSize == 0)
	{
		failReason = filename + " download has zero size" ;
		Path::remove(tempFilename) ;
		return false ;
	}

	// if not enough space, try cleaning out old images
	if (!isFreeFileSpace(saveDir, fileSize, failReason))
	{
		// Try cleaning
		if (!clean(failReason))
		{
			Path::remove(tempFilename) ;
			return false ;
		}
	}

	// if still no space, then stop
	if (!isFreeFileSpace(saveDir, fileSize, failReason))
	{
		// Failed
		failReason = std::string("Insufficient disk space to save ") + filename ;
		Path::remove(tempFilename) ;
		return false ;
	}

	// Move file
	bool ok = Path::fileCopy(tempFilename, destFilename) ;
	Path::remove(tempFilename) ;
	if (!ok)
	{
		failReason = std::string("Failed to save file ") + filename ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::checkData(std::string& failReason) const
{
	if (!this->super::checkData(failReason))
		return false ;

	if (mMd5Name.empty())
	{
		failReason = "MD5 name not set" ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::checkFile(const std::string& saveDir,
		const std::string& filename, const std::string& md5file,
		std::string& failReason)
{
	std::string imagePath = saveDir + "/" + getImageName() ;
	if (!Path::exists(imagePath))
	{
		failReason = std::string("File ") + filename + " not present in " + saveDir ;
		return false ;
	}

	std::string md5Path = saveDir + "/" + md5file ;
	if (!Path::exists(md5Path))
	{
		failReason = std::string("MD5 file ") + md5file + " not present in " + saveDir ;
		return false ;
	}

	// Run ms5 sum on tar file in the save directory
	if (chdir(saveDir.c_str()) != 0)
	{
		failReason = std::string("Check cannot access directory path ") + saveDir ;
		return false ;
	}

	// create the command
	std::string cmd = std::string("md5sum -c ") + md5file ;

	// run command
    std::shared_ptr<SystemTask> systemTask( new SystemTask() ) ;
    systemTask->start();

	int ret = systemTask->runCmd(cmd);

	// reset cwd
	chdir("/") ;

	// check status
	if (ret != 0)
	{
		failReason = filename + " failed MD5 check" ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::isFreeFileSpace(const std::string& dir, unsigned requiredSize, std::string& failReason) const
{
	unsigned long long freeSpace = Path::freeSpace(dir) ;
	if (static_cast<unsigned long long>(requiredSize) >= freeSpace)
	{
		failReason = std::string("Insufficient disk space to save file in ") + dir ;
		return false ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ImageBase::md5Filename(const std::string& imageName) const
{
	std::string md5file = imageName + ".md5" ;
	return md5file ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ImageBase::md5ListFilename(const std::string& imageName) const
{
	std::string md5listfile = imageName + ".md5list" ;
	return md5listfile ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::getVersionBuild(const std::string& imageName,
		std::string& baseName, float& version, unsigned & buildNumber) const
{
	// Assumes the file is of the form:
	//   NNNN-VV.VV-BB-TTT.tgz
	// Grab the NNNN (base name), VV.VV (version), and BB (build number) to compare them in turn.
	// If format does not match, then just compare string
	//
	std::size_t buildEnd(imageName.rfind('-')) ;
	if ((buildEnd == std::string::npos) || (buildEnd == 0))
		return false ;

	std::size_t buildStart(imageName.rfind('-', buildEnd-1)) ;
	if ((buildStart == std::string::npos) || (buildStart == 0))
		return false ;

	std::size_t versionStart(imageName.rfind('-', buildStart-1)) ;
	if ((versionStart == std::string::npos) || (versionStart == 0))
		return false ;

	baseName.assign(imageName.substr(0, versionStart)) ;
	std::string versionStr(imageName.substr(versionStart+1, buildStart-versionStart-1)) ;
	std::string buildStr(imageName.substr(buildStart+1, buildEnd-buildStart-1)) ;

	bool ok = true ;
	try {
		version = std::stof(versionStr) ;
		buildNumber = static_cast<unsigned>(std::stoul(buildStr)) ;
	}
	catch(...)
	{
		ok = false ;
	}


	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageBase::linkCurrent(const std::string& linkPath, std::string& filePath) const
{
	// current link exists
	if (!Path::exists(linkPath))
		return false ;

	// link points to this image
	std::string link ;
	if (!Path::readLink(linkPath, link))
		return false ;

	if (link.compare(filePath) != 0)
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string& ImageBase::getCurrentLink() const
{
	return currentLink ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string& ImageBase::getPreviousLink() const
{
	return previousLink ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void ImageBase::skipFiles()
{
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;

	// skip tgz & tgz.md5
	statusObj->skip(2) ;

	if (!mMd5ListName.empty())
		statusObj->skip(2) ;
}
