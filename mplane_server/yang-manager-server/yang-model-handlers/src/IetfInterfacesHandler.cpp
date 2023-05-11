/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IetfInterfacesHandler.cpp
 * \brief     IETF interfaces module handler
 *
 *
 * \details   IETF interfaces module handler
 *
 * Collection of YANG definitions for managing network interfaces.
 *
 * module: ietf-interfaces
 *   +--rw interfaces
 *      +--rw interface* [name]
 *         +--rw name                        string
 *         +--rw description?                string
 *         +--rw type                        identityref
 *         +--rw enabled?                    boolean
 *         +--rw link-up-down-trap-enable?   enumeration {if-mib}?
 *         +--ro admin-status                enumeration {if-mib}?
 *         +--ro oper-status                 enumeration
 *         +--ro last-change?                yang:date-and-time
 *         +--ro if-index                    int32 {if-mib}?
 *         +--ro phys-address?               yang:phys-address
 *         +--ro higher-layer-if*            interface-ref  leafref:
 * /if:interfaces/if:interface/if:name
 *         +--ro lower-layer-if*             interface-ref  leafref:
 * /if:interfaces/if:interface/if:name
 *         +--ro speed?                      yang:gauge64
 *         +--ro statistics
 *         |  +--ro discontinuity-time  yang:date-and-time
 *         |  +--ro in-octets?          yang:counter64
 *         |  +--ro in-unicast-pkts?    yang:counter64
 *         |  +--ro in-broadcast-pkts?  yang:counter64
 *         |  +--ro in-multicast-pkts?  yang:counter64
 *         |  +--ro in-discards?        yang:counter32
 *         |  +--ro in-errors?          yang:counter32
 *         |  +--ro in-unknown-protos?  yang:counter32
 *         |  +--ro out-octets?         yang:counter64
 *         |  +--ro out-unicast-pkts?   yang:counter64
 *         |  +--ro out-broadcast-pkts? yang:counter64
 *         |  +--ro out-multicast-pkts? yang:counter64
 *         |  +--ro out-discards?       yang:counter32
 *         |  +--ro out-errors?         yang:counter32
 *         +--rw ip:ipv4!
 *         |  +--rw ip:enabled?                  boolean
 *         |  +--rw ip:forwarding?               boolean
 *         |  +--rw ip:mtu?                      uint16
 *         |  +--rw ip:address* [ip]
 *         |  |  +--rw ip:ip             inet:ipv4-address-no-zone
 *         |  |  +--rw (subnet)
 *         |  |  |  +--:(prefix-length)
 *         |  |  |  |  +--rw ip:prefix-length? uint8
 *         |  |  |  +--:(netmask)
 *         |  |  |     +--rw ip:netmask?       yang:dotted-quad
 * {ipv4-non-contiguous-netmasks}? |  |  +--ro ip:origin? ip-address-origin |
 * +--rw ip:neighbor* [ip] |  |  +--rw ip:ip inet:ipv4-address-no-zone |  |
 * +--rw ip:link-layer-address  yang:phys-address |  |  +--ro ip:origin?
 * neighbor-origin |  +--rw o-ran-int:m-plane-marking?   inet:dscp |  +--rw
 * o-ran-int:diffserv-markings {UDPIP-BASED-CU-PLANE}? |     +--rw
 * o-ran-int:u-plane-marking?          inet:dscp |     +--rw
 * o-ran-int:c-plane-marking?          inet:dscp |     +--rw
 * o-ran-int:s-plane-marking?          inet:dscp |     +--rw
 * o-ran-int:other-marking?            inet:dscp |     +--rw
 * o-ran-int:enhanced-uplane-markings* [up-marking-name] |        +--rw
 * o-ran-int:up-marking-name   string |        +--rw o-ran-int:enhanced-marking?
 * inet:dscp
 *         +--rw ip:ipv6!
 *         |  +--rw ip:enabled?                   boolean
 *         |  +--rw ip:forwarding?                boolean
 *         |  +--rw ip:mtu?                       uint32
 *         |  +--rw ip:address* [ip]
 *         |  |  +--rw ip:ip             inet:ipv6-address-no-zone
 *         |  |  +--rw ip:prefix-length  uint8
 *         |  |  +--ro ip:origin?        ip-address-origin
 *         |  |  +--ro ip:status?        enumeration
 *         |  +--rw ip:neighbor* [ip]
 *         |  |  +--rw ip:ip                  inet:ipv6-address-no-zone
 *         |  |  +--rw ip:link-layer-address  yang:phys-address
 *         |  |  +--ro ip:origin?             neighbor-origin
 *         |  |  +--ro ip:is-router?          empty
 *         |  |  +--ro ip:state?              enumeration
 *         |  +--rw ip:dup-addr-detect-transmits? uint32
 *         |  +--rw ip:autoconf
 *         |  |  +--rw ip:create-global-addresses?      boolean
 *         |  |  +--rw ip:create-temporary-addresses?   boolean
 * {ipv6-privacy-autoconf}? |  |  +--rw ip:temporary-valid-lifetime?     uint32
 * {ipv6-privacy-autoconf}? |  |  +--rw ip:temporary-preferred-lifetime? uint32
 * {ipv6-privacy-autoconf}? |  +--rw o-ran-int:m-plane-marking?    inet:dscp |
 * +--rw o-ran-int:diffserv-markings {UDPIP-BASED-CU-PLANE}? |     +--rw
 * o-ran-int:u-plane-marking?          inet:dscp |     +--rw
 * o-ran-int:c-plane-marking?          inet:dscp |     +--rw
 * o-ran-int:s-plane-marking?          inet:dscp |     +--rw
 * o-ran-int:other-marking?            inet:dscp |     +--rw
 * o-ran-int:enhanced-uplane-markings* [up-marking-name] |        +--rw
 * o-ran-int:up-marking-name   string |        +--rw o-ran-int:enhanced-marking?
 * inet:dscp
 *         +--rw o-ran-int:l2-mtu?           uint16
 *         +--rw o-ran-int:vlan-tagging?     boolean
 *         +--rw o-ran-int:class-of-service
 *         |  +--rw o-ran-int:u-plane-marking?          pcp
 *         |  +--rw o-ran-int:c-plane-marking?          pcp
 *         |  +--rw o-ran-int:m-plane-marking?          pcp
 *         |  +--rw o-ran-int:s-plane-marking?          pcp
 *         |  +--rw o-ran-int:other-marking?            pcp
 *         |  +--rw o-ran-int:enhanced-uplane-markings* [up-marking-name]
 *         |     +--rw o-ran-int:up-marking-name   string
 *         |     +--rw o-ran-int:enhanced-marking? pcp
 *         +--rw o-ran-int:base-interface?   if:interface-ref  leafref:
 * /if:interfaces/if:interface/if:name
 *         +--rw o-ran-int:vlan-id?          uint16
 *         +--ro o-ran-int:last-cleared?     yang:date-and-time
 *         +--rw o-ran-int:alias-macs*       yang:mac-address
 * {ALIASMAC-BASED-CU-PLANE}?
 *         +--rw o-ran-int:mac-address?      yang:mac-address
 *         +--rw o-ran-int:port-reference
 *            +--rw o-ran-int:port-name?   leafref  leafref:
 * /hw:hardware/component/name
 *            +--rw o-ran-int:port-number? uint8
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <unistd.h>

