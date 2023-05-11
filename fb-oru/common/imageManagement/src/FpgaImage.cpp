/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaImage.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Path.h"
#include "FpgaImage.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

static const std::string testLink("TEST") ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaImage::FpgaImage(ImageTask& task) :
	ImageBase(task, "FpgaImage")
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaImage::~FpgaImage()
{
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaImage::initialise(std::string& failReason)
{
	if (!this->super::initialise(failReason))
		return false ;
	return setInstallDir("/nandflash/fpga-images", failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaImage::clean(std::string& failReason)
{
	// remove any existing TEST link
	std::string test = getInstallDir() + "/" + testLink ;
	Path::remove(test) ;

	// Use default clean action now
	return this->super::clean(failReason) ;
}


//-------------------------------------------------------------------------------------------------------------
std::string FpgaImage::formatName(const std::string& version, const std::string& buildNumber)
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaImage::info() const
{
	// get default info
	std::string info(this->super::info()) ;

	// Get info of any existing test link
	std::string link ;
	if (Path::readLink(getInstallDir() + "/" + testLink, link))
	{
		if (!info.empty())
			info.append(", ") ;
		info.append(std::string("[") + testLink + "] " + Path::basename(link)) ;
	}

	return info ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaImage::show(std::ostream& os) const
{
	os << "== FPGA Image ==" << std::endl << std::endl ;

	os << "Current Settings:" << std::endl ;

	showPadValue(os, "Install Dir", getInstallDir()) ;
	showPadValue(os, "Server URL", getServerUrl()) ;
	os << std::endl ;

	this->super::show(os) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool FpgaImage::alreadyInstalled()
{
	std::string imagePath = getInstallDir() + "/" + getImageName() ;
	std::string current = getInstallDir() + "/" + testLink ;

	return linkCurrent(current, imagePath) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaImage::install(std::string& failReason)
{
	keepAlive() ;

	// Create a 'TEST' link
	//
	std::string imagePath = getInstallDir() + "/" + getImageName() ;
	std::string current = getInstallDir() + "/" + testLink ;

	if (Path::exists(current))
	{
		Path::remove(current) ;
	}

	Path::createLink(current, imagePath) ;

	return true ;
}
