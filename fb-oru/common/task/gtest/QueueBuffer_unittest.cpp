/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QueueBuffer_unittest.cpp
 * \brief     Google Test of QueueBuffer
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the QueueBuffer class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <queue>
#include <memory>
#include "QueueBuffer.hpp"

using namespace Mplane;

using namespace std;

std::queue<std::string> result ;

static void setResult(const std::string& entry)
{
	result.push(entry) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(QueueBuffer, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::vector<std::string> source ;
	for (unsigned idx=0; idx < 100; ++idx)
	{
		std::string str("Entry " + std::to_string(idx)) ;
		source.push_back(str) ;
	}

	std::shared_ptr<QueueBuffer<std::string>> qb(new QueueBuffer<std::string>([](const std::string& entry){setResult(entry);})) ;

	// send all
	for (auto entry : source)
		qb->add(entry) ;

	// wait for data to complete
	sleep(1) ;

	// Check
	EXPECT_EQ(source.size(), result.size()) ;
	if (source.size() != result.size())
		return ;

	unsigned idx(0) ;
	while (!result.empty())
	{
		EXPECT_EQ(source[idx], result.front()) ;
		result.pop() ;
		++idx ;
	}



}
