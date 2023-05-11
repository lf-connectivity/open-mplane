/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrierFreqPolicy.h
 * \brief     Carrier frequency policy
 *
 *
 * \details   Policy determines how carrier frequency is checked and how the LO centre frequency is calculated
 *
 */


#ifndef ICARRIERFREQPOLICY_H_
#define ICARRIERFREQPOLICY_H_

#include <string>
#include "Frequency.h"

namespace Mplane {

/**
 * Class that sets the policy for calculating the centre frequency
 */
class ICarrierFreqPolicy {
public:
	ICarrierFreqPolicy() {}
	virtual ~ICarrierFreqPolicy() {}

	/**
	 * method which calculates the centre frequency based on the provided data
	 */
	virtual Frequency calcCentre(unsigned port, const Frequency& centre,
			const Frequency& bundleMin, const Frequency& bundleMax) =0 ;

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
			std::string& errorString) =0 ;

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
			std::string& errorString) =0 ;
};

/**
 * Class that sets the policy for calculating the centre frequency
 */
class IDlFrequencyPolicy : public virtual ICarrierFreqPolicy {
public:
	IDlFrequencyPolicy() {}
	virtual ~IDlFrequencyPolicy() {}
};

class IUlFrequencyPolicy : public virtual ICarrierFreqPolicy {
public:
	IUlFrequencyPolicy() {}
	virtual ~IUlFrequencyPolicy() {}

	/**
	 * Set the current DL centre frequency for this antenna
	 */
	virtual void setDlCentre(const Frequency& dlCentre) =0 ;
};




}

#endif /* ICARRIERFREQPOLICY_H_ */
