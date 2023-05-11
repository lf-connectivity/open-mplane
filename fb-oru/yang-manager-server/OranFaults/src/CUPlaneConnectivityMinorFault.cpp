/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectivityMinorFault.cpp
 * \brief     ORAN C/U-Plane Connectivity minor fault
 *
 *
 * \details   ORAN C/U-Plane Connectivity minor fault container
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CUPlaneConnectivityMinorFault.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char * CUPlaneConnectivityMinorFault::NAME="CUPlaneConnectivityMinorFault";

//-------------------------------------------------------------------------------------------------------------
CUPlaneConnectivityMinorFault::CUPlaneConnectivityMinorFault()
	: Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
CUPlaneConnectivityMinorFault::~CUPlaneConnectivityMinorFault()
{
}
