/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Md5List_unittest.cpp
 * \brief     Google Test of Md5List
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Md5List class.
 *
 */

#include <unistd.h>
#include <limits.h>

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "IAppSettingsFactory.h"
#include "AppSettings.h"

#include "Path.h"
#include "Md5List.h"

#include "im_fixture.h"

using namespace Mplane;

using namespace std;

// Relative to new build run dir
const std::string testPath("../../../imageManagement/gtest/test/") ;

//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST(Md5List, Tests)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	WorkingDir::chdirWd() ;

	std::cerr << "testPath=" << testPath << std::endl ;
	char buff[PATH_MAX] ;
	std::string cwd(getcwd(buff, sizeof(buff))) ;
	std::cerr << "working directory: " << cwd << std::endl ;

	// Create some instances
	// 1a=1b, 2a is 1a with different MD5, 3a is different list, X does no exist
	Md5List file1a(testPath + "file1a.md5list") ;
	Md5List file1b(testPath + "file1b.md5list") ;
	Md5List file2a(testPath + "file2a.md5list") ;
	Md5List file3a(testPath + "file3a.md5list") ;
	Md5List fileX(testPath + "fileX.md5list") ;

	EXPECT_TRUE(file1a == file1a) ;
	EXPECT_TRUE(file1b == file1b) ;
	EXPECT_TRUE(file2a == file2a) ;
	EXPECT_TRUE(file3a == file3a) ;
	EXPECT_FALSE(fileX == fileX) ;

	EXPECT_TRUE(file1a == file1b) ;
	EXPECT_TRUE(file1b == file1a) ;
	EXPECT_FALSE(file1a == file2a) ;
	EXPECT_FALSE(file2a == file1b) ;
	EXPECT_FALSE(file1a == file3a) ;
	EXPECT_FALSE(file1a == fileX) ;
}
