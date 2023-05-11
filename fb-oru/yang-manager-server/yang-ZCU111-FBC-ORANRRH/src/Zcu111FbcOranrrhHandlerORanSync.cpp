/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanSync.cpp
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
#include <algorithm>
#include <string>

#include "stringfunc.hpp"
#include "IAppOptions.h"

#include "YangMgrServer.h"
#include "YangParamUtils.h"

#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerORanSync.h"

using namespace Mplane;


//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanSync::Zcu111FbcOranrrhHandlerORanSync(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo("o-ran-sync", moduleMgr, "Zcu111FbcOranrrhHandlerORanSync")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path("sync")))
	, mSyncSources()
	, mLinuxPtp(ILinuxPtp::singleton())
{
	mNotif = std::make_shared<Zcu111FbcOranrrhHandlerORanSyncNotif>(this, path(""));
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanSync::~Zcu111FbcOranrrhHandlerORanSync()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSync::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	// Set the ptp-profile as readonly
	std::string ptpProfilePath = mCallback->path() + "/ptp-config/ptp-profile";
	ds->setItemStr(ptpProfilePath, "G_8275_1");
	makeReadOnly(ptpProfilePath);

	// Create the list of accepted clock classes as readonly
	std::string acceptedClockClasses = mCallback->path() + "/ptp-config/accepted-clock-classes";
	ds->createListEntry(acceptedClockClasses, "clock-classes", std::to_string(mLinuxPtp->getMaxAcceptableClockClass()) );
	makeReadOnly(acceptedClockClasses);

	std::string synceConfigPath = mCallback->path() + "/synce-config";
	std::string acceptanceSsmList = synceConfigPath + "/acceptance-list-of-ssm";
	ds->setItemStr(acceptanceSsmList, mLinuxPtp->getSsmStrFromCode(ILinuxPtpConfig::DNU));
	mLinuxPtp->setAcceptableSsmCode(ILinuxPtpConfig::DNU, true);

	std::string ssmTimeout = synceConfigPath + "/ssm-timeout";
	ds->setItemStr(ssmTimeout, "10");
	mLinuxPtp->setSsmTimeout(10);

	populateSyncSources();

	if (!createSyncStatus())
	{
		return false;
	}

	if (!createSyncCapability())
	{
		return false;
	}

	if (!createPtpStatus())
	{
		return false;
	}

	if (!createSyncEStatus())
	{
		return false;
	}

	// Register callbacks
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe() ;

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanSync::validate(std::shared_ptr<YangParams> params,
		std::shared_ptr<YangParams> deletedParams)
{
	std::string error;
	int ret = SR_ERR_OK;

	for (unsigned i=0; i < params->getNumParams(); ++i)
	{
		std::shared_ptr<YangParam> param(params->getParam(i)) ;

		std::string value( YangParamUtils::toString(param, error) ) ;
		std::string leaf( leafName(param->name()) ) ;

		if (leaf == "multicast-mac-address")
		{
			if (value != "FORWARDABLE" && value != "NONFORWARDABLE")
			{
				ret = SR_ERR_VALIDATION_FAILED;
			}
		}
	}

	return ret ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanSync::valueChange(const std::string & xpath,
                                                  std::shared_ptr<YangParam> oldValue,
                                                  std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanSync::valueChange() - %s", xpath.c_str());

	std::string value ;
	std::string leaf ;
	std::string error;

	if (oldValue)
	{
		value = YangParamUtils::toString(oldValue, error) ;
		std::cerr << " + OLD: " << oldValue->name() << " = " << value << std::endl ;
		leaf = leafName(oldValue->name()) ;
	}
	if (newValue)
	{
		value = YangParamUtils::toString(newValue, error) ;
		std::cerr << " + NEW: " << newValue->name() << " = " << value << std::endl ;
		leaf = leafName(newValue->name()) ;
	}

	if (leaf == "domain-number")
	{
		uint8_t domainNum = (uint8_t)std::stoul(value);
		mLinuxPtp->setDomainNumber(domainNum);
	}
	else if (leaf == "multicast-mac-address")
	{
		ILinuxPtp::MulticastMACAddr_T mac;
		if (value == "FORWARDABLE")
		{
			mac = ILinuxPtp::MulticastMACAddr_T::MAC_FORWARDABLE;
			mLinuxPtp->setMulticastMac(mac);
		}
		else if (value == "NONFORWARDABLE")
		{
			mac = ILinuxPtp::MulticastMACAddr_T::MAC_NONFORWARDABLE;
			mLinuxPtp->setMulticastMac(mac);
		}
	}
	else if (leaf == "ssm-timeout")
	{
		uint16_t timeout = (uint8_t)std::stoul(value);
		mLinuxPtp->setSsmTimeout(timeout);
	}
	else if (leaf == "acceptance-list-of-ssm")
	{
		mLinuxPtp->setAcceptableSsmCode(mLinuxPtp->getSsmCodeFromStr(value), true);
	}

	return;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanSync::paramDelete(const std::string& xpath, std::shared_ptr<YangParam> oldValue)
{
	std::string value ;
	std::string leaf ;
	std::string error;

	if (oldValue)
	{
		value = YangParamUtils::toString(oldValue, error) ;
		leaf = leafName(oldValue->name()) ;
	}

	if (leaf == "acceptance-list-of-ssm")
	{
		mLinuxPtp->setAcceptableSsmCode(mLinuxPtp->getSsmCodeFromStr(value), false);
	}
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSync::createSyncStatus()
{
	auto syncStateFunc = [this](std::string name) -> std::string {
		// Check for SYNCE, PTP and Airframe lock status
		if (mLinuxPtp->getPtpLockStatus() == ILinuxPtp::LockStatus_T::LOCKED &&
			mLinuxPtp->getAirframeLockStatus() == ILinuxPtp::LockStatus_T::LOCKED &&
			mLinuxPtp->getSynceLockStatus() == ILinuxPtp::LockStatus_T::LOCKED)
		{
			return "LOCKED";
		}
		else
		{
			return "FREERUN";
		}
	} ;

	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	// Create sync status

	//	     +--ro sync-status
	//	     |  +--ro sync-state                               enumeration
	//	     |  +--ro supported-reference-types* [item]
	//	     |  |  +--ro item                                  enumeration

	auto syncStatus = parent->addContainer("sync-status");
	syncStatus->addLeaf("sync-state", syncStateFunc);

	auto refTypes = syncStatus->addContainer("supported-reference-types");
	refTypes->addLeaf("item", "PTP");

	refTypes = syncStatus->addContainer("supported-reference-types");
	refTypes->addLeaf("item", "SYNCE");

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSync::createSyncCapability()
{
	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	// Create sync capability

	//	     +--ro sync-capability
	//	     |  +--ro sync-t-tsc                               enumeration

	auto syncCapability = parent->addContainer("sync-capability");
	syncCapability->addLeaf("sync-t-tsc", "CLASS_B");

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSync::createPtpStatus()
{
	auto ptpStateFunc = [this](std::string name) -> std::string {
		if (mLinuxPtp->getPtpLockStatus() == ILinuxPtp::LockStatus_T::LOCKED)
		{
			return "LOCKED";
		}
		else
		{
			return "UNLOCKED";
		}
	} ;

	auto stateFunc = [this](std::string name) -> std::string {
		return(mLinuxPtp->getSourceStateStr(mLinuxPtp->getPtpSourceState()));
	};

	auto twoStepFlagFunc = [this](std::string name) -> std::string {
		return((mLinuxPtp->getTwoStepFlag() == true) ? "true" : "false");
	} ;

	auto leap61Func = [this](std::string name) -> std::string {
		return((mLinuxPtp->getLeap61Flag() == true) ? "true" : "false");
	} ;

	auto leap59Func = [this](std::string name) -> std::string {
		return((mLinuxPtp->getLeap59Flag() == true) ? "true" : "false");
	} ;

	auto utcOffsetValidFunc = [this](std::string name) -> std::string {
		return((mLinuxPtp->getCurrentUtcOffsetValidFlag() == true) ? "true" : "false");
	} ;

	auto ptpTimescaleFunc = [this](std::string name) -> std::string {
		return((mLinuxPtp->getPtpTimescaleFlag() == true) ? "true" : "false");
	} ;

	auto timeTraceableFunc = [this](std::string name) -> std::string {
		return((mLinuxPtp->getTimeTraceableFlag() == true) ? "true" : "false");
	} ;

	auto freqTraceableFunc = [this](std::string name) -> std::string {
		return((mLinuxPtp->getFrequencyTraceableFlag() == true) ? "true" : "false");
	} ;

	auto srcClockIdentityFunc = [this](std::string name) -> std::string {
		std::string idn = "0x" + mLinuxPtp->getSourceClockIdentity();
		idn.erase(std::remove(idn.begin(), idn.end(), '.'), idn.end());
		idn.resize(18);
		return idn;
	};

	auto sourcePortNumFunc = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getSourcePortNumber()));
	} ;

	auto utcOffsetFunc = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getCurrentUtcOffset()));
	} ;

	auto priority1Func = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getPriority1()));
	} ;

	auto clockClassFunc = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getSourceClockClass()));
	} ;

	auto clockAccuracyFunc = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getClockAccuracy()));
	} ;

	auto offsetScaledLogVarianceFunc = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getoffsetScaledLogVariance()));
	} ;

	auto priority2Func = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getPriority2()));
	} ;

	auto gmClockIdentityFunc = [this](std::string name) -> std::string {
		std::string idn = "0x" + mLinuxPtp->getGMClockIdentity();
		idn.erase(std::remove(idn.begin(), idn.end(), '.'), idn.end());
		idn.resize(18);
		return idn;
	};

	auto stepsRemovedFunc = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getStepsRemoved()));
	} ;

	auto timeSourceFunc = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getTimeSource()));
	} ;

	auto ruClockClass = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getRuClockClass()));
	} ;

	auto ruClockIdentityFunc = [this](std::string name) -> std::string {
		std::string idn = "0x" + mLinuxPtp->getRuClockIdentity();
		idn.erase(std::remove(idn.begin(), idn.end(), '.'), idn.end());
		idn.resize(18);
		return idn;
	};

	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	// Create PTP status

	//	     +--ro ptp-status
	//	     |  +--ro lock-state                               enumeration
	//	     |  +--ro clock-class                              uint8_t
	//	     |  +--ro clock-identity                           string
	//	     |  +--ro partial-timing-supported                 boolean
	//	     |  +--ro sources* [local-port-number]
	//	     |  |  +--ro local-port-number                     uint8_t
	//	     |  |  +--ro state                                 enumeration
	//	     |  |  +--ro two-step-flag                         boolean
	//	     |  |  +--ro leap61                                boolean
	//	     |  |  +--ro leap59                                boolean
	//	     |  |  +--ro current-utc-offset-valid              boolean
	//	     |  |  +--ro ptp-timescale                         boolean
	//	     |  |  +--ro time-traceable                        boolean
	//	     |  |  +--ro frequency-traceable                   boolean
	//	     |  |  +--ro source-clock-identity                 string
	//	     |  |  +--ro source-port-number                    uint16_t
	//	     |  |  +--ro current-utc-offset                    uint16_t
	//	     |  |  +--ro priority1                             uint8_t
	//	     |  |  +--ro clock-class                           uint8_t
	//	     |  |  +--ro clock-accuracy                        uint8_t
	//	     |  |  +--ro offset-scaled-log-variance            uint16_t
	//	     |  |  +--ro priority2                             uint8_t
	//	     |  |  +--ro grandmaster-clock-identity            string
	//	     |  |  +--ro steps-removed                         uint16_t
	//	     |  |  +--ro time-source                           uint8_t

	auto ptpStatus = parent->addContainer("ptp-status");
	ptpStatus->addLeaf("lock-state", ptpStateFunc);
	ptpStatus->addLeaf("clock-class", ruClockClass);
	ptpStatus->addLeaf("clock-identity", ruClockIdentityFunc);
	ptpStatus->addLeafBool("partial-timing-supported", false);

	for (auto & source : mSyncSources)
	{
		uint8_t interfaceNum = source.second;
		auto sources = ptpStatus->addContainer("sources");
		sources->addLeafUInt8("local-port-number", (uint8_t)interfaceNum);

		// Check if the interface number is same as the SFP ethernet port number
		if (interfaceNum == mLinuxPtp->getSfpEthPortNumber())
		{
			// If yes, then add an entry to the sync sources with callback functions to get PTP status
			sources->addLeaf("state", stateFunc);
			sources->addLeaf("two-step-flag", twoStepFlagFunc);
			sources->addLeaf("leap61", leap61Func);
			sources->addLeaf("leap59", leap59Func);
			sources->addLeaf("current-utc-offset-valid", utcOffsetValidFunc);
			sources->addLeaf("ptp-timescale", ptpTimescaleFunc);
			sources->addLeaf("time-traceable", timeTraceableFunc);
			sources->addLeaf("frequency-traceable", freqTraceableFunc);
			sources->addLeaf("source-clock-identity", srcClockIdentityFunc);
			sources->addLeaf("source-port-number", sourcePortNumFunc);
			sources->addLeaf("current-utc-offset", utcOffsetFunc);
			sources->addLeaf("priority1", priority1Func);
			sources->addLeaf("clock-class", clockClassFunc);
			sources->addLeaf("clock-accuracy", clockAccuracyFunc);
			sources->addLeaf("offset-scaled-log-variance", offsetScaledLogVarianceFunc);
			sources->addLeaf("priority2", priority2Func);
			sources->addLeaf("grandmaster-clock-identity", gmClockIdentityFunc);
			sources->addLeaf("steps-removed", stepsRemovedFunc);
			sources->addLeaf("time-source", timeSourceFunc);
		}
		else
		{
			// If not, then add an entry to the sync sources with state disabled
			sources->addLeaf("state", "DISABLED");
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSync::createSyncEStatus()
{
	auto synceLockFunc = [this](std::string name) -> std::string {
		if (mLinuxPtp->getSynceLockStatus() == ILinuxPtp::LockStatus_T::LOCKED)
		{
			return "LOCKED";
		}
		else
		{
			return "UNLOCKED";
		}
	} ;

	auto stateFunc = [this](std::string name) -> std::string {
		return(mLinuxPtp->getSourceStateStr(mLinuxPtp->getSynceSourceState()));
	};

	auto qlFunc = [this](std::string name) -> std::string {
		return(std::to_string(mLinuxPtp->getSsmQualityLevel()));
	};

	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	// Create SyncE status

	//	     +--ro synce-status
	//	     |  +--ro lock-state                               enumeration
	//	     |  +--ro sources* [local-port-number]
	//	     |  |  +--ro local-port-number                     uint8_t
	//	     |  |  +--ro state                                 enumeration
	//	     |  |  +--ro quality-level                         uint8_t

	auto synceStatus = parent->addContainer("synce-status");
	// Lock state derived using the ESMC PDU and PLL alarms
	synceStatus->addLeaf("lock-state", synceLockFunc);

	for (auto & source : mSyncSources)
	{
		uint8_t interfaceNum = source.second;
		auto sources = synceStatus->addContainer("sources");
		sources->addLeafUInt8("local-port-number", (uint8_t)interfaceNum);

		// Check if the interface number is same as the SFP ethernet port number
		if (interfaceNum == mLinuxPtp->getSfpEthPortNumber())
		{
			// If yes, then add an entry to the sync sources with callback functions to get PTP status
			sources->addLeaf("state", stateFunc);
			sources->addLeaf("quality-level", qlFunc);
		}
		else
		{
			// If not, then add an entry to the sync sources with state disabled
			sources->addLeaf("state", "DISABLED");
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string> > Zcu111FbcOranrrhHandlerORanSync::getInterfaces(void)
{
	// get all of the interfaces so I can search for the interface name
	return getKeyValues( "/ietf-interfaces:interfaces/interface//.") ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam> > Zcu111FbcOranrrhHandlerORanSync::getPortReference(std::string interface)
{
	// get port reference for the specified interface
	return getParams( "/ietf-interfaces:interfaces/interface[name='" + interface + "']/o-ran-interfaces:port-reference//.") ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanSync::populateSyncSources(void)
{
	// Get all interfaces
	std::map<std::string, std::map<std::string, std::string> > interfaces(getInterfaces());

	for (auto & name : interfaces)
	{
		std::map<std::string, std::shared_ptr<YangParam>> portReference = getPortReference(name.first);
		for (auto & entry : portReference)
		{
			if (entry.first == "port-number")
			{
				std::string error;
				mSyncSources[name.first] = YangParamUtils::toUint8(entry.second, error);
			}
		}
	}
}
