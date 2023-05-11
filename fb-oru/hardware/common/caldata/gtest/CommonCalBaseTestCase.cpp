/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCalBaseTestCase.cpp
 * \brief     The google test file for common calibration base class
 *
 *
 * \details   The google test file for common calibration base class
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "CommonCalBaseTestCase.h"


using namespace Mplane;
using namespace std;

/***************************/

// Test objects

Mplane::TestCommonCalBase::TestCommonCalBase():CommonCalBase("Mplane::TestCommonCalBase","UT"),
        mState( ReturnType::RT_OK)
{
}

Mplane::TestCommonCalBase::~TestCommonCalBase()
{
    cout << "Mplane::TestCommonCalBase destructor" << endl;
}

void TestCommonCalBase::show()
{
}

ReturnType::State TestCommonCalBase::load()
{
    setLoaded( true );
    return mState;
}

void Mplane::TestCommonCalBase::setInfo(std::string info)
{
    CommonCalBase::setInfo( info );
}

void Mplane::TestCommonCalBase::setVersion(int version)
{
    CommonCalBase::setVersion( version );
}


/*
 * Unit test fixtures
 */
TEST(CommonCalBaseTestCases, Test)
{

	cout << endl << "*** CommonCalBaseTestCases Test ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    TestCommonCalBase tCalBase;

    EXPECT_TRUE( tCalBase.getVersion() == -1 );
    EXPECT_EQ( tCalBase.getInfo() , "" );
    EXPECT_FALSE( tCalBase.isLoaded() );

    tCalBase.setVersion(1);
    EXPECT_TRUE( tCalBase.getVersion() == 1 );

    tCalBase.setInfo("Test common cal base class");
    EXPECT_EQ( tCalBase.getInfo() , "Test common cal base class" );

    EXPECT_TRUE( tCalBase.load() == ReturnType::RT_OK );

    EXPECT_TRUE( tCalBase.isLoaded() );

    cout << __func__ << " - END" <<  endl;
}
