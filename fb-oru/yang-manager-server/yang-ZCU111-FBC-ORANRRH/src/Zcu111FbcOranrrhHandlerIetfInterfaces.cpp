/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerIetfInterfaces.cpp
 * \brief     IETF interfaces module handler
 *
 *
 * \details   IETF interfaces module handler
 *
 * Collection of YANG definitions for managing network interfaces.
 *
 * module: ietf-interfaces
 *   +--rw interfaces
 *      +--rw interface* [name]
 *         +--rw name                        string
 *         +--rw description?                string
 *         +--rw type                        identityref
 *         +--rw enabled?                    boolean
 *         +--rw link-up-down-trap-enable?   enumeration {if-mib}?
 *         +--ro admin-status                enumeration {if-mib}?
 *         +--ro oper-status                 enumeration
 *         +--ro last-change?                yang:date-and-time
 *         +--ro if-index                    int32 {if-mib}?
 *         +--ro phys-address?               yang:phys-address
 *         +--ro higher-layer-if*            interface-ref  leafref: /if:interfaces/if:interface/if:name
 *         +--ro lower-layer-if*             interface-ref  leafref: /if:interfaces/if:interface/if:name
 *         +--ro speed?                      yang:gauge64
 *         +--ro statistics
 *         |  +--ro discontinuity-time  yang:date-and-time
 *         |  +--ro in-octets?          yang:counter64
 *         |  +--ro in-unicast-pkts?    yang:counter64
 *         |  +--ro in-broadcast-pkts?  yang:counter64
 *         |  +--ro in-multicast-pkts?  yang:counter64
 *         |  +--ro in-discards?        yang:counter32
 *         |  +--ro in-errors?          yang:counter32
 *         |  +--ro in-unknown-protos?  yang:counter32
 *         |  +--ro out-octets?         yang:counter64
 *         |  +--ro out-unicast-pkts?   yang:counter64
 *         |  +--ro out-broadcast-pkts? yang:counter64
 *         |  +--ro out-multicast-pkts? yang:counter64
 *         |  +--ro out-discards?       yang:counter32
 *         |  +--ro out-errors?         yang:counter32
 *         +--rw ip:ipv4!
 *         |  +--rw ip:enabled?                  boolean
 *         |  +--rw ip:forwarding?               boolean
 *         |  +--rw ip:mtu?                      uint16
 *         |  +--rw ip:address* [ip]
 *         |  |  +--rw ip:ip             inet:ipv4-address-no-zone
 *         |  |  +--rw (subnet)
 *         |  |  |  +--:(prefix-length)
 *         |  |  |  |  +--rw ip:prefix-length? uint8
 *         |  |  |  +--:(netmask)
 *         |  |  |     +--rw ip:netmask?       yang:dotted-quad {ipv4-non-contiguous-netmasks}?
 *         |  |  +--ro ip:origin?        ip-address-origin
 *         |  +--rw ip:neighbor* [ip]
 *         |  |  +--rw ip:ip                  inet:ipv4-address-no-zone
 *         |  |  +--rw ip:link-layer-address  yang:phys-address
 *         |  |  +--ro ip:origin?             neighbor-origin
 *         |  +--rw o-ran-int:m-plane-marking?   inet:dscp
 *         |  +--rw o-ran-int:diffserv-markings {UDPIP-BASED-CU-PLANE}?
 *         |     +--rw o-ran-int:u-plane-marking?          inet:dscp
 *         |     +--rw o-ran-int:c-plane-marking?          inet:dscp
 *         |     +--rw o-ran-int:s-plane-marking?          inet:dscp
 *         |     +--rw o-ran-int:other-marking?            inet:dscp
 *         |     +--rw o-ran-int:enhanced-uplane-markings* [up-marking-name]
 *         |        +--rw o-ran-int:up-marking-name   string
 *         |        +--rw o-ran-int:enhanced-marking? inet:dscp
 *         +--rw ip:ipv6!
 *         |  +--rw ip:enabled?                   boolean
 *         |  +--rw ip:forwarding?                boolean
 *         |  +--rw ip:mtu?                       uint32
 *         |  +--rw ip:address* [ip]
 *         |  |  +--rw ip:ip             inet:ipv6-address-no-zone
 *         |  |  +--rw ip:prefix-length  uint8
 *         |  |  +--ro ip:origin?        ip-address-origin
 *         |  |  +--ro ip:status?        enumeration
 *         |  +--rw ip:neighbor* [ip]
 *         |  |  +--rw ip:ip                  inet:ipv6-address-no-zone
 *         |  |  +--rw ip:link-layer-address  yang:phys-address
 *         |  |  +--ro ip:origin?             neighbor-origin
 *         |  |  +--ro ip:is-router?          empty
 *         |  |  +--ro ip:state?              enumeration
 *         |  +--rw ip:dup-addr-detect-transmits? uint32
 *         |  +--rw ip:autoconf
 *         |  |  +--rw ip:create-global-addresses?      boolean
 *         |  |  +--rw ip:create-temporary-addresses?   boolean {ipv6-privacy-autoconf}?
 *         |  |  +--rw ip:temporary-valid-lifetime?     uint32 {ipv6-privacy-autoconf}?
 *         |  |  +--rw ip:temporary-preferred-lifetime? uint32 {ipv6-privacy-autoconf}?
 *         |  +--rw o-ran-int:m-plane-marking?    inet:dscp
 *         |  +--rw o-ran-int:diffserv-markings {UDPIP-BASED-CU-PLANE}?
 *         |     +--rw o-ran-int:u-plane-marking?          inet:dscp
 *         |     +--rw o-ran-int:c-plane-marking?          inet:dscp
 *         |     +--rw o-ran-int:s-plane-marking?          inet:dscp
 *         |     +--rw o-ran-int:other-marking?            inet:dscp
 *         |     +--rw o-ran-int:enhanced-uplane-markings* [up-marking-name]
 *         |        +--rw o-ran-int:up-marking-name   string
 *         |        +--rw o-ran-int:enhanced-marking? inet:dscp
 *         +--rw o-ran-int:l2-mtu?           uint16
 *         +--rw o-ran-int:vlan-tagging?     boolean
 *         +--rw o-ran-int:class-of-service
 *         |  +--rw o-ran-int:u-plane-marking?          pcp
 *         |  +--rw o-ran-int:c-plane-marking?          pcp
 *         |  +--rw o-ran-int:m-plane-marking?          pcp
 *         |  +--rw o-ran-int:s-plane-marking?          pcp
 *         |  +--rw o-ran-int:other-marking?            pcp
 *         |  +--rw o-ran-int:enhanced-uplane-markings* [up-marking-name]
 *         |     +--rw o-ran-int:up-marking-name   string
 *         |     +--rw o-ran-int:enhanced-marking? pcp
 *         +--rw o-ran-int:base-interface?   if:interface-ref  leafref: /if:interfaces/if:interface/if:name
 *         +--rw o-ran-int:vlan-id?          uint16
 *         +--ro o-ran-int:last-cleared?     yang:date-and-time
 *         +--rw o-ran-int:alias-macs*       yang:mac-address {ALIASMAC-BASED-CU-PLANE}?
 *         +--rw o-ran-int:mac-address?      yang:mac-address
 *         +--rw o-ran-int:port-reference
 *            +--rw o-ran-int:port-name?   leafref  leafref: /hw:hardware/component/name
 *            +--rw o-ran-int:port-number? uint8
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <unistd.h>

