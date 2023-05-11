#ifndef _VRH_IGPIO_H_
#define _VRH_IGPIO_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IGpio.h
 * \brief     A file to contain a generic gpio interface.
 *
 *
 * \details   This file defines a generic gpio interface
 *
 */

#include "GlobalTypeDefs.h"
#include <memory>
#include "IGpioKernel.h"

namespace Mplane
{

/*! \brief  Generic gpio Interface
 *
 *  A virtual interface base class defining a functional interface that must be
 *  adopted by any implementation of a generic gpio interface.
 *
 *  This virtual interface allows the gpio to expose its functionality, allowing
 *  developers to logically group the functionality of one or more gpios
 *  into an interface class.
 *
 */
class IGpio
{
public:

    /** \brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of the generic gpio
     *  object. This must be implemented using the singleton pattern by the
     *  specific radio implementation.
     *
     *  Must be define in: hardware/<BOARD>/radio/src/<Board>Gpio.cpp
     *
     *  Test mock defined in: vrh/test/src/TestIGpio.cpp //TODO
     *
     *
     */
    static std::shared_ptr<IGpio> getInstance(void);

    /*! \brief  The initialise method
     *
     *  Method called during system startup, to fully
     *  initialise the device and to override any initial settings with
     *  board-specific ones.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise(void) = 0;


    /*! \brief  Read an fpga register
     *
     *  Method used to return the gpio register value at the specified offset.
     *
     *  \return  UINT32 gpio register contents
     */
    virtual UINT32 readRegister(unsigned offset) = 0;

    /*! \brief  Write a gpio register
     *
     *  Method used to write a gpio register value at the specified offset.
     *
     */
    virtual void writeRegister(unsigned offset, UINT32 value) = 0;

    /*! \brief  Modify an fpga register
     *
     *  Method used to write a gpio register value at the specified offset.
     *
     */
    virtual void modifyRegister(unsigned offset, UINT32 value, UINT32 mask) = 0;


    /*! Destructor
     *
     *  Destructor, should never be called.
     */
    virtual ~IGpio() { };

protected:
    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     */
    IGpio() {};


};



} /* namespace Mplane */

#endif // _VRH_IGPIO_H_
