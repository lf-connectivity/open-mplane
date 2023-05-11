/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Key.h
 * \brief     Manages 128-bit key manipulation
 *
 *
 * \details   Takes in an external 128-bit license key and combines this with an
 * private shared key so that two or more applications can share the license key
 * by passing around an encoded key
 *
 */

#ifndef KEY_H_
#define KEY_H_

#include <cstdint>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "IKey.h"

namespace Mplane {

class Crypt;

class Key : public virtual IKey {
 public:
  Key();
  explicit Key(IKey::KeyEncodeType type);
  virtual ~Key();

  /**
   * Set the replication factor for any keys created after this call
   * (unless key is created with specific key setting)
   */
  static void setKeyEncodeType(IKey::KeyEncodeType type);

  /**
   * Set the license key from a hex string
   * @param licenseKey
   * @return true if valid 128bit hex value string; false otherwise
   */
  virtual bool setLicenseKey(const std::string& licenseKey) override;

  /**
   * Set the license key from the board serial number, hostid, and the GUI
   * hostid.
   * @param serialNum        Board serial number
   * @param hostId        Board host id
   * @param ctrlHostid    Controlling PC (GUI / SCPI) host id
   * @return true if set the license ok; false otherwise
   */
  virtual bool setLicenseKey(
      const std::string& serialNum,
      const std::string& hostid,
      const std::string& ctrlHostid) override;

  /**
   * Set the license key from any collection information strings.
   * @param info
   * @return true if set the license ok; false otherwise
   */
  virtual bool setLicenseKey(const std::vector<std::string>& info) override;

  /**
   * Get the key in an encoded form suitable for sharing with other applications
   * @return
   */
  virtual std::string encodedKey() override;

  /**
   * Use an encoded key string to set the license key
   * @param encodedKey
   * @return true if key set; false otherwise
   */
  virtual bool setFromEncodedKey(const std::string& encodedKey) override;

  /**
   * Get the license key as an array suitable for using with Crypt
   * @return the license key value
   */
  virtual std::vector<uint32_t> licenseKey() const override;

  /**
   * Is the license key currently set?
   */
  virtual bool isSet() const override;

  /**
   * Takes in 32-bits, expands the value to 128-bits, then encodes that value
   * and returns a hex string
   * @param bits
   * @return hex string
   */
  virtual std::string encode32bits(uint32_t bits) const override;

  /**
   * Takes in the 128-bit hex string and decodes back to 32 bits
   * @param encoded32bits
   * @param decoded32bits
   * @return true if decoded correctly; false if the string is invalid
   */
  virtual bool decode32bits(
      const std::string& encoded32bits, uint32_t& decoded32bits) const override;

  /**
   * Show current settings
   * @param os
   */
  virtual void show(std::ostream& os = std::cout) override;

  /**
   * Clear the key
   */
  virtual void clear() override;

 protected:
  /**
   * Utility function that creates a random number
   */
  unsigned randomNumber();

 private:
  // Convert a 128-bit HEX string into an array of 32-bit unsigned ints
  bool stringToUints(const std::string& str, uint32_t value[4]) const;

  // convert from an array of 32-bit unsigned ints into a hex string
  std::string uintsToString(uint32_t value[4]) const;

  void copyKey(uint32_t src[4], uint32_t dest[4]) const;

  void expand32(uint32_t src, uint32_t dest[4]) const;
  bool compress32(uint32_t src[4], uint32_t& dest) const;

 private:
  static IKey::KeyEncodeType mGlobalKeyType;
  static long mKeyInstanceCount;

 private:
  IKey::KeyEncodeType mKeyType;
  uint32_t mPrivateKey[4];
  uint32_t mLicenseKey[4];
  bool mKeySet;
  std::string mEncodedKey;
  std::shared_ptr<Crypt> mCrypt;
  mutable std::default_random_engine mRandGen;
  mutable std::uniform_int_distribution<unsigned> mRandBitDist;
};

} // namespace Mplane

#endif /* KEY_H_ */
