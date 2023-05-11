/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fault_unittest.cpp
 * \brief     Google Test of Fault
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Fault class.
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
TEST(Fault, Simple)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	EXPECT_EQ(0, faultsList->getSize()) ;

	std::shared_ptr<IFault> faultA(make_fault<FaultA>()) ;
	std::shared_ptr<IFault> faultB(make_fault<FaultB>()) ;
	EXPECT_EQ(2, faultsList->getSize()) ;

	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// set 1
	faultA->setStatus(true) ;
	faultB->setStatus(true) ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// set 2
	faultA->setStatus(true) ;
	faultB->setStatus(true) ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// set 3
	faultA->setStatus(true) ;
	faultB->setStatus(true) ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// set 4
	faultA->setStatus(true) ;
	faultB->setStatus(true) ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	// set 5
	faultA->setStatus(true) ;
	faultB->setStatus(true) ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;



	// clear 1
	faultA->setStatus(false) ;
	faultB->setStatus(false) ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	// clear 2
	faultA->setStatus(false) ;
	faultB->setStatus(false) ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	// clear 3
	faultA->setStatus(false) ;
	faultB->setStatus(false) ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	// clear 4
	faultA->setStatus(false) ;
	faultB->setStatus(false) ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;

	// clear 5
	faultA->setStatus(false) ;
	faultB->setStatus(false) ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;


	std::cerr << "Fault A: " << faultA->getName() << std::endl ;
	std::cerr << "Fault B: " << faultB->getName() << std::endl ;
	EXPECT_EQ(2, faultsList->getSize()) ;


	// Check list
	std::cerr << "Check list start" << std::endl ;
	for (auto name : std::vector<std::string>{"FaultA", "FaultB"})
	{
		std::shared_ptr<IFault> fault(faultsList->getFault(name)) ;
		std::cerr << "fault: " << fault->getName() << std::endl ;
	}
	for (auto name : std::vector<std::string>{"FaultA", "FaultB"})
	{
		std::shared_ptr<IFault> fault(faultsList->getFault(name)) ;
		std::cerr << "fault: " << fault->getName() << std::endl ;
	}
	std::cerr << "Check list end" << std::endl ;

	// Tidy up
	std::shared_ptr<FaultsList> fList(std::dynamic_pointer_cast<FaultsList>(faultsList)) ;
	fList->removeFault(faultA->getName()) ;
	fList->removeFault(faultB->getName()) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(Fault, Integrate)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	EXPECT_EQ(0, faultsList->getSize()) ;

	std::shared_ptr<IFault> faultC(make_fault<FaultC>()) ;
	EXPECT_EQ(1, faultsList->getSize()) ;

	EXPECT_FALSE(faultC->isFaultPresent()) ;


	// set 1
	faultC->setStatus(true) ;
	EXPECT_FALSE(faultC->isFaultPresent()) ;

	// set 2
	faultC->setStatus(true) ;
	EXPECT_FALSE(faultC->isFaultPresent()) ;

	// clear 1
	faultC->setStatus(false) ;
	EXPECT_FALSE(faultC->isFaultPresent()) ;



	// set 1
	faultC->setStatus(true) ;
	EXPECT_FALSE(faultC->isFaultPresent()) ;

	// set 2
	faultC->setStatus(true) ;
	EXPECT_FALSE(faultC->isFaultPresent()) ;

	// set 3
	faultC->setStatus(true) ;
	EXPECT_TRUE(faultC->isFaultPresent()) ;


	// FAULT PRESENT

	// clear 1
	faultC->setStatus(false) ;
	EXPECT_TRUE(faultC->isFaultPresent()) ;

	// clear 2
	faultC->setStatus(false) ;
	EXPECT_TRUE(faultC->isFaultPresent()) ;

	// clear 3
	faultC->setStatus(false) ;
	EXPECT_TRUE(faultC->isFaultPresent()) ;

	// clear 4
	faultC->setStatus(false) ;
	EXPECT_TRUE(faultC->isFaultPresent()) ;

	faultC->setStatus(true) ;
	EXPECT_TRUE(faultC->isFaultPresent()) ;


	// clear 1
	faultC->setStatus(false) ;
	EXPECT_TRUE(faultC->isFaultPresent()) ;

	// clear 2
	faultC->setStatus(false) ;
	EXPECT_TRUE(faultC->isFaultPresent()) ;

	// clear 3
	faultC->setStatus(false) ;
	EXPECT_TRUE(faultC->isFaultPresent()) ;

	// clear 4
	faultC->setStatus(false) ;
	EXPECT_TRUE(faultC->isFaultPresent()) ;

	// clear 5
	faultC->setStatus(false) ;
	EXPECT_FALSE(faultC->isFaultPresent()) ;


	std::cerr << "Fault C: " << faultC->getName() << std::endl ;
	EXPECT_EQ(1, faultsList->getSize()) ;

	// Tidy up
	std::shared_ptr<FaultsList> fList(std::dynamic_pointer_cast<FaultsList>(faultsList)) ;
	fList->removeFault(faultC->getName()) ;

}
