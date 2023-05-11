/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultOwner_unittest.cpp
 * \brief     Google Test of FaultOwner
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FaultOwner class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "IFault.h"
#include "IFaultOwner.h"
#include "IFaultsList.h"

#include "Fault.h"
#include "FaultsList.h"
#include "FaultOwner.h"

#include "FaultTest.h"

using namespace Mplane;

using namespace std;


//-------------------------------------------------------------------------------------------------------------
TEST(FaultOwner, Simple)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	EXPECT_EQ(0, faultsList->getSize()) ;

	std::shared_ptr<IFault> faultA(make_fault<FaultA>()) ;
	std::shared_ptr<IFault> faultB(make_fault<FaultB>()) ;
	std::shared_ptr<IFault> faultC(make_fault<FaultC>()) ;


	std::cerr << "FaultA ref=" << faultA.use_count() << std::endl ;
	std::cerr << "FaultB ref=" << faultB.use_count() << std::endl ;
	std::cerr << "FaultC ref=" << faultC.use_count() << std::endl ;

	EXPECT_EQ(3, faultsList->getSize()) ;

	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

std::cerr << "Creating FaultOwner" << std::endl ;

	// Create owner
	std::shared_ptr<IFaultOwner> faultOwner1(make_faultOwner<FaultOwner1>()) ;
	std::shared_ptr<FaultOwner1> fOwner1(std::dynamic_pointer_cast<FaultOwner1>(faultOwner1)) ;

	std::cerr << "FaultA ref=" << faultA.use_count() << std::endl ;
	std::cerr << "FaultB ref=" << faultB.use_count() << std::endl ;
	std::cerr << "FaultC ref=" << faultC.use_count() << std::endl ;

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
	faultsList->showNamesAndIds() ;

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
	faultsList->showNamesAndIds() ;

	std::cerr << "Fault A: Name - " << faultA->getName() << " Id - " << faultA->getId() << std::endl ;
	std::cerr << "Fault B: Name - " << faultB->getName() << " Id - " << faultB->getId()  << std::endl ;
	EXPECT_EQ(3, faultsList->getSize()) ;

	std::shared_ptr<IFault> fault ;
	fault = faultsList->getFault("FaultA") ;
	EXPECT_EQ("FaultA", fault->getName()) ;
	fault = faultsList->getFault("FaultB") ;
	EXPECT_EQ("FaultB", fault->getName()) ;
	fault = faultsList->getFault("FaultC") ;
	EXPECT_EQ("FaultC", fault->getName()) ;

	std::shared_ptr<IFaultOwner> faultOwner ;
	faultOwner = faultsList->getFaultOwner("FaultOwner1") ;
	EXPECT_EQ("FaultOwner1", faultOwner->getName()) ;

	// Tidy up
	std::cerr << "TIDY UP" << std::endl ;
	std::shared_ptr<FaultsList> fList(std::dynamic_pointer_cast<FaultsList>(faultsList)) ;
	fList->removeFault(faultA->getName()) ;
	fList->removeFault(faultB->getName()) ;
	fList->removeFault(faultC->getName()) ;
	fList->removeFaultOwner(faultOwner1->getName()) ;
}
