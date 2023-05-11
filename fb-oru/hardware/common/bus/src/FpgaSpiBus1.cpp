/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaSpiBus1.cpp
 * \brief     FPGA SPI bus implementation for SPI1
 *
 *
 * \details   FPGA SPI bus implementation for SPI1
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string.h>
#include <iostream>
#include "FpgaSpiBus1.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaSpiBus1::FpgaSpiBus1(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<ISpiBusReadonlySettings> busSettings) :
		FpgaSpiBus(busName, busDetails, busLock, busSettings),
		mFpga(IFpgaMgr::getIFpgaSystemRegs())
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaSpiBus1::~FpgaSpiBus1()
{
}


//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus1::setControlReg2(uint8_t div, uint8_t phase, bool enable)
{
	FpgaVal control2 = 0;
    mFpga->write_spi1KeepEnable(&control2, (uint16_t)enable) ;
    mFpga->write_spi1ClkPhase1(&control2, (uint16_t)phase) ;
    mFpga->write_spi1ClkDiv(&control2, (uint16_t)div) ;
    mFpga->write_spi1Control2(control2) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus1::setControlReg1(uint8_t readLen, uint8_t writeLen, uint8_t polarity, bool rdOppEdge)
{
    FpgaVal control1 = 0;
    mFpga->write_spi1RdataLen(&control1, (uint16_t)readLen) ;
    mFpga->write_spi1WdataLen(&control1, (uint16_t)writeLen) ;
    mFpga->write_spi1ClkInvert(&control1, (uint16_t)polarity) ;
    mFpga->write_spi1Control1(control1) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus1::startSpiTransaction(void)
{
	mFpga->write_spi1Select(0) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus1::setupWriteData(uint16_t low, uint16_t high)
{
	mFpga->write_spi1WriteDataLo(low) ;
	mFpga->write_spi1WriteDataHi(high) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus1::readData(uint32_t& data)
{
	uint16_t loValue = mFpga->read_spi1ReadDataLo() ;
	uint16_t highValue = mFpga->read_spi1ReadDataHi() ;

    data = (highValue << 16) | loValue;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus1::isTransactionComplete()
{
    uint16_t done = mFpga->read_spi1CompleteAlarm() ;

	return done ? true : false ;
}
