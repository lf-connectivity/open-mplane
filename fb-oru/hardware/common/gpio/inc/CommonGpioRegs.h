#ifndef _GPIO_REGS_DEF_H_
#define _GPIO_REGS_DEF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonGpioSystemRegs.h
 * \brief     Gpio System registers
 *
 *
 * \details   This file defines the Gpio System registers
 *
 */

#include "GlobalTypeDefs.h"
#include "IGpioKernel.h"


namespace Mplane
{

class CommonGpioRegs
{
public:

	CommonGpioRegs(void) :
		device( IGpioKernel::getInstance() ) {} ;
	virtual ~CommonGpioRegs(void) {} ;


    // == Accessors ==

    /**
    * Read field FPGA_CONFIG_DONE - bit [28]
    * \return field value
    */
   const UINT16 read_fpgaConfigDone() const { return device->rd_field(GPIO_REG_READ_ADDR, FPGA_CONFIG_DONE_MASK, FPGA_CONFIG_DONE_SHIFT); }




#if 0

    /**
     * Read field SYSTEM_CLOCK_RESET at 0x00000 bit [0]
     * \return field value
     */
    const UINT16 read_systemClockReset() const { return device->rd_field(SYSTEM_CLOCK_RESET_ADDR, SYSTEM_CLOCK_RESET_MASK, SYSTEM_CLOCK_RESET_SHIFT); }

    /**
     * Write field SYSTEM_CLOCK_RESET at 0x00000 bit [0]
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    ReturnType::State write_systemClockReset(UINT16 value) { return device->wr_field(SYSTEM_CLOCK_RESET_ADDR, value, SYSTEM_CLOCK_RESET_MASK, SYSTEM_CLOCK_RESET_SHIFT); }

    /**
     * Write field SYSTEM_CLOCK_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    ReturnType::State write_systemClockReset(UINT16* buff, UINT16 value) { return device->wr_field(buff, value, SYSTEM_CLOCK_RESET_MASK, SYSTEM_CLOCK_RESET_SHIFT); }



    }


#endif

	static const unsigned PPC_MAX_GPIO_PINS = 32;
	static const ULONG GPIO_REG_READ_ADDR = 0x81C;
	static const ULONG GPIO_REG_OUTPUT_ADDR = 0x800;

protected:

    /**
     * Kernel interface singleton
     */
	std::shared_ptr<IGpioKernel> device ;


    static const ULONG GPIO_REG_THREE_STATE_CONTROL_ADDR = 0x804;
    static const ULONG GPIO_REG_OPEN_DRAIN_ADDR = 0x818;

    static const ULONG FPGA_CONFIG_DONE_MASK = 0x00000001;
    static const unsigned FPGA_CONFIG_DONE_SHIFT = 28;


};


} /* namespace Mplane */

#endif /* _SYSTEM_REGS_DEF_H_ */
