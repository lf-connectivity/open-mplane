/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelayUnitFPGA.cpp
 * \brief     fpga clock units
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IHardwareSettings.h"

#include "DelayUnit/DelayUnitFPGA.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const DelayUnitFPGA DelayUnitFPGA::UNIT ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float DelayUnitFPGA::to_ns(float delay, float lineRateMHz) const
{
	std::shared_ptr<const IHardwareSettings> hardwareSettings( IHardwareSettings::getInstance() );

	const double dspClock(hardwareSettings->getDspClock().getDbl(Frequency::Hz)) ;

	float ns = delay / dspClock * 1.0e9 ;
	return ns ;
}

//-------------------------------------------------------------------------------------------------------------
float DelayUnitFPGA::from_ns(float delay_ns, float lineRateMHz) const
{
	std::shared_ptr<const IHardwareSettings> hardwareSettings( IHardwareSettings::getInstance() );

	const double dspClock(hardwareSettings->getDspClock().getDbl(Frequency::Hz)) ;

	float fpga_real = delay_ns * dspClock / 1.0e9 ;
	unsigned fpga = (unsigned)(fpga_real+0.5) ;
	return fpga ;
}
