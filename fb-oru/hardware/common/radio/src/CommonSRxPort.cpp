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
#include "ILoggable.h"
#include "IRadio.h"
#include "IDevices.h"
#include "ITemperatureSensor.h"
#include "ISynth.h"
#include "CommonSynth.h"
#include "CommonSRxPort.h"
#include "IFpgaMgr.h"
#include "Task.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned SYNTH_TIMEOUT_MS{20} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonSRxPort::CommonSRxPort(int index, const char* name):
    CommonPort( index, name),
    mMutex(),
    mSamplePathIndex(0),
	mDir(ISRxPort::Direction::SRX_DIR_FORWARD),
    mSystemFpga( IFpgaMgr::getIFpgaSystemRegs()),
	mAntennaFpga( IFpgaMgr::getIFpgaAntennaRegs()),
    mAtten(0),
	mTempUpdated( false ),
	mMeasInProg(false)
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::initialise()
{
    std::shared_ptr<IRadio> radio( IRadioFactory::getInterface() ) ;
    IDevices& devices( radio->getDevices() );
    mAtten = devices.getDpdAttenuator( getIndex() );

    if (mAtten != nullptr)
    {
    	mAtten->setMaxAttenuation();
    }

	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::setFrequency(const Frequency& frequency)
{
	Mutex::Lock lock(mMutex) ;

	ReturnType::State status = setSynth(frequency) ;
	ILoggable::logEventInfo("SRX%d: Set frequency %f KHz - %s",
			getIndex(), frequency.getDbl(Frequency::KHz), ReturnType::getState(status)) ;
	return status ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::setSynth(const Frequency& frequency)
{
    // set channel frequency
    /* NOTE: This assumes that both the RX and DPD synthesisers need to be set
     * together. If this is not the case for a particular board then that board
     * must override this method
     */
    std::shared_ptr<IRadio> radio( IRadioFactory::getInterface() ) ;
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) CommonPort::getIndex();
    std::shared_ptr<ISynth> dpdSynth( devices.getDpdSynth( index ) ) ;

    {

    	ReturnType::State state;

    	// set the frequency value then program the device
    	dpdSynth->setFrequency(frequency) ;
		state = dpdSynth->program() ;

		// If programming fails, return error
		if (state != ReturnType::RT_OK)
		{
			return state ;
		}

		// Wait for synth in lock (or timeout)
		state = waitSynthLocked(
			SYNTH_TIMEOUT_MS,
			[dpdSynth]()->bool{
				return dpdSynth->isPllLocked();
			}
		) ;

		if (state != ReturnType::RT_OK)
		{
			return state ;
		}
    }

    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonSRxPort::getFrequency()
{
    std::shared_ptr<IRadio> radio( IRadioFactory::getInterface() ) ;
    IDevices& devices( radio->getDevices() ) ;
    volatile const int index = (const int) CommonPort::getIndex();
    std::shared_ptr<ISynth> dpdSynth( devices.getDpdSynth( index ) ) ;

    return dpdSynth->getFrequency() ;
}


//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::setAttenuation( Power attenuation )
{
    if ( mAtten )
    {
        return mAtten->setAttenuation( attenuation ) ;
    }
    return ReturnType::RT_NOT_INITIALISED;
}


//-------------------------------------------------------------------------------------------------------------
Power CommonSRxPort::getAttenuation()
{
    if ( mAtten )
    {
        return mAtten->getAttenuation() ;
    }
    Power power(0.0);
    return power;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonSRxPort::getPower( void )
{
    return getRawAdcRms();
}

//-------------------------------------------------------------------------------------------------------------
Power CommonSRxPort::getRawAdcRms(void)
{
    return Power(0.0);
}

//-------------------------------------------------------------------------------------------------------------
Power CommonSRxPort::getDC(std::complex<double>& dc)
{
    return Power(0.0);
}

//-------------------------------------------------------------------------------------------------------------
Power CommonSRxPort::getRawAdcPeak(void)
{
    return Power(0.0);
}

//-------------------------------------------------------------------------------------------------------------
Power CommonSRxPort::getDC(void)
{
	std::complex<double> dc ;
	return getDC(dc) ;
}

//-------------------------------------------------------------------------------------------------------------
CommonSRxPort::~CommonSRxPort()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::setPath(int index)
{
    mSamplePathIndex = index;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
int CommonSRxPort::getPath()
{
    return mSamplePathIndex;
}

//-------------------------------------------------------------------------------------------------------------
float CommonSRxPort::getTemperature()
{
    if( mTempUpdated == false)
    {
        updateAvgTemp();
    }
    return int(mTemperature.get()*10.0f)/10.0f;  // return the moving average temperature to 1 decimal place
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::setTargetPower(int path, Power target)
{
    return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::getFwdPower(int path, Power& rf, Power& digital)
{
    return getTssi(true, path, rf, digital);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::getRevPower(int path, Power& rf, Power& digital)
{
    return getTssi(false, path, rf, digital);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::getPathAtten(int path, Power& attenuation)
{
    return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonSRxPort::getMeasurementInProgress()
{
    return mMeasInProg;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::setDirection( ISRxPort::Direction dir )
{
	mDir = dir;
	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ISRxPort::Direction CommonSRxPort::getDirection()
{
	return mDir;
}

//-------------------------------------------------------------------------------------------------------------
void CommonSRxPort::updateAvgTemp()
{
	std::shared_ptr<IDevices> devices =  IDevicesFactory::create();
	std::shared_ptr<ITemperatureSensor> sensor( devices->getSRxTemperatureSensor( 0 ) );

	if (sensor != nullptr)
	{
		// Read the temperature from the sensor
		mTemperature.add(sensor->getTemperature().get());

	    mTempUpdated = true;
	}
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonSRxPort::getTssi(bool forward, unsigned path, Power& rfPower, Power& digitalPower)
{
    return ReturnType::RT_ERROR;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonSRxPort::getCorrection(void)
{
    Power power(0.0);
    return power;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonSRxPort::measureRssi(const std::string& fnName)
{
	return false ;
}
