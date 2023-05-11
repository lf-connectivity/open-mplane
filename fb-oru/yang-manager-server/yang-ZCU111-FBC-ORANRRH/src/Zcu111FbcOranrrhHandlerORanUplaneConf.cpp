/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanUplaneConf.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "SysrepoUtils.h"

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <string>

#include "stringfunc.hpp"
#include "ICarrierServer.h"
#include "ICarrier.h"
#include "IYangCarrierMgr.h"

#include "IFpgaMgr.h"

#include "YangMgrServer.h"
#include "YangParamUtils.h"

#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerORanUplaneConf.h"

using namespace Mplane;


//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {

	// We control the static low level endpoint names which will be of the form ccYtx/rxX
	// where X = antenna, Y = carrier component.
	// Extract X & Y
	bool endpointNameParse(const std::string& endpoint, unsigned& ant, unsigned& cc)
	{
		std::string ccstr(endpoint.substr(2, 1)) ;
		std::string antstr(endpoint.substr(endpoint.size()-1)) ;
		bool ok(true) ;
		try {
		ant = stoi(antstr) ;
		cc = stoi(ccstr) ;
		} catch(...) {
			ok = false ;
		}
		return ok ;
	}

	// create the endpoint name
	std::string endpointName(const std::string& txrx, unsigned ant, unsigned cc)
	{
		return IYangCarrierMgr::singleton()->endpointName(txrx, ant, cc) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
using StateSetFunc = std::function<void(const std::string& state)> ;

class CarrierStateDefault {
public:
	CarrierStateDefault(StateSetFunc setFunc, const std::string& defaultState, const std::string& state) :
		mSetFunc(setFunc),
		mDefaultState(defaultState)
	{
		mSetFunc(state) ;
	}

	void set(const std::string& state)
	{
		if (!state.empty())
			mSetFunc(state) ;
		mDefaultState = state ;
	}

	~CarrierStateDefault()
	{
		if (!mDefaultState.empty())
			mSetFunc(mDefaultState) ;
	}


private:
	StateSetFunc mSetFunc;
	std::string mDefaultState ;
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanUplaneConf::Zcu111FbcOranrrhHandlerORanUplaneConf(std::shared_ptr<IYangModuleMgr> moduleMgr) :
	YangHandlerSysrepo("o-ran-uplane-conf", moduleMgr, "Zcu111FbcOranrrhHandlerORanUplaneConf"),
	mCallback(std::make_shared<SysrepoGetitemsCallback>(path("user-plane-configuration"))),
	mRuMac(0),
	mRxCarrierState(),
	mTxCarrierState()
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanUplaneConf::~Zcu111FbcOranrrhHandlerORanUplaneConf()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanUplaneConf::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	// Set up carrier manager
	auto carrierMgr( IYangCarrierMgr::singleton() ) ;
	carrierMgr->setLeafContainer( std::dynamic_pointer_cast<ILeafContainer>(mCallback) ) ;

	// Register callbacks
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe() ;

	// get any initial links
	std::map<std::string, std::map<std::string, std::string>> txlinks(getLinks("tx")) ;
	for (auto entry : txlinks)
	{
		for (auto value : entry.second)
		{
			if (value.first == "tx-array-carrier")
			{
				carrierMgr->updateTxLink( entry.first, "", value.second ) ;
				continue ;
			}

			if (value.first == "low-level-tx-endpoint")
			{
				carrierMgr->updateTxLink( entry.first, value.second, "" ) ;
				continue ;
			}
		}
	}
	std::map<std::string, std::map<std::string, std::string>> rxlinks(getLinks("rx")) ;
	for (auto entry : rxlinks)
	{
		for (auto value : entry.second)
		{
			if (value.first == "rx-array-carrier")
			{
				carrierMgr->updateRxLink( entry.first, "", value.second ) ;
				continue ;
			}

			if (value.first == "low-level-rx-endpoint")
			{
				carrierMgr->updateRxLink( entry.first, value.second, "" ) ;
				continue ;
			}
		}
	}

	std::map<std::string, std::map<std::string, std::string> > txcarriers(getKeyValues(mCallback->path() + "/tx-array-carriers//.")) ;
	for (auto entry : txcarriers)
	{
		updateTxCarrier( entry.first ) ;
	}
	std::map<std::string, std::map<std::string, std::string> > rxcarriers(getKeyValues(mCallback->path() + "/rx-array-carriers//.")) ;
	for (auto entry : rxcarriers)
	{
		updateRxCarrier( entry.first ) ;
	}

	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanUplaneConf::valueChange(
		const std::string &xpath, std::shared_ptr<YangParam> oldValue,
		std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanUplaneHandler::valueChange() - %s", xpath.c_str());

	std::string error ;

	std::string listName ;
	std::string key ;
	std::string index ;
	std::string value ;
	std::string leaf ;

	if (oldValue)
	{
		value = YangParamUtils::toString(oldValue, error) ;
		listIndex(oldValue->name(), listName, key, index) ;
		leaf = leafName(oldValue->name()) ;
	}
	if (newValue)
	{
		value = YangParamUtils::toString(newValue, error) ;
		listIndex(newValue->name(), listName, key, index) ;
		leaf = leafName(newValue->name()) ;
	}

	processValue(newValue, leaf, value) ;

}

//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanUplaneConf::validate(std::shared_ptr<YangParams> params,
		std::shared_ptr<YangParams> deletedParams)
{
	// skip if not changing carrier active state
	std::string error ;
	bool active(false) ;
	for (unsigned i=0; i < params->getNumParams(); ++i)
	{
		std::shared_ptr<YangParam> param(params->getParam(i)) ;

		std::string value( YangParamUtils::toString(param, error) ) ;
		std::string leaf( leafName(param->name()) ) ;

		if (leaf != "active")
			continue ;

		if (value != "ACTIVE")
			continue ;

		active = true ;
		break ;
	}

	if (!active)
		return SR_ERR_OK ;

	// Need to process the parameters to see if we can make the carrier(s) active
	// NOTE: For simplicity I'm actually applying these values and only doing the validation on the final activate
	// ideally this whole transaction would cause no changes if it's rejected, but that's a shed load more work!
	for (unsigned i=0; i < params->getNumParams(); ++i)
	{
		std::shared_ptr<YangParam> param(params->getParam(i)) ;

		std::string leaf( leafName(param->name()) ) ;

		if (leaf == "active")
			continue ;

		// process value
		std::string value( YangParamUtils::toString(param, error) ) ;
		int rc = processValue(param, leaf, value) ;

		if (rc != SR_ERR_OK)
		{
			return rc ;
		}
	}

	// Now just check each active change
	for (unsigned i=0; i < params->getNumParams(); ++i)
	{
		std::shared_ptr<YangParam> param(params->getParam(i)) ;

		std::string leaf( leafName(param->name()) ) ;

		if (leaf != "active")
			continue ;

		// validate active change - without making any change
		std::string value( YangParamUtils::toString(param, error) ) ;
		int rc = validateValue(param, leaf, value) ;

		if (rc != SR_ERR_OK)
		{
			return rc ;
		}
	}

	return SR_ERR_OK ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanUplaneConf::processValue(
		std::shared_ptr<YangParam> param, const std::string &leaf,
		const std::string &value)
{
	std::string error ;

	std::string listName ;
	std::string key ;
	std::string index ;
	listIndex(param->name(), listName, key, index) ;

	if (listName == "low-level-rx-links")
	{
		std::string endpoint ;
		std::string carrierName ;

		if (leaf == "low-level-rx-endpoint")
		{
			endpoint = value ;
		}
		if (leaf == "rx-array-carrier")
		{
			carrierName = value ;
		}

		if (endpoint.empty() && carrierName.empty())
			return SR_ERR_INVAL_ARG ;

		auto carrierMgr( IYangCarrierMgr::singleton() ) ;
		carrierMgr->updateRxLink( index, endpoint, carrierName ) ;

		return SR_ERR_OK ;
	}

	if (listName == "low-level-tx-links")
	{
		std::string endpoint ;
		std::string carrierName ;

		if (leaf == "low-level-tx-endpoint")
		{
			endpoint = value ;
		}
		if (leaf == "tx-array-carrier")
		{
			carrierName = value ;
		}

		if (endpoint.empty() && carrierName.empty())
			return SR_ERR_INVAL_ARG ;

		auto carrierMgr( IYangCarrierMgr::singleton() ) ;
		carrierMgr->updateTxLink( index, endpoint, carrierName ) ;

		return SR_ERR_OK ;
	}



	// For tx-array-carrier & rx-array-carrier, index == carrier name

	// only interested in array carriers activate/de-activate
	if (listName == "rx-array-carriers")
	{
		if (leaf == "name")
		{
			updateRxCarrier(value) ;
			return SR_ERR_OK ;
		}

		// No need to call handleActivate if the leaf is not active
		if (leaf != "active")
		{
			return SR_ERR_OK ;
		}

		// Call the handleActivate only if the carrier is activated or deactivated (transition)
		if (value == "INACTIVE" && mRxCarrierState[index] == "DISABLED")
		{
			return SR_ERR_OK;
		}

		return handleActivate(param, leaf, value, VALUE_APPLY) ;
	}


	if (listName == "tx-array-carriers")
	{
		if (leaf == "name")
		{
			updateTxCarrier(value) ;
			return SR_ERR_OK ;
		}

		// No need to call handleActivate if the leaf is not active
		if (leaf != "active")
		{
			return SR_ERR_OK ;
		}

		// Call the handleActivate only if the carrier is activated or deactivated (transition)
		if (value == "INACTIVE" && mTxCarrierState[index] == "DISABLED")
		{
			return SR_ERR_OK;
		}

		return handleActivate(param, leaf, value, VALUE_APPLY) ;
	}

	return SR_ERR_OK ;
}

//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanUplaneConf::validateValue(
		std::shared_ptr<YangParam> param, const std::string &leaf,
		const std::string &value)
{
	if (leaf != "active")
		return SR_ERR_OK ;

	if (value != "ACTIVE")
		return SR_ERR_OK ;

	// activating a carrier
	return handleActivate(param, leaf, value, VALUE_VALIDATE) ;
}


//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanUplaneConf::handleActivate(
		std::shared_ptr<YangParam> param, const std::string &leaf,
		const std::string &value, ValuePhase phase)
{
	std::string error ;

	std::string listName ;
	std::string key ;
	std::string index ;
	listIndex(param->name(), listName, key, index) ;

	// only interested in array carriers activate/de-activate
	if (listName == "rx-array-carriers")
	{
		if (leaf != "active")
			return SR_ERR_OK ;

		unsigned carrierIndex ;
		std::string rxEndpoint ;
		std::string rxProcessingElement ;
		if (!carrierLinkDetails("rx", index, carrierIndex, rxEndpoint, rxProcessingElement))
		{
			eventWarning("YANG carrier validation failed. Unable to get RX endpoint link for carrier '%s'", index.c_str()) ;
			return SR_ERR_INVAL_ARG ;
		}


		unsigned ant ;
		unsigned cc ;
		if (!endpointNameParse(rxEndpoint, ant, cc))
		{
			eventWarning("YANG carrier validation failed. RX invalid endpoint name '%s'", index.c_str()) ;
			return SR_ERR_INVAL_ARG ;
		}
		std::string txEndpoint(endpointName("tx", ant, cc)) ;

		if (carrierIndex != cc)
		{
			eventWarning("YANG carrier validation failed. RX carrier index '%d' mismatches endpoint index '%d'", carrierIndex, cc) ;
			return SR_ERR_INVAL_ARG ;
		}

		if (!handleCarrier(carrierIndex, SETTING_RX, (value == "ACTIVE"), phase))
			return SR_ERR_INVAL_ARG ;

		return SR_ERR_OK ;
	}


	if (listName == "tx-array-carriers")
	{
		if (leaf != "active")
			return SR_ERR_OK ;

		unsigned carrierIndex ;
		std::string txEndpoint ;
		std::string txProcessingElement ;
		if (!carrierLinkDetails("tx", index, carrierIndex, txEndpoint, txProcessingElement))
		{
			eventWarning("YANG carrier validation failed. Unable to get TX endpoint link for carrier '%s'", index.c_str()) ;
			return SR_ERR_INVAL_ARG ;
		}

		unsigned ant ;
		unsigned cc ;
		if (!endpointNameParse(txEndpoint, ant, cc))
		{
			eventWarning("YANG carrier validation failed. TX invalid endpoint name '%s'", index.c_str()) ;
			return SR_ERR_INVAL_ARG ;
		}
		std::string rxEndpoint(endpointName("rx", ant, cc)) ;

		if (carrierIndex != cc)
		{
			eventWarning("YANG carrier validation failed. TX carrier index '%d' mismatches endpoint index '%d'", carrierIndex, cc) ;
			return SR_ERR_INVAL_ARG ;
		}

		if (!handleCarrier(carrierIndex, SETTING_TX, (value == "ACTIVE"), phase))
			return SR_ERR_INVAL_ARG ;

		return SR_ERR_OK ;
	}

	return SR_ERR_OK ;
}


