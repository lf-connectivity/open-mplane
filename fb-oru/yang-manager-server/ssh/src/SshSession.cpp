/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SshSession.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string.h>

#include "SshSession.h"

using namespace Mplane;

namespace {

	void keyHashPrint(const std::string& msg, ssh_key pubkey)
	{
		// convert key to hash
		unsigned char *hash(nullptr);
		size_t hlen;
		int rc = ssh_get_publickey_hash(pubkey, SSH_PUBLICKEY_HASH_SHA1, &hash, &hlen);
		if (rc < 0)
		{
			return;
		}

		char* hexa = ssh_get_hexa(hash, hlen);
		ssh_clean_pubkey_hash(&hash);
		std::string hexkey(hexa) ;
		ssh_string_free_char(hexa);

		std::cerr << msg << hexkey << std::endl ;
	}

}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

bool SshSession::mInitialised(false) ;

//-------------------------------------------------------------------------------------------------------------
SshSession::SshSession() :
	mUser(""),
	mHost(""),
	mServerPublicKeys(),
	mConnected(false),
	mAuthenticated(false),
	mSession(ssh_new()),
	mError(""),
	mHostKeyTypes("")
{
//	std::cerr << "NEW SshSession" << std::endl ;

	// Init libssh for threads
	if (!mInitialised)
	{
		ssh_init() ;
		mInitialised = true ;
	}
}

//-------------------------------------------------------------------------------------------------------------
SshSession::~SshSession()
{
//	std::cerr << "DEL SshSession" << std::endl ;
	disconnect() ;
}

