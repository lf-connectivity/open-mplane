/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangHandlerSysrepoUnlogged.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <functional>

#include "RadioDatastoreSysrepo.h"
#include "SysrepoUtils.h"
#include "YangMgrServer.h"
#include "YangParamUtils.h"
#include "stringfunc.hpp"

#include "YangHandlerSysrepoUnlogged.h"
#include "YangParamSysrepo.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangHandlerSysrepoUnlogged::YangHandlerSysrepoUnlogged(
    const std::string& moduleName, std::shared_ptr<IYangModuleMgr> moduleMgr)
    : YangHandler(moduleName, moduleMgr),
      mHandlerCallback(std::make_shared<HandlerCallback>(
          this,
          [this]() -> std::set<std::string> { return mReadOnlyPaths; },
          [this](std::shared_ptr<sysrepo::Val> val) { setVal(val); },
          [this]() { persistMgr()->write(); })),
      mReadOnlyPaths(),
      mRpcCallbacks() {}

//-------------------------------------------------------------------------------------------------------------
YangHandlerSysrepoUnlogged::~YangHandlerSysrepoUnlogged() {}

//-------------------------------------------------------------------------------------------------------------
bool
YangHandlerSysrepoUnlogged::initialise() {
  logInfo(groupName() + ": Initialising '" + name() + "' module handler");

  // daisychain the initialisations
  if (!this->YangHandler::initialise())
    return false;

  // process any persistent values
  std::map<std::string, std::string> values(persistMgr()->values());
  if (values.empty())
    return true;

  logInfo(
      groupName() + ": Initialising " + std::to_string(values.size()) +
      " persistent values");

  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));
  for (auto entry : values) {
    ds->setItemStr(entry.first, entry.second);
  }

  return true;
}

//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
YangHandlerSysrepoUnlogged::valueChange(
    const std::string& xpath,
    std::shared_ptr<YangParam> oldValue,
    std::shared_ptr<YangParam> newValue) {
  // does nothing in this class
}

//-------------------------------------------------------------------------------------------------------------
void
YangHandlerSysrepoUnlogged::paramDelete(
    const std::string& xpath, std::shared_ptr<YangParam> oldValue) {
  // does nothing in this class
}

//-------------------------------------------------------------------------------------------------------------
int
YangHandlerSysrepoUnlogged::validate(
    std::shared_ptr<YangParams> params,
    std::shared_ptr<YangParams> deletedParams) {
  //    std::cerr << "YangHandlerSysrepoUnlogged::validate" << std::endl ;
  //    for (unsigned i=0; i < params->getNumParams(); ++i)
  //    {
  //        std::shared_ptr<YangParam> p(params->getParam(i)) ;
  //        std::string error ;
  //        std::cerr << " " << p->name() << " = " <<
  // YangParamUtils::toString(p, error) << std::endl ;
  //    }

  // default is to return invalid
  return SR_ERR_OK;

  //    return SR_ERR_VALIDATION_FAILED ;
}

//-------------------------------------------------------------------------------------------------------------
void
YangHandlerSysrepoUnlogged::logInfo(const std::string& info) {}

//-------------------------------------------------------------------------------------------------------------
std::string
YangHandlerSysrepoUnlogged::groupName() const {
  return "";
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string
YangHandlerSysrepoUnlogged::path(const std::string& path) const {
  return ("/" + name() + ":" + path);
}

//-------------------------------------------------------------------------------------------------------------
void
YangHandlerSysrepoUnlogged::changeSubscribe(const std::string& xpath) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));

  ds->itemsChangeSubscribe(
      name(),
      std::dynamic_pointer_cast<sysrepo::Callback>(mHandlerCallback),
      xpath,
      this);
}

//-------------------------------------------------------------------------------------------------------------
void
YangHandlerSysrepoUnlogged::makeReadOnly(const std::set<std::string>& paths) {
  for (auto xpath : paths) {
    logInfo(groupName() + ": makeReadOnly() - '" + xpath + "'");
  }
  mReadOnlyPaths.insert(paths.begin(), paths.end());
}

