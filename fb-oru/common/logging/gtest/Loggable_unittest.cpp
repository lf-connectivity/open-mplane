/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Loggable_unittest.cpp
 * \brief     Google Test of Loggable
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Loggable class.
 *
 */

#include <gtest/gtest.h>

#include <map>
#include <string>
#include <iostream>
#include <memory>

#include "stringfunc.hpp"

#include "logging_fixture.h"
#include "Loggable.h"

using namespace Mplane;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class LoggableTest : public LoggingTestFixture {
};

//-------------------------------------------------------------------------------------------------------------
class TestingLoggable : public Loggable {
public:
	TestingLoggable(const std::string& instanceName, const std::string& groupName) :
		Loggable(instanceName, groupName)
	{}

	virtual ~TestingLoggable() {}

	// Test methods
	void writeLogNormal(const std::string& msg)
	{
		logDebugNormal(std::string("[") + getInstanceName() + "] " + msg) ;
	}
	void writeLogVerbose(const std::string& msg)
	{
		logDebugVerbose(std::string("[") + getInstanceName() + "] " + msg) ;
	}
	void writeLogNormalFmt(const std::string& msg, unsigned ival)
	{
		std::string str = std::string("[") + getInstanceName() + "] " + msg ;
		logDebugNormal("%s %d", str.c_str(), ival) ;
	}
	void writeLogVerboseFmt(const std::string& msg, unsigned ival)
	{
		std::string str = std::string("[") + getInstanceName() + "] " + msg ;
		logDebugVerbose("%s %d", str.c_str(), ival) ;
	}

	void writeEventData(const std::string& msg)
	{
		eventData(std::string("[") + getInstanceName() + "] " + msg) ;
	}
	void writeEventInfo(const std::string& msg)
	{
		eventInfo(std::string("[") + getInstanceName() + "] " + msg) ;
	}
	void writeEventWarning(const std::string& msg)
	{
		eventWarning(std::string("[") + getInstanceName() + "] " + msg) ;
	}
	void writeEventError(const std::string& msg)
	{
		eventError(std::string("[") + getInstanceName() + "] " + msg) ;
	}
	void writeEventFatal(const std::string& msg)
	{
		eventFatal(std::string("[") + getInstanceName() + "] " + msg) ;
	}
	void writeEventDataFmt(const std::string& msg, unsigned ival)
	{
		std::string str = std::string("[") + getInstanceName() + "] " + msg ;
		eventData("%s %d", str.c_str(), ival) ;
	}
	void writeEventInfoFmt(const std::string& msg, unsigned ival)
	{
		std::string str = std::string("[") + getInstanceName() + "] " + msg ;
		eventInfo("%s %d", str.c_str(), ival) ;
	}
	void writeEventWarningFmt(const std::string& msg, unsigned ival)
	{
		std::string str = std::string("[") + getInstanceName() + "] " + msg ;
		eventWarning("%s %d", str.c_str(), ival) ;
	}
	void writeEventErrorFmt(const std::string& msg, unsigned ival)
	{
		std::string str = std::string("[") + getInstanceName() + "] " + msg ;
		eventError("%s %d", str.c_str(), ival) ;
	}
	void writeEventFatalFmt(const std::string& msg, unsigned ival)
	{
		std::string str = std::string("[") + getInstanceName() + "] " + msg ;
		eventFatal("%s %d", str.c_str(), ival) ;
	}

	void writeDataHourly(const std::string& src, const std::string& msg)
	{
		dataHourly(src, std::string("[") + getInstanceName() + "] " + msg) ;
	}
	void writeDataDaily(const std::string& src, const std::string& msg)
	{
		dataDaily(src, std::string("[") + getInstanceName() + "] " + msg) ;
	}


};

namespace {

	std::string formatShow(const std::string& name, const std::string& group, const std::string& level)
	{
		return std::string(
			padLeft(name, LogList::NAME_WIDTH, ' ') +
			padLeft(group, LogList::GROUP_WIDTH, ' ') +
			padLeft(level, LogList::LEVEL_WIDTH)
		) ;
	}
}

