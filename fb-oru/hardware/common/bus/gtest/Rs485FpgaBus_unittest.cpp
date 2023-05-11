/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Rs485FpgaBus_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string>
#include <iostream>

#include <gtest/gtest.h>

#include "ByteTransfer.hpp"
#include "BusLock.hpp"
#include "SpiBusSettings.h"
#include "Rs485BusFpga.h"

#include "Rs485FpgaBus_fixture.h"

using namespace Mplane ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(Rs485FpgaBusTestFixture, writeDataLessThanBlockSize)
{

	static const OffTargetFPGA::SequenceCheck LessThanBlockSizeSeqData[] = {
			OffTargetFPGA::SequenceCheck(0xBE, 0x0000, 0x0001),
			OffTargetFPGA::SequenceCheck(0xBE, 0x0002, 0x0002),
			OffTargetFPGA::SequenceCheck(0xBE, 0x0002, 0x0004),
			OffTargetFPGA::SequenceCheck(0xBC, 0x0003, 0x0004),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0000, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0001, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0002, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0003, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0004, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0005, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0006, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0007, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0008, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0009, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xBE, 0x0006, 0x0004),
			OffTargetFPGA::SequenceCheck(0xBC, 0x0007, 0x0004)
	};

	(void)LessThanBlockSizeSeqData;

    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    restartFpgaEmulator() ;

    // Initialise the FPGA UART
    fpgaEmu->writeField("UartTxBufferEmpty", 1);
    fpgaEmu->writeField("UartTxBufferFull", 0);
    fpgaEmu->writeField("UartRxDataPresent", 0);
    fpgaEmu->writeField("UartRxFrameError", 0);
    fpgaEmu->writeField("UartRxOverrunError", 0);

    std::vector<uint8_t> txData;

    for (unsigned int index = 0; index < 10; index++)
    {
    	txData.push_back(index);
    }

	std::shared_ptr<IBusSettings> settings(std::make_shared<BusSettings>());

	Rs485BusFpga serialBus("Fpga Rs485 bus", "Test bus", 9600, std::make_shared<NullBusLock>(), settings);

	EXPECT_TRUE(fpgaEmu->readField("UartRxEnableControl") == 1);
	EXPECT_TRUE(fpgaEmu->readField("UartTxEnableControl") == 0);

    // sequences
    SEQ_START(LessThanBlockSize);

	EXPECT_TRUE(serialBus.writeData(txData));

    SEQ_END(LessThanBlockSize);
}

TEST_F(Rs485FpgaBusTestFixture, writeDataEqBlockSize)
{

	static const OffTargetFPGA::SequenceCheck EqBlockSizeSeqData[] = {
			OffTargetFPGA::SequenceCheck(0xBE, 0x0000, 0x0001),
			OffTargetFPGA::SequenceCheck(0xBE, 0x0002, 0x0002),
			OffTargetFPGA::SequenceCheck(0xBE, 0x0002, 0x0004),
			OffTargetFPGA::SequenceCheck(0xBC, 0x0003, 0x0004),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0000, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0001, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0002, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0003, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0004, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0005, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0006, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0007, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0008, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0009, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000A, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000B, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000C, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000D, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000E, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000F, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0010, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0011, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0012, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0013, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0014, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0015, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0016, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0017, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0018, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0019, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001A, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001B, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001C, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001D, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001E, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001F, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0020, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0021, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0022, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0023, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0024, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0025, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0026, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0027, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0028, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0029, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002A, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002B, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002C, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002D, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002E, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002F, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0030, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0031, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0032, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0033, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0034, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0035, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0036, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0037, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0038, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0039, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003A, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003B, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003C, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003D, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003E, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003F, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xBE, 0x0006, 0x0004),
			OffTargetFPGA::SequenceCheck(0xBC, 0x0007, 0x0004)
	};

	(void)EqBlockSizeSeqData;

    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    restartFpgaEmulator() ;

    // Initialise the FPGA UART
    fpgaEmu->writeField("UartTxBufferEmpty", 1);
    fpgaEmu->writeField("UartTxBufferFull", 0);
    fpgaEmu->writeField("UartRxDataPresent", 0);
    fpgaEmu->writeField("UartRxFrameError", 0);
    fpgaEmu->writeField("UartRxOverrunError", 0);

    std::vector<uint8_t> txData;

    for (unsigned int index = 0; index < 64; index++)
    {
    	txData.push_back(index);
    }

	std::shared_ptr<IBusSettings> settings(std::make_shared<BusSettings>());

	Rs485BusFpga serialBus("Fpga Rs485 bus", "Test bus", 9600, std::make_shared<NullBusLock>(), settings);

	EXPECT_TRUE(fpgaEmu->readField("UartRxEnableControl") == 1);
	EXPECT_TRUE(fpgaEmu->readField("UartTxEnableControl") == 0);

    // sequences
    SEQ_START(EqBlockSize);

	EXPECT_TRUE(serialBus.writeData(txData));

    SEQ_END(EqBlockSize);
}

