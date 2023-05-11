/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelayUnitCLK128.cpp
 * \brief     dsl clock units
 *
 *
 * \details   Uses the CLK delay units to perform it's calculations
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "DelayUnit/DelayUnitCLK128.h"
#include "DelayUnit/DelayUnitCLK.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const DelayUnitCLK128 DelayUnitCLK128::UNIT ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float DelayUnitCLK128::to_ns(float delay, float lineRateMHz) const
{
	return DelayUnitCLK::UNIT.to_ns(delay/128.0, lineRateMHz) ;
}

//-------------------------------------------------------------------------------------------------------------
float DelayUnitCLK128::from_ns(float delay_ns, float lineRateMHz) const
{
	return DelayUnitCLK::UNIT.from_ns(delay_ns, lineRateMHz) * 128.0 ;
}
