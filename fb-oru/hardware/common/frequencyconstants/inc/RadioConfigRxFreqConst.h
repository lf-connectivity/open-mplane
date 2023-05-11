#ifndef _RADIOCONFIGRXFREQUENCYCONSTANT_H_
#define _RADIOCONFIGRXFREQUENCYCONSTANT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioConfigRxFreqConst.h
 * \brief     Get the RX frequency constants from the IRadioConfig singleton
 *
 *
 * \details   Get the RX frequency constants from the IRadioConfig singleton
 *
 */

#include "Frequency.h"
#include "IFrequencyConst.h"

namespace Mplane
{

using namespace Mplane;

/**
 * Interface provides a minimum set of data relating to the constant frequency
 * data associated with the radios Rx port.
 */
class RadioConfigRxFreqConst: public IRxFrequencyConst
{
public:
    /**
     * Method to return the radios minimum receive frequency for its band class.
     * @return Frequency constant data
     */
    virtual const Frequency getMinimum() const override;

    /**
     * Method to return the radios maximum receive frequency for its band class.
     * @return Frequency constant data
     */
    virtual const Frequency getMaximum() const override;

    /**
     * Method to return the radios centre receive frequency for its band class.
     * @return Frequency constant data
     */
    virtual const Frequency getCentre() const override;


    /**
     * Method to return the radios receiver filter minimum frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getFilterMinimum() const override;

    /**
     * Method to return the radios receiver filter maximum frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getFilterMaximum() const override;

    /**
     * Method to return the radios receiver minimum frequency as defined by
     * the 3GPP specifications.
     * @return Frequency constant data
     */
    virtual const Frequency get3GMinimum() const override;

    /**
     * Method to return the radios receiver maximum frequency as defined by
     * the 3GPP specifications.
     * @return Frequency constant data
     */
    virtual const Frequency get3GMaximum() const override;

    /**
     * Method to return the radios receiver bandwidth frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getBandwidth() const override;

    /**
     * Method to return the radios receiver frequency raster that determines the
     * resolution of carrier positioning.
     * @return Frequency constant data
     */
    virtual const Frequency getRaster() const override;

    /**
     * Method to return the carrier orientation.
     * @return HIGHSIDE or LOWSIDE
     */
    virtual const Injection_t getCarrierFlip() const override;

    /**
     * Method to return the radios local oscillator injection point orientation.
     * @return
     */
    virtual const Injection_t getLOInjection() const override;


    /**
     * Method to return the number of radio frequency local oscillators supported
     * by the radio receiver hardware.
     * @return
     */
    virtual const unsigned int getNumberOfRFLO() const override;


    /**
     * Display the RX frequency constant data.
     */
    virtual void show();


protected:

    /**
     * Protected constructor to prevent this class being instantiated, it must
     * be constructed through the extending classes.
     */
    RadioConfigRxFreqConst();

    /**
     * Virtual protected constructor, this object is never expected to be destroyed.
     */
    virtual ~RadioConfigRxFreqConst();

    /** Set the radio-specific constants
     *
     */
    void setRadioSpecific(const Frequency& raster,
    	Injection_t carrierFlip,
    	Injection_t loInjection,
    	unsigned int numberOfRFLO) ;

private:
    Frequency mFilterMinimum;
    Frequency mFilterMaximum;
    Frequency m3GMinimum;
    Frequency m3GMaximum;
    Frequency mMinimum;
    Frequency mMaximum;
    Frequency mCentre;
    Frequency mBandwidth;
    Frequency mRaster;
    Injection_t mCarrierFlip;
    Injection_t mLOInjection;
    unsigned int mNumberOfRFLO;

};

}

#endif /* _RADIOCONFIGRXFREQUENCYCONSTANT_H_ */
