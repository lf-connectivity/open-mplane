/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioConfigFpgaHelper.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IFpgaMgr.h"
#include "IRadioConfig.h"

#include "DataVariant.h"
#include "RadioConfigFpgaHelper.h"

using namespace Mplane;

//=============================================================================================================
// LOCAL
//=============================================================================================================
const double MIN_FREQ(1000.0) ; // 1KHz
const double MAX_FREQ(20000000000.0) ; // 20GHz
const unsigned MAX_PORTS(256) ;

//-------------------------------------------------------------------------------------------------------------
namespace {

	void addIntLimit(const std::string& name,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, int value)
	{
		std::shared_ptr<DataVariant> dv(std::make_shared<DataVariant>(name, "INT")) ;
		dv->setInt(value) ;
		limits[name] = dv ;
	}

	void addMinIntLimit(const std::string& variable,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, int value)
	{
		addIntLimit( IRadioConfig::limitMinName(variable), limits, value) ;
	}

	void addMaxIntLimit(const std::string& variable,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, int value)
	{
		addIntLimit( IRadioConfig::limitMaxName(variable), limits, value) ;
	}

	void addDoubleLimit(const std::string& name,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, double value)
	{
		std::shared_ptr<DataVariant> dv(std::make_shared<DataVariant>(name, "DOUBLE")) ;
		dv->setDouble(value) ;
		limits[name] = dv ;
	}

	void addMinDoubleLimit(const std::string& variable,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, double value)
	{
		addDoubleLimit( IRadioConfig::limitMinName(variable), limits, value) ;
	}

	void addMaxDoubleLimit(const std::string& variable,
			std::map<std::string, std::shared_ptr<DataVariant>>& limits, double value)
	{
		addDoubleLimit( IRadioConfig::limitMaxName(variable), limits, value) ;
	}

}



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool RadioConfigFpgaHelper::applyFpgaLimits()
{
//	std::cerr << "SDP: RadioConfigFpgaHelper::applyFpgaLimits()" << std::endl ;

	auto fpga( IFpgaMgr::getIFpgaSystemRegs() ) ;

	std::map<std::string, std::shared_ptr<DataVariant>> limits ;

	addMinIntLimit(IRadioConfig::NUM_TX, limits, 0) ;
	addMinIntLimit(IRadioConfig::NUM_RX, limits, 0) ;
	addMinIntLimit(IRadioConfig::NUM_CARRIERS, limits, 1) ;

	UINT16 rdval ;
	rdval = fpga->read_fpgaTxAntennas() ;
	if (rdval)
	{
		addMaxIntLimit(IRadioConfig::NUM_TX, limits, rdval) ;
	}
	else
	{
		addMaxIntLimit(IRadioConfig::NUM_TX, limits, MAX_PORTS) ;
	}

	rdval = fpga->read_fpgaRxAntennas() ;
	if (rdval)
	{
		addMaxIntLimit(IRadioConfig::NUM_RX, limits, rdval) ;
	}
	else
	{
		addMaxIntLimit(IRadioConfig::NUM_RX, limits, MAX_PORTS) ;
	}

	int numCarriers(0) ;
	rdval = fpga->read_fpgaDlCarriers() ;
	numCarriers += rdval ;
	rdval = fpga->read_fpgaUlCarriers() ;
	numCarriers += rdval ;

	if (numCarriers)
	{
		addMaxIntLimit(IRadioConfig::NUM_CARRIERS, limits, rdval) ;
	}
	else
	{
		addMaxIntLimit(IRadioConfig::NUM_CARRIERS, limits, 256) ;
	}


	// Set some sensible defaults
	addMinDoubleLimit(IRadioConfig::TX_MAX_AIR_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::TX_MAX_AIR_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_MIN_AIR_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::TX_MIN_AIR_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_MAX_FILTER_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::TX_MAX_FILTER_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_MIN_FILTER_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::TX_MIN_FILTER_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_MAX_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::TX_MAX_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_MIN_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::TX_MIN_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_CENTRE_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::TX_CENTRE_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::TX_BANDWIDTH, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::TX_BANDWIDTH, limits, MAX_FREQ) ;

	addMinDoubleLimit(IRadioConfig::TX_MAX_POWER, limits, -10.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_MAX_POWER, limits, 100.0) ;
	addMinDoubleLimit(IRadioConfig::TX_MIN_POWER, limits, -100.0) ;
	addMaxDoubleLimit(IRadioConfig::TX_MIN_POWER, limits, 0.0) ;

	addMinDoubleLimit(IRadioConfig::RX_MAX_AIR_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::RX_MAX_AIR_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_MIN_AIR_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::RX_MIN_AIR_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_MAX_FILTER_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::RX_MAX_FILTER_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_MIN_FILTER_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::RX_MIN_FILTER_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_MAX_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::RX_MAX_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_MIN_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::RX_MIN_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_CENTRE_FREQ, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::RX_CENTRE_FREQ, limits, MAX_FREQ) ;
	addMinDoubleLimit(IRadioConfig::RX_BANDWIDTH, limits, MIN_FREQ) ;
	addMaxDoubleLimit(IRadioConfig::RX_BANDWIDTH, limits, MAX_FREQ) ;

	addMinIntLimit(IRadioConfig::NUM_SRX, limits, 0) ;
	addMaxIntLimit(IRadioConfig::NUM_SRX, limits, MAX_PORTS) ;
	addMinIntLimit(IRadioConfig::SRX_TX_PER_PORT, limits, 1) ;
	addMaxIntLimit(IRadioConfig::SRX_TX_PER_PORT, limits, MAX_PORTS) ;


	// apply the limits
	IRadioConfig::singleton()->setLimits(limits) ;

	return true ;
}
