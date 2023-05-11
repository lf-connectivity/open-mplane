#ifndef _COMMONTXPORT_H_
#define _COMMONTXPORT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxPort.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <complex>

#include "Frequency.h"
#include "Power.h"
#include "Mutex.h"

#include "IFilter.h"
#include "ITxPort.h"
#include "ITxCalPort.h"
#include "CommonPort.h"
#include "MovingAvg.hpp"

namespace Mplane
{

class CommonTxPort: public ITxPort, public ITxCalPort, public CommonPort
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class CommonTxPortTestCase;

public:

    /*! \brief  The initialise method
     *
     *  Method called during system startup for the common TX port initialisation
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() override ;

    /*! \brief  Set the port NCO frequency
     *
     *  Used to set the NCO frequency
     *
     *  \param frequency  the frequency to set
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setFrequency(const Frequency& frequency) override ;

    /*! \brief  Set the port synthesiser frequency (does no other calibrations)
     *
     *  Used to set the NCO frequency
     *
     *  \param frequency  the frequency to set
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setSynth(const Frequency& frequency) override ;

    /*! \brief  Get the tx path frequency
     *
     *  Return the frequency in kHz that the carrier has requested synthesiser be set to.
     *
     *  \return the carrier frequency, in kHz
     */
    virtual const Frequency getFrequency() override;

    /*! \brief  Get the synthesiser frequency
     *
     *  Return the frequency in kHz that the synthesiser has been set to.
     *  In some schemes this may be different to carrier frequency.
     *	e.g. avoiding a bad IBS frequency by shifting LO and compensating with NCOs
     *
     *  \return the synthesiser frequency, in kHz
     */
    virtual const Frequency getSynthFrequency() override;

	/**
	 * Check if the frequency is a bad IBS frequency
	 *
	 * @return true if it is a bad IBS frequency
	 */
    virtual bool isBadIbsFreq( Frequency frequency ) override;

    /**
     * \brief Get the temperature in Deg C associated with this port
     *
     * Used to read the temperature associated with the port.
     *
     * \return Temperature value in degrees Celcius
     */
    virtual const Temperature getTemperature() override ;


    /*! \brief  Turn the transmitter on
     *
     *  Method used to turn on the transmitter for this port.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setTxOn(void) override ;

    /*! \brief  Turn the transmitter off
     *
     *  Method used to turn off the transmitter for this port.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setTxOff(void) override ;

    /*! \brief  Is the transmitter on
     *
     *  \return true if Tx is on, false if not.
     */
    virtual bool isTxOn(void) override ;

    /**
     * This method is used to set the RF output at the radios transmitter output. It uses
     * the power value supplied and along with the current transmit frequency uses this
     * data to retrieve a suitable setting for the transmit path attenuators.
     *
     * Any small differences in the absolute required power, compared to that achievable
     * through the attenuators is compensated for using a final digital scalar.
     *
     * data to look up
     * @param power
     * @return RT_OK if set OK, RT_NOT_INITIALISED if no calibration data is available.
     */
    virtual ReturnType::State setRadioOutputPower( Power &power );


    /**
     * \brief Return the most recent correlated digital and rf power readings
     *
     * Method returns a copy of the last power reading for this path in the digital
     * domain and the antenna output RF power. These power readings are updated at the same
     * time so as to be correlated to the same power control group.
     *
     * @param forward a reference to the measure power at PCG N in the forward path
     * @param digital a reference to the digital power at PCG N
     * @return state RT_OK is successful, some other RT_ return code is failed.
     */
    virtual ReturnType::State getFwdPower( Power &forward, Power &digital ) override ;

    /**
     * \brief Return the most recent correlated digital and rf reverse power readings
     *
     * Method returns a copy of the last reverse power reading for this path in the digital
     * domain and the antenna output RF power. These power readings are updated at the same
     * time so as to be correlated, this allows VSWR monitor to validate return loss
     * calculation.
     *
     * @param reverse a reference to the measure power at PCG N in the reverse path
     * @param digital a reference to the digital power at PCG N
     * @return state RT_OK is successful, some other RT_ return code is failed.
     */
    virtual ReturnType::State getRevPower( Power &reverse, Power &digital ) override;


    /**
     * \brief Used to set the measured instantaneous digital and rf power
     *
     * This method is called by the service that performs the radio transmit
     * power measurements to store the latest readings ino the TX port object.
     *
     * @param forward rf power reading
     * @param reverse rf power reading used in VSWR tests
     * @param digital a reference to digital power asssociated with the rf power
     * @return state RT_OK is successful, some other RT_ return code is failed.
     */
//    virtual ReturnType::State updatePowerReadings(Power &forward, Power &digital ) override ;

