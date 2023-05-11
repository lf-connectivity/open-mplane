/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxShutdownAlarm.cpp
 * \brief     TxShutdown alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxShutdownAlarm.h"

#include "SynthClockFault.h"
#include "Cpri0LossOfFrameFaultMajor.h"
#include "Cpri0LossOfSignalFaultMajor.h"
#include "Cpri0RemoteAlarmIndFaultMajor.h"
#include "Cpri0SapDefectIndFaultMajor.h"
#include "DpdPllLockFaultMajor.h"
#include "PclTxOverPowerFaultMajor.h"
#include "PclTxConvergenceFaultMajor.h"
#include "BoardTxOverTemperatureFaultMajor.h"
#include "PaOverTemperatureFaultMajor.h"
#include "TxOverPowerFaultMajor.h"
#include "TxPllLockFaultMajor.h"
#include "BoardTxUnderTemperatureFaultMajor.h"
#include "PaUnderTemperatureFaultMajor.h"
#include "PopTripTxFaultMajor.h"
#include "SrlTxFaultMajor.h"
#include "DpdTxFaultMajor.h"
#include "HeartBeatFaultMajor.h"
#include "TxPowerMeasurementFaultMajor.h"
#include "RxPllLockFaultMajor.h"
#include "RefPllLockFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Tx1ShutdownAlarm::NAME="Tx1ShutdownAlarm";

const char* Tx2ShutdownAlarm::NAME="Tx2ShutdownAlarm";

const char* Tx3ShutdownAlarm::NAME="Tx3ShutdownAlarm";

const char* Tx4ShutdownAlarm::NAME="Tx4ShutdownAlarm";

