/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhFreqPolicy.h
 * \brief     Simple frequency centring policy
 *
 *
 * \details
 *
 */


#ifndef RRHFREQUENCYPOLICY_H_
#define RRHFREQUENCYPOLICY_H_

#include "ICarrierFreqPolicy.h"

namespace Mplane {

class RrhFreqPolicy : public virtual ICarrierFreqPolicy {
public:
	RrhFreqPolicy() ;
	virtual ~RrhFreqPolicy() ;

	/**
	 * "function" call which calculates the centre frequency based on the provided data
	 */
	virtual Frequency calcCentre(unsigned port, const Frequency& centre,
			const Frequency& bundleMin, const Frequency& bundleMax) override ;

	/**
	 * Check that the carrier bundle is within max limits. If outside bounds sets the errorString
	 * @param port
	 * @param centre
	 * @param halfBandwidth
	 * @param bundleMin
	 * @param bundleMax
	 * @param errorString
	 * @return true if centre within bounds
	 */
	virtual bool checkBundle(unsigned port,
			const Frequency& bandMin, const Frequency& bandMax,
			const Frequency& bundleMin, const Frequency& bundleMax,
			std::string& errorString) override ;

	/**
	 * Check the LO centre covers the carrier bundle. If centre is outside bounds sets the errorString
	 * @param port
	 * @param centre
	 * @param halfBandwidth
	 * @param bundleMin
	 * @param bundleMax
	 * @param errorString
	 * @return true if centre within bounds
	 */
	virtual bool checkCentre(unsigned port, const Frequency& centre,
			const Frequency& halfBandwidth,
			const Frequency& bundleMin, const Frequency& bundleMax,
			std::string& errorString) override ;

};

class RrhUlFreqPolicy : public RrhFreqPolicy, public virtual IUlFrequencyPolicy
{
public:
	RrhUlFreqPolicy() {}
	virtual ~RrhUlFreqPolicy() {}

	/**
	 * Set the current DL centre frequency for this antenna - does nothing here
	 */
	virtual void setDlCentre(const Frequency& dlCentre) override {}
};

class RrhDlFreqPolicy : public RrhFreqPolicy, public virtual IDlFrequencyPolicy
{
public:
	RrhDlFreqPolicy() {}
	virtual ~RrhDlFreqPolicy() {}
};


}

#endif /* RRHFREQUENCYPOLICY_H_ */
