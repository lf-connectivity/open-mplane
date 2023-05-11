/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeFloat.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "DvTypeFloat.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string TYPESTR{"FLOAT"};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeFloat::DvTypeFloat(const std::string& typeStr)
    : DvTypeBase(typeStr), mFloat(0.0), mLimits() {}

//-------------------------------------------------------------------------------------------------------------
DvTypeFloat::~DvTypeFloat() {}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFloat::canHaveUnits() const {
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFloat::canSetValue(const std::string& valueStr) const {
  if (!strIsNumber(valueStr))
    return false;

  if (strIsFloat(valueStr))
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFloat::canSetType(const std::string& typeStr) const {
  if (typeStr == TYPESTR)
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
void
DvTypeFloat::clear() {
  mFloat = 0.0;
  this->DvTypeBase::clear();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeFloat::getTypeStr() const {
  return TYPESTR;
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeFloat::getLimitsStr() const {
  return formatLimits(mLimits);
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeFloat::getLimitsMin() const {
  return mLimits.getMin();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeFloat::getLimitsMax() const {
  return mLimits.getMax();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeFloat::getLimitsStep() const {
  return mLimits.getStep();
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type
DvTypeFloat::getType() const {
  return DataVariantType::Float;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFloat::setLimits(const std::string& limitsStr) {
  mLimits.setUnits(getUnits());
  return mLimits.set(limitsStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFloat::setLimits(
    const std::string& minStr,
    const std::string& maxStr,
    const std::string& stepStr) {
  mLimits.setUnits(getUnits());
  return mLimits.set(minStr, maxStr, stepStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFloat::checkLimits(std::string& error) {
  // skip if not set
  if (!isSet())
    return true;

  return mLimits.check(mFloat, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFloat::set(const std::string& value) {
  std::string valueStr(unitsFromStr(value));

  // Check valid value
  if (!strIsNumber(valueStr)) {
    // invalid setting
    clear();
    return false;
  }

  // Set value
  mFloat = atof(valueStr.c_str());
  setStr(valueStr);

  return true;
}

//-------------------------------------------------------------------------------------------------------------
float
DvTypeFloat::toFloat() const {
  return mFloat;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFloat::setFloat(float value) {
  mFloat = value;
  setStr(mFloat);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt
DvTypeFloat::toInterInt() const {
  return static_cast<IDvAccess::InterInt>(mFloat);
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat
DvTypeFloat::toInterFloat() const {
  return static_cast<IDvAccess::InterFloat>(mFloat);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFloat::fromInterInt(const IDvAccess::InterInt& value) {
  return setFloat(static_cast<float>(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFloat::fromInterFloat(const IDvAccess::InterFloat& value) {
  return setFloat(static_cast<float>(value));
}
