/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectivityMajorAlarm.cpp
 * \brief     ORAN C/U-Plane Connectivity major alarm
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CUPlaneConnectivityMajorAlarm.h"
#include "CUPlaneConnectivityMajorFault.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* CUPlaneConnectivityMajorAlarm::NAME="CUPlaneConnectivityMajorAlarm";

//-------------------------------------------------------------------------------------------------------------
CUPlaneConnectivityMajorAlarm::CUPlaneConnectivityMajorAlarm()
	: Alarm(NAME, "C/U-Plane logical connection is faulty, unstable or broken")
{
	registerFault(CUPlaneConnectivityMajorFault::NAME);
}

//-------------------------------------------------------------------------------------------------------------
Mplane::CUPlaneConnectivityMajorAlarm::~CUPlaneConnectivityMajorAlarm()
{
}
