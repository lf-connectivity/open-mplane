/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxDegradedAlarm.cpp
 * \brief     TxDegraded alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxDegradedAlarm.h"

#include "TxOverPowerFaultMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Tx1DegradedAlarm::NAME="Tx1DegradedAlarm";

const char* Tx2DegradedAlarm::NAME="Tx2DegradedAlarm";

const char* Tx3DegradedAlarm::NAME="Tx3DegradedAlarm";

const char* Tx4DegradedAlarm::NAME="Tx4DegradedAlarm";

//-------------------------------------------------------------------------------------------------------------
Tx1DegradedAlarm::Tx1DegradedAlarm() :
	Alarm(Tx1DegradedAlarm::NAME, "TX1 may be out of specification limits", IAlarm::ALARM_MINOR)
{
    registerFaults( {Tx1OverPowerFaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx1DegradedAlarm::~Tx1DegradedAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx2DegradedAlarm::Tx2DegradedAlarm() :
	Alarm(Tx2DegradedAlarm::NAME, "TX2 may be out of specification limits", IAlarm::ALARM_MINOR)
{
    registerFaults( {Tx2OverPowerFaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx2DegradedAlarm::~Tx2DegradedAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx3DegradedAlarm::Tx3DegradedAlarm() :
	Alarm(Tx3DegradedAlarm::NAME, "TX3 may be out of specification limits", IAlarm::ALARM_MINOR)
{
    registerFaults( {Tx3OverPowerFaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx3DegradedAlarm::~Tx3DegradedAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx4DegradedAlarm::Tx4DegradedAlarm() :
	Alarm(Tx4DegradedAlarm::NAME, "TX4 may be out of specification limits", IAlarm::ALARM_MINOR)
{
    registerFaults( {Tx4OverPowerFaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx4DegradedAlarm::~Tx4DegradedAlarm()
{
}
