/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierTestCase.cpp
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

#include "ICarrier.h"
#include "CarrierUtils.hpp"
#include "CommonCarrierTestCase.h"

using namespace std;

using namespace Mplane;

TestCarrier::TestCarrier(int index, int maxTxPaths, int maxRxPaths ):
    CommonCarrier( index, maxTxPaths, maxRxPaths )
{
}

TestCarrier::~TestCarrier()
{

}



/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonCarrierTestCase );


/*
 * Unit tests
 */
void CommonCarrierTestCase::unittest()
{
    cout << "CommonCarrierTestCase unit test" << endl;

    TestCarrier *testCarrier  = new TestCarrier( 1, 2, 4);
    ICarrierSetter &carrierSetter = *testCarrier;
    ICarrier &carrier = *testCarrier;

    Frequency rxFreq = 1710000000ULL;
    Frequency txFreq = 2109000000ULL;


    CPPUNIT_ASSERT(carrierSetter.setGroupSizeDown(4) == true );
    CPPUNIT_ASSERT(carrierSetter.setGroupSizeUp(8) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(0,1) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(1,5) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(2,10) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(3,15) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(4,20) == false );
    CPPUNIT_ASSERT(carrierSetter.setTxContainer(0,1) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxContainer(1,5) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxContainer(2,10) == false );
    CPPUNIT_ASSERT(carrierSetter.setRxFrequency( rxFreq ) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxFrequency( txFreq ) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxPower( 40.0 ) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxFibre(0,0) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxFibre(1,1) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxFibre(2,0) == false );
    CPPUNIT_ASSERT(carrierSetter.setRxFibre(0,0) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxFibre(1,1) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxFibre(2,0) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxFibre(3,1) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxFibre(4,0) == false );
    CPPUNIT_ASSERT(carrierSetter.setTxScaling(-18.0) == true );


    CPPUNIT_ASSERT(carrier.getGroupSizeDown() == 4 );
    CPPUNIT_ASSERT(carrier.getGroupSizeUp() == 8 );
    CPPUNIT_ASSERT(carrier.getIndex() == 1 );
    CPPUNIT_ASSERT(carrier.getNumberRxPaths() == 4 );
    CPPUNIT_ASSERT(carrier.getNumberTxPaths() == 2 );
    CPPUNIT_ASSERT(carrier.getRxContainer(0) == 1 );
    CPPUNIT_ASSERT(carrier.getRxContainer(1) == 5 );
    CPPUNIT_ASSERT(carrier.getRxContainer(2) == 10 );
    CPPUNIT_ASSERT(carrier.getRxContainer(3) == 15 );
    CPPUNIT_ASSERT(carrier.getRxContainer(4) == 0 );    // invalid index return 0
    CPPUNIT_ASSERT(carrier.getTxContainer(0) == 1 );
    CPPUNIT_ASSERT(carrier.getTxContainer(1) == 5 );
    CPPUNIT_ASSERT(carrier.getTxContainer(2) == 0 );  // invalid index returns 0
    CPPUNIT_ASSERT(carrier.getRxFrequency() == rxFreq );
    CPPUNIT_ASSERT(carrier.getTxFrequency() == txFreq );
    CPPUNIT_ASSERT_DOUBLES_EQUAL(40.0, carrier.getTxPower().get(), 0.01 );
    CPPUNIT_ASSERT(carrier.getRxFibre(0) == 0 );
    CPPUNIT_ASSERT(carrier.getRxFibre(1) == 1 );
    CPPUNIT_ASSERT(carrier.getRxFibre(2) == 0 );
    CPPUNIT_ASSERT(carrier.getRxFibre(3) == 1 );
    CPPUNIT_ASSERT(carrier.getRxFibre(4) == 0 );    // invalid index return 0
    CPPUNIT_ASSERT(carrier.getTxFibre(0) == 0 );
    CPPUNIT_ASSERT(carrier.getTxFibre(1) == 1 );
    CPPUNIT_ASSERT(carrier.getTxFibre(2) == 0 );  // invalid index returns 0
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-18.0, carrier.getTxScaling().get(), 0.01 );

    CPPUNIT_ASSERT(carrier.isRx() == true);
    CPPUNIT_ASSERT(carrier.isTx() == true);
    CPPUNIT_ASSERT(carrier.isConfigured() == true);
    CPPUNIT_ASSERT(CarrierUtils::isEnabled(carrier) == false);

    //  or power setting
    CPPUNIT_ASSERT(carrierSetter.setTxPower( 50 ) == true );
    CPPUNIT_ASSERT(carrierSetter.setUplinkNoise(64.2) == true );
    CPPUNIT_ASSERT_EQUAL(50, carrier.getTxPower().getInt() );
    CPPUNIT_ASSERT_DOUBLES_EQUAL(50.0, carrier.getTxPower().get(), 0.01 );
    CPPUNIT_ASSERT_EQUAL(64, carrier.getUplinkNoise().getInt() );
    CPPUNIT_ASSERT_DOUBLES_EQUAL(64.2, carrier.getUplinkNoise().get(), 0.01 );

    CPPUNIT_ASSERT(carrierSetter.setTxPower( 61.2 ) == true );
    CPPUNIT_ASSERT(carrierSetter.setUplinkNoise(98.7) == true );
    CPPUNIT_ASSERT_EQUAL(61, carrier.getTxPower().getInt() );
    CPPUNIT_ASSERT_DOUBLES_EQUAL(61.2, carrier.getTxPower().get(), 0.01 );
    CPPUNIT_ASSERT_EQUAL(99, carrier.getUplinkNoise().getInt() );
    CPPUNIT_ASSERT_DOUBLES_EQUAL(98.7, carrier.getUplinkNoise().get(), 0.01 );

    delete testCarrier ;
}

