/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerIetfNetconfServer.h
 * \brief     IETF NETCONF Server configuration module handler
 *
 *
 * \details   IETF NETCONF Server configuration module handler
 *
 */

#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFNETCONFSERVER_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFNETCONFSERVER_H_

#include <string>
#include <memory>

#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"
#include "IDhcpOptions.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerIetfNetconfServer
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerIetfNetconfServer : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerIetfNetconfServer(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerIetfNetconfServer();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

protected:
	/*!
	 \brief Module change hook - called by module_change() method to have this class validate the proposed values changes
	 \param params A YangParams pointer containing all of the changed values
	 \return SR_ERR_OK if the values are validated; SR_ERR_VALIDATION_FAILED on validation failure. Can return any other sysrepo error
	 status as necessary.
	 */
	virtual int validate(std::shared_ptr<YangParams> params, std::shared_ptr<YangParams> deletedParams) ;

	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath,
	                         std::shared_ptr<YangParam> oldValue,
	                         std::shared_ptr<YangParam> newValue);

private:
	/*
	 * Callbacks
	 */
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;
	std::shared_ptr<IDhcpOptions> mDhcpOptions;
	std::string mEthbbInterface;

	void getInterfaceInfo(const std::string& interface);
	std::map<std::string, std::string> getCallHomeClients(void);
	bool addCallHomeClient(std::string url, std::string port);
	bool deleteCallHomeClient(std::string url, std::string port);


};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFNETCONFSERVER_H_ */
