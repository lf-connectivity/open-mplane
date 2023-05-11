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

#include "ITemperatureSensorDriver.h"
#include "SensorsTestCase.h"
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
TEST_F(SensorsTestCase, readTemperature)
{
	cout << "SensorsTestCase - Read temperature" << endl;

	std::shared_ptr<II2cBus> bus = std::make_shared<TestI2cBus>("Test bus", "Testing");
	std::shared_ptr<ITemperatureSensorDriver> nxp = std::make_shared<NXPLM75B>(bus, "Sensor1");

	Temperature val(0.0);

	bus->writeShort(0, 0x007F);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), 127.0);

	bus->writeShort(0, 0xE07E);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), 126.875);

	bus->writeShort(0, 0x207E);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), 126.125);

	bus->writeShort(0, 0x007D);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), 125.0);

	bus->writeShort(0, 0x0019);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), 25.0);

	bus->writeShort(0, 0x2000);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), 0.125);

	bus->writeShort(0, 0x0);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), 0.0);

	bus->writeShort(0, 0xE0FF);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), -0.125);

	bus->writeShort(0, 0x00E7);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), -25.0);

	bus->writeShort(0, 0x20C9);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), -54.875);

	bus->writeShort(0, 0x00C9);
	val = nxp->getTemperature();
	EXPECT_EQ(val.get(), -55.0);
}
