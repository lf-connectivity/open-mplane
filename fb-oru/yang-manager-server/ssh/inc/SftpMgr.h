/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SftpMgr.h
 * \brief     Manager of multiple SFTP sessions
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef SSH_INC_SFTPMGR_H_
#define SSH_INC_SFTPMGR_H_

#include <map>
#include <string>
#include <memory>

#include "ISftpMgr.h"

namespace Mplane {

/*!
 * \class  SftpMgr
 * \brief
 * \details
 *
 */
class SftpMgr : public virtual ISftpMgr {
public:
	SftpMgr() ;
	virtual ~SftpMgr() ;


	/**
	 * Set debug
	 */
	virtual void setDebugLevel(unsigned level) ;

	/**
	 * User has finished with the session. If no other users are using this session then it will be
	 * closed down
	 */
	virtual void disconnectSession(std::shared_ptr<ISftpSession>& session) ;

	/**
	 * User has finished with all sessions. Shuts down all sessions.
	 */
	virtual void disconnectAll() ;

	/**
	 * Set the preferred server host key types (comma-separated list). Types must be SSH key types
	 * example: "ssh-rsa,ssh-dss,ecdh-sha2-nistp256"
	 */
	virtual void setHostKeyTypes(const std::string& typesList) ;

	/**
	 * Factory method on singleton
	 */
	virtual std::shared_ptr<ISftpSession> factoryCreate(const std::string& host, const std::string& user,
			const std::string& authData, AuthenticationType auth,
			const std::vector<ISshSession::PublicKey>& serverKeys,
			std::string& error) ;

	/**
	 * Factory method on singleton
	 */
	virtual std::shared_ptr<ISftpSession> factoryCreate(const std::string& remotePath,
			const std::string& authData, AuthenticationType auth,
			const std::vector<ISshSession::PublicKey>& serverKeys,
			std::string& error) ;


private:
	class Session ;
	std::map<std::string, std::shared_ptr<Session>> mSessions ;
	unsigned mDebug ;
	std::string mHostKeyTypes ;
} ;

}

#endif /* SSH_INC_SFTPMGR_H_ */
