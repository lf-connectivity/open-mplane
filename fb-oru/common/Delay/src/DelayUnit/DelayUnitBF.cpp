/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelayUnitBF.cpp
 * \brief     Basic frame delay units
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

#include "DelayUnit/DelayUnitBF.h"

using namespace Mplane;


//=================================================================================================
// DATA

// 1 Basic Frame (BF) = 3.84MHz period
static const float BF_ns = 1000.0 / 3.84 ;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const DelayUnitBF DelayUnitBF::UNIT ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float DelayUnitBF::to_ns(float delay, float lineRateMHz) const
{
	float ns = delay * BF_ns ;
	return ns ;
}

//-------------------------------------------------------------------------------------------------------------
float DelayUnitBF::from_ns(float delay_ns, float lineRateMHz) const
{
	float bf = delay_ns / BF_ns ;

	// Ensure BF is positive
	while (bf < 0.0)
	{
		bf += 38400.0 ;
	}

	return bf ;
}
