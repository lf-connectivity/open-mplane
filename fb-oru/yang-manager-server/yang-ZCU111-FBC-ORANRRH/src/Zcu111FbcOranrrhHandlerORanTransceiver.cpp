/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanTransceiver.cpp
 * \brief     ORAN Transceiver module handler
 *
 *
 * \details   ORAN Transceiver module handler
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <iomanip>

#include "stringfunc.hpp"
#include "IAppOptions.h"
#include "INetworkingService.h"

#include "ILoggable.h"
#include "ILeafContainer.h"
#include "IBootEnv.h"
#include "ISfpData.h"

#include "YangMgrServer.h"
#include "RadioDatastoreSysrepo.h"
#include "YangParamUtils.h"

#include "Zcu111FbcOranrrhHandlerORanTransceiver.h"
#include "Zcu111FbcOranrrhHandlerORanFileManagement.h"

#include "Path.h"

// for debug
#include "CdiNetworkingService.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const std::map<int, std::string> Zcu111FbcOranrrhHandlerORanTransceiver::mSffComplianCode =
{
	{1,"rev9.3-diagnostics"},
	{2,"rev9.5-diagnostics"},
	{3,"rev10.2-diagnostics"},
	{5,"rev11.0-diagnostics"},
	{6,"rev11.3-diagnostics"},
	{7,"rev11.4-diagnostics"},
	{8,"rev12.0-diagnostics"},
	{0xFF,"diagnostics-undefined"}
};

const std::map<int, std::string> Zcu111FbcOranrrhHandlerORanTransceiver::mSffTransceiverIdentifier =
{
	{0, "unknown"},
	{1, "gbic"},
	{2, "soldered"},
	{3, "sfp"},
	{4, "xbi"},
	{5, "xenpack"},
	{6, "xfp"},
	{7, "xff"},
	{8, "xfp-e"},
	{9, "xpak"},
	{0x0A, "x2"},
	{0x0B, "dwdm-sfp"},
	{0x0C, "qsfp"},
	{0x0D, "qsfp+"}
};

