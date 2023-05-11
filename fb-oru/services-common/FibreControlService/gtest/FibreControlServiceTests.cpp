/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FibreControlServiceTests.cpp
 * \brief     The Test file for FibreControlService
 *
 *
 * \details   The Test file for FibreControlService
 *
 */
#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "OffTargetFPGA.h"
#include "CommonFpgaKernel.h"
#include "CommonCpriCore.h"
#include "CommonFpgaCpri.h"
#include "CpriController.h"
#include "FibreControlService.h"
#include "CpriPortHandling.h"
#include <memory>
#include "ILoggable.h"
#include "FibreControlServiceTests.h"

using namespace Mplane;
using namespace std;

// added to the service interval to ensure the service is executed before the test continues
unsigned int gServiceTimeOffset = 100;   // in ms

// global data used during the tests.
// they are global so that they remain active between the tests.
UINT32 slavePort = 0;
UINT32 masterPort = 1;
FibreControlService* fibreControlService = 0;
std::shared_ptr<CpriController> cc ;
CommonCpriCore* cccMaster = 0;
CommonCpriCore* cccSlave = 0;
TestCpriObserver* tco = 0;
TestCpriObserver* tco2 = 0;

namespace Mplane
{

// Test objects

Mplane::TestCpriObserver::TestCpriObserver():
    Loggable("TestCpriObserver", "TC"),
    mLineRate(ICpriCore::RateUnknown),
    mName ( "Test Cpri Observer" ),
    mUpdateDone ( false )
{
}

TestCpriObserver::~TestCpriObserver()
{
    cout << "TestCpriObserver destructor" << endl;

    mName = NULL;
}

void Mplane::TestCpriObserver::show()
{
    eventInfo("%s", mName);
}

bool Mplane::TestCpriObserver::doAttach(bool all, UINT32 portAttach)
{
    bool result = true;

    // Attach to all the CPRI ports
    std::shared_ptr<CpriController> lcc = std::dynamic_pointer_cast<CpriController>( Mplane::ICpriController::getInterface() );

    if (all)
    {
        for (UINT32 port=0; port < lcc->getNumPortHandlers(); port++)
        {
            if (lcc->attachToPortHandler(port, *this) == false)
            {
                result = false;
            }
        }
    }
    else if (portAttach < lcc->getNumPortHandlers())
    {
        result = lcc->attachToPortHandler(portAttach, *this);
    }
    else
    {
        result = false;
    }

    return result;
}

bool Mplane::TestCpriObserver::getUpdateDone()
{
    return mUpdateDone;
}

void Mplane::TestCpriObserver::setUpdateDone(bool setting)
{
    mUpdateDone = setting;
}

void Mplane::TestCpriObserver::update(ICpriPortHandler& subject)
{
    eventInfo("The TestCpriObserver update method: port %d[%s]",
             subject.getPort(), subject.isSlave() ? "Slave" : "Master");

    CpriPortHandler* cpriPortHandlerP = dynamic_cast<CpriPortHandler*>(&subject) ;
//    subject.showSmState();
    EXPECT_TRUE(cpriPortHandlerP != 0) ;
    cpriPortHandlerP->showSmState();

    // check if line rate has changed
    ICpriCore::CpriPortStatus portStatus = subject.getLinkStatus();
    if (mLineRate != portStatus.lineRate)
    {
        eventInfo("port line rate has changed from %s to %s",
                ICpri::getInterface()->getPortCore(0).getCurrentLineRateString(mLineRate),
                ICpri::getInterface()->getPortCore(0).getCurrentLineRateString(portStatus.lineRate));

        mLineRate = portStatus.lineRate;
    }

    setUpdateDone(true);
}


/*
 * Unit test
 */

void Mplane::FibreControlServiceTestCases::SetUp()
{
}

void Mplane::FibreControlServiceTestCases::TearDown()
{
}

bool FibreControlServiceTestCases::waitState(
		std::shared_ptr<CpriPortHandler> ph,
		CpriPortHandler::CpriSMStates state, unsigned timeoutMs)
{
	// Wait for the state to reach the expected value or time out
	while (ph->getSmState() != state)
	{
		Task::msSleep(1) ;
		if (timeoutMs-- < 1)
			return false ;
	}

	return true ;
}



void Mplane::FibreControlServiceTestCases::testCreation()
{
    cout << "testCreation" << endl;

    // these global instances and pointers will persist throughout all tests
    slavePort = 0;
    masterPort = 1;
    fibreControlService = new FibreControlService();
    cc = std::dynamic_pointer_cast<CpriController>(Mplane::ICpriController::getInterface());
    cccMaster = (CommonCpriCore*)(&(CommonCpriCore&)(ICpri::getInterface()->getPortCore(masterPort)));
    cccSlave  = (CommonCpriCore*)(&(CommonCpriCore&)(ICpri::getInterface()->getPortCore(slavePort)));

    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE) ;

    ASSERT_EQ( fibreControlService->getState(), Service::ServiceCreated );

    ASSERT_EQ( fibreControlService->start(), Service::Start );

    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );   // sleep for just over the default service update period

    ASSERT_EQ( fibreControlService->getState(), Service::ServiceRunning );

    // check calling resume has no effect
    ASSERT_EQ( fibreControlService->resume(), Service::Noop );

    ASSERT_EQ( fibreControlService->suspend(), Service::Suspend );

    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );   // sleep for just over the default service update period

    // check still suspended
    ASSERT_EQ( fibreControlService->getState(), Service::ServiceSuspended );

    // lets resume
    ASSERT_EQ( fibreControlService->resume(), Service::Resume );

    // let's see its show() output
    fibreControlService->show();

    usleep( 100 * 1000 );   // give it a little time to resume, else the reset below will fail.
    ASSERT_EQ( fibreControlService->reset(), Service::Reset );
    usleep( 100 * 1000 );   // give it a little time for the reset to be performed
    ASSERT_EQ( fibreControlService->getState(), Service::ServiceRunning);

}

