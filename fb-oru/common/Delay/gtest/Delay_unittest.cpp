/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDelayAttrInterface_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "Delay.h"
#include "DelayUnit/DelayUnitNS.h"
#include "DelayUnit/DelayUnitUI.h"
#include "DelayUnit/DelayUnitBF.h"

using namespace Mplane;


//-------------------------------------------------------------------------------------------------------
class SimpleDelay : public Delay
{
public:
	// Declare which units we support
	static const DelayUnitNS& NS ;
	static const DelayUnitBF& BF ;
	static const DelayUnitUI& UI ;


	/**
	 * default constructor
	 */
	SimpleDelay(float delay = 0.0, const IDelayUnit& unit = SimpleDelay::NS, float lineRateMHz = 3072.0) :
		Delay(delay, unit, lineRateMHz)
	{}

	/**
	 * constructor based on copying the value of the other delay but using new units (use other line rate)
	 */
	SimpleDelay(const Delay& other, const IDelayUnit& unit) :
		Delay(other, unit)
	{}

	/**
	 * constructor based on copying the value of the other delay but using new units and a new line rate
	 */
	SimpleDelay(const Delay& other, const IDelayUnit& unit, float lineRateMHz) :
		Delay(other, unit, lineRateMHz)
	{}

	/**
	 * copy constructor
	 */
	SimpleDelay(const Delay& other) :
		Delay(other)
	{}

};

const DelayUnitNS& SimpleDelay::NS = DelayUnitNS::UNIT ;
const DelayUnitBF& SimpleDelay::BF = DelayUnitBF::UNIT ;
const DelayUnitUI& SimpleDelay::UI = DelayUnitUI::UNIT ;



//-------------------------------------------------------------------------------------------------------
// Fixture
class DelayTest : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
          ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
        std::cout << test_info->name() << " - START" <<  std::endl;

    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {
    }

};


//-------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------
TEST_F(DelayTest, NS)
{
	Delay a0(123.0) ;
	EXPECT_EQ(123, a0.getInt()) ;

	SimpleDelay a(123.0) ;
	EXPECT_EQ(123, a.getInt()) ;
	EXPECT_EQ(123, a.getInt(SimpleDelay::NS)) ;

	EXPECT_EQ("ns", a0.getUnit().unitstring());
	EXPECT_EQ("ns", a.getUnit().unitstring());

	SimpleDelay b(245.0) ;

	SimpleDelay c = b ;
	EXPECT_EQ(245, c.getInt()) ;

	SimpleDelay d( a + c ) ;
	EXPECT_EQ(368, d.getInt()) ;

	SimpleDelay e = ( a + c ) ;
	EXPECT_EQ(368, e.getInt()) ;


}

//-------------------------------------------------------------------------------------------------------
TEST_F(DelayTest, BF)
{
	SimpleDelay d(1, SimpleDelay::BF) ;
	EXPECT_EQ(1, d.getInt(SimpleDelay::BF)) ;
	EXPECT_EQ("BF", d.getUnit().unitstring());

	std::cout << "BF test : " << d << std::endl ;

	// convert to ns => should be ~ 260.4167ns
	EXPECT_EQ(260, d.getInt(SimpleDelay::NS)) ;

	// Start with ns, convert to BF
	SimpleDelay d2(260.4167, SimpleDelay::NS) ;
	EXPECT_EQ(1, d2.getInt(SimpleDelay::BF)) ;
	EXPECT_EQ(260, d2.getInt(SimpleDelay::NS)) ;

	SimpleDelay b = d2 + d ;
	EXPECT_NEAR(520.8334, b.get(), 0.0001) ;

	SimpleDelay c = d + d2 ;
	EXPECT_NEAR(520.8334, c.get(), 0.0001) ;

}


//-------------------------------------------------------------------------------------------------------
TEST_F(DelayTest, UI)
{
	// Default line rate is 3072MHz so 100 UI = 32.5521ns
	SimpleDelay d(100, SimpleDelay::UI) ;
	EXPECT_EQ(100, d.getInt(SimpleDelay::UI)) ;
	EXPECT_EQ("UI", d.getUnit().unitstring());

	std::cout << "UI test : " << d << " in ns=" << d.get(SimpleDelay::NS) << std::endl ;

	// convert to ns => should be ~ 32.5521ns
	EXPECT_NEAR(32.5521, d.get(SimpleDelay::NS), 0.0001) ;

	// Create at twice line rate 100 UI = 16.276ns
	SimpleDelay a(100, SimpleDelay::UI, 6144.0) ;
	EXPECT_NEAR(16.276, a.get(SimpleDelay::NS), 0.0001) ;


	SimpleDelay a_ui(10, SimpleDelay::UI) ;		// uses default line rate of 3.072GHz
	SimpleDelay b_ui(10, SimpleDelay::UI, 6144.0) ;		// uses line rate of 6.144GHz

	SimpleDelay c_ui = a_ui + b_ui ;
	std::cout << "UI test : sum=" << c_ui << std::endl ;

}