//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, Create)
{
	Loggable logger1("A", "G1") ;
	Loggable logger2("B", "G1") ;
	Loggable logger3("C", "G2") ;
	Loggable logger4("D", "G2") ;

	std::cout << "Loggables A-D" << std::endl ;
	ILoggable::showList(std::cout) ;

	std::cout << "Loggables A-E" << std::endl ;
	Loggable logger5("E", "G3") ;
	ILoggable::showList(std::cout) ;

	std::cout << "Loggables A1,A-E" << std::endl ;
	Loggable logger6("A", "G3") ;
	ILoggable::showList(std::cout) ;

	Loggable logger7("", "") ;
	Loggable logger8("", "") ;
	Loggable logger9("", "") ;
	Loggable logger10("A test", "A group") ;
	ILoggable::showList(std::cout) ;

	std::stringstream ss ;
	ILoggable::showList(ss) ;

	EXPECT_TRUE(ss.str().find(formatShow("unnamed", "GLOBAL", "Off")) != std::string::npos) ;
	EXPECT_TRUE(ss.str().find(formatShow("unnamed-1", "GLOBAL", "Off")) != std::string::npos) ;
	EXPECT_TRUE(ss.str().find(formatShow("unnamed-2", "GLOBAL", "Off")) != std::string::npos) ;
	EXPECT_TRUE(ss.str().find(formatShow("A_test", "A_group", "Off")) != std::string::npos) ;

	ILoggable::showList(std::cout) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, LogNormal)
{
	ILoggable::showList(std::cout) ;

	TestingLoggable logger1("A", "G1") ;
	TestingLoggable logger2("B", "G1") ;
	TestingLoggable logger3("C", "G2") ;
	TestingLoggable logger4("D", "G2") ;
	TestingLoggable logger5("E", "G3") ;
	TestingLoggable logger6("A", "G3") ;
	ILoggable::showList(std::cout) ;

	//----------------------------
	TestLogger::mLog.clear() ;
	ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL) ;
	ILoggable::showList(std::cout) ;
	logger1.writeLogNormal("normal") ;
	logger1.writeLogVerbose("verbose") ;
	logger2.writeLogNormal("normal") ;
	logger2.writeLogVerbose("verbose") ;
	logger3.writeLogNormal("normal") ;
	logger3.writeLogVerbose("verbose") ;
	logger4.writeLogNormal("normal") ;
	logger4.writeLogVerbose("verbose") ;
	logger5.writeLogNormal("normal") ;
	logger5.writeLogVerbose("verbose") ;
	logger6.writeLogNormal("normal") ;
	logger6.writeLogVerbose("verbose") ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected1(
		"[A] normal\n"
		"[B] normal\n"
		"[C] normal\n"
		"[D] normal\n"
		"[E] normal\n"
		"[A-1] normal\n"
	) ;
	EXPECT_EQ(expected1, TestLogger::mLog);

	//----------------------------
	TestLogger::mLog.clear() ;
	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_NONE, "G1") ;
	logger1.writeLogNormal("normal") ;
	logger1.writeLogVerbose("verbose") ;
	logger2.writeLogNormal("normal") ;
	logger2.writeLogVerbose("verbose") ;
	logger3.writeLogNormal("normal") ;
	logger3.writeLogVerbose("verbose") ;
	logger4.writeLogNormal("normal") ;
	logger4.writeLogVerbose("verbose") ;
	logger5.writeLogNormal("normal") ;
	logger5.writeLogVerbose("verbose") ;
	logger6.writeLogNormal("normal") ;
	logger6.writeLogVerbose("verbose") ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected2(
		"[C] normal\n"
		"[D] normal\n"
		"[E] normal\n"
		"[A-1] normal\n"
	) ;
	EXPECT_EQ(expected2, TestLogger::mLog);

	//----------------------------
	TestLogger::mLog.clear() ;
	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_NONE, "A-1") ;
	logger1.writeLogNormal("normal") ;
	logger1.writeLogVerbose("verbose") ;
	logger2.writeLogNormal("normal") ;
	logger2.writeLogVerbose("verbose") ;
	logger3.writeLogNormal("normal") ;
	logger3.writeLogVerbose("verbose") ;
	logger4.writeLogNormal("normal") ;
	logger4.writeLogVerbose("verbose") ;
	logger5.writeLogNormal("normal") ;
	logger5.writeLogVerbose("verbose") ;
	logger6.writeLogNormal("normal") ;
	logger6.writeLogVerbose("verbose") ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected3(
		"[C] normal\n"
		"[D] normal\n"
		"[E] normal\n"
	) ;
	EXPECT_EQ(expected3, TestLogger::mLog);

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, LogVerbose)
{
	TestingLoggable logger1("A", "G1") ;
	TestingLoggable logger2("B", "G1") ;
	TestingLoggable logger3("C", "G2") ;
	TestingLoggable logger4("D", "G2") ;
	TestingLoggable logger5("E", "G3") ;
	TestingLoggable logger6("A", "G3") ;
	Loggable::showList(std::cout) ;

	//----------------------------
	TestLogger::mLog.clear() ;
	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE) ;
	logger1.writeLogNormal("normal") ;
	logger1.writeLogVerbose("verbose") ;
	logger2.writeLogNormal("normal") ;
	logger2.writeLogVerbose("verbose") ;
	logger3.writeLogNormal("normal") ;
	logger3.writeLogVerbose("verbose") ;
	logger4.writeLogNormal("normal") ;
	logger4.writeLogVerbose("verbose") ;
	logger5.writeLogNormal("normal") ;
	logger5.writeLogVerbose("verbose") ;
	logger6.writeLogNormal("normal") ;
	logger6.writeLogVerbose("verbose") ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected1(
		"[A] normal\n"
		"[A] verbose\n"
		"[B] normal\n"
		"[B] verbose\n"
		"[C] normal\n"
		"[C] verbose\n"
		"[D] normal\n"
		"[D] verbose\n"
		"[E] normal\n"
		"[E] verbose\n"
		"[A-1] normal\n"
		"[A-1] verbose\n"
	) ;
	EXPECT_EQ(expected1, TestLogger::mLog);

	//----------------------------
	TestLogger::mLog.clear() ;
	TestingLoggable::setGroupLogDebugLevel(TestingLoggable::LOG_DEBUG_NORMAL, "G1") ;
	logger1.writeLogNormal("normal") ;
	logger1.writeLogVerbose("verbose") ;
	logger2.writeLogNormal("normal") ;
	logger2.writeLogVerbose("verbose") ;
	logger3.writeLogNormal("normal") ;
	logger3.writeLogVerbose("verbose") ;
	logger4.writeLogNormal("normal") ;
	logger4.writeLogVerbose("verbose") ;
	logger5.writeLogNormal("normal") ;
	logger5.writeLogVerbose("verbose") ;
	logger6.writeLogNormal("normal") ;
	logger6.writeLogVerbose("verbose") ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected2(
		"[A] normal\n"
		"[B] normal\n"
		"[C] normal\n"
		"[C] verbose\n"
		"[D] normal\n"
		"[D] verbose\n"
		"[E] normal\n"
		"[E] verbose\n"
		"[A-1] normal\n"
		"[A-1] verbose\n"
	) ;
	EXPECT_EQ(expected2, TestLogger::mLog);

	//----------------------------
	TestLogger::mLog.clear() ;
	TestingLoggable::setGroupLogDebugLevel(TestingLoggable::LOG_DEBUG_NONE, "G1") ;
	logger1.writeLogNormal("normal") ;
	logger1.writeLogVerbose("verbose") ;
	logger2.writeLogNormal("normal") ;
	logger2.writeLogVerbose("verbose") ;
	logger3.writeLogNormal("normal") ;
	logger3.writeLogVerbose("verbose") ;
	logger4.writeLogNormal("normal") ;
	logger4.writeLogVerbose("verbose") ;
	logger5.writeLogNormal("normal") ;
	logger5.writeLogVerbose("verbose") ;
	logger6.writeLogNormal("normal") ;
	logger6.writeLogVerbose("verbose") ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected3(
		"[C] normal\n"
		"[C] verbose\n"
		"[D] normal\n"
		"[D] verbose\n"
		"[E] normal\n"
		"[E] verbose\n"
		"[A-1] normal\n"
		"[A-1] verbose\n"
	) ;
	EXPECT_EQ(expected3, TestLogger::mLog);



	//----------------------------
	TestLogger::mLog.clear() ;
	TestingLoggable::setInstanceLogDebugLevel(TestingLoggable::LOG_DEBUG_NORMAL, "A-1") ;
	logger1.writeLogNormal("normal") ;
	logger1.writeLogVerbose("verbose") ;
	logger2.writeLogNormal("normal") ;
	logger2.writeLogVerbose("verbose") ;
	logger3.writeLogNormal("normal") ;
	logger3.writeLogVerbose("verbose") ;
	logger4.writeLogNormal("normal") ;
	logger4.writeLogVerbose("verbose") ;
	logger5.writeLogNormal("normal") ;
	logger5.writeLogVerbose("verbose") ;
	logger6.writeLogNormal("normal") ;
	logger6.writeLogVerbose("verbose") ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected4(
		"[C] normal\n"
		"[C] verbose\n"
		"[D] normal\n"
		"[D] verbose\n"
		"[E] normal\n"
		"[E] verbose\n"
		"[A-1] normal\n"
	) ;
	EXPECT_EQ(expected4, TestLogger::mLog);

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, LogDebugFmt)
{
	TestingLoggable logger1("A", "G1") ;
	TestingLoggable logger2("B", "G1") ;
	TestingLoggable logger3("C", "G2") ;
	TestingLoggable logger4("D", "G2") ;
	TestingLoggable logger5("E", "G3") ;
	TestingLoggable logger6("A", "G3") ;

	//----------------------------
	TestLogger::mLog.clear() ;
	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE) ;
	unsigned count = 0 ;
	logger1.writeLogNormalFmt("normal", count++) ;
	logger1.writeLogVerboseFmt("verbose", count++) ;
	logger2.writeLogNormalFmt("normal", count++) ;
	logger2.writeLogVerboseFmt("verbose", count++) ;
	logger3.writeLogNormalFmt("normal", count++) ;
	logger3.writeLogVerboseFmt("verbose", count++) ;
	logger4.writeLogNormalFmt("normal", count++) ;
	logger4.writeLogVerboseFmt("verbose", count++) ;
	logger5.writeLogNormalFmt("normal", count++) ;
	logger5.writeLogVerboseFmt("verbose", count++) ;
	logger6.writeLogNormalFmt("normal", count++) ;
	logger6.writeLogVerboseFmt("verbose", count++) ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected1(
		"[A] normal 0\n"
		"[A] verbose 1\n"
		"[B] normal 2\n"
		"[B] verbose 3\n"
		"[C] normal 4\n"
		"[C] verbose 5\n"
		"[D] normal 6\n"
		"[D] verbose 7\n"
		"[E] normal 8\n"
		"[E] verbose 9\n"
		"[A-1] normal 10\n"
		"[A-1] verbose 11\n"
	) ;
	EXPECT_EQ(expected1, TestLogger::mLog);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, LogEvent)
{
	TestingLoggable logger1("A", "G1") ;
	TestingLoggable logger2("B", "G1") ;
	TestingLoggable logger3("C", "G2") ;
	TestingLoggable logger4("D", "G2") ;
	TestingLoggable logger5("E", "G3") ;
	TestingLoggable logger6("A", "G3") ;

	//----------------------------
	TestLogger::mLog.clear() ;
	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_NONE) ;
	logger1.writeEventData("data") ;
	logger2.writeEventInfo("info") ;
	logger3.writeEventWarning("warning") ;
	logger4.writeEventError("error") ;
