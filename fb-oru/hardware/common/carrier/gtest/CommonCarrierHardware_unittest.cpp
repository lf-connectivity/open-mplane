/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierHardware_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string>
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

#include "FrequencyUtils.hpp"
#include "IFrequencyConst.h"
#include "ICarrier.h"
#include "ITxPort.h"
#include "IRxPort.h"
#include "CommonCarrier.h"
#include "CarrierUtils.hpp"
#include "CommonCarrierHardware.h"
#include "CommonCarrierModel.h"

#include "TestCarrier.h"
#include "CommonCarrierServer_fixture.h"



using namespace std;

using namespace Mplane;

//=============================================================================================================
// SERVER TEST CLASS
//=============================================================================================================

class CommonCarrierHardwareTestFixture : public CommonCarrierServerTestFixture {
};

//=============================================================================================================
// TESTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommonCarrierHardwareTestFixture, Basic)
{
	TestRadioCarrier* c(new TestRadioCarrier(0, 2, 2)) ;
	CommonCarrierHardware ch(c) ;
	const ICarrier& cref(ch.getCarrier()) ;
	(void)cref;

	EXPECT_TRUE(ch.validateChange(*c)) ;
	EXPECT_TRUE(ch.carrierChange(*c)) ;
	EXPECT_TRUE(ch.preUpdate()) ;
	EXPECT_TRUE(ch.updateHardware()) ;
	EXPECT_TRUE(ch.postUpdate()) ;
	ch.changeComplete() ;

	EXPECT_FALSE(ch.isChanged()) ;

	delete c ;
}
