/*
 * CommonRxPortTestCase.cpp
 *
 *  Created on: 15 May 2014
 *      Author: cmeech
 */
/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxPortTestCase.cpp
 * \brief     The Test file for CommonRxPort
 *
 *
 * \details   The Test file for CommonRxPort
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include <memory>
#include "CommonRxPortTestCase.h"
#include "CommonRxPort.h"

/***************************/


/***************************/

namespace Mplane
{
/*
 * Unit tests
 */
void Mplane::CommonRxPortTestCases::SetUp()
{

}

void Mplane::CommonRxPortTestCases::TearDown()
{
}

void Mplane::CommonRxPortTestCases::testCreation()
{

}

	/*! \brief  Google Test CommonRxPort tests
     *
     *  Google Test CommonRxPort tests
     *
     */

void Mplane::CommonRxPortTestCases::testRxPort()
{
    cout << __func__ << "- START" <<  endl;


    CommonRxPort* port = new TestRxPort( 0, "ThePort");

    ASSERT_TRUE(port != 0);

    ASSERT_TRUE(port->getIndex() == 0);

    ASSERT_TRUE(port->getName() == "ThePort" );

    port->initialise();

     Frequency frequency(20000ULL, Frequency::KHz ) ;

     ASSERT_EQ(port->setFrequency(frequency), ReturnType::RT_OUT_OF_RANGE );

     frequency.set(2345000, Frequency::KHz);
     ASSERT_EQ(port->setFrequency(frequency), ReturnType::RT_OK );

// Test removed as frequency no longer stored in the port, it is help in the device.
//   ASSERT_EQ(freqInHz, port->mNCOFreq.getUint() );
     ASSERT_EQ(frequency.getUint() , port->getFrequency().getUint() );

    delete( port );

    IRxPort* iPort = dynamic_cast<IRxPort*> (new TestRxPort( 2, "VirtualRxPort"));

    ASSERT_TRUE(iPort != 0);

    ASSERT_TRUE(iPort->getIndex() == 2);

    ASSERT_TRUE(iPort->getName() == "VirtualRxPort" );

    delete iPort ;

    cout << __func__ << " - END" <<  endl;

}

void Mplane::CommonRxPortTestCases::testErrorPaths()
{
    cout << __func__ << " - START" <<  endl;


    cout << __func__ << " - END" <<  endl;
}

void Mplane::CommonRxPortTestCases::testTidyUp()
{
    cout << __func__ << " - START" <<  endl;

    cout << __func__ << " - END" <<  endl;
}

/*
 * Unit test fixtures
 */
TEST_F(CommonRxPortTestCases, TestCreation)
{

	cout << endl << "*** CommonRxPortTestCases Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;
    testCreation();

    cout << __func__ << " - END" <<  endl;
}


TEST_F(CommonRxPortTestCases, testRxPort)
{
    cout << __func__ << " - START" <<  endl;
    testRxPort();

    cout << __func__ << " - END" <<  endl;
}

TEST_F(CommonRxPortTestCases, TestErrorPaths)
{
    cout << __func__ << " - START" <<  endl;


    cout << __func__ << " - END" <<  endl;
}

TEST_F(CommonRxPortTestCases, TestTidyUp)
{
    cout << __func__ << " - START" <<  endl;


    cout << __func__ << " - END" <<  endl;
}

TEST_F(CommonRxPortTestCases, TestAdcMute)
{
    cout << __func__ << " - START" <<  endl;

    CommonRxPort* port = new TestRxPort( 0, "rxPortAdcMuteTest");

    ASSERT_TRUE(port != 0);

    port->initialise();

    // Test the initial value, should be true.
    ASSERT_TRUE(true == port->isAdcMuted());

    port->muteAdc(false);

    // We've just set it, so it should be false
    ASSERT_TRUE(false == port->isAdcMuted());

    port->muteAdc(true);

    // We've just reset it, so it should be true
    ASSERT_TRUE(true == port->isAdcMuted());

    cout << __func__ << " - END" <<  endl;
}

TEST_F(CommonRxPortTestCases, TestRxOnOff)
{
    cout << __func__ << " - START" <<  endl;

    CommonRxPort* port = new TestRxPort( 0, "rxPortOnOffTest");

    ASSERT_TRUE(port != 0);

    port->initialise();

    // Test the initial value, should be false.
    ASSERT_TRUE(false == port->isRxOn());

    // Turn on the rx
    ASSERT_TRUE(0 == port->setRxOn());

    // Rx is now on so test the value, should be true.
    ASSERT_TRUE(true == port->isRxOn());

    // Turn off the rx
    ASSERT_TRUE(0 == port->setRxOff());

    // Rx is now off so test the value, should be false.
    ASSERT_TRUE(false == port->isRxOn());
}

} // Namespace
