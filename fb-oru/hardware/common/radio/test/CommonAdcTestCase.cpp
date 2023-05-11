/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAdcTestCase.cpp
 * \brief     Define the unit tests for the CommonAdc class
 *
 *
 * \details   Define the unit tests for the CommonAdc class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>


#include "IAdc.h"
#include "CommonAdc.h"
#include "CommonAdcTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonAdcTestCase );

using namespace std;

/****** Area for unit test specifics  ******/

namespace Mplane
{

// The ADC test class
class TestAdc : public CommonAdc
{
public:

    TestAdc( int index, const char* name);

    virtual ~TestAdc() { };

    virtual ReturnType::State doInit();
};

} /* namespace Mplane */

TestAdc::TestAdc( int index, const char* name):
        CommonAdc::CommonAdc(index, name)
{

}

ReturnType::State TestAdc::doInit()
{
    ReturnType::State result = ReturnType::RT_OK;
    std::string resultString = "TESTADC INITIALISED OK";

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
void CommonAdcTestCase::testCreation()
{
    cout << endl << "*** CommonAdcTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    CommonAdc* testAdc1 = new TestAdc( 0, "TheADC1");
    CPPUNIT_ASSERT(testAdc1 != 0);
    CommonAdc* testAdc2 = new TestAdc( 1, "TheADC2");
    CPPUNIT_ASSERT(testAdc2 != 0);
    CPPUNIT_ASSERT(testAdc1 != testAdc2);

    CPPUNIT_ASSERT(testAdc1->getIndex() == 0);
    CPPUNIT_ASSERT(strcmp(testAdc1->getName().c_str(), "TheADC1") == 0 );
    CPPUNIT_ASSERT(testAdc1->getState() == false );

    CPPUNIT_ASSERT(testAdc2->getIndex() == 1);
    CPPUNIT_ASSERT(strcmp(testAdc2->getName().c_str(), "TheADC2") == 0 );
    CPPUNIT_ASSERT(testAdc2->getState() == false );

    delete( testAdc1 );
    delete( testAdc2 );

    cout << __func__ << " - END" <<  endl;
}

void CommonAdcTestCase::testInitialisation()
{
    cout << __func__ << " - START" <<  endl;

    TestAdc* testAdc1 = new TestAdc( 0, "TheADC1");
    CPPUNIT_ASSERT(testAdc1 != 0);

    // then initialise and confirm it completed ok
    CPPUNIT_ASSERT(testAdc1->initialise() == ReturnType::RT_OK);

    CPPUNIT_ASSERT(testAdc1->getInitResult() == ReturnType::RT_OK);
    CPPUNIT_ASSERT( testAdc1->getInitResultString() == "TESTADC INITIALISED OK");
    CPPUNIT_ASSERT(testAdc1->getInitStartTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testAdc1->getInitEndTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testAdc1->getInitDurationTime() != 0);
    CPPUNIT_ASSERT(testAdc1->isInitComplete() == true);

    CPPUNIT_ASSERT(testAdc1->getState() == false );
    testAdc1->enable();
    CPPUNIT_ASSERT(testAdc1->getState() == true );
    testAdc1->disable();
    CPPUNIT_ASSERT(testAdc1->getState() == false );

    testAdc1->show();

    cout << "The ADC Initialise execution duration was " << testAdc1->getInitDurationTime() << " usecs" << endl;

    delete( testAdc1 );

    cout << __func__ << " - END" <<  endl;
}
