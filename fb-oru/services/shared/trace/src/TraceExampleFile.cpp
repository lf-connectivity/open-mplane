/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TraceExampleFile.cpp
 * \brief     A TraceFile for example
 *
 *
 * \details   A TraceFile for example
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

//#include <iostream>
#include <string>
#include <sstream>

#include "TraceExampleFile.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TraceExampleFile::TraceExampleFile() :
	TraceFile("TraceExample.log")
{
}

//-------------------------------------------------------------------------------------------------------------
TraceExampleFile::~TraceExampleFile()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string TraceExampleFile::dataGather()
{
	std::stringstream ss;

	ss << "TRACE Example" << std::endl;

	return ss.str();
}
