/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxQuadCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxQuadCalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::TxQuadOffsetCalDownload::TxQuadOffsetCalDownload() :
	CalDownload("TxQuadOffsetCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::TxQuadOffsetCalDownload::~TxQuadOffsetCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::TxQuadOffsetCalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("TxQuadratureOffset.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
