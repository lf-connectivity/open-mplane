/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranAlarms.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "OranAlarms.h"

#include "CUPlaneConnectivityMajorAlarm.h"
#include "CUPlaneConnectivityMinorAlarm.h"


using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranAlarms::OranAlarms()
{
	// Create C/U-Plane connectivity alarms
	mCUPlaneConnectivityMajorAlarm = make_alarm<CUPlaneConnectivityMajorAlarm>();
	mCUPlaneConnectivityMinorAlarm = make_alarm<CUPlaneConnectivityMinorAlarm>();
}

//-------------------------------------------------------------------------------------------------------------
OranAlarms::~OranAlarms()
{
	// shared pointers will be taken care of here
}
