/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxPowerControl.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Task.h"

#include "TxPowerControl.h"
#include "IRadio.h"
#include "ITxPort.h"

#include "ICarrierServer.h"
#include "IFpgaMgr.h"

#include "FaultOwner.h"
#include <sstream>
#include <string>

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxPowerControl::TxPowerControl(int portIndex):
        Loggable("Pcl"+std::to_string(portIndex), "TX"),
        mOlState( TxPclOl::SETOL ),
        mState( TxPclState::INIT),
        mPrevState( TxPclState::INIT),
        mPort(portIndex),
        mPABandBackoff(61.0f),
        mBackoff(6.0f),
        mTargetPower(0.0),
        mGainError(0.0),
        mOpenLoopTarget(0.0),
        mRFOutputPower(0.0),
        mLastRFOutputPower(0.0),
        mMinMeasRfPower(10.0),
        mDigitalInputPower(-45.0),
        mMinDigitalPower(-45.0),
        mAttenuation(0.0),
        mPrevAttenuation(0.0),
        mMaxInputPower(-19.5),      // maximum expected digital input power reference
        mRampCount(0),
        mGainErrorCount(0),
        mRampAvgCount(0),
        mTrackAvgCount(0),
        mSlowTrackCount(0),
        mSlowTrack(false),
        mWaitDPCount(0),
        mWaitGoodRfCount(0),
        mDpdRunning(false),
        //TODO update dpd interface mDpdInfo(),
        mRampFailCount(RAMP_FAIL_COUNT),
        mRampGainErrorLimit(RAMP_MODE_GAIN_ERROR_LIMIT),
        mInfiniteWaitDP(false),
        mGainErrorLimitCount( GAIN_ERROR_LIMIT ),
		mDpdTrackOn(false),
        mFpga( IFpgaMgr::getIFpgaAntennaRegs() ),
        mRadio( IRadioFactory::getInterface()),
		mDpdControl(IDpdControl::getInterface())
{
    std::vector<std::shared_ptr<ITxPort>> txPorts = ITxPortFactory::getPorts();
    mTxPort = txPorts[mPort];

    mCarrierMgr = ICarrierServer::getInstance();

    // Register as an observer of the carrier manager TX ON and TX OFF events.
    std::dynamic_pointer_cast<Subject<ITxOn, const ITxEventData&>>(mCarrierMgr)->attach(*this);
    std::dynamic_pointer_cast<Subject<ITxOff, const ITxEventData& >>(mCarrierMgr)->attach(*this);

    // Register as an observer with this application's DpdService for DPD info events

    auto DpdMonitorFunc = [this](const std::map<std::string, DataVariant>& attributeValues){

    	eventInfo("PCL %02d: DPD EV_TRACK received", mPort);
    	// Look for attribute onOff=ON for the Tx port

    	// Check if the Tx port is what we are looking for
    	if (attributeValues.find("tx") != attributeValues.end())
    	{
    		std::string port = attributeValues.at("tx").toString();

    		// If this is the correct port, then check if onOff is set to ON
    		if (std::stoul(port) == (unsigned)(this->mPort) &&
    			attributeValues.find("onoff") != attributeValues.end())
			{
				DataVariant dv = attributeValues.at("onoff");
				if (dv.toString() == "ON")
				{
					this->mDpdTrackOn = true;
				}
				else
				{
					this->mDpdTrackOn = false;
				}
			}
    	}

    	eventInfo("PCL %02d: DPD converge to track is %s", mPort, (this->mDpdTrackOn == true ? "ON" : "OFF"));
    };

    mDpdControl->addEventMonitor("ConvergeToTrack_" + std::to_string(mPort), mPort, "EV_TRACK", DpdMonitorFunc);


    // get interface to all supported radio fault
    mFaults = ICommonRadioFaults::getInstance();

    mOverPowerOwner = std::shared_ptr<OverPowerOwner>(new OverPowerOwner( mPort )) ;
    mConvergenceOwner = std::shared_ptr<ConvergenceOwner>( new  ConvergenceOwner( mPort )) ;
    mPowerMeasurementFaultOwner = std::shared_ptr<PowerMeasurementFaultOwner>( new  PowerMeasurementFaultOwner( mPort )) ;

    mOverPowerOwner->getFault()->addOwner( mOverPowerOwner );
    mConvergenceOwner->getFault()->addOwner( mConvergenceOwner );
    mPowerMeasurementFaultOwner->getFault()->addOwner( mPowerMeasurementFaultOwner );

    mOverPowerOwner->clear();
    mConvergenceOwner->clear();
    mPowerMeasurementFaultOwner->clear();

    mAvgDigitalInputPower.setSize( RAMP_AVG );
    mAvgRFOutputPower.setSize( RAMP_AVG );

}



//-------------------------------------------------------------------------------------------------------------
TxPowerControl::~TxPowerControl()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string TxPowerControl::getStateStr()
{
    return getStateStr(mState);
}

