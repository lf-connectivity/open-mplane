/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardwareRxFixedRate.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "WaveformHardwareRxFixedRate.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

static const unsigned SAMPLE_RATE_KSPS{61440} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::WaveformHardwareRxFixedRate::WaveformHardwareRxFixedRate(unsigned index, unsigned port) :
	WaveformHardware(index, port)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::WaveformHardwareRxFixedRate::~WaveformHardwareRxFixedRate()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::WaveformHardwareRxFixedRate::checkCarrier(std::string& error) const
{
	// Carrier not required
	error = "" ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardwareRxFixedRate::getInstanceSampleRateKsps(ICarrier::Type carrierType) const
{
	return SAMPLE_RATE_KSPS ;
}
