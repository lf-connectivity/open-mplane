/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranYangCarrierMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef INC_ORANYANGCARRIERMGR_H_
#define INC_ORANYANGCARRIERMGR_H_

#include <map>
#include <set>
#include <string>
#include <utility>

#include "YangCarrierMgr.h"

#include <MplaneUplaneConf.h>

namespace Mplane {

/*!
 * \class  OranYangCarrierMgr
 * \brief
 * \details
 *
 */
class OranYangCarrierMgr : public YangCarrierMgr {
 public:
  OranYangCarrierMgr();
  virtual ~OranYangCarrierMgr();

  /**
   * Initialise the object
   */
  virtual bool initialise() override;

  /**
   * Update the RX linkages between carriers and endpoints
   */
  virtual void updateRxLink(
      const std::string& name,
      const std::string& endpoint,
      const std::string& carrierName) override;

  /**
   * Update the TX linkages between carriers and endpoints
   */
  virtual void updateTxLink(
      const std::string& name,
      const std::string& endpoint,
      const std::string& carrierName) override;

  /**
   * Update the RX carrier
   */
  virtual void updateRxCarrier(
      const std::string& carrierName,
      ILeafContainer::LeafFunc stateFunc) override;

  /**
   * Update the TX carrier
   */
  virtual void updateTxCarrier(
      const std::string& carrierName,
      ILeafContainer::LeafFunc stateFunc) override;

  /**
   * Update low-level-rx-endpoints compression/dynamic-compression-configuration
   * and call through to HAL.
   */
  void updateRxEndpointDynCompConfig(
      const std::string& endpointName,
      const std::string& id,
      const std::string& iqBitwidth,
      const std::string& compressionMethod) override;

  /**
   * Update low-level-tx-endpoints compression/dynamic-compression-configuration
   * and call through to HAL.
   */
  void updateTxEndpointDynCompConfig(
      const std::string& endpointName,
      const std::string& id,
      const std::string& iqBitwidth,
      const std::string& compressionMethod) override;

  /**
   * Update low-level-rx-endpoints compression and call through to HAL.
   */
  void updateRxEndpointCompression(
      const std::string& endpointName,
      const std::string& iqBitWidth,
      const std::string& compressionType,
      const std::string& compressionFormat,
      const std::string& val1,
      const std::string& val2) override;

  /**
   * Update low-level-tx-endpoints compression and call through to HAL.
   */
  void updateTxEndpointCompression(
      const std::string& endpointName,
      const std::string& iqBitWidth,
      const std::string& compressionType,
      const std::string& compressionFormat,
      const std::string& val1,
      const std::string& val2) override;

  /**
   * Update low-level-rx-endpoints e-axcid and call through to HAL.
   */
  void updateRxEndpointEaxc(
      const std::string& endpointName,
      const std::string& oduPortBitmask,
      const std::string& bandSectorBitmask,
      const std::string& ccidBitmask,
      const std::string& ruPortBitmask,
      const std::string& eaxcId) override;

  /**
   * Update low-level-tx-endpoints e-axcid and call through to HAL.
   */
  void updateTxEndpointEaxc(
      const std::string& endpointName,
      const std::string& oduPortBitmask,
      const std::string& bandSectorBitmask,
      const std::string& ccidBitmask,
      const std::string& ruPortBitmask,
      const std::string& eaxcId) override;

 private:
  /**
   * Create the endpoint-types in the sysrepo
   */
  void createEndpointTypes();

  /**
   * Create the endpoint-capacity-sharing-groups in the sysrepo
   */
  void createEndpointCapacitySharingGroups();
  void createEndpointCapacitySharingGroup(
      std::shared_ptr<ILeafContainer> parent, unsigned id, unsigned maxPrb);

  /**
   * Create the tx-arrays in the sysrepo
   */
  void createTxArrays();

  /**
   * Create the rx-arrays in the sysrepo
   */
  void createRxArrays();

  void createArray(
      std::shared_ptr<ILeafContainer> array,
      std::shared_ptr<IYangConfig> config,
      const std::string& name);

  /**
   * Create the static-low-level-tx-endpoints in the sysrepo
   */
  void createStaticLowLevelTxEndpoints();

  /**
   * Create the static-low-level-rx-endpoints in the sysrepo
   */
  void createStaticLowLevelRxEndpoints();

  void createRelations();
  void createEndpointPrachGroups();
  void createSupportedCompressionMethodSets();

 private:
  std::shared_ptr<IYangConfig> mConfig;

  bool mInitialised;

  // links
  struct Link;
  std::map<std::string, std::shared_ptr<Link>> mRxLinks;
  std::map<std::string, std::shared_ptr<Link>> mTxLinks;

  // Carriers (i.e. carrier arrays)
  std::set<std::string> mRxCarriers;
  std::set<std::string> mTxCarriers;

  std::map<std::string, std::shared_ptr<compression_t>> mRxEndpointComps;
  std::map<std::string, std::shared_ptr<compression_t>> mTxEndpointComps;

  std::map<std::string, std::shared_ptr<e_axcid_t>> mRxEndpointEaxcs;
  std::map<std::string, std::shared_ptr<e_axcid_t>> mTxEndpointEaxcs;

  std::map<
      std::string,
      std::map<int, std::shared_ptr<dynamic_compression_configuration_t>>>
      mRxEndpointDynComps;
  std::map<
      std::string,
      std::map<int, std::shared_ptr<dynamic_compression_configuration_t>>>
      mTxEndpointDynComps;
};

} // namespace Mplane

#endif /* INC_ORANYANGCARRIERMGR_H_ */
