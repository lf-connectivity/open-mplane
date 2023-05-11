/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GenericFeature_unittest.cpp
 * \brief     Google Test of GenericFeature
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the GenericFeature class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>

#include "ByteTransfer.hpp"
#include "IKey.h"
#include "IGenericFeature.h"

using namespace Mplane ;

static const std::string LICENSE("0a00b000c111d111e222f22933383337") ;

std::map<std::string, unsigned> FeatureNames{
	{"LTE_TDD_TM", 0},
	{"LTE_FDD_TM", 1},
	{"LTE_TDD_FRCA", 2},
	{"LTE_FDD_FRCA", 3},
	{"LTE_GUI_RX_BER", 31},
};

enum class TestFeatureType {
	NO_FEATURES		    = 0,
	LTE_TDD_TM			= 1<<0,
	LTE_FDD_TM			= 1<<1,
	LTE_TDD_FRCA		= 1<<2,
	LTE_FDD_FRCA		= 1<<3,

	// Client/GUI options persisted on the CART - do not affect the CART performance.
	LTE_GUI_RX_BER      = 1<<31
};

#define FEAT(nm)	static_cast<IGenericFeature::GenericFeatureType>(TestFeatureType::nm)

//-------------------------------------------------------------------------------------------------------------
TEST(GenericFeature, SetBits)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IKey> key(IKey::factory()) ;
	EXPECT_TRUE(key->setLicenseKey(LICENSE)) ;


	std::shared_ptr<IGenericFeature> feature(IGenericFeature::factory(FeatureNames, key,
			FEAT(LTE_TDD_TM))) ;

	feature->show() ;

	// Get bits
	IGenericFeature::GenericFeatureType features(feature->supportedFeatures()) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_TDD_TM)) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & FEAT(LTE_FDD_TM)) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & FEAT(LTE_TDD_FRCA)) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & FEAT(LTE_FDD_FRCA)) != 0) ;

	// Check names
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_TM")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_FDD_TM")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_TDD_FRCA")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_FDD_FRCA")) ;

	// Enable
	EXPECT_TRUE(feature->enableFeature("LTE_FDD_TM")) ;
	EXPECT_TRUE(feature->enableFeature(FEAT(LTE_FDD_TM))) ;

	feature->show() ;

	features = feature->supportedFeatures() ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_TDD_TM)) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_FDD_TM)) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & FEAT(LTE_TDD_FRCA)) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & FEAT(LTE_FDD_FRCA)) != 0) ;
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
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_TDD_TM)) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_FDD_TM)) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_TDD_FRCA)) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & FEAT(LTE_FDD_FRCA)) != 0) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_FDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_FRCA")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_FDD_FRCA")) ;

	EXPECT_TRUE(feature->enableFeature("LTE_FDD_FRCA")) ;
	features = feature->supportedFeatures() ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_TDD_TM)) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_FDD_TM)) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_TDD_FRCA)) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_FDD_FRCA)) != 0) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_FDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_FRCA")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_FDD_FRCA")) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(GenericFeature, SetEncoded)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IKey> key(IKey::factory()) ;
	EXPECT_TRUE(key->setLicenseKey(LICENSE)) ;

	std::string encoded("ccc1e8b03bd9bcc10f5db1e535b69e3e") ;

	std::shared_ptr<IGenericFeature> feature(IGenericFeature::factory(FeatureNames, key, encoded)) ;

	feature->show() ;

	IGenericFeature::GenericFeatureType features(feature->supportedFeatures()) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_TDD_TM)) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & FEAT(LTE_FDD_TM)) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & FEAT(LTE_TDD_FRCA)) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & FEAT(LTE_FDD_FRCA)) != 0) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_FDD_TM")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_TDD_FRCA")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_FDD_FRCA")) ;

	// Rubbish
	EXPECT_FALSE( feature->checkSupported("xxx")) ;
	EXPECT_FALSE( feature->checkSupported("dummy")) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(GenericFeature, SetInvalidEncoded)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IKey> key(IKey::factory()) ;
	EXPECT_TRUE(key->setLicenseKey(LICENSE)) ;

	std::string encoded("ccc1e8b03bd9bcc10f5db1e535b69e3f") ;

	std::shared_ptr<IGenericFeature> feature(IGenericFeature::factory(FeatureNames, key, encoded)) ;
	EXPECT_FALSE(feature) ;

}
