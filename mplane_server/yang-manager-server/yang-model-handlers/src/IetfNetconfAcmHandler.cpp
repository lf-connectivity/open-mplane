/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IetfNetconfAcmHandler.cpp
 * \brief     IETF NETCONF Access Control Model module handler
 *
 *
 * \details   IETF NETCONF Access Control Model module handler
 *
 * module: ietf-netconf-acm
 *   +--rw nacm
 *      +--rw enable-nacm?            boolean
 *      +--rw read-default?           action-type
 *      +--rw write-default?          action-type
 *      +--rw exec-default?           action-type
 *      +--rw enable-external-groups? boolean
 *      +--ro denied-operations       yang:zero-based-counter32
 *      +--ro denied-data-writes      yang:zero-based-counter32
 *      +--ro denied-notifications    yang:zero-based-counter32
 *      +--rw groups
 *      |  +--rw group* [name]
 *      |     +--rw name       group-name-type
 *      |     +--rw user-name* user-name-type
 *      +--rw rule-list* [name]
 *         +--rw name   string
 *         +--rw group* union
 *         +--rw rule* [name]
 *            +--rw name               string
 *            +--rw module-name?       union
 *            +--rw (rule-type)?
 *            |  +--:(protocol-operation)
 *            |  |  +--rw rpc-name?          union
 *            |  +--:(notification)
 *            |  |  +--rw notification-name? union
 *            |  +--:(data-node)
 *            |     +--rw path               node-instance-identifier
 *            +--rw access-operations? union
 *            +--rw action             action-type
 *            +--rw comment?           string
 *
 * NOTE: NACM is disabled, until user management is added.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "ILeafContainer.h"
#include "stringfunc.hpp"

#include "IetfNetconfAcmHandler.h"
#include "RadioDatastoreSysrepo.h"

using namespace Mplane;

//=============================================================================================================
// DEFINITIONS
//=============================================================================================================
//#define DISABLE_NETCONF_ACM

//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
IetfNetconfAcmHandler::IetfNetconfAcmHandler(
    std::shared_ptr<IYangModuleMgr> moduleMgr)
    : YangHandlerSysrepo(
          "ietf-netconf-acm", moduleMgr, "IetfNetconfAcmHandler"),
      mCallback(std::make_shared<SysrepoGetitemsCallback>(path("nacm"))) {}

