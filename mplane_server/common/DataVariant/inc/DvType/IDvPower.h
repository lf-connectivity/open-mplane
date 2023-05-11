/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvPower.h
 * \brief     Virtual interface to POWER type
 *
 *
 * \details
 *
 */

#ifndef IDVPOWER_H_
#define IDVPOWER_H_

#include "Power.h"

namespace Mplane {

class IDvPower {
 public:
  IDvPower() {}
  virtual ~IDvPower() {}

  /**
   * Set the value of the the variant to the frequency value.
   *
   * @param value
   */
  virtual bool setPower(const Power& value) = 0;

  /**
   * Method returns the current variant value as a frequency
   *
   * @return variant value as a frequency
   */
  virtual Power toPower() const = 0;
};

} // namespace Mplane

#endif /* IDVPOWER_H_ */
