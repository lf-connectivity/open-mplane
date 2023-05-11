/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PamCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PamCalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::PamCalDownload::PamCalDownload() :
	CalDownload("PamCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PamCalDownload::~PamCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::PamCalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("pamcal.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
