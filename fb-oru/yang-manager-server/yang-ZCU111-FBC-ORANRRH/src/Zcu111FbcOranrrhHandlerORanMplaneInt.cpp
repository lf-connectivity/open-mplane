/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanMplaneInt.cpp
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

#include "stringfunc.hpp"
#include "ILeafContainer.h"
#include "IAppOptions.h"
#include "INetworkingService.h"

#include "FileMap.h"
#include "YangMgrServer.h"
#include "YangParamUtils.h"

// for debug
#include "CdiNetworkingService.h"

#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerORanMplaneInt.h"
#include "Zcu111FbcOranrrhHandlerORanProcessingElement.h"
#include "DhcpOptions.h"
#include "Zcu111FbcOranrrhHandlerIetfInterfaces.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//=============================================================================================================
// CLASSES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#if 0
struct Zcu111FbcOranrrhHandlerORanMplaneInt::InterfaceInfo {

	InterfaceInfo() :
		mIpAddress(),
		mDomain()
	{}
	InterfaceInfo(const std::string& ipAddress, const std::string& domain) :
		mIpAddress(ipAddress),
		mDomain(domain)
	{}

	std::string mIpAddress ;
	std::string mDomain ;
};
#endif

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanMplaneInt::Zcu111FbcOranrrhHandlerORanMplaneInt(std::shared_ptr<IYangModuleMgr> moduleMgr) :
	YangHandlerSysrepo("o-ran-mplane-int", moduleMgr, "Zcu111FbcOranrrhHandlerORanMplaneInt"),
	mCallback(std::make_shared<SysrepoGetitemsCallback>(path("mplane-info"))),
	mMplaneInterfacesContainer(nullptr),
	mMutex(),
	mDhcpOptions(IDhcpOptions::singleton()),
	mInterfaces()
{
	mDhcpOptions->registerDhcpOptionsFunc([this](const std::string& interface)
	{
		// Get the DHCP options
		getDhcpOptions(interface);
	}) ;
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanMplaneInt::~Zcu111FbcOranrrhHandlerORanMplaneInt()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanMplaneInt::initialise()
{
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	// add persistent paths
	makePersistent(path("mplane-info/searchable-mplane-access-vlans-info"));

	// Register callbacks
	getItemsSubscribe(path("mplane-info"), mCallback);
	changeSubscribe() ;

	// create top-level of the r/o area
	auto leafContainer(std::dynamic_pointer_cast<ILeafContainer>(mCallback)) ;
	mMplaneInterfacesContainer = leafContainer->addContainer("m-plane-interfaces") ;

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanMplaneInt::valueChange(const std::string & xpath,
                                                       std::shared_ptr<YangParam> oldValue,
                                                       std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanMplaneInt::valueChange() - %s", xpath.c_str());
}


//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanMplaneInt::validate(std::shared_ptr<YangParams> params,
		std::shared_ptr<YangParams> deletedParams)
{
	return SR_ERR_VALIDATION_FAILED ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanMplaneInt::getDhcpOptions(const std::string &interface)
{
	// The interface has been allocated an ip address

	// Module manager access
	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;

	// If interface is of the form: nnn.xx then split out the base name and the vlan tag
	std::string ifname(interface) ;
	uint16_t vlanId(0);
	std::string vlanIdStr = std::to_string(vlanId);
	std::size_t pos(ifname.find('.')) ;
	if (pos != std::string::npos)
	{
		bool validId;
		vlanIdStr = ifname.substr(pos+1);
		vlanId    = extractUnsigned(vlanIdStr, validId);
		ifname    = ifname.substr(0, pos);
	}

	// If this is not on a VLAN tagged interface, then don't report anything.
	// My reasoning is: every entry needs both an interface name AND a valid vlan id. Also, the keys are BOTH the interface name AND the vlan id
	// So, if I can't set a vlan id, then I can't create an entry
	if (vlanId == 0)
	{
		return ;
	}

	std::string ifvlan(ifname + "." + vlanIdStr) ;

	std::string ipAddress;
	std::string macAddress;

	if (!mDhcpOptions->getIpAddress(ifvlan, ipAddress))
	{
		eventWarning("Interface %s not available", ifvlan.c_str());
		return;
	}
	if (!mDhcpOptions->getMacAddress(ifvlan, macAddress))
	{
		eventWarning("Interface %s not available", ifvlan.c_str());
		return;
	}

	// Run update if already created tree - need to ensure values are updated if ip address is renewed
	// skip if already handled
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		if (std::find(mInterfaces.begin(), mInterfaces.end(), ifvlan) != mInterfaces.end())
		{
			return ;
		}

		// Add the interface
		mInterfaces.push_back(ifvlan);
	}

	// Create the new interface
	std::shared_ptr<Zcu111FbcOranrrhHandlerIetfInterfaces> ietfInteface(std::make_shared<Zcu111FbcOranrrhHandlerIetfInterfaces>(mgr));
	ietfInteface->addVlanInterface(ifvlan,
	                               "1G ethernet interface",
	                               macAddress,
	                               ipAddress,
	                               vlanId,
	                               ifname);

// ToDo: Remove as the DU should add this
	// Create a new processing element
	{
	//std::string pevlan("PE_" + ifvlan);
	std::string pevlan;
	std::string duMac = "00:00:00:00:00:00";
	std::shared_ptr<Zcu111FbcOranrrhHandlerORanProcessingElement> processEle(std::make_shared<Zcu111FbcOranrrhHandlerORanProcessingElement>(mgr));
	processEle->addRuProcessingElement(pevlan, ifvlan, duMac);
	}

	// Create the r/w values

	//	module: o-ran-mplane-int
	//	  +--rw mplane-info
	//	     +--rw m-plane-interfaces
	//	     |  +--rw m-plane-sub-interfaces* [interface-name sub-interface]
	//	     |  |  +--rw interface-name    -> /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name
	//	     |  |  +--rw sub-interface     -> /ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name = current()/../interface-name]/o-ran-interfaces:vlan-id

	std::string treepath("mplane-info/m-plane-interfaces/m-plane-sub-interfaces[interface-name='" +
			ifvlan +
			"'][sub-interface='" +
			vlanIdStr +
			"']") ;
	createListEntry(path(treepath),
		std::map<std::string, std::string>{
		{"interface-name", ifvlan},
		{"sub-interface", vlanIdStr},
		}) ;

	// Create the r/o values

//	module: o-ran-mplane-int
//	  +--rw mplane-info
//	     +--rw m-plane-interfaces
//	     |  +--rw m-plane-sub-interfaces* [interface-name sub-interface]
//	     |  |  +--rw interface-name    -> /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name
//	     |  |  +--rw sub-interface     -> /ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name = current()/../interface-name]/o-ran-interfaces:vlan-id
//	     |  |  +--ro client-info
//	     |  |     +--ro mplane-ipv4-info* [mplane-ipv4]
//	     |  |     |  +--ro mplane-ipv4    ietf-inet-types:ipv4-address
//	     |  |     |  +--ro port?          ietf-inet-types:port-number
//	     |  |     +--ro mplane-fqdn*        ietf-inet-types:domain-name

	std::shared_ptr<ILeafContainer> subInterfaces = mMplaneInterfacesContainer->addContainer("m-plane-sub-interfaces") ;
	subInterfaces->addLeaf("interface-name", ifvlan) ;   	// Add key as state data
	subInterfaces->addLeaf("sub-interface", vlanIdStr) ; 	// Add key as state data
	std::shared_ptr<ILeafContainer> clientInfo = subInterfaces->addContainer("client-info") ;
	std::shared_ptr<ILeafContainer> ipv4Info = clientInfo->addContainer("mplane-ipv4-info") ;

	auto callbackFunc = [this, ifvlan](const std::string& leafName)->std::string {
		return handleGetCallback(leafName, ifvlan) ;
	} ;
	ipv4Info->addLeaf("mplane-ipv4", callbackFunc) ;
	clientInfo->addLeaf("mplane-fqdn", callbackFunc) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111FbcOranrrhHandlerORanMplaneInt::handleGetCallback(const std::string &leafName, const std::string &ifvlan)
{
	std::unique_lock<std::mutex> lock(mMutex) ;

	std::string param;

	if (leafName == "mplane-ipv4")
	{
		mDhcpOptions->getIpAddress(ifvlan, param);
		return param ;
	}

	if (leafName == "mplane-fqdn")
	{
		mDhcpOptions->getDomainName(ifvlan, param);
		return param ;
	}

	return std::string() ;
}
