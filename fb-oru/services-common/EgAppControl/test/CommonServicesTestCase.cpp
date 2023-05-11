/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonServicesTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>

#include "CommonServices.h"
#include "CommonServicesTestCase.h"

#include "IServicesCtl.h"

#include "TxService.h"
#include "RxService.h"
#include "FaultService.h"
#include "DigitalPowerService.h"
#include "FibreControlService.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonServicesTestCase );

using namespace std;

/*
 * Unit test
 */
void CommonServicesTestCase::unittest()
{
    cout << "CommonServices unit test" << endl;

    std::shared_ptr<IServicesCtl> testCtl( IServicesFactory::create() );

    std::shared_ptr<CommonServices> cs = std::dynamic_pointer_cast<CommonServices> (testCtl);

    CPPUNIT_ASSERT( cs->mTxService->getState() == Service::ServiceCreated );
    CPPUNIT_ASSERT( cs->mRxService->getState() == Service::ServiceCreated );
//    CPPUNIT_ASSERT( cs->mFaultService->getState() == Service::ServiceCreated );
    CPPUNIT_ASSERT( cs->mPowerService->getState() == Service::ServiceCreated );
    CPPUNIT_ASSERT( cs->mFibreControlService->getState() == Service::ServiceCreated );

    testCtl->start();

    usleep( 1300 * 1000 );

    CPPUNIT_ASSERT( cs->mTxService->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( cs->mRxService->getState() == Service::ServiceRunning );
//    CPPUNIT_ASSERT( cs->mFaultService->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( cs->mPowerService->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( cs->mFibreControlService->getState() == Service::ServiceRunning );

    testCtl->suspend();

    usleep( 1300 * 1000 );

    CPPUNIT_ASSERT( cs->mTxService->getState() == Service::ServiceSuspended );
    CPPUNIT_ASSERT( cs->mRxService->getState() == Service::ServiceSuspended );
//    CPPUNIT_ASSERT( cs->mFaultService->getState() == Service::ServiceSuspended );
    CPPUNIT_ASSERT( cs->mPowerService->getState() == Service::ServiceSuspended );
    CPPUNIT_ASSERT( cs->mFibreControlService->getState() == Service::ServiceSuspended );

    testCtl->resume();

    usleep( 250 * 1000 ); // give 'em a little time to resume

// don't test for resumed, won't see it.
//    CPPUNIT_ASSERT( cs->mTxService->getState() == Service::ServiceResumed );
//    usleep( 1200 * 1000 );

    CPPUNIT_ASSERT( cs->mTxService->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( cs->mRxService->getState() == Service::ServiceRunning );
//    CPPUNIT_ASSERT( cs->mFaultService->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( cs->mPowerService->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( cs->mFibreControlService->getState() == Service::ServiceRunning );

    testCtl->reset();

// don't test for reset state, won't see it.
//    usleep( 300 * 1000 ); // give 'em a little time to reset
//    CPPUNIT_ASSERT( cs->mTxService->getState() == Service::ServiceReset );

    usleep( 200 * 1000 );

    CPPUNIT_ASSERT( cs->mTxService->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( cs->mRxService->getState() == Service::ServiceRunning );
//    CPPUNIT_ASSERT( cs->mFaultService->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( cs->mPowerService->getState() == Service::ServiceRunning );
    CPPUNIT_ASSERT( cs->mFibreControlService->getState() == Service::ServiceRunning );


    usleep( 200 * 1000 );

    testCtl->shutdown();

    usleep( 200 * 1000 );

    CPPUNIT_ASSERT( cs->mTxService->getState() == Service::ServiceShutdown );
    CPPUNIT_ASSERT( cs->mRxService->getState() == Service::ServiceShutdown );
//    CPPUNIT_ASSERT( cs->mFaultService->getState() == Service::ServiceShutdown );
    CPPUNIT_ASSERT( cs->mPowerService->getState() == Service::ServiceShutdown );
    CPPUNIT_ASSERT( cs->mFibreControlService->getState() == Service::ServiceShutdown );

    CPPUNIT_ASSERT( cs->mTxService->wasCancelled() == false );
    CPPUNIT_ASSERT( cs->mTxService->getExitValue() == 0 );
    CPPUNIT_ASSERT( cs->mRxService->wasCancelled() == false );
    CPPUNIT_ASSERT( cs->mRxService->getExitValue() == 0 );
//    CPPUNIT_ASSERT( cs->mFaultService->wasCancelled() == false );
//    CPPUNIT_ASSERT( cs->mFaultService->getExitValue() == 0 );
    CPPUNIT_ASSERT( cs->mPowerService->wasCancelled() == false );
    CPPUNIT_ASSERT( cs->mPowerService->getExitValue() == 0 );
    CPPUNIT_ASSERT( cs->mFibreControlService->wasCancelled() == false );
    CPPUNIT_ASSERT( cs->mFibreControlService->getExitValue() == 0 );

}
