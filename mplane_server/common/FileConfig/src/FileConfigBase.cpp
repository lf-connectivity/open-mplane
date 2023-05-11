/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileConfigBaseBase.cpp
 * \brief     Base class for FileConfigBase
 *
 *
 * \details   Base class for FileConfigBase
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <fstream>

#include "Path.h"
#include "stringfunc.hpp"

#include "FileConfigBase.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::string WHITESPACE(" \t");

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FileConfigBase::FileConfigBase(
    const std::map<std::string, std::string> defaults)
    : mPath(""),
      mValid(false),
      mError(""),
      mGlobals(),
      mSections(),
      mDefaults(defaults) {
  applyDefaults();
}

//-------------------------------------------------------------------------------------------------------------
FileConfigBase::FileConfigBase(
    const std::string& path, const std::map<std::string, std::string> defaults)
    : FileConfigBase(defaults) {
  setPath(path);
}

//-------------------------------------------------------------------------------------------------------------
FileConfigBase::FileConfigBase(const FileConfigBase& rhs)
    : mPath(rhs.mPath),
      mValid(rhs.mValid),
      mError(rhs.mError),
      mGlobals(rhs.mGlobals),
      mSections(rhs.mSections),
      mDefaults(rhs.mDefaults) {}

//-------------------------------------------------------------------------------------------------------------
FileConfigBase&
FileConfigBase::operator=(const FileConfigBase& rhs) {
  if (&rhs == this)
    return *this;

  mPath = rhs.mPath;
  mValid = rhs.mValid;
  mError = rhs.mError;
  mGlobals = rhs.mGlobals;
  mSections = rhs.mSections;
  mDefaults = rhs.mDefaults;
  return *this;
}

