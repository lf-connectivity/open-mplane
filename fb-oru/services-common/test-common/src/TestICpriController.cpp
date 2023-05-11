/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestICpriController.cpp
 * \brief     Implementation of the CPRI control interface ICpriController class
 *
 *
 * \details   This file defines the stub implementation of the CPRI control
 *            interface ICpriController class.
 *
 */

#include "ICpri.h"
#include "TestICpriPortHandler.h"
#include "TestICpriController.h"

using namespace Mplane;


/****** Global variables for use by unit testers.  ******/


/****** End of Global variables for use by unit testers.  ******/

TestICpriController::TestICpriController()
{
    // reserve vector space for all CPRI ports handlers
    mPortHandlers.reserve(ICpri::getInterface()->getNumCpriPorts());

    for (UINT32 port = 0; port < ICpri::getInterface()->getNumCpriPorts(); port++)
    {
        // instantiate a port handler for each port
        mPortHandlers.push_back(std::shared_ptr<ICpriPortHandler>(new TestICpriPortHandler(port)));
    }
}

TestICpriController::~TestICpriController()
{
}


//==================================================================================================

void Mplane::TestICpriController::testNotifyCpriPortObservers()
{
    // notify observers of the change in slave or master port status.
    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        if (mPortHandlers[port]->hasStateChanged())
        {
            // only notify when a port status has changed
            mPortHandlers[port]->notify();
        }
    }
}

std::shared_ptr<ICpriPortHandler> Mplane::TestICpriController::testGetPortHandler(unsigned port)
{
	if (port < mPortHandlers.size())
		return mPortHandlers[port] ;

	return mPortHandlers[0] ;
}


//==================================================================================================

void TestICpriController::show(std::ostream& os) {
}

void TestICpriController::masterLinkResetRequest(bool resetEnabled) {
}

bool TestICpriController::getMasterLinkStatus(
		ICpriCore::CpriPortStatus& portStatus) {
	return true ;
}

bool TestICpriController::getSlaveLinkStatus(UINT32 cpriPort,
		ICpriCore::CpriPortStatus& portStatus) {
	return true ;
}

UINT32 TestICpriController::getNumPortHandlers() {
    return mPortHandlers.size();
}

bool TestICpriController::attachToPortHandler(UINT32 cpriPort,
		Observer<ICpriPortHandler>& observer)
{
    if (cpriPort < mPortHandlers.size())
    {
        mPortHandlers[cpriPort]->attach(observer);
        return true;
    }

    return false;
}

bool TestICpriController::detachPortHandler(UINT32 cpriPort,
		Observer<ICpriPortHandler>& observer)
{
    if (cpriPort < mPortHandlers.size())
    {
        mPortHandlers[cpriPort]->detach(observer);
        return true;
    }

    return false;
}

void TestICpriController::showFibreControl() {
}

void TestICpriController::startFibreControl() {
}

void TestICpriController::serviceFibreControl() {
}

void TestICpriController::resetFibreControl() {
}

bool TestICpriController::setPortLineRateCapability(UINT32 cpriPort,
		ICpriController::cpriRateCapabilityMask rateMask) {
	return true ;
}

void TestICpriController::loopbackRequest(bool state, UINT32 carrier,
		int txc, int rx1c, int rx2c) {
}

bool TestICpriController::getLayer2Information(UINT32 cpriPort,
		ICpriController::cpriL2Info& cpriL2Info) {
	return true ;
}

bool TestICpriController::isLoopbackCarrierAvailable() {
	return true ;
}

void TestICpriController::setProtocolId(UINT32 pidValue) {
}

void TestICpriController::setTickShowState(bool state) {
}

std::shared_ptr<ICpriPortHandler> Mplane::TestICpriController::getPortHandler(unsigned port) const
{
	if (port >= mPortHandlers.size())
		return std::shared_ptr<ICpriPortHandler>() ;

	return mPortHandlers.at(port) ;
}
