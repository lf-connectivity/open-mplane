/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangServices.cpp
 * \brief     Implementation of services interface to create and controls all
 * services
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IAppOptions.h"
#include "IBootTimer.h"
#include "IYangHandlerMgr.h"

#include "SysrepoUtils.h"
#include "YangMgrServer.h"
#include "YangMgrService.h"
#include "YangParamUtils.h"

#include "YangServices.h"

#include "config.h"

#include "IConfigCoordinator.h"
#include "YangConfigDownload.h"
#include "YangConfigParser.h"

#include "INetopeerMonService.h"
#include "YangMgrService.h"

#include <HalMplane.h>

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangServices::YangServices()
    : AppServices("YangManagerServerApplicationService") {
  // Services

  // Get the instance of configuration coordinator
  std::shared_ptr<IConfigCoordinator> configCoord =
      IConfigCoordinator::singleton();

  // Register the Yang config download and Yang config parser with the
  // coordinator
  std::shared_ptr<IConfigDownload> cfgDownload =
      std::make_shared<YangConfigDownload>();
  std::shared_ptr<IConfigLoad> cfgData = std::make_shared<YangConfigParser>();
  configCoord->registerConfig(cfgDownload, cfgData);

  // Load the Yang configuration
  if (configCoord->load(cfgDownload->getName()) != ReturnType::RT_OK) {
    eventError("Unable to load Yang configuration");
  }

  // Application monitors
  registerServiceInsert(
      std::dynamic_pointer_cast<Service>(INetopeerMonService::singleton()));

  // Register the YANG manager server Service
  registerServiceInsert(YangMgrService::singleton());

  std::string filePath = cfgData->getPath();
  tinyxml2::XMLDocument doc;
  if (doc.LoadFile(filePath.c_str()) == tinyxml2::XML_NO_ERROR)
    {
      halmplane_init(&doc);
    }
  else
    {
      halmplane_init(NULL);
    }

  // YANG
  eventInfo("RRH get YANG manager server");
  std::shared_ptr<YangMgrService> yangService(YangMgrService::singleton());
  std::shared_ptr<YangMgrServer> yangServer(yangService->getYangMgrServer());

  eventInfo("RRH initialise YANG handlers");
  std::shared_ptr<IYangHandlerMgr> yangHandlerMgr(
      IYangHandlerMgr::create(yangServer));
  if (!yangHandlerMgr->initialise()) {
    eventError("RRH unable to initialise YANG handlers");
  }
}

//-------------------------------------------------------------------------------------------------------------
YangServices::~YangServices() {}

//-------------------------------------------------------------------------------------------------------------
void
YangServices::shutdown() {
  AppServices::shutdown();
  halmplane_exit();
}
