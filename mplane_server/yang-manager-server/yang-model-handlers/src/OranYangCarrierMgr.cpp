/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranYangCarrierMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <set>

#include "config.h"

#include "OranYangCarrierMgr.h"

using namespace Mplane;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
struct OranYangCarrierMgr::Link {
  Link() : mName(), mEndpointName(), mCarrierName() {}
  Link(
      const std::string& name,
      const std::string& endpoint,
      const std::string& carrierName)
      : mName(name), mEndpointName(endpoint), mCarrierName(carrierName) {}
  ~Link() {}

  void
  merge(std::shared_ptr<Link> rhs) {
    if (!rhs->mEndpointName.empty())
      mEndpointName = rhs->mEndpointName;
    if (!rhs->mCarrierName.empty())
      mCarrierName = rhs->mCarrierName;
  }

  bool
  empty() const {
    if (!mEndpointName.empty())
      return false;
    if (!mCarrierName.empty())
      return false;
    return true;
  }

  void
  show() {
    std::cerr << "LINK[" << mName << "] endpoint=" << mEndpointName
              << " carrier=" << mCarrierName << std::endl;
  }

  std::string mName;
  std::string mEndpointName;
  std::string mCarrierName;
};

//-------------------------------------------------------------------------------------------------------------
namespace {

// Leaves from groupings
const std::vector<std::string> kEndpointSectionCapacityLeaves = {
    "max-control-sections-per-data-section",
    "max-sections-per-symbol",
    "max-sections-per-slot",
    "max-highest-priority-sections-per-slot",
    "max-remasks-per-section-id",
    "max-uplane-section-header-per-symbol",
    "max-uplane-section-header-per-slot"};
const std::vector<std::string> kEndpointBeamCapacityLeaves = {
    "max-beams-per-symbol",
    "max-beams-per-slot",
    "max-beam-updates-per-slot",
    "max-beam-updates-per-symbol"};
const std::vector<std::string> kEndpointPrbCapacityLeaves = {
    "max-prb-per-symbol"};
const std::vector<std::string> kEndpointNumerologyCapacityLeaves = {
    "endpoint-numerology-capacity"};

const std::vector<std::string> kParametersLeaves = {
    "name",
    "number-of-rows",
    "number-of-columns",
    "number-of-array-layers",
    "horizontal-spacing",
    "vertical-spacing",
    "band-number"};
const std::vector<std::string> kParametersNormalVectorDirectionLeaves = {
    "azimuth-angle", "zenith-angle"};
const std::vector<std::string> kParametersLBAEPLeaves = {"x", "y", "z"};
const std::vector<std::string> kParametersPolarisationsLeaves = {
    "p", "polarisation"};

const std::vector<std::string> kSupportForUl = {
    "max-supported-frequency-ul",
    "min-supported-frequency-ul",
    "max-supported-bandwidth-ul",
    "max-num-carriers-ul",
    "max-carrier-bandwidth-ul",
    "min-carrier-bandwidth-ul"};
const std::vector<std::string> kSupportForDl = {
    "max-supported-frequency-dl",
    "min-supported-frequency-dl",
    "max-supported-bandwidth-dl",
    "max-num-carriers-dl",
    "max-carrier-bandwidth-dl",
    "min-carrier-bandwidth-dl"};

} // namespace

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangCarrierMgr>
IYangCarrierMgr::singleton() {
  static std::shared_ptr<IYangCarrierMgr> instance(
      std::make_shared<OranYangCarrierMgr>());
  return instance;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranYangCarrierMgr::OranYangCarrierMgr()
    : YangCarrierMgr(),
      mInitialised(false),
      mRxLinks(),
      mTxLinks(),
      mRxCarriers(),
      mTxCarriers(),
      mConfig(IYangConfig::getConfigSingleton()) {}

//-------------------------------------------------------------------------------------------------------------
OranYangCarrierMgr::~OranYangCarrierMgr() {}

//-------------------------------------------------------------------------------------------------------------
bool
OranYangCarrierMgr::initialise() {
  if (mInitialised)
    return true;

  std::cerr << "OranYangCarrierMgr::initialise()" << std::endl;

  createEndpointTypes();
  createEndpointCapacitySharingGroups();
  createTxArrays();
  createRxArrays();
  createStaticLowLevelTxEndpoints();
  createStaticLowLevelRxEndpoints();
  createRelations();
  createEndpointPrachGroups();
  createSupportedCompressionMethodSets();

  mInitialised = true;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::updateRxLink(
    const std::string& name,
    const std::string& endpoint,
    const std::string& carrierName) {
  std::shared_ptr link(std::make_shared<Link>(name, endpoint, carrierName));

  auto entry(mRxLinks.find(name));
  if (link->empty()) {
    if (entry == mRxLinks.end())
      return;

    mRxLinks.erase(entry);
    return;
  }

  if (entry == mRxLinks.end())
    mRxLinks[name] = link;
  else
    entry->second->merge(link);
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::updateTxLink(
    const std::string& name,
    const std::string& endpoint,
    const std::string& carrierName) {
  std::shared_ptr link(std::make_shared<Link>(name, endpoint, carrierName));

  auto entry(mTxLinks.find(name));
  if (link->empty()) {
    if (entry == mTxLinks.end())
      return;

    mTxLinks.erase(entry);
    return;
  }

  if (entry == mTxLinks.end())
    mTxLinks[name] = link;
  else
    entry->second->merge(link);
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::updateRxCarrier(
    const std::string& carrierName,
    ILeafContainer::LeafFunc stateFunc) {
  // skip if already present
  if (mRxCarriers.find(carrierName) != mRxCarriers.end())
    return;

  // add new carrier -- state data for rx-array-carriers
  std::shared_ptr<ILeafContainer> parent(leafContainer());
  std::shared_ptr<ILeafContainer> arrayCarriers(
      parent->addContainer("rx-array-carriers"));
  arrayCarriers->addLeaf("name", carrierName);
  // TODO: from HAL or build variable?
  // arrayCarriers->addLeaf("duplex-scheme", BUILD_DUPLEX) ;
  arrayCarriers->addLeaf("state", stateFunc);
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::updateTxCarrier(
    const std::string& carrierName,
    ILeafContainer::LeafFunc stateFunc) {
  // skip if already present
  if (mTxCarriers.find(carrierName) != mTxCarriers.end())
    return;

  // add new carrier -- state data for tx-array-carriers
  std::shared_ptr<ILeafContainer> parent(leafContainer());
  std::shared_ptr<ILeafContainer> arrayCarriers(
      parent->addContainer("tx-array-carriers"));
  arrayCarriers->addLeaf("name", carrierName);
  // TODO: from HAL or build variable?
  // arrayCarriers->addLeaf("duplex-scheme", BUILD_DUPLEX) ;
  arrayCarriers->addLeaf("state", stateFunc);
}

//-----------------------------------------------------------------------------
void
OranYangCarrierMgr::updateRxEndpointDynCompConfig(
    const std::string& endpointName,
    const std::string& id,
    const std::string& iqBitwidth,
    const std::string& compressionMethod) {
  std::shared_ptr<dynamic_compression_configuration_t> compConfig;
  auto configs = mRxEndpointDynComps[endpointName];
  int idVal = std::stoi(id);
  auto entry(configs.find(idVal));
  if (entry == configs.end()) {
    compConfig = std::make_shared<dynamic_compression_configuration_t>();
    mRxEndpointDynComps[endpointName][idVal] = compConfig;
  } else {
    compConfig = entry->second;
  }

  compConfig->id = idVal;
  if (!iqBitwidth.empty()) {
    compConfig->iq_bitwidth = std::stoi(iqBitwidth);
  }
  if (!compressionMethod.empty()) {
    compConfig->compression_method =
        std::make_shared<std::string>(compressionMethod)->c_str();
  }

  halmplane_update_rx_endpoint_compression_dyn_config(
      endpointName.c_str(), mRxEndpointDynComps[endpointName][idVal].get());
}

//-----------------------------------------------------------------------------
void
OranYangCarrierMgr::updateTxEndpointDynCompConfig(
    const std::string& endpointName,
    const std::string& id,
    const std::string& iqBitwidth,
    const std::string& compressionMethod) {
  std::shared_ptr<dynamic_compression_configuration_t> compConfig;
  auto configs = mTxEndpointDynComps[endpointName];
  int idVal = std::stoi(id);
  auto entry(configs.find(idVal));
  if (entry == configs.end()) {
    compConfig = std::make_shared<dynamic_compression_configuration_t>();
    mTxEndpointDynComps[endpointName][idVal] = compConfig;
  } else {
    compConfig = entry->second;
  }

  compConfig->id = idVal;
  if (!iqBitwidth.empty()) {
    compConfig->iq_bitwidth = std::stoi(iqBitwidth);
  }
  if (!compressionMethod.empty()) {
    compConfig->compression_method =
        std::make_shared<std::string>(compressionMethod)->c_str();
  }

  halmplane_update_tx_endpoint_compression_dyn_config(
      endpointName.c_str(), mTxEndpointDynComps[endpointName][idVal].get());
}

//-----------------------------------------------------------------------------
void
OranYangCarrierMgr::updateRxEndpointCompression(
    const std::string& endpointName,
    const std::string& iqBitwidth,
    const std::string& compressionType,
    const std::string& compressionFormat,
    const std::string& val1,
    const std::string& val2) {
  std::shared_ptr<compression_t> compression;
  auto entry(mRxEndpointComps.find(endpointName));
  if (entry == mRxEndpointComps.end()) {
    compression = std::make_shared<compression_t>();
    mRxEndpointComps[endpointName] = compression;
  } else {
    compression = entry->second;
  }
  if (!iqBitwidth.empty()) {
    compression->iq_bitwidth = std::stoi(iqBitwidth);
  }
  if (compressionType == "STATIC") {
    compression->compression_type = STATIC;
  } else if (compressionType == "DYNAMIC") {
    compression->compression_type = DYNAMIC;
  }
  if (compressionFormat == "block-floating-point") {
    compression->exponent = std::stoi(val1);
  } else if (compressionFormat == "block-floating-point-selective-re-sending") {
    compression->sres_exponent = std::stoi(val1);
  } else if (compressionFormat == "block-scaling") {
    compression->block_scalar = std::stoi(val1);
  } else if (compressionFormat == "u-law") {
    if (!val1.empty()) {
      compression->comp_bit_width = std::stoi(val1);
    }
    if (!val2.empty()) {
      compression->comp_shift = std::stoi(val2);
    }
  } else if (compressionFormat == "beam-space-compression") {
    if (!val1.empty()) {
      compression->active_beam_space_coeficient_mask = std::stoi(val1);
    }
    if (!val2.empty()) {
      compression->block_scaler = std::stoi(val2);
    }
  } else if (compressionFormat == "modulation-compression") {
    if (!val1.empty()) {
      compression->csf = std::stoi(val1);
    }
    if (!val2.empty()) {
      compression->mod_comp_scaler = std::stoi(val2);
    }
  } else if (
      compressionFormat == "modulation-compression-selective-re-sending") {
    if (!val1.empty()) {
      compression->sres_csf = std::stoi(val1);
    }
    if (!val2.empty()) {
      compression->sres_mod_comp_scaler = std::stoi(val2);
    }
  }

  halmplane_update_rx_endpoint_compression(
      endpointName.c_str(), mRxEndpointComps[endpointName].get());
}

//-----------------------------------------------------------------------------
void
OranYangCarrierMgr::updateTxEndpointCompression(
    const std::string& endpointName,
    const std::string& iqBitwidth,
    const std::string& compressionType,
    const std::string& compressionFormat,
    const std::string& val1,
    const std::string& val2) {
  std::shared_ptr<compression_t> compression;
  auto entry(mTxEndpointComps.find(endpointName));
  if (entry == mTxEndpointComps.end()) {
    compression = std::make_shared<compression_t>();
    mTxEndpointComps[endpointName] = compression;
  } else {
    compression = entry->second;
  }
  if (!iqBitwidth.empty()) {
    compression->iq_bitwidth = std::stoi(iqBitwidth);
  }
  if (compressionType == "STATIC") {
    compression->compression_type = STATIC;
  } else if (compressionType == "DYNAMIC") {
    compression->compression_type = DYNAMIC;
  }
  if (compressionFormat == "block-floating-point") {
    compression->exponent = std::stoi(val1);
  } else if (compressionFormat == "block-floating-point-selective-re-sending") {
    compression->sres_exponent = std::stoi(val1);
  } else if (compressionFormat == "block-scaling") {
    compression->block_scalar = std::stoi(val1);
  } else if (compressionFormat == "u-law") {
    compression->comp_bit_width = std::stoi(val1);
    compression->comp_shift = std::stoi(val2);
  } else if (compressionFormat == "beam-space-compression") {
    compression->active_beam_space_coeficient_mask = std::stoi(val1);
    compression->block_scalar = std::stoi(val2);
  } else if (compressionFormat == "modulation-compression") {
    compression->csf = std::stoi(val1);
    compression->mod_comp_scaler = std::stoi(val2);
  } else if (
      compressionFormat == "modulation-compression-selective-re-sending") {
    compression->sres_csf = std::stoi(val1);
    compression->sres_mod_comp_scaler = std::stoi(val2);
  }

  halmplane_update_tx_endpoint_compression(
      endpointName.c_str(), mTxEndpointComps[endpointName].get());
}

//-----------------------------------------------------------------------------
void
OranYangCarrierMgr::updateRxEndpointEaxc(
    const std::string& endpointName,
    const std::string& oduPortBitmask,
    const std::string& bandSectorBitmask,
    const std::string& ccidBitmask,
    const std::string& ruPortBitmask,
    const std::string& eaxcId) {
  std::shared_ptr<e_axcid_t> eaxc;
  auto entry(mRxEndpointEaxcs.find(endpointName));
  if (entry == mRxEndpointEaxcs.end()) {
    eaxc = std::make_shared<e_axcid_t>();
    mRxEndpointEaxcs[endpointName] = eaxc;
  } else {
    eaxc = entry->second;
  }

  if (!oduPortBitmask.empty()) {
    eaxc->o_du_port_bitmask = std::stoi(oduPortBitmask);
  }
  if (!bandSectorBitmask.empty()) {
    eaxc->band_sector_bitmask = std::stoi(bandSectorBitmask);
  }
  if (!ccidBitmask.empty()) {
    eaxc->ccid_bitmask = std::stoi(ccidBitmask);
  }
  if (!ruPortBitmask.empty()) {
    eaxc->ru_port_bitmask = std::stoi(ruPortBitmask);
  }
  if (!eaxcId.empty()) {
    eaxc->eaxc_id = std::stoi(eaxcId);
  }

  halmplane_update_rx_eaxc(
      endpointName.c_str(), mRxEndpointEaxcs[endpointName].get());
}

//-----------------------------------------------------------------------------
void
OranYangCarrierMgr::updateTxEndpointEaxc(
    const std::string& endpointName,
    const std::string& oduPortBitmask,
    const std::string& bandSectorBitmask,
    const std::string& ccidBitmask,
    const std::string& ruPortBitmask,
    const std::string& eaxcId) {
  std::shared_ptr<e_axcid_t> eaxc;
  auto entry(mTxEndpointEaxcs.find(endpointName));
  if (entry == mTxEndpointEaxcs.end()) {
    eaxc = std::make_shared<e_axcid_t>();
    mTxEndpointEaxcs[endpointName] = eaxc;
  } else {
    eaxc = entry->second;
  }

  if (!oduPortBitmask.empty()) {
    eaxc->o_du_port_bitmask = std::stoi(oduPortBitmask);
  }
  if (!bandSectorBitmask.empty()) {
    eaxc->band_sector_bitmask = std::stoi(bandSectorBitmask);
  }
  if (!ccidBitmask.empty()) {
    eaxc->ccid_bitmask = std::stoi(ccidBitmask);
  }
  if (!ruPortBitmask.empty()) {
    eaxc->ru_port_bitmask = std::stoi(ruPortBitmask);
  }
  if (!eaxcId.empty()) {
    eaxc->eaxc_id = std::stoi(eaxcId);
  }

  halmplane_update_tx_eaxc(
      endpointName.c_str(), mTxEndpointEaxcs[endpointName].get());
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::createEndpointTypes() {
  std::shared_ptr<ILeafContainer> parent(leafContainer());

  auto numEndpointTypes = mConfig->getNumOfListEntries(
      "module-o-ran-uplane-conf/container-user-plane-configuration/"
      "list-endpoint-types");

  std::vector<std::string> endpointLeaves = {
      "id",
      "managed-delay-support",
      "multiple-numerology-supported",
      "max-numerology-change-duration",
  };

  for (int i = 0; i < numEndpointTypes; i++) {
    std::string configPath =
        std::string(
            "module-o-ran-uplane-conf/container-user-plane-configuration/"
            "list-endpoint-types[") +
        std::to_string(i) + "]";

    auto endpointType = parent->addContainer("endpoint-types");
    endpointType->addLeavesFromConfig(endpointLeaves, mConfig, configPath);
    endpointType->addLeavesFromConfig(
        kEndpointSectionCapacityLeaves, mConfig, configPath);
    endpointType->addLeavesFromConfig(
        kEndpointBeamCapacityLeaves, mConfig, configPath);
    endpointType->addLeavesFromConfig(
        kEndpointPrbCapacityLeaves, mConfig, configPath);
    endpointType->addLeavesFromConfig(
        kEndpointNumerologyCapacityLeaves, mConfig, configPath);

    auto numSupSecTypes = mConfig->getNumOfListEntries(
        configPath + "/list-supported-section-types");
    for (int j = 0; j < numSupSecTypes; j++) {
      std::string secConfigPath = configPath +
                                  "/list-supported-section-types[" +
                                  std::to_string(j) + "]";
      auto sectionTypes = endpointType->addContainer("supported-section-types");
      sectionTypes->addLeafFromConfig("section-type", mConfig, secConfigPath);
      sectionTypes->addListLeafFromConfig(
          "supported-section-extensions", mConfig, secConfigPath);
    }

    endpointType->addListLeafFromConfig(
        "supported-frame-structures", mConfig, configPath);
    endpointType->addListLeafFromConfig(
        "prb-capacity-allocation-granularity", mConfig, configPath);
  }
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::createEndpointCapacitySharingGroups() {
  std::shared_ptr<ILeafContainer> parent(leafContainer());

  std::vector<std::string> leaves = {
      "id",
      "max-endpoints",
      "max-managed-delay-endpoints",
      "max-non-managed-delay-endpoints"};

  auto numEndpointCapacitySharingGroups = mConfig->getNumOfListEntries(
      "module-o-ran-uplane-conf/container-user-plane-configuration/"
      "list-endpoint-capacity-sharing-groups");
  for (int i = 0; i < numEndpointCapacitySharingGroups; i++) {
    std::string configPath =
        std::string(
            "module-o-ran-uplane-conf/container-user-plane-configuration/"
            "list-endpoint-capacity-sharing-groups[") +
        std::to_string(i) + "]";

    auto endpointCap = parent->addContainer("endpoint-capacity-sharing-groups");

    endpointCap->addLeavesFromConfig(leaves, mConfig, configPath);
    endpointCap->addLeavesFromConfig(
        kEndpointSectionCapacityLeaves, mConfig, configPath);
    endpointCap->addLeavesFromConfig(
        kEndpointBeamCapacityLeaves, mConfig, configPath);
    endpointCap->addLeavesFromConfig(
        kEndpointPrbCapacityLeaves, mConfig, configPath);
    endpointCap->addLeavesFromConfig(
        kEndpointNumerologyCapacityLeaves, mConfig, configPath);
  }
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::createTxArrays() {
  std::shared_ptr<ILeafContainer> parent(leafContainer());

  std::vector<std::string> txLeaves = {"max-gain", "independent-power-budget"};

  auto numTxArrays = mConfig->getNumOfListEntries(
      "module-o-ran-uplane-conf/container-user-plane-configuration/"
      "list-tx-arrays");
  for (int i = 0; i < numTxArrays; i++) {
    std::string configPath =
        std::string(
            "module-o-ran-uplane-conf/container-user-plane-configuration/"
            "list-tx-arrays[") +
        std::to_string(i) + "]";

    auto txArray = parent->addContainer("tx-arrays");
    createArray(txArray, mConfig, configPath);
    txArray->addLeavesFromConfig(txLeaves, mConfig, configPath);

    auto numCapab =
        mConfig->getNumOfListEntries(configPath + "/list-capabilities");
    for (int j = 0; j < numCapab; j++) {
      auto capabPath =
          configPath + "/list-capabilities[" + std::to_string(j) + "]";
      auto capabilities = txArray->addContainer("capabilities");
      capabilities->addLeavesFromConfig(kSupportForDl, mConfig, capabPath);
      capabilities->addListLeafFromConfig(
          "supported-technology-dl", mConfig, capabPath);
    }
  }
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::createRxArrays() {
  std::shared_ptr<ILeafContainer> parent(leafContainer());

  std::vector<std::string> gainCorrectionLeaves = {"max", "min"};

  auto numRxArrays = mConfig->getNumOfListEntries(
      "module-o-ran-uplane-conf/container-user-plane-configuration/"
      "list-rx-arrays");
  for (int i = 0; i < numRxArrays; i++) {
    std::string configPath =
        std::string(
            "module-o-ran-uplane-conf/container-user-plane-configuration/"
            "list-rx-arrays[") +
        std::to_string(i) + "]";

    auto rxArray = parent->addContainer("rx-arrays");
    createArray(rxArray, mConfig, configPath);

    auto gainCorrection = rxArray->addContainer("gain-correction-range");
    gainCorrection->addLeavesFromConfig(
        gainCorrectionLeaves,
        mConfig,
        configPath + "/container-gain-correction-range");

    auto numCapab =
        mConfig->getNumOfListEntries(configPath + "/list-capabilities");
    for (int j = 0; j < numCapab; j++) {
      auto capabPath =
          configPath + "/list-capabilities[" + std::to_string(j) + "]";
      auto capabilities = rxArray->addContainer("capabilities");
      capabilities->addLeavesFromConfig(kSupportForUl, mConfig, capabPath);
      capabilities->addListLeafFromConfig(
          "supported-technology-ul", mConfig, capabPath);
    }
  }
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::createArray(
    std::shared_ptr<ILeafContainer> array,
    std::shared_ptr<IYangConfig> config,
    const std::string& configPath) {
  array->addLeavesFromConfig(kParametersLeaves, mConfig, configPath);
  auto direction = array->addContainer("normal-vector-direction");
  direction->addLeavesFromConfig(
      kParametersNormalVectorDirectionLeaves,
      mConfig,
      configPath + "/container-normal-vector-direction");
  auto leftmost = array->addContainer("leftmost-bottom-array-element-position");
  leftmost->addLeavesFromConfig(
      kParametersLBAEPLeaves,
      mConfig,
      configPath + "/container-leftmost-bottom-array-element-position");

  auto numPolar =
      mConfig->getNumOfListEntries(configPath + "/list-polarisations");
  for (int i = 0; i < numPolar; i++) {
    auto polarPath =
        configPath + "/list-polarisations[" + std::to_string(i) + "]";
    auto polarisations = array->addContainer("polarisations");
    polarisations->addLeavesFromConfig(
        kParametersPolarisationsLeaves, mConfig, polarPath);
  }
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::createStaticLowLevelTxEndpoints() {
  std::shared_ptr<ILeafContainer> parent(leafContainer());

  auto numEndpoints = mConfig->getNumOfListEntries(
      "module-o-ran-uplane-conf/container-user-plane-configuration/"
      "list-static-low-level-tx-endpoints");

  std::vector<std::string> leaves = {
      "name", "array", "endpoint-type", "tdd-group"};
  std::vector<std::string> listLeaves = {
      "restricted-interfaces", "capacity-sharing-groups"};
  std::vector<std::string> compressionLeaves = {
      "dynamic-compression-supported",
      "realtime-variable-bit-width-supported",
      "supported-compression-set-id"};

  for (int i = 0; i < numEndpoints; i++) {
    std::string configPath =
        std::string(
            "module-o-ran-uplane-conf/container-user-plane-configuration/"
            "list-static-low-level-tx-endpoints[") +
        std::to_string(i) + "]";
    auto endpoint = parent->addContainer("static-low-level-tx-endpoints");
    endpoint->addLeavesFromConfig(leaves, mConfig, configPath);
    endpoint->addListLeavesFromConfig(listLeaves, mConfig, configPath);

    auto compression = endpoint->addContainer("compression");
    compression->addLeavesFromConfig(
        compressionLeaves, mConfig, configPath + "/container-compression");
  }
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::createStaticLowLevelRxEndpoints() {
  std::shared_ptr<ILeafContainer> parent(leafContainer());

  auto numEndpoints = mConfig->getNumOfListEntries(
      "module-o-ran-uplane-conf/container-user-plane-configuration/"
      "list-static-low-level-rx-endpoints");

  std::vector<std::string> leaves = {
      "name",
      "array",
      "endpoint-type",
      "prach-group",
      "static-config-supported",
      "max-prach-patterns",
      "max-srs-patterns",
      "tdd-group"};
  std::vector<std::string> listLeaves = {
      "restricted-interfaces", "capacity-sharing-groups"};
  std::vector<std::string> compressionLeaves = {
      "dynamic-compression-supported",
      "realtime-variable-bit-width-supported",
      "supported-compression-set-id"};

  for (int i = 0; i < numEndpoints; i++) {
    std::string configPath =
        std::string(
            "module-o-ran-uplane-conf/container-user-plane-configuration/"
            "list-static-low-level-rx-endpoints[") +
        std::to_string(i) + "]";
    auto endpoint = parent->addContainer("static-low-level-rx-endpoints");
    endpoint->addLeavesFromConfig(leaves, mConfig, configPath);
    endpoint->addListLeavesFromConfig(listLeaves, mConfig, configPath);

    auto compression = endpoint->addContainer("compression");
    compression->addLeavesFromConfig(
        compressionLeaves, mConfig, configPath + "/container-compression");
  }
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::createRelations() {
  std::shared_ptr<ILeafContainer> parent(leafContainer());

  std::vector<std::string> arrayNames = {"tx-array-name", "rx-array-name"};

  std::vector<std::string> pairsLeaves = {"element-array1", "element-array2"};

  auto numRelations = mConfig->getNumOfListEntries(
      "module-o-ran-uplane-conf/container-user-plane-configuration/"
      "list-relations");
  for (int i = 0; i < numRelations; i++) {
    std::string configPath =
        std::string(
            "module-o-ran-uplane-conf/container-user-plane-configuration/"
            "list-relations[") +
        std::to_string(i) + "]";
    auto relations = parent->addContainer("relations");
    relations->addLeafFromConfig("entity", mConfig, configPath);

    auto array1 = relations->addContainer("array1");
    array1->addLeavesFromConfig(
        arrayNames, mConfig, configPath + "/container-array1");

    auto array2 = relations->addContainer("array2");
    array2->addLeavesFromConfig(
        arrayNames, mConfig, configPath + "/container-array2");

    auto numTypes = mConfig->getNumOfListEntries(configPath + "/list-types");
    for (int j = 0; j < numTypes; j++) {
      std::string typePath =
          configPath + "/list-types[" + std::to_string(j) + "]";
      auto types = relations->addContainer("types");
      types->addLeafFromConfig("relation-type", mConfig, typePath);

      auto numPairs = mConfig->getNumOfListEntries(typePath + "/list-pairs");
      for (int k = 0; k < numPairs; k++) {
        std::string pairPath =
            typePath + "/list-pairs[" + std::to_string(k) + "]";
        auto pairs = types->addContainer("pairs");
        pairs->addLeavesFromConfig(pairsLeaves, mConfig, pairPath);
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::createEndpointPrachGroups() {
  std::shared_ptr<ILeafContainer> parent(leafContainer());

  auto numGroups = mConfig->getNumOfListEntries(
      "module-o-ran-uplane-conf/container-user-plane-configuration/"
      "list-endpoint-prach-group");
  for (int i = 0; i < numGroups; i++) {
    std::string configPath =
        std::string(
            "module-o-ran-uplane-conf/container-user-plane-configuration/"
            "list-endpoint-prach-group[") +
        std::to_string(i) + "]";
    auto group = parent->addContainer("endpoint-prach-group");
    group->addLeafFromConfig("id", mConfig, configPath);
    group->addListLeafFromConfig(
        "supported-prach-preamble-formats", mConfig, configPath);
  }
}

//-------------------------------------------------------------------------------------------------------------
void
OranYangCarrierMgr::createSupportedCompressionMethodSets() {
  std::shared_ptr<ILeafContainer> parent(leafContainer());

  // leaves from cf:compression-parameters (yes some are spelled "scaler")
  std::vector<std::string> compressionLeaves = {
      "iq-bitwidth",
      "exponent",
      "sres-exponent",
      "block-scalar",
      "comp-bit-width",
      "comp-shift",
      "block-scalar",
      "csf",
      "mod-comp-scaler",
      "sres-csf",
      "sres-mod-comp-scaler"};

  auto numSets = mConfig->getNumOfListEntries(
      "module-o-ran-uplane-conf/container-user-plane-configuration/"
      "list-supported-compression-method-sets");
  for (int i = 0; i < numSets; i++) {
    std::string configPath =
        std::string(
            "module-o-ran-uplane-conf/container-user-plane-configuration/"
            "list-supported-compression-method-sets[") +
        std::to_string(i) + "]";
    auto set = parent->addContainer("supported-compression-method-sets");
    set->addLeafFromConfig("id", mConfig, configPath);
    set->addLeavesFromConfig(compressionLeaves, mConfig, configPath);
    // case beam-space-compression, (yes it is spelled "coeficient" in the YANG
    // model)
    set->addListLeafFromConfig(
        "active-beam-space-coeficient-mask", mConfig, configPath);
  }
}
