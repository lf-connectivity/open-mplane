/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TraceLoghistoryFile.cpp
 * \brief     An IORanLogFile for logging trace history
 *
 *
 * \details   Creates a tracing file which contains the rolling history of previous logs
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ILogHistory.h"
#include "TraceLoghistoryFile.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TraceLoghistoryFile::TraceLoghistoryFile(const std::string &filename)
	: TraceFile(filename)
{
}

//-------------------------------------------------------------------------------------------------------------
TraceLoghistoryFile::~TraceLoghistoryFile()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string TraceLoghistoryFile::dataGather()
{
	std::vector<std::string> history(ILogHistory::singleton()->getHistory());
	std::string str;
	for (auto s : history)
	{
		str += s + "\n";
	}
	return str;
}
