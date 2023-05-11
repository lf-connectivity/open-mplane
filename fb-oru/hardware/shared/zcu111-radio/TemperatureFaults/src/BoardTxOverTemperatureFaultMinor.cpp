/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BoardTx1OverTemperatureFaultMinor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "BoardTxOverTemperatureFaultMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::BoardTx1OverTemperatureFaultMinor::NAME="BoardTx1OverTemperatureMinorFault";

const char* Mplane::BoardTx2OverTemperatureFaultMinor::NAME="BoardTx2OverTemperatureMinorFault";

const char* Mplane::BoardTx3OverTemperatureFaultMinor::NAME="BoardTx3OverTemperatureMinorFault";

const char* Mplane::BoardTx4OverTemperatureFaultMinor::NAME="BoardTx4OverTemperatureMinorFault";


//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx1OverTemperatureFaultMinor::BoardTx1OverTemperatureFaultMinor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx1OverTemperatureFaultMinor::~BoardTx1OverTemperatureFaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx2OverTemperatureFaultMinor::BoardTx2OverTemperatureFaultMinor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx2OverTemperatureFaultMinor::~BoardTx2OverTemperatureFaultMinor()
{
}


//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx3OverTemperatureFaultMinor::BoardTx3OverTemperatureFaultMinor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx3OverTemperatureFaultMinor::~BoardTx3OverTemperatureFaultMinor()
{
}


//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx4OverTemperatureFaultMinor::BoardTx4OverTemperatureFaultMinor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx4OverTemperatureFaultMinor::~BoardTx4OverTemperatureFaultMinor()
{
}
