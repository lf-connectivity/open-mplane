/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectivityMinorAlarm.cpp
 * \brief     ORAN C/U-Plane Connectivity minor alarm
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CUPlaneConnectivityMinorAlarm.h"
#include "CUPlaneConnectivityMinorFault.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* CUPlaneConnectivityMinorAlarm::NAME="CUPlaneConnectivityMinorAlarm";

//-------------------------------------------------------------------------------------------------------------
CUPlaneConnectivityMinorAlarm::CUPlaneConnectivityMinorAlarm()
	: Alarm(NAME, "CUPlane logical connection is faulty, unstable or broken", IAlarm::ALARM_MINOR)
{
	registerFault(CUPlaneConnectivityMinorFault::NAME);
}

//-------------------------------------------------------------------------------------------------------------
Mplane::CUPlaneConnectivityMinorAlarm::~CUPlaneConnectivityMinorAlarm()
{
}
