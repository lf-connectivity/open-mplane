/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Sha1.cpp
 * \brief     Calculate the SHA1 value
 *
 *
 * \details   Based on https://en.wikipedia.org/wiki/SHA-1 (pseudocode shown in
 * //@@)
 *
 */

//@@ Note 1: All variables are unsigned 32-bit quantities and wrap modulo 232
// when calculating, except for
//@@            ml, the message length, which is a 64-bit quantity, and
//@@            hh, the message digest, which is a 160-bit quantity.
//@@    Note 2: All constants in this pseudo code are in big endian.
//@@            Within each word, the most significant byte is stored in
// the leftmost byte position
//@@
//@@    Initialize variables:
//@@
//@@    h0 = 0x67452301
//@@    h1 = 0xEFCDAB89
//@@    h2 = 0x98BADCFE
//@@    h3 = 0x10325476
//@@    h4 = 0xC3D2E1F0
//@@
//@@    ml = message length in bits (always a multiple of the number of bits in
// a character).
//@@
//@@    Pre-processing:
//@@    append the bit '1' to the message e.g. by adding 0x80 if message length
// is a multiple of 8 bits.
//@@    append 0 <= k < 512 bits '0', such that the resulting message length in
// bits
//@@       is congruent to 448 (mod 512)
//@@    append ml, in a 64-bit big-endian integer. Thus, the total length is a
// multiple of 512 bits.
//@@
//@@    Process the message in successive 512-bit chunks:
//@@    break message into 512-bit chunks
//@@    for each chunk
//@@        break chunk into sixteen 32-bit big-endian words w[i], 0 <= i <=
// 15
//@@
//@@        Extend the sixteen 32-bit words into eighty 32-bit words:
//@@        for i from 16 to 79
//@@            w[i] = (w[i-3] xor w[i-8] xor w[i-14] xor w[i-16])
// leftrotate 1
//@@
//@@        Initialize hash value for this chunk:
//@@        a = h0
//@@        b = h1
//@@        c = h2
//@@        d = h3
//@@        e = h4
//@@
//@@        for i from 0 to 79
//@@            if 0 <= i <= 19 then
//@@                f = (b and c) or ((not b) and d)
//@@                k = 0x5A827999
//@@            else if 20 <= i <= 39
//@@                f = b xor c xor d
//@@                k = 0x6ED9EBA1
//@@            else if 40 <= i <= 59
//@@                f = (b and c) or (b and d) or (c and d)
//@@                k = 0x8F1BBCDC
//@@            else if 60 <= i <= 79
//@@                f = b xor c xor d
//@@                k = 0xCA62C1D6
//@@
//@@            temp = (a leftrotate 5) + f + e + k + w[i]
//@@            e = d
//@@            d = c
//@@            c = b leftrotate 30
//@@            b = a
//@@            a = temp
//@@
//@@        Add this chunk's hash to result so far:
//@@        h0 = h0 + a
//@@        h1 = h1 + b
//@@        h2 = h2 + c
//@@        h3 = h3 + d
//@@        h4 = h4 + e

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iomanip>
#include <iostream>
#include <sstream>

//#include "ByteTransfer.hpp"
#include "Sha1.h"

using namespace Mplane;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {

inline uint32_t
leftrotate(uint32_t value, unsigned int steps) {
  return ((value << steps) | (value >> (32 - steps)));
}

} // namespace

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

unsigned Sha1::SHA1_SIZE{20};

//-------------------------------------------------------------------------------------------------------------
static const uint32_t H0{0x67452301};
static const uint32_t H1{0xEFCDAB89};
static const uint32_t H2{0x98BADCFE};
static const uint32_t H3{0x10325476};
static const uint32_t H4{0xC3D2E1F0};

// k values
static const uint32_t K0{0x5a827999};
static const uint32_t K20{0x6ed9eba1};
static const uint32_t K40{0x8f1bbcdc};
static const uint32_t K60{0xca62c1d6};

//=============================================================================================================
// MACROS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
//@@            temp = (a leftrotate 5) + f + e + k + w[i]
//@@            e = d
//@@            d = c
//@@            c = b leftrotate 30
//@@            b = a
//@@            a = temp

#define SHA1(func, k)                                                     \
  {                                                                       \
    const unsigned int temp = leftrotate(a, 5) + (func) + e + (k) + w[i]; \
    e = d;                                                                \
    d = c;                                                                \
    c = leftrotate(b, 30);                                                \
    b = a;                                                                \
    a = temp;                                                             \
  }

