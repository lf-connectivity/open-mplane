/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeInt.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "DvTypeInt.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string INT_TYPESTR{"INT"};
const std::string HEXINT_TYPESTR{"HEXINT"};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeInt::DvTypeInt(const std::string& typeStr)
    : DvTypeBase(typeStr), mInt(0), mIsHex(false), mLimits() {
  if (typeStr == HEXINT_TYPESTR)
    mIsHex = true;
}

//-------------------------------------------------------------------------------------------------------------
DvTypeInt::~DvTypeInt() {}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeInt::canHaveUnits() const {
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeInt::canSetValue(const std::string& valueStr) const {
  if (strIsHex(valueStr))
    return true;

  if (!strIsNumber(valueStr))
    return false;

  if (strIsFloat(valueStr))
    return false;

  if (strIsInt(valueStr))
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeInt::canSetType(const std::string& typeStr) const {
  if (typeStr == INT_TYPESTR)
    return true;

  if (typeStr == HEXINT_TYPESTR)
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
void
DvTypeInt::clear() {
  if (getInitialTypeStr() == HEXINT_TYPESTR)
    mIsHex = true;
  else
    mIsHex = false;

  mInt = 0;
  this->DvTypeBase::clear();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeInt::getTypeStr() const {
  return (mIsHex ? HEXINT_TYPESTR : INT_TYPESTR);
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeInt::getLimitsStr() const {
  return formatLimits(mLimits);
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeInt::getLimitsMin() const {
  return mLimits.getMin();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeInt::getLimitsMax() const {
  return mLimits.getMax();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeInt::getLimitsStep() const {
  return mLimits.getStep();
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type
DvTypeInt::getType() const {
  return DataVariantType::Int;
}

//-------------------------------------------------------------------------------------------------------------
const bool
DvTypeInt::isHex() const {
  return mIsHex;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeInt::setLimits(const std::string& limitsStr) {
  mLimits.setUnits(getUnits());
  return mLimits.set(limitsStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeInt::setLimits(
    const std::string& minStr,
    const std::string& maxStr,
    const std::string& stepStr) {
  mLimits.setUnits(getUnits());
  return mLimits.set(minStr, maxStr, stepStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeInt::checkLimits(std::string& error) {
  // skip if not set
  if (!isSet())
    return true;

  return mLimits.check(mInt, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeInt::set(const std::string& value) {
  std::string valueStr(unitsFromStr(value));

  // Check valid value
  if ((!strIsInt(valueStr) && !strIsHex(valueStr)) || strIsFloat(valueStr)) {
    // invalid setting
    clear();
    return false;
  }

  // Set value
  mIsHex = false;
  if (strIsHex(valueStr)) {
    mIsHex = true;
    sscanf(&valueStr.c_str()[2], "%8X", &mInt);
  } else {
    mInt = atoi(valueStr.c_str());
  }

  setStr(valueStr);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
int
DvTypeInt::toInt() const {
  return mInt;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeInt::setInt(int value) {
  mInt = value;
  setIntStr();
  return true;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt
DvTypeInt::toInterInt() const {
  return static_cast<IDvAccess::InterInt>(mInt);
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat
DvTypeInt::toInterFloat() const {
  return static_cast<IDvAccess::InterFloat>(mInt);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeInt::fromInterInt(const IDvAccess::InterInt& value) {
  return setInt(static_cast<int>(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeInt::fromInterFloat(const IDvAccess::InterFloat& value) {
  return setInt(static_cast<int>(value));
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
DvTypeInt::setIntStr() {
  if (mIsHex) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::uppercase << mInt;
    setStr(oss.str());
  } else {
    setStr(mInt);
  }
}
