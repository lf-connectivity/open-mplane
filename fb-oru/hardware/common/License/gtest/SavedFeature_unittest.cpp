/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SavedFeature_unittest.cpp
 * \brief     Google Test of SavedFeature
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the SavedFeature class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "IBootEnv.h"
#include "SavedFeature.h"

using namespace Mplane;

static const std::string LICENSE("0a00b000c111d111e222f22933383337") ;

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFeature> IFeature::getInstance()
{
	return SavedFeature::getInstance() ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SavedFeature, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IBootEnv> bootenv( IBootEnv::getInstance() ) ;
	bootenv->setVar("FEATURE", "") ;

	std::shared_ptr<IFeature> feature( IFeature::getInstance() ) ;

	EXPECT_FALSE( feature->isSet() ) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SavedFeature, Set)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IBootEnv> bootenv( IBootEnv::getInstance() ) ;
	bootenv->setVar("FEATURE", "") ;

	// Ensure Key singleton is set up
	std::shared_ptr<IKey> license( IKey::getApplicationInstance() ) ;
	// SavedKey: 0a00b000c111d111e222f22933383337 Encoded: 23ba946004a0f43d2d1a0a47481fb16b
	license->setFromEncodedKey("23ba946004a0f43d2d1a0a47481fb16b") ;

	// Can now use feature
	std::shared_ptr<IFeature> feature( IFeature::getInstance() ) ;

	EXPECT_FALSE( feature->isSet() ) ;

	std::string encoded("ccc1e8b03bd9bcc10f5db1e535b69e3e") ;
	feature->setFeatures(encoded) ;
	EXPECT_TRUE( feature->isSet() ) ;
	EXPECT_TRUE( bootenv->isVar("FEATURE") ) ;
	EXPECT_EQ(encoded, bootenv->getVar("FEATURE")) ;

	// Get bits
	IFeature::FeatureType features(feature->supportedFeatures()) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_TM) != 0) ;
	EXPECT_TRUE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_TM) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_TDD_FRCA) != 0) ;
	EXPECT_FALSE( static_cast<uint32_t>(features & IFeature::FeatureType::LTE_FDD_FRCA) != 0) ;
	EXPECT_TRUE( feature->checkSupported("LTE_TDD_TM")) ;
	EXPECT_TRUE( feature->checkSupported("LTE_FDD_TM")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_TDD_FRCA")) ;
	EXPECT_FALSE( feature->checkSupported("LTE_FDD_FRCA")) ;


	// Should be able to create a new feature that loads the encoded key now saved in the (dummy) boot env
	std::shared_ptr<IFeature> feature2( std::make_shared<SavedFeature>() ) ;
	EXPECT_TRUE( feature2->isSet() ) ;
}
