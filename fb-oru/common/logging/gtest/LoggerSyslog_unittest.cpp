/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LoggerSyslog_unittest.cpp
 * \brief     Google Test of LoggerSyslog
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the LoggerSyslog class.
 *
 */

#include <gtest/gtest.h>

#include <map>
#include <string>
#include <iostream>
#include <memory>


#include "logging_fixture.h"
#include "ILoggable.h"
#include "Loggable.h"
#include "LoggerSyslog.h"

using namespace Mplane;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class LoggerSyslogTest : public LoggingTestFixture {
};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(LoggerSyslogTest, Format)
{
	// This test checks that all strings sent to syslog are handled correctly and don't cause a segfault
	// due to unhandled formatting
	//
	// There are no specific checks in the test - it should just run without any segfaults
	//

	Mplane::ILoggable::setLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE);

	// ensure we create LoggerSyslog instances AND log to syslog
	gFactorySyslog = true ;
	Mplane::ILoggable::setLogConsole(false) ;


	Loggable logger1("Z", "Z1") ;

	std::string testString("% %d %f %p %s \t\n") ;


	logger1.eventInfo(testString) ;
	logger1.eventData(testString) ;
	logger1.eventWarning(testString) ;
	logger1.eventError(testString) ;

	logger1.logDebugNormal(testString) ;
	logger1.logDebugVerbose(testString) ;

	logger1.dataDaily(testString, testString) ;
	logger1.dataHourly(testString, testString) ;

	logger1.logStream(std::cerr, testString) ;

	Mplane::ILoggable::setLogConsole(true) ;
	gFactorySyslog = false ;

	Mplane::ILoggable::setLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_NONE);
}