//	logger5.writeEventFatal("fatal") ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected1(
		"[A] data\n"
		"[B] info\n"
		"[C] warning\n"
		"[D] error\n"
//		"[E] fatal\n"
	) ;
	EXPECT_EQ(expected1, TestLogger::mLog);
}



//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, LogEventFmt)
{
	TestingLoggable logger1("A", "G1") ;
	TestingLoggable logger2("B", "G1") ;
	TestingLoggable logger3("C", "G2") ;
	TestingLoggable logger4("D", "G2") ;
	TestingLoggable logger5("E", "G3") ;
	TestingLoggable logger6("A", "G3") ;

	//----------------------------
	TestLogger::mLog.clear() ;
	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_NONE) ;
	unsigned count = 0 ;
	logger1.writeEventDataFmt("data", count++) ;
	logger2.writeEventInfoFmt("info", count++) ;
	logger3.writeEventWarningFmt("warning", count++) ;
	logger4.writeEventErrorFmt("error", count++) ;
//	logger5.writeEventFatalFmt("fatal", count++) ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected1(
		"[A] data 0\n"
		"[B] info 1\n"
		"[C] warning 2\n"
		"[D] error 3\n"
//		"[E] fatal 4\n"
	) ;
	EXPECT_EQ(expected1, TestLogger::mLog);
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, LogData)
{
	TestingLoggable logger1("A", "G1") ;
	TestingLoggable logger2("B", "G1") ;
	TestingLoggable logger3("C", "G2") ;

	//----------------------------
	TestLogger::mLog.clear() ;
	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_NONE) ;
	logger1.writeDataHourly("X", "hour") ;
	logger1.writeDataDaily("X", "day") ;
	logger2.writeDataHourly("Y", "hour") ;
	logger2.writeDataDaily("Y", "day") ;
	logger3.writeDataHourly("Z", "hour") ;
	logger3.writeDataDaily("Z", "day") ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected1(
		"X:[A] hour\n"
		"X:[A] day\n"
		"Y:[B] hour\n"
		"Y:[B] day\n"
		"Z:[C] hour\n"
		"Z:[C] day\n"
	) ;
	EXPECT_EQ(expected1, TestLogger::mLog);
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, LogStream)
{
	std::stringstream ss ;
	ILoggable::logStream(ss, "First line") ;
	unsigned count = 0 ;
	ILoggable::logStream(ss, "%s %d", "Second line", ++count) ;
	ILoggable::logStream(ss, "%s %d", "line", ++count) ;

	std::string expected1(
		"First line\n"
		"Second line 1\n"
		"line 2\n"
	) ;
	EXPECT_EQ(expected1, ss.str());
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, Level)
{
	// Test conversion from level to string
	std::map<ILoggable::LogDebugLevel, std::string> ToString{
		{ILoggable::LOG_DEBUG_NONE,	"Off"},
		{ILoggable::LOG_DEBUG_NORMAL,	"Normal"},
		{ILoggable::LOG_DEBUG_VERBOSE,	"Verbose"},
	};

	for (auto entry : ToString)
	{
		std::string result( ILoggable::levelStr(entry.first) ) ;
		EXPECT_EQ(result, entry.second) ;
	}

	// Test conversion from string to level
	std::map<std::string, ILoggable::LogDebugLevel> ToLevel{
		{"Off",		ILoggable::LOG_DEBUG_NONE},
		{"Normal",	ILoggable::LOG_DEBUG_NORMAL},
		{"Verbose",	ILoggable::LOG_DEBUG_VERBOSE},
		{"OFF",		ILoggable::LOG_DEBUG_NONE},
		{"NORMAL",	ILoggable::LOG_DEBUG_NORMAL},
		{"VERBOSE",	ILoggable::LOG_DEBUG_VERBOSE},
		{"off",		ILoggable::LOG_DEBUG_NONE},
		{"normal",	ILoggable::LOG_DEBUG_NORMAL},
		{"verbose",	ILoggable::LOG_DEBUG_VERBOSE},
		{"xxx",		ILoggable::LOG_DEBUG_NONE},
	};
	for (auto entry : ToLevel)
	{
		ILoggable::LogDebugLevel result( ILoggable::strToLevel(entry.first) ) ;
		EXPECT_EQ(result, entry.second) ;
	}

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, SetLevels)
{
	// Create a scope we can exit during the test
	{
	// Test we can set up debugging levels *before* creating any Loggables
	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_NONE, "GOFF") ;
	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL, "GNORM") ;
	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "GVERB") ;
	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_NONE, "AOFF1") ;
	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_NONE, "AOFF2") ;
	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_NONE, "AOFF3") ;
	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL, "BNORM1") ;
	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL, "BNORM2") ;
	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL, "BNORM3") ;
	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "CVERB1") ;
	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "CVERB2") ;
	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "CVERB3") ;
	ILoggable::showList(std::cout) ;

	// Now create the objects
	Loggable logger1("AOFF1", "GOFF") ;
	Loggable logger2("AOFF2", "GNORM") ;
	Loggable logger3("AOFF3", "GVERB") ;
	Loggable logger4("BNORM1", "GOFF") ;
	Loggable logger5("BNORM2", "GNORM") ;
	Loggable logger6("BNORM3", "GVERB") ;
	Loggable logger7("CVERB1", "GOFF") ;
	Loggable logger8("CVERB2", "GNORM") ;
	Loggable logger9("CVERB3", "GVERB") ;
	ILoggable::showList(std::cout) ;

	std::stringstream ss ;
	ILoggable::showList(ss) ;

	EXPECT_TRUE(ss.str().find(formatShow("AOFF1", 	"GOFF", 	"Off")) != std::string::npos) ;
	EXPECT_TRUE(ss.str().find(formatShow("AOFF2", 	"GNORM", 	"Normal")) != std::string::npos) ;
	EXPECT_TRUE(ss.str().find(formatShow("AOFF3", 	"GVERB", 	"Verbose")) != std::string::npos) ;

	EXPECT_TRUE(ss.str().find(formatShow("BNORM1", 	"GOFF", 	"Normal")) != std::string::npos) ;
	EXPECT_TRUE(ss.str().find(formatShow("BNORM2", 	"GNORM", 	"Normal")) != std::string::npos) ;
	EXPECT_TRUE(ss.str().find(formatShow("BNORM3", 	"GVERB", 	"Verbose")) != std::string::npos) ;

	EXPECT_TRUE(ss.str().find(formatShow("CVERB1", 	"GOFF", 	"Verbose")) != std::string::npos) ;
	EXPECT_TRUE(ss.str().find(formatShow("CVERB2", 	"GNORM", 	"Verbose")) != std::string::npos) ;
	EXPECT_TRUE(ss.str().find(formatShow("CVERB3", 	"GVERB", 	"Verbose")) != std::string::npos) ;

	EXPECT_EQ(ILoggable::LOG_DEBUG_NONE,	logger1.getLevel()) ;
	EXPECT_EQ(ILoggable::LOG_DEBUG_NORMAL,	logger2.getLevel()) ;
	EXPECT_EQ(ILoggable::LOG_DEBUG_VERBOSE,	logger3.getLevel()) ;
	EXPECT_EQ(ILoggable::LOG_DEBUG_NORMAL,	logger4.getLevel()) ;
	EXPECT_EQ(ILoggable::LOG_DEBUG_NORMAL,	logger5.getLevel()) ;
	EXPECT_EQ(ILoggable::LOG_DEBUG_VERBOSE,	logger6.getLevel()) ;
	EXPECT_EQ(ILoggable::LOG_DEBUG_VERBOSE,	logger7.getLevel()) ;
	EXPECT_EQ(ILoggable::LOG_DEBUG_VERBOSE,	logger8.getLevel()) ;
	EXPECT_EQ(ILoggable::LOG_DEBUG_VERBOSE,	logger9.getLevel()) ;

	ILoggable::showList(std::cout) ;
	}
	// Out of scope so loggers should be deleted

	ILoggable::showList(std::cout) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggableTest, StaticEvent)
{
	TestLogger::mLog.clear() ;

	// Create a scope we can exit during the test
	{
	ILoggable::logEventInfo("Info event 1a") ;
	ILoggable::logEventInfo("Info event 1b %s,%u,%.2f", "test strring", 123, 456.789) ;
	}

	// Out of scope so loggers should be deleted
	ILoggable::showList(std::cout) ;

	ILoggable::logEventInfo("Info event 2") ;

	std::cerr << "LOG: " << TestLogger::mLog << std::endl ;

	std::string expected{
		"Info event 1a\n"
		"Info event 1b test strring,123,456.79\n"
		"Info event 2\n"
	};
	EXPECT_EQ(expected, TestLogger::mLog) ;

}