/*
 * change monitoring test
 */
void CommonCarrierTestCase::change_test()
{
    cout << "CommonCarrierTestCase change test" << endl;

    TestCarrier *testCarrier  = new TestCarrier( 1, 2, 4);
    ICarrierSetter &carrierSetter = *testCarrier;

    Frequency rxFreq = 1710000000ULL;
    Frequency txFreq = 2109000000ULL;

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;

    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter) == false) ;


    CPPUNIT_ASSERT(carrierSetter.setGroupSizeDown(4) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setGroupSizeUp(8) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setRxContainer(0,1) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setRxContainer(1,5) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setRxContainer(2,10) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setRxContainer(3,15) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setRxContainer(4,20) == false );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setTxContainer(0,1) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setTxContainer(1,5) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setTxContainer(2,10) == false );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setRxFrequency( rxFreq ) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setTxFrequency( txFreq ) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setTxPower( 400 ) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;

    CPPUNIT_ASSERT(carrierSetter.setSigType(ICarrier::SIGTYPE_TX) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setType(ICarrier::CARRTYPE_LTE5) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;

    CPPUNIT_ASSERT(carrierSetter.setUplinkNoise(64.2) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;

    CPPUNIT_ASSERT(carrierSetter.setState(ICarrier::STATE_ENABLE) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;

    CPPUNIT_ASSERT(carrierSetter.setRxFibre(0, 2) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;


    CPPUNIT_ASSERT(carrierSetter.setTxScaling(-19.5) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == true) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter)) ;



    //-----------------------------------------------------------------------------------------
    // clear out changes
    carrierSetter.applyChanges() ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter) == false) ;


    // should cause no change
    CPPUNIT_ASSERT(carrierSetter.setGroupSizeDown(4) == true );
    CPPUNIT_ASSERT(carrierSetter.setGroupSizeUp(8) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(0,1) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(1,5) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(2,10) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(3,15) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(4,20) == false );
    CPPUNIT_ASSERT(carrierSetter.setTxContainer(0,1) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxContainer(1,5) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxContainer(2,10) == false );
    CPPUNIT_ASSERT(carrierSetter.setRxFrequency( rxFreq ) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxFrequency( txFreq ) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxPower( 400 ) == true );
    CPPUNIT_ASSERT(carrierSetter.setSigType(ICarrier::SIGTYPE_TX) == true );
    CPPUNIT_ASSERT(carrierSetter.setType(ICarrier::CARRTYPE_LTE5) == true );
    CPPUNIT_ASSERT(carrierSetter.setUplinkNoise(64.2) == true );
    CPPUNIT_ASSERT(carrierSetter.setState(ICarrier::STATE_ENABLE) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxFibre(0, 2) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxScaling(-19.5) == true );

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(4) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(2) == false) ; // invalid index always return false
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter) == false) ;


    delete testCarrier ;
}


