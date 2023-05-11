/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeUint.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "DvTypeUint.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string TYPESTR{"UINT"};
const std::string HEX_TYPESTR{"HEXUINT"};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeUint::DvTypeUint(const std::string& typeStr)
    : DvTypeBase(typeStr), mUint(0), mIsHex(false), mLimits() {}

//-------------------------------------------------------------------------------------------------------------
DvTypeUint::~DvTypeUint() {}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeUint::canHaveUnits() const {
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeUint::canSetValue(const std::string& valueStr) const {
  if (strIsHex(valueStr)) {
    return true;
  }

  if (!strIsUnsigned(valueStr)) {
    return false;
  }

  if (!strIsNumber(valueStr)) {
    return false;
  }

  if (strIsFloat(valueStr)) {
    return false;
  }

  if (strIsInt(valueStr)) {
    return true;
  }

  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeUint::canSetType(const std::string& typeStr) const {
  if (typeStr == TYPESTR)
    return true;

  if (typeStr == HEX_TYPESTR)
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
void
DvTypeUint::clear() {
  if (getInitialTypeStr() == HEX_TYPESTR) {
    mIsHex = true;
  } else {
    mIsHex = false;
  }

  mUint = 0;
  this->DvTypeBase::clear();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeUint::getTypeStr() const {
  return (mIsHex ? HEX_TYPESTR : TYPESTR);
}

//-------------------------------------------------------------------------------------------------------------
const bool
DvTypeUint::isHex() const {
  return mIsHex;
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeUint::getLimitsStr() const {
  return formatLimits(mLimits);
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeUint::getLimitsMin() const {
  return mLimits.getMin();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeUint::getLimitsMax() const {
  return mLimits.getMax();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeUint::getLimitsStep() const {
  return mLimits.getStep();
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type
DvTypeUint::getType() const {
  return DataVariantType::Uint;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeUint::setLimits(const std::string& limitsStr) {
  mLimits.setUnits(getUnits());
  return mLimits.set(limitsStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeUint::setLimits(
    const std::string& minStr,
    const std::string& maxStr,
    const std::string& stepStr) {
  mLimits.setUnits(getUnits());
  return mLimits.set(minStr, maxStr, stepStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeUint::checkLimits(std::string& error) {
  // skip if not set
  if (!isSet())
    return true;

  return mLimits.check(mUint, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeUint::set(const std::string& value) {
  std::string valueStr(unitsFromStr(value));

  // Check valid value
  if ((!strIsInt(valueStr) && !strIsHex(valueStr)) || strIsFloat(valueStr) ||
      !strIsUnsigned(valueStr)) {
    // invalid setting
    clear();
    return false;
  }

  // Set value
  mIsHex = false;
  if (strIsHex(valueStr)) {
    mIsHex = true;
    sscanf(&valueStr.c_str()[2], "%8X", &mUint);
  } else {
    mUint = static_cast<unsigned>(atoi(valueStr.c_str()));
  }

  setStr(valueStr);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
unsigned
DvTypeUint::toUint() const {
  return mUint;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeUint::setUint(unsigned value) {
  mUint = value;
  if (mIsHex) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::uppercase << mUint;
    setStr(oss.str());
  } else {
    std::ostringstream oss;
    oss << mUint;
    setStr(oss.str());
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt
DvTypeUint::toInterInt() const {
  return static_cast<IDvAccess::InterInt>(mUint);
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat
DvTypeUint::toInterFloat() const {
  return static_cast<IDvAccess::InterFloat>(mUint);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeUint::fromInterInt(const IDvAccess::InterInt& value) {
  return setUint(static_cast<unsigned>(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeUint::fromInterFloat(const IDvAccess::InterFloat& value) {
  return setUint(static_cast<unsigned>(value));
}
