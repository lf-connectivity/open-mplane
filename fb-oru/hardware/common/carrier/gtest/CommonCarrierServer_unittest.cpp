/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierServer_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

#include "Task.h"
#include "FrequencyUtils.hpp"
#include "IFrequencyConst.h"
#include "ICarrier.h"
#include "ITxPort.h"
#include "IRxPort.h"
#include "ILoggable.h"

#include "CommonCarrier.h"
#include "CarrierUtils.hpp"
#include "CommonCarrierHardware.h"
#include "CommonCarrierModel.h"

#include "TestCarrier.h"
#include "CommonCarrierServer_fixture.h"

#include "IAppSettingsFactory.h"
#include "TestAppSettings.h"



using namespace std;

using namespace Mplane;

//=============================================================================================================
// TX ON/OFF MONITOR
//=============================================================================================================

class TxOnOffMonitor :
		public Observer<ITxOn, const ITxEventData&>,
		public Observer<ITxOff, const ITxEventData&>,
		public Observer<ITxChange, const ITxEventData&>
{
public:
	void clear()
	{
		std::fill(mOnOff.begin(), mOnOff.end(), false) ;
		std::fill(mTxOn.begin(), mTxOn.end(), false) ;
		std::fill(mTxOff.begin(), mTxOff.end(), false) ;
		std::fill(mTxChange.begin(), mTxChange.end(), false) ;
	}

	TxOnOffMonitor() :
		mOnOff(MAX_TXPATHS, false),
		mTxOn(MAX_TXPATHS, false),
		mTxOff(MAX_TXPATHS, false),
		mTxChange(MAX_TXPATHS, false)
	{
	}
	virtual ~TxOnOffMonitor() {}

	void update(ITxOn& subject) {}
	void update(ITxOn& subject, const ITxEventData& txOnOff) {
		std::cerr << "TX" << txOnOff.getPort() << " ON" << std::endl ;
		mOnOff[txOnOff.getPort()] = true ;
		mTxOn[txOnOff.getPort()] = true ;
	}

	void update(ITxOff& subject) {}
	void update(ITxOff& subject, const ITxEventData& txOnOff) {
		std::cerr << "TX" << txOnOff.getPort() << " OFF" << std::endl ;
		mOnOff[txOnOff.getPort()] = false ;
		mTxOff[txOnOff.getPort()] = true ;
	}

	void update(ITxChange& subject) {}
	void update(ITxChange& subject, const ITxEventData& txOnOff) {
		std::cerr << "TX" << txOnOff.getPort() << " CHANGE" << std::endl ;
		mTxChange[txOnOff.getPort()] = true ;
	}

	const char *name() const {
		return "TxOnOffMonitor" ;
	}

	std::vector<bool> mOnOff ;
	std::vector<bool> mTxOn ;
	std::vector<bool> mTxOff ;
	std::vector<bool> mTxChange ;
};

//=============================================================================================================
// TX POWER MONITOR
//=============================================================================================================

class TxPowerMonitor : public Observer<ITxPower, const ITxEventData&> {
public:
	TxPowerMonitor() :
		mPower(MAX_TXPATHS, false)
	{
	}
	virtual ~TxPowerMonitor() {}

	void update(ITxPower& subject) {}
	void update(ITxPower& subject, const ITxEventData& txPower) {
		std::cerr << "TX" << txPower.getPort() << " POWER" << std::endl ;
		mPower[txPower.getPort()] = true ;
	}

	const char *name() const {
		return "TxPowerMonitor" ;
	}

	void clear() {
		for (auto entry : mPower)
		{
			entry = false ;
		}
	}

	std::vector<bool> mPower ;
};

//=============================================================================================================
// TESTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, strFunctions)
{
	// Not strictly CarrierServer, but seems a reasonable place to put it

	EXPECT_EQ("NONE", ICarrier::typeToStr(ICarrier::CARRTYPE_NONE)) ;
	EXPECT_EQ("LTE1_4", ICarrier::typeToStr(ICarrier::CARRTYPE_LTE1_4)) ;
	EXPECT_EQ("LTE3", ICarrier::typeToStr(ICarrier::CARRTYPE_LTE3)) ;
	EXPECT_EQ("LTE5", ICarrier::typeToStr(ICarrier::CARRTYPE_LTE5)) ;
	EXPECT_EQ("LTE10", ICarrier::typeToStr(ICarrier::CARRTYPE_LTE10)) ;
	EXPECT_EQ("LTE15", ICarrier::typeToStr(ICarrier::CARRTYPE_LTE15)) ;
	EXPECT_EQ("LTE20", ICarrier::typeToStr(ICarrier::CARRTYPE_LTE20)) ;
	EXPECT_EQ("WCDMA", ICarrier::typeToStr(ICarrier::CARRTYPE_WCDMA)) ;
	EXPECT_EQ("PIM1_4", ICarrier::typeToStr(ICarrier::CARRTYPE_PIM1_4)) ;
	EXPECT_EQ("PIM3", ICarrier::typeToStr(ICarrier::CARRTYPE_PIM3)) ;
	EXPECT_EQ("PIM5", ICarrier::typeToStr(ICarrier::CARRTYPE_PIM5)) ;
	EXPECT_EQ("PIM10", ICarrier::typeToStr(ICarrier::CARRTYPE_PIM10)) ;
	EXPECT_EQ("PIM15", ICarrier::typeToStr(ICarrier::CARRTYPE_PIM15)) ;
	EXPECT_EQ("PIM20", ICarrier::typeToStr(ICarrier::CARRTYPE_PIM20)) ;
	EXPECT_EQ("IBW153_6", ICarrier::typeToStr(ICarrier::CARRTYPE_IBW153_6)) ;
	EXPECT_EQ("IBW122_88", ICarrier::typeToStr(ICarrier::CARRTYPE_IBW122_88)) ;
	EXPECT_EQ("5GNR5", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR5)) ;
	EXPECT_EQ("5GNR10", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR10)) ;
	EXPECT_EQ("5GNR15", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR15)) ;
	EXPECT_EQ("5GNR20", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR20)) ;
	EXPECT_EQ("5GNR25", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR25)) ;
	EXPECT_EQ("5GNR30", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR30)) ;
	EXPECT_EQ("5GNR40", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR40)) ;
	EXPECT_EQ("5GNR50", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR50)) ;
	EXPECT_EQ("5GNR60", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR60)) ;
	EXPECT_EQ("5GNR70", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR70)) ;
	EXPECT_EQ("5GNR80", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR80)) ;
	EXPECT_EQ("5GNR90", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR90)) ;
	EXPECT_EQ("5GNR100", ICarrier::typeToStr(ICarrier::CARRTYPE_5GNR100)) ;

	EXPECT_EQ("NORMAL", ICarrier::prefixLenToStr(ICarrier::PREFIX_LENGTH_NORMAL)) ;
	EXPECT_EQ("EXTENDED", ICarrier::prefixLenToStr(ICarrier::PREFIX_LENGTH_EXTENDED)) ;
	EXPECT_EQ("NONE", ICarrier::prefixLenToStr(ICarrier::PREFIX_NONE)) ;

	EXPECT_EQ("NONE", ICarrier::scsToStr(ICarrier::SCS_NONE)) ;
	EXPECT_EQ("1.25KHZ", ICarrier::scsToStr(ICarrier::SCS_1kHz25)) ;
	EXPECT_EQ("3.75KHZ", ICarrier::scsToStr(ICarrier::SCS_3kHz75)) ;
	EXPECT_EQ("5KHZ", ICarrier::scsToStr(ICarrier::SCS_5kHz)) ;
	EXPECT_EQ("7.25KHZ", ICarrier::scsToStr(ICarrier::SCS_7kHz5)) ;
	EXPECT_EQ("15KHZ", ICarrier::scsToStr(ICarrier::SCS_15kHz)) ;
	EXPECT_EQ("30KHZ", ICarrier::scsToStr(ICarrier::SCS_30kHz)) ;
	EXPECT_EQ("60KHZ", ICarrier::scsToStr(ICarrier::SCS_60kHz)) ;
	EXPECT_EQ("120KHZ", ICarrier::scsToStr(ICarrier::SCS_120kHz)) ;
	EXPECT_EQ("240KHZ", ICarrier::scsToStr(ICarrier::SCS_240kHz)) ;

	EXPECT_EQ("NONE", ICarrier::fftsizeToStr(ICarrier::FFT_NONE)) ;
	EXPECT_EQ("256", ICarrier::fftsizeToStr(ICarrier::FFT_256)) ;
	EXPECT_EQ("512", ICarrier::fftsizeToStr(ICarrier::FFT_512)) ;
	EXPECT_EQ("1024", ICarrier::fftsizeToStr(ICarrier::FFT_1024)) ;
	EXPECT_EQ("1536", ICarrier::fftsizeToStr(ICarrier::FFT_1536)) ;
	EXPECT_EQ("2048", ICarrier::fftsizeToStr(ICarrier::FFT_2048)) ;
	EXPECT_EQ("4096", ICarrier::fftsizeToStr(ICarrier::FFT_4096)) ;


	EXPECT_EQ("LTE", ICarrier::modeToStr(ICarrier::MODE_LTE)) ;
	EXPECT_EQ("5GNR", ICarrier::modeToStr(ICarrier::MODE_5GNR)) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, serverValues)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    EXPECT_EQ( 4u, carrierServer->getMaxCarriers() );
    EXPECT_EQ( 2u, carrierServer->getMaxTxPaths() );
    EXPECT_EQ( 2u, carrierServer->getMaxRxPaths() );
    EXPECT_EQ( 2u, carrierServer->getMaxTxCarriersPerPort() );
    EXPECT_EQ( 2u, carrierServer->getMaxRxCarriersPerPort() );

    std::shared_ptr<TestRadioCarrierServer> testCarrierServer = std::shared_ptr<TestRadioCarrierServer>( new TestRadioCarrierServer ) ;

    EXPECT_EQ( 4u, testCarrierServer->getMaxCarriers() );
    EXPECT_EQ( 2u, testCarrierServer->getMaxTxPaths() );
    EXPECT_EQ( 2u, testCarrierServer->getMaxRxPaths() );
    EXPECT_EQ( 2u, testCarrierServer->getMaxTxCarriersPerPort() );
    EXPECT_EQ( 2u, testCarrierServer->getMaxRxCarriersPerPort() );

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, csIndex)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    mSharedServer->m_index = 1;
    ICarrierSetter& cs2 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    EXPECT_EQ( 1u, cs2.getIndex() );
    EXPECT_EQ( 0u, mSharedServer->m_cbCount );

    mSharedServer->m_index = 0;

    ICarrierSetter& cs = carrierServer->getCarrierSetter( mSharedServer->m_index );
    EXPECT_EQ( 0u, cs.getIndex() );
    EXPECT_EQ( 0u, mSharedServer->m_cbCount );


    const ICarrier& carr = carrierServer->getCarrier(0);
    EXPECT_EQ( 0u, mSharedServer->m_cbCount );

    // ensure the setter and the data are not the same
    EXPECT_NE( &cs, &carr );

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, setCarrier)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    mSharedServer->m_index = 0;

    ICarrierSetter& cs = carrierServer->getCarrierSetter( mSharedServer->m_index );

