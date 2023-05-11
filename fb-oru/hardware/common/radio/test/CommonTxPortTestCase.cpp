/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxPortTestCase.cpp
 * \brief     Implement the CommonTxPort unit test
 *
 *
 * \details   Implement the CommonTxPort unit test
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>

#include "Observer.hpp"
#include "CommonTxPort.h"
#include "CommonTxPortTestCase.h"


using namespace std;

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonTxPortTestCase );

class CommonTxPortTest: public CommonTxPort
{
public:

	CommonTxPortTest( int index, const char* name):
        CommonTxPort( index, name )
	{
	}


    virtual ~CommonTxPortTest() {}

    virtual ReturnType::State setTxOnLowLevel() { return ReturnType::RT_OK; }
    virtual ReturnType::State setTxOffLowLevel() { return ReturnType::RT_OK; }
    virtual Power getRfPower()
    {
        Power avg = 0.0f;
        return avg;
    }
    virtual ReturnType::State resetFifo()
    {
        return ReturnType::RT_OK;
    }
    unsigned getFifoLevel()
    {
    	return 4 ;
    }

};


/*
 * Unit tests
 */
void CommonTxPortTestCase::unittest()
{
    cout << "CommonTxPort unit test" << endl;

    CommonTxPort* port = new CommonTxPortTest( 0, "ThePort");

    CPPUNIT_ASSERT(port != 0);

    CPPUNIT_ASSERT(port->getIndex() == 0);

    CPPUNIT_ASSERT(port->getName() == "ThePort" );

    delete( port );

    ITxPort* iPort = dynamic_cast<ITxPort*> (new CommonTxPortTest( 2, "VirtualTxPort"));

    CPPUNIT_ASSERT(iPort != 0);

    CPPUNIT_ASSERT(iPort->getIndex() == 2);

    CPPUNIT_ASSERT(iPort->getName() == "VirtualTxPort" );

    delete iPort ;


    // test the setters and getters
    port = new CommonTxPortTest( 0, "ThePort");

    Subject<ITxPort>* sPort( dynamic_cast< Subject<ITxPort>* > ( port ) );

    CPPUNIT_ASSERT( sPort->getNumObservers() == 0);

    CommonTxPortObserver* txPortObs = new CommonTxPortObserver( iPort );

    long long unsigned freqInHz = 1234000;
    Frequency frequency(freqInHz) ;

    CPPUNIT_ASSERT( sPort->getNumObservers() == 1);

    CPPUNIT_ASSERT(port->initialise() == ReturnType::RT_OK);
    CPPUNIT_ASSERT(port->isTxOn() == false);

    port->setFrequency(frequency);
// Test removed as frequency no longer stored in the port, it is help in the device.
//  CPPUNIT_ASSERT_EQUAL(freqInHz, port->mNCOFreq.getUint() );
//    CPPUNIT_ASSERT_EQUAL(freqInHz, port->getFrequency().getUint() );

    CPPUNIT_ASSERT( txPortObs->mObsCalled == false );
    CPPUNIT_ASSERT( txPortObs->mTxState == false );

    port->setTxOn();
    CPPUNIT_ASSERT(port->isTxOn() == true);
    CPPUNIT_ASSERT( txPortObs->mObsCalled == true );
    CPPUNIT_ASSERT( txPortObs->mTxState == true );

    txPortObs->mObsCalled = false;

    port->setTxOff();
    CPPUNIT_ASSERT(port->isTxOn() == false);
    CPPUNIT_ASSERT( txPortObs->mObsCalled == true );
    CPPUNIT_ASSERT( txPortObs->mTxState == false );

    // remove observer should deregister it and number of observer goes back to zero.
    delete txPortObs;
    CPPUNIT_ASSERT( sPort->getNumObservers() == 0);

    //////////////  Power interface content

    Power setRf;
    Power setDigital;
    Power forward;
    Power digital;
    Power targetSet;
    Power targetGet;

    CPPUNIT_ASSERT(port->getFwdPower( forward, digital ) == ReturnType::RT_OK );
    CPPUNIT_ASSERT( forward == 0.0f );
    CPPUNIT_ASSERT( digital == 0.0f );

    setRf = 38.7f;
    setDigital = -14.5f;

//    CPPUNIT_ASSERT(port->updatePowerReadings( setRf, setDigital ) == ReturnType::RT_OK );

    CPPUNIT_ASSERT(port->getFwdPower( forward, digital ) == ReturnType::RT_OK );
//    CPPUNIT_ASSERT( forward == 38.7f );
//    CPPUNIT_ASSERT( digital == -14.5f );

    CPPUNIT_ASSERT( forward == 0.0f );
    CPPUNIT_ASSERT( digital == 0.0f );


    targetSet.setWatts( 49.0 );
    CPPUNIT_ASSERT(port->setTargetPower( targetSet ) == ReturnType::RT_OK );

    targetGet = port->getTargetPower();

    CPPUNIT_ASSERT( targetGet.getInt( Power::TdBm ) == 469 );
    CPPUNIT_ASSERT( targetGet == targetSet );

    ////////////// End power interface content

    CPPUNIT_ASSERT(port->getMaxPower().get() == 0.0);
//    CPPUNIT_ASSERT(port->getMaxAttenuation(0) == 0xFFF);
//    CPPUNIT_ASSERT(port->getMinAttenuation(0) == 0);
//    CPPUNIT_ASSERT(port->getDacValueForAttenuation(0, 0) == 0);
    CPPUNIT_ASSERT_EQUAL(0ull, port->getCalFrequency().getUint());

    CPPUNIT_ASSERT(port->setTxDelay(0) == ReturnType::RT_OK);

    // tidy up
    delete( port );


}
