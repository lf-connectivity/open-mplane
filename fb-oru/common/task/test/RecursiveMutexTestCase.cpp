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

#include "RecursiveMutexTestCase.h"

using namespace Mplane;
using namespace std;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( RecursiveMutexTestCase );


RecWTask::RecWTask():Task(0, Task::SMALL_STACK),
        mCount(0), testHold(false)
{
    state = mt_idle;
}

void Mplane::RecWTask::setCount(int count)
{
    RecursiveMutex::Lock lock( mMutex );  // use the Mutex lock guard here

    mCount = count;
    // set the new value but stay locked.
    while( testHold )
    {
        Mplane::Task::msSleep( 10 );
    }
}

int Mplane::RecWTask::getCount()
{
    int retCount = 0;
    mMutex.lock();          // use the mutex directly here

    retCount = mCount;

    mMutex.unlock();

    return ( retCount );
}

int RecWTask::run()
{
    while( state != mt_exit )
    {
        int theCount = getCount();
        cout << "Unit Test - count is: " << theCount << endl;
        Mplane::Task::msSleep( 100 );
    }
    return mCount;
}

RecIncTask::RecIncTask( RecWTask &task ):
        Task(50, Task::MEDIUM_STACK),
        count(0),
        mTask( task )
{
    state = mt_idle;
}

int RecIncTask::run()
{
    int locCount = 0;
    while( state != mt_exit )
    {
        if( state == mt_increment )
        {
            locCount++;
            mTask.setCount( locCount );
            state = mt_idle;
        }

        Mplane::Task::msSleep( 100 );
    }
    return count;
}

RecResetTask::RecResetTask(RecWTask &task):
        Task(500, Task::LARGE_STACK),
        state( mt_idle ),
        mTask (task)
{

}

int RecResetTask::run()
{
    while( state != mt_exit )
    {
        if( state == mt_reset )
        {
            mTask.setCount( 0 );
            state = mt_idle;
        }
        Mplane::Task::msSleep( 100 );
    }
    return 0;
}


void Mplane::RecursiveMutexTestCase::unittest()
{
    cout << endl << "*** RecursiveMutexTestCase unittest ***" <<  endl;

    wtask = new RecWTask();

    CPPUNIT_ASSERT(wtask != 0);

    inctask = new RecIncTask(*wtask);

    CPPUNIT_ASSERT(inctask != 0);

    resettask = new RecResetTask(*wtask);

    CPPUNIT_ASSERT(resettask != 0);

    CPPUNIT_ASSERT((void *)wtask != (void *)inctask);
    CPPUNIT_ASSERT((void *)wtask != (void *)resettask);
    CPPUNIT_ASSERT((void *)inctask != (void *)resettask);

    CPPUNIT_ASSERT(wtask->isRunning() == false);
    CPPUNIT_ASSERT(inctask->isRunning() == false);
    CPPUNIT_ASSERT(resettask->isRunning() == false);

    wtask->testHold = true;     // keep write task in get/set Count method

    wtask->start();
    inctask->start();
    resettask->start();

    usleep( 200 * 1000);

    CPPUNIT_ASSERT(wtask->isRunning() == true);
    CPPUNIT_ASSERT(inctask->isRunning() == true);
    CPPUNIT_ASSERT(resettask->isRunning() == true);


    /*
     * Ask the increment task to increment the count, hold it in the function
     * and check lock is set and check the lock state
     */

    inctask->state = mt_increment; // as increment task to read an increment

    usleep( 200 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT( wtask->mCount ==  1 );

    /*
     * Release is from hold, the count should be incremented and the mutex
     * unlocked.
     */

    wtask->testHold = false;  // let write task leave get/set Count method

    usleep( 200 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT( wtask->mCount ==  1 );

    /*
     * Go through the increment again and check that the wtask count
     * gets incremented.
     */

    wtask->testHold = true;     // keep write task in get/set Count method

    inctask->state = mt_increment; // as increment task to read an increment

    usleep( 200 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT( wtask->mCount ==  2 );

    wtask->testHold = false;  // let write task leave get/set Count method

    usleep( 200 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT( wtask->mCount ==  2 );


    /*
     * Now ask the increment task to increment the value and hold it in
     * the lock, then ask the reset task to run, it should be blocked by
     * the mutex until write hold is released. This should result in the
     * count being reset yo zero.
     */

    wtask->testHold = true;     // keep write task in get/set Count method

    inctask->state = mt_increment; // as increment task to read an increment

    usleep( 200 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT( wtask->mCount ==  3 );

    resettask->state = mt_reset;

    usleep( 200 * 1000 );  // give task time to see change and call getCount()

    // check the reset task doesn't get in to modify the count
    CPPUNIT_ASSERT( wtask->mCount ==  3 );

    // the the unclock proceed, allowing the reset task to run.
    wtask->testHold = false;  // let write task leave get/set Count method

    usleep( 200 * 1000 );  // give task time to see change and call getCount()
    // check the reset has reset the count and the mutex is unlocked.
    CPPUNIT_ASSERT( wtask->mCount ==  0 );

    // let all the tasks die and make sure they do.

    resettask->state = mt_exit;
    inctask->state = mt_exit;
    wtask->state = mt_exit;

    usleep( 1000 * 1000 );  // give task time to see change and call getCount()

    CPPUNIT_ASSERT(wtask->isRunning() == false);
    CPPUNIT_ASSERT(inctask->isRunning() == false);
    CPPUNIT_ASSERT(resettask->isRunning() == false);

    // delete the writer task so that the destructor deletes the Mutex.
    delete(wtask);
    delete(inctask);
    delete(resettask);


}
