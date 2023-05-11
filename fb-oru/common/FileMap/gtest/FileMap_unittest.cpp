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

#include "FileMap.h"

using namespace Mplane ;

//===================================================================================================================
const std::string TESTDIR("../../../FileMap/gtest/test/") ;

//===================================================================================================================
class FileMapTest : public ::testing::Test
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

    void dumpValues(const std::map<std::string, std::string>& got)
    {
    	std::cerr << "VALUES" << std::endl ;
    	for (auto val : got)
    	{
    		std::cerr << " + '" << val.first << "' = " << " '" << val.second << "'" << std::endl ;
    	}
    }

    bool compareValues(const std::map<std::string, std::string>& expected, const std::map<std::string, std::string>& got)
    {
    	if (expected.size() != got.size())
    	{
    		std::cerr << "Different sizes: expected " << expected.size() << " got " << got.size() << std::endl ;
    		dumpValues(got) ;
    		return false ;
    	}

    	for (auto expect : expected)
    	{
    		auto entry(got.find(expect.first)) ;
    		if (entry == got.end())
    		{
    			std::cerr << "Could not find expected '" << expect.first << "'" << std::endl ;
        		dumpValues(got) ;
    			return false ;
    		}

    		if (entry->second != expect.second)
    		{
    			std::cerr << "Value mismatch for '" << expect.first << "' : expected '" << expect.second <<
    					"' got '" << entry->second << "'" << std::endl ;
        		dumpValues(got) ;
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
TEST_F(FileMapTest, test1)
{
	std::map<std::string, std::string> expected{
		{ "VAR1", "VALUE1" },
		{ "VAR2", "VALUE2" },
		{ "VAR3", "VALUE3" },
	} ;
	FileMap fmap1(TESTDIR + "test1.txt") ;
	EXPECT_EQ("", fmap1.error()) ;
	auto values1(fmap1.values()) ;
	EXPECT_TRUE(compareValues(expected, values1)) ;

	FileMap fmap2 ;
	EXPECT_TRUE(fmap2.setPath(TESTDIR + "test1.txt")) ;
	EXPECT_EQ("", fmap2.error()) ;
	auto values2(fmap2.values()) ;
	EXPECT_TRUE(compareValues(expected, values2)) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileMapTest, test2)
{
	std::map<std::string, std::string> expected{
		{ "VAR1", "VALUE1" },
		{ "VAR2", "VALUE5" },
		{ "VAR3", "VALUE3" },
	} ;
	FileMap fmap1(TESTDIR + "test2.txt") ;
	EXPECT_EQ("", fmap1.error()) ;
	auto values1(fmap1.values()) ;
	EXPECT_TRUE(compareValues(expected, values1)) ;

	FileMap fmap2 ;
	EXPECT_TRUE(fmap2.setPath(TESTDIR + "test2.txt")) ;
	EXPECT_EQ("", fmap2.error()) ;
	auto values2(fmap2.values()) ;
	EXPECT_TRUE(compareValues(expected, values2)) ;

}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileMapTest, test3)
{
	std::map<std::string, std::string> expected{
		{ "VAR1", "VALUE1" },
		{ "VAR2", "VALUE5" },
		{ "VAR3", "VALUE3" },
	} ;
	FileMap fmap1(TESTDIR + "test3.txt") ;
	EXPECT_EQ("", fmap1.error()) ;
	auto values1(fmap1.values()) ;
	EXPECT_TRUE(compareValues(expected, values1)) ;

	FileMap fmap2 ;
	EXPECT_TRUE(fmap2.setPath(TESTDIR + "test3.txt")) ;
	EXPECT_EQ("", fmap2.error()) ;
	auto values2(fmap2.values()) ;
	EXPECT_TRUE(compareValues(expected, values2)) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileMapTest, test4)
{
	std::map<std::string, std::string> expected{
		{ "SHELL", 		"/bin/sh" },
		{ "lease", 		"86400" },
		{ "mask", 		"24" },
		{ "ip", 		"10.0.1.115" },
		{ "router", 		"10.0.1.1" },
		{ "EDITOR", 		"vi" },
		{ "PWD", 		"/home/root" },
		{ "LOGNAME", 		"root" },
		{ "_", 		"/bin/printenv" },
		{ "domain", 		"quartz.com" },
		{ "HOME", 		"/home/root" },
		{ "dns", 		"10.0.1.1" },
		{ "serverid", 		"10.0.1.1" },
		{ "TERM", 		"vt102" },
		{ "subnet", 		"255.255.255.0" },
		{ "USER", 		"root" },
		{ "SHLVL", 		"2" },
		{ "opt53", 		"05" },
		{ "interface", 		"eth0" },
		{ "HUSHLOGIN", 		"FALSE" },
		{ "PATH", 		"/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin" },
		{ "MAIL", 		"/var/spool/mail/root" },

	} ;
	FileMap fmap1(TESTDIR + "test4.txt") ;
	EXPECT_EQ("", fmap1.error()) ;
	auto values1(fmap1.values()) ;
	EXPECT_TRUE(compareValues(expected, values1)) ;

	FileMap fmap2 ;
	EXPECT_TRUE(fmap2.setPath(TESTDIR + "test4.txt")) ;
	EXPECT_EQ("", fmap2.error()) ;
	auto values2(fmap2.values()) ;
	EXPECT_TRUE(compareValues(expected, values2)) ;

}



//===================================================================================================================
