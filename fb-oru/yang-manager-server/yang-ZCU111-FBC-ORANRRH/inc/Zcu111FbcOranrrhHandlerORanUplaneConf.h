/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanUplaneConf.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANUPLANECONF_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANUPLANECONF_H_

#include "SysrepoGetitemsCallback.h"
#include "YangHandlerSysrepo.h"

namespace Mplane {

/*!
 * \class  Zcu111FbcOranrrhUplaneHandler
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanUplaneConf : public YangHandlerSysrepo {
public:
	Zcu111FbcOranrrhHandlerORanUplaneConf(std::shared_ptr<IYangModuleMgr> moduleMgr) ;
	virtual ~Zcu111FbcOranrrhHandlerORanUplaneConf() ;

	/**
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override ;

protected:
	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath, std::shared_ptr<YangParam> oldValue, std::shared_ptr<YangParam> newValue) override ;

	/*!
	 \brief Module change hook - called by module_change() method to have this class validate the proposed values changes
	 \param params A YangParams pointer containing all of the changed values
	 \return SR_ERR_OK if the values are validated; SR_ERR_VALIDATION_FAILED on validation failure. Can return any other sysrepo error
	 status as necessary.
	 */
	virtual int validate(std::shared_ptr<YangParams> params, std::shared_ptr<YangParams> deletedParams) override ;


private:
	enum TxRxSettings {
		SETTING_TX,
		SETTING_RX,
	};

	enum ValuePhase {
		VALUE_VALIDATE,
		VALUE_APPLY,
	};

	/**
	 * Apply the value change. Expects calling method to have extracted the leaf name and value of the variable
	 * \return SR_ERR_OK if value change applied ok
	 */
	int processValue(std::shared_ptr<YangParam> param, const std::string& leaf, const std::string& value) ;

	/**
	 * Apply the value change. Expects calling method to have extracted the leaf name and value of the variable
	 * \return SR_ERR_OK if change is valid
	 */
	int validateValue(std::shared_ptr<YangParam> param, const std::string& leaf, const std::string& value) ;

	/**
	 * Handle an "active" change during the validate or apply value phases
	 */
	int handleActivate(std::shared_ptr<YangParam> param, const std::string& leaf, const std::string& value, ValuePhase phase) ;


	/**
	 * Given a carrier index, get the TX/RX carrier name
	 */
	std::string getCarrierName(const std::string& txrx, unsigned carrierIndex) ;

	/**
	 * Working from the carrier array name, get it's link details
	 */
	bool carrierLinkDetails(const std::string& txrx, const std::string& carrierName,
			unsigned& carrierIndex, std::string& endpoint, std::string& processingElement) ;

	/**
	 * Get the link entry values
	 */
	bool getLink(const std::string &txrx, const std::string& linkName,
			std::string &endpoint, std::string &carrierName) ;

	/**
	 * Working from the endpoint name, get it's link details
	 */
	bool endpointLinkDetails(const std::string& txrx, const std::string& endpoint,
			unsigned& carrierIndex, std::string& carrierName, std::string& processingElement) ;

	/**
	 * Process the carrier settings for this carrier
	 */
	bool handleCarrier(unsigned carrierIndex, TxRxSettings txrx, bool active, ValuePhase phase) ;

	/**
	 * Do the TX setup
	 */
	bool handleCarrierTx(ICarrierSetter& carrier, unsigned carrierIndex, bool active, bool& carrierEnable, uint8_t& frameStruct) ;

	/**
	 * Do the RX setup
	 */
	bool handleCarrierRx(ICarrierSetter& carrier, unsigned carrierIndex, bool active, bool& carrierEnable, uint8_t& frameStruct) ;

	/**
	 * Do the PRACH setup
	 */
	bool handleCarrierPrach(ICarrierSetter& carrier, unsigned carrierIndex, bool active, bool& carrierEnable) ;

	/**
	 * Set the O-RU MAC id (if required)
	 */
	void setRuMac(const std::map<std::string, std::shared_ptr<YangParam>>& data) ;

	/**
	 * Read the links and process the data into a map of vectors. Map key is the link name, vector
	 * is the name/value pairs for that link
	 */
	std::map<std::string, std::map<std::string, std::string>> getLinks(const std::string &txrx) ;

	/**
	 * Read the endpoint and convert the list of params into variable name / YangParam pairs. Variable name
	 * is the leaf name (not the full xpath)
	 */
	std::map<std::string, std::shared_ptr<YangParam>> getEndpoint(const std::string& txrx, const std::string& endpoint) ;

	/**
	 * Read the endpoint and convert the list of params into variable name / YangParam pairs. Variable name
	 * is the leaf name (not the full xpath)
	 */
	std::map<std::string, std::shared_ptr<YangParam>> getArrayCarrier(const std::string& txrx, const std::string& carrierName) ;

	/**
	 * Read the processing element and convert the list of params into
	 * variable name / YangParam pairs. Variable name is the leaf name (not the full xpath)
	 */
	std::map<std::string, std::shared_ptr<YangParam>> getInterface(const std::string& processingElement) ;

	/**
	 * Use the array carrier data to convert the bandwidth (in Hz) into a carrier type for an LTE carrier
	 */
	ICarrier::Type getLteChbw(const std::map<std::string, std::shared_ptr<YangParam>>& data) ;

	/**
	 * Use the array carrier data to convert the bandwidth (in Hz) into a carrier type for a 5G carrier
	 */
	ICarrier::Type get5GChbw(const std::map<std::string, std::shared_ptr<YangParam>>& data) ;

	/**
	 * Ensure RX carrier is in the tree
	 */
	void updateRxCarrier(const std::string& carrierName) ;

	/**
	 * Ensure TX carrier is in the tree
	 */
	void updateTxCarrier(const std::string& carrierName) ;


	/**
	 * Send a notification if needed
	 */
	void carrierChangeNotification(const std::string& txrx, const std::string& carrierName,
			const std::string& currentState, const std::string& newState);


private:
	std::shared_ptr<SysrepoGetitemsCallback> mCallback ;
	uint64_t mRuMac ;
	std::map<std::string, std::string> mRxCarrierState ;
	std::map<std::string, std::string> mTxCarrierState ;
} ;

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANUPLANECONF_H_ */