// Can't check this stuff below - relies on state after previous tests!
//
//    const ICarrier& carr = carrierServer->getCarrier(0);
//    EXPECT_TRUE( carr.getIndex() == 0 );
//    EXPECT_TRUE( carr.getRxContainer(0) == 0 );
//    EXPECT_TRUE( carr.getRxContainer(1) == 0 );
//    EXPECT_TRUE( carr.getTxContainer(0) == 0);
//    EXPECT_TRUE( carr.getRxFrequency() == 0 );
//    EXPECT_TRUE( carr.getTxFrequency() == 0 );
//    EXPECT_TRUE( carr.getTxPower() == 0.0f );
//    EXPECT_TRUE( carr.getNumberRxPaths() == 2 );
//    EXPECT_TRUE( carr.getNumberTxPaths() == 2 );
//    EXPECT_TRUE( carr.getRxIfFrequency(0) == 0 );
//    EXPECT_TRUE( carr.getRxIfFrequency(1) == 0 );
//    EXPECT_TRUE( carr.getTxIfFrequency(0) == 0 );
//    EXPECT_TRUE( carr.getSigType() == ICarrier::SIGTYPE_NONE );
//    EXPECT_TRUE( carr.getState() == ICarrier::STATE_DISABLE );
//    EXPECT_TRUE( carr.getType() == ICarrier::CARRTYPE_NONE );
//    EXPECT_TRUE( carr.getUplinkNoise() == 0.0f );
//    EXPECT_TRUE( carr.getGroupSizeUp() == 0);
//    EXPECT_TRUE( carr.getGroupSizeDown() == 0);
//
//    EXPECT_TRUE( carr.isConfigured() == false );
//    EXPECT_TRUE( CarrierUtils::isEnabled(carr) == false );
//    EXPECT_TRUE( carr.isTx() == false );
//    EXPECT_TRUE( carr.isRx() == false );

    EXPECT_TRUE(cs.setRxContainer(0,1) );
    EXPECT_TRUE(cs.setTxContainer(0,1) );
    EXPECT_TRUE(cs.setRxFrequency(2210000000ULL) );
    EXPECT_TRUE(cs.setTxFrequency(2230000000ULL) );
    EXPECT_TRUE(cs.setTxPower(30) );
    EXPECT_TRUE(cs.setSigType( ICarrier::SIGTYPE_CW ) );
    EXPECT_TRUE(cs.setState( ICarrier::STATE_DISABLE ) );
    EXPECT_TRUE(cs.setType( ICarrier::CARRTYPE_LTE10 ) );
    EXPECT_TRUE(cs.setUplinkNoise( 642 ) );
    EXPECT_TRUE(cs.setGroupSizeUp( 4 ) );
    EXPECT_TRUE(cs.setGroupSizeDown( 4 ) );

    EXPECT_TRUE( carrierServer->setCarrier( cs ) );

    const ICarrier& carr2 = carrierServer->getCarrier(0);
    EXPECT_TRUE( carr2.getIndex() == 0 );
    EXPECT_TRUE( carr2.getIndex() == cs.getIndex());
    EXPECT_TRUE( carr2.getRxContainer(0) == cs.getRxContainer(0));
    EXPECT_TRUE( carr2.getRxContainer(0) == 1 );
    EXPECT_TRUE( carr2.getRxContainer(1) == cs.getRxContainer(1));
    EXPECT_TRUE( carr2.getRxContainer(1) == 0 );
    EXPECT_TRUE( carr2.getTxContainer(0) == cs.getTxContainer(0));
    EXPECT_TRUE( carr2.getTxContainer(0) == 1);
    EXPECT_TRUE( carr2.getRxFrequency() == cs.getRxFrequency());
    EXPECT_TRUE( carr2.getRxFrequency() == 2210000000U );
    EXPECT_TRUE( carr2.getTxFrequency() == cs.getTxFrequency());
    EXPECT_TRUE( carr2.getTxFrequency() == 2230000000U );
    EXPECT_TRUE( carr2.getTxPower() == cs.getTxPower());
    EXPECT_DOUBLE_EQ( 30.0, carr2.getTxPower().get());
    EXPECT_TRUE( carr2.getSigType() == ICarrier::SIGTYPE_CW );
    EXPECT_TRUE( carr2.getState() == ICarrier::STATE_DISABLE );
    EXPECT_TRUE( carr2.getType() == ICarrier::CARRTYPE_LTE10 );

    EXPECT_TRUE( carr2.getUplinkNoise() == 642 );
    EXPECT_TRUE( carr2.getGroupSizeUp() == 4);
    EXPECT_TRUE( carr2.getGroupSizeDown() == 4);


    EXPECT_TRUE( carr2.isConfigured() == true );
    EXPECT_TRUE( CarrierUtils::isEnabled(carr2) == false );
    EXPECT_TRUE( carr2.isTx() == true );
    EXPECT_TRUE( carr2.isRx() == true );


    EXPECT_EQ( 0u, mSharedServer->m_cbCount );

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, boundsCheck)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    mSharedServer->m_index = 1;

    ICarrierSetter& cs = carrierServer->getCarrierSetter( mSharedServer->m_index );
    const ICarrier& carr = carrierServer->getCarrier(1);

    // check invalid container returns false.
    EXPECT_FALSE( cs.setRxContainer(5,6) );
    EXPECT_FALSE( cs.setTxContainer(3,7) );

    // test out of bounds container path returns 0
    EXPECT_TRUE( carr.getRxContainer(3) == 0 );
    EXPECT_TRUE( carr.getTxContainer(2) == 0 );

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, errMessage)
{
    std::shared_ptr<TestRadioCarrierServer> carrierServer = std::shared_ptr<TestRadioCarrierServer>( new TestRadioCarrierServer ) ;

    carrierServer->writeErrorMsg((char*)"This is a error message");

    EXPECT_TRUE( carrierServer->getSetCarrierFailureStr().compare("This is a error message") == 0 );

    carrierServer->writeErrorMsg((char*)" 123456789 123456789 123456789 123456789 123456789"
                       "123456789 123456789 123456789 123456789 123456789 "
                       "123456789 123456789 123456789 123456789");

    EXPECT_TRUE( carrierServer->getSetCarrierFailureStr().compare(
            " 123456789 123456789 123456789 123456789 123456789"
                       "123456789 123456789 123456789 123456789 123456789 "
                       "123456789 123456789 123456789 123456789" ) == 0 );


}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, TxPower)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();


    EXPECT_EQ(Power(0.0), carrierServer->getTxPower(0)) ;
    EXPECT_EQ(Power(0.0), carrierServer->getTxPower(1)) ;


    // Enable Carrier0 on TX0
    {
        mSharedServer->m_index = 0;
		ICarrierSetter& cs = carrierServer->getCarrierSetter( mSharedServer->m_index );
		EXPECT_TRUE(cs.setRxContainer(0,1) );
		EXPECT_TRUE(cs.setTxContainer(0,1) );
		EXPECT_TRUE(cs.setRxFrequency(2210000000ULL) );
		EXPECT_TRUE(cs.setTxFrequency(2230000000ULL) );
		EXPECT_TRUE(cs.setTxPower(10) );
		EXPECT_TRUE(cs.setSigType( ICarrier::SIGTYPE_CW ) );
		EXPECT_TRUE(cs.setState( ICarrier::STATE_ENABLE ) );
		EXPECT_TRUE(cs.setType( ICarrier::CARRTYPE_LTE10 ) );
		EXPECT_TRUE(cs.setUplinkNoise( 642 ) );
		EXPECT_TRUE(cs.setGroupSizeUp( 4 ) );
		EXPECT_TRUE(cs.setGroupSizeDown( 4 ) );
		carrierServer->setCarrier( cs );
    }

    std::stringstream ss ;
    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;

    EXPECT_EQ(Power(10.0), carrierServer->getTxPower(0)) ;
    EXPECT_EQ(Power(0.0), carrierServer->getTxPower(1)) ;

    // Enable Carrier1 on TX1
    {
        mSharedServer->m_index = 1;
		ICarrierSetter& cs = carrierServer->getCarrierSetter( mSharedServer->m_index );
		EXPECT_TRUE(cs.setRxContainer(1,1) );
		EXPECT_TRUE(cs.setTxContainer(1,1) );
		EXPECT_TRUE(cs.setRxFrequency(2210000000ULL) );
		EXPECT_TRUE(cs.setTxFrequency(2230000000ULL) );
		EXPECT_TRUE(cs.setTxPower(30.0) );
		EXPECT_TRUE(cs.setSigType( ICarrier::SIGTYPE_CW ) );
		EXPECT_TRUE(cs.setState( ICarrier::STATE_ENABLE ) );
		EXPECT_TRUE(cs.setType( ICarrier::CARRTYPE_LTE10 ) );
		EXPECT_TRUE(cs.setUplinkNoise( 642 ) );
		EXPECT_TRUE(cs.setGroupSizeUp( 4 ) );
		EXPECT_TRUE(cs.setGroupSizeDown( 4 ) );
		carrierServer->setCarrier( cs );
    }

    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;

    EXPECT_EQ(Power(10.0), carrierServer->getTxPower(0)) ;
    EXPECT_EQ(Power(30.0), carrierServer->getTxPower(1)) ;



    // Enable Carrier2 on TX0
    {
        mSharedServer->m_index = 2;
		ICarrierSetter& cs = carrierServer->getCarrierSetter( mSharedServer->m_index );
		EXPECT_TRUE(cs.setRxContainer(0,5) );
		EXPECT_TRUE(cs.setTxContainer(0,5) );
		EXPECT_TRUE(cs.setRxFrequency(2210000000ULL) );
		EXPECT_TRUE(cs.setTxFrequency(2230000000ULL) );
		EXPECT_TRUE(cs.setTxPower(20.0) );
		EXPECT_TRUE(cs.setSigType( ICarrier::SIGTYPE_CW ) );
		EXPECT_TRUE(cs.setState( ICarrier::STATE_ENABLE ) );
		EXPECT_TRUE(cs.setType( ICarrier::CARRTYPE_LTE10 ) );
		EXPECT_TRUE(cs.setUplinkNoise( 642 ) );
		EXPECT_TRUE(cs.setGroupSizeUp( 4 ) );
		EXPECT_TRUE(cs.setGroupSizeDown( 4 ) );
		carrierServer->setCarrier( cs );
    }

    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;

    EXPECT_EQ(Power(20.414), carrierServer->getTxPower(0)) ;
    EXPECT_EQ(Power(30.0), carrierServer->getTxPower(1)) ;

    // Enable Carrier3 on TX1
    {
        mSharedServer->m_index = 3;
		ICarrierSetter& cs = carrierServer->getCarrierSetter( mSharedServer->m_index );
		EXPECT_TRUE(cs.setRxContainer(1,5) );
		EXPECT_TRUE(cs.setTxContainer(1,5) );
		EXPECT_TRUE(cs.setRxFrequency(2210000000ULL) );
		EXPECT_TRUE(cs.setTxFrequency(2230000000ULL) );
		EXPECT_TRUE(cs.setTxPower(20.0) );
		EXPECT_TRUE(cs.setSigType( ICarrier::SIGTYPE_CW ) );
		EXPECT_TRUE(cs.setState( ICarrier::STATE_ENABLE ) );
		EXPECT_TRUE(cs.setType( ICarrier::CARRTYPE_LTE10 ) );
		EXPECT_TRUE(cs.setUplinkNoise( 642 ) );
		EXPECT_TRUE(cs.setGroupSizeUp( 4 ) );
		EXPECT_TRUE(cs.setGroupSizeDown( 4 ) );
		carrierServer->setCarrier( cs );
    }

    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;

    EXPECT_EQ(Power(20.414), carrierServer->getTxPower(0)) ;
    EXPECT_EQ(Power(30.414), carrierServer->getTxPower(1)) ;

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, TxOnOffMonitor)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }


    TxOnOffMonitor monitor ;
    std::dynamic_pointer_cast< Subject<ITxOn, const ITxEventData&> >(carrierServer)->attach(monitor) ;
    std::dynamic_pointer_cast< Subject<ITxOff, const ITxEventData&> >(carrierServer)->attach(monitor) ;

    mSharedServer->m_index = 0;
    ICarrierSetter& cs = carrierServer->getCarrierSetter( mSharedServer->m_index );


    EXPECT_TRUE(cs.setRxContainer(0,1) );
    EXPECT_TRUE(cs.setTxContainer(0,1) );
    EXPECT_TRUE(cs.setRxContainer(1,0) );
    EXPECT_TRUE(cs.setTxContainer(1,0) );
    EXPECT_TRUE(cs.setRxFrequency(2210000000ULL) );
    EXPECT_TRUE(cs.setTxFrequency(2230000000ULL) );
    EXPECT_TRUE(cs.setTxPower(30) );
    EXPECT_TRUE(cs.setSigType( ICarrier::SIGTYPE_CW ) );
    EXPECT_TRUE(cs.setState( ICarrier::STATE_DISABLE ) );
    EXPECT_TRUE(cs.setType( ICarrier::CARRTYPE_LTE10 ) );
    EXPECT_TRUE(cs.setUplinkNoise( 642 ) );
    EXPECT_TRUE(cs.setGroupSizeUp( 4 ) );
    EXPECT_TRUE(cs.setGroupSizeDown( 4 ) );

    EXPECT_TRUE( carrierServer->setCarrier( cs ) );

    const ICarrier& carr2 = carrierServer->getCarrier(0);
    EXPECT_TRUE( carr2.getIndex() == 0 );
    EXPECT_TRUE( carr2.getIndex() == cs.getIndex());
    EXPECT_TRUE( carr2.getRxContainer(0) == cs.getRxContainer(0));
    EXPECT_TRUE( carr2.getRxContainer(0) == 1 );
    EXPECT_TRUE( carr2.getRxContainer(1) == cs.getRxContainer(1));
    EXPECT_TRUE( carr2.getRxContainer(1) == 0 );
    EXPECT_TRUE( carr2.getTxContainer(0) == cs.getTxContainer(0));
    EXPECT_TRUE( carr2.getTxContainer(0) == 1);
    EXPECT_TRUE( carr2.getRxFrequency() == cs.getRxFrequency());
    EXPECT_TRUE( carr2.getRxFrequency() == 2210000000U );
    EXPECT_TRUE( carr2.getTxFrequency() == cs.getTxFrequency());
    EXPECT_TRUE( carr2.getTxFrequency() == 2230000000U );
    EXPECT_TRUE( carr2.getTxPower() == cs.getTxPower());
    EXPECT_DOUBLE_EQ( 30.0, carr2.getTxPower().get());
    EXPECT_TRUE( carr2.getSigType() == ICarrier::SIGTYPE_CW );
    EXPECT_TRUE( carr2.getState() == ICarrier::STATE_DISABLE );
    EXPECT_TRUE( carr2.getType() == ICarrier::CARRTYPE_LTE10 );

    EXPECT_TRUE( carr2.getUplinkNoise() == 642 );
    EXPECT_TRUE( carr2.getGroupSizeUp() == 4);
    EXPECT_TRUE( carr2.getGroupSizeDown() == 4);


    EXPECT_TRUE( carr2.isConfigured() == true );
    EXPECT_TRUE( CarrierUtils::isEnabled(carr2) == false );
    EXPECT_TRUE( carr2.isTx() == true );
    EXPECT_TRUE( carr2.isRx() == true );


    EXPECT_EQ( 0u, mSharedServer->m_cbCount );

    EXPECT_FALSE( monitor.mOnOff[0] ) ;
    EXPECT_FALSE( monitor.mOnOff[1] ) ;

    std::stringstream ss ;

    ///////////
    EXPECT_TRUE(cs.setState( ICarrier::STATE_ENABLE ) );
    EXPECT_TRUE( carrierServer->setCarrier( cs ) );

    std::cerr << "C0 enabled:" << std::endl ;
    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;

    EXPECT_TRUE( monitor.mOnOff[0] ) ;
    EXPECT_FALSE( monitor.mOnOff[1] ) ;



    ///////////
    EXPECT_TRUE(cs.setState( ICarrier::STATE_DISABLE ) );
    EXPECT_TRUE( carrierServer->setCarrier( cs ) );

    std::cerr << "C0 disabled:" << std::endl ;
    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;

    EXPECT_FALSE( monitor.mOnOff[0] ) ;
    EXPECT_FALSE( monitor.mOnOff[1] ) ;


    // Clean up
    std::dynamic_pointer_cast< Subject<ITxOn, const ITxEventData&> >(carrierServer)->detach(monitor) ;
    std::dynamic_pointer_cast< Subject<ITxOff, const ITxEventData&> >(carrierServer)->detach(monitor) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, dualCarrier)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;

    mSharedServer->m_index = 0;
    ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );
    mSharedServer->m_index = 1;
    ICarrierSetter& cs1 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    unsigned antenna = 0u ;

    Frequency c0Freq(2325000.0, Frequency::KHz) ;
    cs0.setType(ICarrier::CARRTYPE_LTE10) ;
    cs0.setTxFrequency(c0Freq) ;
    cs0.setRxFrequency(c0Freq) ;
    cs0.setTxPower( 27.0) ;
    cs0.setTxFibre(antenna, 0) ;
    cs0.setRxFibre(antenna, 0) ;
    cs0.setTxContainer(antenna, 1) ;
    cs0.setRxContainer(antenna, 1) ;
    cs0.setTxContainer(1-antenna, 5) ;
    cs0.setRxContainer(1-antenna, 5) ;
    cs0.setGroupSizeDown(4) ;
    cs0.setGroupSizeUp(4) ;
    cs0.setTxScaling(Power(-12.0)) ;
    cs0.setState(ICarrier::STATE_ENABLE) ;

    // -- Carier 0 -----------
    carrierServer->setCarrier( cs0 ) ;

    // Ensure LO frequency has NOT shifted
    Frequency lo(2337500.0, Frequency::KHz) ;
    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;


    // -- NONE -----------
    std::cerr << "Disable all carriers" << std::endl ;
    cs0.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs0 ) ;

    // Check LO frequency
    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;


    // -- Carier 0 -----------
    cs0.setState(ICarrier::STATE_ENABLE) ;
    carrierServer->setCarrier( cs0 ) ;

    // c1
    Frequency c1Freq(2350000.0, Frequency::KHz) ;
    cs1.setType(ICarrier::CARRTYPE_LTE10) ;
    cs1.setTxFrequency(c1Freq) ;
    cs1.setRxFrequency(c1Freq) ;
    cs1.setTxPower(27.0) ;
    cs1.setTxFibre(antenna, 0) ;
    cs1.setRxFibre(antenna, 0) ;
    cs1.setTxContainer(antenna, 9) ;
    cs1.setRxContainer(antenna, 9) ;
    cs1.setTxContainer(1-antenna, 13) ;
    cs1.setRxContainer(1-antenna, 13) ;
    cs1.setGroupSizeDown(4) ;
    cs1.setGroupSizeUp(4) ;
    cs1.setTxScaling(Power(-12.0)) ;
    cs1.setState(ICarrier::STATE_ENABLE) ;

    // -- Carrier 0 + Carrier 1 ---------
    carrierServer->setCarrier( cs1 ) ;

    // Ensure LO frequency has NOT shifted
