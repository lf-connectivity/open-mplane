/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Power.cpp
 * \brief     Implementation of the Power class
 *
 *
 * \details   This file contains the implementation of the common datatype
 *            Power class.
 *
 */

#include "Power.h"
#include "Maths.h"
#include "stringfunc.hpp"
#include <cmath>
#include <map>

using namespace Mplane;

namespace {
// Translate the units into conversion factors
const float
getUnitFactor(Power::Unit unit) {
  static const std::map<Power::Unit, float> UNIT_FACTOR{
      {Power::dBm, 1.0},
      {Power::dBFS, 1.0},
      {Power::dB, 1.0},
      {Power::TdBm, 10.0},
      {Power::HdBm, 100.0},
      {Power::KdBm, 1000.0},
      {Power::mW, 1.0},
      {Power::W, 1000.0},
  };
  return UNIT_FACTOR.at(unit);
}
} // namespace

static bool unitsInWatts(Power::Unit unit);
static bool
unitsInWatts(Power::Unit unit) {
  switch (unit) {
    case Power::mW:
    case Power::W:
      return true;

    case Power::dBm:
    case Power::dB:
    case Power::dBFS:
    case Power::TdBm:
    case Power::HdBm:
    case Power::KdBm:
    default:
      return false;
  }
}

const char*
Mplane::Power::unit2Str(Power::Unit unit) {
  switch (unit) {
    case dBm:
      return "dBm";
    case dB:
      return "dB";
    case dBFS:
      return "dBFS";
    case TdBm:
      return "TdBm";
    case HdBm:
      return "HdBm";
    case KdBm:
      return "KdBm";
    case mW:
      return "mW";
    case W:
      return "W";
    default:
      return "unknown";
  }
}

Power::Unit
Power::str2unit(const std::string& units) {
  std::string lowerUnits(toLower(units));
  if (lowerUnits == "dbm") {
    return dBm;
  } else if (lowerUnits == "db") {
    return dB;
  } else if (lowerUnits == "dbfs") {
    return dBFS;
  } else if (lowerUnits == "mw") {
    return mW;
  } else if (lowerUnits == "w") {
    return W;
  } else if (lowerUnits == "tdbm") {
    return TdBm;
  } else if (lowerUnits == "hdbm") {
    return HdBm;
  } else if (lowerUnits == "kdbm") {
    return KdBm;
  } else {
    return dBm;
  }
}

Mplane::Power::Power()
    : mPower_dBm(0.0), mPower_watts(0.0), mWattsSet(false) {
  setPowerWatts();
}

Mplane::Power::Power(float power, Power::Unit unit)
    : mPower_dBm(0.0), mPower_watts(0.0), mWattsSet(false) {
  set(power, unit);
}

void
Mplane::Power::set(float power, Power::Unit unit) {
  // Special optimisation for the default setting case
  if (unit == dBm) {
    set(power);
    return;
  }

  if (unitsInWatts(unit)) {
    // Watts
    mPower_watts = power * getUnitFactor(unit) / getUnitFactor(Power::W);
    mPower_dBm = convertWattsTodBm(mPower_watts);
  } else {
    // dBm
    mPower_dBm = power / getUnitFactor(unit);
    setPowerWatts();
  }
  mWattsSet = true;
}

void
Mplane::Power::set(float power) {
  // dBm
  mPower_dBm = power;
  mWattsSet = false;
}

void
Mplane::Power::set(const std::string& power, Power::Unit unit) {
  float fPower = Maths::str2float(power);
  set(fPower, unit);
}

void
Mplane::Power::setWatts(float power) {
  mPower_watts = power;
  mPower_dBm = convertWattsTodBm(mPower_watts);
  mWattsSet = true;
}

float
Mplane::Power::get(Power::Unit unit) const {
  if (unitsInWatts(unit)) {
    if (!mWattsSet)
      setPowerWatts();

    // Watts
    return mPower_watts * getUnitFactor(Power::W) / getUnitFactor(unit);
  } else {
    // dBm
    return mPower_dBm * getUnitFactor(unit);
  }
}

