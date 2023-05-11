/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioStateService.cpp
 * \brief
 *
 *
 * \details
 *
 */
#include <sstream>

#include "IAlarmsList.h"
#include "IAlarmMonitor.h"
#include "IRadio.h"
#include "ITxPort.h"
#include "IVswr.h"
#include "IFaultsList.h"
#include "ISystemReboot.h"

#include "RrhAlarms.h"
#include "RadioStateService.h"

using namespace Mplane;

Mplane::RadioStateService::RadioStateService() :
	Service( SERVICE_LOW_PRIORITY, SMALL_STACK, 500, "RadioStateService", "RA" ),
	heartBeatAlarmStartTime(0),
	heartBeatTimeOutRunning(false),
	mCarrierMgr(ICarrierServer::getInstance()),
	mIsTxOn(),
	mTxOnUpdated(false),
	mSetPclPathToOff(),
	mSetPclPathToOffCache(),
#if 0
	mSysLedInstance( IRadioFactory::getInterface()->getDevices().getLed( 0 )->getLed(0)),
	mPclPath0( ITxPcl::getInstance( 0 ) ),
	mVswr( IVswr::getInstance( 0 ) ),
#endif
	mCurrentRadioState(IRadioState::RADIO_STATE_INITIAL),
	mRadio( IRadioFactory::getInterface()),  // get our radio instance
	mImageManagement( IImageManagement::getInstance()),
	mRrhAlarms( RrhAlarms::getInstance() ),
	mFaultsList( IFaultsList::getInstance() )
{
	numberOfTxPorts = mRadio->getNumberOfTxPorts();
	numberOfRxPorts = mRadio->getNumberOfRxPorts();
	mIsTxOn.resize(numberOfTxPorts, false);
	mSetPclPathToOff.resize(numberOfTxPorts, false);
	mSetPclPathToOffCache.resize(numberOfTxPorts, false);

#if 0
	if( numberOfTxPorts > 1 )
	{
		mPclPath1 = ITxPcl::getInstance( 1 );
	}
#endif

	// Register as an observer of the carrier manager TX ON and TX OFF events.
	std::dynamic_pointer_cast<Subject<ITxOn,  const ITxEventData&>>(mCarrierMgr)->attach(*this);
	std::dynamic_pointer_cast<Subject<ITxOff, const ITxEventData&>>(mCarrierMgr)->attach(*this);

	// Lambda method to register the update method to handle updates from the Alarm Monitor
	std::shared_ptr<IAlarmMonitor> monitor(IAlarmMonitor::getInstance()) ;

	monitor->registerHandler([this](const IAlarm& alarm) {this->update(alarm);} );
}

Mplane::RadioStateService::~RadioStateService()
{
	// DeRegister as an observer of the carrier manager TX ON and TX OFF events.
	std::dynamic_pointer_cast<Subject<ITxOn,  const ITxEventData&>>(mCarrierMgr)->detach(*this);
	std::dynamic_pointer_cast<Subject<ITxOff, const ITxEventData&>>(mCarrierMgr)->detach(*this);
}

IRadioState::RadioStatesType Mplane::RadioStateService::getState() const
{
	return mCurrentRadioState;
}

