/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MdioTestCase.cpp
 * \brief     Define the unit tests for the Mdio class
 *
 *
 * \details   Define the unit tests for the Mdio class
 *
 */

#include "MdioTestCase.h"
#include <stdexcept>
#include <memory>
#include <string.h>
#include <iostream>

#include "gtest/gtest.h"

#include "GlobalTypeDefs.h"
#include "Loggable.h"




namespace Mplane
{


Mplane::TestMdio::TestMdio(int deviceIndex) : Mdio( deviceIndex ), mName ( "Mplane::TestMdio" )
{
}

Mplane::TestMdio::~TestMdio()
{
    std::cout << "Mplane::TestMdio destructor" << std::endl;
    mName = NULL;
}

/*
 * Unit tests
 */
void MdioTestCases::SetUp()
{
}

void MdioTestCases::TearDown()
{
}

void MdioTestCases::unittest()
{
    const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

    Mdio* mdio = new Mdio(0);

    mdio->show();

    ASSERT_TRUE(ReturnType::RT_OK == mdio->initialise());

    std::cout << __func__ << "- END" <<  std::endl;
}


TEST_F(MdioTestCases, Mdiotests)
{
    unittest();
}

} // Namespace
