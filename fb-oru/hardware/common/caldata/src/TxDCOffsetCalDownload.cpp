/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxDCOffsetCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxDCOffsetCalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::TxDCOffsetCalDownload::TxDCOffsetCalDownload() :
	CalDownload("TxDCOffsetCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::TxDCOffsetCalDownload::~TxDCOffsetCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::TxDCOffsetCalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("TxDcOffset.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
