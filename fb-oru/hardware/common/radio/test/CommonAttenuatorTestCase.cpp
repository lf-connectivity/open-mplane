/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAttenuatorTestCase.cpp
 * \brief     Define the unit tests for the CommonAttenuator class
 *
 *
 * \details   Define the unit tests for the CommonAttenuator class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>


#include "IAttenuator.h"
#include "CommonAttenuator.h"
#include "CommonAttenuatorTestCase.h"
#include "TestAttenuatorDriver.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonAttenuatorTestCase );

using namespace std;

/****** Area for unit test specifics  ******/

namespace Mplane
{

// The Atten test class
class TestAtten : public CommonAttenuator
{
public:

    TestAtten( int index, const char* name,
               float maxAtten);

    virtual ~TestAtten() { };

    virtual ReturnType::State doInit();

};

} /* namespace Mplane */

TestAtten::TestAtten( int index, const char* name, float maxAtten):
        CommonAttenuator::CommonAttenuator(std::make_shared<TestAttenuatorDriver>(0, maxAtten),
        		index, name)
{
    mAttenuation = maxAtten;
}

ReturnType::State TestAtten::doInit()
{
    ReturnType::State result = ReturnType::RT_OK;
    std::string resultString = "TESTATTEN INITIALISED OK";

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
void CommonAttenuatorTestCase::testCreation()
{
    cout << endl << "*** CommonAttenuatorTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    TestAtten* testAtten1 = new TestAtten( 0, "TheAtten1", 63.0f);
    CPPUNIT_ASSERT(testAtten1 != 0);
    TestAtten* testAtten2 = new TestAtten( 1, "TheAtten2", 44.0f);
    CPPUNIT_ASSERT(testAtten2 != 0);
    CPPUNIT_ASSERT(testAtten1 != testAtten2);

    CPPUNIT_ASSERT(testAtten1->getIndex() == 0);
    CPPUNIT_ASSERT(strcmp(testAtten1->getName().c_str(), "TheAtten1") == 0 );
    CPPUNIT_ASSERT(testAtten1->getAttenuation() == 63.0f);
    CPPUNIT_ASSERT(testAtten1->getMaxAttenuation() == 63.0f);

    CPPUNIT_ASSERT(testAtten2->getIndex() == 1);
    CPPUNIT_ASSERT(strcmp(testAtten2->getName().c_str(), "TheAtten2") == 0 );
    CPPUNIT_ASSERT(testAtten2->getAttenuation() == 44.0f);
    CPPUNIT_ASSERT(testAtten2->getMaxAttenuation() == 44.0f);

    delete( testAtten1 );
    delete( testAtten2 );

    cout << __func__ << " - END" <<  endl;
}

void CommonAttenuatorTestCase::testInitialisation()
{
    cout << __func__ << " - START" <<  endl;

    TestAtten* testAtten1 = new TestAtten( 0, "TheAtten1", 63.0);
    CPPUNIT_ASSERT(testAtten1 != 0);

    // then initialise and confirm it completed ok
    CPPUNIT_ASSERT(testAtten1->initialise() == ReturnType::RT_OK);

    CPPUNIT_ASSERT(testAtten1->getInitResult() == ReturnType::RT_OK);
    CPPUNIT_ASSERT( testAtten1->getInitResultString() == "TESTATTEN INITIALISED OK");
    CPPUNIT_ASSERT(testAtten1->getInitStartTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testAtten1->getInitEndTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testAtten1->getInitDurationTime() != 0);
    CPPUNIT_ASSERT(testAtten1->isInitComplete() == true);

    testAtten1->show();

    cout << "The Attenuator Initialise execution duration was " << testAtten1->getInitDurationTime() << " usecs" << endl;

    delete( testAtten1 );

    cout << __func__ << " - END" <<  endl;
}

void CommonAttenuatorTestCase::testAttenSetting()
{
    cout << __func__ << " - START" <<  endl;

    TestAtten* testAtten1 = new TestAtten( 0, "TheAtten1", 63.0);
    CPPUNIT_ASSERT(testAtten1 != 0);

    // then initialise and confirm it completed ok
    CPPUNIT_ASSERT(testAtten1->initialise() == ReturnType::RT_OK);

    // set atten to good level
    CPPUNIT_ASSERT(testAtten1->setAttenuation(62.0f) == ReturnType::RT_OK);
    CPPUNIT_ASSERT(testAtten1->getAttenuation() == 62.0f);

    // set atten to max level
    CPPUNIT_ASSERT(testAtten1->getMinAttenuation() == 0.0f);
    CPPUNIT_ASSERT(testAtten1->getMaxAttenuation() == 63.0f);

    // set atten to greater than max level - invalid case
    CPPUNIT_ASSERT(testAtten1->setAttenuation(64.4) != ReturnType::RT_OK);
    CPPUNIT_ASSERT(testAtten1->getAttenuation() == 62.0f); // previous value unchanged

    testAtten1->show();

    delete( testAtten1 );

    cout << __func__ << " - END" <<  endl;
}
