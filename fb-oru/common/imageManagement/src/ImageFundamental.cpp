/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageFundamental.cpp
 * \brief     Lowest common base class for IIamge classes
 *
 *
 * \details   Originally the class ImageBase was the base class, but when ZipImage was added it became obvious
 * 			that I needed a more fundamental base class which did all the really common bits so this class was born.
 * 			ImageBase now derives from this and adds all of the common tarball behaviour, while this class provides
 * 			the behaviours common to all
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
#include "SystemTask.h"

#include "ImageFundamental.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ImageFundamental::ImageFundamental(ImageTask& task, const std::string& name) :
	Loggable(name, "IMG"),

	mTask(task),
	mMutex(),
	mStatus(ImageStatus::IMAGE_IDLE),
	mServerUrl(""),
	mInstallDir(""),
	mImageName(""),
	mStatusObject(IFileStatus::nullObject()),
	mDownloadFunc()
{
	defaultStatusObject() ;
	defaultDownloadFunction() ;
}

//-------------------------------------------------------------------------------------------------------------
ImageFundamental::~ImageFundamental()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned ImageFundamental::numFiles() const
{
	return 1 ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Mplane::ImageFundamental::installTimeSecs() const
{
	// default - allow a second for install
	return 1 ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::initialise(std::string& failReason)
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::getAndInstall(std::string& failReason)
{
	// Must override
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::clean(std::string& failReason)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::isRunning() const
{
	ImageStatus status = getStatus() ;
	if (status == IMAGE_RUNNING)
		return true ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::setRemoteUrl(const std::string& url, std::string& failReason)
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
bool ImageFundamental::setImageName(const std::string& name, std::string& failReason)
{
	if (isRunning())
	{
		failReason.assign("Download currently running");
		return false ;
	}

	mImageName.assign(name) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::setInstallDir(const std::string& dir, std::string& failReason)
{
	if (isRunning())
	{
		failReason.assign("Download currently running");
		return false ;
	}

	mInstallDir.assign(dir) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ImageFundamental::installDir() const
{
	return mInstallDir ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ImageFundamental::formatName(const std::string& version, const std::string& buildNumber)
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::isDownloaded(void)
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::isInstalled(void)
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageFundamental::show(std::ostream& os) const
{
}

//-------------------------------------------------------------------------------------------------------------
std::string ImageFundamental::info() const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::setCurrent(const std::string &filename)
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ImageFundamental::current() const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ImageFundamental::previous() const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::usePrevious(std::string failReason)
{
	failReason = "This image file type does not support reverting back to previous" ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageFundamental::setStatusObject(std::shared_ptr<IFileStatus> status)
{
	mStatusObject = status ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageFundamental::defaultStatusObject()
{
	setStatusObject(IFileStatus::nullObject()) ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageFundamental::setDownloadFunction(DownloadFunction download)
{
	mDownloadFunc = download ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageFundamental::defaultDownloadFunction()
{
	setDownloadFunction([](const std::string& filename,
		const std::string& serverUrl,
		const std::string& saveDir,
		std::string& failReason){return false;});
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
IImage::DownloadFunction ImageFundamental::getDownloadFunction() const
{
	return mDownloadFunc ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileStatus> ImageFundamental::getStatusObject(void) const
{
	return mStatusObject ;
}

//-------------------------------------------------------------------------------------------------------------
ImageFundamental::ImageStatus ImageFundamental::getStatus() const
{
	Mutex::Lock lock(mMutex) ;
	return mStatus ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageFundamental::setStatus(const ImageStatus& status)
{
	Mutex::Lock lock(mMutex) ;
	mStatus = status ;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageFundamental::checkData(std::string& failReason) const
{
	if (mImageName.empty())
	{
		failReason = "Image name not set" ;
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

//-------------------------------------------------------------------------------------------------------------
void ImageFundamental::keepAlive(void)
{
	mTask.keepAlive() ;
}

//-------------------------------------------------------------------------------------------------------------
void ImageFundamental::showPadValue(std::ostream& os,
		const std::string& title, const std::string& value) const
{
	static const unsigned PAD_WIDTH = 20 ;
	os << "  " << padLeft(title, PAD_WIDTH, '.') << ": " <<
		(value.empty() ? "(not set)" : value) << std::endl ;
}