void Mplane::RadioStateService::showRadioState()
{
	eventInfo("*** Rrh Radio State Service Show ***");
	eventInfo("    Current State is %s", mStateNames[mCurrentRadioState]);
	eventInfo("    Alarm status - ");

	for (unsigned int index = 0; index < numberOfTxPorts; index++)
	{
		eventInfo("    Tx%dShutdownAlarm    - %s", index + 1, ( getAlarm( mRrhAlarms->mTxShutdownAlarm[index] )    ? "true" : "false" ));
		eventInfo("    Tx%dDegradedAlarm    - %s", index + 1, ( getAlarm( mRrhAlarms->mTxDegradedAlarm[index] )    ? "true" : "false" ));
		eventInfo("    VswrTx%dAlarm        - %s", index + 1, ( getAlarm( mRrhAlarms->mVswrTxAlarm[index] )        ? "true" : "false" ));
		eventInfo("    Pa%dTempMajorAlarm   - %s", index + 1, ( getAlarm( mRrhAlarms->mPaTempMajorAlarm[index] )   ? "true" : "false" ));
		eventInfo("    Pa%dTempMinorAlarm   - %s", index + 1, ( getAlarm( mRrhAlarms->mPaTempMinorAlarm[index] )   ? "true" : "false" ));
		eventInfo("    Tx%dBbIqAlarm        - %s", index + 1, ( getAlarm( mRrhAlarms->mTxBbIqAlarm[index] )        ? "true" : "false" ));
	}

	for (unsigned int index = 0; index < numberOfRxPorts; index++)
	{
		eventInfo("    Rx%dMajorAlarm       - %s", index + 1, ( getAlarm( mRrhAlarms->mRxMajorAlarm[index] )       ? "true" : "false" ));
	}
//	eventInfo("    RadioCardPsuAlarm   - %s", ( getAlarm( mRrhAlarms->mRadioCardPsuAlarm )   ? "true" : "false" ));
	eventInfo("    HeartBeatAlarm      - %s", ( getAlarm( mRrhAlarms->mHeartBeatAlarm )      ? "true" : "false" ));
	eventInfo("    Cpri0MajorAlarm     - %s", ( getAlarm( mRrhAlarms->mCpri0MajorAlarm )     ? "true" : "false" ));
	eventInfo("    PllMajorAlarm       - %s", ( getAlarm( mRrhAlarms->mPllMajorAlarm )       ? "true" : "false" ));
	eventInfo("    RadioTempMajorAlarm - %s", ( getAlarm( mRrhAlarms->mRadioTempMajorAlarm ) ? "true" : "false" ));
	eventInfo("    RadioTempMinorAlarm - %s", ( getAlarm( mRrhAlarms->mRadioTempMinorAlarm ) ? "true" : "false" ));
	eventInfo("*** End Rrh Radio State Service Show ***");
}

void Mplane::RadioStateService::updateLedStatusIndication(IRadioState::RadioStatesType radioState)
{
#if 0
	switch( radioState )
	{
	case RADIO_STATE_INITIAL:
		mSysLedInstance->setState(ILed::LED_ON);
		mSysLedInstance->setColour(ILed::LED_RED);
		break;
	case RADIO_STATE_NORMAL:
		mSysLedInstance->setState(ILed::LED_ON);
		mSysLedInstance->setColour(ILed::LED_GREEN);
		break;
	case RADIO_STATE_NORMAL_STANDBY:
		mSysLedInstance->setState(ILed::LED_FLASH);
		mSysLedInstance->setColour(ILed::LED_GREEN);
		mSysLedInstance->setRate(NORMAL_STANDBY_FLASH_RATE);
		break;
	case RADIO_STATE_NORMAL_SW_DOWNLOAD:
		mSysLedInstance->setState(ILed::LED_FLASH);
		mSysLedInstance->setColour(ILed::LED_YELLOW);
		mSysLedInstance->setRate(NORMAL_SW_DOWNLOAD_FLASH_RATE);
		break;
	case RADIO_STATE_FAILED_CPRI_LINK_FAIL:
		mSysLedInstance->setState(ILed::LED_ON);
		mSysLedInstance->setColour(ILed::LED_YELLOW);
		break;
	case RADIO_STATE_DEGRADED:
		mSysLedInstance->setState(ILed::LED_FLASH);
		mSysLedInstance->setColour(ILed::LED_RED);
		mSysLedInstance->setRate(DEGRADED_FLASH_RATE);
		break;
	case RADIO_STATE_FAILED:
	default:
		mSysLedInstance->setState(ILed::LED_ON);
		mSysLedInstance->setColour(ILed::LED_RED);
		break;
	}
#endif
}

void Mplane::RadioStateService::show()
{
}

