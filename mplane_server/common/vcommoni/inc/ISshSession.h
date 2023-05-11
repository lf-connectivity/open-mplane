/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISshSession.h
 * \brief     Simple libssh wrapper
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef VCOMMONI_INC_ISSHSESSION_H_
#define VCOMMONI_INC_ISSHSESSION_H_

#include <libssh/libssh.h>

#include <memory>
#include <string>
#include <vector>

namespace Mplane {

/*!
 * \class  ISshSession
 * \brief
 * \details
 *
 */
class ISshSession {
 public:
  ISshSession() {}
  virtual ~ISshSession() {}

  /**
   * Public key structure
   */
  struct PublicKey {

    PublicKey() : type(SSH_KEYTYPE_UNKNOWN), key("") {}
    PublicKey(ssh_keytypes_e _type, const std::string& _key)
        : type(_type), key(_key) {}

    ssh_keytypes_e type;
    std::string key;
  };

  /**
   * Disconnect session (freeing up resources)
   */
  virtual void disconnect() = 0;

  /**
   * Get the current SFTP user
   */
  virtual std::string user() const = 0;

  /**
   * Get the current SFTP host machine
   */
  virtual std::string host() const = 0;

  /**
   * Set debug level 0 - 4, 0 = no debug, 4 max debug
   */
  virtual void setDebug(unsigned level) = 0;

  /**
   * Set the port number to use (other than the default 22)
   */
  virtual void setPort(unsigned port) = 0;

  /**
   * Set the host machine name/ip
   * MANDATORY
   */
  virtual void setHost(const std::string& host) = 0;

  /**
   * Set the username to use
   * MANDATORY
   */
  virtual void setUser(const std::string& user) = 0;

  /**
   * Set the server public keys
   */
  virtual void setHostKeys(const std::vector<PublicKey>& keys) = 0;

  /**
   * Make the connection to the remote host
   * \return TRUE if successful; FALSE otherwise
   */
  virtual bool connect() = 0;

  /**
   * Is the session currently connected?
   */
  virtual bool isConnected() const = 0;

  /**
   * Set the password for user authentication.
   * Must use this or set an alternative user authentication method
   */
  virtual bool authenticatePassword(const std::string& password) = 0;

  /**
   * Set the key string for user authentication
   * this will most likely be a private key
   * Must use this or set an alternative user authentication method
   */
  virtual bool authenticateKey(const std::string& key) = 0;

  /**
   * Is the session currently user authenticated?
   */
  virtual bool isAuthenticated() const = 0;

  /**
   * get any errors and clear them
   */
  virtual std::string error() = 0;

  /**
   * Get the low-level ssh session pointer
   */
  virtual ssh_session session() const = 0;
};

} // namespace Mplane

#endif /* VCOMMONI_INC_ISSHSESSION_H_ */
