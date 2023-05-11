#ifndef _RADIO_HARDWARE_COMMONDAC_H_
#define _RADIO_HARDWARE_COMMONDAC_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonDac.h
 * \brief     A file to contain the common implementation of a generic DAC.
 *
 *
 * \details   This file defines the common implementation of a generic DAC
 *            and expands on it if necessary.
 *
 */

#include <string>
#include "IDac.h"
#include "Device.h"

namespace Mplane
{

class CommonDac:  public virtual IDac, public Device
{

public:


    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *  This is pure virtual and MUST be implemented by inheritors.
     *
     *  Means that this CommonDac class does not provide any DAC-type specific
     *  initialisation. That is left to the inheritors who know what
     *  device they are.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResult - eg. to ReturnType::RT_OK if all is ok
     *  mInitResultString - eg. to "DAC INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit() = 0;

    /*! \brief  Enable the DAC output
     *
     *  Enable the DAC output, primarily used when recovering from an error
     *  condition.
     */
    virtual void enableOutput() override;

    /*! \brief  Disable the DAC output
     *
     *  Disable the DAC output, primarily used in error conditions
     */
    virtual void disableOutput() override;


    /*! \brief  Dump the DAC registers
     *
     *  Dump the state of the DAC registers to the console or log file
     */
    virtual void show(void);

    /*! \brief Get the DAC state
     *
     * Get the DAC state
     *
     * \return true if enabled, false if disabled
     */
    virtual int getState();

    /**
     * Used to set the DACs DC offset value for I and Q data
     * @param i offset value
     * @param q offset value
     * @return RT_OK if set successfully, or RT_NOT_SUPPORTED if not supported by this device
     */
    virtual ReturnType::State setDCOffset( short int i, short int q) override;

    /**
     * Used to set the DACs Phase offset value for I and Q data
     * @param i phase offset value
     * @param q phase offset value
     * @return RT_OK if set successfully, or RT_NOT_SUPPORTED if not supported by this device
     */
    virtual ReturnType::State setPhaseOffset( short int i, short int q) override;

    /**
     * Used to set the DACs amplitude offset value for I and Q data
     * @param i phase offset value
     * @param q phase offset value
     * @return RT_OK if set successfully, or RT_NOT_SUPPORTED if not supported by this device
     */
    virtual ReturnType::State setMagOffset( short int i, short int q) override;

    /**
      * Method used to set the IF Offset by programming the DAC NCO
      * @return
      */
     virtual ReturnType::State setIfOffset( double  MHzOffset ) override;

     /**
       * Method used to get the IF Offset
       * @return
       */
     virtual double getIfOffset() override;


     /**
      * Method used to set the frequency by programming the DAC (used on boards with no synths)
      * @return
      */
     virtual ReturnType::State setFrequency( double  MHz ) override;

     /**
      * Method used to get the frequency
      * @return
      */
     virtual double getFrequency() override;

    /**
     * Method used to cal the DAC reset on the fly.
     * @return
     */
    virtual ReturnType::State resetFifo() override;

    /**
     * Method used to get the fifo level
     * @return
     */
    virtual unsigned getFifoLevel() override;

    /*! @brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param index  zero-based index of the DAC
     *  \param name   name string for the DAC
     */
    CommonDac( int index, const char* name);

    /*! \brief Destructor
     *
     */
    virtual ~CommonDac();

private:

    /*!
     * Indicates the DAC state.
     * true = enabled
     */
    bool mState;
};

} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONDAC_H_ */
