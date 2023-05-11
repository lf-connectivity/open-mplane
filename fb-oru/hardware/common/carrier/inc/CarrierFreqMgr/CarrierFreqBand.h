/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierFreqBand.h
 * \brief     Manages frequencies of a group of carriers on an antenna
 *
 *
 * \details
 *
 */


#ifndef CARRIERFREQBAND_H_
#define CARRIERFREQBAND_H_

#include <string>
#include <map>

#include "IFrequencyChange.h"
#include "ICarrierFreqPolicy.h"

#include "Observer.hpp"
#include "Loggable.h"

#include "CarrierFreqMgr/CarrierFreq.h"

namespace Mplane {

/**
 * Carrier frequency band class that manages the carriers frequencies for a single antenna either UL or DL
 *
 * This is also an IFrequencyChange Subject that can notify client Observers of any centre frequency changes
 */
class CarrierFreqBand : public Loggable, public virtual IFrequencyChange, public Subject<IFrequencyChange> {
public:
	CarrierFreqBand(const std::string& name,
			unsigned portIndex,
			const Frequency& loBandwidth,
			const Frequency& bandMin, const Frequency& bandMax,
			const Frequency& centre = Frequency(0.0)) ;
	virtual ~CarrierFreqBand() ;

	/**
	 * Will this new carrier fit within the end stop limits, and fit within the LO bandwidth
	 * (may require LO changing to new frequency)
	 * @param carrierFreq	New carrier frequencies
	 * @param policy		Policy used to calculate the new centre frequency
	 * @param failReason	Set to the failure reason on failure
	 * @return true if carrier can fit
	 */
	virtual bool canFit(unsigned index, const CarrierFreq& carrierFreq, std::shared_ptr<ICarrierFreqPolicy> policy, Frequency& newCentre, std::string& failReason) const ;

	/**
	 * Adds the carrier (may require LO changing to new frequency)
	 * @param index		An index used to identify the carrier frequency (usually the ICarrier index)
	 * @param carrierFreq	New carrier frequencies
	 * @param policy		Policy used to calculate the new centre frequency
	 * @param failReason	Set to the failure reason on failure
	 * @return true if carrier added ok
	 */
	virtual bool add(unsigned index, const CarrierFreq& carrierFreq, std::shared_ptr<ICarrierFreqPolicy> policy, std::string& failReason) ;

	/**
	 * Deletes the carrier
	 * @param index			An index used to identify the carrier frequency (usually the ICarrier index)
	 * @param policy		Policy used to calculate the new centre frequency
	 * @param failReason	Set to the failure reason on failure
	 * @return true if carrier deleted ok
	 */
	virtual bool del(unsigned index, std::shared_ptr<ICarrierFreqPolicy> policy, std::string& failReason) ;

	/**
	 * Returns the current centre frequency
	 * @return centre frequency
	 */
	virtual Frequency getCentre() const ;

	/**
	 * Returns the occupied bandwidth min frequency
	 * @return minimum frequency
	 */
	virtual Frequency getMinFrequency() const ;

	/**
	 * Returns the occupied bandwidth max frequency
	 * @return maximum frequency
	 */
	virtual Frequency getMaxFrequency() const ;

	/**
	 * Returns the carrier bundle actual centre frequency (may be different to the value returned by getCentre()
	 * depending on the frequency policy being used)
	 * @return centre frequency
	 */
	virtual Frequency getBundleCentre() const ;


	// IFrequencyChange interface

    /*! \brief Pure virtual method to get the frequency
     *
     * \return The Frequency
     */
    virtual const Frequency getFrequency( void ) override;

protected:
	// Given a map of frequencies, calculate the new centre and end stops. Returns false if unable to set a valid centre frequency
	// for these conditions
	virtual bool calcFrequencies(const std::map<unsigned, CarrierFreq>& carrierFreqs,
			Frequency& centre, Frequency& min, Frequency& max,
			Frequency& bundleRealCentre,
			std::shared_ptr<ICarrierFreqPolicy> policy, std::string& failReason) const ;

private:
	std::string mName ;
	unsigned mPort ;
	Frequency mLoBandwidth ;
	Frequency mLoHalfBandwidth ;
	Frequency mBandMin ;
	Frequency mBandMax ;
	Frequency mCentre ;
	Frequency mBundleCentre ;

	std::map<unsigned, CarrierFreq> mCarrierFreqs ;
	Frequency mMinFreq ;
	Frequency mMaxFreq ;
} ;

}

#endif /* CARRIERFREQBAND_H_ */
