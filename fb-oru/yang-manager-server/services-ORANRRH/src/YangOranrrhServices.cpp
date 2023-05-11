/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangOranRrhServices.h
 * \brief     Implementation of YANG ORAN radio services interface to create and controls all radio services
 *
 *
 * \details   Implementation of YANG ORAN radio services interface to create and controls all radio services
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#define REGISTER_YANG_MGR_SERVICE

#include "IConfigCoordinator.h"
#include "YangConfigDownload.h"
#include "YangConfigParser.h"

#include "INetopeerMonService.h"
#include "IPerformanceMgmt.h"
#include "IMPlaneConnectivityService.h"
#include "Dot1agdMonService.h"
#if defined(REGISTER_YANG_MGR_SERVICE)
#include "YangMgrService.h"
#endif /* REGISTER_YANG_MGR_SERVICE */

#include "YangOranrrhServices.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
YangOranrrhServices::YangOranrrhServices():
	OranRrhServices()
{
	// Services

	// Get the instance of configuration coordinator
	std::shared_ptr<IConfigCoordinator> configCoord = IConfigCoordinator::singleton();

	// Register the Yang config download and Yang config parser with the coordinator
	std::shared_ptr<IConfigDownload> cfgDownload = std::make_shared<YangConfigDownload>();
	std::shared_ptr<IConfigLoad> cfgData = std::make_shared<YangConfigParser>();
	configCoord->registerConfig(cfgDownload, cfgData);

	// Load the Yang configuration
	if (configCoord->load(cfgDownload->getName()) != ReturnType::RT_OK)
	{
		eventError("Unable to load Yang configuration") ;
	}

	// Application monitors
	registerServiceInsert(std::dynamic_pointer_cast<Service>(INetopeerMonService::singleton()));
	registerServiceInsert(std::dynamic_pointer_cast<Service>(Dot1agdMonService::singleton()));

#if defined(REGISTER_YANG_MGR_SERVICE)
	// Register the YANG manager server Service
	registerServiceInsert( YangMgrService::singleton() );
#endif /* REGISTER_YANG_MGR_SERVICE */

	// Register the ORAN performance management service
	registerServiceInsert(std::dynamic_pointer_cast<Service>(IPerformanceMgmt::singleton()));

	// Register the ORAN M-Plane connectivity service
	registerServiceInsert(std::dynamic_pointer_cast<Service>(IMPlaneConnectivityService::singleton()));
}

//-------------------------------------------------------------------------------------------------------------
YangOranrrhServices::~YangOranrrhServices()
{
}
