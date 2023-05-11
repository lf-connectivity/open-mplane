#ifndef _COMM_FREQUENCYBASE_HPP_
#define _COMM_FREQUENCYBASE_HPP_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FrequencyBase.h
 * \brief     Template Frequency wrapper
 *
 *
 * \details   This file defines general purpose radio frequency wrapper data.
 * (Ported from original static file)
 *
 */

#include "ComparisonOperators.hpp"
#include "Maths.h"
#include <cmath>
#include <string>

namespace Mplane {

class FrequencyStatic {
 public:
  /**
   * Enumeration of frequency units supported by the Frequency data type
   * getter and setter interface.The variable is self documenting.
   */
  enum Unit {
    Hz = 1, //!< Hz raw value
    THz = 10, //!< THz tens of hertz
    HHz = 100, //!< HHz hundreds of hertz
    KHz = 1000, //!< KHz thousands of hertz
    TKHz = 10000, //!< TKHz tens of thousands of hertz
    HKHz = 100000, //!< HKHz hundreds of thousands of hertz
    MHz = 1000000, //!< MHz millions of hertz
    GHz = 1000000000, //!< GHz thousand millions of hertz
  };

  /**
   * @ brief Method to convert Frequency::Unit type to a string.
   *
   * This Method can be used to convert the frequency unit type to a
   * simple string constant so that it can be used in debug trace.
   *
   * @code
   * Frequency f1(2000000U);
   * trace("Frequency is %f %s",f1.getDbl( Frequency::MHz ), f1.unit2Str(
   * Frequency::MHz) );
   * @endcode
   *
   *
   * @param value enumerated unit value.
   * @return a string representing the enumeration value
   */
  static const char* unit2Str(FrequencyStatic::Unit value);

