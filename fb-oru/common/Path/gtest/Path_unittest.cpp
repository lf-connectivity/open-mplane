/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      language_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>

#include <unistd.h>

#include "gtest/gtest.h"

#include "Path.h"

using namespace Mplane ;

//===================================================================================================================
class PathTest : public ::testing::Test
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
TEST_F(PathTest, exists)
{
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/a_dir")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/b_dir")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/c_dir")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/a_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/b_file")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/c_file")) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, isDir)
{
	EXPECT_TRUE(Path::isDir("../../../Path/gtest/test/a_dir")) ;
	EXPECT_TRUE(Path::isDir("../../../Path/gtest/test/b_dir")) ;
	EXPECT_FALSE(Path::isDir("../../../Path/gtest/test/c_dir")) ;
	EXPECT_FALSE(Path::isDir("../../../Path/gtest/test/a_file")) ;
	EXPECT_FALSE(Path::isDir("../../../Path/gtest/test/b_file")) ;
	EXPECT_FALSE(Path::isDir("../../../Path/gtest/test/c_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, isFile)
{
	EXPECT_FALSE(Path::isFile("../../../Path/gtest/test/a_dir")) ;
	EXPECT_FALSE(Path::isFile("../../../Path/gtest/test/b_dir")) ;
	EXPECT_FALSE(Path::isFile("../../../Path/gtest/test/c_dir")) ;

	EXPECT_TRUE(Path::isFile("../../../Path/gtest/test/a_file")) ;
	EXPECT_TRUE(Path::isFile("../../../Path/gtest/test/b_file")) ;
	EXPECT_FALSE(Path::isFile("../../../Path/gtest/test/c_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, isLink)
{
	EXPECT_FALSE(Path::isLink("../../../Path/gtest/test/a_dir")) ;
	EXPECT_FALSE(Path::isLink("../../../Path/gtest/test/b_dir")) ;
	EXPECT_FALSE(Path::isLink("../../../Path/gtest/test/c_dir")) ;

	EXPECT_FALSE(Path::isLink("../../../Path/gtest/test/a_file")) ;
	EXPECT_FALSE(Path::isLink("../../../Path/gtest/test/b_file")) ;
	EXPECT_FALSE(Path::isLink("../../../Path/gtest/test/c_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, basename)
{
	EXPECT_EQ(std::string("a_dir"), Path::basename("../../../Path/gtest/test/a_dir")) ;
	EXPECT_EQ(std::string("b_dir"), Path::basename("../../../Path/gtest/test/b_dir")) ;
	EXPECT_EQ(std::string("a_file"), Path::basename("/test/a_file")) ;
	EXPECT_EQ(std::string("b_file"), Path::basename("/b_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, directory)
{
	EXPECT_EQ(std::string("../../../Path/gtest/test/"), Path::dir("../../../Path/gtest/test/a_dir")) ;
	EXPECT_EQ(std::string("../../../Path/gtest/test/"), Path::dir("../../../Path/gtest/test/b_dir")) ;
	EXPECT_EQ(std::string("/test/"), Path::dir("/test/a_file")) ;
	EXPECT_EQ(std::string("/"), Path::dir("/b_file")) ;
	EXPECT_EQ(std::string(""), Path::dir("b_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, join)
{
	EXPECT_EQ(std::string("../../../Path/gtest/test/a_dir"), Path::join("../../../Path/gtest/test", "a_dir")) ;
	EXPECT_EQ(std::string("../../../Path/gtest/test/a_dir"), Path::join("../../../Path/gtest/test/", "a_dir")) ;
	EXPECT_EQ(std::string("/test/a_file"), Path::join("/test/", "a_file")) ;
	EXPECT_EQ(std::string("/test/a_file"), Path::join("/test", "a_file")) ;
	EXPECT_EQ(std::string("/b_file"), Path::join("", "/b_file")) ;
	EXPECT_EQ(std::string("b_file"), Path::join("", "b_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, extension)
{
	EXPECT_EQ(std::string(".tgz"), Path::extension("../../../Path/gtest/test/a_file.tgz")) ;
	EXPECT_EQ(std::string(".md5"), Path::extension("../../../Path/gtest/test/a_file.tgz.md5")) ;
	EXPECT_EQ(std::string(""), Path::extension("../../../Path/gtest/test/a_file")) ;
	EXPECT_EQ(std::string(""), Path::extension("a_file")) ;
	EXPECT_EQ(std::string(""), Path::extension("")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, dirContents)
{
	std::vector<std::string> contents(Path::dirContents("../../../Path/gtest/test")) ;

	std::copy(contents.begin(), contents.end(),
	        std::ostream_iterator<std::string>(std::cout, "\n"));

	std::vector<std::string> expected ;
	expected.push_back("../../../Path/gtest/test/a_dir") ;
	expected.push_back("../../../Path/gtest/test/b_dir") ;
	expected.push_back("../../../Path/gtest/test/a_file") ;
	expected.push_back("../../../Path/gtest/test/b_file") ;
	expected.push_back("../../../Path/gtest/test/file1.txt") ;
	expected.push_back("../../../Path/gtest/test/file2.txt") ;
	expected.push_back("../../../Path/gtest/test/file3.txt") ;

	EXPECT_EQ(expected.size(), contents.size()) ;

	std::sort(contents.begin(), contents.end()) ;
	std::sort(expected.begin(), expected.end()) ;
	for (unsigned idx=0; idx < expected.size(); ++idx)
	{
		EXPECT_EQ(expected[idx], contents[idx]) ;
	}
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, fileCopyFile)
{
	EXPECT_TRUE(Path::fileCopy("../../../Path/gtest/test/a_file", "../../../Path/gtest/test/c_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/c_file")) ;
	EXPECT_FALSE(Path::isDir("../../../Path/gtest/test/c_file")) ;

	EXPECT_EQ(0, system("diff ../../../Path/gtest/test/a_file ../../../Path/gtest/test/c_file")) ;
	unlink("../../../Path/gtest/test/c_file") ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, fileCopyDir)
{
	EXPECT_EQ(0, Path::mkdir("../../../Path/gtest/test/c_dir")) ;
	EXPECT_TRUE(Path::fileCopy("../../../Path/gtest/test/a_file", "../../../Path/gtest/test/c_dir")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/c_dir/a_file")) ;
	EXPECT_FALSE(Path::isDir("../../../Path/gtest/test/c_dir/a_file")) ;

	EXPECT_EQ(0, system("diff ../../../Path/gtest/test/a_file ../../../Path/gtest/test/c_dir/a_file")) ;
	unlink("../../../Path/gtest/test/c_dir/a_file") ;
	rmdir("../../../Path/gtest/test/c_dir") ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, mkdir)
{
	EXPECT_EQ(0, Path::mkdir("../../../Path/gtest/test/c_dir")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/c_dir")) ;
	EXPECT_TRUE(Path::isDir("../../../Path/gtest/test/c_dir")) ;
	rmdir("../../../Path/gtest/test/c_dir");
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, rmdir)
{
	EXPECT_EQ(0, Path::mkdir("../../../Path/gtest/test/c_dir")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/c_dir")) ;
	EXPECT_TRUE(Path::isDir("../../../Path/gtest/test/c_dir")) ;
	EXPECT_EQ(0, Path::rmdir("../../../Path/gtest/test/c_dir"));

	EXPECT_EQ(-1, Path::rmdir("../../../Path/gtest/test/c_dir"));
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, mkpath)
{
	EXPECT_EQ(0, Path::mkpath("../../../Path/gtest/test/c_dir/dir1/dir2")) ;

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/c_dir")) ;
	EXPECT_TRUE(Path::isDir("../../../Path/gtest/test/c_dir")) ;

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/c_dir/dir1")) ;
	EXPECT_TRUE(Path::isDir("../../../Path/gtest/test/c_dir/dir1")) ;

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/c_dir/dir1/dir2")) ;
	EXPECT_TRUE(Path::isDir("../../../Path/gtest/test/c_dir/dir1/dir2")) ;


	EXPECT_EQ(0, Path::rmdir("../../../Path/gtest/test/c_dir/dir1/dir2"));
	EXPECT_EQ(0, Path::rmdir("../../../Path/gtest/test/c_dir/dir1"));
	EXPECT_EQ(0, Path::rmdir("../../../Path/gtest/test/c_dir"));
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, mkpathLinked)
{
	system("ln -sf a_dir ../../../Path/gtest/test/x_dir");

	EXPECT_EQ(0, Path::mkpath("../../../Path/gtest/test/x_dir/dir1/dir2")) ;

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir")) ;
	EXPECT_TRUE(Path::isLink("../../../Path/gtest/test/x_dir")) ;

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/dir1")) ;
	EXPECT_TRUE(Path::isDir("../../../Path/gtest/test/x_dir/dir1")) ;

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/dir1/dir2")) ;
	EXPECT_TRUE(Path::isDir("../../../Path/gtest/test/x_dir/dir1/dir2")) ;


	EXPECT_EQ(0, Path::rmdir("../../../Path/gtest/test/x_dir/dir1/dir2"));
	EXPECT_EQ(0, Path::rmdir("../../../Path/gtest/test/x_dir/dir1"));
	EXPECT_EQ(0, Path::remove("../../../Path/gtest/test/x_dir"));
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, remove)
{
	EXPECT_TRUE(Path::fileCopy("../../../Path/gtest/test/a_file", "../../../Path/gtest/test/xx_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/xx_file")) ;
	EXPECT_FALSE(Path::isDir("../../../Path/gtest/test/xx_file")) ;
	EXPECT_EQ(0, Path::remove("../../../Path/gtest/test/xx_file")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/xx_file")) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, move)
{
	EXPECT_TRUE(Path::fileCopy("../../../Path/gtest/test/a_file", "../../../Path/gtest/test/xx_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/xx_file")) ;
	EXPECT_FALSE(Path::isDir("../../../Path/gtest/test/xx_file")) ;

	EXPECT_EQ(0, Path::move("../../../Path/gtest/test/xx_file", "../../../Path/gtest/test/yy_file")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/xx_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/yy_file")) ;
	EXPECT_EQ(0, Path::remove("../../../Path/gtest/test/yy_file")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/yy_file")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, links)
{
	system("ln -sf b_file ../../../Path/gtest/test/b_link ") ;
	system("ln -sf ../test/a_file ../../../Path/gtest/test/a_link ") ;

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/a_link")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/b_link")) ;

	EXPECT_FALSE(Path::isFile("../../../Path/gtest/test/a_link")) ;
	EXPECT_FALSE(Path::isFile("../../../Path/gtest/test/b_link")) ;

	EXPECT_TRUE(Path::isLink("../../../Path/gtest/test/a_link")) ;
	EXPECT_TRUE(Path::isLink("../../../Path/gtest/test/b_link")) ;

	std::string link ;
	EXPECT_TRUE(Path::readLink("../../../Path/gtest/test/a_link", link)) ;
	EXPECT_EQ(std::string("../test/a_file"), link) ;
	std::cerr << "a link=" << link << std::endl ;
	EXPECT_TRUE(Path::readLink("../../../Path/gtest/test/b_link", link)) ;
	EXPECT_EQ(std::string("b_file"), link) ;
	std::cerr << "b link=" << link << std::endl ;
	EXPECT_FALSE(Path::readLink("../../../Path/gtest/test/c_link", link)) ;
	EXPECT_EQ(std::string(""), link) ;
	std::cerr << "c link=" << link << std::endl ;

	EXPECT_EQ(0, remove("../../../Path/gtest/test/a_link")) ;
	EXPECT_EQ(0, remove("../../../Path/gtest/test/b_link")) ;

	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/a_link")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/b_link")) ;


	// Use createLink
	EXPECT_TRUE(Path::createLink("../../../Path/gtest/test/a_link", "../test/a_file"));
	EXPECT_TRUE(Path::createLink("../../../Path/gtest/test/b_link", "b_file"));

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/a_link")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/b_link")) ;

	EXPECT_FALSE(Path::isFile("../../../Path/gtest/test/a_link")) ;
	EXPECT_FALSE(Path::isFile("../../../Path/gtest/test/b_link")) ;

	EXPECT_TRUE(Path::isLink("../../../Path/gtest/test/a_link")) ;
	EXPECT_TRUE(Path::isLink("../../../Path/gtest/test/b_link")) ;

	EXPECT_TRUE(Path::readLink("../../../Path/gtest/test/a_link", link)) ;
	EXPECT_EQ(std::string("../test/a_file"), link) ;
	std::cerr << "a link=" << link << std::endl ;
	EXPECT_TRUE(Path::readLink("../../../Path/gtest/test/b_link", link)) ;
	EXPECT_EQ(std::string("b_file"), link) ;
	std::cerr << "b link=" << link << std::endl ;
	EXPECT_FALSE(Path::readLink("../../../Path/gtest/test/c_link", link)) ;
	EXPECT_EQ(std::string(""), link) ;
	std::cerr << "c link=" << link << std::endl ;

	EXPECT_EQ(0, remove("../../../Path/gtest/test/a_link")) ;
	EXPECT_EQ(0, remove("../../../Path/gtest/test/b_link")) ;

	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/a_link")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/b_link")) ;


}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, fileSize)
{
	EXPECT_EQ(8259u, Path::fileSize("../../../Path/gtest/test/a_dir/size8259.txt")) ;
	EXPECT_EQ(15u, Path::fileSize("../../../Path/gtest/test/a_file")) ;
	EXPECT_EQ(19u, Path::fileSize("../../../Path/gtest/test/b_file")) ;
	EXPECT_EQ(0u, Path::fileSize("../../../Path/gtest/test/not_there")) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, freeSpace)
{
	EXPECT_EQ(0ULL, Path::freeSpace("../../../Path/gtest/test/a_dir/not_there")) ;
	EXPECT_NE(0ULL, Path::freeSpace("../../../Path/gtest/test/a_file")) ;

	std::cerr << "Free space on current disk: " << Path::freeSpace("../../../Path/gtest/test/a_file") << std::endl ;
}



//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, removeDirContents)
{
	EXPECT_EQ(0, Path::mkpath("../../../Path/gtest/test/x_dir/a/b")) ;
	EXPECT_EQ(0, Path::mkpath("../../../Path/gtest/test/x_dir/c")) ;
	EXPECT_EQ(0, Path::mkpath("../../../Path/gtest/test/x_dir/d")) ;

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a/b")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/c")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/d")) ;

	EXPECT_TRUE(Path::createLink("../../../Path/gtest/test/x_dir/a_link", "../a_file"));
	EXPECT_TRUE(Path::createLink("../../../Path/gtest/test/x_dir/a/a_link", "../../a_file"));
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a_link")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a/a_link")) ;

	EXPECT_TRUE(Path::fileCopy("../../../Path/gtest/test/a_file", "../../../Path/gtest/test/x_dir/a_file")) ;
	EXPECT_TRUE(Path::fileCopy("../../../Path/gtest/test/a_file", "../../../Path/gtest/test/x_dir/a/a_file")) ;
	EXPECT_TRUE(Path::fileCopy("../../../Path/gtest/test/a_file", "../../../Path/gtest/test/x_dir/a/b/a_file")) ;
	EXPECT_TRUE(Path::fileCopy("../../../Path/gtest/test/a_file", "../../../Path/gtest/test/x_dir/c/a_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a/a_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a/b/a_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/c/a_file")) ;

	// non-recursive delete
	EXPECT_TRUE(Path::removeDirContents("../../../Path/gtest/test/x_dir")) ;

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a/b")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/c")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/d")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/a_link")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a/a_link")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/a_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a/a_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/a/b/a_file")) ;
	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir/c/a_file")) ;

	// recursive delete
	EXPECT_TRUE(Path::removeDirContents("../../../Path/gtest/test/x_dir", true)) ;

	EXPECT_TRUE(Path::exists("../../../Path/gtest/test/x_dir")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/a")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/a/b")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/c")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/d")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/a_link")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/a/a_link")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/a_file")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/a/a_file")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/a/b/a_file")) ;
	EXPECT_FALSE(Path::exists("../../../Path/gtest/test/x_dir/c/a_file")) ;

	// should now be able to remove empty dir
	EXPECT_EQ(0, Path::rmdir("../../../Path/gtest/test/x_dir")) ;

}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(PathTest, fileDiff)
{
	// should be the same excluding header
	EXPECT_FALSE(Path::filesDifferent("../../../Path/gtest/test/file1.txt", "../../../Path/gtest/test/file2.txt", 9)) ;
	EXPECT_TRUE(Path::filesDifferent("../../../Path/gtest/test/file1.txt", "../../../Path/gtest/test/file2.txt", 8)) ;
	EXPECT_TRUE(Path::filesDifferent("../../../Path/gtest/test/file2.txt", "../../../Path/gtest/test/file3.txt", 9)) ;

	EXPECT_TRUE(Path::filesDifferent("../../../Path/gtest/test/file2.txt", "../../../Path/gtest/test/not_there.txt")) ;
	EXPECT_TRUE(Path::filesDifferent("../../../Path/gtest/test/not_there.txt", "../../../Path/gtest/test/file1.txt")) ;
	EXPECT_TRUE(Path::filesDifferent("../../../Path/gtest/test/not_there.txt", "../../../Path/gtest/test/not_there.txt")) ;

	// skip all lines and they should match!
	EXPECT_FALSE(Path::filesDifferent("../../../Path/gtest/test/file1.txt", "../../../Path/gtest/test/file2.txt", 100)) ;

	// these are different lengths so will never match
	EXPECT_TRUE(Path::filesDifferent("../../../Path/gtest/test/file2.txt", "../../../Path/gtest/test/file3.txt", 100)) ;
}


//===================================================================================================================
