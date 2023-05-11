/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NullLibImage.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "NullLibImage.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NullLibImage::NullLibImage(ImageTask& task) :
	ImageBase(task, "NullLibImage")
{
}

//-------------------------------------------------------------------------------------------------------------
NullLibImage::~NullLibImage()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned NullLibImage::numFiles() const
{
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullLibImage::initialise(std::string& failReason)
{
	if (!this->super::initialise(failReason))
		return false ;
	return setInstallDir("/tmp/lib-images", failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullLibImage::setImageName(const std::string& name, std::string& failReason)
{
	// set the image name
	if (!this->super::setImageName(name, failReason))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NullLibImage::formatName(const std::string& version, const std::string& buildNumber)
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullLibImage::clean(std::string& failReason)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void NullLibImage::show(std::ostream& os) const
{
}

//-------------------------------------------------------------------------------------------------------------
std::string NullLibImage::info() const
{
	return "" ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool NullLibImage::alreadyDownloaded()
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullLibImage::alreadyInstalled()
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullLibImage::download(std::string& failReason)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullLibImage::check(std::string& failReason)
{
	return true ;
}

bool NullLibImage::install(std::string& failReason)
{
	return true ;
}
