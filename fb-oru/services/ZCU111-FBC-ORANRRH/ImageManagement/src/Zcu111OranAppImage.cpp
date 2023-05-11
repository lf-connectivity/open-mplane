/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111OranAppImage.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ISoftwareSlotMgr.h"
#include "Zcu111OranAppImage.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111OranAppImage::Zcu111OranAppImage(ImageTask &task) :
	AppImage(task)
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111OranAppImage::~Zcu111OranAppImage()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OranAppImage::clean(std::string &failReason)
{
	// Leave the cleaning to the slot manager
	return ISoftwareSlotMgr::singleton()->clean(failReason) ;
}
