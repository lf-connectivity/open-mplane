/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRadioDataStore.h
 * \brief     Virtual interface to radio data store
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef VYMS_INC_IRADIODATASTORE_H_
#define VYMS_INC_IRADIODATASTORE_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <map>

#include "IYangModule.h"
#include "YangTypes.h"
#include "YangParam.h"

namespace Mplane {

typedef struct
{
  std::string module;
} RadDsEvt_t;

/*!
 * \class  IRadioDataStore
 * \brief
 * \details
 *
 */
class IRadioDataStore {
public:
 enum class State_E {
   UNINITIALISED, // Uninitialised
   INITIALISED, // Initialised
   CONFIGURING, // Configuring datastore (Module install with startup data)
   ACTIVE, // Datastore is active (fully operational)
   SETUP_FAILURE, // Setup failure
 };

#define RAD_DS_ID_DEFAULT  0

 IRadioDataStore() {}
 virtual ~IRadioDataStore() {}

 /*
  * Initialise datastore
  */
 virtual YangResult_E initialise(void) = 0;

 /*
  * Get current state
  */
 virtual State_E getState(void) const = 0;

 /*
  * Validate current state
  */
 virtual bool isState(State_E state) const = 0;

 /*
  * Activate datastore
  */
 virtual YangResult_E activate(void) = 0;

 /*
  * Parameter methods
  */
 virtual YangResult_E getItem(
     const std::string& xpath,
     std::shared_ptr<YangParam>& param,
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;
 virtual YangResult_E getItems(
     const std::string& xpath,
     std::shared_ptr<YangParams>& params,
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;
 virtual YangResult_E getListItems(
     const std::string& listXpath,
     std::vector<std::string>& keyValues,
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;
 virtual YangResult_E setItem(
     const std::string& xpath,
     std::shared_ptr<YangParam> param,
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;
 virtual YangResult_E setItemStr(
     const std::string& xpath,
     const std::string& value,
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;
 virtual YangResult_E setItems(
     const std::string& xpath,
     std::shared_ptr<YangParams> params,
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;
 virtual YangResult_E deleteItem(
     const std::string& xpath, uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;

 /**
  * Send out a notification with it's parameters
  */
 virtual YangResult_E sendNotification(
     const std::string& xpath,
     std::shared_ptr<YangParams> params,
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;

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
     std::map<std::string, std::string> values,
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;

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
     std::map<std::string, std::string> values,
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;

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
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;

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
     uint16_t datastoreId = RAD_DS_ID_DEFAULT) = 0;

 /*
  * Install module
  */
 virtual YangResult_E installModule(
     const std::string& name,
     const std::string& path,
     const std::string& filename,
     std::vector<std::string> features) = 0;

 /*
  * Uninstall module
  */
 virtual YangResult_E uninstallModule(const std::string& name) = 0;

 /*
  * Enable module data
  */
 virtual YangResult_E installModuleData(
     const std::string& name,
     const std::string& data,
     const std::string& data_path) = 0;

 /*
  * Enable module feature
  */
 virtual YangResult_E enableFeature(
     const std::string& name, const std::string& feature) = 0;

 /*
  * Disable module feature
  */
 virtual YangResult_E disableFeature(
     const std::string& name, const std::string& feature) = 0;

 /*
  * Check if module is installed
  */
 virtual bool isModuleInstalled(const std::string& name) const = 0;

 /*
  * Get a list of installed modules
  */
 virtual std::vector<std::string> getListOfInstalledModules(void) const = 0;

 /*
  * Get next event
  */
 virtual bool getNextEvent(RadDsEvt_t& event) = 0;

 /*
  * Debug
  */
 virtual YangResult_E dumpInstalledModules(void) = 0;
} ;

}

#endif /* VYMS_INC_IRADIODATASTORE_H_ */
