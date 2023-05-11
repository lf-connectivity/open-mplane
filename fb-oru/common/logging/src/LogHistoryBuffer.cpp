/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LogHistoryBuffer.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include "LogHistoryBuffer.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILogHistory> ILogHistory::singleton()
{
	static std::shared_ptr<ILogHistory> instance(std::make_shared<LogHistoryBuffer>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LogHistoryBuffer::LogHistoryBuffer() :
	mMutex(),
	mBuffer(),
	mLevel(ILoggable::LOG_LEVEL_WARNING),
	mDepth(512)
{
}

//-------------------------------------------------------------------------------------------------------------
LogHistoryBuffer::~LogHistoryBuffer()
{
}

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::setHistoryDepth(unsigned depth)
{
	if (depth ==0)
		return ;

	std::unique_lock<std::mutex> lock(mMutex) ;
	mDepth = depth ;

}

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::clear()
{
	std::unique_lock<std::mutex> lock(mMutex) ;
	mBuffer.clear() ;
}

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::show()
{
	std::vector<std::string> contents(getHistory()) ;
	std::cout << "-- Log History --" << std::endl ;
	for (auto log : contents)
		std::cout << log << std::endl ;
	std::cout << "-----------------" << std::endl ;
}


//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> LogHistoryBuffer::getHistory() const
{
	std::unique_lock<std::mutex> lock(mMutex) ;

	std::vector<std::string> history ;
	for (auto entry : mBuffer)
		history.push_back(entry) ;

	return history ;
}

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::setLogLevel(ILoggable::LogLevel level)
{
	mLevel = level ;

	// NOTE: Does *NOT* clear out any existing logging
}

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::logData(const std::string &logStr)
{
	if (mLevel > ILoggable::LOG_LEVEL_DATA)
		return ;

	addLog("DATA", logStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::logInfo(const std::string &logStr)
{
	if (mLevel > ILoggable::LOG_LEVEL_INFO)
		return ;

	addLog("INFO", logStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::logWarning(const std::string &logStr)
{
	if (mLevel > ILoggable::LOG_LEVEL_WARNING)
		return ;

	addLog("WARN", logStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::logError(const std::string &logStr)
{
	if (mLevel > ILoggable::LOG_LEVEL_ERROR)
		return ;

	addLog("ERROR", logStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::logFatal(const std::string &logStr)
{
	if (mLevel > ILoggable::LOG_LEVEL_FATAL)
		return ;

	addLog("FATAL", logStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::logDebug(const std::string &debugStr)
{
	if (mLevel > ILoggable::LOG_LEVEL_DEBUG)
		return ;

	addLog("DEBUG", debugStr) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void LogHistoryBuffer::addLog(const std::string &type, const std::string &log)
{
	std::unique_lock<std::mutex> lock(mMutex) ;

	// check for start of rollover
	if (mBuffer.size() == mDepth)
	{
		mBuffer.pop_front() ;
	}

	// create a timestamp
	timespec tNow ;
	clock_gettime(CLOCK_REALTIME, &tNow) ;
	struct tm result ;
	struct tm  *ts = localtime_r(&tNow.tv_sec, &result);

	char buff[80];
	std::strftime(buff, sizeof(buff), "%H:%M:%S", ts);

	// store
	mBuffer.push_back(std::string(buff) + std::string(" [" + type + "] " + log)) ;
}
