/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanModuleCap.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <string>
#include <algorithm>

#include "stringfunc.hpp"

#include "YangMgrServer.h"
#include "YangParamUtils.h"

#include "Zcu111FbcOranrrhHandlerORanModuleCap.h"
#include "RadioDatastoreSysrepo.h"

#include "IFrequencyConst.h"
#include "ICarrierHardware.h"
#include "CarrierHardware/ChainModel.h"
#include "CarrierHardware/FibreModel.h"
#include "CarrierHardware/FlexiChainInfo.h"
#include "Zcu111CarrierHardwareData.h"



using namespace Mplane;


//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanModuleCap::Zcu111FbcOranrrhHandlerORanModuleCap(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo("o-ran-module-cap", moduleMgr, "Zcu111FbcOranrrhHandlerORanModuleCap")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path("module-capability")))
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanModuleCap::~Zcu111FbcOranrrhHandlerORanModuleCap()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanModuleCap::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	if (!createRuCapabilities())
	{
		return false;
	}

	if (!createBandCapabilities())
	{
		return false;
	}

	// Register callbacks
	getItemsSubscribe(mCallback->path(), mCallback);

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanModuleCap::valueChange(const std::string & xpath,
                                                       std::shared_ptr<YangParam> oldValue,
                                                       std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanModuleCap::valueChange() - %s", xpath.c_str());
}

