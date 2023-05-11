/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISftpMgr.h
 * \brief     Virtual API for a manager singleton for SFTP sessions
 *
 *
 * \details   Manages all ISftpSession objects, reusing them where possible
 *
 */

#ifndef VCOMMONI_INC_ISFTPMGR_H_
#define VCOMMONI_INC_ISFTPMGR_H_

#include <memory>
#include <string>

#include "ISftpSession.h"
#include "ISshSession.h"

namespace Mplane {

/*!
 * \class  ISftpMgr
 * \brief
 * \details
 *
 */
class ISftpMgr {
 public:
  ISftpMgr() {}
  virtual ~ISftpMgr() {}

  /**
   * Singleton
   */
  static std::shared_ptr<ISftpMgr> singleton();

  enum AuthenticationType {
    AUTH_NONE,
    AUTH_PASSWORD,
    AUTH_RSA_KEY,
    AUTH_CERTIFICATE,
  };

  /**
   * Factory for creating SFTP sessions. May return null pointer
   * @param host    - host machine
   * @param user    - user name
   * @param authData    - string to contain password/key/certificate etc
   * @param auth  - indication of what the pass string contains i.e. how to
   * authenticate
   * @param error - set to an error string if unable to create session
   */
  static std::shared_ptr<ISftpSession> factory(
      const std::string& host,
      const std::string& user,
      const std::string& authData,
      ISftpMgr::AuthenticationType auth,
      const std::vector<ISshSession::PublicKey>& serverKeys,
      std::string& error);

  /**
   * Factory for creating SFTP sessions. May return null pointer
   * @param remotePath    - Remote file path of the form:
   * sftp://<username>@<host>[:port]/path
   * @param authData    - string to contain password/key/certificate etc
   * @param auth  - indication of what the pass string contains i.e. how to
   * authenticate
   * @param error - set to an error string if unable to create session
   */
  static std::shared_ptr<ISftpSession> factory(
      const std::string& remotePath,
      const std::string& authData,
      ISftpMgr::AuthenticationType auth,
      const std::vector<ISshSession::PublicKey>& serverKeys,
      std::string& error);

  /**
   * Set global debug level for all instances
   */
  static void setDebug(unsigned level);

  /**
   * User has finished with the session. If no other users are using this
   * session then it will be closed down
   */
  static void disconnect(std::shared_ptr<ISftpSession>& session);

  /**
   * Disconnect all sessions
   */
  static void disconnect();

  /**
   * Set the preferred server host key types (comma-separated list). Types must
   * be SSH key types example: "ssh-rsa,ssh-dss,ecdh-sha2-nistp256"
   */
  static void hostKeyTypes(const std::string& typesList);
};

} // namespace Mplane

#endif /* VCOMMONI_INC_ISFTPMGR_H_ */
