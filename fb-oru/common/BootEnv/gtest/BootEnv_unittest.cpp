/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BootEnv_unittest.cpp
 * \brief     Google Test of BootEnv
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the BootEnv class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "BootEnvDevice.h"
#include "BootEnv.h"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(BootEnv, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<BootEnv> bootEnv( BootEnv::getInstance() ) ;
	bootEnv->reset() ;

	EXPECT_EQ(1u, bootEnv->getIndex()) ;
	EXPECT_TRUE( bootEnv->isVar("bootcmd") ) ;
	EXPECT_FALSE( bootEnv->isVar("xxx") ) ;

	EXPECT_TRUE( bootEnv->setVar("bootcmd", "run boot1") ) ;
	EXPECT_EQ(2u, bootEnv->getIndex()) ;
	EXPECT_EQ( "run boot1", bootEnv->getVar("bootcmd") ) ;

	EXPECT_TRUE( bootEnv->setVar("bootcmd", "run boot2") ) ;
	EXPECT_EQ(1u, bootEnv->getIndex()) ;
	EXPECT_EQ( "run boot2", bootEnv->getVar("bootcmd") ) ;

	EXPECT_TRUE( bootEnv->deleteVar("bootcmd") ) ;
	EXPECT_EQ(2u, bootEnv->getIndex()) ;
	EXPECT_FALSE( bootEnv->isVar("bootcmd") ) ;

	std::map<std::string, std::string> vars{
		{"bootcmd", "run boot3"},
		{"fred", "blogs"},
	};
	EXPECT_TRUE( bootEnv->setVar(vars) ) ;
	EXPECT_EQ(1u, bootEnv->getIndex()) ;
	EXPECT_TRUE( bootEnv->isVar("bootcmd") ) ;
	EXPECT_EQ( "run boot3", bootEnv->getVar("bootcmd") ) ;
	EXPECT_TRUE( bootEnv->isVar("fred") ) ;
	EXPECT_EQ( "blogs", bootEnv->getVar("fred") ) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(BootEnv, Banks)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<BootEnv> bootEnv( BootEnv::getInstance() ) ;
	bootEnv->reset() ;
	std::vector<std::shared_ptr<IBootEnvDevice>> devices(bootEnv->getDevices()) ;
	std::vector<std::shared_ptr<BootEnvDevice>> bdevices ;
	for (auto dev : devices)
	{
		std::cout << dev->getIndex() << " : " << dev->getDeviceName() <<
				" " << ( dev->isActive() ? "ACTIVE" : "INACTIVE" ) <<
				" " << ( dev->isValid() ? "VALID" : "INVALID" ) <<
				std::endl ;
		std::shared_ptr<BootEnvDevice> bdev(std::dynamic_pointer_cast<BootEnvDevice>(dev)) ;
		bdevices.push_back(bdev) ;
	}
	for (auto bdev : bdevices)
	{
		bdev->show() ;
	}
	EXPECT_EQ(1u, bootEnv->getIndex()) ;

	EXPECT_TRUE( devices[0]->isActive() ) ;
	EXPECT_EQ( 1u, devices[0]->getIndex() ) ;
	EXPECT_FALSE( devices[1]->isActive() ) ;
	EXPECT_EQ( 2u, devices[1]->getIndex() ) ;


	// clear inactive bank
	std::map<std::string, std::string> vars ;

	std::cerr << "** Clear inactive - device[1] **" << std::endl ;
	EXPECT_TRUE( devices[1]->resetVars(vars) ) ;
	EXPECT_TRUE( devices[1]->write() ) ;
	EXPECT_TRUE( bootEnv->isVar("bootcmd") ) ;
	EXPECT_FALSE( devices[1]->isVar("bootcmd") ) ;
	std::cerr << "device[0]: " ; bdevices[0]->show() ;
	std::cerr << "device[1]: " ; bdevices[1]->show() ;

	std::cerr << "** Read **" << std::endl ;
	bootEnv->read() ;
	devices = bootEnv->getDevices() ;
	bdevices.clear() ;
	for (auto dev : devices)
	{
		std::cout << dev->getIndex() << " : " << dev->getDeviceName() <<
				" " << ( dev->isActive() ? "ACTIVE" : "INACTIVE" ) <<
				" " << ( dev->isValid() ? "VALID" : "INVALID" ) <<
				std::endl ;
		std::shared_ptr<BootEnvDevice> bdev(std::dynamic_pointer_cast<BootEnvDevice>(dev)) ;
		bdevices.push_back(bdev) ;
	}

	std::cerr << "** Check **" << std::endl ;
	EXPECT_TRUE( bootEnv->isVar("bootcmd") ) ;
	EXPECT_FALSE( devices[1]->isVar("bootcmd") ) ;

	EXPECT_TRUE( bootEnv->setVar("bootcmd", "run boot2") ) ;
	EXPECT_EQ(2u, bootEnv->getIndex()) ;
	EXPECT_EQ( "run boot2", bootEnv->getVar("bootcmd") ) ;

	for (auto dev : devices)
	{
		std::cout << dev->getIndex() << " : " << dev->getDeviceName() <<
				" " << ( dev->isActive() ? "ACTIVE" : "INACTIVE" ) <<
				" " << ( dev->isValid() ? "VALID" : "INVALID" ) <<
				std::endl ;
	}

	EXPECT_TRUE( bootEnv->isVar("bootcmd") ) ;
	EXPECT_TRUE( devices[1]->isVar("bootcmd") ) ;
	EXPECT_EQ( "run boot2", devices[1]->getVar("bootcmd") ) ;
}
