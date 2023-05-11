/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Networking_unittest.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "NetAddrLinkLocal.h"
#include "IpPortMgr.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

// TODO: Should really get this from the IpPortMgr ?
const std::string IP_PORT_PATH("/tmp/nandflash/.settings/ip-ports") ;
const std::string IP_PORT_PATH_BACKUP(IP_PORT_PATH + ".bak") ;

//-------------------------------------------------------------------------------------------------------------
TEST(NetAddr, LinkLocal)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<INetAddr> ll(std::make_shared<NetAddrLinkLocal>("ens33", 5000)) ;

	INetAddr::NetAddrStatus status = ll->start() ;
	std::cerr << "Status=" << status << " ip=" << ll->ipAddress() << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(NetAddr, IpPortMgr)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	// remove any previous
	if (Path::exists(IP_PORT_PATH))
	{
		Path::move(IP_PORT_PATH, IP_PORT_PATH_BACKUP) ;
	}

	IpPortMgr ipMgr ;

	std::vector<std::pair<std::string, unsigned>> NULL_LIST ;
	std::vector<std::pair<std::string, unsigned>> VALUES{
		{"1.2.3.4", 830},
		{"11.22.33.44", 789},
		{"some-address", 456},
	} ;
	std::vector<std::pair<std::string, unsigned>> VALUES2{
		{"10.20.30.40", 49500},
		{"another-address", 5555},
	} ;

	EXPECT_EQ(NULL_LIST, ipMgr.list()) ;

	ipMgr.setList(VALUES) ;
	EXPECT_EQ(VALUES, ipMgr.list()) ;
	ipMgr.restore() ;
	EXPECT_EQ(NULL_LIST, ipMgr.list()) ;

	ipMgr.setList(VALUES) ;
	EXPECT_EQ(VALUES, ipMgr.list()) ;
	EXPECT_TRUE(ipMgr.save()) ;
	ipMgr.restore() ;
	EXPECT_EQ(VALUES, ipMgr.list()) ;

	ipMgr.setList(VALUES2) ;
	EXPECT_EQ(VALUES2, ipMgr.list()) ;
	ipMgr.restore() ;
	EXPECT_EQ(VALUES, ipMgr.list()) ;


	ipMgr.clear() ;
	EXPECT_EQ(NULL_LIST, ipMgr.list()) ;


	for (auto pair : VALUES)
	{
		ipMgr.addEntry(pair.first, pair.second) ;
	}
	EXPECT_EQ(VALUES, ipMgr.list()) ;

	ipMgr.clear() ;
	ipMgr.save() ;
	EXPECT_EQ(NULL_LIST, ipMgr.list()) ;


	// restore previous
	if (Path::exists(IP_PORT_PATH_BACKUP))
	{
		Path::move(IP_PORT_PATH_BACKUP, IP_PORT_PATH) ;
	}

}
