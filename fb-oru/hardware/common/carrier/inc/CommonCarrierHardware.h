#ifndef _ACE_AXIS_COMMONCARRIERHARDWARE_H_
#define _ACE_AXIS_COMMONCARRIERHARDWARE_H_

#include <vector>
#include <string>
#include <memory>

#include "ICarrierHardware.h"
#include "ICarrierFail.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierHardware.h
 * \brief     Common methods for carrier hardware
 *
 *
 * \details   Defines the generic methods used to implement carrier hardware class
 *
 */

namespace Mplane
{

class CommonCarrierHardware : public virtual ICarrierHardware
{
public:

    /**
     * constructor
     * @param carrier pointer to carrier related to this hardware
     */
	explicit CommonCarrierHardware(const ICarrier *carrier);

    /**
     * (default) constructor
     * Creates an object with no carrier (used for summaries)
     */
    CommonCarrierHardware();

    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~CommonCarrierHardware() ;

    /*! @brief  Validate the carrier change
     *
     * Return a reference to this carrier hardware's ICarrier
     * @return reference to ICarrier
     */
    virtual const ICarrier& getCarrier() const override ;

    /*! @brief  Validate the carrier change
     *
     *  Ensure this worker is happy with the proposed carrier change
     * @param carrier new carrier reference
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool validateChange(const ICarrier& carrier) override ;

    /*! @brief  Carrier changed notification
     *
     *  Given a changed hardware-independent carrier instance, update it's values.
     *  NOTE: Does *not* affect the hardware in any way
     * @param carrier new carrier reference
     * @return false if cannot accept the carrier settings
     */
    virtual bool carrierChange(const ICarrier &carrier) override ;

    /*! @brief  Have any settings change
     *
     * Method that indicates whether any settings in the carrier have changed. This indication will clear when
     * postUpdate() method is called.
     * @return true is settings have changed
     */
    virtual const bool isChanged() const override ;

    /*! @brief  About to apply changes to hardware
     *
     * Called just prior to calling the updateHardware() method. Allows carrier to disable anything
     * that might affect the TX while changing setting (for example)
     * @return false if cannot accept the carrier settings
     */
    virtual bool preUpdate() override ;

    /*! @brief  Apply changes to hardware
     *
     * Called after Mplane::ICarrier::carrierChange() to actively apply the changed values to the hardware
     * @return false if cannot accept the carrier settings
     */
    virtual bool updateHardware() override ;

    /*! @brief  Have just applied changes to hardware
     *
     * Called just after calling the updateHardware() method. Allows carrier to re-enable anything previously
     * disabled
     * @return false if cannot accept the carrier settings
     */
    virtual bool postUpdate() override ;

    /*! @brief  All changes are complete
     *
     * Called after postUpdate() to indicate that all changes have been completed
     */
    virtual void changeComplete() override ;



    /*! @brief  Get failure reason
     *
     *  If a method fails, then this method will return a
     *  string describing the reason for failure
     * @return string containing reason for failure, or empty string if no fail
     */
    virtual std::string failReason(void) override ;

    /**
     * @brief Print out contents of carrier to stdout
     * Used for debug only
     */
    virtual void showCarrier(std::ostream& os = std::cout) const override ;

    /**
     * @brief Print out all register settings related to this carrier
     * Used for debug only
     */
    virtual void showDiag(std::ostream& os = std::cout) const override ;

    /**
     * @brief Get CarrierHardware power
     * Get the CarrierHardware target power. Initially this will be the same as the Carrier power, but may be adjusted
     * for hardware reasons
     * @param txpath antenna number
     * @return power
     */
    virtual Power getPower(unsigned txpath) const override ;

    /**
     * @brief Get CarrierHardware min TX frequency
     * Get the CarrierHardware minimum TX frequency (normally: centre frequency - CHBW/2)
     * @return frequency
     */
    virtual Frequency getMinTxFreq() const override ;

    /**
     * @brief Get CarrierHardware max TX frequency
     * Get the CarrierHardware maximum TX frequency (normally: centre frequency + CHBW/2)
     * @return frequency
     */
    virtual Frequency getMaxTxFreq() const override ;

    /**
     * @brief Get CarrierHardware downlink delay
     * Get the CarrierHardware downlink delay
     * @return delay
     */
    virtual unsigned getDlDelay( unsigned antenna ) const override;

    /**
     * @brief Get CarrierHardware uplink delay
     * Get the CarrierHardware uplink delay
     * @return delay
     */
    virtual unsigned getUlDelay( unsigned antenna ) const override;

    /**
     * @brief Get CarrierHardware uplink additional delay
     * Get the CarrierHardware uplink additional delay
     * @return delay
     */
    virtual unsigned getUlAdditionalDelay( unsigned antenna ) const override;

    /**
     * @brief Resynchronise the UL stream used for this carrier, on this path (if the carrier is enabled)
     * @param path Antenna port number
     * @return false if any parameters/settings are invalid
     */
    virtual bool resyncUlStream( unsigned path ) override ;

    /**
     * @brief Resynchronise the DL stream used for this carrier, on this path (if the carrier is enabled)
     * @param path Antenna port number
     * @return false if any parameters/settings are invalid
     */
    virtual bool resyncDlStream( unsigned path ) override ;

    /**
     * Used to update the ICarrierHardware when a TX port centre frequency change has been detected
     * @param antenna			TX port (0-based)
     * @param newTxFrequency	The new TX centre frequency
     */
    virtual bool txFrequencyChange(unsigned antenna, const Frequency& newTxFrequency) override ;

    /**
     * Used to update the ICarrierHardware when a RX port centre frequency change has been detected
     * @param antenna			RX port (0-based)
     * @param newRxFrequency	The new RX centre frequency
     */
    virtual bool rxFrequencyChange(unsigned antenna, const Frequency& newRxFrequency) override ;

    /**
     * Read the carrier-based RSSI on this RX port
     * @param antenna			RX port (0-based)
     * @param rssi				Set to carrier rssi on success
     * @return true if read rssi ok; false and error string set otherwise
     */
    virtual bool getRssi(unsigned antenna, Power& rssi) const override ;

    /**
     * Get the centre TX frequency
     * @return frequency
     */
    virtual Frequency getTxFreq() const override ;

    /**
     * @brief Get Carrier BW as a frequency
     * @return BW frequency
     */
    virtual Frequency getChbwFreq() const override ;


protected:

    /*! @brief  Set change flag
     *
     *  Object utility that sets the flag marking changes in the carrier settings
     */
    virtual void settingsChanged(void) ;

protected:
    /**
     * Generic Carrier information
     */
    const ICarrier *mCarrier ;

    /**
     * Failure reason
     */
    std::shared_ptr<ICarrierFail> mFail ;

    /**
     * Settings changed
     */
    bool mSettingsChanged ;

};


}
#endif /* _ACE_AXIS_COMMONCARRIERHARDWARE_H_ */
