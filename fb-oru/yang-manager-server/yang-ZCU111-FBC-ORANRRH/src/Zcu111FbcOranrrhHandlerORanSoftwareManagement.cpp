/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanSoftwareManagement.cpp
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
#include <string>
#include <regex>

#include "stringfunc.hpp"
#include "Path.h"
#include "ILoggable.h"
#include "ISftpMgr.h"
#include "ISoftwareSlotMgr.h"

#include "XpathUtils.h"
#include "YangMgrServer.h"
#include "YangParamUtils.h"
#include "SysrepoUtils.h"
#include "YangUserAuth.h"

#include "Zcu111FbcOranrrhHandlerORanSoftwareManagement.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#ifdef OFF_TARGET
const std::string DIR_PREFIX("/tmp") ;
#else
const std::string DIR_PREFIX("") ;
#endif

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanSoftwareManagement::Zcu111FbcOranrrhHandlerORanSoftwareManagement(std::shared_ptr<IYangModuleMgr> moduleMgr) :
	YangHandlerSysrepo("o-ran-software-management", moduleMgr, "Zcu111FbcOranrrhHandlerORanSoftwareManagement"),
	mCallback(std::make_shared<CallbackORanSoftwareMgr>(path("software-inventory"))),
	mSoftwareDir(DIR_PREFIX + "/O-RAN/software")
{
	// ensure download directory is available
	Path::mkpath(mSoftwareDir) ;
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanSoftwareManagement::~Zcu111FbcOranrrhHandlerORanSoftwareManagement()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSoftwareManagement::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	// Register callbacks
	getItemsSubscribe(path("software-inventory"), mCallback);
	changeSubscribe() ;

	// register RPC callbacks
	REGISTER_RPC("software-download", Zcu111FbcOranrrhHandlerORanSoftwareManagement::rpcDownload) ;
	REGISTER_RPC("software-install", Zcu111FbcOranrrhHandlerORanSoftwareManagement::rpcInstall) ;
	REGISTER_RPC("software-activate", Zcu111FbcOranrrhHandlerORanSoftwareManagement::rpcActivate) ;

	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSoftwareManagement::rpcDownload(std::shared_ptr<sysrepo::Session> session,
		const std::string &rpcXpath,
		std::shared_ptr<YangParams> callList,
		std::shared_ptr<YangParams> retList)
{
	const unsigned downloadTimeout(60) ;

	const std::string rpc("software-download") ;
	std::map<std::string, std::shared_ptr<YangParam> > args(SysrepoUtils::paramsToMap(callList)) ;

//    +---x software-download
//    |  +---- input
//    |  |  +---w remote-file-path    ietf-inet-types:uri
//    |  |  +---w (credentials)?
//    |  |     +--:(password)
//    |  |     |  +---w password!
//    |  |     |  |  +---w password    string
//    |  |     |  +---w server
//    |  |     |     +---w keys* [algorithm]
//    |  |     |        +---w algorithm     ietf-crypto-types:asymmetric-key-algorithm-ref
//    |  |     |        +---w public-key?   binary
//    |  |     +--:(certificate)
//    |  |        +---w certificate!
//    |  +---- output
//    |     +--ro status                  enumeration
//    |     +--ro error-message?          string
//    |     +--ro notification-timeout?   int32 <30>


	std::string error ;
	std::string remotePath(YangParamUtils::toString(args["remote-file-path"], error)) ;
	std::string localPath(mSoftwareDir + "/" + Path::basename(remotePath)) ;

	std::string authData ;
	ISftpMgr::AuthenticationType authType(ISftpMgr::AUTH_NONE) ;
	std::vector<ISshSession::PublicKey> serverKeys ;
	if (!YangUserAuth::authParams(callList, authData, authType, serverKeys))
	{
		statusFail(rpc, retList, "Failed to get authentication parameters") ;
		return true ;
	}

	if (authType == ISftpMgr::AUTH_NONE)
	{
		statusFail(rpc, retList, "No supported authorisation method provided") ;
		return true ;
	}

	// Ok now to create an sftp session
	std::shared_ptr<ISftpSession> sftp(ISftpMgr::factory(remotePath, authData, authType, serverKeys, error)) ;
	if (!sftp)
	{
		statusFail(rpc, retList, error) ;
		return true ;
	}

	// Set up completion callback
	auto complete = [this](const std::string& remoteFile, const std::string& localFile,
			ISftpSession::SftpTransaction transaction, const std::string& error, bool timedOut){

		// Transfer complete so send notification
		//	    +---n download-event
		//	    |  +--ro file-name        string
		//	    |  +--ro status?          enumeration
		//	    |  +--ro error-message?   string
		const std::string notifPath( path("download-event") ) ;

		std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;


		params->addParam(localFile, notifPath + "/file-name") ;

		if (error.empty())
		{
			params->addParam("COMPLETED", notifPath + "/status") ;
		}
		else if (timedOut)
		{
			params->addParam("TIMEOUT", notifPath + "/status") ;
			params->addParam(error, notifPath + "/error-message") ;
		}
		else
		{
			params->addParam("PROTOCOL_ERROR", notifPath + "/status") ;
			params->addParam(error, notifPath + "/error-message") ;
		}
		sendNotification(notifPath, params) ;
	} ;

	// do transfer
	if (!sftp->fileDownload(remotePath, localPath, complete, downloadTimeout))
	{
		statusFail(rpc, retList, sftp->error()) ;
		return true ;
	}

	// scheduled ok
	statusOk(rpc, retList) ;
	retList->addParam(std::to_string(downloadTimeout), path(rpc + "/notification-timeout")) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSoftwareManagement::rpcInstall(std::shared_ptr<sysrepo::Session> session,
		const std::string &rpcXpath,
		std::shared_ptr<YangParams> callList,
		std::shared_ptr<YangParams> retList)
{
	const std::string rpc("software-install") ;
	std::map<std::string, std::shared_ptr<YangParam> > args(SysrepoUtils::paramsToMap(callList)) ;

	//    +---x software-install
	//    |  +---- input
	//    |  |  +---w slot-name     -> /software-inventory/software-slot/name
	//    |  |  +---w file-names*   string
	//    |  +---- output
	//    |     +--ro status           enumeration
	//    |     +--ro error-message?   string

	std::string error ;
	std::string slotName(YangParamUtils::toString(args["slot-name"], error)) ;

	std::vector<std::string> files ;
	for (unsigned i=0; i < callList->getNumParams(); ++i)
	{
		std::shared_ptr<YangParam> p(callList->getParam(i)) ;
		std::string leaf(XpathUtils::leafName(p->name())) ;
		if ( !startsWith(leaf, "file-names") )
			continue ;

		// make sure the file uses the download area
		std::string file( YangParamUtils::toString(p, error) ) ;
		file = mSoftwareDir + "/" + Path::basename(file) ;
		files.push_back(file) ;
	}


	// Set up completion callback
	auto complete = [this](const std::string& slotName, ISoftwareSlotMgr::InstallStatus status, const std::string& error){

		// Transfer complete so send notification
		//	    +---n install-event
		//	    |  +--ro slot-name?       -> /software-inventory/software-slot/name
		//	    |  +--ro status?          enumeration
		//	    |  +--ro error-message?   string
		const std::string notifPath( path("install-event") ) ;

		std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;
		params->addParam(slotName, notifPath + "/slot-name") ;
		params->addParam(ISoftwareSlotMgr::installStatusString(status), notifPath + "/status") ;

		if (!error.empty())
		{
			params->addParam(error, notifPath + "/error-message") ;
		}
		sendNotification(notifPath, params) ;
	} ;


	// Do the install
	std::shared_ptr<ISoftwareSlotMgr> mgr(ISoftwareSlotMgr::singleton()) ;
	if (!mgr->install(slotName, files, complete, error))
	{
		statusFail(rpc, retList, error) ;
		return true ;
	}


	// scheduled ok
	statusOk(rpc, retList) ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSoftwareManagement::rpcActivate(std::shared_ptr<sysrepo::Session> session,
		const std::string &rpcXpath,
		std::shared_ptr<YangParams> callList,
		std::shared_ptr<YangParams> retList)
{
	const std::string rpc("software-activate") ;
	std::map<std::string, std::shared_ptr<YangParam> > args(SysrepoUtils::paramsToMap(callList)) ;

//    +---x software-activate
//       +---- input
//       |  +---w slot-name    -> /software-inventory/software-slot/name
//       +---- output
//          +--ro status                  enumeration
//          +--ro error-message?          string
//          +--ro notification-timeout?   int32 <30>

	std::string error ;
	std::string slotName(YangParamUtils::toString(args["slot-name"], error)) ;

	// Set up completion callback
	auto complete = [this](const std::string& slotName, ISoftwareSlotMgr::ActivateStatus status, unsigned returnCode, const std::string& error){

		// Transfer complete so send notification
		//	    +---n activation-event
		//	       +--ro slot-name?       -> /software-inventory/software-slot/name
		//	       +--ro status?          enumeration
		//	       +--ro return-code?     uint8
		//	       +--ro error-message?   string
		const std::string notifPath( path("activation-event") ) ;

		std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;
		params->addParam(slotName, notifPath + "/slot-name") ;
		params->addParam(std::to_string(returnCode), notifPath + "/return-code") ;
		params->addParam(ISoftwareSlotMgr::activateStatusString(status), notifPath + "/status") ;

		if (!error.empty())
		{
			params->addParam(error, notifPath + "/error-message") ;
		}
		sendNotification(notifPath, params) ;
	} ;


	// Do the activation
	unsigned requiredTimeoutSecs ;
	std::shared_ptr<ISoftwareSlotMgr> mgr(ISoftwareSlotMgr::singleton()) ;
	if (!mgr->activate(slotName, requiredTimeoutSecs, complete, error))
	{
		statusFail(rpc, retList, error) ;
		return true ;
	}



	// scheduled ok
	statusOk(rpc, retList) ;
	retList->addParam(requiredTimeoutSecs, path(rpc + "/notification-timeout")) ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanSoftwareManagement::statusOk(const std::string& rpc, std::shared_ptr<YangParams> retList)
{
	retList->addParam("STARTED", path(rpc + "/status")) ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanSoftwareManagement::statusFail(const std::string& rpc, std::shared_ptr<YangParams> retList,
		const std::string &reason, const std::string& status)
{
	retList->addParam(status, path(rpc + "/status")) ;
	retList->addParam(reason, path(rpc + "/error-message")) ;
}
