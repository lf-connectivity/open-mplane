/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDataVariantSettings.h
 * \brief     Interface to settings for DataVariant variable expansion
 *
 *
 * \details
 *
 */

#ifndef IDATAVARIANTSETTINGS_H_
#define IDATAVARIANTSETTINGS_H_

#include <map>
#include <memory>
#include <string>

namespace Mplane {

class IDataVariantSettings {
 public:
  /**
   * Singleton
   */
  static std::shared_ptr<IDataVariantSettings> getInstance();

  virtual ~IDataVariantSettings() {}

  /**
   * Clear out all settings (mainly used for test)
   */
  virtual void clearSettings() = 0;

  /**
   * One-off registration of all the valid variable names and any default values
   * @param settings
   */
  virtual void registerSettings(
      const std::map<std::string, std::string>& settings) = 0;

  /**
   * Is the named setting registered?
   * @param name
   * @return true if registered; false otherwise
   */
  virtual bool isSetting(const std::string& name) const = 0;

  /**
   * Set the value of the specified named setting
   * @param name
   * @param value
   * @return true if set; false if unable to set (setting name invalid)
   */
  virtual bool setSetting(
      const std::string& name, const std::string& value) = 0;

  /**
   * Expand any settings variables in string 'str' and return the expanded
   * string
   * @param str
   * @param error
   * @return expanded string or empty string with error string set on error
   */
  virtual std::string expandString(
      const std::string& str, std::string& error) = 0;
};

} // namespace Mplane

#endif /* IDATAVARIANTSETTINGS_H_ */
