/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriPortHandling.cpp
 * \brief     Implementation of common radio services CPRI Port handler
 *
 *
 * \details   Implementation of common radio services CPRI Port handler
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>

#include "IRadio.h"
#include "Task.h"
#include "ICpri.h"
#include "CommonCpriCore.h"
#include "CpriController.h"
#include "CpriPortHandling.h"
#include "IFpgaMgr.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETONS/FACTORIES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Factory for creating instances if this
std::shared_ptr<ICpriPortHandler> CpriPortHandler::factory(unsigned port, std::shared_ptr<ICpriSfpControlLogic> sfpLogic)
{
	// NOTE: The following works (I can construct a new CpriPortHandler being as I'm in CpriPortHandler static context),
	// however you can't used std::make_shared<CpriPortHandler>() for some reason!
	//
	return std::shared_ptr<ICpriPortHandler>( new CpriPortHandler(port, sfpLogic) ) ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CpriPortHandler::CpriPortHandler(UINT32 instance, std::shared_ptr<ICpriSfpControlLogic> sfpLogic) :
	Loggable("CpriPortHandler", instance, "CC"),
	mPort(instance),
	mSfpLogic(sfpLogic),
	mCore(ICpri::getInterface()->getPortCore(mPort)),
	mCpri(ICpri::getInterface()),
	mPortLogicallyEnabled(false),
	mCpriLinkState(false),
	mCurrentState(ICpriPortHandler::STATE_INITIAL),
	mNextState( mCurrentState),
	mLastSmStateChanged(false),
	mMasterCMretryCount( CpriPortHandler::MASTER_CM_RETRY_COUNT),
	///  move these to CpriController ???
	mCpriPmre(1),   // default to having 1 master port
	mCpriReId(0),
	mCpriLinkId(0),
	mFpga( IFpgaMgr::getIFpgaSystemRegs() ),
	mCpriFaultDetectOn(false),
	mFixedLineRate(ICpriCore::RateUnknown)
{
#ifdef DEBUG_CPRI_CONTROL
	// enable debug on start up
	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "CC") ;
#endif

	// initialise the slave port status
    initialisePortStatus();
}

