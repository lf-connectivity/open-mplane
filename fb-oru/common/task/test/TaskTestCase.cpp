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

#include "TaskTestCase.h"

using namespace Mplane;


using namespace std;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( TaskTestCase );


ATask::ATask():Task(0, Task::SMALL_STACK,"ATask","UT")
{
    count = 0;
    mRunForever = true;
    mRun = true;
}

int ATask::run()
{
    while( mRun )
    {
        if( count < 6)
            count++;
        Mplane::Task::msSleep( 500 );
        kickSoftwareWatchdog();
    }
    return count;
}

void ATask::show()
{
    logDebugNormal("Task: %s is %s",this->getName(),isRunning()?"RUNNING":"STOPPED");
    logDebugNormal("Task: %s Task ID=%d and parent PID=%d",this->getName(),this->getThreadID(),this->getParentPID());
    logDebugNormal("Task: %s Count is %d",this->getName(), count);
}

BTask::BTask():Task(50, Task::MEDIUM_STACK, "BTask", "UT")
{
    count = 0;
    mRunForever = true;
    mRun = true;
    failWatchDog = false;
}

int BTask::run()
{
    while( mRun )
    {
        if( count < 6)
            ++count;
        Mplane::Task::msSleep( 1000 );
        if( failWatchDog == false )
            kickSoftwareWatchdog();
    }
    return count;
}

void BTask::show()
{
    logDebugNormal("Task: %s is %s",this->getName(),isRunning()?"RUNNING":"STOPPED");
    logDebugNormal("Task: %s Task ID=%d and parent PID=%d",this->getName(),this->getThreadID(),this->getParentPID());
    logDebugNormal("Task: %s Count is %d",this->getName(), count);
}

CTask::CTask():Task(500, Task::LARGE_STACK, "CTask", "UT")
{
    count = 6;
    mRunForever = true;
    mRun = true;
}

int CTask::run()
{
    while( mRun )
    {
        --count;
        Mplane::Task::msSleep( 1000 );
        kickSoftwareWatchdog();
    }
    return count;
}

void CTask::show()
{
    logDebugNormal("Task: %s is %s",this->getName(),isRunning()?"RUNNING":"STOPPED");
    logDebugNormal("Task: %s Task ID=%d and parent PID=%d",this->getName(),this->getThreadID(),this->getParentPID());
    logDebugNormal("Task: %s Count is %d",this->getName(), count);
}


/*
 * Unit tests
 */
void TaskTestCase::testCreation()
{
    cout << endl << "*** TaskTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    TaskList::getInstance()->showNames();
    TaskList::getInstance()->show();

    task_a = new ATask();

    CPPUNIT_ASSERT(task_a != 0);

    task_b = new BTask();

    CPPUNIT_ASSERT(task_b != 0);

    task_c = new CTask();

    CPPUNIT_ASSERT(task_c != 0);

    CPPUNIT_ASSERT((void *)task_a != (void *)task_b);
    CPPUNIT_ASSERT((void *)task_a != (void *)task_c);
    CPPUNIT_ASSERT((void *)task_b != (void *)task_c);

    CPPUNIT_ASSERT(task_a->isRunning() == false);
    CPPUNIT_ASSERT(task_b->isRunning() == false);
    CPPUNIT_ASSERT(task_c->isRunning() == false);

    // Task inherits from GeneralLog, so test the GeneralLogList is initialised propertly
    std::stringstream ss;
    ss << std::endl;

//LOG:TODO    AAGlobal::gGeneralLogList.showNames(ss);
    task_a->logDebugNormal(ss.str());

    CPPUNIT_ASSERT(strcmp(task_a->getInstanceName().c_str(), "ATask") == 0);

    // NOTE: In order to be able to run under valgrind on the host I needed to increase the thread stack size, so these tests no longer
    // work
//    CPPUNIT_ASSERT(task_a->getStackSize() == PTHREAD_STACK_MIN);
//
//    CPPUNIT_ASSERT(task_b->getStackSize() == (2*PTHREAD_STACK_MIN));
//
//    CPPUNIT_ASSERT(task_c->getStackSize() == (4*PTHREAD_STACK_MIN));

    //pthread_attr_t attribute;

    int priority = sched_get_priority_min( SCHED_RR );
    CPPUNIT_ASSERT(task_a->getPriority() == priority );

    CPPUNIT_ASSERT(task_b->getPriority() == 50 );

    // this should be our safe upper limit of 98
    CPPUNIT_ASSERT(task_c->getPriority() == 98 );

//    TaskList::getInstance()->remove( task_a );
//    TaskList::getInstance()->remove( task_b );
//    TaskList::getInstance()->remove( task_c );

    delete task_a;
    delete task_b;
    delete task_c;


}

