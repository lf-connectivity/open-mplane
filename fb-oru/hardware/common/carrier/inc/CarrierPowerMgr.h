/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierPowerMgr.h
 * \brief     Manages carrier power allocation on TX ports
 *
 *
 * \details   Tracks the power usage of active carriers on TX ports.
 *
 */


#ifndef CarrierPowerMgr_H_
#define CarrierPowerMgr_H_

#include <functional>
#include <vector>
#include <memory>

#include "ICarrier.h"
#include "ITxPort.h"

#include "Loggable.h"

#include "CarrierPowerMgr/CarrierPowerPath.h"

namespace Mplane {


/**
 * Class for managing DL & UL frequencies on all antennas
 */
class CarrierPowerMgr : public Loggable {
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<CarrierPowerMgr> getInstance(unsigned maxCarriers) ;

	virtual ~CarrierPowerMgr() ;

	/**
	 * Get the current total carrier power on this TX port
	 * @param port 0-based tx port
	 * @return total power
	 */
	virtual Power getTotalPower(unsigned port) const ;

     /**
        * Gets the power of the lowest powered carrier on this TX port
        * @param path zero based Tx path selector
        * @return power
        */
     virtual Power getSmallestCarrierPower(unsigned path) const;

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

protected:
	explicit CarrierPowerMgr(unsigned maxCarriers) ;

	bool isTxActivating(const ICarrier& carrier, unsigned port) const ;
	bool isTxDeactivating(const ICarrier& carrier, unsigned port) const ;

//	bool checkTxFreq(unsigned port, std::shared_ptr<CarrierFreqBand> freqBand, std::string& failReason) ;

private:
	// The TX ports
	std::vector<std::shared_ptr<ITxPort>> mTxPorts ;

	// Per TX port, per carrier - current TX active state of carrier
	std::vector<std::vector<bool>> mTxCarrierActive ;

	// Per TX port carrier power object
	std::vector<std::shared_ptr<CarrierPowerPath>> mTxCarrierPowers ;

} ;

}

#endif /* CarrierPowerMgr_H_ */
