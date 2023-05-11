/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ZipImage.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SystemTask.h"
#include "Path.h"
#include "IFileMgr.h"
#include "IImageManagement.h"

#include "ZipImage.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static const std::string TEMPDIR{"/tmp/zip"} ;
static const std::string TEMPFILE{"files.zip"} ;


//=============================================================================================================
// CLASSES
//=============================================================================================================

// RAII class that changes the IImage file download function from the default to a pseudo download function
// and restores the default when this object goes out of scope
//
class SetFileDownloadFunc {
public:
	explicit SetFileDownloadFunc(IImage::DownloadFunction download)
	{
		// use the image manager to propagate the switch
		std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
		imageMgr->setDownloadFunction(download) ;
	}

	~SetFileDownloadFunc()
	{
		// revert file download back to default
		std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
		imageMgr->defaultDownloadFunction() ;
	}
};


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ZipImage::ZipImage(ImageTask& task) :
	ImageFundamental(task, "ZipImage"),
	mFileMgr(IFileMgr::factory()),
	mTcpTransfer()
{
//	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "IMG") ;
}

//-------------------------------------------------------------------------------------------------------------
ZipImage::~ZipImage()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned ZipImage::numFiles() const
{
	// .zip
	unsigned numFiles{1} ;

	// add others
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	std::shared_ptr<IImage> image(imageMgr->getImage(IImageTypes::IMAGE_PACKAGE) ) ;
	numFiles += image->numFiles() ;

	return numFiles ;
}

//-------------------------------------------------------------------------------------------------------------
bool ZipImage::initialise(std::string& failReason)
{
	if (!mFileMgr->setTempDir(TEMPDIR, true, true))
	{
		failReason = "Unable to initialise temporary directory " + TEMPDIR ;
		return false ;
	}
	if (!mFileMgr->setDir(TEMPDIR))
	{
		failReason = "Unable to initialise temporary directory " + TEMPDIR ;
		return false ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ZipImage::getAndInstall(std::string& failReason)
{
	std::string dir(TEMPDIR) ;

	logDebugVerbose("ZipImage::getAndInstall") ;

	// Add the zip file to the normal list of files to be processed
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;
	statusObj->restart( statusObj->getNumFiles() + 1 ) ;

	// Use the FileMgr to grab the file
	std::string filename(getImageName()) ;
	if (!getZipFile(filename, failReason))
		return false ;

	logDebugVerbose("ZipImage::getAndInstall - filename=%s", filename.c_str()) ;

	// Ensure directory empty of other files before we start extracting
	std::vector<std::string> existingFiles(Path::dirContents(dir)) ;
	for (auto file : existingFiles)
	{
		if (Path::basename(file) == filename)
			continue ;

		if (Path::isDir(file))
		{
			Path::removeDirContents(file, true) ;
			continue ;
		}

		Path::remove(file) ;
	}

	// Unzip file
    std::shared_ptr<SystemTask> systemTask( std::make_shared<SystemTask>() ) ;
    systemTask->start();

    std::string cmd("unzip " + dir + "/" + filename + " -d " + dir) ;
	int ret = systemTask->runCmd(cmd) ;
	if (ret != 0)
	{
		failReason = std::string("Unable to unzip ") + filename ;
		return false ;
	}
	keepAlive() ;

	// Get the directory contents and find the package name
	std::vector<std::string> unzippedFiles(Path::dirContents(dir)) ;
	std::string package ;
	for (auto file : unzippedFiles)
	{
		if (Path::extension(file) == ".pkg")
		{
			package = file ;
			break ;
		}
	}

	if (package.empty())
	{
		failReason = "Zip contains no package" ;
		return false ;
	}

	// ** Do install from this directory **

	// first set the file download to use the unzipped files
	SetFileDownloadFunc switchDownloadFunc(
		[this, unzippedFiles](const std::string& filename,
			const std::string& serverUrl,
			const std::string& saveDir,
			std::string& failReason)->bool
		{
			return transferFile(unzippedFiles, filename, saveDir, failReason) ;
		}
	) ;

	// Now get the package to process the package file
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	std::shared_ptr<IImage> pkgImage(imageMgr->getImage(IImageTypes::IMAGE_PACKAGE)) ;

	if (!pkgImage->setRemoteUrl(getServerUrl(), failReason))
		return false ;
	if (!pkgImage->setImageName(Path::basename(package), failReason))
		return false ;

	if (!pkgImage->getAndInstall(failReason))
		return false ;

	// ** Clean up **
	Path::removeDirContents(dir, true) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ZipImage::clean(std::string& failReason)
{
	// ignore
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ZipImage::setInstallDir(const std::string& dir, std::string& failReason)
{
	// ignore
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ZipImage::isDownloaded(void)
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool ZipImage::isInstalled(void)
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
void ZipImage::show(std::ostream& os) const
{
}

//-------------------------------------------------------------------------------------------------------------
std::string ZipImage::info() const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgrWriter> ZipImage::getZipFileWriter(std::shared_ptr<IFileStatus> statusObj, unsigned fileSize,
		std::string& failReason)
{
	// Start the TCP port transfer using default name. If IFileMgrWriter is null then there's an error
	std::shared_ptr<IFileMgrWriter> fileWriter( mFileMgr->portTransferStart(TEMPFILE, fileSize, statusObj) ) ;
	if (!fileWriter)
		failReason = mFileMgr->getError() ;
	return fileWriter ;
}

//-------------------------------------------------------------------------------------------------------------
void ZipImage::startTcpTransfer(TcpZipTransfer zipTransfer)
{
	mTcpTransfer = zipTransfer ;
}

//-------------------------------------------------------------------------------------------------------------
void ZipImage::endTcpTransfer()
{
	mTcpTransfer = TcpZipTransfer() ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool ZipImage::transferFile(const std::vector<std::string>& unzippedFiles,
		const std::string& filename, const std::string& saveDir,
		std::string& failReason)
{
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;
	statusObj->start("Transfer", filename) ;

	// find file in list and move it
	for (auto filepath : unzippedFiles)
	{
		if (Path::basename(filepath) != filename)
			continue ;

		// Found file, so copy it
		std::string destpath(saveDir+"/"+filename) ;
		if (Path::exists(destpath))
			Path::remove(destpath) ;

		if ( !Path::fileCopy(filepath, destpath) )
		{
			failReason = "Unable to transfer unzipped file " + filename + " to " + saveDir ;
			statusObj->fail(failReason) ;
			return false ;
		}

		// all done
		statusObj->end() ;
		return true ;
	}

	// failed to find file
	failReason = "File " + filename + " not in zip file" ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool ZipImage::getZipFile(std::string& filename, std::string& failReason)
{
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;

	// TCP transfer
	if (mTcpTransfer)
	{
		// Use dummy filename
		filename = TEMPFILE ;

//		std::cerr << "ZipImage::getZipFile() - start TCP transfer..." << std::endl ;

		// do the transfer
		statusObj->start("TCP", filename) ;
		bool ok = mTcpTransfer() ;
		keepAlive() ;

//		std::cerr << "ZipImage::getZipFile() - TCP transfer done ok=" << ok << std::endl ;

		if (!ok)
		{
			failReason = "Unable to transfer file over TCP" ;
			statusObj->fail(failReason) ;
			return false ;
		}

		statusObj->end() ;
		return true ;
	}

	// Normal url download
	filename = getImageName() ;
	std::string url(getServerUrl() + "/" + filename) ;
	if (!mFileMgr->download(url, filename, statusObj))
	{
		failReason = mFileMgr->getError() ;
		return false ;
	}
	keepAlive() ;

	return true ;
}
