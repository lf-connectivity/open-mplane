/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PclTxMajorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PclTxMajorFaultOwner.h"
#include "PclTxConvergenceFaultMajor.h"
#include "PclTxOverPowerFaultMajor.h"


using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PclTxMajorFaultOwner::PclTxMajorFaultOwner() :
	FaultOwner("PclTxMajorFaultOwner", { Mplane::PclTx1ConvergenceFaultMajor::NAME,
										 Mplane::PclTx2ConvergenceFaultMajor::NAME,
										 Mplane::PclTx3ConvergenceFaultMajor::NAME,
										 Mplane::PclTx4ConvergenceFaultMajor::NAME,
										 Mplane::PclTx1OverPowerFaultMajor::NAME,
										 Mplane::PclTx2OverPowerFaultMajor::NAME,
										 Mplane::PclTx3OverPowerFaultMajor::NAME,
										 Mplane::PclTx4OverPowerFaultMajor::NAME} )
{
}

//-------------------------------------------------------------------------------------------------------------
PclTxMajorFaultOwner::~PclTxMajorFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void PclTxMajorFaultOwner::updateFaults()
{
}
