/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierPowerPath.h
 * \brief     Manages powers of a group of carriers on an antenna
 *
 *
 * \details
 *
 */


#ifndef CarrierPowerPath_H_
#define CarrierPowerPath_H_

#include <string>
#include <map>
#include "Power.h"
#include "Loggable.h"

namespace Mplane {

/**
 * Carrier Power band class that manages the carriers Poweruencies for a single antenna either UL or DL
 */
class CarrierPowerPath : public Loggable {
public:
	CarrierPowerPath(const std::string& name,
			unsigned portIndex,
			const Power& extFilter, const Power& extFilterMax) ;
	virtual ~CarrierPowerPath() ;

	/**
	 * Will this new carrier fit within the end stop limits
	 * @param carrierPower	New carrier power
	 * @param failReason	Set to the failure reason on failure
	 * @return true if carrier can fit
	 */
	virtual bool canFit(unsigned index, const Power& carrierPower, std::string& failReason) const ;

	/**
	 * Adds the carrier
	 * @param index		An index used to identify the carrier Power (usually the ICarrier index)
	 * @param carrierPower	New carrier Power
	 * @param failReason	Set to the failure reason on failure
	 * @return true if carrier added ok
	 */
	virtual bool add(unsigned index, const Power& carrierPower, std::string& failReason) ;

	/**
	 * Deletes the carrier
	 * @param index			An index used to identify the carrier Power (usually the ICarrier index)
	 * @param failReason	Set to the failure reason on failure
	 * @return true if carrier deleted ok
	 */
	virtual bool del(unsigned index, std::string& failReason) ;

	/**
	 * Returns the total carrier Power
	 * @return minimum Power
	 */
	virtual Power getPower() const ;

	/**
	 * Update the external filter setting
	 */
	virtual void setExtFilter(const Power& extFilter) ;

	/**
	 * Returns the power of the carrier with the smallest power
	 * @return weighting
	 */
	virtual Power getSmallestPower() const;

protected:
	// Given a map of Power, calculate the new centre and end stops. Returns false if unable to set a valid centre Power
	// for these conditions
	virtual bool calcPowers(const std::map<unsigned, Power>& carrierPowers,
			Power& totalPower,
			std::string& failReason, Power pathMax, Power pathMin) const ;

private:
	std::string mName ;
	unsigned mPort ;
	Power mExtFilter ;
	Power mExtFilterMax ;

	std::map<unsigned, Power> mCarrierPowers ;
	Power mTotalPower ;
} ;

}

#endif /* CarrierPowerPath_H_ */
