/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioDpd2Service.cpp
 * \brief     Service DPD messages for Radio
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <map>

#include "Fault.h"
#include "DpdMinorAlarm.h"
#include "DpdMajorAlarm.h"

#include "RadioDpd2Service.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::string DEFAULT_FAULT("DpdGeneralFault") ;
//-------------------------------------------------------------------------------------------------------------
const std::map<std::string, std::string> DPD_ALARM_CATEGORIES{
	{ "AL_GENERAL",			DEFAULT_FAULT     },
	{ "AL_ORXHIGH",			"DpdOrxHighFault" },
	{ "AL_ORXLOW",			"DpdOrxLowFault"  },
	{ "AL_TXHIGH",			"DpdTxHighFault"  },
	{ "AL_TXLOW",			"DpdTxLowFault"   },
	{ "AL_CONVERGE",		"DpdConvergeFault"},
	{ "AL_DPD",				"DpdFault"		  },
} ;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IDpdControl> IDpdControl::getInterface()
{
	static std::shared_ptr<IDpdControl> interface(std::make_shared<RadioDpd2Service>());

	return interface ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RadioDpd2Service::RadioDpd2Service() :
	Dpd2Service(),
	FaultOwner("dpd2service")
{
	// Add an alarm handler
	addAlarmMonitor("RadioDpd2Service", [this](const std::map<std::string, DataVariant>& attributeValues){

//		std::cerr << "RadioDpd2Service::RadioDpd2Service() ALARM" << std::endl ;
//		for (auto entry : attributeValues)
//		{
//			std::cerr << " * " << entry.second.getName() << "=" << entry.second.toString() << std::endl ;
//		}

		mAlarmAttributes = attributeValues ;
		updateFaults() ;

	}) ;

	// MAJOR ALARM

	// Create a fault for each category
	std::set<std::string> majorNames ;
	for (auto entry : DPD_ALARM_CATEGORIES)
	{
    	std::shared_ptr<Fault> fault(std::make_shared<Fault>(1, 1, entry.second)) ;
    	Fault::makeFault(fault) ;
    	addFault(entry.second) ;

    	majorNames.insert(entry.second) ;
	}

	// Create the alarm
    std::shared_ptr<Alarm> majorAlarm(std::make_shared<DpdMajorAlarm>(majorNames)) ;
    Alarm::makeAlarm(majorAlarm) ;


    // MINOR ALARM

    // dummy fault
    std::string minorFaultName("DpdMinorFault") ;
	std::shared_ptr<Fault> fault(std::make_shared<Fault>(1, 1, minorFaultName)) ;
	Fault::makeFault(fault) ;
	addFault(minorFaultName) ;

	// Create the alarm
    std::shared_ptr<Alarm> minorAlarm(std::make_shared<DpdMinorAlarm>( std::set<std::string>{minorFaultName} )) ;
    Alarm::makeAlarm(minorAlarm) ;


}

//-------------------------------------------------------------------------------------------------------------
RadioDpd2Service::~RadioDpd2Service()
{
}

//-------------------------------------------------------------------------------------------------------------
void RadioDpd2Service::updateFaults()
{
	if (mAlarmAttributes.empty())
		return ;

	std::string alarm(mAlarmAttributes.at("alarm").toString()) ;
	std::string onoff(mAlarmAttributes.at("onoff").toString()) ;

	if (onoff.empty())
		onoff = "OFF" ;

	std::string faultName(DEFAULT_FAULT) ;
	if (DPD_ALARM_CATEGORIES.find(alarm) != DPD_ALARM_CATEGORIES.end())
		faultName = DPD_ALARM_CATEGORIES.at(alarm) ;

	std::shared_ptr<IFaultsList> faultList(IFaultsList::getInstance()) ;
	std::shared_ptr<IFault> fault(faultList->getFault(faultName)) ;
	fault->setStatus(onoff == "ON") ;

	mAlarmAttributes.clear() ;
}
