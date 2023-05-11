/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardwareFastVss.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "WaveformHardwareFastVss.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveformHardwareFastVss::WaveformHardwareFastVss(unsigned index, unsigned port) :
	WaveformHardware(index, port)
{
}

//-------------------------------------------------------------------------------------------------------------
WaveformHardwareFastVss::~WaveformHardwareFastVss()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareFastVss::checkCarrier(std::string& error) const
{
	// Carrier not required
	error = "" ;
	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardwareFastVss::getInstanceSampleRateKsps(ICarrier::Type carrierType) const
{
	// Max rate is ~0.15Ksps
	return 1 ;
}
