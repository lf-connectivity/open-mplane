/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeFreq.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DvTypeFreq.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string TYPESTR{"FREQ"};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeFreq::DvTypeFreq(const std::string& typeStr) : mFreq(0.0), mLimits() {}

//-------------------------------------------------------------------------------------------------------------
DvTypeFreq::~DvTypeFreq() {}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFreq::canHaveUnits() const {
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFreq::canSetValue(const std::string& valueStr) const {
  if (!strIsNumber(valueStr))
    return false;

  if (!strIsUnsigned(valueStr))
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFreq::canSetType(const std::string& typeStr) const {
  if (typeStr == TYPESTR)
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
void
DvTypeFreq::clear() {
  mFreq = 0.0;
  this->DvTypeBase::clear();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeFreq::getTypeStr() const {
  return TYPESTR;
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeFreq::getLimitsStr() const {
  return formatLimits(mLimits);
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeFreq::getLimitsMin() const {
  return mLimits.getMin();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeFreq::getLimitsMax() const {
  return mLimits.getMax();
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeFreq::getLimitsStep() const {
  return mLimits.getStep();
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type
DvTypeFreq::getType() const {
  return DataVariantType::Freq;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFreq::setLimits(const std::string& limitsStr) {
  mLimits.setUnits(getUnits());
  return mLimits.set(limitsStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFreq::setLimits(
    const std::string& minStr,
    const std::string& maxStr,
    const std::string& stepStr) {
  mLimits.setUnits(getUnits());
  return mLimits.set(minStr, maxStr, stepStr);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFreq::checkLimits(std::string& error) {
  // skip if not set
  if (!isSet())
    return true;

  return mLimits.check(mFreq, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFreq::setFreq(const Frequency& value) {
  mFreq = value;
  Frequency::Unit units(Frequency::str2unit(getUnits()));
  setStr(static_cast<IDvAccess::InterFloat>(mFreq.getDbl(units)));
  return true;
}

//-------------------------------------------------------------------------------------------------------------
void
DvTypeFreq::setUnits(const std::string& unitsStr) {
  this->super::setUnits(unitsStr);
  if (!isSet())
    return;

  // Value is set, so we need to update the string based on the changed units
  Frequency::Unit units(Frequency::str2unit(getUnits()));
  setStr(static_cast<IDvAccess::InterFloat>(mFreq.getDbl(units)));
}

//-------------------------------------------------------------------------------------------------------------
Frequency
DvTypeFreq::toFreq() const {
  return mFreq;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFreq::set(const std::string& value) {
  std::string valueStr(unitsFromStr(value));

  // Check valid value
  if (!strIsNumber(valueStr) || !strIsUnsigned(valueStr)) {
    // invalid setting
    clear();
    return false;
  }

  Frequency::Unit units(Frequency::str2unit(getUnits()));

  // Set value
  setStr(valueStr);
  if (strIsFloat(valueStr)) {
    mFreq = Frequency(atof(valueStr.c_str()), units);
    return true;
  }

  mFreq = Frequency(
      static_cast<unsigned long long>(atoll(valueStr.c_str())), units);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt
DvTypeFreq::toInterInt() const {
  Frequency::Unit units(Frequency::str2unit(getUnits()));
  return static_cast<IDvAccess::InterInt>(mFreq.getDbl(units));
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat
DvTypeFreq::toInterFloat() const {
  Frequency::Unit units(Frequency::str2unit(getUnits()));
  return static_cast<IDvAccess::InterFloat>(mFreq.getDbl(units));
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFreq::fromInterInt(const IDvAccess::InterInt& value) {
  Frequency::Unit units(Frequency::str2unit(getUnits()));
  mFreq = Frequency(static_cast<long long unsigned>(value), units);
  setStr(value);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeFreq::fromInterFloat(const IDvAccess::InterFloat& value) {
  Frequency::Unit units(Frequency::str2unit(getUnits()));
  mFreq = Frequency(static_cast<double>(value), units);
  setStr(value);
  return true;
}
