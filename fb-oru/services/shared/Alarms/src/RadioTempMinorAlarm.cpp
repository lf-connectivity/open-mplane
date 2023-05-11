/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioTempMinorAlarm.cpp
 * \brief     BrdTx2Under Temperature Major alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RadioTempMinorAlarm.h"

#include "BoardTxOverTemperatureFaultMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* RadioTempMinorAlarm::NAME="RadioTempMinorAlarm";
//-------------------------------------------------------------------------------------------------------------
RadioTempMinorAlarm::RadioTempMinorAlarm() :
	Alarm(NAME, "Unit temperature is higher than expected", IAlarm::ALARM_MINOR)
{
    registerFaults( { BoardTx1OverTemperatureFaultMinor::NAME,
					  BoardTx2OverTemperatureFaultMinor::NAME,
					  BoardTx3OverTemperatureFaultMinor::NAME,
					  BoardTx4OverTemperatureFaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
RadioTempMinorAlarm::~RadioTempMinorAlarm()
{
}
