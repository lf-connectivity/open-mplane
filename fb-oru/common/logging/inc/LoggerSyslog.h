/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LoggerSyslog.h
 * \brief     Syslog variant of ILogger
 *
 *
 * \details   Provides the ILogger interface, logging to Linux syslog
 *
 */


#ifndef LOGGERSYSLOG_H_
#define LOGGERSYSLOG_H_

#include "Mutex.h"
#include "LoggerBase.h"

namespace Mplane {

class LoggerSyslog : public LoggerBase
{
public:
	LoggerSyslog(ILoggable* parent, const std::string& instanceName, const std::string& groupName) ;

	virtual ~LoggerSyslog() ;

	// ILogEvent

	/**
	 * log a data event (e.g. an ARD command)
	 */
	void eventData(const std::string& eventStr) const override ;

	/**
	 * log informational event
	 */
	void eventInfo(const std::string& eventStr) const override ;

	/**
	 * log a warning
	 */
	void eventWarning(const std::string& eventStr) const override ;

	/**
	 * log a non-fatal error
	 */
	void eventError(const std::string& eventStr) const override ;

	/**
	 * log a fatal error (and terminate)
	 */
	void eventFatal(const std::string& eventStr) const override ;

	// ILogDebug

	/**
	 * Log the string if debug log level is greater than or equal to "normal" setting
	 * @param debugStr String to log
	 */
	void logDebugNormal(const std::string& debugStr) const override ;

	/**
	 * Log the string if debug log level is greater than or equal to "verbose" setting
	 * @param debugStr String to log
	 */
	void logDebugVerbose(const std::string& debugStr) const override ;


	// ILogData

	/**
	 * log an hourly data event
	 * @param dataSource	Name of data source
	 * @param dataStr		String to log
	 */
	void dataHourly(const std::string& dataSource, const std::string& dataStr) const override ;

	/**
	 * log a daily data event
	 * @param dataSource	Name of data source
	 * @param dataStr		String to log
	 */
	void dataDaily(const std::string& dataSource, const std::string& dataStr) const override ;

protected:
	friend class ILogger ;
	static Mutex		mMutex ;
	static bool			mConsoleLogging ;
	static std::string	mForwardHost ;
} ;

}

#endif /* LOGGERSYSLOG_H_ */
