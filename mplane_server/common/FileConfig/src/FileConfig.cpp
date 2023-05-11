/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileConfig.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Path.h"

#include "FileConfig.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FileConfig::FileConfig(const std::map<std::string, std::string> defaults)
    : FileConfigBase(defaults) {}

//-------------------------------------------------------------------------------------------------------------
FileConfig::FileConfig(
    const std::string& path, const std::map<std::string, std::string> defaults)
    : FileConfigBase(path, defaults) {
  _setPath(path);
}

//-------------------------------------------------------------------------------------------------------------
FileConfig::FileConfig(const FileConfig& rhs) : FileConfigBase(rhs) {}

//-------------------------------------------------------------------------------------------------------------
FileConfig&
FileConfig::operator=(const FileConfig& rhs) {
  if (&rhs == this)
    return *this;

  this->FileConfigBase::operator=(rhs);
  return *this;
}

//-------------------------------------------------------------------------------------------------------------
FileConfig::~FileConfig() {}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfig::setPath(const std::string& path) {
  return _setPath(path);
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfig::filename() const {
  return this->FileConfigBase::filename();
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfig::isValid() const {
  return this->FileConfigBase::isValid();
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfig::value(const std::string& varname) const {
  return this->FileConfigBase::value(varname);
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfig::isVariable(const std::string& varname) const {
  return this->FileConfigBase::isVariable(varname);
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfig::value(
    const std::string& section, const std::string& varname) const {
  return this->FileConfigBase::value(section, varname);
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfig::isVariable(
    const std::string& section, const std::string& varname) const {
  return this->FileConfigBase::isVariable(section, varname);
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfig::isSection(const std::string& section) const {
  return this->FileConfigBase::isSection(section);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>
FileConfig::sections() const {
  return this->FileConfigBase::sections();
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfig::error() {
  return this->FileConfigBase::error();
}

//-------------------------------------------------------------------------------------------------------------
void
FileConfig::show() const {
  this->FileConfigBase::show();
}

//-------------------------------------------------------------------------------------------------------------
double
FileConfig::doubleValue(const std::string& varname) const {
  return this->FileConfigBase::doubleValue(varname);
}

//-------------------------------------------------------------------------------------------------------------
double
FileConfig::doubleValue(
    const std::string& section, const std::string& varname) const {
  return this->FileConfigBase::doubleValue(section, varname);
}

//-------------------------------------------------------------------------------------------------------------
int
FileConfig::intValue(const std::string& varname) const {
  return this->FileConfigBase::intValue(varname);
}

//-------------------------------------------------------------------------------------------------------------
int
FileConfig::intValue(
    const std::string& section, const std::string& varname) const {
  return this->FileConfigBase::intValue(section, varname);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
FileConfig::_setPath(const std::string& path) {
  if (!this->FileConfigBase::setPath(path))
    return false;

  // Does file exist
  if (!Path::exists(filename())) {
    return setError("No such file");
  }

  return _read();
}
