/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxPortTestCase.h
 * \brief     The Test file header for CommonRxPort
 *
 *
 * \details   The Test file header for CommonRxPort
 *
 */

#ifndef COMMON_SRX_PORT_TESTCASE_H_
#define COMMON_SRX_PORT_TESTCASE_H_


// Includes go here, before the namespace
#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "CommonSRxPort.h"


namespace Mplane
{

//
class TestCommonSRxPort
{
public:

	TestCommonSRxPort();

    ~TestCommonSRxPort();

    const char* mName;


};


class CommonSRxPortTestCases: public ::testing::Test
{

protected:
    virtual void SetUp();
    virtual void TearDown();
    virtual void unittest();

};

}

#endif /* COMMON_SRX_PORT_TESTCASE_H_ */
