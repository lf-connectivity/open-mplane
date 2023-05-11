/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvDouble.h
 * \brief     Virtual interface to DOUBLE type
 *
 *
 * \details   Interface provides the conversion to/from the specific type
 * (DOUBLE)
 *
 */

#ifndef IDvDouble_H_
#define IDvDouble_H_

namespace Mplane {

class IDvDouble {
 public:
  IDvDouble() {}
  virtual ~IDvDouble() {}

  /**
   * Set the value of the the variant to the double value.
   *
   * @param value
   */
  virtual bool setDouble(double value) = 0;

  /**
   * Method returns the current variant value as a double
   *
   * @return variant value as a double
   */
  virtual double toDouble() const = 0;
};

} // namespace Mplane

#endif /* IDvDouble_H_ */
