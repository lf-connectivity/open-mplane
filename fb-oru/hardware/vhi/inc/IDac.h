#ifndef _VRH_IDAC_H_
#define _VRH_IDAC_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDac.h
 * \brief     A file to define generic interface to a DAC device
 *
 *
 * \details   This file defines a generic interface to a DAC device
 *
 */

// Includes go here, before the namespace
#include "GlobalTypeDefs.h"
#include <string>
#include "IDevice.h"
#include "Frequency.h"

namespace Mplane
{

/*! \brief  Generic DAC interface
 *
 *  A virtual interface base class defining an interface to a DAC.
 *  The interface contains configuration and control aspects.
 */
class IDac: public virtual IDevice
{
public:


    /*! \brief  Enable the DAC output
     *
     *  Enable the DAC output, primarily used when recovering from an error
     *  condition.
     */
    virtual void enableOutput() = 0;

    /*! \brief  Disable the DAC output
     *
     *  Disable the DAC output, primarily used in error conditions
     */
    virtual void disableOutput() = 0;


    /**
     * Used to set the DACs DC offset value for I and Q data
     * @param i offset value
     * @param q offset value
     * @return RT_OK if set successfully, or RT_NOT_SUPPORTED if not supported by this device
     */
    virtual ReturnType::State setDCOffset( short int i, short int q) = 0;

    /**
     * Used to set the DACs Phase offset value for I and Q data
     * @param i phase offset value
     * @param q phase offset value
     * @return RT_OK if set successfully, or RT_NOT_SUPPORTED if not supported by this device
     */
    virtual ReturnType::State setPhaseOffset( short int i, short int q) = 0;

    /**
     * Used to set the DACs amplitude offset value for I and Q data
     * @param i phase offset value
     * @param q phase offset value
     * @return RT_OK if set successfully, or RT_NOT_SUPPORTED if not supported by this device
     */
    virtual ReturnType::State setMagOffset( short int i, short int q) = 0;

    /**
     * Method used to cal the DAC reset on the fly.
     * @return
     */
    virtual ReturnType::State resetFifo() = 0;

    /**
     * Method used to get the fifo level
     * @return
     */
    virtual unsigned getFifoLevel() = 0;

    /**
     * Method used to set the IF Offset by programming the DAC NCO
     * @return
     */
    virtual ReturnType::State setIfOffset( double  MHzOffset ) = 0;

    /**
     * Method used to get the IF Offset
     * @return
     */
    virtual double getIfOffset() = 0;

    /**
     * Method used to set the frequency by programming the DAC (used on boards with no synths)
     * @return
     */
    virtual ReturnType::State setFrequency( double  MHz ) = 0;

    /**
     * Method used to get the frequency
     * @return
     */
    virtual double getFrequency() = 0;

protected:

    IDac() {};

    /*! \brief Destructor
     *
     *  Ensure we can only be destructed via an implementing class
     *
     */
    virtual ~IDac() { };

};

} /* namespace Mplane */

#endif /* _VRH_IDAC_H_ */
