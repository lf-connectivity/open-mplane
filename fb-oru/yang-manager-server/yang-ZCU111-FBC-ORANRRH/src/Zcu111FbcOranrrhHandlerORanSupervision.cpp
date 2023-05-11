/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanSupervision.cpp
 * \brief     O-RAN supervision module handler
 *
 *
 * \details   O-RAN supervision module handler
 *
 * This module defines the configuration data and supervision RPCs that are
 * used to detect loss M-Plane and CU-Plane connectivity.
 *
 * module: o-ran-supervision
 *   +--rw supervision
 *      +--rw cu-plane-monitoring!
 *         +--rw configured-cu-monitoring-interval? uint8
 *
 * rpcs:
 *   +--x supervision-watchdog-reset
 *      +--w input
 *      |  +--w supervision-notification-interval? uint16
 *      |  +--w guard-timer-overhead?              uint16
 *      +--ro output
 *         +--ro next-update-at? yang:date-and-time
 *
 * notifications:
 *   +--n supervision-notification
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "stringfunc.hpp"
#include "ILeafContainer.h"

#include "SysrepoUtils.h"
#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerORanSupervision.h"

using namespace Mplane;

//=============================================================================================================
// Definitions
//=============================================================================================================

// Enables CU monitoring support
//#define SUPPORT_CU_MONITORING

// The interval in seconds at which supervision notifications are sent.
// If not specified the default value of 60 seconds shall apply.
#define DEFAULT_NOTIF_INTERVAL  60

// This is overhead added to the supervision timer used to calculate the
// supervision watchdog timer.
// If not specified the default value of 10 seconds shall apply.
#define DEFAULT_GUARD_TMR_OVERHEAD  10

// This value corresponds to the configured value of the timer used by the
// O-RU to monitor the C/U plane connection.
// If not specified the default value of 160 milliseconds shall apply.
#define DEFAULT_CU_MONITORING_INTERVAL   160
#define CU_MONITORING_INTERVAL_DISABLED  0	// 0ms to disable CU plane monitoring
#define CU_MONITORING_INTERVAL_MIN       0
#define CU_MONITORING_INTERVAL_MAX       160

