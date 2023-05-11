/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierServer_fixture.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string.h>
#include <iostream>
#include <algorithm>

#include "ICarrier.h"
#include "ITxPort.h"
#include "IRxPort.h"
#include "ICarrierHardware.h"

#include "OffTargetFPGA.h"

#include "TestCarrier.h"
#include "CommonCarrierServer_fixture.h"

#include "IAppSettingsFactory.h"
#include "TestAppSettings.h"


using namespace std;

using namespace Mplane;

//===================================================================================================================
// DATA
//===================================================================================================================

// shared data
std::shared_ptr<CommonCarrierServerTest> CommonCarrierServerTestFixture::mSharedServer = std::shared_ptr<CommonCarrierServerTest>() ;


//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void CommonCarrierServerTestFixture::SetUp()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    cout << endl << "*** " << test_info->test_case_name() << " " << test_info->name() << " Tests ***" <<  endl;
    cout << test_info->name() << " - START" <<  endl;

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;

    Frequency loFreq(2337500.0, Frequency::KHz) ;
    txPorts[0]->setFrequency(loFreq) ;
    txPorts[1]->setFrequency(loFreq) ;
    rxPorts[0]->setFrequency(loFreq) ;
    rxPorts[1]->setFrequency(loFreq) ;

    mSharedServer->m_cbCount = 0;

    std::shared_ptr<IAppSettings> appSettings(IAppSettingsFactory::getInterface());

    std::shared_ptr<TestAppSettings> testAppSettings(std::dynamic_pointer_cast<TestAppSettings>(appSettings)) ;

    testAppSettings->setDuplex(IAppSettings::DUPLEX_FDD);

	restartFpgaEmulator() ;
}


//-------------------------------------------------------------------------------------------------------------------
void CommonCarrierServerTestFixture::TearDown()
{
	std::cerr << "Turn off all carriers" << std::endl ;
    // Clear out all carriers
    std::shared_ptr<ICarrierServer> carrierServer = ICarrierServer::getInstance();
    for (unsigned index=0; index < MAX_CARRIERS; ++index)
    {
//    	mSharedServer->m_index = index ;
//        ICarrierSetter& cset = carrierServer->getCarrierSetter( mSharedServer->m_index );
//        cset.setState( ICarrier::STATE_DISABLE );
//        cset.setTxContainer(0, 0) ;
//        cset.setTxContainer(1, 0) ;
//        cset.setRxContainer(0, 0) ;
//        cset.setRxContainer(1, 0) ;
//        EXPECT_TRUE( carrierServer->setCarrier( cset ) );

    	// "delete" the carrier
        EXPECT_TRUE( carrierServer->unconfigCarrier( index ) );
    }

    std::stringstream ss ;
    carrierServer->show(ss) ;
    std::cerr << "CARRIERS:" << std::endl ;
    std::cerr << ss.str() << std::endl ;
    ss.str("") ;


	const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    cout << endl << test_info->name() << " - END" <<  endl;
}



//-------------------------------------------------------------------------------------------------------------------
void CommonCarrierServerTestFixture::restartFpgaEmulator()
{
	// get the fpga emulator
	std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;
	fpgaEmu->reset() ;

	// preset the fpga's current line rate to 9830.4
	fpgaEmu->writeField("curLineRate[0]", 0x40) ;
	fpgaEmu->writeField("curLineRate[1]", 0x40) ;

	// set status code to FRAME_SYNC
	fpgaEmu->writeField("statCode[0]", 0xf) ;
	fpgaEmu->writeField("statCode[1]", 0xf) ;
}

//-------------------------------------------------------------------------------------------------------------------
void CommonCarrierServerTestFixture::checkString(const std::string& expectedFragment, const std::string actual)
{
	std::string lowerExpected(expectedFragment) ;
	std::transform(lowerExpected.begin(), lowerExpected.end(), lowerExpected.begin(), ::tolower) ;
	std::string lowerActual(actual) ;
	std::transform(lowerActual.begin(), lowerActual.end(), lowerActual.begin(), ::tolower) ;

	EXPECT_NE(std::string::npos, lowerActual.find(lowerExpected)) <<
		"Unable to find " <<
		expectedFragment <<
		" within " << actual ;
}



//-------------------------------------------------------------------------------------------------------------------
// Set up the test case (create shared resources)
void CommonCarrierServerTestFixture::SetUpTestCase()
{
	mSharedServer = std::shared_ptr<CommonCarrierServerTest>( new CommonCarrierServerTest() ) ;
}

//-------------------------------------------------------------------------------------------------------------------
// Shut down test case
void CommonCarrierServerTestFixture::TearDownTestCase()
{

}


//===================================================================================================================
// TEST METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
char const * const CommonCarrierServerTest::getObjName()
{
    return "TestCommonCarrier";
}

//-------------------------------------------------------------------------------------------------------------------
bool CommonCarrierServerTest::notify( ICarrierServer const &carrierMgr )
{
    m_cbCount++;
    m_cbCarrier = (ICarrier*) &carrierMgr.getCarrier( carrierMgr.lastCarrierIndexModified() );
    return true;
}

//-------------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrierServerTest::getIndex() const
{
    return m_index;
}
