/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LoggerHistorySyslog.h
 * \brief     An ILogger that outputs to syslog AND stored certain levels into a rolling buffer
 *
 *
 * \details   Derived from LoggerSyslog but also saves any log with level >= specified level into a rolling buffer. This rolling buffer
 * 				can then be accessed to the application.
 *
 */


#ifndef LOGGING_INC_LOGGERHISTORYSYSLOG_H_
#define LOGGING_INC_LOGGERHISTORYSYSLOG_H_

#include <vector>

#include "LogHistoryBuffer.h"
#include "LoggerSyslog.h"

namespace Mplane {

/*!
 * \class  LoggerHistorySyslog
 * \brief
 * \details
 *
 */
class LoggerHistorySyslog : public LoggerSyslog {
public:
	LoggerHistorySyslog(ILoggable* parent, const std::string& instanceName, const std::string& groupName) ;
	virtual ~LoggerHistorySyslog() ;

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

private:
	std::shared_ptr<LogHistoryBuffer> mHistory ;
} ;

}

#endif /* LOGGING_INC_LOGGERHISTORYSYSLOG_H_ */
