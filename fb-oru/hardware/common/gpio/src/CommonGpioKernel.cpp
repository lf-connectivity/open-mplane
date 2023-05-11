/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonGpioKernel.cpp
 * \brief     Implementation of the CommonGpioKernel class
 *
 *
 * \details   This file contains the implementation of the hardware gpio
 *            CommonGpioKernel class.
 *
 */

// -------------------------------------------------------------------------
// //TODO The reference to "kernel" relates to the fact that the PPC GPIO
// used to be accessed via the FPGA kernel driver. We are now using a
// memory-mapped interface so is obsolete and can be renamed and/or
// tidied.
// -------------------------------------------------------------------------


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "CommonGpioKernel.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// @TODO Get values from DTS

// The on-chip peripheral bus (OPB) registers start at address
// 0xEF60 0000. The GPIO control registers form part of this
// block and start at 0xEF60 0800.

static const unsigned  GPIO_REGS_ADDRESS 	= 0xEF600000 ;
static const unsigned  GPIO_REGS_SIZE 		= 0x0010000 ;


#if 0
// GPIO bits
// There are 32 GPIO pins. The behaviour of each pin is controlled
// through a combination of control registers (ouput/3-state/input etc)

// Note: GPIO pin 0 maps to bit 31 in the register
//                1  "    "   " 30
//                2             29
// etc

#define GPIO_FPGA_PROGRAM_N     0x80000000
#define GPIO_FPGA_INIT_N        0x20000000
#define GPIO_FPGA_DONE          0x10000000

// PowerPC GPIO registers - from user guide)

#define  PPC_GPIO_OFFSET      = 0x00000800 ;

// Output
#define PPC405EX_GPIO0_OR       (PPC_GPIO_OFFSET + 0x00)
// 3-state control
#define PPC405EX_GPIO0_TCR      (PPC_GPIO_OFFSET + 0x04)
// Output select low
#define PPC405EX_GPIO0_OSRL     (PPC_GPIO_OFFSET + 0x08)
// Output select high
#define PPC405EX_GPIO0_OSRH     (PPC_GPIO_OFFSET + 0x0C)
// 3-state select low
#define PPC405EX_GPIO0_TSRL     (PPC_GPIO_OFFSET + 0x10)
// 3-state select high
#define PPC405EX_GPIO0_TSRH     (PPC_GPIO_OFFSET + 0x14)
// Open drain control
#define PPC405EX_GPIO0_ODR      (PPC_GPIO_OFFSET + 0x18)
// Input
#define PPC405EX_GPIO0_IR       (PPC_GPIO_OFFSET + 0x1c)


#endif



//=============================================================================================================
// SINGLETON
//=============================================================================================================

class CommonGpioKernelInstance : public CommonGpioKernel {
public:
	CommonGpioKernelInstance() : CommonGpioKernel() {}
	virtual ~CommonGpioKernelInstance() {}
};

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGpioKernel> IGpioKernel::getInstance(void)
{
	static std::shared_ptr<IGpioKernel> instance(std::make_shared<CommonGpioKernelInstance>()) ;
    return instance;
}

////-------------------------------------------------------------------------------------------------------------
//CommonGpioKernel& CommonGpioKernel::getInstance(void)
//{
//    static CommonGpioKernel _instance;
//
//    return _instance;
//}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonGpioKernel::CommonGpioKernel():
#ifdef OFF_TARGET
	// gpio emulator
     mGpioRegs(OffTargetGpio::getInstance())
#else
	// Memory mapped gpio
	 mGpioRegs(GPIO_REGS_ADDRESS, GPIO_REGS_SIZE)
#endif  // OFF_TARGET
{
}


//-------------------------------------------------------------------------------------------------------------
bool CommonGpioKernel::initialise(void)
{
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonGpioKernel::wr_field(UINT32 regOffset, UINT32 value, UINT32 mask, UINT32 shift)
{
	return this->write(regOffset, value << shift, mask << shift) ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonGpioKernel::wr_field(UINT32* buffer, UINT32 value, UINT32 mask, UINT32 shift)
{
	*buffer &= ~(mask << shift) ;
	*buffer |= (value & mask) << shift ;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 CommonGpioKernel::rd_field(UINT32 regOffset, UINT32 mask, UINT32 shift, ReturnType::State* ret_state)
{
	UINT32 value = 0 ;
	ReturnType::State state = this->read(regOffset, &value, mask << shift) ;

	value >>= shift ;

	if (ret_state)
	{
		*ret_state = state ;
	}

	return value ;
}



//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonGpioKernel::write(UINT32 regOffset, UINT32 value, UINT32 mask)
{
	mGpioRegs.modifyVal(regOffset, value, mask) ;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonGpioKernel::read(UINT32 regOffset, UINT32* value, UINT32 mask)
{
	*value = mGpioRegs.readVal(regOffset, mask) ;
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
CommonGpioKernel::~CommonGpioKernel()
{
}
