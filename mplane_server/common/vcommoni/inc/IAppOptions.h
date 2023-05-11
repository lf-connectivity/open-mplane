/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAppOptions.h
 * \brief     Applications options Instance
 *
 *
 * \details
 *
 */

#ifndef IAPPOPTIONS_H_
#define IAPPOPTIONS_H_

#include "DataVariant.h"
#include <memory>
#include <vector>

namespace Mplane {

/**
 * The IAppOptionSpec class defines a pure virtual interface to the data
 * that can be defined when creating a new application that uses the
 * Mplane::IAppOptions class.
 */
class IAppOptionSpec {
 public:
  virtual ~IAppOptionSpec() {}

  /**
   * Get the option specification data entry
   * @return DatVariant for this entry
   */
  virtual DataVariant& getData() = 0;

  /**
   * Get the environment variable name to use for setting this option
   * @return environment variable name or empty string
   */
  virtual std::string getUseEnv() const = 0;

  /**
   * Get the default value for this option
   * @return default value or empty string
   */
  virtual std::string getDefault() const = 0;

  /**
   * Get the description for this option
   * @return description
   */
  virtual std::string getDescription() const = 0;

  /**
   * Factory methods for creating an options specification entry
   */

  /**
   * Factory method for creating an options specification entry
   * @param name    Option name
   * @param type    Option type
   * @param description    Description of option
   * @return option specification
   */
  static std::shared_ptr<IAppOptionSpec> factory(
      const std::string& name,
      const DataVariantType::Type& type,
      const std::string& description);

  /**
   * Factory method for creating an options specification entry
   * @param name    Option name
   * @param type    Option type
   * @param description    Description of option
   * @param defaultValue    Default value to use if option not specified
   * @return option specification
   */
  static std::shared_ptr<IAppOptionSpec> factory(
      const std::string& name,
      const DataVariantType::Type& type,
      const std::string& description,
      const std::string& defaultValue);

  /**
   * Factory method for creating an options specification entry
   * @param name    Option name
   * @param type    Option type
   * @param description    Description of option
   * @param defaultValue    Default value to use if option not specified
   * @param useEnvVar    If option is not specified on the command line, try
   * using this environment variable. If that isn't specified either then use
   * default value
   * @return option specification
   */
  static std::shared_ptr<IAppOptionSpec> factory(
      const std::string& name,
      const DataVariantType::Type& type,
      const std::string& description,
      const std::string& defaultValue,
      const std::string& useEnvVar);

 protected:
  IAppOptionSpec() {}
};

/**
 * The IAppOptions class defines a pure virtual interface that must be
 * implemented by all Mplane software platform applications that implement the
 * Mplane::IApplication interface.
 *
 * It allows the application to be created with a number of startup options
 * defined.
 */
class IAppOptions {
 public:
  virtual ~IAppOptions() {}

  /**
   * Singleton creation - called with the command line args
   * @param argc
   * @param argv
   * @param applicationDescription - a string that describes the application
   * @param optionsSpecification - a vector of IAppOtionSpec objects
   * @return shared pointer to singleton
   */
  static std::shared_ptr<IAppOptions> createInstance(
      int argc,
      const char** argv,
      const std::string& applicationDescription,
      const std::vector<std::shared_ptr<IAppOptionSpec>>& optionsSpecification);

  /**
   * Singleton access
   * @return shared pointer to singleton
   */
  static std::shared_ptr<IAppOptions> getInstance();

  /**
   * Get the option given by the name
   * @param name
   * @return DataVariant containing the option named
   */
  virtual const DataVariant getOption(const std::string& name) const = 0;

 protected:
  IAppOptions() {}

  static std::shared_ptr<IAppOptions> singleton(
      int argc,
      const char** argv,
      const std::string& applicationDescription,
      const std::vector<std::shared_ptr<IAppOptionSpec>>& optionsSpecification);
};

} // namespace Mplane

#endif /* IAPPOPTIONS_H_ */
