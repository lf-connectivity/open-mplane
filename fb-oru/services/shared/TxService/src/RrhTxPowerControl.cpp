/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhTxPowerControl.h
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RrhTxPowerControl.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RrhTxPowerControl::RrhTxPowerControl(int portIndex) :
	TxPowerControl(portIndex)
{
	// set flag to wait indefinitely
	mInfiniteWaitDP = true ;
}

//-------------------------------------------------------------------------------------------------------------
RrhTxPowerControl::~RrhTxPowerControl()
{
}
