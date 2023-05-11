/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdMinorAlarm.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DpdMinorAlarm.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdMinorAlarm::DpdMinorAlarm(const std::set<std::string> &minorFaultNames) :
	Alarm("DpdMinorAlarm", "DPD minor fault", IAlarm::ALARM_MINOR)
{
	registerFaults(minorFaultNames) ;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdMinorAlarm::~DpdMinorAlarm()
{
}
