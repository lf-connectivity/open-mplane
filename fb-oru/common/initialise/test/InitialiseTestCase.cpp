/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      InitialiseTestCase.cpp
 * \brief     Implementation of the CppUnit test harness for Initialise
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the common Initialise class.
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>

#include <string>
#include "Initialise.h"
#include "InitialiseTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( InitialiseTestCase );

using namespace std;

/* Our test class used for the unit tests */

class TestInitialise : public Initialise
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class InitialiseTestCase;

public:

    virtual ReturnType::State initialise();
    virtual ReturnType::State doInit();

};

ReturnType::State TestInitialise::initialise()
{
    return this->_initialise();
}

ReturnType::State TestInitialise::doInit()
{
    ReturnType::State result = ReturnType::RT_OK;
    std::string resultString = "TESTCOMMONINITIALSE INITIALISED OK";

    setInitResultString(resultString);

    // waste a bit of time
    int timedelay = 100000;
    while (timedelay != 0) timedelay--;

    return result;
}


/*
 * Unit tests
 */
void InitialiseTestCase::testCreation()
{
    cout << endl << "*** InitialiseTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    // Test empty string construction
    TestInitialise* tci = new TestInitialise();

    // Assert the instance was created
    CPPUNIT_ASSERT(tci != 0);

    // Test the initial variable values
    CPPUNIT_ASSERT(tci->getInitResult() == ReturnType::RT_ERROR);
    CPPUNIT_ASSERT( tci->getInitResultString() == "UNINITIALISED");
    CPPUNIT_ASSERT(tci->getInitStartTime()->tv_sec == 0);
    CPPUNIT_ASSERT(tci->getInitStartTime()->tv_usec == 0);
    CPPUNIT_ASSERT(tci->getInitEndTime()->tv_sec == 0);
    CPPUNIT_ASSERT(tci->getInitEndTime()->tv_usec == 0);
    CPPUNIT_ASSERT(tci->getInitDurationTime() == 0);
    CPPUNIT_ASSERT(tci->isInitComplete() == false);

    // tidy up
    delete tci;

    cout << __func__ << " - END" <<  endl;
}

void InitialiseTestCase::testInitialisation()
{
    cout << __func__ << " - START" <<  endl;

    // Create our test object
    TestInitialise* tci = new TestInitialise();

    struct timeval lasttime;

    // Assert the instance was created
    CPPUNIT_ASSERT(tci != 0);

    // Confirm the initial variable values
    CPPUNIT_ASSERT(tci->getInitResult() == ReturnType::RT_ERROR);
    CPPUNIT_ASSERT( tci->getInitResultString() == "UNINITIALISED");
    CPPUNIT_ASSERT(tci->getInitStartTime()->tv_sec == 0);
    CPPUNIT_ASSERT(tci->getInitStartTime()->tv_usec == 0);
    CPPUNIT_ASSERT(tci->getInitEndTime()->tv_sec == 0);
    CPPUNIT_ASSERT(tci->getInitEndTime()->tv_usec == 0);
    CPPUNIT_ASSERT(tci->getInitDurationTime() == 0);
    CPPUNIT_ASSERT(tci->isInitComplete() == false);

    // Now initialise the instance. and test the variables again
    // The Init variables should have been initialised
    CPPUNIT_ASSERT(tci->initialise() == ReturnType::RT_OK);

    CPPUNIT_ASSERT(tci->getInitResult() == ReturnType::RT_OK);
    CPPUNIT_ASSERT( tci->getInitResultString() == "TESTCOMMONINITIALSE INITIALISED OK");
    CPPUNIT_ASSERT(tci->getInitStartTime()->tv_sec != 0);
    CPPUNIT_ASSERT(tci->getInitEndTime()->tv_sec != 0);
    CPPUNIT_ASSERT(tci->getInitDurationTime() != 0);
    CPPUNIT_ASSERT(tci->isInitComplete() == true);

    lasttime = *tci->getInitEndTime();  // save last timestamp for testing later

    // Now initialise the instance again. and test the variables again
    // It should return 'already initialised' and not do the initialisation again
//    CPPUNIT_ASSERT(tci->initialise() == ReturnType::RT_ALREADY_INITIALISED);

    // modified to allow re-init
    CPPUNIT_ASSERT(tci->initialise() == ReturnType::RT_OK);

    CPPUNIT_ASSERT(tci->getInitResult() == ReturnType::RT_OK);
    CPPUNIT_ASSERT( tci->getInitResultString() == "TESTCOMMONINITIALSE INITIALISED OK");
    CPPUNIT_ASSERT(tci->getInitEndTime()->tv_sec == lasttime.tv_sec);
    CPPUNIT_ASSERT(tci->getInitEndTime()->tv_usec == lasttime.tv_usec);
    CPPUNIT_ASSERT(tci->isInitComplete() == true);

    cout << "The Initialise execution duration was " << tci->getInitDurationTime() << " usecs" << endl;

    // tidy up
    delete tci;

    cout << __func__ << " - END" <<  endl;
}
