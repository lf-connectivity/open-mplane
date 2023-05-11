/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierServerTestCase.cpp
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

#include "ITxPort.h"
#include "IRxPort.h"
#include "ICarrier.h"
#include "CarrierUtils.hpp"
#include "CommonCarrier.h"
#include "CommonCarrierTestCase.h"
#include "CommonCarrierServer.h"
#include "CommonCarrierServerTestCase.h"
#include "CommonCarrierModel.h"

#include "IAppSettingsFactory.h"
#include "TestAppSettings.h"

using namespace std;

using namespace Mplane;

TestRadioCarrierServer::TestRadioCarrierServer():
    CommonCarrierServer( 6, 3, 4, 1, 2 )
{
    // test add carrier methods with good index
    for( unsigned index = 0; index < mMaxCarriers; index++ )
    {
        TestCarrier *carrierSetter = new TestCarrier( index, mMaxTxPaths, mMaxRxPaths );
        CPPUNIT_ASSERT( addCarrierSetter( *carrierSetter ) == true );
        TestCarrier *carrier = new TestCarrier( index, mMaxTxPaths, mMaxRxPaths );
        CPPUNIT_ASSERT( addCarrier( *carrier ) == true );
    }

    // test add carrier methods with illegal indexes
    ICarrierSetter * carrierSetter = new TestCarrier( mMaxCarriers, mMaxTxPaths, mMaxRxPaths );
    CPPUNIT_ASSERT( addCarrierSetter( *carrierSetter ) == false );
    delete carrierSetter ;

    ICarrier * carrier = new TestCarrier( mMaxCarriers, mMaxTxPaths, mMaxRxPaths );
    CPPUNIT_ASSERT( addCarrier( *carrier ) == false );
    delete carrier ;
}

TestRadioCarrierServer::~TestRadioCarrierServer()
{
}

void TestRadioCarrierServer::writeErrorMsg(char* str)
{
    setCarrierFailureStr( str );
}


/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonCarrierServerTestCase );


/*
 * Unit tests
 */
