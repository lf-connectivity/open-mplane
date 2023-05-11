/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxIfCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RxIfCalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::RxIfCalDownload::RxIfCalDownload() :
	CalDownload("RxIfCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::RxIfCalDownload::~RxIfCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RxIfCalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("rxifcal.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
