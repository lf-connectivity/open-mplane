/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneMonitorSingleton.cpp
 * \brief     ORAN C/U-Plane Monitoring Singleton
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "CUPlaneMonitor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICUPlaneMonitor> ICUPlaneMonitor::singleton(void)
{
	static std::shared_ptr<CUPlaneMonitor> instance(std::make_shared<CUPlaneMonitor>()) ;
	return instance ;
}
