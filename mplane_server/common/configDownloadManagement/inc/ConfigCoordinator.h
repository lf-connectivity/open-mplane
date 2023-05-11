/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ConfigCoordinator.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef CONFIG_COORDINATOR_H_
#define CONFIG_COORDINATOR_H_

#include <map>
#include <memory>
#include <mutex>
#include <tuple>

#include "IConfigCoordinator.h"
#include "IConfigDownloadManagement.h"

namespace Mplane {

/**
 * The ConfigCoordinator interface manages the configuration objects registered
 * with it
 *
 */
class ConfigCoordinator : public virtual IConfigCoordinator {
 public:
  /**
   * Constructor
   */
  ConfigCoordinator();

  /**
   * Destructor
   */
  virtual ~ConfigCoordinator();

  /**
   * Method called to register a configuration object
   */
  virtual ReturnType::State registerConfig(
      std::shared_ptr<IConfigDownload> cfgDownload,
      std::shared_ptr<IConfigLoad> cfgData) override;

  /**
   * Method used to indicate that the application has loaded its configuration
   * data
   * @return
   */
  virtual bool isConfigRegistered(std::string name) override;

  /**
   * Method called during radio initialisation to load the various configuration
   * data files used by the various configuration data interfaces
   */
  virtual ReturnType::State load() override;

  /**
   * Method called during radio initialisation to load a specific configuration
   * data file
   */
  virtual ReturnType::State load(std::string name) override;

 private:
  // Map of config objects
  std::map<
      std::string,
      std::
          tuple<std::shared_ptr<IConfigDownload>, std::shared_ptr<IConfigLoad>>>
      mConfigs;
  std::mutex mMutex; //!> Mutex to protect the map access
};

} // namespace Mplane

#endif /* CONFIG_COORDINATOR_H_ */
