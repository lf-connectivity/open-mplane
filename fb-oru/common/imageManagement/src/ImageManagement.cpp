/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageManagement.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <memory>

#include "stringfunc.hpp"

#include "ImageBase.h"
#include "AppImage.h"
#include "LibImage.h"
#include "FpgaImage.h"
#include "OsImage.h"
#include "PkgImage.h"
#include "ZipImage.h"
#include "ImageManagement.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// tick time in ms
static const unsigned TASK_TICK_MS = 500 ;

// Auto-clean threshold settings
const unsigned AUTOCLEAN_THRESHOLD_MIN = 4 ;
const unsigned AUTOCLEAN_THRESHOLD_DEFAULT = 6 ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ImageManagement::ImageManagement() :
	mTaskRunning(true),
	mMutex(),
	mIsDownloading(false),
	mTypeDownloading(IImageTypes::IMAGE_APPLICATION),
	mImageName(""),
	mCondEnd( std::shared_ptr<Conditional>() ),
	mDownloadImage( std::shared_ptr<IImage>() ),
    mDownloadOk(true),
    mDownloadFailReason(""),
    mStatusObject(IFileStatus::nullObject()),
    mDownloadDoneCallback(),
    mAutocleanThreshold(AUTOCLEAN_THRESHOLD_DEFAULT),

	mCondStart()
{
	// Create the list of Image objects
	mImageMap[IImageTypes::IMAGE_APPLICATION] 	= std::make_shared<AppImage>(*this) ;
	mImageMap[IImageTypes::IMAGE_LIBRARY] 		= std::make_shared<LibImage>(*this) ;
	mImageMap[IImageTypes::IMAGE_FPGA] 			= std::make_shared<FpgaImage>(*this) ;
	mImageMap[IImageTypes::IMAGE_ROS] 			= std::make_shared<OsImage>(*this) ;
	mImageMap[IImageTypes::IMAGE_PACKAGE] 		= std::make_shared<PkgImage>(*this) ;
	mImageMap[IImageTypes::IMAGE_ZIP]	 		= std::make_shared<ZipImage>(*this) ;

	// Initialise them all
	std::string failReason ;
	for (auto& image : mImageMap)
	{
		image.second->initialise(failReason) ;
	}

	// self-start
	start() ;

	logDebugVerbose("ImageManagement created") ;
}

