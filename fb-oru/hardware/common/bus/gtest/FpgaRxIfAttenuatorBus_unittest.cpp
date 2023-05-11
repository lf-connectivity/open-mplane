/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaRxIfAttenuatorBus_unittest.cpp
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
#include "FpgaRxIfAttenuatorBus.h"

#include "bus_fixture.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
class FpgaRxIfAttenuatorBusFixture : public BusTestFixture
{
public:
};


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaRxIfAttenuatorBusFixture, writeByte)
{
	std::shared_ptr<ISpiBusSettings> settings(std::make_shared<SpiBusSettings>());

	auto fpga(IFpgaMgr::getIFpgaAntennaRegs()) ;

	uint8_t index = 0;

	FpgaRxIfAttenuatorBus fpgaRx1Bus("Fpga Rx1 IF Attn bus", "Rx1", std::make_shared<NullBusLock>(), settings, index);

	std::vector<IBus::BusCommand> commands ;

	/// Write a byte
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, 0, 0x55));

	// Reset attenuation update flag
	fpga->write_spi_rx_if_atten_update(0);

	// Execute the command list
	EXPECT_TRUE(fpgaRx1Bus.commandsList(commands));

	// Check that the byte is written in the attenuation register and the update flag is set
	EXPECT_EQ(fpga->read_spi_rx_if_atten(index), 0x55u);
	EXPECT_EQ(fpga->read_spi_rx_if_atten_update(), 1u);

	index = 1;
	FpgaRxIfAttenuatorBus fpgaRx2Bus("Fpga Rx2 IF Attn bus", "Rx2", std::make_shared<NullBusLock>(), settings, index);

	commands.clear();
	/// Write a byte
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, 0, 0x4B));

	// Reset attenuation update flag
	fpga->write_spi_rx_if_atten_update(0);

	// Execute the command list
	EXPECT_TRUE(fpgaRx2Bus.commandsList(commands));

	// Check that the byte is written in the attenuation register and the update flag is set
	EXPECT_EQ(fpga->read_spi_rx_if_atten(index), 0x4Bu);
	EXPECT_EQ(fpga->read_spi_rx_if_atten_update(), 1u);

	index = 2;
	FpgaRxIfAttenuatorBus fpgaRx3Bus("Fpga Rx3 IF Attn bus", "Rx3", std::make_shared<NullBusLock>(), settings, index);

	commands.clear();
	/// Write a byte
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, 0, 0x3D));

	// Reset attenuation update flag
	fpga->write_spi_rx_if_atten_update(0);

	// Execute the command list
	EXPECT_TRUE(fpgaRx3Bus.commandsList(commands));

	// Check that the byte is written in the attenuation register and the update flag is set
	EXPECT_EQ(fpga->read_spi_rx_if_atten(index), 0x3Du);
	EXPECT_EQ(fpga->read_spi_rx_if_atten_update(), 1u);

	index = 3;
	FpgaRxIfAttenuatorBus fpgaRx4Bus("Fpga Rx4 IF Attn bus", "Rx4", std::make_shared<NullBusLock>(), settings, index);

	commands.clear();
	/// Write a byte
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, 0, 0x78));

	// Reset attenuation update flag
	fpga->write_spi_rx_if_atten_update(0);

	// Execute the command list
	EXPECT_TRUE(fpgaRx4Bus.commandsList(commands));

	// Check that the byte is written in the attenuation register and the update flag is set
	EXPECT_EQ(fpga->read_spi_rx_if_atten(index), 0x78u);
	EXPECT_EQ(fpga->read_spi_rx_if_atten_update(), 1u);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaRxIfAttenuatorBusFixture, invalidWrCommands)
{
	std::shared_ptr<ISpiBusSettings> settings(std::make_shared<SpiBusSettings>());

	auto fpga(IFpgaMgr::getIFpgaAntennaRegs()) ;

	uint8_t index = 0;

	FpgaRxIfAttenuatorBus fpgaRx1Bus("Fpga Rx1 IF Attn bus", "Rx1", std::make_shared<NullBusLock>(), settings, index);

	std::vector<IBus::BusCommand> commands ;

	/// Write short
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, 0, 0x5512));

	// Command not supported
	EXPECT_FALSE(fpgaRx1Bus.commandsList(commands));

	/// Write word
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_WORD, 0, 0x5512));

	// Command not supported
	EXPECT_FALSE(fpgaRx1Bus.commandsList(commands));

	/// Write data
	std::vector<uint8_t> bytes(2,0);
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_DATA, bytes));

	// Command not supported
	EXPECT_FALSE(fpgaRx1Bus.commandsList(commands));

	/// Write data at offset
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_DATA_OFFSET, 0, bytes));

	// Command not supported
	EXPECT_FALSE(fpgaRx1Bus.commandsList(commands));
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaRxIfAttenuatorBusFixture, invalidRdCommands)
{
	std::shared_ptr<ISpiBusSettings> settings(std::make_shared<SpiBusSettings>());

	auto fpga(IFpgaMgr::getIFpgaAntennaRegs()) ;

	uint8_t index = 0;

	FpgaRxIfAttenuatorBus fpgaRx1Bus("Fpga Rx1 IF Attn bus", "Rx1", std::make_shared<NullBusLock>(), settings, index);

	std::vector<IBus::BusCommand> commands ;
	std::vector<IBus::BusCommand> readback ;

	/// Read byte
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_BYTE, 0));

	// Command not supported
	EXPECT_FALSE(fpgaRx1Bus.commandsList(commands, readback));

	/// Read short
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_SHORT, 0));

	// Command not supported
	EXPECT_FALSE(fpgaRx1Bus.commandsList(commands, readback));

	/// Read word
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_WORD, 0));

	// Command not supported
	EXPECT_FALSE(fpgaRx1Bus.commandsList(commands, readback));

	/// Read data
	std::vector<uint8_t> bytes(2,0);
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_DATA_OFFSET, 0, bytes));

	// Command not supported
	EXPECT_FALSE(fpgaRx1Bus.commandsList(commands, readback));
}
