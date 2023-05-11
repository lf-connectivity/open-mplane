/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HeartBeatAlarm.cpp
 * \brief     HeartBeat alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "HeartBeatMajorAlarm.h"
#include "HeartBeatFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::HeartBeatAlarm::NAME="HeartBeatAlarm";

//-------------------------------------------------------------------------------------------------------------
HeartBeatAlarm::HeartBeatAlarm() :
	Alarm(NAME, "Watchdog heatbeat was not seen")
{
    registerFault( Mplane::HeartBeatFaultMajor::NAME );
}

//-------------------------------------------------------------------------------------------------------------
HeartBeatAlarm::~HeartBeatAlarm()
{
}
