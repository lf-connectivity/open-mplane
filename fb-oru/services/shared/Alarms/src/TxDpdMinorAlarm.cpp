/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxDpdMinorAlarm.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DpdTxFaultMinor.h"
#include "TxDpdMinorAlarm.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
const char* Tx1DpdMinorAlarm::NAME="Tx1DpdMinorAlarm";

const char* Tx2DpdMinorAlarm::NAME="Tx2DpdMinorAlarm";

const char* Tx3DpdMinorAlarm::NAME="Tx3DpdMinorAlarm";

const char* Tx4DpdMinorAlarm::NAME="Tx4DpdMinorAlarm";

//-------------------------------------------------------------------------------------------------------------
Tx1DpdMinorAlarm::Tx1DpdMinorAlarm()  :
			Alarm(Tx1DpdMinorAlarm::NAME, "DPD minor alarm on TX1", IAlarm::ALARM_MINOR)
{
    registerFaults( {DpdTx1FaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx1DpdMinorAlarm::~Tx1DpdMinorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx2DpdMinorAlarm::Tx2DpdMinorAlarm()  :
			Alarm(Tx2DpdMinorAlarm::NAME, "DPD minor alarm on TX2", IAlarm::ALARM_MINOR)
{
    registerFaults( {DpdTx2FaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx2DpdMinorAlarm::~Tx2DpdMinorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx3DpdMinorAlarm::Tx3DpdMinorAlarm()  :
			Alarm(Tx3DpdMinorAlarm::NAME, "DPD minor alarm on TX3", IAlarm::ALARM_MINOR)
{
    registerFaults( {DpdTx3FaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx3DpdMinorAlarm::~Tx3DpdMinorAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx4DpdMinorAlarm::Tx4DpdMinorAlarm()  :
			Alarm(Tx4DpdMinorAlarm::NAME, "DPD minor alarm on TX4", IAlarm::ALARM_MINOR)
{
    registerFaults( {DpdTx4FaultMinor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx4DpdMinorAlarm::~Tx4DpdMinorAlarm()
{
}
