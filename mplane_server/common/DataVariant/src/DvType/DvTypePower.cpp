/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypePower.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "DvTypePower.h"
#include "Maths.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string TYPESTR{"POWER"};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypePower::DvTypePower(const std::string& typeStr)
    : mPower(0.0f), mLimits() {}

//-------------------------------------------------------------------------------------------------------------
DvTypePower::~DvTypePower() {}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypePower::canHaveUnits() const {
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypePower::canSetValue(const std::string& valueStr) const {
  return strIsNumber(valueStr);

  //    if (!strIsNumber(valueStr))
  //        return false ;
  //
  //     return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypePower::canSetType(const std::string& typeStr) const {
  if (typeStr == TYPESTR)
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
void
DvTypePower::clear() {
  mPower = 0.0f;
  this->DvTypeBase::clear();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypePower::getTypeStr() const {
  return TYPESTR;
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypePower::getLimitsStr() const {
  return formatLimits(mLimits);
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypePower::getLimitsMin() const {
  return mLimits.getMin();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypePower::getLimitsMax() const {
  return mLimits.getMax();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypePower::getLimitsStep() const {
  return mLimits.getStep();
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type
DvTypePower::getType() const {
  return DataVariantType::Power;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypePower::setLimits(const std::string& limitsStr) {
  mLimits.setUnits(getUnits());
  return mLimits.set(limitsStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypePower::setLimits(
    const std::string& minStr,
    const std::string& maxStr,
    const std::string& stepStr) {
  mLimits.setUnits(getUnits());
  return mLimits.set(minStr, maxStr, stepStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypePower::checkLimits(std::string& error) {
  // skip if not set
  if (!isSet())
    return true;

  return mLimits.check(mPower, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypePower::setPower(const Power& value) {
  mPower = value;
  Power::Unit units(Power::str2unit(getUnits()));
  setStr(static_cast<IDvAccess::InterFloat>(mPower.get(units)));
  return true;
}

//-------------------------------------------------------------------------------------------------------------
void
DvTypePower::setUnits(const std::string& unitsStr) {
  this->super::setUnits(unitsStr);
  if (!isSet())
    return;

  // Value is set, so we need to update the string based on the changed units
  Power::Unit units(Power::str2unit(getUnits()));
  setStr(static_cast<IDvAccess::InterFloat>(mPower.get(units)));
}

//-------------------------------------------------------------------------------------------------------------
Power
DvTypePower::toPower() const {
  return mPower;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypePower::set(const std::string& value) {
  std::string valueStr(unitsFromStr(value));

  // Check valid value
  if (!strIsNumber(valueStr)) {
    // invalid setting
    clear();
    return false;
  }

  Power::Unit units(Power::str2unit(getUnits()));

  // Set value
  setStr(valueStr);
  if (strIsFloat(valueStr)) {
    //        mPower = Power(atof( valueStr.c_str() ), units) ;
    mPower = Power(Maths::str2float(valueStr), units);
    return true;
  }

  mPower = Power(static_cast<float>(atoll(valueStr.c_str())), units);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt
DvTypePower::toInterInt() const {
  Power::Unit units(Power::str2unit(getUnits()));
  return static_cast<IDvAccess::InterInt>(mPower.getInt(units));
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat
DvTypePower::toInterFloat() const {
  Power::Unit units(Power::str2unit(getUnits()));
  return static_cast<IDvAccess::InterFloat>(mPower.get(units));
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypePower::fromInterInt(const IDvAccess::InterInt& value) {
  Power::Unit units(Power::str2unit(getUnits()));
  mPower = Power(static_cast<float>(value), units);
  setStr(value);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypePower::fromInterFloat(const IDvAccess::InterFloat& value) {
  Power::Unit units(Power::str2unit(getUnits()));
  mPower = Power(static_cast<float>(value), units);
  setStr(value);
  return true;
}
