/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultServiceTestCase.cpp
 * \brief     Implementation of the CppUnit test harness for FaultService classes
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the FaultService classes.
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>


#include "FaultBuilder.h"
#include "IFaultBuilder.h"
#include "FaultService.h"
#include "FaultServiceTestCase.h"

using namespace Mplane;
using namespace std;


// Dummy fault builder
class TestFaultBuilder : public FaultBuilder {
};

std::shared_ptr<IFaultBuilder> IFaultBuilder::getInstance()
{
	static std::shared_ptr<IFaultBuilder> instance(new TestFaultBuilder()) ;
	return instance ;
}

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( FaultServiceTestCase );

/* Our test classes implementation used for the unit tests */


/*
 * Unit test
 */
void FaultServiceTestCase::testCreation()
{
    cout << endl << "*** FaultServiceTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL) ;

    std::shared_ptr<FaultService>  faults(new FaultService());

    CPPUNIT_ASSERT(faults != 0);

    // lets do the show method to see what faults we have
    faults->show();

    CPPUNIT_ASSERT( faults->getState() == Service::ServiceCreated );

    CPPUNIT_ASSERT( faults->start() == Service::Start );

    usleep( 100 * 1000 );   // sleep for just over the default service update period

    CPPUNIT_ASSERT( faults->getState() == Service::ServiceRunning );

    // check calling resume has no effect
    CPPUNIT_ASSERT( faults->resume() == Service::Noop );

    CPPUNIT_ASSERT( faults->suspend() == Service::Suspend );

    usleep( 100 * 1000 );   // sleep for just over default service update period

    // check still suspended
    CPPUNIT_ASSERT( faults->getState() == Service::ServiceSuspended );

    // lets resume
    CPPUNIT_ASSERT( faults->resume() == Service::Resume );

    usleep( 100 * 1000 );   // give it a little time to resume, else reset will fail.

    CPPUNIT_ASSERT( faults->reset() == Service::Reset );

    CPPUNIT_ASSERT( faults->shutdown() == Service::Shutdown );
    usleep( 100 * 1000 );   // small sleep give it time to process but not as much as wait
    CPPUNIT_ASSERT( faults->getState() == Service::ServiceShutdown );
    CPPUNIT_ASSERT( faults->wasCancelled() == false );
    CPPUNIT_ASSERT( faults->getExitValue() == 0 );

    cout << __func__ << " - END" <<  endl;

}