#include "stringfunc.hpp"
#include "ILeafContainer.h"
#include "IAppOptions.h"
#include "INetworkingService.h"
#include "INetAddr.h"
#include "INetAddrPolicy.h"

#include "Zcu111FbcOranrrhHandlerORanLbm.h"
#include "YangMgrServer.h"

#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerIetfInterfaces.h"

using namespace Mplane;


//=============================================================================================================
// DEFINITIONS
//=============================================================================================================
//#define OPTIONAL_ENABLE_STATS_COUNTERS	// ToDo: Sets fixed values. Add network statistics object.
//#define OPTIONAL_LAST_CLEARED				// ToDo: This does not work. May have to set augmented ro parameters in the actual module.
//#define OPTIONAL_ENABLE_LAST_CHANGE
//#define OPTIONAL_ENABLE_PHYS_ADDR
#define OPTIONAL_ENABLE_SPEED
//#define OPTIONAL_SUPPORT_IPV6
#define OPTIONAL_PORT_REFERENCE
//#define OPTIONAL_MARKING_DSCP
//#define OPTIONAL_MARKING_COS

//#define ENABLE_NEIGHBOR_ADDRESS

//#define SUPPORTED_FEATURE_IFMIB
//#define SUPPORTED_FEATURE_ALIASMAC
//#define SUPPORTED_FEATURE_UDPIP
//#define SUPPORTED_FEATURE_IPV4NETMASK
//#define SUPPORTED_FEATURE_IPV6PRIV
#define FEATURE_IFMIB        "if-mib"
#define FEATURE_ALIASMAC     "ALIASMAC-BASED-CU-PLANE"
#define FEATURE_UDPIP        "UDPIP-BASED-CU-PLANE"
#define FEATURE_IPV4NETMASK  "ipv4-non-contiguous-netmasks"
#define FEATURE_IPV6PRIV     "ipv6-privacy-autoconf"

// DEBUG - Disabled until libyang issue resolved.
// libyang[1]: Schema node "enabled" not found (/ietf-interfaces:interfaces/interface[name='em1.1']/ietf-ip:ipv4/enabled) with context node "/ietf-interfaces:interfaces".
// libyang[1]: Schema node "forwarding" not found (/ietf-interfaces:interfaces/interface[name='em1.1']/ietf-ip:ipv4/forwarding) with context node "/ietf-interfaces:interfaces".
// libyang[1]: Schema node "mtu" not found (/ietf-interfaces:interfaces/interface[name='em1.1']/ietf-ip:ipv4/mtu) with context node "/ietf-interfaces:interfaces".

//#define ENABLE_TEST_AUGMENT_1
//#define ENABLE_ALL_AUGMENT
#if defined (ENABLE_ALL_AUGMENT) && !defined (ENABLE_TEST_AUGMENT_1)
#define ENABLE_TEST_AUGMENT_1
#else
#endif

#if defined (OFF_TARGET)
//#define DEBUG_CREATE_EM1_1_VLAN
#endif /* OFF_TARGET */

//=============================================================================================================
// LOCAL
//=============================================================================================================
UINT32 Zcu111FbcOranrrhHandlerIetfInterfaces::mNumInterfaces = 0;

const std::string moduleName       = "ietf-interfaces";
const std::string topContainerName = "interfaces";

