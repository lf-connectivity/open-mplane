/*
 * PowerCOntrolTestCase.cpp
 *
 *  Created on: 27 Mar 2013
 *      Author: gdurban
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>

#include "RxService.h"
#include "RxServiceTestCase.h"


using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( RxServiceTestCase );

using namespace std;

/*
 * Unit test
 */
void RxServiceTestCase::testCreation()
{
    cout << "testCreation" << endl;

    RxService * rxGainCtl = new RxService();

    CPPUNIT_ASSERT(rxGainCtl != 0);

    CPPUNIT_ASSERT( rxGainCtl->getState() == Service::ServiceCreated );

    CPPUNIT_ASSERT( rxGainCtl->start() == Service::Start );

    usleep( 100 * 1000 );   // sleep for just over the default service update period

    CPPUNIT_ASSERT( rxGainCtl->getState() == Service::ServiceRunning );

    // check calling resume has no effect
    CPPUNIT_ASSERT( rxGainCtl->resume() == Service::Noop );

    CPPUNIT_ASSERT( rxGainCtl->suspend() == Service::Suspend );

    usleep( 100 * 1000 );   // sleep for just over default service update period

    // check still suspended
    CPPUNIT_ASSERT( rxGainCtl->getState() == Service::ServiceSuspended );

    // lets resume
    CPPUNIT_ASSERT( rxGainCtl->resume() == Service::Resume );

    usleep( 100 * 1000 );   // give it a little time to resume, ekse reset will fail.

    CPPUNIT_ASSERT( rxGainCtl->getState() == Service::ServiceRunning );


    CPPUNIT_ASSERT( rxGainCtl->reset() == Service::Reset );

    usleep( 100 * 1000 );   // give it a little time to resume, ekse reset will fail.

    CPPUNIT_ASSERT( rxGainCtl->getState() == Service::ServiceRunning );

    CPPUNIT_ASSERT( rxGainCtl->shutdown() == Service::Shutdown );
    usleep( 100 * 1000 );   // small sleep give it time to process but not as much as wait
    CPPUNIT_ASSERT( rxGainCtl->getState() == Service::ServiceShutdown );
    CPPUNIT_ASSERT( rxGainCtl->wasCancelled() == false );
    CPPUNIT_ASSERT( rxGainCtl->getExitValue() == 0 );

    delete rxGainCtl;

}
