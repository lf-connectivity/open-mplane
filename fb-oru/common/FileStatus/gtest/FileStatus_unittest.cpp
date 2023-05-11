/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileStatus_unittest.cpp
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

#include "ByteTransfer.hpp"
#include "Path.h"
#include "FileStatus.h"

using namespace Mplane ;

//===================================================================================================================
class FileStatusTest : public ::testing::Test
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
		if (!file)
		{
			ASSERT_TRUE(false);
		}
		std::streamsize size(file.tellg()) ;
		file.seekg(0, std::ios::beg) ;

		data.resize(size) ;
		if (!file.read((char *)data.data(), size))
		{
			ASSERT_TRUE(false);
		}
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

    void saveOutput(const std::string& msg)
    {
    	std::cerr << msg ;
    	mOutput += msg ;
    }

    std::string expandedOutput()
    {
    	std::string expanded ;

    	for (char cc : mOutput)
    	{
    		if (cc != '\b')
    		{
    			expanded.push_back(cc) ;
    			continue ;
    		}

    		if (expanded.empty())
    			continue ;

    		expanded.pop_back() ;
    	}

    	return expanded ;
    }

public:
    std::string mOutput ;
};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileStatusTest, factory)
{
	std::shared_ptr<IFileStatus> stat1(IFileStatus::nullObject()) ;
	EXPECT_TRUE(stat1.get() != 0) ;

	std::shared_ptr<IFileStatus> stat2(IFileStatus::simpleTracker()) ;
	EXPECT_TRUE(stat2.get() != 0) ;

	std::shared_ptr<IFileStatus> stat3(IFileStatus::simpleOutput([](const std::string&){})) ;
	EXPECT_TRUE(stat3.get() != 0) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileStatusTest, stats)
{
	std::shared_ptr<IFileStatus> stat(IFileStatus::simpleTracker()) ;
	EXPECT_TRUE(stat.get() != 0) ;


	stat->restart(4) ;
	stat->operation("download") ;


	stat->start("file1") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(0u, stat->getTotalProgress()) ;

	stat->progress(60) ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(60u, stat->getProgress()) ;
	EXPECT_EQ(15u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;


	stat->start("file2") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;

	stat->progress(60) ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(60u, stat->getProgress()) ;
	EXPECT_EQ(40u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(50u, stat->getTotalProgress()) ;


	stat->start("file3") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file3", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(50u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file3", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(75u, stat->getTotalProgress()) ;

	EXPECT_FALSE(stat->isComplete()) ;

	stat->start("file4") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file4", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(75u, stat->getTotalProgress()) ;

	stat->success() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file4", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(100u, stat->getTotalProgress()) ;

	EXPECT_TRUE(stat->isComplete()) ;
	EXPECT_EQ("", stat->getError()) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileStatusTest, output)
{
	std::shared_ptr<IFileStatus> stat(IFileStatus::simpleOutput([this](const std::string& msg){saveOutput(msg);})) ;
	EXPECT_TRUE(stat.get() != 0) ;


	stat->restart(4) ;
	stat->operation("download") ;


	stat->start("file1") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(0u, stat->getTotalProgress()) ;

	stat->progress(60) ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(60u, stat->getProgress()) ;
	EXPECT_EQ(15u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;


	stat->start("file2") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;

	stat->progress(60) ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(60u, stat->getProgress()) ;
	EXPECT_EQ(40u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(50u, stat->getTotalProgress()) ;


	stat->start("file3") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file3", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(50u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file3", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(75u, stat->getTotalProgress()) ;

	EXPECT_FALSE(stat->isComplete()) ;

	stat->start("file4") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file4", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(75u, stat->getTotalProgress()) ;

	stat->success() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file4", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(100u, stat->getTotalProgress()) ;

	EXPECT_TRUE(stat->isComplete()) ;
	EXPECT_EQ("", stat->getError()) ;

	std::string expanded(expandedOutput()) ;
	std::vector<uint8_t> expandedBytes(expanded.begin(), expanded.end()) ;
	ByteTransfer::dump(expandedBytes) ;

	std::string expected{
		"download: file1 100%\n"
		"download: file2 100%\n"
		"download: file3 100%\n"
		"download: file4 100%\n"
	};
	EXPECT_EQ(expected, expanded) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileStatusTest, error)
{
	std::shared_ptr<IFileStatus> stat(IFileStatus::simpleTracker()) ;
	EXPECT_TRUE(stat.get() != 0) ;


	stat->restart(4) ;
	stat->operation("download") ;


	stat->start("file1") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(0u, stat->getTotalProgress()) ;

	stat->progress(60) ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(60u, stat->getProgress()) ;
	EXPECT_EQ(15u, stat->getTotalProgress()) ;

	stat->progress(600000) ; // truncate to 100%
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;


	stat->start("file2") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;

	stat->progress(60) ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(60u, stat->getProgress()) ;
	EXPECT_EQ(40u, stat->getTotalProgress()) ;

	stat->fail("Unexpected error") ;

	EXPECT_TRUE(stat->isComplete()) ;
	EXPECT_EQ("Unexpected error", stat->getError()) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileStatusTest, skip)
{
	std::shared_ptr<IFileStatus> stat(IFileStatus::simpleTracker()) ;
	EXPECT_TRUE(stat.get() != 0) ;


	stat->restart(4) ;
	stat->operation("download") ;


	stat->start("file1") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(0u, stat->getTotalProgress()) ;

	stat->progress(60) ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(60u, stat->getProgress()) ;
	EXPECT_EQ(15u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;

	stat->skip(2) ;

	EXPECT_FALSE(stat->isComplete()) ;

	stat->start("file4") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file4", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(75u, stat->getTotalProgress()) ;

	stat->success() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file4", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(100u, stat->getTotalProgress()) ;

	EXPECT_TRUE(stat->isComplete()) ;
	EXPECT_EQ("", stat->getError()) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileStatusTest, outputSkip)
{
	std::shared_ptr<IFileStatus> stat(IFileStatus::simpleOutput([this](const std::string& msg){saveOutput(msg);})) ;
	EXPECT_TRUE(stat.get() != 0) ;


	stat->restart(4) ;
	stat->operation("download") ;


	stat->start("file1") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(0u, stat->getTotalProgress()) ;

	stat->progress(60) ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(60u, stat->getProgress()) ;
	EXPECT_EQ(15u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;

	stat->skip() ;
	stat->skip() ;

	EXPECT_FALSE(stat->isComplete()) ;

	stat->start("file4") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file4", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(75u, stat->getTotalProgress()) ;

	stat->success() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file4", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(100u, stat->getTotalProgress()) ;

	EXPECT_TRUE(stat->isComplete()) ;
	EXPECT_EQ("", stat->getError()) ;

	std::string expanded(expandedOutput()) ;
	std::vector<uint8_t> expandedBytes(expanded.begin(), expanded.end()) ;
	ByteTransfer::dump(expandedBytes) ;

	std::string expected{
		"download: file1 100%\n"
		"download: file4 100%\n"
	};
	EXPECT_EQ(expected, expanded) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileStatusTest, copy)
{
	std::shared_ptr<IFileStatus> stat(IFileStatus::simpleTracker()) ;
	std::shared_ptr<IFileStatus> stat2(IFileStatus::simpleTracker()) ;
	EXPECT_TRUE(stat.get() != 0) ;


	stat->restart(4) ;
	stat->operation("download") ;


	stat->start("file1") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(0u, stat->getTotalProgress()) ;

	EXPECT_EQ("", stat2->getOperation()) ;
	EXPECT_EQ("", stat2->getFilename()) ;
	EXPECT_EQ(0u, stat2->getProgress()) ;
	EXPECT_EQ(0u, stat2->getTotalProgress()) ;

	stat2->copy(stat) ;
	EXPECT_EQ("download", stat2->getOperation()) ;
	EXPECT_EQ("file1", stat2->getFilename()) ;
	EXPECT_EQ(0u, stat2->getProgress()) ;
	EXPECT_EQ(0u, stat2->getTotalProgress()) ;



	stat->progress(60) ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(60u, stat->getProgress()) ;
	EXPECT_EQ(15u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file1", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;


	stat->start("file2") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(25u, stat->getTotalProgress()) ;

	stat->progress(60) ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(60u, stat->getProgress()) ;
	EXPECT_EQ(40u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file2", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(50u, stat->getTotalProgress()) ;


	EXPECT_EQ("download", stat2->getOperation()) ;
	EXPECT_EQ("file1", stat2->getFilename()) ;
	EXPECT_EQ(0u, stat2->getProgress()) ;
	EXPECT_EQ(0u, stat2->getTotalProgress()) ;
	stat2->copy(stat) ;
	EXPECT_EQ("download", stat2->getOperation()) ;
	EXPECT_EQ("file2", stat2->getFilename()) ;
	EXPECT_EQ(100u, stat2->getProgress()) ;
	EXPECT_EQ(50u, stat2->getTotalProgress()) ;


	stat->start("file3") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file3", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(50u, stat->getTotalProgress()) ;

	stat->end() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file3", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(75u, stat->getTotalProgress()) ;

	EXPECT_FALSE(stat->isComplete()) ;

	stat->start("file4") ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file4", stat->getFilename()) ;
	EXPECT_EQ(0u, stat->getProgress()) ;
	EXPECT_EQ(75u, stat->getTotalProgress()) ;

	stat->success() ;
	EXPECT_EQ("download", stat->getOperation()) ;
	EXPECT_EQ("file4", stat->getFilename()) ;
	EXPECT_EQ(100u, stat->getProgress()) ;
	EXPECT_EQ(100u, stat->getTotalProgress()) ;

	EXPECT_TRUE(stat->isComplete()) ;
	EXPECT_EQ("", stat->getError()) ;


	EXPECT_EQ("download", stat2->getOperation()) ;
	EXPECT_EQ("file2", stat2->getFilename()) ;
	EXPECT_EQ(100u, stat2->getProgress()) ;
	EXPECT_EQ(50u, stat2->getTotalProgress()) ;
	EXPECT_FALSE(stat2->isComplete()) ;
	EXPECT_EQ("", stat2->getError()) ;
	stat2->copy(stat) ;
	EXPECT_EQ("download", stat2->getOperation()) ;
	EXPECT_EQ("file4", stat2->getFilename()) ;
	EXPECT_EQ(100u, stat2->getProgress()) ;
	EXPECT_EQ(100u, stat2->getTotalProgress()) ;
	EXPECT_TRUE(stat2->isComplete()) ;
	EXPECT_EQ("", stat2->getError()) ;

}



//===================================================================================================================
