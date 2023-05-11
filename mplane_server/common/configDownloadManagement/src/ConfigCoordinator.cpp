/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ConfigCoordinator.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ConfigCoordinator.h"
#include "stringfunc.hpp"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//=============================================================================================================
// SINGLETON
//=============================================================================================================

std::shared_ptr<IConfigCoordinator>
IConfigCoordinator::singleton() {
  static std::shared_ptr<IConfigCoordinator> instance =
      std::make_shared<ConfigCoordinator>();

  return instance;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ConfigCoordinator::ConfigCoordinator() : mConfigs(), mMutex() {}

//-------------------------------------------------------------------------------------------------------------
ConfigCoordinator::~ConfigCoordinator() {}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State
ConfigCoordinator::registerConfig(
    std::shared_ptr<IConfigDownload> cfgDownload,
    std::shared_ptr<IConfigLoad> cfgData) {
  ReturnType::State rc = ReturnType::RT_OPERATION_FAILED;

  // Add the config download type to the config download manager
  if (IConfigDownloadManagement::getInstance()->addConfigDownloadType(
          cfgDownload)) {
    // Protect the access to the map with a mutex
    std::lock_guard<std::mutex> lock(mMutex);

    std::string name = toUpper(cfgDownload->getName());

    // Add the config objects to the map
    mConfigs[name] = std::make_tuple(cfgDownload, cfgData);

    // Provide the download object to the data object to extract the file path
    cfgData->setPath(cfgDownload);

    rc = ReturnType::RT_OK;
  }

  return rc;
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigCoordinator::isConfigRegistered(std::string name) {
  // Check if the configuration name is in the map
  auto entry(mConfigs.find(toUpper(name)));
  if (entry != mConfigs.end()) {
    return true;
  }

  return false;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State
ConfigCoordinator::load() {
  ReturnType::State rc = ReturnType::RT_OK;

  // Protect the access to the map with a mutex
  std::lock_guard<std::mutex> lock(mMutex);

  // Navigate through the map
  for (auto const& config : mConfigs) {
    // Get the configuration data and load the configuration
    auto cfgData = std::get<1>(config.second);
    ReturnType::State result = cfgData->load();
    if (result != ReturnType::RT_OK) {
      rc = result;
    }
  }

  return rc;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State
ConfigCoordinator::load(std::string name) {
  ReturnType::State rc = ReturnType::RT_NOT_FOUND;

  // Check if configuration is registered with the coordinator
  if (isConfigRegistered(name)) {
    // Protect the access to the map with a mutex
    std::lock_guard<std::mutex> lock(mMutex);

    // Get the data and load the configuration
    auto cfgData = std::get<1>(mConfigs[toUpper(name)]);
    rc = cfgData->load();
  }

  return rc;
}
