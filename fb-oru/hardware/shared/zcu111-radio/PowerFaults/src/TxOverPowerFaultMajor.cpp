/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxOverpowerFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxOverPowerFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Tx1OverPowerFaultMajor::NAME="Tx1OverPowerMajorFault";

const char* Mplane::Tx2OverPowerFaultMajor::NAME="Tx2OverPowerMajorFault";

const char* Mplane::Tx3OverPowerFaultMajor::NAME="Tx3OverPowerMajorFault";

const char* Mplane::Tx4OverPowerFaultMajor::NAME="Tx4OverPowerMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx1OverPowerFaultMajor::Tx1OverPowerFaultMajor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx1OverPowerFaultMajor::~Tx1OverPowerFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx2OverPowerFaultMajor::Tx2OverPowerFaultMajor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx2OverPowerFaultMajor::~Tx2OverPowerFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx3OverPowerFaultMajor::Tx3OverPowerFaultMajor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx3OverPowerFaultMajor::~Tx3OverPowerFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx4OverPowerFaultMajor::Tx4OverPowerFaultMajor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx4OverPowerFaultMajor::~Tx4OverPowerFaultMajor()
{
}
