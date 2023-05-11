/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ServiceTestCase.cpp
 * \brief     Implement CPPUNIT test case for Service class
 *
 *
 * \details   Implement CPPUNIT test case for Service class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>
#include <limits.h>

#include "Task.h"
#include "Service.h"
#include "ServiceTestCase.h"

#include <signal.h>
#include <pthread.h>


using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( ServiceTestCase );


AService::AService():
        Service( SERVICE_MEDIUM_PRIORITY,
        SMALL_STACK,
        1000,
        "A-Service", "UT")
{
    count = 0;
    std::cerr << "AService" << std::endl ;
}

void AService::show()
{
    logDebugNormal("*** %s Show ***",getName());
}

int AService::service()
{
    count++;
    return 0;
}


BService::BService():Service( SERVICE_MEDIUM_PRIORITY,
        SMALL_STACK,
        1000,
        "B-Service", "UT" )
{
    count = 0;
    doneRegObs = false;
    std::cerr << "BService" << std::endl ;
}

void BService::show()
{
    logDebugNormal("*** %s Show ***",getName());
}

int BService::service()
{
    count--;
    return 0;
}

void BService::doReset()
{
    count = 0;
    usleep( 1000 * 1000 );   // sleep a second for it test to check reset state

}

int Mplane::BService::getCount()
{
    return count;
}

void Mplane::BService::notifytest()
{
    this->eventNotify(); // test the notify executes the service loop immediately.
}

CService::CService():
        Service( SERVICE_MEDIUM_PRIORITY,
        SMALL_STACK,
        5001,
        "C-Service", "UT"),
        bForceError( false )
{
    count = 0;
    std::cerr << "CService" << std::endl ;
}

void CService::show()
{
    logDebugNormal("*** %s Show ***",getName());
}

int CService::service()
{
    count++;
    if( !bForceError)
        return 0;
    return -1;
}


bool BService::registerObservers()
{
    doneRegObs = true;
    return doneRegObs;
}

using namespace std;

/*
 * Unit tests
 */
