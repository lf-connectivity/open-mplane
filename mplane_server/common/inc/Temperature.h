#ifndef _COMM_TEMPERATURE_H_
#define _COMM_TEMPERATURE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Temperature.h
 * \brief     A file to contain general purpose radio temperature wrapper
 *
 *
 * \details   This file defines general purpose radio temperature wrapper data
 *
 */

#include <string>

namespace Mplane {

/*! \brief A general purpose temperature class.
 *
 * The Temperature class acts as a simple data type wrapper class for
 * temperature data.
 *
 * It can be set directly or through a raw value that can do y=mx+c conversion.
 *
 */
class Temperature {
 public:
  /**
   * Simple Temperature object constructor.
   */
  Temperature();

  /**
   * Simple Temperature object constructor.
   */
  // cppcheck-suppress noExplicitConstructor
  Temperature(float temperature);

  /**
   * Constructor used to create a temperature object type whose
   * value in Deg C is derived from a raw value, by multiplying
   * it by the slope and adding the offset.
   *
   * @param slope
   * @param offset
   */
  Temperature(float slope, float offset);

  /**
   * Simple Temperature Destructor
   */
  virtual ~Temperature();

  /**
   * Get the temperature in Deg C.
   *
   * @return temperature in Deg C.
   */
  float get() const;

  /**
   * Return the temperature to the nearest integer value in Deg C.
   * @return Temperature in Deg C as whole integer
   */
  int getInt() const;

  /**
   * Set the temperature value from a string, useful when creating temperature
   * constants from parsed text.
   *
   * @param temperature
   */
  void set(const std::string& temperature);

  /**
   * Assignment operator to allow the value of a Temperature object to be set by
   * another.
   *
   * @code
   * Temperature p1;
   * Temperature p2 = p1;
   * @endcode
   *
   * @param rhs Temperature object reference
   *
   * @return modified Temperature object
   */
  Temperature& operator=(const Temperature& rhs);

  /**
   * Assignment operator to allow the value of a Temperature object to be set by
   * a floating point value.
   *
   * @code
   * Temperature p1;
   * p1 = 50.2;
   * p1 = -8.7;
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return modified Temperature object
   */
  Temperature operator=(const float temperature);

  /**
   * Assignment operator to allow the value of a Temperature object to be set by
   * a signed integer as raw data using a y=(m*x)+c, where the m is defined by
   * the slope and c is defined by the offset in the constructor.
   *
   * @code
   * Temperature p1;
   * p1 = 50;
   * p1 = -8;
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return modified Temperature object
   */
  Temperature operator=(const int temperature);

  /**
   * Equality operator - provided for ComparisonOperators<>
   * @param rhs
   * @return return true if Temperatures equal
   */
  bool operator==(const Temperature& rhs) const;

  /**
   * Equality operator - provided for ComparisonOperators<>
   * @param rhs
   * @return return true if Temperatures equal
   */
  bool operator!=(const Temperature& rhs) const;

  /**
   * Less than operator - provided for ComparisonOperators<>
   * @param rhs
   * @return return true if this < rhs Temperature
   */
  bool operator<(const Temperature& rhs) const;

  /**
   * Less than or equal operator - provided for ComparisonOperators<>
   * @param rhs
   * @return return true if this <= rhs Temperature
   */
  bool operator<=(const Temperature& rhs) const;

  /**
   * Greater than operator - provided for ComparisonOperators<>
   * @param rhs
   * @return return true if this > rhs Temperature
   */
  bool operator>(const Temperature& rhs) const;

  /**
   * Greater than or equal operator - provided for ComparisonOperators<>
   * @param rhs
   * @return return true if this >= rhs Temperature
   */
  bool operator>=(const Temperature& rhs) const;

  /**
   * Operator overload to allow Temperature objects to be added together.
   *
   * @code
   * Temperature p1=20.0;
   * Temperature p2=10.0;
   * Temperature p3 = p1 + p2; // result 30.0
   * @endcode
   *
   * @param rhs an existing Temperature object reference.
   *
   * @return the modified left hand side reference
   */
  Temperature operator+(const Temperature& rhs) const;

  /**
   * Operator overload to allow a floating point value to be added to a
   * Temperature object.
   *
   * @code
   * Temperature p1;
   * Temperature p2=10.0;
   * p1 = p2 + 20.1; // result 30.1
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator+(const float temperature) const;

  /**
   * Operator overload to allow a signed integer to be added to a Temperature
   * object.
   *
   * @code
   * Temperature p1;
   * Temperature p2=10.0;
   * p1 = p2 + 20; // result 30.0
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator+(const int temperature) const;

  /**
   * Operator overload to allow a Temperature object to be added to an existing
   * temperature.
   *
   * @code
   * Temperature p1=20;
   * Temperature p2=33;
   * p1 += p2; // result 53.0
   * @endcode
   *
   * @param rhs
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator+=(const Temperature& rhs);

  /**
   * Operator overload to allow a floating point value to be added to an
   * existing Temperature object.
   *
   * @code
   * Temperature p1=20;
   * p1 += 22.5; // result 42.5
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator+=(const float temperature);

  /**
   * Operator overload to allow a signed int to be added to an existing
   * Temperature object.
   *
   * @code
   * Temperature p1=21;
   * p1 += 22; // result 43.0
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator+=(const int temperature);

  /**
   * Operator overload to allow Temperature objects to be multiplied together.
   *
   * @code
   * Temperature p1=20;
   * Temperature p2=10;
   * Temperature p3 = p1 * p2; // result 200
   * @endcode
   *
   * @param rhs an existing Temperature object reference.
   *
   * @return the modified left hand side reference
   */
  Temperature operator*(const Temperature& rhs) const;