void Mplane::FibreControlServiceTestCases::testCpriController()
{
    cout << __func__ << " - START" <<  endl;

    // These tests will execute more than 90% of the CPRI controller.
    // The remaining is tested with Master and Slave port tests that follow on.

    // expect this test to start with Service in the running state, from the previous test
    EXPECT_TRUE( fibreControlService != 0 );
    EXPECT_TRUE( cc.get() != 0 );
    EXPECT_TRUE( cccMaster != 0 );
    EXPECT_TRUE( cccSlave != 0 );
    ASSERT_EQ( fibreControlService->getState(), Service::ServiceRunning);

    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE) ;

    // Setup the debug and logging levels for the CpriController class
    EXPECT_TRUE( ICpri::getInterface()->getNumCpriPorts() == 2 );
    EXPECT_TRUE( cc->mPortHandlers[slavePort]->isSlave() );
    EXPECT_TRUE( cc->mPortHandlers[masterPort]->isMaster() );

    // Ensure that the core is as per a system start.
    // Full reset, setup the CPRI to the default setup for the CPRI core
    cc->defaultCoreSetup();

    // start the port handlers. Sets the port status from the CPRI ports cores
    cc->mPortHandlers[slavePort]->start();
    cc->mPortHandlers[masterPort]->start();

    // allow another service interval to occur and check the console output has the tick state info
    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );

    // Test the master link reset request, disable then enable.
    // First, test by using direct calls to CpriCore, and then use the
    // masterLinkResetRequest() method
    // Get the master link status, check it is in the initial state and synth locked
    ICpriCore::CpriPortStatus portStatus;
    EXPECT_TRUE( cccMaster->isTransmitResetAckActive() == false );
    cc->mPortHandlers[masterPort]->enableReset();
    EXPECT_TRUE( cccMaster->isTransmitResetAckActive() == true );
    cc->mPortHandlers[masterPort]->disableReset();
    EXPECT_TRUE( cccMaster->isTransmitResetAckActive() == false );

    cc->mPortHandlers[masterPort]->enableReset();
    EXPECT_TRUE( cccMaster->isTransmitResetAckActive() == true );
    cc->masterLinkResetRequest(false);
    EXPECT_TRUE( cccMaster->isTransmitResetAckActive() == false );
    cc->masterLinkResetRequest(true);
    EXPECT_TRUE( cccMaster->isTransmitResetAckActive() == false );

    // Get the master link status, check it is in the initial state and synth locked
    cccMaster->show();  // confirm the Master port core is as expected
    EXPECT_TRUE( cc->getMasterLinkStatus(portStatus) == true );
    EXPECT_TRUE( portStatus.logicallyEnabled == false );
    EXPECT_TRUE( portStatus.active == false );
    EXPECT_TRUE( portStatus.mgtPllLock == false );
    EXPECT_TRUE( portStatus.mgtTxClockLock == false );
    EXPECT_TRUE( portStatus.mgtRxClockLock == false );

    // Get the slave link status, check it is in the initial state and synths not locked
    cccSlave->show();  // confirm the Slave port core is as expected
    EXPECT_TRUE( cc->getSlaveLinkStatus(slavePort, portStatus) == true );
    // Note: the SFP logic for slave transmit being enabled before sync is established is set by the
    // CpriController instantiation.
    if ( cc->mPortHandlers[slavePort]->mSfpLogic.sfpSlaveTransmitBeforeSync() == true)
    {
        EXPECT_TRUE( portStatus.logicallyEnabled == true );
    }
    else
    {
        EXPECT_TRUE( portStatus.logicallyEnabled == false );
    }
    EXPECT_TRUE( portStatus.active == false );
    EXPECT_TRUE( portStatus.mgtPllLock == false );
    EXPECT_TRUE( portStatus.mgtTxClockLock == false );
    EXPECT_TRUE( portStatus.mgtRxClockLock == false );

    // add the extra tick show function for each service path
    cc->setTickShowState(true);
    // allow another service interval to occur and check the console output has the tick state info
    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );

    // set the line rate capability for the slave port.
    // Test different masks, start with just one bit set.
    // set the capability to line rate to 1 only
    ICpriCore::LineRateCapability slaveLRC = cccSlave->getLineRateCapability();
    CpriController::cpriRateCapabilityMask capMask = CpriController::cpriRateMask614;
    cc->setPortLineRateCapability(slavePort, capMask);
    slaveLRC = cccSlave->getLineRateCapability();
    EXPECT_TRUE( slaveLRC.capableOfRate614_4 == true );
    EXPECT_TRUE( slaveLRC.capableOfRate1228_8 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate2457_6 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate3072_0 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate4915_2 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate6144_0 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate9830_4 == false );

    // set the capability to line rate to 2 and 3 only
    capMask = (CpriController::cpriRateCapabilityMask)
              (CpriController::cpriRateMask1228 |
               CpriController::cpriRateMask2457);
    cc->setPortLineRateCapability(slavePort, capMask);
    slaveLRC = cccSlave->getLineRateCapability();
    EXPECT_TRUE( slaveLRC.capableOfRate614_4 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate1228_8 == true );
    EXPECT_TRUE( slaveLRC.capableOfRate2457_6 == true );
    EXPECT_TRUE( slaveLRC.capableOfRate3072_0 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate4915_2 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate6144_0 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate9830_4 == false );

    // set the capability to line rate to 4,5,6,7
    capMask = (CpriController::cpriRateCapabilityMask)
              (CpriController::cpriRateMask3072 |
               CpriController::cpriRateMask4915 |
               CpriController::cpriRateMask6144 |
               CpriController::cpriRateMask9830);
    cc->setPortLineRateCapability(slavePort, capMask);
    slaveLRC = cccSlave->getLineRateCapability();
    EXPECT_TRUE( slaveLRC.capableOfRate614_4 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate1228_8 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate2457_6 == false );
    EXPECT_TRUE( slaveLRC.capableOfRate3072_0 == true );
    EXPECT_TRUE( slaveLRC.capableOfRate4915_2 == true );
    EXPECT_TRUE( slaveLRC.capableOfRate6144_0 == true );
    EXPECT_TRUE( slaveLRC.capableOfRate9830_4 == true );

    // test the CPRI loopback - currently does nothing, check the console to confirm nothing is done
    EXPECT_TRUE( cc->isLoopbackCarrierAvailable() == false ); // no carrier available
    cc->loopbackRequest(true, 0, 0, 0, 0);
    cc->loopbackRequest(false, 0, 0, 0, 0);

    // test the Layer 2 information, slave link is not up so the IDs will be zero
    CpriController::cpriL2Info l2Info;
    l2Info.linkId = 0;
    l2Info.pmre = 0;
    l2Info.remoteEquipmentId = 0;
    EXPECT_TRUE( cc->getLayer2Information(slavePort, l2Info) == true );
    EXPECT_TRUE( l2Info.linkId == 0 );
    EXPECT_TRUE( l2Info.pmre == 1 );
    EXPECT_TRUE( l2Info.remoteEquipmentId == 0 );

    // set the Protocol ID, which will trigger the slave port to be configured for line rate and tx format.
    // First, check that an unsupported Protocol ID is ignored, then send a supported one
    cc->setProtocolId(CpriController::PID_SUPPORTED+1);
    cc->setProtocolId(CpriController::PID_SUPPORTED);

    // test the reset of master ports, which would normally happen when a slave port has gone BAD.
    // Resetting the port means going in and out of core reset.
    cc->resetMasterPorts();

    // test the update to OAM slave link status
    EXPECT_TRUE( cc->mPortHandlers[slavePort]->getSlaveOamLinkState() == false );
    EXPECT_TRUE( cc->mPortHandlers[slavePort]->getSlaveLastOamLinkState() == false );
    cc->updateOAMSlaveCpriState();  // has no effect
    EXPECT_TRUE( cc->mPortHandlers[slavePort]->getSlaveOamLinkState() == false );
    EXPECT_TRUE( cc->mPortHandlers[slavePort]->getSlaveLastOamLinkState() == false );

    // change the last OAM reported value to force an update this time
    cc->mPortHandlers[slavePort]->mCpriOAMSlavePortStatus.lastOAMReportedCpriLinkState =
            !cc->mPortHandlers[slavePort]->getSlaveOamLinkState();
    EXPECT_TRUE( cc->mPortHandlers[slavePort]->getSlaveOamLinkState() == false );
    EXPECT_TRUE( cc->mPortHandlers[slavePort]->getSlaveLastOamLinkState() == true );
    cc->updateOAMSlaveCpriState();  // changes the last OAM reported value to the current link state value
    EXPECT_TRUE( cc->mPortHandlers[slavePort]->getSlaveOamLinkState() == false );
    EXPECT_TRUE( cc->mPortHandlers[slavePort]->getSlaveLastOamLinkState() == false );

    /* Test the endRE logic, for when the RRH is at the end of a chain.
     * Depends on the status of the Master port(s).
     * All master ports must be disabled or link down for it to be set to 'end of chain'
     */
    EXPECT_TRUE( cc->mPortHandlers[masterPort]->getLinkStatus().active == false );
    EXPECT_TRUE( cc->mPortHandlers[masterPort]->getLinkStatus().logicallyEnabled == false);
    cc->updateEndRE();
    EXPECT_TRUE( cc->mIsEndRE == true);  // at the end of the chain

    // change the link to active and retest, this time the RRH is not at the end of the chain
    cc->mPortHandlers[masterPort]->mCurrentPortStatus.active = true;
    cc->updateEndRE();
    EXPECT_TRUE( cc->mIsEndRE == false);  // Not at the end of the chain

    // change the link to Not active but logically enabled and retest, this time the RRH is not at the end of the chain
    cc->mPortHandlers[masterPort]->mCurrentPortStatus.active = false;
    cc->mPortHandlers[masterPort]->mCurrentPortStatus.logicallyEnabled = true;
    cc->updateEndRE();
    EXPECT_TRUE( cc->mIsEndRE == false);  // Not at the end of the chain

    // change the link to Not active and Not logically enabled and retest, this time the RRH is at the end of the chain
    cc->mPortHandlers[masterPort]->mCurrentPortStatus.active = false;
    cc->mPortHandlers[masterPort]->mCurrentPortStatus.logicallyEnabled = false;
    cc->updateEndRE();
    EXPECT_TRUE( cc->mIsEndRE == true);  // at the end of the chain

    // leave this test with Service in the running state, ready for the next test
    // tidy up any memory usage

    // sleep for just over the default service update period to allow for the task to finish neatly and also
    // to give it time to empty log buffers
    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );

    cout << __func__ << " - END" <<  endl;
}

