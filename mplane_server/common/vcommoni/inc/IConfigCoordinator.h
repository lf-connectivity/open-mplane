#ifndef _ICONFIGCOORDINATOR_H_
#define _ICONFIGCOORDINATOR_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IConfigCoordinator.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "GlobalTypeDefs.h"
#include "IConfigData.h"
#include "IConfigDownload.h"
#include "string.h"
#include <memory>

namespace Mplane {

/**
 * The IConfigCoordinator interface manages the configuration objects registered
 * with it
 *
 */
class IConfigCoordinator {
 public:
  /**
   * Singleton
   */
  static std::shared_ptr<IConfigCoordinator> singleton();

  /**
   * Method called to register a configuration object
   */
  virtual ReturnType::State registerConfig(
      std::shared_ptr<IConfigDownload> cfgDownload,
      std::shared_ptr<IConfigLoad> cfgData) = 0;

  /**
   * Method used to indicate that the application has loaded its configuration
   * data
   * @return
   */
  virtual bool isConfigRegistered(std::string name) = 0;

  /**
   * Method called during radio initialisation to load the various configuration
   * data files used by the various configuration data interfaces
   */
  virtual ReturnType::State load() = 0;

  /**
   * Method called during radio initialisation to load a specific configuration
   * data file
   */
  virtual ReturnType::State load(std::string name) = 0;

  /**
   * Default destructor
   */
  virtual ~IConfigCoordinator() {}
};

} // namespace Mplane

#endif /* _ICONFIGCOORDINATOR_H_ */