float
Mplane::Power::getWatts() const {
  if (!mWattsSet)
    setPowerWatts();

  return mPower_watts;
}

int
Mplane::Power::getInt(Power::Unit unit) const {
  double dscaledPower = (double)get(unit);
  dscaledPower =
      (dscaledPower - floor(dscaledPower) < 0.5 ? floor(dscaledPower)
                                                : ceil(dscaledPower));

  int scaledPower = (int)dscaledPower;

  return scaledPower;
}

Power&
Mplane::Power::operator=(const Power& rhs) {
  mPower_dBm = rhs.mPower_dBm;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator=(const float power) {
  mPower_dBm = power;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator=(const int power) {
  mPower_dBm = (float)power;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator+(const Power& rhs) const {
  return Power(mPower_dBm + rhs.mPower_dBm);
}

Power
Mplane::Power::operator+(const float power) const {
  return Power(mPower_dBm + power);
}

Power
Mplane::Power::operator+(const int power) const {
  return Power(mPower_dBm + (float)power);
}

Power
Mplane::Power::operator+=(const Power& rhs) {
  mPower_dBm += rhs.mPower_dBm;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator+=(const float power) {
  mPower_dBm += power;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator+=(const int power) {
  mPower_dBm += (float)power;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator*(const Power& rhs) const {
  return Power(mPower_dBm * rhs.mPower_dBm);
}

Power
Mplane::Power::operator*(const float power) const {
  return Power(mPower_dBm * power);
}

Power
Mplane::Power::operator*(const int power) const {
  return Power(mPower_dBm * (float)power);
}

Power
Mplane::Power::operator*=(const Power& rhs) {
  mPower_dBm *= rhs.mPower_dBm;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator*=(const float power) {
  mPower_dBm *= power;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator*=(const int power) {
  mPower_dBm *= (float)power;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator/(const Power& rhs) const {
  return Power(mPower_dBm / rhs.mPower_dBm);
}

Power
Mplane::Power::operator/(const float power) const {
  return Power(mPower_dBm / power);
}

Power
Mplane::Power::operator/(const int power) const {
  return Power(mPower_dBm / (float)power);
}

Power
Mplane::Power::operator/=(const Power& rhs) {
  mPower_dBm /= rhs.mPower_dBm;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator/=(const float power) {
  mPower_dBm /= power;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator/=(const int power) {
  mPower_dBm /= (float)power;
  setPowerWatts();
  return *this;
}

Power
Mplane::Power::operator-(const Power& rhs) const {
  return Power(mPower_dBm - rhs.mPower_dBm);
}

Power
Mplane::Power::operator-(const int power) const {
  return Power(mPower_dBm - (float)power);
}

Power
Mplane::Power::operator-(const float power) const {
  return Power(mPower_dBm - power);
}

Power
Mplane::Power::operator-=(const Power& rhs) {
  mPower_dBm -= rhs.mPower_dBm;
  return *this;
}

Power
Mplane::Power::operator-=(const float power) {
  mPower_dBm -= power;
  return *this;
}

Power
Mplane::Power::operator-=(const int power) {
  mPower_dBm -= (float)power;
  return *this;
}

float
Mplane::Power::convertdBmToWatts(float powerdBm) const {
  return (float)(exp10(powerdBm / 10) / 1000);
}

float
Mplane::Power::convertWattsTodBm(float powerWatts) const {
  return (float)(10 * log10(1000 * powerWatts));
}

bool
Mplane::Power::operator==(const Power& rhs) const {
  static const float POWER_RESOLUTION = 0.001;

  if (std::abs(mPower_dBm - rhs.mPower_dBm) < POWER_RESOLUTION)
    return true;
  return false;
}

bool
Mplane::Power::operator<(const Power& rhs) const {
  return mPower_dBm < rhs.mPower_dBm;
}

void
Mplane::Power::setPowerWatts() const {
  mPower_watts = convertdBmToWatts(mPower_dBm);
  mWattsSet = true;
}
