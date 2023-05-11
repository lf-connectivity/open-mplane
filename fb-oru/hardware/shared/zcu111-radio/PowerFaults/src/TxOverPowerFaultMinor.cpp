/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxOverpowerFaultMinor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxOverPowerFaultMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Tx1OverPowerFaultMinor::NAME="Tx1OverPowerMinorFault";

const char* Mplane::Tx2OverPowerFaultMinor::NAME="Tx2OverPowerMinorFault";

const char* Mplane::Tx3OverPowerFaultMinor::NAME="Tx3OverPowerMinorFault";

const char* Mplane::Tx4OverPowerFaultMinor::NAME="Tx4OverPowerMinorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx1OverPowerFaultMinor::Tx1OverPowerFaultMinor() :
	Fault(4, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx1OverPowerFaultMinor::~Tx1OverPowerFaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx2OverPowerFaultMinor::Tx2OverPowerFaultMinor() :
	Fault(4, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx2OverPowerFaultMinor::~Tx2OverPowerFaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx3OverPowerFaultMinor::Tx3OverPowerFaultMinor() :
	Fault(4, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx3OverPowerFaultMinor::~Tx3OverPowerFaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx4OverPowerFaultMinor::Tx4OverPowerFaultMinor() :
	Fault(4, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx4OverPowerFaultMinor::~Tx4OverPowerFaultMinor()
{
}
