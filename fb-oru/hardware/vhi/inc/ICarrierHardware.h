#ifndef _ACE_AXIS_ICARRIERHARDWARE_H_
#define _ACE_AXIS_ICARRIERHARDWARE_H_

#include <string>
#include <memory>
#include <vector>

#include "Frequency.h"
#include "Power.h"

#include "ICarrier.h"
#include "ICarrierHardwareTypes.h"
#include "IHardwareSettings.h"


/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrierHardware.h
 * \brief     Interface for hardware-specific carrier values
 *
 *
 * \details   Defines an interface to hardware specific data for a single carrier
 *
 */

namespace Mplane
{

/*! @brief  Carrier Hardware interface
 *
 * The concrete class derived from this interface will convert the generic carrier data into hardware specific values
 * and handle updating the hardware as carrier settings change. The concrete class will have a reference to it's associated
 * ICarrier so that it has access to all of the carrier methods to read the current settings.
 *
 */
class ICarrierHardware
{
public:

	/** @brief constructor
	 *
	 * Expected to be created with an actual ICarrier containing the common interface settings. Will use the
	 * ICarrier index
	 *
	 * @param carrier
	 */
    ICarrierHardware(const ICarrier *carrier = 0){};

    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~ICarrierHardware() {} ;

    /*! @brief  Get carrier
     *
     * Return a reference to this carrier hardware's ICarrier
     * @return reference to ICarrier
     */
    virtual const ICarrier& getCarrier() const = 0 ;

    /*! @brief  Validate the carrier change
     *
     *  Ensure this worker is happy with the proposed carrier change
     * @param carrier new carrier reference
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool validateChange(const ICarrier& carrier) = 0 ;

    /*! @brief  Carrier changed notification
     *
     *  Given a changed hardware-independent carrier instance, update it's values.
     *  NOTE: Does *not* affect the hardware in any way
     * @param carrier new carrier reference
     * @return false if cannot accept the carrier settings
     */
    virtual bool carrierChange(const ICarrier &carrier) = 0 ;

    /*! @brief  Have any settings change
     *
     * Method that indicates whether any settings in the carrier have changed. This indication will clear when
     * postUpdate() method is called.
     * @return true is settings have changed
     */
    virtual const bool isChanged() const = 0 ;

    /*! @brief  About to apply changes to hardware
     *
     * Called just prior to calling the updateHardware() method. Allows carrier to disable anything
     * that might affect the TX while changing setting (for example)
     * @return false if cannot accept the carrier settings
     */
    virtual bool preUpdate() = 0 ;

    /*! @brief  Apply changes to hardware
     *
     * Called after Mplane::ICarrier::carrierChange() to actively apply the changed values to the hardware
     * @return false if cannot accept the carrier settings
     */
    virtual bool updateHardware() = 0 ;

    /*! @brief  Have just applied changes to hardware
     *
     * Called just after calling the updateHardware() method. Allows carrier to re-enable anything previously
     * disabled
     * @return false if cannot accept the carrier settings
     */
    virtual bool postUpdate() = 0 ;

    /*! @brief  All changes are complete
     *
     * Called after postUpdate() to indicate that all changes have been completed
     */
    virtual void changeComplete() = 0 ;

    /*! @brief  Get failure reason
     *
     *  If a method fails, then this method will return a
     *  string describing the reason for failure
     * @return string containing reason for failure, or empty string if no fail
     */
    virtual std::string failReason(void) = 0 ;

    /**
     * @brief Print out contents of carrier to stdout
     * Used for debug only
     */
    virtual void showCarrier(std::ostream& os = std::cout) const = 0 ;

    /**
     * @brief Print out all register settings related to this carrier
     * Used for debug only
     */
    virtual void showDiag(std::ostream& os = std::cout) const = 0 ;

    /**
     * @brief Get CarrierHardware power
     * Get the CarrierHardware target power. Initially this will be the same as the Carrier power, but may be adjusted
     * for hardware reasons
     * @param txpath antenna number
     * @return power
     */
    virtual Power getPower(unsigned txpath) const = 0 ;

    /**
     * @brief Get Carrier BW as a frequency
     * @return BW frequency
     */
    virtual Frequency getChbwFreq() const =0 ;

    /**
     * @brief Get CarrierHardware min TX frequency
     * Get the CarrierHardware minimum TX frequency (normally: centre frequency - CHBW/2)
     * @return frequency
     */
    virtual Frequency getMinTxFreq() const = 0 ;

    /**
     * @brief Get CarrierHardware max TX frequency
     * Get the CarrierHardware maximum TX frequency (normally: centre frequency + CHBW/2)
     * @return frequency
     */
    virtual Frequency getMaxTxFreq() const = 0 ;

    /**
     * @brief Get CarrierHardware downlink delay
     * Get the CarrierHardware downlink delay
     * @return delay
     */
    virtual unsigned getDlDelay( unsigned antenna ) const = 0 ;

