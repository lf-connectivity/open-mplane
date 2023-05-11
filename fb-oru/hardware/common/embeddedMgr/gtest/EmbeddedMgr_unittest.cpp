/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EmbeddedMgr_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "TestEmbeddedMgr.h"
#include "IEmbeddedMgr.h"

//#define GATHER_SEQUENCES
#include "EmbeddedMgr_fixture.h"


using namespace Mplane ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(EmbeddedMgrTestFixture, basic)
{
	std::shared_ptr<IEmbeddedMgr> mgr(IEmbeddedMgr::singleton()) ;
	std::vector<std::string> names(mgr->names()) ;
	EXPECT_EQ(2u, names.size()) ;
	EXPECT_EQ("R5-0", names[0]) ;
	EXPECT_EQ("R5-1", names[1]) ;

	std::cerr << "Firmware R5-0: " << mgr->firmware(0) << std::endl ;
	std::cerr << "Firmware R5-1: " << mgr->firmware(1) << std::endl ;

	EXPECT_EQ(std::string(TestEmbeddedMgr::testFirmwarePath() + "/r5-0-echo-test.bin"), mgr->firmware(0)) ;
	EXPECT_EQ(std::string(TestEmbeddedMgr::testFirmwarePath() + "/r5-1-echo-test.bin"), mgr->firmware(1)) ;

	EXPECT_EQ(std::string(TestEmbeddedMgr::testFirmwarePath() + "/r5-0-echo-test.bin"), mgr->firmware("R5-0")) ;
	EXPECT_EQ(std::string(TestEmbeddedMgr::testFirmwarePath() + "/r5-1-echo-test.bin"), mgr->firmware("R5-1")) ;

	EXPECT_EQ(0, mgr->procIndex("R5-0")) ;
	EXPECT_EQ(1, mgr->procIndex("R5-1")) ;

	EXPECT_EQ("R5-0", mgr->name(0)) ;
	EXPECT_EQ("R5-1", mgr->name(1)) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status(0)) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status(0)) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status("R5-0")) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status("R5-1")) ;

//	EXPECT_FALSE(mgr->setFirmware(0, "not-there")) ;
	EXPECT_EQ(std::string(TestEmbeddedMgr::testFirmwarePath() + "/r5-0-echo-test.bin"), mgr->firmware(0)) ;

//	EXPECT_TRUE(mgr->setFirmware(0, "r5-0-zzz.bin")) ;
//	EXPECT_EQ(std::string(TestEmbeddedMgr::testFirmwarePath() + "/r5-0-zzz.bin"), mgr->firmware(0)) ;

	EXPECT_TRUE(mgr->setFirmware("R5-0", "r5-0-echo-test.bin")) ;
	EXPECT_EQ(std::string(TestEmbeddedMgr::testFirmwarePath() + "/r5-0-echo-test.bin"), mgr->firmware(0)) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(EmbeddedMgrTestFixture, run)
{
	std::shared_ptr<IEmbeddedMgr> mgr(IEmbeddedMgr::singleton()) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status(0)) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status(0)) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status("R5-0")) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status("R5-1")) ;

	EXPECT_TRUE(mgr->loadFirmware(0)) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_RUNNING, mgr->status(0)) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status(1)) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_RUNNING, mgr->status("R5-0")) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status("R5-1")) ;

	EXPECT_TRUE(mgr->loadFirmware("R5-1")) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_RUNNING, mgr->status(0)) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_RUNNING, mgr->status(1)) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_RUNNING, mgr->status("R5-0")) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_RUNNING, mgr->status("R5-1")) ;

	EXPECT_TRUE(mgr->stop("R5-0")) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status(0)) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_RUNNING, mgr->status(1)) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status("R5-0")) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_RUNNING, mgr->status("R5-1")) ;

	EXPECT_TRUE(mgr->stop(1)) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status(0)) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status(0)) ;

	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status("R5-0")) ;
	EXPECT_EQ(IEmbeddedMgr::PROC_OFFLINE, mgr->status("R5-1")) ;

}