//-------------------------------------------------------------------------------------------------------------
void SshSession::disconnect()
{
	if (!mSession)
	{
		mConnected = false ;
		mAuthenticated = false ;
		return ;
	}

	if (mConnected)
	{
//		std::cerr << "SshSession : ssh_disconnect" << std::endl ;
		ssh_disconnect(mSession);
		mConnected = false ;
		mAuthenticated = false ;
	}

//	std::cerr << "SshSession : ssh_free" << std::endl ;
	ssh_free(mSession) ;
	mSession = nullptr ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SshSession::user() const
{
	return mUser ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SshSession::host() const
{
	return mHost ;
}

//-------------------------------------------------------------------------------------------------------------
void SshSession::setDebug(unsigned level)
{
	if (level > SSH_LOG_FUNCTIONS)
		level = SSH_LOG_FUNCTIONS ;

    ssh_options_set(mSession, SSH_OPTIONS_LOG_VERBOSITY, &level);
}

//-------------------------------------------------------------------------------------------------------------
void SshSession::setPort(unsigned port)
{
	if (mConnected)
	{
		setError("Cannot change port of connected ssh session") ;
		return ;
	}
	ssh_options_set(mSession, SSH_OPTIONS_PORT, &port);
}

//-------------------------------------------------------------------------------------------------------------
void SshSession::setHost(const std::string &host)
{
	mHost = host ;
	ssh_options_set(mSession, SSH_OPTIONS_HOST, host.c_str());
}

//-------------------------------------------------------------------------------------------------------------
void SshSession::setUser(const std::string &user)
{
	mUser = user ;
	ssh_options_set(mSession, SSH_OPTIONS_USER, user.c_str());
}

//-------------------------------------------------------------------------------------------------------------
void SshSession::setHostKeyTypes(const std::string &typesList)
{
	mHostKeyTypes = typesList ;
	if (!mHostKeyTypes.empty())
		ssh_options_set(mSession, SSH_OPTIONS_HOSTKEYS, mHostKeyTypes.c_str());
}

//-------------------------------------------------------------------------------------------------------------
void SshSession::setHostKeys(const std::vector<ISshSession::PublicKey> &keys)
{
	mServerPublicKeys = keys ;
}


//-------------------------------------------------------------------------------------------------------------
bool SshSession::connect()
{
std::cerr << "SSH connect...." << std::endl ;
    int rc = ssh_connect(mSession);
    if (rc != SSH_OK)
    {
    	setError( ssh_get_error(mSession) ) ;
    	return false ;
    }

    if (!authenticateHost())
    {
    	return false ;
    }

std::cerr << "SSH Connected" << std::endl ;
    mConnected = true ;
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SshSession::isConnected() const
{
	return mConnected ;
}


//-------------------------------------------------------------------------------------------------------------
bool SshSession::authenticatePassword(const std::string &password)
{
	if (!mConnected)
	{
    	setError("Cannot authenticate unconnected SSH session") ;
    	return false ;
	}

    int rc = ssh_userauth_password(mSession, NULL, password.c_str());
    if (rc != SSH_AUTH_SUCCESS)
    {
    	setError(ssh_get_error(mSession)) ;
    	return false ;
    }

    mAuthenticated = true ;
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SshSession::authenticateKey(const std::string &privkey)
{
	if (!mConnected)
	{
    	setError("Cannot authenticate unconnected SSH session") ;
    	return false ;
	}

    ssh_key key(nullptr);
    int rc = ssh_pki_import_privkey_base64(privkey.c_str(), NULL, NULL, NULL, &key);
    if (rc != SSH_OK)
    {
//    	setError(ssh_get_error(mSession)) ;
    	setError("Unable to import BASE64 private key") ;
    	return false ;
    }

    rc = ssh_userauth_publickey(mSession, NULL, key);
    ssh_key_free(key);
    if (rc != SSH_AUTH_SUCCESS)
    {
    	setError(ssh_get_error(mSession)) ;
    	return false ;
    }

    mAuthenticated = true ;
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SshSession::isAuthenticated() const
{
	return mAuthenticated ;
}


//-------------------------------------------------------------------------------------------------------------
std::string SshSession::error()
{
	std::string tmp ;
	swap(mError, tmp) ;
	return tmp ;
}

//-------------------------------------------------------------------------------------------------------------
ssh_session SshSession::session() const
{
	return mSession ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void SshSession::setError(const std::string &error)
{
std::cerr << "SshSession::setError " << error << std::endl ;
	if (!mError.empty())
		mError += "\n" ;
	mError += error ;
}

//-------------------------------------------------------------------------------------------------------------
bool SshSession::authenticateHost()
{
	ssh_key srv_pubkey = nullptr;
	int rc = ssh_get_server_publickey(mSession, &srv_pubkey);
    if (rc < 0)
    {
    	setError("Unable to retrieve host public key") ;
        return false;
    }

    // DEBUG
    keyHashPrint("Server key: ", srv_pubkey) ;

    // Authenticate using set key(s)
    if (!mServerPublicKeys.empty())
    {
    	for (auto pkey : mServerPublicKeys)
    	{
    		ssh_key pubkey = nullptr;
    	    rc = ssh_pki_import_pubkey_base64( pkey.key.c_str(), pkey.type, &pubkey);
    	    if (rc < 0)
    	    {
    	    	std::cerr << "Failed to import public key: " << pkey.key << std::endl ;
    	    	continue ;
    	    }

    	    // DEBUG
    	    keyHashPrint("Stored key: ", pubkey) ;

    	    int cmp = ssh_key_cmp(srv_pubkey, pubkey, SSH_KEY_CMP_PUBLIC) ;
	        ssh_key_free(pubkey);
    	    if (cmp == 0)
    	    {
    	    	std::cerr << "* MATCHED public keys **" << std::endl ;
    	        ssh_key_free(srv_pubkey);
    	        return true ;
    	    }
    	}

        ssh_key_free(srv_pubkey);
    	setError("Host public keys do not match") ;
    	return false ;
    }

    ssh_key_free(srv_pubkey);

    // try authenticating using stored key
    enum ssh_known_hosts_e state = ssh_session_is_known_server(mSession);
    switch (state)
    {
        case SSH_KNOWN_HOSTS_OK:
std::cerr << "Known host OK" << std::endl ;
            /* OK */
            break;

        case SSH_KNOWN_HOSTS_CHANGED:
        	setError("Host key for server changed") ;
            return false;

        case SSH_KNOWN_HOSTS_OTHER:
        	setError("Host key for server not found but another type of key exists") ;
            return false;

        case SSH_KNOWN_HOSTS_NOT_FOUND:
            /* FALL THROUGH to SSH_SERVER_NOT_KNOWN behaviour */
        case SSH_KNOWN_HOSTS_UNKNOWN:
//            rc = ssh_session_update_known_hosts(mSession);
//            if (rc < 0)
//            {
//            	char buff[512] ;
//                setError(strerror_r(errno, buff, sizeof(buff)));
//                return false;
//            }
        	setError("Host key for server not found") ;
            return false ;

        case SSH_KNOWN_HOSTS_ERROR:
            setError(ssh_get_error(mSession));
            return false;
    }


    return true ;
}