//    Frequency c0c1Freq(2337500.0, Frequency::KHz) ;
    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;


    // -- Carrier 0 ----------
    cs1.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs1 ) ;

    // Ensure LO frequency has NOT shifted
    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;

    // delete C1
    carrierServer->unconfigCarrier( 1 ) ;
    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;


    cs0.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs0 ) ;

    // Ensure *NO* change
    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;


}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, freqCheck)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();
    Mplane::ILoggable::setLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE) ;

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;

    mSharedServer->m_index = 0;
    ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    unsigned antenna = 0u ;

    Frequency c0InitFreq(2355000.0, Frequency::KHz) ;
    Frequency c0TxInitFreq(2455000.0, Frequency::KHz) ;
    Frequency c0Freq(2325000.0, Frequency::KHz) ;
    Frequency c0TxFreq(2425000.0, Frequency::KHz) ;
    cs0.setType(ICarrier::CARRTYPE_LTE10) ;
    cs0.setTxFrequency(c0TxInitFreq) ;
    cs0.setRxFrequency(c0InitFreq) ;
    cs0.setTxPower( 27.0) ;
    cs0.setTxFibre(antenna, 0) ;
    cs0.setRxFibre(antenna, 0) ;
    cs0.setTxContainer(antenna, 1) ;
    cs0.setRxContainer(antenna, 1) ;
    cs0.setTxContainer(1-antenna, 5) ;
    cs0.setRxContainer(1-antenna, 5) ;
    cs0.setGroupSizeDown(4) ;
    cs0.setGroupSizeUp(4) ;
    cs0.setTxScaling(Power(-12.0)) ;
    cs0.setState(ICarrier::STATE_ENABLE) ;

    // -- Carier 0 -----------
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    cs0.setState(ICarrier::STATE_DISABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    cs0.setTxFrequency(c0TxFreq) ;
    cs0.setRxFrequency(c0Freq) ;
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;


    // Ensure LO frequency has NOT shifted
    Frequency lo(2337500.0, Frequency::KHz) ;
    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;


    std::string failureStr ;
    Frequency carrFreq ;

    std::shared_ptr<ITxFrequencyConst> txFreqConst( ITxFrequencyConstFactory::getInterface() ) ;
	Frequency txBandwidth( txFreqConst->getBandwidth() ) ;
	Frequency txMin(txFreqConst->getMinimum());
	Frequency txMax(txFreqConst->getMaximum());

	Frequency carrBandwidth(10.0, Frequency::MHz);

	// Align with min
    cs0.setState(ICarrier::STATE_DISABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

	carrFreq = txMin + (carrBandwidth/2) ;
std::cerr << "TX BW=" << txBandwidth << " : Max " << txMax << " Min " << txMin << " : Carrier Freq " << carrFreq << std::endl ;

	cs0.setState(ICarrier::STATE_ENABLE) ;
	cs0.setTxFrequency(carrFreq);

    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    failureStr = carrierServer->getSetCarrierFailureStr() ;
    EXPECT_TRUE(failureStr.empty()) ;

    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;


    // Try setting below min
    cs0.setState(ICarrier::STATE_DISABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

	carrFreq -= Frequency(1.0, Frequency::KHz) ;
std::cerr << "TX BW=" << txBandwidth << " : Max " << txMax << " Min " << txMin << " : Carrier Freq " << carrFreq << std::endl ;

	cs0.setState(ICarrier::STATE_ENABLE) ;
	cs0.setTxFrequency(carrFreq);

	// should be ok
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    failureStr = carrierServer->getSetCarrierFailureStr() ;
    std::cerr << "Expected str: " << failureStr << std::endl ;
    EXPECT_TRUE(failureStr.empty()) ;

	carrFreq += Frequency(1.0, Frequency::KHz) ;
    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;


	// Align with max
    cs0.setState(ICarrier::STATE_DISABLE) ;
//    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

	carrFreq = txMax - (carrBandwidth/2) ;
std::cerr << "TX BW=" << txBandwidth << " : Max " << txMax << " Min " << txMin << " : Carrier Freq " << carrFreq << std::endl ;

	cs0.setState(ICarrier::STATE_ENABLE) ;
	cs0.setTxFrequency(carrFreq);

    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    failureStr = carrierServer->getSetCarrierFailureStr() ;
    EXPECT_TRUE(failureStr.empty()) ;

    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;


    // Try setting above max
    cs0.setState(ICarrier::STATE_DISABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

	carrFreq += Frequency(1.0, Frequency::KHz) ;
std::cerr << "TX BW=" << txBandwidth << " : Max " << txMax << " Min " << txMin << " : Carrier Freq " << carrFreq << std::endl ;

	cs0.setState(ICarrier::STATE_ENABLE) ;
	cs0.setTxFrequency(carrFreq);

    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    failureStr = carrierServer->getSetCarrierFailureStr() ;
    std::cerr << "Expected str: " << failureStr << std::endl ;
    EXPECT_TRUE(failureStr.empty()) ;

	carrFreq -= Frequency(1.0, Frequency::KHz) ;
    EXPECT_EQ(lo, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(lo, rxPorts[1]->getFrequency()) ;





    // Tidy up
    cs0.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs0 ) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, CalMode)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();
    Mplane::ILoggable::setLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE) ;

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;

    mSharedServer->m_index = 0;
    ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    unsigned antenna = 0u ;

    cs0.setType(ICarrier::CARRTYPE_LTE10) ;
    cs0.setTxPower( 27.0) ;
    cs0.setTxFibre(antenna, 0) ;
    cs0.setRxFibre(antenna, 0) ;
    cs0.setTxContainer(antenna, 1) ;
    cs0.setRxContainer(antenna, 1) ;
    cs0.setTxContainer(1-antenna, 5) ;
    cs0.setRxContainer(1-antenna, 5) ;
    cs0.setGroupSizeDown(4) ;
    cs0.setGroupSizeUp(4) ;
    cs0.setTxScaling(Power(-12.0)) ;

    Frequency c0RxInitFreq(2330000.0, Frequency::KHz) ;
    Frequency c0TxInitFreq(2455000.0, Frequency::KHz) ;
    Frequency c0RxFreq(2325000.0, Frequency::KHz) ;
    Frequency c0TxFreq(2425000.0, Frequency::KHz) ;

    // == Enable cal mode ==

    std::cerr << "== Calibration Mode : ON ==" << std::endl ;
    carrierServer->setCalibrationMode(true) ;

    Frequency rxFreq(2335000.0, Frequency::KHz) ;
    Frequency txFreq(2435000.0, Frequency::KHz) ;
    EXPECT_EQ(ReturnType::RT_OK, txPorts[0]->setFrequency(txFreq)) ;
    EXPECT_EQ(ReturnType::RT_OK, txPorts[1]->setFrequency(txFreq)) ;
    EXPECT_EQ(ReturnType::RT_OK, rxPorts[0]->setFrequency(rxFreq)) ;
    EXPECT_EQ(ReturnType::RT_OK, rxPorts[1]->setFrequency(rxFreq)) ;


    // -- Carier 0 -----------
    cs0.setTxFrequency(c0TxInitFreq) ;
    cs0.setRxFrequency(c0RxInitFreq) ;
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    cs0.setState(ICarrier::STATE_DISABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    cs0.setTxFrequency(c0TxFreq) ;
    cs0.setRxFrequency(c0RxFreq) ;
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;


    // Ensure LO frequency has NOT shifted
    EXPECT_EQ(txFreq, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(txFreq, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(rxFreq, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(rxFreq, rxPorts[1]->getFrequency()) ;


    cs0.setState(ICarrier::STATE_DISABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;


    // == Disable cal mode ==

    std::cerr << "== Calibration Mode : OFF ==" << std::endl ;
    carrierServer->setCalibrationMode(false) ;

    // -- Carier 0 -----------
    cs0.setTxFrequency(c0TxInitFreq) ;
    cs0.setRxFrequency(c0RxInitFreq) ;
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    cs0.setState(ICarrier::STATE_DISABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
    cs0.setTxFrequency(c0TxFreq) ;
    cs0.setRxFrequency(c0RxFreq) ;
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;


    // Ensure LO frequency has NOT shifted
    EXPECT_EQ(txFreq, txPorts[0]->getFrequency()) ;
    EXPECT_EQ(txFreq, txPorts[1]->getFrequency()) ;
    EXPECT_EQ(rxFreq, rxPorts[0]->getFrequency()) ;
    EXPECT_EQ(rxFreq, rxPorts[1]->getFrequency()) ;


    // Tidy up
    cs0.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs0 ) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, PowerCheck)
{
	Loggable::setGroupLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE, "CarrierPower") ;

    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;

    mSharedServer->m_index = 0;
    ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );
    mSharedServer->m_index = 1;
    ICarrierSetter& cs1 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    unsigned antenna = 0u ;

    Frequency c0Freq(2325000.0, Frequency::KHz) ;
    cs0.setType(ICarrier::CARRTYPE_LTE10) ;
    cs0.setTxFrequency(c0Freq) ;
    cs0.setRxFrequency(c0Freq) ;
    cs0.setTxPower( 35.0) ;
    cs0.setTxFibre(antenna, 0) ;
    cs0.setRxFibre(antenna, 0) ;
    cs0.setTxContainer(antenna, 1) ;
    cs0.setRxContainer(antenna, 1) ;
    cs0.setTxContainer(1-antenna, 5) ;
    cs0.setRxContainer(1-antenna, 5) ;
    cs0.setGroupSizeDown(4) ;
    cs0.setGroupSizeUp(4) ;
    cs0.setTxScaling(Power(-12.0)) ;
    cs0.setState(ICarrier::STATE_ENABLE) ;

    // -- Carier 0 -----------
    carrierServer->setCarrier( cs0 ) ;

    // -- NONE -----------
    std::cerr << "Disable all carriers" << std::endl ;
    cs0.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs0 ) ;

    // -- Carier 0 -----------
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    // c1
    Frequency c1Freq(2350000.0, Frequency::KHz) ;
    cs1.setType(ICarrier::CARRTYPE_LTE10) ;
    cs1.setTxFrequency(c1Freq) ;
    cs1.setRxFrequency(c1Freq) ;
    cs1.setTxPower(37.0) ;
    cs1.setTxFibre(antenna, 0) ;
    cs1.setRxFibre(antenna, 0) ;
    cs1.setTxContainer(antenna, 9) ;
    cs1.setRxContainer(antenna, 9) ;
    cs1.setTxContainer(1-antenna, 13) ;
    cs1.setRxContainer(1-antenna, 13) ;
    cs1.setGroupSizeDown(4) ;
    cs1.setGroupSizeUp(4) ;
    cs1.setTxScaling(Power(-12.0)) ;
    cs1.setState(ICarrier::STATE_ENABLE) ;

    EXPECT_FALSE(carrierServer->setCarrier( cs1 )) ; // total power will be 38.0103dB (above max 37.0dB)

    // -- Carrier 0 + Carrier 1 ---------
    cs1.setTxPower(25.0) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    // -- Carrier 0 ----------
    cs1.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs1 ) ;

    // Tidy up
    cs0.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs0 ) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, ShutdownPath)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;

    TxOnOffMonitor monitor ;
    std::dynamic_pointer_cast< Subject<ITxOn, const ITxEventData&> >(carrierServer)->attach(monitor) ;
    std::dynamic_pointer_cast< Subject<ITxOff, const ITxEventData&> >(carrierServer)->attach(monitor) ;


    mSharedServer->m_index = 0;
    ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );
    mSharedServer->m_index = 1;
    ICarrierSetter& cs1 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    unsigned antenna = 0u ;

    Frequency c0Freq(2325000.0, Frequency::KHz) ;
    cs0.setType(ICarrier::CARRTYPE_LTE10) ;
    cs0.setTxFrequency(c0Freq) ;
    cs0.setRxFrequency(c0Freq) ;
    cs0.setTxPower( 30.0) ;
    cs0.setTxFibre(antenna, 0) ;
    cs0.setRxFibre(antenna, 0) ;
    cs0.setTxContainer(antenna, 1) ;
    cs0.setRxContainer(antenna, 1) ;
    cs0.setTxContainer(1-antenna, 5) ;
    cs0.setRxContainer(1-antenna, 5) ;
    cs0.setGroupSizeDown(4) ;
    cs0.setGroupSizeUp(4) ;
    cs0.setTxScaling(Power(-12.0)) ;
    cs0.setState(ICarrier::STATE_ENABLE) ;

    // -- Carier 0 -----------
    carrierServer->setCarrier( cs0 ) ;

    // -- NONE -----------
    std::cerr << "Disable all carriers" << std::endl ;
    cs0.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs0 ) ;

    // -- Carier 0 -----------
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    // c1
    Frequency c1Freq(2350000.0, Frequency::KHz) ;
    cs1.setType(ICarrier::CARRTYPE_LTE10) ;
    cs1.setTxFrequency(c1Freq) ;
    cs1.setRxFrequency(c1Freq) ;
    cs1.setTxPower(30.0) ;
    cs1.setTxFibre(antenna, 0) ;
    cs1.setRxFibre(antenna, 0) ;
    cs1.setTxContainer(antenna, 9) ;
    cs1.setRxContainer(antenna, 9) ;
    cs1.setTxContainer(1-antenna, 13) ;
    cs1.setRxContainer(1-antenna, 13) ;
    cs1.setGroupSizeDown(4) ;
    cs1.setGroupSizeUp(4) ;
    cs1.setTxScaling(Power(-12.0)) ;
    cs1.setState(ICarrier::STATE_ENABLE) ;

    std::stringstream ss ;


    // -- Carrier 0 + Carrier 1 ---------
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    // Should be TX on TX0 and Tx1
    EXPECT_TRUE( monitor.mOnOff[0] ) ;
    EXPECT_TRUE( monitor.mOnOff[1] ) ;
    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;
    {
        const ICarrier& c0(carrierServer->getCarrier(0)) ;
        EXPECT_EQ(1u, c0.getTxContainer(0)) ;
        EXPECT_EQ(5u, c0.getTxContainer(1)) ;
        EXPECT_EQ(ICarrier::STATE_ENABLE, c0.getState()) ;
        const ICarrier& c1(carrierServer->getCarrier(1)) ;
        EXPECT_EQ(9u, c1.getTxContainer(0)) ;
        EXPECT_EQ(13u, c1.getTxContainer(1)) ;
        EXPECT_EQ(ICarrier::STATE_ENABLE, c1.getState()) ;
    }

    // Check path is active
    EXPECT_TRUE( true == carrierServer->isTxActivePath(1));

    // Shutdown TX1
    std::cerr << "Shutdown Tx1" << std::endl ;
    carrierServer->shutdownPath(1) ;

    // Should be TX on TX0 only
    EXPECT_TRUE( monitor.mOnOff[0] ) ;
    EXPECT_FALSE( monitor.mOnOff[1] ) ;
    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;
    {
        const ICarrier& c0(carrierServer->getCarrier(0)) ;
        EXPECT_EQ(1u, c0.getTxContainer(0)) ;
        EXPECT_EQ(0u, c0.getTxContainer(1)) ;
        EXPECT_EQ(ICarrier::STATE_ENABLE, c0.getState()) ;
        const ICarrier& c1(carrierServer->getCarrier(1)) ;
        EXPECT_EQ(9u, c1.getTxContainer(0)) ;
        EXPECT_EQ(0u, c1.getTxContainer(1)) ;
        EXPECT_EQ(ICarrier::STATE_ENABLE, c1.getState()) ;
    }

    // Check path is active
    EXPECT_TRUE( true == carrierServer->isTxActivePath(0));

    // Shutdown TX0
    std::cerr << "Shutdown Tx0" << std::endl ;
    carrierServer->shutdownPath(0) ;

    // Should not be any TX
    EXPECT_FALSE( monitor.mOnOff[0] ) ;
    EXPECT_FALSE( monitor.mOnOff[1] ) ;
    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;
    {
        const ICarrier& c0(carrierServer->getCarrier(0)) ;
//        EXPECT_EQ(0, c0.getTxContainer(0)) ;
//        EXPECT_EQ(0, c0.getTxContainer(1)) ;
        EXPECT_EQ(ICarrier::STATE_DISABLE, c0.getState()) ;
        const ICarrier& c1(carrierServer->getCarrier(1)) ;
//        EXPECT_EQ(0, c1.getTxContainer(0)) ;
//        EXPECT_EQ(0, c1.getTxContainer(1)) ;
        EXPECT_EQ(ICarrier::STATE_DISABLE, c1.getState()) ;
    }

    // Should now be able to totally restore carrier just by changing state to ENABLE
    std::cerr << "C0 ENABLE" << std::endl ;
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    // Should be TX on TX0 and Tx1 c0 only
    EXPECT_TRUE( monitor.mOnOff[0] ) ;
    EXPECT_TRUE( monitor.mOnOff[1] ) ;
    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;
    {
        const ICarrier& c0(carrierServer->getCarrier(0)) ;
        EXPECT_EQ(1u, c0.getTxContainer(0)) ;
        EXPECT_EQ(5u, c0.getTxContainer(1)) ;
        EXPECT_EQ(ICarrier::STATE_ENABLE, c0.getState()) ;

        const ICarrier& c1(carrierServer->getCarrier(1)) ;
//        EXPECT_EQ(0, c1.getTxContainer(0)) ;
//        EXPECT_EQ(0, c1.getTxContainer(1)) ;
        EXPECT_EQ(ICarrier::STATE_DISABLE, c1.getState()) ;
    }

    // Enable c1
    std::cerr << "C1 ENABLE" << std::endl ;
    cs1.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    // Should be TX on TX0 and Tx1 c0 only
