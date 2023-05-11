/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Rs485FpgaBus_fixture.cpp
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

#include "IAppSettingsFactory.h"

#include "Rs485FpgaBus_fixture.h"
#include "TestAppSettings.h"


using namespace std;

using namespace Mplane;

//===================================================================================================================
// DATA
//===================================================================================================================



//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void Rs485FpgaBusTestFixture::SetUp()
{
	this->super::SetUp() ;

}


//-------------------------------------------------------------------------------------------------------------------
void Rs485FpgaBusTestFixture::TearDown()
{
	this->super::TearDown() ;
}



//-------------------------------------------------------------------------------------------------------------------
// Set up the test case (create shared resources)
void Rs485FpgaBusTestFixture::SetUpTestCase()
{
	super::SetUpTestCase() ;
}

//-------------------------------------------------------------------------------------------------------------------
// Shut down test case
void Rs485FpgaBusTestFixture::TearDownTestCase()
{
	super::TearDownTestCase() ;
}
