/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MPlaneConnectivityServiceSingleton.cpp
 * \brief     ORAN M-Plane Connectivity Service Singleton
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <MPlaneConnectivityService.h>

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IMPlaneConnectivityService> IMPlaneConnectivityService::singleton(void)
{
	static std::shared_ptr<MPlaneConnectivityService> instance(std::make_shared<MPlaneConnectivityService>()) ;
	return instance ;
}
