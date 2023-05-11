/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioDatastoreSysrepo.h
 * \brief     Radio datastore for sysrepo datastores
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef RADIO_DATASTORE_SYSREPO_H_
#define RADIO_DATASTORE_SYSREPO_H_

// *****************************************************************************
// Includes
// *****************************************************************************
#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Sysrepo.hpp>

#include "RadioDatastore.h"

namespace Mplane {

// *****************************************************************************
// sysrepo Radio Datastore driver
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        RadioDatastoreSysrepo
// Description:  sysrepo Radio Datastore class.
// -----------------------------------------------------------------------------
class RadioDatastoreSysrepo : public RadioDatastore
{
public:
 enum class RadDs_E : uint16_t {
   RADIO_DS_RUNNING = 0, // default
   RADIO_DS_OPERATIONAL,
 };

 RadioDatastoreSysrepo();
 ~RadioDatastoreSysrepo();

 /*
  * Initialise datastore
  */
 virtual YangResult_E initialise(void) override;

 /*
  * Activate datastore
  */
 virtual YangResult_E activate(void) override;

 /*
  * Parameter methods
  */
 virtual YangResult_E getItem(
     const std::string& xpath,
     std::shared_ptr<YangParam>& param,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;
 virtual YangResult_E getItems(
     const std::string& xpath,
     std::shared_ptr<YangParams>& params,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;
 virtual YangResult_E getListItems(
     const std::string& listXpath,
     std::vector<std::string>& keyValues,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;
 virtual YangResult_E setItem(
     const std::string& xpath,
     std::shared_ptr<YangParam> param,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;
 virtual YangResult_E setItemStr(
     const std::string& xpath,
     const std::string& value,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;
 virtual YangResult_E setItems(
     const std::string& xpath,
     std::shared_ptr<YangParams> params,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;
 virtual YangResult_E deleteItem(
     const std::string& xpath,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;

 /**
  * Send out a notification with it's parameters
  */
 virtual YangResult_E sendNotification(
     const std::string& xpath,
     std::shared_ptr<YangParams> params,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;

 /*
  * Add callback for read-only (non config) data
  */
 virtual YangResult_E getItemsSubscribe(
     const std::string& moduleName,
     const std::string& path,
     sysrepo::S_Callback callback,
     void* privateData = nullptr,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING);

 /*
  * Add callback for config data change
  */
 virtual YangResult_E itemsChangeSubscribe(
     const std::string& moduleName,
     sysrepo::S_Callback callback,
     const std::string& xpath = "",
     void* privateData = nullptr,
     sr_subscr_flag_t subscribeFlag = SR_SUBSCR_DEFAULT,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING);

 /**
  * Subscribe to RPC callbacks
  */
 virtual YangResult_E rpcSubscribe(
     const std::string& path,
     sysrepo::S_Callback callback,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING);

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
         std::map<std::string, std::string>(),
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;

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
         std::map<std::string, std::string>(),
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;

 /*
  * Create a new list entry, and set it's field values. This version of the
  * overloaded function allows to add a field in the list that may not need a
  * value like a container or a list key element within a list. If this is not a
  * requirement, then better to use the function that contains map of
  * std::string, std::string.
  *
  * xpath is the top-level path to this instance of the list entry.
  * The optional values is a map of name/value pairs. The name is relative to
  * the xpath, and value is the string representation of the value.
  *
  * Example: To set /examples2:uplane/low-level-rx-links[name='rx0cc0']
  *
  * createListEntry("/examples2:uplane/low-level-rx-links[name='rx0cc0']",
  *         std::map<std:string, std::shared_ptr<std::string>>{
  *             { "name", std::make_shared<std::string>("rx0cc0") },
  *             { "processing-element", std::make_shared<std::string>("eth0") },
  *             { "rx-array-carrier", nullptr },
  *             { "low-level-rx-endpoint", nullptr },
  *         }) ;
  */
 virtual YangResult_E createListEntry(
     const std::string& xpath,
     std::map<std::string, std::shared_ptr<std::string>> values,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;

 /*
  * Create a new list entry, and set it's field values. This version of the
  * overloaded function allows to add a field in the list that may not need a
  * value like a container or a list key element within a list. If this is not a
  * requirement, then better to use the function that contains map of
  * std::string, std::string.
  *
  * Example: To set /examples2:uplane/low-level-rx-links[name='rx0cc0']
  *
  * createListEntry("/examples2:uplane/low-level-rx-links", "name", "rx0cc0",
  *         std::map<std:string, std::shared_ptr<std::string>>{
  *             { "name", std::make_shared<std::string>("rx0cc0") },
  *             { "processing-element", std::make_shared<std::string>("eth0") },
  *             { "rx-array-carrier", nullptr },
  *         }) ;
  */
 virtual YangResult_E createListEntry(
     const std::string& xpath,
     const std::string& key,
     const std::string& keyval,
     std::map<std::string, std::shared_ptr<std::string>> values,
     uint16_t datastoreId = (uint16_t)RadDs_E::RADIO_DS_RUNNING) override;

 /*
  * Install module
  */
 virtual YangResult_E installModule(
     const std::string& name,
     const std::string& path,
     const std::string& filename,
     std::vector<std::string> features) override;

 /*
  * Uninstall module
  */
 virtual YangResult_E uninstallModule(const std::string& name) override;

 /*
  * Install module data
  */
 virtual YangResult_E installModuleData(
     const std::string& name,
     const std::string& data,
     const std::string& data_path) override;

 /*
  * Enable module feature
  */
 virtual YangResult_E enableFeature(
     const std::string& name, const std::string& feature) override;

 /*
  * Disable module feature
  */
 virtual YangResult_E disableFeature(
     const std::string& name, const std::string& feature) override;

 /**
  * is the module present *and* implemented in sysrepo?
  */
 virtual bool isModuleInstalled(const std::string& name) const override;

 /*
  * Debug methods
  */
 static std::string typeStr(sr_error_t type);

protected:
 /*
  * Exception handlers
  */
 virtual YangResult_E exceptionHandler(
     sr_error_t errType, const std::string& desc, bool halt = false);
 virtual YangResult_E exceptionHandler(
     const sysrepo::sysrepo_exception& exception,
     const std::string& desc,
     bool halt = false);

 /*
  * sysrepo Parameters
  */
 sysrepo::S_Connection mSrConnection;
 std::vector<sysrepo::S_Session> mSrSessions;

private:
 /*
  * Resets sysrepo connection
  */
 YangResult_E resetConnection(void);

 /*
  * List of subsriptions
  */
 std::vector<sysrepo::S_Subscribe> mSubscriptions;
};

} /* namespace Mplane */

#endif /* RADIO_DATASTORE_SYSREPO_H_ */