void Mplane::FibreControlServiceTestCases::testCpriSlavePort()
{
    cout << __func__ << " - START" <<  endl;

    // expect this test to start with Service in the running state, from the previous test
    EXPECT_TRUE( fibreControlService != 0 );
    EXPECT_TRUE( cc.get() != 0 );
    EXPECT_TRUE( cccMaster != 0 );
    EXPECT_TRUE( cccSlave != 0 );
    EXPECT_TRUE( fibreControlService->getState() == Service::ServiceRunning);

    // use the OffTarget FPGA emulator to setup the FPGA registers as we desire
    OffTargetFPGA& offTargetFPGA = OffTargetFPGA::getInstance();

    offTargetFPGA.writeField("los[0]", 0);

    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE) ;

    // Setup the debug and logging levels for the CpriController class
    EXPECT_TRUE( cc->mPortHandlers[slavePort]->isSlave() == true );

    // Now setup the observer
    tco = new TestCpriObserver();

    // confirm the attempt to attach to the CPRI ports succeeds
    EXPECT_TRUE( ICpriController::getInterface()->getNumPortHandlers() == 2);

    // Setup the debug and logging levels for the CpriPortHandler class
    std::shared_ptr<CpriPortHandler> sph = cc->mPortHandlers[slavePort];

    // check there are 2 CPRI ports
    EXPECT_TRUE( ICpri::getInterface()->getNumCpriPorts() == 2 );

    // attach the observer to the slave port only
    EXPECT_TRUE( tco->doAttach(false, slavePort) == true );

    // Get the slave link status, check it is in the initial state and synths not locked
    ICpriCore::CpriPortStatus portStatus;
    cccSlave->show();  // confirm the Slave port core is as expected
    EXPECT_TRUE( cc->getSlaveLinkStatus(slavePort, portStatus) == true );
    // Note: the SFP logic for slave transmit being enabled before sync is established is set by the
    // CpriController instantiation.
    if ( cc->mPortHandlers[slavePort]->mSfpLogic.sfpSlaveTransmitBeforeSync() == true)
    {
        EXPECT_TRUE( portStatus.logicallyEnabled == true );
    }
    else
    {
        EXPECT_TRUE( portStatus.logicallyEnabled == false );
    }
    EXPECT_TRUE( portStatus.active == false );
    EXPECT_TRUE( portStatus.mgtPllLock == false );
    EXPECT_TRUE( portStatus.mgtTxClockLock == false );
    EXPECT_TRUE( portStatus.mgtRxClockLock == false );
    EXPECT_TRUE( portStatus.lineRate == ICpriCore::RateUnknown );
    EXPECT_TRUE( portStatus.ethernetMinCMBandwidth == ICpriCore::CMRateUnknown );
    EXPECT_TRUE( portStatus.ethernetMaxCMBandwidth == ICpriCore::CMRateUnknown );
    EXPECT_TRUE( portStatus.protocolVersion == cccSlave->getCurrentProtocolVersion() );
    EXPECT_TRUE( portStatus.sapDefect == false );
    EXPECT_TRUE( portStatus.lossOfFrame == false );
    EXPECT_TRUE( portStatus.lossOfSync == false );
    EXPECT_TRUE( portStatus.sfpLos == true );

    // check that the observer update done handling works
    EXPECT_TRUE( tco->getUpdateDone() == false );
    tco->setUpdateDone(true);
    EXPECT_TRUE( tco->getUpdateDone() == true );

    // Ensure that the core is as per a system start.
    // Full reset, setup the CPRI to the default setup for the CPRI core
    cc->defaultCoreSetup();

    // start the port handlers. Sets the port status from the CPRI ports cores
    cc->mPortHandlers[slavePort]->start();
    cc->mPortHandlers[masterPort]->start();

    // Note: the SFP logic for slave transmit being enabled before sync is established is set by the
    // CpriController instantiation.
    // For ALU the slave transmit is enabled before sync is established
    if ( cc->mPortHandlers[slavePort]->mSfpLogic.sfpSlaveTransmitBeforeSync() == true)
    {
        // Separate the handling when the SFP control logic uses different sync logic

        // check we are in the BAD SM state
        EXPECT_TRUE( cccSlave->getPreferredProtocolVersion() == sph->getPreferredProtocolValue() );
        EXPECT_TRUE( cccSlave->getPreferredEthernetPointer() == sph->getPreferredEthPointerValue() );
        EXPECT_TRUE( cccSlave->getPreferredHdlcRate() == sph->getPreferredHdlcRateValue() );
        EXPECT_TRUE( cccSlave->isSlaveTransmitEnabled() == true );

        EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_BAD );
        EXPECT_TRUE( sph->mNextState == sph->mCurrentState);

        offTargetFPGA.writeField("sfplos[0]", 0); // set fibre connected
        // set the clocks are locked
        offTargetFPGA.writeField("mgtpllLock[0]", 1);
        offTargetFPGA.writeField("mgtTxClockLock[0]", 1);
        offTargetFPGA.writeField("mgtRxClockLock[0]", 1);

        // check that the clocks are locked, as this is the gate to entering the next state
        EXPECT_TRUE( ICpri::getInterface()->areClocksLocked(slavePort) == true );

        // clear the observer done
        tco->setUpdateDone(false);

        // execute the service update instead of waiting for elapsed time
        EXPECT_TRUE( fibreControlService->service() == 0 );
        EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_BAD );
        EXPECT_TRUE( tco->getUpdateDone() == true );

        // change the link status and test the isLinkOK() method with all permutations possible.
        // The only combination that will give a linkOK of true is:
        // logically enabled and active and no LOS/LOF faults
        portStatus.logicallyEnabled = false;
        portStatus.active = false;
        portStatus.lossOfFrame = false;
        portStatus.lossOfSync = false;
        portStatus.lineRate = ICpriCore::Rate614_4;
        EXPECT_TRUE( sph->isLinkOK(portStatus) == false );
        portStatus.logicallyEnabled = true;
        EXPECT_TRUE( sph->isLinkOK(portStatus) == false );
        portStatus.active = true;
        EXPECT_TRUE( sph->isLinkOK(portStatus) == true );
        portStatus.lossOfFrame = true;
        EXPECT_TRUE( sph->isLinkOK(portStatus) == false );
        portStatus.lossOfFrame = false;
        portStatus.lossOfSync = true;
        EXPECT_TRUE( sph->isLinkOK(portStatus) == false );

        // check we stay in BAD SM state and no state change when SM serviced
        EXPECT_TRUE( sph->mCurrentState == CpriPortHandler::STATE_BAD );
        // execute the service update instead of waiting for elapsed time
        EXPECT_TRUE( fibreControlService->service() == 0 );
        EXPECT_TRUE( sph->mCurrentState == CpriPortHandler::STATE_BAD );
    }
    else
    {
        // check we are in the initial SM state and no state change when SM serviced
        EXPECT_TRUE( cccSlave->isSlaveTransmitEnabled() == false );

        EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_INITIAL );
        EXPECT_TRUE( sph->mNextState == sph->mCurrentState);
        // execute the service update instead of waiting for elapsed time
        EXPECT_TRUE( fibreControlService->service() == 0 );
        EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_INITIAL );
        EXPECT_TRUE( sph->mNextState == sph->mCurrentState);

        // check we are in the initial SM state and state changes to BAD when fibre is connected
        EXPECT_TRUE( sph->mCurrentState == CpriPortHandler::STATE_INITIAL );
        offTargetFPGA.writeField("sfplos[0]", 0); // set fibre connected
        // set the clocks are locked
        offTargetFPGA.writeField("mgtpllLock[0]", 1);
        offTargetFPGA.writeField("mgtTxClockLock[0]", 1);
        offTargetFPGA.writeField("mgtRxClockLock[0]", 1);
        // check that the clocks are locked, as this is the gate to entering the next state
        EXPECT_TRUE( ICpri::getInterface()->areClocksLocked(slavePort) == true );

        // clear the observer done
        tco->setUpdateDone(false);

        // execute the service update instead of waiting for elapsed time
        EXPECT_TRUE( fibreControlService->service() == 0 );
        EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_BAD );
        EXPECT_TRUE( tco->getUpdateDone() == true );
        EXPECT_TRUE( cccSlave->getPreferredProtocolVersion() == sph->getPreferredProtocolValue() );
        EXPECT_TRUE( cccSlave->getPreferredEthernetPointer() == sph->getPreferredEthPointerValue() );
        EXPECT_TRUE( cccSlave->getPreferredHdlcRate() == sph->getPreferredHdlcRateValue() );
        EXPECT_TRUE( cccSlave->isSlaveTransmitEnabled() == true );

        // change the link status and test the isLinkOK() method with all permutations possible.
        // The only combination that will give a linkOK of true is:
        // logically enabled and active and no LOS/LOF faults
        portStatus.lineRate = ICpriCore::Rate614_4;
        EXPECT_TRUE( sph->isLinkOK(portStatus) == false );
        portStatus.logicallyEnabled = true;
        EXPECT_TRUE( sph->isLinkOK(portStatus) == false );
        portStatus.active = true;
        EXPECT_TRUE( sph->isLinkOK(portStatus) == true );
        portStatus.lossOfFrame = true;
        EXPECT_TRUE( sph->isLinkOK(portStatus) == false );
        portStatus.lossOfFrame = false;
        portStatus.lossOfSync = true;
        EXPECT_TRUE( sph->isLinkOK(portStatus) == false );

        // check we stay in BAD SM state and no state change when SM serviced
        EXPECT_TRUE( sph->mCurrentState == CpriPortHandler::STATE_BAD );
        // execute the service update instead of waiting for elapsed time
        EXPECT_TRUE( fibreControlService->service() == 0 );
        EXPECT_TRUE( sph->mCurrentState == CpriPortHandler::STATE_BAD );
    }

    // We are not in BAD state

    // set the status alarm to not on, and state is operational
    offTargetFPGA.writeField("statAlarm[0]", 0x00);
    offTargetFPGA.writeField("los[0]", 0x00);
    offTargetFPGA.writeField("lof[0]", 0x00);
    offTargetFPGA.writeField("rai[0]", 0x00);
    offTargetFPGA.writeField("sdi[0]", 0x00);
    offTargetFPGA.writeField("remoteLos[0]", 0x00);
    offTargetFPGA.writeField("remoteLof[0]", 0x00);
    offTargetFPGA.writeField("removeRai[0]", 0x00);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);
    offTargetFPGA.writeField("StatCode[0]", CommonFpgaCpri::CPRI_OPERATIONAL);
    EXPECT_TRUE(cccSlave->getStatusCode() == ICpriCore::OPERATIONAL);
    EXPECT_TRUE(cccSlave->getPortStatus().active == true);

    ICpriCore::RemoteAlarms remoteAlarms = cccSlave->readRemoteAlarms();
    EXPECT_TRUE(remoteAlarms.remoteLOS == 0);
    EXPECT_TRUE(remoteAlarms.remoteLOF == 0);
    EXPECT_TRUE(remoteAlarms.remoteRAI == 0);
    EXPECT_TRUE(remoteAlarms.remoteSDI == 0);
    EXPECT_TRUE(remoteAlarms.remoteRST == 0);

    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);

    portStatus = cc->mPortHandlers[slavePort]->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );
    EXPECT_TRUE( portStatus.active == true );

    // set the line rate to rate 1, 614_4
    offTargetFPGA.writeReg(0x40210, 0x01);
    EXPECT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate614_4);

    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );

    // expect a transition from INITIAL to TRANSITION state and the link is up
    EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( sph->mNextState == sph->mCurrentState);
    EXPECT_TRUE( sph->isLinkUp() == true );

    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );
    // expect a transition from TRANSITION to GOOD state
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );
    // expect to stay in GOOD state
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);

    // set the status alarm to on, which should cause a transition to BAD state
    offTargetFPGA.writeField("statAlarm[0]", 0x01);
    offTargetFPGA.writeField("sdi[0]", 1);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == true);

    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );

    // expect to transition from GOOD to BAD state, link is down
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_BAD);
    EXPECT_TRUE( sph->isLinkUp() == false );

    // reset the port, which will reset the CPRI core for the slave port.
    // so, put the core into reset first, and check it is out of reset after resetting the port
    cccSlave->putCoreIntoReset();
    EXPECT_TRUE( cccSlave->isCoreOutOfReset() == false );
    sph->resetPort();
    EXPECT_TRUE( cccSlave->isCoreOutOfReset() == true );

    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );

    // repeat the port config for all the different line rates, 2 to 7
    // line rate 2
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[0]", 0x00);
    offTargetFPGA.writeField("sdi[0]", 0);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);
    offTargetFPGA.writeReg(0x40210, 0x02);
    EXPECT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate1228_8);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( sph->isLinkUp() == true );
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[0]", 0x01);
    offTargetFPGA.writeField("sdi[0]", 1);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_BAD);
    EXPECT_TRUE( sph->isLinkUp() == false );

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // line rate 3
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[0]", 0x00);
    offTargetFPGA.writeField("sdi[0]", 0);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);
    offTargetFPGA.writeReg(0x40210, 0x04);
    EXPECT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate2457_6);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( sph->isLinkUp() == true );
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[0]", 0x01);
    offTargetFPGA.writeField("sdi[0]", 1);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_BAD);
    EXPECT_TRUE( sph->isLinkUp() == false );

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // line rate 4
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[0]", 0x00);
    offTargetFPGA.writeField("sdi[0]", 0);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);
    offTargetFPGA.writeReg(0x40210, 0x08);
    EXPECT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate3072_0);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( sph->isLinkUp() == true );
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[0]", 0x01);
    offTargetFPGA.writeField("sdi[0]", 1);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_BAD);
    EXPECT_TRUE( sph->isLinkUp() == false );

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // line rate 5
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[0]", 0x00);
    offTargetFPGA.writeField("sdi[0]", 0);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);
    offTargetFPGA.writeReg(0x40210, 0x010);
    EXPECT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate4915_2);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( sph->isLinkUp() == true );
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[0]", 0x01);
    offTargetFPGA.writeField("sdi[0]", 1);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_BAD);
    EXPECT_TRUE( sph->isLinkUp() == false );

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // line rate 6
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[0]", 0x00);
    offTargetFPGA.writeField("sdi[0]", 0);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);
    offTargetFPGA.writeReg(0x40210, 0x20);
    EXPECT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate6144_0);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( sph->isLinkUp() == true );
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[0]", 0x01);
    offTargetFPGA.writeField("sdi[0]", 1);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_BAD);
    EXPECT_TRUE( sph->isLinkUp() == false );

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // line rate 7 - should fail because this rate is not supported
    // set the status alarm to off
