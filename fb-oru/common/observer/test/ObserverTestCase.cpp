/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskTestCase.cpp
 * \brief     Implementation of the CppUnit test harness for Task
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the common task Task class.
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>
#include <limits.h>

#include "ObserverTestCase.h"

using namespace Mplane;

using namespace std;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ObserverTestCase);

/*
 * Unit tests
 */
void ObserverTestCase::unittests()
{
    cout << endl << "*** ObserverTestCase Tests ***" << endl;

    TestTemperatureFaultSubject& subject =
            TestSubjectFactory::getTemperatureFaultSubject();


    TestHighTemperatureFaultInterface& hiTempFltIft = TestSubjectFactory::getHighTemperatureFaultInterface();

    TestLowTemperatureFaultInterface& loTempFltIft = TestSubjectFactory::getLowTemperatureFaultInterface();


    TestTemperatureFaultObserver* obs_1 = new TestTemperatureFaultObserver();
    TestTemperatureFaultObserver* obs_2 = new TestTemperatureFaultObserver();
    TestTemperatureFaultObserver* obs_3 = new TestTemperatureFaultObserver();

    TestCritTemperatureFaultObserver* obs_4 = new TestCritTemperatureFaultObserver();

    hiTempFltIft.attach(*obs_1);
    hiTempFltIft.attach(*obs_2);
    hiTempFltIft.attach(*obs_3);

    // confirm the first entry in the subject observer list is obs_1
    CPPUNIT_ASSERT(hiTempFltIft.getNumObservers() == 3);
    CPPUNIT_ASSERT(strcmp(hiTempFltIft.getObsName(0), obs_1->mName) == 0);
    cout << "observer 1 in Subject is " << hiTempFltIft.getObsName(0) << endl;

    // now attach as a critical observer
    cout << "now attach a critical observer that should go at front of list,  " << obs_4->mName << endl;
    hiTempFltIft.attachCritical(*obs_4); // critical observer goes to front of list and is notified first

    // confirm the first entry in the subject observer list is now obs_4
    CPPUNIT_ASSERT(hiTempFltIft.getNumObservers() == 4);
    CPPUNIT_ASSERT(strcmp(hiTempFltIft.getObsName(0), obs_4->mName) == 0);
    CPPUNIT_ASSERT(strcmp(hiTempFltIft.getObsName(1), obs_1->mName) == 0);
    cout << "observer 1 in Subject is " << hiTempFltIft.getObsName(0) << endl;
    cout << "observer 2 in Subject is " << hiTempFltIft.getObsName(1) << endl;

    hiTempFltIft.attach(*obs_2);

    loTempFltIft.attach(*obs_1);
    loTempFltIft.attach(*obs_2);

    CPPUNIT_ASSERT(obs_1->mCritical == false);
    CPPUNIT_ASSERT(obs_2->mCritical == false);
    CPPUNIT_ASSERT(obs_3->mCritical == false);
    CPPUNIT_ASSERT(obs_1->mHigh == false);
    CPPUNIT_ASSERT(obs_2->mHigh == false);
    CPPUNIT_ASSERT(obs_3->mHigh == false);
    CPPUNIT_ASSERT(obs_1->mLow == false);
    CPPUNIT_ASSERT(obs_2->mLow == false);
    CPPUNIT_ASSERT(obs_3->mLow == false);
    CPPUNIT_ASSERT(obs_1->mWarmup == false);
    CPPUNIT_ASSERT(obs_2->mWarmup == false);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);

    subject.mHigh = true;

    CPPUNIT_ASSERT(obs_1->mCritical == false);
    CPPUNIT_ASSERT(obs_2->mCritical == false);
    CPPUNIT_ASSERT(obs_3->mCritical == false);
    CPPUNIT_ASSERT(obs_1->mHigh == false);
    CPPUNIT_ASSERT(obs_2->mHigh == false);
    CPPUNIT_ASSERT(obs_3->mHigh == false);
    CPPUNIT_ASSERT(obs_1->mLow == false);
    CPPUNIT_ASSERT(obs_2->mLow == false);
    CPPUNIT_ASSERT(obs_3->mLow == false);
    CPPUNIT_ASSERT(obs_1->mWarmup == false);
    CPPUNIT_ASSERT(obs_2->mWarmup == false);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);

    subject.changeHigh();

    CPPUNIT_ASSERT(subject.high() == true);
    CPPUNIT_ASSERT(subject.critical() == false);
    CPPUNIT_ASSERT(obs_1->mCritical == false);
    CPPUNIT_ASSERT(obs_2->mCritical == false);
    CPPUNIT_ASSERT(obs_3->mCritical == false);
    CPPUNIT_ASSERT(obs_1->mHigh == true);
    CPPUNIT_ASSERT(obs_2->mHigh == true);
    CPPUNIT_ASSERT(obs_3->mHigh == true);
    CPPUNIT_ASSERT(obs_1->mLow == false);
    CPPUNIT_ASSERT(obs_2->mLow == false);
    CPPUNIT_ASSERT(obs_3->mLow == false);
    CPPUNIT_ASSERT(obs_1->mWarmup == false);
    CPPUNIT_ASSERT(obs_2->mWarmup == false);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);

    subject.mHigh = false;
    subject.changeHigh();

    CPPUNIT_ASSERT(subject.high() == false);
    CPPUNIT_ASSERT(subject.critical() == false);
    CPPUNIT_ASSERT(obs_1->mCritical == false);
    CPPUNIT_ASSERT(obs_2->mCritical == false);
    CPPUNIT_ASSERT(obs_3->mCritical == false);
    CPPUNIT_ASSERT(obs_1->mHigh == false);
    CPPUNIT_ASSERT(obs_2->mHigh == false);
    CPPUNIT_ASSERT(obs_3->mHigh == false);
    CPPUNIT_ASSERT(obs_1->mLow == false);
    CPPUNIT_ASSERT(obs_2->mLow == false);
    CPPUNIT_ASSERT(obs_3->mLow == false);
    CPPUNIT_ASSERT(obs_1->mWarmup == false);
    CPPUNIT_ASSERT(obs_2->mWarmup == false);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);

    subject.mCritical = true;

    CPPUNIT_ASSERT(obs_1->mCritical == false);
    CPPUNIT_ASSERT(obs_2->mCritical == false);
    CPPUNIT_ASSERT(obs_3->mCritical == false);
    CPPUNIT_ASSERT(obs_1->mHigh == false);
    CPPUNIT_ASSERT(obs_2->mHigh == false);
    CPPUNIT_ASSERT(obs_3->mHigh == false);
    CPPUNIT_ASSERT(obs_1->mLow == false);
    CPPUNIT_ASSERT(obs_2->mLow == false);
    CPPUNIT_ASSERT(obs_3->mLow == false);
    CPPUNIT_ASSERT(obs_1->mWarmup == false);
    CPPUNIT_ASSERT(obs_2->mWarmup == false);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);

    subject.changeHigh();
    subject.changeLow();        // should have no effect

    CPPUNIT_ASSERT(subject.high() == false);
    CPPUNIT_ASSERT(subject.critical() == true);
    CPPUNIT_ASSERT(obs_1->mCritical == true);
    CPPUNIT_ASSERT(obs_2->mCritical == true);
    CPPUNIT_ASSERT(obs_3->mCritical == true);
    CPPUNIT_ASSERT(obs_1->mHigh == false);
    CPPUNIT_ASSERT(obs_2->mHigh == false);
    CPPUNIT_ASSERT(obs_3->mHigh == false);
    CPPUNIT_ASSERT(obs_1->mLow == false);
    CPPUNIT_ASSERT(obs_2->mLow == false);
    CPPUNIT_ASSERT(obs_3->mLow == false);
    CPPUNIT_ASSERT(obs_1->mWarmup == false);
    CPPUNIT_ASSERT(obs_2->mWarmup == false);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);

    subject.mCritical = false;
    subject.changeHigh();

    CPPUNIT_ASSERT(obs_1->mCritical == false);
    CPPUNIT_ASSERT(obs_2->mCritical == false);
    CPPUNIT_ASSERT(obs_3->mCritical == false);
    CPPUNIT_ASSERT(obs_1->mHigh == false);
    CPPUNIT_ASSERT(obs_2->mHigh == false);
    CPPUNIT_ASSERT(obs_3->mHigh == false);
    CPPUNIT_ASSERT(obs_1->mLow == false);
    CPPUNIT_ASSERT(obs_2->mLow == false);
    CPPUNIT_ASSERT(obs_3->mLow == false);
    CPPUNIT_ASSERT(obs_1->mWarmup == false);
    CPPUNIT_ASSERT(obs_2->mWarmup == false);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);

    subject.mHigh = true;
    subject.mCritical = true;
    subject.changeHigh();

    CPPUNIT_ASSERT(subject.high() == true);
    CPPUNIT_ASSERT(subject.critical() == true);
    CPPUNIT_ASSERT(obs_1->mCritical == true);
    CPPUNIT_ASSERT(obs_2->mCritical == true);
    CPPUNIT_ASSERT(obs_3->mCritical == true);
    CPPUNIT_ASSERT(obs_1->mHigh == true);
    CPPUNIT_ASSERT(obs_2->mHigh == true);
    CPPUNIT_ASSERT(obs_3->mHigh == true);
    CPPUNIT_ASSERT(obs_1->mLow == false);
    CPPUNIT_ASSERT(obs_2->mLow == false);
    CPPUNIT_ASSERT(obs_3->mLow == false);
    CPPUNIT_ASSERT(obs_1->mWarmup == false);
    CPPUNIT_ASSERT(obs_2->mWarmup == false);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);

    subject.mHigh = false;
    subject.mCritical = false;
    subject.changeHigh();

    CPPUNIT_ASSERT(obs_1->mCritical == false);
    CPPUNIT_ASSERT(obs_2->mCritical == false);
    CPPUNIT_ASSERT(obs_3->mCritical == false);
    CPPUNIT_ASSERT(obs_1->mHigh == false);
    CPPUNIT_ASSERT(obs_2->mHigh == false);
    CPPUNIT_ASSERT(obs_3->mHigh == false);
    CPPUNIT_ASSERT(obs_1->mLow == false);
    CPPUNIT_ASSERT(obs_2->mLow == false);
    CPPUNIT_ASSERT(obs_3->mLow == false);
    CPPUNIT_ASSERT(obs_1->mWarmup == false);
    CPPUNIT_ASSERT(obs_2->mWarmup == false);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);

    subject.mLow = true;
    subject.changeLow();

    CPPUNIT_ASSERT(obs_1->mCritical == false);
    CPPUNIT_ASSERT(obs_2->mCritical == false);
    CPPUNIT_ASSERT(obs_3->mCritical == false);
    CPPUNIT_ASSERT(obs_1->mHigh == false);
    CPPUNIT_ASSERT(obs_2->mHigh == false);
    CPPUNIT_ASSERT(obs_3->mHigh == false);
    CPPUNIT_ASSERT(obs_1->mLow == true);
    CPPUNIT_ASSERT(obs_2->mLow == true);
    CPPUNIT_ASSERT(obs_3->mLow == false);       // observer 3 not attached to low temp fault subject
    CPPUNIT_ASSERT(obs_1->mWarmup == false);
    CPPUNIT_ASSERT(obs_2->mWarmup == false);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);

    subject.mLow = false;
    subject.mWarmup = true;
    subject.changeLow();

    CPPUNIT_ASSERT(obs_1->mCritical == false);
    CPPUNIT_ASSERT(obs_2->mCritical == false);
    CPPUNIT_ASSERT(obs_3->mCritical == false);
    CPPUNIT_ASSERT(obs_1->mHigh == false);
    CPPUNIT_ASSERT(obs_2->mHigh == false);
    CPPUNIT_ASSERT(obs_3->mHigh == false);
    CPPUNIT_ASSERT(obs_1->mLow == false);
    CPPUNIT_ASSERT(obs_2->mLow == false);
    CPPUNIT_ASSERT(obs_3->mLow == false);
    CPPUNIT_ASSERT(obs_1->mWarmup == true);
    CPPUNIT_ASSERT(obs_2->mWarmup == true);
    CPPUNIT_ASSERT(obs_3->mWarmup == false);   // observer 3 not attached to low temp fault subject


    hiTempFltIft.detach(*obs_2);

    hiTempFltIft.detach(*obs_2);

    delete obs_1;
    delete obs_2;
    delete obs_3;
    delete obs_4;

    delete &subject;



}
