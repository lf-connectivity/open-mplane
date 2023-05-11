/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneMsgContentMinorFault.cpp
 * \brief     ORAN C/U-Plane Message Content minor fault
 *
 *
 * \details   ORAN C/U-Plane Message Content minor fault container
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CUPlaneMsgContentMinorFault.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char * CUPlaneMsgContentMinorFault::NAME="CUPlaneMsgContentMinorFault";

//-------------------------------------------------------------------------------------------------------------
CUPlaneMsgContentMinorFault::CUPlaneMsgContentMinorFault()
	: Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
CUPlaneMsgContentMinorFault::~CUPlaneMsgContentMinorFault()
{
}
