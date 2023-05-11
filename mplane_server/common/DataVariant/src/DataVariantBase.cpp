/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariant.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>

#include "stringfunc.hpp"

#include "DvTypeBase.h"
#include "DvTypeFactory.h"

#include "DataVariant/DataVariantBase.h"
#include "Tokeniser.h"

using namespace Mplane;

//=============================================================================================================
// DataVariantBase PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantBase::DataVariantBase()
    : DataVariantTypes(mDv),
      mName(""),
      mLowerName(""),
      mDv(DvTypeFactory::factory(DataVariantType::None)),
      mIsOptional(false),
      mDefault("")

{}

//-------------------------------------------------------------------------------------------------------------
DataVariantBase::DataVariantBase(const std::string& name)
    : DataVariantTypes(mDv),
      mName(""),
      mLowerName(""),
      mDv(DvTypeFactory::factory(DataVariantType::None)),
      mIsOptional(false),
      mDefault("") {
  std::string::size_type pos = name.find("=");

  if (pos != std::string::npos) {
    mName = name.substr(0, pos);
    pos++; // skip the equals
    std::string value = name.substr(pos);
    set(value);
  } else {
    mName = name;
  }
  mLowerName = toLower(mName);
}

//-------------------------------------------------------------------------------------------------------------
DataVariantBase::DataVariantBase(
    const std::string& name, const std::string& type)
    : DataVariantTypes(mDv),
      mName(name),
      mLowerName(toLower(name)),
      mDv(DvTypeFactory::factory(DataVariantType::None)),
      mIsOptional(false),
      mDefault("") {
  setType(type);
}

//-------------------------------------------------------------------------------------------------------------
DataVariantBase::DataVariantBase(
    const DataVariantType::Type& type,
    const std::string& name,
    const std::string& value)
    : DataVariantTypes(mDv),
      mName(name),
      mLowerName(toLower(name)),
      mDv(DvTypeFactory::factory(type)),
      mIsOptional(false),
      mDefault("") {
  // sanity check - can't allow for enumerated types created using this method
  // since there is no means of setting the enumerations
  if (type == DataVariantType::Enum) {
    throw std::runtime_error(
        "Attempted to create ENUM without specifying enumerations");
  }

  // set the value
  if (!value.empty()) {
    set(value);
  }
}