  /**
   * @ brief Method to convert a string into a Frequency::Unit type
   *
   * @param a string representing the enumeration value
   * @return value enumerated unit value.
   */
  static FrequencyStatic::Unit str2unit(const std::string& units);
};

/*! \brief A general purpose radio frequency class.
 *
 * The Frequency class acts as a simple data type wrapper class for radio
 * frequency data.
 * Radio frequency typically range from the 100ths of hertz right up to 1000s
 * of megahertz.
 * To ensure no data loss, the frequency needs to be held internal as at least
 * an unsigned integer, giving it a range of zero to 4,294,967,295 (over 4 Ghz).
 *
 * The class also implements a number of getter and setter functions that allow
 * the internal frequency data to be represented in other unit types, as defined
 * by the Frequency::Unit enumeration.
 *
 * All the basic arithmetic and comparative operators have also been implemented
 * to allow the Frequency objects to be used in general math and logic testing.
 */
template <typename T>
class FrequencyBase : public FrequencyStatic,
                      public ComparisonOperators<FrequencyBase<T>> {
 public:
  using IntType = long long int;
  using UintType = long long unsigned int;

  // all FrequencyBase classes should have access to each other
  template <typename U>
  friend class FrequencyBase;

  /**
   * Simple frequency object constructor.
   */
  FrequencyBase<T>() : m_frequency(0) {}

  virtual ~FrequencyBase<T>() {}

  /**
   * Frequency object constructor that allows the initial frequency value to be
   * set using a double precision number with a given units scale
   * @code
   * Frequency fmhz(2100.0, Frequency::MHz);
   * @endcode
   *
   * @param dFrequency assigned to the object
   * @param unit default to hertz but can be overridden to any Frequency::Unit
   * type
   */
  FrequencyBase<T>(
      double dFrequency, FrequencyBase::Unit unit = FrequencyBase::Hz) {
    m_frequency = static_cast<T>(dFrequency * ((double)unit));
  }

  /**
   * Method that allows the frequency of the object to be set using an unsigned
   * integer value. (the equals = operator would normally be used where no unit
   * scaling is required).
   *
   * @code
   * Frequency f1;
   * f1.set( 100U, Frequency::KHz );
   * @endcode
   *
   * @param frequency
   * @param unit default to hertz but can be overridden to any Frequency::Unit
   * type
   */
  void
  set(double frequency, FrequencyBase::Unit unit = FrequencyBase::Hz) {
    m_frequency = static_cast<T>(frequency * static_cast<double>(unit));
  }

  /**
   * Method used to set the frequency using a string value, useful when setting
   * frequency objects from parsed text data.
   *
   * @param frequency
   * @param unit
   */
  void
  set(const std::string& frequency,
      FrequencyBase::Unit unit = FrequencyBase::Hz) {
    double dFreq = atof(frequency.c_str());
    set(dFreq, unit);
  }

  /**
   * Method used to retrieve the current frequency value as an unsigned integer,
   * by default in hertz. The unit parameter may be used to change the unit type
   * returned.
   *
   * @code
   * Frequency fconst(1234, Frequency::MHz);
   * unsigned int freq = fconst.getUint( Frequency::KHz );
   * @endcode
   *
   * @param unit default to hertz but can be overridden to any Frequency::Unit
   * type
   * @return frequency in the selected units
   */
  UintType
  getUint(FrequencyBase::Unit unit = FrequencyBase::Hz) const {
    double dscaledFreq = ((double)m_frequency / (double)unit);
    return static_cast<UintType>(fround(dscaledFreq));
  }

  /**
   * Method used to retrieve the current frequency value as an integer, by
   * default in hertz. The unit parameter may be used to change the unit type
   * returned.
   *
   * @code
   * Frequency fconst(1234, Frequency::MHz);
   * int freq = fconst.getInt( Frequency::KHz );
   * @endcode
   *
   * @param unit default to hertz but can be overridden to any Frequency::Unit
   * type
   * @return frequency in the selected units
   */
  IntType
  getInt(FrequencyBase::Unit unit = FrequencyBase::Hz) const {
    double dscaledFreq = ((double)m_frequency / (double)unit);
    return static_cast<IntType>(fround(dscaledFreq));
  }

  /**
   * Method used to retrieve the current frequency value as a double precision
   * float, by default in hertz. The unit parameter may be used to change the
   * unit type returned.
   *
   * @code
   * Frequency fconst(2100000000);
   * double freq = fconst.getDbl( Frequency::MHz );
   * @endcode
   *
   * @param unit default to hertz but can be overridden to any Frequency::Unit
   * type
   * @return frequency in the selected units.
   */
  double
  getDbl(FrequencyBase::Unit unit = FrequencyBase::Hz) const {
    return ((double)m_frequency / (double)unit);
  }

  /**
   * Method used to retrieve the current frequency value, by default
   * in hertz. The unit parameter may be used to change the unit type returned.
   *
   * @param unit default to hertz but can be overridden to any Frequency::Unit
   * type
   * @return frequency in the selected units
   */
  T
  get(FrequencyBase::Unit unit = FrequencyBase::Hz) const {
    double dscaledFreq = ((double)m_frequency / (double)unit);
    int sign = 1;
    if (dscaledFreq < 0.0) {
      sign = -1;
      dscaledFreq = -dscaledFreq;
    }
    dscaledFreq =
        (dscaledFreq - floor(dscaledFreq) < 0.5 ? floor(dscaledFreq)
                                                : ceil(dscaledFreq));

    T scaledFreq = static_cast<T>(dscaledFreq) * static_cast<T>(sign);
    return scaledFreq;
  }

  /**
   * Operator overload to allow Frequency objects to be added together.
   *
   * @code
   * Frequency f1=200;;
   * Frequency f2=100;
   * Frequency f3 = f1 + f2; // result 300
   * @endcode
   *
   * @param rhs an existing Frequency object reference.
   * @return the modified left hand side reference
   */
  FrequencyBase<T>
  operator+(const FrequencyBase<T>& rhs) const {
    return FrequencyBase<T>(m_frequency + rhs.m_frequency);
  }

  /**
   * Operator overload to allow and unsigned integer to be added to a Frequency
   * object.
   *
   * @code
   * Frequency f1;
   * Frequency f2=100;
   * f1 = f2 + 200; // result 300
   * @endcode
   *
   * @param frequency in hertz
   * @return reference to the modified Frequency object
   */
  FrequencyBase<T>
  operator+(const UintType frequency) const {
    return FrequencyBase<T>(m_frequency + static_cast<T>(frequency));
  }

  /**
   * Operator overload to allow a Frequency object to be added to an existing
   * frequency.
   *
   * @code
   * Frequency f1=200;
   * Frequency f2=2000;
   * f1 += f2; // result 2200
   * @endcode
   *
   *
   * @param rhs
   * @return reference to the modified Frequency object
   */
  FrequencyBase<T>
  operator+=(const FrequencyBase<T>& rhs) {
    m_frequency += rhs.m_frequency;
    return *this;
  }

  /**
   * Operator overload to allow an unsigned int to be added to an existing
   * Frequency object.
   *
   * @code
   * Frequency f1=200;
   * f1 += 2000; // result 2200
   * @endcode
   *
   * @param frequency in hertz
   * @return reference to the modified Frequency object
   */
  FrequencyBase<T>
  operator+=(const UintType frequency) {
    m_frequency += static_cast<T>(frequency);
    return *this;
  }

  /**
   * Operator overload to allow Frequency objects to be multiplied together.
   *
   * @code
   * Frequency f1=200;;
   * Frequency f2=100;
   * Frequency f3 = f1 * f2; // result 2000
   * @endcode
   *
   * @param rhs an existing Frequency object reference.
   * @return the modified left hand side reference
   */
  FrequencyBase<T>
  operator*(const FrequencyBase<T>& rhs) const {
    return FrequencyBase<T>(m_frequency * rhs.m_frequency);
  }

  /**
   * Operator overload to allow and unsigned integer to be multiplied by a
   * Frequency object.
   *
   * @code
   * Frequency f1;
   * Frequency f2=100;
   * f1 = f2 * 100; // result 10000
   * @endcode
   *
   * @param frequency frequency in hertz
   * @return reference to the modified Frequency object
   */
  FrequencyBase<T>
  operator*(const UintType frequency) const {
    return FrequencyBase<T>(m_frequency * static_cast<T>(frequency));
  }

  /**
   * Operator overload to allow a Frequency object to be multiplied by an
   * existing frequency.
   *
   * @code
   * Frequency f1=200;
   * Frequency f2=10;
   * f1 *= f2; // result 2000
   * @endcode
   *
   *
   * @param rhs
   * @return reference to the modified Frequency object
   */
  FrequencyBase<T>
  operator*=(const FrequencyBase<T>& rhs) {
    m_frequency *= rhs.m_frequency;
    return *this;
  }

  /**
   * Operator overload to allow an unsigned int to be multiplied by an existing
   * Frequency object.
   *
   * @code
   * Frequency f1=200;
   * f1 *= 10; // result 2000
   * @endcode
   *
   * @param frequency in hertz
   * @return the modified left hand side reference
   */
  FrequencyBase<T>
  operator*=(const UintType frequency) {
    m_frequency *= static_cast<T>(frequency);
    return *this;
  }

  /**
   * Operator overload to allow Frequency objects to be divided together.
   *
   * @code
   * Frequency f1=200;;
   * Frequency f2=100;
   * Frequency f3 = f1 / f2; // result 2
   * @endcode
   *
   * @param rhs an existing Frequency object reference.
   * @return the modified left hand side reference
   */
  FrequencyBase<T>
  operator/(const FrequencyBase<T>& rhs) const {
    return FrequencyBase<T>(m_frequency / rhs.m_frequency);
  }

  /**
   * Operator overload to allow and unsigned integer to be divided by a
   * Frequency object.
   *
   * @code
   * Frequency f1;
   * Frequency f2=100
   * f1 = f2 / 10; // result 10
   * @endcode
   *
   * @param frequency in hertz
   * @return reference to the modified Frequency object
   */
  FrequencyBase<T>
  operator/(const UintType frequency) const {
    return FrequencyBase<T>(m_frequency / static_cast<T>(frequency));
  }

  /**
   * Operator overload to allow a Frequency object to be divided by an existing
   * frequency.
   *
   * @code
   * Frequency f1=200;
   * Frequency f2=10;
   * f1 /= f2; // result 20
   * @endcode
   *
   *
   * @param rhs
   * @return reference to the modified Frequency object
   */
  FrequencyBase<T>
  operator/=(const FrequencyBase<T>& rhs) {
    m_frequency /= rhs.m_frequency;
    return *this;
  }

  /**
   * Operator overload to allow an unsigned int to divided by an existing
   * Frequency object.
   *
   * @code
   * Frequency f1=200;
   * f1 /= 10; // result 20
   * @endcode
   *
   * @param frequency in hertz
   * @return reference to the modified Frequency object
   */
  FrequencyBase<T>
  operator/=(const UintType frequency) {
    m_frequency /= static_cast<T>(frequency);
    return *this;
  }

  /**
   * Operator overload to allow a Frequency object to be subtracted from another
   * Frequency object.
   *
   * @code
   * Frequency f1=300;;
   * Frequency f2=100;
   * Frequency f3 = f1 - f2; // result 200
   * @endcode
   *
   * @param rhs Frequency object
   * @return modified Frequency object
   */
  FrequencyBase<T>
  operator-(const FrequencyBase<T>& rhs) const {
    T newFreq = (m_frequency - rhs.m_frequency);
    if (m_frequency < rhs.m_frequency)
      newFreq = negativeValue(newFreq);
    return FrequencyBase<T>(newFreq);
  }

  /**
   * Operator overload to allow an unsigned integer to be subtracted from
   * another Frequency object.
   *
   * @code
   * Frequency f1=300;;
   * Frequency f3 = f1 - 100; // result 200
   * @endcode
   *
   * @param frequency in hertz
   * @return modified Frequency object
   */
  FrequencyBase<T>
  operator-(const UintType frequency) const {
    T newFreq = (m_frequency - static_cast<T>(frequency));
    if (m_frequency < static_cast<T>(frequency))
      newFreq = negativeValue(newFreq);
    return FrequencyBase<T>(newFreq);
  }

  /**
   * Operator overload to allow a Frequency object to be subtracted from an
   * existing Frequency.
   *
   * @code
   * Frequency f1=2200;
   * Frequency f2=1000;
   * f1 -= f2; // result 1000
   * @endcode
   *
   *
   * @param rhs
   * @return modified Frequency object
   */
  FrequencyBase<T>
  operator-=(const FrequencyBase<T>& rhs) {
    m_frequency = (m_frequency - rhs.m_frequency);
    if (m_frequency < rhs.m_frequency)
      m_frequency = negativeValue(m_frequency);
    return *this;
  }

  /**
   * Operator overload to allow an unsigned integer to be subtracted from an
   * existing Frequency.
   *
   * @code
   * Frequency f1=2200;
   * f1 -= 1000; // result 1200
   * @endcode
   *
   * @param frequency in hertz
   * @return reference to the modified Frequency object
   */
  FrequencyBase<T>
  operator-=(const UintType frequency) {
    m_frequency = (m_frequency - static_cast<T>(frequency));
    if (m_frequency < static_cast<T>(frequency))
      m_frequency = negativeValue(m_frequency);
    return *this;
  }

  /**
   * Assignment operator to allow the value of a Frequency object to be set by
   * another.
   *
   * @code
   * Frequency f1;
   * Frequency f2 = f1;
   * @endcode
   *
   * @param rhs Frequency object reference
   * @return modified Frequency object
   */
  FrequencyBase<T>&
  operator=(const FrequencyBase<T>& rhs) {
    m_frequency = rhs.m_frequency;
    return *this;
  }

  /**
   * Assignment operator to allow the value of a Frequency object to be set by
   * an unsigned integer.
   *
   * @code
   * Frequency f1;
   * f1 = 5000;
   * @endcode
   *
   * @param frequency in hertz
   * @return modified Frequency object
   */
  FrequencyBase<T>
  operator=(const UintType frequency) {
    m_frequency = static_cast<T>(frequency);
    return *this;
  }

  /**
   * Equality operator - provided for ComparisonOperators<>
   * @param rhs
   * @return return true if frequencies equal
   */
  virtual bool
  operator==(const FrequencyBase<T>& rhs) const {
    return m_frequency == rhs.m_frequency;
  }

  /**
   * Less than operator - provided for ComparisonOperators<>
   * @param rhs
   * @return return true if this < rhs frequency
   */
  virtual bool
  operator<(const FrequencyBase<T>& rhs) const {
    return m_frequency < rhs.m_frequency;
  }

  /**
   * Truncates this frequency to the nearest integer multiple of the raster
   * frequency
   * @param raster
   */
  virtual void
  setRaster(const FrequencyBase<T>& raster) {
    double rasterDbl(raster.getDbl());
    double currentDbl(getDbl());
    UintType rasterMult(static_cast<UintType>(currentDbl / rasterDbl + 0.5));
    set(static_cast<double>(rasterMult) * rasterDbl);
  }

 protected:
  /**
   * Hook called when value will be going negative. For types that don't support
   * negative values, you can either return 0 or throw an exception here (or
   * handle it in some other way)
   * @param val    New value to be checked
   * @return possibly modified value to use
   */
  virtual T
  negativeValue(const T val) const {
    return val;
  }

 protected:
  T m_frequency;
};

} /* namespace Mplane */

#endif /* _COMM_FREQUENCYBASE_HPP_ */