    /**
     * @brief Get CarrierHardware uplink delay
     * Get the CarrierHardware uplink delay
     * @return delay
     */
    virtual unsigned getUlDelay( unsigned antenna ) const = 0 ;

    /**
      * @brief Get CarrierHardware uplink additional delay
      * Get the CarrierHardware uplink additional delay
      * @return delay
      */
     virtual unsigned getUlAdditionalDelay( unsigned antenna ) const = 0 ;

     /**
      * Get the centre TX frequency
      * @return frequency
      */
     virtual Frequency getTxFreq() const =0 ;

    /**
     * @brief Resynchronise the UL stream used for this carrier, on this path (if the carrier is enabled)
     * @param path Antenna port number
     * @return false if any parameters/settings are invalid
     */
    virtual bool resyncUlStream( unsigned path ) = 0 ;

    /**
     * @brief Resynchronise the DL stream used for this carrier, on this path (if the carrier is enabled)
     * @param path Antenna port number
     * @return false if any parameters/settings are invalid
     */
    virtual bool resyncDlStream( unsigned path ) = 0 ;

    /**
     * Used to update the ICarrierHardware when a TX port centre frequency change has been detected
     * @param antenna			TX port (0-based)
     * @param newTxFrequency	The new TX centre frequency
     */
    virtual bool txFrequencyChange(unsigned antenna, const Frequency& newTxFrequency) =0 ;

    /**
     * Used to update the ICarrierHardware when a RX port centre frequency change has been detected
     * @param antenna			RX port (0-based)
     * @param newRxFrequency	The new RX centre frequency
     */
    virtual bool rxFrequencyChange(unsigned antenna, const Frequency& newRxFrequency) =0 ;

    /**
     * Read the carrier-based RSSI on this RX port
     * @param antenna			RX port (0-based)
     * @param rssi				Set to carrier rssi on success
     * @return true if read rssi ok; false and error string set otherwise
     */
    virtual bool getRssi(unsigned antenna, Power& rssi) const =0 ;

	/**
	 * Low-level method for setting a new UL NCO value
	 * @param offset
	 * @param chainIq
	 */
	static void changeUlNco(const FrequencyOffset& offset, unsigned chainIq) ;

	/**
	 * Low-level method for setting a new DL NCO value
	 * @param offset
	 * @param chainIq
	 */
	static void changeDlNco(const FrequencyOffset& offset, unsigned chainIq) ;


protected:

    /*! @brief  Set change flag
     *
     *  Object utility that sets the flag marking changes in the carrier settings
     */
    virtual void settingsChanged(void) = 0 ;

};


/*! @brief  Carrier Hardware list interface
 *
 *  Performs calculations on aggregates of carriers. For example a summary can be made of all currently active carriers
 *  on a particular antenna by iterating through this list of carriers. Note that the concrete class derived from this interface
 *  will only provide the iteration method, the actual summary method will be provided by (for example) the CarrierHardware
 *  class.
 *
 */
class ICarrierHardwareList
{

public:

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of this object within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<ICarrierHardwareList> getInstance(void);

    /*! @brief  Add a carrier to the list
     *
     *  Given the hardware-independent carrier instance, creates a hardware dependent
     *  carrier to calculate the hardware-specific settings
     * @param carrier new carrier reference
     * @return false if cannot accept the carrier settings
     */
    virtual bool addCarrier(const ICarrier &carrier) = 0 ;

    /*! @brief  Validate the carrier change
     *
     *  Ensure this worker is happy with the proposed carrier change
     * @param carrier new carrier reference
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool validateChange(const ICarrier& carrier) = 0 ;

    /*! @brief  Carrier changed notification
     *
     *  Given a changed hardware-independent carrier instance, gets the hardware-specific
     *  carrier to update it's values
     * @param carrier new carrier reference
     * @return false if cannot accept the carrier settings
     */
    virtual bool carrierChange(const ICarrier &carrier) = 0 ;

    /*! @brief  About to apply changes to hardware
     *
     * Called just prior to calling the updateHardware() method. Allows carrier to disable anything
     * that might affect the TX while changing setting (for example)
     * @param carrier new carrier reference (used to tell method what carrier changes have taken place)
     * @return false if cannot accept the carrier settings
     */
    virtual bool preUpdate() = 0 ;

    /*! @brief  Apply changes to hardware
     *
     * Called after carrierChange() to actively apply the changed values to the hardware
     * @return false if cannot accept the carrier settings
     */
    virtual bool updateHardware() = 0 ;

    /*! @brief  Have just applied changes to hardware
     *
     * Called just after calling the updateHardware() method. Allows carrier to re-enable anything previously
     * disabled
     * @return false if cannot accept the carrier settings
     */
    virtual bool postUpdate() = 0 ;

    /*! @brief  All changes are complete
     *
     * Called after postUpdate() to indicate that all changes have been completed
     */
    virtual void changeComplete() = 0 ;


    /** @brief  Get a carrier hardware object from the list
     *
     * @param index		carrier index
     * @return carrier hardware pointer or NULL
     */
    virtual ICarrierHardware* getCarrierHardware(const unsigned index) = 0 ;

