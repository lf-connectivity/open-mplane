/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelayUnitFpgaTimer.cpp
 * \brief     fpga timer units
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IHardwareSettings.h"

#include "DelayUnit/DelayUnitFpgaTimer.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const DelayUnitFpgaTimer DelayUnitFpgaTimer::UNIT ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float DelayUnitFpgaTimer::to_ns(float delay, float lineRateMHz) const
{
	std::shared_ptr<const IHardwareSettings> hardwareSettings( IHardwareSettings::getInstance() );

	const double fpgaAfTimerFreq( hardwareSettings->getFpgaAfTimerFreq().getDbl(Frequency::Hz) ) ;
	float ns = delay / fpgaAfTimerFreq * 1.0e9 ;

	return ns ;
}

//-------------------------------------------------------------------------------------------------------------
float DelayUnitFpgaTimer::from_ns(float delay_ns, float lineRateMHz) const
{
	std::shared_ptr<const IHardwareSettings> hardwareSettings( IHardwareSettings::getInstance() );

	const double fpgaAfTimerFreq( hardwareSettings->getFpgaAfTimerFreq().getDbl(Frequency::Hz) ) ;
	float fpgaTimerValue = delay_ns * fpgaAfTimerFreq / 1.0e9 ;

	return fpgaTimerValue ;
}
