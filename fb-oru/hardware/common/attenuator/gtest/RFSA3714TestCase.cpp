/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RFSA3714TestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "RFSA3714TestCase.h"

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
TEST_F(RFSA3714TestCase, calculateControl)
{
	cout << "RFSA3714TestCase - CalcControl" << endl;

	std::shared_ptr<ISpiBus> bus = std::make_shared<TestSpiBus>("Test bus", "Testing");
	std::shared_ptr<IAttenuatorDriver> attn = std::make_shared<RFSA3714>(bus, "Attn1", 0, 32);

	/// Check if control value is calculated correctly
	EXPECT_EQ(attn->calcControl(Power(21.0)), 84u);

	EXPECT_EQ(attn->calcControl(Power(0.0)), 0u);

	EXPECT_EQ(attn->calcControl(Power(32.0)), 128u);

	EXPECT_EQ(attn->calcControl(Power(15.2)), 61u);

	EXPECT_EQ(attn->calcControl(Power(9.8)), 39u);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(RFSA3714TestCase, calcAttenuation)
{
	cout << "RFSA3714TestCase - calcAttenuation" << endl;

	std::shared_ptr<ISpiBus> bus = std::make_shared<TestSpiBus>("Test bus", "Testing");
	std::shared_ptr<IAttenuatorDriver> attn = std::make_shared<RFSA3714>(bus, "Attn1", 0, 32);

	/// Check if control value is calculated correctly
	EXPECT_EQ(attn->calcAttenuation(84), Power(21.0));

	EXPECT_EQ(attn->calcAttenuation(0), Power(0.0));

	EXPECT_EQ(attn->calcAttenuation(128), Power(32.0));

	EXPECT_EQ(attn->calcAttenuation(60), Power(15.0));

	EXPECT_EQ(attn->calcAttenuation(39), Power(9.75));
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(RFSA3714TestCase, applyAtten)
{
	cout << "RFSA3714TestCase - Apply attenuation" << endl;

	std::shared_ptr<ISpiBus> bus = std::make_shared<TestSpiBus>("Test bus", "Testing");
	std::shared_ptr<IAttenuatorDriver> attn = std::make_shared<RFSA3714>(bus, "Attn1", 0, 32);

	uint8_t byte = 0;

	/// Apply attenuation value
	attn->applyAttenuation(84);

	/// Now read the byte using the bus and verify
	bus->readByte(0, byte);
	EXPECT_EQ(byte, 84u);

	/// Apply attenuation value
	attn->applyAttenuation(0);

	/// Now read the byte using the bus and verify
	bus->readByte(0, byte);
	EXPECT_EQ(byte, 0u);

	/// Apply attenuation value
	attn->applyAttenuation(123);

	/// Now read the byte using the bus and verify
	bus->readByte(0, byte);
	EXPECT_EQ(byte, 123u);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(RFSA3714TestCase, minMaxAtten)
{
	cout << "RFSA3714TestCase - MinMax attenuation" << endl;

	std::shared_ptr<ISpiBus> bus = std::make_shared<TestSpiBus>("Test bus", "Testing");
	std::shared_ptr<IAttenuatorDriver> attn = std::make_shared<RFSA3714>(bus, "Attn1", 1.3, 69.2);

	/// Verify min and max value
	EXPECT_EQ(attn->getMinAttenuation(), 1.3);
	EXPECT_EQ(attn->getMaxAttenuation(), 69.2);
}
