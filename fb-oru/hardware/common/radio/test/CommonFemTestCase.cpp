/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestFemTestCase.cpp
 * \brief     Define the unit tests for the TestFem class
 *
 *
 * \details   Define the unit tests for the TestFem class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>


#include "IFem.h"
#include "CommonFem.h"
#include "CommonFemTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonFemTestCase );

using namespace std;

/****** Area for unit test specifics  ******/

namespace Mplane
{

// The Fem test class
class TestFem : public CommonFem
{
public:

    TestFem( int index, int number, const char* name);

    virtual ~TestFem() { };

    virtual ReturnType::State doInit();
};

} /* namespace Mplane */

TestFem::TestFem( int index, int number, const char* name):
        CommonFem::CommonFem(index, number, name)
{

}

ReturnType::State TestFem::doInit()
{
    ReturnType::State result = ReturnType::RT_OK;
    std::string resultString =  "TESTFEM INITIALISED OK";

    setInitResultString(resultString);

    // waste a bit of time
    int timedelay = 1000000;
    while (timedelay != 0) timedelay--;

    return result;
}

/****** End of Area for unit test specifics  ******/

/*
 * Unit tests
 */
void CommonFemTestCase::testCreation()
{
    cout << endl << "*** TestFemTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    TestFem* testFem1 = new TestFem( 0, 1, "TheFEM1");
    CPPUNIT_ASSERT(testFem1 != 0);
    TestFem* testFem2 = new TestFem( 1, 2, "TheFEM2");
    CPPUNIT_ASSERT(testFem2 != 0);
    CPPUNIT_ASSERT(testFem2 != testFem1);

    CPPUNIT_ASSERT(testFem1->getIndex() == 0);
    CPPUNIT_ASSERT(testFem1->getNumber() == 1);
    CPPUNIT_ASSERT(strcmp(testFem1->getName(), "TheFEM1") == 0 );

    CPPUNIT_ASSERT(testFem2->getIndex() == 1);
    CPPUNIT_ASSERT(testFem2->getNumber() == 2);
    CPPUNIT_ASSERT(strcmp(testFem2->getName(), "TheFEM2") == 0 );

    delete( testFem1 );
    delete( testFem2 );

    cout << __func__ << " - END" <<  endl;
}

void CommonFemTestCase::testInitialisation()
{
    cout << __func__ << " - START" <<  endl;

    TestFem* testFem = new TestFem( 0, 1, "TheFEM1");
    CPPUNIT_ASSERT(testFem != 0);

    // then initialise and confirm it completed ok
    CPPUNIT_ASSERT(testFem->initialise() == ReturnType::RT_OK);

    CPPUNIT_ASSERT(testFem->getInitResult() == ReturnType::RT_OK);
    CPPUNIT_ASSERT( testFem->getInitResultString() == "TESTFEM INITIALISED OK");
    CPPUNIT_ASSERT(testFem->getInitStartTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testFem->getInitEndTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testFem->getInitDurationTime() != 0);
    CPPUNIT_ASSERT(testFem->isInitComplete() == true);


    testFem->show();

    cout << "The Fem Initialise execution duration was " << testFem->getInitDurationTime() << " usecs" << endl;

    delete( testFem );

    cout << __func__ << " - END" <<  endl;
}
