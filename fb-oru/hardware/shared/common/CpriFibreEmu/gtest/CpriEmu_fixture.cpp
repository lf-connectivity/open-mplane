/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriEmu_fixture.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CpriEmu_fixture.h"

using namespace Mplane ;

//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void CpriEmuTestFixture::SetUp()
{
	this->super::SetUp() ;

//    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
//    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;
//
//    Frequency loFreq(2337500.0, Frequency::KHz) ;
//    txPorts[0]->setFrequency(loFreq) ;
//    txPorts[1]->setFrequency(loFreq) ;
//    rxPorts[0]->setFrequency(loFreq) ;
//    rxPorts[1]->setFrequency(loFreq) ;

	restartFpgaEmulator() ;
}


//-------------------------------------------------------------------------------------------------------------------
void CpriEmuTestFixture::TearDown()
{
	this->super::TearDown() ;
}



//-------------------------------------------------------------------------------------------------------------------
// Set up the test case (create shared resources)
void CpriEmuTestFixture::SetUpTestCase()
{
	FpgaRegCaptureTestFixture::SetUpTestCase() ;
}

//-------------------------------------------------------------------------------------------------------------------
// Shut down test case
void CpriEmuTestFixture::TearDownTestCase()
{
	FpgaRegCaptureTestFixture::TearDownTestCase() ;
}
