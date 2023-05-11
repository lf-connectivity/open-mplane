/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanTransceiver.h
 * \brief     ORAN Transceiver module handler
 *
 *
 * \details   ORAN Transceiver module handler
 *
 */

#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANTRANSCEIVER_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANTRANSCEIVER_H_

#include <string>
#include <memory>

#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanTransceiver
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanTransceiver : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanTransceiver(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanTransceiver();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

protected:
	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath,
	                         std::shared_ptr<YangParam> oldValue,
	                         std::shared_ptr<YangParam> newValue);

	/*!
	 \brief Module change hook - called by module_change() method to have this class validate the proposed values changes
	 \param params A YangParams pointer containing all of the changed values
	 \return SR_ERR_OK if the values are validated; SR_ERR_VALIDATION_FAILED on validation failure. Can return any other sysrepo error
	 status as necessary.
	 */
	virtual int validate(std::shared_ptr<YangParams> params, std::shared_ptr<YangParams> deletedParams) ;

private:
	/*
	 * Callbacks
	 */
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;

	std::map<std::string, uint8_t> mInterfaces;
	std::map<int, int> mEthPortToSFPPort;
	static const std::map<int, std::string> mSffComplianCode;
	static const std::map<int, std::string> mSffTransceiverIdentifier;
	static const std::map<int, std::string> mConnectorType;

	/**
	 * Get the interfaces from ietf-interfaces module
	 */
	std::map<std::string, std::map<std::string, std::string> > getInterfaces(void);

	/**
	 * Get the port reference for a given interface name
	 */
	std::map<std::string, std::shared_ptr<YangParam> > getPortReference(std::string interface);

	/**
	 * Method to populate interfaces
	 */
	void populateInterfaces(void);

	/**
	 * Method to create read-write data
	 */
	void createReadWriteData(std::string ethPort, uint8_t portNum);

	/**
	 * Method to create read-only data
	 */
	void createReadOnlyData(std::string ethPort, uint8_t portNum);

	/**
	 * Method to write transceiver files
	 */
	void writeTransceiverFiles(void);

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANTRANSCEIVER_H_ */
