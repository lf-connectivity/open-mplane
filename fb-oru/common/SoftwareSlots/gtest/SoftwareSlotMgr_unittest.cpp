/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwareSlotMgr_unittest.cpp
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

#include "Path.h"

#include "TestConstants.h"
#include "SoftwarePackage.h"
#include "SoftwareSlot.h"
#include "SoftwareSlotMgr.h"

using namespace Mplane ;


//=============================================================================================================
// LOCAL
//=============================================================================================================

namespace {

	void clearLinks()
	{
		// make sure there are no links
		Path::remove(TestConstants::TESTDIR + "/app-images/current");
		Path::remove(TestConstants::TESTDIR + "/app-images/previous");

		std::vector<std::string> links(Path::dirContents(TestConstants::TESTDIR + "/sw-mgmt/invalid")) ;
		for (auto f : links)
		{
			if (Path::isLink(f))
				Path::remove(f) ;
		}

		links = Path::dirContents(TestConstants::TESTDIR + "/sw-mgmt/slots") ;
		for (auto f : links)
		{
			if (Path::isLink(f))
				Path::remove(f) ;
		}
	}
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST(SoftwareSlotMgr, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	std::shared_ptr<ISoftwareSlotMgr> mgr(std::make_shared<SoftwareSlotMgr>(8,
			TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images",
			TestConstants::TESTDIR + "/os-images")) ;
	mgr->show() ;

	std::vector< std::shared_ptr<ISoftwareSlot> > slots(mgr->slots()) ;
	EXPECT_EQ(8u, slots.size()) ;

	// make sure there are no links
	clearLinks() ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(SoftwareSlotMgr, Clean)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	// set up slots
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/slots/slot1",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt") ;
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/slots/slot2",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.5-241-manifest.txt") ;
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/slots/slot3",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.6-250-manifest.txt") ;


	std::shared_ptr<ISoftwareSlotMgr> mgr(std::make_shared<SoftwareSlotMgr>(4,
			TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images",
			TestConstants::TESTDIR + "/os-images")) ;
	mgr->show() ;


	// Create some files that should be deleted after a clean()
	EXPECT_TRUE(Path::fileCopy(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.6-250-APP.tgz", TestConstants::TESTDIR + "/app-images/app.delete1.tgz") );
	EXPECT_TRUE(Path::fileCopy(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.6-250-APP.tgz.md5", TestConstants::TESTDIR + "/app-images/app.delete1.tgz.md5") );
	EXPECT_TRUE(Path::fileCopy(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.6-250-APP.tgz", TestConstants::TESTDIR + "/app-images/app.delete2.tgz") );
	EXPECT_TRUE(Path::fileCopy(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.6-250-APP.tgz.md5", TestConstants::TESTDIR + "/app-images/app.delete2.tgz.md5") );

	EXPECT_TRUE(Path::fileCopy(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz", TestConstants::TESTDIR + "/os-images/os.delete1.tgz") );
	EXPECT_TRUE(Path::fileCopy(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz.md5", TestConstants::TESTDIR + "/os-images/os.delete1.tgz.md5") );


	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz.md5")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.5-241-APP.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.5-241-APP.tgz.md5")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.6-250-APP.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.6-250-APP.tgz.md5")) ;

	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/app.delete1.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/app.delete1.tgz.md5")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/app.delete2.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/app.delete2.tgz.md5")) ;

	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz.md5")) ;

	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/os-images/os.delete1.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/os-images/os.delete1.tgz.md5")) ;


	std::string error ;
	EXPECT_TRUE(mgr->clean(error)) ;
	EXPECT_TRUE(error.empty()) ;


	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz.md5")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.5-241-APP.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.5-241-APP.tgz.md5")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.6-250-APP.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.6-250-APP.tgz.md5")) ;

	EXPECT_FALSE(Path::isFile(TestConstants::TESTDIR + "/app-images/delete1.tgz")) ;
	EXPECT_FALSE(Path::isFile(TestConstants::TESTDIR + "/app-images/delete1.tgz.md5")) ;
	EXPECT_FALSE(Path::isFile(TestConstants::TESTDIR + "/app-images/delete2.tgz")) ;
	EXPECT_FALSE(Path::isFile(TestConstants::TESTDIR + "/app-images/delete2.tgz.md5")) ;

	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz")) ;
	EXPECT_TRUE(Path::isFile(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz.md5")) ;

	EXPECT_FALSE(Path::isFile(TestConstants::TESTDIR + "/os-images/os.delete1.tgz")) ;
	EXPECT_FALSE(Path::isFile(TestConstants::TESTDIR + "/os-images/os.delete1.tgz.md5")) ;



	// make sure there are no links
	clearLinks() ;

}