void ServiceTestCase::unittest()
{
    cout << endl << "*** ServiceTestCase unit test ***" <<  endl;

    svc_a = new AService();

    CPPUNIT_ASSERT(svc_a != 0);
    svc_b = new BService();

    CPPUNIT_ASSERT(svc_b != 0);

     // CService uses an invalid timer period
    svc_c = new CService();

    CPPUNIT_ASSERT(svc_c != 0);


    CPPUNIT_ASSERT((void *)svc_a != (void *)svc_b);

    // Test the base class show(), which should be overridden by inheritors
    svc_a->Service::show();

    // Now do the inherited shows
    svc_a->show();
    svc_b->show();
    svc_c->show();

    CPPUNIT_ASSERT(svc_a->isRunning() == false);
    CPPUNIT_ASSERT(svc_b->isRunning() == false);
    CPPUNIT_ASSERT(svc_c->isRunning() == false);

    CPPUNIT_ASSERT( svc_a->getState() == Service::ServiceCreated );
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceCreated );
    CPPUNIT_ASSERT( svc_c->getState() == Service::ServiceCreated );

    TaskList::getInstance()->showNames();
    CPPUNIT_ASSERT( svc_a->start() == Service::Start );
    CPPUNIT_ASSERT( svc_b->start() == Service::Start );
    CPPUNIT_ASSERT( svc_c->start() == Service::Start );

    TaskList::getInstance()->showNames();

    // check the start method called out registerObservers() method
    CPPUNIT_ASSERT( svc_b->doneRegObs == true );
    usleep( 1200 * 1000 );   // sleep for just over the default service update period

    CPPUNIT_ASSERT( svc_a->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( svc_c->getState() == Service::ServiceRunning );

    // Ensure calling start again has no effect
    CPPUNIT_ASSERT( svc_a->start() == Service::Noop );
    CPPUNIT_ASSERT( svc_b->start() == Service::Noop );
    CPPUNIT_ASSERT( svc_a->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceRunning );

    // check calling resume has no effect
    CPPUNIT_ASSERT( svc_a->resume() == Service::Noop );
    CPPUNIT_ASSERT( svc_b->resume() == Service::Noop );
    CPPUNIT_ASSERT( svc_a->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceRunning );

    TaskList::getInstance()->showNames();

    usleep( 1200 * 1000 );   // sleep for just over the default service update period

    // now see if the service run method has called our service methods.
    CPPUNIT_ASSERT( svc_b->count < 0 );
    CPPUNIT_ASSERT( svc_a->count > 0 );
    // it's a slow loop but it should have run the service on entry
    CPPUNIT_ASSERT( svc_c->count == 1 );

    CPPUNIT_ASSERT( svc_a->suspend() == Service::Suspend );
    CPPUNIT_ASSERT( svc_b->suspend() == Service::Suspend );
    usleep( 200 * 1000 );   // sleep to give them time to suspend

    CPPUNIT_ASSERT( svc_a->getState() == Service::ServiceSuspended );
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceSuspended );

    int scv_a_count = svc_a->count;
    int scv_b_count = svc_b->count;

     TaskList::getInstance()->showNames();

    usleep( 1100 * 1000 );   // sleep for just over default service update period

    // check still suspended
    CPPUNIT_ASSERT( svc_a->getState() == Service::ServiceSuspended );
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceSuspended );

    // check calling again has no effect
    CPPUNIT_ASSERT( svc_a->suspend() == Service::Noop );
    CPPUNIT_ASSERT( svc_b->suspend() == Service::Noop );
    CPPUNIT_ASSERT( svc_a->getState() == Service::ServiceSuspended );
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceSuspended );

    // check the values have not changed as service is suspended
    CPPUNIT_ASSERT( svc_a->count == scv_a_count);
    CPPUNIT_ASSERT( svc_b->count == scv_b_count);

    // lets resume
    CPPUNIT_ASSERT( svc_a->resume() == Service::Resume );
    CPPUNIT_ASSERT( svc_b->resume() == Service::Resume );
    usleep( 200 * 1000 );   // sleep to give them time to resume

    CPPUNIT_ASSERT( svc_a->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceRunning );

     TaskList::getInstance()->showNames();

    usleep( 1200 * 1000 );   // sleep for just over the default service update period

    CPPUNIT_ASSERT( svc_a->count > scv_a_count);
    CPPUNIT_ASSERT( svc_b->count < scv_b_count);

    // now lets call reset, this should leave service a data unchanged but reset
    // service b data back to zero, as per the overridden implementation.
    CPPUNIT_ASSERT( svc_a->reset() == Service::Reset );
    CPPUNIT_ASSERT( svc_b->reset() == Service::Reset );
    usleep( 100 * 1000 );   // give them chance to process the command

    // the svc_b doReset implementation has a two second delay so we can see the ServiceReset state
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceReset );
    CPPUNIT_ASSERT( svc_b->count == 0);  // svc_b reset sets count back to zero
    CPPUNIT_ASSERT( svc_a->count > scv_a_count);  // svc_a reset does nothing
    usleep( 1200 * 1000 );   // the the thread a chance to do the reset
    // check back in running state
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( svc_a->getState() == Service::ServiceRunning );

    svc_b->notifytest();    // do a notify, so it should increment and go back into its wait 1 sec.
    usleep( 100 * 1000 );   // small sleep give it time to process but not as much as wait
    scv_b_count = svc_b->count;
    svc_b->notifytest();
    scv_b_count--;
    usleep( 100 * 1000 );   // small sleep give it time to process but not as much as wait
    CPPUNIT_ASSERT(scv_b_count == svc_b->count );

    usleep( 1100 * 1000 );   // small sleep give it time to process but not as much as wait

     TaskList::getInstance()->showNames();

        TaskList::getInstance()->show();

    const char *failedService = 0;

        CPPUNIT_ASSERT( TaskList::getInstance()->allRunning( &failedService ) == true );

    pthread_cancel( svc_a->getId() );

    usleep( 1100 * 1000 );   // small sleep give it time to process but not as much as wait

    // over 5 seconds into the test, the svc_c should have run again, check the count.
    CPPUNIT_ASSERT( svc_c->count == 2 );

    CPPUNIT_ASSERT( svc_a->wasCancelled() == true );

    TaskList::getInstance()->showNames();

    TaskList::getInstance()->show();

    CPPUNIT_ASSERT( TaskList::getInstance()->allRunning( &failedService ) == false );

    CPPUNIT_ASSERT( strcmp( failedService, "A-Service") == 0);

    // check the state name strings
    CPPUNIT_ASSERT( strcmp(svc_a->getStateName(Service::ServiceCreated), "Created") == 0 );
    CPPUNIT_ASSERT( strcmp(svc_a->getStateName(Service::ServiceStarted), "Started") == 0 );
    CPPUNIT_ASSERT( strcmp(svc_a->getStateName(Service::ServiceReset), "Reset") == 0 );
    CPPUNIT_ASSERT( strcmp(svc_a->getStateName(Service::ServiceSuspended), "Suspended") == 0 );
    CPPUNIT_ASSERT( strcmp(svc_a->getStateName(Service::ServiceResumed), "Resumed") == 0 );
    CPPUNIT_ASSERT( strcmp(svc_a->getStateName(Service::ServiceRunning), "Running") == 0 );
    CPPUNIT_ASSERT( strcmp(svc_a->getStateName(Service::ServiceFault), "Fault") == 0 );

    svc_c->bForceError = true;
    svc_c->eventNotify(); // force the service to update
    usleep( 100 * 1000 );   // small sleep give it time to process but not as much as wait
    CPPUNIT_ASSERT( svc_c->getState() == Service::ServiceShutdown );
    CPPUNIT_ASSERT( svc_c->wasCancelled() == false );
    CPPUNIT_ASSERT( svc_c->getExitValue() == -1 );

    CPPUNIT_ASSERT( svc_b->shutdown() == Service::Shutdown );
    usleep( 100 * 1000 );   // small sleep give it time to process but not as much as wait
    CPPUNIT_ASSERT( svc_b->getState() == Service::ServiceShutdown );
    CPPUNIT_ASSERT( svc_b->wasCancelled() == false );
    CPPUNIT_ASSERT( svc_b->getExitValue() == 0 );


    std::cerr << "** End of tests **" << std::endl ;
    delete svc_b;
    delete svc_c;
    delete svc_a;

    cout << endl << "*** ServiceTestCase complete ***" <<  endl;

}
