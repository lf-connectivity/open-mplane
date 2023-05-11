/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelayUnitUI.cpp
 * \brief     UI delay units (1 / line rate)
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "Maths.h"

#include "DelayUnit/DelayUnitUI.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const DelayUnitUI DelayUnitUI::UNIT ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float DelayUnitUI::to_ns(float delay, float lineRateMHz) const
{
	float ns = delay * 1000.0 / lineRateMHz ;
	return ns ;
}

//-------------------------------------------------------------------------------------------------------------
float DelayUnitUI::from_ns(float delay_ns, float lineRateMHz) const
{
	float ui = delay_ns / 1000.0 * lineRateMHz ;
	return ui ;
}
