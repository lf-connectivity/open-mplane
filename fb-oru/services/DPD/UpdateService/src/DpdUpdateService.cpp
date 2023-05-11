/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdUpdateService.cpp
 * \brief
 *
 *
 * \details
 *
 */
#include "DpdUpdateService.h"
#include "ICpriController.h"
#include "ICpriCore.h"

using namespace Mplane;

DpdUpdateService::DpdUpdateService() :
		Service(SERVICE_MEDIUM_PRIORITY, SMALL_STACK, 500, // update stuff every 500 msec
		        "DpdUpdateService", "PS"),
		mRadio( IRadioFactory::getInterface()),   // get our radio instance
//		mFaults( DpdFaults::getInstance()) ,   // create the lists of faults specific to DPD
//		mFaultList( IFaultsList::getInstance() ),// a reference to the resulting faults list
		mConnected( false )
{
	// we are interested in when the port 0, the CPRI master port in the case
	// of the FTU changes state.
	ICpriController::getInterface()->attachToPortHandler( 0, *this );
}


void DpdUpdateService::show()
{
	eventInfo("*** DpdUpdateService has no specific data at this time ***");
}

int DpdUpdateService::service()
{
	mRadio->updateTemperatureData();
	mRadio->updatePowerSupplyData();

	if( true == mConnected )
	{
		// Only update the system synth if cpri is connected and the link is up
		mRadio->updateSystemSynthState();
	}

//	if( !mRadio->getCalMode() )
//	{
//		mFaultList->updateFaults();         // @TODO work to remove this, individual fault owners should decide when to update faults.
//	}

	logDebugVerbose("DpdUpdateService");

	return 0;   // no errors
}

void DpdUpdateService::doReset()
{
}

DpdUpdateService::~DpdUpdateService()
{
}

const char* DpdUpdateService::name() const
{
	return "DpdUpdateService";
}

void DpdUpdateService::update(ICpriPortHandler& subject)
{
	// so something has changed in the CPRI master port status
	// if we are not already in the connected state, check to see if we have become connected
	if( mConnected == false  )
	{
		if( subject.isLinkUp() == true )
		{
			mConnected = true;
		}
	}
	// if we are connected check to see if the CPRI master link has gone down
	else
	{
		if( subject.isLinkUp() == false )
		{
			mConnected = false;
		}
	}
}
