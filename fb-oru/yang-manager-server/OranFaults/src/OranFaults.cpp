/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranFaults.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "OranFaults.h"
#include "CUPlaneConnectivityMajorFault.h"
#include "CUPlaneConnectivityMinorFault.h"
#include "CUPlaneMsgContentMajorFault.h"
#include "CUPlaneMsgContentMinorFault.h"


using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranFaults::OranFaults()
{
	// Create C/U-Plane connectivity alarms
	mCUPlaneConnectivityMajorFault = make_fault<CUPlaneConnectivityMajorFault>();
	mCUPlaneConnectivityMinorFault = make_fault<CUPlaneConnectivityMinorFault>();

	// Create C/U-Plane message content alarms
	mCUPlaneMsgContentMajorFault = make_fault<CUPlaneMsgContentMajorFault>();
	mCUPlaneMsgContentMinorFault = make_fault<CUPlaneMsgContentMinorFault>();
}

//-------------------------------------------------------------------------------------------------------------
OranFaults::~OranFaults()
{
	// shared pointers will be taken care of here
}
