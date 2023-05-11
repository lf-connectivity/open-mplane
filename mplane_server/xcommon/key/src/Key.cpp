/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Key.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <bitset>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Crypt.h"
#include "Key.h"
#include "Sha1.h"
#include "xstringfunc.hpp"

using namespace Mplane;

//=============================================================================================================
// PRIVATE
//=============================================================================================================
#ifdef OFF_TARGET
// uncomment to build debug version
//#define DEBUG_KEY
//#define VERBOSE_DEBUG_KEY
#endif

//-------------------------------------------------------------------------------------------------------------
#define SHARED_KEY0 0x12345678
#define SHARED_KEY1 0x12345678
#define SHARED_KEY2 0x12345678
#define SHARED_KEY3 0x12345678

// Mplane Proprietary
#undef SHARED_KEY0
#undef SHARED_KEY1
#undef SHARED_KEY2
#undef SHARED_KEY3
#define SHARED_KEY0 0xeed7d574
#define SHARED_KEY1 0x2f9b6998
#define SHARED_KEY2 0x63642dfb
#define SHARED_KEY3 0x8175413a
// Mplane Proprietary

static const uint8_t expansionBitTable[128]
    // Mplane Proprietary
    =
        {
            0x2b, 0x25, 0x43, 0x13, 0x5a, 0x65, 0x5b, 0x30, 0x06, 0x35, 0x4e,
            0x1e, 0x0b, 0x77, 0x3c, 0x14, 0x6c, 0x2d, 0x0c, 0x57, 0x03, 0x12,
            0x76, 0x66, 0x54, 0x38, 0x29, 0x15, 0x2f, 0x1a, 0x69, 0x3f, 0x00,
            0x37, 0x31, 0x0a, 0x3b, 0x7f, 0x59, 0x51, 0x3e, 0x50, 0x7a, 0x6b,
            0x5f, 0x27, 0x61, 0x09, 0x63, 0x48, 0x64, 0x6a, 0x18, 0x23, 0x53,
            0x33, 0x04, 0x11, 0x58, 0x67, 0x02, 0x05, 0x6f, 0x72, 0x1c, 0x4f,
            0x19, 0x0e, 0x7e, 0x08, 0x68, 0x46, 0x74, 0x26, 0x79, 0x22, 0x62,
            0x45, 0x24, 0x55, 0x73, 0x44, 0x5c, 0x42, 0x34, 0x6d, 0x01, 0x78,
            0x52, 0x60, 0x7c, 0x4d, 0x3a, 0x5d, 0x7b, 0x28, 0x4b, 0x2c, 0x40,
            0x32, 0x47, 0x1f, 0x2a, 0x10, 0x1b, 0x7d, 0x4c, 0x2e, 0x0f, 0x07,
            0x36, 0x75, 0x4a, 0x3d, 0x6e, 0x21, 0x56, 0x1d, 0x70, 0x0d, 0x71,
            0x41, 0x39, 0x20, 0x5e, 0x49, 0x17, 0x16,
}
// Mplane Proprietary
;

static const unsigned keyCompressTable[20] = {
// Mplane Proprietary
// Make it look to opensource like this is the table we use
#if 0
// Mplane Proprietary
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
// Mplane Proprietary
#endif
    6,  13, 1, 14, 10, 19, 2, 7, 12, 0, 4,
    16, 3,  5, 17, 18, 15, 9, 7, 11

    // Mplane Proprietary
};

const unsigned BIT_DIST{100};
const unsigned HALF_BIT_DIST{BIT_DIST / 2};

