/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxCalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::TxCalDownload::TxCalDownload() :
	CalDownload("TxCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::TxCalDownload::~TxCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::TxCalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("txcal.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
