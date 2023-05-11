/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file     LogList_unittest.cpp
 * \brief     Google Test of LogList
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the LogList class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>


#include "logging_fixture.h"
#include "LogList.h"

using namespace Mplane;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class LogListTest : public LoggingTestFixture {
};



//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(LogListTest, AddDel)
{
	LogList logList ;

	TestLoggable logger1("A", "G1") ;
	EXPECT_TRUE(logList.add(&logger1)) ;

	TestLoggable logger2("B", "G1") ;
	EXPECT_TRUE(logList.add(&logger2)) ;

	TestLoggable logger3("C", "G2") ;
	EXPECT_TRUE(logList.add(&logger3)) ;

	TestLoggable logger4("D", "G2") ;
	EXPECT_TRUE(logList.add(&logger4)) ;

	logList.show(std::cout) ;

	TestLoggable logger5("E", "G3") ;
	EXPECT_FALSE(logList.del(&logger5)) ;

	EXPECT_TRUE(logList.del(&logger1)) ;
	EXPECT_TRUE(logList.del(&logger2)) ;
	EXPECT_TRUE(logList.del(&logger3)) ;
	EXPECT_TRUE(logList.del(&logger4)) ;

	logList.show(std::cout) ;

	EXPECT_FALSE(logList.del(&logger1)) ;
	EXPECT_FALSE(logList.del(&logger2)) ;
	EXPECT_FALSE(logList.del(&logger3)) ;
	EXPECT_FALSE(logList.del(&logger4)) ;

	logList.show(std::cout) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(LogListTest, SetLevels)
{
	LogList logList ;
	logList.show(std::cout) ;

	TestLoggable logger1("A", "G1") ;
	EXPECT_TRUE(logList.add(&logger1)) ;

	TestLoggable logger2("B", "G1") ;
	EXPECT_TRUE(logList.add(&logger2)) ;

	TestLoggable logger3("C", "G2") ;
	EXPECT_TRUE(logList.add(&logger3)) ;

	TestLoggable logger4("D", "G2") ;
	EXPECT_TRUE(logList.add(&logger4)) ;

	logList.show(std::cout) ;

	// Set global levels
	logList.setLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE) ;
	std::cout << "Global = VERBOSE" << std::endl ;
	logList.show(std::cout) ;

	// Set Group levels
	EXPECT_TRUE(logList.setGroupLevel(Mplane::ILoggable::LOG_DEBUG_NORMAL, "G1")) ;
	std::cout << "G1 = NORMAL" << std::endl ;
	logList.show(std::cout) ;

	// Set instance level
	EXPECT_TRUE(logList.setInstanceLevel(Mplane::ILoggable::LOG_DEBUG_NONE, "A")) ;
	std::cout << "A = NONE" << std::endl ;
	logList.show(std::cout) ;

	EXPECT_TRUE(logList.del(&logger1)) ;
	EXPECT_TRUE(logList.del(&logger2)) ;
	EXPECT_TRUE(logList.del(&logger3)) ;
	EXPECT_TRUE(logList.del(&logger4)) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(LogListTest, CheckLevels)
{
	LogList logList ;

	TestLoggable logger1("A", "G1") ;
	EXPECT_TRUE(logList.add(&logger1)) ;

	TestLoggable logger2("B", "G1") ;
	EXPECT_TRUE(logList.add(&logger2)) ;

	TestLoggable logger3("C", "G2") ;
	EXPECT_TRUE(logList.add(&logger3)) ;

	TestLoggable logger4("D", "G2") ;
	EXPECT_TRUE(logList.add(&logger4)) ;

	logList.show(std::cout) ;

	// Set global levels
	logList.setLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE) ;
	std::cout << "Global = VERBOSE" << std::endl ;
	logList.show(std::cout) ;

	// Set Group levels
	EXPECT_TRUE(logList.setGroupLevel(Mplane::ILoggable::LOG_DEBUG_NORMAL, "G1")) ;
	std::cout << "G1 = NORMAL" << std::endl ;
	logList.show(std::cout) ;

	// Set instance level
	EXPECT_TRUE(logList.setInstanceLevel(Mplane::ILoggable::LOG_DEBUG_NONE, "A")) ;
	std::cout << "A = NONE" << std::endl ;
	logList.show(std::cout) ;

	// Should now be:
	//	A : G1 [0]
	//	B : G1 [1]
	//	C : G2 [2]
	//	D : G2 [2]

	EXPECT_FALSE(logger1.isDebug(Mplane::ILoggable::LOG_DEBUG_NORMAL)) ;
	EXPECT_FALSE(logger1.isDebug(Mplane::ILoggable::LOG_DEBUG_NORMAL)) ;

	EXPECT_TRUE(logger2.isDebug(Mplane::ILoggable::LOG_DEBUG_NORMAL)) ;
	EXPECT_FALSE(logger2.isDebug(Mplane::ILoggable::LOG_DEBUG_VERBOSE)) ;

	EXPECT_TRUE(logger3.isDebug(Mplane::ILoggable::LOG_DEBUG_NORMAL)) ;
	EXPECT_TRUE(logger3.isDebug(Mplane::ILoggable::LOG_DEBUG_VERBOSE)) ;

	EXPECT_TRUE(logger4.isDebug(Mplane::ILoggable::LOG_DEBUG_NORMAL)) ;
	EXPECT_TRUE(logger4.isDebug(Mplane::ILoggable::LOG_DEBUG_VERBOSE)) ;

	EXPECT_TRUE(logList.del(&logger1)) ;
	EXPECT_TRUE(logList.del(&logger2)) ;
	EXPECT_TRUE(logList.del(&logger3)) ;
	EXPECT_TRUE(logList.del(&logger4)) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(LogListTest, UniqueName)
{
	// NOTE: LogList relies on the use of uniqueInstanceName() to maintain it's lists
	LogList logList ;
	logList.show(std::cout) ;
	std::string unique ;

	unique = logList.uniqueInstanceName("A") ;
	EXPECT_EQ(std::string("A"), unique) ;
	TestLoggable logger1(unique, "G1") ;
	EXPECT_TRUE(logList.add(&logger1)) ;
	logList.show(std::cout) ;

	unique = logList.uniqueInstanceName("A") ;
	EXPECT_EQ(std::string("A-1"), unique) ;
	TestLoggable logger2(unique, "G1") ;
	EXPECT_TRUE(logList.add(&logger2)) ;
	logList.show(std::cout) ;

	unique = logList.uniqueInstanceName("A") ;
	EXPECT_EQ(std::string("A-2"), unique) ;
	TestLoggable logger3(unique, "G1") ;
	EXPECT_TRUE(logList.add(&logger3)) ;

	unique = logList.uniqueInstanceName("A") ;
	EXPECT_EQ(std::string("A-3"), unique) ;
	TestLoggable logger4(unique, "G2") ;
	EXPECT_TRUE(logList.add(&logger4)) ;

	unique = logList.uniqueInstanceName("A") ;
	EXPECT_EQ(std::string("A-4"), unique) ;
	TestLoggable logger5(unique, "G2") ;
	EXPECT_TRUE(logList.add(&logger5)) ;

	logList.show(std::cout) ;


	unique = logList.uniqueInstanceName("Alarm") ;
	EXPECT_EQ(std::string("Alarm"), unique) ;
	TestLoggable logger10(unique, "G1") ;
	EXPECT_TRUE(logList.add(&logger10)) ;

	unique = logList.uniqueInstanceName("Alarm") ;
	EXPECT_EQ(std::string("Alarm-1"), unique) ;
	TestLoggable logger11(unique, "G1") ;
	EXPECT_TRUE(logList.add(&logger11)) ;

	unique = logList.uniqueInstanceName("Alarm") ;
	EXPECT_EQ(std::string("Alarm-2"), unique) ;
	TestLoggable logger12(unique, "G1") ;
	EXPECT_TRUE(logList.add(&logger12)) ;

	unique = logList.uniqueInstanceName("Alarm") ;
	EXPECT_EQ(std::string("Alarm-3"), unique) ;
	TestLoggable logger13(unique, "G1") ;
	EXPECT_TRUE(logList.add(&logger13)) ;


	logList.show(std::cout) ;

	// Spaces in names
	unique = logList.uniqueInstanceName("A l a r m") ;
	EXPECT_EQ(std::string("A_l_a_r_m"), unique) ;
	TestLoggable logger14(unique, "G1") ;
	EXPECT_TRUE(logList.add(&logger14)) ;

	// No names specified
	unique = logList.uniqueInstanceName("") ;
	EXPECT_EQ(std::string("unnamed"), unique) ;
	TestLoggable logger15(unique, "G1") ;
	EXPECT_TRUE(logList.add(&logger15)) ;
	unique = logList.uniqueInstanceName("") ;
	EXPECT_EQ(std::string("unnamed-1"), unique) ;
	TestLoggable logger16(unique, "G1") ;
	EXPECT_TRUE(logList.add(&logger16)) ;

	logList.show(std::cout) ;


	EXPECT_TRUE(logList.del(&logger1)) ;
	EXPECT_TRUE(logList.del(&logger2)) ;
	EXPECT_TRUE(logList.del(&logger3)) ;
	EXPECT_TRUE(logList.del(&logger4)) ;
	EXPECT_TRUE(logList.del(&logger5)) ;

	EXPECT_TRUE(logList.del(&logger10)) ;
	EXPECT_TRUE(logList.del(&logger11)) ;
	EXPECT_TRUE(logList.del(&logger12)) ;
	EXPECT_TRUE(logList.del(&logger13)) ;
	EXPECT_TRUE(logList.del(&logger14)) ;
	EXPECT_TRUE(logList.del(&logger15)) ;
	EXPECT_TRUE(logList.del(&logger16)) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(LogListTest, GroupName)
{
	LogList logList ;

	std::string group ;

	group = logList.validGroupName("") ;
	EXPECT_EQ(std::string("GLOBAL"), group) ;

	group = logList.validGroupName("A t e s t") ;
	EXPECT_EQ(std::string("A_t_e_s_t"), group) ;

	group = logList.validGroupName("ValidGroup") ;
	EXPECT_EQ(std::string("ValidGroup"), group) ;
}
