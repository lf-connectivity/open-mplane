/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvInt.h
 * \brief     Virtual interface to INT type
 *
 *
 * \details   Interface provides the conversion to/from the specific type (INT)
 *
 */

#ifndef IDVINT_H_
#define IDVINT_H_

namespace Mplane {

class IDvInt {
 public:
  IDvInt() {}
  virtual ~IDvInt() {}

  /**
   * Set the value of the the variant to the integer value. If the variant
   * is type Float, the value is cast to a float internally.
   *
   *
   * @param value
   */
  virtual bool setInt(int value) = 0;

  /**
   * Method returns the current variant value as an integer
   *
   * @return variant value as an integer
   */
  virtual int toInt() const = 0;
};

} // namespace Mplane

#endif /* IDVINT_H_ */
