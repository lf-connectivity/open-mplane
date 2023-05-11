/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdMajorAlarm.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DpdMajorAlarm.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DpdMajorAlarm::DpdMajorAlarm(const std::set<std::string> &majorFaultNames) :
	Alarm("DpdMajorAlarm", "DPD major fault", IAlarm::ALARM_MAJOR)
{
	registerFaults(majorFaultNames) ;
}

//-------------------------------------------------------------------------------------------------------------
DpdMajorAlarm::~DpdMajorAlarm()
{
}