//    EXPECT_TRUE( monitor.mOnOff[0] ) ;
//    EXPECT_TRUE( monitor.mOnOff[1] ) ;
    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;
    {
        const ICarrier& c0(carrierServer->getCarrier(0)) ;
        EXPECT_EQ(1u, c0.getTxContainer(0)) ;
        EXPECT_EQ(5u, c0.getTxContainer(1)) ;
        EXPECT_EQ(ICarrier::STATE_ENABLE, c0.getState()) ;

        const ICarrier& c1(carrierServer->getCarrier(1)) ;
        EXPECT_EQ(9u, c1.getTxContainer(0)) ;
        EXPECT_EQ(13u, c1.getTxContainer(1)) ;
        EXPECT_EQ(ICarrier::STATE_ENABLE, c1.getState()) ;
    }


    // Tidy up
    cs0.setState(ICarrier::STATE_DISABLE) ;
    cs1.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs0 ) ;
    carrierServer->setCarrier( cs1 ) ;
    std::dynamic_pointer_cast< Subject<ITxOn, const ITxEventData&> >(carrierServer)->detach(monitor) ;
    std::dynamic_pointer_cast< Subject<ITxOff, const ITxEventData&> >(carrierServer)->detach(monitor) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, TxPowerMonitor)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }


    TxPowerMonitor monitor ;
    std::dynamic_pointer_cast< Subject<ITxPower, const ITxEventData&> >(carrierServer)->attach(monitor) ;

    mSharedServer->m_index = 0;
    ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );
    mSharedServer->m_index = 1;
    ICarrierSetter& cs1 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    unsigned antenna = 0u ;

    Frequency c0Freq(2325000.0, Frequency::KHz) ;
    cs0.setType(ICarrier::CARRTYPE_LTE10) ;
    cs0.setTxFrequency(c0Freq) ;
    cs0.setRxFrequency(c0Freq) ;
    cs0.setTxPower( 30.0) ;
    cs0.setTxFibre(antenna, 0) ;
    cs0.setRxFibre(antenna, 0) ;
    cs0.setTxContainer(antenna, 1) ;
    cs0.setRxContainer(antenna, 1) ;
    cs0.setTxContainer(1-antenna, 5) ;
    cs0.setRxContainer(1-antenna, 5) ;
    cs0.setGroupSizeDown(4) ;
    cs0.setGroupSizeUp(4) ;
    cs0.setTxScaling(Power(-12.0)) ;
    cs0.setState(ICarrier::STATE_ENABLE) ;

    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;
    monitor.clear() ;

    // -- Carier 0 -----------
    std::cerr << "Enable C0" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    EXPECT_TRUE( monitor.mPower[0] ) ;
    EXPECT_TRUE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    // -- NONE -----------
    std::cerr << "Disable C0" << std::endl ;
    cs0.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs0 ) ;

    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;


    // -- Carier 0 -----------
    std::cerr << "Enable C0" << std::endl ;
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;


    // c1
    Frequency c1Freq(2350000.0, Frequency::KHz) ;
    cs1.setType(ICarrier::CARRTYPE_LTE10) ;
    cs1.setTxFrequency(c1Freq) ;
    cs1.setRxFrequency(c1Freq) ;
    cs1.setTxPower(30.0) ;
    cs1.setTxFibre(antenna, 0) ;
    cs1.setRxFibre(antenna, 0) ;
    cs1.setTxContainer(antenna, 9) ;
    cs1.setRxContainer(antenna, 9) ;
    cs1.setTxContainer(1-antenna, 13) ;
    cs1.setRxContainer(1-antenna, 13) ;
    cs1.setGroupSizeDown(4) ;
    cs1.setGroupSizeUp(4) ;
    cs1.setTxScaling(Power(-12.0)) ;
    cs1.setState(ICarrier::STATE_ENABLE) ;

    std::stringstream ss ;


    // -- Carrier 0 + Carrier 1 ---------
    std::cerr << "Enable C1" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    // Should be TX on TX0 and Tx1
    EXPECT_TRUE( monitor.mPower[0] ) ;
    EXPECT_TRUE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    // Tidy up
    cs0.setState(ICarrier::STATE_DISABLE) ;
    cs1.setState(ICarrier::STATE_DISABLE) ;

    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    std::cerr << "Disable C0" << std::endl ;
    carrierServer->setCarrier( cs0 ) ;

    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    std::cerr << "Disable C1" << std::endl ;
    carrierServer->setCarrier( cs1 ) ;

    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    cs1.setTxContainer(0, 0) ;
    cs1.setRxContainer(0, 0) ;
    cs1.setTxContainer(1, 0) ;
    cs1.setRxContainer(1, 0) ;
    cs1.setState(ICarrier::STATE_DISABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    EXPECT_TRUE( monitor.mPower[0] ) ;
    EXPECT_TRUE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    // TIDY UP
    std::dynamic_pointer_cast< Subject<ITxPower, const ITxEventData&> >(carrierServer)->detach(monitor) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, TxPowerManager)
{
//	Loggable::setGroupLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE, "Carrier") ;
//	Loggable::setGroupLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE, "CarrierPower") ;
	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE) ;

    std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