void TaskTestCase::testRun()
{
    cout << "testRun" << endl;

    TaskList::getInstance()->showNames();
    TaskList::getInstance()->show();

    task_a = new ATask();

    CPPUNIT_ASSERT(task_a != 0);

    task_b = new BTask();

    CPPUNIT_ASSERT(task_b != 0);

    task_c = new CTask();

    CPPUNIT_ASSERT(task_c != 0);

    TaskList::getInstance()->show();

    CPPUNIT_ASSERT(task_a->count == 0);
    CPPUNIT_ASSERT(task_b->count == 0);
    CPPUNIT_ASSERT(task_c->count == 6);

    TaskList::getInstance()->showNames();

    task_b->start();

    usleep( 50 * 1000 );  // 10 milliseconds, make sure task executes

    CPPUNIT_ASSERT(task_a->isRunning() == false);
    CPPUNIT_ASSERT(task_b->isRunning() == true);
    CPPUNIT_ASSERT(task_c->isRunning() == false);

    CPPUNIT_ASSERT(task_a->count == 0);
    CPPUNIT_ASSERT(task_b->count == 1);
    CPPUNIT_ASSERT(task_c->count == 6);

    usleep( 1050 * 1000 );  // sleep just over a second

    CPPUNIT_ASSERT(task_a->count == 0);
    CPPUNIT_ASSERT(task_b->count == 2);
    CPPUNIT_ASSERT(task_c->count == 6);

    task_a->start();

    usleep( 10 * 1000 );  // 10 milliseconds, make sure task executes

    CPPUNIT_ASSERT(task_a->isRunning() == true);
    CPPUNIT_ASSERT(task_b->isRunning() == true);
    CPPUNIT_ASSERT(task_c->isRunning() == false);

    CPPUNIT_ASSERT(task_a->count == 1);
    CPPUNIT_ASSERT(task_b->count == 2);
    CPPUNIT_ASSERT(task_c->count == 6);

    usleep( 520 * 1000 );  // sleep just over half a second
    CPPUNIT_ASSERT(task_a->count == 2);
    CPPUNIT_ASSERT(task_b->count == 2);
    CPPUNIT_ASSERT(task_c->count == 6);

    task_c->start();

    usleep( 10 * 1000 );  // 10 milliseconds, make sure task executes

    CPPUNIT_ASSERT(task_a->isRunning() == true);
    CPPUNIT_ASSERT(task_b->isRunning() == true);
    CPPUNIT_ASSERT(task_c->isRunning() == true);

    // now that all tasks are runniing check thread details are correct
    TaskList::getInstance()->show();

    TaskList::getInstance()->showNames();

    sched_param param;
    int policy;
    int ret;
    /* scheduling parameters of target thread */
    ret = pthread_getschedparam (task_a->getId(), &policy, &param);

    CPPUNIT_ASSERT( ret == 0 );
    CPPUNIT_ASSERT( param.sched_priority == task_a->getPriority() );
    CPPUNIT_ASSERT( policy == SCHED_RR );

    ret = pthread_getschedparam (task_b->getId(), &policy, &param);

    CPPUNIT_ASSERT( ret == 0 );
    CPPUNIT_ASSERT( param.sched_priority == task_b->getPriority() );
    CPPUNIT_ASSERT( policy == SCHED_RR );

    ret = pthread_getschedparam (task_c->getId(), &policy, &param);

    CPPUNIT_ASSERT( ret == 0 );
    CPPUNIT_ASSERT( param.sched_priority == task_c->getPriority() );
    CPPUNIT_ASSERT( policy == SCHED_RR );


    CPPUNIT_ASSERT(task_a->count == 2);
    CPPUNIT_ASSERT(task_b->count == 2);
    CPPUNIT_ASSERT(task_c->count == 5);

    usleep( 520 * 1000 );  // sleep just over half a second

    CPPUNIT_ASSERT(task_a->count == 3);
    CPPUNIT_ASSERT(task_b->count == 3);
    CPPUNIT_ASSERT(task_c->count == 5);

    usleep( 520 * 1000 );  // sleep just over half a second

     CPPUNIT_ASSERT(task_a->count == 4);
     CPPUNIT_ASSERT(task_b->count == 3);
     CPPUNIT_ASSERT(task_c->count == 4);

     usleep( 1050 * 1000 );  // sleep just over half a second

     CPPUNIT_ASSERT(task_a->count == 6);
     CPPUNIT_ASSERT(task_b->count == 4);
     CPPUNIT_ASSERT(task_c->count == 3);

     CPPUNIT_ASSERT(task_a->isRunning() == true);
     CPPUNIT_ASSERT(task_b->isRunning() == true);
     CPPUNIT_ASSERT(task_c->isRunning() == true);

     const char *failedService = 0;

     CPPUNIT_ASSERT( TaskList::getInstance()->allRunning( &failedService ) == true );

     CPPUNIT_ASSERT( task_c->wasCancelled() == false );

     cout <<"Cancel thread for task_c" << endl;

     // we shouldn't call thread cancel directly on our tasks so make sure
     // we've picked up this in our task list allRunning check.
     int result = pthread_cancel( task_c->getId() );

     cout <<"Cancel return: " << result << endl;
//     CPPUNIT_ASSERT( result == 0 );

     usleep( 1100 * 1000 );   // small sleep give it time to process but not as much as wait

     CPPUNIT_ASSERT( task_c->wasCancelled() == true );

TaskList::getInstance()->showNames() ;

     CPPUNIT_ASSERT( TaskList::getInstance()->allRunning( &failedService ) == false );

     CPPUNIT_ASSERT( strcmp( failedService, "CTask") == 0);

//     TaskList::getInstance()->remove( task_c );
     delete task_c;

     usleep( 200 * 1000 );   // small sleep give it time to process but not as much as wait

     TaskList::getInstance()->show();

     Task* task = TaskList::getInstance()->checkStuckTask();

     CPPUNIT_ASSERT( task == 0 );

     task_b->failWatchDog = true;   // cause task b to stop updating the software watchdog

     usleep( 2200 * 1000 ); // sleep for at least its update time to make sure it did its last kick

     task = TaskList::getInstance()->checkStuckTask();

     CPPUNIT_ASSERT( task != 0 );

     cout << "Task " << task->getName() << " has stopped updating the watch dog counter" << endl;

     CPPUNIT_ASSERT( task == task_b );

//     pthread_cancel( task->getId() );

     task_a->mRun = false;

     // let the other tasks finish
     usleep( 1050 * 1000 );  // sleep just over half a second

     CPPUNIT_ASSERT(task_a->isRunning() == false);
//     CPPUNIT_ASSERT(task_b->isRunning() == false);
     CPPUNIT_ASSERT(task_a->getExitValue() == 6);
//     CPPUNIT_ASSERT(task_b->getExitValue() == 6);

  //   pthread_cancel( task_a->getId() );
  //   pthread_cancel( task_b->getId() );

     task_b->stop();

     // task_a exited normally and so was not cancelled
     CPPUNIT_ASSERT( task_a->wasCancelled() == false );

     // because task_b was forced to stop, it was cancelled
     CPPUNIT_ASSERT( task_b->wasCancelled() == true );

     delete task_a;
     delete task_b;

}

void TaskTestCase::testStop()
{
    cout << __func__ << " - START" <<  endl;

    task_a = new ATask();

    CPPUNIT_ASSERT(task_a != 0);

//    task_a->start();

    delete task_a;

}
