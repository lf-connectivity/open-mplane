/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SftpMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <set>

#include "SftpPath.h"
#include "SftpSession.h"
#include "SshSession.h"

#include "SftpMgr.h"

using namespace Mplane;

//=============================================================================================================
// Session struct
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
struct SftpMgr::Session {
  Session(std::shared_ptr<SshSession> ssh, std::shared_ptr<SftpSession> sftp)
      : mSsh(ssh), mSftp(sftp) {}

  void
  disconnect() {
    mSftp->disconnect();
    mSsh->disconnect();
  }

  void
  clear() {
    mSftp.reset();
    mSsh.reset();
  }

  std::shared_ptr<SshSession> mSsh;
  std::shared_ptr<SftpSession> mSftp;
};

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISftpMgr>
ISftpMgr::singleton() {
  static std::shared_ptr<ISftpMgr> instance(std::make_shared<SftpMgr>());
  return instance;
}

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISftpSession>
ISftpMgr::factory(
    const std::string& host,
    const std::string& user,
    const std::string& authData,
    AuthenticationType auth,
    const std::vector<ISshSession::PublicKey>& serverKeys,
    std::string& error) {
  std::shared_ptr<SftpMgr> mgr(
      std::dynamic_pointer_cast<SftpMgr>(ISftpMgr::singleton()));
  return mgr->factoryCreate(host, user, authData, auth, serverKeys, error);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISftpSession>
ISftpMgr::factory(
    const std::string& remotePath,
    const std::string& authData,
    AuthenticationType auth,
    const std::vector<ISshSession::PublicKey>& serverKeys,
    std::string& error) {
  std::shared_ptr<SftpMgr> mgr(
      std::dynamic_pointer_cast<SftpMgr>(ISftpMgr::singleton()));
  return mgr->factoryCreate(remotePath, authData, auth, serverKeys, error);
}

//-------------------------------------------------------------------------------------------------------------
void
ISftpMgr::setDebug(unsigned level) {
  std::shared_ptr<SftpMgr> mgr(
      std::dynamic_pointer_cast<SftpMgr>(ISftpMgr::singleton()));
  mgr->setDebugLevel(level);
}

//-------------------------------------------------------------------------------------------------------------
void
ISftpMgr::disconnect(std::shared_ptr<ISftpSession>& session) {
  std::shared_ptr<SftpMgr> mgr(
      std::dynamic_pointer_cast<SftpMgr>(ISftpMgr::singleton()));
  mgr->disconnectSession(session);
}

//-------------------------------------------------------------------------------------------------------------
void
ISftpMgr::disconnect() {
  std::shared_ptr<SftpMgr> mgr(
      std::dynamic_pointer_cast<SftpMgr>(ISftpMgr::singleton()));
  mgr->disconnectAll();
}

//-------------------------------------------------------------------------------------------------------------
void
ISftpMgr::hostKeyTypes(const std::string& typesList) {
  std::shared_ptr<SftpMgr> mgr(
      std::dynamic_pointer_cast<SftpMgr>(ISftpMgr::singleton()));
  mgr->setHostKeyTypes(typesList);
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SftpMgr::SftpMgr() : mSessions(), mDebug(0), mHostKeyTypes("") {}

//-------------------------------------------------------------------------------------------------------------
SftpMgr::~SftpMgr() {
  // disconnect from all
  for (auto entry : mSessions) {
    entry.second->mSftp->disconnect();
    entry.second->mSsh->disconnect();
    entry.second->clear();
  }
}

//-------------------------------------------------------------------------------------------------------------
void
SftpMgr::setDebugLevel(unsigned level) {
  mDebug = level;
  for (auto entry : mSessions) {
    entry.second->mSftp->setDebug(level);
  }
}

//-------------------------------------------------------------------------------------------------------------
void
SftpMgr::disconnectSession(std::shared_ptr<ISftpSession>& sftp) {
  // std::cerr << "SftpMgr::disconnectSession count=" << sftp.use_count() <<
  // std::endl ;

  // See how many users of this pointer there are. If there are only 2 (i.e. the
  // caller and this) then we are safe to shut down the connection
  if (sftp.use_count() > 2)
    return;

  // get the session
  std::string key(sftp->user() + "@" + sftp->host());
  if (mSessions.find(key) == mSessions.end())
    return;

  // shut down the connections
  auto session(mSessions[key]);
  session->disconnect();
  session->clear();
  mSessions.erase(key);

  sftp.reset();
}

//-------------------------------------------------------------------------------------------------------------
void
SftpMgr::disconnectAll() {
  for (auto entry : mSessions) {
    entry.second->disconnect();
    entry.second->clear();
  }

  mSessions.clear();
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISftpSession>
SftpMgr::factoryCreate(
    const std::string& host,
    const std::string& user,
    const std::string& authData,
    ISftpMgr::AuthenticationType auth,
    const std::vector<ISshSession::PublicKey>& serverKeys,
    std::string& error) {
  // combine user & host into a string to use as the hash key
  std::string key(user + "@" + host);

  // check existing sessions
  if (mSessions.find(key) != mSessions.end()) {
    // get the session
    auto session(mSessions[key]);
    return session->mSftp;
  }

  // Create a new entry

  // 1. Create ssh session
  std::shared_ptr<SshSession> ssh(std::make_shared<SshSession>());
  ssh->setHost(host);
  ssh->setUser(user);
  ssh->setHostKeys(serverKeys);
  ssh->setDebug(mDebug);

  // If we have server keys specified then use them to determine the valid list
  // of server key types we will accept
  if (!serverKeys.empty()) {
    std::set<std::string> types;
    for (auto key : serverKeys) {
      std::string type;
      switch (key.type) {
        case SSH_KEYTYPE_DSS:
          type = "ssh-dss";
          break;

        case SSH_KEYTYPE_RSA:
          type = "ssh-rsa";
          break;

        case SSH_KEYTYPE_ED25519:
          type = "ssh-ed25519";
          break;

        case SSH_KEYTYPE_DSS_CERT01:
          type = "ssh-dss-cert-v01@openssh.com";
          break;

        case SSH_KEYTYPE_RSA_CERT01:
          type = "ssh-rsa-cert-v01@openssh.com";
          break;

        case SSH_KEYTYPE_ECDSA_P256:
          type = "ecdsa-sha2-nistp256";
          break;

        case SSH_KEYTYPE_ECDSA_P384:
          type = "ecdsa-sha2-nistp384";
          break;

        case SSH_KEYTYPE_ECDSA_P521:
          type = "ecdsa-sha2-nistp521";
          break;

        case SSH_KEYTYPE_ECDSA_P256_CERT01:
          type = "ecdsa-sha2-nistp256-cert-v01@openssh.com";
          break;

        case SSH_KEYTYPE_ECDSA_P384_CERT01:
          type = "ecdsa-sha2-nistp384-cert-v01@openssh.com";
          break;

        case SSH_KEYTYPE_ECDSA_P521_CERT01:
          type = "ecdsa-sha2-nistp521-cert-v01@openssh.com";
          break;

        case SSH_KEYTYPE_ED25519_CERT01:
          type = "ssh-ed25519-cert-v01@openssh.com";
          break;

        case SSH_KEYTYPE_RSA1:
        case SSH_KEYTYPE_ECDSA:
        case SSH_KEYTYPE_UNKNOWN:
        default:
          break;
      }

      if (type.empty())
        continue;

      types.insert(type);
    }
    std::string keyTypes;
    for (auto type : types) {
      if (!keyTypes.empty())
        keyTypes += ",";
      keyTypes += type;
    }
    ssh->setHostKeyTypes(keyTypes);
  } else {
    if (!mHostKeyTypes.empty())
      ssh->setHostKeyTypes(mHostKeyTypes);
  }

  if (!ssh->connect()) {
    error = ssh->error();
    return std::shared_ptr<ISftpSession>();
  }

  // Use one of these alternatives:
  bool ok;
  if (auth == ISftpMgr::AUTH_PASSWORD) {
    ok = ssh->authenticatePassword(authData);
  } else if (auth == ISftpMgr::AUTH_RSA_KEY) {
    ok = ssh->authenticateKey(authData);
  } else {
    error = "Unsupported authentication type";
    return std::shared_ptr<ISftpSession>();
  }

  if (!ok) {
    error = ssh->error();
    return std::shared_ptr<ISftpSession>();
  }

  // 2. Now create SFTP
  std::shared_ptr<SftpSession> sftp(std::make_shared<SftpSession>(ssh));
  if (!sftp->isConnected()) {
    error = sftp->error();
    return std::shared_ptr<ISftpSession>();
  }

  // Add to cache
  mSessions[key] = std::make_shared<Session>(ssh, sftp);

  return sftp;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISftpSession>
SftpMgr::factoryCreate(
    const std::string& remotePath,
    const std::string& authData,
    AuthenticationType auth,
    const std::vector<ISshSession::PublicKey>& serverKeys,
    std::string& error) {
  SftpPath sp(remotePath);
  if (!sp.isValid()) {
    error = sp.error();
    return std::shared_ptr<ISftpSession>();
  }

  return factoryCreate(sp.host(), sp.user(), authData, auth, serverKeys, error);
}

//-------------------------------------------------------------------------------------------------------------
void
SftpMgr::setHostKeyTypes(const std::string& typesList) {
  mHostKeyTypes = typesList;
}