//    offTargetFPGA.writeField("statAlarm[0]", 0x00);
//    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);
//    offTargetFPGA.writeReg(0x40210, 0x40);
//    EXPECT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate9830_4);
//    EXPECT_TRUE( fibreControlService->service() == 0 );
//    EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_BAD );
//    EXPECT_TRUE( sph->isLinkUp() == false );

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // make line rate 7 allowable and retest
    // set the status alarm to off
    // set the capability to line rate to 7 only
    CpriController::cpriRateCapabilityMask capMask = CpriController::cpriRateMask9830;
    cc->setPortLineRateCapability(slavePort, capMask);
    offTargetFPGA.writeField("statAlarm[0]", 0x00);
    offTargetFPGA.writeField("sdi[0]", 0);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);
    offTargetFPGA.writeReg(0x40210, 0x40);
    EXPECT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate9830_4);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->mNextState == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( sph->isLinkUp() == true );
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[0]", 0x01);
    offTargetFPGA.writeField("sdi[0]", 1);
    EXPECT_TRUE(cccSlave->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( sph->getSmState() == CpriPortHandler::STATE_BAD);
    EXPECT_TRUE( sph->isLinkUp() == false );

    // leave this test with Service in the running state, ready for the next test
    // and the slave port in the BAD state
    // tidy up any memory usage

    // sleep for just over the default service update period to allow for the task to finish neatly and also
    // to give it time to empty log buffers
    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );

    cout << __func__ << " - END" <<  endl;
}

