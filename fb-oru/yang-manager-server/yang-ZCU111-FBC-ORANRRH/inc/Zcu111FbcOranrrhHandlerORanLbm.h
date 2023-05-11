/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanLbm.cpp
 * \brief     O-RAN radio loop-back module (LBM) handler
 *
 *
 * \details   O-RAN radio loop-back module (LBM) handler
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANLBM_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANLBM_H_

#include <string>
#include <memory>

#include "Dot1agdMonService.h"

#include "YangMgrServer.h"
#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanLbm
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanLbm : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanLbm(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanLbm();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

	/*
	 * Add an maintenance domain entry
	 */
	virtual void addMaintenaceDomainEntry(const std::string & ethName,
	                                      const std::string & macAddr,
	                                      UINT16 vlanId);

protected:
	/*
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath,
	                         std::shared_ptr<YangParam> oldValue,
	                         std::shared_ptr<YangParam> newValue);

	/*
	 * Control the 802.1ag daemon application
	 */
	void startDot1agDaemonApp(const std::string & ethName);
	void stopDot1agDaemonApp();

private:

	/*
	 * Handler callbacks
	 */
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;

	/*
	 * 802.1ag Daemon monitoring service
	 */
	std::shared_ptr<Dot1agdMonService> mDot1agdMonService;

	std::string mDomainId;
	std::string mDomainName;
	std::string mAssocId;
	std::string mAssocName;

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANLBM_H_ */
