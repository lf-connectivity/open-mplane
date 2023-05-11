/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileMgr_unittest.cpp
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
#include "FileMgr.h"

using namespace Mplane ;

//===================================================================================================================
class FileMgrTest : public ::testing::Test
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

	void readFile(const std::string& path, std::vector<uint8_t>& data)
	{
		std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate) ;
		if (!file) { ASSERT_TRUE(false); }
		std::streamsize size(file.tellg()) ;
		file.seekg(0, std::ios::beg) ;

		data.resize(size) ;
		if (!file.read((char *)data.data(), size)) { ASSERT_TRUE(false); }
	}

	void compareData(const std::vector<uint8_t>& data1, const std::vector<uint8_t>& data2)
	{
		ASSERT_EQ(data1.size(), data2.size()) ;
		for (unsigned i=0; i < data1.size(); ++i)
		{
			ASSERT_EQ(data1.at(i), data2.at(i)) ;
		}
	}

    bool checkLists(const std::vector<std::string>& a, const std::vector<std::string>& b)
    {
    	if (a.size() != b.size())
    	{
    		std::cerr << "Lists different sizes: a=" << a.size() << " b=" << b.size() << std::endl ;
    		return false ;
    	}

    	std::vector<std::string> a_sort(a) ;
    	std::vector<std::string> b_sort(b) ;

    	std::sort(a_sort.begin(), a_sort.end()) ;
    	std::sort(b_sort.begin(), b_sort.end()) ;

    	for (unsigned i=0; i < a_sort.size(); ++i)
    	{
    		if (a_sort[i] != b_sort[i])
    		{
        		std::cerr << "Mismatch at index " << i << ": a=" << a_sort[i] << " b=" << b_sort[i] << std::endl ;
        		return false ;
    		}
    	}
    	return true ;
    }

};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileMgrTest, list)
{
	std::shared_ptr<IFileMgr> fmgr(IFileMgr::factory("../../../FileMgr/gtest/test/dir_a")) ;
	std::vector<std::string> allContents(fmgr->listFiles()) ;
	EXPECT_TRUE( checkLists(allContents, {"file1.txt", "file2.txt", "fileX1.xx"})) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileMgrTest, noDir)
{
	std::shared_ptr<IFileMgr> fmgr(IFileMgr::factory()) ;
	EXPECT_EQ(0ull, fmgr->dirFreeSpace()) ;
	EXPECT_FALSE(fmgr->download("http://swin-11/~guest/test_files/images/FTU-0.0-35.pkg", "FTU-0.0-35.pkg")) ;
	EXPECT_NE("", fmgr->getError()) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileMgrTest, download)
{
	std::shared_ptr<IFileMgr> fmgr(IFileMgr::factory("../../../FileMgr/gtest/output")) ;

	std::vector<std::string> allContents1(fmgr->listFiles()) ;
	EXPECT_TRUE( checkLists(allContents1, {"README"})) ;

	EXPECT_TRUE(fmgr->download("http://swin-11/~guest/test_files/images/FTU-0.0-35.pkg", "FTU-0.0-35.pkg")) ;
	EXPECT_EQ("", fmgr->getError()) ;

	std::vector<std::string> allContents2(fmgr->listFiles()) ;
	EXPECT_TRUE( checkLists(allContents2, {"README", "FTU-0.0-35.pkg"})) ;

	EXPECT_TRUE(Path::remove("../../../FileMgr/gtest/output/FTU-0.0-35.pkg") == 0) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileMgrTest, del)
{
	std::shared_ptr<IFileMgr> fmgr(IFileMgr::factory("../../../FileMgr/gtest/output")) ;

	std::vector<std::string> allContents1(fmgr->listFiles()) ;
	EXPECT_TRUE( checkLists(allContents1, {"README"})) ;

	EXPECT_TRUE(fmgr->download("http://swin-11/~guest/test_files/images/FTU-0.0-35.pkg", "FTU-0.0-35.pkg")) ;
	EXPECT_EQ("", fmgr->getError()) ;
	EXPECT_TRUE(fmgr->download("http://swin-11/~guest/test_files/images/FTU-0.0-35.pkg", "FTU-0.0-35.pkg.md5")) ;
	EXPECT_EQ("", fmgr->getError()) ;

	std::vector<std::string> allContents2(fmgr->listFiles()) ;
	EXPECT_TRUE( checkLists(allContents2, {"FTU-0.0-35.pkg", "FTU-0.0-35.pkg.md5", "README", })) ;

unsigned i=0;
for (auto f : allContents2)
{
	std::cerr << i++ << ": " << f << std::endl ;
}

	EXPECT_TRUE(fmgr->del(1)) ;

	std::vector<std::string> allContents3(fmgr->listFiles()) ;
	EXPECT_TRUE( checkLists(allContents3, {"FTU-0.0-35.pkg", "README", })) ;

	EXPECT_TRUE(fmgr->del("FTU-0.0-35.pkg")) ;

	std::vector<std::string> allContents4(fmgr->listFiles()) ;
	EXPECT_TRUE( checkLists(allContents4, {"README"})) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileMgrTest, portTransfer)
{
	std::shared_ptr<IFileMgr> fmgr(IFileMgr::factory("../../../FileMgr/gtest/output")) ;

	std::vector<std::string> allContents1(fmgr->listFiles()) ;
	EXPECT_TRUE( checkLists(allContents1, {"README"})) ;

	std::vector<uint8_t> data;
	readFile("../../../FileMgr/gtest/test/Path.h", data) ;

	std::shared_ptr<IFileMgrWriter> fileWriter(fmgr->portTransferStart("Path.h", data.size())) ;
	ASSERT_TRUE(fileWriter.get() != 0) ;

	EXPECT_TRUE(fileWriter->addData(data)) ;
	EXPECT_TRUE(fmgr->portTransferEnd(true)) ;

	EXPECT_EQ("", fmgr->getError()) ;

	std::vector<std::string> allContents2(fmgr->listFiles()) ;
	EXPECT_TRUE( checkLists(allContents2, {"README", "Path.h"})) ;

	std::vector<uint8_t> data2;
	readFile("../../../FileMgr/gtest/output/Path.h", data2) ;

	EXPECT_TRUE(Path::remove("../../../FileMgr/gtest/output/Path.h") == 0) ;
}



//===================================================================================================================
