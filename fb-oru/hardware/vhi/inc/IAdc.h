#ifndef _VRH_IADC_H_
#define _VRH_IADC_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAdc.h
 * \brief     A file to define generic interface to a ADC device
 *
 *
 * \details   This file defines a generic interface to a ADC device
 *
 */

#include "IDevice.h"

namespace Mplane
{

/*! \brief  Generic ADC interface
 *
 *  A virtual interface base class defining an interface to an ADC.
 *  The interface contains configuration and control aspects.
 */
class IAdc: public virtual IDevice
{
public:



    /*! \brief  Enable the ADC
     *
     *  Enable the ADC, primarily used when recovering from an error
     *  condition.
     */
    virtual void enable() = 0;

    /*! \brief  Disable the ADC
     *
     *  Disable the ADC, primarily used in error conditions
     */
    virtual void disable() = 0;

    /*! \brief  Dump the ADC registers
     *
     *  Dump the state of the ADC registers to the console or log file
     */
    virtual void show(void) = 0;

    /**
     * Debug dump out information to stream about this device
     * @param os
     */
    virtual void show(std::ostream& os) =0;


protected:

    IAdc() {};


    /*! \brief Destructor
     *
     *  Ensure we can only be destructed via an implementing class
     *
     */
    virtual ~IAdc() { };

};


} /* namespace Mplane */

#endif /* _VRH_IADC_H_ */
