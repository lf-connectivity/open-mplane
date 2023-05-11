/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file     LogHistoryBuffer_unittest.cpp
 * \brief     Google Test of LogHistoryBuffer
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the LogHistoryBuffer class.
 *
 */

#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "stringfunc.hpp"
#include "logging_fixture.h"
#include "LogHistoryBuffer.h"

using namespace Mplane;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class LogHistoryBufferTest : public LoggingTestFixture {
public:
	std::string join(const std::vector<std::string>& strings)
	{
		std::string str ;

		for (auto s : strings)
		{
			str += s + "\n" ;
		}
		return str ;
	}
};



//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(LogHistoryBufferTest, Singleton)
{
	std::shared_ptr<ILogHistory> history(ILogHistory::singleton()) ;
	EXPECT_TRUE(history.get() != nullptr) ;

	std::shared_ptr<LogHistoryBuffer> buff(std::dynamic_pointer_cast<LogHistoryBuffer>(history)) ;
	EXPECT_TRUE(buff.get() != nullptr) ;

	history->setHistoryDepth(8) ;
	history->clear() ;

	std::vector<std::string> content ;

	content = history->getHistory() ;

	EXPECT_EQ("", join(content)) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(LogHistoryBufferTest, Content)
{
	std::shared_ptr<ILogHistory> history(ILogHistory::singleton()) ;
	EXPECT_TRUE(history.get() != nullptr) ;

	std::shared_ptr<LogHistoryBuffer> buff(std::dynamic_pointer_cast<LogHistoryBuffer>(history)) ;
	EXPECT_TRUE(buff.get() != nullptr) ;

	history->setLogLevel(ILoggable::LOG_LEVEL_WARNING) ;
	history->setHistoryDepth(8) ;
	history->clear() ;

	std::vector<std::string> content ;

	content = history->getHistory() ;
	EXPECT_EQ("", join(content)) ;

	buff->logData("shouldn't appear") ;
	buff->logInfo("shouldn't appear") ;
	buff->logDebug("shouldn't appear") ;

	content = history->getHistory() ;
	EXPECT_EQ("", join(content)) ;

	buff->logWarning("warn1") ;
	buff->logError("err1") ;

	content = history->getHistory() ;
	std::cerr << "HISTORY:" << std::endl << join(content) << std::endl ;
	EXPECT_NE("", join(content)) ;


	history->clear() ;
	history->setLogLevel(ILoggable::LOG_LEVEL_DEBUG) ;

	buff->logData("data1") ;
//	sleep(1) ;
	buff->logInfo("info1") ;
//	sleep(1) ;
	buff->logDebug("debug1") ;
	sleep(1) ;
	buff->logWarning("warn1") ;
//	sleep(1) ;
	buff->logError("err1") ;
	sleep(1) ;

	content = history->getHistory() ;
	std::cerr << "HISTORY:" << std::endl << join(content) << std::endl ;
	EXPECT_NE("", join(content)) ;
	EXPECT_TRUE(content[0].find("data1") != std::string::npos) ;
	EXPECT_TRUE(content[1].find("info1") != std::string::npos) ;
	EXPECT_TRUE(content[2].find("debug1") != std::string::npos) ;
	EXPECT_TRUE(content[3].find("warn1") != std::string::npos) ;
	EXPECT_TRUE(content[4].find("err1") != std::string::npos) ;

	for (unsigned i=2; i<=6; ++i)
	{
		buff->logWarning("warn" + std::to_string(i)) ;
	}

	content = history->getHistory() ;
	std::cerr << "HISTORY:" << std::endl << join(content) << std::endl ;
	EXPECT_NE("", join(content)) ;

	EXPECT_TRUE(content[0].find("debug1") != std::string::npos) ;
	EXPECT_TRUE(content[1].find("warn1") != std::string::npos) ;
	EXPECT_TRUE(content[2].find("err1") != std::string::npos) ;
	EXPECT_TRUE(content[3].find("warn2") != std::string::npos) ;
	EXPECT_TRUE(content[4].find("warn3") != std::string::npos) ;
	EXPECT_TRUE(content[5].find("warn4") != std::string::npos) ;
	EXPECT_TRUE(content[6].find("warn5") != std::string::npos) ;
	EXPECT_TRUE(content[7].find("warn6") != std::string::npos) ;

	history->show() ;
}
