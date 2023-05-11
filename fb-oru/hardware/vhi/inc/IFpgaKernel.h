#ifndef _VRH_IFPGA_KERNEL_H_
#define _VRH_IFPGA_KERNEL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaKernel.h
 * \brief     Generic interface to FPGA kernel device driver
 *
 *
 * \details   This file defines a the generic interface to an FPGA kernel device driver.
 *
 */

#include <memory>
#include <string>
#include "GlobalTypeDefs.h"

namespace Mplane
{

/*! \brief  Generic FPGA kernel device driver Interface
 *
 *  A virtual interface base class defining a functional interface that must be
 *  adopted by any implementation of a kernel FPGA device driver interface.
 *
 *  This virtual interface allows an FPGA to expose its functionality, allowing
 *  developers to logically group the functionality of one or more FPGAs
 *  into an interface class.
 *
 */
class IFpgaKernel
{
public:
    /** \brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of the generic FPGA
     *  kernel interface object. This must be implemented using the singleton pattern by the
     *  specific radio implementation.
     */
    static std::shared_ptr<IFpgaKernel> getInstance(void);

    /*! \brief  The initialise method
     *
     *  Method called during system startup, post FPGA image load, to fully
     *  initialise the device and to override any initial settings with
     *  board-specific ones.
     *
     *  \return true if initialised ok
     */
    virtual bool initialise(void) = 0 ;

    /*! \brief  Write to an FPGA register field
     *
     *  Write a value into the specified field of the FPGA register.
     *
     *  This is an atomic action.
     *
     *  \param   regOffset   register number as described in FPGA spec
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write
     *  \param   shift       start bit location of field within register
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State wr_field(UINT32 regOffset, UINT16 value, UINT16 mask, UINT16 shift) = 0;

    /*! \brief  Write to an FPGA register field
     *
     *  Overloaded function that writes a value into the specified field of a buffer
     *
     *  This is an atomic action.
     *
     *  \param   buffer      pointer to 16 bit register buffer
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write
     *  \param   shift       start bit location of field within register
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State wr_field(UINT16* buffer, UINT16 value, UINT16 mask, UINT16 shift) = 0;

    /*! \brief  Read an FPGA register field
     *
     *  Overloaded function that reads a value from the specified field of a buffer
     *
     *  This is an atomic action.
     *
     *  \param   regOffset   register number as described in FPGA spec
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write
     *  \param   shift       start bit location of field within register
     *  \param   state       pointer to a ReturnType::State variable
     *
     *  \return read value
     */
    virtual UINT16 rd_field(UINT32 regOffset, UINT16 mask, UINT16 shift, ReturnType::State* state=0) = 0;



    /*! \brief  Write to an FPGA register
     *
     *  Write a 16 bit value into the specified register of the FPGA.
     *
     *  This is an atomic action.
     *
     *  \param   regOffset   register number as described in FPGA spec
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write. All unmasked bits will be written 0.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write(UINT32 regOffset, UINT16 value, UINT16 mask = 0xFFFF) = 0;

    /*! \brief  Modify an FPGA register
     *
     *  Performs a read-modify-write operation on the specified FPGA register.
     *
     *  This is an atomic action.
     *
     *  \param   regOffset   register number as described in FPGA spec
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State modify(UINT32 regOffset, UINT16 value, UINT16 mask = 0xFFFF) = 0;

    /*! \brief  Read from an FPGA register
     *
     *  Read the specified register of the FPGA.
     *
     *  \param  regOffset  register number as described in FPGA spec
     *  \param  value      the place to put the 16-bit value
     *  \param   mask        bit mask of which bits to read
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read(UINT32 regOffset, UINT16* value, UINT16 mask = 0xFFFF) = 0;

    /*! \brief  Write to an FPGA register
     *
     *  Write a 32 bit value into the specified register of the FPGA.
     *
     *  This is an atomic action.
     *
     *  \param   regOffset   register number as described in FPGA spec
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write. All unmasked bits will be written 0.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write32(UINT32 regOffset, UINT32 value, UINT32 mask = 0xFFFFFFFF) = 0;

    /*! \brief  Read from an FPGA register
     *
     *  Read the specified register of the FPGA.
     *
     *  \param  regOffset  register number as described in FPGA spec
     *  \param  value      the place to put the 16-bit value
     *  \param   mask        bit mask of which bits to read
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read32(UINT32 regOffset, UINT32* value, UINT32 mask = 0xFFFFFFFF) = 0;

    /*! \brief  Modify an FPGA register
     *
     *  Performs a read-modify-write operation on the specified FPGA register.
     *
     *  This is an atomic action.
     *
     *  \param   regOffset   register number as described in FPGA spec
     *  \param   value       value to write into register
     *  \param   mask        bit mask of which bits to write
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State modify32(UINT32 regOffset, UINT32 value, UINT32 mask = 0xFFFFFFFF) = 0;


protected:

    /*! Destructor
     *
     *  Destructor, should never be called.
     */
    virtual ~IFpgaKernel() { };

    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     */
    IFpgaKernel() {};

};



} /* namespace Mplane */

#endif // _VRH_IFPGA_KERNEL_H_
