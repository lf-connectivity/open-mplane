/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MdioTestCase.h
 * \brief     Define the unit tests for the Mdio class
 *
 *
 * \details   This GTEST test class will test all the functionality of the
 *            Mdio implementation.
 *
 */

#ifndef _RADIO_HARDWARE_MII_TESTCASE_H_
#define _RADIO_HARDWARE_MII_TESTCASE_H_

// Includes go here, before the namespace
#include "gtest/gtest.h"

#include "Mdio.h"

namespace Mplane
{

class TestMdio : Mdio
{
public:
    TestMdio( int deviceIndex );

    virtual ~TestMdio();

    const char* mName;
};

class MdioTestCases : public ::testing::Test
{

protected:
    virtual void SetUp();
    virtual void TearDown();
    virtual void unittest();

};

} /* namespace Mplane */


#endif /* _RADIO_HARDWARE_MII_TESTCASE_H_ */
