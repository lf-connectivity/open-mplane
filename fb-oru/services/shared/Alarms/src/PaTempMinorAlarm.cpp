/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaTempMinorAlarm.cpp
 * \brief     Pa Temperature Minor alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PaTempMinorAlarm.h"

#include "PaOverTemperatureFaultMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Pa1TempMinorAlarm::NAME="Pa1TempMinorAlarm";

const char* Pa2TempMinorAlarm::NAME="Pa2TempMinorAlarm";

const char* Pa3TempMinorAlarm::NAME="Pa3TempMinorAlarm";

const char* Pa4TempMinorAlarm::NAME="Pa4TempMinorAlarm";

//-------------------------------------------------------------------------------------------------------------
Pa1TempMinorAlarm::Pa1TempMinorAlarm() :
	Alarm(Pa1TempMinorAlarm::NAME, "Power Amplifier 1 hotter than expected", IAlarm::ALARM_MINOR)
{
    registerFault(Mplane::Pa1OverTemperatureFaultMinor::NAME) ;
}

//-------------------------------------------------------------------------------------------------------------
Pa1TempMinorAlarm::~Pa1TempMinorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Pa2TempMinorAlarm::Pa2TempMinorAlarm() :
	Alarm(Pa2TempMinorAlarm::NAME, "Power Amplifier 2 hotter than expected", IAlarm::ALARM_MINOR)
{
    registerFault(Mplane::Pa2OverTemperatureFaultMinor::NAME) ;
}

//-------------------------------------------------------------------------------------------------------------
Pa2TempMinorAlarm::~Pa2TempMinorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Pa3TempMinorAlarm::Pa3TempMinorAlarm() :
	Alarm(Pa3TempMinorAlarm::NAME, "Power Amplifier 3 hotter than expected", IAlarm::ALARM_MINOR)
{
    registerFault(Mplane::Pa3OverTemperatureFaultMinor::NAME) ;
}

//-------------------------------------------------------------------------------------------------------------
Pa3TempMinorAlarm::~Pa3TempMinorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Pa4TempMinorAlarm::Pa4TempMinorAlarm() :
	Alarm(Pa4TempMinorAlarm::NAME, "Power Amplifier 4 hotter than expected", IAlarm::ALARM_MINOR)
{
    registerFault(Mplane::Pa4OverTemperatureFaultMinor::NAME) ;
}

//-------------------------------------------------------------------------------------------------------------
Pa4TempMinorAlarm::~Pa4TempMinorAlarm()
{
}
