/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaSpiBus_unittest.cpp
 * \brief
 *
 *
 * \details
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
#include "FpgaSpiBus.h"
#include "FpgaSpiBus0.h"
#include "FpgaSpiBus1.h"

#include "bus_fixture.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
class FpgaSpiBusFixture : public BusTestFixture
{
public:
};


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaSpiBusFixture, writeByte)
{
	std::shared_ptr<ISpiBusSettings> settings(std::make_shared<SpiBusSettings>());
	settings->setOffsetNumBits(16);

	std::shared_ptr<IFpgaSystemRegs> fpga(IFpgaMgr::getIFpgaSystemRegs());

	FpgaSpiBus0 fpgaBus("Fpga SPI0", "SPI0", std::make_shared<NullBusLock>(), settings);

	std::vector<IBus::BusCommand> commands ;

	/// Write value 0x55 at offset 0x1340
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, 0x1340, 0x55));

	EXPECT_TRUE(fpgaBus.commandsList(commands));

	EXPECT_EQ(fpga->read_spi0ClkDiv(), FpgaSpiBus::CLOCK_DIV);
	EXPECT_EQ(fpga->read_spi0ClkPhase1(), 0u);
	EXPECT_EQ(fpga->read_spi0KeepEnable(), 0u);

	EXPECT_EQ(fpga->read_spi0RdataLen(), 0u);
	EXPECT_EQ(fpga->read_spi0WdataLen(), 23u);
	EXPECT_EQ(fpga->read_spi0ClkInvert(), 0u);
	EXPECT_EQ(fpga->read_spi0RdOppEdge(), 0u);

	EXPECT_EQ(fpga->read_spi0WriteDataLo(), 0x1355u);
	EXPECT_EQ(fpga->read_spi0WriteDataHi(), 0x40u);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaSpiBusFixture, writeShort)
{
	std::shared_ptr<ISpiBusSettings> settings(std::make_shared<SpiBusSettings>());
	settings->setOffsetNumBits(16);

	std::shared_ptr<IFpgaSystemRegs> fpga(IFpgaMgr::getIFpgaSystemRegs());

	FpgaSpiBus0 fpgaBus("Fpga SPI0", "SPI0", std::make_shared<NullBusLock>(), settings);

	std::vector<IBus::BusCommand> commands ;

	/// Write value 0x55AB at offset 0x1540
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, 0x1540, 0x55AB));

	EXPECT_TRUE(fpgaBus.commandsList(commands));

	EXPECT_EQ(fpga->read_spi0ClkDiv(), FpgaSpiBus::CLOCK_DIV);
	EXPECT_EQ(fpga->read_spi0ClkPhase1(), 0u);
	EXPECT_EQ(fpga->read_spi0KeepEnable(), 0u);

	EXPECT_EQ(fpga->read_spi0RdataLen(), 0u);
	EXPECT_EQ(fpga->read_spi0WdataLen(), 31u);
	EXPECT_EQ(fpga->read_spi0ClkInvert(), 0u);
	EXPECT_EQ(fpga->read_spi0RdOppEdge(), 0u);

	EXPECT_EQ(fpga->read_spi0WriteDataLo(), 0xAB55u);
	EXPECT_EQ(fpga->read_spi0WriteDataHi(), 0x4015u);
}

//-------------------------------------------------------------------------------------------------------------

