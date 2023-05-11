/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultBuilder_unittest.cpp
 * \brief     Google Test of FaultBuilder
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FaultBuilder class.
 *
 */

#include <gtest/gtest.h>

#include "FaultTest.h"

using namespace Mplane;

using namespace std;


//-------------------------------------------------------------------------------------------------------------
TEST(FaultBuilder, Simple)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	EXPECT_EQ(0, faultsList->getSize()) ;

	// Create the builder
	std::shared_ptr<IFaultBuilder> faultPackage(std::make_shared<FaultBuilder1>()) ;
	EXPECT_EQ(2, faultsList->getSize()) ;

	// get hold of the faults/owner for testing
	std::shared_ptr<IFault> faultA(faultsList->getFault("FaultA")) ;
	std::shared_ptr<IFault> faultB(faultsList->getFault("FaultB")) ;
	std::shared_ptr<IFaultOwner> faultOwner1(faultsList->getFaultOwner("FaultOwner1")) ;
	std::shared_ptr<FaultOwner1> fOwner1(std::dynamic_pointer_cast<FaultOwner1>(faultOwner1)) ;

	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// set 1
	fOwner1->mState = true ;
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// set 2
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// set 3
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// set 4
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	// set 5
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	faultsList->show() ;

	// clear 1
	fOwner1->mState = false ;
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	// clear 2
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	// clear 3
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	// clear 4
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	// clear 5
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	faultsList->show() ;

	EXPECT_EQ(2, faultsList->getSize()) ;


	// Tidy up
	std::cerr << "TIDY UP" << std::endl ;
	std::shared_ptr<FaultsList> fList(std::dynamic_pointer_cast<FaultsList>(faultsList)) ;
	fList->removeFault(faultA->getName()) ;
	fList->removeFault(faultB->getName()) ;
	fList->removeFaultOwner(faultOwner1->getName()) ;
}
