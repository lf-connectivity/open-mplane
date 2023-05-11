/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaDetCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PaDetCalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::PaDetCalDownload::PaDetCalDownload() :
	CalDownload("PaDetCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PaDetCalDownload::~PaDetCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::PaDetCalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("padetcal.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
