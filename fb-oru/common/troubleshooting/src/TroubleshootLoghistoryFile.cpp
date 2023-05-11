/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootLoghistoryFile.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ILogHistory.h"
#include "TroubleshootLoghistoryFile.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TroubleshootLoghistoryFile::TroubleshootLoghistoryFile(const std::string &filename) :
	TroubleshootFile(filename)
{
}

//-------------------------------------------------------------------------------------------------------------
TroubleshootLoghistoryFile::~TroubleshootLoghistoryFile()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string TroubleshootLoghistoryFile::dataGather()
{
	std::vector<std::string> history(ILogHistory::singleton()->getHistory()) ;
	std::string str ;
	for (auto s : history)
	{
		str += s + "\n" ;
	}
	return str ;
}