void CommonCarrierTestCase::path_change_test()
{
    cout << "CommonCarrierTestCase path change test" << endl;

    TestCarrier *testCarrier  = new TestCarrier( 1, 2, 4);
    ICarrierSetter &carrierSetter = *testCarrier;
//    ICarrier &carrier = *testCarrier;

    Frequency rxFreq = 1720000000ULL;
    Frequency txFreq = 2119000000ULL;


    CPPUNIT_ASSERT(carrierSetter.setGroupSizeDown(2) == true );
    CPPUNIT_ASSERT(carrierSetter.setGroupSizeUp(2) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(0,3) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(1,5) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(2,7) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(3,1) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxContainer(0,5) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxContainer(1,1) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxFrequency( rxFreq ) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxFrequency( txFreq ) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxPower( 50.0 ) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxFibre(0,10) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxFibre(1,11) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxFibre(0,10) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxFibre(1,11) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxFibre(2,12) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxFibre(3,13) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxScaling(-19.0) == true );
    CPPUNIT_ASSERT(carrierSetter.setSigType(ICarrier::SIGTYPE_CW) == true );
    CPPUNIT_ASSERT(carrierSetter.setType(ICarrier::CARRTYPE_LTE10) == true );
    CPPUNIT_ASSERT(carrierSetter.setUplinkNoise(65.2) == true );
    CPPUNIT_ASSERT(carrierSetter.setState(ICarrier::STATE_ENABLE) == true );


    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == true) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter) == true) ;

    // clear out changes
    carrierSetter.applyChanges() ;

    CPPUNIT_ASSERT(carrierSetter.getGroupSizeDownChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getGroupSizeUpChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxContainerChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxContainerChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFrequencyChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPowerChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getSigTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTypeChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getUplinkNoiseChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getStateChanged() == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxFibreChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxFibreChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxScalingChanged() == false) ;
    CPPUNIT_ASSERT(CarrierUtils::isChanged(carrierSetter) == false) ;


    // Change RX antenna settings
//    CPPUNIT_ASSERT(carrierSetter.setRxContainer(0,3) == true );
//    CPPUNIT_ASSERT(carrierSetter.setRxContainer(1,5) == true );
//    CPPUNIT_ASSERT(carrierSetter.setRxContainer(2,7) == true );
//    CPPUNIT_ASSERT(carrierSetter.setRxContainer(3,1) == true );
//    CPPUNIT_ASSERT(carrierSetter.setTxContainer(0,5) == true );
//    CPPUNIT_ASSERT(carrierSetter.setTxContainer(1,1) == true );

    CPPUNIT_ASSERT(carrierSetter.setRxContainer(0,6) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxContainer(0,10) == true );
    CPPUNIT_ASSERT(carrierSetter.setTxContainer(1,10) == true );

    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPathChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPathChanged(1) == false) ;

    CPPUNIT_ASSERT(carrierSetter.setRxContainer(0,0) == true );

    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(1) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(2) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPathChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPathChanged(1) == false) ;

    CPPUNIT_ASSERT(carrierSetter.setRxContainer(1,0) == true );
    CPPUNIT_ASSERT(carrierSetter.setRxContainer(2,0) == true );

    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPathChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPathChanged(1) == false) ;

    CPPUNIT_ASSERT(carrierSetter.setTxContainer(1,0) == true );

    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(0) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(1) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(2) == true) ;
    CPPUNIT_ASSERT(carrierSetter.getRxPathChanged(3) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPathChanged(0) == false) ;
    CPPUNIT_ASSERT(carrierSetter.getTxPathChanged(1) == true) ;

    delete testCarrier ;
}
