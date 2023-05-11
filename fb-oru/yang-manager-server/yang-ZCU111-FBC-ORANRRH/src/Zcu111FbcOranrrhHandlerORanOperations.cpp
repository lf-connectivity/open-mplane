/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanOperations.cpp
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
#include <string>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

#include "IBootEnv.h"
#include "ISystemReboot.h"

#include "YangCarrierMgr.h"
#include "YangMgrServer.h"
#include "YangParamUtils.h"

#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerORanOperations.h"

using namespace Mplane;
using namespace std;

//=============================================================================================================
// LOCAL
//=============================================================================================================


/*!
 * \brief Format a C time structure in a suitable YANG format
 * \param lt C time struct to fomrat
 * \returns A string in a standard yang:date time format
 *
 */
static string TimeToYang(struct tm &lt)
{
	auto utcOffsetMins = lt.tm_gmtoff / 60;		// System gives UTC offset in seconds, YANG wants it in minutes
	auto utcOffsetHours = utcOffsetMins / 60;
	auto utcOffsetMinsOnly = abs(utcOffsetMins % 60);

	char formattedTime[200];
	snprintf(formattedTime, sizeof(formattedTime), "%04d-%02d-%02dT%02d:%02d:%02d%+03ld:%02ld",
			1900 + lt.tm_year, lt.tm_mon + 1, lt.tm_mday, lt.tm_hour, lt.tm_min, lt.tm_sec, utcOffsetHours, utcOffsetMinsOnly);

	return string(formattedTime);
}


/*!
 * \brief Use the product code and board serial number to get a unique hardware instance ID
 * \returns A unique instance ID string
 */
static string MakeUniqueInstanceId()
{
	const string ENV_SERIALNUM{"hwBoardSerialNum"};

	shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	string productCode = PRODUCT_CODE ;
	string serialNumber = bootEnv->getVar(ENV_SERIALNUM) ;
	return productCode + "-" + serialNumber;
}

//=============================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanOperations::Zcu111FbcOranrrhHandlerORanOperations(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo("o-ran-operations", moduleMgr, "Zcu111FbcOranrrhHandlerORanOperations")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path("operational-info")))
{}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanOperations::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false;


	// Find the initial time zone we are in
	time_t t = time(NULL);
	struct tm lt = {0};
	localtime_r(&t, &lt);

	string formattedTime = TimeToYang(lt);
	logDebugNormal("reboot time %s", formattedTime.c_str());

	/*
	 * +--rw operational-info
     +--ro declarations
     |  +--ro ru-instance-id?             string
     |  +--ro supported-mplane-version?   version
     |  +--ro supported-cusplane-version? version
     |  +--ro supported-header-mechanism* [protocol]
     |     +--ro protocol                     enumeration
     |     +--ro ecpri-concatenation-support? boolean
     |     +--ro protocol-version?            version
    +--ro operational-state
     |  +--ro restart-cause?    enumeration
     |  +--ro restart-datetime? yang:date-and-time
    +--rw clock
     |  +--rw timezone-name?       timezone-name
     |  +--rw timezone-utc-offset? int16
     +--rw re-call-home-no-ssh-timer? uint16
	 */



	// Add read only information
	std::shared_ptr<ILeafContainer> declarations = mCallback->addContainer("declarations");
	declarations->addLeaf("ru-instance-id", MakeUniqueInstanceId());
	declarations->addLeaf("supported-mplane-version", "2.00.00");	// Register callback for each top level container
	declarations->addLeaf("supported-cusplane-version", "2.00.00");	// Register callback for each top level container
	std::shared_ptr<ILeafContainer> headerMech = declarations->addContainer("supported-header-mechanism");
	headerMech->addLeaf("protocol", "ECPRI");
	headerMech->addLeaf("ecpri-concatenation-support", "false");
	headerMech->addLeaf("protocol-version", "1.0");

	std::shared_ptr<ILeafContainer> operationalState= mCallback->addContainer("operational-state");
	operationalState->addLeaf("restart-cause", "UNKNOWN");
	operationalState->addLeaf("restart-datetime", formattedTime);

	// Add read write information
	shared_ptr<YangMgrServer> mgr(dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	shared_ptr<RadioDatastoreSysrepo> ds(dynamic_pointer_cast <RadioDatastoreSysrepo> (mgr->dataStore()));
	string path = mCallback->path() + "/clock/timezone-name";
	ds->setItemStr(path, "not-set");
	path = mCallback->path() + "/clock/timezone-utc-offset";
	auto utcOffsetMins = lt.tm_gmtoff / 60;		// System gives UTC offset in seconds, YANG wants it in minutes
	ds->setItemStr(path, to_string(utcOffsetMins));
	path = mCallback->path() + "/re-call-home-no-ssh-timer";
	uint16_t callHomeTimer = 60;
	ds->setItemStr(path, std::to_string(callHomeTimer));
	makeReadOnly(path);

	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe();


	REGISTER_RPC("reset", Zcu111FbcOranrrhHandlerORanOperations::rpcReset) ;

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

/*!
 * \brief Handle <rpc><reset> message, reboot the linux machine
 * \details Only works on a real board, on a simulation it does nothing
 */
bool Zcu111FbcOranrrhHandlerORanOperations::rpcReset(
		std::shared_ptr<sysrepo::Session> session,
		const std::string &rpcXpath,
		std::shared_ptr<YangParams> callList,
		std::shared_ptr<YangParams> retList)
{
#ifndef OFF_TARGET
	// reboot on a real board only
	std::shared_ptr<ISystemReboot> reboot = ISystemReboot::getInstance();
	reboot->now();
#endif
    return true;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanOperations::valueChange(const string &xpath,
		shared_ptr<YangParam> oldValue,
		shared_ptr<YangParam> newValue)
{

	logDebugVerbose("Zcu111FbcOranrrhHandlerORanOperations::valueChange() - %s", xpath.c_str());

	string leaf = leafName(newValue->name()) ;
	logDebugNormal("leaf name %s", leaf.c_str());

	if (leaf == "timezone-utc-offset" )
	{
		// New value is the UTC offset in minutes from -720 .. 840
		// Convert this to an hours minutes string, place into TZ environment variable and call TZSet
		// For some reason setting UTC is backward, you need to set 'UTC1' to set clock BACK one hour
		int utcOffset = -newValue->getInt16();
		int hours = utcOffset / 60;
		int minutes = abs(utcOffset) % 60;
		string tzString = string("UTC") + to_string(hours) + ":" + to_string(minutes);
		setenv("TZ", tzString.c_str(), 1);
		callTzSet();
	}
	else if (leaf == "re-call-home-no-ssh-timer" )
	{
		/*
		  type uint16;
		  units seconds;
		  default 60;
		  "A common timer used by the O-RAN equipment to trigger the repeated call
			home procedure to all identified call home servers to which the O-RAN
		equipment has not already an established SSH connection.

		A value of 0 means that the O-RAN equipment shall disable operation
		of the timer triggered NETCONF call home procedure.";
		 */
	}


	return;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

void Zcu111FbcOranrrhHandlerORanOperations::callTzSet()
{
	string tz = getenv("TZ");

	// tzset must only be called on a real radio, it can damage the linux machine
#ifndef OFF_TARGET
	logDebugNormal("TZSET called with: %s", tz.c_str());
	tzset();
#endif

}
