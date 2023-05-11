/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxPort.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <typeinfo>
#include <memory>

#include "IRadio.h"
#include "IDevices.h"
#include "IDevice.h"
#include "IAttenuator.h"
#include "ISynth.h"
#include "IRadio.h"
#include "IModules.h"
#include "IFrequencyConst.h"
#include "IDac.h"

#include "ILoggable.h"
#include "Task.h"

#include "IFpgaMgr.h"
#include "CommonSynth.h"
#include "CommonTxPort.h"
#include "CommonTemperatureSensor.h"
#include "CommonAttenuator.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const unsigned SYNTH_TIMEOUT_MS{1000} ;
const unsigned EXPECTED_SYNTH_LOCK_TIME_MS{4} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonTxPort::CommonTxPort(int index, const char* name) :
	CommonPort(index, name),
	mMutex(),
	mExternalPathIndex(1),
	mTxOnState(false),
	mPadState( AttenPadState::PAD_OFF ),
	mFilterState( LowPassFilterState::FILTER_OFF ),
	mMaxPower(0.0f),
	mMinPower(0.0f),
	mMaxPaPower(0.0f),
	mForward(0.0f),
	mReverse(0.0f),
	mDigital(0.0f),
	mRevDigital(0.0f),
	mExtLoss(0.0f),
	mInitRequired(true),
	mOutputMode( Mode::MODULATED ),
	mDigitalPowerScaler(0.0f),
	mCWPower(0.0),
	mTempUpdated( false ),
	mCurrentTemperature(0.0),
	mPreviousTemperature(0.0),
	mTxGain(0.0f)
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::initialise()
{
    // Start with Tx off
    setTxOff();

    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setFrequency(const Frequency& frequency)
{
	return setSynth(frequency) ;
}

//-------------------------------------------------------------------------------------------------------------
/*!
 * ATG requirement traceability for implementation.
 * Please do not remove.
 *
 * \satisfy{@req_8403{013}}
 * \satisfy{@req_8403{014}}
 */
ReturnType::State CommonTxPort::setSynth(const Frequency& frequency)
{
	auto fpga( IFpgaMgr::getIFpgaAntennaRegs() ) ;
	unsigned txPort(getIndex()) ;

	// set channel frequency
	std::shared_ptr<ITxFrequencyConst> txf = ITxFrequencyConstFactory::getInterface();

    std::shared_ptr<IRadio> mRadio = IRadioFactory::getInterface();

    // Check to see if cal mode is off.
    if( false == mRadio->getCalMode() ) //! \calmode Do not apply frequency limits to TX set synth if in calibration mode.
    {
        if( frequency < txf->getMinimum() || frequency > txf->getMaximum() )
        {
            return ReturnType::RT_OUT_OF_RANGE;
        }
    }

	// Hold a lock while we set the synth
	{
		Mutex::Lock lock(mMutex) ;

		ReturnType::State state;

		std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
		IDevices& devices(radio->getDevices());
		std::shared_ptr<CommonSynth> txSynth(std::dynamic_pointer_cast<CommonSynth>(devices.getTxSynth(getIndex())));

		// TODO Is this required? - disable synth output
		fpga->write_txQuadModEnable(txPort, 0) ;

		// check the frequency value then program the device
		txSynth->setFrequency(frequency);
		state = txSynth->program() ;

		// If programming fails, return error
		if (state != ReturnType::RT_OK)
		{
			return state ;
		}

		// Wait for synth in lock (or timeout)
		state = waitSynthLocked(
			SYNTH_TIMEOUT_MS,
			[txSynth]()->bool{
				return txSynth->isPllLocked();
			}
		) ;

		// TODO Is this required? - enable synth output
		fpga->write_txQuadModEnable(txPort, 1) ;

		if (state != ReturnType::RT_OK)
		{
			return state ;
		}
	}

    // Notify observers of the tx frequency that something has changed
    static_cast< Subject<IFrequencyChange>* >(this)->notify();

    return ReturnType::RT_OK;
}


//-------------------------------------------------------------------------------------------------------------
const Frequency CommonTxPort::getFrequency()
{
	Mutex::Lock lock(mMutex) ;

    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices(radio->getDevices());
    std::shared_ptr<CommonSynth> txSynth(std::dynamic_pointer_cast<CommonSynth>(devices.getTxSynth(getIndex())));
    return txSynth->getFrequency();
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonTxPort::getSynthFrequency()
{
	Mutex::Lock lock(mMutex) ;

    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices(radio->getDevices());
    std::shared_ptr<CommonSynth> txSynth(std::dynamic_pointer_cast<CommonSynth>(devices.getTxSynth(getIndex())));
    return txSynth->getSynthFrequency();
}

//-------------------------------------------------------------------------------------------------------------
bool CommonTxPort::isBadIbsFreq( Frequency frequency )
{
	Mutex::Lock lock(mMutex) ;

    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices(radio->getDevices());
    std::shared_ptr<CommonSynth> txSynth(std::dynamic_pointer_cast<CommonSynth>(devices.getTxSynth(getIndex())));
    return txSynth->isBadIbsFreq( frequency );
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setTxOn(void)
{
    // turn Tx on
    ReturnType::State ret = setTxOnLowLevel();
    if (ret != ReturnType::RT_OK)
        return ret;

    // - set max attenuation, digital and analog
    // - update fem control registers for pa on and tx enable
    // - set configured atten values, actually turns RF on

    mTxOnState = true;

    // skip notification if this is initialisation
    if (!mInitRequired)
        static_cast<Subject<ITxPort>*>(this)->notify(); // tell register observers there's been a change in the tx port.
    else
        mInitRequired = false;

    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setTxOff(void)
{
    // turn Tx off
    ReturnType::State ret = setTxOffLowLevel();
    if (ret != ReturnType::RT_OK)
        return ret;

    // - set max attenuation, digital and analog
    // - update fem control registers for pa on and tx enable

    mTxOnState = false;

    // skip notification if this is initialisation
    if (!mInitRequired)
        static_cast<Subject<ITxPort>*>(this)->notify(); // tell register observers there's been a change in the tx port.
    else
        mInitRequired = false;

    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonTxPort::isTxOn(void)
{
    // either a simple return of the state variable or a more complex
    // test to see if there is actual RF being transmitted, by checking
    // the power meters.

    return mTxOnState;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setRadioOutputPower( Power &power )
{
    return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::getFwdPower(Power &forward, Power &digital)
{
    forward = mForward;
    digital = mDigital;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::getRevPower(Power &reverse, Power &digital)
{
    reverse = mReverse;
    digital = mRevDigital;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonTxPort::getTargetPower()
{
    return mTargetPower;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setTargetPower(Power targetPower)
{
    mTargetPower = targetPower;
    static_cast<Subject<ITxPort>*>(this)->notify(); // tell register observers there's been a change in the tx port.
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonTxPort::getMaxPower(void)
{
    return mMaxPower;
}

Power CommonTxPort::getMaxFreqDepPower(void)
{
    return mMaxPower;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonTxPort::getMinPower(void)
{
    return mMinPower;
}

Power CommonTxPort::getMinFreqDepPower(void)
{
    return mMinPower;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonTxPort::getMaxPaPower(void)
{
    return mMaxPaPower;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setTxDelay(UINT32 delay)
{
    // set the Tx delay adjustment - TBD

    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonTxPort::getCalFrequency(void) const
{
    //  - TBD

    return Frequency(0ull);
}


//-------------------------------------------------------------------------------------------------------------
CommonTxPort::~CommonTxPort()
{
}

//-------------------------------------------------------------------------------------------------------------
Power CommonTxPort::getAttenuation()
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> txAttn = std::dynamic_pointer_cast<IAttenuator>(
    		devices.getDevice(IDevice::ATTENUATOR, IDevices::DeviceCollection::TX, index)) ;

	if (txAttn != nullptr)
	{
		return txAttn->getAttenuation();
	}

	return Power(96.6);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setAttenuation( Power attn)
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> txAttn = std::dynamic_pointer_cast<IAttenuator>(
        		devices.getDevice(IDevice::ATTENUATOR, IDevices::DeviceCollection::TX, index)) ;

	if (txAttn != nullptr)
	{
		return txAttn->setAttenuation(attn);
	}

	return ReturnType::RT_OPERATION_FAILED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setMode(Mode mode)
{
    mOutputMode = mode;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ITxPort::Mode CommonTxPort::getMode()
{
    return mOutputMode;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setDigitalPowerScaler(float power)
{
    mDigitalPowerScaler = power;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
const Power CommonTxPort::getDigitalPowerScaler()
{
    return mDigitalPowerScaler;
}

//-------------------------------------------------------------------------------------------------------------
const Temperature CommonTxPort::getTemperature()
{
    if( mTempUpdated == false)
    {
        updateAvgTemp();
    }
    return mCurrentTemperature;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setCWPower(Power power)
{
    mCWPower = power;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonTxPort::getCWPower()
{
    return mCWPower;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::resetFifo()
{
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonTxPort::getFifoLevel()
{
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setDacDCOffset(int IOffset,  int QOffset)
{
	return ReturnType::RT_NOT_SUPPORTED;
}


//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setDacPhaseOffset(int IOffset,  int QOffset)
{
	return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setDacMagOffset(int IOffset,  int QOffset)
{
	return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::getDacDCOffset(int& IOffset, int& QOffset)
{
	return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::getDacPhaseOffset(int& IOffset, int& QOffset)
{
	return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::getDacMagOffset(int& IOffset, int& QOffset)
{
	return ReturnType::RT_NOT_SUPPORTED;
}



//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setDacIfOffset( double  MHzOffset )
{
	return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
double CommonTxPort::getDacIfOffset()
{
	return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::updatePowerData(Power &rfPower, int &rawAdcValue)
{
    return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setIFAttenuation(Power attn)
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> txIfAttn( devices.getTxIFAttenuator( index ) ) ;

    if (txIfAttn != nullptr)
    {
    	return txIfAttn->setAttenuation(attn);
    }

	return ReturnType::RT_OPERATION_FAILED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setRFAttenuation(Power attn)
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> txRfAttn( devices.getTxRFAttenuator( index ) ) ;

    if (txRfAttn != nullptr)
    {
    	return txRfAttn->setAttenuation(attn);
    }

	return ReturnType::RT_OPERATION_FAILED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setRFAttenuation(Power attn, Temperature temp)
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> txRfAttn( devices.getTxRFAttenuator( index ) ) ;

    if (txRfAttn != nullptr)
    {
    	return txRfAttn->setAttenuation(attn, temp);
    }

	return ReturnType::RT_OPERATION_FAILED;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonTxPort::getIFAttenuation()
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> txIfAttn( devices.getTxIFAttenuator( index ) ) ;

    if (txIfAttn != nullptr)
    {
    	return txIfAttn->getAttenuation();
    }

	return Power(96.6);
}

//-------------------------------------------------------------------------------------------------------------
Power CommonTxPort::getRFAttenuation()
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    const int index = (const int) getIndex();
    std::shared_ptr<IAttenuator> txRfAttn( devices.getTxRFAttenuator( index ) ) ;

    if (txRfAttn != nullptr)
    {
    	return txRfAttn->getAttenuation();
    }

	return Power(96.6);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setOpAttenPad( AttenPadState state )
{
    mPadState = state;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ITxPort::AttenPadState CommonTxPort::getOpAttenPad()
{
    return mPadState;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setLowPassFilter( LowPassFilterState state )
{
    mFilterState = state;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ITxPort::LowPassFilterState CommonTxPort::getLowPassFilter()
{
    return mFilterState;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setPowerDetCal( float coeff, float offset, float calPower )
{
    return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
int CommonTxPort::getAvgRawRfPower()
{
	return -1 ;
}

//-------------------------------------------------------------------------------------------------------------
int CommonTxPort::getRawRfPowerVariantion()
{
	return -1 ;
}

//-------------------------------------------------------------------------------------------------------------
int CommonTxPort::getRawRfPower()
{
	return -1 ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setRawRFAtten(unsigned int pwm)
{
    return ReturnType::RT_NOT_SUPPORTED;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonTxPort::hasPA()
{
    return false;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IPa> CommonTxPort::getPA()
{
    std::shared_ptr<IPa> pa(0);
    return pa;
}

//-------------------------------------------------------------------------------------------------------------
void CommonTxPort::updateAvgTemp()
{
	std::shared_ptr<IDevices> devices =  IDevicesFactory::create();
	std::shared_ptr<ITemperatureSensor> sensor( devices->getTxTemperatureSensor( 0 ) );

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
Power CommonTxPort::getExtFilterLoss()
{
    return mExtLoss;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setExtFilterLoss(Power filterLoss)
{
	// NOTE: Rely on the limits being enforced externally to this method (e.g. in TIF)
	mExtLoss = filterLoss;
	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
void CommonTxPort::setTxGain( float gain )
{
	mTxGain = gain;
}

//-------------------------------------------------------------------------------------------------------------
float CommonTxPort::getTxGain()
{
	return mTxGain;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonTxPort::setPath( int path )
{
	mExternalPathIndex = path;
	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
int CommonTxPort::getPath()
{
	return mExternalPathIndex;
}
