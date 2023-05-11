/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanProcessingElement.cpp
 * \brief     O-RAN processing element module handler
 *
 *
 * \details   O-RAN processing element module handler
 *
 * Defines the mapping between transport flows and arbitrary O-RAN processing elements. A processing element
 * may be then defined for handling connectivity or delay procedures, or defined with a corresponding eaxcid
 * for CU plane operations
 *
 * module: o-ran-processing-element
 *   +--rw processing-elements
 *      +--ro maximum-number-of-transport-flows? uint16
 *      +--rw transport-session-type?            enumeration
 *      +--rw enhanced-uplane-mapping!
 *      |  +--rw uplane-mapping* [up-marking-name]
 *      |     +--rw up-marking-name  string
 *      |     +--rw (up-markings)?
 *      |        +--:(ethernet)  when "(../../transport-session-type = 'ALIASMAC-INTERFACE') or (../../transport-session-type = 'ETH-INTERFACE')";
 *      |        |  +--rw up-cos-name?     leafref: /if:interfaces/if:interface/o-ran-int:class-of-service/o-ran-int:enhanced-uplane-markings/o-ran-int:up-marking-name
 *      |        +--:(ipv4)  when "(../../transport-session-type = 'UDPIP-INTERFACE')";
 *      |        |  +--rw upv4-dscp-name?  leafref: /if:interfaces/if:interface/ip:ipv4/o-ran-int:diffserv-markings/o-ran-int:enhanced-uplane-markings/o-ran-int:up-marking-name
 *      |        +--:(ipv6)  when "(../../transport-session-type = 'UDPIP-INTERFACE')";
 *      |           +--rw upv6-dscp-name?  leafref: /if:interfaces/if:interface/ip:ipv6/o-ran-int:diffserv-markings/o-ran-int:enhanced-uplane-markings/o-ran-int:up-marking-name
 *      +--rw ru-elements* [name]
 *         +--rw name            string
 *         +--rw transport-flow
 *            +--rw interface-name? leafref: /if:interfaces/if:interface/if:name
 *            +--rw aliasmac-flow {o-ran-int:ALIASMAC-BASED-CU-PLANE}?  when "../../../transport-session-type = 'ALIASMAC-INTERFACE'";
 *            |  +--rw ru-aliasmac-address  leafref: /if:interfaces/if:interface[if:name = current()/../../interface-name]/o-ran-int:alias-macs
 *            |  +--rw vlan-id?             leafref: /if:interfaces/if:interface[if:name = current()/../../interface-name]/o-ran-int:vlan-id
 *            |  +--rw o-du-mac-address     yang:mac-address
 *            +--rw eth-flow  when "../../../transport-session-type = 'ETH-INTERFACE'";
 *            |  +--rw ru-mac-address    leafref: /if:interfaces/if:interface[if:name = current()/../../interface-name]/o-ran-int:mac-address
 *            |  +--rw vlan-id           leafref: /if:interfaces/if:interface[if:name = current()/../../interface-name]/o-ran-int:vlan-id
 *            |  +--rw o-du-mac-address  yang:mac-address
 *            +--rw udpip-flow  when "(../../transport-session-type = 'UDPIP-INTERFACE')";
 *               +--rw (address)
 *               |  +--:(ru-ipv4-address)-elk
 *               |  |  +--rw ru-ipv4-address?         leafref: /if:interfaces/if:interface[if:name = current()/../../interface-name]/ip:ipv4/ip:address/ip:ip
 *               |  +--:(ru-ipv6-address)
 *               |     +--rw ru-ipv6-address?         leafref: /if:interfaces/if:interface[if:name = current()/../../interface-name]/ip:ipv6/ip:address/ip:ip
 *               +--rw o-du-ip-address          inet:ip-address
 *               +--rw ru-ephemeral-udp-port    inet:port-number
 *               +--rw o-du-ephemeral-udp-port  inet:port-number
 *               +--rw ecpri-destination-udp    inet:port-number
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "stringfunc.hpp"
#include "ILeafContainer.h"

#include "SysrepoUtils.h"
#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerORanProcessingElement.h"

using namespace Mplane;


//=============================================================================================================
// LOCAL
//=============================================================================================================

