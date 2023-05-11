/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SavedKey_unittest.cpp
 * \brief     Google Test of SavedKey
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the SavedKey class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "IBootEnv.h"
#include "SavedKey.h"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IKey> IKey::getApplicationInstance()
{
	return SavedKey::getInstance() ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SavedKey, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IBootEnv> bootenv( IBootEnv::getInstance() ) ;
	bootenv->setVar("LICENSE", "") ;

	std::shared_ptr<IKey> license( IKey::getApplicationInstance() ) ;
	license->clear() ;

	EXPECT_FALSE( license->isSet() ) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SavedKey, Set)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IBootEnv> bootenv( IBootEnv::getInstance() ) ;
	bootenv->setVar("LICENSE", "") ;

	std::shared_ptr<IKey> license( IKey::getApplicationInstance() ) ;
	license->clear() ;

	EXPECT_FALSE( license->isSet() ) ;

	// SavedKey: 0a00b000c111d111e222f22933383337 Encoded: 23ba946004a0f43d2d1a0a47481fb16b
	std::string encodedKey("23ba946004a0f43d2d1a0a47481fb16b") ;
	license->setFromEncodedKey(encodedKey) ;
	EXPECT_TRUE( license->isSet() ) ;
	EXPECT_TRUE( bootenv->isVar("LICENSE") ) ;
	EXPECT_EQ(encodedKey, bootenv->getVar("LICENSE")) ;

	// Should be able to create a new license that loads the encoded key now saved in the (dummy) boot env
	std::shared_ptr<IKey> license2( std::make_shared<SavedKey>() ) ;
	EXPECT_TRUE( license2->isSet() ) ;
}
