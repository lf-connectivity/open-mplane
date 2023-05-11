/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIMeasAdc.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TestIMeasAdc.h"

using namespace Mplane;

Mplane::TestIMeasAdc::TestIMeasAdc() {
}

Mplane::TestIMeasAdc::~TestIMeasAdc() {
}

ReturnType::State Mplane::TestIMeasAdc::getAdcRms(Power& power) {
	power = Power(1.0) ;
	return ReturnType::RT_OK ;
}

ReturnType::State Mplane::TestIMeasAdc::getAdcRms(Power& power,
		unsigned & adcRaw) {
	power = Power(1.0) ;
	adcRaw = 123 ;
	return ReturnType::RT_OK ;
}
//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