//-------------------------------------------------------------------------------------------------------------
IetfNetconfAcmHandler::~IetfNetconfAcmHandler() {}

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfAcmHandler::initialise() {
  // ------------------------------------------------------------------------
  // daisychain the initialisations
  // ------------------------------------------------------------------------
  if (!this->YangHandlerSysrepo::initialise())
    return false;

  // NOTE: We set up the groups/users in a start up script (so that
  // o-ran-usermgmt can be initialised) That means we only need to add in the
  // access rules here (done here to minimise the start up script)

  // ------------------------------------------------------------------------
  // Initialise configuration data
  // ------------------------------------------------------------------------

  bool ok(true);

  ok |= addSudoRules();
  ok |= addNmsRules();
  ok |= addFmpmRules();
  ok |= addSwmRules();
  ok |= addSmoRules();
  ok |= addHybridoduRules();
  ok |= addRootRules();

#if defined(DISABLE_NETCONF_ACM)
  // Map of config data (rw)
  std::map<std::string, std::string> dataCfg;

  // +--rw nacm
  YangPath pathNacm(name(), "nacm");

  //    +--rw enable-nacm?            boolean
  dataCfg["enable-nacm"] = "false";

  // Create 'nacm' configuration data list entry in sysrepo
  createListEntry(pathNacm.pathRoot(), dataCfg);
#endif /* DISABLE_NETCONF_ACM */

  // Make configuration data pseudo read only
  makeReadOnly(path("nacm"));

  // ------------------------------------------------------------------------
  // Register callback for each top level container
  // ------------------------------------------------------------------------
  getItemsSubscribe(mCallback->path(), mCallback);
  changeSubscribe();

  return ok;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
IetfNetconfAcmHandler::valueChange(
    const std::string& xpath,
    std::shared_ptr<YangParam> oldValue,
    std::shared_ptr<YangParam> newValue) {
  if (oldValue && !newValue) {
    logDebugVerbose(
        "IetfNetconfAcmHandler::valueChange() - %s", oldValue->name().c_str());
  }
  if (newValue) {
    logDebugVerbose(
        "IetfNetconfAcmHandler::valueChange() - %s", newValue->name().c_str());
  }
}

//-------------------------------------------------------------------------------------------------------------
int
IetfNetconfAcmHandler::validate(
    std::shared_ptr<YangParams> params,
    std::shared_ptr<YangParams> deletedParams) {
  return SR_ERR_VALIDATION_FAILED;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfAcmHandler::addSudoRules() {
  std::map<std::string, std::string> dataCfg;

  dataCfg["rule-list[name='sudo-rules']/name"] = "sudo-rules";
  dataCfg["rule-list[name='sudo-rules']/group"] = "sudo";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-hardware']/name"]
  //= "sudo-iana-hardware" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-iana-hardware']/"
       "module-name"] = "iana-hardware";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-iana-hardware']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-iana-hardware']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-iana-hardware']/comment"] =
          "sudo iana-hardware R--";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-hardware']/name"]
  //= "sudo-ietf-hardware" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-hardware']/"
       "module-name"] = "ietf-hardware";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-hardware']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-hardware']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-hardware']/comment"] =
          "sudo ietf-hardware RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-permit-write']/name"]
  //= "sudo-ietf-interfaces-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-interfaces-permit-write']/module-name"] =
          "ietf-interfaces";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-interfaces-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-interfaces-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-interfaces-permit-write']/comment"] =
          "sudo ietf-interfaces RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-deny-exec']/name"]
  //= "sudo-ietf-interfaces-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-interfaces-deny-exec']/module-name"] =
          "ietf-interfaces";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-interfaces-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-interfaces-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-interfaces-deny-exec']/comment"] =
          "sudo ietf-interfaces RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-permit-write']/name"]
  //= "sudo-ietf-ip-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-permit-write']/"
       "module-name"] = "ietf-ip";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-permit-write']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-permit-write']/"
       "comment"] = "sudo ietf-ip RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-deny-exec']/name"]
  //= "sudo-ietf-ip-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-deny-exec']/"
       "module-name"] = "ietf-ip";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-deny-exec']/"
       "comment"] = "sudo ietf-ip RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-acm-permit-write']/name"]
  //= "sudo-ietf-netconf-acm-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-acm-permit-write']/module-name"] =
          "ietf-netconf-acm";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-acm-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-acm-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-acm-permit-write']/comment"] =
          "sudo ietf-netconf-acm RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-acm-deny-exec']/name"]
  //= "sudo-ietf-netconf-acm-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-acm-deny-exec']/module-name"] =
          "ietf-netconf-acm";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-acm-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-acm-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-acm-deny-exec']/comment"] =
          "sudo ietf-netconf-acm RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-notifications']/name"]
  //= "sudo-ietf-netconf-notifications" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-notifications']/module-name"] =
          "ietf-netconf-notifications";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-notifications']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-notifications']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-netconf-notifications']/comment"] =
          "sudo ietf-netconf-notifications --X";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-subscribed-notifications-deny-read']/name"]
  //= "sudo-ietf-subscribed-notifications-deny-read" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-subscribed-notifications-deny-read']/"
       "module-name"] = "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-subscribed-notifications-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-subscribed-notifications-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-subscribed-notifications-deny-read']/comment"] =
          "sudo ietf-subscribed-notifications --- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-subscribed-notifications-deny-exec']/name"]
  //= "sudo-ietf-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-subscribed-notifications-deny-exec']/"
       "module-name"] = "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-subscribed-notifications-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-ietf-subscribed-notifications-deny-exec']/comment"] =
          "sudo ietf-subscribed-notifications --- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald']/name"]
  //= "sudo-o-ran-ald" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald']/module-name"] =
          "o-ran-ald";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald']/"
       "access-operations"] = "read";
  dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald']/action"] =
      "deny";
  dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald']/comment"] =
      "sudo o-ran-ald --X";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald-port']/name"]
  //= "sudo-o-ran-ald-port" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald-port']/"
       "module-name"] = "o-ran-ald-port";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald-port']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald-port']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald-port']/"
       "comment"] = "sudo o-ran-ald-port RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-antenna-calibration']/name"]
  //= "sudo-o-ran-antenna-calibration" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-antenna-calibration']/module-name"] =
          "o-ran-antenna-calibration";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-antenna-calibration']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-antenna-calibration']/action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-antenna-calibration']/comment"] =
          "sudo o-ran-antenna-calibration RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-permit-write']/name"]
  //= "sudo-o-ran-delay-management-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-delay-management-permit-write']/module-name"] =
          "o-ran-delay-management";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-delay-management-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-delay-management-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-delay-management-permit-write']/comment"] =
          "sudo o-ran-delay-management RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-deny-exec']/name"]
  //= "sudo-o-ran-delay-management-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-delay-management-deny-exec']/module-name"] =
          "o-ran-delay-management";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-delay-management-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-delay-management-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-delay-management-deny-exec']/comment"] =
          "sudo o-ran-delay-management RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-dhcp']/name"]
  //= "sudo-o-ran-dhcp" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-dhcp']/"
       "module-name"] = "o-ran-dhcp";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-dhcp']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-dhcp']/action"] =
      "deny";
  dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-dhcp']/comment"] =
      "sudo o-ran-dhcp R--";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-permit-write']/name"]
  //= "sudo-o-ran-ecpri-delay-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ecpri-delay-permit-write']/module-name"] =
          "o-ran-ecpri-delay";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ecpri-delay-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ecpri-delay-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ecpri-delay-permit-write']/comment"] =
          "sudo o-ran-ecpri-delay RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-deny-exec']/name"]
  //= "sudo-o-ran-ecpri-delay-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ecpri-delay-deny-exec']/module-name"] =
          "o-ran-ecpri-delay";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ecpri-delay-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ecpri-delay-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ecpri-delay-deny-exec']/comment"] =
          "sudo o-ran-ecpri-delay RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ethernet-forwarding-permit-write']/name"]
  //= "sudo-o-ran-ethernet-forwarding-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ethernet-forwarding-permit-write']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ethernet-forwarding-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ethernet-forwarding-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ethernet-forwarding-permit-write']/comment"] =
          "sudo o-ran-ethernet-forwarding RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ethernet-forwarding-deny-exec']/name"]
  //= "sudo-o-ran-ethernet-forwarding-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ethernet-forwarding-deny-exec']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ethernet-forwarding-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ethernet-forwarding-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ethernet-forwarding-deny-exec']/comment"] =
          "sudo o-ran-ethernet-forwarding RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-externalio']/name"]
  //= "sudo-o-ran-externalio" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-externalio']/"
       "module-name"] = "o-ran-externalio";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-externalio']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-externalio']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-externalio']/"
       "comment"] = "sudo o-ran-externalio RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-fan']/name"]
  //= "sudo-o-ran-fan" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-fan']/module-name"] =
          "o-ran-fan";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-fan']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-fan']/action"] =
      "deny";
  dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-fan']/comment"] =
      "sudo o-ran-fan R--";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-file-management']/name"]
  //= "sudo-o-ran-file-management" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-file-management']/"
       "module-name"] = "o-ran-file-management";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-file-management']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-file-management']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-file-management']/"
       "comment"] = "sudo o-ran-file-management --X";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-hardware']/name"]
  //= "sudo-o-ran-hardware" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-hardware']/"
       "module-name"] = "o-ran-hardware";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-hardware']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-hardware']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-hardware']/"
       "comment"] = "sudo o-ran-hardware RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-interfaces']/name"]
  //= "sudo-o-ran-interfaces" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-interfaces']/"
       "module-name"] = "o-ran-interfaces";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-interfaces']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-interfaces']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-interfaces']/"
       "comment"] = "sudo o-ran-interfaces RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-permit-write']/name"]
  //= "sudo-o-ran-laa-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-permit-write']/"
       "module-name"] = "o-ran-laa";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-permit-write']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-permit-write']/"
       "comment"] = "sudo o-ran-laa RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-deny-exec']/name"]
  //= "sudo-o-ran-laa-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-deny-exec']/"
       "module-name"] = "o-ran-laa";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-deny-exec']/"
       "comment"] = "sudo o-ran-laa RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-operations']/name"]
  //= "sudo-o-ran-laa-operations" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-operations']/"
       "module-name"] = "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-operations']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-operations']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-operations']/"
       "comment"] = "sudo o-ran-laa-operations --X";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm-permit-write']/name"]
  //= "sudo-o-ran-lbm-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm-permit-write']/"
       "module-name"] = "o-ran-lbm";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm-permit-write']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm-permit-write']/"
       "comment"] = "sudo o-ran-lbm RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm-deny-exec']/name"]
  //= "sudo-o-ran-lbm-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm-deny-exec']/"
       "module-name"] = "o-ran-lbm";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm-deny-exec']/"
       "comment"] = "sudo o-ran-lbm RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-module-cap-permit-write']/name"]
  //= "sudo-o-ran-module-cap-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-module-cap-permit-write']/module-name"] =
          "o-ran-module-cap";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-module-cap-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-module-cap-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-module-cap-permit-write']/comment"] =
          "sudo o-ran-module-cap RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-module-cap-deny-exec']/name"]
  //= "sudo-o-ran-module-cap-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-module-cap-deny-exec']/module-name"] =
          "o-ran-module-cap";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-module-cap-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-module-cap-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-module-cap-deny-exec']/comment"] =
          "sudo o-ran-module-cap RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-permit-write']/name"]
  //= "sudo-o-ran-mplane-int-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-mplane-int-permit-write']/module-name"] =
          "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-mplane-int-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-mplane-int-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-mplane-int-permit-write']/comment"] =
          "sudo o-ran-mplane-int RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-deny-exec']/name"]
  //= "sudo-o-ran-mplane-int-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-mplane-int-deny-exec']/module-name"] =
          "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-mplane-int-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-mplane-int-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-mplane-int-deny-exec']/comment"] =
          "sudo o-ran-mplane-int RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-operations']/name"]
  //= "sudo-o-ran-operations" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-operations']/"
       "module-name"] = "o-ran-operations";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-operations']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-operations']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-operations']/"
       "comment"] = "sudo o-ran-operations RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-performance-management']/name"]
  //= "sudo-o-ran-performance-management" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-performance-management']/module-name"] =
          "o-ran-performance-management";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-performance-management']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-performance-management']/action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-performance-management']/comment"] =
          "sudo o-ran-performance-management RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-permit-write']/name"]
  //= "sudo-o-ran-processing-element-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-processing-element-permit-write']/module-name"] =
          "o-ran-processing-element";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-processing-element-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-processing-element-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-processing-element-permit-write']/comment"] =
          "sudo o-ran-processing-element RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-deny-exec']/name"]
  //= "sudo-o-ran-processing-element-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-processing-element-deny-exec']/module-name"] =
          "o-ran-processing-element";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-processing-element-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-processing-element-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-processing-element-deny-exec']/comment"] =
          "sudo o-ran-processing-element RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-shared-cell-permit-write']/name"]
  //= "sudo-o-ran-shared-cell-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-shared-cell-permit-write']/module-name"] =
          "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-shared-cell-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-shared-cell-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-shared-cell-permit-write']/comment"] =
          "sudo o-ran-shared-cell RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-shared-cell-deny-exec']/name"]
  //= "sudo-o-ran-shared-cell-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-shared-cell-deny-exec']/module-name"] =
          "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-shared-cell-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-shared-cell-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-shared-cell-deny-exec']/comment"] =
          "sudo o-ran-shared-cell RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-supervision']/name"]
  //= "sudo-o-ran-supervision" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-supervision']/"
       "module-name"] = "o-ran-supervision";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-supervision']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-supervision']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-supervision']/"
       "comment"] = "sudo o-ran-supervision RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync']/name"]
  //= "sudo-o-ran-sync" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync']/"
       "module-name"] = "o-ran-sync";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync']/action"] =
      "permit";
  dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync']/comment"] =
      "sudo o-ran-sync RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-trace']/name"]
  //= "sudo-o-ran-trace" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-trace']/"
       "module-name"] = "o-ran-trace";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-trace']/"
       "access-operations"] = "read";
  dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-trace']/action"] =
      "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-trace']/comment"] =
          "sudo o-ran-trace --X";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-permit-write']/name"]
  //= "sudo-o-ran-transceiver-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-transceiver-permit-write']/module-name"] =
          "o-ran-transceiver";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-transceiver-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-transceiver-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-transceiver-permit-write']/comment"] =
          "sudo o-ran-transceiver RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-deny-exec']/name"]
  //= "sudo-o-ran-transceiver-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-transceiver-deny-exec']/module-name"] =
          "o-ran-transceiver";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-transceiver-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-transceiver-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-transceiver-deny-exec']/comment"] =
          "sudo o-ran-transceiver RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-troubleshooting']/name"]
  //= "sudo-o-ran-troubleshooting" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-troubleshooting']/"
       "module-name"] = "o-ran-troubleshooting";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-troubleshooting']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-troubleshooting']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-troubleshooting']/"
       "comment"] = "sudo o-ran-troubleshooting --X";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-permit-write']/name"]
  //= "sudo-o-ran-udp-echo-permit-write" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-udp-echo-permit-write']/module-name"] =
          "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-udp-echo-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-udp-echo-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-udp-echo-permit-write']/comment"] =
          "sudo o-ran-udp-echo RW- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-deny-exec']/name"]
  //= "sudo-o-ran-udp-echo-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-udp-echo-deny-exec']/module-name"] =
          "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-udp-echo-deny-exec']/access-operations"] = "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-udp-echo-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-udp-echo-deny-exec']/comment"] =
          "sudo o-ran-udp-echo RW- (2/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-uplane-conf']/name"]
  //= "sudo-o-ran-uplane-conf" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-uplane-conf']/"
       "module-name"] = "o-ran-uplane-conf";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-uplane-conf']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-uplane-conf']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-uplane-conf']/"
       "comment"] = "sudo o-ran-uplane-conf RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt']/name"]
  //= "sudo-o-ran-usermgmt" ;
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt']/"
       "module-name"] = "o-ran-usermgmt";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt']/"
       "comment"] = "sudo o-ran-usermgmt RWX";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ves-subscribed-notifications-deny-read']/name"]
  //= "sudo-o-ran-ves-subscribed-notifications-deny-read" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ves-subscribed-notifications-deny-read']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ves-subscribed-notifications-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ves-subscribed-notifications-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ves-subscribed-notifications-deny-read']/"
       "comment"] = "sudo o-ran-ves-subscribed-notifications --- (1/2)";

  //    dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ves-subscribed-notifications-deny-exec']/name"]
  //= "sudo-o-ran-ves-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ves-subscribed-notifications-deny-exec']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ves-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ves-subscribed-notifications-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='sudo-rules']/"
       "rule[name='sudo-o-ran-ves-subscribed-notifications-deny-exec']/"
       "comment"] = "sudo o-ran-ves-subscribed-notifications --- (2/2)";

  if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfAcmHandler::addNmsRules() {
  std::map<std::string, std::string> dataCfg;

  dataCfg["rule-list[name='nms-rules']/name"] = "nms-rules";
  dataCfg["rule-list[name='nms-rules']/group"] = "nms";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-hardware']/name"]
  //= "nms-iana-hardware" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-iana-hardware']/"
       "module-name"] = "iana-hardware";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-iana-hardware']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-hardware']/action"] =
      "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-iana-hardware']/comment"] =
          "nms iana-hardware R--";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-hardware']/name"]
  //= "nms-ietf-hardware" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-hardware']/"
       "module-name"] = "ietf-hardware";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-hardware']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-hardware']/action"] =
      "permit";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-hardware']/comment"] =
          "nms ietf-hardware RWX";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-permit-write']/name"]
  //= "nms-ietf-interfaces-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-interfaces-permit-write']/module-name"] =
          "ietf-interfaces";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-interfaces-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-interfaces-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-interfaces-permit-write']/comment"] =
          "nms ietf-interfaces RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-deny-exec']/name"]
  //= "nms-ietf-interfaces-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-deny-exec']/"
       "module-name"] = "ietf-interfaces";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-deny-exec']/"
       "comment"] = "nms ietf-interfaces RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-permit-write']/name"]
  //= "nms-ietf-ip-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-permit-write']/"
       "module-name"] = "ietf-ip";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-permit-write']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-permit-write']/"
       "comment"] = "nms ietf-ip RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-deny-exec']/name"]
  //= "nms-ietf-ip-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-deny-exec']/"
       "module-name"] = "ietf-ip";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-deny-exec']/"
       "comment"] = "nms ietf-ip RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-acm']/name"]
  //= "nms-ietf-netconf-acm" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-acm']/"
       "module-name"] = "ietf-netconf-acm";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-acm']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-acm']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-acm']/"
       "comment"] = "nms ietf-netconf-acm R--";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-notifications']/name"]
  //= "nms-ietf-netconf-notifications" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-netconf-notifications']/module-name"] =
          "ietf-netconf-notifications";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-netconf-notifications']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-netconf-notifications']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-netconf-notifications']/comment"] =
          "nms ietf-netconf-notifications --X";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-subscribed-notifications-deny-read']/name"]
  //= "nms-ietf-subscribed-notifications-deny-read" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-subscribed-notifications-deny-read']/module-name"] =
          "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-subscribed-notifications-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-subscribed-notifications-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-subscribed-notifications-deny-read']/comment"] =
          "nms ietf-subscribed-notifications --- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-subscribed-notifications-deny-exec']/name"]
  //= "nms-ietf-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-subscribed-notifications-deny-exec']/module-name"] =
          "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-subscribed-notifications-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-ietf-subscribed-notifications-deny-exec']/comment"] =
          "nms ietf-subscribed-notifications --- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-read']/name"]
  //= "nms-o-ran-ald-deny-read" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-read']/"
       "module-name"] = "o-ran-ald";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-read']/"
       "comment"] = "nms o-ran-ald --- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-exec']/name"]
  //= "nms-o-ran-ald-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-exec']/"
       "module-name"] = "o-ran-ald";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-exec']/"
       "comment"] = "nms o-ran-ald --- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-port']/name"]
  //= "nms-o-ran-ald-port" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-port']/"
       "module-name"] = "o-ran-ald-port";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-port']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-port']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-port']/comment"] =
          "nms o-ran-ald-port RWX";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-antenna-calibration']/name"]
  //= "nms-o-ran-antenna-calibration" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-antenna-calibration']/"
       "module-name"] = "o-ran-antenna-calibration";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-antenna-calibration']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-antenna-calibration']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-antenna-calibration']/"
       "comment"] = "nms o-ran-antenna-calibration R--";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-delay-management']/name"]
  //= "nms-o-ran-delay-management" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-delay-management']/"
       "module-name"] = "o-ran-delay-management";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-delay-management']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-delay-management']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-delay-management']/"
       "comment"] = "nms o-ran-delay-management R--";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-dhcp']/name"]
  //= "nms-o-ran-dhcp" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-dhcp']/module-name"] =
          "o-ran-dhcp";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-dhcp']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-dhcp']/action"] =
      "deny";
  dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-dhcp']/comment"] =
      "nms o-ran-dhcp R--";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay']/name"]
  //= "nms-o-ran-ecpri-delay" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay']/"
       "module-name"] = "o-ran-ecpri-delay";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay']/"
       "comment"] = "nms o-ran-ecpri-delay R--";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ethernet-forwarding-permit-write']/name"]
  //= "nms-o-ran-ethernet-forwarding-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ethernet-forwarding-permit-write']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ethernet-forwarding-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ethernet-forwarding-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ethernet-forwarding-permit-write']/comment"] =
          "nms o-ran-ethernet-forwarding RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ethernet-forwarding-deny-exec']/name"]
  //= "nms-o-ran-ethernet-forwarding-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ethernet-forwarding-deny-exec']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ethernet-forwarding-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ethernet-forwarding-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ethernet-forwarding-deny-exec']/comment"] =
          "nms o-ran-ethernet-forwarding RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-externalio']/name"]
  //= "nms-o-ran-externalio" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-externalio']/"
       "module-name"] = "o-ran-externalio";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-externalio']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-externalio']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-externalio']/"
       "comment"] = "nms o-ran-externalio RWX";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-fan']/name"] =
  //"nms-o-ran-fan" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-fan']/module-name"] =
          "o-ran-fan";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-fan']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-fan']/action"] =
      "deny";
  dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-fan']/comment"] =
      "nms o-ran-fan R--";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-file-management']/name"]
  //= "nms-o-ran-file-management" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-file-management']/"
       "module-name"] = "o-ran-file-management";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-file-management']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-file-management']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-file-management']/"
       "comment"] = "nms o-ran-file-management --X";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-hardware-permit-write']/name"]
  //= "nms-o-ran-hardware-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-hardware-permit-write']/module-name"] =
          "o-ran-hardware";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-hardware-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-hardware-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-hardware-permit-write']/comment"] =
          "nms o-ran-hardware RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-hardware-deny-exec']/name"]
  //= "nms-o-ran-hardware-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-hardware-deny-exec']/"
       "module-name"] = "o-ran-hardware";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-hardware-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-hardware-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-hardware-deny-exec']/"
       "comment"] = "nms o-ran-hardware RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-interfaces']/name"]
  //= "nms-o-ran-interfaces" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-interfaces']/"
       "module-name"] = "o-ran-interfaces";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-interfaces']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-interfaces']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-interfaces']/"
       "comment"] = "nms o-ran-interfaces RWX";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-permit-write']/name"]
  //= "nms-o-ran-laa-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-permit-write']/"
       "module-name"] = "o-ran-laa";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-permit-write']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-permit-write']/"
       "comment"] = "nms o-ran-laa RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-deny-exec']/name"]
  //= "nms-o-ran-laa-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-deny-exec']/"
       "module-name"] = "o-ran-laa";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-deny-exec']/"
       "comment"] = "nms o-ran-laa RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-read']/name"]
  //= "nms-o-ran-laa-operations-deny-read" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-laa-operations-deny-read']/module-name"] =
          "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-laa-operations-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-laa-operations-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-laa-operations-deny-read']/comment"] =
          "nms o-ran-laa-operations --- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-exec']/name"]
  //= "nms-o-ran-laa-operations-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-laa-operations-deny-exec']/module-name"] =
          "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-laa-operations-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-laa-operations-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-laa-operations-deny-exec']/comment"] =
          "nms o-ran-laa-operations --- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-permit-write']/name"]
  //= "nms-o-ran-lbm-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-permit-write']/"
       "module-name"] = "o-ran-lbm";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-permit-write']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-permit-write']/"
       "comment"] = "nms o-ran-lbm RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-deny-exec']/name"]
  //= "nms-o-ran-lbm-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-deny-exec']/"
       "module-name"] = "o-ran-lbm";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-deny-exec']/"
       "comment"] = "nms o-ran-lbm RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-module-cap']/name"]
  //= "nms-o-ran-module-cap" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-module-cap']/"
       "module-name"] = "o-ran-module-cap";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-module-cap']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-module-cap']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-module-cap']/"
       "comment"] = "nms o-ran-module-cap R--";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-permit-write']/name"]
  //= "nms-o-ran-mplane-int-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-mplane-int-permit-write']/module-name"] =
          "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-mplane-int-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-mplane-int-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-mplane-int-permit-write']/comment"] =
          "nms o-ran-mplane-int RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-deny-exec']/name"]
  //= "nms-o-ran-mplane-int-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-mplane-int-deny-exec']/module-name"] =
          "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-mplane-int-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-mplane-int-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-mplane-int-deny-exec']/comment"] =
          "nms o-ran-mplane-int RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-operations-permit-write']/name"]
  //= "nms-o-ran-operations-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-operations-permit-write']/module-name"] =
          "o-ran-operations";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-operations-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-operations-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-operations-permit-write']/comment"] =
          "nms o-ran-operations RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-operations-deny-exec']/name"]
  //= "nms-o-ran-operations-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-operations-deny-exec']/module-name"] =
          "o-ran-operations";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-operations-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-operations-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-operations-deny-exec']/comment"] =
          "nms o-ran-operations RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-performance-management']/name"]
  //= "nms-o-ran-performance-management" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-performance-management']/module-name"] =
          "o-ran-performance-management";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-performance-management']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-performance-management']/action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-performance-management']/comment"] =
          "nms o-ran-performance-management RWX";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-permit-write']/name"]
  //= "nms-o-ran-processing-element-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-processing-element-permit-write']/module-name"] =
          "o-ran-processing-element";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-processing-element-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-processing-element-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-processing-element-permit-write']/comment"] =
          "nms o-ran-processing-element RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-deny-exec']/name"]
  //= "nms-o-ran-processing-element-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-processing-element-deny-exec']/module-name"] =
          "o-ran-processing-element";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-processing-element-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-processing-element-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-processing-element-deny-exec']/comment"] =
          "nms o-ran-processing-element RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-shared-cell-permit-write']/name"]
  //= "nms-o-ran-shared-cell-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-shared-cell-permit-write']/module-name"] =
          "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-shared-cell-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-shared-cell-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-shared-cell-permit-write']/comment"] =
          "nms o-ran-shared-cell RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-shared-cell-deny-exec']/name"]
  //= "nms-o-ran-shared-cell-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-shared-cell-deny-exec']/module-name"] =
          "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-shared-cell-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-shared-cell-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-shared-cell-deny-exec']/comment"] =
          "nms o-ran-shared-cell RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-read']/name"]
  //= "nms-o-ran-supervision-deny-read" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-supervision-deny-read']/module-name"] =
          "o-ran-supervision";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-supervision-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-supervision-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-supervision-deny-read']/comment"] =
          "nms o-ran-supervision --- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-exec']/name"]
  //= "nms-o-ran-supervision-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-supervision-deny-exec']/module-name"] =
          "o-ran-supervision";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-supervision-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-supervision-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-supervision-deny-exec']/comment"] =
          "nms o-ran-supervision --- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync']/name"]
  //= "nms-o-ran-sync" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync']/module-name"] =
          "o-ran-sync";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync']/action"] =
      "permit";
  dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync']/comment"] =
      "nms o-ran-sync RWX";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-trace']/name"]
  //= "nms-o-ran-trace" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-trace']/module-name"] =
          "o-ran-trace";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-trace']/"
       "access-operations"] = "read";
  dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-trace']/action"] =
      "deny";
  dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-trace']/comment"] =
      "nms o-ran-trace --X";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-permit-write']/name"]
  //= "nms-o-ran-transceiver-permit-write" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-transceiver-permit-write']/module-name"] =
          "o-ran-transceiver";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-transceiver-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-transceiver-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-transceiver-permit-write']/comment"] =
          "nms o-ran-transceiver RW- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-deny-exec']/name"]
  //= "nms-o-ran-transceiver-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-transceiver-deny-exec']/module-name"] =
          "o-ran-transceiver";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-transceiver-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-transceiver-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-transceiver-deny-exec']/comment"] =
          "nms o-ran-transceiver RW- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-troubleshooting']/name"]
  //= "nms-o-ran-troubleshooting" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-troubleshooting']/"
       "module-name"] = "o-ran-troubleshooting";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-troubleshooting']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-troubleshooting']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-troubleshooting']/"
       "comment"] = "nms o-ran-troubleshooting --X";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-udp-echo']/name"]
  //= "nms-o-ran-udp-echo" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-udp-echo']/"
       "module-name"] = "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-udp-echo']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-udp-echo']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-udp-echo']/comment"] =
          "nms o-ran-udp-echo R--";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-uplane-conf']/name"]
  //= "nms-o-ran-uplane-conf" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-uplane-conf']/"
       "module-name"] = "o-ran-uplane-conf";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-uplane-conf']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-uplane-conf']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-uplane-conf']/"
       "comment"] = "nms o-ran-uplane-conf RWX";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-read']/name"]
  //= "nms-o-ran-usermgmt-deny-read" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-read']/"
       "module-name"] = "o-ran-usermgmt";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-read']/"
       "comment"] = "nms o-ran-usermgmt --- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-exec']/name"]
  //= "nms-o-ran-usermgmt-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-exec']/"
       "module-name"] = "o-ran-usermgmt";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-exec']/"
       "comment"] = "nms o-ran-usermgmt --- (2/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ves-subscribed-notifications-deny-read']/name"]
  //= "nms-o-ran-ves-subscribed-notifications-deny-read" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ves-subscribed-notifications-deny-read']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ves-subscribed-notifications-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ves-subscribed-notifications-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ves-subscribed-notifications-deny-read']/"
       "comment"] = "nms o-ran-ves-subscribed-notifications --- (1/2)";

  //    dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ves-subscribed-notifications-deny-exec']/name"]
  //= "nms-o-ran-ves-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ves-subscribed-notifications-deny-exec']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ves-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ves-subscribed-notifications-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='nms-rules']/"
       "rule[name='nms-o-ran-ves-subscribed-notifications-deny-exec']/"
       "comment"] = "nms o-ran-ves-subscribed-notifications --- (2/2)";

  if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfAcmHandler::addFmpmRules() {
  std::map<std::string, std::string> dataCfg;

  dataCfg["rule-list[name='fm-pm-rules']/name"] = "fm-pm-rules";
  dataCfg["rule-list[name='fm-pm-rules']/group"] = "fm-pm";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-interfaces']/name"]
  //= "fm-pm-ietf-interfaces" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-interfaces']/"
       "module-name"] = "ietf-interfaces";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-interfaces']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-interfaces']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-interfaces']/"
       "comment"] = "fm-pm ietf-interfaces R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-ip']/name"]
  //= "fm-pm-ietf-ip" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-ip']/module-name"] =
          "ietf-ip";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-ip']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-ip']/action"] =
      "deny";
  dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-ip']/comment"] =
      "fm-pm ietf-ip R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-acm']/name"]
  //= "fm-pm-ietf-netconf-acm" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-acm']/"
       "module-name"] = "ietf-netconf-acm";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-acm']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-acm']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-acm']/"
       "comment"] = "fm-pm ietf-netconf-acm R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-notifications']/name"]
  //= "fm-pm-ietf-netconf-notifications" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-netconf-notifications']/module-name"] =
          "ietf-netconf-notifications";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-netconf-notifications']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-netconf-notifications']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-netconf-notifications']/comment"] =
          "fm-pm ietf-netconf-notifications --X";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-subscribed-notifications-deny-read']/name"]
  //= "fm-pm-ietf-subscribed-notifications-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-subscribed-notifications-deny-read']/"
       "module-name"] = "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-subscribed-notifications-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-subscribed-notifications-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-subscribed-notifications-deny-read']/comment"] =
          "fm-pm ietf-subscribed-notifications --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-subscribed-notifications-deny-exec']/name"]
  //= "fm-pm-ietf-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-subscribed-notifications-deny-exec']/"
       "module-name"] = "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-subscribed-notifications-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-ietf-subscribed-notifications-deny-exec']/comment"] =
          "fm-pm ietf-subscribed-notifications --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-read']/name"]
  //= "fm-pm-o-ran-ald-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-read']/"
       "module-name"] = "o-ran-ald";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-read']/"
       "comment"] = "fm-pm o-ran-ald --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-exec']/name"]
  //= "fm-pm-o-ran-ald-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-exec']/"
       "module-name"] = "o-ran-ald";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-exec']/"
       "comment"] = "fm-pm o-ran-ald --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-read']/name"]
  //= "fm-pm-o-ran-ald-port-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ald-port-deny-read']/module-name"] =
          "o-ran-ald-port";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ald-port-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ald-port-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ald-port-deny-read']/comment"] =
          "fm-pm o-ran-ald-port --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-exec']/name"]
  //= "fm-pm-o-ran-ald-port-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ald-port-deny-exec']/module-name"] =
          "o-ran-ald-port";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ald-port-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ald-port-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ald-port-deny-exec']/comment"] =
          "fm-pm o-ran-ald-port --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-read']/name"]
  //= "fm-pm-o-ran-antenna-calibration-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-antenna-calibration-deny-read']/module-name"] =
          "o-ran-antenna-calibration";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-antenna-calibration-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-antenna-calibration-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-antenna-calibration-deny-read']/comment"] =
          "fm-pm o-ran-antenna-calibration --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-exec']/name"]
  //= "fm-pm-o-ran-antenna-calibration-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-antenna-calibration-deny-exec']/module-name"] =
          "o-ran-antenna-calibration";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-antenna-calibration-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-antenna-calibration-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-antenna-calibration-deny-exec']/comment"] =
          "fm-pm o-ran-antenna-calibration --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-beamforming']/name"]
  //= "fm-pm-o-ran-beamforming" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-beamforming']/"
       "module-name"] = "o-ran-beamforming";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-beamforming']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-beamforming']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-beamforming']/"
       "comment"] = "fm-pm o-ran-beamforming R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-delay-management']/name"]
  //= "fm-pm-o-ran-delay-management" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-delay-management']/module-name"] =
          "o-ran-delay-management";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-delay-management']/access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-delay-management']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-delay-management']/comment"] =
          "fm-pm o-ran-delay-management R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-dhcp']/name"]
  //= "fm-pm-o-ran-dhcp" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-dhcp']/"
       "module-name"] = "o-ran-dhcp";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-dhcp']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-dhcp']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-dhcp']/comment"] =
          "fm-pm o-ran-dhcp R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ecpri-delay']/name"]
  //= "fm-pm-o-ran-ecpri-delay" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ecpri-delay']/"
       "module-name"] = "o-ran-ecpri-delay";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ecpri-delay']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ecpri-delay']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ecpri-delay']/"
       "comment"] = "fm-pm o-ran-ecpri-delay R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ethernet-forwarding-deny-read']/name"]
  //= "fm-pm-o-ran-ethernet-forwarding-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ethernet-forwarding-deny-read']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ethernet-forwarding-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ethernet-forwarding-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ethernet-forwarding-deny-read']/comment"] =
          "fm-pm o-ran-ethernet-forwarding --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ethernet-forwarding-deny-exec']/name"]
  //= "fm-pm-o-ran-ethernet-forwarding-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ethernet-forwarding-deny-exec']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ethernet-forwarding-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ethernet-forwarding-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ethernet-forwarding-deny-exec']/comment"] =
          "fm-pm o-ran-ethernet-forwarding --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-read']/name"]
  //= "fm-pm-o-ran-externalio-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-externalio-deny-read']/module-name"] =
          "o-ran-externalio";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-externalio-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-externalio-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-externalio-deny-read']/comment"] =
          "fm-pm o-ran-externalio --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-exec']/name"]
  //= "fm-pm-o-ran-externalio-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-externalio-deny-exec']/module-name"] =
          "o-ran-externalio";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-externalio-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-externalio-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-externalio-deny-exec']/comment"] =
          "fm-pm o-ran-externalio --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-fan']/name"]
  //= "fm-pm-o-ran-fan" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-fan']/"
       "module-name"] = "o-ran-fan";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-fan']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-fan']/action"] =
      "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-fan']/comment"] =
          "fm-pm o-ran-fan R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-file-management']/name"]
  //= "fm-pm-o-ran-file-management" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-file-management']/"
       "module-name"] = "o-ran-file-management";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-file-management']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-file-management']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-file-management']/"
       "comment"] = "fm-pm o-ran-file-management --X";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-read']/name"]
  //= "fm-pm-o-ran-hardware-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-hardware-deny-read']/module-name"] =
          "o-ran-hardware";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-hardware-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-hardware-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-hardware-deny-read']/comment"] =
          "fm-pm o-ran-hardware --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-exec']/name"]
  //= "fm-pm-o-ran-hardware-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-hardware-deny-exec']/module-name"] =
          "o-ran-hardware";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-hardware-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-hardware-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-hardware-deny-exec']/comment"] =
          "fm-pm o-ran-hardware --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-interfaces']/name"]
  //= "fm-pm-o-ran-interfaces" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-interfaces']/"
       "module-name"] = "o-ran-interfaces";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-interfaces']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-interfaces']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-interfaces']/"
       "comment"] = "fm-pm o-ran-interfaces R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-read']/name"]
  //= "fm-pm-o-ran-laa-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-read']/"
       "module-name"] = "o-ran-laa";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-read']/"
       "comment"] = "fm-pm o-ran-laa --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-exec']/name"]
  //= "fm-pm-o-ran-laa-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-exec']/"
       "module-name"] = "o-ran-laa";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-exec']/"
       "comment"] = "fm-pm o-ran-laa --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-read']/name"]
  //= "fm-pm-o-ran-laa-operations-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-laa-operations-deny-read']/module-name"] =
          "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-laa-operations-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-laa-operations-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-laa-operations-deny-read']/comment"] =
          "fm-pm o-ran-laa-operations --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-exec']/name"]
  //= "fm-pm-o-ran-laa-operations-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-laa-operations-deny-exec']/module-name"] =
          "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-laa-operations-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-laa-operations-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-laa-operations-deny-exec']/comment"] =
          "fm-pm o-ran-laa-operations --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-lbm']/name"]
  //= "fm-pm-o-ran-lbm" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-lbm']/"
       "module-name"] = "o-ran-lbm";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-lbm']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-lbm']/action"] =
      "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-lbm']/comment"] =
          "fm-pm o-ran-lbm R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-module-cap']/name"]
  //= "fm-pm-o-ran-module-cap" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-module-cap']/"
       "module-name"] = "o-ran-module-cap";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-module-cap']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-module-cap']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-module-cap']/"
       "comment"] = "fm-pm o-ran-module-cap R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-mplane-int']/name"]
  //= "fm-pm-o-ran-mplane-int" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-mplane-int']/"
       "module-name"] = "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-mplane-int']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-mplane-int']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-mplane-int']/"
       "comment"] = "fm-pm o-ran-mplane-int R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-operations']/name"]
  //= "fm-pm-o-ran-operations" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-operations']/"
       "module-name"] = "o-ran-operations";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-operations']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-operations']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-operations']/"
       "comment"] = "fm-pm o-ran-operations R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-performance-management']/name"]
  //= "fm-pm-o-ran-performance-management" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-performance-management']/module-name"] =
          "o-ran-performance-management";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-performance-management']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-performance-management']/action"] = "permit";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-performance-management']/comment"] =
          "fm-pm o-ran-performance-management RWX";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-processing-element']/name"]
  //= "fm-pm-o-ran-processing-element" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-processing-element']/module-name"] =
          "o-ran-processing-element";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-processing-element']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-processing-element']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-processing-element']/comment"] =
          "fm-pm o-ran-processing-element R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-shared-cell-deny-read']/name"]
  //= "fm-pm-o-ran-shared-cell-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-shared-cell-deny-read']/module-name"] =
          "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-shared-cell-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-shared-cell-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-shared-cell-deny-read']/comment"] =
          "fm-pm o-ran-shared-cell --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-shared-cell-deny-exec']/name"]
  //= "fm-pm-o-ran-shared-cell-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-shared-cell-deny-exec']/module-name"] =
          "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-shared-cell-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-shared-cell-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-shared-cell-deny-exec']/comment"] =
          "fm-pm o-ran-shared-cell --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-software-management']/name"]
  //= "fm-pm-o-ran-software-management" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-software-management']/module-name"] =
          "o-ran-software-management";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-software-management']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-software-management']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-software-management']/comment"] =
          "fm-pm o-ran-software-management R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-read']/name"]
  //= "fm-pm-o-ran-supervision-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-supervision-deny-read']/module-name"] =
          "o-ran-supervision";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-supervision-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-supervision-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-supervision-deny-read']/comment"] =
          "fm-pm o-ran-supervision --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-exec']/name"]
  //= "fm-pm-o-ran-supervision-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-supervision-deny-exec']/module-name"] =
          "o-ran-supervision";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-supervision-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-supervision-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-supervision-deny-exec']/comment"] =
          "fm-pm o-ran-supervision --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-sync']/name"]
  //= "fm-pm-o-ran-sync" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-sync']/"
       "module-name"] = "o-ran-sync";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-sync']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-sync']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-sync']/comment"] =
          "fm-pm o-ran-sync R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-trace']/name"]
  //= "fm-pm-o-ran-trace" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-trace']/"
       "module-name"] = "o-ran-trace";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-trace']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-trace']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-trace']/comment"] =
          "fm-pm o-ran-trace --X";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-transceiver']/name"]
  //= "fm-pm-o-ran-transceiver" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-transceiver']/"
       "module-name"] = "o-ran-transceiver";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-transceiver']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-transceiver']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-transceiver']/"
       "comment"] = "fm-pm o-ran-transceiver R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-troubleshooting']/name"]
  //= "fm-pm-o-ran-troubleshooting" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-troubleshooting']/"
       "module-name"] = "o-ran-troubleshooting";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-troubleshooting']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-troubleshooting']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-troubleshooting']/"
       "comment"] = "fm-pm o-ran-troubleshooting --X";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-read']/name"]
  //= "fm-pm-o-ran-udp-echo-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-udp-echo-deny-read']/module-name"] =
          "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-udp-echo-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-udp-echo-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-udp-echo-deny-read']/comment"] =
          "fm-pm o-ran-udp-echo --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-exec']/name"]
  //= "fm-pm-o-ran-udp-echo-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-udp-echo-deny-exec']/module-name"] =
          "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-udp-echo-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-udp-echo-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-udp-echo-deny-exec']/comment"] =
          "fm-pm o-ran-udp-echo --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-uplane-conf']/name"]
  //= "fm-pm-o-ran-uplane-conf" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-uplane-conf']/"
       "module-name"] = "o-ran-uplane-conf";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-uplane-conf']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-uplane-conf']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-uplane-conf']/"
       "comment"] = "fm-pm o-ran-uplane-conf R--";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-read']/name"]
  //= "fm-pm-o-ran-usermgmt-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-usermgmt-deny-read']/module-name"] =
          "o-ran-usermgmt";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-usermgmt-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-usermgmt-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-usermgmt-deny-read']/comment"] =
          "fm-pm o-ran-usermgmt --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-exec']/name"]
  //= "fm-pm-o-ran-usermgmt-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-usermgmt-deny-exec']/module-name"] =
          "o-ran-usermgmt";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-usermgmt-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-usermgmt-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-usermgmt-deny-exec']/comment"] =
          "fm-pm o-ran-usermgmt --- (2/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ves-subscribed-notifications-deny-read']/name"]
  //= "fm-pm-o-ran-ves-subscribed-notifications-deny-read" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ves-subscribed-notifications-deny-read']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ves-subscribed-notifications-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ves-subscribed-notifications-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ves-subscribed-notifications-deny-read']/"
       "comment"] = "fm-pm o-ran-ves-subscribed-notifications --- (1/2)";

  //    dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ves-subscribed-notifications-deny-exec']/name"]
  //= "fm-pm-o-ran-ves-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ves-subscribed-notifications-deny-exec']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ves-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ves-subscribed-notifications-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='fm-pm-rules']/"
       "rule[name='fm-pm-o-ran-ves-subscribed-notifications-deny-exec']/"
       "comment"] = "fm-pm o-ran-ves-subscribed-notifications --- (2/2)";

  if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfAcmHandler::addSwmRules() {
  std::map<std::string, std::string> dataCfg;

  dataCfg["rule-list[name='swm-rules']/name"] = "swm-rules";
  dataCfg["rule-list[name='swm-rules']/group"] = "swm";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-read']/name"]
  //= "swm-iana-hardware-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-read']/"
       "module-name"] = "iana-hardware";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-read']/"
       "comment"] = "swm iana-hardware --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-exec']/name"]
  //= "swm-iana-hardware-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-exec']/"
       "module-name"] = "iana-hardware";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-exec']/"
       "comment"] = "swm iana-hardware --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-read']/name"]
  //= "swm-ietf-hardware-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-read']/"
       "module-name"] = "ietf-hardware";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-read']/"
       "comment"] = "swm ietf-hardware --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-exec']/name"]
  //= "swm-ietf-hardware-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-exec']/"
       "module-name"] = "ietf-hardware";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-exec']/"
       "comment"] = "swm ietf-hardware --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-read']/name"]
  //= "swm-ietf-interfaces-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-read']/"
       "module-name"] = "ietf-interfaces";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-read']/"
       "comment"] = "swm ietf-interfaces --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-exec']/name"]
  //= "swm-ietf-interfaces-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-exec']/"
       "module-name"] = "ietf-interfaces";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-exec']/"
       "comment"] = "swm ietf-interfaces --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-read']/name"]
  //= "swm-ietf-ip-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-read']/"
       "module-name"] = "ietf-ip";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-read']/"
       "comment"] = "swm ietf-ip --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-exec']/name"]
  //= "swm-ietf-ip-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-exec']/"
       "module-name"] = "ietf-ip";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-exec']/"
       "comment"] = "swm ietf-ip --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-acm']/name"]
  //= "swm-ietf-netconf-acm" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-acm']/"
       "module-name"] = "ietf-netconf-acm";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-acm']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-acm']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-acm']/"
       "comment"] = "swm ietf-netconf-acm R--";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-notifications']/name"]
  //= "swm-ietf-netconf-notifications" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-netconf-notifications']/module-name"] =
          "ietf-netconf-notifications";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-netconf-notifications']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-netconf-notifications']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-netconf-notifications']/comment"] =
          "swm ietf-netconf-notifications --X";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-subscribed-notifications-deny-read']/name"]
  //= "swm-ietf-subscribed-notifications-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-subscribed-notifications-deny-read']/module-name"] =
          "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-subscribed-notifications-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-subscribed-notifications-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-subscribed-notifications-deny-read']/comment"] =
          "swm ietf-subscribed-notifications --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-subscribed-notifications-deny-exec']/name"]
  //= "swm-ietf-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-subscribed-notifications-deny-exec']/module-name"] =
          "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-subscribed-notifications-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-ietf-subscribed-notifications-deny-exec']/comment"] =
          "swm ietf-subscribed-notifications --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-read']/name"]
  //= "swm-o-ran-ald-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-read']/"
       "module-name"] = "o-ran-ald";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-read']/"
       "comment"] = "swm o-ran-ald --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-exec']/name"]
  //= "swm-o-ran-ald-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-exec']/"
       "module-name"] = "o-ran-ald";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-exec']/"
       "comment"] = "swm o-ran-ald --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-read']/name"]
  //= "swm-o-ran-ald-port-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-read']/"
       "module-name"] = "o-ran-ald-port";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-read']/"
       "comment"] = "swm o-ran-ald-port --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-exec']/name"]
  //= "swm-o-ran-ald-port-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-exec']/"
       "module-name"] = "o-ran-ald-port";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-exec']/"
       "comment"] = "swm o-ran-ald-port --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-read']/name"]
  //= "swm-o-ran-antenna-calibration-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-antenna-calibration-deny-read']/module-name"] =
          "o-ran-antenna-calibration";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-antenna-calibration-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-antenna-calibration-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-antenna-calibration-deny-read']/comment"] =
          "swm o-ran-antenna-calibration --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-exec']/name"]
  //= "swm-o-ran-antenna-calibration-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-antenna-calibration-deny-exec']/module-name"] =
          "o-ran-antenna-calibration";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-antenna-calibration-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-antenna-calibration-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-antenna-calibration-deny-exec']/comment"] =
          "swm o-ran-antenna-calibration --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-read']/name"]
  //= "swm-o-ran-beamforming-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-beamforming-deny-read']/module-name"] =
          "o-ran-beamforming";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-beamforming-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-beamforming-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-beamforming-deny-read']/comment"] =
          "swm o-ran-beamforming --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-exec']/name"]
  //= "swm-o-ran-beamforming-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-beamforming-deny-exec']/module-name"] =
          "o-ran-beamforming";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-beamforming-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-beamforming-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-beamforming-deny-exec']/comment"] =
          "swm o-ran-beamforming --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-read']/name"]
  //= "swm-o-ran-delay-management-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-delay-management-deny-read']/module-name"] =
          "o-ran-delay-management";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-delay-management-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-delay-management-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-delay-management-deny-read']/comment"] =
          "swm o-ran-delay-management --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-exec']/name"]
  //= "swm-o-ran-delay-management-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-delay-management-deny-exec']/module-name"] =
          "o-ran-delay-management";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-delay-management-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-delay-management-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-delay-management-deny-exec']/comment"] =
          "swm o-ran-delay-management --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-read']/name"]
  //= "swm-o-ran-dhcp-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-read']/"
       "module-name"] = "o-ran-dhcp";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-read']/"
       "comment"] = "swm o-ran-dhcp --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-exec']/name"]
  //= "swm-o-ran-dhcp-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-exec']/"
       "module-name"] = "o-ran-dhcp";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-exec']/"
       "comment"] = "swm o-ran-dhcp --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-read']/name"]
  //= "swm-o-ran-ecpri-delay-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ecpri-delay-deny-read']/module-name"] =
          "o-ran-ecpri-delay";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ecpri-delay-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ecpri-delay-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ecpri-delay-deny-read']/comment"] =
          "swm o-ran-ecpri-delay --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-exec']/name"]
  //= "swm-o-ran-ecpri-delay-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ecpri-delay-deny-exec']/module-name"] =
          "o-ran-ecpri-delay";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ecpri-delay-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ecpri-delay-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ecpri-delay-deny-exec']/comment"] =
          "swm o-ran-ecpri-delay --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ethernet-forwarding-deny-read']/name"]
  //= "swm-o-ran-ethernet-forwarding-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ethernet-forwarding-deny-read']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ethernet-forwarding-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ethernet-forwarding-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ethernet-forwarding-deny-read']/comment"] =
          "swm o-ran-ethernet-forwarding --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ethernet-forwarding-deny-exec']/name"]
  //= "swm-o-ran-ethernet-forwarding-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ethernet-forwarding-deny-exec']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ethernet-forwarding-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ethernet-forwarding-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ethernet-forwarding-deny-exec']/comment"] =
          "swm o-ran-ethernet-forwarding --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-read']/name"]
  //= "swm-o-ran-externalio-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-externalio-deny-read']/module-name"] =
          "o-ran-externalio";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-externalio-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-externalio-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-externalio-deny-read']/comment"] =
          "swm o-ran-externalio --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-exec']/name"]
  //= "swm-o-ran-externalio-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-externalio-deny-exec']/module-name"] =
          "o-ran-externalio";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-externalio-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-externalio-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-externalio-deny-exec']/comment"] =
          "swm o-ran-externalio --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-read']/name"]
  //= "swm-o-ran-fan-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-read']/"
       "module-name"] = "o-ran-fan";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-read']/"
       "comment"] = "swm o-ran-fan --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-exec']/name"]
  //= "swm-o-ran-fan-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-exec']/"
       "module-name"] = "o-ran-fan";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-exec']/"
       "comment"] = "swm o-ran-fan --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-read']/name"]
  //= "swm-o-ran-file-management-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-file-management-deny-read']/module-name"] =
          "o-ran-file-management";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-file-management-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-file-management-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-file-management-deny-read']/comment"] =
          "swm o-ran-file-management --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-exec']/name"]
  //= "swm-o-ran-file-management-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-file-management-deny-exec']/module-name"] =
          "o-ran-file-management";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-file-management-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-file-management-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-file-management-deny-exec']/comment"] =
          "swm o-ran-file-management --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-read']/name"]
  //= "swm-o-ran-fm-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-read']/"
       "module-name"] = "o-ran-fm";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-read']/"
       "comment"] = "swm o-ran-fm --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-exec']/name"]
  //= "swm-o-ran-fm-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-exec']/"
       "module-name"] = "o-ran-fm";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-exec']/"
       "comment"] = "swm o-ran-fm --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-read']/name"]
  //= "swm-o-ran-hardware-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-read']/"
       "module-name"] = "o-ran-hardware";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-read']/"
       "comment"] = "swm o-ran-hardware --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-exec']/name"]
  //= "swm-o-ran-hardware-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-exec']/"
       "module-name"] = "o-ran-hardware";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-exec']/"
       "comment"] = "swm o-ran-hardware --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-read']/name"]
  //= "swm-o-ran-interfaces-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-interfaces-deny-read']/module-name"] =
          "o-ran-interfaces";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-interfaces-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-interfaces-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-interfaces-deny-read']/comment"] =
          "swm o-ran-interfaces --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-exec']/name"]
  //= "swm-o-ran-interfaces-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-interfaces-deny-exec']/module-name"] =
          "o-ran-interfaces";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-interfaces-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-interfaces-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-interfaces-deny-exec']/comment"] =
          "swm o-ran-interfaces --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-read']/name"]
  //= "swm-o-ran-laa-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-read']/"
       "module-name"] = "o-ran-laa";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-read']/"
       "comment"] = "swm o-ran-laa --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-exec']/name"]
  //= "swm-o-ran-laa-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-exec']/"
       "module-name"] = "o-ran-laa";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-exec']/"
       "comment"] = "swm o-ran-laa --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-read']/name"]
  //= "swm-o-ran-laa-operations-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-laa-operations-deny-read']/module-name"] =
          "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-laa-operations-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-laa-operations-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-laa-operations-deny-read']/comment"] =
          "swm o-ran-laa-operations --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-exec']/name"]
  //= "swm-o-ran-laa-operations-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-laa-operations-deny-exec']/module-name"] =
          "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-laa-operations-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-laa-operations-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-laa-operations-deny-exec']/comment"] =
          "swm o-ran-laa-operations --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-read']/name"]
  //= "swm-o-ran-lbm-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-read']/"
       "module-name"] = "o-ran-lbm";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-read']/"
       "comment"] = "swm o-ran-lbm --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-exec']/name"]
  //= "swm-o-ran-lbm-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-exec']/"
       "module-name"] = "o-ran-lbm";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-exec']/"
       "comment"] = "swm o-ran-lbm --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-read']/name"]
  //= "swm-o-ran-module-cap-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-module-cap-deny-read']/module-name"] =
          "o-ran-module-cap";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-module-cap-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-module-cap-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-module-cap-deny-read']/comment"] =
          "swm o-ran-module-cap --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-exec']/name"]
  //= "swm-o-ran-module-cap-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-module-cap-deny-exec']/module-name"] =
          "o-ran-module-cap";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-module-cap-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-module-cap-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-module-cap-deny-exec']/comment"] =
          "swm o-ran-module-cap --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-read']/name"]
  //= "swm-o-ran-mplane-int-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-mplane-int-deny-read']/module-name"] =
          "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-mplane-int-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-mplane-int-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-mplane-int-deny-read']/comment"] =
          "swm o-ran-mplane-int --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-exec']/name"]
  //= "swm-o-ran-mplane-int-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-mplane-int-deny-exec']/module-name"] =
          "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-mplane-int-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-mplane-int-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-mplane-int-deny-exec']/comment"] =
          "swm o-ran-mplane-int --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-read']/name"]
  //= "swm-o-ran-operations-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-operations-deny-read']/module-name"] =
          "o-ran-operations";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-operations-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-operations-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-operations-deny-read']/comment"] =
          "swm o-ran-operations --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-exec']/name"]
  //= "swm-o-ran-operations-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-operations-deny-exec']/module-name"] =
          "o-ran-operations";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-operations-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-operations-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-operations-deny-exec']/comment"] =
          "swm o-ran-operations --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-read']/name"]
  //= "swm-o-ran-performance-management-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-performance-management-deny-read']/module-name"] =
          "o-ran-performance-management";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-performance-management-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-performance-management-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-performance-management-deny-read']/comment"] =
          "swm o-ran-performance-management --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-exec']/name"]
  //= "swm-o-ran-performance-management-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-performance-management-deny-exec']/module-name"] =
          "o-ran-performance-management";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-performance-management-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-performance-management-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-performance-management-deny-exec']/comment"] =
          "swm o-ran-performance-management --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-read']/name"]
  //= "swm-o-ran-processing-element-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-processing-element-deny-read']/module-name"] =
          "o-ran-processing-element";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-processing-element-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-processing-element-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-processing-element-deny-read']/comment"] =
          "swm o-ran-processing-element --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-exec']/name"]
  //= "swm-o-ran-processing-element-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-processing-element-deny-exec']/module-name"] =
          "o-ran-processing-element";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-processing-element-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-processing-element-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-processing-element-deny-exec']/comment"] =
          "swm o-ran-processing-element --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-shared-cell-deny-read']/name"]
  //= "swm-o-ran-shared-cell-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-shared-cell-deny-read']/module-name"] =
          "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-shared-cell-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-shared-cell-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-shared-cell-deny-read']/comment"] =
          "swm o-ran-shared-cell --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-shared-cell-deny-exec']/name"]
  //= "swm-o-ran-shared-cell-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-shared-cell-deny-exec']/module-name"] =
          "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-shared-cell-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-shared-cell-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-shared-cell-deny-exec']/comment"] =
          "swm o-ran-shared-cell --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-read']/name"]
  //= "swm-o-ran-supervision-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-supervision-deny-read']/module-name"] =
          "o-ran-supervision";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-supervision-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-supervision-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-supervision-deny-read']/comment"] =
          "swm o-ran-supervision --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-exec']/name"]
  //= "swm-o-ran-supervision-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-supervision-deny-exec']/module-name"] =
          "o-ran-supervision";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-supervision-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-supervision-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-supervision-deny-exec']/comment"] =
          "swm o-ran-supervision --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-read']/name"]
  //= "swm-o-ran-sync-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-read']/"
       "module-name"] = "o-ran-sync";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-read']/"
       "comment"] = "swm o-ran-sync --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-exec']/name"]
  //= "swm-o-ran-sync-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-exec']/"
       "module-name"] = "o-ran-sync";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-exec']/"
       "comment"] = "swm o-ran-sync --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-read']/name"]
  //= "swm-o-ran-trace-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-read']/"
       "module-name"] = "o-ran-trace";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-read']/"
       "comment"] = "swm o-ran-trace --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-exec']/name"]
  //= "swm-o-ran-trace-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-exec']/"
       "module-name"] = "o-ran-trace";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-exec']/"
       "comment"] = "swm o-ran-trace --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-read']/name"]
  //= "swm-o-ran-transceiver-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-transceiver-deny-read']/module-name"] =
          "o-ran-transceiver";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-transceiver-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-transceiver-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-transceiver-deny-read']/comment"] =
          "swm o-ran-transceiver --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-exec']/name"]
  //= "swm-o-ran-transceiver-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-transceiver-deny-exec']/module-name"] =
          "o-ran-transceiver";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-transceiver-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-transceiver-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-transceiver-deny-exec']/comment"] =
          "swm o-ran-transceiver --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-read']/name"]
  //= "swm-o-ran-troubleshooting-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-troubleshooting-deny-read']/module-name"] =
          "o-ran-troubleshooting";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-troubleshooting-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-troubleshooting-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-troubleshooting-deny-read']/comment"] =
          "swm o-ran-troubleshooting --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-exec']/name"]
  //= "swm-o-ran-troubleshooting-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-troubleshooting-deny-exec']/module-name"] =
          "o-ran-troubleshooting";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-troubleshooting-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-troubleshooting-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-troubleshooting-deny-exec']/comment"] =
          "swm o-ran-troubleshooting --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-read']/name"]
  //= "swm-o-ran-udp-echo-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-read']/"
       "module-name"] = "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-read']/"
       "comment"] = "swm o-ran-udp-echo --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-exec']/name"]
  //= "swm-o-ran-udp-echo-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-exec']/"
       "module-name"] = "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-exec']/"
       "comment"] = "swm o-ran-udp-echo --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-read']/name"]
  //= "swm-o-ran-uplane-conf-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-uplane-conf-deny-read']/module-name"] =
          "o-ran-uplane-conf";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-uplane-conf-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-uplane-conf-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-uplane-conf-deny-read']/comment"] =
          "swm o-ran-uplane-conf --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-exec']/name"]
  //= "swm-o-ran-uplane-conf-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-uplane-conf-deny-exec']/module-name"] =
          "o-ran-uplane-conf";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-uplane-conf-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-uplane-conf-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-uplane-conf-deny-exec']/comment"] =
          "swm o-ran-uplane-conf --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-read']/name"]
  //= "swm-o-ran-usermgmt-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-read']/"
       "module-name"] = "o-ran-usermgmt";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-read']/"
       "comment"] = "swm o-ran-usermgmt --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-exec']/name"]
  //= "swm-o-ran-usermgmt-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-exec']/"
       "module-name"] = "o-ran-usermgmt";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-exec']/"
       "comment"] = "swm o-ran-usermgmt --- (2/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ves-subscribed-notifications-deny-read']/name"]
  //= "swm-o-ran-ves-subscribed-notifications-deny-read" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ves-subscribed-notifications-deny-read']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ves-subscribed-notifications-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ves-subscribed-notifications-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ves-subscribed-notifications-deny-read']/"
       "comment"] = "swm o-ran-ves-subscribed-notifications --- (1/2)";

  //    dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ves-subscribed-notifications-deny-exec']/name"]
  //= "swm-o-ran-ves-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ves-subscribed-notifications-deny-exec']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ves-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ves-subscribed-notifications-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='swm-rules']/"
       "rule[name='swm-o-ran-ves-subscribed-notifications-deny-exec']/"
       "comment"] = "swm o-ran-ves-subscribed-notifications --- (2/2)";

  if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfAcmHandler::addSmoRules() {
  std::map<std::string, std::string> dataCfg;

  dataCfg["rule-list[name='smo-rules']/name"] = "smo-rules";
  dataCfg["rule-list[name='smo-rules']/group"] = "smo";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-iana-hardware']/name"]
  //= "smo-iana-hardware" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-iana-hardware']/"
       "module-name"] = "iana-hardware";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-iana-hardware']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-iana-hardware']/action"] =
      "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-iana-hardware']/comment"] =
          "smo iana-hardware R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-ietf-hardware']/name"]
  //= "smo-ietf-hardware" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-hardware']/"
       "module-name"] = "ietf-hardware";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-hardware']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-ietf-hardware']/action"] =
      "permit";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-hardware']/comment"] =
          "smo ietf-hardware RWX";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-ietf-interfaces-permit-write']/name"]
  //= "smo-ietf-interfaces-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-interfaces-permit-write']/module-name"] =
          "ietf-interfaces";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-interfaces-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-interfaces-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-interfaces-permit-write']/comment"] =
          "smo ietf-interfaces RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-ietf-interfaces-deny-exec']/name"]
  //= "smo-ietf-interfaces-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-interfaces-deny-exec']/"
       "module-name"] = "ietf-interfaces";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-interfaces-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-interfaces-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-interfaces-deny-exec']/"
       "comment"] = "smo ietf-interfaces RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-ietf-ip-permit-write']/name"]
  //= "smo-ietf-ip-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-ip-permit-write']/"
       "module-name"] = "ietf-ip";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-ip-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-ip-permit-write']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-ip-permit-write']/"
       "comment"] = "smo ietf-ip RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-ietf-ip-deny-exec']/name"]
  //= "smo-ietf-ip-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-ip-deny-exec']/"
       "module-name"] = "ietf-ip";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-ip-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-ip-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-ietf-ip-deny-exec']/"
       "comment"] = "smo ietf-ip RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-ietf-netconf-acm-permit-write']/name"]
  //= "smo-ietf-netconf-acm-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-acm-permit-write']/module-name"] =
          "ietf-netconf-acm";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-acm-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-acm-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-acm-permit-write']/comment"] =
          "smo ietf-netconf-acm RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-ietf-netconf-acm-deny-exec']/name"]
  //= "smo-ietf-netconf-acm-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-acm-deny-exec']/module-name"] =
          "ietf-netconf-acm";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-acm-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-acm-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-acm-deny-exec']/comment"] =
          "smo ietf-netconf-acm RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-ietf-netconf-notifications']/name"]
  //= "smo-ietf-netconf-notifications" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-notifications']/module-name"] =
          "ietf-netconf-notifications";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-notifications']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-notifications']/action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-netconf-notifications']/comment"] =
          "smo ietf-netconf-notifications --X";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-ietf-subscribed-notifications']/name"]
  //= "smo-ietf-subscribed-notifications" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-subscribed-notifications']/module-name"] =
          "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-subscribed-notifications']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-subscribed-notifications']/action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-ietf-subscribed-notifications']/comment"] =
          "smo ietf-subscribed-notifications RWX";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-ald']/name"] =
  //"smo-o-ran-ald" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-ald']/module-name"] =
          "o-ran-ald";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-ald']/"
       "access-operations"] = "read";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-ald']/action"] =
      "deny";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-ald']/comment"] =
      "smo o-ran-ald --X";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-ald-port']/name"]
  //= "smo-o-ran-ald-port" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-ald-port']/"
       "module-name"] = "o-ran-ald-port";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-ald-port']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-ald-port']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-ald-port']/comment"] =
          "smo o-ran-ald-port RWX";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-antenna-calibration']/name"]
  //= "smo-o-ran-antenna-calibration" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-antenna-calibration']/"
       "module-name"] = "o-ran-antenna-calibration";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-antenna-calibration']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-antenna-calibration']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-antenna-calibration']/"
       "comment"] = "smo o-ran-antenna-calibration R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-beamforming']/name"]
  //= "smo-o-ran-beamforming" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-beamforming']/"
       "module-name"] = "o-ran-beamforming";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-beamforming']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-beamforming']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-beamforming']/"
       "comment"] = "smo o-ran-beamforming R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-delay-management']/name"]
  //= "smo-o-ran-delay-management" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-delay-management']/"
       "module-name"] = "o-ran-delay-management";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-delay-management']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-delay-management']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-delay-management']/"
       "comment"] = "smo o-ran-delay-management R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-dhcp']/name"]
  //= "smo-o-ran-dhcp" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-dhcp']/module-name"] =
          "o-ran-dhcp";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-dhcp']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-dhcp']/action"] =
      "deny";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-dhcp']/comment"] =
      "smo o-ran-dhcp R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-ecpri-delay']/name"]
  //= "smo-o-ran-ecpri-delay" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-ecpri-delay']/"
       "module-name"] = "o-ran-ecpri-delay";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-ecpri-delay']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-ecpri-delay']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-ecpri-delay']/"
       "comment"] = "smo o-ran-ecpri-delay R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-ethernet-forwarding-permit-write']/name"]
  //= "smo-o-ran-ethernet-forwarding-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ethernet-forwarding-permit-write']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ethernet-forwarding-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ethernet-forwarding-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ethernet-forwarding-permit-write']/comment"] =
          "smo o-ran-ethernet-forwarding RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-ethernet-forwarding-deny-exec']/name"]
  //= "smo-o-ran-ethernet-forwarding-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ethernet-forwarding-deny-exec']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ethernet-forwarding-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ethernet-forwarding-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ethernet-forwarding-deny-exec']/comment"] =
          "smo o-ran-ethernet-forwarding RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-externalio']/name"]
  //= "smo-o-ran-externalio" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-externalio']/"
       "module-name"] = "o-ran-externalio";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-externalio']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-externalio']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-externalio']/"
       "comment"] = "smo o-ran-externalio RWX";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-fan']/name"] =
  //"smo-o-ran-fan" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-fan']/module-name"] =
          "o-ran-fan";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-fan']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-fan']/action"] =
      "deny";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-fan']/comment"] =
      "smo o-ran-fan R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-file-management']/name"]
  //= "smo-o-ran-file-management" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-file-management']/"
       "module-name"] = "o-ran-file-management";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-file-management']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-file-management']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-file-management']/"
       "comment"] = "smo o-ran-file-management --X";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-hardware-permit-write']/name"]
  //= "smo-o-ran-hardware-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-hardware-permit-write']/module-name"] =
          "o-ran-hardware";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-hardware-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-hardware-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-hardware-permit-write']/comment"] =
          "smo o-ran-hardware RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-hardware-deny-exec']/name"]
  //= "smo-o-ran-hardware-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-hardware-deny-exec']/"
       "module-name"] = "o-ran-hardware";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-hardware-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-hardware-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-hardware-deny-exec']/"
       "comment"] = "smo o-ran-hardware RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-interfaces']/name"]
  //= "smo-o-ran-interfaces" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-interfaces']/"
       "module-name"] = "o-ran-interfaces";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-interfaces']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-interfaces']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-interfaces']/"
       "comment"] = "smo o-ran-interfaces RWX";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-laa']/name"] =
  //"smo-o-ran-laa" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-laa']/module-name"] =
          "o-ran-laa";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-laa']/"
       "access-operations"] = "exec";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-laa']/action"] =
      "deny";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-laa']/comment"] =
      "smo o-ran-laa R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-laa-operations-deny-read']/name"]
  //= "smo-o-ran-laa-operations-deny-read" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-laa-operations-deny-read']/module-name"] =
          "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-laa-operations-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-laa-operations-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-laa-operations-deny-read']/comment"] =
          "smo o-ran-laa-operations --- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-laa-operations-deny-exec']/name"]
  //= "smo-o-ran-laa-operations-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-laa-operations-deny-exec']/module-name"] =
          "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-laa-operations-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-laa-operations-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-laa-operations-deny-exec']/comment"] =
          "smo o-ran-laa-operations --- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-lbm-permit-write']/name"]
  //= "smo-o-ran-lbm-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-lbm-permit-write']/"
       "module-name"] = "o-ran-lbm";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-lbm-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-lbm-permit-write']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-lbm-permit-write']/"
       "comment"] = "smo o-ran-lbm RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-lbm-deny-exec']/name"]
  //= "smo-o-ran-lbm-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-lbm-deny-exec']/"
       "module-name"] = "o-ran-lbm";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-lbm-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-lbm-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-lbm-deny-exec']/"
       "comment"] = "smo o-ran-lbm RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-module-cap']/name"]
  //= "smo-o-ran-module-cap" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-module-cap']/"
       "module-name"] = "o-ran-module-cap";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-module-cap']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-module-cap']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-module-cap']/"
       "comment"] = "smo o-ran-module-cap R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-mplane-int-permit-write']/name"]
  //= "smo-o-ran-mplane-int-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-mplane-int-permit-write']/module-name"] =
          "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-mplane-int-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-mplane-int-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-mplane-int-permit-write']/comment"] =
          "smo o-ran-mplane-int RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-mplane-int-deny-exec']/name"]
  //= "smo-o-ran-mplane-int-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-mplane-int-deny-exec']/module-name"] =
          "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-mplane-int-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-mplane-int-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-mplane-int-deny-exec']/comment"] =
          "smo o-ran-mplane-int RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-operations']/name"]
  //= "smo-o-ran-operations" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-operations']/"
       "module-name"] = "o-ran-operations";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-operations']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-operations']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-operations']/"
       "comment"] = "smo o-ran-operations RWX";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-performance-management']/name"]
  //= "smo-o-ran-performance-management" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-performance-management']/module-name"] =
          "o-ran-performance-management";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-performance-management']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-performance-management']/action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-performance-management']/comment"] =
          "smo o-ran-performance-management RWX";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-processing-element-permit-write']/name"]
  //= "smo-o-ran-processing-element-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-processing-element-permit-write']/module-name"] =
          "o-ran-processing-element";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-processing-element-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-processing-element-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-processing-element-permit-write']/comment"] =
          "smo o-ran-processing-element RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-processing-element-deny-exec']/name"]
  //= "smo-o-ran-processing-element-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-processing-element-deny-exec']/module-name"] =
          "o-ran-processing-element";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-processing-element-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-processing-element-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-processing-element-deny-exec']/comment"] =
          "smo o-ran-processing-element RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-shared-cell']/name"]
  //= "smo-o-ran-shared-cell" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-shared-cell']/"
       "module-name"] = "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-shared-cell']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-shared-cell']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-shared-cell']/"
       "comment"] = "smo o-ran-shared-cell R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-supervision-permit-write']/name"]
  //= "smo-o-ran-supervision-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-supervision-permit-write']/module-name"] =
          "o-ran-supervision";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-supervision-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-supervision-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-supervision-permit-write']/comment"] =
          "smo o-ran-supervision RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-supervision-deny-exec']/name"]
  //= "smo-o-ran-supervision-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-supervision-deny-exec']/module-name"] =
          "o-ran-supervision";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-supervision-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-supervision-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-supervision-deny-exec']/comment"] =
          "smo o-ran-supervision RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-sync']/name"]
  //= "smo-o-ran-sync" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-sync']/module-name"] =
          "o-ran-sync";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-sync']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-sync']/action"] =
      "permit";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-sync']/comment"] =
      "smo o-ran-sync RWX";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-trace']/name"]
  //= "smo-o-ran-trace" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-trace']/module-name"] =
          "o-ran-trace";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-trace']/"
       "access-operations"] = "read";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-trace']/action"] =
      "deny";
  dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-trace']/comment"] =
      "smo o-ran-trace --X";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-transceiver-permit-write']/name"]
  //= "smo-o-ran-transceiver-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-transceiver-permit-write']/module-name"] =
          "o-ran-transceiver";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-transceiver-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-transceiver-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-transceiver-permit-write']/comment"] =
          "smo o-ran-transceiver RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-transceiver-deny-exec']/name"]
  //= "smo-o-ran-transceiver-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-transceiver-deny-exec']/module-name"] =
          "o-ran-transceiver";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-transceiver-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-transceiver-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-transceiver-deny-exec']/comment"] =
          "smo o-ran-transceiver RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-troubleshooting']/name"]
  //= "smo-o-ran-troubleshooting" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-troubleshooting']/"
       "module-name"] = "o-ran-troubleshooting";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-troubleshooting']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-troubleshooting']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-troubleshooting']/"
       "comment"] = "smo o-ran-troubleshooting --X";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-udp-echo-permit-write']/name"]
  //= "smo-o-ran-udp-echo-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-udp-echo-permit-write']/module-name"] =
          "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-udp-echo-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-udp-echo-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-udp-echo-permit-write']/comment"] =
          "smo o-ran-udp-echo RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-udp-echo-deny-exec']/name"]
  //= "smo-o-ran-udp-echo-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-udp-echo-deny-exec']/"
       "module-name"] = "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-udp-echo-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-udp-echo-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-udp-echo-deny-exec']/"
       "comment"] = "smo o-ran-udp-echo RW- (2/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-uplane-conf']/name"]
  //= "smo-o-ran-uplane-conf" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-uplane-conf']/"
       "module-name"] = "o-ran-uplane-conf";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-uplane-conf']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-uplane-conf']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-uplane-conf']/"
       "comment"] = "smo o-ran-uplane-conf R--";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-usermgmt']/name"]
  //= "smo-o-ran-usermgmt" ;
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-usermgmt']/"
       "module-name"] = "o-ran-usermgmt";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-usermgmt']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-usermgmt']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='smo-rules']/rule[name='smo-o-ran-usermgmt']/comment"] =
          "smo o-ran-usermgmt RWX";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-ves-subscribed-notifications-permit-write']/name"]
  //= "smo-o-ran-ves-subscribed-notifications-permit-write" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ves-subscribed-notifications-permit-write']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ves-subscribed-notifications-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ves-subscribed-notifications-permit-write']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ves-subscribed-notifications-permit-write']/"
       "comment"] = "smo o-ran-ves-subscribed-notifications RW- (1/2)";

  //    dataCfg["rule-list[name='smo-rules']/rule[name='smo-o-ran-ves-subscribed-notifications-deny-exec']/name"]
  //= "smo-o-ran-ves-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ves-subscribed-notifications-deny-exec']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ves-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ves-subscribed-notifications-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='smo-rules']/"
       "rule[name='smo-o-ran-ves-subscribed-notifications-deny-exec']/"
       "comment"] = "smo o-ran-ves-subscribed-notifications RW- (2/2)";

  if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfAcmHandler::addHybridoduRules() {
  std::map<std::string, std::string> dataCfg;

  dataCfg["rule-list[name='hybrid-odu-rules']/name"] = "hybrid-odu-rules";
  dataCfg["rule-list[name='hybrid-odu-rules']/group"] = "hybrid-odu";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-iana-hardware']/name"]
  //= "hybrid-odu-iana-hardware" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-iana-hardware']/module-name"] = "iana-hardware";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-iana-hardware']/access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-iana-hardware']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-iana-hardware']/comment"] =
          "hybrid-odu iana-hardware R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-interfaces']/name"]
  //= "hybrid-odu-ietf-interfaces" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-interfaces']/module-name"] =
          "ietf-interfaces";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-interfaces']/access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-interfaces']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-interfaces']/comment"] =
          "hybrid-odu ietf-interfaces R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-ip']/name"]
  //= "hybrid-odu-ietf-ip" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-ip']/"
       "module-name"] = "ietf-ip";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-ip']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-ip']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-ip']/"
       "comment"] = "hybrid-odu ietf-ip R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-netconf-acm-permit-write']/name"]
  //= "hybrid-odu-ietf-netconf-acm-permit-write" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-acm-permit-write']/module-name"] =
          "ietf-netconf-acm";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-acm-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-acm-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-acm-permit-write']/comment"] =
          "hybrid-odu ietf-netconf-acm RW- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-netconf-acm-deny-exec']/name"]
  //= "hybrid-odu-ietf-netconf-acm-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-acm-deny-exec']/module-name"] =
          "ietf-netconf-acm";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-acm-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-acm-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-acm-deny-exec']/comment"] =
          "hybrid-odu ietf-netconf-acm RW- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-netconf-notifications']/name"]
  //= "hybrid-odu-ietf-netconf-notifications" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-notifications']/module-name"] =
          "ietf-netconf-notifications";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-notifications']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-notifications']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-netconf-notifications']/comment"] =
          "hybrid-odu ietf-netconf-notifications --X";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-subscribed-notifications-deny-read']/name"]
  //= "hybrid-odu-ietf-subscribed-notifications-deny-read" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-subscribed-notifications-deny-read']/"
       "module-name"] = "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-subscribed-notifications-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-subscribed-notifications-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-subscribed-notifications-deny-read']/"
       "comment"] = "hybrid-odu ietf-subscribed-notifications --- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-ietf-subscribed-notifications-deny-exec']/name"]
  //= "hybrid-odu-ietf-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-subscribed-notifications-deny-exec']/"
       "module-name"] = "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-subscribed-notifications-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-ietf-subscribed-notifications-deny-exec']/"
       "comment"] = "hybrid-odu ietf-subscribed-notifications --- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ald']/name"]
  //= "hybrid-odu-o-ran-ald" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ald']/"
       "module-name"] = "o-ran-ald";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ald']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ald']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ald']/"
       "comment"] = "hybrid-odu o-ran-ald --X";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ald-port']/name"]
  //= "hybrid-odu-o-ran-ald-port" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ald-port']/module-name"] = "o-ran-ald-port";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ald-port']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ald-port']/action"] = "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ald-port']/comment"] =
          "hybrid-odu o-ran-ald-port RWX";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-antenna-calibration']/name"]
  //= "hybrid-odu-o-ran-antenna-calibration" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-antenna-calibration']/module-name"] =
          "o-ran-antenna-calibration";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-antenna-calibration']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-antenna-calibration']/action"] = "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-antenna-calibration']/comment"] =
          "hybrid-odu o-ran-antenna-calibration RWX";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-delay-management-permit-write']/name"]
  //= "hybrid-odu-o-ran-delay-management-permit-write" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-delay-management-permit-write']/"
       "module-name"] = "o-ran-delay-management";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-delay-management-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-delay-management-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-delay-management-permit-write']/comment"] =
          "hybrid-odu o-ran-delay-management RW- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-delay-management-deny-exec']/name"]
  //= "hybrid-odu-o-ran-delay-management-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-delay-management-deny-exec']/module-name"] =
          "o-ran-delay-management";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-delay-management-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-delay-management-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-delay-management-deny-exec']/comment"] =
          "hybrid-odu o-ran-delay-management RW- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-dhcp']/name"]
  //= "hybrid-odu-o-ran-dhcp" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-dhcp']/"
       "module-name"] = "o-ran-dhcp";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-dhcp']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-dhcp']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-dhcp']/"
       "comment"] = "hybrid-odu o-ran-dhcp R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ecpri-delay-permit-write']/name"]
  //= "hybrid-odu-o-ran-ecpri-delay-permit-write" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ecpri-delay-permit-write']/module-name"] =
          "o-ran-ecpri-delay";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ecpri-delay-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ecpri-delay-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ecpri-delay-permit-write']/comment"] =
          "hybrid-odu o-ran-ecpri-delay RW- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ecpri-delay-deny-exec']/name"]
  //= "hybrid-odu-o-ran-ecpri-delay-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ecpri-delay-deny-exec']/module-name"] =
          "o-ran-ecpri-delay";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ecpri-delay-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ecpri-delay-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ecpri-delay-deny-exec']/comment"] =
          "hybrid-odu o-ran-ecpri-delay RW- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ethernet-forwarding']/name"]
  //= "hybrid-odu-o-ran-ethernet-forwarding" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ethernet-forwarding']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ethernet-forwarding']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ethernet-forwarding']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ethernet-forwarding']/comment"] =
          "hybrid-odu o-ran-ethernet-forwarding R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-externalio']/name"]
  //= "hybrid-odu-o-ran-externalio" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-externalio']/module-name"] =
          "o-ran-externalio";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-externalio']/access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-externalio']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-externalio']/comment"] =
          "hybrid-odu o-ran-externalio R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-fan']/name"]
  //= "hybrid-odu-o-ran-fan" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-fan']/"
       "module-name"] = "o-ran-fan";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-fan']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-fan']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-fan']/"
       "comment"] = "hybrid-odu o-ran-fan R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-file-management-deny-read']/name"]
  //= "hybrid-odu-o-ran-file-management-deny-read" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-file-management-deny-read']/module-name"] =
          "o-ran-file-management";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-file-management-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-file-management-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-file-management-deny-read']/comment"] =
          "hybrid-odu o-ran-file-management --- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-file-management-deny-exec']/name"]
  //= "hybrid-odu-o-ran-file-management-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-file-management-deny-exec']/module-name"] =
          "o-ran-file-management";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-file-management-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-file-management-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-file-management-deny-exec']/comment"] =
          "hybrid-odu o-ran-file-management --- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-hardware']/name"]
  //= "hybrid-odu-o-ran-hardware" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-hardware']/module-name"] = "o-ran-hardware";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-hardware']/access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-hardware']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-hardware']/comment"] =
          "hybrid-odu o-ran-hardware R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-interfaces']/name"]
  //= "hybrid-odu-o-ran-interfaces" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-interfaces']/module-name"] =
          "o-ran-interfaces";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-interfaces']/access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-interfaces']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-interfaces']/comment"] =
          "hybrid-odu o-ran-interfaces R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-laa-permit-write']/name"]
  //= "hybrid-odu-o-ran-laa-permit-write" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-permit-write']/module-name"] =
          "o-ran-laa";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-permit-write']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-permit-write']/action"] = "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-permit-write']/comment"] =
          "hybrid-odu o-ran-laa RW- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-laa-deny-exec']/name"]
  //= "hybrid-odu-o-ran-laa-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-deny-exec']/module-name"] = "o-ran-laa";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-deny-exec']/comment"] =
          "hybrid-odu o-ran-laa RW- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-laa-operations']/name"]
  //= "hybrid-odu-o-ran-laa-operations" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-operations']/module-name"] =
          "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-operations']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-operations']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-laa-operations']/comment"] =
          "hybrid-odu o-ran-laa-operations --X";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-lbm']/name"]
  //= "hybrid-odu-o-ran-lbm" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-lbm']/"
       "module-name"] = "o-ran-lbm";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-lbm']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-lbm']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-lbm']/"
       "comment"] = "hybrid-odu o-ran-lbm R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-module-cap-permit-write']/name"]
  //= "hybrid-odu-o-ran-module-cap-permit-write" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-module-cap-permit-write']/module-name"] =
          "o-ran-module-cap";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-module-cap-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-module-cap-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-module-cap-permit-write']/comment"] =
          "hybrid-odu o-ran-module-cap RW- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-module-cap-deny-exec']/name"]
  //= "hybrid-odu-o-ran-module-cap-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-module-cap-deny-exec']/module-name"] =
          "o-ran-module-cap";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-module-cap-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-module-cap-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-module-cap-deny-exec']/comment"] =
          "hybrid-odu o-ran-module-cap RW- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-mplane-int']/name"]
  //= "hybrid-odu-o-ran-mplane-int" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-mplane-int']/module-name"] =
          "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-mplane-int']/access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-mplane-int']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-mplane-int']/comment"] =
          "hybrid-odu o-ran-mplane-int R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-operations']/name"]
  //= "hybrid-odu-o-ran-operations" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-operations']/module-name"] =
          "o-ran-operations";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-operations']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-operations']/action"] = "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-operations']/comment"] =
          "hybrid-odu o-ran-operations RWX";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-processing-element-permit-write']/name"]
  //= "hybrid-odu-o-ran-processing-element-permit-write" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-processing-element-permit-write']/"
       "module-name"] = "o-ran-processing-element";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-processing-element-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-processing-element-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-processing-element-permit-write']/"
       "comment"] = "hybrid-odu o-ran-processing-element RW- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-processing-element-deny-exec']/name"]
  //= "hybrid-odu-o-ran-processing-element-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-processing-element-deny-exec']/"
       "module-name"] = "o-ran-processing-element";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-processing-element-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-processing-element-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-processing-element-deny-exec']/comment"] =
          "hybrid-odu o-ran-processing-element RW- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-shared-cell-permit-write']/name"]
  //= "hybrid-odu-o-ran-shared-cell-permit-write" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-shared-cell-permit-write']/module-name"] =
          "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-shared-cell-permit-write']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-shared-cell-permit-write']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-shared-cell-permit-write']/comment"] =
          "hybrid-odu o-ran-shared-cell RW- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-shared-cell-deny-exec']/name"]
  //= "hybrid-odu-o-ran-shared-cell-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-shared-cell-deny-exec']/module-name"] =
          "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-shared-cell-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-shared-cell-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-shared-cell-deny-exec']/comment"] =
          "hybrid-odu o-ran-shared-cell RW- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-software-management']/name"]
  //= "hybrid-odu-o-ran-software-management" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-software-management']/module-name"] =
          "o-ran-software-management";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-software-management']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-software-management']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-software-management']/comment"] =
          "hybrid-odu o-ran-software-management R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-supervision']/name"]
  //= "hybrid-odu-o-ran-supervision" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-supervision']/module-name"] =
          "o-ran-supervision";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-supervision']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-supervision']/action"] = "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-supervision']/comment"] =
          "hybrid-odu o-ran-supervision RWX";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-trace-deny-read']/name"]
  //= "hybrid-odu-o-ran-trace-deny-read" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-trace-deny-read']/module-name"] =
          "o-ran-trace";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-trace-deny-read']/access-operations"] =
          "read";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-trace-deny-read']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-trace-deny-read']/comment"] =
          "hybrid-odu o-ran-trace --- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-trace-deny-exec']/name"]
  //= "hybrid-odu-o-ran-trace-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-trace-deny-exec']/module-name"] =
          "o-ran-trace";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-trace-deny-exec']/access-operations"] =
          "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-trace-deny-exec']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-trace-deny-exec']/comment"] =
          "hybrid-odu o-ran-trace --- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-transceiver']/name"]
  //= "hybrid-odu-o-ran-transceiver" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-transceiver']/module-name"] =
          "o-ran-transceiver";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-transceiver']/access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-transceiver']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-transceiver']/comment"] =
          "hybrid-odu o-ran-transceiver R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-troubleshooting-deny-read']/name"]
  //= "hybrid-odu-o-ran-troubleshooting-deny-read" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-troubleshooting-deny-read']/module-name"] =
          "o-ran-troubleshooting";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-troubleshooting-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-troubleshooting-deny-read']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-troubleshooting-deny-read']/comment"] =
          "hybrid-odu o-ran-troubleshooting --- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-troubleshooting-deny-exec']/name"]
  //= "hybrid-odu-o-ran-troubleshooting-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-troubleshooting-deny-exec']/module-name"] =
          "o-ran-troubleshooting";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-troubleshooting-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-troubleshooting-deny-exec']/action"] =
          "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-troubleshooting-deny-exec']/comment"] =
          "hybrid-odu o-ran-troubleshooting --- (2/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-udp-echo']/name"]
  //= "hybrid-odu-o-ran-udp-echo" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-udp-echo']/module-name"] = "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-udp-echo']/access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-udp-echo']/action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-udp-echo']/comment"] =
          "hybrid-odu o-ran-udp-echo R--";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-uplane-conf']/name"]
  //= "hybrid-odu-o-ran-uplane-conf" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-uplane-conf']/module-name"] =
          "o-ran-uplane-conf";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-uplane-conf']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-uplane-conf']/action"] = "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-uplane-conf']/comment"] =
          "hybrid-odu o-ran-uplane-conf RWX";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-usermgmt']/name"]
  //= "hybrid-odu-o-ran-usermgmt" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-usermgmt']/module-name"] = "o-ran-usermgmt";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-usermgmt']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-usermgmt']/action"] = "permit";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-usermgmt']/comment"] =
          "hybrid-odu o-ran-usermgmt RWX";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ves-subscribed-notifications-deny-read']/name"]
  //= "hybrid-odu-o-ran-ves-subscribed-notifications-deny-read" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ves-subscribed-notifications-deny-read']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ves-subscribed-notifications-deny-read']/"
       "access-operations"] = "read";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ves-subscribed-notifications-deny-read']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ves-subscribed-notifications-deny-read']/"
       "comment"] = "hybrid-odu o-ran-ves-subscribed-notifications --- (1/2)";

  //    dataCfg["rule-list[name='hybrid-odu-rules']/rule[name='hybrid-odu-o-ran-ves-subscribed-notifications-deny-exec']/name"]
  //= "hybrid-odu-o-ran-ves-subscribed-notifications-deny-exec" ;
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ves-subscribed-notifications-deny-exec']/"
       "module-name"] = "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ves-subscribed-notifications-deny-exec']/"
       "access-operations"] = "exec";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ves-subscribed-notifications-deny-exec']/"
       "action"] = "deny";
  dataCfg
      ["rule-list[name='hybrid-odu-rules']/"
       "rule[name='hybrid-odu-o-ran-ves-subscribed-notifications-deny-exec']/"
       "comment"] = "hybrid-odu o-ran-ves-subscribed-notifications --- (2/2)";

  if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
