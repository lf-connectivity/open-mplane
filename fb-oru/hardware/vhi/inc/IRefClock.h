/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRefClock.h
 * \brief     A file to define generic interface to a reference clock device
 *
 *
 * \details   This file defines a generic interface to a reference clock device
 *
 */

#ifndef _VRH_IREFCLOCK_H_
#define _VRH_IREFCLOCK_H_

// Includes go here, before the namespace
#include <vector>
#include <string>

#include "GlobalTypeDefs.h"
#include "Frequency.h"
#include "FrequencyOffset.h"
#include "IDevice.h"

// forward declarations go here, before the namespace

namespace Mplane
{

/*! \brief  Generic reference clock device interface
 *
 *  A generic virtual interface base class defining an interface to a
 *  reference clock device.
 *
 *  The IRefClock interface represents the devices in the system that
 *  generate fixed clocks that need to be programmed at startup and then
 *  remain unchanged. Hence the interface does not have any methods other than
 *  the debug methods. The setting up of clock as part of startup can be
 *  implemented by inheritors in the initialise method of IDevice class.
 *
 */
class IRefClock : public virtual IDevice
{
public:
	IRefClock() {};
    virtual ~IRefClock() {};

    /*! \brief  Determine whether the PLL is locked
     *
     *  Method used to check if the PLL is locked.
     *
     *  \return true if the PLL is locked
     */
    virtual bool isPllLocked(void) =0;

    /*! \brief  Force the synthesiser out of lock
     *
     *  Used for synthesiser testing by forcing the synth to go out lock.
     */
    virtual void forceOutOfLock(void) =0;


    /*! \brief  Dump the reference clock status
     *
     *  Dump the state of the reference clock driver to the console or log file
     */
    virtual void show(std::ostream& os) = 0;
    virtual void show(void) =0;


};

} /* namespace Mplane */

#endif /* _VRH_IREFCLOCK_H_ */