//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanModuleCap::validate(std::shared_ptr<YangParams> params,
		std::shared_ptr<YangParams> deletedParams)
{
	return SR_ERR_OK ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanModuleCap::createRuCapabilities(void)
{
	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );
	uint8_t rxPorts = hardwareData->getNumRxAntennas();
	uint8_t txPorts = hardwareData->getNumTxAntennas();


	// Create Ru capability

	//	     +--ro ru-capabilities
	//	     |  +--ro ru-supported-category                              enumeration
	//	     |  +--ro number-of-ru-ports                                 uint8_t
	//	     |  +--ro number-of-spatial-streams                          uint8_t
	//	     |  +--ro max-power-per-pa-antenna                           decimal64
	//	     |  +--ro min-power-per-pa-antenna                           decimal64
	//	     |  +--ro fronthaul-split-option                             uint8_t
	//	     |  +--ro format-of-iq-sample                                container
	//	     |	|  +--ro dynamic-compression-supported                   boolean
	//	     |	|  +--ro realtime-variable-bit-width-supported           boolean
	//       |  |  +--ro compression-method-supported*                   list
	//       |  |  +--ro variable-bit-width-per-channel-supported        boolean
	//       |  |  +--ro syminc-supported                                boolean
	//	     |  +--ro ul-mixed-num-required-guard-rbs* [scs-a scs-b]
	//	     |	|  +--ro scs-a                                           enumeration
	//	     |	|  +--ro scs-b                                           enumeration
	//	     |	|  +--ro number-of-guard-rbs-ul                          uint8_t
	//	     |  +--ro dl-mixed-num-required-guard-rbs* [scs-a scs-b]
	//	     |	|  +--ro scs-a                                           enumeration
	//	     |	|  +--ro scs-b                                           enumeration
	//	     |	|  +--ro number-of-guard-rbs-dl                          uint8_t
	//	     |  +--ro energy-saving-by-transmission-blanks               boolean
	//	     |  +--ro dynamic-transport-delay-management-supported       boolean

	auto ruCapability = parent->addContainer("ru-capabilities");
	ruCapability->addLeaf("ru-supported-category", "CAT_A");
	ruCapability->addLeafUInt8("number-of-ru-ports", (2 * rxPorts));
	ruCapability->addLeafUInt8("number-of-spatial-streams", (txPorts >= rxPorts ? txPorts : rxPorts));
	ruCapability->addLeaf("max-power-per-pa-antenna", "0.0");
	ruCapability->addLeaf("min-power-per-pa-antenna", "-32.0");
	ruCapability->addLeaf("fronthaul-split-option", "7");

	auto iqSampleFormat = ruCapability->addContainer("format-of-iq-sample");
	iqSampleFormat->addLeafBool("dynamic-compression-supported", false);
	iqSampleFormat->addLeafBool("realtime-variable-bit-width-supported", false);
	iqSampleFormat->addContainer("compression-method-supported");
	iqSampleFormat->addLeafBool("variable-bit-width-per-channel-supported", false);
	iqSampleFormat->addLeafBool("syminc-supported", false);

	ruCapability->addContainer("ul-mixed-num-required-guard-rbs");
	ruCapability->addContainer("dl-mixed-num-required-guard-rbs");

	ruCapability->addLeafBool("energy-saving-by-transmission-blanks", false);
	ruCapability->addLeafBool("dynamic-transport-delay-management-supported", false);

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanModuleCap::createBandCapabilities(void)
{
	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	// Create band capability

	//	     +--ro band-capabilities* [band-number]
	//	     |  +--ro band-number                                  uint8_t
    //       |  +--ro max-supported-frequency-dl                   uint64_t
    //       |  +--ro min-supported-frequency-dl                   uint64_t
    //       |  +--ro max-supported-bandwidth-dl                   uint64_t
    //       |  +--ro max-num-carriers-dl                          uint32_t
    //       |  +--ro max-carrier-bandwidth-dl                     uint64_t
    //       |  +--ro min-carrier-bandwidth-dl                     uint64_t
    //       |  +--ro max-supported-frequency-ul                   uint64_t
    //       |  +--ro min-supported-frequency-ul                   uint64_t
    //       |  +--ro max-supported-bandwidth-ul                   uint64_t
    //       |  +--ro max-num-carriers-ul                          uint32_t
    //       |  +--ro max-carrier-bandwidth-ul                     uint64_t
    //       |  +--ro min-carrier-bandwidth-ul                     uint64_t
	//	     |  +--ro max-num-component-carriers                   uint8_t
	//	     |  +--ro max-num-bands                                uint16_t
	//	     |  +--ro max-num-sectors                              uint8_t
	//	     |  +--ro max-power-per-antenna                        decimal64
	//	     |  +--ro min-power-per-antenna                        decimal64
	//	     |  +--ro codebook-configuration_ng                    uint8_t
	//	     |  +--ro codebook-configuration_n1                    uint8_t
	//	     |  +--ro codebook-configuration_n2                    uint8_t

	auto bandCapability = parent->addContainer("band-capabilities");

	// This radio supports a single band number 3
	bandCapability->addLeafUInt8("band-number", 3);

	// Populate the band information for downlink
	populateBanduldl(bandCapability, 1805000000, 1880000000, false);

	// Populate the band information for uplink
	populateBanduldl(bandCapability, 1710000000, 1785000000, true);

	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );
	uint8_t maxRfChains = hardwareData->getNumChains();

	bandCapability->addLeafUInt8("max-num-component-carriers", maxRfChains);
	bandCapability->addLeafUInt8("max-num-bands", 1);
	bandCapability->addLeafUInt8("max-num-sectors", 1);
	bandCapability->addLeaf("max-power-per-antenna", "0.0");
	bandCapability->addLeaf("min-power-per-antenna", "-32.0");
	bandCapability->addLeafUInt8("codebook-configuration_ng", 0);
	bandCapability->addLeafUInt8("codebook-configuration_n1", 0);
	bandCapability->addLeafUInt8("codebook-configuration_n2", 0);

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanModuleCap::populateBanduldl(std::shared_ptr<ILeafContainer> bandCapability,
		uint64_t minFreq, uint64_t maxFreq, bool isUl)
{
	std::string uldl = (isUl == true ? "ul" : "dl");
	// This would be the smaller of (max-supported-frequency-dl - min-supported-frequency-dl)
	// or 100000000
	uint64_t bandwidth = maxFreq - minFreq;
	if (bandwidth > 100000000)
	{
		bandwidth = 100000000;
	}

	// 32-bit integer indicating the maximum number of uplink/downlink carriers in module.
	// This is equal to 2 times the number of RF chains times the number of Rx/Tx antenna ports.
	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );
	uint32_t numCarriers;
	if (isUl)
	{
		numCarriers = hardwareData->getNumUlchains() * hardwareData->getNumRxAntennas() * 2;
	}
	else
	{
		numCarriers = hardwareData->getNumDlchains() * hardwareData->getNumTxAntennas();
	}

	// Get the number of chains for uplink/downlink
	unsigned numChains = (isUl == true ? hardwareData->getNumUlchains() : hardwareData->getNumDlchains());

	// Calculate the maximum and minimum carrier bandwidth
	std::vector<unsigned long> chbwFreq;
	// Loop through all the chains
	for (unsigned chain=0; chain < numChains; ++chain)
	{
		// Get the chain type
		const ChainCarrierInfo& chainInfo = (isUl == true ? hardwareData->getUlChainInfo(chain) : hardwareData->getDlChainInfo(chain)) ;

		// Find the supported channel bandwidths for the chain type
		std::vector<ICarrierHardwareTypes::ChbwType> supported(FlexiChainInfo::supportedChbw(chainInfo.chain_type)) ;

		for (auto chbw : supported)
		{
			// Convert each channel bandwidh type to frequency value
			unsigned long freq = hardwareData->chbwTypeToFreq(chbw).getUint();
			if (freq != 0 &&
			    std::find(chbwFreq.begin(), chbwFreq.end(), freq) == chbwFreq.end())
			{
				chbwFreq.push_back(freq);
			}
		}
	}

	// Find the minimum and maximum frequency to get the min and max carrier bandwidth
	auto minCarrierBW = std::min_element(chbwFreq.begin(), chbwFreq.end());
	auto maxCarrierBW = std::max_element(chbwFreq.begin(), chbwFreq.end());

	bandCapability->addLeafUInt64("max-supported-frequency-" + uldl, maxFreq);
	bandCapability->addLeafUInt64("min-supported-frequency-" + uldl, minFreq);
	bandCapability->addLeafUInt64("max-supported-bandwidth-" + uldl, bandwidth);
	bandCapability->addLeafUInt32("max-num-carriers-" + uldl, numCarriers);
	if (maxCarrierBW != chbwFreq.end())
	{
		// BW is in KHz, converting to Hz
		bandCapability->addLeafUInt64("max-carrier-bandwidth-" + uldl, *maxCarrierBW * 1000);
	}
	else
	{
		eventError("Cannot find max carrier BW for %s", uldl.c_str());
	}
	if (minCarrierBW != chbwFreq.end())
	{
		// BW is in KHz, converting to Hz
		bandCapability->addLeafUInt64("min-carrier-bandwidth-" + uldl, *minCarrierBW * 1000);
	}
	else
	{
		eventError("Cannot find min carrier BW for %s", uldl.c_str());
	}
	return true;
}
