/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranModuleCapHandler.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <algorithm>
#include <iostream>
#include <string>

#include "stringfunc.hpp"

#include "YangMgrServer.h"
#include "YangParamUtils.h"

#include "OranModuleCapHandler.h"
#include "RadioDatastoreSysrepo.h"

using namespace Mplane;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranModuleCapHandler::OranModuleCapHandler(
    std::shared_ptr<IYangModuleMgr> moduleMgr)
    : YangHandlerSysrepo("o-ran-module-cap", moduleMgr, "OranModuleCapHandler"),
      mCallback(
          std::make_shared<SysrepoGetitemsCallback>(path("module-capability"))),
      mConfig(IYangConfig::getConfigSingleton()) {}

//-------------------------------------------------------------------------------------------------------------
OranModuleCapHandler::~OranModuleCapHandler() {}

//-------------------------------------------------------------------------------------------------------------
bool
OranModuleCapHandler::initialise() {
  // daisychain the initialisations
  if (!this->YangHandlerSysrepo::initialise())
    return false;

  if (!createRuCapabilities()) {
    return false;
  }

  if (!createBandCapabilities()) {
    return false;
  }

  // Register callbacks
  getItemsSubscribe(mCallback->path(), mCallback);

  return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
OranModuleCapHandler::valueChange(
    const std::string& xpath,
    std::shared_ptr<YangParam> oldValue,
    std::shared_ptr<YangParam> newValue) {
  if (oldValue && !newValue) {
    logDebugVerbose(
        "OranModuleCapHandler::valueChange() - %s", oldValue->name().c_str());
  }
  if (newValue) {
    logDebugVerbose(
        "OranModuleCapHandler::valueChange() - %s", newValue->name().c_str());
  }
}

//-------------------------------------------------------------------------------------------------------------
int
OranModuleCapHandler::validate(
    std::shared_ptr<YangParams> params,
    std::shared_ptr<YangParams> deletedParams) {
  return SR_ERR_OK;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
OranModuleCapHandler::createRuCapabilities(void) {
  std::shared_ptr<ILeafContainer> parent(mCallback);

  // Create Ru capability

  //         +--ro ru-capabilities
  //         |  +--ro ru-supported-category enumeration          |  +--ro
  // number-of-ru-ports-ul                                        uint8_t |
  // +--ro number-of-ru-ports-dl                                        uint8_t
  // | +--ro number-of-spatial-streams uint8_t | +--ro max-power-per-pa-antenna
  // decimal64          |
  //+--ro min-power-per-pa-antenna                                     decimal64
  //         |  +--ro fronthaul-split-option uint8_t          |  +--ro
  // format-of-iq-sample                                          container | |
  //+--ro dynamic-compression-supported                             boolean
  //         |    |  +--ro realtime-variable-bit-width-supported boolean
  //       |  |  +--ro compression-method-supported* list |  |  +--ro
  //       variable-bit-width-per-channel-supported                  boolean |
  //       |  +--ro syminc-supported boolean |  |  +--ro
  //       regularization-factor-se-supported                        boolean |
  //       |  +--ro little-endian-supported boolean
  //         |  +--ro ul-mixed-num-required-guard-rbs* [scs-a scs-b]
  //         |    |  +--ro scs-a enumeration          |    |  +--ro scs-b
  //         enumeration          |
  //|  +--ro number-of-guard-rbs-ul                                    uint8_t
  //         |  +--ro dl-mixed-num-required-guard-rbs* [scs-a scs-b]
  //         |    |  +--ro scs-a enumeration          |    |  +--ro scs-b
  //         enumeration          |
  //|  +--ro number-of-guard-rbs-dl                                    uint8_t
  //         |  +--ro energy-saving-by-transmission-blanks boolean          |
  //         +--ro
  // dynamic-transport-delay-management-supported                 boolean |
  // +--ro support-only-unique-ecpri-seqid-per-eaxc                     boolean
  // | +--ro coupling-methods container          |  |
  //+--ro coupling-via-frequency-and-time                           boolean |  |
  //+--ro coupling-via-frequency-and-time-with-priorities           boolean |  |
  //+--ro coupling-via-frequency-and-time-with-priorities-optimized boolean |
  //+--ro ud-comp-len-supported                                        boolean

  auto ruCapability = parent->addContainer("ru-capabilities");
  std::string ruCapPath(
      "module-o-ran-module-cap/container-module-capability/"
      "container-ru-capabilities");

  std::vector<std::string> ruCapLeaves = {
      "ru-supported-category",
      "number-of-ru-ports-ul",
      "number-of-ru-ports-dl",
      "number-of-spatial-streams",
      "max-power-per-pa-antenna",
      "min-power-per-pa-antenna",
      "fronthaul-split-option",
      "energy-saving-by-transmission-blanks",
      "dynamic-transport-delay-management-supported",
      "support-only-unique-ecpri-seqid-per-eaxc",
      "ud-comp-len-supported"};
  ruCapability->addLeavesFromConfig(ruCapLeaves, mConfig, ruCapPath);

  auto iqSampleFormat = ruCapability->addContainer("format-of-iq-sample");
  std::string iqContPath = ruCapPath + "/container-format-of-iq-sample";
  std::vector<std::string> iqSampLeaves = {
      "dynamic-compression-supported",
      "realtime-variable-bit-width-supported",
      "variable-bit-width-per-channel-supported",
      "syminc-supported",
      "regularization-factor-se-supported",
      "little-endian-supported"};
  iqSampleFormat->addLeavesFromConfig(iqSampLeaves, mConfig, iqContPath);

  auto numMethods = mConfig->getNumOfListEntries(
      iqContPath + "/list-compression-method-supported");
  for (int i = 0; i < numMethods; i++) {
    std::string listEntryPath = iqContPath +
                                "/list-compression-method-supported[" +
                                std::to_string(i) + "]";
    auto compressMethod =
        iqSampleFormat->addContainerList("compression-method-supported");
    compressMethod->addLeafFromConfig("iq-bitwidth", mConfig, listEntryPath);
    compressMethod->addLeafFromConfig("exponent", mConfig, listEntryPath);
  }

  std::string ulMixPath = ruCapPath + "/ul-mixed-num-required-guard-rbs";
  auto ulMix = ruCapability->addContainer("ul-mixed-num-required-guard-rbs");
  std::vector<std::string> ulMixLeaves = {
      "scs-a", "scs-b", "number-of-guard-rbs-ul"};
  ulMix->addLeavesFromConfig(ulMixLeaves, mConfig, ulMixPath);

  std::string dlMixPath = ruCapPath + "/dl-mixed-num-required-guard-rbs";
  auto dlMix = ruCapability->addContainer("dl-mixed-num-required-guard-rbs");
  std::vector<std::string> dlMixLeaves = {
      "scs-a", "scs-b", "number-of-guard-rbs-dl"};
  ulMix->addLeavesFromConfig(dlMixLeaves, mConfig, dlMixPath);

  auto coupling = ruCapability->addContainer("coupling-methods");
  std::string couplingPath = ruCapPath + "/container-coupling-methods";
  std::vector<std::string> couplingLeaves = {
      "coupling-via-frequency-and-time",
      "coupling-via-frequency-and-time-with-priorities",
      "coupling-via-frequency-and-time-with-priorities-optimized"};

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
OranModuleCapHandler::createBandCapabilities(void) {
  std::shared_ptr<ILeafContainer> parent(mCallback);

  // Create band capability

  //         +--ro band-capabilities* [band-number]
  //         |  +--ro band-number                                  uint8_t
  //         |  +--ro max-supported-frequency-dl                   uint64_t
  //         |  +--ro min-supported-frequency-dl                   uint64_t
  //         |  +--ro max-supported-bandwidth-dl                   uint64_t
  //         |  +--ro max-num-carriers-dl                          uint32_t
  //         |  +--ro max-carrier-bandwidth-dl                     uint64_t
  //         |  +--ro min-carrier-bandwidth-dl                     uint64_t
  //         |  +--ro max-supported-frequency-ul                   uint64_t
  //         |  +--ro min-supported-frequency-ul                   uint64_t
  //         |  +--ro max-supported-bandwidth-ul                   uint64_t
  //         |  +--ro max-num-carriers-ul                          uint32_t
  //         |  +--ro max-carrier-bandwidth-ul                     uint64_t
  //         |  +--ro min-carrier-bandwidth-ul                     uint64_t
  //         |  +--ro max-num-component-carriers                   uint8_t
  //         |  +--ro max-num-bands                                uint16_t
  //         |  +--ro max-num-sectors                              uint8_t
  //         |  +--ro max-power-per-antenna                        decimal64
  //         |  +--ro min-power-per-antenna                        decimal64
  //         |  +--ro codebook-configuration_ng                    uint8_t
  //         |  +--ro codebook-configuration_n1                    uint8_t
  //         |  +--ro codebook-configuration_n2                    uint8_t

  auto bandCapability = parent->addContainer("band-capabilities");
  std::string bandCapPath(
      "module-o-ran-module-cap/container-module-capability/"
      "container-band-capabilities");

  std::vector<std::string> leaves = {
      "band-number",
      "max-supported-frequency-dl",
      "min-supported-frequency-dl",
      "max-supported-bandwidth-dl",
      "max-num-carriers-dl",
      "max-carrier-bandwidth-dl",
      "min-carrier-bandwidth-dl",
      "max-supported-frequency-ul",
      "min-supported-frequency-ul",
      "max-supported-bandwidth-ul",
      "max-num-carriers-ul",
      "max-carrier-bandwidth-ul",
      "min-carrier-bandwidth-ul",
      "max-num-component-carriers",
      "max-num-bands",
      "max-num-sectors",
      "max-power-per-antenna",
      "min-power-per-antenna",
      "codebook-configuration_ng",
      "codebook-configuration_n1",
      "codebook-configuration_n2"};

  bandCapability->addLeavesFromConfig(leaves, mConfig, bandCapPath);

  return true;
}