    /**
     * @brief Return the target power for this transmit path
     *
     * Method returns the current target power as defined by the customers
     * carrier configuration, this power is set by the Carrier Manager.
     *
     * @return the target power for this transmit port
     */
    virtual Power getTargetPower() override ;

    /**
     * @brief Set the target transmit power for this port
     *
     * Method called by the carrier manager to set the required transmit
     * power for this transmit port.
     *
     * @param targetPower
     * @return state RT_OK is successful, some other RT_ return code is failed.
     */
    virtual ReturnType::State setTargetPower(Power targetPower ) override ;

    /**
     * @brief Return the external filter loss for this TX path
     *
     * Method returns the current external filter loss that is added to the
     * target power on systems that are calibrated to the PA output, without
     * a filter/duplexer.
     *
     * @return the transmit port filter loss - defaults to 0.0 dB
     */
    virtual Power getExtFilterLoss() override;

    /**
     * @brief Set the external filter loss for this TX path
     *
     * Method used to set the external filter/duplexer losses
     * for this transmit port.
     *
     * @param filterLoss
     * @return state RT_OK is successful, some other RT_ return code if failed.
     */
    virtual ReturnType::State setExtFilterLoss(Power filterLoss ) override;


    /*! \brief Method to retrieve the Max Transmit Power in Watts
     *
     * \return Max Power capability in Watts
     */
    virtual Power getMaxPower(void) override ;

    /*! \brief Method to retrieve the Max Frequency Dependent Transmit Power for the port, The power
     * class returned can be used to express Watts or dBm.  This is for products where max power
     * depends on frequency.
     *
     * \return Max Power capability
     */
    virtual Power getMaxFreqDepPower(void) override;

    /*! \brief Method to retrieve the Min Transmit Power for the port, The power
     * class returned can be used to express Watts or dBm
     *
     * \return Min Power capability
     */
    virtual Power getMinPower(void) override ;

    /*! \brief Method to retrieve the Min Frequency Dependent Transmit Power for the port, The power
     * class returned can be used to express Watts or dBm.  This is for products where min power
     * depends on frequency.
     *
     * \return Min Power capability
     */
    virtual Power getMinFreqDepPower(void) override;

    /*! \brief Method to retrieve the maximum rms power that the PA should ever be set to for the port, The power
     * class returned can be used to express Watts or dBm
     *
     * \return Max Power capability
     */
    virtual Power getMaxPaPower(void) override ;

    /*! \brief  Set the adjustable transmit delay for this port
     *
     *  Method to set the adjustable transmit delay for this port.
     *  This is expected to be done once during hardware initialisation and
     *  then the real delay is calculated and adjusted under control of a
     *  downlink delay controlling function.
     *
     *  \param  delay   the required delay, in ns
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setTxDelay(UINT32 delay) override ;


    /**
     * Set the output play mode between modulated data or carrier wave test tone.
     * @param mode
     * @return RT_OK if mode correctly set, otherwise RT_ERROR
     */
    virtual ReturnType::State setMode( Mode mode ) override ;

    /**
     * Return the state of the current output test mode.
     *
     * @return Mode::MOD is the default modulated output signal Mode::CW_TEST when a CW tone is being output.
     *
     */
    virtual Mode getMode() override ;


    /**
     * This method is used to scale the digital power, from either the modulated output
     * data or CW test tone from a unity value.
     *
     * @param power the dBFS value for the output
     * @return RT_OK is mode and power set successfully.
     */
    virtual ReturnType::State setDigitalPowerScaler( float power ) override ;


    /**
     * Method returns the the last set CW test tone power level in DbFS or the last
     * modulated digital power adjustment, depending on the current Tx output mode.
     *
     * @return last set CW test tone power or modulated digital power adjustment..
     */
    virtual const Power getDigitalPowerScaler() override ;


    /**
     * Used to set the CW test tone power.
     *
     * @param power
     * @return RT_OK is set successfully
     */
    virtual ReturnType::State setCWPower( Power power ) override ;

    /**
     * Method used to return the value of the last set CW test tone power.
     *
     * @return the last set CW power.
     */
    virtual Power getCWPower() override ;

    /**
     * Method used to set the attenuation for the  transmit path. When called with
     * AttenuatorMode set to ABSOLUTE, the internal algorithm attempt to set the transmit
     * path power as best it can to the given power value.
     *
     * With the AttenuatorMode set to ERROR, the power indicates an error adjustment and the
     * algorithm of the implementation attempts to change the transmit path by the given amount
     * from the previous absolute value.
     *
     * @param power value to be set.
     * @return
     */
    virtual ReturnType::State setAttenuation( Power power ) override ;

    /**
     * Method used to retrieve the current internal power value being used by the transmit
     * path attenuation implementation.
     * @return current transmit path attenuation power.
     */
    virtual Power getAttenuation() override ;

