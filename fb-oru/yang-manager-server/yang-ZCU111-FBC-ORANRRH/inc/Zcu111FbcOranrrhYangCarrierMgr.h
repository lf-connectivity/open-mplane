/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhYangCarrierMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHYANGCARRIERMGR_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHYANGCARRIERMGR_H_

#include <set>
#include <map>
#include <string>
#include <utility>

#include "ICarrier.h"
#include "YangCarrierMgr.h"

namespace Mplane {

/*!
 * \class  Zcu111FbcOranrrhYangCarrierMgr
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhYangCarrierMgr : public YangCarrierMgr {
public:
	Zcu111FbcOranrrhYangCarrierMgr() ;
	virtual ~Zcu111FbcOranrrhYangCarrierMgr() ;

	/**
	 * Initialise the object
	 */
	virtual bool initialise() override ;

	/**
	 * Look up the carrier/iq map from the endpoint name
	 */
	virtual std::pair<unsigned, unsigned> lookupUlEndpoint(const std::string& endpointName) override ;
	virtual std::pair<unsigned, unsigned> lookupDlEndpoint(const std::string& endpointName) override ;

	/**
	 * Number of TX antennas
	 */
	virtual unsigned numTx() const override ;

	/**
	 * Number of RX antennas
	 */
	virtual unsigned numRx() const override ;

	/**
	 * Update the RX linkages between carriers and endpoints
	 */
	virtual void updateRxLink(const std::string& name, const std::string& endpoint, const std::string& carrierName) override ;

	/**
	 * Update the TX linkages between carriers and endpoints
	 */
	virtual void updateTxLink(const std::string& name, const std::string& endpoint, const std::string& carrierName) override ;

	/**
	 * Update the RX carrier
	 */
	virtual void updateRxCarrier(const std::string& carrierName, ILeafContainer::LeafFunc stateFunc,
			ILeafContainer::LeafFunc activeFunc) override ;

	/**
	 * Update the TX carrier
	 */
	virtual void updateTxCarrier(const std::string& carrierName, ILeafContainer::LeafFunc stateFunc,
			ILeafContainer::LeafFunc activeFunc) override ;



private:
	ICarrierHardwareTypes::ScheduleStatus scheduleUl(const unsigned carrierIndex, const unsigned antenna,
				const ICarrierHardwareTypes::AirstdType airstd, const ICarrierHardwareTypes::ChbwType chbw, const unsigned fibre,
				unsigned& fibreIndex, unsigned& chain, unsigned& chainIndex) ;
	ICarrierHardwareTypes::ScheduleStatus scheduleDl(const unsigned carrierIndex, const unsigned antenna,
				const ICarrierHardwareTypes::AirstdType airstd, const ICarrierHardwareTypes::ChbwType chbw, const unsigned fibre,
				unsigned& fibreIndex, unsigned& chain, unsigned& chainIndex) ;

	/**
	 * Calc ORAN frame-structure coded value
	 */
	unsigned frameStructure(ICarrier::FFTsizeType fft, ICarrier::ScsType scs) ;

	/**
	 * Initialise some shared data
	 */
	void initData() ;

	void initUlMap() ;
	void initDlMap() ;

	/**
	 * Create the endpoint-types in the sysrepo
	 */
	bool createEndpointTypes() ;

	/**
	 * Create the endpoint-capacity-sharing-groups in the sysrepo
	 */
	bool createEndpointCapacitySharingGroups() ;
	bool createEndpointCapacitySharingGroup(std::shared_ptr<ILeafContainer> parent, unsigned id, unsigned maxPrb) ;

	/**
	 * Create the tx-arrays in the sysrepo
	 */
	bool createTxArrays() ;

	/**
	 * Create the rx-arrays in the sysrepo
	 */
	bool createRxArrays() ;

	bool createArray(std::shared_ptr<ILeafContainer> array, const std::string& name) ;


	/**
	 * Create the static-low-level-tx-endpoints in the sysrepo
	 */
	bool createStaticLowLevelTxEndpoints() ;

	/**
	 * Create the static-low-level-rx-endpoints in the sysrepo
	 */
	bool createStaticLowLevelRxEndpoints() ;

	// create endpoint name
	std::string txEndpointName(unsigned ant, unsigned cc) ;
	std::string rxEndpointName(unsigned ant, unsigned cc) ;
	std::string prachEndpointName(unsigned ant, unsigned cc) ;


private:
	bool mInitialised ;

	unsigned mNumTx ;
	unsigned mNumRx ;

	// For each chain, get the number of supported streams - used to calculate indices
	std::vector<unsigned> mNumStreamsPerChain ;

	// sum up number of streams in the previous chains - used to calculate indices
	std::vector<unsigned> mTotalStreams ;

	// calc min/max channel bandwidths
	ICarrierHardwareTypes::ChbwType mMinChbw ;
	ICarrierHardwareTypes::ChbwType mMaxChbw ;

	// map from endpoint name to iq stream - each name maps to a chain number (== carrier index) & iq stream index
	std::map<std::string, std::pair<unsigned, unsigned>> mUlStreamMap ;
	std::map<std::string, std::pair<unsigned, unsigned>> mDlStreamMap ;

	// links
	struct Link ;
	std::map<std::string, std::shared_ptr<Link>> mRxLinks ;
	std::map<std::string, std::shared_ptr<Link>> mTxLinks ;

	// Carriers (i.e. carrier arrays)
	std::set<std::string> mRxCarriers ;
	std::set<std::string> mTxCarriers ;
} ;

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHYANGCARRIERMGR_H_ */
