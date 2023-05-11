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

#include "ServicesMonitor.h"
#include "KickWatchdog.h"
#include "IServicesMonitorFactory.h"
#include "ServicesMonitorTestCase.h"


using namespace Mplane;
using namespace std;

ServiceTest::ServiceTest(const char* sname, const char* su):
	Service( SERVICE_MEDIUM_PRIORITY,
		   SMALL_STACK,
		   1000,
		   sname, su ),
	mEnterTightLoop(false),
	mShutdown(false)
{
    count = 0;
}

void ServiceTest::show()
{
    logDebugNormal("*** Service: %s Show ***", getName());
}

int ServiceTest::service()
{
    count++;

    if( mEnterTightLoop == true )
    {
        cout << "Task: " << getName() << " entering tight loop" << endl;
        cout.flush();
        msSleep(500);
        while (!mShutdown)
        {
            if( (count++ % 100000) == 0 )
                msSleep(1);
        }
    }
    return 0;
}

ServiceTest::~ServiceTest()
{
	mShutdown = true ;
	msSleep(5) ;
}


/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( ServicesMonitorTestCase );

using namespace std;

/*
 * Unit test
 */
void ServicesMonitorTestCase::unittest()
{
    int ret;
    struct sched_param param;

    cout << "ServicesMonitor task unit test" << endl;

    std::shared_ptr<IServicesMonitor> sm( IServicesMonitorFactory::getInterface() );

    std::shared_ptr<ServicesMonitor> smp = std::dynamic_pointer_cast<ServicesMonitor>(sm);

    CPPUNIT_ASSERT( smp->mApplicationStableCount == ServicesMonitor::APPLICATION_STABLE_TIME );
    CPPUNIT_ASSERT( smp->mStartupPhase == true );

    sm->startMonitoring();

    usleep( 200 * 1000 );  // sleep just over a second so it completes one start phase loop

    CPPUNIT_ASSERT( smp->isRunning() == true );

    // create services, they get added to the global service list
    svc_a = new ServiceTest("A-Service","SV");
    svc_b = new ServiceTest("B-Service","SV");
    svc_c = new ServiceTest("C-Service","SV");
    svc_d = new ServiceTest("D-Service","SV");
    svc_e = new ServiceTest("E-Service","SV");

    svc_a->start();
    svc_b->start();
    svc_c->start();
    svc_d->start();
    svc_e->start();

    int policy;
    /* scheduling parameters of target thread */
    ret = pthread_getschedparam (smp->getId(), &policy, &param);

    CPPUNIT_ASSERT( ret == 0 );
    CPPUNIT_ASSERT( param.sched_priority == ServicesMonitor::SERVICE_MONITOR_PRIORITY );
    CPPUNIT_ASSERT( policy == SCHED_RR );


    TaskList::getInstance()->showNames();

    usleep( 1100 * 1000 );  // sleep just over a second so it completes one start phase loop

    CPPUNIT_ASSERT( smp->mApplicationStableCount <= ServicesMonitor::APPLICATION_STABLE_TIME );
    CPPUNIT_ASSERT( smp->mStartupPhase == true );

    sm->applicationStable();

    usleep( 1200 * 1000 );  // sleep just over a second so it completes one start phase loop
    CPPUNIT_ASSERT( smp->mStartupPhase == false );

    usleep( 500 * 1000 );  // sleep just over a second so it completes one start phase loop

    CPPUNIT_ASSERT( smp->mServiceDied == false );

    cout << "Cancel task C" << endl;
    pthread_cancel( svc_c->getId() );

    // give services monitor a chance to catch dead thread
    usleep( 5200 * 1000 );  // sleep just over a second so it completes one start phase loop

    CPPUNIT_ASSERT( smp->mServiceDied == true );

    CPPUNIT_ASSERT( smp->mServiceStuck == false );

    // give services monitor a chance to go through another check
    usleep( 5200 * 1000 );  // sleep just over a second so it completes one start phase loop

    CPPUNIT_ASSERT( smp->mServiceStuck == false );

    // now let's detect a stuck task. Should take 5 seconds
    cout << "Put task D into tight execution loop" << endl;
    svc_d->mEnterTightLoop = true;
    usleep( 15200 * 1000 );

    CPPUNIT_ASSERT( smp->mServiceStuck == true );

    // force task to die, this will delete the ServicesMonitor object, have to
    // manually recreate it.
    smp->mLoop = false;

    //----------------------------------------------------------------------------------

    ServicesMonitor* smp2 = new ServicesMonitor();

    IServicesMonitor& smi = *smp2;

    CPPUNIT_ASSERT( smp2->mApplicationStableCount == ServicesMonitor::APPLICATION_STABLE_TIME );
    CPPUNIT_ASSERT( smp2->mStartupPhase == true );

    smi.startMonitoring();

    usleep( 200 * 1000 );  // sleep just over a second so it completes one start phase loop

    CPPUNIT_ASSERT( smp2->isRunning() == true );

    usleep( 1100 * 1000 );  // sleep just over a second so it completes one start phase loop

    CPPUNIT_ASSERT( smp2->mApplicationStableCount < ServicesMonitor::APPLICATION_STABLE_TIME );
    CPPUNIT_ASSERT( smp2->mStartupPhase == true );

    // test the app failing
    smp2->applicationFailed();

    usleep( 1200 * 1000 );  // sleep just over a second so it completes one start phase loop
    CPPUNIT_ASSERT( smp2->mApplicationStableCount == 0 );
    CPPUNIT_ASSERT( smp2->mStartupPhase == false );

    pthread_cancel( svc_a->getId() );
    pthread_cancel( svc_b->getId() );
    pthread_cancel( svc_d->getId() );
    pthread_cancel( svc_e->getId() );


    std::cerr << "** TEST TIDY ** " << std::endl ;

    std::cerr << "* del Service A" << std::endl ;
    delete svc_a;
    std::cerr << "* del Service B" << std::endl ;
    delete svc_b;
    std::cerr << "* del Service C" << std::endl ;
    delete svc_c;
    std::cerr << "* del Service D" << std::endl ;
    delete svc_d;
    std::cerr << "* del Service E" << std::endl ;
    delete svc_e;

    std::cerr << "* del ServiceMonitor" << std::endl ;
    delete smp2;

    std::cerr << "** TEST END **" << std::endl ;

}
