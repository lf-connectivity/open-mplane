/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PclTxOverPowerFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PclTxOverPowerFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::PclTx1OverPowerFaultMajor::NAME="PclTx1OverPowerMajorFault";

const char* Mplane::PclTx2OverPowerFaultMajor::NAME="PclTx2OverPowerMajorFault";

const char* Mplane::PclTx3OverPowerFaultMajor::NAME="PclTx3OverPowerMajorFault";

const char* Mplane::PclTx4OverPowerFaultMajor::NAME="PclTx4OverPowerMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx1OverPowerFaultMajor::PclTx1OverPowerFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx1OverPowerFaultMajor::~PclTx1OverPowerFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx2OverPowerFaultMajor::PclTx2OverPowerFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx2OverPowerFaultMajor::~PclTx2OverPowerFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx3OverPowerFaultMajor::PclTx3OverPowerFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx3OverPowerFaultMajor::~PclTx3OverPowerFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx4OverPowerFaultMajor::PclTx4OverPowerFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx4OverPowerFaultMajor::~PclTx4OverPowerFaultMajor()
{
}