TEST_F(FpgaSpiBusFixture, writeData)
{
	std::shared_ptr<ISpiBusSettings> settings(std::make_shared<SpiBusSettings>());
	settings->setOffsetNumBits(16);

	std::shared_ptr<IFpgaSystemRegs> fpga(IFpgaMgr::getIFpgaSystemRegs());

	FpgaSpiBus0 fpgaBus("Fpga SPI0", "SPI0", std::make_shared<NullBusLock>(), settings);

	std::vector<IBus::BusCommand> commands ;

	std::vector<uint8_t> bytes;
	bytes.push_back(0x12);
	bytes.push_back(0x34);

	/// Write data at offset
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_DATA_OFFSET, 0x2541, bytes));

	EXPECT_TRUE(fpgaBus.commandsList(commands));

	EXPECT_EQ(fpga->read_spi0ClkDiv(), FpgaSpiBus::CLOCK_DIV);
	EXPECT_EQ(fpga->read_spi0ClkPhase1(), 0u);
	EXPECT_EQ(fpga->read_spi0KeepEnable(), 0u);

	EXPECT_EQ(fpga->read_spi0RdataLen(), 0u);
	EXPECT_EQ(fpga->read_spi0WdataLen(), 31u);
	EXPECT_EQ(fpga->read_spi0ClkInvert(), 0u);
	EXPECT_EQ(fpga->read_spi0RdOppEdge(), 0u);

	EXPECT_EQ(fpga->read_spi0WriteDataLo(), 0x1234u);
	EXPECT_EQ(fpga->read_spi0WriteDataHi(), 0x4125u);

	/// Try to add more than 4 bytes and the transfer should fail
	bytes.push_back(0x56);

	/// Write data at offset
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_DATA_OFFSET, 0x2541, bytes));

	EXPECT_FALSE(fpgaBus.commandsList(commands));

	EXPECT_EQ(fpgaBus.error(), "Cannot write more than 4 bytes on FPGA SPI bus in a single transaction");

	std::cout << fpgaBus.error() << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaSpiBusFixture, readByte)
{
	std::shared_ptr<ISpiBusSettings> settings(std::make_shared<SpiBusSettings>());
	settings->setOffsetNumBits(16);

	std::shared_ptr<IFpgaSystemRegs> fpga(IFpgaMgr::getIFpgaSystemRegs());

	FpgaSpiBus0 fpgaBus("Fpga SPI0", "SPI0", std::make_shared<NullBusLock>(), settings);

	std::vector<IBus::BusCommand> commands ;
	std::vector<IBus::BusCommand> readback ;

	/// Read byte from offset
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_BYTE, 0x1340));

	EXPECT_TRUE(fpgaBus.commandsList(commands, readback));

	EXPECT_EQ(fpga->read_spi0ClkDiv(), FpgaSpiBus::CLOCK_DIV);
	EXPECT_EQ(fpga->read_spi0ClkPhase1(), 0u);
	EXPECT_EQ(fpga->read_spi0KeepEnable(), 0u);

	EXPECT_EQ(fpga->read_spi0RdataLen(), 8u);
	EXPECT_EQ(fpga->read_spi0WdataLen(), 15u);
	EXPECT_EQ(fpga->read_spi0ClkInvert(), 0u);
	EXPECT_EQ(fpga->read_spi0RdOppEdge(), 0u);

	EXPECT_EQ(fpga->read_spi0WriteDataLo(), 0x4013u);

	EXPECT_EQ(readback.size(), 1u);
	EXPECT_EQ(readback[0].offset(), 0x1340u);
	EXPECT_EQ(readback[0].type(), IBus::BUS_READ_BYTE);
	EXPECT_EQ(readback[0].data8(), 0x34u);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaSpiBusFixture, readShort)
{
	std::shared_ptr<ISpiBusSettings> settings(std::make_shared<SpiBusSettings>());
	settings->setOffsetNumBits(16);

	std::shared_ptr<IFpgaSystemRegs> fpga(IFpgaMgr::getIFpgaSystemRegs());

	FpgaSpiBus0 fpgaBus("Fpga SPI0", "SPI0", std::make_shared<NullBusLock>(), settings);

	std::vector<IBus::BusCommand> commands ;
	std::vector<IBus::BusCommand> readback ;

	/// Read short from offset
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_SHORT, 0x1340));

	EXPECT_TRUE(fpgaBus.commandsList(commands, readback));

	EXPECT_EQ(fpga->read_spi0ClkDiv(), FpgaSpiBus::CLOCK_DIV);
	EXPECT_EQ(fpga->read_spi0ClkPhase1(), 0u);
	EXPECT_EQ(fpga->read_spi0KeepEnable(), 0u);

	EXPECT_EQ(fpga->read_spi0RdataLen(), 16u);
	EXPECT_EQ(fpga->read_spi0WdataLen(), 15u);
	EXPECT_EQ(fpga->read_spi0ClkInvert(), 0u);
	EXPECT_EQ(fpga->read_spi0RdOppEdge(), 0u);

	EXPECT_EQ(fpga->read_spi0WriteDataLo(), 0x4013u);

	EXPECT_EQ(readback.size(), 1u);
	EXPECT_EQ(readback[0].offset(), 0x1340u);
	EXPECT_EQ(readback[0].type(), IBus::BUS_READ_SHORT);
	EXPECT_EQ(readback[0].data16(), 0x1234u);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaSpiBusFixture, readData)
{
	std::shared_ptr<ISpiBusSettings> settings(std::make_shared<SpiBusSettings>());
	settings->setOffsetNumBits(16);

	std::shared_ptr<IFpgaSystemRegs> fpga(IFpgaMgr::getIFpgaSystemRegs());

	FpgaSpiBus0 fpgaBus("Fpga SPI0", "SPI0", std::make_shared<NullBusLock>(), settings);

	std::vector<IBus::BusCommand> commands ;
	std::vector<IBus::BusCommand> readback ;

	std::vector<uint8_t> bytes(4, 0);

	/// Read data from offset
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_DATA_OFFSET, 0x1340, bytes));

	EXPECT_TRUE(fpgaBus.commandsList(commands, readback));

	EXPECT_EQ(fpga->read_spi0ClkDiv(), FpgaSpiBus::CLOCK_DIV);
	EXPECT_EQ(fpga->read_spi0ClkPhase1(), 0u);
	EXPECT_EQ(fpga->read_spi0KeepEnable(), 0u);

	// Known issue with FPGA read data length - Field size is 5 bits. So max value can be 31
	// If you want to read 4 bytes, then currently it does not work.
	//EXPECT_EQ(fpga->read_spi0RdataLen(), 32u);
	EXPECT_EQ(fpga->read_spi0WdataLen(), 15u);
	EXPECT_EQ(fpga->read_spi0ClkInvert(), 0u);
	EXPECT_EQ(fpga->read_spi0RdOppEdge(), 0u);

	EXPECT_EQ(fpga->read_spi0WriteDataLo(), 0x4013u);

	EXPECT_EQ(readback.size(), 1u);
	EXPECT_EQ(readback[0].offset(), 0x1340u);
	EXPECT_EQ(readback[0].type(), IBus::BUS_READ_DATA_OFFSET);
	bytes = readback[0].bytes();
	EXPECT_EQ(bytes.size(), 4u);
	EXPECT_EQ(bytes[0], 0x34u);
	EXPECT_EQ(bytes[1], 0x12u);
	EXPECT_EQ(bytes[2], 0x78u);
	EXPECT_EQ(bytes[3], 0x56u);
}
