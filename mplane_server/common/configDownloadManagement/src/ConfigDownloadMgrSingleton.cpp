/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ConfigDownloadMgrSingleton.cpp
 * \brief     Singleton to create the ConfigDownloadManagement object
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ConfigDownloadManagement.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
class ConfigDownloadMgr : public ConfigDownloadManagement {
 public:
  ConfigDownloadMgr() : ConfigDownloadManagement() {}

  virtual ~ConfigDownloadMgr() {}
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IConfigDownloadManagement>
IConfigDownloadManagement::getInstance() {
  static std::shared_ptr<IConfigDownloadManagement> instance(
      new ConfigDownloadMgr());
  static int start =
      std::dynamic_pointer_cast<ConfigDownloadManagement>(instance)->start();

  // avoid compiler warning
  int rc = start;
  start = rc;

  return instance;
}
