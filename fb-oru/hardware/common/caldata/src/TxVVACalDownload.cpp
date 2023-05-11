/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxVVACalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxVVACalDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::TxVVACalDownload::TxVVACalDownload() :
	CalDownload("TxVVACalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::TxVVACalDownload::~TxVVACalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::TxVVACalDownload::initialise(std::string& failReason)
{
	if (!setInstallFileName("TxVVA.xml", failReason))
		return false ;
	return this->super::initialise(failReason) ;
}
