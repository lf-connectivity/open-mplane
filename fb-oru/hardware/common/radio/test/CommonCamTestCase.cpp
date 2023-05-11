/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAdcTestCase.cpp
 * \brief     Define the unit tests for the CommonAdc class
 *
 *
 * \details   Define the unit tests for the CommonAdc class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>

#include <memory>

#include "CommonCam.h"
#include "CommonCamTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonCamTestCase );

using namespace std;

/****** Area for unit test specifics  ******/

namespace Mplane
{

// The CAM test class
class TestCam : public CommonCam
{
public:

    TestCam( int index, const char* name);

    virtual ~TestCam() { };

    virtual ReturnType::State doInit();

    virtual float  getTemperature(short int readTempSensor);

    virtual int readExternalBoardNumber();

    ICam::boardRevision readBoardRevision();

    virtual bool setAdcGain( unsigned int channel, ICam::adcGain_T adcGain) /* throw (std::out_of_range) */;
};

} /* namespace Mplane */

TestCam::TestCam( int index, const char* name):
        CommonCam::CommonCam(index, name)
{

}

ReturnType::State TestCam::doInit()
{
    ReturnType::State result = ReturnType::RT_OK;
    std::string resultString = "TESTCAM INITIALISED OK";

    setInitResultString(resultString);

    // waste a bit of time
    int timedelay = 1000000;
    while (timedelay != 0) timedelay--;

    return result;
}

float  TestCam::getTemperature(short int readTempSensor)
{
    std::string resultString = "TESTCAM GET TEMPERATURE";

    setInitResultString(resultString);

    // waste a bit of time
    int timedelay = 1000000;
    while (timedelay != 0) timedelay--;

    return 30.00;
}

int TestCam::readExternalBoardNumber()
{
    std::string resultString = "TESTCAM READ EXTERNAL BOARD NUMBER";

    setInitResultString(resultString);

    // waste a bit of time
    int timedelay = 1000000;
    while (timedelay != 0) timedelay--;

    return 8;
}

ICam::boardRevision TestCam::readBoardRevision()
{
    std::string resultString = "TESTCAM READ BOARD REVISION";

    setInitResultString(resultString);

    // waste a bit of time
    int timedelay = 1000000;
    while (timedelay != 0) timedelay--;

    return ICam::REV_1;
}

bool TestCam::setAdcGain( unsigned int channel, ICam::adcGain_T adcGain) /* throw (std::out_of_range) */
{
    std::string resultString = "TESTCAM SET ADC GAIN";

    setInitResultString(resultString);

    // waste a bit of time
    int timedelay = 1000000;
    while (timedelay != 0) timedelay--;

    return true;
}

/****** End of Area for unit test specifics  ******/

/*
 * Unit tests
 */
void CommonCamTestCase::testCreation()
{
    cout << endl << "*** CommonCamTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    CommonCam* testCam1 = new TestCam( 0, "TheCAM1");
    CPPUNIT_ASSERT(testCam1 != 0);
    CommonCam* testCam2 = new TestCam( 1, "TheCAM2");
    CPPUNIT_ASSERT(testCam2 != 0);
    CPPUNIT_ASSERT(testCam1 != testCam2);

    CPPUNIT_ASSERT(testCam1->getIndex() == 0);
    CPPUNIT_ASSERT(strcmp(testCam1->getName().c_str(), "TheCAM1") == 0 );
    CPPUNIT_ASSERT(testCam1->getTemperature(1) == 30.00);
    CPPUNIT_ASSERT(testCam1->readExternalBoardNumber() == 8);

    CPPUNIT_ASSERT(testCam2->getIndex() == 1);
    CPPUNIT_ASSERT(strcmp(testCam2->getName().c_str(), "TheCAM2") == 0 );
    CPPUNIT_ASSERT(testCam2->getTemperature(2) == 30.00);
    CPPUNIT_ASSERT(testCam2->readExternalBoardNumber() == 8);

    delete( testCam1 );
    delete( testCam2 );

    cout << __func__ << " - END" <<  endl;
}

void CommonCamTestCase::testInitialisation()
{
    cout << __func__ << " - START" <<  endl;

    TestCam* testCam1 = new TestCam( 0, "TheCAM1");
    CPPUNIT_ASSERT(testCam1 != 0);

    // then initialise and confirm it completed ok
    CPPUNIT_ASSERT(testCam1->initialise() == ReturnType::RT_OK);

    CPPUNIT_ASSERT(testCam1->getInitResult() == ReturnType::RT_OK);
    CPPUNIT_ASSERT( testCam1->getInitResultString() == "TESTCAM INITIALISED OK");
    CPPUNIT_ASSERT(testCam1->getInitStartTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testCam1->getInitEndTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testCam1->getInitDurationTime() != 0);
    CPPUNIT_ASSERT(testCam1->isInitComplete() == true);

    testCam1->show();

    cout << "The CAM Initialise execution duration was " << testCam1->getInitDurationTime() << " usecs" << endl;

    delete( testCam1 );

    cout << __func__ << " - END" <<  endl;
}

void CommonCamTestCase::testBaseClass()
{
    cout << __func__ << " - START" <<  endl;
    std::shared_ptr<TestCam> cam( new TestCam( 0, "TheBaseCam" ) );

    ReturnType::State status;
    int itest;
    bool btest;

    try
    {
        status = cam->readAdc( 0, itest );
    } catch( std::out_of_range &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "readAdc() not implemented in base class" ) == 0 );
    }


    try
    {
        btest = cam->writeDac( 0, 0 );
    } catch( std::out_of_range &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "writeDac() not implemented in base class" ) == 0 );
    }

    try
    {
        itest = cam->getValue( 0 );
    } catch( std::out_of_range &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getValue() not implemented in base class" ) == 0 );
    }

    try
    {
        btest = cam->setOutput( 0, false );
    } catch( std::out_of_range &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "setOutput() not implemented in base class" ) == 0 );
    }

    try
    {
        btest = cam->getOutput( 0 );
    } catch( std::out_of_range &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getOutput() not implemented in base class" ) == 0 );
    }

    try
    {
        btest = cam->getInput( 0 );
    } catch( std::out_of_range &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getInput() not implemented in base class" ) == 0 );
    }

    try
    {
        btest = cam->setFreeRun( false );
    } catch( std::out_of_range &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "setFreeRun() not implemented in base class" ) == 0 );
    }

    try
    {
        btest = cam->getFreeRun( );
    } catch( std::out_of_range &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getFreeRun() not implemented in base class" ) == 0 );
    }

    // keep compiler happy
    (void)itest ;
    (void)btest ;
    (void)status;

    cout << __func__ << " - END" <<  endl;
}