// ToDo: Is there anywhere that this value is stored already
#define MAX_NUM_TRANSPORT_FLOWS  128

const std::string moduleName       = "o-ran-processing-element";
const std::string topContainerName = "processing-elements";

const std::string modInt     = "ietf-interfaces";
const std::string modORanInt = "o-ran-interfaces";

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

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanProcessingElement::Zcu111FbcOranrrhHandlerORanProcessingElement(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo(moduleName, moduleMgr, "Zcu111FbcOranrrhHandlerORanProcessingElement")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path(topContainerName)))
	, mCUPlaneMonitor(ICUPlaneMonitor::singleton())
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanProcessingElement::~Zcu111FbcOranrrhHandlerORanProcessingElement()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanProcessingElement::initialise()
{
	// ------------------------------------------------------------------------
	// daisychain the initialisations
	// ------------------------------------------------------------------------
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	// ------------------------------------------------------------------------
	// Initialise state data
	// ------------------------------------------------------------------------

	// Container for 'processing-elements' state data (ro)
	std::shared_ptr<ILeafContainer> dataSte(mCallback);

	//   +--ro maximum-number-of-transport-flows? uint16
	dataSte->addLeafUInt16("maximum-number-of-transport-flows", MAX_NUM_TRANSPORT_FLOWS);

	// ------------------------------------------------------------------------
	// Initialise configuration data
	// ------------------------------------------------------------------------

	// Map of config data (rw)
	std::map<std::string, std::string> dataCfg;

	// +--rw processing-elements
	YangPath pathParent(name(), topContainerName);

	//   +--rw transport-session-type?            enumeration
	dataCfg["transport-session-type"] = "ETH-INTERFACE";

	// Create 'processing-elements' configuration data list entry in sysrepo
	createListEntry(pathParent.pathRoot(), dataCfg);

	// Make configuration data pseudo read only
		// No pseudo read only configuration data

#if 0
// Testing
	std::string namePe;
	std::string nameIf;
	std::string duMac;
	nameIf = "em1";
	duMac = "10:10:10:10:10:10";
	addRuProcessingElement(namePe, nameIf, duMac);
	nameIf = "em1.1";
	duMac = "12:12:12:12:12:12";
	addRuProcessingElement(namePe, nameIf, duMac);
	namePe = "PE25";
	nameIf = "em1.2";
	duMac = "14:14:14:14:14:14";
	addRuProcessingElement(namePe, nameIf, duMac);
#endif

	// ------------------------------------------------------------------------
	// Register callback for each top level container
	// ------------------------------------------------------------------------
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe();

	// ------------------------------------------------------------------------
	// Initialise C/U-Plane Monitor
	// ------------------------------------------------------------------------
	mCUPlaneMonitor->setStreamLimit(MAX_NUM_TRANSPORT_FLOWS);

	return true;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanProcessingElement::addRuProcessingElement(const std::string & ruElement,
                                                                          const std::string & vlanIf,
                                                                          const std::string & duMac)
{
	std::string errorStr("Unable to find '" + vlanIf + "' virtual network interface");

	// Validate RU element name
	std::string ruElementName = ruElement;

	// Create ru-processing name from the interface port number - PE_<vlanIf>.
	if (ruElement.empty())
	{
		ruElementName = "PE_" + vlanIf;
	}
	eventInfo("Adding ORAN processing element '%s' [interface-name='%s', DU-MAC=%s]",
			ruElementName.c_str(), vlanIf.c_str(), duMac.c_str());

	// Map of config data (rw)
	std::map<std::string, std::string> dataCfg;

	// +--rw processing-elements
	YangPath pathParent(name(), topContainerName);

	// Get list of interfaces
	YangPath pathInterfaces(modInt, "interfaces");
	std::map<std::string, std::map<std::string, std::string>> interfaces(getInterfaces(pathInterfaces));

	// Search for specified vlan interface
	for (auto interface : interfaces)
	{
		//std::cerr << "interface.first " << interface.first << std::endl;
		if (interface.first == vlanIf)
		{
			// Found interface
			errorStr.clear();

			// Ignore non-virtual interfaces
			std::string interfaceTypeStr = getInterfaceParameter(vlanIf, YangPath("type"));
			if (interfaceTypeStr != "iana-if-type:l2vlan")
			{
				errorStr = "Not a virtual network interface [Type='" + interfaceTypeStr + "']";
				break;
			}

			// Validate the virtual interface ID
			bool validVlanId = false;
			std::string vlanIdStr = getInterfaceParameter(vlanIf, YangPath(modORanInt, "vlan-id"));
			extractInt(vlanIdStr, validVlanId);
			if (!validVlanId)
			{
				errorStr = "Invalid virtual network interface parameter [ID='" + vlanIdStr + "']";
				break;
			}

			//   +--rw ru-elements* [name]
			std::pair<std::string, std::string> keyRuElements("name", ruElementName);
			YangPath pathRuElements("ru-elements", keyRuElements);  	// ru-elements[name='<ruElementName>']

			//      +--rw name            string
			//dataCfg[pathRuElements.pathParam() + "name"] = ruElementName;	// Key is set automatically, when entries added

			//      +--rw transport-flow
			YangPath pathTransportFlow(pathRuElements);
			pathTransportFlow.add("transport-flow");	// ru-elements[name='<ruElementName>']/transport-flow

			//         +--rw interface-name? leafref: /if:interfaces/if:interface/if:name
			dataCfg[pathTransportFlow.pathParam() + "interface-name"] = vlanIf;

			//         +--rw aliasmac-flow {o-ran-int:ALIASMAC-BASED-CU-PLANE}?  when "../../../transport-session-type = 'ALIASMAC-INTERFACE'";
			// Not present. transport-session-type != 'ALIASMAC-INTERFACE'

			//         +--rw eth-flow  when "../../../transport-session-type = 'ETH-INTERFACE'";
			YangPath pathEthFlow(pathTransportFlow);
			pathEthFlow.add("eth-flow");	// ru-elements[name='<ruElementName>']/eth-flow

			//         |  +--rw ru-mac-address    leafref: /if:interfaces/if:interface[if:name = current()/../../interface-name]/o-ran-int:mac-address
			std::string ruMac = getInterfaceParameter(vlanIf, YangPath(modORanInt, "mac-address"));
			dataCfg[pathEthFlow.pathParam() + "ru-mac-address"] = ruMac;

			//         |  +--rw vlan-id           leafref: /if:interfaces/if:interface[if:name = current()/../../interface-name]/o-ran-int:vlan-id
			dataCfg[pathEthFlow.pathParam() + "vlan-id"] = vlanIdStr;

			//         |  +--rw o-du-mac-address  yang:mac-address
			dataCfg[pathEthFlow.pathParam() + "o-du-mac-address"] = duMac;

			//         +--rw udpip-flow  when "(../../transport-session-type = 'UDPIP-INTERFACE')";
			// Not present. transport-session-type != 'UDPIP-INTERFACE'

			// Create 'processing-elements' configuration data list entry in sysrepo
			createListEntry(pathParent.pathRoot(), dataCfg);
			break;
		}
	}

	if (!errorStr.empty())
	{
		eventError("Networking[%s]: %s", ruElementName.c_str(), errorStr.c_str());
	}
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanProcessingElement::valueChange(const std::string & xpath,
                                                               std::shared_ptr<YangParam> oldValue,
                                                               std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanProcessingElement::valueChange() - %s", xpath.c_str());
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string>> Zcu111FbcOranrrhHandlerORanProcessingElement::getInterfaces(YangPath pathInterfaces)
{
	std::map<std::string, std::map<std::string, std::string>> interfaces;

	// Get list of interfaces
	pathInterfaces.add("interface");
	interfaces = getKeyValues(pathInterfaces.pathRootParam(true));

	return interfaces;
}

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111FbcOranrrhHandlerORanProcessingElement::getInterfaceParameter(const std::string & interface,
                                                                                YangPath pathParam)
{
	std::string paramStr;
	std::map<std::string, std::shared_ptr<YangParam>> params;

	// Setup path to list of interface
	YangPath pathInterface(modInt, "interfaces");
	std::pair<std::string, std::string> keyInterface("name", interface);
	pathInterface.add("interface", keyInterface);  	// interface[name='<interface>']

	// Get interface parameter
	params = getParams(pathInterface.pathRootParam(true));
	paramStr = SysrepoUtils::paramVal(params, pathParam.parameter());

	return paramStr;
}
