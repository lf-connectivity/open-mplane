/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierPowerPath_unittest.cpp
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


#include "CarrierPowerMgr/CarrierPowerPath.h"

#include "CommonCarrierServer_fixture.h"


using namespace std;

using namespace Mplane;

//=============================================================================================================
// TEST FIXTURE
//=============================================================================================================
class CarrierPowerPathTestFixture : public CommonCarrierServerTestFixture {
public:

	void addExpectOk(CarrierPowerPath& pathPower, const Power& power, unsigned carrierIndex, const Power& expectedTotal)
	{
		std::string failReason ;

		EXPECT_TRUE(pathPower.canFit(carrierIndex, power, failReason)) << failReason ;
		EXPECT_TRUE(pathPower.add(carrierIndex, power, failReason)) << failReason ;
		EXPECT_EQ(expectedTotal, pathPower.getPower()) ;
	}

	void addExpectFail(CarrierPowerPath& pathPower, const Power& power, unsigned carrierIndex)
	{
		std::string failReason ;

		EXPECT_FALSE(pathPower.canFit(carrierIndex, power, failReason)) ;
	}

	void delExpectOk(CarrierPowerPath& pathPower, unsigned carrierIndex, const Power& expectedTotal)
	{
		std::string failReason ;

		EXPECT_TRUE(pathPower.del(carrierIndex, failReason)) << failReason ;
		EXPECT_EQ(expectedTotal, pathPower.getPower()) ;
	}

	void delExpectFail(CarrierPowerPath& pathPower, unsigned carrierIndex)
	{
		std::string failReason ;

		EXPECT_FALSE(pathPower.del(carrierIndex, failReason)) ;
		EXPECT_FALSE(failReason.empty()) ;
	}

};

//=============================================================================================================
// TESTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(CarrierPowerPathTestFixture, Basic)
{
	Power pathMin(0.0) ;
	Power pathMax(37.0) ;
	Power ext(3.0) ;
	Power extMax(44.2) ;
	CarrierPowerPath pathPower("test", 0, pathMin, pathMax, ext, extMax) ;

	EXPECT_EQ(Power(0.0), pathPower.getPower()) ;

	// Can't delete from empty list
	delExpectFail(pathPower, 0) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CarrierPowerPathTestFixture, SingleCarrier)
{
	Power pathMin(0.0) ;
	Power pathMax(37.0) ;
	Power ext(3.0) ;
	Power extMax(44.2) ;
	CarrierPowerPath pathPower("test", 0, pathMin, pathMax, ext, extMax) ;

	EXPECT_EQ(Power(0.0), pathPower.getPower()) ;

	addExpectFail(pathPower, Power(40.0), 0) ;

	addExpectOk(pathPower, Power(10.0), 0, Power(10.0)) ;
	delExpectOk(pathPower, 0, Power(0.0)) ;

	// Can't delete from empty list
	delExpectFail(pathPower, 0) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CarrierPowerPathTestFixture, MultipleCarriers)
{
	Power pathMin(0.0) ;
	Power pathMax(37.1) ;
	Power ext(3.0) ;
	Power extMax(44.2) ;
	CarrierPowerPath pathPower("test", 0, pathMin, pathMax, ext, extMax) ;

	EXPECT_EQ(Power(0.0), pathPower.getPower()) ;

	addExpectOk(pathPower, Power(30.0), 0, Power(30.0)) ;
	addExpectOk(pathPower, Power(30.0), 1, Power(33.0103)) ;
	addExpectOk(pathPower, Power(30.0), 2, Power(34.7712)) ;
	addExpectOk(pathPower, Power(30.0), 3, Power(36.0206)) ;
	addExpectOk(pathPower, Power(30.0), 4, Power(36.99)) ;

	// this would be over max
	addExpectFail(pathPower, Power(30.0), 5) ;

	delExpectOk(pathPower, 4, Power(36.0206)) ;
	delExpectOk(pathPower, 3, Power(34.7712)) ;
	delExpectOk(pathPower, 2, Power(33.0103)) ;
	delExpectOk(pathPower, 1, Power(30.0)) ;
	delExpectOk(pathPower, 0, Power(0.0)) ;

	// Can't delete from empty list
	delExpectFail(pathPower, 0) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CarrierPowerPathTestFixture, ExtFilterPower)
{
	Power pathMin(0.0) ;
	Power pathMax(40.0) ;
	Power ext(6.0) ;
	Power extMax(44.2) ;
	CarrierPowerPath pathPower("test", 0, pathMin, pathMax, ext, extMax) ;

	EXPECT_EQ(Power(0.0), pathPower.getPower()) ;

	addExpectOk(pathPower, Power(30.0), 0, Power(30.0)) ;
	addExpectOk(pathPower, Power(30.0), 1, Power(33.0103)) ;
	addExpectOk(pathPower, Power(30.0), 2, Power(34.7712)) ;
	addExpectOk(pathPower, Power(30.0), 3, Power(36.0206)) ;
	addExpectOk(pathPower, Power(30.0), 4, Power(36.99)) ;
//	addExpectOk(pathPower, Power(30.0), 5, Power(37.7815)) ;

	// this would be over max
	addExpectFail(pathPower, Power(30.0), 6) ;	// 38.45 + 6.0 = 44.45 > 44.2

//	delExpectOk(pathPower, 5, Power(36.99)) ;
	delExpectOk(pathPower, 4, Power(36.0206)) ;
	delExpectOk(pathPower, 3, Power(34.7712)) ;
	delExpectOk(pathPower, 2, Power(33.0103)) ;
	delExpectOk(pathPower, 1, Power(30.0)) ;
	delExpectOk(pathPower, 0, Power(0.0)) ;

	// Can't delete from empty list
	delExpectFail(pathPower, 0) ;
}