#define EXPAND_W(i) \
  { w[i] = leftrotate((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]), 1); }

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::vector<uint8_t>
Sha1::getHash(const std::vector<uint8_t>& data) {
  //@@    Initialize variables:
  //@@
  //@@    h0 = 0x67452301
  //@@    h1 = 0xEFCDAB89
  //@@    h2 = 0x98BADCFE
  //@@    h3 = 0x10325476
  //@@    h4 = 0xC3D2E1F0
  uint32_t h[] = {H0, H1, H2, H3, H4};

  // Buffer for the 80 32-bit words (derived from each block of sizteen 32-bit
  // words)
  uint32_t w[80];

  // work out how many complete 512-bit (64 byte) chunks we've got in the data
  const int numChunks(data.size() - 64);

  //@@    Process the message in successive 512-bit chunks:
  //@@    break message into 512-bit chunks
  //@@    for each chunk
  int currentChunk(0);
  while (currentChunk <= numChunks) {
    //@@        break chunk into sixteen 32-bit big-endian words w[i], 0 <= i <=
    // 15
    int endCurrentChunk(currentChunk + 64);
    int i(0);
    while (currentChunk < endCurrentChunk) {
      w[i++] = (uint32_t)data[currentChunk + 3] |
               (((uint32_t)data[currentChunk + 2]) << 8) |
               (((uint32_t)data[currentChunk + 1]) << 16) |
               (((uint32_t)data[currentChunk]) << 24);
      currentChunk += 4;
    }

    // calc the hash so far
    calcHash(h, w);
  }

  // Handle any remaining bytes
  clearW(w);
  int endCurrentChunk(data.size() - currentChunk);

  //    std::cerr << "[NEW] ================" << std::endl ;
  //    std::cerr << "[NEW] endCurrentBlock=" << endCurrentChunk << "
  // bytelength=" << data.size() << " : currentBlock=" << currentChunk <<
  // std::endl ;     std::cerr << "[NEW]  * --clear-- " << std::endl ;

  int remainingBytes = 0;
  //    unsigned dataIndex(currentChunk) ;
  while (remainingBytes < endCurrentChunk) {
    // std::cerr << "[NEW]  * w[" << (remainingBytes / 4) << "] = data[" <<
    //        dataIndex<<
    //        "]" <<
    //        std::endl ;

    w[remainingBytes / 4] |= (uint32_t)data[remainingBytes + currentChunk]
                             << ((3 - (remainingBytes % 4)) * 8);
    ++remainingBytes;
  }

  // std::cerr << "[NEW]  * w[" << (remainingBytes / 4) << "] |= 0x80 << " <<
  // (((3 - (remainingBytes & 3)) << 3)) << std::endl ;
  w[remainingBytes / 4] |= 0x80 << ((3 - (remainingBytes % 4)) * 8);

  if (endCurrentChunk >= 56) {
    // std::cerr << "[NEW]  * --hash-- " << std::endl ;
    calcHash(h, w);
    // std::cerr << "[NEW]  * --clear-- " << std::endl ;
    clearW(w);
  }

  // std::cerr << "[NEW]  * w[15] = " << (data.size() * 8) << std::endl ;
  w[15] = data.size() * 8;
  // std::cerr << "[NEW]  * --hash-- " << std::endl ;
  calcHash(h, w);
  //    std::cerr << "[NEW] ================" << std::endl ;

  // Format hash
  std::vector<uint8_t> hh(SHA1_SIZE);
  //    for (unsigned word=0, byte=0; word < 5; ++word)
  for (unsigned byte = 0; byte < SHA1_SIZE; ++byte) {
    //        ByteTransfer::writeWord(byte, hh, h[word]) ;
    hh[byte] = (h[byte / 4] >> (((3 - byte) & 0x3) << 3)) & 0xff;
  }
  return hh;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<uint8_t>
Sha1::getHash(const std::string& data) {
  std::vector<uint8_t> bytes(data.begin(), data.end());
  return getHash(bytes);
}

//-------------------------------------------------------------------------------------------------------------
std::string
Sha1::getHashString(const std::vector<uint8_t>& data) {
  return hashToString(getHash(data));
}

//-------------------------------------------------------------------------------------------------------------
std::string
Sha1::getHashString(const std::string& data) {
  return hashToString(getHash(data));
}

//-------------------------------------------------------------------------------------------------------------
std::string
Sha1::hashToString(const std::vector<uint8_t>& data) {
  std::stringstream ss;
  for (uint8_t byte : data) {
    ss << std::setfill('0') << std::setw(2) << std::hex << (unsigned)byte;
  }
  return ss.str();
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
Sha1::calcHash(uint32_t h[], uint32_t w[]) {
  //@@        Initialize hash value for this chunk:
  //@@        a = h0
  //@@        b = h1
  //@@        c = h2
  //@@        d = h3
  //@@        e = h4
  unsigned a(h[0]);
  unsigned b(h[1]);
  unsigned c(h[2]);
  unsigned d(h[3]);
  unsigned e(h[4]);

  // Combine 16 to 80 word expansion with the calculation
  //@@        for i from 16 to 79
  //@@            w[i] = (w[i-3] xor w[i-8] xor w[i-14] xor w[i-16]) leftrotate
  // 1

  //@@        for i from 0 to 79
  //@@            if 0 <= i <= 19 then
  //@@                f = (b and c) or ((not b) and d)
  //@@                k = 0x5A827999
  //@@            else if 20 <= i <= 39
  //@@                f = b xor c xor d
  //@@                k = 0x6ED9EBA1
  //@@            else if 40 <= i <= 59
  //@@                f = (b and c) or (b and d) or (c and d)
  //@@                k = 0x8F1BBCDC
  //@@            else if 60 <= i <= 79
  //@@                f = b xor c xor d
  //@@                k = 0xCA62C1D6

  int i(0);

  while (i < 16) {
    SHA1((b & c) | (~b & d), K0)
    ++i;
  }
  while (i < 20) {
    EXPAND_W(i);
    SHA1((b & c) | (~b & d), K0)
    ++i;
  }
  while (i < 40) {
    EXPAND_W(i);
    SHA1(b ^ c ^ d, K20)
    ++i;
  }
  while (i < 60) {
    EXPAND_W(i);
    SHA1((b & c) | (b & d) | (c & d), K40)
    ++i;
  }
  while (i < 80) {
    EXPAND_W(i);
    SHA1(b ^ c ^ d, K60)
    ++i;
  }

  //@@        Add this chunk's hash to result so far:
  //@@        h0 = h0 + a
  //@@        h1 = h1 + b
  //@@        h2 = h2 + c
  //@@        h3 = h3 + d
  //@@        h4 = h4 + e
  h[0] += a;
  h[1] += b;
  h[2] += c;
  h[3] += d;
  h[4] += e;
}

//-------------------------------------------------------------------------------------------------------------
void
Sha1::clearW(uint32_t w[]) {
  for (unsigned i = 0; i < 16; ++i)
    w[i] = 0;
}