int Mplane::RadioStateService::service()
{
#if 0
	// As this service uses the LEDs, ensure they've completed initialisation before we start
	std::shared_ptr<ILedControl> ledControl(IRadioFactory::getInterface()->getDevices().getLed( 0 )) ;
	if (!ledControl->isInitComplete())
	{
		// Initialisation of the LEDs is not yet complete - check again next time around
		return 0 ;
	}
#endif

	// Protect with a mutex to make sure we complete this exercise with no interruptions
	Mutex::Lock lock(mMutex) ;

	// See if TxOn has been update whilst we have been sleeping. Clear the alarms if needed per path.
	if ( true == mTxOnUpdated )
	{
		for (unsigned int index = 0; index < numberOfTxPorts; index++)
		{
			// Tx On has been updated in the background, reset the alarms according to the path
			if (true == mIsTxOn[index])
			{
				eventInfo("RadioStateService::service - Clearing alarms for common/path %d", index);

				// Clear the alarms associated with path 1 and the other alarms not associated with a path
				resetAlarm(mRrhAlarms->mTxShutdownAlarm[index]);
				resetAlarm(mRrhAlarms->mTxDegradedAlarm[index]);
				resetAlarm(mRrhAlarms->mRxMajorAlarm[index]);
				resetAlarm(mRrhAlarms->mVswrTxAlarm[index]);

				resetAlarm(mRrhAlarms->mPaTempMajorAlarm[index]);
				resetAlarm(mRrhAlarms->mPaTempMinorAlarm[index]);
				resetAlarm(mRrhAlarms->mTxBbIqAlarm[index]);

				resetAlarm(mRrhAlarms->mRadioTempMajorAlarm);
				resetAlarm(mRrhAlarms->mRadioTempMinorAlarm);
//				resetAlarm(mRrhAlarms->mRadioCardPsuAlarm);
				resetAlarm(mRrhAlarms->mCpri0MajorAlarm);
				resetAlarm(mRrhAlarms->mHeartBeatAlarm);
				resetAlarm(mRrhAlarms->mPllMajorAlarm);

				// Reset the faults so that they will be re-asserted if the still exist
				// Otherwise, the alarms will not get re-raised!
				//
				// This is meant to be the fix for issue #FLX:4187
				mFaultsList->resetFaults();

				// Clear the mSetPclPathToOffCache
				mSetPclPathToOffCache[index] = false;
			}
		}

		// Reset the flag for next time
		mTxOnUpdated = false;
	}

	// Reset the Pcl path vector
	std::fill(mSetPclPathToOff.begin(),mSetPclPathToOff.end(), false);

	// Update the radio state from the alarms and action anything as a result.
	IRadioState::RadioStatesType radioState = updateRadioStateFromAlarms();

	// Only update the LED status indication if the radio state has changed or
	// either of the two Pcl shutdown path flags have been set.
	if( (radioState != mCurrentRadioState)            ||
		(mSetPclPathToOff != mSetPclPathToOffCache) )
	{
		eventInfo("RadioStateService::service - Changing state - %s to %s",
		IRadioState::mStateNames[mCurrentRadioState],
		IRadioState::mStateNames[radioState]);

		for (unsigned int index = 0; index < numberOfTxPorts; index++)
		{
			eventInfo("PCL Path %d = %s", index, (mSetPclPathToOff[index]?"true":"false"));
		}

		logDebugVerbose("RadioTempMajorAlarm - %s", ( getAlarm( mRrhAlarms->mRadioTempMajorAlarm ) ? "true" : "false" ));
		logDebugVerbose("RadioTempMinorAlarm - %s", ( getAlarm( mRrhAlarms->mRadioTempMinorAlarm ) ? "true" : "false" ));

		for (unsigned int index = 0; index < numberOfTxPorts; index++)
		{
			logDebugVerbose("Tx%dShutdownAlarm    - %s", index + 1, ( getAlarm( mRrhAlarms->mTxShutdownAlarm[index] )    ? "true" : "false" ));
			logDebugVerbose("Tx%dDegradedAlarm    - %s", index + 1, ( getAlarm( mRrhAlarms->mTxDegradedAlarm[index] )    ? "true" : "false" ));
			logDebugVerbose("VswrTx%dAlarm        - %s", index + 1, ( getAlarm( mRrhAlarms->mVswrTxAlarm[index] )        ? "true" : "false" ));
			logDebugVerbose("Pa%dTempMajorAlarm   - %s", index + 1, ( getAlarm( mRrhAlarms->mPaTempMajorAlarm[index] )   ? "true" : "false" ));
			logDebugVerbose("Pa%dTempMinorAlarm   - %s", index + 1, ( getAlarm( mRrhAlarms->mPaTempMinorAlarm[index] )   ? "true" : "false" ));
			logDebugVerbose("Tx%dBbIqAlarm        - %s", index + 1, ( getAlarm( mRrhAlarms->mTxBbIqAlarm[index] )        ? "true" : "false" ));

		}

		for (unsigned int index = 0; index < numberOfRxPorts; index++)
		{
			logDebugVerbose("Rx%dMajorAlarm       - %s", index + 1, ( getAlarm( mRrhAlarms->mRxMajorAlarm[index] )       ? "true" : "false" ));
		}

//		logDebugVerbose("RadioCardPsuAlarm   - %s", ( getAlarm( mRrhAlarms->mRadioCardPsuAlarm )   ? "true" : "false" ));
		logDebugVerbose("Cpri0MajorAlarm     - %s", ( getAlarm( mRrhAlarms->mCpri0MajorAlarm )     ? "true" : "false" ));
		logDebugVerbose("HeartBeatAlarm      - %s", ( getAlarm( mRrhAlarms->mHeartBeatAlarm )      ? "true" : "false" ));
		logDebugVerbose("PllMajorAlarm       - %s", ( getAlarm( mRrhAlarms->mPllMajorAlarm )       ? "true" : "false" ));

		if( IRadioState::RADIO_STATE_FAILED == radioState )
		{
			// Shutdown both paths.
			eventInfo("RadioStateService - FAILED - requesting shut down of all paths");

#if 0
			mPclPath0->setTxOff();

			if( numberOfTxPorts > 1 )
			{
				// Only if we actually have more than 1 port
				mPclPath1->setTxOff();
			}
#endif

			// Cache the current path settings so we only do it once.
			std::fill(mSetPclPathToOffCache.begin(),mSetPclPathToOffCache.end(), true);
		}
		else if( IRadioState::RADIO_STATE_DEGRADED == radioState )
		{
			for (unsigned int index = 0; index < numberOfTxPorts; index++)
			{
				// Shutdown paths as required.
				if( mSetPclPathToOff[index] )
				{
					eventInfo("RadioStateService - DEGRADED - requesting shut down of path %d", index);
#if 0
					mPclPath0->setTxOff();
#endif
					// Cache the current path settings so we only do it once.
					mSetPclPathToOffCache[index] = true;
				}
			}
		}

		// Now update the LED status based on the current radio state
		updateLedStatusIndication(radioState);

		mCurrentRadioState = radioState;
	}

	return 0;
}

