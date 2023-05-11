/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxIfCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxIfCalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::TxIfCalDownload::TxIfCalDownload() :
	CalDownload("TxIfCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::TxIfCalDownload::~TxIfCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::TxIfCalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("txifcal.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