//-------------------------------------------------------------------------------------------------------------
ImageManagement::~ImageManagement()
{
	shutdown() ;

	logDebugVerbose("ImageManagement stopped") ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::replaceImageObject(IImageTypes::Type type, std::shared_ptr<IImage> image)
{
	logDebugVerbose("ImageManagement: Replacing image object %s", IImageTypes::typeToStr(type).c_str()) ;
	mImageMap[type]	= image ;

	// Initialise it
	std::string failReason ;
	bool ok = mImageMap[type]->initialise(failReason) ;

	return ok ;
}



//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::getAndInstall(ImageType type,
		const std::string& _imageName,
		std::shared_ptr<IFileStatus> status,
		std::string& failReason,
		std::shared_ptr<Conditional> endSignal)
{
	// If image name contains a url, then set url
	std::string imageName(_imageName);
	std::size_t pos(imageName.find_last_of('/')) ;
	if (pos != std::string::npos)
	{
		if (!setRemoteUrl( imageName.substr(0, pos), failReason ))
			return false ;

		imageName = imageName.substr(pos+1) ;
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
	mTypeDownloading = type ;
	mIsDownloading = true ;

	logDebugVerbose("ImageManagement::getAndInstall url=%s image=%s", mServerUrl.c_str(), imageName.c_str()) ;

	// Check for auto-clean
	if (!checkAutoClean(mAutocleanThreshold-1, failReason))
		return false ;


	// Grab settings for download task
	mImageName = imageName ;
	mCondEnd = endSignal ;
	mDownloadOk = true ;
	mDownloadFailReason.clear() ;
	mDownloadImage = mImageMap[type] ;
	mDownloadDoneCallback = std::function<void(void)>() ;

	// Set up the image object
	if (!mDownloadImage->setImageName(mImageName, mDownloadFailReason))
		return false ;

	// Set up the status reporting object
	setStatusObject(status) ;
	unsigned numFiles(mDownloadImage->numFiles()) ;
	status->restart(numFiles) ;

	// Initiate download
	Conditional::Lock condLock(mCondStart) ;
	mCondStart.signal() ;

	logDebugVerbose("ImageManagement::getAndInstall signalled start") ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::getAndInstall(ImageType type,
		const std::string& version, const std::string& build,
		std::shared_ptr<IFileStatus> status,
		std::string& failReason,
		std::shared_ptr<Conditional> endSignal)
{
	// format into base name
	std::string imageName( mImageMap[type]->formatName(version, build) ) ;

	// run download
	return getAndInstall(type, imageName, status, failReason, endSignal) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::getAndInstall(ImageType type,
		const std::string& imageName,
		std::shared_ptr<IFileStatus> status,
		std::string& failReason)
{
	// Create Conditional
    std::shared_ptr<Conditional> endSignal(new Conditional) ;

	// run download
	if (!getAndInstall(type, imageName, status, failReason, endSignal))
		return false ;

	// Wait for completion
    endSignal->wait() ;

    // Check for error
    return isDownloadOk(failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::getAndInstall(ImageType type,
		const std::string& version, const std::string& build,
		std::shared_ptr<IFileStatus> status,
		std::string& failReason)
{
	// Create Conditional
    std::shared_ptr<Conditional> endSignal(new Conditional) ;

	// run download
	if (!getAndInstall(type, version, build, status, failReason, endSignal))
		return false ;

	// Wait for completion
    endSignal->wait() ;

    // Check for error
    return isDownloadOk(failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::getAndInstall(ImageType type,
		const std::string& imageName,
		std::string& failReason,
		std::shared_ptr<Conditional> endSignal)
{
	// run download
	return getAndInstall(type, imageName, IFileStatus::nullObject(), failReason, endSignal) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::getAndInstall(ImageType type,
		const std::string& version, const std::string& build,
		std::string& failReason,
		std::shared_ptr<Conditional> endSignal)
{
	// run download
	return getAndInstall(type, version, build, IFileStatus::nullObject(), failReason, endSignal) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::getAndInstall(ImageType type,
		const std::string& imageName,
		std::string& failReason)
{
	// run download
	return getAndInstall(type, imageName, IFileStatus::nullObject(), failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::getAndInstall(ImageType type,
		const std::string& version, const std::string& build,
		std::string& failReason)
{
	// run download
	return getAndInstall(type, version, build, IFileStatus::nullObject(), failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::cleanImages(ImageType type, std::string& failReason)
{
	Mutex::Lock lock(mMutex) ;
	if (mIsDownloading)
	{
		failReason = "Unable to clean while downloading" ;
		return false ;
	}
	return mImageMap[type]->clean(failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::cleanImages(std::string& failReason)
{
	Mutex::Lock lock(mMutex) ;
	if (mIsDownloading)
	{
		failReason = "Unable to clean while downloading" ;
		return false ;
	}
	return doCleanImages(failReason) ;
}


//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::isDownloading() const
{
	Mutex::Lock lock(mMutex) ;
	return mIsDownloading ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::isDownloadOk(std::string& failReason) const
{
	Mutex::Lock lock(mMutex) ;
	if (!mDownloadOk)
		failReason.assign(mDownloadFailReason) ;
	return mDownloadOk ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::setRemoteUrl(const std::string& url, std::string& failReason)
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
bool ImageManagement::setUbootInstall(bool ubootInstall, std::string& failReason)
{
	Mutex::Lock lock(mMutex) ;
	if (mIsDownloading)
	{
		failReason = "Unable to set u-boot install while downloading" ;
		return false ;
	}

	std::shared_ptr<IOsImage> osImage(std::dynamic_pointer_cast<IOsImage>(mImageMap[IImageTypes::IMAGE_ROS])) ;
	return osImage->setUbootInstall(ubootInstall, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::setAutocleanThreshold(unsigned threshold, std::string& failReason)
{
	Mutex::Lock lock(mMutex) ;
	if (mIsDownloading)
	{
		failReason = "Unable to set auto-clean threshold while downloading" ;
		return false ;
	}

	if (threshold < AUTOCLEAN_THRESHOLD_MIN)
		threshold = AUTOCLEAN_THRESHOLD_MIN ;

	mAutocleanThreshold = threshold ;
	return checkAutoClean(mAutocleanThreshold, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned ImageManagement::getAutocleanThreshold(void)
{
	Mutex::Lock lock(mMutex) ;
	return mAutocleanThreshold ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageManagement::show(std::ostream& os) const
{

	for (auto& imageType : {
		IImageTypes::IMAGE_PACKAGE,
		IImageTypes::IMAGE_APPLICATION,
		IImageTypes::IMAGE_LIBRARY,
		IImageTypes::IMAGE_ROS,
		IImageTypes::IMAGE_FPGA,
	})
	{
		std::shared_ptr<IImage> image(mImageMap.at(imageType)) ;
		std::string info(image->info()) ;

		if (info.empty())
			continue ;

		std::string typeStr(IImageTypes::typeToStr(imageType)) ;

		static const unsigned PAD_WIDTH = 10 ;
		os << padLeft(typeStr, PAD_WIDTH, ' ') << " : " << info << std::endl ;
	}

}

//-------------------------------------------------------------------------------------------------------------
void ImageManagement::showDetail(std::ostream& os) const
{
	os << "STATUS: " << (isDownloading() ? "DOWNLOADING" : "Idle") << std::endl << std::endl ;
	for (auto& image : mImageMap)
	{
		image.second->show(os) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void ImageManagement::show(ImageType type, std::ostream& os) const
{
	std::map<ImageType, std::shared_ptr<IImage>>::const_iterator iter( mImageMap.find(type) ) ;
	iter->second->show(os) ;
}


//-------------------------------------------------------------------------------------------------------------
std::string ImageManagement::getRemoteUrl()
{
	return mServerUrl ;
}

//-------------------------------------------------------------------------------------------------------------
IImageTypes::OsImageBank ImageManagement::getOsBank(void)
{
	std::shared_ptr<IOsImage> osImage(std::dynamic_pointer_cast<IOsImage>(mImageMap[IImageTypes::IMAGE_ROS])) ;
	return osImage->getOsBank() ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::getUbootInstall(void)
{
	std::shared_ptr<IOsImage> osImage(std::dynamic_pointer_cast<IOsImage>(mImageMap[IImageTypes::IMAGE_ROS])) ;
	return osImage->getUbootInstall() ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageManagement::shutdown(void)
{
	mTaskRunning = false ;
	msSleep(2*TASK_TICK_MS) ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageManagement::setDownloadFunction(IImage::DownloadFunction download)
{
	for (auto& image : mImageMap)
	{
		image.second->setDownloadFunction(download) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void ImageManagement::defaultDownloadFunction()
{
	for (auto& image : mImageMap)
	{
		image.second->defaultDownloadFunction() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgrWriter> ImageManagement::getZipFileWriter(std::shared_ptr<IFileStatus> statusObj,
		unsigned fileSize, std::string& failReason)
{
	std::shared_ptr<ZipImage> zipImage(std::dynamic_pointer_cast<ZipImage>(mImageMap[IImageTypes::IMAGE_ZIP])) ;
	return zipImage->getZipFileWriter(statusObj, fileSize, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::zipInstall(std::shared_ptr<IFileStatus> status,
		ImageZipWrite zipWriteFunc, ImageZipComplete zipCompleteFunc,
		std::string& failReason)
{
	Mutex::Lock lock(mMutex) ;

	// Get state and mark as downloading if idle
	if (mIsDownloading)
	{
		failReason = "Cannot start a new download until existing download completes" ;
		return false ;
	}

	if (!zipWriteFunc)
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

	// Check for auto-clean
	if (!checkAutoClean(mAutocleanThreshold-1, failReason))
		return false ;


	std::string imageName("dummy.zip") ;
	mTypeDownloading = IImageTypes::IMAGE_ZIP ;
	mIsDownloading = true ;

	logDebugVerbose("ImageManagement::zipInstall") ;

	// Grab settings for download task
	mImageName = imageName ;
	mCondEnd = std::make_shared<Conditional>() ;

	mDownloadOk = true ;
	mDownloadFailReason.clear() ;
	mDownloadImage = mImageMap[IImageTypes::IMAGE_ZIP] ;

	// Set up the image object
	if (!mDownloadImage->setImageName(mImageName, mDownloadFailReason))
		return false ;

	std::shared_ptr<ZipImage> zipImage(std::dynamic_pointer_cast<ZipImage>(mDownloadImage)) ;
	mDownloadDoneCallback = [this, zipImage, zipCompleteFunc, cleanUrl](void) {
		// Tell zip to stop TCP transfer
		zipImage->endTcpTransfer() ;

		// Clean up url if required
		std::string dummy ;
		if (cleanUrl)
			setRemoteUrlNoMutex( "", dummy ) ;

		// Call callback
		if (zipCompleteFunc)
			zipCompleteFunc() ;
	} ;

	// Tell zip image to use TCP to transfer data
	zipImage->startTcpTransfer(zipWriteFunc) ;


	// Set up the status reporting object
	setStatusObject(status) ;
	unsigned numFiles(mDownloadImage->numFiles()) ;
	status->restart(numFiles) ;

	// Initiate download
	Conditional::Lock condLock(mCondStart) ;
	mCondStart.signal() ;

	logDebugVerbose("ImageManagement::getAndInstall signalled start") ;

	return true ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
int ImageManagement::run()
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
        	logDebugVerbose("ImageManagement::run - start download") ;

            // run download
        	mDownloadOk = mDownloadImage->getAndInstall(mDownloadFailReason) ;

        	logDebugVerbose("ImageManagement::run - download done : ok=%u error=%s", (unsigned)mDownloadOk, mDownloadFailReason.c_str()) ;

        	// Switch back to idle state
        	setState(false, mTypeDownloading) ;

        	// Finish with status
        	if (mDownloadOk)
        		mStatusObject->success() ;
        	else
        		mStatusObject->fail(mDownloadFailReason) ;

        	// run the callback if set
        	if (mDownloadDoneCallback)
        		mDownloadDoneCallback() ;

        	// tidy up
        	defaultStatusObject() ;

        	// Signal end
        	if (mCondEnd.get())
        	{
        		Conditional::Lock lock(*mCondEnd) ;
        		mCondEnd->signal() ;
        	}
        }
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::getState(ImageType& type) const
{
	Mutex::Lock lock(mMutex) ;
	type = mTypeDownloading ;
	return mIsDownloading ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageManagement::setState(bool downloading, const ImageType& type)
{
	Mutex::Lock lock(mMutex) ;
	mTypeDownloading = type ;
	mIsDownloading = downloading ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IImage> ImageManagement::getImage(const ImageType& type)
{
	return mImageMap[type] ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageManagement::setStatusObject(std::shared_ptr<IFileStatus> status)
{
    mStatusObject = status ;
	for (auto& image : mImageMap)
	{
		image.second->setStatusObject(status) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void ImageManagement::defaultStatusObject()
{
    mStatusObject = IFileStatus::nullObject() ;
    setStatusObject(mStatusObject) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::setRemoteUrlNoMutex(const std::string& url, std::string& failReason)
{

	mServerUrl = url ;
	for (auto& image : mImageMap)
	{
		image.second->setRemoteUrl(url, failReason) ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::checkAutoClean(unsigned threshold, std::string& failReason)
{
	std::shared_ptr<PkgImage> pkgImg( std::dynamic_pointer_cast<PkgImage>(mImageMap[IImageTypes::IMAGE_PACKAGE]) ) ;
	unsigned numInstalledPackages = pkgImg->numPackagesInstalled() ;
	if (numInstalledPackages <= threshold)
		return true ;

	logDebugVerbose("ImageManagement - Number of packages %u above threshold (%u), auto-cleaning...",
			numInstalledPackages, threshold) ;

	// above threshold so clean
	return doCleanImages(failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageManagement::doCleanImages(std::string& failReason)
{
	for (auto& image : mImageMap)
	{
		if (!image.second->clean(failReason))
			return false ;
	}
	return true ;
}