//-------------------------------------------------------------------------------------------------------------
Tx1ShutdownAlarm::Tx1ShutdownAlarm() :
		AlarmLatched(Tx1ShutdownAlarm::NAME, "TX1 is about to shut down", IAlarm::ALARM_CRITICAL)
{
    registerFaults( {SynthClockFault::NAME,
    			     Cpri0LossOfFrameFaultMajor::NAME,
					 Cpri0LossOfSignalFaultMajor::NAME,
					 Cpri0RemoteAlarmIndicationFaultMajor::NAME,
					 Cpri0SapDefectIndFaultMajor::NAME,
					 DpdPllLockFaultMajor::NAME,
					 PclTx1ConvergenceFaultMajor::NAME,
					 PclTx1OverPowerFaultMajor::NAME,
					 BoardTx1OverTemperatureFaultMajor::NAME,
					// FpgaOverTemperatureFaultMajor::NAME,
					 Pa1OverTemperatureFaultMajor::NAME,
					// RadioCardPsuOverVoltageFaultMajor::NAME,
					// RadioCardPsuUnderVoltageFaultMajor::NAME,
					 Tx1OverPowerFaultMajor::NAME,
					 TxPllLockFaultMajor::NAME,
					 BoardTx1UnderTemperatureFaultMajor::NAME,
					// FpgaUnderTemperatureFaultMajor::NAME,
					 Pa1UnderTemperatureFaultMajor::NAME,
					 PopTripTx1FaultMajor::NAME,
					 SrlTx1FaultMajor::NAME,
					 DpdTx1FaultMajor::NAME,
					 HeartBeatFaultMajor::NAME,
                     Tx1PowerMeasurementFaultMajor::NAME,
					 RxPllLockFaultMajor::NAME,
					 RefPllLockFaultMajor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx1ShutdownAlarm::~Tx1ShutdownAlarm()
{
}


//-------------------------------------------------------------------------------------------------------------
Tx2ShutdownAlarm::Tx2ShutdownAlarm() :
		AlarmLatched(Tx2ShutdownAlarm::NAME, "TX2 is about to shut down", IAlarm::ALARM_CRITICAL)
{
    registerFaults( {SynthClockFault::NAME,
    			     Cpri0LossOfFrameFaultMajor::NAME,
					 Cpri0LossOfSignalFaultMajor::NAME,
					 Cpri0RemoteAlarmIndicationFaultMajor::NAME,
					 Cpri0SapDefectIndFaultMajor::NAME,
					 DpdPllLockFaultMajor::NAME,
					 PclTx2ConvergenceFaultMajor::NAME,
					 PclTx2OverPowerFaultMajor::NAME,
					 BoardTx2OverTemperatureFaultMajor::NAME,
					// FpgaOverTemperatureFaultMajor::NAME,
					 Pa2OverTemperatureFaultMajor::NAME,
					// RadioCardPsuOverVoltageFaultMajor::NAME,
					// RadioCardPsuUnderVoltageFaultMajor::NAME,
					 Tx2OverPowerFaultMajor::NAME,
					 TxPllLockFaultMajor::NAME,
					 BoardTx2UnderTemperatureFaultMajor::NAME,
					// FpgaUnderTemperatureFaultMajor::NAME,
					 Pa2UnderTemperatureFaultMajor::NAME,
					 PopTripTx2FaultMajor::NAME,
					 SrlTx2FaultMajor::NAME,
					 DpdTx2FaultMajor::NAME,
					 HeartBeatFaultMajor::NAME,
                     Tx2PowerMeasurementFaultMajor::NAME,
					 RxPllLockFaultMajor::NAME,
					 RefPllLockFaultMajor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx2ShutdownAlarm::~Tx2ShutdownAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx3ShutdownAlarm::Tx3ShutdownAlarm() :
		AlarmLatched(Tx3ShutdownAlarm::NAME, "TX3 is about to shut down", IAlarm::ALARM_CRITICAL)
{
    registerFaults( {SynthClockFault::NAME,
    			     Cpri0LossOfFrameFaultMajor::NAME,
					 Cpri0LossOfSignalFaultMajor::NAME,
					 Cpri0RemoteAlarmIndicationFaultMajor::NAME,
					 Cpri0SapDefectIndFaultMajor::NAME,
					 DpdPllLockFaultMajor::NAME,
					 PclTx3ConvergenceFaultMajor::NAME,
					 PclTx3OverPowerFaultMajor::NAME,
					 BoardTx3OverTemperatureFaultMajor::NAME,
					// FpgaOverTemperatureFaultMajor::NAME,
					 Pa3OverTemperatureFaultMajor::NAME,
					// RadioCardPsuOverVoltageFaultMajor::NAME,
					// RadioCardPsuUnderVoltageFaultMajor::NAME,
					 Tx3OverPowerFaultMajor::NAME,
					 TxPllLockFaultMajor::NAME,
					 BoardTx3UnderTemperatureFaultMajor::NAME,
					// FpgaUnderTemperatureFaultMajor::NAME,
					 Pa3UnderTemperatureFaultMajor::NAME,
					 PopTripTx3FaultMajor::NAME,
					 SrlTx3FaultMajor::NAME,
					 DpdTx3FaultMajor::NAME,
					 HeartBeatFaultMajor::NAME,
                     Tx3PowerMeasurementFaultMajor::NAME,
					 RxPllLockFaultMajor::NAME,
					 RefPllLockFaultMajor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx3ShutdownAlarm::~Tx3ShutdownAlarm()
{
}

//-------------------------------------------------------------------------------------------------------------
Tx4ShutdownAlarm::Tx4ShutdownAlarm() :
		AlarmLatched(Tx4ShutdownAlarm::NAME, "TX4 is about to shut down", IAlarm::ALARM_CRITICAL)
{
    registerFaults( {SynthClockFault::NAME,
    			     Cpri0LossOfFrameFaultMajor::NAME,
					 Cpri0LossOfSignalFaultMajor::NAME,
					 Cpri0RemoteAlarmIndicationFaultMajor::NAME,
					 Cpri0SapDefectIndFaultMajor::NAME,
					 DpdPllLockFaultMajor::NAME,
					 PclTx4ConvergenceFaultMajor::NAME,
					 PclTx4OverPowerFaultMajor::NAME,
					 BoardTx4OverTemperatureFaultMajor::NAME,
					// FpgaOverTemperatureFaultMajor::NAME,
					 Pa4OverTemperatureFaultMajor::NAME,
					// RadioCardPsuOverVoltageFaultMajor::NAME,
					// RadioCardPsuUnderVoltageFaultMajor::NAME,
					 Tx4OverPowerFaultMajor::NAME,
					 TxPllLockFaultMajor::NAME,
					 BoardTx4UnderTemperatureFaultMajor::NAME,
					// FpgaUnderTemperatureFaultMajor::NAME,
					 Pa4UnderTemperatureFaultMajor::NAME,
					 PopTripTx4FaultMajor::NAME,
					 SrlTx4FaultMajor::NAME,
					 DpdTx4FaultMajor::NAME,
					 HeartBeatFaultMajor::NAME,
                     Tx4PowerMeasurementFaultMajor::NAME,
					 RxPllLockFaultMajor::NAME,
					 RefPllLockFaultMajor::NAME} );
}

//-------------------------------------------------------------------------------------------------------------
Tx4ShutdownAlarm::~Tx4ShutdownAlarm()
{
}
