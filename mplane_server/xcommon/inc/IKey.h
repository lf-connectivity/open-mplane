/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IKey.h
 * \brief     Virtual interface to license key
 *
 *
 * \details
 *
 */

#ifndef IKEY_H_
#define IKEY_H_

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Mplane {

class IKey {
 public:
  IKey() {}
  virtual ~IKey() {}

  /**
   * This enum type sets the replication factor of the 32 bits
   */
  enum class KeyEncodeType {
    KEY_DUP4 = -1, //!< KEY_DUP4
    KEY_DUP3 = 0, //!< KEY_DUP3
    KEY_DUP2 = 1, //!< KEY_DUP2
    KEY_DUP1 = 2, //!< KEY_DUP1
  };

  /**
   * Set the replication factor for any keys created after this call
   */
  static void setKeyEncodeType(KeyEncodeType type);

  /**
   * Factory for making key objects
   */
  static std::shared_ptr<IKey> factory();

  /**
   * Factory for making key objects using the board serial number, hostid, and
   * the GUI hostid.
   */
  static std::shared_ptr<IKey> factory(
      const std::string& serialNum,
      const std::string& hostid,
      const std::string& ctrlHostid);

  /**
   * Get the application-specific singleton. This will be provided by the
   * embedded application (normally within a wrapper that stores the information
   * to flash)
   */
  static std::shared_ptr<IKey> getApplicationInstance();

  /**
   * Get the global singleton. This will be provided by the embedded application
   * (normally within a wrapper that stores the information to flash). The
   * global key uses a hard-coded public key string that is shared among all
   * applications
   */
  static std::shared_ptr<IKey> getGlobalInstance();

  /**
   * Set the license key from a hex string
   * @param licenseKey
   * @return true if valid 128bit hex value string; false otherwise
   */
  virtual bool setLicenseKey(const std::string& licenseKey) = 0;

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
      const std::string& ctrlHostid) = 0;

  /**
   * Set the license key from any collection information strings.
   * @param info
   * @return true if set the license ok; false otherwise
   */
  virtual bool setLicenseKey(const std::vector<std::string>& info) = 0;

  /**
   * Get the key in an encoded form suitable for sharing with other applications
   * @return
   */
  virtual std::string encodedKey() = 0;

  /**
   * Use an encoded key string to set the license key
   * @param encodedKey
   * @return true if key set; false otherwise
   */
  virtual bool setFromEncodedKey(const std::string& encodedKey) = 0;

  /**
   * Get the license key as an array suitable for using with Crypt
   * @return the license key value
   */
  virtual std::vector<uint32_t> licenseKey() const = 0;

  /**
   * Is the license key currently set?
   */
  virtual bool isSet() const = 0;

  /**
   * Takes in 32-bits, expands the value to 128-bits, then encodes that value
   * and returns a hex string
   * @param bits
   * @return hex string
   */
  virtual std::string encode32bits(uint32_t bits) const = 0;

  /**
   * Takes in the 128-bit hex string and decodes back to 32 bits
   * @param encoded32bits
   * @param decoded32bits
   * @return true if decoded correctly; false if the string is invalid
   */
  virtual bool decode32bits(
      const std::string& encoded32bits, uint32_t& decoded32bits) const = 0;

  /**
   * Show current settings
   * @param os
   */
  virtual void show(std::ostream& os = std::cout) = 0;

  /**
   * Clear the key
   */
  virtual void clear() = 0;
};

} // namespace Mplane

#endif /* IKEY_H_ */
