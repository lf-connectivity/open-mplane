
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LedSX1509bTestCase.cpp
 * \brief     SX1509b LED driver test cases
 *
 *
 * \details   Pure virtual interface that defines methods needed to access the
 *            LED indicators.
 *
 */

#include <stdexcept>
#include <memory>
#include <string.h>
#include <iostream>

#include "GlobalTypeDefs.h"

#include "gtest/gtest.h"

#include "LedSystemTestCase.h"

#include "ILed.h"
#include "LedSystem.h"

namespace Mplane
{



// Test objects

Mplane::TestLedSystem::TestLedSystem(): mName ( "Mplane::TestLedSystem" )
{
}

Mplane::TestLedSystem::~TestLedSystem()
{
    std::cout << "Mplane::TestLedSystem destructor" << std::endl;
    mName = NULL;
}

/*
 * Unit tests
 */
void Mplane::LedSystemTestCases::SetUp()
{

}

void Mplane::LedSystemTestCases::TearDown()
{
}

void Mplane::LedSystemTestCases::unittest()
{
    const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

    // Check the basics work first.
    LedSystem* led = new LedSystem(0x800);
    ASSERT_TRUE( led != (void *)0 );

    led->show(); // Show the limited device information

    // Set led on/off bounds check
    ASSERT_TRUE(ReturnType::RT_OK == led->setLed( LedSystem::systemLed, ILed::LED_RED, ILed::LED_OFF,    0 ));
    ASSERT_TRUE(ReturnType::RT_OK == led->setLed( LedSystem::systemLed, ILed::LED_RED, ILed::LED_ON,     0 ));
    ASSERT_TRUE(ReturnType::RT_OK == led->setLed( LedSystem::systemLed, ILed::LED_RED, ILed::LED_FLASH,  10 ));
    ASSERT_TRUE(ReturnType::RT_NOT_SUPPORTED == led->setLed( LedSystem::systemLed, ILed::LED_RED, ILed::LED_BREATH, 6 ));

    ASSERT_TRUE(ReturnType::RT_OUT_OF_RANGE == led->setLed( LedSystem::systemLed, ILed::LED_AMBER, ILed::LED_OFF,    0 ));

    ASSERT_TRUE(ReturnType::RT_OK == led->setLed( LedSystem::systemLed, ILed::LED_YELLOW, ILed::LED_OFF,    0 ));
    ASSERT_TRUE(ReturnType::RT_OK == led->setLed( LedSystem::systemLed, ILed::LED_YELLOW, ILed::LED_ON,     0 ));
    ASSERT_TRUE(ReturnType::RT_OK == led->setLed( LedSystem::systemLed, ILed::LED_YELLOW, ILed::LED_FLASH,  10 ));
    ASSERT_TRUE(ReturnType::RT_NOT_SUPPORTED == led->setLed( LedSystem::systemLed, ILed::LED_YELLOW, ILed::LED_BREATH, 6 ));

    ASSERT_TRUE(ReturnType::RT_OK == led->setLed( LedSystem::systemLed, ILed::LED_GREEN, ILed::LED_OFF,    0 ));
    ASSERT_TRUE(ReturnType::RT_OK == led->setLed( LedSystem::systemLed, ILed::LED_GREEN, ILed::LED_ON,     0 ));
    ASSERT_TRUE(ReturnType::RT_OK == led->setLed( LedSystem::systemLed, ILed::LED_GREEN, ILed::LED_FLASH,  10 ));
    ASSERT_TRUE(ReturnType::RT_NOT_SUPPORTED == led->setLed( LedSystem::systemLed, ILed::LED_GREEN, ILed::LED_BREATH, 6 ));

    std::cout << __func__ << "- END" <<  std::endl;
}

TEST_F(LedSystemTestCases, unittest)
{
    unittest();
}

} // Namespace
