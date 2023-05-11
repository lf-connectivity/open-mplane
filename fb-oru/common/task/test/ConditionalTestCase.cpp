/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MutexTestCase.cpp
 * \brief     Implementation of test case for Mutex thread lock class
 *
 *
 * \details   Implementation of test case for Mutex thread lock class
 *
 */


#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>
#include <limits.h>

#include "ConditionalTestCase.h"

using namespace Mplane;
using namespace std;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( ConditionalTestCase );


CondWTask::CondWTask():Task(90, Task::SMALL_STACK),
        mCount(0), nowCount(0), testHold(false)
{
    state = ct_idle;
}

void Mplane::CondWTask::setCount(int count)
{
//    Conditional::Lock lock( mConditional );  // use the Conditioal lock guard here, unlocks on out of scope

    cout << "Unit Test - setCount(" << count << ")" << endl;

    mConditional.lock();
    cout << "Unit Test - setCount() count is now " << count << endl;
    mCount = count;
    mConditional.unlock();

    while( testHold )
    {
        Mplane::Task::msSleep( 10 );
    }

    mConditional.lock();
    cout << "Unit Test - signal" << endl;
    mConditional.signal();
    mConditional.unlock();

    cout << "Unit Test - setCount() complete " << endl;
//    mConditional.unlock();
}

int Mplane::CondWTask::waitCount()
{
//    Conditional::Lock lock( mConditional );

    mConditional.wait();

    nowCount = mCount;
    mCount = 0;

    return nowCount;
}

int Mplane::CondWTask::getCount()
{
    mConditional.lock();          // use conditionals mutex directly here

    int retCount = nowCount;

    mConditional.unlock();

    return ( retCount );
}

int CondWTask::run()
{
    cout << "Wtask thread " << pthread_self() << endl;
    cout.flush();
    while( waitCount() != 0 )
    {
        cout << "Unit Test - now count is: " << getCount() << endl;
        cout.flush();
    }
    cout << "Write task exit, waitCount() returned zero" << endl;
    cout.flush();
    return mCount;
}

CondTestTask::CondTestTask( CondWTask &task ):
        Task(50, Task::MEDIUM_STACK),
        count(0),
        mTask( task )
{
    state = ct_idle;
}

int CondTestTask::run()
{
    cout << "Set task thread " << pthread_self() << endl;
    cout.flush();
    int locCount = 0;
    while( state != ct_exit )
    {
        if( state == ct_writecount )
        {
            locCount++;
            mTask.setCount( locCount );
            state = ct_idle;
        }
        else
        {
            Mplane::Task::msSleep( 20 );
        }
    }
    return count;
}



void Mplane::ConditionalTestCase::unittest()
{
    cout << endl << "*** ConditionalTestCase unittest ***" <<  endl;

    wtask = new CondWTask();

    CPPUNIT_ASSERT(wtask != 0);

    atask = new CondTestTask(*wtask);

    CPPUNIT_ASSERT(atask != 0);


    CPPUNIT_ASSERT((void *)wtask != (void *)atask);

    CPPUNIT_ASSERT(wtask->isRunning() == false);
    CPPUNIT_ASSERT(atask->isRunning() == false);


    wtask->start();
    usleep( 200 * 1000 );  // give wtask time to initialise
    atask->start();
    usleep( 100 * 1000 );  // give atask time to initialise

    CPPUNIT_ASSERT(wtask->isRunning() == true);
    CPPUNIT_ASSERT(atask->isRunning() == true);

    /*
     * Ask the increment task to increment the count, hold it in the function
     * and check lock is set and check the lock state
     */
    wtask->testHold = true;     // keep write task in set Count method

    atask->state = ct_writecount; // as increment task to read an increment

    usleep( 100 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT_EQUAL( 1, wtask->mCount );
    CPPUNIT_ASSERT_EQUAL( 0, wtask->nowCount ); // no signal yet, should copy mCount to nowCount

    /*
     * Release is from hold, the count should be incremented and the mutex
     * unlocked.
     */

    wtask->testHold = false;  // let write task leave get/set Count method

    usleep( 100 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT( wtask->mCount ==  0 );
    CPPUNIT_ASSERT( wtask->nowCount ==  1 ); // should be signalled and count copied

    /*
     * Go through the increment again and check that the wtask count
     * gets incremented.
     */

    wtask->testHold = true;     // keep write task in get/set Count method

    atask->state = ct_writecount; // as increment task to read an increment

    usleep( 100 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT( wtask->mCount ==  2 );
    CPPUNIT_ASSERT( wtask->nowCount ==  1 ); // no signal yet, should copy mCount to nowCount

    wtask->testHold = false;  // let write task leave get/set Count method

    usleep( 100 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT( wtask->mCount ==  0 );
    CPPUNIT_ASSERT( wtask->nowCount ==  2 ); // should be signalled and count copied


    /*
     * Now ask the a task to increment the value and write it and hold it in
     * the lock, then ask the b task to run, it should be blocked by
     * the mutex until write hold is released. This should result in the
     * count being set to 1 as it's the first time btask has written.
     */

    wtask->testHold = true;     // keep write task in get/set Count method

    atask->state = ct_writecount; // as increment task to read an increment

    usleep( 100 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT( wtask->mCount ==  3 );
    CPPUNIT_ASSERT( wtask->nowCount ==  2 ); // no signal yet, should copy mCount to nowCount



    // the the unclock proceed, allowing the reset task to run.
    wtask->testHold = false;  // let write task leave get/set Count method

    usleep( 100 * 1000 );  // give task time to see change and call getCount()
    // check the reset has reset the count and the mutex is unlocked.
    CPPUNIT_ASSERT( wtask->mCount ==  0 );
    CPPUNIT_ASSERT( wtask->nowCount ==  3 );

    // let all the tasks die and make sure they do.

    atask->state = ct_exit;

    wtask->setCount(0); // should cause write task to exit.

    usleep( 200 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT(wtask->isRunning() == false);
    CPPUNIT_ASSERT(atask->isRunning() == false);

    // delete the writer task so that the destructor deletes the Mutex.
    delete(wtask);
    delete(atask);


}
