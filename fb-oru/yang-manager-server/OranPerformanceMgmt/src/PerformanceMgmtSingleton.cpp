/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PerformanceMgmtSingleton.cpp
 * \brief     PerformanceMgmt singleton
 *
 *
 * \details
 *
 */
#include "PerformanceMgmtService.h"

using namespace Mplane;

std::shared_ptr<IPerformanceMgmt> Mplane::IPerformanceMgmt::singleton(void)
{
	std::vector<int> sfpPorts;

	// Add the SFP port for the DU facing fibre
	sfpPorts.push_back(ISfpData::getPhysicalPortNum(0));

	static std::shared_ptr<IPerformanceMgmt> instance(std::make_shared<PerformanceMgmtService>(sfpPorts)) ;
	return instance ;
}
