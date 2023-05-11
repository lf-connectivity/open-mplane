/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestWaveformFpga.cpp
 * \brief     Implementation of the TestWaveformFpga class
 *
 *
 * \details   This file contains the implementation of the hardware fpga
 *            TestWaveformFpga class.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "TestWaveformFpga.h"

using namespace Mplane;

////=============================================================================================================
//// SINGLETON
////=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<TestWaveformFpga> TestWaveformFpga::getInstance(void)
{
    static std::shared_ptr<TestWaveformFpga> instance(new TestWaveformFpga() ) ;
    return instance;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TestWaveformFpga::TestWaveformFpga() :
	CommonFPGA(),
	CommonFpgaWaveformRegs()
{
}
