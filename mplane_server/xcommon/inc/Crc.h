/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Crc.h
 * \brief     Implements the CRC algorithm
 *
 *
 * \details   Implements polynomial 0x04C11DB7
 *
 */

#ifndef CRC_H_
#define CRC_H_

#include <cstdint>
#include <vector>

namespace Mplane {

class Crc32 {
 public:
  /**
   * Calculate the 32-bit CRC of the specified data
   */
  static uint32_t calc(uint32_t crc, const std::vector<uint8_t>& data);

  /**
   * Calculate the 32-bit CRC of the specified data
   */
  static uint32_t calc(uint32_t crc, const uint8_t* data, unsigned size);

  /**
   * Calculate the 32-bit CRC of the specified data
   */
  static uint32_t calc(const std::vector<uint8_t>& data);

  /**
   * Calculate the 32-bit CRC of the specified data
   */
  static uint32_t calc(const uint8_t* data, unsigned size);

 private:
  // table of all possible CRCs for a byte
  static uint32_t crc32table[256];
};

class Crc16 {
 public:
  /**
   * Calculate the 16-bit CRC of the specified data
   */
  static uint16_t calc_ibm(const char* dataBuffer, const unsigned numBytes);
  static uint16_t bitReverse(uint16_t data, const int numBits);

  static uint16_t calc_ccitt(const char* dataBuffer, unsigned numBytes);

 protected:
  static const uint16_t WIDTH;
  static const uint16_t CRC16_POLYNOMIAL;
  static const uint16_t MSB;
};

} // namespace Mplane

#endif /* CRC_H_ */
