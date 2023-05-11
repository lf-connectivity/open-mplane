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
	static std::shared_ptr<IYangCarrierMgr> singleton() ;

	IYangCarrierMgr() {}
	virtual ~IYangCarrierMgr() {}

	/**
	 * Initialise the object
	 */
	virtual bool initialise() =0 ;

	/**
	 * Look up the carrier/iq map from the endpoint name
	 */
	virtual std::pair<unsigned, unsigned> lookupUlEndpoint(const std::string& endpointName) =0 ;
	virtual std::pair<unsigned, unsigned> lookupDlEndpoint(const std::string& endpointName) =0 ;

	/**
	 * Assign the leaf container
	 */
	virtual void setLeafContainer(std::shared_ptr<ILeafContainer> leafContainer) =0 ;

	/**
	 * Get the leaf container
	 */
	virtual std::shared_ptr<ILeafContainer> leafContainer() =0 ;

	/**
	 * Create an endpoint name from the prefix, antenna, carrier
	 *
	 */
	virtual std::string endpointName(const std::string& prefix, unsigned antenna, unsigned carrier) =0 ;

	/**
	 * Number of TX antennas
	 */
	virtual unsigned numTx() const =0 ;

	/**
	 * Number of RX antennas
	 */
	virtual unsigned numRx() const =0 ;

	/**
	 * Update the RX linkages between carriers and endpoints
	 */
	virtual void updateRxLink(const std::string& name, const std::string& endpoint, const std::string& carrierName) =0 ;

	/**
	 * Update the TX linkages between carriers and endpoints
	 */
	virtual void updateTxLink(const std::string& name, const std::string& endpoint, const std::string& carrierName) =0 ;

	/**
	 * Update the RX carrier
	 */
	virtual void updateRxCarrier(const std::string& carrierName, ILeafContainer::LeafFunc stateFunc, ILeafContainer::LeafFunc activeFunc) =0 ;

	/**
	 * Update the TX carrier
	 */
	virtual void updateTxCarrier(const std::string& carrierName, ILeafContainer::LeafFunc stateFunc, ILeafContainer::LeafFunc activeFunc) =0 ;

} ;

}

#endif /* YANG_HANDLERS_INC_IYANGCARRIERMGR_H_ */
