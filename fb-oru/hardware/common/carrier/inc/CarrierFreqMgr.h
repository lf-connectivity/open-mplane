/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierFreqMgr.h
 * \brief     Manages frequency allocation on RX and TX ports
 *
 *
 * \details   Tracks the frequency band usage of active carriers on both TX and RX ports. Adjusts the port LO as required
 *
 */


#ifndef CARRIERFREQMGR_H_
#define CARRIERFREQMGR_H_

#include <functional>
#include <vector>
#include <memory>

#include "ITxPort.h"
#include "IRxPort.h"
#include "ICarrierBundleFreq.h"
#include "IFrequencyConst.h"

#include "Loggable.h"

#include "CarrierFreqMgr/CarrierFreqBand.h"

namespace Mplane {


/**
 * Class for managing DL & UL frequencies on all antennas
 */
class CarrierFreqMgr : public virtual ICarrierBundleFreq, public Loggable {
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<CarrierFreqMgr> getInstance(unsigned maxCarriers) ;

	virtual ~CarrierFreqMgr() ;

	/**
	 * Validate the carrier change. If carrier is becoming active, checks that the carrier can be added
	 * @param carrier
	 * @param failReason
	 * @return true if handled ok; false with failureReason string set otherwise
	 */
	virtual bool validateCarrier(const ICarrier& carrier, std::string& failReason) ;

	/**
	 * Update the models based on the carrier change.
	 * @param carrier
	 * @param failReason
	 * @return true if handled ok; false with failureReason string set otherwise
	 */
	virtual bool carrierChange(const ICarrier& carrier, std::string& failReason) ;

	/**
	 * Set a new policy for calculating the DL centre frequency
	 */
	virtual void setDlFrequencyPolicy(std::shared_ptr<IDlFrequencyPolicy> dlFreqPolicy) ;

	/**
	 * Set a new policy for calculating the DL centre frequency
	 */
	virtual void setUlFrequencyPolicy(std::shared_ptr<IUlFrequencyPolicy> ulFreqPolicy) ;

	/**
	 * Set to true to disable policies (disabled auto centre); set to false for normal operation
	 * @param disable
	 */
	virtual void disablePolicies(bool disable) ;

	// ICarrierBundleFreq interface

	/**
	 * Attach a frequency change observer to the specified RX port
	 * @param port
	 * @param observer
	 */
	virtual void attachRx(unsigned port, Observer<IFrequencyChange>& observer) override ;

	/**
	 * Detach a frequency change observer from the specified RX port
	 * @param port
	 * @param observer
	 */
	virtual void detachRx(unsigned port, Observer<IFrequencyChange>& observer) override ;

	/**
	 * Attach a frequency change observer to the specified TX port
	 * @param port
	 * @param observer
	 */
	virtual void attachTx(unsigned port, Observer<IFrequencyChange>& observer) override ;

	/**
	 * Detach a frequency change observer from the specified RX port
	 * @param port
	 * @param observer
	 */
	virtual void detachTx(unsigned port, Observer<IFrequencyChange>& observer) override ;

protected:
	explicit CarrierFreqMgr(unsigned maxCarriers) ;

	bool isTxActivating(const ICarrier& carrier, unsigned port) const ;
	bool isTxDeactivating(const ICarrier& carrier, unsigned port) const ;
	bool isRxActivating(const ICarrier& carrier, unsigned port) const ;
	bool isRxDeactivating(const ICarrier& carrier, unsigned port) const ;

	bool checkTxFreq(unsigned port, std::shared_ptr<CarrierFreqBand> freqBand, std::string& failReason) ;
	bool checkRxFreq(unsigned port, std::shared_ptr<CarrierFreqBand> freqBand, std::string& failReason) ;

	std::pair<Frequency, Frequency> getFreqLimits(std::shared_ptr<IFrequencyConst> freqConst) ;


private:
	bool mDisablePolicies ;

	// The TX/RX ports
	std::vector<std::shared_ptr<ITxPort>> mTxPorts ;
	std::vector<std::shared_ptr<IRxPort>> mRxPorts ;

	// Per TX port, per carrier - current TX active state of carrier
	std::vector<std::vector<bool>> mTxCarrierActive ;

	// Per RX port, per carrier - current RX active state of carrier
	std::vector<std::vector<bool>> mRxCarrierActive ;

	// Current TX port centre frequency
	std::vector<Frequency> mTxFreqs ;

	// Current RX port centre frequency
	std::vector<Frequency> mRxFreqs ;

	// track changes in TX/RX port centre frequency
	std::vector<bool> mTxFreqChange ;
	std::vector<bool> mRxFreqChange ;

	// Per TX port frequency band object
	std::vector<std::shared_ptr<CarrierFreqBand>> mTxFreqBands ;

	// Per RX port frequency band object
	std::vector<std::shared_ptr<CarrierFreqBand>> mRxFreqBands ;

	// Policies on how to calculate the centre frequencies - set to the normal operating poilcies
	std::shared_ptr<IDlFrequencyPolicy> mDlFreqPolicy;
	std::shared_ptr<IUlFrequencyPolicy> mUlFreqPolicy;

	// The currently active policies - may be set to a null policy to disable autocentre
	std::shared_ptr<IDlFrequencyPolicy> mActiveDlFreqPolicy;
	std::shared_ptr<IUlFrequencyPolicy> mActiveUlFreqPolicy;
} ;

}

#endif /* CARRIERFREQMGR_H_ */