void Mplane::FibreControlServiceTestCases::testCpriMasterPort()
{
    cout << __func__ << " - START" <<  endl;

    // expect this test to start with Service in the running state, from the previous test
    EXPECT_TRUE( fibreControlService != 0 );
    EXPECT_TRUE( cc.get() != 0 );
    EXPECT_TRUE( cccMaster != 0 );
    EXPECT_TRUE( cccSlave != 0 );
    EXPECT_TRUE( fibreControlService->getState() == Service::ServiceRunning);

    // use the OffTarget FPGA emulator to setup the FPGA registers as we desire
    OffTargetFPGA& offTargetFPGA = OffTargetFPGA::getInstance();

    offTargetFPGA.writeField("los[1]", 0);

    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE) ;

    // Setup the debug and logging levels for the CpriController class
    EXPECT_TRUE( cc->mPortHandlers[masterPort]->isMaster() == true );

    // Now setup the observer
    tco2 = new TestCpriObserver();

    // confirm the attempt to attach to the CPRI ports succeeds
    EXPECT_TRUE( ICpriController::getInterface()->getNumPortHandlers() == 2);

    // Setup the debug and logging levels for the MasterPortHandler class
    std::shared_ptr<CpriPortHandler> sph = cc->mPortHandlers[slavePort];
    std::shared_ptr<CpriPortHandler> mph = cc->mPortHandlers[masterPort];

    // check there 2 ports
    EXPECT_TRUE( ICpri::getInterface()->getNumCpriPorts() == 2 );

    // detach any existing observers
    if ( mph->getNumObservers() != 0 )
    {
        mph->detachAll();
    }
    EXPECT_TRUE( mph->getNumObservers() == 0 );
    // attach the observers
    EXPECT_TRUE( tco2->doAttach(false, masterPort) == true );
    EXPECT_TRUE( mph->getNumObservers() == 1 );

    // Get the master link status, check it is in the initial state and synth locked
    ICpriCore::CpriPortStatus portStatus;
    cccMaster->show();  // confirm the Master port core is as expected
    EXPECT_TRUE( cc->getMasterLinkStatus(portStatus) == true );
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // legacy from slave port tests
    EXPECT_TRUE( portStatus.active == false );
    EXPECT_TRUE( portStatus.mgtPllLock == false );
    EXPECT_TRUE( portStatus.mgtTxClockLock == false );
    EXPECT_TRUE( portStatus.mgtRxClockLock == false );
    EXPECT_TRUE( portStatus.lineRate == ICpriCore::RateUnknown );
    EXPECT_TRUE( portStatus.ethernetMinCMBandwidth == ICpriCore::CMRateUnknown );
    EXPECT_TRUE( portStatus.ethernetMaxCMBandwidth == ICpriCore::CMRateUnknown );
    EXPECT_TRUE( portStatus.protocolVersion == cccMaster->getCurrentProtocolVersion() );
    EXPECT_TRUE( portStatus.sapDefect == false );
    EXPECT_TRUE( portStatus.lossOfFrame == false );
    EXPECT_TRUE( portStatus.lossOfSync == false );
    EXPECT_TRUE( portStatus.sfpLos == true );

    // check that the observer update done handling works
    EXPECT_TRUE( tco2->getUpdateDone() == false );
    tco2->setUpdateDone(true);
    EXPECT_TRUE( tco2->getUpdateDone() == true );

    // check we are in the initial SM state and no state change when SM serviced
    EXPECT_TRUE( mph->mNextState == CpriPortHandler::STATE_INITIAL );
    EXPECT_TRUE( mph->mNextState == mph->mCurrentState);
    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->mNextState == CpriPortHandler::STATE_INITIAL );
    EXPECT_TRUE( mph->mNextState == mph->mCurrentState);

    // check we are in the initial SM state and state changes to BAD when fibre is connected
    EXPECT_TRUE( mph->mCurrentState == CpriPortHandler::STATE_INITIAL );

    // clear alarms
    offTargetFPGA.writeField("statAlarm[1]", 0);
    offTargetFPGA.writeField("los[1]", 0);
    offTargetFPGA.writeField("lof[1]", 0);
    offTargetFPGA.writeField("rai[1]", 0);
    offTargetFPGA.writeField("sdi[1]", 0);
    offTargetFPGA.writeField("remoteLos[1]", 0x00);
    offTargetFPGA.writeField("remoteLof[1]", 0x00);
    offTargetFPGA.writeField("removeRai[1]", 0x00);

    offTargetFPGA.writeField("sfplos[1]", 0); // set fibre connected
    offTargetFPGA.writeField("statCode[1]", CommonFpgaCpri::CPRI_OPERATIONAL); // set fibre operational
    // set the clocks are locked
    offTargetFPGA.writeField("mgtpllLock[1]", 1);
    offTargetFPGA.writeField("mgtTxClockLock[1]", 1);
    offTargetFPGA.writeField("mgtRxClockLock[1]", 1);

    // check that the clocks are locked, as this is the gate to entering the next state
    EXPECT_TRUE( ICpri::getInterface()->areClocksLocked(masterPort) == true );

    ICpriCore::CpriPortStatus newPortStatus( mph->getCpriPortStatus() ) ;
    EXPECT_TRUE( mph->isFibreConnected(newPortStatus) == true );

    // clear the observer done
    tco2->setUpdateDone(false);

    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );

    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );   // sleep for just over the default service update period

    ASSERT_EQ( mph->mNextState,  CpriPortHandler::STATE_BAD );
    EXPECT_TRUE( tco2->getUpdateDone() == true );
    EXPECT_TRUE( cccMaster->getPreferredProtocolVersion() == mph->getPreferredProtocolValue() );
    EXPECT_TRUE( cccMaster->getPreferredEthernetPointer() == mph->getPreferredEthPointerValue() );
    EXPECT_TRUE( cccMaster->getPreferredHdlcRate() == mph->getPreferredHdlcRateValue() );

    // change the link status and test the isLinkOK() method with all permutations possible.
    // The only combination that will give a linkOK of true is:
    // logically enabled and active and no LOS/LOF faults and line rate is supported
    mph->mPortControl.allowableRates.capableOfRate614_4 = true;
    portStatus.lineRate = ICpriCore::Rate614_4;
    EXPECT_TRUE( mph->isLinkOK(portStatus) == false );
    portStatus.logicallyEnabled = true;
    EXPECT_TRUE( mph->isLinkOK(portStatus) == false );
    portStatus.active = true;
    EXPECT_TRUE( mph->isLinkOK(portStatus) == true );
    portStatus.lossOfFrame = true;
    EXPECT_TRUE( mph->isLinkOK(portStatus) == false );
    portStatus.lossOfFrame = false;
    portStatus.lossOfSync = true;
    EXPECT_TRUE( mph->isLinkOK(portStatus) == false );

    // check we stay in BAD SM state and no state change when SM serviced
    EXPECT_TRUE( mph->mCurrentState == CpriPortHandler::STATE_BAD );
    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->mCurrentState == CpriPortHandler::STATE_BAD );

    // set the status alarm to not on, and state is operational
    offTargetFPGA.writeField("statAlarm[1]", 0x00);  // address 0x4120C, mask 1, shift 7
    offTargetFPGA.writeField("sdi[1]", 0);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == false);

    offTargetFPGA.writeField("StatCode[1]", CommonFpgaCpri::CPRI_OPERATIONAL);
    EXPECT_TRUE(cccMaster->getStatusCode() == ICpriCore::OPERATIONAL);
    EXPECT_TRUE(cccMaster->getPortStatus().active == true);

    ICpriCore::RemoteAlarms remoteAlarms = cccMaster->readRemoteAlarms();
    EXPECT_TRUE(remoteAlarms.remoteLOS == 0);
    EXPECT_TRUE(remoteAlarms.remoteLOF == 0);
    EXPECT_TRUE(remoteAlarms.remoteRAI == 0);
    EXPECT_TRUE(remoteAlarms.remoteSDI == 0);
    EXPECT_TRUE(remoteAlarms.remoteRST == 0);

    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == false);

    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // true when port is enabled
    EXPECT_TRUE( portStatus.active == true );

    // set the slave port line rate to rate 1, 614_4
    offTargetFPGA.writeReg(0x40210, 0x01);

    // enable the port, simulating the slave link up
    mph->enableMasterPort(ICpri::getInterface()->getPortCore(slavePort));
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    EXPECT_TRUE( mph->mPortControl.allowableRates.capableOfRate614_4 == true );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);
    // set the master port line rate to rate 1, 614_4
    offTargetFPGA.writeReg(0x41210, 0x01);
    EXPECT_TRUE(cccMaster->getCurrentLineRate() == ICpriCore::Rate614_4);

    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );

    // need the link to be ok and the CM rate stable (which it always is on this RRH) to transition the SM state
    // expect a transition from INITIAL to TRANSITION state

    ASSERT_EQ( mph->mNextState, CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( mph->mNextState == mph->mCurrentState);

    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );
    // expect a transition from TRANSITION to GOOD state as no other actions apply
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_GOOD);
    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );
    // expect to stay in GOOD state
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_GOOD);

    // set the status alarm to on, which should cause a transition to BAD state
    offTargetFPGA.writeField("statAlarm[1]", 0x01);
    offTargetFPGA.writeField("sdi[1]", 1);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == true);

    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );
    // expect to transition from GOOD to BAD state, link is down
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);
    // execute the service update instead of waiting for elapsed time
    EXPECT_TRUE( fibreControlService->service() == 0 );

    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );   // sleep for just over the default service update period

    // repeat the port config for all the different line rates, 2 to 7
    // line rate 2
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[1]", 0x00);
    offTargetFPGA.writeField("sdi[1]", 0);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == false);
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    offTargetFPGA.writeReg(0x40210, 0x02);  // set the slave port line rate to rate 2
    mph->enableMasterPort(ICpri::getInterface()->getPortCore(slavePort));
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    EXPECT_TRUE( mph->mPortControl.allowableRates.capableOfRate1228_8 == true );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);
    offTargetFPGA.writeReg(0x41210, 0x02);  // set the master port line rate to rate 2
    EXPECT_TRUE(cccMaster->getCurrentLineRate() == ICpriCore::Rate1228_8);
    EXPECT_TRUE( fibreControlService->service() == 0 );

    //@T)D) not going to see this at the moment, need to change the test
    // EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_TRANSITION );


    EXPECT_TRUE( fibreControlService->service() == 0 );
    // @TODO: FIX
    EXPECT_TRUE( waitState(mph, CpriPortHandler::STATE_GOOD, 1000)) ;

    EXPECT_TRUE( fibreControlService->service() == 0 );
    // @TODO: FIX
    EXPECT_TRUE( waitState(mph, CpriPortHandler::STATE_GOOD, 1000)) ;
    offTargetFPGA.writeField("statAlarm[1]", 0x01);
    offTargetFPGA.writeField("sdi[1]", 1);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // line rate 3
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[1]", 0x00);
    offTargetFPGA.writeField("sdi[1]", 0);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == false);
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    offTargetFPGA.writeReg(0x40210, 0x04);  // set the slave port line rate to rate 3
    mph->enableMasterPort(ICpri::getInterface()->getPortCore(slavePort));
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    EXPECT_TRUE( mph->mPortControl.allowableRates.capableOfRate2457_6 == true );

    // @TODO: FIX
    EXPECT_TRUE( waitState(mph, CpriPortHandler::STATE_BAD, 1000)) ;

    offTargetFPGA.writeReg(0x41210, 0x04);  // set the master port line rate to rate 3
    EXPECT_TRUE(cccMaster->getCurrentLineRate() == ICpriCore::Rate2457_6);
    EXPECT_TRUE( fibreControlService->service() == 0 );

    // @TODO not going to catch this without more work to control the thread.
