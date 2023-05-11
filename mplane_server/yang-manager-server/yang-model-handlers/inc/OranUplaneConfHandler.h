/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranUplaneConfHandler.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef INC_ORANUPLANECONF_HANDLER_H_
#define INC_ORANUPLANECONF_HANDLER_H_

#include "SysrepoGetitemsCallback.h"
#include "YangHandlerSysrepo.h"

#include <MplaneUplaneConf.h>

namespace Mplane {

/*!
 * \class  OranUplaneConfHandler
 * \brief
 * \details
 *
 */
class OranUplaneConfHandler : public YangHandlerSysrepo {
 public:
  OranUplaneConfHandler(std::shared_ptr<IYangModuleMgr> moduleMgr);
  virtual ~OranUplaneConfHandler();

  /**
   * Run the initialisation of the handler (can only be done once the rest of
   * the YANG framework is up)
   */
  virtual bool initialise() override;

 protected:
  /**
   * Module change hook - called by module_change() method with filtered events
   */
  virtual void valueChange(
      const std::string& xpath,
      std::shared_ptr<YangParam> oldValue,
      std::shared_ptr<YangParam> newValue) override;

  /*!
   \brief Module change hook - called by module_change() method to have this
   class validate the proposed values changes \param params A YangParams pointer
   containing all of the changed values \return SR_ERR_OK if the values are
   validated; SR_ERR_VALIDATION_FAILED on validation failure. Can return any
   other sysrepo error status as necessary.
   */
  virtual int validate(
      std::shared_ptr<YangParams> params,
      std::shared_ptr<YangParams> deletedParams) override;

 private:
  enum TxRxSettings {
    SETTING_TX,
    SETTING_RX,
  };

  enum ValuePhase {
    VALUE_VALIDATE,
    VALUE_APPLY,
  };

  /**
   * Apply the value change. Expects calling method to have extracted the leaf
   * name and value of the variable \return SR_ERR_OK if value change applied ok
   */
  int processValue(
      std::shared_ptr<YangParam> param,
      const std::string& leaf,
      const std::string& value,
      const std::string& xpath);

  /**
   * Apply the value change. Expects calling method to have extracted the leaf
   * name and value of the variable \return SR_ERR_OK if change is valid
   */
  int validateValue(
      std::shared_ptr<YangParam> param,
      const std::string& leaf,
      const std::string& value);

  /**
   * Handle an "active" change during the validate or apply value phases
   */
  int handleActivate(
      std::shared_ptr<YangParam> param,
      const std::string& leaf,
      const std::string& value,
      ValuePhase phase);

  void handleEaxc(
      const std::string& endpointName,
      const std::string& leaf,
      const std::string& value,
      bool rx);

  void handleDynCompConfig(
      const std::string& endpointName,
      const std::string& id,
      const std::string& leaf,
      const std::string& value,
      bool rx);

  void handleCompression(
      const std::string& endpointName,
      const std::string& leaf,
      const std::string& value,
      bool rx);

  /**
   * Read the endpoint and convert the list of params into variable name /
   * YangParam pairs. Variable name is the leaf name (not the full xpath)
   */
  std::map<std::string, std::shared_ptr<YangParam>> getArrayCarrier(
      const std::string& txrx, const std::string& carrierName);

  /**
   * Read the links and process the data into a map of vectors. Map key is the
   * link name, vector is the name/value pairs for that link
   */
  std::map<std::string, std::map<std::string, std::string>> getLinks(
      const std::string& txrx);

  /**
   * Ensure RX carrier is in the tree
   */
  void updateRxCarrier(const std::string& carrierName);

  /**
   * Ensure TX carrier is in the tree
   */
  void updateTxCarrier(const std::string& carrierName);

  /**
   * Static function registered as a callback in the HAL. Wrapper around the
   * associated member function, using a global pointer of the class instance.
   */
  static void rxCarrierStateCallbackWrapper(
      const char* carrierName, carrier_state_t carrierState);

  /**
   * Static function registered as a callback in the HAL. Wrapper around the
   * associated member function, using a global pointer of the class instance.
   */
  static void txCarrierStateCallbackWrapper(
      const char* carrierName, carrier_state_t carrierState);

  /**
   * Send a notification if needed
   */
  void carrierChangeNotification(
      const std::string& txrx,
      const std::string& carrierName,
      const std::string& currentState,
      const std::string& newState);

 private:
  /**
   * Change the stored carrier state which is used by the tree, and trigger
   * a state change notificaton.
   */
  void rxCarrierStateCallback(
      const char* carrierName, carrier_state_t carrierState);

  /**
   * Change the stored carrier state which is used by the tree, and trigger
   * a state change notificaton.
   */
  void txCarrierStateCallback(
      const char* carrierName, carrier_state_t carrierState);

  std::shared_ptr<SysrepoGetitemsCallback> mCallback;
  std::shared_ptr<IYangConfig> mConfig;
  std::map<std::string, std::string> mRxCarrierState;
  std::map<std::string, std::string> mTxCarrierState;
};

} // namespace Mplane

#endif /* INC_ORANUPLANECONF_HANDLER_H_ */