//    std::shared_ptr<CarrierPowerMgr> powerMgr(CarrierPowerMgr::getInstance(MAX_CARRIERS)) ;

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }


    TxPowerMonitor monitor ;
    std::dynamic_pointer_cast< Subject<ITxPower, const ITxEventData&> >(carrierServer)->attach(monitor) ;

    mSharedServer->m_index = 0;
    ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );
    mSharedServer->m_index = 1;
    ICarrierSetter& cs1 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    // C0 on TX0
    Frequency c0Freq(2325000.0, Frequency::KHz) ;
    cs0.setType(ICarrier::CARRTYPE_LTE10) ;
    cs0.setTxFrequency(c0Freq) ;
    cs0.setRxFrequency(c0Freq) ;
    cs0.setTxPower( 37.0) ;
    cs0.setTxFibre(0, 0) ;
    cs0.setRxFibre(0, 0) ;
    cs0.setTxContainer(0, 1) ;
    cs0.setRxContainer(0, 1) ;
    cs0.setTxContainer(1, 0) ;
    cs0.setRxContainer(1, 0) ;
    cs0.setGroupSizeDown(4) ;
    cs0.setGroupSizeUp(4) ;
    cs0.setTxScaling(Power(-12.0)) ;
    cs0.setState(ICarrier::STATE_DISABLE) ;

    // -- Carier 0 -----------
    std::cerr << "Configure C0" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    // c1 on TX1
    Frequency c1Freq(2350000.0, Frequency::KHz) ;
    cs1.setType(ICarrier::CARRTYPE_LTE10) ;
    cs1.setTxFrequency(c1Freq) ;
    cs1.setRxFrequency(c1Freq) ;
    cs1.setTxPower(37.0) ;
    cs1.setTxFibre(0, 0) ;
    cs1.setRxFibre(0, 0) ;
    cs1.setTxContainer(0, 0) ;
    cs1.setRxContainer(0, 0) ;
    cs1.setTxContainer(1, 13) ;
    cs1.setRxContainer(1, 13) ;
    cs1.setGroupSizeDown(4) ;
    cs1.setGroupSizeUp(4) ;
    cs1.setTxScaling(Power(-12.0)) ;
    cs1.setState(ICarrier::STATE_DISABLE) ;

    std::cerr << "Configure C1" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    monitor.clear() ;

    // Should now be able to get the total power
    EXPECT_EQ(Power(37.0), carrierServer->getTxPower(0)) ;
    EXPECT_EQ(Power(37.0), carrierServer->getTxPower(1)) ;



    // -- Carier 0 -----------
    std::cerr << "Enable C0" << std::endl ;
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;


    // -- Carrier 0 + Carrier 1 ---------
    std::cerr << "Enable C1" << std::endl ;
    cs1.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    // Should be TX on TX0 and Tx1
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    // Change target power for C0
    std::cerr << "Disable C0" << std::endl ;
    cs0.setState(ICarrier::STATE_DISABLE) ;
    carrierServer->setCarrier( cs0 ) ;

    std::cerr << "Change C0 power" << std::endl ;
    cs0.setTxPower( 30.0) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    EXPECT_EQ(Power(30.0), carrierServer->getTxPower(0)) ;
    EXPECT_EQ(Power(37.0), carrierServer->getTxPower(1)) ;

    std::cerr << "Enable C0" << std::endl ;
    cs0.setState(ICarrier::STATE_ENABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    EXPECT_EQ(Power(30.0), carrierServer->getTxPower(0)) ;
    EXPECT_EQ(Power(37.0), carrierServer->getTxPower(1)) ;

    EXPECT_TRUE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;
    monitor.clear() ;



    // Tidy up
    cs0.setState(ICarrier::STATE_DISABLE) ;
    cs1.setState(ICarrier::STATE_DISABLE) ;

    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    std::cerr << "Disable C0" << std::endl ;
    carrierServer->setCarrier( cs0 ) ;

    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    std::cerr << "Disable C1" << std::endl ;
    carrierServer->setCarrier( cs1 ) ;

    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    // Actually shut down the IQ stream for C1
    cs1.setTxContainer(0, 0) ;
    cs1.setRxContainer(0, 0) ;
    cs1.setTxContainer(1, 0) ;
    cs1.setRxContainer(1, 0) ;
    cs1.setState(ICarrier::STATE_DISABLE) ;
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    // should only affect TX1
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_TRUE( monitor.mPower[1] ) ;
    monitor.clear() ;
    EXPECT_FALSE( monitor.mPower[0] ) ;
    EXPECT_FALSE( monitor.mPower[1] ) ;

    // TIDY UP
    std::dynamic_pointer_cast< Subject<ITxPower, const ITxEventData&> >(carrierServer)->detach(monitor) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, EnableUnsetCarrier)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    mSharedServer->m_index = 0;

	// "delete" the carrier
	EXPECT_TRUE( carrierServer->unconfigCarrier( mSharedServer->m_index  ) );


    ICarrierSetter& cs = carrierServer->getCarrierSetter( mSharedServer->m_index );

    // Cannot enable an unset carrier - that's just stupid!
    EXPECT_TRUE(cs.setState( ICarrier::STATE_ENABLE ) );
    EXPECT_FALSE( carrierServer->setCarrier( cs ) );

    std::stringstream ss ;
    carrierServer->show(ss) ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, TxChangeMonitor)
{
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }


    TxOnOffMonitor monitor ;
    std::dynamic_pointer_cast< Subject<ITxOn, const ITxEventData&> >(carrierServer)->attach(monitor) ;
    std::dynamic_pointer_cast< Subject<ITxOff, const ITxEventData&> >(carrierServer)->attach(monitor) ;
    std::dynamic_pointer_cast< Subject<ITxChange, const ITxEventData&> >(carrierServer)->attach(monitor) ;

    mSharedServer->m_index = 0;
    ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );
    mSharedServer->m_index = 1;
    ICarrierSetter& cs1 = carrierServer->getCarrierSetter( mSharedServer->m_index );
    mSharedServer->m_index = 2;
    ICarrierSetter& cs2 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    // C0 on TX0
    Frequency c0Freq(2325000.0, Frequency::KHz) ;
    cs0.setType(ICarrier::CARRTYPE_LTE10) ;
    cs0.setTxFrequency(c0Freq) ;
    cs0.setRxFrequency(c0Freq) ;
    cs0.setTxPower( 27.0) ;
    cs0.setTxFibre(0, 0) ;
    cs0.setRxFibre(0, 0) ;
    cs0.setTxContainer(0, 1) ;
    cs0.setRxContainer(0, 1) ;
    cs0.setTxContainer(1, 0) ;
    cs0.setRxContainer(1, 0) ;
    cs0.setGroupSizeDown(4) ;
    cs0.setGroupSizeUp(4) ;
    cs0.setTxScaling(Power(-12.0)) ;
    cs0.setState(ICarrier::STATE_DISABLE) ;
    std::cerr << "Configure C0" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    // c1 on TX1
    Frequency c1Freq(2350000.0, Frequency::KHz) ;
    cs1.setType(ICarrier::CARRTYPE_LTE10) ;
    cs1.setTxFrequency(c1Freq) ;
    cs1.setRxFrequency(c1Freq) ;
    cs1.setTxPower(27.0) ;
    cs1.setTxFibre(0, 0) ;
    cs1.setRxFibre(0, 0) ;
    cs1.setTxContainer(0, 0) ;
    cs1.setRxContainer(0, 0) ;
    cs1.setTxContainer(1, 13) ;
    cs1.setRxContainer(1, 13) ;
    cs1.setGroupSizeDown(4) ;
    cs1.setGroupSizeUp(4) ;
    cs1.setTxScaling(Power(-12.0)) ;
    cs1.setState(ICarrier::STATE_DISABLE) ;
    std::cerr << "Configure C1" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    // c2 on TX0 & TX1
    Frequency c2Freq(2350000.0, Frequency::KHz) ;
    cs2.setType(ICarrier::CARRTYPE_LTE10) ;
    cs2.setTxFrequency(c2Freq) ;
    cs2.setRxFrequency(c2Freq) ;
    cs2.setTxPower(27.0) ;
    cs2.setTxFibre(0, 0) ;
    cs2.setRxFibre(0, 0) ;
    cs2.setTxContainer(0, 5) ;
    cs2.setRxContainer(0, 5) ;
    cs2.setTxContainer(1, 13) ;
    cs2.setRxContainer(1, 13) ;
    cs2.setGroupSizeDown(4) ;
    cs2.setGroupSizeUp(4) ;
    cs2.setTxScaling(Power(-12.0)) ;
    cs2.setState(ICarrier::STATE_DISABLE) ;
    std::cerr << "Configure C1" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs2 )) ;

    monitor.clear() ;