//    ASSERT_EQ( mph->getSmState(), CpriPortHandler::STATE_TRANSITION );

//    EXPECT_TRUE( fibreControlService->service() == 0 );
    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );   // sleep for just over the default service update period

    ASSERT_EQ( mph->getSmState(), CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );

    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );   // sleep for just over the default service update period

    ASSERT_EQ( mph->getSmState(), CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[1]", 0x01);
    offTargetFPGA.writeField("sdi[1]", 1);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );

    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );   // sleep for just over the default service update period

    ASSERT_EQ( mph->getSmState(), CpriPortHandler::STATE_BAD);

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // line rate 4
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[1]", 0x00);
    offTargetFPGA.writeField("sdi[1]", 0);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == false);
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    offTargetFPGA.writeReg(0x40210, 0x08);  // set the slave port line rate to rate 4
    mph->enableMasterPort(ICpri::getInterface()->getPortCore(slavePort));
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    EXPECT_TRUE( mph->mPortControl.allowableRates.capableOfRate3072_0 == true );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);
    offTargetFPGA.writeReg(0x41210, 0x08);  // set the master port line rate to rate 4
    EXPECT_TRUE(cccMaster->getCurrentLineRate() == ICpriCore::Rate3072_0);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[1]", 0x01);
    offTargetFPGA.writeField("sdi[1]", 1);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // line rate 5
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[1]", 0x00);
    offTargetFPGA.writeField("sdi[1]", 0);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == false);
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    offTargetFPGA.writeReg(0x40210, 0x10);  // set the slave port line rate to rate 5
    mph->enableMasterPort(ICpri::getInterface()->getPortCore(slavePort));
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    EXPECT_TRUE( mph->mPortControl.allowableRates.capableOfRate4915_2 == true );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);
    offTargetFPGA.writeReg(0x41210, 0x10);  // set the master port line rate to rate 5
    EXPECT_TRUE(cccMaster->getCurrentLineRate() == ICpriCore::Rate4915_2);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[1]", 0x01);
    offTargetFPGA.writeField("sdi[1]", 1);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // line rate 6
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[1]", 0x00);
    offTargetFPGA.writeField("sdi[1]", 0);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == false);
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    offTargetFPGA.writeReg(0x40210, 0x20);  // set the slave port line rate to rate 6
    mph->enableMasterPort(ICpri::getInterface()->getPortCore(slavePort));
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    EXPECT_TRUE( mph->mPortControl.allowableRates.capableOfRate6144_0 == true );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);
    offTargetFPGA.writeReg(0x41210, 0x20);  // set the master port line rate to rate 6
    EXPECT_TRUE(cccMaster->getCurrentLineRate() == ICpriCore::Rate6144_0);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[1]", 0x01);
    offTargetFPGA.writeField("sdi[1]", 1);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);

    EXPECT_TRUE( fibreControlService->service() == 0 );

    // line rate 7
    // set the status alarm to off
    offTargetFPGA.writeField("statAlarm[1]", 0x00);
    offTargetFPGA.writeField("sdi[1]", 0);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == false);
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    offTargetFPGA.writeReg(0x40210, 0x40);  // set the slave port line rate to rate 7
    mph->enableMasterPort(ICpri::getInterface()->getPortCore(slavePort));
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == true );  // only true when port is enabled
    EXPECT_TRUE( portStatus.active == true );
    EXPECT_TRUE( mph->mPortControl.allowableRates.capableOfRate9830_4 == true );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);
    offTargetFPGA.writeReg(0x41210, 0x40);  // set the master port line rate to rate 7
    EXPECT_TRUE(cccMaster->getCurrentLineRate() == ICpriCore::Rate9830_4);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_TRANSITION );
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_GOOD);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_GOOD);
    offTargetFPGA.writeField("statAlarm[1]", 0x01);
    offTargetFPGA.writeField("sdi[1]", 1);
    EXPECT_TRUE(cccMaster->isAlarmCurrentlyActive() == true);
    EXPECT_TRUE( fibreControlService->service() == 0 );
    EXPECT_TRUE( mph->getSmState() == CpriPortHandler::STATE_BAD);

    // disable the port, which will reset the CPRI core for the masterport.
    // so, put the core into reset first, and check it remains in reset after resetting the port
    cccMaster->takeCoreOutOfReset();
    EXPECT_TRUE( cccMaster->isCoreOutOfReset() == true );
    mph->disableMasterPort();
    EXPECT_TRUE( cccMaster->isCoreOutOfReset() == false );
    portStatus = mph->getCpriPortStatus();
    EXPECT_TRUE( portStatus.logicallyEnabled == false );  // only true when port is enabled

    // leave this test with Service in the running state, ready for the next test
    // and the slave and master ports in the BAD state

    // sleep for just over the default service update period to allow for the task to finish neatly and also
    // to give it time to empty log buffers
    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );

    cout << __func__ << " - END" <<  endl;
}

