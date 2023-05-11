/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetDevice_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>

#include "NetDevice.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void display(NetDevice & nd)
{
	std::cerr << nd.getName() << ": " <<
		(nd.isUp() ? "UP " : "DOWN ") <<
		(nd.isBroadcast() ? "BROADCAST " : "") <<
		(nd.isMulticast() ? "MULTICAST " : "") <<
		std::endl ;
	if (nd.getMac().empty())
	{
		std::cerr << "MAC: Unknown" << std::endl ;
	}
	else
	{
		std::cerr << "MAC: " << nd.getMac() << " [" << nd.getMacFormatted() << "]" << std::endl ;
	}
	std::cerr << "IP: " << nd.getAddr() << std::endl ;
	std::cerr << "MASK: " << nd.getNetmask() << std::endl ;
	std::cerr << "BROADCAST: " << nd.getBroadcastAddr() << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(NetDevice, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	const std::string interfaceName = "lo";

	NetDevice nd (interfaceName);
	EXPECT_TRUE(nd.open(interfaceName)) ;

	display(nd);

	EXPECT_EQ(interfaceName, nd.getName()) ;
	EXPECT_TRUE(nd.isUp()) ;
	EXPECT_FALSE(nd.isBroadcast()) ;
	EXPECT_FALSE(nd.isMulticast()) ;
	EXPECT_TRUE(nd.getMac().empty()) ;
	EXPECT_EQ("127.0.0.1", nd.getAddr()) ;
	EXPECT_EQ("255.0.0.0", nd.getNetmask()) ;
	EXPECT_EQ("0.0.0.0", nd.getBroadcastAddr()) ;

	nd.close() ;
}
