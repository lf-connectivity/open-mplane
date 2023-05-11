/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LogHistoryBuffer.h
 * \brief     Singleton buffer for LoggerHistorySyslog class
 *
 *
 * \details   Stores logs into a rolling buffer
 *
 */


#ifndef LOGGING_INC_LogHistoryBuffer_H_
#define LOGGING_INC_LogHistoryBuffer_H_

#include <atomic>
#include <mutex>
#include <memory>
#include <string>
#include <vector>
#include <list>

#include "ILoggable.h"
#include "ILogHistory.h"

namespace Mplane {

/*!
 * \class  LogHistoryBuffer
 * \brief
 * \details
 *
 */
class LogHistoryBuffer : public virtual ILogHistory {
public:
	LogHistoryBuffer() ;
	virtual ~LogHistoryBuffer() ;


	/**
	 * Get the buffered history logs
	 */
	virtual std::vector<std::string> getHistory() const override ;

	/**
	 * Change the history logging level
	 */
	virtual void setLogLevel(ILoggable::LogLevel level) override ;

	/**
	 * Change the history depth
	 */
	virtual void setHistoryDepth(unsigned depth) override ;

	/**
	 * Clear history (Mainly for debug)
	 */
	virtual void clear() override ;

	/**
	 * Display contents for debug
	 */
	virtual void show() override ;


	// History API

	/**
	 * log a data log
	 */
	void logData(const std::string& logStr) ;

	/**
	 * log informational log
	 */
	void logInfo(const std::string& logStr) ;

	/**
	 * log a warning
	 */
	void logWarning(const std::string& logStr) ;

	/**
	 * log a non-fatal error
	 */
	void logError(const std::string& logStr) ;

	/**
	 * log a fatal error (and terminate)
	 */
	void logFatal(const std::string& logStr) ;

	/**
	 * Log some debug
	 */
	void logDebug(const std::string& debugStr) ;

private:
	void addLog(const std::string& type, const std::string& log) ;

private:
	mutable std::mutex mMutex ;
	std::list<std::string> mBuffer ;
	std::atomic<ILoggable::LogLevel> mLevel ;
	unsigned mDepth ;
} ;

}

#endif /* LOGGING_INC_LogHistoryBuffer_H_ */