    /**
     * This method is provided in the common TX port base class simply to store
     * the IF attenuation setting so that it can be recalled by the getIFAttenuation method.
     *
     * The actual attenuator setting  is provided by hardware specific implementations
     * that sit above this class.
     *
     * @param attn
     * @return RT_OK is successful otherwise an appropriate error status.
     */
    virtual ReturnType::State setIFAttenuation( Power attn ) override ;

    /**
     * This method is provided in the common TX port base class simply to store
     * the RF attenuation setting so that it can be recalled by the getRFAttenuation method.
     *
     * The actual attenuator setting  is provided by hardware specific implementations
     * that sit above this class.
     *
     * @param attn
     * @return RT_OK is successful otherwise an appropriate error status.
     */
    virtual ReturnType::State setRFAttenuation( Power attn ) override ;

    /**
     * This method is provided in the common TX port base class simply to store
     * the RF attenuation setting so that it can be recalled by the getRFAttenuation method.
     *
     * The actual attenuator setting  is provided by hardware specific implementations
     * that sit above this class.
     *
     * @param attn
     * @param temp
     * @return RT_OK is successful otherwise an appropriate error status.
     */
    virtual ReturnType::State setRFAttenuation( Power attn, Temperature temp ) override ;


    /**
     * Return the currently set IF attenuation value.
     *
     * @see Mplane::CommonTxPort::setIFAttenuation()
     *
     * @return attenuation in dB
     */
    virtual Power getIFAttenuation() override ;

    /**
     * Return the currently set RF attenuation value
     *
     * @see Mplane::CommonTxPort::setRFAttenuation()
     *
     * @return attenuation in dB
     */
    virtual Power getRFAttenuation() override ;

    /**
     * This method is used to set the attenuation pad on the output of
     * the RF section of the radio either on or off.
     * @param attn
     * @return RT_OK is successful otherwise an appropriate error status.
     */
    virtual ReturnType::State setOpAttenPad( AttenPadState state ) override ;

    /**
     * Return the currently state of the output attenuation pad
     * @return pad state
     */
    virtual ITxPort::AttenPadState getOpAttenPad() override ;

    /**
     * This method is used to set the low pass filter of
     * the RF section of the radio either on or off.
     * @param attn
     * @return RT_OK is successful otherwise an appropriate error status.
     */
    virtual ReturnType::State setLowPassFilter( LowPassFilterState state ) override ;

    /**
     * Return the currently state of the low pass filter
     * @return filter state
     */
    virtual ITxPort::LowPassFilterState getLowPassFilter() override ;


    /*! \brief  Get the calibration frequency
     *
     *  Method to retrieve the calibration frequency. This is the base frequency
     *  at which the transmit path is calibrated.
     *
     *  The frequency returned is in units of kHz.
     *
     *  \return Tx port calibration frequency in kHz
     */
    virtual const Frequency getCalFrequency(void) const ;

    /**
     * Method used to call the DAC fifo reset function.
     * @return
     */
    virtual ReturnType::State resetFifo() override;

    /**
     * Method used to get the fifo level
     *
     * \return fifo level
     */
    virtual unsigned getFifoLevel() override ;

    /**
     * Set the DC Offset for the DAC associated with this Tx path instance
     *
     * @param IOffset
     * @param QOffset
     * @return RT_OK if set OK.
     */
    virtual ReturnType::State setDacDCOffset(int IOffset, int QOffset) override ;

    /**
     * Get the DC Offset for the DAC associated with this Tx path instance
     *
     * @param IOffset
     * @param QOffset
     * @return RT_OK if set OK.
     */
    virtual ReturnType::State getDacDCOffset(int& IOffset, int& QOffset) override ;

    /**
     * Set the Phase Offset for the DAC associated with this Tx path instance
     *
     * @param IOffset
     * @param QOffset
     * @return RT_OK if set OK.
     */
    virtual ReturnType::State setDacPhaseOffset(int IOffset, int QOffset) override ;

    /**
     * Get the Phase Offset for the DAC associated with this Tx path instance
     *
     * @param IOffset
     * @param QOffset
     * @return RT_OK if set OK.
     */
    virtual ReturnType::State getDacPhaseOffset(int& IOffset, int& QOffset) override ;

    /**
     * Set the DAC Amplitude Offset for the DAC associated with this Tx path instance
     *
     * @param IOffset
     * @param QOffset
     * @return RT_OK if set OK.
     */
    virtual ReturnType::State setDacMagOffset(int IOffset, int QOffset) override ;

