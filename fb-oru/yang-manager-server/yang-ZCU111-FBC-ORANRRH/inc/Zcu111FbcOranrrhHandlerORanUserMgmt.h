/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanUserMgmt.h
 * \brief     ORAN user management Model module handler
 *
 *
 * \details   IETF NETCONF Access Control Model module handler
 *
 */

#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORanUserMgmt_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORanUserMgmt_H_

#include <string>
#include <memory>

#include "YangMgrServer.h"
#include "YangHandlerSysrepo.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanUserMgmt
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanUserMgmt : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanUserMgmt(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanUserMgmt();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

private:
	bool rpcChgPassword(std::shared_ptr<sysrepo::Session> session, const std::string& rpcXpath,
			std::shared_ptr<YangParams> callList, std::shared_ptr<YangParams> retList) ;

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORanUserMgmt_H_ */
