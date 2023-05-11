/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranProcessingElementHandler.cpp
 * \brief     O-RAN processing element module handler
 *
 *
 * \details   O-RAN processing element module handler
 *
 * Defines the mapping between transport flows and arbitrary O-RAN processing
 * elements. A processing element may be then defined for handling connectivity
 * or delay procedures, or defined with a corresponding eaxcid for CU plane
 * operations
 *
 * module: o-ran-processing-element
 *   +--rw processing-elements
 *      +--ro maximum-number-of-transport-flows? uint16
 *      +--rw transport-session-type?            enumeration
 *      +--rw enhanced-uplane-mapping!
 *      |  +--rw uplane-mapping* [up-marking-name]
 *      |     +--rw up-marking-name  string
 *      |     +--rw (up-markings)?
 *      |        +--:(ethernet)  when "(../../transport-session-type =
 * 'ALIASMAC-INTERFACE') or (../../transport-session-type = 'ETH-INTERFACE')";
 *      |        |  +--rw up-cos-name?     leafref:
 * /if:interfaces/if:interface/o-ran-int:class-of-service/o-ran-int:enhanced-uplane-markings/o-ran-int:up-marking-name
 *      |        +--:(ipv4)  when "(../../transport-session-type =
 * 'UDPIP-INTERFACE')"; |        |  +--rw upv4-dscp-name?  leafref:
 * /if:interfaces/if:interface/ip:ipv4/o-ran-int:diffserv-markings/o-ran-int:enhanced-uplane-markings/o-ran-int:up-marking-name
 *      |        +--:(ipv6)  when "(../../transport-session-type =
 * 'UDPIP-INTERFACE')"; |           +--rw upv6-dscp-name?  leafref:
 * /if:interfaces/if:interface/ip:ipv6/o-ran-int:diffserv-markings/o-ran-int:enhanced-uplane-markings/o-ran-int:up-marking-name
 *      +--rw ru-elements* [name]
 *         +--rw name            string
 *         +--rw transport-flow
 *            +--rw interface-name? leafref: /if:interfaces/if:interface/if:name
 *            +--rw aliasmac-flow {o-ran-int:ALIASMAC-BASED-CU-PLANE}?  when
 * "../../../transport-session-type = 'ALIASMAC-INTERFACE'"; |  +--rw
 * ru-aliasmac-address  leafref: /if:interfaces/if:interface[if:name =
 * current()/../../interface-name]/o-ran-int:alias-macs |  +--rw vlan-id?
 * leafref: /if:interfaces/if:interface[if:name =
 * current()/../../interface-name]/o-ran-int:vlan-id |  +--rw o-du-mac-address
 * yang:mac-address
 *            +--rw eth-flow  when "../../../transport-session-type =
 * 'ETH-INTERFACE'"; |  +--rw ru-mac-address    leafref:
 * /if:interfaces/if:interface[if:name =
 * current()/../../interface-name]/o-ran-int:mac-address |  +--rw vlan-id
 * leafref: /if:interfaces/if:interface[if:name =
 * current()/../../interface-name]/o-ran-int:vlan-id |  +--rw o-du-mac-address
 * yang:mac-address
 *            +--rw udpip-flow  when "(../../transport-session-type =
 * 'UDPIP-INTERFACE')";
 *               +--rw (address)
 *               |  +--:(ru-ipv4-address)-elk
 *               |  |  +--rw ru-ipv4-address?         leafref:
 * /if:interfaces/if:interface[if:name =
 * current()/../../interface-name]/ip:ipv4/ip:address/ip:ip |
 * +--:(ru-ipv6-address) |     +--rw ru-ipv6-address?         leafref:
 * /if:interfaces/if:interface[if:name =
 * current()/../../interface-name]/ip:ipv6/ip:address/ip:ip
 *               +--rw o-du-ip-address          inet:ip-address
 *               +--rw ru-ephemeral-udp-port    inet:port-number
 *               +--rw o-du-ephemeral-udp-port  inet:port-number
 *               +--rw ecpri-destination-udp    inet:port-number
 */

//===========================================================================
// INCLUDE
//===========================================================================
#include <iostream>

#include "ILeafContainer.h"
#include "stringfunc.hpp"

#include "OranProcessingElementHandler.h"
#include "RadioDatastoreSysrepo.h"
#include "SysrepoUtils.h"

using namespace Mplane;

