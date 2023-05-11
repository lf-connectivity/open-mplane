/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaTempMajorAlarm.cpp
 * \brief     Pa Temperature Major alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PaTempMajorAlarm.h"

#include "PaOverTemperatureFaultMajor.h"
#include "PaUnderTemperatureFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Pa1TempMajorAlarm::NAME="Pa1TempMajorAlarm";

const char* Pa2TempMajorAlarm::NAME="Pa2TempMajorAlarm";

const char* Pa3TempMajorAlarm::NAME="Pa3TempMajorAlarm";

const char* Pa4TempMajorAlarm::NAME="Pa4TempMajorAlarm";

//-------------------------------------------------------------------------------------------------------------
Pa1TempMajorAlarm::Pa1TempMajorAlarm() :
		AlarmLatched(Pa1TempMajorAlarm::NAME, "Power Amplifier 1 dangerously hot")
{
    registerFaults( { Pa1OverTemperatureFaultMajor::NAME,
    				  Pa1UnderTemperatureFaultMajor::NAME } ) ;
}

//-------------------------------------------------------------------------------------------------------------
Pa1TempMajorAlarm::~Pa1TempMajorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Pa2TempMajorAlarm::Pa2TempMajorAlarm() :
		AlarmLatched(Pa2TempMajorAlarm::NAME, "Power Amplifier 2 dangerously hot")
{
    registerFaults( { Pa2OverTemperatureFaultMajor::NAME,
    				  Pa2UnderTemperatureFaultMajor::NAME } ) ;
}

//-------------------------------------------------------------------------------------------------------------
Pa2TempMajorAlarm::~Pa2TempMajorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Pa3TempMajorAlarm::Pa3TempMajorAlarm() :
		AlarmLatched(Pa3TempMajorAlarm::NAME, "Power Amplifier 3 dangerously hot")
{
    registerFaults( { Pa3OverTemperatureFaultMajor::NAME,
    				  Pa3UnderTemperatureFaultMajor::NAME } ) ;
}

//-------------------------------------------------------------------------------------------------------------
Pa3TempMajorAlarm::~Pa3TempMajorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Pa4TempMajorAlarm::Pa4TempMajorAlarm() :
		AlarmLatched(Pa4TempMajorAlarm::NAME, "Power Amplifier 4 dangerously hot")
{
    registerFaults( { Pa4OverTemperatureFaultMajor::NAME,
    				  Pa4UnderTemperatureFaultMajor::NAME } ) ;
}

//-------------------------------------------------------------------------------------------------------------
Pa4TempMajorAlarm::~Pa4TempMajorAlarm()
{
}
