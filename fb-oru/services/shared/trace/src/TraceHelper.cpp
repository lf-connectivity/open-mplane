/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TraceHelper.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ITraceMgr.h"

#include "TraceLoghistoryFile.h"
#include "TraceExampleFile.h"

#include "TraceHelper.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void TraceHelper::commonSetup()
{
	// add trace for the logs
	ITraceMgr::singleton()->addFile(std::make_shared<TraceLoghistoryFile>());

	// Firmware trace
	ITraceMgr::singleton()->addFile(std::make_shared<TraceExampleFile>());

}
