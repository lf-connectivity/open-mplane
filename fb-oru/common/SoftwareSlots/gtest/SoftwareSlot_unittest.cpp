/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwareSlot_unittest.cpp
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
TEST(SoftwareSlot, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	// unsigned slotNumber, const std::string& mgmtPath, const std::string& appsPath
	SoftwareSlot slot1("slot1",
			TestConstants::TESTDIR + "/sw-mgmt") ;

	slot1.show() ;

	EXPECT_FALSE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_FALSE(slot1.isActive()) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(SoftwareSlot, Package)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	// unsigned slotNumber, const std::string& mgmtPath, const std::string& appsPath
	SoftwareSlot slot1("slot1",
			TestConstants::TESTDIR + "/sw-mgmt") ;

	slot1.show() ;

	EXPECT_FALSE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_FALSE(slot1.isActive()) ;

	// Add a package
	std::shared_ptr<SoftwarePackage> sp1( std::make_shared<SoftwarePackage>(TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt") ) ;

//	sp1->show() ;

	slot1.allocatePackage(sp1) ;
	EXPECT_TRUE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_FALSE(slot1.isActive()) ;

	std::cerr << "Allocated package..." << std::endl ;
	slot1.show() ;

	// make this package active
	Path::createLink(TestConstants::TESTDIR + "/app-images/current",
			TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz") ;

	std::cerr << "After creating link..." << std::endl ;
	slot1.show() ;

	// Should now show as active
	EXPECT_TRUE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_TRUE(slot1.isActive()) ;

	// make sure there are no links
	clearLinks() ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(SoftwareSlot, RunningPackage)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	// unsigned slotNumber, const std::string& mgmtPath, const std::string& appsPath
	SoftwareSlot slot1("slot1",
			TestConstants::TESTDIR + "/sw-mgmt") ;

	slot1.show() ;

	EXPECT_FALSE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_FALSE(slot1.isActive()) ;

	// make this package active
	Path::createLink(TestConstants::TESTDIR + "/app-images/current",
			TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz") ;


	// Add a package
	std::shared_ptr<SoftwarePackage> sp1( std::make_shared<SoftwarePackage>(TestConstants::TESTDIR + "/sw-mgmt",
			TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt") ) ;

	slot1.allocatePackage(sp1) ;
	EXPECT_TRUE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_TRUE(slot1.isRunning()) ;
	EXPECT_TRUE(slot1.isActive()) ;

	std::cerr << "Allocated package..." << std::endl ;
	slot1.show() ;


	EXPECT_TRUE(slot1.setReadOnly(true)) ;

	std::cerr << "Read only..." << std::endl ;
	slot1.show() ;

	EXPECT_TRUE(slot1.isValid()) ;
	EXPECT_TRUE(slot1.isReadOnly()) ;
	EXPECT_TRUE(slot1.isRunning()) ;
	EXPECT_TRUE(slot1.isActive()) ;


	EXPECT_TRUE(slot1.setReadOnly(false)) ;

	std::cerr << "Not Read only..." << std::endl ;
	slot1.show() ;

	EXPECT_TRUE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_TRUE(slot1.isRunning()) ;
	EXPECT_TRUE(slot1.isActive()) ;




	// make sure there are no links
	Path::remove(TestConstants::TESTDIR + "/app-images/current");
	Path::remove(TestConstants::TESTDIR + "/app-images/previous");

	std::cerr << "Removed current..." << std::endl ;
	slot1.show() ;

	EXPECT_TRUE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_TRUE(slot1.isRunning()) ;
	EXPECT_FALSE(slot1.isActive()) ;


	clearLinks() ;

}




//-------------------------------------------------------------------------------------------------------------
TEST(SoftwareSlot, Init)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	// Create packages
	std::vector<std::shared_ptr<ISoftwarePackage>> packages ;
	for (auto manifest : std::vector<std::string>{
		"ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt",
		"ZCU111-FBC-ORANRRH-1.0.0.5-241-manifest.txt",
		"ZCU111-FBC-ORANRRH-1.0.0.6-250-manifest.txt",

	}) {
		std::shared_ptr<SoftwarePackage> sp( std::make_shared<SoftwarePackage>(TestConstants::TESTDIR + "/sw-mgmt",
				TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
				TestConstants::TESTDIR + "/sw-mgmt/manifests/" + manifest) ) ;

		packages.push_back(sp) ;
	}



	SoftwareSlot slot1("slot1",
			TestConstants::TESTDIR + "/sw-mgmt") ;

	SoftwareSlot slot2("slot2",
			TestConstants::TESTDIR + "/sw-mgmt") ;

	SoftwareSlot slot3("slot3",
			TestConstants::TESTDIR + "/sw-mgmt") ;

	slot1.show() ;
	slot2.show() ;
	slot3.show() ;

	EXPECT_FALSE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isAllocated()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_FALSE(slot1.isActive()) ;

	EXPECT_FALSE(slot2.isValid()) ;
	EXPECT_FALSE(slot2.isAllocated()) ;
	EXPECT_FALSE(slot2.isReadOnly()) ;
	EXPECT_FALSE(slot2.isRunning()) ;
	EXPECT_FALSE(slot2.isActive()) ;

	EXPECT_FALSE(slot3.isValid()) ;
	EXPECT_FALSE(slot3.isAllocated()) ;
	EXPECT_FALSE(slot3.isReadOnly()) ;
	EXPECT_FALSE(slot3.isRunning()) ;
	EXPECT_FALSE(slot3.isActive()) ;

	// make this package active
	Path::createLink(TestConstants::TESTDIR + "/app-images/current",
			TestConstants::TESTDIR + "/app-images/ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz") ;

	// set up slots
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/slots/slot1",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt") ;
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/slots/slot2",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.5-241-manifest.txt") ;
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/slots/slot3",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.6-250-manifest.txt") ;

	// Initialise
	slot1.initialise(packages) ;
	slot2.initialise(packages) ;
	slot3.initialise(packages) ;

	std::cerr << "Initialised..." << std::endl ;
	slot1.show() ;

	EXPECT_TRUE(slot1.isValid()) ;
	EXPECT_TRUE(slot1.isAllocated()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_TRUE(slot1.isActive()) ;
	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.4#240", slot1.package()->buildName()) ;

	EXPECT_TRUE(slot2.isValid()) ;
	EXPECT_TRUE(slot2.isAllocated()) ;
	EXPECT_FALSE(slot2.isReadOnly()) ;
	EXPECT_FALSE(slot2.isRunning()) ;
	EXPECT_FALSE(slot2.isActive()) ;
	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.5#241", slot2.package()->buildName()) ;

	EXPECT_TRUE(slot3.isValid()) ;
	EXPECT_TRUE(slot3.isAllocated()) ;
	EXPECT_FALSE(slot3.isReadOnly()) ;
	EXPECT_FALSE(slot3.isRunning()) ;
	EXPECT_FALSE(slot3.isActive()) ;
	EXPECT_EQ("ZCU111-FBC-ORANRRH-1.0.0.6#250", slot3.package()->buildName()) ;




	// make sure there are no links
	clearLinks() ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(SoftwareSlot, InitBadLink1)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	// Create packages
	std::vector<std::shared_ptr<ISoftwarePackage>> packages ;
	for (auto manifest : std::vector<std::string>{
		"ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt",
		"ZCU111-FBC-ORANRRH-1.0.0.5-241-manifest.txt",
		"ZCU111-FBC-ORANRRH-1.0.0.6-250-manifest.txt",

	}) {
		std::shared_ptr<SoftwarePackage> sp( std::make_shared<SoftwarePackage>(TestConstants::TESTDIR + "/sw-mgmt",
				TestConstants::TESTDIR + "/app-images", TestConstants::TESTDIR + "/os-images",
				TestConstants::TESTDIR + "/sw-mgmt/manifests/" + manifest) ) ;

		packages.push_back(sp) ;
	}



	SoftwareSlot slot1("slot1",
			TestConstants::TESTDIR + "/sw-mgmt") ;


	slot1.show() ;

	EXPECT_FALSE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isAllocated()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_FALSE(slot1.isActive()) ;


	// Invalid link
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/slots/slot1",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest-not-there.txt") ;
	EXPECT_TRUE(Path::exists(TestConstants::TESTDIR + "/sw-mgmt/slots/slot1")) ;

	// Initialise
	slot1.initialise(packages) ;

	std::cerr << "Initialised..." << std::endl ;
	slot1.show() ;

	EXPECT_FALSE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isAllocated()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_FALSE(slot1.isActive()) ;

	// Link should be removed
	EXPECT_FALSE(Path::exists(TestConstants::TESTDIR + "/sw-mgmt/slots/slot1")) ;


	// make sure there are no links
	clearLinks() ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(SoftwareSlot, InitNoPackages)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// make sure there are no links
	clearLinks() ;

	// Create packages
	std::vector<std::shared_ptr<ISoftwarePackage>> packages ;

	SoftwareSlot slot1("slot1",
			TestConstants::TESTDIR + "/sw-mgmt") ;

	EXPECT_FALSE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isAllocated()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_FALSE(slot1.isActive()) ;

	// set up slots
	Path::createLink(TestConstants::TESTDIR + "/sw-mgmt/slots/slot1",
			TestConstants::TESTDIR + "/sw-mgmt/manifests/ZCU111-FBC-ORANRRH-1.0.0.4-240-manifest.txt") ;
	EXPECT_TRUE(Path::exists(TestConstants::TESTDIR + "/sw-mgmt/slots/slot1")) ;

	// Initialise
	slot1.initialise(packages) ;

	std::cerr << "Initialised..." << std::endl ;
	slot1.show() ;

	EXPECT_FALSE(slot1.isValid()) ;
	EXPECT_FALSE(slot1.isAllocated()) ;
	EXPECT_FALSE(slot1.isReadOnly()) ;
	EXPECT_FALSE(slot1.isRunning()) ;
	EXPECT_FALSE(slot1.isActive()) ;

	// Link should be removed
	EXPECT_FALSE(Path::exists(TestConstants::TESTDIR + "/sw-mgmt/slots/slot1")) ;


	// make sure there are no links
	clearLinks() ;

}
