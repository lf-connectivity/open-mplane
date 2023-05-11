/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BoardTxUnderTemperatureFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "BoardTxUnderTemperatureFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::BoardTx1UnderTemperatureFaultMajor::NAME="BoardTx1UnderTemperatureMajorFault";

const char* Mplane::BoardTx2UnderTemperatureFaultMajor::NAME="BoardTx2UnderTemperatureMajorFault";

const char* Mplane::BoardTx3UnderTemperatureFaultMajor::NAME="BoardTx3UnderTemperatureMajorFault";

const char* Mplane::BoardTx4UnderTemperatureFaultMajor::NAME="BoardTx4UnderTemperatureMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx1UnderTemperatureFaultMajor::BoardTx1UnderTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx1UnderTemperatureFaultMajor::~BoardTx1UnderTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx2UnderTemperatureFaultMajor::BoardTx2UnderTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx2UnderTemperatureFaultMajor::~BoardTx2UnderTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx3UnderTemperatureFaultMajor::BoardTx3UnderTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx3UnderTemperatureFaultMajor::~BoardTx3UnderTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx4UnderTemperatureFaultMajor::BoardTx4UnderTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::BoardTx4UnderTemperatureFaultMajor::~BoardTx4UnderTemperatureFaultMajor()
{
}
