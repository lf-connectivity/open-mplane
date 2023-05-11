/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanDelayManagement.cpp
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
#include <map>
#include <string>
#include <unistd.h>

#include "stringfunc.hpp"

#include "IHighSpeedEthernet.h"
#include "YangMgrServer.h"
#include "RadioDatastoreSysrepo.h"
#include "YangParamUtils.h"

#include "Zcu111FbcOranrrhHandlerORanDelayManagement.h"


using namespace Mplane;


//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanDelayManagement::Zcu111FbcOranrrhHandlerORanDelayManagement(std::shared_ptr<IYangModuleMgr> moduleMgr) :
	YangHandlerSysrepo("o-ran-delay-management", moduleMgr, "Zcu111FbcOranrrhHandlerORanDelayManagement"),
	mCallback(std::make_shared<SysrepoGetitemsCallback>(path("delay-management")))

{

	// Initialise the Oran Delays singleton with the required ethernet clock
	// This will set up the values correctly depending on the 10G or 25G
	bool is25Gclock = IHighSpeedEthernet::singleton()->is25G();

	IOranDelays::DelayClock_T delayClock;
	delayClock = (is25Gclock == true ? IOranDelays::DelayClock_T::_25G_CLOCK : IOranDelays::DelayClock_T::_10G_CLOCK);

	mOranDelays = IOranDelays::getOranDelaysSingleton(delayClock);
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanDelayManagement::~Zcu111FbcOranrrhHandlerORanDelayManagement()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanDelayManagement::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	if(false == createBandwidthScsDelayStateList())
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
void Mplane::Zcu111FbcOranrrhHandlerORanDelayManagement::valueChange(const std::string & xpath,
                                                             std::shared_ptr<YangParam> oldValue,
                                                             std::shared_ptr<YangParam> newValue)
{
	logDebugNormal("Zcu111FbcOranrrhHandlerORanDelayManagement::valueChange() - %s", xpath.c_str());
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

bool Mplane::Zcu111FbcOranrrhHandlerORanDelayManagement::createBandwidthScsDelayStateList(void)
{
	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	// Create the list of bandwidth scs states as readonly
	std::string bandwidthScsDelayState = mCallback->path() + "/bandwidth-scs-delay-state";

	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	std::vector<Frequency> supportedAirStdBw;
	std::vector<Frequency> supportedScsSpacing;

	mOranDelays->getSupportedAirStdBw(supportedAirStdBw);
	mOranDelays->getSupportedScsSpacing(supportedScsSpacing);

	for(std::vector<Frequency>::iterator bandwidthItr = supportedAirStdBw.begin();
		bandwidthItr < supportedAirStdBw.end();
		bandwidthItr ++)
	{
		for(std::vector<Frequency>::iterator scsItr = supportedScsSpacing.begin();
			scsItr < supportedScsSpacing.end();
			scsItr ++)
		{

//			module: o-ran-delay-management
//			  +--rw delay-management
//			     +--rw bandwidth-scs-delay-state* [bandwidth subcarrier-spacing]
//			     |  +--rw bandwidth           bandwidth
//			     |  +--rw subcarrier-spacing  uint32
//			     |  +--ro ru-delay-profile
//			     |     +--ro t2a-min-up     uint32
//			     |     +--ro t2a-max-up     uint32
//			     |     +--ro t2a-min-cp-dl  uint32
//			     |     +--ro t2a-max-cp-dl  uint32
//			     |     +--ro tcp-adv-dl     uint32
//			     |     +--ro ta3-min        uint32
//			     |     +--ro ta3-max        uint32
//			     |     +--ro t2a-min-cp-ul  uint32
//			     |     +--ro t2a-max-cp-ul  uint32

			std::string bandwidth = std::to_string(bandwidthItr->get(Frequency::KHz));
			UINT32 subCarrierSpacing = scsItr->get(Frequency::Hz);

			logDebugNormal("Zcu111FbcOranrrhHandlerORanDelayManagement::createBandwidthScsDelayStateList()");
			logDebugNormal("bandwidth = %s KHz", bandwidth.c_str());
			logDebugNormal("subcarrier-spacing = %s Hz", std::to_string(subCarrierSpacing).c_str());

			// For the running database; We are only setting the rw values
			{
				std::string bandwidth_key = "bandwidth";
				std::string bandwidth_keyval = bandwidth;

				std::string scs_key = "subcarrier-spacing";
				std::string scs_keyval = std::to_string(subCarrierSpacing);

				// The bandwidth-scs-delay-state list entry is unusual in that it has two keys - bandwidth and subcarrier-spacing
				std::string path(bandwidthScsDelayState + "[" + bandwidth_key + "='" + bandwidth_keyval + "']"+ "[" + scs_key + "='" + scs_keyval + "']") ;

				std::string bandwidthItemPath = path + "/" + bandwidth_key;
				std::string scsItemPath = path + "/" + scs_key;

				ds->setItemStr(bandwidthItemPath, bandwidth_keyval);

				usleep(1000);

				ds->setItemStr(scsItemPath, scs_keyval);

				usleep(1000);

				ds->createListEntry(path);

				usleep(1000);
			}

			// For the operational database
			{
				std::string t2aMinUp = std::to_string((mOranDelays->CalcT2aMinUp(bandwidthItr->get())).getInt());
				std::string t2aMaxUp = std::to_string((mOranDelays->CalcT2aMaxUp(bandwidthItr->get())).getInt());
				std::string t2aMinCpDl = std::to_string((mOranDelays->CalcT2aMinCpDl(bandwidthItr->get())).getInt());
				std::string t2aMaxCpDl = std::to_string((mOranDelays->CalcT2aMaxCpDl(bandwidthItr->get())).getInt());
				std::string tcpAdvDl = std::to_string((mOranDelays->CalcTcpAdvDl(bandwidthItr->get())).getInt());
				std::string ta3Min = std::to_string((mOranDelays->CalcTa3Min(bandwidthItr->get())).getInt());
				std::string ta3Max = std::to_string((mOranDelays->CalcTa3Max(bandwidthItr->get())).getInt());
				std::string t2aMinCpUl = std::to_string((mOranDelays->CalcT2aMinCpUl(bandwidthItr->get())).getInt());
				std::string t2aMaxCpUl = std::to_string((mOranDelays->CalcT2aMaxCpUl(bandwidthItr->get(),
																					 scsItr->get())).getInt());

				auto bandwidthScsDelayState = parent->addContainer("bandwidth-scs-delay-state");

				bandwidthScsDelayState->addLeaf("bandwidth", bandwidth);
				bandwidthScsDelayState->addLeafInt32("subcarrier-spacing", subCarrierSpacing);

				auto ruDelayProfile = bandwidthScsDelayState->addContainer("ru-delay-profile");
				ruDelayProfile->addLeaf("t2a-min-up", t2aMinUp);
				ruDelayProfile->addLeaf("t2a-max-up", t2aMaxUp);
				ruDelayProfile->addLeaf("t2a-min-cp-dl", t2aMinCpDl);
				ruDelayProfile->addLeaf("t2a-max-cp-dl", t2aMaxCpDl);
				ruDelayProfile->addLeaf("tcp-adv-dl", tcpAdvDl);
				ruDelayProfile->addLeaf("ta3-min", ta3Min);
				ruDelayProfile->addLeaf("ta3-max", ta3Max);
				ruDelayProfile->addLeaf("t2a-min-cp-ul", t2aMinCpUl);
				ruDelayProfile->addLeaf("t2a-max-cp-ul", t2aMaxCpUl);
			}
		}
	}

	makeReadOnly(bandwidthScsDelayState);

	return true;
}