void CommonCarrierServerTestCase::unittest()
{
    std::shared_ptr<IAppSettings> appSettings(IAppSettingsFactory::getInterface());

    std::shared_ptr<TestAppSettings> testAppSettings(std::dynamic_pointer_cast<TestAppSettings>(appSettings)) ;

    testAppSettings->setDuplex(IAppSettings::DUPLEX_FDD);

    cout << "CommonCarrierServerTestCase unit test" << endl;

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;

    Frequency loFreq(2337500.0, Frequency::KHz) ;
    txPorts[0]->setFrequency(loFreq) ;
    txPorts[1]->setFrequency(loFreq) ;
    rxPorts[0]->setFrequency(loFreq) ;
    rxPorts[1]->setFrequency(loFreq) ;

    m_cbCount = 0;
    /*
     * Test the methods of the CommonBoardInformation class
     */
    TestRadioCarrierServer *rcm = new TestRadioCarrierServer();

    CPPUNIT_ASSERT( rcm->getMaxCarriers() == 6 );
    CPPUNIT_ASSERT( rcm->getMaxTxPaths() == 1 );
    CPPUNIT_ASSERT( rcm->getMaxRxPaths() == 2 );
    CPPUNIT_ASSERT( rcm->getMaxTxCarriersPerPort() == 3);
    CPPUNIT_ASSERT( rcm->getMaxRxCarriersPerPort() == 4);


    m_index = 1;

    ICarrierSetter& cs2 = rcm->getCarrierSetter( m_index );
    CPPUNIT_ASSERT( cs2.getIndex() == 1 );
    CPPUNIT_ASSERT( m_cbCount == 0);


    m_index = 0;

    ICarrierSetter& cs = rcm->getCarrierSetter( m_index );
    CPPUNIT_ASSERT( cs.getIndex() == 0 );
    CPPUNIT_ASSERT( m_cbCount == 0);


    const ICarrier& carr = rcm->getCarrier(0);
    CPPUNIT_ASSERT( m_cbCount == 0);

    // ensure the setter and the data are not the same
    CPPUNIT_ASSERT( &cs != &carr );

    CPPUNIT_ASSERT( carr.getIndex() == 0 );
    CPPUNIT_ASSERT( carr.getRxContainer(0) == 0 );
    CPPUNIT_ASSERT( carr.getRxContainer(1) == 0 );
    CPPUNIT_ASSERT( carr.getTxContainer(0) == 0);
    CPPUNIT_ASSERT( carr.getRxFrequency() == 0 );
    CPPUNIT_ASSERT( carr.getTxFrequency() == 0 );
    CPPUNIT_ASSERT( carr.getTxPower() == 0.0f );
    CPPUNIT_ASSERT( carr.getNumberRxPaths() == 2 );
    CPPUNIT_ASSERT( carr.getNumberTxPaths() == 1 );
//    CPPUNIT_ASSERT( carr.getRxIfFrequency(0) == 0 );
//    CPPUNIT_ASSERT( carr.getRxIfFrequency(1) == 0 );
//    CPPUNIT_ASSERT( carr.getTxIfFrequency(0) == 0 );
    CPPUNIT_ASSERT( carr.getSigType() == ICarrier::SIGTYPE_NONE );
    CPPUNIT_ASSERT( carr.getState() == ICarrier::STATE_DISABLE );
    CPPUNIT_ASSERT( carr.getType() == ICarrier::CARRTYPE_NONE );
    CPPUNIT_ASSERT( carr.getUplinkNoise() == 0.0f );
    CPPUNIT_ASSERT( carr.getGroupSizeUp() == 0);
    CPPUNIT_ASSERT( carr.getGroupSizeDown() == 0);

    CPPUNIT_ASSERT( carr.isConfigured() == false );
    CPPUNIT_ASSERT( CarrierUtils::isEnabled(carr) == false );
    CPPUNIT_ASSERT( carr.isTx() == false );
    CPPUNIT_ASSERT( carr.isRx() == false );

    CPPUNIT_ASSERT(cs.setRxContainer(0,1) );
    CPPUNIT_ASSERT(cs.setTxContainer(0,1) );
    CPPUNIT_ASSERT(cs.setRxFrequency(4000ULL) );
    CPPUNIT_ASSERT(cs.setTxFrequency(5000ULL) );
    CPPUNIT_ASSERT(cs.setTxPower(30) );
    CPPUNIT_ASSERT(cs.setSigType( ICarrier::SIGTYPE_CW ) );
    CPPUNIT_ASSERT(cs.setState( ICarrier::STATE_DISABLE ) );
    CPPUNIT_ASSERT(cs.setType( ICarrier::CARRTYPE_LTE10 ) );
    CPPUNIT_ASSERT(cs.setUplinkNoise( 642 ) );
    CPPUNIT_ASSERT(cs.setGroupSizeUp( 4 ) );
    CPPUNIT_ASSERT(cs.setGroupSizeDown( 4 ) );

    rcm->setCarrier( cs );

    const ICarrier& carr2 = rcm->getCarrier(0);
    CPPUNIT_ASSERT( carr2.getIndex() == 0 );
    CPPUNIT_ASSERT( carr2.getIndex() == cs.getIndex());
    CPPUNIT_ASSERT( carr2.getRxContainer(0) == cs.getRxContainer(0));
    CPPUNIT_ASSERT( carr2.getRxContainer(0) == 1 );
    CPPUNIT_ASSERT( carr2.getRxContainer(1) == cs.getRxContainer(1));
    CPPUNIT_ASSERT( carr2.getRxContainer(1) == 0 );
    CPPUNIT_ASSERT( carr2.getTxContainer(0) == cs.getTxContainer(0));
    CPPUNIT_ASSERT( carr2.getTxContainer(0) == 1);
    CPPUNIT_ASSERT( carr2.getRxFrequency() == cs.getRxFrequency());
    CPPUNIT_ASSERT( carr2.getRxFrequency() == 4000 );
    CPPUNIT_ASSERT( carr2.getTxFrequency() == cs.getTxFrequency());
    CPPUNIT_ASSERT( carr2.getTxFrequency() == 5000 );
    CPPUNIT_ASSERT( carr2.getTxPower() == cs.getTxPower());
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 30.0, carr2.getTxPower().get(), 0.01 );
    CPPUNIT_ASSERT( carr2.getSigType() == ICarrier::SIGTYPE_CW );
    CPPUNIT_ASSERT( carr2.getState() == ICarrier::STATE_DISABLE );
    CPPUNIT_ASSERT( carr2.getType() == ICarrier::CARRTYPE_LTE10 );

    CPPUNIT_ASSERT( carr2.getUplinkNoise() == 642 );
    CPPUNIT_ASSERT( carr2.getGroupSizeUp() == 4);
    CPPUNIT_ASSERT( carr2.getGroupSizeDown() == 4);


    CPPUNIT_ASSERT( carr2.isConfigured() == true );
    CPPUNIT_ASSERT( CarrierUtils::isEnabled(carr2) == false );
    CPPUNIT_ASSERT( carr2.isTx() == true );
    CPPUNIT_ASSERT( carr2.isRx() == true );



