/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PllMajorAlarm.cpp
 * \brief     PllMajor alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PllMajorAlarm.h"

#include "SynthClockFault.h"
#include "RxPllLockFaultMajor.h"
#include "RefPllLockFaultMajor.h"
#include "TxPllLockFaultMajor.h"
#include "DpdPllLockFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* PllMajorAlarm::NAME="PllMajorAlarm";

//-------------------------------------------------------------------------------------------------------------
PllMajorAlarm::PllMajorAlarm() :
	Alarm(NAME, "PLL is out of lock")
{
    registerFaults( {SynthClockFault::NAME,
		 	 	 	 RxPllLockFaultMajor::NAME,
					 TxPllLockFaultMajor::NAME,
					 DpdPllLockFaultMajor::NAME,
					 RefPllLockFaultMajor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
PllMajorAlarm::~PllMajorAlarm()
{
}
