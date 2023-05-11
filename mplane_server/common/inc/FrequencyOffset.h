#ifndef _COMM_FREQUENCYOFFSET_H_
#define _COMM_FREQUENCYOFFSET_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FrequencyOffset.h
 * \brief     A file to contain general purpose radio frequency wrapper
 *
 *
 * \details   This file defines general purpose radio frequency wrapper data
 *
 */

#include "Frequency.h"
#include "FrequencyBase.hpp"
#include <iostream>
#include <sstream>

namespace Mplane {

/*! \brief A general purpose radio frequency class.
 *
 * The Frequency class acts as a simple data type wrapper class for radio
 * frequency data.
 * Radio frequency typically range from the 100ths of hertz right up to 1000s
 * of megahertz.
 * To ensure no data loss, the frequency needs to be held internal as a 64bit
 * long long which gives anough room for negative values.
 *
 * The class also implements a number of getter and setter functions that allow
 * the internal frequency data to be represented in other unit types, as defined
 * by the Frequency::Unit enumeration.
 *
 * All the basic arithmetic and comparative operators have also been implemented
 * to allow the Frequency objects to be used in general math and logic testing.
 */
class FrequencyOffset : public FrequencyBase<long long> {

 public:
  using Unit = FrequencyStatic::Unit;

  /**
   * Simple frequency object constructor.
   */
  FrequencyOffset();

  /**
   * FrequencyOffset object constructor that allows the initial frequency value
   * to be set using an unsigned integer with a given units scale
   *
   * @code
   * FrequencyOffset fmhz(2100LL, FrequencyOffset::MHz);
   * @endcode
   *
   *
   * @param frequency assigned to the object
   * @param unit default to hertz but can be overridden to any
   * FrequencyOffset::Unit type
   */
  FrequencyOffset(
      long long frequency, FrequencyOffset::Unit unit = FrequencyOffset::Hz);

  /**
   * Conversion function to convert from base type to this type (just some glue
   * to make the operators work as expected)
   * @param rhs    Object to copy convert
   */
  // cppcheck-suppress noExplicitConstructor
  FrequencyOffset(const FrequencyBase<long long>& rhs);

  /**
   * Conversion function to convert from Frequency to this type
   * @param rhs    Frequency to copy convert
   */
  // cppcheck-suppress noExplicitConstructor
  FrequencyOffset(const Frequency& rhs);

 protected:
  /**
   * Hook called when value may be going negative. For types that don't support
   * negative values, you can either return 0 or throw an exception here (or
   * handle it in some other way)
   * @param val    New value to be checked
   * @return possibly modified value to use
   */
  virtual long long negativeValue(const long long val) const;
};

} /* namespace Mplane */

// Make FrequencyOffset printable
inline std::ostream&
operator<<(std::ostream& os, const Mplane::FrequencyOffset& frequency) {
  os << frequency.getInt(Mplane::FrequencyOffset::KHz) << " "
     << frequency.unit2Str(Mplane::FrequencyOffset::KHz);
  return os;
}

#endif /* _COMM_FREQUENCYOFFSET_H_ */
