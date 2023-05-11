/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranUserMgmtHandler.cpp
 * \brief     ORAN user management Model module handler
 *
 *
 * \details   ORAN user management Model module handler
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "OranUserMgmtHandler.h"
#include "ILeafContainer.h"
#include "RadioDatastoreSysrepo.h"
#include "SysrepoUtils.h"
#include "stringfunc.hpp"
#include <iostream>
using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranUserMgmtHandler::OranUserMgmtHandler(
    std::shared_ptr<IYangModuleMgr> moduleMgr)
    : YangHandlerSysrepo("o-ran-usermgmt", moduleMgr, "OranUserMgmtHandler") {}

//-------------------------------------------------------------------------------------------------------------
OranUserMgmtHandler::~OranUserMgmtHandler() {}

//-------------------------------------------------------------------------------------------------------------

bool
OranUserMgmtHandler::initialise() {
  if (!this->YangHandlerSysrepo::initialise())
    return false;
  // NOTE: We can't load this module until there is at least one enabled user,
  // and that needs to be set up on the start up data BEFORE any sysrepo
  // connections. In other words it needs to be done in a start up script.
  REGISTER_RPC("chg-password", OranUserMgmtHandler::rpcChgPassword);
  return true;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------

bool
OranUserMgmtHandler::rpcChgPassword(
    std::shared_ptr<sysrepo::Session> session,
    const std::string& rpcXpath,
    std::shared_ptr<YangParams> callList,
    std::shared_ptr<YangParams> retList) {
  std::map<std::string, std::shared_ptr<YangParam>> args(
      SysrepoUtils::paramsToMap(callList));
  std::string error;
  std::string newPassword(YangParamUtils::toString(args["newPassword"], error));
  std::string newPasswordConfirm(
      YangParamUtils::toString(args["newPasswordConfirm"], error));
  const std::string rpc("chg-password");
  if (newPasswordConfirm != newPassword) {
    retList->addParam("Failed", path(rpc + "/status"));
    retList->addParam(
        "New Passwords don't match", path(rpc + "/status-message"));
    return true;
  }

  std::string userName(session->get_user());
  std::string userMgmtPath("/o-ran-usermgmt:users[name='" + userName + "']/password");
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));
  std::shared_ptr<YangParam> passwordParam;
  std::string currentPassword(
      YangParamUtils::toString(args["currentPassword"], error));
  if (ds->getItem(userMgmtPath, passwordParam) != YangResult_E::OK) {
    retList->addParam("Failed", path(rpc + "/status"));
    retList->addParam(
        "Failed to get current password", path(rpc + "/status-message"));
    return true;
  }
  if (currentPassword != passwordParam->getString()) {
    retList->addParam("Failed", path(rpc + "/status"));
    retList->addParam(
        "Current Password Match Failed", path(rpc + "/status-message"));
    return true;
  }

  if (ds->setItemStr(userMgmtPath, newPassword) != YangResult_E::OK) {
    retList->addParam("Failed", path(rpc + "/status"));
    retList->addParam(
        "Password has not successfully updated", path(rpc + "/status-message"));
    return true;
  }
  retList->addParam("Success", path(rpc + "/status"));
  retList->addParam(
      "Password has been successfully updated", path(rpc + "/status-message"));
  return true;
}
