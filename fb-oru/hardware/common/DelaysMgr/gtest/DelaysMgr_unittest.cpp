/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelaysMgr_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "gtest/gtest.h"

#include "DelaysMgr.h"

using namespace Mplane ;


const unsigned NUM_TX = 2 ;
const unsigned NUM_RX = 3 ;
const unsigned NUM_CARRIERS = 4 ;

//=============================================================================================================
class DelaysMgrTests : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
    	std::shared_ptr<IDelaysMgr> delaysMgr(IDelaysMgr::getInterface()) ;
    	delaysMgr->reset() ;
    	delaysMgr->initialise(NUM_TX, NUM_RX, NUM_CARRIERS) ;
    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {

    }


protected:

    // Set up the test case (create shared resources)
    static void SetUpTestCase() {}

    // Shut down test case
    static void TearDownTestCase() {}

    void checkNonPath(IDelaysMgr::DelayAttr attr)
    {
    	std::shared_ptr<IDelaysMgr> delaysMgr(IDelaysMgr::getInterface()) ;

    	// Should fail if we try to set ant or carrier
    	EXPECT_FALSE(delaysMgr->hwSetPathDelay(attr, 0, 10)) ;
    	EXPECT_FALSE(delaysMgr->hwSetCarrierDelay(attr, 0, 0, 10)) ;
    	EXPECT_FALSE(delaysMgr->appSetPathDelay(attr, 0, 10)) ;
    	EXPECT_FALSE(delaysMgr->appSetCarrierDelay(attr, 0, 0, 10)) ;

    	EXPECT_EQ(0u, delaysMgr->getDelay(attr)) ;
    	EXPECT_TRUE(delaysMgr->hwSetDelay(attr, 20)) ;
    	EXPECT_EQ(20u, delaysMgr->getDelay(attr)) ;
    	EXPECT_TRUE(delaysMgr->appSetDelay(attr, 30)) ;
    	EXPECT_EQ(30u, delaysMgr->getDelay(attr)) ;
    	EXPECT_TRUE(delaysMgr->appSetDelay(attr, 0)) ;
    	EXPECT_EQ(0u, delaysMgr->getDelay(attr)) ;
    }

    void checkPath(IDelaysMgr::DelayAttr attr, unsigned numPorts)
    {
    	std::shared_ptr<IDelaysMgr> delaysMgr(IDelaysMgr::getInterface()) ;

    	// Should fail if we try to set non-path or carrier
    	EXPECT_FALSE(delaysMgr->hwSetDelay(attr, 10)) ;
    	EXPECT_FALSE(delaysMgr->hwSetCarrierDelay(attr, 0, 0, 10)) ;
    	EXPECT_FALSE(delaysMgr->appSetDelay(attr, 10)) ;
    	EXPECT_FALSE(delaysMgr->appSetCarrierDelay(attr, 0, 0, 10)) ;

    	// test invalid port
		EXPECT_FALSE(delaysMgr->hwSetPathDelay(attr, numPorts, 10)) ;

    	// Test all valid ports
    	for (unsigned port=0; port < numPorts; ++port)
    	{
			EXPECT_EQ(0u, delaysMgr->getPathDelay(attr, port)) ;

			EXPECT_TRUE(delaysMgr->hwSetPathDelay(attr, port, 20)) ;
			EXPECT_EQ(20u, delaysMgr->getPathDelay(attr, port)) ;

			EXPECT_TRUE(delaysMgr->appSetPathDelay(attr, port, 30)) ;
			EXPECT_EQ(30u, delaysMgr->getPathDelay(attr, port)) ;


			EXPECT_TRUE(delaysMgr->appSetPathDelay(attr, port, 0)) ;
			EXPECT_EQ(0u, delaysMgr->getPathDelay(attr, port)) ;
    	}
    }

    void checkCarrier(IDelaysMgr::DelayAttr attr, unsigned numPorts)
    {
    	std::shared_ptr<IDelaysMgr> delaysMgr(IDelaysMgr::getInterface()) ;

    	// Should fail if we try to set non-path or path
    	EXPECT_FALSE(delaysMgr->hwSetDelay(attr, 10)) ;
    	EXPECT_FALSE(delaysMgr->appSetDelay(attr, 10)) ;
		EXPECT_FALSE(delaysMgr->hwSetPathDelay(attr, 0, 10)) ;
		EXPECT_FALSE(delaysMgr->appSetPathDelay(attr, 0, 10)) ;

    	// test invalid port
		EXPECT_FALSE(delaysMgr->hwSetCarrierDelay(attr, 0, numPorts, 10)) ;
    	// test invalid carrier
		EXPECT_FALSE(delaysMgr->hwSetCarrierDelay(attr, NUM_CARRIERS, 0, 10)) ;

    	// Test all valid carriers
    	for (unsigned carrier=0; carrier < NUM_CARRIERS; ++carrier)
    	{
        	// Test all valid ports
        	for (unsigned port=0; port < numPorts; ++port)
        	{
				EXPECT_EQ(0u, delaysMgr->getCarrierDelay(attr, carrier, port)) ;

				EXPECT_TRUE(delaysMgr->hwSetCarrierDelay(attr, carrier, port, 20)) ;
				EXPECT_EQ(20u, delaysMgr->getCarrierDelay(attr, carrier, port)) ;

				EXPECT_TRUE(delaysMgr->appSetCarrierDelay(attr, carrier, port, 30)) ;
				EXPECT_EQ(30u, delaysMgr->getCarrierDelay(attr, carrier, port)) ;


				EXPECT_TRUE(delaysMgr->appSetCarrierDelay(attr, carrier, port, 0)) ;
				EXPECT_EQ(0u, delaysMgr->getCarrierDelay(attr, carrier, port)) ;
        	}
    	}
    }

};


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(DelaysMgrTests, init)
{
	std::shared_ptr<IDelaysMgr> delaysMgr(IDelaysMgr::getInterface()) ;
	EXPECT_TRUE(delaysMgr->getError().empty()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(DelaysMgrTests, nonPath)
{
	std::shared_ptr<IDelaysMgr> delaysMgr(IDelaysMgr::getInterface()) ;
	EXPECT_TRUE(delaysMgr->getError().empty()) ;

	checkNonPath(IDelaysMgr::OFFSET_DELAY) ;
	checkNonPath(IDelaysMgr::FRAMEDIFF) ;
	checkNonPath(IDelaysMgr::THRUDELAY_UP) ;
	checkNonPath(IDelaysMgr::THRUDELAY_DOWN) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(DelaysMgrTests, path)
{
	std::shared_ptr<IDelaysMgr> delaysMgr(IDelaysMgr::getInterface()) ;
	EXPECT_TRUE(delaysMgr->getError().empty()) ;

	checkPath(IDelaysMgr::EXTDELAY_DOWN, NUM_TX) ;
	checkPath(IDelaysMgr::EXTDELAY_UP, NUM_RX) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(DelaysMgrTests, carrier)
{
	std::shared_ptr<IDelaysMgr> delaysMgr(IDelaysMgr::getInterface()) ;
	EXPECT_TRUE(delaysMgr->getError().empty()) ;

	checkCarrier(IDelaysMgr::ADJDELAY_DOWN, NUM_TX) ;
	checkCarrier(IDelaysMgr::ANTDELAY_DOWN, NUM_TX) ;
	checkCarrier(IDelaysMgr::FRAMEOFF_DOWN, NUM_TX) ;

	checkCarrier(IDelaysMgr::ADJDELAY_UP, NUM_RX) ;
	checkCarrier(IDelaysMgr::ANTDELAY_UP, NUM_RX) ;
	checkCarrier(IDelaysMgr::FRAMEOFF_UP, NUM_RX) ;
}
