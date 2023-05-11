/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierFreq_unittest.cpp
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


#include "CarrierFreqMgr/CarrierFreq.h"

#include "CommonCarrierServer_fixture.h"



using namespace std;

using namespace Mplane;

//=============================================================================================================
// TEST FIXTURE
//=============================================================================================================
class CarrierFreqTestFixture : public CommonCarrierServerTestFixture {
public:
	void testCarrierFreq(const CarrierFreq& carrierFreq, const Frequency& centre, const Frequency& bandwidth)
	{
		Frequency min(centre - bandwidth/2.0) ;
		Frequency max(centre + bandwidth/2.0) ;
		EXPECT_EQ(centre, carrierFreq.getCentre()) ;
		EXPECT_EQ(min, carrierFreq.getMin()) ;
		EXPECT_EQ(max, carrierFreq.getMax()) ;

	}
};

//=============================================================================================================
// TESTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFreqTestFixture, Basic)
{
	CarrierFreq empty ;
//	EXPECT_EQ(Frequency(0.0), empty.getCentre()) ;
//	EXPECT_EQ(Frequency(0.0), empty.getMin()) ;
//	EXPECT_EQ(Frequency(0.0), empty.getMax()) ;
	testCarrierFreq(empty, Frequency(0.0), Frequency(0.0)) ;

	Frequency centre(Frequency(1000.0, Frequency::KHz)) ;

	CarrierFreq cf5MHz(centre, ICarrier::CARRTYPE_LTE5) ;
	testCarrierFreq(cf5MHz, centre, Frequency(5.0, Frequency::MHz)) ;
	CarrierFreq cf10MHz(centre, ICarrier::CARRTYPE_LTE10) ;
	testCarrierFreq(cf10MHz, centre, Frequency(10.0, Frequency::MHz)) ;
	CarrierFreq cf15MHz(centre, ICarrier::CARRTYPE_LTE15) ;
	testCarrierFreq(cf15MHz, centre, Frequency(15.0, Frequency::MHz)) ;
	CarrierFreq cf20MHz(centre, ICarrier::CARRTYPE_LTE20) ;
	testCarrierFreq(cf20MHz, centre, Frequency(20.0, Frequency::MHz)) ;

	CarrierFreq cfp5MHz(centre, ICarrier::CARRTYPE_PIM5) ;
	testCarrierFreq(cfp5MHz, centre, Frequency(5.0, Frequency::MHz)) ;
	CarrierFreq cfp10MHz(centre, ICarrier::CARRTYPE_PIM10) ;
	testCarrierFreq(cfp10MHz, centre, Frequency(10.0, Frequency::MHz)) ;
	CarrierFreq cfp15MHz(centre, ICarrier::CARRTYPE_PIM15) ;
	testCarrierFreq(cfp15MHz, centre, Frequency(15.0, Frequency::MHz)) ;
	CarrierFreq cfp20MHz(centre, ICarrier::CARRTYPE_PIM20) ;
	testCarrierFreq(cfp20MHz, centre, Frequency(20.0, Frequency::MHz)) ;

}
