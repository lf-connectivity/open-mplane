/*
 * PowerControlTestCase.cpp
 *
 *  Created on: 27 Mar 2013
 *      Author: gdurban
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "OranRrhUpdateService.h"
#include "CommonRadio.h"

#include "TestCommonRadio.h"

using namespace Mplane;

using namespace std;



namespace Mplane
{

class RrhUpdateServiceTestCases: public ::testing::Test
{
protected:
    virtual void SetUp();
    virtual void TearDown();
    virtual void testCreation();

};

void Mplane::RrhUpdateServiceTestCases::SetUp()
{
}

void Mplane::RrhUpdateServiceTestCases::TearDown()
{
}

void Mplane::RrhUpdateServiceTestCases::testCreation()
{
    cout << "testCreation" << endl;

    OranRrhUpdateService * updateService = new OranRrhUpdateService();

    ASSERT_TRUE(updateService != 0);

    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL) ;

    ASSERT_TRUE( updateService->getState() == Service::ServiceCreated );
    updateService->start();

    usleep( 100 * 1000 );   // give it chance

    ASSERT_TRUE( updateService->getState() == Service::ServiceRunning );

    // check calling resume has no effect
    updateService->resume();
    ASSERT_TRUE( updateService->getState() == Service::ServiceRunning );

    updateService->suspend();
    usleep( 100 * 1000 );   // give it chance
    ASSERT_TRUE( updateService->getState() == Service::ServiceSuspended );


    // lets resume
    updateService->resume();
    usleep( 500 * 1000 );   // give it a chance
    ASSERT_EQ( updateService->getState(), Service::ServiceRunning );

    updateService->reset();
    usleep( 100 * 1000 );   // give it a chance
    ASSERT_TRUE( updateService->getState() == Service::ServiceRunning );

    ASSERT_TRUE( updateService->shutdown() == Service::Shutdown );
    usleep( 100 * 1000 );   // small sleep give it time to process but not as much as wait
    ASSERT_TRUE( updateService->getState() == Service::ServiceShutdown );
    ASSERT_TRUE( updateService->wasCancelled() == false );
    ASSERT_TRUE( updateService->getExitValue() == 0 );

    delete updateService;

}


/*
 * Unit tests
 */
TEST_F(RrhUpdateServiceTestCases, TestCreation)
{
    cout << endl << "*** RrhUpdateServiceTestCases Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    testCreation();


    cout << __func__ << " - END" <<  endl;
}

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

} // end namespace
