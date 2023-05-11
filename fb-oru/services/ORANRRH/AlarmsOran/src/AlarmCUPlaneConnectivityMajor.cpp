/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmCUPlaneConnectivityMajor.cpp
 * \brief     ORAN C/U-Plane Connectivity major alarm
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FaultCUPlaneConnectivityMajor.h"
#include "AlarmCUPlaneConnectivityMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* AlarmCUPlaneConnectivityMajor::NAME="AlarmCUPlaneConnectivityMajor";
const char* AlarmCUPlaneConnectivityMajor::DESCRIPTION="Major CU-plane alarm";

//-------------------------------------------------------------------------------------------------------------
AlarmCUPlaneConnectivityMajor::AlarmCUPlaneConnectivityMajor()
	: Alarm(NAME, DESCRIPTION)
{
	registerFault(FaultCUPlaneConnectivityMajor::NAME);
}

//-------------------------------------------------------------------------------------------------------------
Mplane::AlarmCUPlaneConnectivityMajor::~AlarmCUPlaneConnectivityMajor()
{
}
