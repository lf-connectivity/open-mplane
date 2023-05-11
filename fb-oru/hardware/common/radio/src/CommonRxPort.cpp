/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxPort.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IRadio.h"
#include "IDevices.h"
#include "ISynth.h"
#include "CommonSynth.h"
#include "CommonRxPort.h"
#include "IFrequencyConst.h"
#include "CommonTemperatureSensor.h"
#include "CommonAttenuator.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned SYNTH_TIMEOUT_MS{20} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonRxPort::CommonRxPort(int index, const char* name):
    CommonPort( index, name),
    mMutex(),
	mExternalPathIndex(1),
    mRxOnState(false),
    mAdcMuteState(false),
	mTempUpdated( false ),
    mCurrentTemperature(0.0),
    mPreviousTemperature(0.0),
    mDigitalPowerScaler(0.0f),
    mExtLoss(0.0f),
    mRadio( 0 )
{

}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonRxPort::initialise()
{
    // Start with Rx off and ADC muted
    setRxOff();
    muteAdc(true);
    mRadio = IRadioFactory::getInterface();

	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonRxPort::setFrequency(const Frequency& frequency)
{
	return setSynth(frequency) ;
}

//-------------------------------------------------------------------------------------------------------------
/*!
 * ATG requirement traceability for implementation.
 * Please do not remove.
 *
 * \satisfy{@req_8403{015}}
 * \satisfy{@req_8403{016}}
 */
ReturnType::State CommonRxPort::setSynth(const Frequency& frequency)
{
    std::shared_ptr<IRxFrequencyConst> rxf = IRxFrequencyConstFactory::getInterface();

    std::shared_ptr<IRadio> mRadio = IRadioFactory::getInterface();

    // Check to see if cal mode is off.
    if( false == mRadio->getCalMode() ) //! \calmode Do not apply frequency limits to RX set synth if in calibration mode.
    {
        if( frequency < rxf->getMinimum() || frequency > rxf->getMaximum() )
        {
            return ReturnType::RT_OUT_OF_RANGE;
        }
    }

    // set channel frequency
    // NOTE: This assumes that both the RX and DPD synthesisers need to be set together. If this is not the case
    // for a particular board then that board must override this method
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;

	unsigned rxPort(getIndex()) ;
    std::shared_ptr<ISynth> rxSynth( devices.getRxSynth( rxPort ) ) ;

    {
    	Mutex::Lock lock(mMutex) ;

    	ReturnType::State state;

    	// set the frequency value then program the device
		rxSynth->setFrequency(frequency) ;
		state = rxSynth->program() ;

		// If programming fails, return error
		if (state != ReturnType::RT_OK)
		{
			return state ;
		}

		// Wait for synth in lock (or timeout)
		state = waitSynthLocked(
			SYNTH_TIMEOUT_MS,
			[rxSynth]()->bool{
				return rxSynth->isPllLocked();
			}
		) ;

		if (state != ReturnType::RT_OK)
		{
			return state ;
		}
    }

    // Notify observers of the rx frequency that something has changed
    static_cast< Subject<IFrequencyChange>* >(this)->notify();

    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonRxPort::getFrequency()
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<ISynth> rxSynth( devices.getRxSynth( index ) ) ;

	Mutex::Lock lock(mMutex) ;
    return rxSynth->getFrequency() ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonRxPort::setIfAttenuation( Power attenuation )
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> rxIfAttn( devices.getRxIFAttenuator( index ) ) ;

    if (rxIfAttn != nullptr)
    {
    	return rxIfAttn->setAttenuation(attenuation);
    }

	return ReturnType::RT_OPERATION_FAILED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonRxPort::setRfAttenuation( Power attenuation )
{
	ReturnType::State rc = ReturnType::RT_OPERATION_FAILED;

	if (mRadio->getRxAttenMode() == IRxAgc::RxAgcMode::RX_AGC_MODE_AUTO)
	{
		return ReturnType::RT_NOT_ALLOWED;
	}

    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> rxRfAttn( devices.getRxRFAttenuator( index ) ) ;

    if (rxRfAttn != nullptr)
    {
    	rc = rxRfAttn->setAttenuation(attenuation);
    }

	return rc;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonRxPort::getIfAttenuation()
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> rxIfAttn( devices.getRxIFAttenuator( index ) ) ;

    if (rxIfAttn != nullptr)
    {
    	return rxIfAttn->getAttenuation();
    }

    return Power(31.75);
}

//-------------------------------------------------------------------------------------------------------------
Power CommonRxPort::getRfAttenuation()
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> rxRfAttn( devices.getRxRFAttenuator( index ) ) ;

    if (rxRfAttn != nullptr)
    {
    	return rxRfAttn->getAttenuation();
    }

    return Power(96.6);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonRxPort::setDigitalPowerScaler(float power)
{
    mDigitalPowerScaler = power;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
const Power CommonRxPort::getDigitalPowerScaler()
{
    return mDigitalPowerScaler;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonRxPort::getRssi(void)
{
    Power power(97.6);
    return power;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonRxPort::setRxOn(void)
{
    // turn Rx on
    ReturnType::State ret = setRxOnLowLevel();
    if (ret != ReturnType::RT_OK)
    {
        return ret;
    }

    mRxOnState = true;

    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonRxPort::setRxOff(void)
{
    // turn Rx off
    ReturnType::State ret = setRxOffLowLevel();
    if (ret != ReturnType::RT_OK)
    {
        return ret;
    }

    mRxOnState = false;

    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonRxPort::isRxOn(void)
{
    // either a simple return of the state variable or a more complex
    // test to see if there is actual RF being transmitted, by checking
    // the power meters.

    return mRxOnState;
}

//-------------------------------------------------------------------------------------------------------------
void CommonRxPort::muteAdc(bool muteState)
{
    if (mAdcMuteState != muteState)
    {
        // mute/unmute the DAC - TBD

        mAdcMuteState = muteState;
    }
}

//-------------------------------------------------------------------------------------------------------------
bool CommonRxPort::isAdcMuted()
{
    return mAdcMuteState;
}

//-------------------------------------------------------------------------------------------------------------
CommonRxPort::~CommonRxPort()
{
}

//-------------------------------------------------------------------------------------------------------------
const Temperature CommonRxPort::getTemperature()
{
    if( mTempUpdated == false)
    {
        updateAvgTemp();
    }
    return mCurrentTemperature;
}

//-------------------------------------------------------------------------------------------------------------
void CommonRxPort::updateAvgTemp()
{
	std::shared_ptr<IDevices> devices =  IDevicesFactory::create();
	std::shared_ptr<ITemperatureSensor> sensor( devices->getRxTemperatureSensor( 0 ) );

	if (sensor != nullptr)
	{
		// Read the temperature from the sensor
		mTemperature.add(sensor->getTemperature().get());

	    mTempUpdated = true;

	    // Keep the moving average temperature to 1 decimal place
	    mCurrentTemperature = Temperature(int(mTemperature.get()*10.0f)/10.0f) ;
	}

	// compare the current/previous and notify any observers if it's changed
	if (mPreviousTemperature != mCurrentTemperature)
	{
		static_cast< Subject<ITemperatureChange>* >(this)->notify() ;
	}

	// track
	mPreviousTemperature = mCurrentTemperature ;

}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAttenuator> CommonRxPort::getIfAttenuator()
{
    IDevices& devices( mRadio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<CommonAttenuator> rxIfAttn( std::dynamic_pointer_cast<CommonAttenuator>( devices.getRxIFAttenuator( index ) ) ) ;

    return rxIfAttn;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAttenuator> CommonRxPort::getRfAttenuator()
{
    IDevices& devices( mRadio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<CommonAttenuator> rxRfAttn( std::dynamic_pointer_cast<CommonAttenuator>( devices.getRxRFAttenuator( index ) ) ) ;

    return rxRfAttn;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonRxPort::getAdjustment()
{
    return Power(0.0) ;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonRxPort::getExtFilterLoss()
{
    return mExtLoss;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonRxPort::setExtFilterLoss(Power filterLoss)
{
	// NOTE: Rely on the limits being enforced externally to this method (e.g. in TIF)
	mExtLoss = filterLoss;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonRxPort::setPath( int path )
{
	mExternalPathIndex = path;
	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
int CommonRxPort::getPath()
{
	return mExternalPathIndex;
}