void Mplane::RadioStateService::doReset()
{
}

bool Mplane::RadioStateService::registerObservers()
{
	return true ;
}

IRadioState::RadioStatesType_T Mplane::RadioStateService::updateRadioStateFromAlarms(void)
{
	IRadioState::RadioStatesType_T radioState = IRadioState::RADIO_STATE_NORMAL_STANDBY;

	logDebugVerbose("Cpri0MajorAlarm     - %s", ( getAlarm( mRrhAlarms->mCpri0MajorAlarm )     ? "true" : "false" ));
	logDebugVerbose("PllMajorAlarm       - %s", ( getAlarm( mRrhAlarms->mPllMajorAlarm )       ? "true" : "false" ));

	bool radioTempMajorAlarm = getAlarm( mRrhAlarms->mRadioTempMajorAlarm );
	bool heartBeatAlarm      = getAlarm( mRrhAlarms->mHeartBeatAlarm );
	bool cpri0MajorAlarm     = getAlarm( mRrhAlarms->mCpri0MajorAlarm );
//	bool RadioCardPsuAlarm   = getAlarm( mRrhAlarms->mRadioCardPsuAlarm );

	std::vector<bool> txShutdownAlarm(numberOfTxPorts, false);
	std::vector<bool> txDegradedAlarm(numberOfTxPorts, false);
	std::vector<bool> vswrTxAlarm(numberOfTxPorts, false);
	std::vector<bool> rxMajorAlarm(numberOfRxPorts, false);

	// Populate vectors for Tx alarms
	for (unsigned int index = 0; index < numberOfTxPorts; index++)
	{
		txShutdownAlarm[index] = getAlarm( mRrhAlarms->mTxShutdownAlarm[index] );
		txDegradedAlarm[index] = getAlarm( mRrhAlarms->mTxDegradedAlarm[index] );
		vswrTxAlarm[index] = getAlarm( mRrhAlarms->mVswrTxAlarm[index] );
	}

	// Populate vector for Rx alarms
	for (unsigned int index = 0; index < numberOfRxPorts; index++)
	{
		rxMajorAlarm[index] = getAlarm( mRrhAlarms->mRxMajorAlarm[index] );
	}

#if 0
	IVswr::vswrShutdownMode_T vswrShutdownMode = mVswr->getShutdownMode();

	bool autoEnabledVswr = (vswrShutdownMode == IVswr::vswrShutdownMode_T::automatic) ? true:false;

	logDebugVerbose("RadioStateService::updateRadioStateFromAlarms - vswr shutdown mode - %s", (vswrShutdownMode == IVswr::vswrShutdownMode_T::automatic) ? "auto":"manual" );
#endif

	std::vector<bool> shutdownTxFault(numberOfTxPorts, false);
	std::vector<bool> degradeRxFault(numberOfTxPorts, false);

	bool allTxPathsShutdown = true;
	bool atleastOneTxPathShutdown = false;
	bool atleastOneTxPathDegraded = false;
	bool atleastOneTxIsOn = false;

	// Go through the list of Tx alarms
	for (unsigned int index = 0; index < numberOfTxPorts; index++)
	{
		// Check whether any Tx paths have shutdown alarms
		if (txShutdownAlarm[index] == true ||
			(vswrTxAlarm[index] == true /*&& autoEnabledVswr == true */) )
		{
			shutdownTxFault[index] = true;
			atleastOneTxPathShutdown = true;
		}
		else
		{
			allTxPathsShutdown = false;
		}

		// Check whether any Tx paths have degrade alarms
		if (txDegradedAlarm[index] == true)
		{
			atleastOneTxPathDegraded = true;
		}

		// Check whether any Tx path is ON
		if (mIsTxOn[index])
		{
			atleastOneTxIsOn = true;
		}
	}

	// Check whether any Rx paths have major alarms
	bool allRxPathsDegraded = true;
	bool atleastOneRxPathDegraded = false;
	for (unsigned int index = 0; index < numberOfRxPorts; index++)
	{
		if (rxMajorAlarm[index] == true )
		{
			degradeRxFault[index] = true;
			atleastOneRxPathDegraded = true;
		}
		else
		{
			allRxPathsDegraded = false;
		}
	}

	if( true == mImageManagement->isDownloading() )
	{
		radioState = IRadioState::RADIO_STATE_NORMAL_SW_DOWNLOAD;
	}
	else if( (true == heartBeatAlarm)      ||
//	         (true == radioCardPsuAlarm)   ||
	         (true == radioTempMajorAlarm) ||
	         (true == allTxPathsShutdown)  ||
	         (true == allRxPathsDegraded))
	{
		radioState = IRadioState::RADIO_STATE_FAILED;

		// Shutdown all paths. We have to do this to stop a cyclic request for the PCL to shut down.

		std::fill(mSetPclPathToOff.begin(), mSetPclPathToOff.end(), true);
	}
	else if( true == cpri0MajorAlarm )
	{
		radioState = IRadioState::RADIO_STATE_FAILED_CPRI_LINK_FAIL;
	}
	else if( true == atleastOneTxPathShutdown )
	{
		radioState = IRadioState::RADIO_STATE_DEGRADED;

		// Shutdown the paths with fault
		for (unsigned int index = 0; index < numberOfTxPorts; index++)
		{
			if (true == shutdownTxFault[index])
			{
				mSetPclPathToOff[index] = true;
			}
		}
	}
	else if( (true == atleastOneRxPathDegraded)    ||
			 (true == atleastOneTxPathDegraded))
	{
		radioState = IRadioState::RADIO_STATE_DEGRADED;
	}
	else if ( true == atleastOneTxIsOn )
	{
		radioState = IRadioState::RADIO_STATE_NORMAL;
	}
	else
	{
		radioState = IRadioState::RADIO_STATE_NORMAL_STANDBY;
	}

	if( true == heartBeatAlarm )
	{
		if( false == heartBeatTimeOutRunning )
		{
			eventInfo("RadioStateService - Starting heart beat time out");

			// Heart beat time out has occurred
			heartBeatTimeOutRunning = true;

			// Make a note of the time
			time( &heartBeatAlarmStartTime);

			// The radio state will be taken care of as the heartbeat fault is also
			// associated with the TxnShutdown alarms.
		}
		else
		{
			// Check to see how much time has elapsed
			time_t timeNow;
			time( &timeNow );

			if( HEARTBEAT_TIME_OUT_PERIOD < difftime(timeNow, heartBeatAlarmStartTime))
			{
				eventWarning("Radio State Service - Heartbeat timeout! !!REBOOTING!!");

				std::shared_ptr<ISystemReboot> systemReboot = ISystemReboot::getInstance();
				systemReboot->now();
			}
		}
	}
	else
	{
		// Has the Heartbeat Alarm been cancelled
		if( true == heartBeatTimeOutRunning )
		{
			// If it was running, reset out variables.
			heartBeatAlarmStartTime = 0;
			heartBeatTimeOutRunning = false;

			eventInfo("RadioStateService - Heart beat cancelled");
		}
	}

	return radioState;
}

