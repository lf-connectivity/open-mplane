/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranSupervisionHandler.h
 * \brief     O-RAN supervision module handler
 *
 *
 * \details   O-RAN supervision module handler
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_OranSupervisionHandler_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_OranSupervisionHandler_H_

#include <string>
#include <memory>

#include "IMPlaneConnectivityService.h"
#include "ICUPlaneMonitor.h"

#include "YangMgrServer.h"
#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  OranSupervisionHandler
 * \brief
 * \details
 *
 */
class OranSupervisionHandler : public YangHandlerSysrepo
{
public:
	OranSupervisionHandler(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~OranSupervisionHandler();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

protected:
	/*
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath,
	                         std::shared_ptr<YangParam> oldValue,
	                         std::shared_ptr<YangParam> newValue);

private:
	/*
	 * RPC callbacks
	 */
	bool rpcSupervisionWatchdogReset(std::shared_ptr<sysrepo::Session> session, const std::string& rpcXpath,
	                                 std::shared_ptr<YangParams> paramsIn,
	                                 std::shared_ptr<YangParams> paramsOut);

	/*
	 * RPC helpers
	 */
	bool getRpcArg(std::shared_ptr<YangParams> params,
	               const std::string & param,
	               UINT16 & paramVal);

	/*
	 * Notifications
	 */
	void netconfSessionUpNotification();

	/*
	 * Handler callbacks
	 */
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;

	/*
	 * M-Plane connectivity service
	 */
	std::shared_ptr<IMPlaneConnectivityService> mMPlaneService;

	/*
	 * C/U-Plane monitor
	 */
	std::shared_ptr<ICUPlaneMonitor> mCUPlaneMonitor;

};

}

#endif /* YANG_OranSupervisionHandler_H_ */
