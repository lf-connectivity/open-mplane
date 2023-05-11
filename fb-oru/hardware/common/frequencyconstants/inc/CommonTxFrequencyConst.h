#ifndef _COMMONTXFREQUENCYCONSTANT_H_
#define _COMMONTXFREQUENCYCONSTANT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxFrequencyConst.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "Frequency.h"
#include "IFrequencyConst.h"

namespace Mplane
{

using namespace Mplane;

/**
 * Interface provides a minimum set of data relating to the constant frequency
 * data associated with the radios Tx port.
 */
class CommonTxFrequencyConst: public ITxFrequencyConst
{
public:

    /**
     * Method to return the radios minimum transmitter frequency for its band class.
     * @return Frequency constant data
     */
    virtual const Frequency getMinimum() const override;

    /**
     * Method to return the radios maximum transmitter frequency for its band class.
     * @return Frequency constant data
     */
    virtual const Frequency getMaximum() const override;

    /**
     * Method to return the radios centre transmit frequency for its band class.
     * @return Frequency constant data
     */
    virtual const Frequency getCentre() const override;

    /**
     * Method to return the radios transmitter filter minimum frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getFilterMinimum() const override;

    /**
     * Method to return the radios transmitter filter maximum frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getFilterMaximum() const override;

    /**
     * Method to return the radios transmitter minimum frequency as defined by
     * the 3GPP specifications.
     * @return Frequency constant data
     */
    virtual const Frequency get3GMinimum() const override;

    /**
     * Method to return the radios transmitter maximum frequency as defined by
     * the 3GPP specifications.
     * @return Frequency constant data
     */
    virtual const Frequency get3GMaximum() const override;

    /**
     * Method to return the radios transmitter frequency bandwidth.
     * @return Frequency constant data
     */
    virtual const Frequency getBandwidth() const override;

    /**
     * Method to return the radios transmitter frequency raster that determines the
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
     * Method to return the number of radio frequency local oscillators supported
     * by the radio transmitter hardware.
     * @return
     */
    virtual const unsigned int getNumberOfRFLO() const override;

    /**
     * Method to return this radios transmit local oscillator injection orientation.
     * The transmitters LO injection orientation indicates whether
     * the carrier frequency needs inverting (multiplying by minus one),
     * ensuring the IQ data through the RF is oriented correctly.
     * @return HIGHSIDE or LOWSIDE
     */
    virtual const Injection_t getLOInjection() const override;

    /**
     * Display the TX frequency constant data.
     */
    virtual void show();

protected:

    CommonTxFrequencyConst();
    /**
     * Destructor
     */
    virtual ~CommonTxFrequencyConst();


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

#endif /* _COMMONTXFREQUENCYCONSTANT_H_ */
