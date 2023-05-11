/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangCarrierMgr.h
 * \brief     Virtual interface to manager object for YANG carrier model
 *
 *
 * \details   Virtual interface to manager object for YANG carrier model
 *
 */


#ifndef YANG_HANDLERS_INC_IYANGCARRIERMGR_H_
#define YANG_HANDLERS_INC_IYANGCARRIERMGR_H_

#include <memory>
#include <utility>

#include "ILeafContainer.h"

namespace Mplane {

/*!
 * \class  IYangCarrierMgr
 * \brief
 * \details
 *
 */
class IYangCarrierMgr {
public:
 /**
  * Singleton
  */
 static std::shared_ptr<IYangCarrierMgr> singleton();

 IYangCarrierMgr() {}
 virtual ~IYangCarrierMgr() {}

 /**
  * Initialise the object
  */
 virtual bool initialise() = 0;

 /**
  * Assign the leaf container
  */
 virtual void setLeafContainer(
     std::shared_ptr<ILeafContainer> leafContainer) = 0;

 /**
  * Get the leaf container
  */
 virtual std::shared_ptr<ILeafContainer> leafContainer() = 0;

 /**
  * Update the RX linkages between carriers and endpoints
  */
 virtual void updateRxLink(
     const std::string& name,
     const std::string& endpoint,
     const std::string& carrierName) = 0;

 /**
  * Update the TX linkages between carriers and endpoints
  */
 virtual void updateTxLink(
     const std::string& name,
     const std::string& endpoint,
     const std::string& carrierName) = 0;

 /**
  * Update the RX carrier
  */
 virtual void updateRxCarrier(
     const std::string& carrierName,
     ILeafContainer::LeafFunc stateFunc) = 0;

 /**
  * Update the TX carrier
  */
 virtual void updateTxCarrier(
     const std::string& carrierName,
     ILeafContainer::LeafFunc stateFunc) = 0;

  /**
   * Update low-level-rx-endpoints compression/dynamic-compression-configuration
   * and call through to HAL.
   */
  virtual void updateRxEndpointDynCompConfig(
      const std::string& endpointName,
      const std::string& id,
      const std::string& iqBitwidth,
      const std::string& compressionMethod) = 0;

  /**
   * Update low-level-tx-endpoints compression/dynamic-compression-configuration
   * and call through to HAL.
   */
  virtual void updateTxEndpointDynCompConfig(
      const std::string& endpointName,
      const std::string& id,
      const std::string& iqBitwidth,
      const std::string& compressionMethod) = 0;

  /**
   * Update low-level-rx-endpoints compression and call through to HAL.
   */
  virtual void updateRxEndpointCompression(
      const std::string& endpointName,
      const std::string& iqBitWidth,
      const std::string& compressionType,
      const std::string& compressionFormat,
      const std::string& val1,
      const std::string& val2) = 0;

  /**
   * Update low-level-tx-endpoints compression and call through to HAL.
   */
  virtual void updateTxEndpointCompression(
      const std::string& endpointName,
      const std::string& iqBitWidth,
      const std::string& compressionType,
      const std::string& compressionFormat,
      const std::string& val1,
      const std::string& val2) = 0;

  /**
   * Update low-level-rx-endpoints e-axcid and call through to HAL.
   */
  virtual void updateRxEndpointEaxc(
      const std::string& endpointName,
      const std::string& oduPortBitmask,
      const std::string& bandSectorBitmask,
      const std::string& ccidBitmask,
      const std::string& ruPortBitmask,
      const std::string& eaxcId) = 0;

  /**
   * Update low-level-tx-endpoints e-axcid and call through to HAL.
   */
  virtual void updateTxEndpointEaxc(
      const std::string& endpointName,
      const std::string& oduPortBitmask,
      const std::string& bandSectorBitmask,
      const std::string& ccidBitmask,
      const std::string& ruPortBitmask,
      const std::string& eaxcId) = 0;

} ;

}

#endif /* YANG_HANDLERS_INC_IYANGCARRIERMGR_H_ */
