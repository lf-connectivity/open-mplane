#ifndef _RADIO_HARDWARE_COMMONGPIOKERNEL_H_
#define _RADIO_HARDWARE_COMMONGPIOKERNEL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonGpioKernel.h
 * \brief     A file to contain the common implementation of a generic Gpio register access driver.
 *
 *
 * \details   This file defines the common implementation of a generic gpio register access driver
 *            and expands on it if necessary.
 *
 */


// -------------------------------------------------------------------------
// //TODO The reference to "kernel" relates to the fact that the PPC GPIO
// used to be accessed via the FPGA kernel driver. We are now using a
// memory-mapped interface so is obsolete and can be renamed and/or
// tidied.
// -------------------------------------------------------------------------


#include "MemMap.hpp"
#include "IGpioKernel.h"

#ifdef OFF_TARGET
#include "OffTargetGpio.h"
#endif  // OFF_TARGET

namespace Mplane
{

class CommonGpioKernel : public IGpioKernel
{
public:

//    /** \brief  Get the singleton instance
//     *
//     *  Used to get a reference to the single instance of the generic gpio
//     *  interface object. This must be implemented using the singleton pattern by the
//     *  specific radio implementation.
//     */
//    static std::shared_ptr<CommonGpioKernel> getInstance(void) ;

    /*! \brief  The initialise method
     *
     *  Method called during system startup, to fully
     *  initialise the device and to override any initial settings with
     *  board-specific ones.
     *
     *  \return true if initialised ok
     */
    virtual bool initialise(void) ;

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
    virtual ReturnType::State wr_field(UINT32 regOffset, UINT32 value, UINT32 mask, UINT32 shift);

    /*! \brief  Write to a gpio register field
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
    virtual ReturnType::State wr_field(UINT32* buffer, UINT32 value, UINT32 mask, UINT32 shift);

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
    virtual UINT32 rd_field(UINT32 regOffset, UINT32 mask, UINT32 shift, ReturnType::State* state=0);

    /*! \brief  Write to a gpio register
     *
     *  Write a 32 bit value into the specified gpio register.
     *
     *  This is an atomic action.
     *
     *  \param   regOffset   register number
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write(UINT32 regOffset, UINT32 value, UINT32 mask=0xffffffff) ;

    /*! \brief  Read from a gpio register
     *
     *  Read the specified gpio register
     *
     *  \param  regOffset  register number
     *  \param  value      the place to put the 16-bit value
     *  \param   mask        bit mask of which bits to reasd
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read(UINT32 regOffset, UINT32* value, UINT32 mask=0xffffffff) ;


    /*! Destructor
     *
     */
    virtual ~CommonGpioKernel();



protected:

     /*! \brief  Constructor
      *
      */
 	CommonGpioKernel();


protected:

     /**
      * Gpio register access
      */
#ifdef OFF_TARGET
     OffTargetGpio &mGpioRegs ;
#else
     MemMap<UINT32>	mGpioRegs ;
#endif  // OFF_TARGET

};


} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONGPIOKERNEL_H_ */
