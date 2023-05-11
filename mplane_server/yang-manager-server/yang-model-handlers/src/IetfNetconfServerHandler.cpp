/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IetfNetconfServerHandler.cpp
 * \brief     IETF NETCONF Server configuration module handler
 *
 *
 * \details   IETF NETCONF Server configuration module handler
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <ctime>
#include <fstream>
#include <iostream>

#include "IAppOptions.h"
#include "stringfunc.hpp"

#include "ILeafContainer.h"
#include "ILoggable.h"

#include "RadioDatastoreSysrepo.h"
#include "YangMgrServer.h"
#include "YangParamUtils.h"

#include "IIpPortMgr.h"
#include "IetfNetconfServerHandler.h"

using namespace Mplane;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
IetfNetconfServerHandler::IetfNetconfServerHandler(
    std::shared_ptr<IYangModuleMgr> moduleMgr)
    : YangHandlerSysrepo(
          "ietf-netconf-server", moduleMgr, "IetfNetconfServerHandler") {
  // Get any call home clients from the stored list and add them to sysrepo
  for (auto& client : IIpPortMgr::singleton()->list()) {
    // Add new client to sysrepo
    addCallHomeClient(client.first, std::to_string(client.second));
  }
}

//-------------------------------------------------------------------------------------------------------------
IetfNetconfServerHandler::~IetfNetconfServerHandler() {}

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfServerHandler::initialise() {
  // daisychain the initialisations
  if (!this->YangHandlerSysrepo::initialise())
    return false;

  return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
IetfNetconfServerHandler::valueChange(
    const std::string& xpath,
    std::shared_ptr<YangParam> oldValue,
    std::shared_ptr<YangParam> newValue) {
  if (oldValue && !newValue) {
    logDebugVerbose(
        "IetfNetconfServerHandler::valueChange() - %s",
        oldValue->name().c_str());
  }
  if (newValue) {
    logDebugVerbose(
        "IetfNetconfServerHandler::valueChange() - %s",
        newValue->name().c_str());
  }
}

//-------------------------------------------------------------------------------------------------------------
int
IetfNetconfServerHandler::validate(
    std::shared_ptr<YangParams> params,
    std::shared_ptr<YangParams> deletedParams) {
  return SR_ERR_OK;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfServerHandler::addCallHomeClient(std::string url, std::string port) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));

  std::string clientName = "client-" + url + "-" + port;

  std::string endPointPath = "endpoints/endpoint[name='ssh-endpoint']";
  std::string callHome =
      "/ietf-netconf-server:netconf-server/call-home/netconf-client";
  YangResult_E result = ds->createListEntry(
      callHome,
      "name",
      clientName,
      std::map<std::string, std::shared_ptr<std::string>>{
          {endPointPath, nullptr},
          {endPointPath + "/ssh/tcp-client-parameters/remote-address",
           std::make_shared<std::string>(url)},
          {endPointPath + "/ssh/tcp-client-parameters/remote-port",
           std::make_shared<std::string>(port)},
          {endPointPath + "/ssh/tcp-client-parameters/keepalives/idle-time",
           std::make_shared<std::string>("60")},
          {endPointPath + "/ssh/tcp-client-parameters/keepalives/max-probes",
           std::make_shared<std::string>("10")},
          {endPointPath +
               "/ssh/tcp-client-parameters/keepalives/probe-interval",
           std::make_shared<std::string>("30")},
          {endPointPath + "/ssh/ssh-server-parameters/server-identity/"
                          "host-key[name='default-key']",
           nullptr},
          {endPointPath +
               "/ssh/ssh-server-parameters/server-identity/"
               "host-key[name='default-key']/public-key/keystore-reference",
           std::make_shared<std::string>("genkey")},
          {endPointPath + "/ssh/ssh-server-parameters/client-authentication/"
                          "users/user[name='default-user']",
           nullptr},
          {"connection-type/persistent", nullptr},
      });

  return (result == YangResult_E::OK);
}

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfServerHandler::deleteCallHomeClient(
    std::string url, std::string port) {
  YangResult_E result = YangResult_E::NOT_FOUND;

  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));

  std::string clientListPath =
      "/ietf-netconf-server:netconf-server/call-home/netconf-client";
  std::vector<std::string> keyValues;
  std::string clientNameToSearch = "name='client-" + url + "-" + port + "'";

  ds->getListItems(clientListPath, keyValues);

  // Check if the client is present in the sysrepo
  if (std::find(keyValues.begin(), keyValues.end(), clientNameToSearch) !=
      keyValues.end()) {
    // Check if there are more than 1 clients in the list
    if (keyValues.size() > 1) {
      result = ds->deleteItem(clientListPath + "[" + clientNameToSearch + "]");
    }
    // If there is a single client in the list, then delete the call home
    // container
    else {
      result = ds->deleteItem("netconf-server/call-home");
    }
  }

  return (result == YangResult_E::OK);
}
