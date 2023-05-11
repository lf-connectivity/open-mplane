/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangHandlerSysrepoUnlogged.h
 * \brief     YangHandler with sysrepo connections
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_SYSREPO_INC_YANGHANDLERSYSREPOUNLOGGED_H_
#define YANG_SYSREPO_INC_YANGHANDLERSYSREPOUNLOGGED_H_

#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Sysrepo.hpp>

#include <string>
#include <vector>
#include <memory>
#include <set>
#include <map>
#include <functional>

#include "YangParam.h"
#include "YangHandler.h"
#include "YangParamUtils.h"
#include "YangUtils.h"

#include "ISendNotification.h"
#include "YangHandlerSysrepo/HandlerCallback.h"
#include "YangHandlerSysrepo/RpcCallback.h"

namespace Mplane {

/*!
 * \class  YangHandlerSysrepoUnlogged
 * \brief
 * \details
 *
 */
class YangHandlerSysrepoUnlogged : public YangHandler, public ISendNotification
{
public:
 YangHandlerSysrepoUnlogged(
     const std::string& moduleName, std::shared_ptr<IYangModuleMgr> moduleMgr);
 virtual ~YangHandlerSysrepoUnlogged();

 /**
  * Run the initialisation of the handler (can only be done once the rest of the
  * YANG framework is up)
  */
 virtual bool initialise() override;

 /**
  * Send out a notification with it's parameters
  */
 YangResult_E sendNotification(
     const std::string& xpath,
     std::shared_ptr<YangParams> params) final override;

 /**
  * Called to display info. A loggable derived class will override this with a
  * call to eventInfo()
  */
 virtual void logInfo(const std::string& info);

 // PROTECTED HOOKS
protected:
 /*!
  \brief Module change hook - called by module_change() method with filtered
  events \param xpath Contains full path of the element for which valueChange
  callback is called. Eg /o-ran-sync:sync/ptp-config/ptp-profile. \param
  oldValue The original value of the element (could be null) \param newValue The
  new value of the element (could be null)
  */
 virtual void valueChange(
     const std::string& xpath,
     std::shared_ptr<YangParam> oldValue,
     std::shared_ptr<YangParam> newValue);

 /*!
  \brief Module change hook - called by module_change() method with filtered
  events \param xpath Contains full path of the element for which paramDelete
  callback is called. Eg /o-ran-sync:sync/ptp-config/ptp-profile. \param
  oldValue The original value of the element
  */
 virtual void paramDelete(
     const std::string& xpath, std::shared_ptr<YangParam> oldValue);

 /*!
  \brief Module change hook - called by module_change() method to have this
  class validate the proposed values changes \param params A YangParams pointer
  containing all of the changed values and another containing deleted values
  \return SR_ERR_OK if the values are validated; SR_ERR_VALIDATION_FAILED on
  validation failure. Can return any other sysrepo error status as necessary.
  */
 virtual int validate(
     std::shared_ptr<YangParams> params,
     std::shared_ptr<YangParams> deletedParams);

 /**
  * Called to display info. A loggable derived class will override this with a
  * call to Loggable::getGroupName()
  */
 virtual std::string groupName() const;

 // PROTECTED
protected:
 /**
  * Get the full path of the modules specified path
  */
 virtual std::string path(const std::string& path) const;

 /**
  * Subscribe to module changes - callback only called when all changes are
  * complete
  */
 virtual void changeSubscribe(const std::string& xpath = "");

 /**
  * Add this/these paths to a list of paths that will refuse any changes,
  * effectively making the values read-only
  */
 virtual void makeReadOnly(const std::set<std::string>& xpath);

 /**
  * Add this path to a list of paths that will refuse any changes, effectively
  * making the values read-only
  */
 virtual void makeReadOnly(const std::string& xpath);

 /**
  * Remove this path from a list of read-only paths
  */
 virtual void removeReadOnly(const std::string& xpath);

 /**
  * Subscribe to get items
  */
 virtual void getItemsSubscribe(
     const std::string& xpath, std::shared_ptr<sysrepo::Callback> callback);

 /*
  * Create a string item
  *
  * xpath is the top-level path to this instance of the item.
  *
  */
 YangResult_E createItemStr(const std::string& xpath, const std::string& value);

 /*
  * Create a new list entry, and optionally set it's field values.
  *
  * xpath is the top-level path to this instance of the list entry.
  * The optional values is a map of name/value pairs. The name is relative to
  * the xpath, and value is the string representation of the value.
  *
  * Example: To set /examples2:uplane/low-level-rx-links[name='rx0cc0']
  *
  * createListEntry("/examples2:uplane/low-level-rx-links[name='rx0cc0']",
  *         std::map<std:string, std::string>{
  *             { "name", "rx0cc0" },
  *             { "processing-element", "eth0" },
  *             { "rx-array-carrier", "cc0" },
  *             { "low-level-rx-endpoint", "rx0cc0" },
  *         }) ;
  */
 virtual YangResult_E createListEntry(
     const std::string& xpath,
     std::map<std::string, std::string> values =
         std::map<std::string, std::string>());

