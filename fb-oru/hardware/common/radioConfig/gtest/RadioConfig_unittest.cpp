/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioConfig_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>

#include <unistd.h>

#include "gtest/gtest.h"

#include "Path.h"
#include "RadioConfig.h"

using namespace Mplane ;

//===================================================================================================================
const std::string TESTDIR("./") ;
const double MAX_FREQ(20000000000.0) ; // 20G

//===================================================================================================================
class RadioConfigTest : public ::testing::Test
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


	void addIntLimit(const std::string& name,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, int value)
	{
		std::shared_ptr<DataVariant> dv(std::make_shared<DataVariant>(name, "INT")) ;
		dv->setInt(value) ;
		limits[name] = dv ;
	}

	void addMinIntLimit(const std::string& variable,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, int value)
	{
		addIntLimit( IRadioConfig::limitMinName(variable), limits, value) ;
	}

	void addMaxIntLimit(const std::string& variable,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, int value)
	{
		addIntLimit( IRadioConfig::limitMaxName(variable), limits, value) ;
	}

	void addDoubleLimit(const std::string& name,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, double value)
	{
		std::shared_ptr<DataVariant> dv(std::make_shared<DataVariant>(name, "DOUBLE")) ;
		dv->setDouble(value) ;
		limits[name] = dv ;
	}

	void addMinDoubleLimit(const std::string& variable,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, double value)
	{
		addDoubleLimit( IRadioConfig::limitMinName(variable), limits, value) ;
	}

	void addMaxDoubleLimit(const std::string& variable,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, double value)
	{
		addDoubleLimit( IRadioConfig::limitMaxName(variable), limits, value) ;
	}



};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RadioConfigTest, create)
{
	std::string file(TESTDIR + "radio-config") ;
	Path::remove(file) ;

	RadioConfig rc(file) ;
	EXPECT_FALSE(rc.isValid()) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(RadioConfigTest, test1)
{

	const std::map<std::string, std::string> DEFAULTS{
		{ IRadioConfig::NUM_CARRIERS, 	"4" },

		{ IRadioConfig::NUM_TX, "4" },
		{ IRadioConfig::TX_MAX_AIR_FREQ, "3800000" },
		{ IRadioConfig::TX_MIN_AIR_FREQ, "700000" },
		{ IRadioConfig::TX_MAX_FILTER_FREQ, "3800000" },
		{ IRadioConfig::TX_MIN_FILTER_FREQ, "700000" },
		{ IRadioConfig::TX_MAX_FREQ, "3800000" },
		{ IRadioConfig::TX_MIN_FREQ, "700000" },
		{ IRadioConfig::TX_CENTRE_FREQ, "2000000" },
		{ IRadioConfig::TX_BANDWIDTH, "100000" },
		{ IRadioConfig::TX_MAX_POWER, "0" },
		{ IRadioConfig::TX_MIN_POWER, "-30" },

		{ IRadioConfig::NUM_RX, "4" },
		{ IRadioConfig::RX_MAX_AIR_FREQ, "3800000" },
		{ IRadioConfig::RX_MIN_AIR_FREQ, "700000" },
		{ IRadioConfig::RX_MAX_FILTER_FREQ, "3800000" },
		{ IRadioConfig::RX_MIN_FILTER_FREQ, "700000" },
		{ IRadioConfig::RX_MAX_FREQ, "3800000" },
		{ IRadioConfig::RX_MIN_FREQ, "700000" },
		{ IRadioConfig::RX_CENTRE_FREQ, "2000000" },
		{ IRadioConfig::RX_BANDWIDTH, "100000" },

		{ IRadioConfig::NUM_SRX, "2" },
		{ IRadioConfig::SRX_TX_PER_PORT, "2" },

	} ;

	std::string file(TESTDIR + "radio-config") ;
	Path::remove(file) ;

	RadioConfig rc(file, DEFAULTS) ;
	EXPECT_TRUE(rc.isValid()) ;
	EXPECT_EQ("", rc.error()) ;

	std::map<std::string, std::shared_ptr<DataVariant>> limits ;
	addMinIntLimit(IRadioConfig::NUM_CARRIERS, limits, 1) ;
	addMaxIntLimit(IRadioConfig::NUM_CARRIERS, limits, 256) ;

	addMinIntLimit(IRadioConfig::NUM_TX, limits, 0) ;
	addMaxIntLimit(IRadioConfig::NUM_TX, limits, 256) ;
	addMinDoubleLimit(IRadioConfig::TX_MAX_AIR_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_MAX_AIR_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_MIN_AIR_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_MIN_AIR_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_MAX_FILTER_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_MAX_FILTER_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_MIN_FILTER_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_MIN_FILTER_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_MAX_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_MAX_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_MIN_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_MIN_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_CENTRE_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_CENTRE_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_BANDWIDTH, limits, 1000.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_BANDWIDTH, limits, MAX_FREQ) ;

	addMinDoubleLimit(IRadioConfig::TX_MAX_POWER, limits, -10.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_MAX_POWER, limits, 100.0) ;
	addMinDoubleLimit(IRadioConfig::TX_MIN_POWER, limits, -100.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_MIN_POWER, limits, 0.0) ;

	addMinIntLimit(IRadioConfig::NUM_RX, limits, 0) ;
	addMaxIntLimit(IRadioConfig::NUM_RX, limits, 256) ;
	addMinDoubleLimit(IRadioConfig::RX_MAX_AIR_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::RX_MAX_AIR_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_MIN_AIR_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::RX_MIN_AIR_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_MAX_FILTER_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::RX_MAX_FILTER_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_MIN_FILTER_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::RX_MIN_FILTER_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_MAX_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::RX_MAX_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_MIN_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::RX_MIN_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_CENTRE_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::RX_CENTRE_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_BANDWIDTH, limits, 1000.0) ;
	addMaxDoubleLimit(IRadioConfig::RX_BANDWIDTH, limits, MAX_FREQ) ;

	addMinIntLimit(IRadioConfig::NUM_SRX, limits, 0) ;
	addMaxIntLimit(IRadioConfig::NUM_SRX, limits, 256) ;
	addMinIntLimit(IRadioConfig::SRX_TX_PER_PORT, limits, 1) ;
	addMaxIntLimit(IRadioConfig::SRX_TX_PER_PORT, limits, 256) ;

	rc.setLimits(limits) ;
	EXPECT_EQ("", rc.error()) ;

	EXPECT_EQ(4, rc.intValue(IRadioConfig::NUM_CARRIERS)) ;

	EXPECT_EQ(4, rc.intValue(IRadioConfig::NUM_TX)) ;
	EXPECT_EQ(3800000.0, rc.doubleValue(IRadioConfig::TX_MAX_AIR_FREQ)) ;
	EXPECT_EQ(700000.0, rc.doubleValue(IRadioConfig::TX_MIN_AIR_FREQ)) ;

	std::string error;

	// try to set value below limit
	rc.setValue(IRadioConfig::NUM_CARRIERS, "0") ;
	error = rc.error() ;
	std::cerr << "Expected error: " << error << std::endl ;
	EXPECT_NE("", error) ;
	EXPECT_TRUE(error.find("below") != std::string::npos) ;

	// try to set value above limit
	rc.setValue(IRadioConfig::NUM_CARRIERS, "10000000") ;
	error = rc.error() ;
	std::cerr << "Expected error: " << error << std::endl ;
	EXPECT_NE("", error) ;
	EXPECT_TRUE(error.find("above") != std::string::npos) ;

	// try to set gibberish
	rc.setValue(IRadioConfig::NUM_CARRIERS, "gobbly goop") ;
	error = rc.error() ;
	std::cerr << "Expected error: " << error << std::endl ;
	EXPECT_NE("", error) ;
	EXPECT_TRUE(error.find("below") == std::string::npos) ;
	EXPECT_TRUE(error.find("above") == std::string::npos) ;


	addMinDoubleLimit(IRadioConfig::RX_MAX_FREQ, limits, 0.0) ;
	addMaxDoubleLimit(IRadioConfig::RX_MAX_FREQ, limits, MAX_FREQ) ;

	// try to set value below limit
	rc.setValue(IRadioConfig::RX_MAX_FREQ, "-10.0") ;
	error = rc.error() ;
	std::cerr << "Expected error: " << error << std::endl ;
	EXPECT_NE("", error) ;
	EXPECT_TRUE(error.find("below") != std::string::npos) ;

	// try to set value above limit
	rc.setValue(IRadioConfig::RX_MAX_FREQ, std::to_string(2.0*MAX_FREQ)) ;
	error = rc.error() ;
	std::cerr << "Expected error: " << error << std::endl ;
	EXPECT_NE("", error) ;
	EXPECT_TRUE(error.find("above") != std::string::npos) ;

	// try to set gibberish
	rc.setValue(IRadioConfig::RX_MAX_FREQ, "z1.2") ;
	error = rc.error() ;
	std::cerr << "Expected error: " << error << std::endl ;
	EXPECT_NE("", error) ;
	EXPECT_TRUE(error.find("below") == std::string::npos) ;
	EXPECT_TRUE(error.find("above") == std::string::npos) ;

}



//===================================================================================================================
