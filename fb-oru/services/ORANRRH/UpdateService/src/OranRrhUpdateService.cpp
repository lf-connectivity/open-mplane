/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranRrhUpdateService.cpp
 * \brief     ORAN RRH update service
 *
 *
 * \details   ORAN RRH update service
 *
 */
#include "OranRrhUpdateService.h"

using namespace Mplane;

OranRrhUpdateService::OranRrhUpdateService() :
	Service(SERVICE_MEDIUM_PRIORITY, SMALL_STACK, 500, // update stuff every 500 msec
	        "RrhUpdateService", "PS"),
	mRadio(IRadioFactory::getInterface()),  	// get our radio instance
	mFaults(RrhFaults::getInstance()),      	// create the lists of faults specific to ORAN RRH
	mFaultList(IFaultsList::getInstance()), 	// a reference to the resulting faults list
	mServicesMon(IServicesMonitorFactory::getInterface())
{
}


void OranRrhUpdateService::show()
{
	eventInfo("*** OranRrhUpdateService has no specific data at this time ***");
}

int OranRrhUpdateService::service()
{
	mRadio->updateTemperatureData();
	mRadio->updatePowerSupplyData();

	// Wait until the application is in a stable state before updating the system synth status
	// This will ensure that the radio is in a known state before monitoring starts,
	// avoiding any issues with false positives during the initialisation process.
	IServicesMonitor::ApplicationState state(mServicesMon->getApplicationState()) ;

	if( state == IServicesMonitor::STABLE )
	{
		mRadio->updateSystemSynthState();
	}

	if( !mRadio->getCalMode() )
	{
		mFaultList->updateFaults();         // @TODO work to remove this, individual fault owners should decide when to update faults.
	}

	logDebugVerbose("RrhUpdateService");

	return 0;   // no errors
}

void OranRrhUpdateService::doReset()
{
}

OranRrhUpdateService::~OranRrhUpdateService()
{
}

const char* OranRrhUpdateService::name() const
{
	return "OranRrhUpdateService";
}