//-------------------------------------------------------------------------------------------------------------
FileConfigBase::~FileConfigBase() {}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::clean() {
  if (mDefaults.empty())
    return false;

  // clean out globals first
  for (auto entry : mGlobals) {
    if (mDefaults.find(entry.first) != mDefaults.end())
      continue;

    // variable is not in defaults so remove it
    mGlobals.erase(entry.first);
  }

  // clean out sections
  for (auto sect : mSections) {
    for (auto entry : sect.second) {
      if (mDefaults.find(toPath(sect.first, entry.first)) != mDefaults.end())
        continue;

      // variable is not in defaults so remove it
      mSections[sect.first].erase(entry.first);
    }

    // Check this section still has some contents
    if (mSections[sect.first].empty())
      mSections.erase(sect.first);
  }

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::clear() {
  mGlobals.clear();
  mSections.clear();
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::isEqual(const FileConfigBase& rhs) const {
  if (values() != rhs.values())
    return false;

  // also check the sections to see if there are any empty ones
  if (sections().size() != rhs.sections().size())
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::isEqual(std::shared_ptr<FileConfigBase> rhs) const {
  return isEqual(*rhs);
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::setPath(const std::string& path) {
  // Clear any previous settings
  mValid = false;
  mPath = path;
  mError.clear();
  applyDefaults();

  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfigBase::filename() const {
  return mPath;
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::isValid() const {
  return mValid;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::pair<std::string, std::string>>
FileConfigBase::values() const {
  std::vector<std::pair<std::string, std::string>> list;

  for (auto entry : mGlobals)
    list.push_back(std::make_pair(entry.first, entry.second));

  for (auto sect : mSections) {
    for (auto entry : sect.second) {
      list.push_back(
          std::make_pair(toPath(sect.first, entry.first), entry.second));
    }
  }

  return list;
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfigBase::value(const std::string& varname) const {
  bool found(false);
  return find(varname, found);
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::isVariable(const std::string& varname) const {
  bool found(false);
  find(varname, found);
  return found;
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfigBase::value(
    const std::string& section, const std::string& varname) const {
  bool found(false);
  return find(section, varname, found);
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::isVariable(
    const std::string& section, const std::string& varname) const {
  bool found(false);
  find(section, varname, found);
  return found;
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::isSection(const std::string& section) const {
  if (mSections.find(section) == mSections.end())
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>
FileConfigBase::sections() const {
  std::vector<std::string> list;
  for (auto entry : mSections)
    list.push_back(entry.first);
  return list;
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfigBase::error() {
  std::string err;
  std::swap(mError, err);
  return err;
}

//-------------------------------------------------------------------------------------------------------------
void
FileConfigBase::show() const {
  std::cerr << "-- CONFIG --" << std::endl;
  for (auto entry : mGlobals)
    std::cerr << entry.first << " = " << entry.second << std::endl;

  for (auto sect : mSections) {
    std::cerr << std::endl;
    std::cerr << "[" << sect.first << "]" << std::endl;
    for (auto entry : sect.second)
      std::cerr << entry.first << " = " << entry.second << std::endl;
  }
  std::cerr << "------------" << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
double
FileConfigBase::doubleValue(const std::string& varname) const {
  bool found(false);
  std::string value(find(varname, found));
  if (!found)
    return 0.0;

  return strtod(value.c_str(), nullptr);
}

//-------------------------------------------------------------------------------------------------------------
double
FileConfigBase::doubleValue(
    const std::string& section, const std::string& varname) const {
  bool found(false);
  std::string value(find(section, varname, found));
  if (!found)
    return 0.0;

  return strtod(value.c_str(), nullptr);
}

//-------------------------------------------------------------------------------------------------------------
int
FileConfigBase::intValue(const std::string& varname) const {
  bool found(false);
  std::string value(find(varname, found));
  if (!found)
    return 0.0;

  return (int)strtol(value.c_str(), nullptr, 0);
}

//-------------------------------------------------------------------------------------------------------------
int
FileConfigBase::intValue(
    const std::string& section, const std::string& varname) const {
  bool found(false);
  std::string value(find(section, varname, found));
  if (!found)
    return 0.0;

  return (int)strtol(value.c_str(), nullptr, 0);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::setError(const std::string& error) {
  if (!mError.empty())
    mError += "\n";
  mError += error;

  // always return false
  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_read() {
  std::ifstream in;
  in.open(mPath.c_str());
  if (!in.is_open()) {
    setError("Unable to read control file");
    return false;
  }

  std::map<std::string, std::string>* storep(&mGlobals);
  std::string section;
  std::string line;
  while (in.good()) {
    // get the line text string
    std::getline(in, line);

    // skip empty string
    line = trim(line, WHITESPACE);
    if (line.empty())
      continue;

    // Skip comments (#) - comment '#' must be start of line
    if (line[0] == '#')
      continue;

    // check for section:
    // [section]
    if ((line.size() > 3) && (line[0] == '[') &&
        (line[line.size() - 1] == ']')) {
      section = line.substr(1, line.size() - 2);
      if (toUpper(section) == "GLOBAL")
        section.clear();

      storep = &mGlobals;
      if (!section.empty()) {
        if (mSections.find(section) == mSections.end())
          mSections[section] = std::map<std::string, std::string>();

        storep = &mSections[section];
      }
      continue;
    }

    // get any variables
    std::size_t pos(line.find("="));
    if (pos == std::string::npos)
      continue;

    std::string var(trim(line.substr(0, pos), WHITESPACE));
    std::string value(trim(line.substr(pos + 1), WHITESPACE));
    (*storep)[var] = value;
  }
  in.close();

  mValid = true;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfigBase::find(const std::string& varname, bool& found) const {
  found = false;

  std::string section;
  std::string sectionVarname;
  if (nameIsPath(varname, section, sectionVarname))
    return find(section, sectionVarname, found);

  if (mGlobals.find(varname) == mGlobals.end())
    return "";

  found = true;
  return mGlobals.at(varname);
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfigBase::find(
    const std::string& section, const std::string& varname, bool& found) const {
  found = false;

  if (mSections.find(section) == mSections.end())
    return "";

  if (mSections.at(section).find(varname) == mSections.at(section).end()) {
    // not in this section so try global area
    return find(varname, found);
  }

  found = true;
  return mSections.at(section).at(varname);
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::nameIsPath(
    const std::string& varname,
    std::string& section,
    std::string& sectionVarname) const {
  std::size_t pos(varname.find('/'));
  if (pos == std::string::npos)
    return false;

  section = varname.substr(0, pos);
  sectionVarname = varname.substr(pos + 1);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string
FileConfigBase::toPath(
    const std::string& section, const std::string& varname) const {
  return section + "/" + varname;
}

//-------------------------------------------------------------------------------------------------------------
void
FileConfigBase::applyDefaults() {
  mGlobals.clear();
  mSections.clear();

  // handle defaults
  for (auto entry : mDefaults) {
    _setValue(entry.first, entry.second);

    // setting any default makes the config valid
    mValid = true;
  }
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_modifyValue(
    const std::string& varname, const std::string& value) {
  if (!isVariable(varname))
    return false;

  return _setValue(varname, value);
  std::string section;
  std::string sectionVarname;
  if (nameIsPath(varname, section, sectionVarname))
    return _modifyValue(section, sectionVarname, value);

  mGlobals[varname] = value;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_modifyValue(
    const std::string& section,
    const std::string& varname,
    const std::string& value) {
  if (!isVariable(section, varname))
    return false;

  mSections[section][varname] = value;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_modifyValue(const std::string& varname, double value) {
  return _modifyValue(varname, std::to_string(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_modifyValue(
    const std::string& section, const std::string& varname, double value) {
  return _modifyValue(section, varname, std::to_string(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_modifyValue(const std::string& varname, int value) {
  return _modifyValue(varname, std::to_string(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_modifyValue(
    const std::string& section, const std::string& varname, int value) {
  return _modifyValue(section, varname, std::to_string(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_setValue(
    const std::string& varname, const std::string& value) {
  std::string section;
  std::string sectionVarname;
  if (nameIsPath(varname, section, sectionVarname))
    return _setValue(section, sectionVarname, value);

  mGlobals[varname] = value;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_setValue(
    const std::string& section,
    const std::string& varname,
    const std::string& value) {
  if (mSections.find(section) == mSections.end())
    mSections[section] = std::map<std::string, std::string>();

  mSections[section][varname] = value;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_setValue(const std::string& varname, double value) {
  return _setValue(varname, std::to_string(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_setValue(
    const std::string& section, const std::string& varname, double value) {
  return _setValue(section, varname, std::to_string(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_setValue(const std::string& varname, int value) {
  return _setValue(varname, std::to_string(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_setValue(
    const std::string& section, const std::string& varname, int value) {
  return _setValue(section, varname, std::to_string(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
FileConfigBase::_save() {
  // ensure directory is created
  Path::mkpath(Path::dir(mPath));

  // open file for writing
  std::ofstream file(mPath);
  if (!file.is_open())
    return setError("Unable to write to " + mPath);

  for (auto entry : mGlobals) {
    file << entry.first << " = " << entry.second << std::endl;
  }

  for (auto sect : mSections) {
    file << std::endl;
    file << "[" << sect.first << "]" << std::endl;
    for (auto entry : sect.second) {
      file << entry.first << " = " << entry.second << std::endl;
    }
  }

  file.close();

  return true;
}
