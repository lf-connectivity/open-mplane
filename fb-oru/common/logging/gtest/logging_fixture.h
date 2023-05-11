#ifndef _MPLANE_LOGFIXTURE_H_
#define _MPLANE_LOGFIXTURE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      im_fixture.h
 * \brief     Image Management test fixture
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <vector>
#include <string>
#include <memory>

#include "gtest/gtest.h"

#include "ILoggable.h"
#include "ILogger.h"
#include "LogList.h"

namespace Mplane
{

// Use a global(!) to control the factory
extern bool gFactorySyslog ;

//-------------------------------------------------------------------------------------------------------------
/*! @brief Test fixture for Logging
 *
 *  This class uses the Google test facilities to perform unit testing
 */
class LoggingTestFixture : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp();

    /*! @brief Tear down the test
     */
    virtual void TearDown();

};

//-------------------------------------------------------------------------------------------------------------
class TestLogger : public ILogger
{
public:
	TestLogger(const std::string& instanceName, const std::string& groupName) :
		mInstanceName(instanceName), mGroupName(groupName)
	{}

	virtual ~TestLogger() {}

	virtual std::string getInstanceName(void) const { return mInstanceName; }
	virtual std::string getGroupName(void) const override { return mGroupName; }

	// ILogEvent
	virtual void eventData(const std::string& eventStr) const override {mLog.append(eventStr); mLog.append("\n");}
	virtual void eventInfo(const std::string& eventStr) const override {mLog.append(eventStr); mLog.append("\n");}
	virtual void eventWarning(const std::string& eventStr) const override {mLog.append(eventStr); mLog.append("\n");}
	virtual void eventError(const std::string& eventStr) const override {mLog.append(eventStr); mLog.append("\n");}
	virtual void eventFatal(const std::string& eventStr) const override {mLog.append(eventStr); mLog.append("\n");}

	// ILogDebug
	virtual void logDebugNormal(const std::string& debugStr) const override {mLog.append(debugStr); mLog.append("\n");}
	virtual void logDebugVerbose(const std::string& debugStr) const override {mLog.append(debugStr); mLog.append("\n");}

	// ILogData
	virtual void dataHourly(const std::string& dataSource, const std::string& dataStr) const override {
		mLog.append(dataSource);
		mLog.append(":");
		mLog.append(dataStr);
		mLog.append("\n");
	}
	virtual void dataDaily(const std::string& dataSource, const std::string& dataStr) const override {
		mLog.append(dataSource);
		mLog.append(":");
		mLog.append(dataStr);
		mLog.append("\n");
	}


	static std::string mLog ;

private:
	std::string mInstanceName ;
	std::string mGroupName ;

} ;

//-------------------------------------------------------------------------------------------------------------
class TestLoggable : public Mplane::ILoggable
{
public:
	using LogDebugLevel = ILoggable::LogDebugLevel ;

	TestLoggable(const std::string& instanceName, const std::string& groupName) :
//		mInstanceName(mLogList.uniqueInstanceName(instanceName)),
//		mGroupName(mLogList.validGroupName(groupName)),
		mInstanceName(instanceName),
		mGroupName(groupName),
		mLevel(ILoggable::LOG_DEBUG_NONE)
	{}

	virtual ~TestLoggable() {}

	// ILoggable
	virtual std::string getInstanceName(void) const override {return mInstanceName;}
	virtual std::string getGroupName(void) const override {return mGroupName;}
	virtual void setLevel(ILoggable::LogDebugLevel level) override {mLevel=level;} ;
	virtual ILoggable::LogDebugLevel getLevel() const override {return mLevel;} ;
	virtual bool isDebug(LogDebugLevel level) const {return mLevel >= level;}

	virtual void show(std::ostream& os) const override {}
	virtual std::string info() const override {return "";}

	static std::string uniqueInstanceName(const std::string& name) {return"";}
	static void showList(std::ostream& os) {}
	static void setLogDebugLevel(LogDebugLevel level) {}
	static void setGroupLogDebugLevel(LogDebugLevel level, const std::string& groupName) {}
	static void setInstanceLogDebugLevel(LogDebugLevel level, const std::string& instanceName) {}
	static bool isToBeLogged(LogDebugLevel level, const std::string& instanceName) {return false;}


	// ILogEvent
	virtual void eventData(const std::string& eventStr) const override {}
	virtual void eventInfo(const std::string& eventStr) const override {}
	virtual void eventWarning(const std::string& eventStr) const override {}
	virtual void eventError(const std::string& eventStr) const override {}
	virtual void eventFatal(const std::string& eventStr) const override {}

	// ILogDebug
	virtual void logDebugNormal(const std::string& debugStr) const override {}
	virtual void logDebugNormal( char const* fmt, ... ) const override
    	__attribute__ ((format (printf, 2, 3)))  {}
	virtual void logDebugVerbose(const std::string& debugStr) const override {}
	virtual void logDebugVerbose( char const* fmt, ... ) const override
    	__attribute__ ((format (printf, 2, 3)))  {}


	// Event
	virtual void eventData( char const* fmt, ... ) const override
	__attribute__ ((format (printf, 2, 3))) {}

	virtual void eventInfo( char const* fmt, ... ) const override
	__attribute__ ((format (printf, 2, 3))) {}

	virtual void eventWarning( char const* fmt, ... ) const override
	__attribute__ ((format (printf, 2, 3))) {}

	virtual void eventError( char const* fmt, ... ) const override
	__attribute__ ((format (printf, 2, 3))) {}

	virtual void eventFatal( char const* fmt, ... ) const override
	__attribute__ ((format (printf, 2, 3))) {}

	virtual void eventFatal( char const* filename, int line, unsigned long errNumber, char const* fmt, ... ) const override
	__attribute__ ((format (printf, 5, 6))) {}

	// ILogData
	virtual void dataHourly(const std::string& dataSource, const std::string& dataStr) const override {}
	virtual void dataDaily(const std::string& dataSource, const std::string& dataStr) const override {}

public:
//	static LogList mLogList ;
	std::string mInstanceName ;
	std::string mGroupName ;
	ILoggable::LogDebugLevel mLevel ;
} ;


} /* namespace Mplane */

#endif