//-------------------------------------------------------------------------------------------------------------
void
YangHandlerSysrepoUnlogged::makeReadOnly(const std::string& xpath) {
  logInfo(groupName() + ": makeReadOnly() - '" + xpath + "'");
  mReadOnlyPaths.insert(xpath);
}

//-------------------------------------------------------------------------------------------------------------
void
YangHandlerSysrepoUnlogged::removeReadOnly(const std::string& xpath) {
  //    logDebugNormal("YANG: removeReadOnly() - '" + xpath + "'");
  mReadOnlyPaths.erase(xpath);
}
//-------------------------------------------------------------------------------------------------------------
void
YangHandlerSysrepoUnlogged::getItemsSubscribe(
    const std::string& xpath, std::shared_ptr<sysrepo::Callback> callback) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));

  ds->getItemsSubscribe(name(), xpath, callback, this);
}

//-------------------------------------------------------------------------------------------------------------
YangResult_E
YangHandlerSysrepoUnlogged::createItemStr(
    const std::string& xpath, const std::string& value) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));

  return ds->setItemStr(xpath, value);
}

//-------------------------------------------------------------------------------------------------------------
YangResult_E
YangHandlerSysrepoUnlogged::createListEntry(
    const std::string& xpath, std::map<std::string, std::string> values) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));

  return ds->createListEntry(xpath, values);
}

//-------------------------------------------------------------------------------------------------------------
YangResult_E
YangHandlerSysrepoUnlogged::createListEntry(
    const std::string& xpath,
    const std::string& key,
    const std::string& keyval,
    std::map<std::string, std::string> values) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));

  return ds->createListEntry(xpath, key, keyval, values);
}

//-------------------------------------------------------------------------------------------------------------
YangResult_E
YangHandlerSysrepoUnlogged::sendNotification(
    const std::string& xpath, std::shared_ptr<YangParams> params) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));

  return ds->sendNotification(xpath, params);
}

//-------------------------------------------------------------------------------------------------------------
void
YangHandlerSysrepoUnlogged::registerRpc(
    const std::string& rpcPath, RpcCallback::RpcFunc func) {
  std::string xpath(path(rpcPath));

  // Convert to full path
  std::shared_ptr<RpcCallback> callback(
      std::make_shared<RpcCallback>(xpath, func));

  logInfo(groupName() + ": Registering RPC - '" + xpath + "'");

  // register
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));
  ds->rpcSubscribe(xpath, callback);

  // Add callback to list
  mRpcCallbacks.push_back(callback);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>>
