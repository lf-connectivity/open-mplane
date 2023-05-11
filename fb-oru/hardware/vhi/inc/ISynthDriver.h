/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISynthDriver.h
 * \brief     A file to define generic interface to a radio Synthesiser device driver
 *
 *
 * \details   This file defines a generic interface to a radio Synthesiser device driver
 *
 */

#ifndef _VRH_ISYNTHDRIVER_H_
#define _VRH_ISYNTHDRIVER_H_

// Includes go here, before the namespace
#include <vector>
#include <string>

#include "GlobalTypeDefs.h"
#include "Frequency.h"
#include "FrequencyOffset.h"

// forward declarations go here, before the namespace

namespace Mplane
{

/*! \brief  Generic Synthesiser driver interface
 *
 *  A generic virtual interface base class defining an interface to a
 *  radio synthesiser driver.
 *  The interface contains configuration and control aspects.
 *
 *  The aim for creating the ISynthDriver interface is to make the Tx, Rx, Dpd,
 *  System synth objects independent of the PLL driver chip / library used.
 *  The ISynthDriver implementations would have the board specific code to
 *  communicate with the PLL to initialise and program the required frequency.
 *  The individual synthesiser object (Tx, Rx, etc) would use one of the
 *  ISynthDriver implementations via the virtual interface.
 *
 */
class ISynthDriver
{
public:
	ISynthDriver() {};
    virtual ~ISynthDriver() {};

    /*! \brief  Initialise the synthesiser driver
     *
     *  \param None
     */
    virtual ReturnType::State initialise(void) =0;

    /*! \brief  Set the synthesiser frequency
     *
     *  Program the given frequency
     *
     *  \param the synthesiser frequency
     */
    virtual ReturnType::State program(Frequency frequency ) =0;

    /*! \brief  Post Program steps if any
     *
     *  Called after ISynthDriver::program to perform any steps after frequency is changed
     *
     *  \return None
     */
    virtual void postProgram(void) =0;

    /*! \brief  Determine whether the PLL is locked
     *
     *  Method used to check if the PLL is locked.
     *
     *  \return true if the PLL is locked
     */
    virtual bool isPllLocked(void) =0;

    /*! \brief  Determine whether the synthesiser is locked
     *
     *  Method used to check if the synthesiser is out of lock.
     *
     *  \return true if the synthesiser is out of lock.
     */
    virtual bool isOutOfLock(void) =0;

    /*! \brief  Force the synthesiser out of lock
     *
     *  Used for synthesiser testing by forcing the synth to go out lock.
     */
    virtual void forceOutOfLock(void) =0;


    /*! \brief  Dump the Synth status
     *
     *  Dump the state of the synthesiser driver to the console or log file
     */
    virtual void show(std::ostream& os) = 0;
    virtual void show(void) =0;


};

} /* namespace Mplane */

#endif /* _VRH_ISYNTHDRIVER_H_ */
