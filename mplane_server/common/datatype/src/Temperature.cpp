/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Temperature.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "Temperature.h"
#include "Maths.h"
#include <cmath>

using namespace Mplane;

Mplane::Temperature::Temperature()
    : mTemperature(0.0f), mSlope(1.0f), mOffset(0.0f), mRawTemp(0) {}

Mplane::Temperature::Temperature(float temperature)
    : mTemperature(temperature), mSlope(1.0f), mOffset(0.0f), mRawTemp(0) {}
Mplane::Temperature::Temperature(float slope, float offset)
    : mTemperature(0.0f), mSlope(slope), mOffset(offset), mRawTemp(0) {}

Mplane::Temperature::~Temperature() {}

Mplane::Temperature&
Mplane::Temperature::operator=(const Mplane::Temperature& rhs) {
  mTemperature = rhs.mTemperature;
  mSlope = rhs.mSlope;
  mOffset = rhs.mOffset;
  mRawTemp = rhs.mRawTemp;
  return *this;
}

Mplane::Temperature
Mplane::Temperature::operator=(const float temperature) {
  mTemperature = temperature;
  return *this;
}

Mplane::Temperature
Mplane::Temperature::operator=(const int temperature) {
  mRawTemp = temperature;
  mTemperature = ((float)mRawTemp * mSlope) + mOffset;
  return *this;
}

bool
Mplane::Temperature::operator==(const Mplane::Temperature& rhs) const {
  return (mTemperature == rhs.mTemperature);
}

bool
Mplane::Temperature::operator!=(const Temperature& rhs) const {
  return !operator==(rhs);
}

bool
Mplane::Temperature::operator<(const Mplane::Temperature& rhs) const {
  return (mTemperature < rhs.mTemperature);
}

bool
Mplane::Temperature::operator<=(const Mplane::Temperature& rhs) const {
  return !operator>(rhs);
}

bool
Mplane::Temperature::operator>(const Mplane::Temperature& rhs) const {
  return (mTemperature > rhs.mTemperature);
}

bool
Mplane::Temperature::operator>=(const Mplane::Temperature& rhs) const {
  return !operator<(rhs);
}

float
Mplane::Temperature::get() const {
  return mTemperature;
}

int
Mplane::Temperature::getInt() const {
  return (
      int)(mTemperature - floor(mTemperature) < 0.5 ? floor(mTemperature) : ceil(mTemperature));
}

void
Mplane::Temperature::set(const std::string& temperature) {
  mTemperature = Maths::str2float(temperature);
}

Temperature
Mplane::Temperature::operator+(const Temperature& rhs) const {
  return Temperature(mTemperature + rhs.mTemperature);
}

Temperature
Mplane::Temperature::operator+(const float temperature) const {
  return Temperature(mTemperature + temperature);
}

Temperature
Mplane::Temperature::operator+(const int temperature) const {
  return Temperature(mTemperature + (float)temperature);
}

Temperature
Mplane::Temperature::operator+=(const Temperature& rhs) {
  mTemperature += rhs.mTemperature;
  return *this;
}

Temperature
Mplane::Temperature::operator+=(const float temperature) {
  mTemperature += temperature;
  return *this;
}

Temperature
Mplane::Temperature::operator+=(const int temperature) {
  mTemperature += (float)temperature;
  return *this;
}

Temperature
Mplane::Temperature::operator*(const Temperature& rhs) const {
  return Temperature(mTemperature * rhs.mTemperature);
}

Temperature
Mplane::Temperature::operator*(const float temperature) const {
  return Temperature(mTemperature * temperature);
}

Temperature
Mplane::Temperature::operator*(const int temperature) const {
  return Temperature(mTemperature * (float)temperature);
}

Temperature
Mplane::Temperature::operator*=(const Temperature& rhs) {
  mTemperature *= rhs.mTemperature;
  return *this;
}

Temperature
Mplane::Temperature::operator*=(const float temperature) {
  mTemperature *= temperature;
  return *this;
}

Temperature
Mplane::Temperature::operator*=(const int temperature) {
  mTemperature *= (float)temperature;
  return *this;
}

Temperature
Mplane::Temperature::operator/(const Temperature& rhs) const {
  return Temperature(mTemperature / rhs.mTemperature);
}

Temperature
Mplane::Temperature::operator/(const float temperature) const {
  return Temperature(mTemperature / temperature);
}

Temperature
Mplane::Temperature::operator/(const int temperature) const {
  return Temperature(mTemperature / (float)temperature);
}

Temperature
Mplane::Temperature::operator/=(const Temperature& rhs) {
  mTemperature /= rhs.mTemperature;
  return *this;
}

Temperature
Mplane::Temperature::operator/=(const float temperature) {
  mTemperature /= temperature;
  return *this;
}

Temperature
Mplane::Temperature::operator/=(const int temperature) {
  mTemperature /= (float)temperature;
  return *this;
}

Temperature
Mplane::Temperature::operator-(const Temperature& rhs) const {
  return Temperature(mTemperature - rhs.mTemperature);
}

Temperature
Mplane::Temperature::operator-(const float temperature) const {
  return Temperature(mTemperature - temperature);
}

Temperature
Mplane::Temperature::operator-(const int temperature) const {
  return Temperature(mTemperature - (float)temperature);
}

Temperature
Mplane::Temperature::operator-=(const Temperature& rhs) {
  mTemperature -= rhs.mTemperature;
  return *this;
}

Temperature
Mplane::Temperature::operator-=(const float temperature) {
  mTemperature -= temperature;
  return *this;
}

Temperature
Mplane::Temperature::operator-=(const int temperature) {
  mTemperature -= (float)temperature;
  return *this;
}
