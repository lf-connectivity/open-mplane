/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranUplaneConfHandler.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "SysrepoUtils.h"

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <string>

#include "IYangCarrierMgr.h"
#include "stringfunc.hpp"

#include "YangMgrServer.h"
#include "YangParamUtils.h"

#include "OranUplaneConfHandler.h"
#include "RadioDatastoreSysrepo.h"

using namespace Mplane;

// Global variable used with the state callback wrappers so that a standard
// function pointer can be passed into the HAL. There should never be more than
// one instance of this class anyway.
OranUplaneConfHandler* oranUplaneConfHandlerInstance = NULL;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranUplaneConfHandler::OranUplaneConfHandler(
    std::shared_ptr<IYangModuleMgr> moduleMgr)
    : YangHandlerSysrepo(
          "o-ran-uplane-conf", moduleMgr, "OranUplaneConfHandler"),
      mCallback(std::make_shared<SysrepoGetitemsCallback>(
          path("user-plane-configuration"))),
      mRxCarrierState(),
      mTxCarrierState(),
      mConfig(IYangConfig::getConfigSingleton()) {}

//-------------------------------------------------------------------------------------------------------------
OranUplaneConfHandler::~OranUplaneConfHandler() {}

//-------------------------------------------------------------------------------------------------------------
bool
OranUplaneConfHandler::initialise() {
  // daisychain the initialisations
  if (!this->YangHandlerSysrepo::initialise())
    return false;

  // Set up carrier manager
  auto carrierMgr(IYangCarrierMgr::singleton());
  carrierMgr->setLeafContainer(
      std::dynamic_pointer_cast<ILeafContainer>(mCallback));

  // Register callbacks
  getItemsSubscribe(mCallback->path(), mCallback);
  changeSubscribe();

  // get any initial links
  std::map<std::string, std::map<std::string, std::string>> txlinks(
      getLinks("tx"));
  for (auto entry : txlinks) {
    for (auto value : entry.second) {
      if (value.first == "tx-array-carrier") {
        carrierMgr->updateTxLink(entry.first, "", value.second);
        continue;
      }

      if (value.first == "low-level-tx-endpoint") {
        carrierMgr->updateTxLink(entry.first, value.second, "");
        continue;
      }
    }
  }
  std::map<std::string, std::map<std::string, std::string>> rxlinks(
      getLinks("rx"));
  for (auto entry : rxlinks) {
    for (auto value : entry.second) {
      if (value.first == "rx-array-carrier") {
        carrierMgr->updateRxLink(entry.first, "", value.second);
        continue;
      }

      if (value.first == "low-level-rx-endpoint") {
        carrierMgr->updateRxLink(entry.first, value.second, "");
        continue;
      }
    }
  }

  std::map<std::string, std::map<std::string, std::string>> txcarriers(
      getKeyValues(mCallback->path() + "/tx-array-carriers//."));
  for (auto entry : txcarriers) {
    updateTxCarrier(entry.first);
  }
  std::map<std::string, std::map<std::string, std::string>> rxcarriers(
      getKeyValues(mCallback->path() + "/rx-array-carriers//."));
  for (auto entry : rxcarriers) {
    updateRxCarrier(entry.first);
  }

  oranUplaneConfHandlerInstance = this;

  halmplane_register_rx_carrier_state_cb(
      &Mplane::OranUplaneConfHandler::rxCarrierStateCallbackWrapper);
  halmplane_register_tx_carrier_state_cb(
      &Mplane::OranUplaneConfHandler::txCarrierStateCallbackWrapper);

  return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
OranUplaneConfHandler::valueChange(
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
    value = YangParamUtils::toString(oldValue, error);
    listIndex(oldValue->name(), listName, key, index);
    leaf = leafName(oldValue->name());
    logDebugVerbose(
        "OranUplaneConfHandler::valueChange() - %s", oldValue->name().c_str());
  }
  if (newValue) {
    value = YangParamUtils::toString(newValue, error);
    listIndex(newValue->name(), listName, key, index);
    leaf = leafName(newValue->name());
    logDebugVerbose(
        "OranUplaneConfHandler::valueChange() - %s", newValue->name().c_str());
    // TODO: handle deletions?
    processValue(newValue, leaf, value, xpath);
  }
}

