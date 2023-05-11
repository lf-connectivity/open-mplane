/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootFile_unittest.cpp
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
#include "TroubleshootFile.h"

using namespace Mplane ;

//===================================================================================================================
class TroubleshootFileTest : public ::testing::Test
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


	std::string fileSlurp(const std::string& path)
	{
		if (!Path::exists(path))
			return "!!FILE DOES NOT EXIST!!" ;

		std::ifstream inFile(path);
		std::stringstream ss;
		ss << inFile.rdbuf();
		return ss.str() ;
	}

};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TroubleshootFileTest, create)
{
	TroubleshootFile tsf("test1.log") ;
	EXPECT_TRUE(tsf.empty()) ;

	EXPECT_TRUE(tsf.generateLog()) ;
	EXPECT_TRUE(tsf.empty()) ;

	EXPECT_FALSE(Path::exists("./test1.log")) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(TroubleshootFileTest, file)
{
	std::shared_ptr<IORanLogFile> tsf(IORanLogFile::factory("test1.log")) ;
	EXPECT_TRUE(tsf->empty()) ;

	EXPECT_TRUE(tsf->generateLog()) ;
	EXPECT_TRUE(tsf->empty()) ;
	EXPECT_FALSE(Path::exists("./test1.log")) ;

	std::string expected("a test line\nanother one\n") ;
	tsf->registerDataGatherer([&expected]()->std::string {
		return expected ;
	}) ;

	EXPECT_TRUE(tsf->generateLog()) ;
	EXPECT_FALSE(tsf->empty()) ;
	EXPECT_TRUE(Path::exists("./test1.log")) ;

	std::string contents(fileSlurp("./test1.log")) ;
	EXPECT_EQ(expected, contents) ;

	Path::remove("./test1.log") ;
}



//===================================================================================================================
