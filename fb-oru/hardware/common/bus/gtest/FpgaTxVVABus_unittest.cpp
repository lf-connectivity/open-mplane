/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaTxVVABus_unittest.cpp
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
#include "FpgaTxVVABus.h"

#include "bus_fixture.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
class FpgaTxVVABusFixture : public BusTestFixture
{
public:
};


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaTxVVABusFixture, writeShort)
{
	std::shared_ptr<IBusSettings> settings(std::make_shared<BusSettings>());

	auto fpga(IFpgaMgr::getIFpgaAntennaRegs()) ;

	uint8_t index = 0;

	FpgaTxVVABus fpgaTx1VVABus("Fpga Tx1 VVA bus", "Tx1", std::make_shared<NullBusLock>(), settings, index);

	std::vector<IBus::BusCommand> commands ;

	/// Write data
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, 0, 0x1BCD));

	// Execute the command list
	EXPECT_TRUE(fpgaTx1VVABus.commandsList(commands));

	// Check that the data is written in the attenuation register
	EXPECT_EQ(fpga->read_txVattenRaw(index), 0x1BCDu);

	index = 1;
	FpgaTxVVABus fpgaTx2VVABus("Fpga Tx2 VVA bus", "Tx2", std::make_shared<NullBusLock>(), settings, index);

	/// Write data
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, 0, 0x1234));

	// Execute the command list
	EXPECT_TRUE(fpgaTx2VVABus.commandsList(commands));

	// Check that the data is written in the attenuation register
	EXPECT_EQ(fpga->read_txVattenRaw(index), 0x1234u);

	index = 2;
	FpgaTxVVABus fpgaTx3VVABus("Fpga Tx3 VVA bus", "Tx3", std::make_shared<NullBusLock>(), settings, index);

	/// Write data
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, 0, 0x3FFF));

	// Execute the command list
	EXPECT_TRUE(fpgaTx3VVABus.commandsList(commands));

	// Check that the data is written in the attenuation register
	EXPECT_EQ(fpga->read_txVattenRaw(index), 0x3FFFu);

	index = 3;
	FpgaTxVVABus fpgaTx4VVABus("Fpga Tx4 VVA bus", "Tx4", std::make_shared<NullBusLock>(), settings, index);

	/// Write data
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, 0, 0x2678));

	// Execute the command list
	EXPECT_TRUE(fpgaTx4VVABus.commandsList(commands));

	// Check that the data is written in the attenuation register
	EXPECT_EQ(fpga->read_txVattenRaw(index), 0x2678u);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaTxVVABusFixture, invalidWrCommands)
{
	std::shared_ptr<IBusSettings> settings(std::make_shared<BusSettings>());

	auto fpga(IFpgaMgr::getIFpgaAntennaRegs()) ;

	uint8_t index = 0;

	FpgaTxVVABus fpgaTx1VVABus("Fpga Tx1 VVA bus", "Tx1", std::make_shared<NullBusLock>(), settings, index);

	std::vector<IBus::BusCommand> commands ;

	/// Write byte
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, 0, 0x55));

	// Command not supported
	EXPECT_FALSE(fpgaTx1VVABus.commandsList(commands));

	/// Write word
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_WORD, 0, 0x5512));

	// Command not supported
	EXPECT_FALSE(fpgaTx1VVABus.commandsList(commands));

	/// Write data
	std::vector<uint8_t> bytes(2,0);
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_DATA, bytes));

	// Command not supported
	EXPECT_FALSE(fpgaTx1VVABus.commandsList(commands));

	/// Write data at offset
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_DATA_OFFSET, 0, bytes));

	// Command not supported
	EXPECT_FALSE(fpgaTx1VVABus.commandsList(commands));
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaTxVVABusFixture, invalidRdCommands)
{
	std::shared_ptr<ISpiBusSettings> settings(std::make_shared<SpiBusSettings>());

	auto fpga(IFpgaMgr::getIFpgaAntennaRegs()) ;

	uint8_t index = 0;

	FpgaTxVVABus fpgaTx1VVABus("Fpga Tx1 VVA bus", "Tx1", std::make_shared<NullBusLock>(), settings, index);

	std::vector<IBus::BusCommand> commands ;
	std::vector<IBus::BusCommand> readback ;

	/// Read byte
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_BYTE, 0));

	// Command not supported
	EXPECT_FALSE(fpgaTx1VVABus.commandsList(commands, readback));

	/// Read short
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_SHORT, 0));

	// Command not supported
	EXPECT_FALSE(fpgaTx1VVABus.commandsList(commands, readback));

	/// Read word
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_WORD, 0));

	// Command not supported
	EXPECT_FALSE(fpgaTx1VVABus.commandsList(commands, readback));

	/// Read data
	std::vector<uint8_t> bytes(2,0);
	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_DATA_OFFSET, 0, bytes));

	// Command not supported
	EXPECT_FALSE(fpgaTx1VVABus.commandsList(commands, readback));
}