//-------------------------------------------------------------------------------------------------------------
CpriPortHandler::~CpriPortHandler()
{
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::show()
{
    std::stringstream ss;
    ss << std::endl;
    show(ss);
    eventInfo("%s", ss.str().c_str());
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::show(std::ostream& os)
{
    logStream(os, "*** CpriPortHandler show - Port %d is %s ***", mPort,
            getCoreModeString(mCore));

    if (isMaster())
    {
        logStream(os, "Port is logically %s",
                mPortLogicallyEnabled ? "enabled" : "disabled");

    }
//    else if (isSlave())
//    {
//        logStream(os, "Max Master Ports (PMRE) = %d", mCpriPmre);
//        logStream(os, "Remote EquipmentId (REID) = %d", mCpriReId);
//        logStream(os, "Link Id (LINKID) = %d", mCpriLinkId);
//    }

    logStream(os, "Port STATUS...");
    showPortStatus(mCurrentPortStatus, os);

    logStream(os, "STATE: %s", getStateString(mCurrentState)) ;

    // status as reported to OAM
    logStream(os, "  Link up[%s]",
            mCpriOAMSlavePortStatus.cpriLinkState ? "YES" : "NO");
    logStream(os, "  Last OAM reported link state[%s]",
            mCpriOAMSlavePortStatus.lastOAMReportedCpriLinkState ?
                    "Link up" : "Link down");

    logStream(os, "Port CONTROL info...");
    showPortControl(mPortControl, os);

    logStream(os, "*** CpriPortHandler show Port %d - end ***", mPort);

}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::isSlave()
{
    return mCore->isSlave();
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::isMaster()
{
    return mCore->isMaster();
}

//-------------------------------------------------------------------------------------------------------------
// initialise the slave port states
void CpriPortHandler::initialisePortStatus()
{
    ICpriCore::CpriPortStatus portStatus;

    portStatus.logicallyEnabled = false;
    portStatus.active = false;
    portStatus.mgtPllLock = false;
    portStatus.mgtTxClockLock = false;
    portStatus.mgtRxClockLock = false;
    portStatus.lineRate = ICpriCore::RateUnknown;
    portStatus.ethernetMinCMBandwidth = ICpriCore::CMRateUnknown;
    portStatus.ethernetMaxCMBandwidth = ICpriCore::CMRateUnknown;
    portStatus.protocolVersion = 0;
    portStatus.remoteSapDefect = false;
    portStatus.remoteLossOfFrame = false;
    portStatus.remoteLossOfSync = false;
    portStatus.sfpLos = true;  // start with no fibre connected
    portStatus.remoteAlarmInd = false;
    portStatus.localLossOfFrame = false;
    portStatus.localLossOfSync = false;

    mCurrentPortStatus = portStatus;

    // initialise OAM slave port status report variables.
    cpriOAMPortStatus oamPortStatus;

    oamPortStatus.cpriLinkState = false;
    oamPortStatus.lastOAMReportedCpriLinkState = false;

    mCpriOAMSlavePortStatus = oamPortStatus;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::stateMachine()
{
	bool returnState = false;

    if (isSlave())
    {
    	returnState = slaveStateMachine();
    }
    else if (isMaster())
    {
    	returnState = masterStateMachine();
    }

    // If fault detection is enabled, update the faults.
    if( true == mCpriFaultDetectOn )
    {
    	updateCpriFaults();
    }


    return returnState;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::showSmState()
{
    switch (mCurrentState)
    {
    case STATE_INACTIVE:
        eventInfo("%s %d: %s", getCoreModeString(mCore), mPort,
                getStateString(mCurrentState));
        break;
    case STATE_INITIAL:
        eventInfo("%s %d: %s", getCoreModeString(mCore), mPort,
                getStateString(mCurrentState));
        break;
    case STATE_BAD:
        eventInfo("%s %d: %s", getCoreModeString(mCore), mPort,
                getStateString(mCurrentState));
        break;
    case STATE_TRANSITION:
        eventInfo("%s %d: %s", getCoreModeString(mCore), mPort,
                getStateString(mCurrentState));
        break;
    case STATE_GOOD:
        eventInfo("%s %d: %s", getCoreModeString(mCore), mPort,
                getStateString(mCurrentState));
        break;
    }
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::CpriPortStatus CpriPortHandler::getLinkStatus()
{
    return mCurrentPortStatus;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::start()
{
    // set the port status from the core
    mCurrentPortStatus = getCpriPortStatus();

    // get interface to all supported radio fault
    mFaults = ICommonRadioFaults::getInstance();

    mLossOfSignalOwner = std::shared_ptr<LossOfSignalOwner>(new LossOfSignalOwner( mPort )) ;
    mLossOfFrameOwner = std::shared_ptr<LossOfFrameOwner>( new  LossOfFrameOwner( mPort )) ;
    mServiceAccessPointDefectIndOwner = std::shared_ptr<ServiceAccessPointDefectIndOwner>( new  ServiceAccessPointDefectIndOwner( mPort )) ;
    mRemoteAlarmIndicationOwner = std::shared_ptr<RemoteAlarmIndicationOwner>( new  RemoteAlarmIndicationOwner( mPort )) ;

    mLossOfSignalOwner->getFault()->addOwner( mLossOfSignalOwner );
    mLossOfFrameOwner->getFault()->addOwner( mLossOfFrameOwner );
    mServiceAccessPointDefectIndOwner->getFault()->addOwner( mServiceAccessPointDefectIndOwner );
    mRemoteAlarmIndicationOwner->getFault()->addOwner( mRemoteAlarmIndicationOwner );

    mLossOfSignalOwner->clear();
    mLossOfFrameOwner->clear();
    mServiceAccessPointDefectIndOwner->clear();
    mRemoteAlarmIndicationOwner->clear();

    setupDefaults();

	setupAutoNeg();
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::isLinkUp()
{
    return mCpriLinkState;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::resetPort()
{
    if (isSlave())
    {
        mCore->resetCore();

        logDebugVerbose("Slave Core Reset Complete for port %d", mPort);
    }

    if (isMaster())
    {
        if( mCpri->isMainMaster() )
        {
            mCore->resetCore();

            logDebugVerbose("Master Core Reset Complete for port %d", mPort);
        }
        else
        {
            mCore->putCoreIntoReset();

            logDebugVerbose("Master Core put into Reset Complete for port %d", mPort);
        }
    }

#ifdef DEBUG_CPRI_CONTROL
    logDebugVerbose("reset port %d : allowed rates [%s]", mPort,
    		mCore->getLineRateCapabilityString(mPortControl.allowableRates));
#endif

    // Need to re-write parameters after reset
    mCore->setPortParameters(mPortControl);

    // Don't monitor alarms until we're up
    mCpriFaultDetectOn = false ;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::isLinkOK(ICpriCore::CpriPortStatus portStatus)
{
	// Forward
	return mCore->isLinkOK(portStatus) ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::setPortLineRateCapability(ICpriTypes::cpriRateCapabilityMask rateMask)
{
    // Configure slave port rate capabilities.
    mPortControl.allowableRates.capableOfRate614_4  = ((rateMask & ICpriTypes::cpriRateMask614) != 0);
    mPortControl.allowableRates.capableOfRate1228_8 = ((rateMask & ICpriTypes::cpriRateMask1228) != 0);
    mPortControl.allowableRates.capableOfRate2457_6 = ((rateMask & ICpriTypes::cpriRateMask2457) != 0);
    mPortControl.allowableRates.capableOfRate3072_0 = ((rateMask & ICpriTypes::cpriRateMask3072) != 0);
    mPortControl.allowableRates.capableOfRate4915_2 = ((rateMask & ICpriTypes::cpriRateMask4915) != 0);
    mPortControl.allowableRates.capableOfRate6144_0 = ((rateMask & ICpriTypes::cpriRateMask6144) != 0);
    mPortControl.allowableRates.capableOfRate9830_4 = ((rateMask & ICpriTypes::cpriRateMask9830) != 0);
    mPortControl.allowableRates.capableOfRate10137_6= ((rateMask & ICpriTypes::cpriRateMask10137) != 0);

    logDebugVerbose(
            "%s: setting slave port %d line rate capability [%s]", __func__,
            mPort,
            mCore->getLineRateCapabilityString(mPortControl.allowableRates));

    mCore->setLineRateCapability(mPortControl.allowableRates);
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::configSlavePort(ICpriCore::LineRate lineRate,
        ICpriCore::TxFormat txFormat)
{
    // Configure slave port rate capabilities.

    switch (lineRate)
    {
    // see ARD-0546 for values

    case ICpriCore::Rate10137_6:  // rate 8
        mPortControl.txFormat = txFormat;
        mPortControl.ethernetBandwidth = ICpriCore::CMRate2400;
        mCore->setPortParameters(mPortControl);
        break;

    case ICpriCore::Rate9830_4:  // rate 7 now supported
        mPortControl.txFormat = txFormat;
        mPortControl.ethernetBandwidth = ICpriCore::CMRate2400;
        mCore->setPortParameters(mPortControl);
        break;

    case ICpriCore::Rate6144_0:  // rate 6
        mPortControl.txFormat = txFormat;
        mPortControl.ethernetBandwidth = ICpriCore::CMRate2400;
        mCore->setPortParameters(mPortControl);
        break;

    case ICpriCore::Rate4915_2:  // rate 5
        mPortControl.txFormat = txFormat;
        mPortControl.ethernetBandwidth = ICpriCore::CMRate2400;
        mCore->setPortParameters(mPortControl);
        break;

    case ICpriCore::Rate3072_0:  // rate 4
        mPortControl.txFormat = txFormat;
        mPortControl.ethernetBandwidth = ICpriCore::CMRate2400;
        mCore->setPortParameters(mPortControl);
        break;

    case ICpriCore::Rate2457_6:  // rate 3
        mPortControl.txFormat = txFormat;
        mPortControl.ethernetBandwidth = ICpriCore::CMRate1920;
        mCore->setPortParameters(mPortControl);
        break;

    case ICpriCore::Rate1228_8:  // rate 2
        mPortControl.txFormat = txFormat;
        mPortControl.ethernetBandwidth = ICpriCore::CMRate960;
        mCore->setPortParameters(mPortControl);
        break;

    case ICpriCore::Rate614_4:  // rate 1
        mPortControl.txFormat = txFormat;
        mPortControl.ethernetBandwidth = ICpriCore::CMRate960;
        mCore->setPortParameters(mPortControl);
        break;

    default:
        eventWarning("%s:  Unsupported CPRI line rate", __func__);
        break;
    }
}

//-------------------------------------------------------------------------------------------------------------
ICpriPortHandler::CpriSMStates CpriPortHandler::getSmState()
{
    return mCurrentState;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::initPort()
{
    // Don't monitor alarms until we're up
    mCpriFaultDetectOn = false ;

    // Restart the state machine
    mCurrentState = ICpriPortHandler::STATE_INITIAL ;
    mNextState = mCurrentState ;

	// Reset hardware and initialise
    if (isSlave())
    {
        logDebugVerbose( "%s:  Slave Port %d Init",
                __func__, mPort);

        if (mSfpLogic->sfpSlaveTransmitBeforeSync())
        {
            /* This is the abnormal CPRI behaviour, goes against the CPRI spec but is used by some customers.
             * Slave transmit is to be enabled before the sync is achieved, so we reset the core and setup the
             * port for auto-negotiation and then leave the control logic to the Slave state machine.
             */
            mCore->putCoreIntoReset();

            // Turn on the Slave transmit enable
            mCore->slaveTransmitEnable();

            // take the core out of reset and let the CPRI sync process begin
            Task::msSleep(10);

            mCore->takeCoreOutOfReset();

            /* Core Line rate defaults to "all line rates", which means the CPRI core will try to synchronise to
             * a link immediately after deasserting the reset. Software must set the line rate to 0 immediately after
             * deasserting the reset to allow for the setting of CPRI core parameters
             * (e.g. the ethernet pointer, line rate, etc.) before the link comes up.
             *
             * Auto negotiation is the preferred method of setting the line rate.
             * Once the line rate and the other preferred parameters are written to the core it starts the CPRI
             * sync process.
             */
            setupAutoNeg();
        }
        else
        {
            /* This is the normal CPRI behaviour.
             * Slave transmit is NOT to be enabled before the sync is achieved, so we put the slave port core into
             * reset and keep it in reset. It will be taken out of reset when the SFP_LOS is cleared.
             * The state machine controls the logic.
             */
            mCore->putCoreIntoReset();

            // Turn off the Slave transmit enable explicitly
            mCore->slaveTransmitDisable();
        }
    }
    if (isMaster())
    {
        logDebugVerbose( "%s:  Master Port %d Init", __func__, mPort);

        if( mCpri->isMainMaster() )
        {
            // puts the master port core into reset. Will be taken out of reset when the slave port is in sync
            mCore->putCoreIntoReset();

            // Master port is logically disabled
            mPortLogicallyEnabled = true;

            // take the core out of reset and let the CPRI sync process begin
            Task::msSleep(10);

            mCore->takeCoreOutOfReset();

            setupAutoNeg();

        }
        else
        {
            // puts the master port core into reset. Will be taken out of reset when the slave port is in sync
            mCore->putCoreIntoReset();


            // Master port is logically disabled
            mPortLogicallyEnabled = false;
        }
    }

}

//-------------------------------------------------------------------------------------------------------------
UINT32 CpriPortHandler::getPort()
{
    return mPort;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 CpriPortHandler::getPmre()
{
    return mCpriPmre;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 CpriPortHandler::getReId()
{
    return mCpriReId;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 CpriPortHandler::getLinkId()
{
    return mCpriLinkId;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::getSlaveOamLinkState()
{
    return mCpriOAMSlavePortStatus.cpriLinkState;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::getSlaveLastOamLinkState()
{
    return mCpriOAMSlavePortStatus.lastOAMReportedCpriLinkState;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::setSlaveLastOamLinkState()
{
    mCpriOAMSlavePortStatus.lastOAMReportedCpriLinkState =
            mCpriOAMSlavePortStatus.cpriLinkState;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::enableReset()
{
    // a master port only action
    mCore->enableTransmitResetRequest();
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::disableReset()
{
    // a master port only action
    mCore->disableTransmitResetRequest();
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::hasStateChanged()
{
    return mLastSmStateChanged;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::enableMasterPort(std::shared_ptr<ICpriCore> slaveCore)
{
    ICpriCore::CpriPortControl portControl = mPortControl;

    // hold the port in core reset until config is done
    mCore->putCoreIntoReset();

#ifdef DEBUG_CPRI_CONTROL
    logDebugVerbose( "%s: Master port %d Enable (is master? %u) : Current rates [%s]",
            __func__, mPort, (unsigned)isMaster(),
            mCore->getLineRateCapabilityString(mPortControl.allowableRates)
    );
#else
    logDebugVerbose( "%s: Master port %d Enable (is master? %u)",
            __func__, mPort, (unsigned)isMaster());
#endif

    // Program the preferred protocol
    mCore->setPreferredProtocolVersion(getPreferredProtocolValue());

    // Program the preferred ethernet pointer
    mCore->setPreferredEthernetPointer(getPreferredEthPointerValue());

    // Program the preferred HDLC rate
    mCore->setPreferredHdlcRate(getPreferredHdlcRateValue());

    // BUG #1692 - set rate to the single slave core rate
    portControl.allowableRates = ICpriCore::LineRateCapability() ;

    // Copy the actual slave line rate to the master line rate - only
    // one option given in available rates.
    switch (slaveCore->getCurrentLineRate())
    {
    case ICpriCore::Rate614_4:
        portControl.allowableRates.capableOfRate614_4 = true;
        break;
    case ICpriCore::Rate1228_8:
        portControl.allowableRates.capableOfRate1228_8 = true;
        break;
    case ICpriCore::Rate2457_6:
        portControl.allowableRates.capableOfRate2457_6 = true;
        break;
    case ICpriCore::Rate3072_0:
        portControl.allowableRates.capableOfRate3072_0 = true;
        break;
    case ICpriCore::Rate4915_2:
        portControl.allowableRates.capableOfRate4915_2 = true;
        break;
    case ICpriCore::Rate6144_0:
        portControl.allowableRates.capableOfRate6144_0 = true;
        break;
    case ICpriCore::Rate9830_4:
        portControl.allowableRates.capableOfRate9830_4 = true;
        break;
    case ICpriCore::Rate10137_6:
        portControl.allowableRates.capableOfRate10137_6 = true;
        break;
    default:
        eventWarning("%s: Unsupported required line rate", __func__);
//        alert( "Unsupported required line rate" );
        break;
    }

#ifdef DEBUG_CPRI_CONTROL
    logDebugVerbose( "%s: Master port %d - Slave rate %s, This rate [%s]",
            __func__, mPort,
            ICpriCore::getCurrentLineRateString(slaveCore->getCurrentLineRate()),
            mCore->getLineRateCapabilityString(portControl.allowableRates)
    );
#endif

    // Set ethernet preferred ethernet rate to currently selected slave rate.
    portControl.ethernetBandwidth =
            (ICpriCore::CMRateValue_t) slaveCore->getCurrentEthernetPointer();

    // take the core out of reset and let the CPRI sync process begin
    Task::msSleep(10);

    mCore->takeCoreOutOfReset();

    // Configure the topology for the downstream RRH.
    mCore->setTopologyREID(slaveCore->getTopologyREID() + 1);

    // Configure master port, sets the line rate, which kicks off the CPRI sync process.
    // NOTE: This *MUST* be written AFTER taking the core out of reset otherwise the values are not updated
    mCore->setPortParameters(portControl);

    mPortControl = portControl;

    mPortLogicallyEnabled = true;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::disableMasterPort()
{
    logDebugVerbose( "%s: Master port %d Disable",
            __func__, mPort);

    // Inform alarm handler that the Master port CPRI alarms should now be blocked/disabled
    // to avoid raising bogus alarms.
    // TBD.

    resetPort();

    // Update CPRISTAT -
    // Link State is INACTIVE
    // Link Info is MASTER_SET_DISABLED

    mPortLogicallyEnabled = false;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::changePortMode(ICpri::CpriPortType cpriPortType)
{
    bool result = false;

    if (mCore->changeMode(cpriPortType))
    {
        // core changed successfully, reinitialise the data

        // Puts the port core into reset. Will be taken out of reset when the SFP_LOS is cleared.
        // The state machine controls the logic
        mCore->putCoreIntoReset();

        mPortLogicallyEnabled = false;
        mCpriLinkState = false;
        mCurrentState = ICpriPortHandler::STATE_INITIAL;
        mNextState = mCurrentState;
        mLastSmStateChanged = false;
        mMasterCMretryCount = CpriPortHandler::MASTER_CM_RETRY_COUNT;
        mCpriPmre = 1;   // default to having 1 master port
        mCpriReId = 0;
        mCpriLinkId = 0;

        // initialise the slave port status
        initialisePortStatus();

        result = true;
    }

    return result;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::setFixedLineRate(ICpriCore::LineRate lineRate)
{
	switch (lineRate)
	{
	case ICpriCore::RateUnknown:
		break ;

	case ICpriCore::Rate614_4:
		if (!mPortControl.allowableRates.capableOfRate614_4)
			return false ;
		break ;

	case ICpriCore::Rate1228_8:
		if (!mPortControl.allowableRates.capableOfRate1228_8)
			return false ;
		break ;

	case ICpriCore::Rate2457_6:
		if (!mPortControl.allowableRates.capableOfRate2457_6)
			return false ;
		break ;

	case ICpriCore::Rate3072_0:
		if (!mPortControl.allowableRates.capableOfRate3072_0)
			return false ;
		break ;

	case ICpriCore::Rate4915_2:
		if (!mPortControl.allowableRates.capableOfRate4915_2)
			return false ;
		break ;

	case ICpriCore::Rate6144_0:
		if (!mPortControl.allowableRates.capableOfRate6144_0)
			return false ;
		break ;

	case ICpriCore::Rate9830_4:
		if (!mPortControl.allowableRates.capableOfRate9830_4)
			return false ;
		break ;

	case ICpriCore::Rate10137_6:
		if (!mPortControl.allowableRates.capableOfRate10137_6)
			return false ;
		break ;

	default:
		return false ;
	}

	forceFixedLineRate(lineRate) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::clearFixedLineRate()
{
	// clear fixed rate
	mFixedLineRate = ICpriCore::RateUnknown ;

	// restore allowable rates to the real set
	mPortControl.allowableRates = mCore->getLineRateCapability() ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::forceFixedLineRate(ICpriCore::LineRate lineRate)
{
	mFixedLineRate = lineRate ;

	if( lineRate == ICpriCore::Rate614_4 )
	{
		mPortControl.allowableRates.capableOfRate614_4 = true;
	}
	else
	{
		mPortControl.allowableRates.capableOfRate614_4 = false;
	}

	if( lineRate == ICpriCore::Rate1228_8 )
	{
		mPortControl.allowableRates.capableOfRate1228_8 = true;
	}
	else
	{
		mPortControl.allowableRates.capableOfRate1228_8 = false;
	}

	if( lineRate == ICpriCore::Rate2457_6 )
	{
		mPortControl.allowableRates.capableOfRate2457_6 = true;
	}
	else
	{
		mPortControl.allowableRates.capableOfRate2457_6 = false;
	}

	if( lineRate == ICpriCore::Rate3072_0 )
	{
		mPortControl.allowableRates.capableOfRate3072_0 = true;
	}
	else
	{
		mPortControl.allowableRates.capableOfRate3072_0 = false;
	}

	if(  lineRate == ICpriCore::Rate4915_2 )
	{
		mPortControl.allowableRates.capableOfRate4915_2 = true;
	}
	else
	{
		mPortControl.allowableRates.capableOfRate4915_2 = false;
	}

	if(  lineRate == ICpriCore::Rate6144_0 )
	{
		mPortControl.allowableRates.capableOfRate6144_0 = true;
	}
	else
	{
		mPortControl.allowableRates.capableOfRate6144_0 = false;
	}

	if(  lineRate == ICpriCore::Rate9830_4 )
	{
		mPortControl.allowableRates.capableOfRate9830_4 = true;
	}
	else
	{
		mPortControl.allowableRates.capableOfRate9830_4 = false;
	}

	if(  lineRate == ICpriCore::Rate10137_6 )
	{
		mPortControl.allowableRates.capableOfRate10137_6 = true;
	}
	else
	{
		mPortControl.allowableRates.capableOfRate10137_6 = false;
	}
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::showPortStatus(
        ICpriCore::CpriPortStatus& portStatus, std::ostream& os)
{
    logStream(os, "  Fibre connected[%s]",
            isFibreConnected(portStatus) ? "YES" : "NO");

    logStream(os, "  MGT Clocks: PLL[%s], Tx Clock[%s], Rx Clock[%s]",
            portStatus.mgtPllLock ? "LOCK" : "NO LOCK",
            portStatus.mgtTxClockLock ? "LOCK" : "NO LOCK",
            portStatus.mgtRxClockLock ? "LOCK" : "NO LOCK");

    logStream(os, "  logicallyEnabled[%s], active[%s]",
            portStatus.logicallyEnabled ? "YES" : "NO",
            portStatus.active ? "YES" : "NO");

    logStream(os, "  line rate=%s Mbps",
            ICpriCore::getCurrentLineRateString(
                    portStatus.lineRate));
    logStream(os, "  ethernet CM bit rate Mbps:  Min=%s,  Max=%s",
            mCore->getCurrentEthernetRateString(
                    portStatus.ethernetMinCMBandwidth),
            mCore->getCurrentEthernetRateString(
                    portStatus.ethernetMaxCMBandwidth));

    logStream(os, "  CPRI Protocol Version=%d", portStatus.protocolVersion);
    logStream(os, "  Remote SAP Defect[%s],  Remote Loss of Frame[%s],  Remote Loss of Sync[%s]",
            portStatus.remoteSapDefect ? "YES" : "NO",
            portStatus.remoteLossOfFrame ? "YES" : "NO",
            portStatus.remoteLossOfSync ? "YES" : "NO");

    logStream(os, "  Local Loss of Frame[%s],  Local Loss of Sync[%s]",
            portStatus.localLossOfFrame ? "YES" : "NO",
            portStatus.localLossOfSync ? "YES" : "NO");
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::showPortControl(
        ICpriCore::CpriPortControl& portControl, std::ostream& os)
{
    logStream(os, "  TX format for BBU[%s]",
            mCore->getTxFormatString(
                    portControl.txFormat));
    logStream(os, "  Supported CPRI rates[%s]",
            mCore->getLineRateCapabilityString(
                    portControl.allowableRates));
    logStream(os, "  Ethernet bandwidth[%s Mbps]",
            mCore->getCurrentEthernetRateString(
                    portControl.ethernetBandwidth));
}


//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::portStatusChanged(
        ICpriCore::CpriPortStatus newStatus)
{
	std::stringstream ss;
	ss << std::endl;

	logStream(ss, "%s: %s port status has changed for port %d", __func__,
			getCoreModeString(mCore), mPort);

	logStream(ss, "PORT %d STATUS ..WAS..", mPort);
	showPortStatus(mCurrentPortStatus, ss);

	logStream(ss, "PORT %d STATUS ..NEW..", mPort);
	showPortStatus(newStatus, ss);

	logDebugVerbose(ss.str());

    mCurrentPortStatus = newStatus;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::slaveStateMachine()
{
    bool anyChange = false;

    // get the port status from the slave core
    ICpriCore::CpriPortStatus newPortStatus = getCpriPortStatus();

    // check if the link is ok
    bool slaveOK = isLinkOK(newPortStatus);

    // check if anything has changed in the port status
    if (hasPortStatusChanged(newPortStatus))
    {
        portStatusChanged(newPortStatus);

        anyChange = true;
    }

    mNextState = mCurrentState;

    logDebugVerbose(
            "%s: port %d: current state %s: slaveOK[%s]: port status changed[%s] ",
            __func__, mPort, getStateString(mCurrentState),
            slaveOK ? "Yes" : "No", anyChange ? "Yes" : "No");

    switch (mCurrentState)
    {
    case STATE_INACTIVE:  // Does nothing, an inactive port
        break;

    case STATE_INITIAL:

        if (mSfpLogic->sfpSlaveTransmitBeforeSync())
        {
            /* This is the abnormal CPRI behaviour case, as it goes against the CPRI spec but is used by some customers.
             * In this case the core is out of reset and the transmit enabled, to allow the BBU or RRH Master
             * to detect this RRH and for it to start the sync process.
             * No action is taken, and we transition to the next state, waiting for the link to become good.
             */

            // change state to BAD, waiting for link to become good
            mNextState = STATE_BAD;
        }
        else
        {
            /* This is the normal CPRI behaviour.
             * In this case the core is held in reset and the transmit disabled.
             * We wait for the fibre to get connected and for the clocks to be locked.
             * There is no timeout, it will wait in this state forever.
             * Once connected and clocks locked we can program its preferred settings and then move on to progress
             * through the next states.
             * The core is still held in reset whilst in this state.
             */
            if (isFibreConnected(newPortStatus)
                    && areClocksLocked(newPortStatus))
            {
                // Turn on the Slave transmit enable
                mCore->slaveTransmitEnable();

                // take the core out of reset and let the CPRI sync process begin
                Task::msSleep(10);

                mCore->takeCoreOutOfReset();

                /* Core Line rate defaults to "all line rates", which means the CPRI core will try to synchronise to
                 * a link immediately after deasserting the reset. Software must set the line rate to 0 immediately after
                 * deasserting the reset to allow for the setting of CPRI core parameters
                 * (e.g. the ethernet pointer, line rate, etc.) before the link comes up.
                 *
                 * Auto negotiation is the preferred method of setting the line rate.
                 * Once the line rate and the other preferred parameters are written to the core it starts the CPRI
                 * sync process.
                 */
                setupAutoNeg();

                // change state to BAD, waiting for link to become good
                mNextState = STATE_BAD;
            }
        }
        break;

    case STATE_BAD:

    	/**
    	 * In this state we need to keep checking the allowable rates in case the reason we're here is due to the
    	 * SFP module being pulled. In that case we have to keep re-reading the SFP module to get the real
    	 * set of allowed rates.
    	 *
    	 * Once we have a valid set of rates to use we can then ensure that auto-negotiation is set correctly
    	 */
    	checkAutoNeg() ;

        /* In this state we are waiting for the port to become good.
         * There is no timeout, it will wait in this state forever.
         */
        if (slaveOK)
        {
            portStatusChanged(newPortStatus);
            configSlavePort(newPortStatus.lineRate, mPortControl.txFormat);
            updateTopologyData();

            // this will force an observer update. Not entirely sure why we'd want to but I'll keep it
            // for backwards compatibility
            anyChange = true;

            // only set Slave port Link is up if BOTH Link Id and Re Id are non-zero
            if ((mCpriLinkId != 0) && (mCpriReId != 0))
            {
                setSlavePortLinkUp();

                /* Notify alarm handler that Slave CPRI is up.
                 * This is used to unblock certain Slave port hardware faults.
                 * eg.
                 * clock alarms,
                 * sync alarms,
                 * CPRI alarms (LOS, LOF.....),
                 * OOL alarms,
                 * .....  more  ......
                 *
                 */

                // change state to transition, waiting for clocks to be locked
                mNextState = STATE_TRANSITION;

                // reset the count of the number of zero REID reads
                std::dynamic_pointer_cast<CommonCpriCore>(mCore)->resetCpriReIdIsZeroCount();
            }
        }
        break;

    case STATE_TRANSITION:
        /* In this state we double check that the clocks are locked.
         * If not, we go back to the BAD state.
         */
        if (areClocksLocked(newPortStatus))
        {
            // change state to good, now in normal operating mode
            mNextState = STATE_GOOD;

            mCpriFaultDetectOn = true;
        }
        else
        {
            // change state, go back to the start
            mNextState = STATE_BAD;
        }

        break;

    case STATE_GOOD:
        /* We stay in this state while the link is up and good.
         * If it goes down then the state machine goes back to the start, i.e. to state BAD.
         */
        if (!slaveOK)
        {
            portStatusChanged(newPortStatus);

            setSlavePortLinkDown();

            // change state, go back to the start
            mNextState = STATE_BAD;

//            mCpriFaultDetectOn = false;
        }
        break;

    } // end switch statement

    // check for state change
    if (mCurrentState != mNextState)
    	anyChange = true ;

    mCurrentState = mNextState;

    mLastSmStateChanged = anyChange;

    return anyChange;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::masterStateMachine()
{
    bool anyChange = false;

    // get the port status from the master core
    ICpriCore::CpriPortStatus newPortStatus = getCpriPortStatus();

    // check if the link is ok
    bool masterOK = isLinkOK(newPortStatus);

    // check if anything has changed in the port status
    if (hasPortStatusChanged(newPortStatus))
    {
        portStatusChanged(newPortStatus);

        anyChange = true;
    }

    logDebugVerbose(
            "%s: port %d: current state %s: masterOK[%s]: port status changed[%s] ",
            __func__, mPort, getStateString(mCurrentState),
            masterOK ? "Yes" : "No", anyChange ? "Yes" : "No");

    mNextState = mCurrentState;

    switch (mCurrentState)
    {
    case STATE_INACTIVE:  // Does nothing, an inactive port
        break;

    case STATE_INITIAL:
        /* In this initial state we wait for the fibre to get connected and for the clocks to be locked.
         * There is no timeout, it will wait in this state forever.
         * Once connected and clocks locked we can program its preferred settings and then move on to progress
         * through the next states.
         * The core is still held in reset whilst in this state.
         */
        if (isFibreConnected(newPortStatus) && areClocksLocked(newPortStatus))
        {
            // change state to BAD, waiting for link to become good
            mNextState = STATE_BAD;
        }
        break;

    case STATE_BAD:
        /* In this state we are waiting for the port to become good.
         * There is no timeout, it will wait in this state forever if it never comes good.
         * If it comes good but does not manage to get a stable CM rate then a retry counter is used
         * to transition the state so that the onus is on the controlling OAM to reset the master link.
         */
        if (masterOK)
        {
            mMasterCMretryCount--;

            if (ICpri::getInterface()->isCMRateStable()
                    || mMasterCMretryCount == 0)
            {
                // Link is stable or the retries expired, transition to good
                // state. At least if master is up the OAM can send a LINKRESET.

                mMasterCMretryCount = MASTER_CM_RETRY_COUNT;

                portStatusChanged(newPortStatus);

                setMasterPortLinkUp();

                // Next state
                mNextState = STATE_TRANSITION;
            }
            else
            {
                // Master CMRate is unstable - need to reset the master.
                // Should never happen for the RRH as the CM rate should always be stable.
                resetPort();

                if( !mCpri->isMainMaster() )
                {
                    // re-enable the master port from the primary slave core
                    enableMasterPort(ICpri::getInterface()->getPrimaryPortCore());
                }
                // Update CPRISTAT - as state machine not being implemented.
                // Link State is INIT
                // Link Info is MASTERLINK_INITIALISING

                eventWarning(
                        "%s: CPRI Master Reset - CMRate is unstable, remaining retries=%d",
                        __func__, mMasterCMretryCount);
            }
        }
        break;

    case STATE_TRANSITION:

        /* Notify alarm handler that Master CPRI is up.
         * This is used to unblock certain Master port hardware faults.
         * eg.
         * clock alarms,
         * sync alarms,
         * CPRI alarms (LOS, LOF.....),
         * OOL alarms,
         * .....  more  ......
         *
         */
        // enable pause packets for CPRI port 1 ethernet vlan
        //-> @TODO move this to an interface in hardware, should not use FPGA directly.
        mFpga->write_ethPauseMask(0x1);


        mNextState = STATE_GOOD;

        mCpriFaultDetectOn = true;
        break;

    case STATE_GOOD:
        /* We stay in this state while the link is up and good.
         * If it goes down then the state machine goes back to the start, i.e. to state BAD.
         */
        if (!masterOK)
        {
            portStatusChanged(newPortStatus);

            setMasterPortLinkDown();

            // disable pause packets for CPRI port 2 ethernet vlan
            mFpga->write_ethPauseMask(0);

            mNextState = STATE_BAD;

//            mCpriFaultDetectOn = false;
        }
        break;

    } // end switch master state

    if (anyChange)
		logDebugVerbose(
				"%s: port %d: current state %s -> next state %s ",
				__func__, mPort, getStateString(mCurrentState),
				getStateString(mNextState));

    // check for state change
    if (mCurrentState != mNextState)
    	anyChange = true ;

    mCurrentState = mNextState;

    mLastSmStateChanged = anyChange;

    return anyChange;
}



//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::setSlavePortLinkUp()
{
    mCpriLinkState = true;

    // set status for OAM reporting via updateOAMCpriState method
    mCpriOAMSlavePortStatus.cpriLinkState = mCpriLinkState;

    // Slave link is up
#if 0
    if we are currently not using CPRI derived clock
    {
        // Switch to internal CPRI reference.
    }
#endif
    // Slave is up so inform the OAM so it can update the CPRISTAT attribute
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::setMasterPortLinkUp()
{
    mCpriLinkState = true;

    // Master link is up so must be in either PASS or PARTIAL states.
#if 0
    if (mCurrentPortStatus.sapDefect)
    {
        // Update CPRISTAT -
        // Link State is PARTIAL
        // Link Info is MASTERLINK_SET_PARTIAL
    }
    else
    {
        // Update CPRISTAT -
        // Link State is PASS
        // Link Info is MASTERLINK_SET_PASS
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::setSlavePortLinkDown()
{
    mCpriLinkState = false;

    // set status for OAM reporting via updateOAMCpriState method
    mCpriOAMSlavePortStatus.cpriLinkState = mCpriLinkState;

    // Link has gone down.
    // It must have been active so now set it to fail.

#if 0
    if (linkState != INIT || mCurrentPortStatus.active == true)
    {
        // Move slave link state to FAIL state only if not initialising or link is active.

        // Update CPRISTAT -
        // Link State is FAIL
        // Link Info is SLAVELINK_SET_FAIL
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::setMasterPortLinkDown()
{
    // Master link has gone down.
    // It must have been active so now set it to fail.

    mCpriLinkState = false;


#if 0
    if (mCurrentPortStatus.logicallyEnabled == true)
    {
        if (linkState != INIT ||
                mCurrentPortStatus.active == true)
        {
            // Move slave link state to FAIL state only if not initialising or link is active.

            // Update CPRISTAT -
            // Link State is FAIL
            // Link Info is MASTERLINK_SET_FAIL
        }
    }
    else if (CPRI master port enable State = DISABLE)
    {
        // Move master link state to INACTIVE state only if CPRISTAT state for master link is disable.

        // Update CPRISTAT -
        // Link State is INACTIVE
        // Link Info is MASTERLINK_SET_INACTIVE
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::setupDefaults()
{
    // This setup only applies to a slave port
    ICpriCore::CpriPortControl spc;

    /**
     * Note: this function must be called immediately after the core is taken out of reset.
     * When the core comes out of reset it will immediately attempt to sync and the line rate capabilities
     * defaults to "capable of all rates".
     *
     * Therefore this function sets the line rate capabilities to zero immediately after
     * deasserting the reset to allow for the setting of CPRI core parameters
     * (e.g. the ethernet pointer, line rate, etc.) before the link comes up.
     */

    // Setting no preferred line rate capability will inhibit the core attempting to sync.
    // Allows us time to setup the registers before setting the real line rate capabilities.
    mCore->setNoLineRateCapability();

    // Program the preferred protocol
    mCore->setPreferredProtocolVersion(getPreferredProtocolValue());

    // Program the preferred ethernet pointer
    mCore->setPreferredEthernetPointer(getPreferredEthPointerValue());

    // Program the preferred HDLC rate
    mCore->setPreferredHdlcRate(getPreferredHdlcRateValue());

    spc.txFormat = ICpriCore::TxFormat_9e2;

    spc.allowableRates = ICpriCore::LineRateCapability() ;

    spc.ethernetBandwidth = ICpriCore::CMRate960;

    mPortControl = spc;

    // Program the preferred line rates to the core register
    mCore->setPortParameters(spc);
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::checkAutoNeg()
{
	ICpriCore::LineRateCapability rates(getAllowableRates()) ;

	// if no available rates then stop
	if ( rates.empty() )
	{
		// see if object data matches the hardware
		if ( !mPortControl.allowableRates.empty() )
		{
			// reflect the hardware
			mPortControl.allowableRates.clear() ;

			// clear out old line rate to ensure hardware uses new value when it's set
		    mCore->setNoLineRateCapability();
		}
		return ;
	}

	// if rates have changed then use them
	if (rates != mPortControl.allowableRates)
//		&&
//		mFixedLineRate == ICpriCore::RateUnknown)
	{
			setupAutoNeg() ;
	}
//
//	// if there is a fixed line rate set then use that and only that rate
//	if (mFixedLineRate != ICpriCore::RateUnknown)
//	{
//		setupDefaults() ;
//
//		// Program the preferred line rates to the core register
//	    mCore->setPortParameters(mPortControl);
//
//	    //clearFixedLineRate();
//	}

}


//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::setupAutoNeg()
{
	logDebugVerbose("%s: port %d", __func__, mPort);

	setupDefaults() ;

    if (mFixedLineRate == ICpriCore::RateUnknown)
    {
        // This setup only applies to a slave port
        ICpriCore::CpriPortControl spc(mPortControl) ;

		// get the rates to use
		spc.allowableRates = getAllowableRates() ;

		// save setting
		mPortControl = spc;
    }
    else
    {
        forceFixedLineRate( mFixedLineRate );

    }

    // Program the preferred line rates to the core register
    mCore->setPortParameters(mPortControl);
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::LineRateCapability CpriPortHandler::getAllowableRates()
{
    // if fixed line rate is set, use it
    if (mFixedLineRate != ICpriCore::RateUnknown)
    {
		// Reset to this single rate
		return rateToCapability(mFixedLineRate) ;
    }

	// Reset to only those rates allowed by the hardware
	return mCore->getLineRateCapability() ;
}



//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::updateTopologyData()
{
    // save the topology data in this class
    mCpriPmre = mCore->getTopologyPMRE();
    mCpriLinkId = mCore->getTopologyLinkId();
    mCpriReId = mCore->getTopologyREID();

    if (mCpriPmre == 0)
    {
        mCpriPmre = 1;
    }

    if (mCpriLinkId == 0)
    {
        // can we get the linkId from somewhere else??
        mCpriLinkId = 1;
    }

    if (mCpriReId == 0)
    {
        // can we get the ReId from somewhere else??
        mCpriReId = 1;
    }

    logDebugVerbose("%s:  Port %d TOPOLOGY_DATA: PMRE=%d, LINKID=%d REID=%d", __func__,
            mPort, mCpriPmre, mCpriLinkId, mCpriReId);
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::CpriPortStatus CpriPortHandler::getCpriPortStatus()
{
    ICpriCore::CpriPortStatus portStatus = mCore->getPortStatus();

    if (isSlave())
    {
        // Test whether h/w enabled - should only be disabled for factory test and while in INITIAL state
        portStatus.logicallyEnabled = mCore->isCoreOutOfReset();
    }
    else if (isMaster())
    {
        portStatus.logicallyEnabled = mPortLogicallyEnabled;
    }

    return portStatus;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::isLineRateSupported(ICpriCore::LineRate lineRate)
{
	// Forward
	return mCore->isLineRateSupported(lineRate) ;
}

//-------------------------------------------------------------------------------------------------------------
const char* CpriPortHandler::getCoreModeString(std::shared_ptr<ICpriCore> rCore)
{
    if (rCore->isMaster())
        return "Master";

    if (rCore->isSlave())
        return "Slave";

    return "Inactive";
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriPortHandler::getPreferredProtocolValue()
{
    return CpriPortHandler::PREFERRED_PROTOCOL_VALUE;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriPortHandler::getPreferredEthPointerValue()
{
    return CpriPortHandler::PREFERRED_ETHERNET_POINTER_VALUE;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriPortHandler::getPreferredHdlcRateValue()
{
    return CpriPortHandler::PREFERRED_HDLC_RATE_VALUE;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::isFibreConnected(
        ICpriCore::CpriPortStatus portStatus)
{
    // Return true when fibre connected
    return !portStatus.sfpLos;
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::areClocksLocked(
        ICpriCore::CpriPortStatus portStatus)
{
    // Return true when all MGT PLLs are locked
    return (portStatus.mgtPllLock && portStatus.mgtTxClockLock
            && portStatus.mgtRxClockLock);
}

//-------------------------------------------------------------------------------------------------------------
bool CpriPortHandler::hasPortStatusChanged(
        ICpriCore::CpriPortStatus portStatus)
{
    // Return true when any element of the port status has changed

    return (mCurrentPortStatus.logicallyEnabled != portStatus.logicallyEnabled
            || mCurrentPortStatus.active != portStatus.active
            || mCurrentPortStatus.lineRate != portStatus.lineRate
            || mCurrentPortStatus.ethernetMinCMBandwidth
                    != portStatus.ethernetMinCMBandwidth
            || mCurrentPortStatus.ethernetMaxCMBandwidth
                    != portStatus.ethernetMaxCMBandwidth
            || mCurrentPortStatus.protocolVersion != portStatus.protocolVersion
            || mCurrentPortStatus.remoteSapDefect != portStatus.remoteSapDefect
            || mCurrentPortStatus.remoteLossOfFrame != portStatus.remoteLossOfFrame
            || mCurrentPortStatus.remoteLossOfSync != portStatus.remoteLossOfSync
            || mCurrentPortStatus.mgtPllLock != portStatus.mgtPllLock
            || mCurrentPortStatus.mgtTxClockLock != portStatus.mgtTxClockLock
            || mCurrentPortStatus.mgtRxClockLock != portStatus.mgtRxClockLock
            || mCurrentPortStatus.sfpLos != portStatus.sfpLos
			|| mCurrentPortStatus.remoteAlarmInd != portStatus.remoteAlarmInd
            || mCurrentPortStatus.localLossOfFrame != portStatus.localLossOfFrame
            || mCurrentPortStatus.localLossOfSync  != portStatus.localLossOfSync);
}

//-------------------------------------------------------------------------------------------------------------
// Converts the state into a string.
const char* CpriPortHandler::getStateString(
        ICpriPortHandler::CpriSMStates smState) const
{
    switch (smState)
    {
    case ICpriPortHandler::STATE_INACTIVE:
        return "STATE_INACTIVE";
        break;
    case ICpriPortHandler::STATE_INITIAL:
        return "STATE_INIT";
        break;
    case ICpriPortHandler::STATE_BAD:
        return "STATE_BAD";
        break;
    case ICpriPortHandler::STATE_TRANSITION:
        return "STATE_TRANS";
        break;
    case ICpriPortHandler::STATE_GOOD:
        return "STATE_GOOD";
        break;
    }

    return "UNKNOWN STATE";  // should never be reached
}


//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::updateCpriFaults(void)
{
	updateLossOfSignalMajorFault();
	updateLossOfFrameMajorFault();
	updateServiceAccessPointDefectIndMajorFault();
	updateRemoteAlarmIndicationMajorFault();
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::updateLossOfSignalMajorFault( void )
{
    /* *** Update faults, if any exist.*** */
    if( true == mCurrentPortStatus.sfpLos ||
        true == mCurrentPortStatus.localLossOfSync )
    {
    	mLossOfSignalOwner->set();
    }
    else
    {
    	mLossOfSignalOwner->clear();
    }
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::updateLossOfFrameMajorFault( void )
{
	/* *** Update faults, if any exist.*** */
    if( true == mCurrentPortStatus.localLossOfFrame )
    {
    	mLossOfFrameOwner->set();
    }
    else
    {
    	mLossOfFrameOwner->clear();
    }
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::updateServiceAccessPointDefectIndMajorFault( void )
{
    /* *** Update faults, if any exist.*** */
    if( true == mCurrentPortStatus.remoteSapDefect )
    {
    	mServiceAccessPointDefectIndOwner->set();
    }
    else
    {
    	mServiceAccessPointDefectIndOwner->clear();
    }
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::updateRemoteAlarmIndicationMajorFault( void )
{
    /* *** Update faults, if any exist.*** */
    if( true == mCurrentPortStatus.remoteAlarmInd )
    {
    	mRemoteAlarmIndicationOwner->set();
    }
    else
    {
    	mRemoteAlarmIndicationOwner->clear();
    }
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::LineRateCapability CpriPortHandler::rateToCapability(ICpriCore::LineRate lineRate) const
{
	ICpriCore::LineRateCapability capability ;

	switch (lineRate)
	{
	case ICpriCore::Rate614_4:
		capability.capableOfRate614_4 = true ;
		return capability ;

	case ICpriCore::Rate1228_8:
		capability.capableOfRate1228_8 = true ;
		return capability ;

	case ICpriCore::Rate2457_6:
		capability.capableOfRate2457_6 = true ;
		return capability ;

	case ICpriCore::Rate3072_0:
		capability.capableOfRate3072_0 = true ;
		return capability ;

	case ICpriCore::Rate4915_2:
		capability.capableOfRate4915_2 = true ;
		return capability ;

	case ICpriCore::Rate6144_0:
		capability.capableOfRate6144_0 = true ;
		return capability ;

	case ICpriCore::Rate9830_4:
		capability.capableOfRate9830_4 = true ;
		return capability ;

	case ICpriCore::Rate10137_6:
		capability.capableOfRate10137_6 = true ;
		return capability ;

	case ICpriCore::RateUnknown:
	default:
		return ICpriCore::LineRateCapability() ;
	}

	return capability ;
}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------
CpriPortHandler::LossOfSignalOwner::LossOfSignalOwner(UINT32 path) :
	FaultOwner("CpriPortHandler"),
	mFault( ICommonRadioFaults::getInstance()->getCpriLossOfSignalFaultMajor(path) )
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> CpriPortHandler::LossOfSignalOwner::getFault()
{
	return mFault;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::LossOfSignalOwner::set()
{
	mFault->setStatus( true );
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::LossOfSignalOwner::clear()
{
	mFault->setStatus( false );
}

//-------------------------------------------------------------------------------------------------------------
CpriPortHandler::LossOfFrameOwner::LossOfFrameOwner(UINT32 path) :
	FaultOwner("CpriPortHandler"),
	mFault( ICommonRadioFaults::getInstance()->getCpriLossOfFrameFaultMajor(path) )
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> CpriPortHandler::LossOfFrameOwner::getFault()
{
	return mFault;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::LossOfFrameOwner::set()
{
	mFault->setStatus( true );
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::LossOfFrameOwner::clear()
{
	mFault->setStatus( false );
}

//-------------------------------------------------------------------------------------------------------------
CpriPortHandler::ServiceAccessPointDefectIndOwner::ServiceAccessPointDefectIndOwner(UINT32 path)  :
	FaultOwner("CpriPortHandler"),
	mFault( ICommonRadioFaults::getInstance()->getCpriSapDefectIndFaultMajor(path) )
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> CpriPortHandler::ServiceAccessPointDefectIndOwner::getFault()
{
	return mFault;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::ServiceAccessPointDefectIndOwner::set()
{
	mFault->setStatus( true );
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::ServiceAccessPointDefectIndOwner::clear()
{
	mFault->setStatus( false );
}

//-------------------------------------------------------------------------------------------------------------
CpriPortHandler::RemoteAlarmIndicationOwner::RemoteAlarmIndicationOwner(UINT32 path) :
	FaultOwner("CpriPortHandler"),
	mFault( ICommonRadioFaults::getInstance()->getCpriRemoteAlarmIndicationFaultMajor(path) )
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> CpriPortHandler::RemoteAlarmIndicationOwner::getFault()
{
	return mFault;
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::RemoteAlarmIndicationOwner::set()
{
	mFault->setStatus( true );
}

//-------------------------------------------------------------------------------------------------------------
void CpriPortHandler::RemoteAlarmIndicationOwner::clear()
{
	mFault->setStatus( false );
}
