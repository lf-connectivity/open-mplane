#ifndef _VRH_IGPIO_KERNEL_H_
#define _VRH_IGPIO_KERNEL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IGpioKernel.h
 * \brief     Generic interface to Gpio
 *
 *
 * \details   This file defines a generic interface the gpio "kernel"
 *
 */

// -------------------------------------------------------------------------
// //TODO The reference to "kernel" relates to the fact that the PPC GPIO
// used to be accessed via the FPGA kernel driver. We are now using a
// memory-mapped interface so is obsolete and can be renamed and/or
// tidied.
// -------------------------------------------------------------------------

#include <memory>
#include <string>
#include "GlobalTypeDefs.h"

namespace Mplane
{



/*! \brief  Generic Gpio Interface
 *
 *  A virtual interface base class defining a functional interface that must be
 *  adopted by any implementation of a gpio interface.
 *
 *  This virtual interface allows gpio to expose its functionality, allowing
 *  developers to logically group the functionality of one or more Gpios
 *  into an interface class.
 *
 */
class IGpioKernel
{
public:
    /** \brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of the generic gpio
     *  interface object. This must be implemented using the singleton pattern by the
     *  specific radio implementation.
     */
    static std::shared_ptr<IGpioKernel> getInstance(void);

    /*! \brief  The initialise method
     *
     *  Method called during system startup, to fully
     *  initialise the device and to override any initial settings with
     *  board-specific ones.
     *
     *  \return true if initialised ok
     */
    virtual bool initialise(void) = 0 ;


    /*! \brief  Write to a gpio register field
     *
     *  Write a value into the specified field of the gpio register.
     *
     *  This is an atomic action.
     *
     *  \param   regOffset   register number
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write
     *  \param   shift       start bit location of field within register
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State wr_field(UINT32 regOffset, UINT32 value, UINT32 mask, UINT32 shift) = 0;

    /*! \brief  Write to an gpio register field
     *
     *  Overloaded function that writes a value into the specified field of a buffer
     *
     *  This is an atomic action.
     *
     *  \param   buffer      pointer to 32 bit register buffer
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write
     *  \param   shift       start bit location of field within register
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State wr_field(UINT32* buffer, UINT32 value, UINT32 mask, UINT32 shift) = 0;

    /*! \brief  Read a gpio register field
     *
     *  Overloaded function that reads a value from the specified field of a buffer
     *
     *  This is an atomic action.
     *
     *  \param   regOffset   register number
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write
     *  \param   shift       start bit location of field within register
     *  \param   state       pointer to a ReturnType::State variable
     *
     *  \return read value
     */
    virtual UINT32 rd_field(UINT32 regOffset, UINT32 mask, UINT32 shift, ReturnType::State* state=0) = 0;



    /*! \brief  Write to an gpio register
     *
     *  Write a 32 bit value into the specified register of the gpio.
     *
     *  This is an atomic action.
     *
     *  \param   regOffset   register number
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write(UINT32 regOffset, UINT32 value, UINT32 mask) = 0;

    /*! \brief  Read from a gpio register
     *
     *  Read the specified gpio register.
     *
     *  \param  regOffset  register number
     *  \param  value      the place to put the 32-bit value
     *  \param   mask        bit mask of which bits to reasd
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read(UINT32 regOffset, UINT32* value, UINT32 mask) = 0;




protected:

    /*! Destructor
     *
     *  Destructor, should never be called.
     */
    virtual ~IGpioKernel() { };

    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     */
    IGpioKernel() {};

};



} /* namespace Mplane */

#endif // _VRH_IGPIO_KERNEL_H_