// Definition checking
#if (DEFAULT_CU_MONITORING_INTERVAL > CU_MONITORING_INTERVAL_MAX)
#error "Zcu111FbcOranrrhHandlerORanSupervision: Invalid default interval"
#endif
#if (CU_MONITORING_INTERVAL_MIN > CU_MONITORING_INTERVAL_MAX)
#error "Zcu111FbcOranrrhHandlerORanSupervision: Invalid interval range"
#endif
#if (CU_MONITORING_INTERVAL_MAX < 1)
#error "Zcu111FbcOranrrhHandlerORanSupervision: Invalid maximum interval"
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ToDo: Remove this block of definitions when fully tested
#define DISABLE_CU_MONITORING_DURING_INIT  	// Disables CU monitoring during initialisation
#if defined(DISABLE_CU_MONITORING_DURING_INIT)
#undef DEFAULT_CU_MONITORING_INTERVAL
#define DEFAULT_CU_MONITORING_INTERVAL  CU_MONITORING_INTERVAL_DISABLED
#endif /* DISABLE_CU_MONITORING_DURING_INIT */
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================================================
// LOCAL
//=============================================================================================================
const std::string moduleName       = "o-ran-supervision";
const std::string topContainerName = "supervision";

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanSupervision::Zcu111FbcOranrrhHandlerORanSupervision(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo(moduleName, moduleMgr, "Zcu111FbcOranrrhHandlerORanSupervision")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path(topContainerName)))
	, mMPlaneService(IMPlaneConnectivityService::singleton())
	, mCUPlaneMonitor(ICUPlaneMonitor::singleton())
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanSupervision::~Zcu111FbcOranrrhHandlerORanSupervision()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSupervision::initialise()
{
	// ------------------------------------------------------------------------
	// daisychain the initialisations
	// ------------------------------------------------------------------------
	if (!this->YangHandlerSysrepo::initialise())
		return false;

	// ------------------------------------------------------------------------
	// Initialise state data
	// ------------------------------------------------------------------------
	// No state data

	// ------------------------------------------------------------------------
	// Initialise configuration data
	// ------------------------------------------------------------------------

#if defined(SUPPORT_CU_MONITORING)
	// Map of config data (rw)
	std::map<std::string, std::string> dataCfg;

	// +--rw supervision

	// Indicates O-RU supports timer based cu-plane monitoring interval. If
	// this container is NOT present, the operation of the O-RU is undefined.
	//    +--rw cu-plane-monitoring!
	YangPath pathParent(name(), topContainerName);
	pathParent.add("cu-plane-monitoring");

	//       +--rw configured-cu-monitoring-interval? uint8
	UINT8 cuPlaneIntervalMs = DEFAULT_CU_MONITORING_INTERVAL;

	// This value corresponds to the configured value of the timer used by the
	// O-RU to monitor the C/U plane connection.
	//
	// A value of 0 means that the O-RU's shall disable its CU plane monitoring.
	//
	// A NETCONF client should configure the value according to the
	// configuration of the PHY layer and/or C/U plane section types
	// supported and/or any fault tolerant operation. For example:
	//
	// i) when operating with an O-DU supporting non-LAA LTE, this value can
	// be configured to a value according to the repetition time of
	// transmitted reference symbols across the fronthaul interface
	// ii) when operating with an O-DU supporting C-Plane Section Type 0,
	// this value can configured to a value according to the minimum
	// repetition interval of section type 0.
	// iii) when operating with an O-DU supporting fault tolerant operation,
	// this value can be configured according to the fault tolerant heartbeat
	// interval
	dataCfg["configured-cu-monitoring-interval"] = std::to_string(cuPlaneIntervalMs);

	// Create 'supervision' configuration data in sysrepo
	createListEntry(pathParent.pathRoot(), dataCfg);
#else
	UINT8 cuPlaneIntervalMs = CU_MONITORING_INTERVAL_DISABLED;
#endif /* SUPPORT_CU_MONITORING */

	// Make configuration data pseudo read only
		// No pseudo read only configuration data

	// ------------------------------------------------------------------------
	// Register RPC callback
	// ------------------------------------------------------------------------

	// +--x supervision-watchdog-reset
	REGISTER_RPC("supervision-watchdog-reset", Zcu111FbcOranrrhHandlerORanSupervision::rpcSupervisionWatchdogReset);

	// ------------------------------------------------------------------------
	// Register callback for each top level container
	// ------------------------------------------------------------------------
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe();

	// ------------------------------------------------------------------------
	// Initialise M-Plane Service
	// ------------------------------------------------------------------------
	mMPlaneService->setInterval(DEFAULT_NOTIF_INTERVAL);
	mMPlaneService->registerNotifTimerExpired([this]()
	{
		netconfSessionUpNotification();
	});

	// ------------------------------------------------------------------------
	// Initialise C/U-Plane Monitor
	// ------------------------------------------------------------------------
	mCUPlaneMonitor->setIntervalRange(CU_MONITORING_INTERVAL_MIN, CU_MONITORING_INTERVAL_MAX);
	mCUPlaneMonitor->setInterval(cuPlaneIntervalMs);

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanSupervision::valueChange(const std::string & xpath,
                                                         std::shared_ptr<YangParam> oldValue,
                                                         std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanSupervision::valueChange() - '%s'", xpath.c_str());

	// +--rw supervision
	//    +--rw cu-plane-monitoring!
	//       +--rw configured-cu-monitoring-interval? uint8

	// This value corresponds to the configured value of the timer used by the
	// O-RU to monitor the C/U plane connection.
	std::string valueOld;
	std::string valueNew;
	std::string leaf;
	std::string error;

	if (oldValue)
	{
		valueOld = YangParamUtils::toString(oldValue, error);
		std::cerr << " + OLD: " << oldValue->name() << " = " << valueOld << std::endl;
		leaf = leafName(oldValue->name());
	}
	if (newValue)
	{
		valueNew = YangParamUtils::toString(newValue, error);
		std::cerr << " + NEW: " << newValue->name() << " = " << valueNew << std::endl;
		leaf = leafName(newValue->name());
	}

	if ((valueNew.empty()) || (leaf.empty()))
	{
		std::cerr << "No change" << std::endl;
	}
	else
	{
		std::cerr << "'" << leaf << "' change [" << valueOld << "] => [" << valueNew << "]" << std::endl;
		if (leaf == "configured-cu-monitoring-interval")
		{
			// Update C/U monitoring manager
			UINT8 cuPlaneIntervalMs = YangParamUtils::toUint8(newValue, error);
			if (error.empty())
			{
				mCUPlaneMonitor->setInterval(cuPlaneIntervalMs);
			}
			else
			{
				eventError("Zcu111FbcOranrrhHandlerORanSupervision - '%s'", error.c_str());
			}
		}
	}
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSupervision::rpcSupervisionWatchdogReset(std::shared_ptr<sysrepo::Session> session,
                                                                         const std::string& rpcXpath,
                                                                         std::shared_ptr<YangParams> paramsIn,
                                                                         std::shared_ptr<YangParams> paramsOut)
{
//	std::cerr << "RPC session id=" << session->get_id() <<
//	             " nc id=" << session->get_nc_id() <<
//	             " user=" << (session->get_user() == nullptr ? "UNKNOWN" : session->get_user()) <<
//	             std::endl;

	// +--x supervision-watchdog-reset
	//    +--w input
	//    |  +--w supervision-notification-interval? uint16

	// The interval in seconds at which supervision notifications are sent.
	UINT16 notifInterval = DEFAULT_NOTIF_INTERVAL;
	getRpcArg(paramsIn, "supervision-notification-interval", notifInterval);

	//    +--w input
	//    |  +--w guard-timer-overhead?              uint16

	// This is overhead added to the supervision timer used to calculate the
	// supervision watchdog timer.
	UINT16 guardTmrOverhead = DEFAULT_GUARD_TMR_OVERHEAD;
	getRpcArg(paramsIn, "guard-timer-overhead", guardTmrOverhead);

	// Kick M-Plane connectivity Service
	std::string nextUpdateAt;
	mMPlaneService->kick(session->get_nc_id(), notifInterval, guardTmrOverhead, nextUpdateAt);

	if (!nextUpdateAt.empty())
	{
		YangPath pathRpc(name(), "supervision-watchdog-reset");
		pathRpc.add("next-update-at");

		// +--x supervision-watchdog-reset
		//    +--ro output
		//       +--ro next-update-at? yang:date-and-time
		paramsOut->addParam(nextUpdateAt, pathRpc.pathRoot());
	}

	// Reset watchdog timer
	// supervision timer = notification timer + guard-timer-overhead
	//
	// NOTE - The supervision timer MUST not be less that the confirmed
	// timeout timer (when the feature is supported).

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSupervision::getRpcArg(std::shared_ptr<YangParams> params,
                                                       const std::string & param,
                                                       UINT16 & paramVal)
{
	bool success = true;
	UINT16 value = 0;

	// Extract specified parameter from input parameters (No parameter is valid)
	std::map<std::string, std::shared_ptr<YangParam>> mapParams(SysrepoUtils::paramsToMap(params));
	if (mapParams.find(param) != mapParams.end())
	{
		std::string error;
		value = YangParamUtils::toUint16(mapParams[param], error);

		if (error.empty())
		{
			// Valid parameter
			paramVal = value;

			//std::cerr << param << "=" << paramVal << std::endl;

		}
		else
		{
			//std::cerr << "[error] " << param << " - " << error << std::endl;


			// Invalid parameter
			success = false;
		}
	}
	else
	{
		// Parameter not found - leave parameter as is (default)
		//std::cerr << param << "=" << paramVal << " [DEFAULT]" << std::endl;

	}

	return success;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanSupervision::netconfSessionUpNotification()
{
	// Notification to indicate that NETCONF management interface is up
	// and also indicate the values of the timers for this NETCONF session

	logDebugNormal("NETCONF Session UP notification");

	YangPath pathNotif(name(), "supervision-notification");

	// +--n supervision-notification
	std::shared_ptr<YangParams> params(std::make_shared<YangParams>());

	sendNotification(pathNotif.pathRoot(), params);
}
