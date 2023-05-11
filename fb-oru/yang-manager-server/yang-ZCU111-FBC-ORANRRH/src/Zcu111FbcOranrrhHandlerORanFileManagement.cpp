/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanFileManagement.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>
//#include "RadioDatastoreSysrepo.h"

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <regex>

#include "stringfunc.hpp"
#include "Path.h"
#include "ILoggable.h"
#include "ISftpMgr.h"
#include "ITroubleshootMgr.h"
#include "ITraceMgr.h"

#include "XpathUtils.h"
#include "YangMgrServer.h"
#include "YangParamUtils.h"
#include "SysrepoUtils.h"
#include "YangUserAuth.h"

#include "Zcu111FbcOranrrhHandlerORanFileManagement.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#ifdef OFF_TARGET
const std::string Zcu111FbcOranrrhHandlerORanFileManagement::mDirPrefix("/tmp") ;
#else
const std::string Zcu111FbcOranrrhHandlerORanFileManagement::mDirPrefix("") ;
#endif

const std::string Zcu111FbcOranrrhHandlerORanFileManagement::mOranLogFolder("/O-RAN/log") ;
const std::string Zcu111FbcOranrrhHandlerORanFileManagement::mOranPMFolder("/O-RAN/PM") ;
const std::string Zcu111FbcOranrrhHandlerORanFileManagement::mOranTransceiverFolder("/O-RAN/transceiver") ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanFileManagement::Zcu111FbcOranrrhHandlerORanFileManagement(std::shared_ptr<IYangModuleMgr> moduleMgr) :
	YangHandlerSysrepo("o-ran-file-management", moduleMgr, "Zcu111FbcOranrrhHandlerORanFileManagement")
{
	// ensure standard directories are available
	Path::mkpath(mDirPrefix + mOranLogFolder) ;
	Path::mkpath(mDirPrefix + mOranPMFolder) ;
	Path::mkpath(mDirPrefix + mOranTransceiverFolder) ;
//	Path::mkpath(DIR_PREFIX + "/O-RAN/beamforming") ;

	ITroubleshootMgr::singleton()->setDir(mDirPrefix + mOranLogFolder) ;
	ITraceMgr::singleton()->setDir(mDirPrefix + mOranLogFolder) ;
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanFileManagement::~Zcu111FbcOranrrhHandlerORanFileManagement()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanFileManagement::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	// register RPC callbacks
	REGISTER_RPC("file-upload", Zcu111FbcOranrrhHandlerORanFileManagement::rpcFileUpload) ;
	REGISTER_RPC("file-download", Zcu111FbcOranrrhHandlerORanFileManagement::rpcFileDownload) ;
	REGISTER_RPC("retrieve-file-list", Zcu111FbcOranrrhHandlerORanFileManagement::rpcFileList) ;

	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanFileManagement::rpcFileUpload(std::shared_ptr<sysrepo::Session> session,
		const std::string& rpcXpath,
		std::shared_ptr<YangParams> callList,
		std::shared_ptr<YangParams> retList)
{
	return handleFileTransfer(true, callList, retList) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanFileManagement::rpcFileDownload(std::shared_ptr<sysrepo::Session> session,
		const std::string &rpcXpath,
		std::shared_ptr<YangParams> callList,
		std::shared_ptr<YangParams> retList)
{
	return handleFileTransfer(false, callList, retList) ;
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanFileManagement::handleFileTransfer(
		bool upload, std::shared_ptr<YangParams> callList,
		std::shared_ptr<YangParams> retList)
{
	const std::string rpc(upload ? "file-upload" : "file-download") ;
	std::map<std::string, std::shared_ptr<YangParam> > args(SysrepoUtils::paramsToMap(callList)) ;

	std::string error ;
	std::string localPath(YangParamUtils::toString(args["local-logical-file-path"], error)) ;
	std::string remotePath(YangParamUtils::toString(args["remote-file-path"], error)) ;


	std::string authData ;
	ISftpMgr::AuthenticationType authType(ISftpMgr::AUTH_NONE) ;
	std::vector<ISshSession::PublicKey> serverKeys ;
	if (!YangUserAuth::authParams(callList, authData, authType, serverKeys))
	{
		statusFail(rpc, retList, "Failed to get authentication parameters") ;
		return true ;
	}


//	for (auto entry : args)
//		std::cerr << "ARGS: " << entry.first << " = " << YangParamUtils::toString(entry.second, error) << std::endl ;

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

	// Schedule the file upload
	auto complete = [this, upload](const std::string& remoteFile, const std::string& localFile,
			ISftpSession::SftpTransaction transaction, const std::string& error, bool timedOut){

		// Transfer complete so send notification
		//	    +---n file-upload-notification
		//	    |  +--ro local-logical-file-path    string
		//	    |  +--ro remote-file-path           string
		//	    |  +--ro status?                    enumeration
		//	    |  +--ro reject-reason?             string
		const std::string notifPath( path(upload ? "file-upload-notification" : "file-download-event") ) ;

		std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;


		params->addParam(localFile, notifPath + "/local-logical-file-path") ;
		params->addParam(remoteFile, notifPath + "/remote-file-path") ;

		if (error.empty())
		{
			params->addParam("SUCCESS", notifPath + "/status") ;
		}
		else
		{
			params->addParam("FAILURE", notifPath + "/status") ;
			params->addParam(error, notifPath + "/reject-reason") ;
		}
		sendNotification(notifPath, params) ;
	} ;

	// do transfer
	if (upload)
	{
		if (!sftp->fileUpload(remotePath, localPath, complete))
		{
			statusFail(rpc, retList, sftp->error()) ;
			return true ;
		}
	}
	else
	{
		if (!sftp->fileDownload(remotePath, localPath, complete))
		{
			statusFail(rpc, retList, sftp->error()) ;
			return true ;
		}
	}

	// scheduled ok
	statusOk(rpc, retList) ;
	return true ;
}



//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanFileManagement::rpcFileList(std::shared_ptr<sysrepo::Session> session,
		const std::string &rpcXpath,
		std::shared_ptr<YangParams> callList,
		std::shared_ptr<YangParams> retList)
{
	const std::string rpc("retrieve-file-list") ;
	std::map<std::string, std::shared_ptr<YangParam> > args(SysrepoUtils::paramsToMap(callList)) ;

	std::string error ;
	std::string logicalPath(YangParamUtils::toString(args["logical-path"], error)) ;
	std::string filter ;
	if (args.find("file-name-filter") != args.end())
	{
		filter = YangParamUtils::toString(args["file-name-filter"], error) ;
	}

	// check path, ensure directory exists
	if ( !startsWith(logicalPath, "/O-RAN") )
	{
		statusFail(rpc, retList, "Can only access /O-RAN directory and sub-directories") ;
		return true ;
	}

	// We only accept wildcard '*' in the filename part
	std::string dir(Path::dir(logicalPath)) ;
	if (dir.find('*') != std::string::npos)
	{
		statusFail(rpc, retList, "Wildcards not accepted in directory name") ;
		return true ;
	}

	dir = mDirPrefix + dir ;
	if (!Path::exists(dir))
	{
		statusFail(rpc, retList, "Invalid directory") ;
		return true ;
	}

	// If a filename is given then it's used as a file filter (in addition to any actual filter provided)
	std::string filespec(Path::basename(logicalPath)) ;
	std::vector<std::string> filters ;
	if (!filespec.empty())
		filters.push_back(filespec) ;
	if (!filter.empty())
		filters.push_back(filter) ;

	// Get the directory contents
	std::vector<std::string> contents(Path::dirContents(dir)) ;

	// contents will contain full path. Strip out directories first
	std::vector<std::string> filtered ;
	for (auto f : contents)
	{
		if (Path::isDir(f))
			continue ;

		// strip off directory
		filtered.push_back(f.substr(dir.size())) ;
	}

	// now run the filter
	for (auto filter : filters)
	{
		contents = filtered ;
		filtered.clear() ;

		filter = replaceStrs(filter, "*", ".*") ;
		std::regex regexp(filter) ;

		for (auto f : contents)
		{
			if (!std::regex_search(f, regexp))
				continue ;

			filtered.push_back(f) ;
		}
	}

	// return the filtered filenames
	std::string fileList(path(rpc + "/file-list")) ;
	for (auto f : filtered)
	{
		retList->addParam(f, fileList) ;
	}
	statusOk(rpc, retList) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanFileManagement::statusOk(const std::string& rpc, std::shared_ptr<YangParams> retList)
{
	retList->addParam("SUCCESS", path(rpc + "/status")) ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanFileManagement::statusFail(const std::string& rpc, std::shared_ptr<YangParams> retList,
		const std::string &reason)
{
	retList->addParam("FAILURE", path(rpc + "/status")) ;
	retList->addParam(reason, path(rpc + "/reject-reason")) ;
}
