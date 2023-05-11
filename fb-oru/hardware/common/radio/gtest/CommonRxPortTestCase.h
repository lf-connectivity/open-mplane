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

#ifndef COMMONRXPORTTESTCASE_H_
#define COMMONRXPORTTESTCASE_H_


// Includes go here, before the namespace
#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include <memory>
#include "CommonRxPort.h"

using namespace std;
namespace Mplane
{
//
class TestRxPort: public CommonRxPort
{

public:

	TestRxPort(int index, const char* name):
	            CommonRxPort( index, name )
    {
	    mName = name;
    }

    ~TestRxPort()
    {
        cout << "Mplane::TestCommonRxPort destructor" << endl;
        mName = NULL;
    }

    const char* mName;

    virtual ReturnType::State setRxOnLowLevel() { return ReturnType::RT_OK; }
    virtual ReturnType::State setRxOffLowLevel() { return ReturnType::RT_OK;}
};


class CommonRxPortTestCases: public ::testing::Test
{
friend class CommonRxPort;

protected:
    virtual void SetUp();
    virtual void TearDown();
    virtual void testCreation();
    virtual void testRxPort();
    virtual void testErrorPaths();
    virtual void testTidyUp();

};

}
#endif /* COMMONRXPORTTESTCASE_H_ */
