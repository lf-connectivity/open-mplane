/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanDhcp.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <fstream>
#include <string>

#include "stringfunc.hpp"
#include "IAppOptions.h"

#include "ILoggable.h"
#include "ILeafContainer.h"
#include "IBootEnv.h"

#include "RadioDatastoreSysrepo.h"

#include "Zcu111FbcOranrrhHandlerORanDhcp.h"
#include "IDhcpOptions.h"
#include "DhcpOptions.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const std::string ENV_SERIALNUM{"hwBoardSerialNum"};
const uint32_t Zcu111FbcOranrrhHandlerORanDhcp::mPrivateEnterpriseNum(53148);

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanDhcp::Zcu111FbcOranrrhHandlerORanDhcp(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo("o-ran-dhcp", moduleMgr, "Zcu111FbcOranrrhHandlerORanDhcp")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path("dhcp")))
	, mMutex()
	, mProductCode(PRODUCT_CODE)
	, mSerialNumber("")
    , mDhcpOptions(IDhcpOptions::singleton())
    , mInterfaces()
{
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	mSerialNumber = bootEnv->getVar(ENV_SERIALNUM) ;

	mDhcpOptions->registerDhcpOptionsFunc([this](const std::string& interface)
	{
		// Get the DHCP options
		getDhcpOptions(interface);
	}) ;
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanDhcp::~Zcu111FbcOranrrhHandlerORanDhcp()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanDhcp::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

//	module: o-ran-dhcp
//	  +--ro dhcp
//	     +--ro interfaces* [interface]
//	     +--ro m-plane-dhcp
//	        x--ro private-enterprise-number? uint16
//	        +--ro private-enterprise-num?    uint32
//	        +--ro vendor-class-data?         string

	// create top-level of the r/o area
	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	std::shared_ptr<ILeafContainer> mplaneDhcp = parent->addContainer("m-plane-dhcp");
	mplaneDhcp->addLeafUInt32("private-enterprise-num", mPrivateEnterpriseNum);

	std::string vendorClassData = "o-ran-ru2/Mplane/" + mProductCode + "/" + mSerialNumber;
	mplaneDhcp->addLeaf("vendor-class-data", vendorClassData);

	// Register callbacks
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe() ;

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanDhcp::valueChange(const std::string & xpath,
                                                  std::shared_ptr<YangParam> oldValue,
                                                  std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanDhcp::valueChange() - %s", xpath.c_str());
}

//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanDhcp::validate(std::shared_ptr<YangParams> params,
		std::shared_ptr<YangParams> deletedParams)
{
	return SR_ERR_OK ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanDhcp::getDhcpOptions(const std::string &interface)
{
	// The interface has been allocated an ip address
	std::cerr << "Zcu111FbcOranrrhHandlerORanDhcp::getDhcpOptions interface '" << interface << "'" << std::endl ;

	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	std::vector<std::string> dns; //!> List of DNS servers to be used by the client
	std::vector<std::string> gateways;   //!> List of default gateways (the first router or L3 switch seen by the client to get to the Internet)
	std::map<std::string, std::string> netconfClients; //!> Netconf client url and port numbers to be used for call home functionality
	std::map<unsigned int, std::vector<std::string>> vendorInfo; //!> Vendor specific info

	// Get the DHCP options
	mDhcpOptions->getDns(interface, dns);

	mDhcpOptions->getDefaultGateways(interface, gateways);

	mDhcpOptions->getNetConfClients(interface, netconfClients);

	mDhcpOptions->getVendorSpecificInfo(interface, vendorInfo);

	// Run update if already created tree - need to ensure values are updated if ip address is renewed
	// skip if already handled
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		if (std::find(mInterfaces.begin(), mInterfaces.end(), interface) != mInterfaces.end())
		{
			// If the tree structure is already created, then delete the lists and recreate with new values

			std::shared_ptr<ILeafContainer> dhcpv4 = getDhcpv4Node(interface);

			if (dhcpv4 != nullptr)
			{
				// Delete the lists
				dhcpv4->deleteNamed("domain-name-servers", false);
				dhcpv4->deleteNamed("default-gateways", false);
				dhcpv4->deleteNamed("netconf-clients", false);
				dhcpv4->deleteNamed("ca-ra-servers", false);
				dhcpv4->deleteNamed("security-gateways", false);

				addDhcpLists(dhcpv4, dns, gateways, netconfClients, vendorInfo);
			}

			return ;
		}

		// Add the interface
		mInterfaces.push_back(interface);
	}

	//	     |  +--ro interface  if:interface-ref
	//	     |  +--ro dhcpv4
	//	     |  |  +--ro client-id?              string
	//	     |  |  +--ro dhcp-server-identifier? inet:ip-address
	//	     |  |  +--ro domain-name?            string
	//	     |  |  +--ro domain-name-servers*    inet:ip-address
	//	     |  |  +--ro interface-mtu?          uint32
	//	     |  |  +--ro default-gateways*       inet:ip-address
	//	     |  |  +--ro netconf-clients* [client]
	//	     |  |  |  +--ro client         netconf-client-id
	//	     |  |  |  +--ro optional-port? inet:port-number
	//	     |  |  +--ro ca-ra-servers* [servers]
	//	     |  |  |  +--ro servers       ca-ra-server-id
	//	     |  |  |  +--ro port-number?  inet:port-number
	//	     |  |  |  +--ro ca-ra-path?   string
	//	     |  |  |  +--ro subject-name? string
	//	     |  |  |  +--ro protocol?     enumeration
	//	     |  |  +--ro segw* [gateways]
	//	     |  |     +--ro gateways  segw-id


	auto interfaces = parent->addContainer("interfaces") ;

	// Create interface name leaf
	interfaces->addLeaf("interface", interface);

	// Create dhcpv4 container
	std::shared_ptr<ILeafContainer> dhcpv4 = interfaces->addContainer("dhcpv4");

	std::string clientId = "o-ran-ru2/Mplane/" + mProductCode + "/" + mSerialNumber;
	dhcpv4->addLeaf("client-id", clientId);

	auto callbackFunc = [this, interface](const std::string& leafName)->std::string {
		return handleGetCallback(leafName, interface) ;
	} ;

	dhcpv4->addLeaf("dhcp-server-identifier", callbackFunc);
	dhcpv4->addLeaf("domain-name", callbackFunc);
	dhcpv4->addLeaf("interface-mtu", callbackFunc);

	addDhcpLists(dhcpv4, dns, gateways, netconfClients, vendorInfo);

}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanDhcp::addDhcpLists(std::shared_ptr<ILeafContainer>& dhcpv4,
		std::vector<std::string>& dns, std::vector<std::string>& gateways,
		std::map<std::string, std::string>& netconfClients,
		std::map<unsigned int, std::vector<std::string>>& vendorInfo)
{
	for (auto & elem : dns)
	{
		dhcpv4->addLeaf("domain-name-servers", elem);
	}

	for (auto & elem : gateways)
	{
		dhcpv4->addLeaf("default-gateways", elem);
	}

	for (auto & elem : netconfClients)
	{
		std::shared_ptr<ILeafContainer> netconfClientsList = dhcpv4->addContainer("netconf-clients");
		netconfClientsList->addLeaf("client", elem.first);
		if (elem.second != "")
		{
			netconfClientsList->addLeaf("optional-port", elem.second);
		}
	}

	// Create ca-ra-servers list
	bool caRaPortAvailable = (vendorInfo.find(DhcpOptions::SuboptionCaRaPort) != vendorInfo.end());
	bool caRaPathAvailable = (vendorInfo.find(DhcpOptions::SuboptionCaRaPath) != vendorInfo.end());
	bool caRaSubNameAvailable = (vendorInfo.find(DhcpOptions::SuboptionCaRaSubName) != vendorInfo.end());
	bool caRaProtocolAvailable = (vendorInfo.find(DhcpOptions::SuboptionCaRaProtocol) != vendorInfo.end());

	// Loop through the discovered CA RA IP addresses
	if (vendorInfo.find(DhcpOptions::SuboptionCaRaIP) != vendorInfo.end())
	{
		std::vector<std::string> caRaIp = vendorInfo[DhcpOptions::SuboptionCaRaIP];
		for (auto & elem : caRaIp)
		{
			std::shared_ptr<ILeafContainer> caRaList = dhcpv4->addContainer("ca-ra-servers");
			caRaList->addLeaf("servers", elem);
			if (caRaPortAvailable)
			{
				caRaList->addLeaf("port-number", vendorInfo[DhcpOptions::SuboptionCaRaPort][0]);
			}

			if (caRaPathAvailable)
			{
				caRaList->addLeaf("ca-ra-path", vendorInfo[DhcpOptions::SuboptionCaRaPath][0]);
			}

			if (caRaSubNameAvailable)
			{
				caRaList->addLeaf("subject-name", vendorInfo[DhcpOptions::SuboptionCaRaSubName][0]);
			}

			if (caRaProtocolAvailable)
			{
				caRaList->addLeaf("protocol", vendorInfo[DhcpOptions::SuboptionCaRaProtocol][0]);
			}
		}
	}

	// Loop through the discovered CA RA FQDNs
	if (vendorInfo.find(DhcpOptions::SuboptionCaRaName) != vendorInfo.end())
	{
		std::vector<std::string> caRaName = vendorInfo[DhcpOptions::SuboptionCaRaName];
		for (auto & elem : caRaName)
		{
			std::shared_ptr<ILeafContainer> caRaList = dhcpv4->addContainer("ca-ra-servers");
			caRaList->addLeaf("servers", elem);
			if (caRaPortAvailable)
			{
				caRaList->addLeaf("port-number", vendorInfo[DhcpOptions::SuboptionCaRaPort][0]);
			}

			if (caRaPathAvailable)
			{
				caRaList->addLeaf("ca-ra-path", vendorInfo[DhcpOptions::SuboptionCaRaPath][0]);
			}

			if (caRaSubNameAvailable)
			{
				caRaList->addLeaf("subject-name", vendorInfo[DhcpOptions::SuboptionCaRaSubName][0]);
			}

			if (caRaProtocolAvailable)
			{
				caRaList->addLeaf("protocol", vendorInfo[DhcpOptions::SuboptionCaRaProtocol][0]);
			}
		}
	}

	// Create Security gateways list

	// Loop through the discovered Security gateways IP addresses
	if (vendorInfo.find(DhcpOptions::SuboptionSeGwIP) != vendorInfo.end())
	{
		std::vector<std::string> seGwIp = vendorInfo[DhcpOptions::SuboptionSeGwIP];
		for (auto & elem : seGwIp)
		{
			std::shared_ptr<ILeafContainer> seGwList = dhcpv4->addContainer("segw");
			seGwList->addLeaf("gateways", elem);
		}
	}

	// Loop through the discovered Security gateways FQDNs
	if (vendorInfo.find(DhcpOptions::SuboptionSeGwName) != vendorInfo.end())
	{
		std::vector<std::string> seGwName = vendorInfo[DhcpOptions::SuboptionSeGwName];
		for (auto & elem : seGwName)
		{
			std::shared_ptr<ILeafContainer> seGwList = dhcpv4->addContainer("segw");
			seGwList->addLeaf("gateways", elem);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111FbcOranrrhHandlerORanDhcp::handleGetCallback(const std::string &leafName, const std::string &interface)
{
	std::unique_lock<std::mutex> lock(mMutex) ;

	std::string param;

	if (leafName == "dhcp-server-identifier")
	{
		mDhcpOptions->getServerIdentifier(interface, param);
		return param ;
	}

	if (leafName == "domain-name")
	{
		mDhcpOptions->getDomainName(interface, param);
		return param ;
	}

	if (leafName == "interface-mtu")
	{
		mDhcpOptions->getMtu(interface, param);
		return param ;
	}

	return std::string() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILeafContainer> Zcu111FbcOranrrhHandlerORanDhcp::getDhcpv4Node(std::string interfaceName)
{
	// Navigate to the interfaces list by getting contents of the parent
	// Find the child node for the interface that we are processing now

	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	// Get the children for the top level container
	std::vector<std::shared_ptr<ILeafContainer>> dhcpChildren = parent->contents();
	std::shared_ptr<ILeafContainer> node = nullptr;

	// Go through the children of dhcp top level container
	for (auto & dhcpChild : dhcpChildren)
	{
		if (dhcpChild->name() != "interfaces")
		{
			continue;
		}

		// Get the children of the interfaces list entry
		std::vector<std::shared_ptr<ILeafContainer>> interfacesChildren = dhcpChild->contents();

		// Look for a child with the interface name provided in this method
		for (auto & interfacesChild : interfacesChildren)
		{
			// If it is found, then save the parent and exit the loop
			if (interfacesChild->name() == "interface" &&
				interfacesChild->value() == interfaceName)
			{
				node = dhcpChild;
				break;
			}
		}
	}

	// If a node is found with the required interface name, then look for dhcpv4 child in that node
	if (node != nullptr)
	{
		std::vector<std::shared_ptr<ILeafContainer>> interfacesChildren = node->contents();
		for (auto & interfacesChild : interfacesChildren)
		{
			// If the dhcpv4 child is found, then return
			if (interfacesChild->name() == "dhcpv4")
			{
				return interfacesChild;
			}
		}
	}
	return nullptr;
}
