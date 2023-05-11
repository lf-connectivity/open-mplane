/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxMajorAlarm.cpp
 * \brief     RxMajor alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RxMajorAlarm.h"

#include "SynthClockFault.h"
#include "RxPllLockFaultMajor.h"
#include "RefPllLockFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Rx1MajorAlarm::NAME="Rx1MajorAlarm";

const char* Rx2MajorAlarm::NAME="Rx2MajorAlarm";

const char* Rx3MajorAlarm::NAME="Rx3MajorAlarm";

const char* Rx4MajorAlarm::NAME="Rx4MajorAlarm";

//-------------------------------------------------------------------------------------------------------------
Rx1MajorAlarm::Rx1MajorAlarm() :
		AlarmLatched(NAME, "Receiver 1 clocks fault")

{
    registerFaults( {SynthClockFault::NAME,
    				 RxPllLockFaultMajor::NAME,
					 RefPllLockFaultMajor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Rx1MajorAlarm::~Rx1MajorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Rx2MajorAlarm::Rx2MajorAlarm() :
		AlarmLatched(NAME, "Receiver 2 clocks fault")
{
    registerFaults( {SynthClockFault::NAME,
    				 RxPllLockFaultMajor::NAME,
					 RefPllLockFaultMajor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Rx2MajorAlarm::~Rx2MajorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Rx3MajorAlarm::Rx3MajorAlarm() :
		AlarmLatched(NAME, "Receiver 3 clocks fault")
{
    registerFaults( {SynthClockFault::NAME,
    				 RxPllLockFaultMajor::NAME,
					 RefPllLockFaultMajor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Rx3MajorAlarm::~Rx3MajorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Rx4MajorAlarm::Rx4MajorAlarm() :
		AlarmLatched(NAME, "Receiver 4 clocks fault")
{
    registerFaults( {SynthClockFault::NAME,
    				 RxPllLockFaultMajor::NAME,
					 RefPllLockFaultMajor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Rx4MajorAlarm::~Rx4MajorAlarm()
{
}