//-------------------------------------------------------------------------------------------------------------
DataVariantBase::DataVariantBase(const DataVariantBase& value)
    : DataVariantTypes(mDv),
      mName(value.mName),
      mLowerName(value.mLowerName),
      mDv(DvTypeFactory::copy(value.mDv)),
      mIsOptional(value.mIsOptional),
      mDefault(value.mDefault) {
  // std::cerr << "DataVariantBase copy construct - value " << value.mName << "
  // value.mDv " << value.mDv->getTypeStr() << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
DataVariantBase::~DataVariantBase() {}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantBase::setType(const std::string& type) {
  // This needs to be in the form:
  //
  // TYPE [(UNITS)]
  //
  Tokeniser t(type, " ");
  std::vector<std::string> tokens(t.getTokens());

  std::string typeStr(tokens[0]);
  std::string units;

  // Get units if specified
  if (tokens.size() >= 2) {
    units = tokens[1];

    // strip () from units
    if ((units.at(0) == '(') && (units.at(units.size() - 1) == ')'))
      units = units.substr(1, units.size() - 2);
  }

  mDv = DvTypeFactory::factory(typeStr);

  // add units
  if (!units.empty())
    mDv->setUnits(units);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantBase::set(const DataVariantBase& rhs) {
  operator=(rhs);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantBase::set(const DataVariantBase* rhs) {
  operator=(*rhs);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantBase::set(const std::shared_ptr<DataVariantBase>& rhs) {
  operator=(*rhs);
}

//-------------------------------------------------------------------------------------------------------------
DataVariantBase&
DataVariantBase::operator=(const DataVariantBase& value) {
  mName = value.mName;
  mLowerName = value.mLowerName;
  mDv = DvTypeFactory::copy(value.mDv);
  mIsOptional = value.mIsOptional;

  return *this;
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DataVariantBase::getTypeStr() const {
  return mDv->getTypeStr();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DataVariantBase::getLimitsStr() const {
  return mDv->getLimitsStr();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DataVariantBase::getLimitsMin() const {
  return mDv->getLimitsMin();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DataVariantBase::getLimitsMax() const {
  return mDv->getLimitsMax();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DataVariantBase::getLimitsStep() const {
  return mDv->getLimitsStep();
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type
DataVariantBase::getType() const {
  return mDv->getType();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DataVariantBase::getUnits() const {
  return mDv->getUnits();
}

//-------------------------------------------------------------------------------------------------------------
const bool
DataVariantBase::isHex() const {
  return mDv->isHex();
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantBase::set(const std::string& value) {
  // we could be initially setting a float or integer using a string
  // so we need to do some checks.

  // Is type already set?
  bool typeSet(mDv->getType() != DataVariantType::None);

  // Start by determining the type
  if (!typeSet) {
    std::vector<std::shared_ptr<IDvType>> types(DvTypeFactory::getTypes());
    for (auto dv : types) {
      if (!dv->canSetValue(value))
        continue;

      // create a new instance of this type
      mDv = DvTypeFactory::factory(dv->getType());
      break;
    }
  }

  // Set value from the string
  mDv->set(value);
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DataVariantBase::getName() const {
  return mName;
}

//-------------------------------------------------------------------------------------------------------------
const std::string
Mplane::DataVariantBase::getLowerName() const {
  return mLowerName;
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantBase::toString() const {
  return mDv->toString();
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantBase::isSet() const {
  return mDv->isSet();
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantBase::clear() {
  mDv->clear();
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantBase::reset() {
  mName = "";
  mLowerName = "";
  mIsOptional = false;

  mDv = DvTypeFactory::factory(DataVariantType::None);

  clear();
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantBase::getValue() const {
  return mDv->getValue();
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantBase::getValueOptional() const {
  std::string value(getValue());

  // Don't show anything for optional empty strings
  if (isEmptyOptionalString())
    return "";

  return value;
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantBase::getNameValuePair(const std::string& name) const {
  std::string nameStr(name);
  if (nameStr.empty())
    nameStr = mName;

  std::string valuepair = nameStr + "=" + getValue();
  return valuepair;
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantBase::getNameValuePairOptional(const std::string& name) const {
  // Don't show anything for optional empty strings
  if (isEmptyOptionalString())
    return "";

  std::string nameStr(name);
  if (nameStr.empty())
    nameStr = mName;

  std::string value(getValueOptional());
  std::string valuepair = nameStr + "=" + value;
  return valuepair;
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantBase::setOptional(bool optional) {
  mIsOptional = optional;
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantBase::setDefault(const std::string& value) {
  mDefault = value;
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantBase::getDefault() const {
  return mDefault;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantBase::isOptional() const {
  return mIsOptional;
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantBase::setUnits(const std::string& units) {
  mDv->setUnits(units);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantBase::setLimits(const std::string& limitsStr) {
  return mDv->setLimits(limitsStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantBase::setLimits(
    const std::string& minStr,
    const std::string& maxStr,
    const std::string& stepStr) {
  return mDv->setLimits(minStr, maxStr, stepStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantBase::checkLimits(std::string& error) {
  std::string errstr;
  if (!mDv->checkLimits(errstr)) {
    error = mName + " " + errstr;
    return false;
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantBase::checkLimits() {
  return mDv->checkLimits();
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantBase::isEmptyOptionalString() const {
  // Is this an optional string that is empty?
  if ((mDv->getType() == DataVariantType::String) && mIsOptional &&
      mDv->toString().empty())
    return true;

  return false;
}
