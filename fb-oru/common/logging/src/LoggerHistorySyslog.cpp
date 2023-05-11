/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LoggerHistorySyslog.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "LoggerHistorySyslog.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LoggerHistorySyslog::LoggerHistorySyslog(ILoggable *parent,
		const std::string &instanceName, const std::string &groupName) :
	LoggerSyslog(parent, instanceName, groupName),
	mHistory( std::dynamic_pointer_cast<LogHistoryBuffer>(ILogHistory::singleton()) )
{
}

//-------------------------------------------------------------------------------------------------------------
LoggerHistorySyslog::~LoggerHistorySyslog()
{
}

//-------------------------------------------------------------------------------------------------------------
void LoggerHistorySyslog::eventData(const std::string &eventStr) const
{
	mHistory->logData(eventStr) ;
	this->LoggerSyslog::eventData(eventStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LoggerHistorySyslog::eventInfo(const std::string &eventStr) const
{
	mHistory->logInfo(eventStr) ;
	this->LoggerSyslog::eventInfo(eventStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LoggerHistorySyslog::eventWarning(const std::string &eventStr) const
{
	mHistory->logWarning(eventStr) ;
	this->LoggerSyslog::eventWarning(eventStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LoggerHistorySyslog::eventError(const std::string &eventStr) const
{
	mHistory->logError(eventStr) ;
	this->LoggerSyslog::eventError(eventStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LoggerHistorySyslog::eventFatal(const std::string &eventStr) const
{
	mHistory->logFatal(eventStr) ;
	this->LoggerSyslog::eventFatal(eventStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LoggerHistorySyslog::logDebugNormal(const std::string &debugStr) const
{
	mHistory->logData(debugStr) ;
	this->LoggerSyslog::logDebugNormal(debugStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LoggerHistorySyslog::logDebugVerbose(const std::string &debugStr) const
{
	mHistory->logData(debugStr) ;
	this->LoggerSyslog::logDebugVerbose(debugStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LoggerHistorySyslog::dataHourly(const std::string &dataSource,
		const std::string &dataStr) const
{
	mHistory->logData(dataStr) ;
	this->LoggerSyslog::eventData(dataStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void LoggerHistorySyslog::dataDaily(const std::string &dataSource,
		const std::string &dataStr) const
{
	mHistory->logData(dataStr) ;
	this->LoggerSyslog::eventData(dataStr) ;
}
