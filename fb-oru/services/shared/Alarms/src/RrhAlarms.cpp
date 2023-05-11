/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FelixAlarm.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "RrhAlarms.h"

#include "PllMajorAlarm.h"
#include "Cpri0MajorAlarm.h"
#include "RadioTempMajorAlarm.h"
#include "RadioTempMinorAlarm.h"
#include "RxMajorAlarm.h"
#include "TxShutdownAlarm.h"
#include "TxDegradedAlarm.h"
#include "PaTempMajorAlarm.h"
#include "PaTempMinorAlarm.h"
#include "VswrTxAlarm.h"
#include "TxBbIqAlarm.h"
#include "HeartBeatMajorAlarm.h"
#include "TxDpdMinorAlarm.h"


using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RrhAlarms::RrhAlarms()
{
	// Create PLL major alarm
	mPllMajorAlarm = make_alarm<PllMajorAlarm>();

	// Create CPRI0 major alarm
	mCpri0MajorAlarm = make_alarm<Cpri0MajorAlarm>();

	// Create radio temperature alarms
	mRadioTempMajorAlarm = make_alarm<RadioTempMajorAlarm>();
	mRadioTempMinorAlarm = make_alarm<RadioTempMinorAlarm>();

	// Create and populate Rx major alarms vector
	mRxMajorAlarm.push_back( make_alarm<Rx1MajorAlarm>());
	mRxMajorAlarm.push_back( make_alarm<Rx2MajorAlarm>());
	mRxMajorAlarm.push_back( make_alarm<Rx3MajorAlarm>());
	mRxMajorAlarm.push_back( make_alarm<Rx4MajorAlarm>());

	// Create and populate PA major alarms vector
	mPaTempMajorAlarm.push_back( make_alarm<Pa1TempMajorAlarm>() );
	mPaTempMajorAlarm.push_back( make_alarm<Pa2TempMajorAlarm>() );
	mPaTempMajorAlarm.push_back( make_alarm<Pa3TempMajorAlarm>() );
	mPaTempMajorAlarm.push_back( make_alarm<Pa4TempMajorAlarm>() );

	// Create and populate PA minor alarms vector
	mPaTempMinorAlarm.push_back( make_alarm<Pa1TempMinorAlarm>() );
	mPaTempMinorAlarm.push_back( make_alarm<Pa2TempMinorAlarm>() );
	mPaTempMinorAlarm.push_back( make_alarm<Pa3TempMinorAlarm>() );
	mPaTempMinorAlarm.push_back( make_alarm<Pa4TempMinorAlarm>() );

	// Create and populate Tx shutdown alarms vector
	mTxShutdownAlarm.push_back( make_alarm<Tx1ShutdownAlarm>() );
	mTxShutdownAlarm.push_back( make_alarm<Tx2ShutdownAlarm>() );
	mTxShutdownAlarm.push_back( make_alarm<Tx3ShutdownAlarm>() );
	mTxShutdownAlarm.push_back( make_alarm<Tx4ShutdownAlarm>() );

	// Create and populate Tx degraded alarms vector
	mTxDegradedAlarm.push_back( make_alarm<Tx1DegradedAlarm>() );
	mTxDegradedAlarm.push_back( make_alarm<Tx2DegradedAlarm>() );
	mTxDegradedAlarm.push_back( make_alarm<Tx3DegradedAlarm>() );
	mTxDegradedAlarm.push_back( make_alarm<Tx4DegradedAlarm>() );

	// Create and populate VSWR alarms vector
	mVswrTxAlarm.push_back( make_alarm<VswrTx1Alarm>() );
	mVswrTxAlarm.push_back( make_alarm<VswrTx2Alarm>() );
	mVswrTxAlarm.push_back( make_alarm<VswrTx3Alarm>() );
	mVswrTxAlarm.push_back( make_alarm<VswrTx4Alarm>() );

	// Create and populate Tx baseband IQ alarms vector
	mTxBbIqAlarm.push_back( make_alarm<Tx1BbIqAlarm>() );
	mTxBbIqAlarm.push_back( make_alarm<Tx2BbIqAlarm>() );
	mTxBbIqAlarm.push_back( make_alarm<Tx3BbIqAlarm>() );
	mTxBbIqAlarm.push_back( make_alarm<Tx4BbIqAlarm>() );

	// Create heartbeat alarm
	mHeartBeatAlarm = make_alarm<HeartBeatAlarm>();

	// Create and populate Tx DPD minor alarms vector
	mTxDpdMinorAlarm.push_back( make_alarm<Tx1DpdMinorAlarm>() );
	mTxDpdMinorAlarm.push_back( make_alarm<Tx2DpdMinorAlarm>() );
	mTxDpdMinorAlarm.push_back( make_alarm<Tx3DpdMinorAlarm>() );
	mTxDpdMinorAlarm.push_back( make_alarm<Tx4DpdMinorAlarm>() );

}

//-------------------------------------------------------------------------------------------------------------
RrhAlarms::~RrhAlarms()
{
	// shared pointers will be taken care of here
}
