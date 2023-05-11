/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvLong.h
 * \brief     Virtual interface to LONG type
 *
 *
 * \details   Interface provides the conversion to/from the specific type (LONG)
 *
 */

#ifndef IDvLong_H_
#define IDvLong_H_

namespace Mplane {

class IDvLong {
 public:
  IDvLong() {}
  virtual ~IDvLong() {}

  /**
   * Set the value of the the variant to the long long value.
   *
   * @param value
   */
  virtual bool setLong(long long value) = 0;

  /**
   * Method returns the current variant value as a long long
   *
   * @return variant value as a long long
   */
  virtual long long toLong() const = 0;
};

} // namespace Mplane

#endif /* IDvLong_H_ */
