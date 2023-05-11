/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RxCalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::RxCalDownload::RxCalDownload() :
	CalDownload("RxCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::RxCalDownload::~RxCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RxCalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("rxcal.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
