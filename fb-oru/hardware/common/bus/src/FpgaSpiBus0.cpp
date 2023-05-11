/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaSpiBus0.cpp
 * \brief     FPGA SPI bus implementation for SPI0
 *
 *
 * \details   FPGA SPI bus implementation for SPI0
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string.h>
#include <iostream>
#include "FpgaSpiBus0.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaSpiBus0::FpgaSpiBus0(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<ISpiBusReadonlySettings> busSettings) :
		FpgaSpiBus(busName, busDetails, busLock, busSettings),
		mFpga(IFpgaMgr::getIFpgaSystemRegs())
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaSpiBus0::~FpgaSpiBus0()
{
}


//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus0::setControlReg2(uint8_t div, uint8_t phase, bool enable)
{
	FpgaVal control2 = 0;
    mFpga->write_spi0KeepEnable(&control2, (uint16_t)enable) ;
    mFpga->write_spi0ClkPhase1(&control2, (uint16_t)phase) ;
    mFpga->write_spi0ClkDiv(&control2, (uint16_t)div) ;
    mFpga->write_spi0Control2(control2) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus0::setControlReg1(uint8_t readLen, uint8_t writeLen, uint8_t polarity, bool rdOppEdge)
{
	FpgaVal control1 = 0;
    mFpga->write_spi0RdataLen(&control1, (uint16_t)readLen) ;
    mFpga->write_spi0WdataLen(&control1, (uint16_t)writeLen) ;
    mFpga->write_spi0ClkInvert(&control1, (uint16_t)polarity) ;
    mFpga->write_spi0RdOppEdge(&control1, (uint16_t)rdOppEdge) ;
    mFpga->write_spi0Control1(control1) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus0::startSpiTransaction(void)
{
	// Write the channel number for the SPI transaction
	mFpga->write_spi0Select(0) ;

	// Toggle the request bit to start the transaction
	mFpga->write_spi0Request(0) ;

	mFpga->write_spi0Request(1) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus0::setupWriteData(uint16_t low, uint16_t high)
{
	mFpga->write_spi0WriteDataLo(low) ;
	mFpga->write_spi0WriteDataHi(high) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus0::readData(uint32_t& data)
{
	uint16_t loValue = mFpga->read_spi0ReadDataLo() ;
	uint16_t highValue = mFpga->read_spi0ReadDataHi() ;

    data = (highValue << 16) | loValue;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus0::isTransactionComplete()
{
    uint16_t done = mFpga->read_spi0CompleteAlarm() ;

	return done ? true : false ;
}