//===========================================================================
// LOCAL
//===========================================================================

const std::string moduleName = "o-ran-processing-element";
const std::string topContainerName = "processing-elements";

const std::string modInt = "ietf-interfaces";
const std::string modORanInt = "o-ran-interfaces";

#define DEFAULT_TRANSPORT_SESSION_TYPE "ETH-INTERFACE"

//===========================================================================
// PUBLIC
//===========================================================================

//---------------------------------------------------------------------------
OranProcessingElementHandler::OranProcessingElementHandler(
    std::shared_ptr<IYangModuleMgr> moduleMgr)
    : YangHandlerSysrepo(moduleName, moduleMgr, "OranProcessingElementHandler"),
      mCallback(
          std::make_shared<SysrepoGetitemsCallback>(path(topContainerName))),
      mRuElements(),
      mPathParent(moduleName, topContainerName),
      mConfig(IYangConfig::getConfigSingleton()) {}

//---------------------------------------------------------------------------
OranProcessingElementHandler::~OranProcessingElementHandler() {}

//---------------------------------------------------------------------------
bool
OranProcessingElementHandler::initialise() {
  // ------------------------------------------------------------------------
  // daisychain the initialisations
  // ------------------------------------------------------------------------
  if (!this->YangHandlerSysrepo::initialise())
    return false;

  // ------------------------------------------------------------------------
  // Initialise state data
  // ------------------------------------------------------------------------

  // Container for 'processing-elements' state data (ro)
  std::shared_ptr<ILeafContainer> dataSte(mCallback);

  //   +--ro maximum-number-of-transport-flows? uint16
  dataSte->addLeafFromConfig(
      "maximum-number-of-transport-flows",
      mConfig,
      "module-o-ran-processing-element/container-processing-elements/"
      "leaf-maximum-number-of-transport-flows");

  std::string transportSessionType = mConfig->getValue(
      "module-o-ran-processing-element/container-processing-elements/"
      "leaf-transport-session-type");

  //   +--rw transport-session-type?            enumeration
  // TODO: handle transportSessionType != ETH-INTERFACE
  if (transportSessionType.empty()) {
    transportSessionType = DEFAULT_TRANSPORT_SESSION_TYPE;
  }
  YangPath transportPath(mPathParent);
  transportPath.add("transport-session-type");
  createItemStr(transportPath.pathRoot(), transportSessionType);

  // TODO: enhanced-uplane-mapping

  auto numRuElements = mConfig->getNumOfListEntries(
      "module-o-ran-processing-element/container-processing-elements/"
      "list-ru-elements");

  for (int i = 0; i < numRuElements; i++) {
    addRuProcessingElementConfig(i, transportSessionType);
  }

  // ------------------------------------------------------------------------
  // Register callback for each top level container
  // ------------------------------------------------------------------------
  getItemsSubscribe(mCallback->path(), mCallback);
  changeSubscribe();

  return true;
}

//---------------------------------------------------------------------------
void
OranProcessingElementHandler::addRuProcessingElementConfig(
    int idx, const std::string& transportSessionType) {
  std::string baseConfigPath =
      std::string(
          "module-o-ran-processing-element/container-processing-elements/"
          "list-ru-elements[") +
      std::to_string(idx) + "]";

  std::string name = mConfig->getValue(baseConfigPath + "/leaf-name");

  std::map<std::string, std::string> dataCfg;

  std::pair<std::string, std::string> keyName("name", name);
  YangPath pathElement("ru-elements", keyName);

  //      +--rw transport-flow
  YangPath pathTransportFlow(pathElement);
  pathTransportFlow.add("transport-flow");
  std::string transFlowPath = baseConfigPath + "/container-transport-flow";

  //         +--rw interface-name? leafref: /if:interfaces/if:interface/if:name
  std::string interfaceName =
      mConfig->getValue(transFlowPath + "/leaf-interface-name");
  if (!interfaceName.empty()) {
    dataCfg[pathTransportFlow.pathParam() + "interface-name"] = interfaceName;
  }

  //         +--rw eth-flow  when "../../../transport-session-type =
  //         'ETH-INTERFACE'";
  YangPath pathEthFlow(pathTransportFlow);
  pathEthFlow.add("eth-flow");
  std::string ethFlowPath = transFlowPath + "/container-eth-flow";

  //         |  +--rw ru-mac-address    leafref:
  //         /if:interfaces/if:interface[if:name =
  //         current()/../../interface-name]/o-ran-int:mac-address
  std::string ruMac = mConfig->getValue(ethFlowPath + "/leaf-ru-mac-address");
  dataCfg[pathEthFlow.pathParam() + "ru-mac-address"] = ruMac;

  //         |  +--rw vlan-id           leafref:
  //         /if:interfaces/if:interface[if:name =
  //         current()/../../interface-name]/o-ran-int:vlan-id
  std::string vlanId = mConfig->getValue(ethFlowPath + "/leaf-vlan-id");
  dataCfg[pathEthFlow.pathParam() + "vlan-id"] = vlanId;

  //         |  +--rw o-du-mac-address  yang:mac-address
  std::string oduMac =
      mConfig->getValue(ethFlowPath + "/leaf-o-du-mac-address");
  dataCfg[pathEthFlow.pathParam() + "o-du-mac-address"] = oduMac;

  // TODO: handle transportSessionType != ETH-INTERFACE

  // store config data in datastore
  createListEntry(mPathParent.pathRoot(), dataCfg);
  updateRuElement(name, interfaceName, ruMac, vlanId, oduMac);
}

