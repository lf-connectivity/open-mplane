/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectServiceSingleton.cpp
 * \brief     ORAN C/U-Plane Connectivity Service Singleton
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "CUPlaneConnectService.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICUPlaneConnectService> ICUPlaneConnectService::CUPlaneConnectServiceSingleton(void)
{
	static std::shared_ptr<CUPlaneConnectService> instance(std::make_shared<CUPlaneConnectService>()) ;
	return instance ;
}