//-------------------------------------------------------------------------------------------------------------
std::string Zcu111FbcOranrrhHandlerORanUplaneConf::getCarrierName(const std::string &txrx, unsigned carrierIndex)
{
	std::string endpoint(IYangCarrierMgr::singleton()->endpointName(txrx, 0, carrierIndex)) ;

	unsigned cc ;
	std::string processingElement ;
	std::string carrierArray ;
	endpointLinkDetails(txrx, endpoint, cc, carrierArray, processingElement) ;

	return carrierArray ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanUplaneConf::carrierLinkDetails(const std::string &txrx, const std::string& carrierName,
		unsigned &carrierIndex, std::string &endpoint, std::string &processingElement)
{
	endpoint.clear() ;
	processingElement.clear() ;

	// get all of the links so I can search for the carrier name
	std::map<std::string, std::map<std::string, std::string>> links(getLinks(txrx)) ;

	// find the carrier in the links
	std::string carrierLeaf = txrx + "-array-carrier" ;
	for (auto entry : links)
	{
		auto linkEntry(entry.second) ;
		if (linkEntry.find(carrierLeaf) == linkEntry.end())
			continue ;

		if (linkEntry[carrierLeaf] != carrierName)
			continue ;

		// found it
		// get the endpoint and processing element names
		endpoint = linkEntry["low-level-" + txrx + "-endpoint"] ;
		processingElement = linkEntry["processing-element"] ;

		// use the carrier manager to get the carrier index
		std::pair<unsigned, unsigned> cciq ;
		if (txrx == "tx")
			cciq = IYangCarrierMgr::singleton()->lookupDlEndpoint(endpoint) ;
		else
			cciq = IYangCarrierMgr::singleton()->lookupUlEndpoint(endpoint) ;

		carrierIndex = cciq.first ;

		return true ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanUplaneConf::endpointLinkDetails(const std::string &txrx, const std::string &endpoint,
		unsigned &carrierIndex, std::string &carrierName,
		std::string &processingElement)
{
	// get all of the links so I can search for the carrier name
	std::map<std::string, std::map<std::string, std::string>> links(getLinks(txrx)) ;

	// find the endpoint in the links
	std::string endpointLeaf = "low-level-" + txrx + "-endpoint" ;
	for (auto entry : links)
	{
		auto linkEntry(entry.second) ;
		if (linkEntry.find(endpointLeaf) == linkEntry.end())
			continue ;

		if (linkEntry[endpointLeaf] != endpoint)
			continue ;

		// found it
		// get the endpoint and processing element names
		carrierName = linkEntry[txrx + "-array-carrier"] ;
		processingElement = linkEntry["processing-element"] ;

		// use the carrier manager to get the carrier index
		std::pair<unsigned, unsigned> cciq ;
		if (txrx == "tx")
			cciq = IYangCarrierMgr::singleton()->lookupDlEndpoint(endpoint) ;
		else
			cciq = IYangCarrierMgr::singleton()->lookupUlEndpoint(endpoint) ;

		carrierIndex = cciq.first ;

		return true ;
	}

	return false ;
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanUplaneConf::getLink(const std::string &txrx, const std::string& linkName,
		std::string &endpoint, std::string &carrierName)
{

	// get all of the links so I can search for the carrier name
	std::map<std::string, std::map<std::string, std::string>> links(getLinks(txrx)) ;

	if (links.find(linkName) == links.end())
		return false ;

	endpoint = links[linkName]["low-level-" + txrx + "-endpoint"] ;
	carrierName = links[linkName][txrx + "-array-carrier"] ;

	return false ;
}



//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanUplaneConf::handleCarrier(unsigned carrierIndex, TxRxSettings txrx, bool active, ValuePhase phase)
{
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance()) ;
	if (carrierIndex >= carrierServer->getMaxCarriers())
		return false ;
	ICarrierSetter& carrier(carrierServer->getCarrierSetter(carrierIndex));

	carrier.setState(ICarrier::STATE_DISABLE) ;

	// Only apply the change if we are in the VALUE_APPLY phase. Otherwise we are just validating the changes
	if (phase == VALUE_APPLY)
	{
		if (!carrierServer->setCarrier(carrier))
			return false ;
	}

	bool txCarrierEnable(false) ;
	bool rxCarrierEnable(false) ;
	bool prachCarrierEnable(false) ;

	// Maintain the TX state
	std::string txCarrier(getCarrierName("tx", carrierIndex)) ;
	if (txCarrier.empty())
		return false ;
	auto txFunc = [this, txCarrier](const std::string& state){

		std::string currentState(mTxCarrierState[txCarrier]) ;
		mTxCarrierState[txCarrier] = state ;

		// Send notification if needed
		carrierChangeNotification("tx", txCarrier, currentState, state) ;
	} ;
	std::string defaultTxState("BUSY") ;
	std::string disableTxState("DISABLED") ;
	if ( (txrx != SETTING_TX) || (phase == VALUE_VALIDATE) )
	{
		// don't change state
		defaultTxState = mTxCarrierState[txCarrier] ;
		disableTxState = mTxCarrierState[txCarrier] ;
	}
	CarrierStateDefault txState(txFunc, disableTxState, defaultTxState) ;

	// Maintain the RX state
	std::string rxCarrier(getCarrierName("rx", carrierIndex)) ;
	if (rxCarrier.empty())
		return false ;
	auto rxFunc = [this, rxCarrier](const std::string& state){

		std::string currentState(mRxCarrierState[rxCarrier]) ;
		mRxCarrierState[rxCarrier] = state ;

		// Send notification if needed
		carrierChangeNotification("rx", rxCarrier, currentState, state) ;
	} ;
	std::string defaultRxState("BUSY") ;
	std::string disableRxState("DISABLED") ;
	if ( (txrx != SETTING_RX) || (phase == VALUE_VALIDATE) )
	{
		// don't change state
		defaultRxState = mRxCarrierState[rxCarrier] ;
		disableRxState = mRxCarrierState[rxCarrier] ;
	}
	CarrierStateDefault rxState(rxFunc, disableRxState, defaultRxState) ;

	uint8_t rxFrameStruct(0) ;
	uint8_t txFrameStruct(0) ;

	// The carrier common settings like the type and mode are done from handleCarrierTx.
	// The TX carrier settings (DL) are done in handleCarrierTx
	// The RX carrier settings (UL) are done in handleCarrierRx. So if the UL is setup without
	// DL, then the carrier activation fails
	// TX
	if (!handleCarrierTx(carrier, carrierIndex, active, txCarrierEnable, txFrameStruct))
		return false ;

	// RX
	if (!handleCarrierRx(carrier, carrierIndex, active, rxCarrierEnable, rxFrameStruct))
		return false ;

	// PRACH
	if (!handleCarrierPrach(carrier, carrierIndex, active, prachCarrierEnable))
		return false ;

	// ensure frame structs match
	if (txFrameStruct && rxFrameStruct && (txFrameStruct != rxFrameStruct))
	{
std::cerr << "SDP: TX frame struct " << (unsigned)txFrameStruct << " does not match RX " << (unsigned)rxFrameStruct << std::endl ;
		return false ;
	}

	if (phase == VALUE_APPLY)
	{
		// applying changes
		if (txCarrierEnable || rxCarrierEnable)
		{
			if (!carrier.setState(ICarrier::STATE_ENABLE))
				return false ;

			if (!carrierServer->setCarrier(carrier))
				return false ;

			if (txCarrierEnable)
				txState.set("READY") ;

			if (rxCarrierEnable)
				rxState.set("READY") ;
		}
	}
	else
	{
		// Validating changes
		if (!carrierServer->validateChange(carrier))
		{
			eventWarning("Validation failed for carrier index %s %s", std::to_string(carrierIndex).c_str(), (txrx == SETTING_RX ? "UL" : "DL"));
			return false ;
		}
	}

	return true ;

}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanUplaneConf::handleCarrierTx(ICarrierSetter& carrier, unsigned carrierIndex, bool active,
		bool& carrierEnable, uint8_t& txFrameStruct)
{
	txFrameStruct = 0 ;

	unsigned numTx(IYangCarrierMgr::singleton()->numTx()) ;
	for (unsigned ant=0; ant < numTx; ++ant)
	{
		std::string endpoint(IYangCarrierMgr::singleton()->endpointName("tx", ant, carrierIndex)) ;
		std::map<std::string, std::shared_ptr<YangParam> > data(getEndpoint("tx", endpoint)) ;

		unsigned cc ;
		std::string processingElement ;
		std::string carrierArray ;
		endpointLinkDetails("tx", endpoint, cc, carrierArray, processingElement) ;

		// sanity check
		if (cc != carrierIndex)
			logEventWarning("ORAN Carrier DL: link carrier index %u does not match expected index (%u)", cc, carrierIndex) ;


		// Get the array carrier data
		std::map<std::string, std::shared_ptr<YangParam> > carrierData(getArrayCarrier("tx", carrierArray)) ;
		if (paramVal(carrierData, "active") != "ACTIVE")
		{
			// clear the EAXCID and move on
			carrier.setDlEaxcId(ant, 0) ;
			continue ;
		}

		// EAXC-ID
		carrier.setDlEaxcId(ant, paramValUInt16(data, "eaxc-id")) ;

		auto processingElementData(getInterface(processingElement)) ;
		setRuMac(processingElementData) ;

		// frame-structure
		{
			uint8_t frameStruct( paramValUInt8(data, "frame-structure") ) ;

			if (txFrameStruct == 0)
			{
				txFrameStruct = frameStruct ;
			}
			else
			{
				// check against the other channels
				if (txFrameStruct != frameStruct)
				{
					std::cerr << "SDP: TX frame struct " << (unsigned)txFrameStruct << " does not match latest " << (unsigned)frameStruct << std::endl ;
					return false ;
				}
			}

			if (!carrier.setDlScs( frameStructToScsType(frameStruct) ) )
				return false ;

			ICarrier::FFTsizeType fftSize(frameStructToFFTsize(frameStruct));

			if (fftSize == ICarrier::FFT_NONE)
				return false ;
			if (! carrier.setDlFftSize(fftSize) )
				return false ;
		}

		// cp-type
		{
			std::string cptype( paramVal(data, "cp-type") ) ;

			if (! carrier.setDlPrefixLenConfig( ICarrier::strToPrefixLen( cptype ) ))
				return false ;
		}

		// cp-length
		{
			unsigned cplen( paramValUInt16(data, "cp-length") ) ;

			if (!carrier.setDlCpSize( cplen ) )
				return false ;
		}

		// cp-length-other
		{
			unsigned cplen( paramValUInt16(data, "cp-length-other") ) ;

			if (!carrier.setDlCpOtherSize( cplen ) )
				return false ;
		}



		ICarrier::Type type(ICarrier::CARRTYPE_NONE) ;
		if (paramVal(carrierData, "rw-type") == "LTE")
		{
			// LTE
			if (!carrier.setMode(ICarrier::MODE_LTE))
				return false ;

			// channel-bandwidth
			type = getLteChbw(carrierData) ;
		}
		else
		{
			// 5G
			if (!carrier.setMode(ICarrier::MODE_5GNR))
				return false ;

			// channel-bandwidth
			type = get5GChbw(carrierData) ;
		}

		// type
		if (!carrier.setType(type))
			return false ;

		// Frequency
		{
			uint64_t centre(paramValUInt64(carrierData, "center-of-channel-bandwidth")) ;
			if (centre == 0)
				eventWarning("TX centre frequency 0. Value ignored...") ;

			if (centre > 0)
				if (!carrier.setTxFrequency( Frequency( (long long unsigned)centre, Frequency::Hz) ))
					return false ;
		}

		// gain
		{
			double gain( paramValDecimal64(carrierData, "gain") ) ;

			if (!carrier.setTxPower( Power(gain) ) )
				return false ;
		}


		carrierEnable = true ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanUplaneConf::handleCarrierRx(ICarrierSetter& carrier, unsigned carrierIndex, bool active,
		bool& carrierEnable, uint8_t& rxFrameStruct)
{
	rxFrameStruct = 0 ;

	auto oranRegs(IFpgaMgr::getIFpgaOranRegs()) ;
	if (!oranRegs)
		return false ;

	unsigned numRx(IYangCarrierMgr::singleton()->numRx()) ;
	for (unsigned ant=0; ant < numRx; ++ant)
	{
		std::string endpoint(IYangCarrierMgr::singleton()->endpointName("rx", ant, carrierIndex)) ;
		std::map<std::string, std::shared_ptr<YangParam> > data(getEndpoint("rx", endpoint)) ;

		unsigned cc ;
		std::string processingElement ;
		std::string carrierArray ;
		endpointLinkDetails("rx", endpoint, cc, carrierArray, processingElement) ;

		// sanity check
		if (cc != carrierIndex)
			logEventWarning("ORAN Carrier UL: link carrier index %u does not match expected index (%u)", cc, carrierIndex) ;

		// Get the array carrier data
		std::map<std::string, std::shared_ptr<YangParam> > carrierData(getArrayCarrier("rx", carrierArray)) ;
		if (paramVal(carrierData, "active") != "ACTIVE")
		{
			// clear the EAXCID and move on
			carrier.setUlEaxcId(ant, 0) ;
			continue ;
		}

		auto processingElementData(getInterface(processingElement)) ;
		setRuMac(processingElementData) ;

		// destination MAC
		std::string macstr(paramVal(processingElementData, "o-du-mac-address")) ;
		uint64_t mac(strToMac(macstr)) ;
		carrier.setUlMacId(mac) ;

		// TODO: Move into Carrier (?)
		std::pair<unsigned, unsigned> cciq(IYangCarrierMgr::singleton()->lookupUlEndpoint(endpoint)) ;
		if (processingElementData.find("vlan-id") == processingElementData.end())
		{
			// destination VLAN
			oranRegs->write_uplaneVlanTag(cciq.second, 0) ;

			// VLAN enable
			oranRegs->write_uplaneVlanEnable(cciq.second, 0) ;
		}
		else
		{
			// destination VLAN
			oranRegs->write_uplaneVlanTag(cciq.second, paramValUInt16(processingElementData, "vlan-id")) ;

			// VLAN enable
			oranRegs->write_uplaneVlanEnable(cciq.second, 1) ;
		}

		// EAXC-ID
		carrier.setUlEaxcId(ant, paramValUInt16(data, "eaxc-id")) ;

		// frame-structure
		{
			uint8_t frameStruct( paramValUInt8(data, "frame-structure") ) ;

			if (rxFrameStruct == 0)
			{
				rxFrameStruct = frameStruct ;
			}
			else
			{
				// check against the other channels
				if (rxFrameStruct != frameStruct)
				{
					std::cerr << "SDP: RX frame struct " << (unsigned)rxFrameStruct << " does not match latest " << (unsigned)frameStruct << std::endl ;
					return false ;
				}
			}

			if (!carrier.setUlScs( frameStructToScsType(frameStruct) ) )
				return false ;

			ICarrier::FFTsizeType fftSize(frameStructToFFTsize(frameStruct));
			if (fftSize == ICarrier::FFT_NONE)
				return false ;
			if (! carrier.setUlFftSize(fftSize) )
				return false ;
		}

		// cp-type
		{
			std::string cptype( paramVal(data, "cp-type") ) ;

			if (! carrier.setUlPrefixLenConfig( ICarrier::strToPrefixLen( cptype ) ))
				return false ;
		}

		// cp-length
		{
			unsigned cplen( paramValUInt16(data, "cp-length") ) ;

			if (!carrier.setUlCpSize( cplen ) )
				return false ;
		}

		// cp-length-other
		{
			unsigned cplen( paramValUInt16(data, "cp-length-other") ) ;

			if (!carrier.setUlCpOtherSize( cplen ) )
				return false ;
		}

		// Frequency
		uint64_t centre(paramValUInt64(carrierData, "center-of-channel-bandwidth")) ;
		if (centre == 0)
			eventWarning("RX centre frequency 0. Value ignored...") ;

		if (centre > 0)
			if (!carrier.setRxFrequency( Frequency( (long long unsigned)centre, Frequency::Hz) ))
				return false ;

		carrierEnable = true ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanUplaneConf::handleCarrierPrach(ICarrierSetter& carrier, unsigned carrierIndex, bool active, bool& carrierEnable)
{
	// Handle the PRACH - probably should move this somewhere else, but do it here for now
	auto oranRegs(IFpgaMgr::getIFpgaOranRegs()) ;
	if (!oranRegs)
		return false ;

	unsigned numRx(IYangCarrierMgr::singleton()->numRx()) ;
	for (unsigned ant=0; ant < numRx; ++ant)
	{
		std::string endpoint(IYangCarrierMgr::singleton()->endpointName("prach", ant, carrierIndex)) ;
		std::map<std::string, std::shared_ptr<YangParam> > data(getEndpoint("rx", endpoint)) ;

		unsigned cc ;
		std::string processingElement ;
		std::string carrierArray ;
		endpointLinkDetails("rx", endpoint, cc, carrierArray, processingElement) ;

		// sanity check
		if (cc != carrierIndex)
			logEventWarning("ORAN Carrier PRACH: link carrier index %u does not match expected index (%u)", cc, carrierIndex) ;

		std::pair<unsigned, unsigned> cciq(IYangCarrierMgr::singleton()->lookupUlEndpoint(endpoint)) ;

		// Get the array carrier data
		std::map<std::string, std::shared_ptr<YangParam> > carrierData(getArrayCarrier("rx", carrierArray)) ;
		if (paramVal(carrierData, "active") != "ACTIVE")
		{
			// clear the EAXCID and move on
			oranRegs->write_rtcPcId(cciq.second, 0) ;
			continue ;
		}

		// EAXC-ID
		oranRegs->write_rtcPcId(cciq.second, paramValUInt16(data, "eaxc-id")) ;

		auto processingElementData(getInterface(processingElement)) ;
		setRuMac(processingElementData) ;

		// destination MAC
		std::string macstr(paramVal(processingElementData, "o-du-mac-address")) ;
		uint64_t mac(strToMac(macstr)) ;
		carrier.setUlMacId(mac) ;

		if (processingElementData.find("vlan-id") == processingElementData.end())
		{
			// destination VLAN
			oranRegs->write_uplaneVlanTag(cciq.second, 0) ;

			// VLAN enable
			oranRegs->write_uplaneVlanEnable(cciq.second, 0) ;
		}
		else
		{
			// destination VLAN
			oranRegs->write_uplaneVlanTag(cciq.second, paramValUInt16(processingElementData, "vlan-id")) ;

			// VLAN enable
			oranRegs->write_uplaneVlanEnable(cciq.second, 1) ;
		}
	}

	return true ;
}






//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string> > Zcu111FbcOranrrhHandlerORanUplaneConf::getLinks(const std::string &txrx)
{
	// get all of the links so I can search for the carrier name
	return getKeyValues( std::string(mCallback->path() + "/low-level-") + txrx + "-links//.") ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam> > Zcu111FbcOranrrhHandlerORanUplaneConf::getEndpoint(const std::string& txrx, const std::string &endpoint)
{
	return getParams( std::string(mCallback->path() + "/low-level-") + txrx + "-endpoints[name='" + endpoint + "']//.") ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam> > Zcu111FbcOranrrhHandlerORanUplaneConf::getArrayCarrier(const std::string& txrx, const std::string &carrierName)
{
	return getParams(mCallback->path() + "/" + txrx + "-array-carriers[name='" + carrierName + "']//.") ;
}


//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam> > Zcu111FbcOranrrhHandlerORanUplaneConf::getInterface(const std::string &processingElement)
{
	return getParams("/o-ran-processing-element:processing-elements/ru-elements[name='" + processingElement + "']//.") ;
}




//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanUplaneConf::setRuMac(const std::map<std::string, std::shared_ptr<YangParam> > &data)
{
	std::string macstr(paramVal(data, "ru-mac-address")) ;
	uint64_t mac(strToMac(macstr)) ;
	if (mRuMac == mac)
		return ;

	// TODO: Move to hardware ?
	auto oranRegs(IFpgaMgr::getIFpgaOranRegs()) ;
	if (!oranRegs)
		return ;

	mRuMac = mac ;

	uint16_t lo(mac & 0xffff) ;
	uint16_t mid((mac >> 16) & 0xffff) ;
	uint16_t hi((mac >> 32) & 0xffff) ;

	// There is only 1 register shared across all instances
	oranRegs->write_cuplaneSrcMacLo(0u, lo) ;
	oranRegs->write_cuplaneSrcMacMid(0u, mid) ;
	oranRegs->write_cuplaneSrcMacHi(0u, hi) ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrier::Type Zcu111FbcOranrrhHandlerORanUplaneConf::getLteChbw(const std::map<std::string, std::shared_ptr<YangParam> > &data)
{
	uint64_t bw(paramValUInt64(data, "channel-bandwidth")) ;

	// convert to MHz
	bw /= 1000000 ;

	// now slot this bandwidth into one of the valid types
	if (bw < 5)
		return ICarrier::CARRTYPE_NONE ;

	if (bw < 10)
		return ICarrier::CARRTYPE_LTE5 ;

	if (bw < 15)
		return ICarrier::CARRTYPE_LTE10 ;

	if (bw < 20)
		return ICarrier::CARRTYPE_LTE15 ;

	return ICarrier::CARRTYPE_LTE20 ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrier::Type Zcu111FbcOranrrhHandlerORanUplaneConf::get5GChbw(const std::map<std::string, std::shared_ptr<YangParam> > &data)
{
	uint64_t bw(paramValUInt64(data, "channel-bandwidth")) ;

	if (bw == 200000)
		return ICarrier::CARRTYPE_NBIOT ;

	// convert to MHz
	bw /= 1000000 ;

	// now slot this bandwidth into one of the valid types
	if (bw < 5)
		return ICarrier::CARRTYPE_NONE ;

	if (bw < 10)
		return ICarrier::CARRTYPE_5GNR5 ;

	if (bw < 15)
		return ICarrier::CARRTYPE_5GNR10 ;

	if (bw < 20)
		return ICarrier::CARRTYPE_5GNR15 ;

	if (bw < 25)
		return ICarrier::CARRTYPE_5GNR20 ;

	if (bw < 30)
		return ICarrier::CARRTYPE_5GNR25 ;

	if (bw < 40)
		return ICarrier::CARRTYPE_5GNR30 ;

	if (bw < 50)
		return ICarrier::CARRTYPE_5GNR40 ;

	if (bw < 60)
		return ICarrier::CARRTYPE_5GNR50 ;

	if (bw < 70)
		return ICarrier::CARRTYPE_5GNR60 ;

	if (bw < 80)
		return ICarrier::CARRTYPE_5GNR70 ;

	if (bw < 90)
		return ICarrier::CARRTYPE_5GNR80 ;

	if (bw < 100)
		return ICarrier::CARRTYPE_5GNR90 ;

	return ICarrier::CARRTYPE_5GNR100 ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanUplaneConf::updateRxCarrier(const std::string &carrierName)
{
	// skip if already present
	if (mRxCarrierState.find(carrierName) != mRxCarrierState.end())
		return ;

	// create new entry and a callback for it
	mRxCarrierState[carrierName] = "DISABLED" ;
	auto stateFunc = [this, carrierName](std::string name) -> std::string {
		return mRxCarrierState[carrierName] ;
	} ;

	auto activeFunc = [this, carrierName](std::string name) -> std::string {
		if (mRxCarrierState[carrierName] == "READY")
			return "ACTIVE" ;
		else
			return "INACTIVE" ;
	} ;

	auto carrierMgr( IYangCarrierMgr::singleton() ) ;
	carrierMgr->updateRxCarrier( carrierName, stateFunc, activeFunc ) ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanUplaneConf::updateTxCarrier(const std::string &carrierName)
{
	// skip if already present
	if (mTxCarrierState.find(carrierName) != mTxCarrierState.end())
		return ;

	// create new entry and a callback for it
	mTxCarrierState[carrierName] = "DISABLED" ;
	auto stateFunc = [this, carrierName](std::string name) -> std::string {
		return mTxCarrierState[carrierName] ;
	} ;

	auto activeFunc = [this, carrierName](std::string name) -> std::string {
		if (mTxCarrierState[carrierName] == "READY")
			return "ACTIVE" ;
		else
			return "INACTIVE" ;
	} ;

	auto carrierMgr( IYangCarrierMgr::singleton() ) ;
	carrierMgr->updateTxCarrier( carrierName, stateFunc, activeFunc ) ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanUplaneConf::carrierChangeNotification(
		const std::string &txrx, const std::string &carrierName,
		const std::string &currentState, const std::string &newState)
{
	// skip if the same
	if (newState == currentState)
		return ;

	std::string notifPath( path(txrx + "-array-carriers-state-change") ) ;
	std::string carrierPath( notifPath + "/" + txrx + "-array-carriers[name='" + carrierName + "']" ) ;

	std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;
	params->addParam(carrierName, carrierPath + "/name") ;
	params->addParam(newState, carrierPath + "/state") ;

	sendNotification(notifPath, params) ;
}
