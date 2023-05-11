/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PllMajorAlarm.cpp
 * \brief     PllMajor alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PllMajorAlarm.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::PllMajorAlarm::NAME="PllMajorAlarm";

//-------------------------------------------------------------------------------------------------------------
Mplane::PllMajorAlarm::PllMajorAlarm() :
	Alarm(NAME, "PLL is out of lock")
{

}

//-------------------------------------------------------------------------------------------------------------
Mplane::PllMajorAlarm::~PllMajorAlarm()
{
}
