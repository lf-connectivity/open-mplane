/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierServer_fixture.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CarrierServer_fixture.h"

#include <string.h>
#include <iostream>
#include <algorithm>

#include "ICarrier.h"
#include "ITxPort.h"
#include "IRxPort.h"
#include "ICarrierHardware.h"

#include "OffTargetFPGA.h"



using namespace std;

using namespace Mplane;

//===================================================================================================================
// DATA
//===================================================================================================================

// shared data
std::shared_ptr<CarrierServerTest> CarrierServerTestFixture::mSharedServer = std::shared_ptr<CarrierServerTest>() ;


//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void CarrierServerTestFixture::SetUp()
{
	//this->super::SetUp() ;

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;

    Frequency loFreq(2337500.0, Frequency::KHz) ;
    txPorts[0]->setFrequency(loFreq) ;
    txPorts[1]->setFrequency(loFreq) ;
    rxPorts[0]->setFrequency(loFreq) ;
    rxPorts[1]->setFrequency(loFreq) ;

    mSharedServer->m_cbCount = 0;

}


//-------------------------------------------------------------------------------------------------------------------
void CarrierServerTestFixture::TearDown()
{
	//this->super::TearDown() ;
}



//-------------------------------------------------------------------------------------------------------------------
// Set up the test case (create shared resources)
void CarrierServerTestFixture::SetUpTestCase()
{
	//super::SetUpTestCase() ;
	mSharedServer = std::shared_ptr<CarrierServerTest>( new CarrierServerTest() ) ;
}

//-------------------------------------------------------------------------------------------------------------------
// Shut down test case
void CarrierServerTestFixture::TearDownTestCase()
{
	//super::TearDownTestCase() ;
}

//-------------------------------------------------------------------------------------------------------------------
bool CarrierServerTestFixture::carrierHwCheck(unsigned index,
		const std::string& msg, const std::string& findStr)
{
    std::shared_ptr<ICarrierHardwareList> hwlist(ICarrierHardwareList::getInstance()) ;
    ICarrierHardware* ch(hwlist->getCarrierHardware(index)) ;

    std::stringstream ss ;
    ch->showCarrier(ss) ;

    std::cerr << msg << std::endl ;
    std::cerr << ss.str() << std::endl ;

    return ss.str().find(findStr) != std::string::npos ;
}

//===================================================================================================================
// TEST METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
char const * const CarrierServerTest::getObjName()
{
    return "TestCommonCarrier";
}

//-------------------------------------------------------------------------------------------------------------------
bool CarrierServerTest::notify( ICarrierServer const &carrierMgr )
{
    m_cbCount++;
    m_cbCarrier = (ICarrier*) &carrierMgr.getCarrier( carrierMgr.lastCarrierIndexModified() );
    return true;
}

//-------------------------------------------------------------------------------------------------------------------
const unsigned CarrierServerTest::getIndex() const
{
    return m_index;
}
