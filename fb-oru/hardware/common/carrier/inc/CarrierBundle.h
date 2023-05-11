/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierBundle.h
 * \brief     Classify carriers as a bundle
 *
 *
 * \details   Classify the carriers on an antenna in terms of their total bandwidth and the gaps
 *
 */


#ifndef CARRIERBUNDLE_H_
#define CARRIERBUNDLE_H_

#include <iostream>
#include <vector>

#include "ICarrierBundle.h"

namespace Mplane {


class CarrierBundle : public virtual ICarrierBundle {
public:
	/**
	 * Constructor
	 */
	CarrierBundle(unsigned numCarriers, const Frequency& totalBw, const Frequency& maxGap,
			const Frequency& sumBw, const Frequency& aveCentre) ;
	CarrierBundle() ;

	/**
	 * Copy settings
	 */
	virtual void set(const ICarrierBundle& rhs) override ;
	virtual void set(std::shared_ptr<ICarrierBundle> rhs) override ;

	/**
	 * Get the list of thresholds
	 * @return list of thresholds (dB)
	 */
	virtual std::vector<Power> getThresholds() const override ;

	/**
	 * Output bundle
	 * @param os	Output stream
	 */
	virtual void show(std::ostream& os = std::cout) const override ;

	/**
	 * Check for equal settings
	 * @param rhs	Carrier bundle to compare with
	 * @return true if settings are equal
	 */
	virtual bool operator==(const ICarrierBundle& rhs) const override;
	virtual bool operator!=(const ICarrierBundle& rhs) const override;
	virtual bool operator==(std::shared_ptr<ICarrierBundle> rhs) const override ;
	virtual bool operator!=(std::shared_ptr<ICarrierBundle> rhs) const override ;

	/**
	 * Get the bundle bandwidth
	 */
	virtual ICarrierBundle::BundleBw getBw() const override ;

	/**
	 * Get the bundle gap
	 */
	virtual ICarrierBundle::BundleGap getGap() const override ;

	/**
	 * Get the number of active carriers in the bundle
	 */
	virtual unsigned getNumCarriers() const override ;

	/**
	 * Get the sum of the carrier BW's
	 * e.g. If 2 carriers LTE5 and LTE10, sunBw will be 15M
	 */
	virtual Frequency getSumBw() const override ;

	/**
	 * Get the maximum gap between the carriers
	 */
	virtual Frequency getMaxGap() const override ;

	/**
	 * Get the carrier average centre frequency
	 * e.g. if the centre frequencies are 755.5 and 789.5 the average is 772.5
	 */
	virtual Frequency getAveCentre() const override ;


private:
	ICarrierBundle::BundleBw quantiseBw(const Frequency& totalBw) const ;
	ICarrierBundle::BundleGap quantiseGap(const Frequency& maxGap) const ;

private:
	unsigned mNumCarriers ;
	ICarrierBundle::BundleBw mBw ;
	ICarrierBundle::BundleGap mGap ;
	Frequency mSumBw ;
	Frequency mMaxGap ;
	Frequency mAveCentre ;
};

}

// Make it printable
inline std::ostream& operator << (std::ostream& os, const Mplane::ICarrierBundle& bundle)
{
	bundle.show(os) ;
	return os;
}

inline std::ostream& operator << (std::ostream& os, std::shared_ptr<Mplane::ICarrierBundle> bundle)
{
	bundle->show(os) ;
	return os;
}


#endif /* CARRIERBUNDLE_H_ */
