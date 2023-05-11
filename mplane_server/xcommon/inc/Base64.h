/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Base64.h
 * \brief     Base64 encode/decode
 *
 *
 * \details
 *
 */

#ifndef BASE64_H_
#define BASE64_H_

#include <cstdint>
#include <string>
#include <vector>

namespace Mplane {

class Base64 {
 public:
  /**
   * Encode string into BASE-64 string
   * @param str
   * @return BASE-64 string
   */
  static std::string encode(const std::string& str);

  /**
   * Encode data into BASE-64 string
   * @param data
   * @return BASE-64 string
   */
  static std::string encode(const std::vector<uint8_t>& data);

  /**
   * Decode BASE-64 string into string
   * @param base64
   * @return decoded string
   */
  static std::string decode(const std::string& base64);

  /**
   * Decode BASE-64 data into string
   * @param data
   * @return decoded string
   */
  static std::string decode(const std::vector<uint8_t>& data);
};

} // namespace Mplane

#endif /* BASE64_H_ */
