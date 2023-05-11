#ifndef _MPLANE_IFREQUENCYCONSTANTS_H_
#define _MPLANE_IFREQUENCYCONSTANTS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFrequencyConstants.h
 * \brief     This interface class provides access to the radios constant frequency
 *
 *
 * \details   This interface class provides access to the radios constant frequency
 *
 */

#include <memory>
#include "Frequency.h"

namespace Mplane
{

using namespace Mplane;

/**
 * Defines a variable type used to represent the possible LO injection values.
 */
typedef enum _injection
{
    HIGHSIDE = 1,//!< HIGHSIDE
    LOWSIDE = -1 //!< LOWSIDE
} Injection_t;


/**
 * Interface provides a minimum set of data relating to the constant frequency
 * data.
 */
class IFrequencyConst
{
public:

    /**
     * Method to return the radio's minimum LO frequency for its band class.
     * @return Frequency constant data
     */
    virtual const Frequency getMinimum() const = 0;

    /**
     * Method to return the radio's maximum LO frequency for its band class.
     * @return Frequency constant data
     */
    virtual const Frequency getMaximum() const = 0;

    /**
     * Method to return the radio's LO centre frequency for its band class.
     * @return Frequency constant data
     */
    virtual const Frequency getCentre() const = 0;

    /**
     * Method to return the radio's filter minimum frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getFilterMinimum() const = 0;

    /**
     * Method to return the radio's filter maximum frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getFilterMaximum() const = 0;

    /**
     * Method to return the radio's minimum frequency as defined by
     * the 3GPP specifications.
     * @return Frequency constant data
     */
    virtual const Frequency get3GMinimum() const = 0;

    /**
     * Method to return the radio's maximum frequency as defined by
     * the 3GPP specifications.
     * @return Frequency constant data
     */
    virtual const Frequency get3GMaximum() const = 0;

    /**
     * Method to return the radio's bandwidth frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getBandwidth() const = 0;

    /**
     * Method to return the radio's frequency raster that determines the
     * resolution of carrier positioning.
     * @return Frequency constant data
     */
    virtual const Frequency getRaster() const = 0;

    /**
     * Method to return the carrier orientation.
     * @return HIGHSIDE or LOWSIDE
     */
    virtual const Injection_t getCarrierFlip() const = 0;

    /**
     * Method to return the radios local oscillator injection point orientation.
     * @return
     */
    virtual const Injection_t getLOInjection() const = 0;


    /**
     * Method to return the number of radio frequency local oscillators supported
     * by the radio receiver hardware.
     * @return
     */
    virtual const unsigned int getNumberOfRFLO() const = 0;


    /**
     * Display the frequency constant data.
     */
    virtual void show() = 0;

    /**
     * Destructor
     */
    virtual ~IFrequencyConst() {}

};

/**
 * Interface provides a minimum set of data relating to the constant frequency
 * data associated with the radios Rx port.
 */
class IRxFrequencyConst : public virtual IFrequencyConst
{
public:
    /**
     * Destructor
     */
    virtual ~IRxFrequencyConst() {}

};

/**
 * Interface provides a minimum set of data relating to the constant frequency
 * data associated with the radios Tx port.
 */
class ITxFrequencyConst : public virtual IFrequencyConst
{
public:
    /**
     * Destructor
     */
    virtual ~ITxFrequencyConst() {}

};

class IRxFrequencyConstFactory
{
public:
    /**
     * Method implements a factory that uses the radio board type to
     * select and return an instance of a receive frequency constant class
     * that implements the IRxFrequencyConstanst interface.
     * @return a reference to this radios receive frequency constant data.
     */
    static std::shared_ptr<IRxFrequencyConst> getInterface();

};


class ITxFrequencyConstFactory
{
public:
    /**
     * Method implements a factory that uses the radio board type to
     * select and return an instance of a transmit frequency constant class
     * that implements the ITxFrequencyConstanst interface.
     * @return a reference to this radios transmit frequency constant data.
     *
     *  Must be define in: hardware/<BOARD>/radio/src/<Board>TxFrequencyConstFactory.cpp
     *
     */
    static std::shared_ptr<ITxFrequencyConst> getInterface();

};

}

#endif /* _MPLANE_IFREQUENCYCONSTANTS_H_ */
