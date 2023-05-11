/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Tx1UnderpowerFaultMinor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxUnderPowerFaultMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Tx1UnderPowerFaultMinor::NAME="Tx1UnderPowerMinorFault";

const char* Mplane::Tx2UnderPowerFaultMinor::NAME="Tx2UnderPowerMinorFault";

const char* Mplane::Tx3UnderPowerFaultMinor::NAME="Tx3UnderPowerMinorFault";

const char* Mplane::Tx4UnderPowerFaultMinor::NAME="Tx4UnderPowerMinorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx1UnderPowerFaultMinor::Tx1UnderPowerFaultMinor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx1UnderPowerFaultMinor::~Tx1UnderPowerFaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx2UnderPowerFaultMinor::Tx2UnderPowerFaultMinor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx2UnderPowerFaultMinor::~Tx2UnderPowerFaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx3UnderPowerFaultMinor::Tx3UnderPowerFaultMinor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx3UnderPowerFaultMinor::~Tx3UnderPowerFaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx4UnderPowerFaultMinor::Tx4UnderPowerFaultMinor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx4UnderPowerFaultMinor::~Tx4UnderPowerFaultMinor()
{
}
