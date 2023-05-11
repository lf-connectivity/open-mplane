/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriController.cpp
 * \brief     Implementation of common radio services CPRI Controller to create and control the CPRI interface
 *
 *
 * \details   Implementation of common radio services CPRI Controller to create and control the CPRI interface
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include <memory>

#include "Task.h"
#include "ICpri.h"
#include "CpriController.h"

using namespace Mplane;
using namespace std;

//=============================================================================================================
// SINGLETONS/FACTORIES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFibreControl> IFibreControl::getInterface()
{
    static std::shared_ptr<IFibreControl> _rInstance(
            std::dynamic_pointer_cast<IFibreControl>( ICpriController::getInterface()));

    return _rInstance;
}

//-------------------------------------------------------------------------------------------------------------
// This is an ALU specific CPRI SFP Control logic, to enable slave transmit before sync is established
class CpriSfpControlLogic : public virtual ICpriSfpControlLogic
{
public:
    CpriSfpControlLogic() {}
    virtual ~CpriSfpControlLogic() { }
    virtual bool sfpSlaveTransmitBeforeSync() const override { return true; }
};

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICpriController> CpriController::getInterface()
{
    static std::shared_ptr<ICpriSfpControlLogic> sfpLogic(std::make_shared<CpriSfpControlLogic>());
//    static std::shared_ptr<ICpriController> _pInstance(std::make_shared<CpriController>(sfpLogic));
    static std::shared_ptr<ICpriController> _pInstance(new CpriController(sfpLogic));

    return _pInstance;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
/*
 * Thales ATG requirements tagging. Do no remove.
 *
 * \satisfy{@req_8403{019}}
 * \satisfy{@req_8403{020}}
 */
CpriController::CpriController(std::shared_ptr<ICpriSfpControlLogic> sfpLogic) :
        Loggable("CpriController", "CC"),
        mIsEndRE(true),
        mLoopbackCarrier(1),  // carrier to perform loopback on, default to first carrier
        mControllerStarted(false),
        mServiceInProgress(false),
        mControllerTickShowState(false),
        mCpri(  ICpri::getInterface() )
{
#ifdef DEBUG_CPRI_CONTROL
	// enable debug on start up
	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "CC") ;
#endif

    // reserve vector space for all CPRI ports handlers
    mPortHandlers.reserve(ICpri::getInterface()->getNumCpriPorts());

    for (UINT32 port = 0; port < ICpri::getInterface()->getNumCpriPorts();
            port++)
    {
        // instantiate a port handler for each port
        mPortHandlers.push_back(ICpriPortHandler::factory(port, sfpLogic)) ;
    }
}

