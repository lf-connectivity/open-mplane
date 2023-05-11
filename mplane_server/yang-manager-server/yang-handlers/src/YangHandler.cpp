/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangHandler.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangHandler.h"
#include "XpathUtils.h"
#include "YangParamUtils.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangHandler::YangHandler(
    const std::string& name, std::shared_ptr<IYangModuleMgr> moduleMgr)
    : mName(name),
      mModuleMgr(moduleMgr),
      mPersist(IYangPersist::factory(mName)) {
  // ensure we get any saved values
  mPersist->read();
}

//-------------------------------------------------------------------------------------------------------------
YangHandler::~YangHandler() {}

//-------------------------------------------------------------------------------------------------------------
std::string
YangHandler::name() const {
  return mName;
}

//-------------------------------------------------------------------------------------------------------------
bool
YangHandler::initialise() {
  return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangModuleMgr>
YangHandler::moduleMgr() const {
  return mModuleMgr;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangPersist>
YangHandler::persistMgr() const {
  return mPersist;
}

//-------------------------------------------------------------------------------------------------------------
void
YangHandler::makePersistent(const std::set<std::string>& paths) {
  mPersist->setPersist(paths);
}

//-------------------------------------------------------------------------------------------------------------
void
YangHandler::makePersistent(const std::string& xpath) {
  mPersist->setPersist(xpath);
}

//-------------------------------------------------------------------------------------------------------------
std::string
YangHandler::leafName(const std::string& xpath) const {
  return XpathUtils::leafName(xpath);
}

//-------------------------------------------------------------------------------------------------------------
unsigned
YangHandler::getParamUint16(
    uint32_t moduleId, const std::string& xpath, bool& ok) {
  ok = false;

  std::shared_ptr<YangParam> param(getParam(moduleId, xpath));
  if (!param)
    return 0;

  std::string error;
  uint16_t val(YangParamUtils::toUint16(param, error));
  if (!error.empty())
    return 0;

  ok = true;
  return val;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<YangParam>
YangHandler::getParam(uint32_t moduleId, const std::string& xpath) {
  std::shared_ptr<YangParam> param;
  YangResult_E result(mModuleMgr->getItem(moduleId, xpath, param));

  if (result != YangResult_E::OK)
    return std::shared_ptr<YangParam>();

  return param;
}

//-------------------------------------------------------------------------------------------------------------
bool
YangHandler::listIndex(
    const std::string& xpath,
    std::string& listName,
    std::string& key,
    std::string& value) const {
  return XpathUtils::listIndex(xpath, listName, key, value);
}

//-------------------------------------------------------------------------------------------------------------
bool
YangHandler::listIndex(
    const std::string& xpath,
    std::string& listName,
    std::string& key,
    int& value) const {
  return XpathUtils::listIndex(xpath, listName, key, value);
}

//-----------------------------------------------------------------------------
bool
YangHandler::listIndexN(
    const std::string& xpath,
    std::string& listName,
    std::string& key,
    std::string& value,
    int n) const {
  return XpathUtils::listIndexN(xpath, listName, key, value, n);
}
