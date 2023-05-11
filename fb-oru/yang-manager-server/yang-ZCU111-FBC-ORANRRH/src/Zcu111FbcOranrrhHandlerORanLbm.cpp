/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanLbm.cpp
 * \brief     O-RAN radio loop-back module (LBM) handler
 *
 *
 * \details   O-RAN radio loop-back module (LBM) handler
 *
 * This module defines the module capabilities for the O-RAN Radio loop-back protocol (IEEE 802.1ag).
 * It is derived from MEF-38 (Service OAM Fault Management YANG Modules, April 2012)
 *
 * module: o-ran-lbm
 *   +--rw md-data-definitions
 *      +--rw maintenance-domain* [id]
 *         +--rw id                       string
 *         +--rw name?                    string
 *         +--rw md-level?                md-level-type
 *         +--rw maintenance-association* [id]
 *            +--rw id              string
 *            +--rw name?           string
 *            +--rw component-list* [component-id]
 *               +--rw component-id                       uint32
 *               +--rw name?                              string
 *               +--rw vid*                               leafref: /if:interfaces/if:interface/o-ran-int:vlan-id
 *               +--rw remote-meps*                       mep-id-type
 *               +--rw maintenance-association-end-point* [mep-identifier]
 *                  +--rw mep-identifier        mep-id-type
 *                  +--rw interface             leafref: /if:interfaces/if:interface/if:name
 *                  +--rw primary-vid           leafref: /if:interfaces/if:interface/o-ran-int:vlan-id
 *                  +--rw administrative-state  boolean
 *                  +--ro mac-address?          leafref: /if:interfaces/if:interface/o-ran-int:mac-address
 *                  +--ro loopback
 *                     +--ro replies-transmitted  yang:counter32
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
#include "INetAddr.h"
#include "INetAddrPolicy.h"

#include "SysrepoUtils.h"
#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerORanLbm.h"

using namespace Mplane;

//=============================================================================================================
// Definitions
//=============================================================================================================

//=============================================================================================================
// LOCAL
//=============================================================================================================
const std::string moduleName       = "o-ran-lbm";
const std::string topContainerName = "md-data-definitions";