void
OranProcessingElementHandler::updateRuElement(
    const std::string& name,
    const std::string& interfaceName,
    const std::string& ruMac,
    const std::string& vlanId,
    const std::string& oduMac) {

  auto entry(mRuElements.find(name));
  if (entry == mRuElements.end()) {
    std::shared_ptr ruElement(std::make_shared<ru_elements_t>());

    ruElement->name = std::make_shared<std::string>(name)->c_str();
    ruElement->t_flow.interface_name =
        std::make_shared<std::string>(interfaceName)->c_str();
    ruElement->t_flow.e_flow.ru_mac_address =
        std::make_shared<std::string>(ruMac)->c_str();
    ruElement->t_flow.e_flow.vlan_id = std::stoi(vlanId);
    ruElement->t_flow.e_flow.o_du_mac_address =
        std::make_shared<std::string>(oduMac)->c_str();

    mRuElements[name] = ruElement;
  } else {
    if (!interfaceName.empty()) {
      entry->second->t_flow.interface_name =
          std::make_shared<std::string>(interfaceName)->c_str();
    }
    if (!ruMac.empty()) {
      entry->second->t_flow.e_flow.ru_mac_address =
          std::make_shared<std::string>(ruMac)->c_str();
    }
    if (!vlanId.empty()) {
      entry->second->t_flow.e_flow.vlan_id = std::stoi(vlanId);
    }
    if (!oduMac.empty()) {
      entry->second->t_flow.e_flow.o_du_mac_address =
          std::make_shared<std::string>(oduMac)->c_str();
    }
  }
  halmplane_update_ru_element(mRuElements[name].get());
}

//===========================================================================
// PROTECTED
//===========================================================================

//---------------------------------------------------------------------------
void
OranProcessingElementHandler::valueChange(
    const std::string& xpath,
    std::shared_ptr<YangParam> oldValue,
    std::shared_ptr<YangParam> newValue) {
  logDebugVerbose(
      "OranProcessingElementHandler::valueChange() - %s", xpath.c_str());

  std::string error;

  std::string listName;
  std::string key;
  std::string index;
  std::string value;
  std::string leaf;

  if (oldValue && !newValue) {
    // value deleted
    value = "";
    listIndex(oldValue->name(), listName, key, index);
    leaf = leafName(oldValue->name());
    logDebugVerbose(
        "OranProcessingElementHandler::valueChange() - %s",
        oldValue->name().c_str());
  } else if (newValue) {
    value = YangParamUtils::toString(newValue, error);
    listIndex(newValue->name(), listName, key, index);
    leaf = leafName(newValue->name());
    logDebugVerbose(
        "OranProcessingElementHandler::valueChange() - %s",
        newValue->name().c_str());
  }

  if (listName == "ru-elements") {
    if (leaf == "interface-name") {
      updateRuElement(index, value, "", "", "");
    } else if (leaf == "ru-mac-address") {
      updateRuElement(index, "", value, "", "");
    } else if (leaf == "vlan-id") {
      updateRuElement(index, "", "", value, "");
    } else if (leaf == "o-du-mac-address") {
      updateRuElement(index, "", "", "", value);
    }
  }
}
