/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Mcp23S17SpiTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "Mcp23S17SpiTestCase.h"
#include "TestBus.h"

using namespace std;

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRegData> Mplane::IRegData::singleton()
{
    static std::shared_ptr<IRegData> _pInstance(new RegData());

    return _pInstance;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RegData::getRegisterData(std::string driverName, std::vector< std::pair< uint32_t, uint32_t> > & regData )
{
	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RegData::getRegisterData(std::string driverName, std::vector< uint32_t > & regData )
{
	return ReturnType::RT_OK;
}

/*
 * Unit test fixtures
 */
//-------------------------------------------------------------------------------------------------------------
TEST_F(Mcp23S17SpiTestCase, writePort)
{
	cout << "Mcp23S17SpiTestCase - Write Port" << endl;

	std::shared_ptr<ISpiBus> bus = std::make_shared<TestSpiBus>("Test bus", "Testing");
	std::shared_ptr<IGpioExpDriver> gpioExp = std::make_shared<Mcp23S17Spi>(bus, "GpioExp1");

	uint8_t byte = 0;

	/// Write port A and verify value
	gpioExp->write8BitPort(0, 0x55);

	/// The latch value should resemble the port value
	bus->writeByte(((uint16_t)MCP23S17::OLATA << 8) | MCP23S17::RD_Opcode, 0x55);

	/// Now read the byte using the bus and verify
	bus->readByte(((uint16_t)MCP23S17::GPIOA << 8) | MCP23S17::WR_Opcode, byte);
	EXPECT_EQ(byte, 0x55);

	/// Write upper nibble of port A and verify value
	gpioExp->write8BitPort(0, 0xA2, 0xF0);
	bus->readByte(((uint16_t)MCP23S17::GPIOA << 8) | MCP23S17::WR_Opcode, byte);
	EXPECT_EQ(byte, 0xA5);


	/// Write port B and verify value
	gpioExp->write8BitPort(1, 0xAA);

	/// The latch value should resemble the port value
	bus->writeByte(((uint16_t)MCP23S17::OLATB << 8) | MCP23S17::RD_Opcode, 0xAA);

	/// Now read the byte using the bus and verify
	bus->readByte(((uint16_t)MCP23S17::GPIOB << 8) | MCP23S17::WR_Opcode, byte);
	EXPECT_EQ(byte, 0xAA);

	/// Write some bits of port B and verify value
	gpioExp->write8BitPort(1, 0x47, 0x24);
	bus->readByte(((uint16_t)MCP23S17::GPIOB << 8) | MCP23S17::WR_Opcode, byte);
	EXPECT_EQ(byte, 0x8E);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(Mcp23S17SpiTestCase, readPort)
{
	cout << "Mcp23S17SpiTestCase - Read Port" << endl;

	std::shared_ptr<ISpiBus> bus = std::make_shared<TestSpiBus>("Test bus", "Testing");
	std::shared_ptr<IGpioExpDriver> gpioExp = std::make_shared<Mcp23S17Spi>(bus, "GpioExp1");

	uint8_t byte = 0;

	/// Write port A and verify value
	bus->writeByte(((uint16_t)MCP23S17::GPIOA << 8) | MCP23S17::RD_Opcode, 0x5C);

	/// Now read the byte using the bus and verify
	gpioExp->read8BitPort(0, byte);
	EXPECT_EQ(byte, 0x5C);

	/// Write port B and verify value
	bus->writeByte(((uint16_t)MCP23S17::GPIOB << 8) | MCP23S17::RD_Opcode, 0xAB);

	/// Now read the byte using the bus and verify
	gpioExp->read8BitPort(1, byte);
	EXPECT_EQ(byte, 0xAB);
}
