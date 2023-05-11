/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TraceLoghistoryFile_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "TraceLoghistoryFile.h"

#include <algorithm>
#include <iostream>
#include <fstream>

#include <unistd.h>

#include "gtest/gtest.h"

#include "Path.h"
#include "stringfunc.hpp"
#include "LogHistoryBuffer.h"

using namespace Mplane ;

//===================================================================================================================
class TraceLoghistoryFileTest : public ::testing::Test
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

	std::vector<std::string> fileLines(const std::string& path)
	{
		std::string contents(fileSlurp(path)) ;
		return(splitStr(contents, "\n")) ;
	}

};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TraceLoghistoryFileTest, create)
{
	Path::remove("./test1.log") ;

	TraceLoghistoryFile tsf("test1.log") ;
	EXPECT_TRUE(tsf.empty()) ;

	EXPECT_TRUE(tsf.generateLog()) ;
	EXPECT_TRUE(tsf.empty()) ;

	EXPECT_FALSE(Path::exists("./test1.log")) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(TraceLoghistoryFileTest, file)
{
	Path::remove("./test2.log") ;

	std::shared_ptr<TraceLoghistoryFile> tsf(std::make_shared<TraceLoghistoryFile>("test2.log")) ;
	EXPECT_TRUE(tsf->empty()) ;

	EXPECT_TRUE(tsf->generateLog()) ;
	EXPECT_TRUE(tsf->empty()) ;
	EXPECT_FALSE(Path::exists("./test2.log")) ;

	std::shared_ptr<ILogHistory> history(ILogHistory::singleton()) ;
	EXPECT_TRUE(history.get() != nullptr) ;

	std::shared_ptr<LogHistoryBuffer> buff(std::dynamic_pointer_cast<LogHistoryBuffer>(history)) ;
	EXPECT_TRUE(buff.get() != nullptr) ;

	history->setLogLevel(ILoggable::LOG_LEVEL_WARNING) ;
	history->setHistoryDepth(8) ;
	history->clear() ;

	buff->logData("data1") ;
	buff->logInfo("info1") ;
	buff->logDebug("debug1") ;
	buff->logWarning("warn1") ;
	buff->logError("err1") ;


	EXPECT_TRUE(tsf->generateLog()) ;
	EXPECT_FALSE(tsf->empty()) ;
	EXPECT_TRUE(Path::exists("./test2.log")) ;

	std::string contents(fileSlurp("./test2.log")) ;
	EXPECT_NE("", contents) ;

	std::cerr << contents << std::endl ;

	std::vector<std::string> lines(fileLines("./test2.log")) ;
	EXPECT_TRUE(lines[0].find("warn1") != std::string::npos) ;
	EXPECT_TRUE(lines[1].find("err1") != std::string::npos) ;


	Path::remove("./test2.log") ;
}



//===================================================================================================================
