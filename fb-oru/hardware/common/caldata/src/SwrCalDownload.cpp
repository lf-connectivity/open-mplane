/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SwrCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SwrCalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::SwrCalDownload::SwrCalDownload() :
	CalDownload("SwrCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SwrCalDownload::~SwrCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::SwrCalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("swrcal.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