//    CPPUNIT_ASSERT(rcm->getTxLowestCarrierFreq(0) == 5000);
//    CPPUNIT_ASSERT(rcm->getRxLowestCarrierFreq(0) == 4000);
//    CPPUNIT_ASSERT(rcm->getRxLowestCarrierFreq(1) == 0);


    CPPUNIT_ASSERT( m_cbCount == 0);

    rcm->registerObserver( *this );

    cs.setRxContainer(1,5);
    cs.setTxContainer(1,5);
    cs.setRxFrequency(2350000000ULL);
    cs.setTxFrequency(2340000000ULL);
    cs.setTxPower(30);
    cs.setState( ICarrier::STATE_ENABLE );
    cs.setSigType( ICarrier::SIGTYPE_NONE );
    cs.setGroupSizeUp( 3 );
    cs.setGroupSizeDown( 3 );


    rcm->setCarrier( cs );

    rcm->show(std::cerr) ;

//    CPPUNIT_ASSERT(rcm->getTxLowestCarrierFreq(0) == 2500);
//    CPPUNIT_ASSERT(rcm->getRxLowestCarrierFreq(0) == 1500);
//    CPPUNIT_ASSERT(rcm->getRxLowestCarrierFreq(1) == 1500);

    CPPUNIT_ASSERT( m_cbCount == 1);

    CPPUNIT_ASSERT( m_cbCarrier->getIndex() == 0 );
    CPPUNIT_ASSERT( m_cbCarrier->getIndex() == cs.getIndex());
    CPPUNIT_ASSERT( m_cbCarrier->getRxContainer(0) == cs.getRxContainer(0));
    CPPUNIT_ASSERT( m_cbCarrier->getRxContainer(0) == 1 );
    CPPUNIT_ASSERT( m_cbCarrier->getRxContainer(1) == cs.getRxContainer(1));
    CPPUNIT_ASSERT( m_cbCarrier->getRxContainer(1) == 5 );
    CPPUNIT_ASSERT( m_cbCarrier->getTxContainer(0) == cs.getTxContainer(0));
    CPPUNIT_ASSERT( m_cbCarrier->getTxContainer(0) == 1);
    CPPUNIT_ASSERT( m_cbCarrier->getRxFrequency() == cs.getRxFrequency());
    CPPUNIT_ASSERT( m_cbCarrier->getRxFrequency() == 2350000000U );
    CPPUNIT_ASSERT( m_cbCarrier->getTxFrequency() == cs.getTxFrequency());
    CPPUNIT_ASSERT( m_cbCarrier->getTxFrequency() == 2340000000U );
    CPPUNIT_ASSERT( m_cbCarrier->getSigType() == ICarrier::SIGTYPE_NONE );
    CPPUNIT_ASSERT( m_cbCarrier->getState() == ICarrier::STATE_ENABLE );
    CPPUNIT_ASSERT( m_cbCarrier->getGroupSizeUp() == 3);
    CPPUNIT_ASSERT( m_cbCarrier->getGroupSizeDown() == 3);

    CPPUNIT_ASSERT(cs.setTxContainer(0,0) );
    rcm->setCarrier( cs );


    m_index = 1;

    ICarrierSetter& cs3 = rcm->getCarrierSetter( m_index );



    CPPUNIT_ASSERT( cs3.getIndex() == 1 );
    CPPUNIT_ASSERT( m_cbCount == 1);

    CPPUNIT_ASSERT( cs3.setRxContainer(0,6) == true );
    CPPUNIT_ASSERT( cs3.setTxContainer(0,7) == true );
    cs3.setRxFrequency(2332000000ULL);
    cs3.setTxFrequency(2331000000ULL);
    cs3.setTxPower(200);

    // check invalid container returns false.
    CPPUNIT_ASSERT( cs3.setRxContainer(5,6) == false );
    CPPUNIT_ASSERT( cs3.setTxContainer(3,7) == false );


    rcm->setCarrier( cs3 );

