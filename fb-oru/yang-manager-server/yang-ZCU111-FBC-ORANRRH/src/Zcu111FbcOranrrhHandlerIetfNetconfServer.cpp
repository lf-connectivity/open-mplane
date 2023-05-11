/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerIetfNetconfServer.cpp
 * \brief     IETF NETCONF Server configuration module handler
 *
 *
 * \details   IETF NETCONF Server configuration module handler
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <fstream>
#include <ctime>

#include "stringfunc.hpp"
#include "IAppOptions.h"

#include "INetworkingService.h"
#include "ILoggable.h"
#include "ILeafContainer.h"
#include "IBootEnv.h"

#include "YangMgrServer.h"
#include "RadioDatastoreSysrepo.h"
#include "YangParamUtils.h"

#include "Zcu111FbcOranrrhHandlerIetfNetconfServer.h"
#include "Zcu111FbcOranrrhHandlerORanDhcp.h"
#include "IDhcpOptions.h"
#include "IIpPortMgr.h"

// for debug
#include "CdiNetworkingService.h"

using namespace Mplane;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerIetfNetconfServer::Zcu111FbcOranrrhHandlerIetfNetconfServer(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo("ietf-netconf-server", moduleMgr, "Zcu111FbcOranrrhHandlerIetfNetconfServer")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path("netconf-server")))
	, mDhcpOptions(IDhcpOptions::singleton())
{
#ifdef TEST_BB_ON_CDI
	const std::string itfc("ethcdi") ;
#else
	const std::string itfc("ethbb") ;
#endif
	mEthbbInterface = IAppOptions::getInstance()->getOption(itfc).toString() ;

	auto ns(INetworkingService::singleton(mEthbbInterface)) ;
	if (ns)
	{
		std::shared_ptr<INetAddrPolicy> policy(ns->getNetAddrPolicy()) ;
		policy->registerAllocatedFunc([this](const std::string& interface, const std::string& ipAddress,
				const std::string& macAddress, const std::string& allocatorName, INetChange::NetState allocatorType){

			getInterfaceInfo(interface) ;
		}) ;
	}


	mDhcpOptions->registerDhcpOptionsFunc([this](const std::string& interface)
	{
		// Get the netconf clients
		getInterfaceInfo(interface);
	}) ;
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerIetfNetconfServer::~Zcu111FbcOranrrhHandlerIetfNetconfServer()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfNetconfServer::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	// Register callback for each top level container
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe();

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfNetconfServer::valueChange(const std::string & xpath,
                                                        std::shared_ptr<YangParam> oldValue,
                                                        std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerIetfNetconfServer::valueChange() - %s", xpath.c_str());
}

//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerIetfNetconfServer::validate(std::shared_ptr<YangParams> params,
		std::shared_ptr<YangParams> deletedParams)
{
	return SR_ERR_OK ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfNetconfServer::getInterfaceInfo(const std::string& interface)
{
	// The interface has been allocated an ip address
	std::cerr << "getInterfaceInfo interface '" << interface << "'" << std::endl ;

	std::string ifname = interface;
	std::size_t pos(interface.find('.')) ;

	if (pos != std::string::npos)
	{
		ifname = interface.substr(0, pos) ;
	}

	if (ifname == mEthbbInterface)
	{
		std::map<std::string, std::string> clientList; //!> Netconf client url and port numbers to be used for call home functionality
		std::map<std::string, std::string> existingClients = getCallHomeClients();

		// Get the DHCP options
		mDhcpOptions->getNetConfClients(interface, clientList);

		// Check for new clients
		for (auto & client : clientList)
		{
			if (existingClients.find(client.first) != existingClients.end())
				continue ;

			// Add new client to sysrepo
			addCallHomeClient(client.first, client.second);

			// mark as seen
			existingClients[client.first] = client.second ;
		}

		// Now get any clients from the stored list
		for (auto & client : IIpPortMgr::singleton()->list())
		{
			if (existingClients.find(client.first) != existingClients.end())
				continue ;

			// Add new client to sysrepo
			addCallHomeClient(client.first, std::to_string(client.second));

			// mark as seen
			existingClients[client.first] = std::to_string(client.second) ;
		}


	}
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::string> Zcu111FbcOranrrhHandlerIetfNetconfServer::getCallHomeClients(void)
{
	std::map<std::string, std::string> existingClients;

	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	std::string clientListPath = mCallback->path() + "/call-home/netconf-client";
	std::vector<std::string> keyValues;

	ds->getListItems(clientListPath, keyValues);

	// Looking for client names of the form:
	//
	//   "client-" + url + "-" + port
	//
	// so we can split the parts using the '-' character
	//
	// NOTE: Assumes url doesn't have any '-' characters if it's a DNS name
	//
	for (auto & client : keyValues)
	{
		size_t urlStartPos = client.find_first_of('-');
		size_t urlEndPos = client.find_last_of('-');

		if ( (urlStartPos == std::string::npos) ||
			(urlEndPos == std::string::npos) ||
			(urlEndPos <= urlStartPos) )
			continue ;

		size_t portEndPos = client.find_first_of('\'', urlEndPos + 1);
		if (portEndPos == std::string::npos)
			continue ;

		std::string url( client.substr(urlStartPos + 1, (urlEndPos - urlStartPos - 1)) );
		std::string port( client.substr(urlEndPos + 1, (portEndPos - urlEndPos - 1)) );
		existingClients[url] = port;
	}

	return existingClients;

}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfNetconfServer::addCallHomeClient(std::string url, std::string port)
{
	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	std::string clientName = "client-" + url + "-" + port;

	std::string endPointPath = "endpoints/endpoint[name='ssh-endpoint']";
	std::string callHome = mCallback->path() + "/call-home/netconf-client";
	YangResult_E result = ds->createListEntry(callHome, "name", clientName,
			std::map<std::string, std::shared_ptr<std::string>>{
						{endPointPath, nullptr},
						{endPointPath + "/ssh/tcp-client-parameters/remote-address", std::make_shared<std::string>(url)},
						{endPointPath + "/ssh/tcp-client-parameters/remote-port", std::make_shared<std::string>(port)},
						{endPointPath + "/ssh/tcp-client-parameters/keepalives/idle-time", std::make_shared<std::string>("60")},
						{endPointPath + "/ssh/tcp-client-parameters/keepalives/max-probes", std::make_shared<std::string>("10")},
						{endPointPath + "/ssh/tcp-client-parameters/keepalives/probe-interval", std::make_shared<std::string>("30")},
						{endPointPath + "/ssh/ssh-server-parameters/server-identity/host-key[name='default-key']",nullptr},
						{endPointPath + "/ssh/ssh-server-parameters/server-identity/host-key[name='default-key']/public-key/keystore-reference", std::make_shared<std::string>("genkey")},
						{endPointPath + "/ssh/ssh-server-parameters/client-authentication/users", nullptr},
						{"connection-type/persistent", nullptr},
	});

	return (result == YangResult_E::OK);
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfNetconfServer::deleteCallHomeClient(std::string url, std::string port)
{
	YangResult_E result = YangResult_E::NOT_FOUND;

	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	std::string clientListPath = mCallback->path() + "/call-home/netconf-client";
	std::vector<std::string> keyValues;
	std::string clientNameToSearch = "name='client-" + url + "-" + port + "'";

	ds->getListItems(clientListPath, keyValues);

	// Check if the client is present in the sysrepo
	if (std::find(keyValues.begin(), keyValues.end(), clientNameToSearch) != keyValues.end())
	{
		// Check if there are more than 1 clients in the list
		if (keyValues.size() > 1)
		{
			result = ds->deleteItem(clientListPath + "[" + clientNameToSearch + "]");
		}
		// If there is a single client in the list, then delete the call home container
		else
		{
			result = ds->deleteItem(mCallback->path() + "/call-home");
		}
	}

	return (result == YangResult_E::OK);
}