const std::map<int, std::string> Zcu111FbcOranrrhHandlerORanTransceiver::mConnectorType =
{
	{0, "unknown"},
	{1,"subscrber-connector"},
	{6,"fiber-jack"},
	{7,"lucent-connector"},
	{8,"mt-rj"},
	{9,"multiple-optical"},
	{0x0A,"sg"},
	{0x0B,"optical-pigtail"},
	{0x0C,"multi-fiber-parralel-optic-1x12"},
	{0x0D,"multi-fiber-parralel-optic-2x16"},
	{0x20,"hssdc_2"},
	{0x21,"copper-pigtail"},
	{0x22,"rj45"},
	{0x23,"no-separable-connector"},
	{0x24,"mxc-2x16"}
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanTransceiver::Zcu111FbcOranrrhHandlerORanTransceiver(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo("o-ran-transceiver", moduleMgr, "Zcu111FbcOranrrhHandlerORanTransceiver")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path("port-transceivers")))
    , mInterfaces()
{
#ifdef TEST_BB_ON_CDI
	const std::string itfc("ethcdi") ;
#else
	const std::string itfc("ethbb") ;
#endif
	std::string ethbbInterface = IAppOptions::getInstance()->getOption(itfc).toString() ;

	// Network services access
	auto ns(INetworkingService::singleton(ethbbInterface));
	auto policy(ns->getNetAddrPolicy());

	int interfaceNum = policy->interfacePort();

	// Ethbb interface is linked to Fibre index 0
	mEthPortToSFPPort[interfaceNum] = ISfpData::getPhysicalPortNum(0);

	// Write the sfp files
	writeTransceiverFiles();
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanTransceiver::~Zcu111FbcOranrrhHandlerORanTransceiver()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanTransceiver::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

//	module: o-ran-transceiver
//	  +--rw port-transceivers
//	     +--rw port-transceiver-data* [interface-name port-number]
//	        +--rw interface-name                   leafref
//	        +--rw port-number                      leafref
//	        +--rw name?                            string
//	        +--ro present                          boolean
//	        +--ro vendor-id?                       string
//	        +--ro vendor-part?                     string
//	        +--ro vendor-rev?                      string
//	        +--ro serial-no?                       string
//	        +--ro SFF8472-compliance-code?         enumeration
//	        +--ro connector-type?                  enumeration
//	        +--ro identifier?                      enumeration
//	        +--ro nominal-bitrate?                 uint32
//	        +--ro low-bitrate-margin?              uint8
//	        +--ro high-bitrate-margin?             uint8
//	        +--ro rx-power-type?                   enumeration
//	        +--ro rx-power?                        decimal64
//	        +--ro tx-power?                        decimal64
//	        +--ro tx-bias-current?                 decimal64
//	        +--ro voltage?                         decimal64
//	        +--ro temperature?                     decimal64
//	        +--ro additional-multi-lane-reporting* [lane]
//	           +--ro lane             uint8
//	           +--ro rx-power?        decimal64
//	           +--ro tx-bias-current? decimal64
//	           +--ro tx-power?        decimal64

	populateInterfaces();

	for (auto & source : mInterfaces)
	{
		// Check if the interface number is same as the ethbb port number
		if (mEthPortToSFPPort.find(source.second) != mEthPortToSFPPort.end())
		{
			createReadWriteData(source.first, source.second);
			createReadOnlyData(source.first, source.second);
		}
	}

	// Register callback for each top level container
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe();

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanTransceiver::valueChange(const std::string & xpath,
                                                        std::shared_ptr<YangParam> oldValue,
                                                        std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanTransceiver::valueChange() - %s", xpath.c_str());
}

//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanTransceiver::validate(std::shared_ptr<YangParams> params,
		std::shared_ptr<YangParams> deletedParams)
{
	return SR_ERR_OK ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string> > Zcu111FbcOranrrhHandlerORanTransceiver::getInterfaces(void)
{
	// get all of the interfaces so I can search for the interface name
	return getKeyValues( "/ietf-interfaces:interfaces/interface//.") ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam> > Zcu111FbcOranrrhHandlerORanTransceiver::getPortReference(std::string interface)
{
	// get port reference for the specified interface
	return getParams( "/ietf-interfaces:interfaces/interface[name='" + interface + "']/o-ran-interfaces:port-reference//.") ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanTransceiver::populateInterfaces(void)
{
	// Get all interfaces
	std::map<std::string, std::map<std::string, std::string> > interfaces(getInterfaces());

	for (auto & name : interfaces)
	{
		std::map<std::string, std::shared_ptr<YangParam>> portReference = getPortReference(name.first);
		for (auto & entry : portReference)
		{
			if (entry.first == "port-number")
			{
				std::string error;
				mInterfaces[name.first] = YangParamUtils::toUint8(entry.second, error);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanTransceiver::createReadWriteData(std::string ethPort, uint8_t portNum)
{
	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	// Create the list of transceivers
	std::string transceiverList = mCallback->path() + "/port-transceiver-data";

	// Get the SFP port from the map
	int sfpPort = mEthPortToSFPPort[portNum];

	// Get the SFP data object linked to this eth interface
	std::shared_ptr<ISfpData> sfpData = ISfpData::getInstance(sfpPort);

	// Create read-write list with key values and name
	std::string interface_key = "interface-name";
	std::string interface_keyval = ethPort;

	std::string portNum_key = "port-number";
	std::string portNum_keyval = std::to_string(portNum);

	std::string name_key = "name";
	std::string name_keyval = "SFP_" + ethPort + "_" + std::to_string(portNum);

	// The port-transceiver-data list entry is unusual in that it has two keys - interface-name and port-number
	std::string path(transceiverList + "[" + interface_key + "='" + interface_keyval + "']"+ "[" + portNum_key + "='" + portNum_keyval + "']") ;

	std::string interfaceItemPath = path + "/" + interface_key;
	std::string portNumItemPath = path + "/" + portNum_key;
	std::string namePath = path + "/" + name_key;

	ds->setItemStr(interfaceItemPath, interface_keyval);
	usleep(1000);

	ds->setItemStr(portNumItemPath, portNum_keyval);
	usleep(1000);

	ds->setItemStr(namePath, name_keyval);
	usleep(1000);

	ds->createListEntry(path);
	usleep(1000);
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanTransceiver::createReadOnlyData(std::string ethPort, uint8_t portNum)
{
	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	// Create the list of transceivers
	std::string transceiverList = mCallback->path() + "/port-transceiver-data";

	// Get the SFP port from the map
	int sfpPort = mEthPortToSFPPort[portNum];

	// Create read only list entry
	std::shared_ptr<ILeafContainer> parent(mCallback) ;
	std::shared_ptr<ISfpData> sfpData = ISfpData::getInstance(sfpPort);

	std::string interface_key = "interface-name";
	std::string interface_keyval = ethPort;

	std::string portNum_key = "port-number";
	std::string portNum_keyval = std::to_string(portNum);

	auto sfpList = parent->addContainerList("port-transceiver-data");
	sfpList->addLeaf(interface_key, interface_keyval);
	sfpList->addLeaf(portNum_key, portNum_keyval);

	auto sfpPresentFunc = [this, sfpData](std::string name) -> std::string {
		return (sfpData->sfpIsPresent() ? "true" : "false");
	} ;

	auto vendorIdFunc = [this, sfpData](std::string name) -> std::string {
		return (sfpData->sfpVendorName());
	} ;

	auto vendorPartFunc = [this, sfpData](std::string name) -> std::string {
		return (sfpData->sfpVendorPart());
	} ;

	auto vendorRevFunc = [this, sfpData](std::string name) -> std::string {
		std::string rev = sfpData->sfpVendorRev();
		// Max length of vendor revision is 2 as per the yang model
		if (rev.size() > 2)
		{
			rev.resize(2);
		}
		return (rev);
	} ;

	auto vendorSNFunc = [this, sfpData](std::string name) -> std::string {
		return (sfpData->sfpVendorSN());
	} ;

	auto complianCodeFunc = [this, sfpData](std::string name) -> std::string {
		int code = sfpData->sfpComplianceCode();
		std::string ret = "diagnostics-undefined";
		if (mSffComplianCode.find(code) != mSffComplianCode.end())
		{
			ret = mSffComplianCode.at(code);
		}
		return (ret);
	} ;

	auto connectorTypeFunc = [this, sfpData](std::string name) -> std::string {
		int code = sfpData->sfpConnectorType();
		std::string ret = "unknown";
		if (mConnectorType.find(code) != mConnectorType.end())
		{
			ret = mConnectorType.at(code);
		}
		return (ret);
	} ;

	auto identifierFunc = [this, sfpData](std::string name) -> std::string {
		int code = sfpData->sfpIdentifier();
		std::string ret = "unknown";
		if (mSffTransceiverIdentifier.find(code) != mSffTransceiverIdentifier.end())
		{
			ret = mSffTransceiverIdentifier.at(code);
		}
		return (ret);
	} ;

	auto nominalBitRateFunc = [this, sfpData](std::string name) -> std::string {
		return (std::to_string(sfpData->sfpSupportedRateMBps()));
	} ;

	auto lowBitRateFunc = [this, sfpData](std::string name) -> std::string {
		return (std::to_string(sfpData->sfpMinRateMBps()));
	} ;

	auto highBitRateFunc = [this, sfpData](std::string name) -> std::string {
		return (std::to_string(sfpData->sfpMaxRateMBps()));
	} ;

	auto rxPowerTypeFunc = [this, sfpData](std::string name) -> std::string {
		return ((sfpData->sfpRxPowerType() == ISfpData::RxPowerType::RX_POWER_TYPE_OMA) ? "oma" : "avp" );
	} ;

	auto rxPowerFunc = [this, sfpData](std::string name) -> std::string {
			std::stringstream out;
			out << std::fixed << std::setprecision(4) << sfpData->sfpRxPowerMilliW();
			return (out.str());
		} ;

	auto txPowerFunc = [this, sfpData](std::string name) -> std::string {
			std::stringstream out;
			out << std::fixed << std::setprecision(4) << sfpData->sfpTxPowerMilliW();
			return (out.str());

		} ;

	auto txBiasCurrentFunc = [this, sfpData](std::string name) -> std::string {
			std::stringstream out;
			out << std::fixed << std::setprecision(4) << sfpData->sfpTxBiasCurrent();
			return (out.str());
		} ;

	auto supplyVoltageFunc = [this, sfpData](std::string name) -> std::string {
			std::stringstream out;
			out << std::fixed << std::setprecision(4) << sfpData->sfpSupplyVoltage();
			return (out.str());
		} ;

	auto temperatureFunc = [this, sfpData](std::string name) -> std::string {
			std::stringstream out;
			out << std::fixed << std::setprecision(4) << sfpData->sfpTemperature();
			return (out.str());
		} ;

	sfpList->addLeaf("present", sfpPresentFunc);
	sfpList->addLeaf("vendor-id", vendorIdFunc);
	sfpList->addLeaf("vendor-part", vendorPartFunc);
	sfpList->addLeaf("vendor-rev", vendorRevFunc);
	sfpList->addLeaf("serial-no", vendorSNFunc);
	sfpList->addLeaf("SFF8472-compliance-code", complianCodeFunc);
	sfpList->addLeaf("connector-type", connectorTypeFunc);
	sfpList->addLeaf("identifier", identifierFunc);
	sfpList->addLeaf("nominal-bitrate", nominalBitRateFunc);
	sfpList->addLeaf("low-bitrate-margin", lowBitRateFunc);
	sfpList->addLeaf("high-bitrate-margin", highBitRateFunc);
	sfpList->addLeaf("rx-power-type", rxPowerTypeFunc);
	sfpList->addLeaf("rx-power", rxPowerFunc);
	sfpList->addLeaf("tx-power", txPowerFunc);
	sfpList->addLeaf("tx-bias-current", txBiasCurrentFunc);
	sfpList->addLeaf("voltage", supplyVoltageFunc);
	sfpList->addLeaf("temperature", temperatureFunc);

}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanTransceiver::writeTransceiverFiles(void)
{
	// Vectors to store SFP data
	std::vector<UINT8> a0Bytes;
	std::vector<UINT8> a2Bytes;
	std::vector<UINT8> fileBytes;

	// Create the folder path
	std::string filePath = Zcu111FbcOranrrhHandlerORanFileManagement::mDirPrefix +
			Zcu111FbcOranrrhHandlerORanFileManagement::mOranTransceiverFolder;
	Path::mkpath(filePath) ;

	// Loop through the available SFP ports
	for (auto & port : mEthPortToSFPPort)
	{
		a0Bytes.clear();
		a2Bytes.clear();
		fileBytes.clear();

		std::shared_ptr<ISfpData> sfpData = ISfpData::getInstance(port.second);

		bool sfpPresent = sfpData->sfpRawData(a0Bytes, a2Bytes);

		// Create the output file if SFP is present
		if (sfpPresent)
		{
			fileBytes.reserve(a0Bytes.size() + a2Bytes.size());
			fileBytes.insert(fileBytes.end(), a0Bytes.begin(), a0Bytes.end());
			fileBytes.insert(fileBytes.end(), a2Bytes.begin(), a2Bytes.end());

			std::string fileName = filePath + "/sfp_" + std::to_string(port.second) + ".sffcap";
			std::ofstream wf(fileName, std::ios::out | std::ios::binary);
			if(!wf) {
				eventError("Cannot create %s to store transceiver data", fileName.c_str());
			}
			else
			{
				for (auto & data : fileBytes)
				{
					wf << data;
				}

				wf.close();
			}
		}
	}
}