TEST_F(Rs485FpgaBusTestFixture, writeDataMoreThanBlockSize)
{

	static const OffTargetFPGA::SequenceCheck MoreThanBlockSizeSeqData[] = {
			OffTargetFPGA::SequenceCheck(0xBE, 0x0000, 0x0001),
			OffTargetFPGA::SequenceCheck(0xBE, 0x0002, 0x0002),
			OffTargetFPGA::SequenceCheck(0xBE, 0x0002, 0x0004),
			OffTargetFPGA::SequenceCheck(0xBC, 0x0003, 0x0004),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0000, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0001, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0002, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0003, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0004, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0005, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0006, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0007, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0008, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0009, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000A, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000B, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000C, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000D, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000E, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x000F, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0010, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0011, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0012, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0013, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0014, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0015, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0016, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0017, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0018, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0019, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001A, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001B, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001C, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001D, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001E, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x001F, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0020, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0021, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0022, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0023, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0024, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0025, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0026, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0027, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0028, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0029, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002A, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002B, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002C, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002D, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002E, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x002F, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0030, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0031, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0032, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0033, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0034, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0035, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0036, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0037, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0038, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0039, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003A, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003B, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003C, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003D, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003E, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x003F, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xBC, 0x0007, 0x0004),
			OffTargetFPGA::SequenceCheck(0xBC, 0x0003, 0x0004),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0040, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0041, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0042, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0043, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xB2, 0x0044, 0x00ff),
			OffTargetFPGA::SequenceCheck(0xBE, 0x0006, 0x0004),
			OffTargetFPGA::SequenceCheck(0xBC, 0x0007, 0x0004)
	};

	(void)MoreThanBlockSizeSeqData;

    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    restartFpgaEmulator() ;

    // Initialise the FPGA UART
    fpgaEmu->writeField("UartTxBufferEmpty", 1);
    fpgaEmu->writeField("UartTxBufferFull", 0);
    fpgaEmu->writeField("UartRxDataPresent", 0);
    fpgaEmu->writeField("UartRxFrameError", 0);
    fpgaEmu->writeField("UartRxOverrunError", 0);

    std::vector<uint8_t> txData;

    for (unsigned int index = 0; index < 69; index++)
    {
    	txData.push_back(index);
    }

	std::shared_ptr<IBusSettings> settings(std::make_shared<BusSettings>());

	Rs485BusFpga serialBus("Fpga Rs485 bus", "Test bus", 9600, std::make_shared<NullBusLock>(), settings);

	EXPECT_TRUE(fpgaEmu->readField("UartRxEnableControl") == 1);
	EXPECT_TRUE(fpgaEmu->readField("UartTxEnableControl") == 0);

    // sequences
    SEQ_START(MoreThanBlockSize);

	EXPECT_TRUE(serialBus.writeData(txData));

    SEQ_END(MoreThanBlockSize);
}

TEST_F(Rs485FpgaBusTestFixture, writeDataTimeout)
{
    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    restartFpgaEmulator() ;

    // Initialise the FPGA UART
    // Tx buffer is full, so write times out
    fpgaEmu->writeField("UartTxBufferEmpty", 0);
    fpgaEmu->writeField("UartTxBufferFull", 1);
    fpgaEmu->writeField("UartRxDataPresent", 0);
    fpgaEmu->writeField("UartRxFrameError", 0);
    fpgaEmu->writeField("UartRxOverrunError", 0);

    std::vector<uint8_t> txData;

    for (unsigned int index = 0; index < 5; index++)
    {
    	txData.push_back(index);
    }

	std::shared_ptr<IBusSettings> settings(std::make_shared<BusSettings>());

	Rs485BusFpga serialBus("Fpga Rs485 bus", "Test bus", 9600, std::make_shared<NullBusLock>(), settings);

	EXPECT_TRUE(fpgaEmu->readField("UartRxEnableControl") == 1);
	EXPECT_TRUE(fpgaEmu->readField("UartTxEnableControl") == 0);

	EXPECT_FALSE(serialBus.writeData(txData));
}