YangHandlerSysrepoUnlogged::getKeyParams(const std::string& path) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  return SysrepoUtils::getKeyParams(mgr, path);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string>>
YangHandlerSysrepoUnlogged::getKeyValues(const std::string& path) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  return SysrepoUtils::getKeyValues(mgr, path);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam>>
YangHandlerSysrepoUnlogged::getParams(const std::string& xpath) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  return SysrepoUtils::getParams(mgr, xpath);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>>
YangHandlerSysrepoUnlogged::getOperationalKeyParams(const std::string& path) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  return SysrepoUtils::getOperationalKeyParams(mgr, path);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string>>
YangHandlerSysrepoUnlogged::getOperationalKeyValues(const std::string& path) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  return SysrepoUtils::getOperationalKeyValues(mgr, path);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam>>
YangHandlerSysrepoUnlogged::getOperationalParams(const std::string& xpath) {
  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  return SysrepoUtils::getOperationalParams(mgr, xpath);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam>>
YangHandlerSysrepoUnlogged::paramsToMap(
    std::shared_ptr<YangParams> params) const {
  return SysrepoUtils::paramsToMap(params);
}

//-------------------------------------------------------------------------------------------------------------
std::string
YangHandlerSysrepoUnlogged::paramVal(
    const std::map<std::string, std::shared_ptr<YangParam>>& values,
    const std::string& key) {
  return SysrepoUtils::paramVal(values, key);
}

//-------------------------------------------------------------------------------------------------------------
uint8_t
YangHandlerSysrepoUnlogged::paramValUInt8(
    const std::map<std::string, std::shared_ptr<YangParam>>& values,
    const std::string& key) {
  return SysrepoUtils::paramValUInt8(values, key);
}

//-------------------------------------------------------------------------------------------------------------
uint16_t
YangHandlerSysrepoUnlogged::paramValUInt16(
    const std::map<std::string, std::shared_ptr<YangParam>>& values,
    const std::string& key) {
  return SysrepoUtils::paramValUInt16(values, key);
}

//-------------------------------------------------------------------------------------------------------------
uint32_t
YangHandlerSysrepoUnlogged::paramValUInt32(
    const std::map<std::string, std::shared_ptr<YangParam>>& values,
    const std::string& key) {
  return SysrepoUtils::paramValUInt32(values, key);
}

//-------------------------------------------------------------------------------------------------------------
uint64_t
YangHandlerSysrepoUnlogged::paramValUInt64(
    const std::map<std::string, std::shared_ptr<YangParam>>& values,
    const std::string& key) {
  return SysrepoUtils::paramValUInt64(values, key);
}

//-------------------------------------------------------------------------------------------------------------
double
YangHandlerSysrepoUnlogged::paramValDecimal64(
    const std::map<std::string, std::shared_ptr<YangParam>>& values,
    const std::string& key) {
  return SysrepoUtils::paramValDecimal64(values, key);
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
YangHandlerSysrepoUnlogged::setVal(std::shared_ptr<sysrepo::Val> value) {
  // std::cerr << "YangHandlerSysrepoUnlogged::setVal " << value->xpath() << " :
  // " << value->to_string() << std::endl ;

  std::string xpath(charpToString(value->xpath()));

  // pass value over to persistence manager
  persistMgr()->set(xpath, value->val_to_string());

  // Do check on values - some values come in with an xpath that isn't unique.
  // For example, list entries
  // /o-ran-mplane-int:mplane-info/searchable-mplane-access-vlans-info/searchable-access-vlans
  // = 4 should come in as
  // /o-ran-mplane-int:mplane-info/searchable-mplane-access-vlans-info/searchable-access-vlans[.='4']
  // = 4 otherwise we end up with all of the list entries over writing each
  // other.
  //
  // In order to fix this I have to read back the xpath and ensure the values
  // are set. So for the above, reading the xpath might give:
  //
  // /o-ran-mplane-int:mplane-info/searchable-mplane-access-vlans-info/searchable-access-vlans[.='4']
  // = 4
  // /o-ran-mplane-int:mplane-info/searchable-mplane-access-vlans-info/searchable-access-vlans[.='1']
  // = 1
  //

  std::shared_ptr<YangMgrServer> mgr(
      std::dynamic_pointer_cast<YangMgrServer>(moduleMgr()));
  std::shared_ptr<RadioDatastoreSysrepo> ds(
      std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore()));

  std::shared_ptr<YangParams> params;
  if (ds->getItems(xpath, params) != YangResult_E::OK) {
    //        std::cerr << "Failed to read values inside setVal!" << std::endl
    //;
    return;
  }

  for (unsigned i = 0; i < params->getNumParams(); ++i) {
    std::shared_ptr<YangParam> p(params->getParam(i));
    std::string error;
    //        std::cerr << " + '" << p->name() << "' = '" <<
    // YangParamUtils::toString(p, error) << "'" << std::endl ;

    // skip any that match the original xpath because we've already done it
    if (p->name() == xpath)
      continue;

    persistMgr()->set(p->name(), YangParamUtils::toString(p, error));
  }
}
