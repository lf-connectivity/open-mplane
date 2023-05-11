/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PathUtils_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>

#ifdef _MSC_VER
#define RMDIR    ::_rmdir
#define UNLINK   ::_unlink
#define RELPATH  "..\\.."
#else
#include <unistd.h>
#define RMDIR    ::rmdir
#define UNLINK   ::unlink
#define RELPATH  "../../.."
#endif

#include "gtest/gtest.h"

#include "PathUtils.h"

using namespace Mplane ;

//===================================================================================================================
class PathUtilsTest : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
    	const ::testing::TestInfo* const test_info =
    	  ::testing::UnitTest::GetInstance()->current_test_info();

    	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    	std::cout << test_info->name() << " - START" <<  std::endl;

    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {

    }


};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, exists)
{
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/a_dir")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/b_dir")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/c_dir")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/a_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/b_file")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/c_file")) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, isDir)
{
	EXPECT_TRUE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/a_dir")) ;
	EXPECT_TRUE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/b_dir")) ;
	EXPECT_FALSE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/c_dir")) ;
	EXPECT_FALSE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/a_file")) ;
	EXPECT_FALSE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/b_file")) ;
	EXPECT_FALSE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/c_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, isFile)
{
	EXPECT_FALSE(PathUtils::isFile(RELPATH "/PathUtils/gtest/test/a_dir")) ;
	EXPECT_FALSE(PathUtils::isFile(RELPATH "/PathUtils/gtest/test/b_dir")) ;
	EXPECT_FALSE(PathUtils::isFile(RELPATH "/PathUtils/gtest/test/c_dir")) ;

	EXPECT_TRUE(PathUtils::isFile(RELPATH "/PathUtils/gtest/test/a_file")) ;
	EXPECT_TRUE(PathUtils::isFile(RELPATH "/PathUtils/gtest/test/b_file")) ;
	EXPECT_FALSE(PathUtils::isFile(RELPATH "/PathUtils/gtest/test/c_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, isLink)
{
#ifndef _MSC_VER
	EXPECT_FALSE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/a_dir")) ;
	EXPECT_FALSE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/b_dir")) ;
	EXPECT_FALSE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/c_dir")) ;

	EXPECT_FALSE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/a_file")) ;
	EXPECT_FALSE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/b_file")) ;
	EXPECT_FALSE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/c_file")) ;
#endif
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, basename)
{
	EXPECT_EQ(std::string("a_dir"), PathUtils::basename(RELPATH "/PathUtils/gtest/test/a_dir")) ;
	EXPECT_EQ(std::string("b_dir"), PathUtils::basename(RELPATH "/PathUtils/gtest/test/b_dir")) ;
	EXPECT_EQ(std::string("a_file"), PathUtils::basename("/test/a_file")) ;
	EXPECT_EQ(std::string("b_file"), PathUtils::basename("/b_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, directory)
{
	EXPECT_EQ(PathUtils::sanitisePath(RELPATH "/PathUtils/gtest/test/"), PathUtils::dir(RELPATH "/PathUtils/gtest/test/a_dir")) ;
	EXPECT_EQ(PathUtils::sanitisePath(RELPATH "/PathUtils/gtest/test/"), PathUtils::dir(RELPATH "/PathUtils/gtest/test/b_dir")) ;
	EXPECT_EQ(PathUtils::sanitisePath("/test/"), PathUtils::dir("/test/a_file")) ;
	EXPECT_EQ(PathUtils::sanitisePath("/"), PathUtils::dir("/b_file")) ;
	EXPECT_EQ(PathUtils::sanitisePath(""), PathUtils::dir("b_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, join)
{
	EXPECT_EQ(PathUtils::sanitisePath(RELPATH "/PathUtils/gtest/test/a_dir"), PathUtils::join(RELPATH "/PathUtils/gtest/test", "a_dir")) ;
	EXPECT_EQ(PathUtils::sanitisePath(RELPATH "/PathUtils/gtest/test/a_dir"), PathUtils::join(RELPATH "/PathUtils/gtest/test/", "a_dir")) ;
	EXPECT_EQ(PathUtils::sanitisePath("/test/a_file"), PathUtils::join("/test/", "a_file")) ;
	EXPECT_EQ(PathUtils::sanitisePath("/test/a_file"), PathUtils::join("/test", "a_file")) ;
	EXPECT_EQ(PathUtils::sanitisePath("/b_file"), PathUtils::join("", "/b_file")) ;
	EXPECT_EQ(PathUtils::sanitisePath("b_file"), PathUtils::join("", "b_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, extension)
{
	EXPECT_EQ(std::string(".tgz"), PathUtils::extension(RELPATH "/PathUtils/gtest/test/a_file.tgz")) ;
	EXPECT_EQ(std::string(".md5"), PathUtils::extension(RELPATH "/PathUtils/gtest/test/a_file.tgz.md5")) ;
	EXPECT_EQ(std::string(""), PathUtils::extension(RELPATH "/PathUtils/gtest/test/a_file")) ;
	EXPECT_EQ(std::string(""), PathUtils::extension("a_file")) ;
	EXPECT_EQ(std::string(""), PathUtils::extension("")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, dirContents)
{
	std::vector<std::string> contents(PathUtils::dirContents(RELPATH "/PathUtils/gtest/test")) ;

	std::copy(contents.begin(), contents.end(),
	        std::ostream_iterator<std::string>(std::cout, "\n"));

	std::vector<std::string> expected ;
	expected.push_back(RELPATH "/PathUtils/gtest/test/a_dir") ;
	expected.push_back(RELPATH "/PathUtils/gtest/test/b_dir") ;
	expected.push_back(RELPATH "/PathUtils/gtest/test/a_file") ;
	expected.push_back(RELPATH "/PathUtils/gtest/test/b_file") ;
	expected.push_back(RELPATH "/PathUtils/gtest/test/file1.txt") ;
	expected.push_back(RELPATH "/PathUtils/gtest/test/file2.txt") ;
	expected.push_back(RELPATH "/PathUtils/gtest/test/file3.txt") ;

	EXPECT_EQ(expected.size(), contents.size()) ;

	std::sort(contents.begin(), contents.end()) ;
	std::sort(expected.begin(), expected.end()) ;
//	for (unsigned idx=0; idx < expected.size(); ++idx)
//	{
//		EXPECT_EQ(expected[idx], contents[idx]) ;
//	}
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, fileCopyFile)
{
	EXPECT_TRUE(PathUtils::fileCopy(RELPATH "/PathUtils/gtest/test/a_file", RELPATH "/PathUtils/gtest/test/c_file"));
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/c_file")) ;
	EXPECT_FALSE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/c_file")) ;

#ifndef _MSC_VER
	EXPECT_EQ(0, system("diff " RELPATH "/PathUtils/gtest/test/a_file " RELPATH "/PathUtils/gtest/test/c_file")) ;
#endif
	UNLINK(RELPATH "/PathUtils/gtest/test/c_file") ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, fileCopyDir)
{
	EXPECT_EQ(0, PathUtils::mkdir(RELPATH "/PathUtils/gtest/test/c_dir")) ;
	EXPECT_TRUE(PathUtils::fileCopy(RELPATH "/PathUtils/gtest/test/a_file", RELPATH "/PathUtils/gtest/test/c_dir")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/c_dir/a_file")) ;
	EXPECT_FALSE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/c_dir/a_file")) ;

#ifndef _MSC_VER
	EXPECT_EQ(0, system("diff " RELPATH "/PathUtils/gtest/test/a_file " RELPATH "/PathUtils/gtest/test/c_dir/a_file")) ;
#endif
	UNLINK(RELPATH "/PathUtils/gtest/test/c_dir/a_file") ;
	RMDIR(RELPATH "/PathUtils/gtest/test/c_dir") ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, mkdir)
{
	EXPECT_EQ(0, PathUtils::mkdir(RELPATH "/PathUtils/gtest/test/c_dir")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/c_dir")) ;
	EXPECT_TRUE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/c_dir")) ;
	RMDIR(RELPATH "/PathUtils/gtest/test/c_dir");
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, rmdir)
{
	EXPECT_EQ(0, PathUtils::mkdir(RELPATH "/PathUtils/gtest/test/c_dir")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/c_dir")) ;
	EXPECT_TRUE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/c_dir")) ;
	EXPECT_EQ(0, PathUtils::rmdir(RELPATH "/PathUtils/gtest/test/c_dir"));

	EXPECT_EQ(-1, PathUtils::rmdir(RELPATH "/PathUtils/gtest/test/c_dir"));
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, mkpath)
{
	EXPECT_EQ(0, PathUtils::mkpath(RELPATH "/PathUtils/gtest/test/c_dir/dir1/dir2")) ;

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/c_dir")) ;
	EXPECT_TRUE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/c_dir")) ;

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/c_dir/dir1")) ;
	EXPECT_TRUE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/c_dir/dir1")) ;

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/c_dir/dir1/dir2")) ;
	EXPECT_TRUE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/c_dir/dir1/dir2")) ;


	EXPECT_EQ(0, PathUtils::rmdir(RELPATH "/PathUtils/gtest/test/c_dir/dir1/dir2"));
	EXPECT_EQ(0, PathUtils::rmdir(RELPATH "/PathUtils/gtest/test/c_dir/dir1"));
	EXPECT_EQ(0, PathUtils::rmdir(RELPATH "/PathUtils/gtest/test/c_dir"));
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, mkpathLinked)
{
#ifndef _MSC_VER

	system("ln -sf a_dir " RELPATH "/PathUtils/gtest/test/x_dir");

	EXPECT_EQ(0, PathUtils::mkpath(RELPATH "/PathUtils/gtest/test/x_dir/dir1/dir2")) ;

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir")) ;
	EXPECT_TRUE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/x_dir")) ;

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/dir1")) ;
	EXPECT_TRUE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/x_dir/dir1")) ;

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/dir1/dir2")) ;
	EXPECT_TRUE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/x_dir/dir1/dir2")) ;


	EXPECT_EQ(0, PathUtils::rmdir(RELPATH "/PathUtils/gtest/test/x_dir/dir1/dir2"));
	EXPECT_EQ(0, PathUtils::rmdir(RELPATH "/PathUtils/gtest/test/x_dir/dir1"));
	EXPECT_EQ(0, PathUtils::remove(RELPATH "/PathUtils/gtest/test/x_dir"));
#endif
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, remove)
{
	EXPECT_TRUE(PathUtils::fileCopy(RELPATH "/PathUtils/gtest/test/a_file", RELPATH "/PathUtils/gtest/test/xx_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/xx_file")) ;
	EXPECT_FALSE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/xx_file")) ;
	EXPECT_EQ(0, PathUtils::remove(RELPATH "/PathUtils/gtest/test/xx_file")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/xx_file")) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, move)
{
	EXPECT_TRUE(PathUtils::fileCopy(RELPATH "/PathUtils/gtest/test/a_file", RELPATH "/PathUtils/gtest/test/xx_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/xx_file")) ;
	EXPECT_FALSE(PathUtils::isDir(RELPATH "/PathUtils/gtest/test/xx_file")) ;

	EXPECT_EQ(0, PathUtils::move(RELPATH "/PathUtils/gtest/test/xx_file", RELPATH "/PathUtils/gtest/test/yy_file")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/xx_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/yy_file")) ;
	EXPECT_EQ(0, PathUtils::remove(RELPATH "/PathUtils/gtest/test/yy_file")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/yy_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, links)
{
#ifndef _MSC_VER
	system("ln -sf " RELPATH "/PathUtils/gtest/test/a_file " RELPATH "/PathUtils/gtest/test/a_link");
	system("ln -sf " RELPATH "/PathUtils/gtest/test/b_file " RELPATH "/PathUtils/gtest/test/b_link");

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/a_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/b_file")) ;

	EXPECT_FALSE(PathUtils::isFile(RELPATH "/PathUtils/gtest/test/a_link")) ;
	EXPECT_FALSE(PathUtils::isFile(RELPATH "/PathUtils/gtest/test/b_link")) ;

	EXPECT_TRUE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/a_link")) ;
	EXPECT_TRUE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/b_link")) ;

	std::string link ;
	EXPECT_TRUE(PathUtils::readLink(RELPATH "/PathUtils/gtest/test/a_link", link)) ;
	EXPECT_EQ(std::string(RELPATH "/PathUtils/gtest/test/a_file"), link) ;
	std::cerr << "a link=" << link << std::endl ;
	EXPECT_TRUE(PathUtils::readLink(RELPATH "/PathUtils/gtest/test/b_link", link)) ;
	EXPECT_EQ(std::string(RELPATH "/PathUtils/gtest/test/b_file"), link) ;
	std::cerr << "b link=" << link << std::endl ;
	EXPECT_FALSE(PathUtils::readLink(RELPATH "/PathUtils/gtest/test/c_link", link)) ;
	EXPECT_EQ(std::string(""), link) ;
	std::cerr << "c link=" << link << std::endl ;

	EXPECT_EQ(0, remove(RELPATH "/PathUtils/gtest/test/a_link")) ;
	EXPECT_EQ(0, remove(RELPATH "/PathUtils/gtest/test/b_link")) ;

	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/a_link")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/b_link")) ;


	// Use createLink
	EXPECT_TRUE(PathUtils::createLink(RELPATH "/PathUtils/gtest/test/a_link", "../test/a_file"));
	EXPECT_TRUE(PathUtils::createLink(RELPATH "/PathUtils/gtest/test/b_link", "b_file"));

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/a_link")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/b_link")) ;

	EXPECT_FALSE(PathUtils::isFile(RELPATH "/PathUtils/gtest/test/a_link")) ;
	EXPECT_FALSE(PathUtils::isFile(RELPATH "/PathUtils/gtest/test/b_link")) ;

	EXPECT_TRUE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/a_link")) ;
	EXPECT_TRUE(PathUtils::isLink(RELPATH "/PathUtils/gtest/test/b_link")) ;

	EXPECT_TRUE(PathUtils::readLink(RELPATH "/PathUtils/gtest/test/a_link", link)) ;
	EXPECT_EQ(std::string("../test/a_file"), link) ;
	std::cerr << "a link=" << link << std::endl ;
	EXPECT_TRUE(PathUtils::readLink(RELPATH "/PathUtils/gtest/test/b_link", link)) ;
	EXPECT_EQ(std::string("b_file"), link) ;
	std::cerr << "b link=" << link << std::endl ;
	EXPECT_FALSE(PathUtils::readLink(RELPATH "/PathUtils/gtest/test/c_link", link)) ;
	EXPECT_EQ(std::string(""), link) ;
	std::cerr << "c link=" << link << std::endl ;

	EXPECT_EQ(0, remove(RELPATH "/PathUtils/gtest/test/a_link")) ;
	EXPECT_EQ(0, remove(RELPATH "/PathUtils/gtest/test/b_link")) ;

	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/a_link")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/b_link")) ;
#endif
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, fileSize)
{
	EXPECT_EQ(8259u, PathUtils::fileSize(RELPATH "/PathUtils/gtest/test/a_dir/size8259.txt")) ;
	EXPECT_EQ(15u, PathUtils::fileSize(RELPATH "/PathUtils/gtest/test/a_file")) ;
	EXPECT_EQ(19u, PathUtils::fileSize(RELPATH "/PathUtils/gtest/test/b_file")) ;
	EXPECT_EQ(0u, PathUtils::fileSize(RELPATH "/PathUtils/gtest/test/not_there")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, freeSpace)
{
#ifndef _MSC_VER
	EXPECT_EQ(0ULL, PathUtils::freeSpace(RELPATH "/PathUtils/gtest/test/a_dir/not_there")) ;
	EXPECT_NE(0ULL, PathUtils::freeSpace(RELPATH "/PathUtils/gtest/test/a_file")) ;

	std::cerr << "Free space on current disk: " << PathUtils::freeSpace(RELPATH "/PathUtils/gtest/test/a_file") << std::endl ;
#endif
}



//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, removeDirContents)
{
	EXPECT_EQ(0, PathUtils::mkpath(RELPATH "/PathUtils/gtest/test/x_dir/a/b")) ;
	EXPECT_EQ(0, PathUtils::mkpath(RELPATH "/PathUtils/gtest/test/x_dir/c")) ;
	EXPECT_EQ(0, PathUtils::mkpath(RELPATH "/PathUtils/gtest/test/x_dir/d")) ;

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/b")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/c")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/d")) ;

#ifndef _MSC_VER
	EXPECT_TRUE(PathUtils::createLink(RELPATH "/PathUtils/gtest/test/x_dir/a_link", "../a_file"));
	EXPECT_TRUE(PathUtils::createLink(RELPATH "/PathUtils/gtest/test/x_dir/a/a_link", "../../a_file"));
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a_link")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/a_link")) ;
#endif

	EXPECT_TRUE(PathUtils::fileCopy(RELPATH "/PathUtils/gtest/test/a_file", RELPATH "/PathUtils/gtest/test/x_dir/a_file")) ;
	EXPECT_TRUE(PathUtils::fileCopy(RELPATH "/PathUtils/gtest/test/a_file", RELPATH "/PathUtils/gtest/test/x_dir/a/a_file")) ;
	EXPECT_TRUE(PathUtils::fileCopy(RELPATH "/PathUtils/gtest/test/a_file", RELPATH "/PathUtils/gtest/test/x_dir/a/b/a_file")) ;
	EXPECT_TRUE(PathUtils::fileCopy(RELPATH "/PathUtils/gtest/test/a_file", RELPATH "/PathUtils/gtest/test/x_dir/c/a_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/a_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/b/a_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/c/a_file")) ;

	// non-recursive delete
	EXPECT_TRUE(PathUtils::removeDirContents(RELPATH "/PathUtils/gtest/test/x_dir")) ;

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/b")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/c")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/d")) ;
#ifndef _MSC_VER
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a_link")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/a_link")) ;
#endif
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/a_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/b/a_file")) ;
	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/c/a_file")) ;

	// recursive delete
	EXPECT_TRUE(PathUtils::removeDirContents(RELPATH "/PathUtils/gtest/test/x_dir", true)) ;

	EXPECT_TRUE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/b")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/c")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/d")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a_link")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/a_link")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a_file")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/a_file")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/a/b/a_file")) ;
	EXPECT_FALSE(PathUtils::exists(RELPATH "/PathUtils/gtest/test/x_dir/c/a_file")) ;

	// should now be able to remove empty dir
	EXPECT_EQ(0, PathUtils::rmdir(RELPATH "/PathUtils/gtest/test/x_dir")) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathUtilsTest, fileDiff)
{
	// should be the same excluding header
	EXPECT_FALSE(PathUtils::filesDifferent(RELPATH "/PathUtils/gtest/test/file1.txt", RELPATH "/PathUtils/gtest/test/file2.txt", 9)) ;
	EXPECT_TRUE(PathUtils::filesDifferent(RELPATH "/PathUtils/gtest/test/file1.txt", RELPATH "/PathUtils/gtest/test/file2.txt", 8)) ;
	EXPECT_TRUE(PathUtils::filesDifferent(RELPATH "/PathUtils/gtest/test/file2.txt", RELPATH "/PathUtils/gtest/test/file3.txt", 9)) ;

	EXPECT_TRUE(PathUtils::filesDifferent(RELPATH "/PathUtils/gtest/test/file2.txt", RELPATH "/PathUtils/gtest/test/not_there.txt")) ;
	EXPECT_TRUE(PathUtils::filesDifferent(RELPATH "/PathUtils/gtest/test/not_there.txt", RELPATH "/PathUtils/gtest/test/file1.txt")) ;
	EXPECT_TRUE(PathUtils::filesDifferent(RELPATH "/PathUtils/gtest/test/not_there.txt", RELPATH "/PathUtils/gtest/test/not_there.txt")) ;

	// skip all lines and they should match!
	EXPECT_FALSE(PathUtils::filesDifferent(RELPATH "/PathUtils/gtest/test/file1.txt", RELPATH "/PathUtils/gtest/test/file2.txt", 100)) ;

	// these are different lengths so will never match
	EXPECT_TRUE(PathUtils::filesDifferent(RELPATH "/PathUtils/gtest/test/file2.txt", RELPATH "/PathUtils/gtest/test/file3.txt", 100)) ;
}


//===================================================================================================================
