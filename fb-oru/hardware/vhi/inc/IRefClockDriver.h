/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRefClockDriver.h
 * \brief     A file to define generic interface to a reference clock device driver
 *
 *
 * \details   This file defines a generic interface to a reference clock device driver
 *
 */

#ifndef _VRH_IREFCLOCKDRIVER_H_
#define _VRH_IREFCLOCKDRIVER_H_

// Includes go here, before the namespace
#include <vector>
#include <string>

#include "GlobalTypeDefs.h"
#include "Frequency.h"
#include "FrequencyOffset.h"

// forward declarations go here, before the namespace

namespace Mplane
{

/*! \brief  Generic reference clock driver interface
 *
 *  A generic virtual interface base class defining an interface to a
 *  reference clock driver.
 *  The interface contains configuration and control aspects.
 *
 *  The aim for creating the IRefClockDriver interface is to make the reference clock
 *  devices independent of the PLL driver chip / library used.
 *  The IRefClockDriver implementations would have the board specific code to
 *  communicate with the PLL to set the required frequency.
 *  The individual reference clock object (DAC reference, ADC reference, etc) would use one of the
 *  IRefClockDriver implementations via the virtual interface.
 *
 */
class IRefClockDriver
{
public:
	IRefClockDriver() {};
    virtual ~IRefClockDriver() {};


    /*! \brief  Initialise the reference clock
     *
     */
    virtual ReturnType::State initialise ( void ) =0;


    /*! \brief  Determine whether the PLL is locked
     *
     *  Method used to check if the PLL is locked.
     *
     *  \return true if the PLL is locked
     */
    virtual bool isPllLocked(void) =0;

    /*! \brief  Dump the reference clock status
     *
     *  Dump the state of the reference clock driver to the log file
     */
    virtual void show ( std::ostream& os ) = 0;

    /*! \brief  Dump the reference clock status
     *
     *  Dump the state of the reference clock driver to the console
     */
    virtual void show ( void ) = 0;


};

} /* namespace Mplane */

#endif /* _VRH_IREFCLOCKDRIVER_H_ */
