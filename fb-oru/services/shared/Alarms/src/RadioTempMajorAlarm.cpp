/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioTempMajorAlarm.cpp
 * \brief     Radio Temperature Major alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RadioTempMajorAlarm.h"

#include "BoardTxOverTemperatureFaultMajor.h"
#include "BoardTxUnderTemperatureFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* RadioTempMajorAlarm::NAME="RadioTempMajorAlarm";

//-------------------------------------------------------------------------------------------------------------
RadioTempMajorAlarm::RadioTempMajorAlarm() :
		AlarmLatched(NAME, "Unit temperature is dangerously hot")
{
    registerFaults( {  BoardTx1OverTemperatureFaultMajor::NAME,
					   BoardTx2OverTemperatureFaultMajor::NAME,
					   BoardTx3OverTemperatureFaultMajor::NAME,
					   BoardTx4OverTemperatureFaultMajor::NAME,
					   BoardTx1UnderTemperatureFaultMajor::NAME,
					   BoardTx2UnderTemperatureFaultMajor::NAME,
					   BoardTx3UnderTemperatureFaultMajor::NAME,
					   BoardTx4UnderTemperatureFaultMajor::NAME} ) ;
}

//-------------------------------------------------------------------------------------------------------------
RadioTempMajorAlarm::~RadioTempMajorAlarm()
{
}