#include "IAppOptions.h"
#include "ILeafContainer.h"
#include "stringfunc.hpp"

#include "YangMgrServer.h"

#include "IetfInterfacesHandler.h"
#include "RadioDatastoreSysrepo.h"

using namespace Mplane;

//=============================================================================================================
// DEFINITIONS
//=============================================================================================================

//=============================================================================================================
// LOCAL
//=============================================================================================================
UINT32 IetfInterfacesHandler::mNumInterfaces = 0;

const std::string moduleName = "ietf-interfaces";
const std::string topContainerName = "interfaces";

const std::string modIp = "ietf-ip";
const std::string modORanInt = "o-ran-interfaces";

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
IetfInterfacesHandler::IetfInterfacesHandler(
    std::shared_ptr<IYangModuleMgr> moduleMgr)
    : YangHandlerSysrepo(moduleName, moduleMgr, "IetfInterfacesHandler"),
      mCallback(
          std::make_shared<SysrepoGetitemsCallback>(path(topContainerName))),
      mInterfaces(),
      mPathParent(moduleName, topContainerName),
      mConfig(IYangConfig::getConfigSingleton()) {}

//-------------------------------------------------------------------------------------------------------------
IetfInterfacesHandler::~IetfInterfacesHandler() {}

//-------------------------------------------------------------------------------------------------------------
bool
IetfInterfacesHandler::initialise() {
  // ------------------------------------------------------------------------
  // daisychain the initialisations
  // ------------------------------------------------------------------------
  if (!this->YangHandlerSysrepo::initialise())
    return false;

  // ------------------------------------------------------------------------
  // Initialise IETF interface module in sysrepo
  // ------------------------------------------------------------------------
  // +--rw interfaces
  std::shared_ptr<ILeafContainer> dataSte(
      mCallback); // Container for 'interfaces' state data (ro)

  auto numInterfaces = mConfig->getNumOfListEntries(
      "module-ietf-interfaces/container-interfaces/list-interface");

  // Add an interface entry for each interface
  for (int i = 0; i < numInterfaces; i++) {
    std::string name = mConfig->getValue(
        std::string(
            "module-ietf-interfaces/container-interfaces/list-interface[") +
        std::to_string(i) + "]/leaf-name");
    // Create callback to handle IETF interface module state data
    createInterfaceListEntry(dataSte, i);
    // Add configuration data for physical interface
    addInterface(i);
    halmplane_interface_update(mInterfaces[name].get());
  }

  // ------------------------------------------------------------------------
  // Register callback for each top level container
  // ------------------------------------------------------------------------
  getItemsSubscribe(mCallback->path(), mCallback);
  changeSubscribe();

  return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
IetfInterfacesHandler::valueChange(
    const std::string& xpath,
    std::shared_ptr<YangParam> oldValue,
    std::shared_ptr<YangParam> newValue) {
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
        "IetfInterfacesHandler::valueChange() - %s", oldValue->name().c_str());
  } else if (newValue) {
    value = YangParamUtils::toString(newValue, error);
    listIndex(newValue->name(), listName, key, index);
    leaf = leafName(newValue->name());
    logDebugVerbose(
        "IetfInterfacesHandler::valueChange() - %s", newValue->name().c_str());
  }

  if (listName == "interface") {
    if (leaf == "description") {
      halmplane_interface_update_description(index.c_str(), value.c_str());
    } else if (leaf == "type") {
      halmplane_interface_update_type(index.c_str(), value.c_str());
    } else if (leaf == "enabled") {
      halmplane_interface_update_enabled(index.c_str(), value == "true");
    }
    // leaf names that originate from augments contain prefixes in this parsing
    else if (leaf.find("l2-mtu") != std::string::npos) {
      halmplane_interface_update_l2_mtu(index.c_str(), std::stoi(value));
    } else if (leaf.find("vlan-tagging") != std::string::npos) {
      halmplane_interface_update_vlan_tagging(index.c_str(), value == "true");
    } else if (leaf.find("base-interface") != std::string::npos) {
      halmplane_interface_update_base_interface(index.c_str(), value.c_str());
    } else if (leaf.find("vlan-id") != std::string::npos) {
      halmplane_interface_update_vlan_id(index.c_str(), std::stoi(value));
    } else if (leaf.find("mac-address") != std::string::npos) {
      halmplane_interface_update_mac_address(index.c_str(), value.c_str());
    }
    // TODO: cos markings
  }
}

