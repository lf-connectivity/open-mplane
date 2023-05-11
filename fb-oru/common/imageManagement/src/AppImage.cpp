/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppImage.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "AppImage.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AppImage::AppImage(ImageTask& task) :
	ImageBase(task, "AppImage")
{
}

//-------------------------------------------------------------------------------------------------------------
AppImage::~AppImage()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned AppImage::numFiles() const
{
	// tgz + tgz.md5
	return 2 ;
}

//-------------------------------------------------------------------------------------------------------------
bool AppImage::initialise(std::string& failReason)
{
	if (!this->super::initialise(failReason))
		return false ;
	return setInstallDir("/nandflash/app-images", failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppImage::formatName(const std::string& version, const std::string& buildNumber)
{
	std::string name(this->super::formatName(version, buildNumber)) ;
	name.append("-APP.tgz") ;
	return name ;
}

//-------------------------------------------------------------------------------------------------------------
void AppImage::show(std::ostream& os) const
{
	os << "== App Image ==" << std::endl << std::endl ;

	os << "Current Settings:" << std::endl ;

	showPadValue(os, "Install Dir", getInstallDir()) ;
	showPadValue(os, "Server URL", getServerUrl()) ;
//	showPadValue(os, "Image", getImageName()) ;
//	showPadValue(os, "MD5", getMd5Name()) ;
	os << std::endl ;

	this->super::show(os) ;
}
