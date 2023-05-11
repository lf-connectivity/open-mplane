/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcCal_fixture.cpp
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

#include "QmcCal_fixture.h"


using namespace std;

using namespace Mplane;

//===================================================================================================================
// DATA
//===================================================================================================================



//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void QmcCalTestFixture::SetUp()
{
	this->super::SetUp() ;

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;

    Frequency loFreq(2337500.0, Frequency::KHz) ;
    txPorts[0]->setFrequency(loFreq) ;
    txPorts[1]->setFrequency(loFreq) ;
    rxPorts[0]->setFrequency(loFreq) ;
    rxPorts[1]->setFrequency(loFreq) ;

}


//-------------------------------------------------------------------------------------------------------------------
void QmcCalTestFixture::TearDown()
{
	this->super::TearDown() ;
}



//-------------------------------------------------------------------------------------------------------------------
// Set up the test case (create shared resources)
void QmcCalTestFixture::SetUpTestCase()
{
	super::SetUpTestCase() ;
}

//-------------------------------------------------------------------------------------------------------------------
// Shut down test case
void QmcCalTestFixture::TearDownTestCase()
{
	super::TearDownTestCase() ;
}
