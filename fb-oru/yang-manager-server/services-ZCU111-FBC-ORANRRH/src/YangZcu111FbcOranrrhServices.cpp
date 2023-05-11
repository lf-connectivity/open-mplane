/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangZcu111FbcOranrrhServices.cpp
 * \brief     Implementation of services interface to create and controls all services
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IBootEnv.h"
#include "IAppOptions.h"
#include "INetworkingService.h"
#include "IPacketSniffer.h"
#include "IYangHandlerMgr.h"
#include "ILinuxPtpService.h"
#include "IBootTimer.h"
#include "IFaultsList.h"
#include "IAlarmsList.h"

#include "YangParamUtils.h"
#include "YangMgrServer.h"
#include "YangMgrService.h"
#include "SysrepoUtils.h"

// for debug
#include "CdiNetworkingService.h"

#include "OranNetAddrDhcp.h"
#include "OranNetAddrDhcpVlan.h"
#include "YangZcu111FbcOranrrhServices.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string ENV_VLANMAC{"ethaddr2"} ;
const std::string ETHBB_DHCP_SCRIPT("/etc/ethbb-udhcpc.sh") ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangZcu111FbcOranrrhServices::YangZcu111FbcOranrrhServices()
	: YangOranrrhServices()
	, mOranFaults(OranFaults::getInstance())	// Add ORAN specific faults
	, mOranAlarms(OranAlarms::getInstance())	// Add ORAN specific alarms
{
	std::string ethcdi(IAppOptions::getInstance()->getOption("ethcdi").toString()) ;
	std::string ethbb(IAppOptions::getInstance()->getOption("ethbb").toString()) ;

	// Task based services
	if (INetworkingService::singleton(ethcdi))
	{
		registerTaskService( std::dynamic_pointer_cast<Task>(INetworkingService::singleton(ethcdi)) ) ;

		// prevent networking service from starting until the application is up
		INetworkingService::singleton(ethcdi)->startEnable("yang", false) ;
		IBootTimer::getInstance()->registerAppCompleteCallback([ethcdi](){
			// can now enable the service
			INetworkingService::singleton(ethcdi)->startEnable("yang", true) ;
		}) ;
	}

#ifndef TEST_BB_ON_CDI
	if (INetworkingService::singleton(ethbb))
	{
		registerTaskService( std::dynamic_pointer_cast<Task>(INetworkingService::singleton(ethbb)) ) ;

		// prevent networking service from starting until the application is up
		INetworkingService::singleton(ethbb)->startEnable("yang", false) ;
		IBootTimer::getInstance()->registerAppCompleteCallback([ethbb](){
			// can now enable the service
			INetworkingService::singleton(ethbb)->startEnable("yang", true) ;
		}) ;
	}
#endif

	if (IPacketSniffer::singleton(ethbb))
	{
		registerTaskService( std::dynamic_pointer_cast<Task>(IPacketSniffer::singleton(ethbb)) ) ;
	}

    // Update the networking service - add the DHCP policy
#ifdef TEST_BB_ON_CDI
	auto ns(INetworkingService::singleton(ethcdi)) ;
#else
	auto ns(INetworkingService::singleton(ethbb)) ;
#endif
	ns->pause() ;

	// YANG
    eventInfo("RRH get YANG manager server");
    std::shared_ptr<YangMgrService> yangService(YangMgrService::singleton()) ;
	std::shared_ptr<YangMgrServer> yangServer(yangService->getYangMgrServer()) ;

    eventInfo("RRH initialise YANG handlers");
    std::shared_ptr<IYangHandlerMgr> yangHandlerMgr(IYangHandlerMgr::create(yangServer)) ;
    if (!yangHandlerMgr->initialise())
    {
    	eventError("RRH unable to initialise YANG handlers") ;
    }

    // Add ORAN DHCP with vlan search if we have a VLAN MAC, otherwise we can only use the standard interface
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	std::string vlanMac(bootEnv->getVar(ENV_VLANMAC)) ;

#ifdef OFF_TARGET
	vlanMac = "00:33:44:55:66:77" ;
#endif

	// Get the vlan search values

	//	module: o-ran-mplane-int
	//	  +--rw mplane-info
	//		 +--rw searchable-mplane-access-vlans-info
	//		 |  +--rw searchable-access-vlans*   vlan-id
	//		 |  +--rw vlan-range
	//		 |     +--rw lowest-vlan-id?    vlan-id
	//		 |     +--rw highest-vlan-id?   vlan-id
	std::map<std::string, std::shared_ptr<YangParam>> params(
		SysrepoUtils::getParams(yangServer, "/o-ran-mplane-int:mplane-info/searchable-mplane-access-vlans-info//.")
	) ;

	int startVlan(SysrepoUtils::paramValUInt16(params, "lowest-vlan-id")) ;
	int endVlan(SysrepoUtils::paramValUInt16(params, "highest-vlan-id")) ;
	std::vector<unsigned> vlanList ;
	for (auto val : params)
	{
		if (val.first.find("searchable-access-vlans") == std::string::npos)
			continue ;

		std::string error ;
		vlanList.push_back(YangParamUtils::toUint16(val.second, error)) ;
	}

	// Can only do a VLAN search if we have the start/end OR have a list
	bool doVlanSearch(false) ;
	if ( (startVlan > 0) && (endVlan > 0) )
		doVlanSearch = true ;
	if (!vlanList.empty())
		doVlanSearch = true ;

	auto policy(ns->getNetAddrPolicy()) ;
	if (!vlanMac.empty() && doVlanSearch)
	{
		// vlan tag search
		auto dhcpAlloc(std::make_shared<OranNetAddrDhcpVlan>(policy->interface(), vlanMac, ETHBB_DHCP_SCRIPT)) ;
		policy->addAllocator(dhcpAlloc) ;

		// set search params
		if ( (startVlan > 0) && (endVlan > 0) )
			dhcpAlloc->setSearchLimits(startVlan, endVlan) ;
		if (!vlanList.empty())
			dhcpAlloc->setVlan(vlanList) ;

		// Register the callback for when a valid vlan is found
		dhcpAlloc->registerVlanCallback([this, yangServer](unsigned vlanId){

			// Save this vlan into the list of searchable vlans
			std::string value(std::to_string(vlanId)) ;
			std::string xpath("/o-ran-mplane-int:mplane-info/searchable-mplane-access-vlans-info/searchable-access-vlans[.='" + value + "']") ;
			SysrepoUtils::setItemStr(yangServer, xpath, value) ;

		}) ;
	}
	else
	{
		// Use the untagged interface
		policy->addAllocator(std::make_shared<OranNetAddrDhcp>(policy->interface(), "ORAN-DHCP", ETHBB_DHCP_SCRIPT)) ;
	}

	ns->restart() ;

	// ptp
	std::shared_ptr<ILinuxPtp> linuxPtp = ILinuxPtp::singleton();
	registerServiceInsert( std::dynamic_pointer_cast<Service>(linuxPtp));
	linuxPtp->initialise();

#if 0
	// Show full list of faults
	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance());
//	faultsList->show();
	faultsList->showNamesAndIds();
#endif
#if 0
	// Show full list of alarms
	std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance());
//	alarmsList->show();
	alarmsList->showNamesAndIds();
#endif

}

//-------------------------------------------------------------------------------------------------------------
YangZcu111FbcOranrrhServices::~YangZcu111FbcOranrrhServices()
{
}