//=============================================================================================================
// PRIVATE - State data
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
IetfInterfacesHandler::createInterfaceListEntry(
    std::shared_ptr<ILeafContainer> dataSte, int idx) {
  std::string baseConfigPath =
      std::string(
          "module-ietf-interfaces/container-interfaces/list-interface[") +
      std::to_string(idx) + "]";

  // +--rw interface* [name]
  //    +--rw name                        string
  //    +--ro oper-status                 enumeration
  //    +--ro speed?                      yang:gauge64

  std::shared_ptr<ILeafContainer> dataSteIf = dataSte->addContainerList(
      "interface"); // interface container for state data (ro)
  std::vector<std::string> interfaceLeaves = {"name", "oper-status", "speed"};
  dataSteIf->addLeavesFromConfig(interfaceLeaves, mConfig, baseConfigPath);

  // TODO: create the rest of the ro data leaves -- see fb-oru ZCU111
  // implementation for reference
}

//=============================================================================================================
// PRIVATE - Configuration data
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
IetfInterfacesHandler::addInterface(int idx) {
  std::string baseConfigPath =
      std::string(
          "module-ietf-interfaces/container-interfaces/list-interface[") +
      std::to_string(idx) + "]";

  std::shared_ptr interface(std::make_shared<interface_t>());
  // defaults
  interface->enabled = true;
  interface->vlanTagging = true;
  interface->l2Mtu = 1500;

  // Current timestamp
  time_t rawtime;
  time(&rawtime);
  std::string currentTime = YangUtils::getDateTime(rawtime);

  std::string ifName = mConfig->getValue(baseConfigPath + "/leaf-name");
  interface->name = std::make_shared<std::string>(ifName)->c_str();
  mInterfaces[ifName] = interface;

  // Map of config data (rw)
  std::map<std::string, std::string> dataCfg;

  // +--rw interface* [name]
  YangPath pathIf(mPathParent);
  std::pair<std::string, std::string> keyInterface("name", ifName);
  pathIf.add(
      "interface",
      keyInterface); // Base path: <pathParent>/interface[name='<ifName>']

  //    +--rw name                        string
  // dataCfg["name"] = ifName;                 // Key is set automatically, when
  // entries added

  //    +--rw description?                string
  std::string ifDesc = mConfig->getValue(baseConfigPath + "/leaf-description");
  if (!ifDesc.empty()) {
    dataCfg["description"] = ifDesc;
    interface->description = std::make_shared<std::string>(ifDesc)->c_str();
  }

  //    +--rw type                        identityref
  std::string ifType = mConfig->getValue(baseConfigPath + "/leaf-type");
  // HACK to compensate for current config format
  // if ifType doesn't start with "iana-if-type:"
  if (ifType.rfind("iana-if-type:", 0) != 0) {
    ifType.insert(0, "iana-if-type:");
  }
  dataCfg["type"] = ifType;
  interface->type = std::make_shared<std::string>(ifType)->c_str();

  //    +--rw enabled?                    boolean
  std::string ifEnabled = mConfig->getValue(baseConfigPath + "/leaf-enabled");
  if (!ifEnabled.empty()) {
    dataCfg["enabled"] = ifEnabled;
    interface->enabled = ifEnabled == "true";
  }

  // Augmented O-RAN interfaces (o-ran-int) module path
  YangPath pathORanInt;
  pathORanInt.addModule(modORanInt);

  // augment from o-ran-int, when "if:type = 'ianaift:l2vlan'"
  //    +--rw o-ran-int:base-interface?   if:interface-ref
  //    +--rw o-ran-int:vlan-id?          uint16
  if (ifType == "iana-if-type:l2vlan") {
    std::string baseIfName =
        mConfig->getValue(baseConfigPath + "/leaf-base-interface");
    if (!baseIfName.empty()) {
      dataCfg[pathORanInt.pathParam() + "base-interface"] = baseIfName;
      interface->baseInterface =
          std::make_shared<std::string>(baseIfName)->c_str();
    }
    std::string ifVlanId = mConfig->getValue(baseConfigPath + "/leaf-vlan-id");
    dataCfg[pathORanInt.pathParam() + "vlan-id"] = ifVlanId;
    interface->vlanId = std::stoi(ifVlanId);
  }
  // augment from o-ran-int, when "if:type = 'ianaift:ethernetCsmacd'"
  //    +--rw o-ran-int:l2-mtu?           uint16
  //    +--rw o-ran-int:vlan-tagging?     boolean
  //    +--rw o-ran-int:class-of-service
  //    +--rw o-ran-int:alias-macs*       yang:mac-address
  //    {ALIASMAC-BASED-CU-PLANE}?
  else {
    std::string ifL2mtu = mConfig->getValue(baseConfigPath + "/leaf-l2-mtu");
    if (!ifL2mtu.empty()) {
      dataCfg[pathORanInt.pathParam() + "l2-mtu"] = ifL2mtu;
      interface->l2Mtu = std::stoi(ifL2mtu);
    }
    std::string ifVlanTagging =
        mConfig->getValue(baseConfigPath + "/leaf-vlan-tagging");
    if (!ifVlanTagging.empty()) {
      dataCfg[pathORanInt.pathParam() + "vlan-tagging"] = ifVlanTagging;
      interface->vlanTagging = ifVlanTagging == "true";
    }

    addClassOfService(dataCfg, idx, interface);
  }

  // augment from o-ran-int, when "if:type = 'ianaift:l2vlan'" OR "if:type =
  // 'ianaift:ethernetCsmacd'"
  //    +--rw o-ran-int:mac-address?      yang:mac-address
  //    +--rw o-ran-int:port-reference

  std::string ifMac = mConfig->getValue(baseConfigPath + "/leaf-mac-address");
  if (!ifMac.empty()) {
    dataCfg[pathORanInt.pathParam() + "mac-address"] = ifMac;
    interface->macAddress = std::make_shared<std::string>(ifMac)->c_str();
  }

  // TODO: create the rest of the rw data leaves and add switches for if
  // features are enabled or augments exist

  // Create 'interface' configuration data list entry in sysrepo
  createListEntry(pathIf.pathRoot(), dataCfg);
  usleep(1000);

  // Added another interface
  mNumInterfaces++;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
void
IetfInterfacesHandler::addClassOfService(
    std::map<std::string, std::string>& dataCfg,
    int idx,
    std::shared_ptr<interface_t> interface) {
  std::string baseConfigPath =
      std::string(
          "module-ietf-interfaces/container-interfaces/list-interface[") +
      std::to_string(idx) + "]/container-class-of-service";

  // +--rw o-ran-int:class-of-service
  YangPath pathCoS(modORanInt, "class-of-service");

  //    +--rw o-ran-int:u-plane-marking?          pcp
  //    +--rw o-ran-int:c-plane-marking?          pcp
  //    +--rw o-ran-int:m-plane-marking?          pcp
  //    +--rw o-ran-int:s-plane-marking?          pcp
  //    +--rw o-ran-int:other-marking?            pcp
  std::string uPlaneMarking =
      mConfig->getValue(baseConfigPath + "/leaf-u-plane-marking");
  if (!uPlaneMarking.empty()) {
    dataCfg[pathCoS.pathParam() + "c-plane-marking"] = uPlaneMarking;
    interface->classOfService.uPlaneMarking = std::stoi(uPlaneMarking);
  } else {
    interface->classOfService.uPlaneMarking = 7;
  }
  std::string cPlaneMarking =
      mConfig->getValue(baseConfigPath + "/leaf-c-plane-marking");
  if (!cPlaneMarking.empty()) {
    dataCfg[pathCoS.pathParam() + "c-plane-marking"] = cPlaneMarking;
    interface->classOfService.cPlaneMarking = std::stoi(cPlaneMarking);
  } else {
    interface->classOfService.cPlaneMarking = 7;
  }
  std::string mPlaneMarking =
      mConfig->getValue(baseConfigPath + "/leaf-m-plane-marking");
  if (!mPlaneMarking.empty()) {
    dataCfg[pathCoS.pathParam() + "m-plane-marking"] = mPlaneMarking;
    interface->classOfService.mPlaneMarking = std::stoi(mPlaneMarking);
  } else {
    interface->classOfService.mPlaneMarking = 2;
  }
  std::string sPlaneMarking =
      mConfig->getValue(baseConfigPath + "/leaf-s-plane-marking");
  if (!sPlaneMarking.empty()) {
    dataCfg[pathCoS.pathParam() + "s-plane-marking"] = sPlaneMarking;
    interface->classOfService.sPlaneMarking = std::stoi(sPlaneMarking);
  } else {
    interface->classOfService.sPlaneMarking = 7;
  }
  std::string otherMarking =
      mConfig->getValue(baseConfigPath + "/leaf-other-marking");
  if (!otherMarking.empty()) {
    dataCfg[pathCoS.pathParam() + "other-marking"] = otherMarking;
    interface->classOfService.otherMarking = std::stoi(otherMarking);
  } else {
    interface->classOfService.otherMarking = 1;
  }

  // TODO: enhanced-uplane-marking
  //    +--rw o-ran-int:enhanced-uplane-markings* [up-marking-name]
  //       +--rw o-ran-int:up-marking-name   string
  //       +--rw o-ran-int:enhanced-marking? pcp
}

//=============================================================================================================
// PRIVATE - Helper Functions
//=============================================================================================================
