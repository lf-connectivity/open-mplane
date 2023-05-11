/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SftpPath_unittest.cpp
 * \brief     Google Test of SftpPath
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the SftpPath class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <regex>

#include <memory>
#include "SftpPath.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, Valid)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://sprice@swin-12/O-RAN/log") ;

	EXPECT_TRUE(sp.isValid()) ;
	EXPECT_EQ(std::string("sprice"), sp.user()) ;
	EXPECT_EQ(std::string("swin-12"), sp.host()) ;
	EXPECT_EQ(std::string("O-RAN/log"), sp.path()) ;
	EXPECT_EQ(0u, sp.port()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, ValidPath)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://sprice@swin-12/O-RAN/log/subdir") ;

	EXPECT_TRUE(sp.isValid()) ;
	EXPECT_EQ(std::string("sprice"), sp.user()) ;
	EXPECT_EQ(std::string("swin-12"), sp.host()) ;
	EXPECT_EQ(std::string("O-RAN/log/subdir"), sp.path()) ;
	EXPECT_EQ(0u, sp.port()) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, ValidPort)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://sprice@swin-12:22/O-RAN/log") ;

	EXPECT_TRUE(sp.isValid()) ;
	EXPECT_EQ(std::string("sprice"), sp.user()) ;
	EXPECT_EQ(std::string("swin-12"), sp.host()) ;
	EXPECT_EQ(std::string("O-RAN/log"), sp.path()) ;
	EXPECT_EQ(22u, sp.port()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, ValidNoScheme)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sprice@swin-12/O-RAN/log") ;

	EXPECT_TRUE(sp.isValid()) ;
	EXPECT_EQ(std::string("sprice"), sp.user()) ;
	EXPECT_EQ(std::string("swin-12"), sp.host()) ;
	EXPECT_EQ(std::string("O-RAN/log"), sp.path()) ;
	EXPECT_EQ(0u, sp.port()) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidScheme)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("http://sprice@swin-12/O-RAN/log") ;

	EXPECT_FALSE(sp.isValid()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidUser)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://sprice-swin-12/O-RAN/log") ;

	EXPECT_FALSE(sp.isValid()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidUser2)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://@swin-12/O-RAN/log") ;

	EXPECT_FALSE(sp.isValid()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidUser3)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://user:pass@swin-12/O-RAN/log") ;

	EXPECT_FALSE(sp.isValid()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidUser4)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://user/pass@swin-12/O-RAN/log") ;

	EXPECT_FALSE(sp.isValid()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidHost)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://sprice@/O-RAN/log") ;

	EXPECT_FALSE(sp.isValid()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidHost2)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://sprice@host@other/O-RAN/log") ;

	EXPECT_FALSE(sp.isValid()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidPath)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://sprice@swin-12/") ;

	EXPECT_FALSE(sp.isValid()) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidPath2)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://sprice@swin-12") ;

	EXPECT_FALSE(sp.isValid()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidPath3)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://sprice@swin-12/path@path") ;

	EXPECT_FALSE(sp.isValid()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SftpPath, InValidPath4)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	SftpPath sp("sftp://sprice@swin-12/path:path") ;

	EXPECT_FALSE(sp.isValid()) ;
}
