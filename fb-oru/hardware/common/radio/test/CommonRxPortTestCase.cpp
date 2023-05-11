/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxTestCase.cpp
 * \brief      Implement the CommonRxPort unit test
 *
 *
 * \details    Implement the CommonTxPort unit test
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "CommonRxPort.h"
#include "CommonRxPortTestCase.h"


using namespace std;

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonRxPortTestCase );

class CommonRxPortTest: public CommonRxPort
{
public:

    CommonRxPortTest( int index, const char* name):
        CommonRxPort( index, name )
    {
    }

    virtual ~CommonRxPortTest() {}

    virtual ReturnType::State setRxOnLowLevel() { return ReturnType::RT_OK; }
    virtual ReturnType::State setRxOffLowLevel() { return ReturnType::RT_OK;}
};


void CommonRxPortTestCase::unittest()
{
    cout << "CommonRxPort unit test" << endl;

    CommonRxPort* port = new CommonRxPortTest( 0, "ThePort");

    CPPUNIT_ASSERT(port != 0);

    CPPUNIT_ASSERT(port->getIndex() == 0);

    CPPUNIT_ASSERT(port->getName() == "ThePort" );

     long long unsigned freqInHz = 2234000000;
     Frequency frequency(freqInHz) ;

     port->setFrequency(frequency);
// Test removed as frequency no longer stored in the port, it is help in the device.
//     CPPUNIT_ASSERT_EQUAL(freqInHz, port->mNCOFreq.getUint() );
     CPPUNIT_ASSERT_EQUAL(freqInHz, port->getFrequency().getUint() );




    delete( port );

    IRxPort* iPort = dynamic_cast<IRxPort*> (new CommonRxPortTest( 2, "VirtualRxPort"));

    CPPUNIT_ASSERT(iPort != 0);

    CPPUNIT_ASSERT(iPort->getIndex() == 2);

    CPPUNIT_ASSERT(iPort->getName() == "VirtualRxPort" );

    delete iPort ;

}