void Mplane::FibreControlServiceTestCases::testCpriCfgChange()
{
    cout << __func__ << " - START" <<  endl;

    UINT32 port0 = 0;
    UINT32 port1 = 1;

    // expect this test to start with Service in the running state, from the previous test
    EXPECT_TRUE( fibreControlService != 0 );
    EXPECT_TRUE( cc.get() != 0 );
    EXPECT_TRUE( cccMaster != 0 );
    EXPECT_TRUE( cccSlave != 0 );
    EXPECT_TRUE( fibreControlService->getState() == Service::ServiceRunning);

    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE) ;

    // Setup the debug and logging levels for the CpriController class
    EXPECT_TRUE( cc->mPortHandlers[port1]->isMaster() == true );

    // confirm the attempt to attach to the CPRI ports succeeds
    EXPECT_TRUE( ICpriController::getInterface()->getNumPortHandlers() == 2);

    // Setup the debug and logging levels for the PortHandler instances
    std::shared_ptr<CpriPortHandler> ph0 = cc->mPortHandlers[port0];
    std::shared_ptr<CpriPortHandler> ph1 = cc->mPortHandlers[port1];

    // check there 2 ports
    EXPECT_TRUE( ICpri::getInterface()->getNumCpriPorts() == 2 );

    EXPECT_TRUE( cc->mPortHandlers[port0]->isSlave() == true );
    EXPECT_TRUE( cc->mPortHandlers[port1]->isMaster() == true );

    // test the invalid mode changes first, cannot change to its current mode
    EXPECT_TRUE( cc->mPortHandlers[port0]->changePortMode(ICpri::CpriPortSlave) == false );
    EXPECT_TRUE( cc->mPortHandlers[port1]->changePortMode(ICpri::CpriPortMaster) == false );

    // change port 1 from master to slave
    EXPECT_TRUE( cc->mPortHandlers[port1]->changePortMode(ICpri::CpriPortSlave) == true );
    EXPECT_TRUE( cc->mPortHandlers[port0]->isSlave() == true );
    EXPECT_TRUE( cc->mPortHandlers[port1]->isSlave() == true );

    // change port 0 from slave to master
    EXPECT_TRUE( cc->mPortHandlers[port0]->changePortMode(ICpri::CpriPortMaster) == true );
    EXPECT_TRUE( cc->mPortHandlers[port0]->isMaster() == true );
    EXPECT_TRUE( cc->mPortHandlers[port1]->isSlave() == true );

    // change port 0 from master to slave
    EXPECT_TRUE( cc->mPortHandlers[port0]->changePortMode(ICpri::CpriPortSlave) == true );
    EXPECT_TRUE( cc->mPortHandlers[port0]->isSlave() == true );
    EXPECT_TRUE( cc->mPortHandlers[port1]->isSlave() == true );

    // change port 1 from slave to inactive
    EXPECT_TRUE( cc->mPortHandlers[port1]->changePortMode(ICpri::CpriPortInactive) == true );
    EXPECT_TRUE( cc->mPortHandlers[port0]->isSlave() == true );
    EXPECT_TRUE( cc->mPortHandlers[port1]->isSlave() == false );
    EXPECT_TRUE( cc->mPortHandlers[port1]->isMaster() == false );

    cout << __func__ << " - END" <<  endl;
}

void Mplane::FibreControlServiceTestCases::testErrorPaths()
{
    cout << __func__ << " - START" <<  endl;

    cout << __func__ << " *** TBD ***" <<  endl;

#if 0
    ICpriCore::RemoteAlarms remoteAlarms = cccSlave->readRemoteAlarms();
    EXPECT_TRUE(remoteAlarms.remoteLOS == 0);
    EXPECT_TRUE(remoteAlarms.remoteLOF == 0);
    EXPECT_TRUE(remoteAlarms.remoteRAI == 0);
    EXPECT_TRUE(remoteAlarms.remoteSDI == 0);
    EXPECT_TRUE(remoteAlarms.remoteRST == 0);

    // set no LOS alarm
    offTargetFPGA.writeField("los[0]", 0x00);
    EXPECT_TRUE(cccSlave->haveLOS() == false);
    // set LOS alarm
    offTargetFPGA.writeField("los[0]", 0x01);
    EXPECT_TRUE(cccSlave->haveLOS() == true);

    // set no LOF alarm
    offTargetFPGA.writeField("lof[0]", 0x00);
    EXPECT_TRUE(cccSlave->haveLOF() == false);
    // set LOF alarm
    offTargetFPGA.writeField("lof[0]", 0x01);
    EXPECT_TRUE(cccSlave->haveLOF() == true);
#endif


    cout << __func__ << " - END" <<  endl;
}