std::string TxPowerControl::getStateStr(TxPclState pState)
{
    std::string stateStr = "UNKNOWN";
    switch( pState )
    {
    case TxPclState::INIT:
        stateStr = "INITIALISE";
        break;
    case TxPclState::OFF:
        stateStr = "OFF";
        break;
    case TxPclState::OPENLOOP:
        stateStr = "OPENLOOP";
        break;
    case TxPclState::RAMP:
        stateStr = "RAMP";
        break;
    case TxPclState::CONVERGE:
        stateStr = "CONVERGE";
        break;
    case TxPclState::TRACK:
        stateStr = "TRACK";
        break;
    case TxPclState::MANUAL:
        stateStr = "MANUAL";
        break;
    case TxPclState::TESTING:
        stateStr = "TESTING";
        break;
    default:
    	stateStr = "UNKNOWN";
        break;
    }
    return stateStr;
}

std::string TxPowerControl::getEventStr(TxPclEvent pEvent)
{
    std::string eventStr = "UNKNOWN";
    switch( pEvent )
    {
    case TxPclEvent::TX_OFF:
    	eventStr = "TX_OFF";
        break;
    case TxPclEvent::TX_ON:
    	eventStr = "TX_ON";
        break;
    case TxPclEvent::MANUAL:
    	eventStr = "MANUAL";
        break;
    case TxPclEvent::TESTING:
    	eventStr = "TESTING";
        break;
    case TxPclEvent::AUTO:
    	eventStr = "AUTO";
        break;
    case TxPclEvent::TIMER_TICK:
    	eventStr = "TIMER_TICK";
        break;
    default:
    	eventStr = "UNKNOWN";
        break;
    }
    return eventStr;
}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::stateMachine(TxPclEvent txPclEvent)
{
    Mutex::Lock lock( mMutex );     // lock the state machine to prevent TxService update fighting with carrier config callbacks.

    TxPclState newState = mState;
    switch( mState )
    {
    case TxPclState::INIT:                          // initial state to set things up
        newState = initialise( txPclEvent);
        break;
    case TxPclState::OFF:                           // TX off state waiting for a TX on request
        newState = txOff( txPclEvent );
        break;
    case TxPclState::OPENLOOP:                      // open loop state state waiting for a TX on request
        newState = openLoop( txPclEvent );
        break;
    case TxPclState::RAMP:                          // intitial power set and DPD OK so ramp up the power
        newState = ramp( txPclEvent );
        break;
    case TxPclState::CONVERGE:                      // ramped to power so wait for DPD to converge
        newState = converge( txPclEvent );
        break;
    case TxPclState::TRACK:                         // in narrow powerband, so track with small power adjustments
        newState = track( txPclEvent );
        break;
    case TxPclState::MANUAL:                        // left in previous state until AUTO event received
        newState = manual( txPclEvent );
        break;
    case TxPclState::TESTING:                       // does nothing
        newState = testing( txPclEvent );
        break;
    }
    if( newState != mState )            // we have changed state as a result of processing the event
    {
        mPrevState = mState;            // remember the previous state
        mState = newState;              // where we go to next
    }
}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::show(std::ostream& os)
{
	ILoggable::logStream(os, "*** TxPowerControl Show - port %d ***\n", mPort);
	ILoggable::logStream(os, "mOlState = %d, mState = %s, mPrevState = %s", (int)mOlState, getStateStr(mState).c_str(), getStateStr(mPrevState).c_str());
	ILoggable::logStream(os, "mPABandBackoff   = %f, mBackoff           = %f", mPABandBackoff.get(), mBackoff.get());
	ILoggable::logStream(os, "mTargetPower     = %f, mOpenLoopTarget    = %f", mTargetPower.get(), mOpenLoopTarget.get());
	ILoggable::logStream(os, "mPADesignGain    = %f, mGainError         = %f", mPADesignGain.get(), mGainError.get());
	ILoggable::logStream(os, "mRFOutputPower   = %f, mLastRFOutputPower = %f", mRFOutputPower.get(), mLastRFOutputPower.get());
	ILoggable::logStream(os, "mMinMeasRfPower  = %f, mDigitalInputPower = %f", mMinMeasRfPower.get(), mDigitalInputPower.get());
	ILoggable::logStream(os, "mMinDigitalPower = %f, mMaxInputPower     = %f", mMinDigitalPower.get(), mMaxInputPower.get());
	ILoggable::logStream(os, "mAttenuation     = %f, mPrevAttenuation   = %f", mAttenuation.get(), mPrevAttenuation.get());
	ILoggable::logStream(os, "IFAttenuation    = %f, RFAttenuation      = %f", mTxPort->getIFAttenuation().get(), mTxPort->getRFAttenuation().get());
	ILoggable::logStream(os, "mRefInput        = %f", mRefInput.get());
	ILoggable::logStream(os, "mRampCount       = %d, mGainErrorCount    = %d", mRampCount, mGainErrorCount);
	ILoggable::logStream(os, "mRampAvgCount    = %d, mTrackAvgCount     = %d", mRampAvgCount, mTrackAvgCount);
	ILoggable::logStream(os, "mSlowTrackCount  = %d, mSlowTrack         = %s", mSlowTrackCount, mSlowTrack ? "Yes" : "No");
	ILoggable::logStream(os, "mWaitDPCount     = %d, mWaitGoodRfCount   = %d", mWaitDPCount, mWaitGoodRfCount);
	ILoggable::logStream(os, "mDpdRunning      = %s", mDpdRunning ? "Yes" : "No");
	ILoggable::logStream(os, "mRampFailCount   = %d, mRampGainErrorLimit = %f", mRampFailCount, mRampGainErrorLimit);
	ILoggable::logStream(os, "\n*** TxPowerControl Show - port %d  - END ***", mPort);
}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::showPcl()
{
    std::stringstream ss;
    ss << std::endl;
    TxPowerControl::show(ss);
    eventInfo("%s", ss.str().c_str());
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxPclState TxPowerControl::initialise(TxPclEvent event)
{
    TxPclState changeState = mState;

    switch( event )
    {
    case TxPclEvent::MANUAL:
        changeState = TxPclState::MANUAL;
        break;

    case TxPclEvent::TX_ON:
    case TxPclEvent::TX_OFF:                    // no action for event in this state
    case TxPclEvent::AUTO:
    case TxPclEvent::TIMER_TICK:
    case TxPclEvent::TESTING:
        changeState = TxPclState::OFF;
        break;
    }
    return changeState;
}

//-------------------------------------------------------------------------------------------------------------
TxPclState TxPowerControl::txOff(TxPclEvent event)
{
    TxPclState changeState = mState;

    switch( event )
    {
    case TxPclEvent::TX_ON:

        mWaitDPCount = 0;
        mWaitGoodRfCount = 0;
        changeState = TxPclState::OPENLOOP;     // we are off and running so start ramping

        mOlState = TxPclOl::SETOL;              // set the initial open loop state machine condition
        // as we have received a carrier configuration request, we must reset our faults (if any)

        mOverPowerOwner->clear();
        mConvergenceOwner->clear();
        mPowerMeasurementFaultOwner->clear();

        eventInfo("PCL %02d: Going from OFF to OPENLOOP",mPort);
        break;
    case TxPclEvent::MANUAL:
        changeState = TxPclState::MANUAL;
        eventInfo("PCL %02d: Going from OFF to MANUAL",mPort);
        break;
    case TxPclEvent::TX_OFF:                // no action for event in this state
    case TxPclEvent::AUTO:
    case TxPclEvent::TESTING:
        break;
    case TxPclEvent::TIMER_TICK:
    	// NOTE: This should now never be active - the TXOFF event should automatically stop DPD
        if( mDpdRunning )
        {
            // no matter what the event turn off everything and go back to the TX OFF state
        	mDpdControl->stopDpd( mPort );  // tell DPD to stop

            mDpdRunning = false;
        }
        break;
    }
    return changeState;
}


//-------------------------------------------------------------------------------------------------------------
TxPclState TxPowerControl::openLoop(TxPclEvent event)
{
    TxPclState changeState = mState;

    switch( event )
    {
    case TxPclEvent::MANUAL:
        changeState = TxPclState::MANUAL;
        break;
    case TxPclEvent::TX_OFF:
        shutdown();
        changeState = TxPclState::OFF;
        eventInfo("PCL %02d: Recvd TX_OFF going from OPENLOOP to OFF",mPort);
        break;
    case TxPclEvent::TX_ON:
    case TxPclEvent::AUTO:
    case TxPclEvent::TESTING:
        break;
    case TxPclEvent::TIMER_TICK:

        switch ( mOlState )
        {
        case TxPclOl::SETOL:
            // for systems calibrated to the output of the amplifier the user can manually set
            // an external filter loss, to achieve the correct power at the antenna. So the
            // filter loss is added to the combined target here, although it's default value is 0.
            mTargetPower = mCarrierMgr->getTxPower( mPort ) + mTxPort->getExtFilterLoss();
            if( mTargetPower >= mTxPort->getMinPower() )
            {
                mTxPort->setTargetPower(mTargetPower);  // which in turn tells the SRx port to optimise the SRx attenuation

                mTxPort->setTxOn();

                // Check that the retrieval of the power is ok before using the value.
                if( ReturnType::RT_OK == mTxPort->getFwdPower( mRFOutputPower, mDigitalInputPower ) )
                {
					mLastRFOutputPower = mRFOutputPower;
					mRefInput = mMaxInputPower - mDigitalInputPower;

					if( mTxPort->hasPA() )
					{
						mPADesignGain = mTxPort->getPA()->getDesignGain();
						// We use the worse case maximum design gain for our initial open loop set point
						// and then back it off a little more for safety
						mPABandBackoff = mTxPort->getPA()->getMaxDesignGain() + mBackoff;
					}

					// Use the target power and the worse case PA design gain to set the radio output power
					// set a reasonable starting point for the radio output power
					mOpenLoopTarget = mTargetPower - mPABandBackoff;

					// set the output, keeping the VVA at it's optimal
					// and using the IF DSA to give most of the attenuation
					mTxPort->setRadioOutputPower( mOpenLoopTarget );

					// read back the combined attenuation
					mAttenuation = mTxPort->getAttenuation();


					eventInfo("PCL %02d: OPENLOOP target power = %f, open loop target = %f, TX Path attenuation now %f ",mPort,
							mTargetPower.get(), mOpenLoopTarget.get(), mAttenuation.get() );

					mOlState = TxPclOl::WAIT_DP;
                }
                else
                {
                	// If the power value wasn't ok, we'll come back around again on the next timer tick.
                	eventInfo("PCL %02d: Bad getFwdPower() reading", mPort);
                }
            }
            else
            {
                changeState = TxPclState::OFF;
                eventInfo("PCL %02d: Bad target power %f too low, going from OPENLOOP to OFF",mPort, mTargetPower.get() );
            }
            break;
        case TxPclOl::WAIT_DP:
        {
        	// Check that the retrieval of the power is ok before using the value.
        	if( ReturnType::RT_OK == mTxPort->getFwdPower( mRFOutputPower, mDigitalInputPower ) )
        	{
				eventInfo("PCL %02d: OPENLOOP WAIT_DP rf power = %f, dig inout power = %f ",mPort,
						mRFOutputPower.get(), mDigitalInputPower.get() );

				bool lpa = mFpga->read_lowPowerAlarm( mPort ) != 0;
				bool hpa = mFpga->read_highPowerAlarm( mPort ) != 0;

				if( true == lpa )
				{
					eventInfo("PCL %02d: OPENLOOP WAIT_DP - FPGA Low Power Alarm ", mPort);

					mFpga->write_lowPowerAlarm(mPort, 1 );      // clear the low power alarm
				}

				if( true == hpa )
				{
					eventInfo("PCL %02d: OPENLOOP WAIT_DP - FPGA High Power Alarm ", mPort);

					mFpga->write_highPowerAlarm(mPort, 1 );      // clear the high power alarm
				}

				if( mDigitalInputPower > mMinDigitalPower )
				{
					mOlState = TxPclOl::CHECK_PM;
				}
				else
				{
					if( (false == lpa) && (false == hpa) )
					{
						// wait indefinitely if flag is set
						if (!mInfiniteWaitDP)
						{
							if( ++mWaitDPCount > 5 )
							{
								shutdown();
								mPowerMeasurementFaultOwner->set();
								mOlState = TxPclOl::SETOL;
								changeState = TxPclState::OFF;
								eventInfo("PCL %02d: Now digital power last reading %f too low, going from OPENLOOP to OFF",mPort, mDigitalInputPower.get() );
							}
						}
					}
					else
					{
						eventInfo("PCL %02d: OPENLOOP WAIT_DP - Holding off Wait DP Count ", mPort);
					}
				}
        	}
            else
            {
            	// If the power value wasn't ok, we'll come back around again on the next timer tick.
            	eventInfo("PCL %02d: Bad getFwdPower() reading", mPort);
            }
        }
        break;

        case TxPclOl::CHECK_PM:

        	// Check that the retrieval of the power is ok before using the value.
        	if( ReturnType::RT_OK == mTxPort->getFwdPower( mRFOutputPower, mDigitalInputPower ) )
        	{
				eventInfo("PCL %02d: OPENLOOP CECK rf power = %f, dig inout power = %f ",mPort,
						mRFOutputPower.get(), mDigitalInputPower.get() );


				if( mRFOutputPower >=  mMinMeasRfPower )
				{
					mAvgDigitalInputPower.setSize(RAMP_AVG);
					mAvgRFOutputPower.setSize(RAMP_AVG);
					mRampAvgCount = 0;
					mRampCount = 0;                     // initialise the ramp count for fail to ramp to power error
					mRampFailCount = RAMP_FAIL_COUNT ;
					mRampGainErrorLimit = RAMP_MODE_GAIN_ERROR_LIMIT;

					changeState = TxPclState::RAMP;     // we are off and running so start ramping
					eventInfo("PCL %02d: Power %f good, Going from OPENLOOP to RAMP",mPort,mRFOutputPower.get());
				}
				else
				{
					if( ++mWaitGoodRfCount > 5 )
					{
						shutdown();
						mPowerMeasurementFaultOwner->set();
						changeState = TxPclState::OFF;
						eventInfo("PCL %02d: Bad SRX power reading %f too low, going from OPENLOOP to OFF",mPort, mRFOutputPower.get() );
					}
				}
        	}
            else
            {
            	// If the power value wasn't ok, we'll come back around again on the next timer tick.
            	eventInfo("PCL %02d: Bad getFwdPower() reading", mPort);
            }
        }
        break;
    }
    return changeState;
}


//-------------------------------------------------------------------------------------------------------------
TxPclState TxPowerControl::ramp(TxPclEvent event)
{
    TxPclState changeState = mState;
    TxPclRamp status;

    switch( event )
    {
    case TxPclEvent::TX_OFF:
        shutdown();
        changeState = TxPclState::OFF;
        eventInfo("PCL %02d: Recvd TX_OFF going from RAMP to OFF",mPort);
        break;
    case TxPclEvent::TIMER_TICK:

        // update the gain error limit as necessary - uses previously measured values
        if (mDigitalInputPower.get() >= RAMP_MODE_LOWPOWER_THRESHOLD)
        {
        	// Higher power so ensure we use the smaller limit
        	mRampGainErrorLimit = RAMP_MODE_GAIN_ERROR_LIMIT;
        }
        else
        {
        	// lower power so widen the threshold
        	mRampGainErrorLimit = RAMP_MODE_LOWPOWER_GAIN_ERROR_LIMIT;
        }

    	// do ramp
        status = rampToPower();

        // check status
        if( status  ==  TxPclRamp::COMPLETE )               // out gain error is less than 0.5 db so switch to track mode
        {
            eventInfo("RAMP %02d: RAMP COMPLETE try DPD start...", mPort) ;
            if( waitDPD() )                                 // start DPD and wait for result
            {
                eventInfo("PCL %02d: Going from RAMP to CONVERGE",mPort);
                mDpdRunning = true;
                mAvgDigitalInputPower.setSize(RAMP_AVG);
                mAvgRFOutputPower.setSize(RAMP_AVG);
                mSlowTrack = false;
                mSlowTrackCount = 0;
                mRampAvgCount = 0;
                mRampCount = 0;                     // initialise the ramp count for fail to ramp to power error
                mRampFailCount = CONVERGE_RAMP_FAIL_COUNT ;
                mRampGainErrorLimit = RAMP_MODE_GAIN_ERROR_LIMIT;
                changeState = TxPclState::CONVERGE;            // good result from DPD go to converge mode
            }
            else
            {
                eventInfo("PCL %02d: RAMP ERROR, DPD did not start!",mPort);
            }
        }
        else if( status == TxPclRamp::ERROR )
        {

            // raise gain control error and turn off
            shutdown();
            changeState = TxPclState::OFF;
            mConvergenceOwner->set();

            eventInfo("PCL %02d: RAMP ERROR, shutdown and going to OFF",mPort);
        }

        break;
    case TxPclEvent::MANUAL:
        changeState = TxPclState::MANUAL;
        eventInfo("PCL %02d: Going from RAMP to MANUAL",mPort);
        break;
    case TxPclEvent::TX_ON:             // we don't want to do anything with these events
    case TxPclEvent::AUTO:
    case TxPclEvent::TESTING:
        break;
    }
    return changeState;
}

//-------------------------------------------------------------------------------------------------------------
TxPclState TxPowerControl::converge(TxPclEvent event)
{
    TxPclState changeState = mState;
    TxPclRamp status;

    switch( event )
    {
    case TxPclEvent::TX_OFF:
        shutdown();
        changeState = TxPclState::OFF;
        eventInfo("PCL %02d: Recvd TX_OFF going from CONVERGE to OFF",mPort);
        break;
    case TxPclEvent::TIMER_TICK:
        status = rampToPower();
        if( status  ==  TxPclRamp::COMPLETE )               // out gain error is less than 0.5 db so switch to track mode
        {
        	// Gain error is below threshold - is DPD past Q=1 iteration (which causes a big jump in PA
        	// gain that this state is meant to compensate for)?
        	//
        	if (mDpdTrackOn)
        	{
                eventInfo("PCL %02d: Going from CONVERGE to TRACK",mPort);
                mTrackAvgCount = 0;                         // initialise stuff for track mode
                mAvgDigitalInputPower.setSize(TRACK_AVG);
                mAvgRFOutputPower.setSize(TRACK_AVG);
                mSlowTrack = false;
                mSlowTrackCount = 0;
                changeState = TxPclState::TRACK;            // go to track mode
        	}
        	else
        	{
        		eventInfo("PCL %02d: CONVERGE ramp complete - waiting for DPD EV_TRACK", mPort);
        	}
        }
        else if( status == TxPclRamp::ERROR )
        {
            // raise gain control error and turn off
            shutdown();
            changeState = TxPclState::OFF;
            mConvergenceOwner->set();

            eventInfo("PCL %02d: CONVERGE ramp error, shutdown and going to OFF",mPort);
        }

        break;
    case TxPclEvent::MANUAL:
        changeState = TxPclState::MANUAL;
        eventInfo("PCL %02d: Going from CONVERGE to MANUAL",mPort);
        break;
    case TxPclEvent::TX_ON:             // we don't want to do anything with these events
    case TxPclEvent::AUTO:
    case TxPclEvent::TESTING:
        break;
    }
    return changeState;
}

//-------------------------------------------------------------------------------------------------------------
TxPclState TxPowerControl::track(TxPclEvent event)
{
    TxPclState changeState = mState;

    switch( event )
    {
    case TxPclEvent::TX_OFF:
        shutdown();
        changeState = TxPclState::OFF;
        eventInfo("PCL %02d: Going from TRACK to OFF",mPort);
        mTrackAvgCount = 0;
        break;
    case TxPclEvent::MANUAL:
        changeState = TxPclState::MANUAL;
        eventInfo("PCL %02d: Going from TRACK to MANUAL",mPort);
        break;
    case TxPclEvent::TX_ON:
    case TxPclEvent::AUTO:
    case TxPclEvent::TESTING:
        break;
    case TxPclEvent::TIMER_TICK:
        if( !trackMode() )
        {
            // raise gain control error and turn off
            shutdown();
            changeState = TxPclState::OFF;
            mOverPowerOwner->set();
            eventInfo("PCL %02d: TRACK mode failure, shutdown and going to OFF",mPort);
        }
        break;
    }
    return changeState;
}

//-------------------------------------------------------------------------------------------------------------
TxPclState TxPowerControl::manual(TxPclEvent event)
{
    TxPclState changeState = mState;

    if( !mRadio->getCalMode() )
    {
        // update the power readings for this port.
    	// Check that the retrieval of the power is ok before using the value.
    	if( ReturnType::RT_OK == mTxPort->getFwdPower( mRFOutputPower, mDigitalInputPower ) )
    	{
			mRefInput = mMaxInputPower - mDigitalInputPower;
			mGainError = (mTargetPower - mRefInput ) - mRFOutputPower;

			eventInfo("MANUAL %02d: TSSI %f, RSSI %f, GERR %f, ATTN %f ",mPort,
					mDigitalInputPower.get(), mRFOutputPower.get(), mGainError.get(), mAttenuation.get()  );
    	}
        else
        {
        	// If the power value wasn't ok, then all we can do is report it.
        	eventInfo("MANUAL %02d: Bad getFwdPower() reading", mPort);
        }
    }

    switch( event )
    {
    case TxPclEvent::AUTO:              // only an AUTO event will take us out of manual mode
        changeState = mPrevState;
        eventInfo("PCL %02d: Going from MANUAL to previous state",mPort);
        break;
    case TxPclEvent::TX_OFF:            // ignore other events
    case TxPclEvent::TX_ON:
    case TxPclEvent::MANUAL:
    case TxPclEvent::TIMER_TICK:
    case TxPclEvent::TESTING:
        break;
    }

    return changeState;
}

//-------------------------------------------------------------------------------------------------------------
TxPclState TxPowerControl::testing(TxPclEvent event)
{
    return mState;  // this mode does nothing in this common implementation
}

//-------------------------------------------------------------------------------------------------------------
bool TxPowerControl::shutdown()
{
    mTxPort->setTxOff();
    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool TxPowerControl::waitDPD()
{
    eventInfo("PCL %02d: DPD start", mPort);
    mDpdControl->startDpd( mPort, 2000 );
    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool TxPowerControl::setTxOn()
{
    stateMachine( TxPclEvent::TX_ON );
    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool TxPowerControl::setTxOff()
{
    stateMachine( TxPclEvent::TX_OFF );
    return true;
}


//-------------------------------------------------------------------------------------------------------------
bool TxPowerControl::setManual()
{
    stateMachine( TxPclEvent::MANUAL );
    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool TxPowerControl::setTesting()
{
    return false;  // this mode does nothing in this common implementation
}

//-------------------------------------------------------------------------------------------------------------
bool TxPowerControl::setAuto()
{
    stateMachine( TxPclEvent::AUTO );
    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool TxPowerControl::timerUpdate()
{
    stateMachine( TxPclEvent::TIMER_TICK );
    return true;
}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::update(ITxOn& subject,  const ITxEventData& txOnOff)
{
    if( mRadio->getCalMode() || txOnOff.getPort() != (unsigned)mPort )
    	return ;

    // Reset DPD
    eventInfo("PCL %02d: TXON - DPD reset", mPort);
    mDpdControl->resetDpd(mPort) ;
    mDpdTrackOn = false;

    // send TX ON event
    setTxOn();

}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::update(ITxOff& subject,  const ITxEventData& txOnOff)
{
    if( mRadio->getCalMode() || txOnOff.getPort() != (unsigned)mPort )
    	return ;

    // Stop DPD
    eventInfo("PCL %02d: TXOFF - DPD stop", mPort);
    if (mDpdControl->stopDpd(mPort))
    {
    	mDpdRunning = false ;
    	mDpdTrackOn = false;
    }

    // send TX OFF event
    setTxOff();
}

//-------------------------------------------------------------------------------------------------------------

const float TxPowerControl::RAMP_MODE_ERROR_FACTOR = 0.5f;
const float TxPowerControl::RAMP_MODE_GAIN_ERROR_LIMIT = 0.35f;
const float TxPowerControl::RAMP_MODE_LOWPOWER_GAIN_ERROR_LIMIT = 1.00f;
const float TxPowerControl::RAMP_MODE_LOWPOWER_THRESHOLD = -22.5f; // Any TSSI below this value is treated as "low power"

TxPclRamp TxPowerControl::rampToPower()
{
    // update the power readings for this port.
	// Check that the retrieval of the power is ok before using the value.
	if( ReturnType::RT_OK == mTxPort->getFwdPower( mRFOutputPower, mDigitalInputPower ) )
	{
		mAvgRFOutputPower.add( mRFOutputPower.getWatts() );
		mAvgDigitalInputPower.add( mDigitalInputPower.getWatts() );

		if( ++mRampAvgCount == RAMP_AVG)
		{
			mRampAvgCount = 0;
			mDigitalInputPower.set( mAvgDigitalInputPower.get(), Power::W);
			mRFOutputPower.set( mAvgRFOutputPower.get(), Power::W );

			// check our measurements are above expected minimum power measurement levels
			if( mDigitalInputPower > mMinDigitalPower &&
					mRFOutputPower > mMinMeasRfPower )
			{
				mRefInput = mMaxInputPower - mDigitalInputPower;
				mGainError = (mTargetPower - mRefInput ) - mRFOutputPower;

				eventInfo("%s %02d: AVG TSSI %f, AVG RSSI %f, GERR %f, ATTN %f : Gain error limit %f ",
					getStateStr().c_str(), mPort,
					mDigitalInputPower.get(), mRFOutputPower.get(), mGainError.get(), mAttenuation.get(),
					mRampGainErrorLimit
				);

				if( fabs(mGainError.get())  < mRampGainErrorLimit )
				{
					eventInfo("%s %02d: RAMP COMPLETE, abs GERR %f < %f ",
							getStateStr().c_str(), mPort, mGainError.get(), mRampGainErrorLimit );
					return TxPclRamp::COMPLETE;
				}
				else
				{
					bool lpa = mFpga->read_lowPowerAlarm( mPort ) != 0;
					bool hpa = mFpga->read_highPowerAlarm( mPort ) != 0;

					if(  !lpa &&  !hpa  &&
							mRFOutputPower != mLastRFOutputPower )  // stop us winding the attenuator down if power hasn't changed.
					{
						mLastRFOutputPower = mRFOutputPower;
						mAttenuation -= ( mGainError.get() * RAMP_MODE_ERROR_FACTOR );
						if( mAttenuation > 0.0 )    // check attenuation is semi-reasonable
						{
							mTxPort->setAttenuation( mAttenuation );
							mAttenuation = mTxPort->getAttenuation();

							if( mAttenuation == mPrevAttenuation )
							{
								eventInfo("%s %02d: Error attenuation not changed", getStateStr().c_str(), mPort);
								return TxPclRamp::ERROR;
							}
							mPrevAttenuation = mAttenuation;
						}
					}
					else
					{
						if( lpa )
							mFpga->write_lowPowerAlarm(mPort, 1 );      // clear the low power alarm
						if( hpa )
							mFpga->write_highPowerAlarm(mPort, 1);      // clear the hi power alarm
						if( lpa || hpa )
							--mRampCount;   // we can't ramp when alarm raised so don't timeout the ramp mode.
					}
				}
			}

			eventInfo("%s %02d: RAMP COUNT %d / %d ",
					getStateStr().c_str(), mPort, (mRampCount+1), mRampFailCount );

			if( ++mRampCount > mRampFailCount )
			{
				eventInfo("PCL %02d: In %s mode, ramp count exceeded, failed to converge in time", mPort, getStateStr().c_str() );
				return TxPclRamp::ERROR;
			}
		}
	}
    return TxPclRamp::RAMPING;
}

//-------------------------------------------------------------------------------------------------------------
const float TxPowerControl::TRACK_MODE_GAIN_ERROR = 1.5f; //1.0f;   // increased from 0.75f to cope with gain errors introduced by DPD
const float TxPowerControl::TRACK_MODE_SLOW_UPDATE_LIMIT = 0.25f;
const float TxPowerControl::TRACK_MODE_LOW_DIG_POWER_LIMIT = -32.0f; // Changed from 30.0 to help with LTE 20 dynamic range
const float TxPowerControl::TRACK_MODE_ERROR_FACTOR = 0.1f;
const float TxPowerControl::TRACK_MODE_RF_ATTEN_LOW_LIMIT = 1.0f;
const float TxPowerControl::TRACK_MODE_RF_ATTEN_HIGH_LIMIT = 15.0f;

bool TxPowerControl::trackMode()
{
    //
    // Are we in slow track mode, if so we will slow down our readings and updates.
    // This will reduce interference with DPD
    //
    if( mSlowTrack && ++mSlowTrackCount <= SLOW_TRACK )
    {
        return true;
    }
    mSlowTrackCount = 0;

    // update the power readings for this port.
	// Check that the retrieval of the power is ok before using the value.
	if( ReturnType::RT_OK == mTxPort->getFwdPower( mRFOutputPower, mDigitalInputPower ) )
	{
		mAvgRFOutputPower.add( mRFOutputPower.getWatts() );
		mAvgDigitalInputPower.add( mDigitalInputPower.getWatts() );

		if( ++mTrackAvgCount == TRACK_AVG)
		{
			mTrackAvgCount = 0;
			mDigitalInputPower.set( mAvgDigitalInputPower.get(), Power::W);
			mRFOutputPower.set( mAvgRFOutputPower.get(), Power::W );

			if( mDigitalInputPower > mMinDigitalPower &&  mRFOutputPower > mMinMeasRfPower )
			{
				mRefInput = mMaxInputPower - mDigitalInputPower;
				mGainError = (mTargetPower - mRefInput ) - mRFOutputPower;

				eventInfo("TRACK %02d: AVG TSSI %f, AVG RSSI %f, gives GERR %f ",mPort,
						mDigitalInputPower.get(), mRFOutputPower.get(), mGainError.get() );

				float absoluteGainError = fabs( mGainError.get() );
				/**
				 * Because the digital measurement resolution is so poor if the digital input power
				 * leave the attenuation where it is, and continue as normal.
				 *
				 */
				if( mDigitalInputPower < TRACK_MODE_LOW_DIG_POWER_LIMIT)
				{
					return true;
				}


				//
				// Is our gain error small enough to slow down the track mode updates?
				//
				if(absoluteGainError  < TRACK_MODE_SLOW_UPDATE_LIMIT
						&& mSlowTrack == false)
				{
					mSlowTrackCount = 0;
					mSlowTrack = true;
                    mGainErrorLimitCount = (GAIN_ERROR_LIMIT/SLOW_TRACK);
				}
				else
				{
			        mGainErrorLimitCount = GAIN_ERROR_LIMIT;

					mSlowTrack = false;
				}

				if( absoluteGainError  < TRACK_MODE_GAIN_ERROR )
				{
					mGainErrorCount = 0;
					Power attenuation = mTxPort->getAttenuation();
					attenuation -= ( mGainError.get() * TRACK_MODE_ERROR_FACTOR );    // we need to make really small changes in track mode.
					mTxPort->setAttenuation( attenuation );
					mAttenuation = mTxPort->getAttenuation();
					eventInfo("TRACK %02d: Set RF - ATTN %f, total ATTN %f ",mPort,
							attenuation.get(), mAttenuation.get() );


					// if we have reached the limits of the RF attenuator in track mode we must have a hardware error
					// so return  false to indicate so
					if( attenuation.get() <  TRACK_MODE_RF_ATTEN_LOW_LIMIT || attenuation.get() > TRACK_MODE_RF_ATTEN_HIGH_LIMIT )
					{
						eventInfo("PCL %02d: TRACK mode failure, RF attenuation going out of bounds",mPort);
						return false;
					}
					mPrevAttenuation = mAttenuation;
					return true;
				}

				eventInfo("PCL %02d: TRACK mode unexpected very large gain error, assume bad reading! Count=%d",mPort,mGainErrorCount);

				if( ++mGainErrorCount > mGainErrorLimitCount )
				{
					 eventInfo("PCL %02d: TRACK mode failure, %d consecutive large gain errors gtr than %f db",mPort,mGainErrorCount,TRACK_MODE_GAIN_ERROR );
					 return false;
				}
			}
		}
	}
    return true;
}

//=============================================================================================================
// OverPowerOwner
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxPowerControl::OverPowerOwner::OverPowerOwner(int path):
                FaultOwner("TxPcl"),
			    mFault(ICommonRadioFaults::getInstance()->getPclOverPowerMajor(path))
{
}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::OverPowerOwner::set()
{
    mFault->setStatus( true );
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> TxPowerControl::OverPowerOwner::getFault()
{
    return mFault;
}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::OverPowerOwner::clear()
{
    mFault->setStatus( false );
}


//=============================================================================================================
// ConvergenceOwner
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxPowerControl::ConvergenceOwner::ConvergenceOwner(int path):
                FaultOwner("TxPcl"),
			    mFault(ICommonRadioFaults::getInstance()->getPclConvergenceMajor(path))
{
}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::ConvergenceOwner::set()
{
    mFault->setStatus( true );
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> TxPowerControl::ConvergenceOwner::getFault()
{
    return mFault;
}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::ConvergenceOwner::clear()
{
    mFault->setStatus( false );
}


//=============================================================================================================
// PowerMeasurementFaultOwner
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxPowerControl::PowerMeasurementFaultOwner::PowerMeasurementFaultOwner(int path):
                FaultOwner("TxPcl"),
			    mFault(ICommonRadioFaults::getInstance()->getPclPowerMeasurementMajor(path))
{
}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::PowerMeasurementFaultOwner::set()
{
    mFault->setStatus( true );
}

std::shared_ptr<IFault> TxPowerControl::PowerMeasurementFaultOwner::getFault()
{
    return mFault;
}

//-------------------------------------------------------------------------------------------------------------
void TxPowerControl::PowerMeasurementFaultOwner::clear()
{
    mFault->setStatus( false );
}
