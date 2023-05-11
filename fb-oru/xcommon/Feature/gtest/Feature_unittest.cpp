/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Feature_unittest.cpp
 * \brief     Google Test of Feature
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Feature class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>

#include "ByteTransfer.hpp"
#include "IKey.h"
#include "IFeature.h"

using namespace Mplane ;

static const std::string LICENSE("0a00b000c111d111e222f22933383337") ;

//-------------------------------------------------------------------------------------------------------------
TEST(Feature, SetBits)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IKey> key(IKey::factory()) ;
	EXPECT_TRUE(key->setLicenseKey(LICENSE)) ;


	std::shared_ptr<IFeature> feature(IFeature::factory(key, IFeature::FeatureType::LTE_TDD_TM)) ;

	feature->show() ;

	// Get bits
	IFeature::FeatureType features(feature->supportedFeatures()) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_TM) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_TM) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_FRCA) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_FRCA) != 0) ;

	// Check names
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_TM")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_FDD_TM")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_TDD_FRCA")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_FDD_FRCA")) ;

	// Enable
	EXPECT_TRUE(feature->enableFeature("LTE_FDD_TM")) ;
	EXPECT_TRUE(feature->enableFeature(IFeature::FeatureType::LTE_FDD_TM)) ;

	feature->show() ;

	features = feature->supportedFeatures() ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_TM) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_TM) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_FRCA) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_FRCA) != 0) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_FDD_TM")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_TDD_FRCA")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_FDD_FRCA")) ;

	EXPECT_FALSE(feature->enableFeature("dummy")) ;


	// Get encoded string
	std::string encoded(feature->encodeFeatures()) ;
	std::cout << "Encoded: " << encoded << std::endl ;
	EXPECT_EQ("ccc1e8b03bd9bcc10f5db1e535b69e3e", encoded) ;

	EXPECT_TRUE(feature->enableFeature("LTE_TDD_FRCA")) ;
	features = feature->supportedFeatures() ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_TM) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_TM) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_FRCA) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_FRCA) != 0) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_FDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_FRCA")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_FDD_FRCA")) ;

	EXPECT_TRUE(feature->enableFeature("LTE_FDD_FRCA")) ;
	features = feature->supportedFeatures() ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_TM) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_TM) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_FRCA) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_FRCA) != 0) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_FDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_FRCA")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_FDD_FRCA")) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(Feature, SetEncoded)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IKey> key(IKey::factory()) ;
	EXPECT_TRUE(key->setLicenseKey(LICENSE)) ;

	std::string encoded("ccc1e8b03bd9bcc10f5db1e535b69e3e") ;

	std::shared_ptr<IFeature> feature(IFeature::factory(key,encoded)) ;

	feature->show() ;

	IFeature::FeatureType features(feature->supportedFeatures()) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_TM) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_TM) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_FRCA) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_FRCA) != 0) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_FDD_TM")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_TDD_FRCA")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_FDD_FRCA")) ;

	// Rubbish
	EXPECT_FALSE( feature->checkSupported("xxx")) ;
	EXPECT_FALSE( feature->checkSupported("dummy")) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(Feature, SetInvalidEncoded)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IKey> key(IKey::factory()) ;
	EXPECT_TRUE(key->setLicenseKey(LICENSE)) ;

	std::string encoded("ccc1e8b03bd9bcc10f5db1e535b69e3f") ;

	std::shared_ptr<IFeature> feature(IFeature::factory(key,encoded)) ;
	EXPECT_FALSE(feature) ;

}
