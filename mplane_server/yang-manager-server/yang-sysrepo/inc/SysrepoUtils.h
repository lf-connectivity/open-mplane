/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SysrepoUtils.h
 * \brief     Set of static utilities for sysrepo access
 *
 *
 * \details   Set of static utilities for sysrepo access
 *
 */


#ifndef YANG_SYSREPO_INC_SYSREPOUTILS_H_
#define YANG_SYSREPO_INC_SYSREPOUTILS_H_

#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Sysrepo.hpp>

#include <string>
#include <vector>
#include <memory>
#include <set>
#include <map>

#include "YangMgrServer.h"
#include "YangParam.h"

namespace Mplane {

/*!
 * \class  SysrepoUtils
 * \brief
 * \details
 *
 */
class SysrepoUtils {
public:
 SysrepoUtils() {}
 virtual ~SysrepoUtils() {}

 /**
  * Write a value
  */
 static bool setItemStr(
     std::shared_ptr<YangMgrServer> mgr,
     const std::string& xpath,
     const std::string& value);

 /**
  * Get the items of a list and convert into a map where the key is the list
  * entry key value. Each value of the map is itself a new map, but of leaf /
  * YangParam pairs
  */
 static std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>>
 getKeyParams(std::shared_ptr<YangMgrServer> mgr, const std::string& path);

 /**
  * Get the items of a list and convert into a map where the key is the list
  * entry key value. Each value of the map is itself a new map, but of leaf /
  * value string pairs
  */
 static std::map<std::string, std::map<std::string, std::string>> getKeyValues(
     std::shared_ptr<YangMgrServer> mgr, const std::string& path);

 /**
  * Get the items of a list YangParams and convert into a map with the leaf name
  * as the key and a YangParam as the value
  */
 static std::map<std::string, std::shared_ptr<YangParam>> getParams(
     std::shared_ptr<YangMgrServer> mgr, const std::string& path);

 /**
  * Get the items of a list from the operational datastore and convert into a
  * map where the key is the list entry key value. Each value of the map is
  * itself a new map, but of leaf / YangParam pairs
  */
 static std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>>
 getOperationalKeyParams(
     std::shared_ptr<YangMgrServer> mgr, const std::string& path);

 /**
  * Get the items of a list from the operational datastore and convert into a
  * map where the key is the list entry key value. Each value of the map is
  * itself a new map, but of leaf / value string pairs
  */
 static std::map<std::string, std::map<std::string, std::string>>
 getOperationalKeyValues(
     std::shared_ptr<YangMgrServer> mgr, const std::string& path);

 /**
  * Get the items of a list YangParams from the operational datastore and
  * convert into a map with the leaf name as the key and a YangParam as the
  * value
  */
 static std::map<std::string, std::shared_ptr<YangParam>> getOperationalParams(
     std::shared_ptr<YangMgrServer> mgr, const std::string& path);

 /**
  * Convert the YangParams into a map with the leaf name as the key and a
  * YangParam as the value
  */
 static std::map<std::string, std::shared_ptr<YangParam>> paramsToMap(
     std::shared_ptr<YangParams> params);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * empty string; otherwise converts param into a string and returns it
  */
 static std::string paramVal(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * 0; otherwise converts param into a 8bit unsigned and returns it
  */
 static uint8_t paramValUInt8(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * 0; otherwise converts param into a 16bit unsigned and returns it
  */
 static uint16_t paramValUInt16(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * 0; otherwise converts param into a 16bit unsigned and returns it
  */
 static uint32_t paramValUInt32(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * 0; otherwise converts param into a 64bit unsigned and returns it
  */
 static uint64_t paramValUInt64(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * 0; otherwise converts param into a double and returns it
  */
 static double paramValDecimal64(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Convert YangParams pointer value into a sysrepo Vals pointer
  */
 static std::shared_ptr<sysrepo::Vals> paramsToVals(
     std::shared_ptr<YangParams> params);

 /**
  * Convert sysrepo Vals pointer to YangParams pointer value
  */
 static std::shared_ptr<YangParams> valsToParams(
     std::shared_ptr<sysrepo::Vals> vals);

 /**
  * Update a Vals_Holder from a YangParams
  */
 static bool paramsToValsHolder(
     std::shared_ptr<YangParams> params,
     std::shared_ptr<sysrepo::Vals_Holder> valsHolder);

 /**
  * Debug - display the map of YangParam values
  */
 static void dumpParamsMap(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& title = "");

private:
 /**
  * Get the items of a list and convert into a map where the key is the list
  * entry key value. Each value of the map is itself a new map, but of leaf /
  * YangParam pairs
  */
 static std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>>
 getKeyParams(
     std::shared_ptr<YangMgrServer> mgr,
     const std::string& path,
     uint16_t datastoreId);

 /**
  * Get the items of a list and convert into a map where the key is the list
  * entry key value. Each value of the map is itself a new map, but of leaf /
  * value string pairs
  */
 static std::map<std::string, std::map<std::string, std::string>> getKeyValues(
     std::shared_ptr<YangMgrServer> mgr,
     const std::string& path,
     uint16_t datastoreId);

 /**
  * Get the items of a list YangParams and convert into a map with the leaf name
  * as the key and a YangParam as the value
  */
 static std::map<std::string, std::shared_ptr<YangParam>> getParams(
     std::shared_ptr<YangMgrServer> mgr,
     const std::string& path,
     uint16_t datastoreId);
} ;

}

#endif /* YANG_SYSREPO_INC_SYSREPOUTILS_H_ */
