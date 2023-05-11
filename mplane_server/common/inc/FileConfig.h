/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileConfig.h
 * \brief     Read a config file
 *
 *
 * \details   Read a config file of the form:
 *
 * vendor=@VENDOR_CODE@
 * code=@PRODUCT_CODE@
 * name=@BUILD_BOARD@-@BUILD_CUSTOMER@-@BUILD_APPLICATION@-@BUILD_VERSION@#@BUILD_NUMBER@
 * build-Id=1
 *
 * [os]
 * fileName=@OS_PKG_FILENAME@
 * fileVersion=@OS_PKG_VERSION@
 * path=@OS_PKG_FILENAME@
 * checksum=@osMd5@
 * status=valid
 *
 * [app]
 * fileName=@APP_PKG_FILENAME@
 * fileVersion=@BUILD_VERSION@
 * path=@APP_PKG_FILENAME@
 * checksum=@appMd5@
 * status=valid
 *
 *         In other words, sets of variable=value pairs either at the top
 * of the file (i.e. "global") or contained under a section started by a
 * "[section]" section label.
 *
 *         Variables can be retrieved either from the global namespace or
 * from a section namespace.
 *
 *         The global variables are available inside all of the sections.
 *
 */

#ifndef INC_FILECONFIG_H_
#define INC_FILECONFIG_H_

#include <map>
#include <string>
#include <vector>

#include "FileConfigBase.h"

namespace Mplane {

/*!
 * \class  FileConfig
 * \brief
 * \details
 *
 */
class FileConfig : public FileConfigBase {
 public:
  FileConfig(
      const std::map<std::string, std::string> defaults =
          std::map<std::string, std::string>{});
  FileConfig(
      const std::string& path,
      const std::map<std::string, std::string> defaults =
          std::map<std::string, std::string>{});
  virtual ~FileConfig();

  /**
   * Copy constructor
   */
  FileConfig(const FileConfig& rhs);

  /**
   * Assignment operator
   */
  FileConfig& operator=(const FileConfig& rhs);

  /**
   * Set a file path and read the config file
   * @return TRUE if file read ok; FALSE otherwise (use error() method to get
   * error string)
   */
  virtual bool setPath(const std::string& path) override;

  /**
   * get current config file path
   */
  virtual std::string filename() const override;

  /**
   * Is the current config valid?
   */
  virtual bool isValid() const override;

  /**
   * Get the value of the global variable (or a section variable if varname is a
   * path)
   * @return value string if variable is preset; empty string otherwise
   */
  virtual std::string value(const std::string& varname) const override;

  /**
   * is the global variable (or a section variable if varname is a path)
   * available?
   */
  virtual bool isVariable(const std::string& varname) const override;

  /**
   * Get the value of the section variable
   * @return value string if variable is preset; empty string otherwise
   */
  virtual std::string value(
      const std::string& section, const std::string& varname) const override;

  /**
   * is the section variable available?
   */
  virtual bool isVariable(
      const std::string& section, const std::string& varname) const override;

  /**
   * Is this section name valid?
   */
  virtual bool isSection(const std::string& section) const override;

  /**
   * Get the list of section names
   */
  virtual std::vector<std::string> sections() const override;

  /**
   * Get any error and clear it
   */
  virtual std::string error() override;

  /**
   * Debug
   */
  virtual void show() const override;

  /**
   * Get the value of the global variable (or a section variable if varname is a
   * path) as a double
   * @return value if variable is preset; 0.0 otherwise
   */
  virtual double doubleValue(const std::string& varname) const override;

  /**
   * Get the value of the section variable as a double
   * @return value if variable is preset; 0.0 otherwise
   */
  virtual double doubleValue(
      const std::string& section, const std::string& varname) const override;

  /**
   * Get the value of the global variable (or a section variable if varname is a
   * path) as an int
   * @return value if variable is preset; 0 otherwise
   */
  virtual int intValue(const std::string& varname) const override;

  /**
   * Get the value of the section variable as an int
   * @return value if variable is preset; 0 otherwise
   */
  virtual int intValue(
      const std::string& section, const std::string& varname) const override;

 protected:
  bool _setPath(const std::string& path);
};

} // namespace Mplane

#endif /* INC_FILECONFIG_H_ */