  /**
   * Operator overload to allow a floating point value to be multiplied by a
   * Temperature object.
   *
   * @code
   * Temperature p1;
   * Temperature p2=100;
   * p1 = p2 * 10.0; // result 1000
   * @endcode
   *
   * @param temperature temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator*(const float temperature) const;

  /**
   * Operator overload to allow a signed integer to be multiplied by a
   * Temperature object.
   *
   * @code
   * Temperature p1;
   * Temperature p2=100;
   * p1 = p2 * 3; // result 300
   * @endcode
   *
   * @param temperature temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator*(const int temperature) const;

  /**
   * Operator overload to allow a Temperature object to be multiplied by an
   * existing temperature.
   *
   * @code
   * Temperature p1=20;
   * Temperature p2=10;
   * p1 *= p2; // result 200
   * @endcode
   *
   * @param rhs
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator*=(const Temperature& rhs);

  /**
   * Operator overload to allow a floating point value to be multiplied by an
   * existing Temperature object.
   *
   * @code
   * Temperature p1=20;
   * p1 *= 10.1; // result 202
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return the modified left hand side reference
   */
  Temperature operator*=(const float temperature);

  /**
   * Operator overload to allow a signed int to be multiplied by an existing
   * Temperature object.
   *
   * @code
   * Temperature p1=20;
   * p1 *= 11; // result 220
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return the modified left hand side reference
   */
  Temperature operator*=(const int temperature);

  /**
   * Operator overload to allow Temperature objects to be divided together.
   *
   * @code
   * Temperature p1=20;
   * Temperature p2=10;
   * Temperature p3 = p1 / p2; // result 2
   * @endcode
   *
   * @param rhs an existing Temperature object reference.
   *
   * @return the modified left hand side reference
   */
  Temperature operator/(const Temperature& rhs) const;

  /**
   * Operator overload to allow a floating point value to be divided by a
   * Temperature object.
   *
   * @code
   * Temperature p1;
   * Temperature p2=120
   * p1 = p2 / 1.5; // result 80
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator/(const float temperature) const;

  /**
   * Operator overload to allow a signed integer to be divided by a Temperature
   * object.
   *
   * @code
   * Temperature p1;
   * Temperature p2=100
   * p1 = p2 / 10; // result 10
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator/(const int temperature) const;

  /**
   * Operator overload to allow a Temperature object to be divided by an
   * existing temperature.
   *
   * @code
   * Temperature p1=200;
   * Temperature p2=10;
   * p1 /= p2; // result 20
   * @endcode
   *
   * @param rhs
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator/=(const Temperature& rhs);

  /**
   * Operator overload to allow a floating point value to divided by an
   * existing Temperature object.
   *
   * @code
   * Temperature p1=200;
   * p1 /= 2.5; // result 80
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator/=(const float temperature);

  /**
   * Operator overload to allow a signed int to divided by an existing
   * Temperature object.
   *
   * @code
   * Temperature p1=200;
   * p1 /= 10; // result 20
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator/=(const int temperature);

  /**
   * Operator overload to allow a Temperature object to be subtracted from
   * another Temperature object.
   *
   * @code
   * Temperature p1=20.0;
   * Temperature p2=10.0;
   * Temperature p3 = p1 - p2; // result 10.0
   * @endcode
   *
   * @param rhs Temperature object
   *
   * @return modified Temperature object
   */
  Temperature operator-(const Temperature& rhs) const;

  /**
   * Operator overload to allow a floating point value to be subtracted from
   * another Temperature object.
   *
   * @code
   * Temperature p1;
   * Temperature p2=10.0;
   * p1 = 20.1 - p2; // result 10.1
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator-(const float temperature) const;

  /**
   * Operator overload to allow a signed integer to be subtracted from another
   * Temperature object.
   *
   * @code
   * Temperature p1;
   * Temperature p2=10.0;
   * p1 = 20 - p2; // result 10.0
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator-(const int temperature) const;

  /**
   * Operator overload to allow a Temperature object to be subtracted from an
   * existing Temperature.
   *
   * @code
   * Temperature f1=220;
   * Temperature f2=100;
   * f1 -= f2; // result 120
   * @endcode
   *
   * @param rhs
   *
   * @return modified Temperature object
   */
  Temperature operator-=(const Temperature& rhs);

  /**
   * Operator overload to allow a floating point value to be subtracted from an
   * existing Temperature.
   *
   * @code
   * Temperature f1=210;
   * f1 -= 100; // result 110
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator-=(const float temperature);

  /**
   * Operator overload to allow a signed integer to be subtracted from an
   * existing Temperature.
   *
   * @code
   * Temperature f1=210;
   * f1 -= 100; // result 110
   * @endcode
   *
   * @param temperature in Deg C
   *
   * @return reference to the modified Temperature object
   */
  Temperature operator-=(const int temperature);

 protected:
  float mTemperature;
  float mSlope;
  float mOffset;
  int mRawTemp;
};

} /* namespace Mplane */

#endif /* _COMM_TEMPERATURE_H_ */
