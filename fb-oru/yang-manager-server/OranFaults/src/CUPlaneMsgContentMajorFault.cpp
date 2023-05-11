/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneMsgContentMajorFault.cpp
 * \brief     ORAN C/U-Plane Message Content major fault
 *
 *
 * \details   ORAN C/U-Plane Message Content major fault container
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CUPlaneMsgContentMajorFault.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char * CUPlaneMsgContentMajorFault::NAME="CUPlaneMsgContentMajorFault";

//-------------------------------------------------------------------------------------------------------------
CUPlaneMsgContentMajorFault::CUPlaneMsgContentMajorFault()
	: Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
CUPlaneMsgContentMajorFault::~CUPlaneMsgContentMajorFault()
{
}
