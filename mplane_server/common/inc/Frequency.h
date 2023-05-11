#ifndef _COMM_FREQUENCY_H_
#define _COMM_FREQUENCY_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Frequency.h
 * \brief     A file to contain general purpose radio frequency wrapper
 *
 *
 * \details   This file defines general purpose radio frequency wrapper data
 *
 */

#include "FrequencyBase.hpp"
#include <iostream>

namespace Mplane {

/*! \brief A general purpose radio frequency class.
 *
 * The Frequency class acts as a simple data type wrapper class for radio
 * frequency data.
 * Radio frequency typically range from the 100ths of hertz right up to 1000s
 * of megahertz.
 * To ensure no data loss, the frequency needs to be held internal as an
 * unsigned integer, giving it a range of zero to 4,294,967,295 (over 4 Ghz).
 *
 * The class also implements a number of getter and setter functions that allow
 * the internal frequency data to be represented in other unit types, as defined
 * by the Frequency::Unit enumeration.
 *
 * All the basic arithmetic and comparative operators have also been implemented
 * to allow the Frequency objects to be used in general math and logic testing.
 */
class Frequency : public FrequencyBase<long long unsigned> {

 public:
  using Unit = FrequencyStatic::Unit;

  /**
   * Simple frequency object constructor.
   */
  Frequency();

  /**
   * Frequency object constructor that allows the initial frequency value to be
   * set using an unsigned integer with a given units scale
   *
   * @code
   * Frequency fmhz(2100U, Frequency::MHz);
   * @endcode
   *
   *
   * @param frequency assigned to the object
   * @param unit default to hertz but can be overridden to any Frequency::Unit
   * type
   */
  Frequency(
      long long unsigned int frequency, Frequency::Unit unit = Frequency::Hz);

  /**
   * Frequency object constructor that allows the initial frequency value to be
   * set using an unsigned integer with a given units scale
   *
   * @code
   * Frequency fmhz(21.4, Frequency::MHz);
   * @endcode
   *
   *
   * @param frequency assigned to the object
   * @param unit default to hertz but can be overridden to any Frequency::Unit
   * type
   */
  Frequency(double frequency, Frequency::Unit unit = Frequency::Hz);

  /**
   * Conversion function to convert from base type to this type (just some glue
   * to make the operators work as expected)
   * @param rhs    Object to copy convert
   */
  // cppcheck-suppress noExplicitConstructor
  Frequency(const FrequencyBase<long long unsigned>& rhs);

 protected:
  /**
   * Hook called when value may be going negative. For types that don't support
   * negative values, you can either return 0 or throw an exception here (or
   * handle it in some other way)
   * @param val    New value to be checked
   * @return possibly modified value to use
   */
  virtual long long unsigned negativeValue(const long long unsigned val) const;
};

} /* namespace Mplane */

// Make Frequency printable
inline std::ostream&
operator<<(std::ostream& os, const Mplane::Frequency& frequency) {
  os << frequency.getUint(Mplane::Frequency::KHz) << " "
     << frequency.unit2Str(Mplane::Frequency::KHz);
  return os;
}

#endif /* _COMM_FREQUENCY_H_ */