const std::string modIp      = "ietf-ip";
const std::string modORanInt = "o-ran-interfaces";

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerIetfInterfaces::Zcu111FbcOranrrhHandlerIetfInterfaces(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo(moduleName, moduleMgr, "Zcu111FbcOranrrhHandlerIetfInterfaces")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path(topContainerName)))
	, mPathParent(moduleName, topContainerName)
	, mInterfaceUp(false)
	, mLastChangeTime()
	, mDiscontinuityTime()
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerIetfInterfaces::~Zcu111FbcOranrrhHandlerIetfInterfaces()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfInterfaces::initialise()
{
	// ------------------------------------------------------------------------
	// daisychain the initialisations
	// ------------------------------------------------------------------------
	if (!this->YangHandlerSysrepo::initialise())
		return false;

	// ------------------------------------------------------------------------
	// Physical radio interface names
	// ------------------------------------------------------------------------
	std::vector<std::string> ifNameKeys { "ethcdi", "ethbb" };

	// ------------------------------------------------------------------------
	// Initialise IETF interface module in sysrepo
	// ------------------------------------------------------------------------
	// +--rw interfaces
	std::shared_ptr<ILeafContainer> dataSte(mCallback); 	// Container for 'interfaces' state data (ro)

	// Add an interface entry for each physical interface
	std::vector<std::string> ifNameCreatedList;
	for (auto nameKey : ifNameKeys)
	{
		// Find interface device information.
		std::string ifName = IAppOptions::getInstance()->getOption(nameKey).toString();

		// Network services access
		auto ns(INetworkingService::singleton(ifName));
		auto policy(ns->getNetAddrPolicy());

		if (!policy)
		{
			eventWarning("Networking[%s]: Unable to find network interface", ifName.c_str());
			continue;
		}

		std::string ethName = ifName;

		// Check interface is not already assigned.
		bool enableInterface = true;
		for (auto name : ifNameCreatedList)
		{
			if (name == ethName)
			{
				enableInterface = false;
				eventError("Networking[%s]: Unable to add duplicate interface", name.c_str());
				break;
			}
		}

		// Add interface unless it's a duplicate
		if (enableInterface)
		{
			// Network services access

			eventInfo("Networking[%s]: Adding interface to datastore (IP:%s, MAC:%s)",
					ethName.c_str(),
					policy->ipAddress().c_str(),
					policy->macAddress().c_str());

			// Add interface to list for duplicate checking
			ifNameCreatedList.push_back(ethName);

			// Register our interest in, when the interface goes up / down
			policy->registerUpFunc([this, ethName](void)
			{
				if (!mInterfaceUp)
				{
					mInterfaceUp = true;
					//std::cerr << "Networking["<< ethName << "]: UP" << std::endl ;
				}
				else
				{
					//std::cerr << "Networking["<< ethName << "]:  Interface already UP" << std::endl ;
				}
			}) ;
			policy->registerDownFunc([this, ethName](void)
			{
				if (mInterfaceUp)
				{
					mInterfaceUp = false;

					// Store interface discontinuity time
					time_t timestamp;
					time(&timestamp);
					mDiscontinuityTime[ethName] = YangUtils::getDateTime(timestamp);

					std::cerr << "Networking["<< ethName << "]: Interface down: " << mDiscontinuityTime[ethName] << std::endl ;
				}
				else
				{
					//std::cerr << "Networking["<< ethName << "]:  Interface already DOWN" << std::endl ;
				}
			}) ;

			// Register our interest in when the interface gets allocated an IP address
			policy->registerAllocatedFunc([this](const std::string& interface, const std::string& ipAddress, const std::string& macAddress,
					const std::string& allocatorName, INetChange::NetState allocatorType)
			{
				std::string allocatorStr;
				if (allocatorType == INetChange::NET_DISCONNECTED)
					allocatorStr = "NET_DISCONNECTED";
				if (allocatorType == INetChange::NET_STATIC)
					allocatorStr = "NET_STATIC";
				if (allocatorType == INetChange::NET_DHCP)
					allocatorStr = "NET_DHCP";
				if (allocatorType == INetChange::NET_LINK_LOCAL)
					allocatorStr = "NET_LINK_LOCAL";
				std::cerr << "Networking["<< interface << "]: ietf-interface [IP: " << ipAddress << ", MAC: " << macAddress << ", allocName: " << allocatorName << ", allocName: " << allocatorStr << "]" << std::endl ;
#if defined (DEBUG_CREATE_EM1_1_VLAN)
				static bool vlanCreated = false;
				// Create test vlan interface
				if ((!vlanCreated) && (interface == std::string("em1")))
				{
					vlanCreated = true;
					UINT16 vlanId(1);
					std::string vlanIdStr = std::to_string(vlanId);
					std::string ifvlan(interface + "." + vlanIdStr);
					addVlanInterface(ifvlan,
									 "VLAN",
									 macAddress,
									 ipAddress,
									 vlanId,
									 interface);
				}
#endif /* DEBUG_CREATE_EM1_1_VLAN */
			}) ;

			// Create callback to handle IETF interface module state data
			createInterfaceListEntry(dataSte, ethName,
				policy->interfacePort(),
				policy->ipAddress(),
				policy->interfaceSpeed());

			// Add configuration data for physical interface
			addInterface(ethName,
			             policy->interfaceDescription(),
			             policy->interfacePort(),
			             policy->macAddress(),
			             policy->ipAddress(),
			             "",	// format: xxxx::xxxx:xxxx:xxxx:xxxx"
			             0,
			             false,
			             0,
			             "");
		}
	}

	// ------------------------------------------------------------------------
	// Register callback for each top level container
	// ------------------------------------------------------------------------
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe();

	return true;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::addVlanInterface(const std::string & ethName,
                                                             const std::string & desc,
                                                             const std::string & macAddr,
                                                             const std::string & ipAddr,
                                                             UINT16 vlanId,
                                                             const std::string & baseEthName)
{
	// Find interface device information.
	eventInfo("Networking[%s]: Adding vlan interface to datastore (IP:%s, MAC:%s, ID:%d)",
			ethName.c_str(), ipAddr.c_str(), macAddr.c_str(), vlanId);

	std::shared_ptr<ILeafContainer> dataSte(mCallback); 	// Container for 'interfaces' state data (ro)

// ToDo: This should use the vlan policy, which is not being created?

	// Create callback to handle state data
	createInterfaceListEntry(dataSte, ethName, 0, ipAddr, 0);

	// Add configuration data for virtual interface
	addInterface(ethName, desc, 0, macAddr, ipAddr, "", 0, true, vlanId, baseEthName);

	// Add LBM entry
	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
	std::shared_ptr<Zcu111FbcOranrrhHandlerORanLbm> oranLbm(std::make_shared<Zcu111FbcOranrrhHandlerORanLbm>(mgr));
	oranLbm->addMaintenaceDomainEntry(ethName, macAddr, vlanId);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::valueChange(const std::string & xpath,
                                                        std::shared_ptr<YangParam> oldValue,
                                                        std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerIetfInterfaces::valueChange() - %s", xpath.c_str());
}

//=============================================================================================================
// PRIVATE - State data
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::createInterfaceListEntry(std::shared_ptr<ILeafContainer> dataSte,
                                                                     const std::string & ethName,
																	 uint8_t portNumber,
                                                                     const std::string & ipAddr,
                                                                     UINT64 speed)
{
	// +--rw interface* [name]
	std::shared_ptr<ILeafContainer> dataSteIf = dataSte->addContainerList("interface");	// interface container for state data (ro)

	//    +--rw name                        string
	dataSteIf->addLeaf("name", ethName);	// Add key as state data

	//    +--ro admin-status                enumeration {if-mib}?
	if (isModuleFeatureEnabled(FEATURE_IFMIB))
		dataSteIf->addLeaf("admin-status", "down");

	//    +--ro oper-status                 enumeration

	// Callback to get operational status
	auto operStatusFunc = [this, ethName](std::string name) -> std::string
	{
		// Network services access
		auto ns(INetworkingService::singleton(ethName));
		auto policy(ns->getNetAddrPolicy());

		INetAddr::NetAddrStatus netStatus = policy->status();

		std::string operStatus = "unknown";
		switch (netStatus)
		{
			case INetAddr::NetAddrStatus::NET_INACTIVE:
				operStatus = "dormant";
				break;

			case INetAddr::NetAddrStatus::NET_IP_ALLOCATED:
			case INetAddr::NetAddrStatus::NET_RUNNING:
				operStatus = "up";
				break;

			case INetAddr::NetAddrStatus::NET_TIMED_OUT:
			case INetAddr::NetAddrStatus::NET_ERROR:
				operStatus = "down";
				break;

			default:
				break;
		}
		std::cerr << "IetfInterface ["<< policy->interface() << "]: " << operStatus << std::endl ;
		return operStatus;
	};
	dataSteIf->addLeaf("oper-status", operStatusFunc);

	//    +--ro last-change?                yang:date-and-time
#if defined (OPTIONAL_ENABLE_LAST_CHANGE)
	// Callback to get operational status
	auto lastChangeFunc = [this, ethName](std::string name) -> std::string
	{
		return mLastChangeTime[ethName];
	}
	dataSteIf->addLeaf("last-change", lastChangeFunc); // Time the interface entered its current operational state.
#endif /* OPTIONAL_ENABLE_LAST_CHANGE */

	//    +--ro if-index                    int32 {if-mib}?
	if (isModuleFeatureEnabled(FEATURE_IFMIB))
		dataSteIf->addLeafInt32("if-index", mNumInterfaces);

	//    +--ro phys-address?               yang:phys-address
#if defined (OPTIONAL_ENABLE_PHYS_ADDR)
	dataSteIf->addLeaf("phys-address", "11:11:11:11:11:11");
#endif /* OPTIONAL_ENABLE_PHYS_ADDR */

	//    +--ro speed?                      yang:gauge64
#if defined (OPTIONAL_ENABLE_SPEED)
	if (speed > 0)
	{
		dataSteIf->addLeafUInt64("speed", speed);
	}
#endif /* OPTIONAL_ENABLE_SPEED */

	//    +--ro statistics
	createStatistics(dataSteIf, ethName);

#if defined (ENABLE_TEST_AUGMENT_1)
	//    +--rw ip:ipv4!
	createIpv4(dataSteIf, ipAddr);
#endif

#if defined (ENABLE_ALL_AUGMENT)
	//    +--rw ip:ipv6!
#if defined (OPTIONAL_SUPPORT_IPV6)
	createIpv6(dataSteIf);
#endif /* OPTIONAL_SUPPORT_IPV6 */
#endif

	/*
	 *         +--rw o-ran-int:port-reference
	 *            +--rw o-ran-int:port-name?   leafref  leafref: /hw:hardware/component/name
	 *            +--rw o-ran-int:port-number? uint8
	 */
	std::shared_ptr<ILeafContainer> dataPortRef = dataSteIf->addContainerList(modORanInt + ":port-reference");
	dataPortRef->addLeafInt(modORanInt + ":port-number", portNumber) ;

	// Augmented O-RAN interfaces (o-ran-int) module path
	YangPath pathORanInt;
	pathORanInt.addModule(modORanInt);

	// augment from o-ran-int, when "if:type = 'ianaift:ethernetCsmacd'" OR "if:type = 'ianaift:l2vlan'"
	//    +--ro o-ran-int:last-cleared?     yang:date-and-time
// ToDo: This does not work. May have to set augmented ro parameters in the actual module.
#if defined (OPTIONAL_ENABLE_STATS_COUNTERS)
	//dataSteIf->addLeaf(pathORanInt.pathParam() + "last-cleared", currentTime);
#endif /* OPTIONAL_ENABLE_STATS_COUNTERS */
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::createStatistics(std::shared_ptr<ILeafContainer> dataSte,
                                                             const std::string & ethName)
{
	// +--ro statistics
	std::shared_ptr<ILeafContainer> dataSteStats = dataSte->addContainer("statistics");

	//    +--ro discontinuity-time  yang:date-and-time

	// Callback to get discontinuity time
	auto discontinuityTimeFunc = [this, ethName](std::string name) -> std::string {
		return mDiscontinuityTime[ethName];
	};
	dataSteStats->addLeaf("discontinuity-time", discontinuityTimeFunc);

#if defined (OPTIONAL_ENABLE_STATS_COUNTERS)
	//    +--ro in-octets?          yang:counter64
	auto inOctectsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt64("in-octets", inOctectsFunc);

	//    +--ro in-unicast-pkts?    yang:counter64
	auto inUnicastPktsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt64("in-unicast-pkts", inUnicastPktsFunc);

	//    +--ro in-broadcast-pkts?  yang:counter64
	auto inBroadcastPktsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt64("in-broadcast-pkts", inBroadcastPktsFunc);

	//    +--ro in-multicast-pkts?  yang:counter64
	auto inMulticastPktsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt64("in-multicast-pkts", inMulticastPktsFunc);

	//    +--ro in-discards?        yang:counter32
	auto inDiscardsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt32("in-discards", inDiscardsFunc);

	//    +--ro in-errors?          yang:counter32
	auto inErrorsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt32("in-errors", inErrorsFunc);

	//    +--ro in-unknown-protos?  yang:counter32
	auto inUnknownProtosFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt32("in-unknown-protos", inUnknownProtosFunc);

	//    +--ro out-octets?         yang:counter64
	auto outOctectsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt64("out-octets", outOctectsFunc);

	//    +--ro out-unicast-pkts?   yang:counter64
	auto outUnicastPktsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt64("out-unicast-pkts", outUnicastPktsFunc);

	//    +--ro out-broadcast-pkts? yang:counter64
	auto outBroadcastPktsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt64("out-broadcast-pkts", outBroadcastPktsFunc);

	//    +--ro out-multicast-pkts? yang:counter64
	auto outMulticastPktsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt64("out-multicast-pkts", outMulticastPktsFunc);

	//    +--ro out-discards?       yang:counter32
	auto outDiscardsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt32("out-discards", outDiscardsFunc);

	//    +--ro out-errors?         yang:counter32
	auto outErrorsFunc = [this, ethName](std::string name) -> std::string {
		return 0;
	};
	dataSteStats->addLeafUInt32("out-errors", outErrorsFunc);
#endif /* OPTIONAL_ENABLE_STATISTICS */
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::createIpv4(std::shared_ptr<ILeafContainer> dataSte,
                                                       const std::string & ipAddr)
{
	// +--rw ip:ipv4!
	YangPath pathIpv(modIp, "ipv4");
	std::shared_ptr<ILeafContainer> dataSteIpv = dataSte->addContainer(pathIpv.parameter());	// ip:ipv4 container for state data (ro)

	//    +--rw ip:address* [ip]
	//YangPath pathAddrIp(modIp, "address");
	YangPath pathAddrIp("address");
	std::shared_ptr<ILeafContainer> dataSteIpvAddr = dataSteIpv->addContainerList(pathAddrIp.parameter());	// ip:address container for state data (ro)

	//       +--rw ip:ip             inet:ipv4-address-no-zone
	dataSteIpvAddr->addLeaf(pathAddrIp.pathParam() + "ip", ipAddr);	// Add key as state data

	// augment from ip
	pathAddrIp.addModule(modIp);

	//       +--ro ip:origin?        ip-address-origin
	dataSteIpvAddr->addLeaf(pathAddrIp.pathParam() + "origin", "other");

#if !defined (ENABLE_TEST_AUGMENT_1)
#if defined (ENABLE_NEIGHBOR_ADDRESS)
	if (!ipNeighborAddr.empty())
	{
		//    +--rw ip:neighbor* [ip]
		YangPath pathNeighborIp(modIp, "neighbor");
		std::shared_ptr<ILeafContainer> dataSteIpvNeighbor = dataSteIpv->addContainerList(pathNeighborIp.parameter());	// ip:neighbor container for state data (ro)

		//       +--rw ip:ip                  inet:ipv4-address-no-zone
		pathNeighborIp->addLeaf(pathNeighborIp.pathParam() + "ip", ipNeighborAddr);	// Add key as state data

		// augment from ip
		pathNeighborIp.addModule(modIp);

		//       +--ro ip:origin?        neighbor-origin
		dataSteIpvNeighbor->addLeaf(pathNeighborIp.pathParam() + "origin", "other");
	}
#endif /* ENABLE_NEIGHBOR_ADDRESS */
#endif /* ENABLE_TEST_AUGMENT_1 */
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::createIpv6(std::shared_ptr<ILeafContainer> dataSte)
{
	// +--rw ip:ipv6!
	YangPath pathIpv(modIp, "ipv6");
	std::shared_ptr<ILeafContainer> dataSteIpv = dataSte->addContainer(pathIpv.parameter());	// ip:ipv6 container for state data (ro)

	//    +--rw ip:address* [ip]
	YangPath pathAddr(modIp, "address");
	std::shared_ptr<ILeafContainer> dataSteIpvAddr = dataSteIpv->addContainerList(pathAddr.parameter());	// ip:address container for state data (ro)

	//       +--ro ip:origin?        ip-address-origin
	//       +--ro ip:status?        enumeration
	dataSteIpvAddr->addLeaf(pathAddr.pathParam() + "origin", "other");
	dataSteIpvAddr->addLeaf(pathAddr.pathParam() + "status", "preferred");

#if defined (ENABLE_NEIGHBOR_ADDRESS)
	//    +--rw ip:neighbor* [ip]
	YangPath pathAddr(modIp, "neighbor");
	std::shared_ptr<ILeafContainer> dataSteIpvNeighbor = dataSteIpv->addContainerList(pathAddr.parameter());	// ip:address container for state data (ro)

	//       +--ro ip:origin?             neighbor-origin
	//       +--ro ip:is-router?          empty
	//       +--ro ip:state?              enumeration
	dataSteIpvNeighbor->addLeaf(pathAddr.pathParam() + "origin", "other");
	dataSteIpvNeighbor->addLeaf(pathAddr.pathParam() + "is-router", "");
	dataSteIpvNeighbor->addLeaf(pathAddr.pathParam() + "state", "incomplete");
#endif /* ENABLE_NEIGHBOR_ADDRESS */
}

//=============================================================================================================
// PRIVATE - Configuration data
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfInterfaces::addInterface(const std::string & ethName,
                                                         const std::string & desc,
                                                         UINT8 portNumber,
                                                         const std::string & macAddr,
                                                         const std::string & ipAddrV4,
                                                         const std::string & ipAddrV6,
                                                         UINT8 prefixLength,
                                                         bool isVlan,
                                                         UINT16 vlanId,
                                                         const std::string & baseEthName)
{
	bool result = true;

	// Current timestamp
	time_t rawtime;
	time(&rawtime);
	std::string currentTime = YangUtils::getDateTime(rawtime);

	// Initialise timestamps to current time
	mDiscontinuityTime[ethName] = currentTime;
	mLastChangeTime[ethName] = currentTime;	// ToDo: Register for state change. Set timestamp when state changes.

	// Map of config data (rw)
	std::map<std::string, std::string> dataCfg;

	// +--rw interface* [name]
	YangPath pathIf(mPathParent);
	std::pair<std::string, std::string> keyInterface("name", ethName);
	pathIf.add("interface", keyInterface); 	// Base path: <pathParent>/interface[name='<ethName>']

	//    +--rw name                        string
	//dataCfg["name"] = ethName;             	// Key is set automatically, when entries added

	//    +--rw description?                string
	dataCfg["description"] = desc;

	//    +--rw type                        identityref
	if (isVlan)
		dataCfg["type"] = "iana-if-type:l2vlan";
	else
		dataCfg["type"] = "iana-if-type:ethernetCsmacd";

	//    +--rw enabled?                    boolean
	dataCfg["enabled"] = "true";

#if 0
	//    +--rw link-up-down-trap-enable?   enumeration {if-mib}?
	if (isModuleFeatureEnabled(FEATURE_IFMIB))
		dataCfg["link-up-down-trap-enable"] = "disabled";

#if defined (ENABLE_TEST_AUGMENT_1)
	//    +--rw ip:ipv4!
	addIpv4(dataCfg, ipAddrV4);
#endif /* ENABLE_TEST_AUGMENT_1 */

#if defined (ENABLE_ALL_AUGMENT)
	//    +--rw ip:ipv6!
#if defined (OPTIONAL_SUPPORT_IPV6)
	addIpv6(dataCfg, ipAddrV6, prefixLength);
#endif /* OPTIONAL_SUPPORT_IPV6 */
#endif
#endif

	// Augmented O-RAN interfaces (o-ran-int) module path
	YangPath pathORanInt;
	pathORanInt.addModule(modORanInt);

	// augment from o-ran-int, when "if:type = 'ianaift:l2vlan'"
	//    +--rw o-ran-int:base-interface?   if:interface-ref
	//    +--rw o-ran-int:vlan-id?          uint16
	if (isVlan)
	{
		if(!baseEthName.empty())
		{
			dataCfg[pathORanInt.pathParam() + "base-interface"] = baseEthName;
		}
		dataCfg[pathORanInt.pathParam() + "vlan-id"] = std::to_string(vlanId);
	}
#if 0

#if defined (ENABLE_ALL_AUGMENT)
	// augment from o-ran-int, when "if:type = 'ianaift:ethernetCsmacd'"
	//    +--rw o-ran-int:l2-mtu?           uint16
	//    +--rw o-ran-int:vlan-tagging?     boolean
	//    +--rw o-ran-int:class-of-service
	//    +--rw o-ran-int:alias-macs*       yang:mac-address {ALIASMAC-BASED-CU-PLANE}?
	else
	{
		dataCfg[pathORanInt.pathParam() + "l2-mtu"] = std::to_string(1500);
		dataCfg[pathORanInt.pathParam() + "vlan-tagging"] = "false";

#if defined (OPTIONAL_MARKING_COS)
		addClassOfService(dataCfg,
		                  7, // markingUPlane
		                  7, // markingCPlane
		                  2, // markingMPlane
		                  7, // markingSPlane
		                  1, // markingOther
		                  std::map<std::string, UINT8>());
#endif /* OPTIONAL_MARKING_COS */

		if (isModuleFeatureEnabled(FEATURE_ALIASMAC))
			dataCfg[pathORanInt.pathParam() + "alias-macs"] = "00:00:00:00:00:00";
	}
#endif
#endif
	// augment from o-ran-int, when "if:type = 'ianaift:l2vlan'" OR "if:type = 'ianaift:ethernetCsmacd'"
	//    +--rw o-ran-int:mac-address?      yang:mac-address
	//    +--rw o-ran-int:port-reference
	{
		if (!macAddr.empty())
			dataCfg[pathORanInt.pathParam() + "mac-address"] = macAddr;

		if (!isVlan)
			addPortReference(dataCfg, portNumber);
	}

	// Create 'interface' configuration data list entry in sysrepo
	createListEntry(pathIf.pathRoot(), dataCfg);
	usleep(1000);

	// Make 'interface' configuration data pseudo read only
	//makeReadOnly(pathIf.pathRoot());

	// Added another interface
	mNumInterfaces++;

	return result;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::addIpv4(std::map<std::string, std::string> & dataCfg,
                                                    const std::string & ipAddr)
{
	// +--rw ip:ipv4!
	YangPath pathIpv(modIp, "ipv4");

	// augment from ip
	YangPath pathIpvIp(pathIpv);
	pathIpvIp.addModule(modIp);

	//    +--rw ip:enabled?                  boolean
	//    +--rw ip:forwarding?               boolean
	//    +--rw ip:mtu?                      uint16
	dataCfg[pathIpvIp.pathParam() + "enabled"] = "true";
	dataCfg[pathIpvIp.pathParam() + "forwarding"] = "false";
	dataCfg[pathIpvIp.pathParam() + "mtu"] = std::to_string(68);

#if !defined (ENABLE_TEST_AUGMENT_1)
	//    +--rw ip:address* [ip]
	addIpv4Address(dataCfg, pathIpv, ipAddr);

	//    +--rw ip:neighbor* [ip]
#if defined (ENABLE_NEIGHBOR_ADDRESS)
	std::string ipNeighborAddr = "15.15.15.15";
	std::string linkLayerAddr = "15:15:15:15:15:15";
	addIpvNeighbor(dataCfg, pathIpv, ipNeighborAddr, linkLayerAddr);
#endif /* ENABLE_NEIGHBOR_ADDRESS */

	//    +--rw o-ran-int:diffserv-markings {UDPIP-BASED-CU-PLANE}?
#if defined (OPTIONAL_MARKING_DSCP)
	addIpvDscpMarkings(dataCfg,
	                   pathIpv,
	                   18, 	// markingMPlane
	                   46, 	// markingUPlane
	                   46, 	// markingCPlane
	                   46, 	// markingSPlane
	                   0, 	// markingOther
	                   std::map<std::string, UINT8>());
#endif /* OPTIONAL_MARKING_DSCP */
#endif
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::addIpv6(std::map<std::string, std::string> & dataCfg,
                                                    const std::string & ipAddr,
                                                    UINT8 prefixLength)
{
	// +--rw ip:ipv6!
	YangPath pathIpv(modIp, "ipv6");

	//    +--rw ip:enabled?                  boolean
	//    +--rw ip:forwarding?               boolean
	//    +--rw ip:mtu?                      uint32
	dataCfg[pathIpv.pathParam() + "enabled"] = "true";
	dataCfg[pathIpv.pathParam() + "forwarding"] = "false";
	dataCfg[pathIpv.pathParam() + "mtu"] = std::to_string(1280);

	//    +--rw ip:address* [ip]
	addIpv6Address(dataCfg, pathIpv, ipAddr, prefixLength);

#if defined (ENABLE_NEIGHBOR_ADDRESS)
	//    +--rw ip:neighbor* [ip]
	std::string neighborAddr = "2525::2525:2525:2525:2525";
	std::string linkLayerAddr = "25:25:25:25:25:25";
	addIpvNeighbor(dataCfg, pathIpv, neighborAddr, linkLayerAddr);
#endif /* ENABLE_NEIGHBOR_ADDRESS */

	//    +--rw ip:dup-addr-detect-transmits? uint32
	dataCfg[pathIpv.pathParam() + "dup-addr-detect-transmits"] = std::to_string(1);

	//    +--rw ip:autoconf
	addIpv6Autoconf(dataCfg, pathIpv);

	//    +--rw o-ran-int:diffserv-markings {UDPIP-BASED-CU-PLANE}?
#if defined (OPTIONAL_MARKING_DSCP)
	addIpvDscpMarkings(dataCfg,
	                   pathIpv,
	                   18, 	// markingMPlane
	                   46, 	// markingUPlane
	                   46, 	// markingCPlane
	                   46, 	// markingSPlane
	                   0, 	// markingOther
	                   std::map<std::string, UINT8>());
#endif /* OPTIONAL_MARKING_DSCP */
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::addClassOfService(std::map<std::string, std::string> & dataCfg,
                                                              UINT8 markingUPlane,
                                                              UINT8 markingCPlane,
                                                              UINT8 markingMPlane,
                                                              UINT8 markingSPlane,
                                                              UINT8 markingOther,
                                                              std::map<std::string, UINT8> markingEnhUPlane)
{
	// +--rw o-ran-int:class-of-service
	YangPath pathCoS(modORanInt, "class-of-service");

	//    +--rw o-ran-int:u-plane-marking?          pcp
	//    +--rw o-ran-int:c-plane-marking?          pcp
	//    +--rw o-ran-int:m-plane-marking?          pcp
	//    +--rw o-ran-int:s-plane-marking?          pcp
	//    +--rw o-ran-int:other-marking?            pcp
	dataCfg[pathCoS.pathParam() + "u-plane-marking"] = std::to_string(markingUPlane);
	dataCfg[pathCoS.pathParam() + "c-plane-marking"] = std::to_string(markingCPlane);
	dataCfg[pathCoS.pathParam() + "m-plane-marking"] = std::to_string(markingMPlane);
	dataCfg[pathCoS.pathParam() + "s-plane-marking"] = std::to_string(markingSPlane);
	dataCfg[pathCoS.pathParam() + "other-marking"]   = std::to_string(markingOther);

	//    +--rw o-ran-int:enhanced-uplane-markings* [up-marking-name]
	//       +--rw o-ran-int:up-marking-name   string
	//       +--rw o-ran-int:enhanced-marking? pcp
	for (auto marking : markingEnhUPlane)
	{
		YangPath pathEnhMarkings(pathCoS);
		std::pair<std::string, std::string> keyEnhMarkings("up-marking-name", marking.first);
		pathEnhMarkings.add(modORanInt, "enhanced-uplane-markings", keyEnhMarkings); 	// Base path: <pathParent>/enhanced-uplane-markings[up-marking-name='<upMarkingName>']

		//dataCfg[pathEnhMarkings.pathParam() + "up-marking-name"] = marking.first; 	// Key is set automatically, when entries added

		dataCfg[pathEnhMarkings.pathParam() + "enhanced-marking"] = std::to_string(marking.second);
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::addPortReference(std::map<std::string, std::string> & dataCfg,
                                                             UINT8 portNumber)
{
#if defined (OPTIONAL_PORT_REFERENCE)
	// +--rw o-ran-int:port-reference
	YangPath pathPortRef(modORanInt, "port-reference");

	//    +--rw o-ran-int:port-name?   leafref  leafref: /hw:hardware/component/name
// ToDo: This does not work. May need ietf-hardware to be implemented.
	//dataCfg[pathPortRef.pathParam() + "port-name"] = "SFP0";

	//    +--rw o-ran-int:port-number? uint8
	dataCfg[pathPortRef.pathParam() + "port-number"] = std::to_string(portNumber);
#endif /* OPTIONAL_PORT_REFERENCE */
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::addIpv4Address(std::map<std::string, std::string> & dataCfg,
                                                           YangPath & pathIpv,
                                                           const std::string & ipAddr)
{
	if (ipAddr.empty())
		return;

	// +--rw ip:address* [ip]
	YangPath pathIpAddrIp(pathIpv);
	std::pair<std::string, std::string> keyAddr("ip", ipAddr);
	pathIpAddrIp.add("address", keyAddr);
//	pathIpAddrIp.add(modIp, "address", keyAddr);
//	pathIpAddrIp.addModule(modIp);

	//    +--rw ip:ip             inet:ipv4-address-no-zone
	//dataCfg[pathIpAddrIp.pathParam() + "ip"] = ipAddr; 	// Key is set automatically, when entries added

	//    +--rw (subnet)
	//       +--:(prefix-length)
	//       |  +--rw ip:prefix-length? uint8
	//       +--:(netmask)
	//          +--rw ip:netmask?       yang:dotted-quad {ipv4-non-contiguous-netmasks}?
	dataCfg[pathIpAddrIp.pathParam() + "prefix-length"] = std::to_string(0);
	if (isModuleFeatureEnabled(FEATURE_IPV4NETMASK))
	{
		dataCfg[pathIpAddrIp.pathParam() + "netmask"] = std::to_string(0);
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::addIpv6Address(std::map<std::string, std::string> & dataCfg,
                                                           YangPath & pathIpv,
                                                           const std::string & ipAddr,
                                                           UINT8 prefixLength)
{
	if (ipAddr.empty())
		return;

	// +--rw ip:address* [ip]
	YangPath pathIpAddr(pathIpv);
	std::pair<std::string, std::string> keyAddr("ip", ipAddr);
	pathIpAddr.add(modIp, "address", keyAddr);

	//    +--rw ip:ip             inet:ipv6-address-no-zone
	//dataCfg[pathIpAddr.pathParam() + "ip"] = ipAddr; 	// Key is set automatically, when entries added

	//       +--rw ip:prefix-length  uint8
	dataCfg[pathIpAddr.pathParam() + "prefix-length"] = std::to_string(prefixLength);
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::addIpv6Autoconf(std::map<std::string, std::string> & dataCfg,
                                                            YangPath & pathIpv)
{
	// +--rw ip:autoconf
	YangPath pathAutoconf(pathIpv);
	pathAutoconf.add(modIp, "autoconf");

	//    +--rw ip:create-global-addresses?      boolean
	dataCfg[pathAutoconf.pathParam() + "create-global-addresses"] = "true";

	//    +--rw ip:create-temporary-addresses?   boolean {ipv6-privacy-autoconf}?
	//    +--rw ip:temporary-valid-lifetime?     uint32 {ipv6-privacy-autoconf}?
	//    +--rw ip:temporary-preferred-lifetime? uint32 {ipv6-privacy-autoconf}?
	if (isModuleFeatureEnabled(FEATURE_IPV6PRIV))
	{
		dataCfg[pathAutoconf.pathParam() + "create-temporary-addresses"]   = "false";
		dataCfg[pathAutoconf.pathParam() + "temporary-valid-lifetime"]     = std::to_string(604800);
		dataCfg[pathAutoconf.pathParam() + "temporary-preferred-lifetime"] = std::to_string(86400);
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::addIpvNeighbor(std::map<std::string, std::string> & dataCfg,
                                                           YangPath & pathIpv,
                                                           const std::string & ipAddr,
                                                           const std::string & linkLayerAddr)
{
	if (ipAddr.empty())
		return;

	// +--rw ip:neighbor* [ip]
	YangPath pathIpNeighbor(pathIpv);
	std::pair<std::string, std::string> keyNeighbor("ip", ipAddr);
	pathIpNeighbor.add(modIp, "neighbor", keyNeighbor);

	//    +--rw ip:ip                  inet:ipv4-address-no-zone / inet:ipv6-address-no-zone
	//dataCfg[pathIpNeighbor.pathParam() + "ip"] = ipAddr; 	// Key is set automatically, when entries added

	//    +--rw ip:link-layer-address  yang:phys-address
	dataCfg[pathIpNeighbor.pathParam() + "link-layer-address"] = linkLayerAddr;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfInterfaces::addIpvDscpMarkings(std::map<std::string, std::string> & dataCfg,
                                                               YangPath & pathIpv,
                                                               UINT8 markingMPlane,
                                                               UINT8 markingUPlane,
                                                               UINT8 markingCPlane,
                                                               UINT8 markingSPlane,
                                                               UINT8 markingOther,
                                                               std::map<std::string, UINT8> markingEnhUPlane)
{
	// Augmented O-RAN interfaces module path
	YangPath pathORanInt(pathIpv);

	// augment from o-ran-int
	pathORanInt.addModule(modORanInt);

	// +--rw o-ran-int:m-plane-marking?   inet:dscp
	dataCfg[pathORanInt.pathParam() + "m-plane-marking"] = std::to_string(markingMPlane);

	// +--rw o-ran-int:diffserv-markings {UDPIP-BASED-CU-PLANE}?
	if (isModuleFeatureEnabled(FEATURE_UDPIP))
	{
		// Augmented O-RAN interfaces module diffserv-markings container path
		YangPath pathDiffservMarkingORanInt(pathIpv);
		pathDiffservMarkingORanInt.add(modORanInt, "diffserv-markings");
		pathDiffservMarkingORanInt.addModule(modORanInt);

		// o-ran-int is assumed as the parent container is at that level

		//    +--rw o-ran-int:u-plane-marking?          inet:dscp
		//    +--rw o-ran-int:c-plane-marking?          inet:dscp
		//    +--rw o-ran-int:s-plane-marking?          inet:dscp
		//    +--rw o-ran-int:other-marking?            inet:dscp
		dataCfg[pathDiffservMarkingORanInt.pathParam() + "u-plane-marking"] = std::to_string(markingUPlane);
		dataCfg[pathDiffservMarkingORanInt.pathParam() + "c-plane-marking"] = std::to_string(markingCPlane);
		dataCfg[pathDiffservMarkingORanInt.pathParam() + "s-plane-marking"] = std::to_string(markingSPlane);
		dataCfg[pathDiffservMarkingORanInt.pathParam() + "other-marking"]   = std::to_string(markingOther);

		//    +--rw o-ran-int:enhanced-uplane-markings* [up-marking-name]
		//       +--rw o-ran-int:up-marking-name   string
		//       +--rw o-ran-int:enhanced-marking? inet:dscp
		for (auto marking : markingEnhUPlane)
		{
			YangPath pathEnhMarkingsORanInt(pathIpv);
			std::pair<std::string, std::string> keyEnhMarkings("up-marking-name", marking.first);
			pathEnhMarkingsORanInt.add(modORanInt, "enhanced-uplane-markings", keyEnhMarkings); 	// Base path: <pathParent>/enhanced-uplane-markings[up-marking-name='<upMarkingName>']
			pathEnhMarkingsORanInt.addModule(modORanInt);

			//dataCfg[pathEnhMarkingsORanInt.pathParam() + "up-marking-name"] = marking.first; 	// Key is set automatically, when entries added

			dataCfg[pathEnhMarkingsORanInt.pathParam() + "enhanced-marking"] = std::to_string(marking.second);
		}
	}
}

//=============================================================================================================
// PRIVATE - Helper Functions
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<NetDevice> Zcu111FbcOranrrhHandlerIetfInterfaces::getNetDevice(const std::string & name)
{
	std::shared_ptr<NetDevice> netDevice;
	std::vector<std::shared_ptr<NetDevice>> netDevices = NetDevice::getInterfaces();

	for (auto device : netDevices)
	{
		if (device->getName() == name)
		{
			netDevice = device;
			break;
		}
	}

	return netDevice;
}

//-------------------------------------------------------------------------------------------------------------
// ToDo: Move to an module class.
bool Zcu111FbcOranrrhHandlerIetfInterfaces::isModuleFeatureEnabled(const std::string & feature)
{
	bool enabled = moduleMgr()->isFeatureEnabled(YangHandler::name(), feature);

	if(enabled)
	{
		bool fault = false;

#if !defined (SUPPORTED_FEATURE_IFMIB)
		fault |= (feature == FEATURE_IFMIB);
#endif

#if !defined (SUPPORTED_FEATURE_ALIASMAC)
		fault |= (feature == FEATURE_ALIASMAC);
#endif

#if !defined (SUPPORTED_FEATURE_UDPIP)
		fault |= (feature == FEATURE_UDPIP);
#endif

#if !defined (SUPPORTED_FEATURE_IPV4NETMASK)
		fault |= (feature == FEATURE_IPV4NETMASK);
#endif

#if !defined (SUPPORTED_FEATURE_IPV6PRIV)
		fault |= (feature == FEATURE_IPV6PRIV);
#endif

		if (fault)
			eventError("Module %s: %s feature is not supported and is enabled", YangHandler::name().c_str(), feature.c_str());
	}

	return enabled;
}
