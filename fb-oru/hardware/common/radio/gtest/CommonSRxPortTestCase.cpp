/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonSRxPortTestCase.cpp
 * \brief     The Test file for CommonSRxPort
 *
 *
 * \details   The Test file for CommonSRxPort
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "CommonSRxPortTestCase.h"
#include "CommonSRxPort.h"
#include "CommonFPGA.h"
#include "OffTargetFPGA.h"

using namespace Mplane;
using namespace std;

/***************************/


/***************************/

namespace Mplane
{

// Test objects

Mplane::TestCommonSRxPort::TestCommonSRxPort():
    	    mName ( "Mplane::TestCommonSRxPort" )
{
}

Mplane::TestCommonSRxPort::~TestCommonSRxPort()
{
    cout << "Mplane::TestCommonSRxPort destructor" << endl;
    mName = NULL;
}

/*
 * Unit tests
 */
void Mplane::CommonSRxPortTestCases::SetUp()
{

}

void Mplane::CommonSRxPortTestCases::TearDown()
{
}

void Mplane::CommonSRxPortTestCases::unittest()
{
    cout << __func__ << "- START" <<  endl;


    CommonSRxPort* port = new CommonSRxPort( 0, "SRXPort");

    ASSERT_TRUE(port != 0);

    ASSERT_TRUE(port->getIndex() == 0);

    ASSERT_TRUE(port->getName() == "SRXPort" );

    long long unsigned freqInHz = 1234000;
    Frequency frequency(freqInHz) ;

    port->setFrequency(frequency);
    // Test removed as frequency no longer stored in the port, it is help in the device.
    //   ASSERT_EQ(freqInHz, port->mNCOFreq.getUint() );
    ASSERT_EQ(freqInHz, port->getFrequency().getUint() );

    // Ensure rssiDone bit is set to allow test to run
    std::shared_ptr<OffTargetFPGA> offTargetFpga = OffTargetFPGA::getInstance();
    offTargetFpga->writeField("rssiDone", 1);

    cout << "getRssi() = " << port->getRawAdcRms() << endl;

    Power rssiActual = port->getRawAdcRms();
    Power rssiExpected(14.2678, Power::dBm);

    // The power class overloads the == operator. So use that to compare the two values.
    // Returns true if they are the same.
    ASSERT_EQ(rssiExpected, rssiActual);

    delete( port );

    ISRxPort* iPort = dynamic_cast<ISRxPort*> (new CommonSRxPort( 2, "VirtualSRxPort"));

    ASSERT_TRUE(iPort != 0);

    ASSERT_TRUE(iPort->getIndex() == 2);

    ASSERT_TRUE(iPort->getName() == "VirtualSRxPort" );

    delete iPort ;

    cout << __func__ << " - END" <<  endl;

}


TEST_F(CommonSRxPortTestCases, unittest)
{
    unittest();
}


} // Namespace
