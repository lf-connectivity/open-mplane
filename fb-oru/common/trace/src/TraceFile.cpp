/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TraceFile.cpp
 * \brief     Base class implementing a trace log file
 *
 *
 * \details   Base class implementing a trace log file. This base class needs a data gather function to be
 *            defined. Otherwise derived classes can override the dataGather() method.
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "TraceFile.h"

#include <string>


using namespace Mplane;

//=============================================================================================================
// FACTORY
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TraceFile::TraceFile(const std::string & filename)
	: ORanLogFile(filename)
{
}

//-------------------------------------------------------------------------------------------------------------
TraceFile::~TraceFile()
{
}
