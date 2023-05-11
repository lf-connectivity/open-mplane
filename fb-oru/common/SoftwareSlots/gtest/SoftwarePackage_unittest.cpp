/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwarePackage_unittest.cpp
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

	}
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST(SoftwarePackage, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	//
	SoftwarePackage sp("x", "x", "x", "x") ;
	EXPECT_FALSE(sp.isValid()) ;

	// make sure there are no links
	clearLinks() ;

	//
	SoftwarePackage sp1(TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt") ;

	sp1.show() ;

	EXPECT_TRUE(sp1.isValid()) ;
	EXPECT_FALSE(sp1.isRunning()) ;

	EXPECT_EQ("FB", sp1.vendorCode()) ;
	EXPECT_EQ("FBOR-12345678", sp1.productCode()) ;
	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.4#240", sp1.buildName()) ;
	EXPECT_EQ("240", sp1.buildId()) ;
	EXPECT_EQ("1.0.0.4", sp1.buildVersion()) ;

	EXPECT_EQ("os.ZCU111-local-123-0.0.tgz", sp1.osFileName()) ;
	EXPECT_EQ("0.0", sp1.osFileVersion()) ;
	EXPECT_EQ(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz", sp1.osPath()) ;
	EXPECT_EQ("993b9a047b5f0b2c9235ded1d6e0c0fc", sp1.osChecksum()) ;
	EXPECT_TRUE(sp1.osIntegrity()) ;

	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz", sp1.appFileName()) ;
	EXPECT_EQ("1.0.0.4", sp1.appFileVersion()) ;
	EXPECT_EQ(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz", sp1.appPath()) ;
	EXPECT_EQ("76b645e28b0b53122b4428f4ab9eb4b9", sp1.appChecksum()) ;
	EXPECT_TRUE(sp1.appIntegrity()) ;


	//
	SoftwarePackage sp2(TestConstants::TESTDIR + "/sw-mgmt", TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.5-241-manifest.txt") ;

	sp2.show() ;

	EXPECT_TRUE(sp2.isValid()) ;
	EXPECT_FALSE(sp2.isRunning()) ;

	EXPECT_EQ("FB", sp2.vendorCode()) ;
	EXPECT_EQ("FBOR-12345678", sp2.productCode()) ;
	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.5#241", sp2.buildName()) ;
	EXPECT_EQ("241", sp2.buildId()) ;

	EXPECT_EQ("os.ZCU111-local-123-0.0.tgz", sp2.osFileName()) ;
	EXPECT_EQ("0.0", sp2.osFileVersion()) ;
	EXPECT_EQ(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz", sp2.osPath()) ;
	EXPECT_EQ("993b9a047b5f0b2c9235ded1d6e0c0fc", sp2.osChecksum()) ;
	EXPECT_TRUE(sp2.osIntegrity()) ;

	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.5-241-APP.tgz", sp2.appFileName()) ;
	EXPECT_EQ("1.0.0.5", sp2.appFileVersion()) ;
	EXPECT_EQ(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.5-241-APP.tgz", sp2.appPath()) ;
	EXPECT_EQ("3aa011ba1be270375c45875c2ed7426f", sp2.appChecksum()) ;
	EXPECT_TRUE(sp2.appIntegrity()) ;




	//
	SoftwarePackage sp3(TestConstants::TESTDIR + "/sw-mgmt", TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.6-250-manifest.txt") ;

	sp3.show() ;

	EXPECT_TRUE(sp3.isValid()) ;


}


//-------------------------------------------------------------------------------------------------------------
TEST(SoftwarePackage, BadChecksum)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	//
	SoftwarePackage sp1(TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-BAD-manifest.txt") ;

	sp1.show() ;

	EXPECT_FALSE(sp1.isValid()) ;
	EXPECT_FALSE(sp1.isRunning()) ;

	EXPECT_EQ("FB", sp1.vendorCode()) ;
	EXPECT_EQ("FBOR-12345678", sp1.productCode()) ;
	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.4#240", sp1.buildName()) ;
	EXPECT_EQ("240", sp1.buildId()) ;

	EXPECT_EQ("os.ZCU111-local-123-0.0.tgz", sp1.osFileName()) ;
	EXPECT_EQ("0.0", sp1.osFileVersion()) ;
	EXPECT_EQ(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz", sp1.osPath()) ;
	EXPECT_EQ("00000000000000000000000000000000", sp1.osChecksum()) ;
	EXPECT_FALSE(sp1.osIntegrity()) ;

	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz", sp1.appFileName()) ;
	EXPECT_EQ("1.0.0.4", sp1.appFileVersion()) ;
	EXPECT_EQ(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz", sp1.appPath()) ;
	EXPECT_EQ("76b645e28b0b53122b4428f4ab9eb4b9", sp1.appChecksum()) ;
	EXPECT_TRUE(sp1.appIntegrity()) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(SoftwarePackage, Running)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	//
	SoftwarePackage sp("x", "x", "x", "x") ;
	EXPECT_FALSE(sp.isValid()) ;

	// make 1.0.0.4-240 the current running app
	std::string cmd( std::string("ln -sf ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz ") + TestConstants::TESTDIR + "/app-images/current") ;
	system(cmd.c_str()) ;

	//
	SoftwarePackage sp1(TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt") ;

	sp1.show() ;

	EXPECT_TRUE(sp1.isValid()) ;
	EXPECT_TRUE(sp1.isRunning()) ;

	EXPECT_EQ("FB", sp1.vendorCode()) ;
	EXPECT_EQ("FBOR-12345678", sp1.productCode()) ;
	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.4#240", sp1.buildName()) ;
	EXPECT_EQ("240", sp1.buildId()) ;

	EXPECT_EQ("os.ZCU111-local-123-0.0.tgz", sp1.osFileName()) ;
	EXPECT_EQ("0.0", sp1.osFileVersion()) ;
	EXPECT_EQ(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz", sp1.osPath()) ;
	EXPECT_EQ("993b9a047b5f0b2c9235ded1d6e0c0fc", sp1.osChecksum()) ;
	EXPECT_TRUE(sp1.osIntegrity()) ;

	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz", sp1.appFileName()) ;
	EXPECT_EQ("1.0.0.4", sp1.appFileVersion()) ;
	EXPECT_EQ(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz", sp1.appPath()) ;
	EXPECT_EQ("76b645e28b0b53122b4428f4ab9eb4b9", sp1.appChecksum()) ;
	EXPECT_TRUE(sp1.appIntegrity()) ;


	//
	SoftwarePackage sp2(TestConstants::TESTDIR + "/sw-mgmt", TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.5-241-manifest.txt") ;

	sp2.show() ;

	EXPECT_TRUE(sp2.isValid()) ;
	EXPECT_FALSE(sp2.isRunning()) ;

	EXPECT_EQ("FB", sp2.vendorCode()) ;
	EXPECT_EQ("FBOR-12345678", sp2.productCode()) ;
	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.5#241", sp2.buildName()) ;
	EXPECT_EQ("241", sp2.buildId()) ;
	EXPECT_EQ("1.0.0.5", sp2.buildVersion()) ;

	EXPECT_EQ("os.ZCU111-local-123-0.0.tgz", sp2.osFileName()) ;
	EXPECT_EQ("0.0", sp2.osFileVersion()) ;
	EXPECT_EQ(TestConstants::TESTDIR + "/os-images/os.ZCU111-local-123-0.0.tgz", sp2.osPath()) ;
	EXPECT_EQ("993b9a047b5f0b2c9235ded1d6e0c0fc", sp2.osChecksum()) ;
	EXPECT_TRUE(sp2.osIntegrity()) ;

	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.5-241-APP.tgz", sp2.appFileName()) ;
	EXPECT_EQ("1.0.0.5", sp2.appFileVersion()) ;
	EXPECT_EQ(TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.5-241-APP.tgz", sp2.appPath()) ;
	EXPECT_EQ("3aa011ba1be270375c45875c2ed7426f", sp2.appChecksum()) ;
	EXPECT_TRUE(sp2.appIntegrity()) ;


	// make sure there are no links
	clearLinks() ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(SoftwarePackage, Active)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	//
	SoftwarePackage sp1(TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt") ;

	sp1.show() ;
	EXPECT_FALSE(sp1.isActive()) ;

	// make 1.0.0.4-240 the current running app
	Path::createLink(TestConstants::TESTDIR + "/app-images/current",
			TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz") ;

	sp1.show() ;
	EXPECT_TRUE(sp1.isActive()) ;

	// make sure there are no links
	clearLinks() ;


}



//-------------------------------------------------------------------------------------------------------------
TEST(SoftwarePackage, InvalidityLinks)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	// Create some invalidity links
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/invalid/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz",
			TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz") ;
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/invalid/not-real.tgz",
			TestConstants::TESTDIR + "/app-images/not-real.tgz") ;

	// make 1.0.0.4-240 the current running app - this means that the above invalidty link is broken so should be removed
	Path::createLink(TestConstants::TESTDIR + "/app-images/current",
			TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz") ;

	//
	SoftwarePackage sp1(TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt") ;

	sp1.show() ;
	EXPECT_TRUE(sp1.isActive()) ;
	EXPECT_TRUE(sp1.isValid()) ;

	// links should have been removed
	EXPECT_FALSE(Path::exists(TestConstants::TESTDIR + "/sw-mgmt/invalid/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz")) ;
	EXPECT_FALSE(Path::exists(TestConstants::TESTDIR + "/sw-mgmt/invalid/not-real.tgz")) ;

	// make sure there are no links
	clearLinks() ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(SoftwarePackage, InvalidityLinks2)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	// Create some invalidity links
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/invalid/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz",
			TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz") ;
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/invalid/not-real.tgz",
			TestConstants::TESTDIR + "/app-images/not-real.tgz") ;

	//
	SoftwarePackage sp1(TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt") ;

	sp1.show() ;
	EXPECT_FALSE(sp1.isActive()) ;
	EXPECT_FALSE(sp1.isValid()) ;

	// broken link should have been removed
	EXPECT_TRUE(Path::exists(TestConstants::TESTDIR + "/sw-mgmt/invalid/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz")) ;
	EXPECT_FALSE(Path::exists(TestConstants::TESTDIR + "/sw-mgmt/invalid/not-real.tgz")) ;

	// make sure there are no links
	clearLinks() ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(SoftwarePackage, BadManifestCommon)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	//
	SoftwarePackage sp1(TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-BAD-COMMON-manifest.txt") ;

	sp1.show() ;

	EXPECT_FALSE(sp1.isValid()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SoftwarePackage, BadManifestApp)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	//
	SoftwarePackage sp1(TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-BAD-APP-manifest.txt") ;

	sp1.show() ;

	EXPECT_FALSE(sp1.isValid()) ;
}