const std::string modInt = "ietf-interfaces";

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanLbm::Zcu111FbcOranrrhHandlerORanLbm(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo(moduleName, moduleMgr, "Zcu111FbcOranrrhHandlerORanLbm")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path(topContainerName)))
	, mDot1agdMonService(Dot1agdMonService::singleton())
	, mDomainId("DOMAIN01")
	, mDomainName("DomainName")
	, mAssocId("ASSOC01")
	, mAssocName("AssocName")
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanLbm::~Zcu111FbcOranrrhHandlerORanLbm()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanLbm::initialise()
{
	// ------------------------------------------------------------------------
	// daisychain the initialisations
	// ------------------------------------------------------------------------
	if (!this->YangHandlerSysrepo::initialise())
		return false;

	// ------------------------------------------------------------------------
	// Initialise state data
	// ------------------------------------------------------------------------
	// +--rw md-data-definitions
	std::shared_ptr<ILeafContainer> dataSte(mCallback);	// Container for 'md-data-definitions' state data (ro)

	//    +--rw maintenance-domain* [id]
	//       +--rw id                       string
	std::shared_ptr<ILeafContainer> dataSteMaintDom = dataSte->addContainerList("maintenance-domain");
	dataSteMaintDom->addLeaf("id", mDomainId);	// Add key as state data

	//       +--rw maintenance-association* [id]
	//          +--rw id              string
	std::shared_ptr<ILeafContainer> dataSteMaintAssoc = dataSteMaintDom->addContainerList("maintenance-association");
	dataSteMaintAssoc->addLeaf("id", mAssocId);	// Add key as state data

	// ------------------------------------------------------------------------
	// Initialise configuration data
	// ------------------------------------------------------------------------
	// No configuration data to initialise
	// Map of config data (rw)
	std::map<std::string, std::string> dataCfg;

	// +--rw md-data-definitions
	YangPath pathParent(name(), topContainerName);

	//    +--rw maintenance-domain* [id]
	std::pair<std::string, std::string> keyMaintDom("id", mDomainId);
	YangPath pathMaintDom("maintenance-domain", keyMaintDom);  	// maintenance-domain[id='<domainId>']

	//       +--rw id                       string
//	dataCfg[pathMaintDom.pathParam() + "id"] = mDomainId;	// Key is set automatically, when entries added

	//       +--rw name?                    string
	dataCfg[pathMaintDom.pathParam() + "name"] = mDomainName;

	//       +--rw md-level?                md-level-type
	INT32  mdLevel = 0;
	dataCfg[pathMaintDom.pathParam() + "md-level"] = std::to_string(mdLevel);

	//       +--rw maintenance-association* [id]
	YangPath pathMaintAssoc(pathMaintDom);
	std::pair<std::string, std::string> keyMaintAssoc("id", mAssocId);
	pathMaintAssoc.add("maintenance-association", keyMaintAssoc);  	// maintenance-association[id='<assocId>']

	//          +--rw id              string
	//dataCfg[pathMaintAssoc.pathParam() + "id"] = mAssocId;	// Key is set automatically, when entries added

	//          +--rw name?           string
	dataCfg[pathMaintAssoc.pathParam() + "name"] = mAssocName;

	// Create 'md-data-definitions' configuration data in sysrepo
	createListEntry(pathParent.pathRoot(), dataCfg);

	// Make configuration data pseudo read only
		// No pseudo read only configuration data

	// ------------------------------------------------------------------------
	// Register RPC callback
	// ------------------------------------------------------------------------
	// No RPCs

	// ------------------------------------------------------------------------
	// Register callback for each top level container
	// ------------------------------------------------------------------------
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe();

	return true;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanLbm::addMaintenaceDomainEntry(const std::string & ethName, const std::string & macAddr, UINT16 vlanId)
{
	UINT32 componentId = 0;
	std::string componentName("radioCard");
	UINT16 mepIdentifier = 1;	// type:  UINT16, range: 1..8191

	// +--rw md-data-definitions
	std::shared_ptr<ILeafContainer> dataSte(mCallback);	// Container for 'md-data-definitions' state data (ro)

	//    +--rw maintenance-domain* [id]
	//       +--rw id                       string
	std::shared_ptr<ILeafContainer> dataSteMaintDom = dataSte->addContainerList("maintenance-domain");
	dataSteMaintDom->addLeaf("id", mDomainId);	// Add key as state data

	//       +--rw maintenance-association* [id]
	//          +--rw id              string
	std::shared_ptr<ILeafContainer> dataSteMaintAssoc = dataSteMaintDom->addContainerList("maintenance-association");
	dataSteMaintAssoc->addLeaf("id", mAssocId);	// Add key as state data

	//          +--rw component-list* [component-id]
	//             +--rw component-id                       uint32
	std::shared_ptr<ILeafContainer> dataSteCompList = dataSteMaintAssoc->addContainerList("component-list");
	dataSteMaintAssoc->addLeafUInt32("component-id", componentId);	// Add key as state data

	//             +--rw maintenance-association-end-point* [mep-identifier]
	//                +--rw mep-identifier        mep-id-type
	std::shared_ptr<ILeafContainer> dataSteEndPoint = dataSteMaintAssoc->addContainerList("maintenance-association-end-point");
	dataSteEndPoint->addLeafUInt16("mep-identifier", mepIdentifier);	// Add key as state data

	//                +--ro mac-address?          leafref: /if:interfaces/if:interface/o-ran-int:mac-address
	auto macAddrFunc = [this, ethName](std::string name) -> std::string
	{
		// Get the MAC address of the interface
		auto ns(INetworkingService::singleton(ethName)) ;
		auto policy(ns->getNetAddrPolicy()) ;
		std::string macAddr = policy->macAddress();
		if (macAddr.empty())
		{
			eventWarning("LBM[%s]: Invalid MAC address %s", ethName.c_str(), macAddr.c_str());
		}
		eventWarning("LBM[%s]: MAC address %s", ethName.c_str(), macAddr.c_str());

		return macAddr;
	};
	dataSteEndPoint->addLeaf("mac-address", macAddrFunc);

	//                +--ro loopback
	std::shared_ptr<ILeafContainer> dataSteLoopback = dataSteEndPoint->addContainer("loopback");

	//                   +--ro replies-transmitted  yang:counter32
	auto repliesTxdFunc = [this](std::string name) -> std::string {
		std::cerr << "KG DEBUG: '" << name << "'" << std::endl;
		return 0;
	};
	dataSteLoopback->addLeaf("replies-transmitted", repliesTxdFunc);

	// Map of config data (rw)
	std::map<std::string, std::string> dataCfg;

	// +--rw md-data-definitions
	YangPath pathParent(name(), topContainerName);

	//    +--rw maintenance-domain* [id]
	std::pair<std::string, std::string> keyMaintDom("id", mDomainId);
	YangPath pathMaintDom("maintenance-domain", keyMaintDom);  	// maintenance-domain[id='<domainId>']

	//       +--rw id                       string
//	dataCfg[pathMaintDom.pathParam() + "id"] = mDomainId;	// Key is set automatically, when entries added

	//       +--rw name?                    string
	dataCfg[pathMaintDom.pathParam() + "name"] = mDomainName;

	//       +--rw md-level?                md-level-type
	INT32  mdLevel = 0;
	dataCfg[pathMaintDom.pathParam() + "md-level"] = std::to_string(mdLevel);

	//       +--rw maintenance-association* [id]
	YangPath pathMaintAssoc(pathMaintDom);
	std::pair<std::string, std::string> keyMaintAssoc("id", mAssocId);
	pathMaintAssoc.add("maintenance-association", keyMaintAssoc);  	// maintenance-association[id='<assocId>']

	//          +--rw id              string
	//dataCfg[pathMaintAssoc.pathParam() + "id"] = mAssocId;	// Key is set automatically, when entries added

	//          +--rw name?           string
	dataCfg[pathMaintAssoc.pathParam() + "name"] = mAssocName;

	//          +--rw component-list* [component-id]
	YangPath pathCompList(pathMaintAssoc);
	std::pair<std::string, std::string> keyCompList("component-id", std::to_string(componentId));
	pathCompList.add("component-list", keyCompList);  	// component-list[component-id='<componentId>']

	//             +--rw component-id                       uint32
	//dataCfg[pathCompList.pathParam() + "component-id"] = componentId;	// Key is set automatically, when entries added

	//             +--rw name?                              string
	dataCfg[pathCompList.pathParam() + "name"] = componentName;

	//             +--rw vid*                               leafref: /if:interfaces/if:interface/o-ran-int:vlan-id
	dataCfg[pathCompList.pathParam() + "vid"] = std::to_string(vlanId);

#if 0
	UINT16 remoteMeps = 1;	// type:  UINT16, range: 1..8191
	UINT16 primaryVid = 1;// type:  UINT16, range: 1..4094

	//             +--rw remote-meps*                       mep-id-type
	dataCfg[pathCompList.pathParam() + "remote-meps"] = std::to_string(remoteMeps);

	//             +--rw maintenance-association-end-point* [mep-identifier]
	YangPath pathEndPoint(pathCompList);
	std::pair<std::string, std::string> keyEndPoint("mep-identifier", std::to_string(mepIdentifier));
	pathEndPoint.add("maintenance-association-end-point", keyEndPoint);  	// maintenance-association[id='<assocId>']

	//                +--rw mep-identifier        mep-id-type
	//dataCfg[pathEndPoint.pathParam() + "mep-identifier"] = std::to_string(mepIdentifier);	// Key is set automatically, when entries added

	//                +--rw interface             leafref: /if:interfaces/if:interface/if:name
	//dataCfg[pathEndPoint.pathParam() + "interface"] = ;

	//                +--rw primary-vid           leafref: /if:interfaces/if:interface/o-ran-int:vlan-id
	dataCfg[pathCompList.pathParam() + "primary-vid"] = std::to_string(primaryVid);

	//                +--rw administrative-state  boolean
	dataCfg[pathEndPoint.pathParam() + "administrative-state"] = "false";
#endif

	// Create 'md-data-definitions' configuration data in sysrepo
	createListEntry(pathParent.pathRoot(), dataCfg);

	// ------------------------------------------------------------------------
	// Start 802.1ag daemon application
	// ------------------------------------------------------------------------
	startDot1agDaemonApp(ethName);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanLbm::valueChange(const std::string & xpath,
                                                 std::shared_ptr<YangParam> oldValue,
                                                 std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanLbm::valueChange() - '%s'", xpath.c_str());
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanLbm::startDot1agDaemonApp(const std::string & ethName)
{
	// Set daemon to use the correct ethernet interface
	std::string options("-i " + ethName + " -d");
	mDot1agdMonService->setOptions(options);

	// Start 802.1ag daemon application
	mDot1agdMonService->startService();
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanLbm::stopDot1agDaemonApp()
{
	// Stop the daemon application
	mDot1agdMonService->stopService();
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
