/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelayUnitCLK.cpp
 * \brief     dsp clock units
 *
 *
 * \details   Uses the UI delay units to perform it's calculations
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IHardwareSettings.h"

#include "DelayUnit/DelayUnitCLK.h"
#include "DelayUnit/DelayUnitUI.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const DelayUnitCLK DelayUnitCLK::UNIT ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float DelayUnitCLK::to_ns(float delay, float lineRateMHz) const
{
	std::shared_ptr<const IHardwareSettings> hardwareSettings( IHardwareSettings::getInstance() );

	float ui = delay * static_cast<float>(hardwareSettings->getClockToUi()) ;

	return DelayUnitUI::UNIT.to_ns(ui, lineRateMHz) ;
}

//-------------------------------------------------------------------------------------------------------------
float DelayUnitCLK::from_ns(float delay_ns, float lineRateMHz) const
{
	std::shared_ptr<const IHardwareSettings> hardwareSettings( IHardwareSettings::getInstance() );

	float ui = DelayUnitUI::UNIT.from_ns(delay_ns, lineRateMHz) ;
	float clocks = ui / static_cast<float>(hardwareSettings->getClockToUi()) ;
	return clocks ;
}