//-------------------------------------------------------------------------------------------------------
TEST_F(DelayTest, Examples)
{
	SimpleDelay a_ns(10) ;
	SimpleDelay b_bf(20, SimpleDelay::BF) ;
	SimpleDelay c_ui(30, SimpleDelay::UI, 6144.0) ;

	// Get the delays
	std::cout << a_ns.get(SimpleDelay::NS) << std::endl ; // prints 10
	std::cout << b_bf.get(SimpleDelay::BF) << std::endl ; // prints 20
	std::cout << c_ui.get(SimpleDelay::UI) << std::endl ; // prints 30

	// Get delays in ns - default is to show NS
	std::cout << a_ns.get(SimpleDelay::NS) << std::endl ; // prints 10
	std::cout << b_bf.get(SimpleDelay::NS) << std::endl ; // prints 5208.33
	std::cout << c_ui.get(SimpleDelay::NS) << std::endl ; // prints 4.88281

	// Get delays in ns
	std::cout << a_ns.get() << std::endl ; // prints 10
	std::cout << b_bf.get() << std::endl ; // prints 5208.33
	std::cout << c_ui.get() << std::endl ; // prints 4.88281

	EXPECT_NEAR(10.0, a_ns.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(5208.33, b_bf.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(4.88281, c_ui.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(10.0, a_ns.get(), 0.01) ;
	EXPECT_NEAR(5208.33, b_bf.get(), 0.01) ;
	EXPECT_NEAR(4.88281, c_ui.get(), 0.01) ;

	// Get units
	if (c_ui.getUnit().usesLineRate())
	{
		// show line rate if this delay unit uses it
		std::cout << c_ui.getLineRate() << std::endl ; // shows 6144
	}

	// Change units
	a_ns.setUnit(SimpleDelay::BF) ; // converts delay in ns into a delay in BF



	// Show delays
	std::cout << a_ns << std::endl ; // prints 10 ns
	std::cout << b_bf << std::endl ; // prints 20 BF
	std::cout << c_ui << std::endl ; // prints 30 UI @ 6144 MHz
}

//-------------------------------------------------------------------------------------------------------
TEST_F(DelayTest, Round)
{
	SimpleDelay a_ns(10.0) ;
	SimpleDelay b_ns(10.1) ;
	SimpleDelay c_ns(20.5) ;
	SimpleDelay d_ns(30.8) ;


	// Show delays
	std::cout << a_ns << std::endl ;
	std::cout << b_ns << std::endl ;
	std::cout << c_ns << std::endl ;
	std::cout << d_ns << std::endl ;

	a_ns.round() ;
	b_ns.round() ;
	c_ns.round() ;
	d_ns.round() ;

	EXPECT_NEAR(10.0, a_ns.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(10.0, b_ns.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(21.0, c_ns.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(31.0, d_ns.get(SimpleDelay::NS), 0.01) ;

	// Show delays
	std::cout << a_ns << std::endl ;
	std::cout << b_ns << std::endl ;
	std::cout << c_ns << std::endl ;
	std::cout << d_ns << std::endl ;

}

//-------------------------------------------------------------------------------------------------------
TEST_F(DelayTest, Ceil)
{
	SimpleDelay a_ns(10.0) ;
	SimpleDelay b_ns(10.1) ;
	SimpleDelay c_ns(20.5) ;
	SimpleDelay d_ns(30.8) ;


	// Show delays
	std::cout << a_ns << std::endl ;
	std::cout << b_ns << std::endl ;
	std::cout << c_ns << std::endl ;
	std::cout << d_ns << std::endl ;

	a_ns.ceil() ;
	b_ns.ceil() ;
	c_ns.ceil() ;
	d_ns.ceil() ;

	EXPECT_NEAR(10.0, a_ns.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(11.0, b_ns.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(21.0, c_ns.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(31.0, d_ns.get(SimpleDelay::NS), 0.01) ;

	// Show delays
	std::cout << a_ns << std::endl ;
	std::cout << b_ns << std::endl ;
	std::cout << c_ns << std::endl ;
	std::cout << d_ns << std::endl ;

}

//-------------------------------------------------------------------------------------------------------
TEST_F(DelayTest, Floor)
{
	SimpleDelay a_ns(10.0) ;
	SimpleDelay b_ns(10.1) ;
	SimpleDelay c_ns(20.5) ;
	SimpleDelay d_ns(30.8) ;


	// Show delays
	std::cout << a_ns << std::endl ;
	std::cout << b_ns << std::endl ;
	std::cout << c_ns << std::endl ;
	std::cout << d_ns << std::endl ;

	a_ns.floor() ;
	b_ns.floor() ;
	c_ns.floor() ;
	d_ns.floor() ;

	EXPECT_NEAR(10.0, a_ns.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(10.0, b_ns.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(20.0, c_ns.get(SimpleDelay::NS), 0.01) ;
	EXPECT_NEAR(30.0, d_ns.get(SimpleDelay::NS), 0.01) ;

	// Show delays
	std::cout << a_ns << std::endl ;
	std::cout << b_ns << std::endl ;
	std::cout << c_ns << std::endl ;
	std::cout << d_ns << std::endl ;

}



//===================================================================================================================
