/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SRxCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SRxCalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::SRxCalDownload::SRxCalDownload() :
	CalDownload("SRxCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SRxCalDownload::~SRxCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::SRxCalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("srxcal.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
