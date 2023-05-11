/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestDacTestCase.cpp
 * \brief     Define the unit tests for the TestDac class
 *
 *
 * \details   Define the unit tests for the TestDac class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>


#include "IDac.h"
#include "CommonDac.h"
#include "CommonDacTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonDacTestCase );

using namespace std;

/****** Area for unit test specifics  ******/

namespace Mplane
{

// The DAC test class
class TestDac : public CommonDac
{
public:

    TestDac( int index, const char* name);

    virtual ~TestDac() { };

    virtual ReturnType::State doInit();
};

} /* namespace Mplane */

TestDac::TestDac( int index, const char* name):
        CommonDac::CommonDac(index, name)
{

}

ReturnType::State TestDac::doInit()
{
    ReturnType::State result = ReturnType::RT_OK;
    std::string resultString = "TESTDAC INITIALISED OK";

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
void CommonDacTestCase::testCreation()
{
    cout << endl << "*** TestDacTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    TestDac* testDac1 = new TestDac( 0, "TheDAC1");
    CPPUNIT_ASSERT(testDac1 != 0);
    TestDac* testDac2 = new TestDac( 1, "TheDAC2");
    CPPUNIT_ASSERT(testDac2 != 0);
    CPPUNIT_ASSERT(testDac1 != testDac2);

    CPPUNIT_ASSERT(testDac1->getIndex() == 0);
    CPPUNIT_ASSERT(strcmp(testDac1->getName().c_str(), "TheDAC1") == 0 );
    CPPUNIT_ASSERT(testDac1->getState() == false );

    CPPUNIT_ASSERT(testDac2->getIndex() == 1);
    CPPUNIT_ASSERT(strcmp(testDac2->getName().c_str(), "TheDAC2") == 0 );
    CPPUNIT_ASSERT(testDac2->getState() == false );

    delete( testDac1 );
    delete( testDac2 );

    cout << __func__ << " - END" <<  endl;
}

void CommonDacTestCase::testInitialisation()
{
    cout << __func__ << " - START" <<  endl;

    TestDac* testDac1 = new TestDac( 0, "TheDAC1");
    CPPUNIT_ASSERT(testDac1 != 0);

    // then initialise and confirm it completed ok
    CPPUNIT_ASSERT(testDac1->initialise() == ReturnType::RT_OK);

    CPPUNIT_ASSERT(testDac1->getInitResult() == ReturnType::RT_OK);
    CPPUNIT_ASSERT( testDac1->getInitResultString() == "TESTDAC INITIALISED OK");
    CPPUNIT_ASSERT(testDac1->getInitStartTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testDac1->getInitEndTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testDac1->getInitDurationTime() != 0);
    CPPUNIT_ASSERT(testDac1->isInitComplete() == true);

    CPPUNIT_ASSERT(testDac1->getState() == false );
    testDac1->enableOutput();
    CPPUNIT_ASSERT(testDac1->getState() == true );
    testDac1->disableOutput();
    CPPUNIT_ASSERT(testDac1->getState() == false );

    testDac1->show();

    cout << "The DAC Initialise execution duration was " << testDac1->getInitDurationTime() << " usecs" << endl;

    delete( testDac1 );

    cout << __func__ << " - END" <<  endl;
}
