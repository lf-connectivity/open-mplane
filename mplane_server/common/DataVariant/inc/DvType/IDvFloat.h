/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvFloat.h
 * \brief     Virtual interface to FLOAT type
 *
 *
 * \details   Interface provides the conversion to/from the specific type
 * (FLOAT)
 *
 */

#ifndef IDvFloat_H_
#define IDvFloat_H_

namespace Mplane {

class IDvFloat {
 public:
  IDvFloat() {}
  virtual ~IDvFloat() {}

  /**
   * Set the value of the the variant to the float value.
   *
   * @param value
   */
  virtual bool setFloat(float value) = 0;

  /**
   * Method returns the current variant value as a float
   *
   * @return variant value as a float
   */
  virtual float toFloat() const = 0;
};

} // namespace Mplane

#endif /* IDvFloat_H_ */