void Mplane::RadioStateService::update(ITxOn& subject, const ITxEventData& txOnOff)
{
	// Protect with a mutex to make sure we complete this exercise with no interruptions
	Mutex::Lock lock(mMutex) ;

	mTxOnUpdated = true;

	unsigned port = txOnOff.getPort();
	if (port < numberOfTxPorts)
	{
		mIsTxOn[port] = true;

		logDebugVerbose("RadioStateService::update - Tx%dOn = true", port + 1);

		// We need to action this ASAP and we cannot wait for the next timer expiry
		mNotify.signal();
	}
}

void Mplane::RadioStateService::update(ITxOff& subject, const ITxEventData& txOnOff)
{
	// Protect with a mutex to make sure we complete this exercise with no interruptions
	Mutex::Lock lock(mMutex) ;

	unsigned port = txOnOff.getPort();
	if (port < numberOfTxPorts)
	{
		mIsTxOn[port] = false;

		logDebugVerbose("RadioStateService::update - Tx%dOff = true", port + 1);

		// We need to action this ASAP and we cannot wait for the next timer expiry
		mNotify.signal();
	}
}

void Mplane::RadioStateService::update(const IAlarm& alarm)
{
	// The alarm monitor is telling us that an alarm has changed.
	// We need to action this ASAP and we cannot wait for the next timer expiry
	eventInfo("RadioStateService::update alarm - %s; state = %s", alarm.getName().c_str(), alarm.getAlarmStateString().c_str());

	mNotify.signal();
}

bool Mplane::RadioStateService::getAlarm(std::shared_ptr<IAlarm> alarmToRetrieve)
{
	return alarmToRetrieve->isAlarmActive();
}

bool Mplane::RadioStateService::resetAlarm(std::shared_ptr<IAlarm> alarmToReset)
{
	bool returnState = false;

	if( alarmToReset->isAlarmActive() )
	{
		alarmToReset->setStatus(false);

		returnState = true;
	}

	return returnState;
}
