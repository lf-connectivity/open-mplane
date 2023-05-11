/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NxpBap70QTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "NxpBap70QTestCase.h"

#include "TestBus.h"

using namespace std;

using namespace Mplane;

/*
 * Unit test fixtures
 */
//-------------------------------------------------------------------------------------------------------------
TEST_F(NxpBap70QTestCase, calculateControl)
{
	cout << "NxpBap70QTestCase - CalcControl" << endl;

	std::shared_ptr<IBus> bus = std::make_shared<TestBus>("Test bus", "Testing");
	std::shared_ptr<IAttenuatorDriver> attn = std::make_shared<NxpBap70Q>(bus, "Attn1", -50, 0);

	/// Check if control value is calculated correctly
	EXPECT_EQ(attn->calcControl(Power(-50.0)), 326u);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(NxpBap70QTestCase, applyAtten)
{
	cout << "NxpBap70QTestCase - Apply attenuation" << endl;

	std::shared_ptr<IBus> bus = std::make_shared<TestBus>("Test bus", "Testing");
	std::shared_ptr<IAttenuatorDriver> attn = std::make_shared<NxpBap70Q>(bus, "Attn1", -50, 0);

	uint16_t val = 0;

	/// Apply attenuation value
	attn->applyAttenuation(16383);

	/// Now read the val using the bus and verify
	bus->readShort(0, val);
	EXPECT_EQ(val, 16383u);

	/// Apply attenuation value
	attn->applyAttenuation(0);

	/// Now read the val using the bus and verify
	bus->readShort(0, val);
	EXPECT_EQ(val, 0u);

	/// Apply attenuation value
	attn->applyAttenuation(326);

	/// Now read the val using the bus and verify
	bus->readShort(0, val);
	EXPECT_EQ(val, 326u);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(NxpBap70QTestCase, minMaxAtten)
{
	cout << "NxpBap70QTestCase - MinMax attenuation" << endl;

	std::shared_ptr<IBus> bus = std::make_shared<TestBus>("Test bus", "Testing");
	std::shared_ptr<IAttenuatorDriver> attn = std::make_shared<NxpBap70Q>(bus, "Attn1", 1.3, 69.2);

	/// Verify min and max value
	EXPECT_EQ(attn->getMinAttenuation(), 1.3);
	EXPECT_EQ(attn->getMaxAttenuation(), 69.2);
}
