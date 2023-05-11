/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonSynthTestCase.cpp
 * \brief     Define the unit tests for the CommonSynth class
 *
 *
 * \details   Define the unit tests for the CommonSynth class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>
#include <ostream>

#include "CommonSynth.h"
#include "CommonSynthTestCase.h"
#include "ISynthDriver.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonSynthTestCase );

using namespace std;

/****** Area for unit test specifics  ******/

namespace Mplane
{
// The synth test class
class TestSynthDriver : public ISynthDriver
{
public:

    virtual ReturnType::State program(Frequency frequency);
    virtual void postProgram(void);
    virtual ReturnType::State initialise();
    virtual bool isPllLocked(void);
    virtual bool isOutOfLock(void);
    virtual void forceOutOfLock(void);
    virtual void show(void);
    virtual void show(std::ostream& os);

    TestSynthDriver() {mLocked = false;};

    virtual ~TestSynthDriver() { };

private:
    bool mLocked;

};

} /* namespace Mplane */

ReturnType::State Mplane::TestSynthDriver::program(Frequency frequency)
{
    return ReturnType::RT_OK;
}

void Mplane::TestSynthDriver::postProgram(void)
{
}

ReturnType::State TestSynthDriver::initialise()
{
    ReturnType::State result = ReturnType::RT_OK;

    // waste a bit of time
    int timedelay = 1000000;
    while (timedelay != 0) timedelay--;


    return result;
}

bool TestSynthDriver::isPllLocked(void)
{
	return mLocked;
}

bool TestSynthDriver::isOutOfLock(void)
{
	return !mLocked;
}

void TestSynthDriver::forceOutOfLock(void)
{
	mLocked = false;
}

void TestSynthDriver::show(std::ostream& os)
{
	os << "Test Synth";
}

void TestSynthDriver::show(void)
{
}

/****** End of Area for unit test specifics  ******/

/*
 * Unit tests
 */
void CommonSynthTestCase::testCreation()
{
    cout << endl << "*** CommonSynthTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    std::shared_ptr<ISynthDriver> testSynthdriver = std::make_shared<TestSynthDriver>();
    CPPUNIT_ASSERT(testSynthdriver != 0);
    CommonSynth* testSynth = new CommonSynth( testSynthdriver, 1, "TheSYNTH2", 2345000ULL);
    CPPUNIT_ASSERT(testSynth != 0);

    CPPUNIT_ASSERT(testSynth->getIndex() == 1);
    CPPUNIT_ASSERT(strcmp(testSynth->getName().c_str(), "TheSYNTH2") == 0 );
    CPPUNIT_ASSERT(testSynth->getFrequency() == 2345000);
    CPPUNIT_ASSERT(testSynth->isOutOfLock() == true);

    // tidy up
    delete( testSynth );

    cout << __func__ << " - END" <<  endl;
}

void CommonSynthTestCase::testInitialisation()
{
    cout << __func__ << " - START" <<  endl;

    std::shared_ptr<ISynthDriver> testSynthdriver = std::make_shared<TestSynthDriver>();
    CPPUNIT_ASSERT(testSynthdriver != 0);
    CommonSynth* testSynth = new CommonSynth( testSynthdriver, 1, "TheSYNTH2", 2345000ULL);

    // then initialise and confirm it completed ok
    CPPUNIT_ASSERT(testSynth->initialise() == ReturnType::RT_OK);

    CPPUNIT_ASSERT(testSynth->getInitResult() == ReturnType::RT_OK);
    CPPUNIT_ASSERT(  testSynth->getInitResultString() == "TheSYNTH2 Init_OK");
    CPPUNIT_ASSERT(testSynth->getInitStartTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testSynth->getInitEndTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testSynth->getInitDurationTime() != 0);
    CPPUNIT_ASSERT(testSynth->isInitComplete() == true);

    // test another initialise will not do anything
//    CPPUNIT_ASSERT(testSynth1->initialise() == ReturnType::RT_ALREADY_INITIALISED);
    CPPUNIT_ASSERT(testSynth->initialise() == ReturnType::RT_OK);

    testSynth->show();

    cout << "The Synthesiser initialise execution duration was " << testSynth->getInitDurationTime() << " usecs" << endl;

    // tidy up
    delete( testSynth );

    cout << __func__ << " - END" <<  endl;
}

void CommonSynthTestCase::testSynthGetAndSet()
{
    cout << __func__ << " - START" <<  endl;

    std::shared_ptr<ISynthDriver> testSynthdriver = std::make_shared<TestSynthDriver>();
    CPPUNIT_ASSERT(testSynthdriver != 0);
    CommonSynth* testSynth = new CommonSynth( testSynthdriver, 1, "TheSYNTH2", 2345000ULL);


    // set a different frequency
    testSynth->setFrequency(1234500ULL);
    CPPUNIT_ASSERT(testSynth->getFrequency() == 1234500U);

    // force synth to go OOL.
    testSynth->forceOutOfLock();
    CPPUNIT_ASSERT(testSynth->isOutOfLock() == true);

    // tidy up
    delete( testSynth );

    cout << __func__ << " - END" <<  endl;
}
