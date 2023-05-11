/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LedSX150bTestCase.h
 * \brief     The Test file header for the LED System device driver
 *
 *
 * \details   The Test file header for the LED System device driver
 *
 */

#ifndef LED_SYSTEM_TESTCASE_H_
#define LED_SYSTEM_TESTCASE_H_


// Includes go here, before the namespace
#include "gtest/gtest.h"

#include <string.h>
#include <iostream>


namespace Mplane
{

//
class TestLedSystem
{
public:

	TestLedSystem();

    ~TestLedSystem();

    const char* mName;
};


class LedSystemTestCases: public ::testing::Test
{

protected:
    virtual void SetUp();
    virtual void TearDown();
    virtual void unittest();

};

}

#endif /* LED_SYSTEM_TESTCASE_H_ */