/*
           A      B     C         D   E        F
            __________________________
	C0 ____|                          |________________
	       :       _______________
	C1 ____:______|               |____________________
	       :             ______________________
	C2 ____:____________|                      |_______
	       :
	       :___________________________________
	TX0____|C0          :C0C2         :C2      |_______
	      TXON         TXCHANGE     TXCHANGE   TXOFF
           A      B     C         D   E        F
	       :       ____________________________
	TX1____:______|C1   :C1C2     :C2          |_______
           :
                 TXON  TXCHANGE  TXCHANGE     TXOFF
           A      B     C         D   E        F

 */


    std::stringstream ss ;

    ///////////
    // A
    monitor.clear() ;
    cs0.setState(ICarrier::STATE_ENABLE) ;
    std::cerr << "C0 enabled:" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    EXPECT_TRUE( monitor.mTxOn[0] ) ;
    EXPECT_FALSE( monitor.mTxOff[0] ) ;
    EXPECT_FALSE( monitor.mTxChange[0] ) ;

    EXPECT_FALSE( monitor.mTxOn[1] ) ;
    EXPECT_FALSE( monitor.mTxOff[1] ) ;
    EXPECT_FALSE( monitor.mTxChange[1] ) ;

    ///////////
    // B
    monitor.clear() ;
    cs1.setState(ICarrier::STATE_ENABLE) ;
    std::cerr << "C1 enabled:" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    EXPECT_FALSE( monitor.mTxOn[0] ) ;
    EXPECT_FALSE( monitor.mTxOff[0] ) ;
    EXPECT_FALSE( monitor.mTxChange[0] ) ;

    EXPECT_TRUE( monitor.mTxOn[1] ) ;
    EXPECT_FALSE( monitor.mTxOff[1] ) ;
    EXPECT_FALSE( monitor.mTxChange[1] ) ;

    ///////////
    // C
    monitor.clear() ;
    cs2.setState(ICarrier::STATE_ENABLE) ;
    std::cerr << "C2 enabled:" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs2 )) ;

    EXPECT_FALSE( monitor.mTxOn[0] ) ;
    EXPECT_FALSE( monitor.mTxOff[0] ) ;
    EXPECT_TRUE( monitor.mTxChange[0] ) ;

    EXPECT_FALSE( monitor.mTxOn[1] ) ;
    EXPECT_FALSE( monitor.mTxOff[1] ) ;
    EXPECT_TRUE( monitor.mTxChange[1] ) ;


    ///////////
    // D
    monitor.clear() ;
    cs1.setState(ICarrier::STATE_DISABLE) ;
    std::cerr << "C1 disabled:" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    EXPECT_FALSE( monitor.mTxOn[0] ) ;
    EXPECT_FALSE( monitor.mTxOff[0] ) ;
    EXPECT_FALSE( monitor.mTxChange[0] ) ;

    EXPECT_FALSE( monitor.mTxOn[1] ) ;
    EXPECT_FALSE( monitor.mTxOff[1] ) ;
    EXPECT_TRUE( monitor.mTxChange[1] ) ;

    ///////////
    // E
    monitor.clear() ;
    cs0.setState(ICarrier::STATE_DISABLE) ;
    std::cerr << "C0 disabled:" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    EXPECT_FALSE( monitor.mTxOn[0] ) ;
    EXPECT_FALSE( monitor.mTxOff[0] ) ;
    EXPECT_TRUE( monitor.mTxChange[0] ) ;

    EXPECT_FALSE( monitor.mTxOn[1] ) ;
    EXPECT_FALSE( monitor.mTxOff[1] ) ;
    EXPECT_FALSE( monitor.mTxChange[1] ) ;

    ///////////
    // F
    monitor.clear() ;
    cs2.setState(ICarrier::STATE_DISABLE) ;
    std::cerr << "C2 disabled:" << std::endl ;
    EXPECT_TRUE(carrierServer->setCarrier( cs2 )) ;

    EXPECT_FALSE( monitor.mTxOn[0] ) ;
    EXPECT_TRUE( monitor.mTxOff[0] ) ;
    EXPECT_FALSE( monitor.mTxChange[0] ) ;

    EXPECT_FALSE( monitor.mTxOn[1] ) ;
    EXPECT_TRUE( monitor.mTxOff[1] ) ;
    EXPECT_FALSE( monitor.mTxChange[1] ) ;



    // Clean up
    std::dynamic_pointer_cast< Subject<ITxOn, const ITxEventData&> >(carrierServer)->detach(monitor) ;
    std::dynamic_pointer_cast< Subject<ITxOff, const ITxEventData&> >(carrierServer)->detach(monitor) ;
    std::dynamic_pointer_cast< Subject<ITxChange, const ITxEventData&> >(carrierServer)->detach(monitor) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, TDDParamsCheck)
{
    std::shared_ptr<IAppSettings> appSettings(IAppSettingsFactory::getInterface());

    std::shared_ptr<TestAppSettings> testAppSettings(std::dynamic_pointer_cast<TestAppSettings>(appSettings)) ;

    testAppSettings->setDuplex(IAppSettings::DUPLEX_TDD);

    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }

    mSharedServer->m_index = 0;
	ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    // Configure carrier 0
	Frequency c0Freq(2325000.0, Frequency::KHz) ;
	cs0.setType(ICarrier::CARRTYPE_LTE10) ;
	cs0.setTxFrequency(c0Freq) ;
	cs0.setRxFrequency(c0Freq) ;
	cs0.setTxPower( 37.0) ;
	cs0.setTxFibre(0, 0) ;
	cs0.setRxFibre(0, 0) ;
	cs0.setTxContainer(0, 1) ;
	cs0.setRxContainer(0, 1) ;
	cs0.setTxContainer(1, 0) ;
	cs0.setRxContainer(1, 0) ;
	cs0.setGroupSizeDown(4) ;
	cs0.setGroupSizeUp(4) ;
	cs0.setTxScaling(Power(-12.0)) ;
	cs0.setUlDlConfig(3);
	cs0.setSpSuConfig(5);
	cs0.setUlPrefixLenConfig(ICarrier::PREFIX_LENGTH_NORMAL);
	cs0.setDlPrefixLenConfig(ICarrier::PREFIX_LENGTH_EXTENDED);
	cs0.setState(ICarrier::STATE_ENABLE) ;
	std::cerr << "Configure C0" << std::endl ;
	EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
	EXPECT_EQ(3u, cs0.getUlDlConfig());
	EXPECT_EQ(5u, cs0.getSpSuConfig());
	EXPECT_EQ(ICarrier::PREFIX_LENGTH_NORMAL, cs0.getUlPrefixLen());
	EXPECT_EQ(ICarrier::PREFIX_LENGTH_EXTENDED, cs0.getDlPrefixLen());

	cs0.setUlDlConfig(0);
	cs0.setSpSuConfig(10);
	cs0.setUlPrefixLenConfig(ICarrier::PREFIX_LENGTH_EXTENDED);
	cs0.setDlPrefixLenConfig(ICarrier::PREFIX_LENGTH_EXTENDED);
	EXPECT_EQ(0u, cs0.getUlDlConfig());
	EXPECT_EQ(10u, cs0.getSpSuConfig());
	EXPECT_EQ(ICarrier::PREFIX_LENGTH_EXTENDED, cs0.getUlPrefixLen());
	EXPECT_EQ(ICarrier::PREFIX_LENGTH_EXTENDED, cs0.getDlPrefixLen());

	cs0.setUlDlConfig(6);
	cs0.setSpSuConfig(0);
	cs0.setUlPrefixLenConfig(ICarrier::PREFIX_LENGTH_NORMAL);
	cs0.setDlPrefixLenConfig(ICarrier::PREFIX_LENGTH_NORMAL);
	EXPECT_EQ(6u, cs0.getUlDlConfig());
	EXPECT_EQ(0u, cs0.getSpSuConfig());
	EXPECT_EQ(ICarrier::PREFIX_LENGTH_NORMAL, cs0.getUlPrefixLen());
	EXPECT_EQ(ICarrier::PREFIX_LENGTH_NORMAL, cs0.getDlPrefixLen());
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, TDDFreqValidation)
{
    std::shared_ptr<IAppSettings> appSettings(IAppSettingsFactory::getInterface());

    std::shared_ptr<TestAppSettings> testAppSettings(std::dynamic_pointer_cast<TestAppSettings>(appSettings)) ;

    testAppSettings->setDuplex(IAppSettings::DUPLEX_TDD);

    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }

    mSharedServer->m_index = 0;
	ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    // Configure carrier 0
	Frequency c0TxFreq(2325000.0, Frequency::KHz) ;
	Frequency c0RxFreq(2330000.0, Frequency::KHz) ;
	cs0.setType(ICarrier::CARRTYPE_LTE10) ;
	cs0.setTxFrequency(c0TxFreq) ;
	cs0.setRxFrequency(c0RxFreq) ;
	cs0.setTxPower( 37.0) ;
	cs0.setTxFibre(0, 0) ;
	cs0.setRxFibre(0, 0) ;
	cs0.setTxContainer(0, 1) ;
	cs0.setRxContainer(0, 1) ;
	cs0.setTxContainer(1, 0) ;
	cs0.setRxContainer(1, 0) ;
	cs0.setGroupSizeDown(4) ;
	cs0.setGroupSizeUp(4) ;
	cs0.setTxScaling(Power(-12.0)) ;
	cs0.setUlDlConfig(3);
	cs0.setSpSuConfig(5);
	cs0.setUlPrefixLenConfig(ICarrier::PREFIX_LENGTH_NORMAL);
	cs0.setDlPrefixLenConfig(ICarrier::PREFIX_LENGTH_EXTENDED);
	cs0.setState(ICarrier::STATE_ENABLE) ;
	std::cerr << "Configure C0" << std::endl ;
	EXPECT_FALSE(carrierServer->setCarrier( cs0 )) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, TDDSingleConfig)
{
    std::shared_ptr<IAppSettings> appSettings(IAppSettingsFactory::getInterface());

    std::shared_ptr<TestAppSettings> testAppSettings(std::dynamic_pointer_cast<TestAppSettings>(appSettings)) ;

    testAppSettings->setDuplex(IAppSettings::DUPLEX_TDD);

    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }

    mSharedServer->m_index = 0;
	ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    // Configure carrier 0
	Frequency c0Freq(2325000.0, Frequency::KHz) ;
	cs0.setType(ICarrier::CARRTYPE_LTE10) ;
	cs0.setTxFrequency(c0Freq) ;
	cs0.setRxFrequency(c0Freq) ;
	cs0.setTxPower( 10.0) ;
	cs0.setTxFibre(0, 0) ;
	cs0.setRxFibre(0, 0) ;
	cs0.setTxContainer(0, 1) ;
	cs0.setRxContainer(0, 1) ;
	cs0.setTxContainer(1, 0) ;
	cs0.setRxContainer(1, 0) ;
	cs0.setGroupSizeDown(4) ;
	cs0.setGroupSizeUp(4) ;
	cs0.setTxScaling(Power(-12.0)) ;
	cs0.setUlDlConfig(3);
	cs0.setSpSuConfig(5);
	cs0.setUlPrefixLenConfig(ICarrier::PREFIX_LENGTH_NORMAL);
	cs0.setDlPrefixLenConfig(ICarrier::PREFIX_LENGTH_EXTENDED);
	cs0.setState(ICarrier::STATE_ENABLE) ;
	std::cerr << "Configure C0" << std::endl ;
	EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;

    mSharedServer->m_index = 1;
	ICarrierSetter& cs1 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    // Configure carrier 1
	Frequency c1Freq(2330000.0, Frequency::KHz) ;
	cs1.setType(ICarrier::CARRTYPE_LTE10) ;
	cs1.setTxFrequency(c1Freq) ;
	cs1.setRxFrequency(c1Freq) ;
	cs1.setTxPower( 10.0) ;
	cs1.setTxFibre(0, 0) ;
	cs1.setRxFibre(0, 0) ;
	cs1.setTxContainer(0, 1) ;
	cs1.setRxContainer(0, 1) ;
	cs1.setTxContainer(1, 0) ;
	cs1.setRxContainer(1, 0) ;
	cs1.setGroupSizeDown(4) ;
	cs1.setGroupSizeUp(4) ;
	cs1.setTxScaling(Power(-12.0)) ;
	cs1.setState(ICarrier::STATE_ENABLE) ;
	std::cerr << "Configure C1 with same TDD config" << std::endl ;
	EXPECT_TRUE(carrierServer->setCarrier( cs1 )) ;

    mSharedServer->m_index = 2;
	ICarrierSetter& cs2 = carrierServer->getCarrierSetter( mSharedServer->m_index );

    // Configure carrier 2
	Frequency c2Freq(2430000.0, Frequency::KHz) ;
	cs2.setType(ICarrier::CARRTYPE_LTE10) ;
	cs2.setTxFrequency(c2Freq) ;
	cs2.setRxFrequency(c2Freq) ;
	cs2.setTxPower( 10.0) ;
	cs2.setTxFibre(0, 0) ;
	cs2.setRxFibre(0, 0) ;
	cs2.setTxContainer(0, 1) ;
	cs2.setRxContainer(0, 1) ;
	cs2.setTxContainer(1, 0) ;
	cs2.setRxContainer(1, 0) ;
	cs2.setGroupSizeDown(4) ;
	cs2.setGroupSizeUp(4) ;
	cs2.setTxScaling(Power(-12.0)) ;
	cs2.setUlDlConfig(2);
	cs2.setSpSuConfig(5);
	cs2.setUlPrefixLenConfig(ICarrier::PREFIX_LENGTH_NORMAL);
	cs2.setDlPrefixLenConfig(ICarrier::PREFIX_LENGTH_EXTENDED);
	cs2.setState(ICarrier::STATE_ENABLE) ;
	std::cerr << "Configure C2 with different TDD config" << std::endl ;
	EXPECT_FALSE(carrierServer->setCarrier( cs2 )) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierServerTestFixture, ORANParamsCheck)
{
    std::shared_ptr<IAppSettings> appSettings(IAppSettingsFactory::getInterface());

    std::shared_ptr<TestAppSettings> testAppSettings(std::dynamic_pointer_cast<TestAppSettings>(appSettings)) ;

    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();

    // Clear out all carriers
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
    	mSharedServer->m_index = index ;
        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
        EXPECT_TRUE(cset.setState( ICarrier::STATE_DISABLE ) );
        EXPECT_TRUE( carrierServer->setCarrier( cset ) );
    }

    mSharedServer->m_index = 0;
	ICarrierSetter& cs0 = carrierServer->getCarrierSetter( mSharedServer->m_index );

	cs0.applyChanges() ;
	EXPECT_FALSE(cs0.getTypeChanged()) ;
	EXPECT_FALSE(cs0.getTxFrequencyChanged()) ;
	EXPECT_FALSE(cs0.getRxFrequencyChanged()) ;
	EXPECT_FALSE(cs0.getTxPowerChanged()) ;
	EXPECT_FALSE(cs0.getTxFibreChanged(0)) ;
	EXPECT_FALSE(cs0.getRxFibreChanged(0)) ;

    // Configure carrier 0
	Frequency c0Freq(2325000.0, Frequency::KHz) ;
	cs0.setType(ICarrier::CARRTYPE_LTE10) ;
	EXPECT_TRUE(cs0.getTypeChanged()) ;
	cs0.setTxFrequency(c0Freq) ;
	EXPECT_TRUE(cs0.getTxFrequencyChanged()) ;
	cs0.setRxFrequency(c0Freq) ;
	EXPECT_TRUE(cs0.getRxFrequencyChanged()) ;
	cs0.setTxPower( 37.0) ;
	EXPECT_TRUE(cs0.getTxPowerChanged()) ;
	cs0.setTxFibre(0, 1) ;
	cs0.setTxFibre(0, 0) ;
	EXPECT_TRUE(cs0.getTxFibreChanged(0)) ;
	cs0.setRxFibre(0, 1) ;
	cs0.setRxFibre(0, 0) ;
	EXPECT_TRUE(cs0.getRxFibreChanged(0)) ;


