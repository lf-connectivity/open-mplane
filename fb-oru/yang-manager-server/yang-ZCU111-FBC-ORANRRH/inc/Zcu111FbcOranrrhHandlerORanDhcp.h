/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanDhcp.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANDHCP_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANDHCP_H_

#include <string>
#include <memory>

#include "YangMgrServer.h"
#include "YangParamUtils.h"
#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"
#include "IDhcpOptions.h"
#include <mutex>

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanDhcp
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanDhcp : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanDhcp(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanDhcp();

	static const uint32_t mPrivateEnterpriseNum;
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

	void getDhcpOptions(const std::string& interface) ;
	std::string handleGetCallback(const std::string& leafName, const std::string& ifvlan) ;
	std::shared_ptr<ILeafContainer> getDhcpv4Node(std::string interfaceName);
	void addDhcpLists(std::shared_ptr<ILeafContainer>& dhcpv4,
			std::vector<std::string>& dns, std::vector<std::string>& gateways,
			std::map<std::string, std::string>& netconfClients,
			std::map<unsigned int, std::vector<std::string>>& vendorInfo);

	std::shared_ptr<SysrepoGetitemsCallback> mCallback;

	std::mutex mMutex ;
	std::string mProductCode;
	std::string mSerialNumber;
	std::shared_ptr<IDhcpOptions> mDhcpOptions;
	std::vector<std::string> mInterfaces;
};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANDHCP_H_ */
