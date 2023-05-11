/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantSettings.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DataVariant/DataVariantSettings.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class DataVariantSettingsInstance : public DataVariantSettings {
 public:
  DataVariantSettingsInstance() : DataVariantSettings() {}
  virtual ~DataVariantSettingsInstance() {}
};
std::shared_ptr<IDataVariantSettings>
IDataVariantSettings::getInstance() {
  static std::shared_ptr<IDataVariantSettings> instance(
      std::make_shared<DataVariantSettingsInstance>());
  return instance;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantSettings::~DataVariantSettings() {}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantSettings::clearSettings() {
  mSettings.clear();
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantSettings::registerSettings(
    const std::map<std::string, std::string>& settings) {
  mSettings = settings;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantSettings::setSetting(
    const std::string& name, const std::string& value) {
  if (!isSetting(name))
    return false;

  mSettings[name] = value;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantSettings::expandString(const std::string& str, std::string& error) {
  error = "";
  if (mSettings.empty())
    return str;

  // Find any variables of the form: ${...}
  std::size_t startPos(str.find("${"));
  if (startPos == std::string::npos)
    return str;

  // Need to process the variables
  std::string expanded;
  std::size_t offset{0};

  do {
    // end of variable
    std::size_t endPos(str.find("}", startPos));
    if (endPos == std::string::npos) {
      error = "Invalid variable definition, no closing }";
      return "";
    }

    // add any chars between previous and new start
    expanded.append(str.substr(offset, startPos));

    // look up variable value
    std::string var(str.substr(startPos + 2, endPos - startPos - 2));
    if (mSettings.find(var) == mSettings.end()) {
      error = "Invalid variable '" + var + "'";
      return "";
    }

    // expand the variable
    expanded.append(mSettings[var]);

    // prepare for next iteration
    offset = endPos + 1;
    startPos = str.find("${", offset);

  } while (startPos != std::string::npos);

  // append any remaining
  expanded.append(str.substr(offset));

  return expanded;
}

//-------------------------------------------------------------------------------------------------------------
bool
Mplane::DataVariantSettings::isSetting(const std::string& name) const {
  auto entry(mSettings.find(name));
  if (entry == mSettings.end())
    return false;

  return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantSettings::DataVariantSettings() {}
