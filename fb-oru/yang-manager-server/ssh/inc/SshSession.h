/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SshSession.h
 * \brief     Simple libssh wrapper
 *
 *
 * \details   Simplified libssh C++ wrapper revealing only the API we need for ORAN sftp transfer
 *
 * 			Connection sequence to create an ssh session as "user" on machine "host" is:
 *
 * 			SshSession ssh ;
 * 			ssh.setHost(host) ;
 * 			ssh.setUser(user) ;
 * 			if (!ssh.connect())
 * 				return ssh.error() ;
 *
 * 			// Use one of these alternatives:
 * 			bool ok;
 * 			ok = ssh.authenticatePassword(password) ;
 * 			// or
 * 			ok = ssh.authenticateKey(privateKeyString) ;
 *
 * 			if (!ok)
 * 				return ssh.error() ;
 *
 */


#ifndef SSH_INC_SSHSESSION_H_
#define SSH_INC_SSHSESSION_H_

#include <libssh/libssh.h>

#include <string>
#include <memory>
#include <vector>

#include "ISshSession.h"

namespace Mplane {

/*!
 * \class  SshSession
 * \brief
 * \details
 *
 */
class SshSession : public virtual ISshSession {
public:
	SshSession() ;
	virtual ~SshSession() ;

	/**
	 * Disconnect session (freeing up resources)
	 */
	void disconnect() override ;

	/**
	 * Get the current SFTP user
	 */
	std::string user() const override ;

	/**
	 * Get the current SFTP host machine
	 */
	std::string host() const override ;


	/**
	 * Set debug level 0 - 4, 0 = no debug, 4 max debug
	 */
	void setDebug(unsigned level) override ;

	/**
	 * Set the port number to use (other than the default 22)
	 */
	void setPort(unsigned port) override ;

	/**
	 * Set the host machine name/ip
	 * MANDATORY
	 */
	void setHost(const std::string& host) override ;

	/**
	 * Set the username to use
	 * MANDATORY
	 */
	void setUser(const std::string& user) override ;

	/**
	 * Set the preferred server host key types (comma-separated list). Types must be SSH key types
	 * example: "ssh-rsa,ssh-dss,ecdh-sha2-nistp256"
	 */
	void setHostKeyTypes(const std::string& typesList) ;

	/**
	 * Set the server public keys
	 */
	virtual void setHostKeys(const std::vector<ISshSession::PublicKey>& keys) override ;

	/**
	 * Make the connection to the remote host
	 * \return TRUE if successful; FALSE otherwise
	 */
	bool connect() override ;

	/**
	 * Is the session currently connected?
	 */
	bool isConnected() const override ;


	/**
	 * Set the password for user authentication.
	 * Must use this or set an alternative user authentication method
	 */
	bool authenticatePassword(const std::string& password) override ;

	/**
	 * Set the key string for user authentication
	 * this will most likely be a private key
	 * Must use this or set an alternative user authentication method
	 */
	bool authenticateKey(const std::string& key) override ;

	/**
	 * Is the session currently user authenticated?
	 */
	bool isAuthenticated() const override ;


	/**
	 * get any errors and clear them
	 */
	std::string error() override ;


	/**
	 * Get the low-level ssh session pointer
	 */
	ssh_session session() const override ;


private:
	void setError(const std::string& error) ;
	bool authenticateHost() ;

private:
	std::string mUser ;
	std::string mHost ;
	std::vector<ISshSession::PublicKey> mServerPublicKeys ;
	bool mConnected ;
	bool mAuthenticated ;
	ssh_session mSession ;
	std::string mError ;
	std::string mHostKeyTypes ;

	static bool mInitialised ;
} ;

}

#endif /* SSH_INC_SSHSESSION_H_ */
