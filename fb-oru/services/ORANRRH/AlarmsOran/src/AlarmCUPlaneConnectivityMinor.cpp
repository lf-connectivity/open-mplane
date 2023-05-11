/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmCUPlaneConnectivityMinor.cpp
 * \brief     ORAN C/U-Plane Connectivity minor alarm
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FaultCUPlaneConnectivityMinor.h"
#include "AlarmCUPlaneConnectivityMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* AlarmCUPlaneConnectivityMinor::NAME="AlarmCUPlaneConnectivityMinor";
const char* AlarmCUPlaneConnectivityMinor::DESCRIPTION="Minor CU-plane alarm";

//-------------------------------------------------------------------------------------------------------------
AlarmCUPlaneConnectivityMinor::AlarmCUPlaneConnectivityMinor()
	: Alarm(NAME, DESCRIPTION)
{
	registerFault(FaultCUPlaneConnectivityMinor::NAME);
}

//-------------------------------------------------------------------------------------------------------------
Mplane::AlarmCUPlaneConnectivityMinor::~AlarmCUPlaneConnectivityMinor()
{
}
