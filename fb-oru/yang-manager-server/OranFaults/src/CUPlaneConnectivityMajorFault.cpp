/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectivityMajorFault.cpp
 * \brief     ORAN C/U-Plane Connectivity major fault
 *
 *
 * \details   ORAN C/U-Plane Connectivity major fault container
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CUPlaneConnectivityMajorFault.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char * CUPlaneConnectivityMajorFault::NAME="CUPlaneConnectivityMajorFault";

//-------------------------------------------------------------------------------------------------------------
CUPlaneConnectivityMajorFault::CUPlaneConnectivityMajorFault()
	: Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
CUPlaneConnectivityMajorFault::~CUPlaneConnectivityMajorFault()
{
}