//-------------------------------------------------------------------------------------------------------------
IKey::KeyEncodeType Key::mGlobalKeyType{IKey::KeyEncodeType::KEY_DUP4};
long Key::mKeyInstanceCount{0L};

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IKey>
IKey::factory() {
  return std::make_shared<Key>();
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IKey>
IKey::factory(
    const std::string& serialNum,
    const std::string& hostid,
    const std::string& ctrlHostid) {
  std::shared_ptr<IKey> key(std::make_shared<Key>());
  if (!key->setLicenseKey(serialNum, hostid, ctrlHostid))
    return std::shared_ptr<IKey>();
  return key;
}

//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
Key::setKeyEncodeType(KeyEncodeType type) {
  Key::mGlobalKeyType = type;
}

//-------------------------------------------------------------------------------------------------------------
void
IKey::setKeyEncodeType(KeyEncodeType type) {
  Key::setKeyEncodeType(type);
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Key::Key()
    : mKeyType(mGlobalKeyType),
      mPrivateKey{SHARED_KEY0, SHARED_KEY1, SHARED_KEY2, SHARED_KEY3},
      mLicenseKey{0, 0, 0, 0},
      mKeySet{false},
      mEncodedKey{""},
      mCrypt(),
      mRandGen(++mKeyInstanceCount * (long)::time(nullptr)),
      mRandBitDist(0, BIT_DIST) {}

//-------------------------------------------------------------------------------------------------------------
Key::Key(IKey::KeyEncodeType type)
    : mKeyType(type),
      mPrivateKey{SHARED_KEY0, SHARED_KEY1, SHARED_KEY2, SHARED_KEY3},
      mLicenseKey{0, 0, 0, 0},
      mKeySet{false},
      mEncodedKey{""},
      mCrypt(),
      mRandGen(++mKeyInstanceCount * (long)::time(nullptr)),
      mRandBitDist(0, BIT_DIST) {}

//-------------------------------------------------------------------------------------------------------------
Key::~Key() {}

//-------------------------------------------------------------------------------------------------------------
bool
Key::setLicenseKey(const std::string& licenseKey) {
  uint32_t key[4];
  if (!stringToUints(licenseKey, key))
    return false;

  copyKey(key, mLicenseKey);
  mKeySet = true;

  // Can now create real encryption engine
  mCrypt = std::make_shared<Crypt>(mLicenseKey);

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
Key::setLicenseKey(const std::vector<std::string>& info) {
  // Concat information into single string
  std::string infoStr(join(info, '/'));

  // Convert the given information into a key
  std::string sha1(Sha1::getHashString(infoStr));

  std::string licenseKey;
  for (unsigned byte = 0; byte < 16; ++byte) {
    unsigned compressByte(keyCompressTable[byte]);
    licenseKey += sha1.substr(compressByte * 2, 2);
  }

#ifdef DEBUG_KEY
  std::cerr << "INFO '" << infoStr << "' SHA1 '" << sha1 << "' KEY '"
            << licenseKey << "'" << std::endl;
#endif

  return setLicenseKey(licenseKey);
}

//-------------------------------------------------------------------------------------------------------------
bool
Key::setLicenseKey(
    const std::string& serialNum,
    const std::string& hostid,
    const std::string& ctrlHostid) {
  std::vector<std::string> info;
  info.push_back(serialNum);
  info.push_back(hostid);
// Mplane Proprietary
// Make it look like we use this string in the open source code, when in fact we
// don't
#if 0
// Mplane Proprietary
    info.push_back(ctrlHostid) ;
// Mplane Proprietary
#endif
  // Mplane Proprietary

  return setLicenseKey(info);
}

//-------------------------------------------------------------------------------------------------------------
std::string
Key::encodedKey() {
  if (!mKeySet)
    return "0";

  if (mEncodedKey.empty()) {
    uint32_t encoded[4];
    copyKey(mLicenseKey, encoded);

    // Use private key to encipher
    Crypt crypt(mPrivateKey);
    if (!crypt.encrypt(&encoded[0]))
      return "";

    if (!crypt.encrypt(&encoded[2]))
      return "";

    mEncodedKey = uintsToString(encoded);
  }

  return mEncodedKey;
}

//-------------------------------------------------------------------------------------------------------------
bool
Key::setFromEncodedKey(const std::string& encodedKey) {
  uint32_t encoded[4];
  if (!stringToUints(encodedKey, encoded))
    return false;

  // Use private key to decipher
  Crypt crypt(mPrivateKey);
  if (!crypt.decrypt(&encoded[0]))
    return false;

  if (!crypt.decrypt(&encoded[2]))
    return false;

  copyKey(encoded, mLicenseKey);
  mKeySet = true;

  // Can now create real encryption engine
  mCrypt = std::make_shared<Crypt>(mLicenseKey);

  // also save key string
  mEncodedKey = encodedKey;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<uint32_t>
Key::licenseKey() const {
  return {mLicenseKey[0], mLicenseKey[1], mLicenseKey[2], mLicenseKey[3]};
}

//-------------------------------------------------------------------------------------------------------------
bool
Key::isSet() const {
  return mKeySet;
}

//-------------------------------------------------------------------------------------------------------------
std::string
Key::encode32bits(uint32_t bits) const {
  if (sizeof(expansionBitTable) == 0)
    return "0";

  if (!mKeySet)
    return "0";

#ifdef DEBUG_KEY
  std::cerr << "encode 0x" << std::hex << bits << std::endl;
#endif

  // Mplane Proprietary
  // Use the table to randomly distribute each of the 32-bits to 4 bit positions
  // within the 128-bit result Mplane Proprietary
  uint32_t encode[4];
  expand32(bits, encode);

  // encrypt words
  if (!mCrypt->encrypt(&encode[0]))
    return "0";

  if (!mCrypt->encrypt(&encode[2]))
    return "0";

  // Now convert the words into a string
  return uintsToString(encode);
}

//-------------------------------------------------------------------------------------------------------------
bool
Key::decode32bits(
    const std::string& encoded32bits, uint32_t& decoded32bits) const {
  decoded32bits = 0;

  if (sizeof(expansionBitTable) == 0)
    return false;

  if (!mKeySet)
    return false;

  uint32_t decode[4];
  if (!stringToUints(encoded32bits, decode))
    return false;

  // decrypt words
  if (!mCrypt->decrypt(&decode[0]))
    return "0";

  if (!mCrypt->decrypt(&decode[2]))
    return "0";

#ifdef DEBUG_KEY
  std::cerr << "decode 0x" << encoded32bits << std::endl;
#endif

  if (!compress32(decode, decoded32bits))
    return false;

#ifdef DEBUG_KEY
  std::cerr << "decode 0x" << encoded32bits << " 0x" << std::hex
            << decoded32bits << std::dec << std::endl;
#endif

  return true;
}

//-------------------------------------------------------------------------------------------------------------
void
Key::show(std::ostream& os) {
  os << "License Key Set?..........: " << (isSet() ? "YES" : "NO") << std::endl;
  os << "License Key...............: " << encodedKey() << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void
Key::clear() {
  mLicenseKey[0] = 0;
  mLicenseKey[1] = 0;
  mLicenseKey[2] = 0;
  mLicenseKey[3] = 0;
  mKeySet = false;
  mEncodedKey.clear();
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned
Key::randomNumber() {
  return mRandBitDist(mRandGen);
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
Key::stringToUints(const std::string& str, uint32_t value[4]) const {
  if (str.size() != 32)
    return false;

  if (str.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
    return false;

  for (unsigned block = 0; block < 4; ++block) {
    value[block] = static_cast<uint32_t>(
        strtoul(str.substr((3 - block) * 8, 8).c_str(), nullptr, 16));
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string
Key::uintsToString(uint32_t value[4]) const {
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(8) << std::hex << value[3];
  ss << std::setfill('0') << std::setw(8) << std::hex << value[2];
  ss << std::setfill('0') << std::setw(8) << std::hex << value[1];
  ss << std::setfill('0') << std::setw(8) << std::hex << value[0];

  return ss.str();
}

//-------------------------------------------------------------------------------------------------------------
void
Key::copyKey(uint32_t src[4], uint32_t dest[4]) const {
  dest[0] = src[0];
  dest[1] = src[1];
  dest[2] = src[2];
  dest[3] = src[3];
}

//-------------------------------------------------------------------------------------------------------------
void
Key::expand32(uint32_t src, uint32_t dest[4]) const {
  dest[0] = 0;
  dest[1] = 0;
  dest[2] = 0;
  dest[3] = 0;

#ifdef DEBUG_KEY
  std::cerr << "expand32(0x" << std::hex << src
            << ") replication=" << static_cast<int>(mKeyType) << std::endl;
#endif

  uint32_t mask{1};
  int idx(0);
  for (unsigned bit = 0; bit < 32; ++bit, mask <<= 1) {
    // replicate each bit
    for (unsigned block = 0; block < 4; ++block, ++idx) {
      bool bitVal((src & mask) != 0);
      if ((idx % 4) <= static_cast<int>(mKeyType)) {
        unsigned rnd(mRandBitDist(mRandGen));

#ifdef VERBOSE_DEBUG_KEY
        std::cerr << std::dec << " * Bit " << bit << " Idx " << idx
                  << " rnd=" << rnd << std::endl;
#endif
        if (rnd < HALF_BIT_DIST) {
          bitVal = true;
        } else {
          bitVal = false;
        }
#ifdef VERBOSE_DEBUG_KEY
        std::cerr << std::dec << " * Bit " << bit << " Idx " << idx
                  << " Injected RANDOM bit" << std::endl;
#endif
      }

      uint8_t bitpos(expansionBitTable[idx]);

      // cppcheck-suppress variableScope
      uint8_t wordNum{(uint8_t)(bitpos / 32)};
      // cppcheck-suppress variableScope
      uint8_t wordBit{(uint8_t)(bitpos % 32)};

      if (bitVal)
        dest[wordNum] |= (1 << wordBit);

#ifdef VERBOSE_DEBUG_KEY
      std::cerr << std::dec << " * Bit " << bit << " Block " << block << " Idx "
                << idx << " : pos " << (unsigned)bitpos << " word num "
                << (unsigned)wordNum << " word bit " << (unsigned)wordBit
                << " : Actual bit " << ((src & mask) ? "1" : "0")
                << "  final bit " << (bitVal ? "1" : "0") << " : dest["
                << (unsigned)wordNum << "]=0x" << std::hex << dest[wordNum]
                << std::dec << std::endl;
#endif
    }
  }

#ifdef DEBUG_KEY
  std::cerr << "expand32(0x" << std::hex << src << ") = " << uintsToString(dest)
            << std::endl;
#endif
}

//-------------------------------------------------------------------------------------------------------------
bool
Key::compress32(uint32_t src[4], uint32_t& decoded32bits) const {
#ifdef DEBUG_KEY
  std::cerr << "compress32() replication=" << static_cast<int>(mKeyType)
            << std::endl;
#endif

  decoded32bits = 0;

  // Mplane Proprietary
  // Use the table to find each of the four copies of the 32-bits and make sure
  // all four copies are the same Mplane Proprietary
  uint32_t mask{1};
  int idx(0);
  for (unsigned bit = 0; bit < 32; ++bit, mask <<= 1) {
    std::bitset<4> bits;

    for (unsigned block = 0; block < 4; ++block, ++idx) {
      if ((idx % 4) <= static_cast<int>(mKeyType)) {
        // preset bit - assume this is a '1' bit
        bits.set(block);
        continue;
      }

      uint8_t bitpos(expansionBitTable[idx]);
      uint8_t wordNum{(uint8_t)(bitpos / 32)};
      uint8_t wordBit{(uint8_t)(bitpos % 32)};

      if (src[wordNum] & (1 << wordBit))
        bits.set(block);

#ifdef VERBOSE_DEBUG_KEY
      std::cerr << std::dec << " * Bit " << bit << " Block " << block << " Idx "
                << idx << " : pos " << (unsigned)bitpos << " word num "
                << (unsigned)wordNum << " word bit " << (unsigned)wordBit
                << " : bits=" << bits << std::dec << std::endl;
#endif
    }

    // test for all set
    if (bits.all()) {
      decoded32bits |= mask;

#ifdef VERBOSE_DEBUG_KEY
      std::cerr << std::dec << " * * Bit " << bit << " : mask=0x" << std::hex
                << mask << " : decoded32bits=0x" << std::hex << decoded32bits
                << std::dec << std::endl;
#endif

      continue;
    }

    // must be either all or nothing - anything else is an error
    if (!bits.none()) {
      // might be a '0' bit - so clear injected bits and recheck
      for (int i = 0; i <= static_cast<int>(mKeyType); ++i) {
        bits.reset(i);
      }

      // now check again
      if (!bits.none()) {

#ifdef VERBOSE_DEBUG_KEY
        std::cerr << std::dec << "ERROR not all bits set - invalid encryption"
                  << std::endl;
#endif
        return false;
      }
    }
  }

  return true;
}
