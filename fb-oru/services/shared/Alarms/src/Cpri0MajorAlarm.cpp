/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri0MajorAlarm.cpp
 * \brief     Cpri0 Major alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Cpri0MajorAlarm.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Cpri0MajorAlarm::NAME="Cpri0MajorAlarm";

//-------------------------------------------------------------------------------------------------------------
Cpri0MajorAlarm::Cpri0MajorAlarm() :
	Alarm(NAME, "CPRI0 has failed")
{
    registerFaults( {"Cpri0LossOfSignalMajorFault",
                     "Cpri0LossOfFrameMajorFault",
                     "Cpri0SapDefectIndMajorFault",
                     "Cpri0RemoteAlarmIndMajorFault"} ) ;
}

//-------------------------------------------------------------------------------------------------------------
Cpri0MajorAlarm::~Cpri0MajorAlarm()
{
}
