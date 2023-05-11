/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierFreqBand.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <algorithm>
#include <sstream>
#include "CarrierFreqBand.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CarrierFreqBand::CarrierFreqBand(
		const std::string& name,
		unsigned portIndex,
		const Frequency& loBandwidth,
		const Frequency& bandMin, const Frequency& bandMax,
		const Frequency& centre) :
	Loggable(name, "CarrierFreq"),

	mName(name),
	mPort(portIndex),
	mLoBandwidth(loBandwidth),
	mLoHalfBandwidth(mLoBandwidth / 2.0),
	mBandMin(bandMin),
	mBandMax(bandMax),
	mCentre(centre),
	mBundleCentre(0.0),
	mCarrierFreqs(),
	mMinFreq(0.0),
	mMaxFreq(0.0)
{
}

//-------------------------------------------------------------------------------------------------------------
CarrierFreqBand::~CarrierFreqBand()
{
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqBand::canFit(unsigned index, const CarrierFreq& carrierFreq, std::shared_ptr<ICarrierFreqPolicy> policy, Frequency& newCentre, std::string& failReason) const
{

	if (isDebug(Loggable::LOG_DEBUG_VERBOSE))
	{
		logDebugVerbose("%s canFit: Freq %llu kHz [%llu  kHz .. %llu kHz]",
			mName.c_str(),
			carrierFreq.getCentre().get(Frequency::KHz),
			carrierFreq.getMin().get(Frequency::KHz),
			carrierFreq.getMax().get(Frequency::KHz)
		) ;
	}

	Frequency bundleCentre ;
	Frequency minFreq ;
	Frequency maxFreq ;
	std::map<unsigned, CarrierFreq> carrierFreqs(mCarrierFreqs) ;

	carrierFreqs[index] = carrierFreq ;
	return calcFrequencies(carrierFreqs, newCentre, minFreq, maxFreq, bundleCentre, policy, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqBand::add(unsigned index, const CarrierFreq& carrierFreq, std::shared_ptr<ICarrierFreqPolicy> policy, std::string& failReason)
{
	if (isDebug(Loggable::LOG_DEBUG_VERBOSE))
	{
		logDebugVerbose("%s add: Freq %llu kHz [%llu  kHz .. %llu kHz]",
			mName.c_str(),
			carrierFreq.getCentre().get(Frequency::KHz),
			carrierFreq.getMin().get(Frequency::KHz),
			carrierFreq.getMax().get(Frequency::KHz)
		) ;
	}

	Frequency centre ;
	Frequency bundleCentre ;
	Frequency minFreq ;
	Frequency maxFreq ;
	std::map<unsigned, CarrierFreq> carrierFreqs(mCarrierFreqs) ;  // create a new temporary carrier frequencies map on the stack based on the current map

	carrierFreqs[index] = carrierFreq ;     // add the new carrier frequency info into the temporary map.
	if (!calcFrequencies(carrierFreqs, centre, minFreq, maxFreq, bundleCentre, policy, failReason)) // now find the min, max and centres and check them with the frequency policy manager
		return false ;

	mCarrierFreqs[index] = carrierFreq ;    // new carrier frequency data looks OK so now we add it to our current map

	// Test for change
	bool notify(false) ;
	if (mBundleCentre != bundleCentre)
		notify = true ;

	mCentre = centre ;
	mBundleCentre = bundleCentre ;
	mMinFreq = minFreq ;
	mMaxFreq = maxFreq ;

    // Notify observers of the frequency that something has changed
	if (notify)
	    static_cast< Subject<IFrequencyChange>* >(this)->notify();

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqBand::del(unsigned index, std::shared_ptr<ICarrierFreqPolicy> policy, std::string& failReason)
{
	failReason = "" ;
	auto entry(mCarrierFreqs.find(index)) ;
	if (entry == mCarrierFreqs.end())
	{
		failReason = "Carrier not active on port. Index " + std::to_string(index) ;
		return false ;
	}

	if (isDebug(Loggable::LOG_DEBUG_VERBOSE))
	{
		logDebugVerbose("%s del: Freq %llu kHz [%llu  kHz .. %llu kHz]",
			mName.c_str(),
			entry->second.getCentre().get(Frequency::KHz),
			entry->second.getMin().get(Frequency::KHz),
			entry->second.getMax().get(Frequency::KHz)
		) ;
	}

	mCarrierFreqs.erase(entry) ;
	Frequency centre ;
	Frequency bundleCentre ;
	Frequency minFreq ;
	Frequency maxFreq ;
	if (!calcFrequencies(mCarrierFreqs, centre, minFreq, maxFreq, bundleCentre, policy, failReason))
		return false ;

	// Test for change
	bool notify(false) ;
	if (mBundleCentre != bundleCentre)
		notify = true ;

	mCentre = centre ;
	mBundleCentre = bundleCentre ;
	mMinFreq = minFreq ;
	mMaxFreq = maxFreq ;

    // Notify observers of the frequency that something has changed
	if (notify)
	    static_cast< Subject<IFrequencyChange>* >(this)->notify();

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CarrierFreqBand::getCentre() const
{
	return mCentre ;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CarrierFreqBand::getMinFrequency() const
{
	return mMinFreq ;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CarrierFreqBand::getMaxFrequency() const
{
	return mMaxFreq ;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CarrierFreqBand::getBundleCentre() const
{
	return mBundleCentre ;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency Mplane::CarrierFreqBand::getFrequency(void)
{
	return getBundleCentre() ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqBand::calcFrequencies(
		const std::map<unsigned, CarrierFreq>& carrierFreqs, Frequency& centre,
		Frequency& minFreq, Frequency& maxFreq,
		Frequency& bundleRealCentre,
		std::shared_ptr<ICarrierFreqPolicy> policy,
		std::string& failReason) const
{
	centre = mCentre ;

	// special case of empty list
	if (carrierFreqs.empty())
	{
		minFreq = Frequency(0.0) ;
		maxFreq = Frequency(0.0) ;
		return true ;
	}

	// Calculate the min & max values
	using MapEntry = std::pair<unsigned, CarrierFreq> ;
	auto minEntry( std::min_element(carrierFreqs.begin(), carrierFreqs.end(),
		[](const MapEntry& a, const MapEntry& b)->bool {
			return a.second.getMin() < b.second.getMin() ;
		}
	) ) ;
	minFreq = minEntry->second.getMin() ;

	auto maxEntry( std::max_element(carrierFreqs.begin(), carrierFreqs.end(),
		[](const MapEntry& a, const MapEntry& b)->bool {
			return a.second.getMax() < b.second.getMax() ;
		}
	) ) ;
	maxFreq = maxEntry->second.getMax() ;

	// Calculate the bundle centre
	Frequency bandwidth(maxFreq - minFreq) ;
	bundleRealCentre = minFreq + (bandwidth/2.0) ;

	if (isDebug(Loggable::LOG_DEBUG_VERBOSE))
	{
		logDebugVerbose("%s calcFreqs: %u entries", mName.c_str(), (unsigned)carrierFreqs.size()) ;
		logDebugVerbose("%s calcFreqs: * Current Centre %lld KHz", mName.c_str(), centre.getInt(Frequency::KHz)) ;
		logDebugVerbose("%s calcFreqs: * Max %lld KHz Min %lld KHz", mName.c_str(), maxFreq.getInt(Frequency::KHz), minFreq.getInt(Frequency::KHz)) ;
		logDebugVerbose("%s calcFreqs: * Band Max %lld KHz Band Min %lld KHz", mName.c_str(), mBandMax.getInt(Frequency::KHz), mBandMin.getInt(Frequency::KHz)) ;
		logDebugVerbose("%s calcFreqs: * Bundle Centre %lld KHz", mName.c_str(), bundleRealCentre.getInt(Frequency::KHz)) ;
	}

	// Check against end stops
	if (!policy->checkBundle(mPort, mBandMin, mBandMax, minFreq, maxFreq, failReason))
		return false ;

	// Use the policy to work out the new centre frequency (if policy doesn't allow moving then this will be the same value)
	centre = policy->calcCentre(mPort, centre, minFreq, maxFreq) ;

	if (isDebug(Loggable::LOG_DEBUG_VERBOSE))
	{
		logDebugVerbose("%s calcFreqs: * New Centre %lld KHz", mName.c_str(), centre.getInt(Frequency::KHz)) ;
		logDebugVerbose("%s calcFreqs: * LO Max %lld KHz LO Min %lld KHz",
			mName.c_str(),
			(centre + mLoHalfBandwidth).getInt(Frequency::KHz),
			(centre - mLoHalfBandwidth).getInt(Frequency::KHz)) ;
	}

	// Now check against the centre
	if (!policy->checkCentre(mPort, centre, mLoHalfBandwidth, minFreq, maxFreq, failReason))
		return false ;


	// All ok
	return true ;
}