IetfNetconfAcmHandler::addRootRules() {
  std::map<std::string, std::string> dataCfg;

  dataCfg["rule-list[name='root-rules']/name"] = "root-rules";
  dataCfg["rule-list[name='root-rules']/group"] = "root";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-iana-hardware']/name"]
  //= "root-iana-hardware" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-iana-hardware']/"
       "module-name"] = "iana-hardware";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-iana-hardware']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-iana-hardware']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-iana-hardware']/comment"] =
          "root iana-hardware RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-hardware']/name"]
  //= "root-ietf-hardware" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-hardware']/"
       "module-name"] = "ietf-hardware";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-hardware']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-hardware']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-hardware']/comment"] =
          "root ietf-hardware RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-interfaces']/name"]
  //= "root-ietf-interfaces" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-interfaces']/"
       "module-name"] = "ietf-interfaces";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-interfaces']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-interfaces']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-interfaces']/"
       "comment"] = "root ietf-interfaces RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-ip']/name"] =
  //"root-ietf-ip" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-ip']/module-name"] =
          "ietf-ip";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-ip']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-ip']/action"] =
      "permit";
  dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-ip']/comment"] =
      "root ietf-ip RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-acm']/name"]
  //= "root-ietf-netconf-acm" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-netconf-acm']/"
       "module-name"] = "ietf-netconf-acm";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-netconf-acm']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-netconf-acm']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-netconf-acm']/"
       "comment"] = "root ietf-netconf-acm RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-monitoring']/name"]
  //= "root-ietf-netconf-monitoring" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-netconf-monitoring']/"
       "module-name"] = "ietf-netconf-monitoring";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-netconf-monitoring']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-netconf-monitoring']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-netconf-monitoring']/"
       "comment"] = "root ietf-netconf-monitoring RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-notifications']/name"]
  //= "root-ietf-netconf-notifications" ;
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-ietf-netconf-notifications']/module-name"] =
          "ietf-netconf-notifications";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-ietf-netconf-notifications']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-ietf-netconf-notifications']/action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-ietf-netconf-notifications']/comment"] =
          "root ietf-netconf-notifications RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-subscribed-notifications']/name"]
  //= "root-ietf-subscribed-notifications" ;
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-ietf-subscribed-notifications']/module-name"] =
          "ietf-subscribed-notifications";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-ietf-subscribed-notifications']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-ietf-subscribed-notifications']/action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-ietf-subscribed-notifications']/comment"] =
          "root ietf-subscribed-notifications RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-yang-library']/name"]
  //= "root-ietf-yang-library" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-yang-library']/"
       "module-name"] = "ietf-yang-library";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-yang-library']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-yang-library']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-ietf-yang-library']/"
       "comment"] = "root ietf-yang-library RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald']/name"]
  //= "root-o-ran-ald" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-ald']/module-name"] =
          "o-ran-ald";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-ald']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald']/action"] =
      "permit";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald']/comment"] =
      "root o-ran-ald RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald-port']/name"]
  //= "root-o-ran-ald-port" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-ald-port']/"
       "module-name"] = "o-ran-ald-port";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-ald-port']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-ald-port']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-ald-port']/"
       "comment"] = "root o-ran-ald-port RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-antenna-calibration']/name"]
  //= "root-o-ran-antenna-calibration" ;
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-antenna-calibration']/module-name"] =
          "o-ran-antenna-calibration";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-antenna-calibration']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-antenna-calibration']/action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-antenna-calibration']/comment"] =
          "root o-ran-antenna-calibration RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-beamforming']/name"]
  //= "root-o-ran-beamforming" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-beamforming']/"
       "module-name"] = "o-ran-beamforming";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-beamforming']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-beamforming']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-beamforming']/"
       "comment"] = "root o-ran-beamforming RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-delay-management']/name"]
  //= "root-o-ran-delay-management" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-delay-management']/"
       "module-name"] = "o-ran-delay-management";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-delay-management']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-delay-management']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-delay-management']/"
       "comment"] = "root o-ran-delay-management RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-dhcp']/name"]
  //= "root-o-ran-dhcp" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-dhcp']/"
       "module-name"] = "o-ran-dhcp";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-dhcp']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-dhcp']/action"] =
      "permit";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-dhcp']/comment"] =
      "root o-ran-dhcp RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ecpri-delay']/name"]
  //= "root-o-ran-ecpri-delay" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-ecpri-delay']/"
       "module-name"] = "o-ran-ecpri-delay";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-ecpri-delay']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-ecpri-delay']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-ecpri-delay']/"
       "comment"] = "root o-ran-ecpri-delay RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ethernet-forwarding']/name"]
  //= "root-o-ran-ethernet-forwarding" ;
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-ethernet-forwarding']/module-name"] =
          "o-ran-ethernet-forwarding";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-ethernet-forwarding']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-ethernet-forwarding']/action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-ethernet-forwarding']/comment"] =
          "root o-ran-ethernet-forwarding RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-externalio']/name"]
  //= "root-o-ran-externalio" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-externalio']/"
       "module-name"] = "o-ran-externalio";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-externalio']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-externalio']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-externalio']/"
       "comment"] = "root o-ran-externalio RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fan']/name"]
  //= "root-o-ran-fan" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-fan']/module-name"] =
          "o-ran-fan";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-fan']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fan']/action"] =
      "permit";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fan']/comment"] =
      "root o-ran-fan RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-file-management']/name"]
  //= "root-o-ran-file-management" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-file-management']/"
       "module-name"] = "o-ran-file-management";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-file-management']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-file-management']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-file-management']/"
       "comment"] = "root o-ran-file-management RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fm']/name"]
  //= "root-o-ran-fm" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-fm']/module-name"] =
          "o-ran-fm";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-fm']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fm']/action"] =
      "permit";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fm']/comment"] =
      "root o-ran-fm RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-hardware']/name"]
  //= "root-o-ran-hardware" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-hardware']/"
       "module-name"] = "o-ran-hardware";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-hardware']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-hardware']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-hardware']/"
       "comment"] = "root o-ran-hardware RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-interfaces']/name"]
  //= "root-o-ran-interfaces" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-interfaces']/"
       "module-name"] = "o-ran-interfaces";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-interfaces']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-interfaces']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-interfaces']/"
       "comment"] = "root o-ran-interfaces RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa']/name"]
  //= "root-o-ran-laa" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-laa']/module-name"] =
          "o-ran-laa";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-laa']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa']/action"] =
      "permit";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa']/comment"] =
      "root o-ran-laa RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa-operations']/name"]
  //= "root-o-ran-laa-operations" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-laa-operations']/"
       "module-name"] = "o-ran-laa-operations";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-laa-operations']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-laa-operations']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-laa-operations']/"
       "comment"] = "root o-ran-laa-operations RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-lbm']/name"]
  //= "root-o-ran-lbm" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-lbm']/module-name"] =
          "o-ran-lbm";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-lbm']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-lbm']/action"] =
      "permit";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-lbm']/comment"] =
      "root o-ran-lbm RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-module-cap']/name"]
  //= "root-o-ran-module-cap" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-module-cap']/"
       "module-name"] = "o-ran-module-cap";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-module-cap']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-module-cap']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-module-cap']/"
       "comment"] = "root o-ran-module-cap RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-mplane-int']/name"]
  //= "root-o-ran-mplane-int" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-mplane-int']/"
       "module-name"] = "o-ran-mplane-int";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-mplane-int']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-mplane-int']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-mplane-int']/"
       "comment"] = "root o-ran-mplane-int RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-operations']/name"]
  //= "root-o-ran-operations" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-operations']/"
       "module-name"] = "o-ran-operations";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-operations']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-operations']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-operations']/"
       "comment"] = "root o-ran-operations RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-performance-management']/name"]
  //= "root-o-ran-performance-management" ;
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-performance-management']/module-name"] =
          "o-ran-performance-management";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-performance-management']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-performance-management']/action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-performance-management']/comment"] =
          "root o-ran-performance-management RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-processing-element']/name"]
  //= "root-o-ran-processing-element" ;
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-processing-element']/module-name"] =
          "o-ran-processing-element";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-processing-element']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-processing-element']/action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-processing-element']/comment"] =
          "root o-ran-processing-element RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-shared-cell']/name"]
  //= "root-o-ran-shared-cell" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-shared-cell']/"
       "module-name"] = "o-ran-shared-cell";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-shared-cell']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-shared-cell']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-shared-cell']/"
       "comment"] = "root o-ran-shared-cell RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-software-management']/name"]
  //= "root-o-ran-software-management" ;
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-software-management']/module-name"] =
          "o-ran-software-management";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-software-management']/access-operations"] =
          "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-software-management']/action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-software-management']/comment"] =
          "root o-ran-software-management RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-supervision']/name"]
  //= "root-o-ran-supervision" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-supervision']/"
       "module-name"] = "o-ran-supervision";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-supervision']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-supervision']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-supervision']/"
       "comment"] = "root o-ran-supervision RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-sync']/name"]
  //= "root-o-ran-sync" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-sync']/"
       "module-name"] = "o-ran-sync";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-sync']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-sync']/action"] =
      "permit";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-sync']/comment"] =
      "root o-ran-sync RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-trace']/name"]
  //= "root-o-ran-trace" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-trace']/"
       "module-name"] = "o-ran-trace";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-trace']/"
       "access-operations"] = "create update delete";
  dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-trace']/action"] =
      "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-trace']/comment"] =
          "root o-ran-trace RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-transceiver']/name"]
  //= "root-o-ran-transceiver" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-transceiver']/"
       "module-name"] = "o-ran-transceiver";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-transceiver']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-transceiver']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-transceiver']/"
       "comment"] = "root o-ran-transceiver RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-troubleshooting']/name"]
  //= "root-o-ran-troubleshooting" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-troubleshooting']/"
       "module-name"] = "o-ran-troubleshooting";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-troubleshooting']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-troubleshooting']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-troubleshooting']/"
       "comment"] = "root o-ran-troubleshooting RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-udp-echo']/name"]
  //= "root-o-ran-udp-echo" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-udp-echo']/"
       "module-name"] = "o-ran-udp-echo";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-udp-echo']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-udp-echo']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-udp-echo']/"
       "comment"] = "root o-ran-udp-echo RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-uplane-conf']/name"]
  //= "root-o-ran-uplane-conf" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-uplane-conf']/"
       "module-name"] = "o-ran-uplane-conf";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-uplane-conf']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-uplane-conf']/"
       "action"] = "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-uplane-conf']/"
       "comment"] = "root o-ran-uplane-conf RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-usermgmt']/name"]
  //= "root-o-ran-usermgmt" ;
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-usermgmt']/"
       "module-name"] = "o-ran-usermgmt";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-usermgmt']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-usermgmt']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='root-rules']/rule[name='root-o-ran-usermgmt']/"
       "comment"] = "root o-ran-usermgmt RWX";

  //    dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ves-subscribed-notifications']/name"]
  //= "root-o-ran-ves-subscribed-notifications" ;
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-ves-subscribed-notifications']/module-name"] =
          "o-ran-ves-subscribed-notifications";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-ves-subscribed-notifications']/"
       "access-operations"] = "create update delete";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-ves-subscribed-notifications']/action"] =
          "permit";
  dataCfg
      ["rule-list[name='root-rules']/"
       "rule[name='root-o-ran-ves-subscribed-notifications']/comment"] =
          "root o-ran-ves-subscribed-notifications RWX";

  if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
    return false;

  return true;
}