    /** @brief  Get a carrier object from the list (uses carrier hardware getCarrier() method)
     *
     * @param index		carrier index
     * @return carrier reference
     */
    virtual const ICarrier& getCarrier(const unsigned index) const = 0 ;


    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~ICarrierHardwareList() {} ;

    /*! @brief  Get failure reason
     *
     *  If a method fails, then this method will return a
     *  string describing the reason for failure
     * @return string containing reason for failure, or empty string if no fail
     */
    virtual std::string failReason(void) = 0 ;

    /**
     * @brief Return the size of the list
     * @return number of CarrierHardware objects in list
     */
    virtual unsigned size(void) const = 0 ;

    /**
     * @brief Return boolean stating whether list is empty or not
     * @return true if empty
     */
    virtual bool empty(void) const = 0 ;

    /**
     * @brief Print out contents of carrier list to stdout
     * Used for debug only
     */
    virtual void showCarriers(std::ostream& os = std::cout) const = 0 ;

    /**
     * Returns the list of CarrierHardware pointers
     */
    virtual std::vector<ICarrierHardware*> getList() =0 ;

protected:

    /**
     *
     */
    ICarrierHardwareList(){};

};


class ICarrierHardwareData {
public:

	virtual ~ICarrierHardwareData() {}


	/**
	 * Get the singleton instance
	 */
	static std::shared_ptr<ICarrierHardwareData> getInstance() ;

	/**
	 * Reload the data from the fpga (mainly used for testbenches)
	 */
	virtual void reload() =0 ;

	/**
	 * Convert carrier type into an air standard
	 */
	virtual const ICarrierHardwareTypes::AirstdType getAirStd(ICarrier::Type carrType) =0 ;

	/**
	 * Convert carrier type into a channel bandwidth
	 */
	virtual const ICarrierHardwareTypes::ChbwType getChbw(ICarrier::Type carrType) =0 ;

	/**
	 * Get sample rate from airstd/chbw
	 */
	virtual const ICarrierHardwareTypes::SampleRate* getSampleRate(IHardwareSettings::dspclk_type dspclk,
			ICarrierHardwareTypes::AirstdType airstd, ICarrierHardwareTypes::ChbwType chbw) =0 ;

	/**
	 * Get the buffer delay from the airstd/chbw and buffer size (in k). Returns delay in ns
	 */
	virtual unsigned calcBuffDelay(IHardwareSettings::dspclk_type dspclk,
			ICarrierHardwareTypes::AirstdType airstd, ICarrierHardwareTypes::ChbwType chbw, unsigned bufferSize) =0 ;

	/**
	 * Get the sample delay from the airstd/chbw and number of samples. Returns delay in ns
	 */
	virtual unsigned calcSampleDelay(IHardwareSettings::dspclk_type dspclk,
			ICarrierHardwareTypes::AirstdType airstd, ICarrierHardwareTypes::ChbwType chbw, unsigned numSamples) =0 ;

	/**
	 * Get UL gain compensation from airstd/chbw
	 */
	virtual const Power getUlGainCompensation(ICarrierHardwareTypes::AirstdType airstd,
			ICarrierHardwareTypes::ChbwType chbw) =0 ;


    /**
     * Read the TDD DwPTS (Downlink Pilot Time Slot) based on the carrier settings
     * @param spsuConfig - Special subframe config
     * @param ulPrefixLen - Uplink Cyclic Prefix Length (normal/extended)
     * @param dlPrefixLen - Downlink Cyclic Prefix Length (normal/extended)
     * @return DwPTS
     */
    virtual unsigned getDwPTS(unsigned spsuConfig, ICarrier::CyclicPrefixLenType ulPrefixLen, ICarrier::CyclicPrefixLenType dlPrefixLen) const = 0;

    /**
     * Read the TDD UpPTS (Uplink Pilot Time Slot) based on the carrier settings
     * @param spsuConfig - Special subframe config
     * @param ulPrefixLen - Uplink Cyclic Prefix Length (normal/extended)
     * @param dlPrefixLen - Downlink Cyclic Prefix Length (normal/extended)
     * @return UpPTS
     */
    virtual unsigned getUpPTS(unsigned spsuConfig, ICarrier::CyclicPrefixLenType ulPrefixLen, ICarrier::CyclicPrefixLenType dlPrefixLen) const = 0;

    /**
     * Read the TDD alpha parameter based on the carrier settings
     * @return alpha
     */
    virtual unsigned getAlpha(unsigned uldlconfig) const = 0;

    /**
     * Read the TDD beta parameter based on the carrier settings
     * @return beta
     */
    virtual unsigned getBeta(unsigned uldlconfig) const = 0;

    /**
     * Get channel frequency from bandwidth
     * @return beta
     */
    virtual Frequency chbwTypeToFreq(ICarrierHardwareTypes::ChbwType chbwType) const = 0;

};


}

#endif /* _ACE_AXIS_ICARRIERHARDWARE_H_ */
