#ifndef _ICONFIGDATA_H_
#define _ICONFIGDATA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IConfigData.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "GlobalTypeDefs.h"
#include "IConfigDownload.h"
#include "string.h"
#include <memory>
#include <stdexcept>

namespace Mplane {

/**
 * The IConfigLoad interface provides interface to cal file loading
 *
 */
class IConfigLoad {
 public:
  /**
   * Method used to provide path to load the configuration
   */
  virtual void setPath(std::shared_ptr<IConfigDownload> download) = 0;

  /**
   * Method used to get the path to load the configuration
   */
  virtual std::string getPath() = 0;

  /**
   * Method called during radio initialisation to load the various configuration
   * data files used by the various configuration data interfaces and populate
   * the ITxCal and IRxCal interface implementations.
   * @return
   */
  virtual ReturnType::State load() = 0;

  /**
   * Method used to indicate that the application has loaded its configuration
   * data
   * @return
   */
  virtual bool isLoaded() = 0;

  /**
   * Default destructor
   */
  virtual ~IConfigLoad() {}
};

/**
 * This class defines a base set of functionality expected to be implemented by
 * all configuration data interfaces. This data must include a general
 * information string and version number.
 *
 * The load() method is called during initialisation to load the configuration
 * data from from its particular data store. Once successfully the isLoaded()
 * method is expected to return true.
 *
 */
class IConfigBase : public virtual IConfigLoad {
 public:
  /**
   * Return a general information string associated with the creation of the
   * configuration data, this data is set by the final implementation using the
   * protected setInfo() method.
   * @return configuration information string
   */
  virtual std::string getInfo() = 0;

  /**
   * Return the version number of the configuration data, this defaults to -1
   * and must be set by the final configuration data implementation using the
   * protected setVersion() method.
   * @return
   */
  virtual int getVersion() = 0;

  /**
   * Empty virtual destructor for pure virtual interface
   */
  virtual ~IConfigBase() {}
};

/**
 * The IConfigData interface provides a common base implementation that can be
 * incrementally applied to functionality associated with any number of radio
 * types. It defines access methods used to return the base configuration data
 * interface common to a number of types. This interface can be used to first
 * load the configuration data and secondly provide an interface to the basic
 * configuration object that can be dynamically cast to a known high level
 * implementation.
 *
 * If a particular hardware configuration doesn't support a specific
 * configuration data type, calling the appropriate get method will throw an
 * exception that will cause the application to terminate. This is a logical
 * programming error that must be fixed.
 *
 */
class IConfigData : public virtual IConfigLoad {
 public:
  // Uses the IConfigLoad interface : load() and isLoaded()

  /**
   * Default destructor
   */
  virtual ~IConfigData() {}
};

class IConfigDataFactory {
 public:
  /** @brief  Get the singleton instance of the configuration data interface
   *
   *  Used to get a reference to the single instance of the radio hardware
   *  configuration data object. This must be implemented using the singleton
   * pattern by the specific radio implementation.
   *
   *  Must be define in: hardware/<BOARD>/radio/src/<Board>ConfigDataFactory.cpp
   *
   *  Test mock defined in: vrh/test/src/TestIConfigData.cpp
   *
   *
   */
  static std::shared_ptr<IConfigData> getInterface(void);
};

} // namespace Mplane

#endif /* _ICONFIGDATA_H_ */
