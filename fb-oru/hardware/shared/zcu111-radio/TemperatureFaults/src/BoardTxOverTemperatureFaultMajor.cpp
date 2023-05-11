/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BoardTxOverTemperatureFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "BoardTxOverTemperatureFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::BoardTx1OverTemperatureFaultMajor::NAME="BoardTx1OverTemperatureMajorFault";

const char* Mplane::BoardTx2OverTemperatureFaultMajor::NAME="BoardTx2OverTemperatureMajorFault";

const char* Mplane::BoardTx3OverTemperatureFaultMajor::NAME="BoardTx3OverTemperatureMajorFault";

const char* Mplane::BoardTx4OverTemperatureFaultMajor::NAME="BoardTx4OverTemperatureMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx1OverTemperatureFaultMajor::BoardTx1OverTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx1OverTemperatureFaultMajor::~BoardTx1OverTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx2OverTemperatureFaultMajor::BoardTx2OverTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx2OverTemperatureFaultMajor::~BoardTx2OverTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx3OverTemperatureFaultMajor::BoardTx3OverTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx3OverTemperatureFaultMajor::~BoardTx3OverTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx4OverTemperatureFaultMajor::BoardTx4OverTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx4OverTemperatureFaultMajor::~BoardTx4OverTemperatureFaultMajor()
{
}
