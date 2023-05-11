/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranUserMgmtHandler.h
 * \brief     ORAN user management Model module handler
 *
 *
 * \details   IETF NETCONF Access Control Model module handler
 *
 */

#ifndef INC_ORANUSERMGMT_HANDLER_H_
#define INC_ORANUSERMGMT_HANDLER_H_

#include <string>
#include <memory>

#include "YangMgrServer.h"
#include "YangHandlerSysrepo.h"

namespace Mplane
{

/*!
 * \class  OranUserMgmtHandler
 * \brief
 * \details
 *
 */
class OranUserMgmtHandler : public YangHandlerSysrepo
{
public:
 OranUserMgmtHandler(std::shared_ptr<IYangModuleMgr> moduleMgr);
 virtual ~OranUserMgmtHandler();

 /*
  * Run the initialisation of the handler (can only be done once the rest of the
  * YANG framework is up)
  */
 virtual bool initialise() override;

private:
 bool rpcChgPassword(
     std::shared_ptr<sysrepo::Session> session,
     const std::string& rpcXpath,
     std::shared_ptr<YangParams> callList,
     std::shared_ptr<YangParams> retList);
};

}

#endif /* INC_ORANUSERMGMT_HANDLER_H_ */
