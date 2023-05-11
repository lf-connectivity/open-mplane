#ifndef _RADIO_HARDWARE_COMMONREFCLOCK_H_
#define _RADIO_HARDWARE_COMMONREFCLOCK_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRefClock.h
 * \brief     A file to contain the common implementation of a generic reference clock.
 *
 *
 * \details   This file defines the common implementation of a generic reference clock
 *            and expands on it if necessary.
 *
 */

// Includes go here, before the namespace
#include <string>
#include <memory>

#include "IRefClock.h"
#include "Initialise.h"
#include "Device.h"
#include "IRefClockDriver.h"

namespace Mplane
{

/*! \brief  Generic reference clock interface
 *
 *  A generic virtual interface base class defining an interface to a
 *  reference clock.
 *  The interface contains configuration and control aspects.
 *
 *  This class represents a virtual interface used to setup a reference clock
 *  on a radio. It is designed to be implemented as a polymorphic base class
 *  for all reference clock device programming classes.
 *
 */
class CommonRefClock:  public virtual IRefClock, public Device
{

public:


    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit();

    /*! \brief  Determine whether the PLL is locked
     *
     *  Method used to check if the PLL is locked.
     *
     *  \return true if the PLL is locked
     */
    virtual bool isPllLocked(void) override;

    /*! \brief  Force the synthesiser out of lock
     *
     *  Used for synthesiser testing by forcing the synth to go out lock.
     */
    virtual void forceOutOfLock(void) override;

    /*! \brief  Dump the reference clock status
     *
     *  Dump the state of the reference clock to the console or log file
     */
    virtual void show(std::ostream& os);
    virtual void show(void);


    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param driver pointer to reference clock driver that drives the hardware
     *  \param index  zero-based index of the reference clock
     *  \param name   name string for the reference clock
     *  \param frequency the frequency for the reference clock to be set to
     */
    CommonRefClock( std::shared_ptr<IRefClockDriver> driver, int index, const std::string& name);

    /*! \brief Destructor
     *
     *  Ensure we can only be destructed via an implementing class
     *
     */
    virtual ~CommonRefClock();


private:

    /*!
     * The reference clock driver that gives access to the hardware
     */
    std::shared_ptr<IRefClockDriver> mDriver;

};

} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONREFCLOCK_H_ */