////
//	cs0.setTxContainer(0, 1) ;
//	cs0.setRxContainer(0, 1) ;
//	cs0.setTxContainer(1, 0) ;
//	cs0.setRxContainer(1, 0) ;
//	cs0.setGroupSizeDown(4) ;
//	cs0.setGroupSizeUp(4) ;
////

	EXPECT_FALSE(cs0.getTxScalingChanged()) ;
	EXPECT_FALSE(cs0.getUlPrefixLenChanged()) ;
	EXPECT_FALSE(cs0.getDlPrefixLenChanged()) ;
	EXPECT_FALSE(cs0.getDlScsChanged()) ;
	EXPECT_FALSE(cs0.getUlScsChanged()) ;
	EXPECT_FALSE(cs0.getDlFftSizeChanged()) ;
	EXPECT_FALSE(cs0.getUlFftSizeChanged()) ;
	EXPECT_FALSE(cs0.getUlEaxcIdChanged(0)) ;
	EXPECT_FALSE(cs0.getUlEaxcIdChanged(1)) ;
	EXPECT_FALSE(cs0.getDlEaxcIdChanged(0)) ;
	EXPECT_FALSE(cs0.getDlEaxcIdChanged(1)) ;
	EXPECT_FALSE(cs0.getUlMacIdChanged()) ;

	cs0.setTxScaling(Power(-12.0)) ;
	EXPECT_TRUE(cs0.getTxScalingChanged()) ;
	cs0.setUlPrefixLenConfig(ICarrier::PREFIX_NONE);
	cs0.setUlPrefixLenConfig(ICarrier::PREFIX_LENGTH_NORMAL);
	EXPECT_TRUE(cs0.getUlPrefixLenChanged()) ;
	cs0.setDlPrefixLenConfig(ICarrier::PREFIX_NONE);
	cs0.setDlPrefixLenConfig(ICarrier::PREFIX_LENGTH_EXTENDED);
	EXPECT_TRUE(cs0.getDlPrefixLenChanged()) ;
	cs0.setDlScs(ICarrier::SCS_120kHz) ;
	EXPECT_TRUE(cs0.getDlScsChanged()) ;
	cs0.setUlScs(ICarrier::SCS_1kHz25) ;
	EXPECT_TRUE(cs0.getUlScsChanged()) ;
	cs0.setDlFftSize(ICarrier::FFT_512) ;
	EXPECT_TRUE(cs0.getDlFftSizeChanged()) ;
	cs0.setUlFftSize(ICarrier::FFT_4096) ;
	EXPECT_TRUE(cs0.getUlFftSizeChanged()) ;
	cs0.setUlEaxcId(0, 0x1234) ;
	EXPECT_TRUE(cs0.getUlEaxcIdChanged(0)) ;
	cs0.setUlEaxcId(1, 0x5678) ;
	EXPECT_TRUE(cs0.getUlEaxcIdChanged(1)) ;
	cs0.setDlEaxcId(0, 0x9abc) ;
	EXPECT_TRUE(cs0.getDlEaxcIdChanged(0)) ;
	cs0.setDlEaxcId(1, 0xdef0) ;
	EXPECT_TRUE(cs0.getDlEaxcIdChanged(1)) ;
	cs0.setUlMacId(0xaabbccddeeffULL) ;
	EXPECT_TRUE(cs0.getUlMacIdChanged()) ;

	cs0.setState(ICarrier::STATE_ENABLE) ;
	std::cerr << "Configure C0" << std::endl ;
	EXPECT_TRUE(carrierServer->setCarrier( cs0 )) ;
	EXPECT_EQ(ICarrier::PREFIX_LENGTH_NORMAL, cs0.getUlPrefixLen());
	EXPECT_EQ(ICarrier::PREFIX_LENGTH_EXTENDED, cs0.getDlPrefixLen());
	EXPECT_EQ(ICarrier::SCS_120kHz, cs0.getDlScs());
	EXPECT_EQ(ICarrier::SCS_1kHz25, cs0.getUlScs());
	EXPECT_EQ(ICarrier::FFT_512, cs0.getDlFftSize());
	EXPECT_EQ(ICarrier::FFT_4096, cs0.getUlFftSize());
	EXPECT_EQ(0x1234u, cs0.getUlEaxcId(0));
	EXPECT_EQ(0x5678u, cs0.getUlEaxcId(1));
	EXPECT_EQ(0x9abcu, cs0.getDlEaxcId(0));
	EXPECT_EQ(0xdef0u, cs0.getDlEaxcId(1));
	EXPECT_EQ(0xaabbccddeeffULL, cs0.getUlMacId());


/*
	cs0.setUlPrefixLenConfig(ICarrier::PREFIX_LENGTH_EXTENDED);
	cs0.setDlPrefixLenConfig(ICarrier::PREFIX_LENGTH_EXTENDED);
	EXPECT_EQ(0u, cs0.getUlDlConfig());
	EXPECT_EQ(10u, cs0.getSpSuConfig());

	cs0.setUlPrefixLenConfig(ICarrier::PREFIX_LENGTH_NORMAL);
	cs0.setDlPrefixLenConfig(ICarrier::PREFIX_LENGTH_NORMAL);
	EXPECT_EQ(6u, cs0.getUlDlConfig());
	EXPECT_EQ(0u, cs0.getSpSuConfig());
*/
}
