/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxBbIqAlarm.cpp
 * \brief     TxBbIq alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxBbIqAlarm.h"

#include "TxOverPowerFaultMinor.h"
#include "TxUnderPowerFaultMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Tx1BbIqAlarm::NAME="Tx1BbIqAlarm";

const char* Tx2BbIqAlarm::NAME="Tx2BbIqAlarm";

const char* Tx3BbIqAlarm::NAME="Tx3BbIqAlarm";

const char* Tx4BbIqAlarm::NAME="Tx4BbIqAlarm";

//-------------------------------------------------------------------------------------------------------------
Tx1BbIqAlarm::Tx1BbIqAlarm() :
	Alarm(Tx1BbIqAlarm::NAME, "BB IQ input too high/low on TX1", IAlarm::ALARM_MINOR)
{
    registerFaults( {Tx1OverPowerFaultMinor::NAME,
    			     Tx1UnderPowerFaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx1BbIqAlarm::~Tx1BbIqAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx2BbIqAlarm::Tx2BbIqAlarm() :
	Alarm(Tx2BbIqAlarm::NAME, "BB IQ input too high/low on TX2", IAlarm::ALARM_MINOR)
{
    registerFaults( {Tx2OverPowerFaultMinor::NAME,
    			     Tx2UnderPowerFaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx2BbIqAlarm::~Tx2BbIqAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx3BbIqAlarm::Tx3BbIqAlarm() :
	Alarm(Tx3BbIqAlarm::NAME, "BB IQ input too high/low on TX3", IAlarm::ALARM_MINOR)
{
    registerFaults( {Tx3OverPowerFaultMinor::NAME,
    			     Tx3UnderPowerFaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx3BbIqAlarm::~Tx3BbIqAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx4BbIqAlarm::Tx4BbIqAlarm() :
	Alarm(Tx4BbIqAlarm::NAME, "BB IQ input too high/low on TX4", IAlarm::ALARM_MINOR)
{
    registerFaults( {Tx4OverPowerFaultMinor::NAME,
    			     Tx4UnderPowerFaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx4BbIqAlarm::~Tx4BbIqAlarm()
{
}