//-------------------------------------------------------------------------------------------------------------
int
OranUplaneConfHandler::validate(
    std::shared_ptr<YangParams> params,
    std::shared_ptr<YangParams> deletedParams) {
  // skip if not changing carrier active state
  std::string error;
  bool active(false);
  for (unsigned i = 0; i < params->getNumParams(); ++i) {
    std::shared_ptr<YangParam> param(params->getParam(i));

    std::string value(YangParamUtils::toString(param, error));
    std::string leaf(leafName(param->name()));

    if (leaf != "active")
      continue;

    if (value != "ACTIVE")
      continue;

    active = true;
    break;
  }

  if (!active)
    return SR_ERR_OK;

  // Need to process the parameters to see if we can make the carrier(s) active
  // NOTE: For simplicity I'm actually applying these values and only doing the
  // validation on the final activate ideally this whole transaction would cause
  // no changes if it's rejected, but that's a shed load more work!
  for (unsigned i = 0; i < params->getNumParams(); ++i) {
    std::shared_ptr<YangParam> param(params->getParam(i));

    std::string leaf(leafName(param->name()));

    if (leaf == "active")
      continue;

    // process value
    std::string value(YangParamUtils::toString(param, error));
    int rc = processValue(param, leaf, value, "");

    if (rc != SR_ERR_OK) {
      return rc;
    }
  }

  // Now just check each active change
  for (unsigned i = 0; i < params->getNumParams(); ++i) {
    std::shared_ptr<YangParam> param(params->getParam(i));

    std::string leaf(leafName(param->name()));

    if (leaf != "active")
      continue;

    // validate active change - without making any change
    std::string value(YangParamUtils::toString(param, error));
    int rc = validateValue(param, leaf, value);

    if (rc != SR_ERR_OK) {
      return rc;
    }
  }

  return SR_ERR_OK;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int
OranUplaneConfHandler::processValue(
    std::shared_ptr<YangParam> param,
    const std::string& leaf,
    const std::string& value,
    const std::string& xpath) {
  std::string error;

  std::string listName;
  std::string key;
  std::string index;
  listIndex(param->name(), listName, key, index);

  if (listName == "low-level-rx-links") {
    std::string endpoint;
    std::string carrierName;

    if (leaf == "low-level-rx-endpoint") {
      endpoint = value;
    }
    if (leaf == "rx-array-carrier") {
      carrierName = value;
    }

    if (endpoint.empty() && carrierName.empty())
      return SR_ERR_INVAL_ARG;

    auto carrierMgr(IYangCarrierMgr::singleton());
    carrierMgr->updateRxLink(index, endpoint, carrierName);

    return SR_ERR_OK;
  }

  if (listName == "low-level-tx-links") {
    std::string endpoint;
    std::string carrierName;

    if (leaf == "low-level-tx-endpoint") {
      endpoint = value;
    }
    if (leaf == "tx-array-carrier") {
      carrierName = value;
    }

    if (endpoint.empty() && carrierName.empty())
      return SR_ERR_INVAL_ARG;

    auto carrierMgr(IYangCarrierMgr::singleton());
    carrierMgr->updateTxLink(index, endpoint, carrierName);

    return SR_ERR_OK;
  }

  // For tx-array-carrier & rx-array-carrier, index == carrier name

  // only interested in array carriers activate/de-activate
  if (listName == "rx-array-carriers") {
    if (leaf == "name") {
      updateRxCarrier(value);
      return SR_ERR_OK;
    }

    // No need to call handleActivate if the leaf is not active
    if (leaf != "active") {
      return SR_ERR_OK;
    }

    // Call the handleActivate only if the carrier is activated or deactivated
    // (transition)
    if (value == "INACTIVE" && mRxCarrierState[index] == "DISABLED") {
      return SR_ERR_OK;
    }

    return handleActivate(param, leaf, value, VALUE_APPLY);
  }

  if (listName == "tx-array-carriers") {
    if (leaf == "name") {
      updateTxCarrier(value);
      return SR_ERR_OK;
    }

    // No need to call handleActivate if the leaf is not active
    if (leaf != "active") {
      return SR_ERR_OK;
    }

    // Call the handleActivate only if the carrier is activated or deactivated
    // (transition)
    if (value == "INACTIVE" && mTxCarrierState[index] == "DISABLED") {
      return SR_ERR_OK;
    }

    return handleActivate(param, leaf, value, VALUE_APPLY);
  }

  if (listName == "low-level-rx-endpoints") {
    std::string endpointName = index;
    if (xpath.find("/compression/") == std::string::npos) {
      handleEaxc(index, leaf, value, true);
    } else if (listIndexN(param->name(), listName, key, index, 2)) {
      // there is another nested list, handle dynamic-compression-configuration
      handleDynCompConfig(endpointName, index, leaf, value, true);
    } else {
      // no nested list, this is a leaf within compression
      handleCompression(index, leaf, value, true);
    }
  }

  if (listName == "low-level-tx-endpoints") {
    std::string endpointName = index;
    if (xpath.find("/compression/") == std::string::npos) {
      handleEaxc(index, leaf, value, false);
    } else if (listIndexN(param->name(), listName, key, index, 2)) {
      // there is another nested list, handle dynamic-compression-configuration
      handleDynCompConfig(endpointName, index, leaf, value, false);
    } else {
      // no nested list, this is a leaf within compression
      handleCompression(index, leaf, value, false);
    }
  }

  return SR_ERR_OK;
}

//-------------------------------------------------------------------------------------------------------------
int
OranUplaneConfHandler::validateValue(
    std::shared_ptr<YangParam> param,
    const std::string& leaf,
    const std::string& value) {
  if (leaf != "active")
    return SR_ERR_OK;

  if (value != "ACTIVE")
    return SR_ERR_OK;

  // activating a carrier
  return handleActivate(param, leaf, value, VALUE_VALIDATE);
}

//-------------------------------------------------------------------------------------------------------------
int
OranUplaneConfHandler::handleActivate(
    std::shared_ptr<YangParam> param,
    const std::string& leaf,
    const std::string& value,
    ValuePhase phase) {
  std::string listName;
  std::string key;
  std::string name;
  listIndex(param->name(), listName, key, name);

  // only interested in array carriers activate/deactivate
  if (listName == "rx-array-carriers") {
    if (leaf != "active") {
      return SR_ERR_OK;
    }

    std::map<std::string, std::shared_ptr<YangParam>> carrierData(
        getArrayCarrier("rx", name));
    uint64_t chbw = paramValUInt64(carrierData, "channel-bandwidth");
    uint64_t center =
        paramValUInt64(carrierData, "center-of-channel-bandwidth");
    double gainCorrection = paramValDecimal64(carrierData, "gain-correction");

    int ret = halmplane_rx_carrier_state_change(
        name.c_str(),
        chbw,
        center,
        gainCorrection,
        value.c_str(),
        phase == VALUE_APPLY);
    if (ret != 0) {
      return SR_ERR_INVAL_ARG;
    }
    // only apply change if we are in the VALUE_APPLY phase
    if (phase != VALUE_APPLY) {
      return SR_ERR_OK;
    }
  }
  if (listName == "tx-array-carriers") {
    if (leaf != "active") {
      return SR_ERR_OK;
    }

    std::map<std::string, std::shared_ptr<YangParam>> carrierData(
        getArrayCarrier("tx", name));
    uint64_t chbw = paramValUInt64(carrierData, "channel-bandwidth");
    uint64_t center =
        paramValUInt64(carrierData, "center-of-channel-bandwidth");
    double gain = paramValDecimal64(carrierData, "gain");

    int ret = halmplane_tx_carrier_state_change(
        name.c_str(), chbw, center, gain, value.c_str(), phase == VALUE_APPLY);
    if (ret != 0) {
      return SR_ERR_INVAL_ARG;
    }
    // only apply change if we are in the VALUE_APPLY phase
    if (phase != VALUE_APPLY) {
      return SR_ERR_OK;
    }
  }

  return SR_ERR_OK;
}

//-----------------------------------------------------------------------------
void
OranUplaneConfHandler::handleEaxc(
    const std::string& endpointName,
    const std::string& leaf,
    const std::string& value,
    bool rx) {
  auto carrierMgr(IYangCarrierMgr::singleton());
  if (rx) {
    if (leaf == "o-du-port-bitmask") {
      carrierMgr->updateRxEndpointEaxc(endpointName, value, "", "", "", "");
    } else if (leaf == "band-sector-bitmask") {
      carrierMgr->updateRxEndpointEaxc(endpointName, "", value, "", "", "");
    } else if (leaf == "ccid-bitmask") {
      carrierMgr->updateRxEndpointEaxc(endpointName, "", "", value, "", "");
    } else if (leaf == "ru-port-bitmask") {
      carrierMgr->updateRxEndpointEaxc(endpointName, "", "", "", value, "");
    } else if (leaf == "eaxc-id") {
      carrierMgr->updateRxEndpointEaxc(endpointName, "", "", "", "", value);
    }
  } else {
    if (leaf == "o-du-port-bitmask") {
      carrierMgr->updateTxEndpointEaxc(endpointName, value, "", "", "", "");
    } else if (leaf == "band-sector-bitmask") {
      carrierMgr->updateTxEndpointEaxc(endpointName, "", value, "", "", "");
    } else if (leaf == "ccid-bitmask") {
      carrierMgr->updateTxEndpointEaxc(endpointName, "", "", value, "", "");
    } else if (leaf == "ru-port-bitmask") {
      carrierMgr->updateTxEndpointEaxc(endpointName, "", "", "", value, "");
    } else if (leaf == "eaxc-id") {
      carrierMgr->updateTxEndpointEaxc(endpointName, "", "", "", "", value);
    }
  }
}

//-----------------------------------------------------------------------------
void
OranUplaneConfHandler::handleDynCompConfig(
    const std::string& endpointName,
    const std::string& id,
    const std::string& leaf,
    const std::string& value,
    bool rx) {
  auto carrierMgr(IYangCarrierMgr::singleton());
  if (rx) {
    if (leaf == "iq-bitwidth") {
      carrierMgr->updateRxEndpointDynCompConfig(endpointName, id, value, "");
    } else if (leaf == "compression-method") {
      carrierMgr->updateRxEndpointDynCompConfig(endpointName, id, "", value);
    }
  } else {
    if (leaf == "iq-bitwidth") {
      carrierMgr->updateTxEndpointDynCompConfig(endpointName, id, value, "");
    } else if (leaf == "compression-method") {
      carrierMgr->updateTxEndpointDynCompConfig(endpointName, id, "", value);
    }
  }
}

//-----------------------------------------------------------------------------
void
OranUplaneConfHandler::handleCompression(
    const std::string& endpointName,
    const std::string& leaf,
    const std::string& value,
    bool rx) {
  auto carrierMgr(IYangCarrierMgr::singleton());
  if (rx) {
    if (leaf == "iq-bitwidth") {
      carrierMgr->updateRxEndpointCompression(
          endpointName, value, "", "", "", "");
    } else if (leaf == "compression-type") {
      carrierMgr->updateRxEndpointCompression(
          endpointName, "", value, "", "", "");
    } else if (leaf == "exponent") {
      carrierMgr->updateRxEndpointCompression(
          endpointName, "", "", "block-floating-point", value, "");
    } else if (leaf == "sres-exponent") {
      carrierMgr->updateRxEndpointCompression(
          endpointName,
          "",
          "",
          "block-floating-point-selective-re-sending",
          value,
          "");
    } else if (leaf == "block-scalar") {
      carrierMgr->updateRxEndpointCompression(
          endpointName, "", "", "block-scaling", value, "");
    } else if (leaf == "comp-bit-width") {
      carrierMgr->updateRxEndpointCompression(
          endpointName, "", "", "u-law", value, "");
    } else if (leaf == "comp-shift") {
      carrierMgr->updateRxEndpointCompression(
          endpointName, "", "", "u-law", "", value);
    } else if (leaf == "active-beam-space-coeficient-mask") {
      carrierMgr->updateRxEndpointCompression(
          endpointName, "", "", "beam-space-compression", value, "");
    } else if (leaf == "block-scaler") {
      carrierMgr->updateRxEndpointCompression(
          endpointName, "", "", "beam-space-compression", "", value);
    } else if (leaf == "csf") {
      carrierMgr->updateRxEndpointCompression(
          endpointName, "", "", "modulation-compression", value, "");
    } else if (leaf == "mod-comp-scaler") {
      carrierMgr->updateRxEndpointCompression(
          endpointName, "", "", "modulation-compression", "", value);
    } else if (leaf == "sres-csf") {
      carrierMgr->updateRxEndpointCompression(
          endpointName,
          "",
          "",
          "modulation-compression-selective-re-sending",
          value,
          "");
    } else if (leaf == "sres-mod-comp-scaler") {
      carrierMgr->updateRxEndpointCompression(
          endpointName,
          "",
          "",
          "modulation-compression-selective-re-sending",
          "",
          value);
    }
  } else {
    if (leaf == "iq-bitwidth") {
      carrierMgr->updateTxEndpointCompression(
          endpointName, value, "", "", "", "");
    } else if (leaf == "compression-type") {
      carrierMgr->updateTxEndpointCompression(
          endpointName, "", value, "", "", "");
    } else if (leaf == "exponent") {
      carrierMgr->updateTxEndpointCompression(
          endpointName, "", "", "block-floating-point", value, "");
    } else if (leaf == "sres-exponent") {
      carrierMgr->updateTxEndpointCompression(
          endpointName,
          "",
          "",
          "block-floating-point-selective-re-sending",
          value,
          "");
    } else if (leaf == "block-scalar") {
      carrierMgr->updateTxEndpointCompression(
          endpointName, "", "", "block-scaling", value, "");
    } else if (leaf == "comp-bit-width") {
      carrierMgr->updateTxEndpointCompression(
          endpointName, "", "", "u-law", value, "");
    } else if (leaf == "comp-shift") {
      carrierMgr->updateTxEndpointCompression(
          endpointName, "", "", "u-law", "", value);
    } else if (leaf == "active-beam-space-coeficient-mask") {
      carrierMgr->updateTxEndpointCompression(
          endpointName, "", "", "beam-space-compression", value, "");
    } else if (leaf == "block-scaler") {
      carrierMgr->updateTxEndpointCompression(
          endpointName, "", "", "beam-space-compression", "", value);
    } else if (leaf == "csf") {
      carrierMgr->updateTxEndpointCompression(
          endpointName, "", "", "modulation-compression", value, "");
    } else if (leaf == "mod-comp-scaler") {
      carrierMgr->updateTxEndpointCompression(
          endpointName, "", "", "modulation-compression", "", value);
    } else if (leaf == "sres-csf") {
      carrierMgr->updateTxEndpointCompression(
          endpointName,
          "",
          "",
          "modulation-compression-selective-re-sending",
          value,
          "");
    } else if (leaf == "sres-mod-comp-scaler") {
      carrierMgr->updateTxEndpointCompression(
          endpointName,
          "",
          "",
          "modulation-compression-selective-re-sending",
          "",
          value);
    }
  }
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam>>
OranUplaneConfHandler::getArrayCarrier(
    const std::string& txrx, const std::string& carrierName) {
  return getParams(
      mCallback->path() + "/" + txrx + "-array-carriers[name='" + carrierName +
      "']//.");
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string>>
OranUplaneConfHandler::getLinks(const std::string& txrx) {
  // get all of the links so I can search for the carrier name
  return getKeyValues(
      std::string(mCallback->path() + "/low-level-") + txrx + "-links//.");
}

//-------------------------------------------------------------------------------------------------------------
void
OranUplaneConfHandler::updateRxCarrier(const std::string& carrierName) {
  // skip if already present
  if (mRxCarrierState.find(carrierName) != mRxCarrierState.end())
    return;

  // create new entry and a callback for it
  mRxCarrierState[carrierName] = "DISABLED";
  auto stateFunc = [this, carrierName](std::string name) -> std::string {
    return mRxCarrierState[carrierName];
  };

  auto carrierMgr(IYangCarrierMgr::singleton());
  carrierMgr->updateRxCarrier(carrierName, stateFunc);
}

//-------------------------------------------------------------------------------------------------------------
void
OranUplaneConfHandler::updateTxCarrier(const std::string& carrierName) {
  // skip if already present
  if (mTxCarrierState.find(carrierName) != mTxCarrierState.end())
    return;

  // create new entry and a callback for it
  mTxCarrierState[carrierName] = "DISABLED";
  auto stateFunc = [this, carrierName](std::string name) -> std::string {
    return mTxCarrierState[carrierName];
  };

  auto carrierMgr(IYangCarrierMgr::singleton());
  carrierMgr->updateTxCarrier(carrierName, stateFunc);
}

//-------------------------------------------------------------------------------------------------------------
void
OranUplaneConfHandler::carrierChangeNotification(
    const std::string& txrx,
    const std::string& carrierName,
    const std::string& currentState,
    const std::string& newState) {
  // skip if the same
  if (newState == currentState)
    return;

  std::string notifPath(path(txrx + "-array-carriers-state-change"));
  std::string carrierPath(
      notifPath + "/" + txrx + "-array-carriers[name='" + carrierName + "']");

  std::shared_ptr<YangParams> params(std::make_shared<YangParams>());
  params->addParam(carrierName, carrierPath + "/name");
  params->addParam(newState, carrierPath + "/state");

  sendNotification(notifPath, params);
}

//-----------------------------------------------------------------------------
void
OranUplaneConfHandler::rxCarrierStateCallbackWrapper(
    const char* carrierName, carrier_state_t carrierState) {
  OranUplaneConfHandler* classInstance = oranUplaneConfHandlerInstance;
  if (classInstance) {
    classInstance->rxCarrierStateCallback(carrierName, carrierState);
  }
}

//-----------------------------------------------------------------------------
void
OranUplaneConfHandler::txCarrierStateCallbackWrapper(
    const char* carrierName, carrier_state_t carrierState) {
  OranUplaneConfHandler* classInstance = oranUplaneConfHandlerInstance;
  if (classInstance) {
    classInstance->txCarrierStateCallback(carrierName, carrierState);
  }
}

//=============================================================================
// PRIVATE
//=============================================================================

//-----------------------------------------------------------------------------
void
OranUplaneConfHandler::rxCarrierStateCallback(
    const char* carrierName, carrier_state_t carrierState) {
  std::string name(carrierName);
  updateRxCarrier(name);
  std::string oldState = mRxCarrierState[name];
  std::string newState;
  switch (carrierState) {
    case carrier_state_t::DISABLED:
      newState = "DISABLED";
      break;
    case carrier_state_t::BUSY:
      newState = "BUSY";
      break;
    case carrier_state_t::READY:
      newState = "READY";
      break;
  }
  mRxCarrierState[name] = newState;
  carrierChangeNotification("rx", name, oldState, newState);
}

//-----------------------------------------------------------------------------
void
OranUplaneConfHandler::txCarrierStateCallback(
    const char* carrierName, carrier_state_t carrierState) {
  std::string name(carrierName);
  updateTxCarrier(name);
  std::string oldState = mTxCarrierState[name];
  std::string newState;
  switch (carrierState) {
    case carrier_state_t::DISABLED:
      newState = "DISABLED";
      break;
    case carrier_state_t::BUSY:
      newState = "BUSY";
      break;
    case carrier_state_t::READY:
      newState = "READY";
      break;
  }
  mTxCarrierState[name] = newState;
  carrierChangeNotification("tx", name, oldState, newState);
}
