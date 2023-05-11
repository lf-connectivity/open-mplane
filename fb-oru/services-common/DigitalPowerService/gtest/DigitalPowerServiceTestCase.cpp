/*
 * PowerControlTestCase.cpp
 *
 *  Created on: 27 Mar 2013
 *      Author: gdurban
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "DigitalPowerService.h"

#include "CommonRadio.h"

#include "TestCommonRadio.h"

using namespace Mplane;

using namespace std;



namespace Mplane
{

class DigitalPowerServiceTestCases: public ::testing::Test
{
protected:
    virtual void SetUp();
    virtual void TearDown();
    virtual void testCreation();

};

void Mplane::DigitalPowerServiceTestCases::SetUp()
{
}

void Mplane::DigitalPowerServiceTestCases::TearDown()
{
}

void Mplane::DigitalPowerServiceTestCases::testCreation()
{
    cout << "testCreation" << endl;

    DigitalPowerService * powerService = new DigitalPowerService();

    ASSERT_TRUE(powerService != 0);

    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL) ;

    ASSERT_TRUE( powerService->getState() == Service::ServiceCreated );
    powerService->start();

    usleep( 100 * 1000 );   // give it chance

    ASSERT_TRUE( powerService->getState() == Service::ServiceRunning );

    // check calling resume has no effect
    powerService->resume();
    ASSERT_TRUE( powerService->getState() == Service::ServiceRunning );

    powerService->suspend();
    usleep( 100 * 1000 );   // give it chance
    ASSERT_TRUE( powerService->getState() == Service::ServiceSuspended );


    // lets resume
    powerService->resume();
    usleep( 500 * 1000 );   // give it a chance
    ASSERT_EQ( powerService->getState(), Service::ServiceRunning );

    powerService->reset();
    usleep( 100 * 1000 );   // give it a chance
    ASSERT_TRUE( powerService->getState() == Service::ServiceRunning );

    ASSERT_TRUE( powerService->shutdown() == Service::Shutdown );
    usleep( 100 * 1000 );   // small sleep give it time to process but not as much as wait
    ASSERT_TRUE( powerService->getState() == Service::ServiceShutdown );
    ASSERT_TRUE( powerService->wasCancelled() == false );
    ASSERT_TRUE( powerService->getExitValue() == 0 );

    delete powerService;

}


/*
 * Unit tests
 */
TEST_F(DigitalPowerServiceTestCases, TestCreation)
{
    cout << endl << "*** DigitalPowerServiceTestCases Tests ***" <<  endl;
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
