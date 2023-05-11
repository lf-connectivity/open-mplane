/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestRadioConfigFactory.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RadioConfig.h"

using namespace Mplane ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRadioConfigSetter> IRadioConfigSetter::singleton()
{
	const std::map<std::string, std::string> DEFAULTS{
		{ IRadioConfig::NUM_CARRIERS, 	"4" },

		{ IRadioConfig::NUM_TX, "4" },
		{ IRadioConfig::TX_MAX_AIR_FREQ, "3800000" },
		{ IRadioConfig::TX_MIN_AIR_FREQ, "700000" },
		{ IRadioConfig::TX_MAX_FILTER_FREQ, "3800000" },
		{ IRadioConfig::TX_MIN_FILTER_FREQ, "700000" },
		{ IRadioConfig::TX_MAX_FREQ, "3800000" },
		{ IRadioConfig::TX_MIN_FREQ, "700000" },
		{ IRadioConfig::TX_CENTRE_FREQ, "2000000" },
		{ IRadioConfig::TX_BANDWIDTH, "100000" },
		{ IRadioConfig::TX_MAX_POWER, "0" },
		{ IRadioConfig::TX_MIN_POWER, "-30" },

		{ IRadioConfig::NUM_RX, "4" },
		{ IRadioConfig::RX_MAX_AIR_FREQ, "3800000" },
		{ IRadioConfig::RX_MIN_AIR_FREQ, "700000" },
		{ IRadioConfig::RX_MAX_FILTER_FREQ, "3800000" },
		{ IRadioConfig::RX_MIN_FILTER_FREQ, "700000" },
		{ IRadioConfig::RX_MAX_FREQ, "3800000" },
		{ IRadioConfig::RX_MIN_FREQ, "700000" },
		{ IRadioConfig::RX_CENTRE_FREQ, "2000000" },
		{ IRadioConfig::RX_BANDWIDTH, "100000" },

		{ IRadioConfig::NUM_SRX, "2" },
		{ IRadioConfig::SRX_TX_PER_PORT, "2" },

	} ;

	return IRadioConfigSetter::create(DEFAULTS) ;
}