    /**
     * Get the DAC Amplitude Offset for the DAC associated with this Tx path instance
     *
     * @param IOffset
     * @param QOffset
     * @return RT_OK if set OK.
     */
    virtual ReturnType::State getDacMagOffset(int& IOffset, int& QOffset) override ;

    /**
      * Method used to set the IF Offset by programming the DAC NCO
      * @return
      */
    virtual ReturnType::State setDacIfOffset( double  MHzOffset ) override;

    /**
      * Method used to get the IF Offset
      * @return
      */
    virtual double getDacIfOffset() override;

    /**
	 * This method can be implemented to make sure all power measurement data is updated
	 * at the same time. Subsequent uses of getXXXPower methods are then guaranteed
	 * to be correctly aligned. The implementation of this method is likely to vary
	 * between radio products.
	 *
	 * @param *rfPower
	 * @param *rawAdcValue
	 * @return RT_OK if update was performed, else RT_NOT_SUPPORTED.
	 */
	virtual ReturnType::State updatePowerData(Power &rfPower, int &rawAdcValue) override ;

   /**
     * Method used to update the calibration data associated with the output power-detector
     * @param coeff
     * @param offset
     * @param calPower
     * @return
     */
    virtual ReturnType::State setPowerDetCal( float coeff,
                                              float offset,
                                              float calPower ) override ;


    /**
     * Method used to measure the average power from the power detector.
     *
     * @return average RF power measured by the power detector.
     */
    virtual int getAvgRawRfPower() override ;

    /**
     * Method used to return the spread of the raw values in the RF power moving average.
     *
     * @return
     */
    virtual int getRawRfPowerVariantion() override ;

    /**
     * Method used to read the raw RF power ADC reading.
     * @return
     */
    virtual int getRawRfPower() override ;

    /**
     * Method used to set the RAW VVA attenuation using the pulse width modulation count value.
     * @param pwm
     */
    virtual ReturnType::State setRawRFAtten( unsigned int pwm ) override ;


    /**
     * Method returns true if this TX path supports an external output PA.
     *
     * @return true if external PA available, otherwise false.
     */
    virtual const bool hasPA() override;

    /**
     * If TX path has an external PA fitted this method return a shared pointer to an
     * appropriate implementation of the IPa interface.
     *
     * @return
     */
    virtual std::shared_ptr<IPa> getPA() override;


    /**
     * The radio updateTemperature method calls this method to update the
     * average temperature for this port.
     */
    virtual void updateAvgTemp();

    /*! \brief  Stores the port gain
     *
     *  This method stores the gain.
     *
     *  \param gain  the gain to set
     *
     *  \return nothing
     */
    virtual void setTxGain( float gain ) override;

    /*! \brief  Get the port gain
     *
     *  This method gets the gain.
     *
     *  \return gain
     */
    virtual float getTxGain() override;

    /**
     * Method used to manually set the external path connected to
     * the transmit port
     *
     * @param path 0 to N-1 supported external transmit paths
     * @return RT_OK if index is valid else RT_OUT_OF_RANGE
     */
    virtual ReturnType::State setPath( int path )  override;

    /**
     * Return the currently selected external transmit path.
     * @return 0 to N-1 path index values.
     */
    virtual int getPath() override;


    CommonTxPort( int index, char const* name);

    virtual ~CommonTxPort();


protected:
    /*! \brief  Low-level method to turn the transmitter on. Must be implemented by derived object
     *
     *  Method used to turn on the transmitter for this port.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setTxOnLowLevel(void)=0;

    /*! \brief  Low-level method to turn the transmitter off. Must be implemented by derived object
     *
     *  Method used to turn off the transmitter for this port.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setTxOffLowLevel(void)=0;

protected:
    Mutex       mMutex;
    int         mExternalPathIndex;
    bool        mTxOnState;
    AttenPadState   mPadState;
    LowPassFilterState  mFilterState;
    Power       mMaxPower;
    Power       mMinPower;
    Power       mMaxPaPower;
    Power       mForward;
    Power       mReverse;
    Power       mDigital;
    Power       mRevDigital;
    Power       mTargetPower;               //!> This holds the target output power for this port in dB
    Power       mExtLoss;                   //!> Optional external loss for the transmit path

    // Flag set when initialisation is required before the object will be in a valid state
    bool        mInitRequired ;
    Mode        mOutputMode;              //!> Used to record the current test mode state
    Power       mDigitalPowerScaler;
    Power       mCWPower;

    bool mTempUpdated;
    MovingAvg<float>  mTemperature;
    Temperature       mCurrentTemperature;   //!> The temperature value associated with this port
    Temperature       mPreviousTemperature;   //!> The temperature value associated with this port

    float mTxGain;	// The requested tx gain which gets converted to power based upon frequency.

};

} /* namespace Mplane */

#endif /* _COMMONTXPORT_H_ */