////    CPPUNIT_ASSERT(rcm->getTxLowestCarrierFreq(0) == 2000);
////    CPPUNIT_ASSERT(rcm->getRxLowestCarrierFreq(0) == 1000);
////    CPPUNIT_ASSERT(rcm->getRxLowestCarrierFreq(1) == 1500);
//
//    CPPUNIT_ASSERT( m_cbCount == 2);
//    CPPUNIT_ASSERT( m_cbCarrier->getIndex() == 1 );
//    CPPUNIT_ASSERT( m_cbCarrier->getIndex() == cs3.getIndex());
//    CPPUNIT_ASSERT( m_cbCarrier->getRxContainer(0) == cs3.getRxContainer(0));
//    CPPUNIT_ASSERT( m_cbCarrier->getRxContainer(0) == 6 );
//    CPPUNIT_ASSERT( m_cbCarrier->getRxContainer(1) == cs3.getRxContainer(1));
//    CPPUNIT_ASSERT( m_cbCarrier->getRxContainer(1) == 0 );
//    CPPUNIT_ASSERT( m_cbCarrier->getTxContainer(0) == cs3.getTxContainer(0));
//    CPPUNIT_ASSERT( m_cbCarrier->getTxContainer(0) == 7);
//    CPPUNIT_ASSERT( m_cbCarrier->getRxFrequency() == cs3.getRxFrequency());
//    CPPUNIT_ASSERT( m_cbCarrier->getRxFrequency() == 2332000000U );
//    CPPUNIT_ASSERT( m_cbCarrier->getTxFrequency() == cs3.getTxFrequency());
//    CPPUNIT_ASSERT( m_cbCarrier->getTxFrequency() == 2331000000U );
//
//    // test out of bounds container path returns 0
//    CPPUNIT_ASSERT( m_cbCarrier->getRxContainer(3) == 0 );
//    CPPUNIT_ASSERT( m_cbCarrier->getTxContainer(2) == 0 );
//
//
//    CPPUNIT_ASSERT( carr2.isConfigured() == true );
//    CPPUNIT_ASSERT( CarrierUtils::isEnabled(carr2) == true );
//    CPPUNIT_ASSERT( carr2.isTx() == true );
//    CPPUNIT_ASSERT( carr2.isRx() == true );
//
//    CPPUNIT_ASSERT(cs3.setTxContainer(0,0) );
//    rcm->setCarrier( cs3 );


    rcm->writeErrorMsg((char*)"This is a error message");

    CPPUNIT_ASSERT( rcm->getSetCarrierFailureStr().compare("This is a error message") == 0 );

    rcm->writeErrorMsg((char*)" 123456789 123456789 123456789 123456789 123456789"
                       "123456789 123456789 123456789 123456789 123456789 "
                       "123456789 123456789 123456789 123456789");

    CPPUNIT_ASSERT( rcm->getSetCarrierFailureStr().compare(
            " 123456789 123456789 123456789 123456789 123456789"
                       "123456789 123456789 123456789 123456789 123456789 "
                       "123456789 123456789 123456789 123456789" ) == 0 );


    delete rcm;
}

char const * const CommonCarrierServerTestCase::getObjName()
{
    return "TestCommonCarrier";
}

bool CommonCarrierServerTestCase::notify( ICarrierServer const &carrierMgr )
{


    m_cbCount++;
    m_cbCarrier = (ICarrier*) &carrierMgr.getCarrier( carrierMgr.lastCarrierIndexModified() );
    return true;
}

const unsigned CommonCarrierServerTestCase::getIndex() const
{
    return m_index;
}