void Mplane::FibreControlServiceTestCases::testResetScenarios()
{
    cout << __func__ << " - START" <<  endl;

    cout << __func__ << " *** TBD ***" <<  endl;

    cout << __func__ << " - END" <<  endl;
}

void Mplane::FibreControlServiceTestCases::testAlarmScenarios()
{
    cout << __func__ << " - START" <<  endl;

    cout << __func__ << " *** TBD ***" <<  endl;

    cout << __func__ << " - END" <<  endl;
}

void Mplane::FibreControlServiceTestCases::testMultiplePorts()
{
    cout << __func__ << " - START" <<  endl;

    cout << __func__ << " *** TBD ***" <<  endl;

    cout << __func__ << " - END" <<  endl;
}

void Mplane::FibreControlServiceTestCases::testTidyUp()
{
    cout << __func__ << " - START" <<  endl;

    // expect this test to start with Service in the running state, from the previous test
    EXPECT_TRUE( fibreControlService != 0 );
    EXPECT_TRUE( cc.get() != 0 );
    EXPECT_TRUE( cccMaster != 0 );
    EXPECT_TRUE( cccSlave != 0 );
    EXPECT_TRUE( fibreControlService->getState() == Service::ServiceRunning);

    EXPECT_TRUE( fibreControlService->shutdown() == Service::Shutdown );
    usleep( 100 * 1000 );   // small sleep give it time to process but not as much as wait
    EXPECT_TRUE( fibreControlService->getState() == Service::ServiceShutdown );
    EXPECT_TRUE( fibreControlService->wasCancelled() == false );
    EXPECT_TRUE( fibreControlService->getExitValue() == 0 );

    // detach any existing observers
    std::shared_ptr<CpriPortHandler> sph = cc->mPortHandlers[slavePort];
    std::shared_ptr<CpriPortHandler> mph = cc->mPortHandlers[masterPort];
    mph->detachAll();
    sph->detachAll();
    EXPECT_TRUE( sph->getNumObservers() == 0 );
    EXPECT_TRUE( mph->getNumObservers() == 0 );

    // tidy up memory
    if (tco != 0)
    {
        delete tco;
        tco = 0;
    }

    if (tco2 != 0)
    {
        delete tco2;
        tco2 = 0;
    }

    if (cccSlave != 0)
    {
        cccSlave = 0;
    }

    if (cccMaster != 0)
    {
        cccMaster = 0;
    }

    if (fibreControlService != 0)
    {
        delete fibreControlService;
        fibreControlService = 0;
    }

    usleep( 2000 * 1000 );   // sleep to give it time to empty all log buffers

    cout << __func__ << " - END" <<  endl;
}


/*
 * Unit test fixtures
 */
TEST_F(FibreControlServiceTestCases, TestCreation)
{
    cout << endl << "*** FibreControlServiceTestCases Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    testCreation();

    // leave this test with Service in the running state, ready for the next test
    // tidy up any memory usage

    // sleep for just over the default service update period to allow for the task to finish neatly and also
    // to give it time to empty log buffers
    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );

    cout << __func__ << " - END" <<  endl;
}

TEST_F(FibreControlServiceTestCases, TestCpriController)
{
    cout << __func__ << " - START" <<  endl;

    testCpriController();

    // leave this test with Service in the running state, ready for the next test
    // tidy up any memory usage

    // sleep for just over the default service update period to allow for the task to finish neatly and also
    // to give it time to empty log buffers
    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );

    cout << __func__ << " - END" <<  endl;
}

TEST_F(FibreControlServiceTestCases, TestCpriSlavePort)
{
    cout << __func__ << " - START" <<  endl;

    testCpriSlavePort();

    // leave this test with Service in the running state, ready for the next test
    // tidy up any memory usage

    // sleep for just over the default service update period to allow for the task to finish neatly and also
    // to give it time to empty log buffers
    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );

    cout << __func__ << " - END" <<  endl;
}

TEST_F(FibreControlServiceTestCases, TestCpriMasterPort)
{
    cout << __func__ << " - START" <<  endl;

    testCpriMasterPort();

    // leave this test with Service in the running state, ready for the next test
    // tidy up any memory usage

    // sleep for just over the default service update period to allow for the task to finish neatly and also
    // to give it time to empty log buffers
    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );

    cout << __func__ << " - END" <<  endl;
}

TEST_F(FibreControlServiceTestCases, TestCpriCfgChange)
{
    cout << __func__ << " - START" <<  endl;

    testCpriCfgChange();

    // leave this test with Service in the running state, ready for the next test
    // tidy up any memory usage

    // sleep for just over the default service update period to allow for the task to finish neatly and also
    // to give it time to empty log buffers
    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );

    cout << __func__ << " - END" <<  endl;
}

TEST_F(FibreControlServiceTestCases, TestErrorPaths)
{
    cout << __func__ << " - START" <<  endl;

    cout << __func__ << " *** TBD ***" <<  endl;

#if 0
    ICpriCore::RemoteAlarms remoteAlarms = cccSlave->readRemoteAlarms();
    EXPECT_TRUE(remoteAlarms.remoteLOS == 0);
    EXPECT_TRUE(remoteAlarms.remoteLOF == 0);
    EXPECT_TRUE(remoteAlarms.remoteRAI == 0);
    EXPECT_TRUE(remoteAlarms.remoteSDI == 0);
    EXPECT_TRUE(remoteAlarms.remoteRST == 0);

    // set no LOS alarm
    offTargetFPGA.writeField("los[0]", 0x00);
    EXPECT_TRUE(cccSlave->haveLOS() == false);
    // set LOS alarm
    offTargetFPGA.writeField("los[0]", 0x01);
    EXPECT_TRUE(cccSlave->haveLOS() == true);

    // set no LOF alarm
    offTargetFPGA.writeField("lof[0]", 0x00);
    EXPECT_TRUE(cccSlave->haveLOF() == false);
    // set LOF alarm
    offTargetFPGA.writeField("lof[0]", 0x01);
    EXPECT_TRUE(cccSlave->haveLOF() == true);
#endif


    cout << __func__ << " - END" <<  endl;
}

TEST_F(FibreControlServiceTestCases, TestResetScenarios)
{
    cout << __func__ << " - START" <<  endl;

    cout << __func__ << " *** TBD ***" <<  endl;

    cout << __func__ << " - END" <<  endl;
}

TEST_F(FibreControlServiceTestCases, TestAlarmScenarios)
{
    cout << __func__ << " - START" <<  endl;

    cout << __func__ << " *** TBD ***" <<  endl;

    cout << __func__ << " - END" <<  endl;
}

TEST_F(FibreControlServiceTestCases, TestMultiplePorts)
{
    cout << __func__ << " - START" <<  endl;

    cout << __func__ << " *** TBD ***" <<  endl;

    cout << __func__ << " - END" <<  endl;
}

TEST_F(FibreControlServiceTestCases, TestTidyUp)
{
    cout << __func__ << " - START" <<  endl;

    testTidyUp();

    // sleep for just over the default service update period to allow for the task to finish neatly and also
    // to give it time to empty log buffers
    usleep( (FibreControlService::SERVICE_PERIOD + gServiceTimeOffset) * 1000 );

    cout << __func__ << " - END" <<  endl;
}


int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

} // end namespace