 /*
  * Register a callback for an RPC command in this module
  */
 virtual void registerRpc(const std::string& path, RpcCallback::RpcFunc func);

 /*
  * Create a new list entry, and optionally set it's field values. Overloaded
  * method where the key is specifically set so doesn't need to be part of the
  * xpath or the values.
  *
  * Example: To set /examples2:uplane/low-level-rx-links[name='rx0cc0']
  *
  * createListEntry("/examples2:uplane/low-level-rx-links", "name", "rx0cc0",
  *         std::map<std:string, std::string>{
  *             { "processing-element", "eth0" },
  *             { "rx-array-carrier", "cc0" },
  *             { "low-level-rx-endpoint", "rx0cc0" },
  *         }) ;
  */
 virtual YangResult_E createListEntry(
     const std::string& xpath,
     const std::string& key,
     const std::string& keyval,
     std::map<std::string, std::string> values =
         std::map<std::string, std::string>());

 /**
  * Get the items of a list and convert into a map where the key is the list
  * entry key value. Each value of the map is itself a new map, but of leaf /
  * YangParam pairs
  */
 virtual std::
     map<std::string, std::map<std::string, std::shared_ptr<YangParam>>>
     getKeyParams(const std::string& path);

 /**
  * Get the items of a list and convert into a map where the key is the list
  * entry key value. Each value of the map is itself a new map, but of leaf /
  * value string pairs
  */
 virtual std::map<std::string, std::map<std::string, std::string>> getKeyValues(
     const std::string& path);

 /**
  * Get the items of a list YangParams and convert into a map with the leaf name
  * as the key and a YangParam as the value
  */
 virtual std::map<std::string, std::shared_ptr<YangParam>> getParams(
     const std::string& path);

 /**
  * Get the items of a list and convert into a map where the key is the list
  * entry key value. Each value of the map is itself a new map, but of leaf /
  * YangParam pairs
  */
 virtual std::
     map<std::string, std::map<std::string, std::shared_ptr<YangParam>>>
     getOperationalKeyParams(const std::string& path);

 /**
  * Get the items of a list and convert into a map where the key is the list
  * entry key value. Each value of the map is itself a new map, but of leaf /
  * value string pairs
  */
 virtual std::map<std::string, std::map<std::string, std::string>>
 getOperationalKeyValues(const std::string& path);

 /**
  * Get the items of a list YangParams and convert into a map with the leaf name
  * as the key and a YangParam as the value
  */
 virtual std::map<std::string, std::shared_ptr<YangParam>> getOperationalParams(
     const std::string& path);

 /**
  * Convert the YangParams into a map with the leaf name as the key and a
  * YangParam as the value
  */
 virtual std::map<std::string, std::shared_ptr<YangParam>> paramsToMap(
     std::shared_ptr<YangParams> params) const;

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * empty string; otherwise converts param into a string and returns it
  */
 virtual std::string paramVal(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * 0; otherwise converts param into a 8bit unsigned and returns it
  */
 virtual uint8_t paramValUInt8(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * 0; otherwise converts param into a 16bit unsigned and returns it
  */
 virtual uint16_t paramValUInt16(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * 0; otherwise converts param into a 16bit unsigned and returns it
  */
 virtual uint32_t paramValUInt32(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * 0; otherwise converts param into a 64bit unsigned and returns it
  */
 virtual uint64_t paramValUInt64(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

 /**
  * Get the YangParam from values based on the given key. If not found returns
  * 0; otherwise converts param into a double and returns it
  */
 virtual double paramValDecimal64(
     const std::map<std::string, std::shared_ptr<YangParam>>& values,
     const std::string& key);

private:
 void setVal(std::shared_ptr<sysrepo::Val> value);

private:
 friend class HandlerCallback;
 std::shared_ptr<HandlerCallback> mHandlerCallback;
 std::set<std::string> mReadOnlyPaths;
 std::vector<std::shared_ptr<RpcCallback>> mRpcCallbacks;
} ;

}

/**
 * Register a local method as an RPC callback function
 */
#define REGISTER_RPC(str, mthd)  \
  registerRpc(                   \
      str,                       \
      std::bind(                 \
          &mthd,                 \
          this,                  \
          std::placeholders::_1, \
          std::placeholders::_2, \
          std::placeholders::_3, \
          std::placeholders::_4))

#endif /* YANG_SYSREPO_INC_YANGHANDLERSYSREPOUNLOGGED_H_ */
