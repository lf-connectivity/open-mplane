#ifndef _RADIO_HARDWARE_COMMONADC_H_
#define _RADIO_HARDWARE_COMMONADC_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAdc.h
 * \brief     A file to contain the common implementation of a generic ADC.
 *
 *
 * \details   This file defines the common implementation of a generic ADC
 *            and expands on it if necessary.
 *
 */

#include <string>
#include "IAdc.h"
#include "Device.h"

namespace Mplane
{

class CommonAdc: public virtual IAdc, public Device
{

public:

    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *  This is pure virtual and MUST be implemented by inheritors.
     *
     *  Means that this CommonAdc class does not provide any ADC-type specific
     *  initialisation. That is left to the inheritors who know what
     *  device they are.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResult - eg. to ReturnType::RT_OK if all is ok
     *  mInitResultString - eg. to "ADC INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit() = 0;

    /*! \brief  Enable the ADC
     *
     *  Enable the ADC, primarily used when recovering from an error
     *  condition.
     */
    virtual void enable();

    /*! \brief  Disable the ADC
     *
     *  Disable the ADC, primarily used in error conditions
     */
    virtual void disable();


    /*! \brief  Dump the ADC registers
     *
     *  Dump the state of the ADC registers to the console or log file
     */
    virtual void show(void) ;

    /*! \brief Get the ADC state
     *
     * Get the ADC state
     *
     * \return true if enabled, false if disabled
     */
    virtual int getState();

    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param index  zero-based index of the ADC
     *  \param name   name string for the ADC
     */
    CommonAdc( int index, const char* name);

    /*! \brief Destructor
     *
     */
    virtual ~CommonAdc();

    /**
     * Debug dump out information to stream about this device
     * @param os
     */
    virtual void show(std::ostream& os)  ;


private:


    /*!
     * Indicates the ADC state.
     * true = enabled
     */
    bool mState;
};

} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONADC_H_ */
