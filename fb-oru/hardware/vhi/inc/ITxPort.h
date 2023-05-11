#ifndef _ITXPORT_H_
#define _ITXPORT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITxPort.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <memory>
#include "Observer.hpp"
#include <vector>
#include "IPort.h"
#include "IFrequencyChange.h"
#include "ITemperatureChange.h"

#include "GlobalTypeDefs.h"
#include "Frequency.h"
#include "Power.h"
#include "IPa.h"

#include "Observer.hpp"

/*
 * Forward class declarations
 */

namespace Mplane
{

class Frequency;

/**
 * The ITxPort interface provides access to all the functionality related
 * to the transmit path of the radio.
 *
 * It is independent of the actual physical radio implementation and can
 * therefore be used as a common interface into the functionality of the
 * radio port for any radio variant.
 *
 * The ITxPort also inherits from the common Subject template class
 * declaring itself as the subject matter. This allows any object to
 * become an observer of the Tx port, being notified of any changes
 * in the Tx port state, for example as the Tx port is turned on and
 * off.
 *
 * Here is some sample code of how to become an ITxPort Observer
 *
 * @code
 *
 * #include "ITxPort.h"
 * #include "Observer.hpp"
 *
 *
 * class MyTxPortStateObserver: public Observer<ITxPort>
 * {
 *
 * private:
 *   const char* mName;
 *   ITxPort& mTxPort;
 *   bool mTxState;
 *
 * public:
 *   MyTxPortStateObserver(ITxPort *txPort ):
 *       mName("TxPortObs"),
 *       mTxPort(*txPort),
 *       mTxState( false )
 *   {
 *       mTxPort.attach( *this );
 *   }
 *
 *   virtual ~MyTxPortStateObserver()
 *   {
 *       mTxPort.detach( *this );
 *   }
 *
 *   virtual void update(ITxPort& subject)
 *   {
 *       mTxState = subject.isTxOn();
 *   }
 *
 *   virtual const char* name() const
 *   {
 *       return mName;
 *   }
 *
 *   bool getTxState()
 *   {
 *       return mTxState;
 *   }
 *
 * };
 *
 * @endcode
 *
 *
 */
class ITxPort : public virtual IPort,
	public Subject<ITxPort>,
	public ITemperatureChange, public Subject<ITemperatureChange>,
	public IFrequencyChange, public Subject<IFrequencyChange>
{
public:

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() = 0;

    /*! \brief  Set the port NCO frequency
     *
     *  Used to set the NCO frequency
     *
     *  \param frequency  the frequency to set
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setFrequency(const Frequency& frequency) = 0;

    /*! \brief  Set the port synthesiser frequency (does no other calibrations)
     *
     *  Used to set the NCO frequency
     *
     *  \param frequency  the frequency to set
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setSynth(const Frequency& frequency) = 0;

    /*! \brief  Get the tx path frequency
     *
     *  Return the frequency in kHz that the carrier has requested synthesiser be set to.
     *
     *  \return the carrier frequency, in kHz
     */
    virtual const Frequency getFrequency() = 0;

    /*! \brief  Get the synthesiser frequency
     *
     *  Return the frequency in kHz that the synthesiser has been set to.
     *  In some schemes this may be different to carrier frequency.
     *	e.g. avoiding a bad IBS frequency by shifting LO and compensating with NCOs
     *
     *  \return the synthesiser frequency, in kHz
     */
    virtual const Frequency getSynthFrequency() = 0;

	/**
	 * Check if the frequency is a bad IBS frequency
	 *
	 * @return true if it is a bad IBS frequency
	 */
    virtual bool isBadIbsFreq( Frequency frequency ) = 0;

    /*! \brief  Turn the transmitter on
     *
     *  Method used to turn on the transmitter for this port.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setTxOn(void) = 0;

    /*! \brief  Turn the transmitter off
     *
     *  Method used to turn off the transmitter for this port.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setTxOff(void) = 0;

    /*! \brief  Is the transmitter on
     *
     *  \return true if Tx is on, false if not.
     */
    virtual bool isTxOn(void) = 0;


    /**
     * \brief Get the temperature in Deg C associated with this port
     *
     * Used to read the temperature associated with the port.
     *
     * \return Temperature value in degrees Celcius
     */
    virtual const Temperature getTemperature() = 0;


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
    virtual ReturnType::State setRadioOutputPower( Power &power ) = 0;


    /**
     * \brief Return the most recent correlated digital and rf forward power readings
     *
     * Method returns a copy of the last power reading for this path in the digital
     * domain and the antenna output RF power. These power readings are updated at the same
     * time so as to be correlated to the same power control group.
     *
     * @param forward a reference to the measured power at PCG N in the forward path
     * @param digital a reference to the digital power at PCG N
     * @return state RT_OK is successful, some other RT_ return code is failed.
     */
    virtual ReturnType::State getFwdPower( Power &forward, Power &digital ) = 0;

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
    virtual ReturnType::State getRevPower( Power &reverse, Power &digital ) = 0;

    /**
     * Method used to measure the average power from the power detector.
     *
     * @return average RF power measured by the power detector.
     */
    virtual Power getRfPower() = 0;


    /**
     * @brief Return the target power for this transmit path
     *
     * Method returns the current target power as defined by the customers
     * carrier configuration, this power is set by the Carrier Manager.
     *
     * @return the target power for this transmit port
     */
    virtual Power getTargetPower() = 0;

    /**
     * @brief Set the target transmit power for this port
     *
     * Method called by the carrier manager to set the required transmit
     * power for this transmit port.
     *
     * @param targetPower
     * @return state RT_OK is successful, some other RT_ return code if failed.
     */
    virtual ReturnType::State setTargetPower(Power targetPower ) = 0;

    /**
     * @brief Return the external filter loss for this TX path
     *
     * Method returns the current external filter loss that is added to the
     * target power on systems that are calibrated to the PA output, without
     * a filter/duplexer.
     *
     * @return the transmit port filter loss - defaults to 0.0 dB
     */
    virtual Power getExtFilterLoss() = 0;

    /**
     * @brief Set the external filter loss for this TX path
     *
     * Method used to set the external filter/duplexer losses
     * for this transmit port.
     *
     * @param filterLoss
     * @return state RT_OK is successful, some other RT_ return code if failed.
     */
    virtual ReturnType::State setExtFilterLoss(Power filterLoss ) = 0;


    /*! \brief Method to retrieve the Max Transmit Power for the port, The power
     * class returned can be used to express Watts or dBm
     *
     * \return Max Power capability
     */
    virtual Power getMaxPower(void) = 0;

    /*! \brief Method to retrieve the Max Frequency Dependent Transmit Power for the port, The power
     * class returned can be used to express Watts or dBm.  This is for products where max power
     * depends on frequency.
     *
     * \return Max Power capability
     */
    virtual Power getMaxFreqDepPower(void) = 0;

    /*! \brief Method to retrieve the Min Frequency Dependent Transmit Power for the port, The power
     * class returned can be used to express Watts or dBm.  This is for products where min power
     * depends on frequency.
     *
     * \return Min Power capability
     */
    virtual Power getMinFreqDepPower(void) = 0;

    /*! \brief Method to retrieve the Min Transmit Power for the port, The power
     * class returned can be used to express Watts or dBm
     *
     * \return Min Power capability
     */
    virtual Power getMinPower(void) = 0;

    /*! \brief Method to retrieve the maximum rms power that the PA should ever be set to for the port, The power
     * class returned can be used to express Watts or dBm
     *
     * \return Max Power capability
     */
    virtual Power getMaxPaPower(void) = 0;

    /*! \brief  Set the adjustable transmit delay for this port
     *
     *  Method to set the adjustable transmit delay for this port.
     *  This is expected to be done once during hardware initialisation and
     *  then the real delay is calculated and adjusted under control of a
     *  downlink delay controlling function in the application software.
     *
     *  \param  delay   the required delay, in ns
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setTxDelay(UINT32 delay) = 0;


    enum Mode
    {
        MODULATED,
        CW_TEST
    };

    /**
     * Set the output play mode between modulated data or carrier wave test tone.
     * @param mode
     * @return RT_OK if mode correctly set, otherwise RT_ERROR
     */
    virtual ReturnType::State setMode( Mode mode ) = 0;

    /**
     * Return the state of the current output test mode.
     *
     * @return Mode::MOD is the default modulated output signal Mode::CW_TEST when a CW tone is being output.
     *
     */
    virtual Mode getMode() = 0;


    /**
     * This method is used to scale the digital power, from either the modulated output
     * data or CW test tone from a unity value.
     *
     * @param power the dBFS value for the output
     * @return RT_OK is mode and power set successfully.
     */
    virtual ReturnType::State setDigitalPowerScaler( float power ) = 0;


    /**
     * Used to set the CW test tone power.
     *
     * @param power
     * @return RT_OK is set successfully
     */
    virtual ReturnType::State setCWPower( Power power ) = 0;

    /**
     * Method used to return the value of the last set CW test tone power.
     *
     * @return the last set CW power.
     */
    virtual Power getCWPower() = 0;

    /**
     * Method returns the the last set CW test tone power level in DbFS or the last
     * modulated digital power adjustment, depending on the current Tx output mode.
     *
     * @return last set CW test tone power or modulated digital power adjustment..
     */
    virtual const Power getDigitalPowerScaler() = 0;


    enum AttenuatorMode
    {
        ABSOLUTE,
        ERROR
    };

    /**
     * Method used to set the attenuation for the  transmit path using some
     * hardware implementation specific functionality.
     *
     * @param power value to be set.
     * @return
     */
    virtual ReturnType::State setAttenuation( Power power ) = 0;

    /**
     * Method used to retrieve the current transmit path attenuation.
     *
     * @return current transmit path attenuation power.
     */
    virtual Power getAttenuation() = 0;


    /**
     * This method is used to set the absolute attenuation value of the
     * attenuator in the IF section of the radio. The implementation is responsible
     * for converting the power in dbs to the low level device settings.
     * @param attn
     * @return RT_OK is successful otherwise an appropriate error status.
     */
    virtual ReturnType::State setIFAttenuation( Power attn ) = 0;

    /**
     * This method is used to set the absolute attenuation value of the
     * attenuator in the RF section of the radio. The implementation is responsible
     * for converting the power in dbs to the low level device settings.
     * @param attn
     * @return RT_OK is successful otherwise an appropriate error status.
     */
    virtual ReturnType::State setRFAttenuation( Power attn ) = 0;


    /**
     * This method is used to set the absolute attenuation value of the
     * attenuator in the RF section of the radio. The implementation is responsible
     * for converting the power in dbs to the low level device settings.
     * @param attn
     * @return RT_OK is successful otherwise an appropriate error status.
     */
    virtual ReturnType::State setRFAttenuation( Power attn, Temperature temp ) = 0;

    /**
     * Return the currently set IF attenuation value
     * @return attenuation in dB
     */
    virtual Power getIFAttenuation() = 0;

    /**
     * Return the currently set RF attenuation value
     * @return attenuation in dB
     */
    virtual Power getRFAttenuation() = 0;

    enum AttenPadState
    {
        PAD_OFF,
        PAD_ON
    };

    /**
     * This method is used to set the attenuation pad on the output of
     * the RF section of the radio either on or off.
     * @param attn
     * @return RT_OK is successful otherwise an appropriate error status.
     */
    virtual ReturnType::State setOpAttenPad( AttenPadState state ) = 0;

    /**
     * Return the currently state of the output attenuation pad
     * @return pad state
     */
    virtual AttenPadState getOpAttenPad() = 0;

    enum LowPassFilterState
    {
        FILTER_OFF,
        FILTER_ON
    };

    /**
     * This method is used to set the low pass filter of
     * the RF section of the radio either on or off.
     * @param attn
     * @return RT_OK is successful otherwise an appropriate error status.
     */
    virtual ReturnType::State setLowPassFilter( LowPassFilterState state ) = 0;

     /**
      * Return the currently state of the low pass filter
      * @return filter state
      */
     virtual LowPassFilterState getLowPassFilter() = 0;


     /**
      * Set the DC Offset for the DAC associated with this Tx path instance
      *
      * @param IOffset
      * @param QOffset
      * @return RT_OK if set OK.
      */
     virtual ReturnType::State setDacDCOffset(int IOffset, int QOffset) = 0;

     /**
      * Get the DC Offset for the DAC associated with this Tx path instance
      *
      * @param IOffset
      * @param QOffset
      * @return RT_OK if set OK.
      */
     virtual ReturnType::State getDacDCOffset(int& IOffset, int& QOffset) = 0;

    /**
     * Set the DAC Phase Offset for the DAC associated with this Tx path instance
     *
     * @param IOffset
     * @param QOffset
     * @return RT_OK if set OK.
     */
    virtual ReturnType::State setDacPhaseOffset(int IOffset, int QOffset) = 0;

    /**
     * Get the DAC Phase Offset for the DAC associated with this Tx path instance
     *
     * @param IOffset
     * @param QOffset
     * @return RT_OK if set OK.
     */
    virtual ReturnType::State getDacPhaseOffset(int& IOffset, int& QOffset) = 0;

    /**
     * Set the DAC Amplitude Offset for the DAC associated with this Tx path instance
     *
     * @param IOffset
     * @param QOffset
     * @return RT_OK if set OK.
     */
    virtual ReturnType::State setDacMagOffset(int IOffset, int QOffset) = 0;

    /**
     * Get the DAC Amplitude Offset for the DAC associated with this Tx path instance
     *
     * @param IOffset
     * @param QOffset
     * @return RT_OK if set OK.
     */
    virtual ReturnType::State getDacMagOffset(int& IOffset, int& QOffset) = 0;

    /**
      * Method used to set the IF Offset by programming the DAC NCO
      * @return
      */
     virtual ReturnType::State setDacIfOffset( double  MHzOffset ) = 0;

     /**
       * Method used to get the IF Offset
       * @return
       */
      virtual double getDacIfOffset() = 0;

    /**
     * This method can be implemented to make sure all power measurement data is updated
     * at the same time. Subsequent uses of getXXXPower methods are then guaranteed
     * to be correctly aligned. The implementation of this method is likely to vary
     * between radio products.
     *
     * @param *rfPower
     * @param *rawAdcValue
     * @return RT_OK if update was performed, else RT_NOT_SUPPORTED.
     *
     * @todo Remove this function and replace with updatePowerData() with no parameters.
     */
    virtual ReturnType::State updatePowerData(Power &rfPower, int &rawAdcValue) = 0;

    /**
     * Method used to call the DAC fifo reset function.
     * @return
     */
    virtual ReturnType::State resetFifo() = 0;

    /**
     * Method used to get the fifo level
     *
     * \return fifo level
     */
    virtual unsigned getFifoLevel() =0 ;

    /**
     * Method returns true if this TX path supports an external output PA.
     *
     * @return true if external PA available, otherwise false.
     */
    virtual const bool hasPA() = 0;

    /**
     * If TX path has an external PA fitted this method return a shared pointer to an
     * appropriate implementation of the IPa interface.
     *
     * @return
     */
    virtual std::shared_ptr<IPa> getPA() = 0;

    /*! \brief  Stores the port gain
     *
     *  This method stores the gain.
     *
     *  \param gain  the gain to set
     *
     *  \return nothing
     */
    virtual void setTxGain( float gain ) = 0;

    /*! \brief  Get the port gain
     *
     *  This method gets the gain.
     *
     *  \return gain
     */
    virtual float getTxGain() = 0;

    /**
     * Method used to manually set the external path connected to
     * the transmit port
     *
     * @param path 0 to N-1 supported external transmit paths
     * @return RT_OK if index is valid else RT_OUT_OF_RANGE
     */
    virtual ReturnType::State setPath( int path )  = 0;

    /**
     * Return the currently selected external transmit path.
     * @return 0 to N-1 path index values.
     */
    virtual int getPath() = 0;

    virtual ~ITxPort() {};

private:

    float mTxGain;	// The requested tx gain which gets converted to power based upon frequency.
};

/**
 * The ITxPortFactory is a polymorphic Tx port interface factory that allows a
 * specific radio implementation to set the number of Tx ports supported by
 * that particular hardware implementation, create the actual Tx port, again
 * specific to the radio implementation and return them as a vector that is
 * stored in the common radio implementation.
 *
 * @note This factory must be implemented by each radio type where its physical
 * characteristics have nothing in common with any existing implementation.
 */
class ITxPortFactory
{
public:
    /**
     * This interface must be implemented by each radio implementation
     * type. The caller passes in a variable by reference that will be used to
     * return the number of ports created. The return value, is a vector of
     * pointers to the common ITxPort interface.
     *
     * Any radio specific implementation code that is aware of the actual Tx port
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * \param maxPorts a reference to a variable that is used to return the number of ports
     * \return a vector containing maxPorts Rx ports interface pointers.
     */
    static std::vector< std::shared_ptr<ITxPort> > createPorts( int &maxPorts );

    /**
     * This interface must be implemented by each radio implementation
     * type. Returns a previous created list of ports. The return value, is a vector of
     * pointers to the common ITxPort interface.
     *
     * Any radio specific implementation code that is aware of the actual Tx port
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * \return a vector containing maxPorts Rx ports interface pointers.
     */
    static std::vector< std::shared_ptr<ITxPort> > getPorts( );
};



} /* namespace Mplane */

#endif /* _ITXPORT_H_ */