//-------------------------------------------------------------------------------------------------------------
CpriController::~CpriController()
{
    /* We do not expect the destructor to ever be called in normal execution.
     * This is included for good practice to tidy up, and is useful to ensure unit
     * tests have a clean exit with no memory leak issues.
     */
    mPortHandlers.clear();
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::show()
{
    std::stringstream ss;
    ss << std::endl;
    show(ss);
    eventInfo("%s", ss.str().c_str());
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::show(std::ostream& os)
{
    logStream(os, "*** CpriController show ***");

    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        // show each port handler
        showPort(os, port);
    }
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::showPort(std::ostream& os, UINT32 portIndex)
{
    if (portIndex < mPortHandlers.size())
    {
        // show each port handler
        mPortHandlers[portIndex]->show(os);
    }
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::masterLinkResetRequest(bool resetEnabled)
{
    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        if (mPortHandlers[port]->isMaster())
        {
            logDebugNormal(
                    "%s: master link reset %s being initiated on port %d",
                    __func__, resetEnabled ? "ENABLE" : "DISABLE", port);

            if (resetEnabled)
            {
                // Initiate a master link reset. Must leave in disabled state
                // to stop downstream RRH from continually resetting.
                enableMasterReset(port);
                Task::msSleep(20); // Short (20ms) delay to ensure it takes effect.
            }
            disableMasterReset(port);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------
bool CpriController::getMasterLinkStatus(
        ICpriCore::CpriPortStatus& portStatus)
{
    bool returnStatus = false;

    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        if (mPortHandlers[port]->isMaster())
        {
            portStatus = mPortHandlers[port]->getLinkStatus();
            // @todo really??
            returnStatus = true;
            break;
        }
    }

    return returnStatus;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriController::getSlaveLinkStatus(UINT32 cpriPort,
        ICpriCore::CpriPortStatus& portStatus)
{
    if (cpriPort < mPortHandlers.size() && mPortHandlers[cpriPort]->isSlave())
    {
        portStatus = mPortHandlers[cpriPort]->getLinkStatus();
        // @todo really?
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 CpriController::getNumPortHandlers()
{
    return mPortHandlers.size();
}

//-------------------------------------------------------------------------------------------------------------
bool CpriController::attachToPortHandler(UINT32 cpriPort,
        Observer<ICpriPortHandler>& observer)
{
    if (cpriPort < mPortHandlers.size())
    {
        mPortHandlers[cpriPort]->attach(observer);
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriController::detachPortHandler(UINT32 cpriPort,
        Observer<ICpriPortHandler>& observer)
{
    if (cpriPort < mPortHandlers.size())
    {
        mPortHandlers[cpriPort]->detach(observer);
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::showFibreControl()
{
    this->show();
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::startFibreControl()
{
    logDebugVerbose("CpriController %s", __func__);

    /*
     * We must determine what type of reboot we should be performing here.
     * For a 'FULL hardware reboot' we perform a default setup of the CPRI core in the FPGA.
     * For a 'PROCESSOR only reboot' the FPGA remains untouched and the setup is bypassed to allow
     * downstream CPRI links to continue operation.
     */
//    if (1 == 1) // @todo add a test for a full hardware reset in the FibreControl start method
    {
        // full reset, setup the CPRI to the default setup for the CPRI core
        defaultCoreSetup();
    }

    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        // start the port handlers. Sets the port status from the CPRI ports cores
        mPortHandlers[port]->start();
    }

    // populate CPRI attributes values
    populateCpriDesc();
    populateCpriStat();
    populateSfpData();

    // Indicate that we have been started
    mControllerStarted = true;
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::serviceFibreControl()
{
    logDebugNormal("CpriController %s", __func__);

    if (!mControllerStarted || mServiceInProgress)
    {
        // Early exit if we haven't been started or we are already servicing a service event
        return;
    }

    // Service event in progress
    mServiceInProgress = true;

    /*
     * This is the main focus of the CPRI controller. On each service entry it
     * polls the status of the CPRI ports and handles their individual state-machines.
     * If any change is noted then this will be reported to observers.
     */

    // Do the SLAVE port handling
    bool slaveChanged = slavePortHandling();

    if (slaveChanged)
    {
        // update OAM
        updateOAMSlaveCpriState();
    }

    // Do the MASTER port handling
    bool masterChanged = masterPortHandling();

    // Distribute the SLAVE and MASTER status as required.
    if (slaveChanged || masterChanged)
    {
        // update end of chain status
        updateEndRE();

        // populate CPRI attribute values that may have changed as a consequence of the state changes
        populateCpriStat();
        populateSfpData();

        // notify observers of the change in slave or master port status.
        notifyCpriPortObservers();
    }

    // dump the state machine info when requested by user/tester
    if (mControllerTickShowState)
    {
        controllerTickShow();
    }

    // Service event not in progress
    mServiceInProgress = false;

}

//-------------------------------------------------------------------------------------------------------------
void CpriController::resetFibreControl()
{
    logDebugVerbose("CpriController %s:  No action taken -- TBD", __func__);
}

//-------------------------------------------------------------------------------------------------------------
bool CpriController::setPortLineRateCapability(UINT32 cpriPort,
        CpriController::cpriRateCapabilityMask rateMask)
{
    logDebugVerbose("CpriController %s:  Rate mask 0x%02x", __func__, (unsigned)rateMask);

    // Configure slave port rate capabilities.
    bool returnStatus = false;

    if (cpriPort < mPortHandlers.size() && mPortHandlers[cpriPort]->isSlave())
    {
        mPortHandlers[cpriPort]->setPortLineRateCapability(rateMask);
        returnStatus = true;
    }

    return returnStatus;
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::loopbackRequest(bool state, UINT32 carrier,
        int txc, int rx1c, int rx2c)
{
    if (state)
    {
        // loopback being enabled, set the containers in the loopback request for the available free
        // carrier. Ensure that we don't override the real carrier data.

        enableSlaveLoopback();
    }
    else
    {
        disableSlaveLoopback();

        // restore the original container mapping
    }
}

//-------------------------------------------------------------------------------------------------------------
bool CpriController::getLayer2Information(UINT32 cpriPort,
        CpriController::cpriL2Info& cpriL2Info)
{
    bool returnStatus = false;

    if (cpriPort < mPortHandlers.size() && mPortHandlers[cpriPort]->isSlave())
    {
        cpriL2Info.linkId = mPortHandlers[cpriPort]->getLinkId();
        cpriL2Info.pmre = mPortHandlers[cpriPort]->getPmre();
        cpriL2Info.remoteEquipmentId = mPortHandlers[cpriPort]->getReId();
        returnStatus = true;
    }

    return returnStatus;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriController::isLoopbackCarrierAvailable()
{
    bool carrierAvailable = false;

    /* Check if there is a free unconfigured carrier to perform the loopback test.
     * For each carrier check to see if the container mapping data is configured.
     * If both the Tx and Rx containers are not configured then this is considered to
     * be an unconfigured carrier and can be used for a CPRI loopback test.
     */

    return carrierAvailable;
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::setProtocolId(UINT32 pidValue)
{
    if (pidValue == PID_SUPPORTED)
    {
        // see ARD-0546 for values
        for (UINT32 port = 0; port < mPortHandlers.size(); port++)
        {
            if (mPortHandlers[port]->isSlave())
            {
                mPortHandlers[port]->configSlavePort(
                        mPortHandlers[port]->getLinkStatus().lineRate,
                        ICpriCore::TxFormat_16);
            }
        }
    }
    else
    {
        eventWarning("Protocol ID %d, not supported by RRH", pidValue);
    }
}


//-------------------------------------------------------------------------------------------------------------
void CpriController::setTickShowState(bool state)
{
    // when true the state-machine states will be displayed each service period
    mControllerTickShowState = state;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICpriPortHandler> CpriController::getPortHandler(unsigned port) const
{
	if (port >= mPortHandlers.size())
		return std::shared_ptr<ICpriPortHandler>() ;

	return mPortHandlers.at(port) ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
void CpriController::defaultCoreSetup()
{
    // Called once at startup
    // The master port(s) are initialised before the slaves
    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        if (mPortHandlers[port]->isMaster())
        {
            mPortHandlers[port]->initPort();

            // Add a 10ms delay
            Task::msSleep(10);
        }
    }

    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        if (mPortHandlers[port]->isSlave())
        {
            mPortHandlers[port]->initPort();

            // Add a 10ms delay
            Task::msSleep(10);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::enableSlaveLoopback()
{
    logDebugVerbose("CpriController %s:  No action taken -- TBD", __func__);
    // TBD
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::disableSlaveLoopback()
{
    logDebugVerbose("CpriController %s:  No action taken -- TBD", __func__);
    // TBD
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::enableMasterReset(UINT32 port)
{
    mPortHandlers[port]->enableReset();
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::disableMasterReset(UINT32 port)
{
    mPortHandlers[port]->disableReset();
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::resetMasterPorts()
{
    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        if (mPortHandlers[port]->isMaster())
        {
            resetMasterPort(port);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::resetMasterPort(UINT32 port)
{
    logDebugVerbose( "%s: resetting master port %d",
            __func__, port);

    mPortHandlers[port]->resetPort();
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::updateOAMSlaveCpriState()
{
    // we only need to tell the OAM in the event the link status has changed
    // since we last reported it.
    // NOTE:  Consider whether this should be implemented as an Observer/Subject template rather than this
    //        Interface implementation

    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        if (mPortHandlers[port]->isSlave()
                && mPortHandlers[port]->getSlaveOamLinkState()
                        != mPortHandlers[port]->getSlaveLastOamLinkState())
        {
            // tell OAM the link status
            // TBD
//            IOamCpri::getInterface().OamCpriStable(mSlavePortHandler[port]->getOamLinkState());

            mPortHandlers[port]->setSlaveLastOamLinkState();
        }
    }
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::populateCpriDesc()
{
    logDebugVerbose("CpriController %s:  No action taken -- TBD", __func__);
    // TBD
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::populateCpriStat()
{
    logDebugVerbose("CpriController %s:  No action taken -- TBD", __func__);
    // TBD
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::populateSfpData()
{
    logDebugVerbose("CpriController %s:  No action taken -- TBD", __func__);
    // TBD
}

//-------------------------------------------------------------------------------------------------------------
bool CpriController::slavePortHandling()
{

    bool anyChange = false;

    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        // action each slave port state machine and record if there is a state change
        if (mPortHandlers[port]->isSlave())
        {
            anyChange |= mPortHandlers[port]->stateMachine();
        }
    }

    // Check for a SLAVE status change, as this can affect the master ports immediately
    // only do this if the main port is not a master port, ie we are possibly a
    // daisy chained RRH
    if (anyChange)
    {
        std::shared_ptr<ICpri> cpri = ICpri::getInterface();

        for (UINT32 port = 0, notDone = true;
                port < mPortHandlers.size() && notDone; port++)
        {
            if (mPortHandlers[port]->isSlave()
                    && mPortHandlers[port]->hasStateChanged())
            {
                // This slave port has changed state, so check what state it changed to
#ifdef DEBUG_CPRI_CONTROL
logDebugVerbose("CpriController: port %u slave? %u isMainMaster? %u state=%u Primary=%d",
		port, (unsigned)mPortHandlers[port]->isSlave(),
		(unsigned)cpri->isMainMaster(),
		(unsigned)mPortHandlers[port]->getSmState(),
		cpri->getPrimaryCpriPort()) ;
#endif

                // if the main port is not the master port then we are potentially a daisy chaned
                // RRH and therefore we set the master state when the slave comes up.
                // The the main port is the master, it is enable from start up.
                if (!cpri->isMainMaster())
                {
                    if (mPortHandlers[port]->getSmState() == ICpriPortHandler::STATE_GOOD
                            && port == cpri->getPrimaryCpriPort())
                    {
                        // TBD:  confirm how to manage the master ports when the slave ports change state
                        // If the primary slave port has gone GOOD then check to see if we need to enable the master port.
                        // Master may already be running after a processor reset. If it is running then do not disturb.
                        // Check if CPRISTAT master port is enabled as a gating test.
                        for (UINT32 masterPort = 0;  masterPort < mPortHandlers.size(); masterPort++)
                        {
#ifdef DEBUG_CPRI_CONTROL
logDebugVerbose("CpriController: port %u master? %u isCoreOutOfReset? %u",
		masterPort, (unsigned)mPortHandlers[masterPort]->isMaster(),
		(unsigned)cpri->getPortCore(masterPort).isCoreOutOfReset()) ;
#endif

                            if (mPortHandlers[masterPort]->isMaster()
                                    && cpri->getPortCore(masterPort)->isCoreOutOfReset() == false)
                            {
                                logDebugVerbose("CpriController: master port %u enabled", masterPort) ;

                                mPortHandlers[masterPort]->enableMasterPort(cpri->getPrimaryPortCore());
                                notDone = false;
                                break;  // end masterPort for loop
                            }
                        }
                    }
                    else if (mPortHandlers[port]->getSmState()  == ICpriPortHandler::STATE_BAD)
                    {
                        logDebugVerbose("CpriController: slave bad");

                        // If any slave port has gone BAD reset all master ports
                        resetMasterPorts();
                        notDone = false;
                    }
                }
            }
        }
    }

    return anyChange;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriController::masterPortHandling()
{
    bool anyChange = false;

    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        // action each master port state machine and record if there is a state change
        if (mPortHandlers[port]->isMaster())
        {
            anyChange |= mPortHandlers[port]->stateMachine();
        }
    }

    return anyChange;
}



//-------------------------------------------------------------------------------------------------------------
void CpriController::updateEndRE()
{
    /* Determine whether this RRH is at the end of a chain.
     * Depends on the status of the Master port(s).
     * All master ports must be disabled or link down for it to be set to 'end of chain'
     */
    bool lEndRE = true; // start at end of chain

    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        if (mPortHandlers[port]->isMaster()
                && (mPortHandlers[port]->getLinkStatus().active
                        || mPortHandlers[port]->getLinkStatus().logicallyEnabled))
        {
            lEndRE = false;  // not end of chain
            break;  // end the loop
        }
    }

    mIsEndRE = lEndRE;
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::notifyCpriPortObservers()
{
    // notify observers of the change in slave or master port status.
    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        if (mPortHandlers[port]->hasStateChanged())
        {
            // only notify when a port status has changed
            mPortHandlers[port]->notify();

            // Notify the ICpri object
            mCpri->signalPortChange(port) ;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------
void CpriController::controllerTickShow()
{
    for (UINT32 port = 0; port < mPortHandlers.size(); port++)
    {
        mPortHandlers[port]->showSmState();
    }
}


#if 0
//-------------------------------------------------------------------------------------------------------------
bool CpriController::changeCpriCfg()
{
    // this needs to be completed once the interface to the CPRI attributes is defined

    // change the CPRI config according to the CPRICFG attribute

    // if the PORTnMODE has changed for port n
    switch (PORTnMODE)
    {
        case PORTnMODE_SLAVE:
        mPortHandlers[port]->changePortMode(ICpri::CpriPortSlave);
        break;

        case PORTnMODE_MASTER:
        mPortHandlers[port]->changePortMode(ICpri::CpriPortMaster);
        break;
    }

}
#endif
