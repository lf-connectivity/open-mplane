/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrierBundle.h
 * \brief     Virtual interface to carrier bundle
 *
 *
 * \details   Classify the carriers on an antenna in terms of their total bandwidth and the gaps
 *
 */


#ifndef ICARRIERBUNDLE_H_
#define ICARRIERBUNDLE_H_

#include <ostream>
#include <memory>
#include <vector>

#include "Power.h"
#include "Frequency.h"

namespace Mplane {

/*!
 * \class ICarrierBundle
 */
class ICarrierBundle {
public:
	ICarrierBundle() {}
	virtual ~ICarrierBundle() {}

	// carrier bundle total bandwidths
	enum BundleBw {
		CB_BW_0		= 0,
		CB_BW_1M4	= 1,
		CB_BW_3		= 2,
		CB_BW_5		= 3,
		CB_BW_10	= 4,
		CB_BW_20	= 5,
		CB_BW_30	= 6,
		CB_BW_40	= 7,
		CB_BW_50	= 8,
		CB_BW_60	= 9,
		CB_BW_70	= 10,
		CB_BW_80	= 11,
		CB_BW_90	= 12,
		CB_BW_100	= 13,
	};

	// carrier bundle max gaps
	enum BundleGap {
		CB_GAP_0	= 0,
		CB_GAP_10	= 1,
		CB_GAP_20	= 2,
		CB_GAP_30	= 3,
		CB_GAP_40	= 4,
		CB_GAP_50	= 5,
		CB_GAP_60	= 6,
		CB_GAP_70	= 7,
		CB_GAP_80	= 8,
		CB_GAP_90	= 9,
	};

	enum BundleLimits {
		CB_BW_MAX	= CB_BW_100,
		CB_GAP_MAX	= CB_GAP_90
	};

	/**
	 * Copy settings
	 */
	virtual void set(const ICarrierBundle& rhs) =0 ;
	virtual void set(std::shared_ptr<ICarrierBundle> rhs) =0 ;

	/**
	 * Get the list of thresholds
	 * @return list of thresholds (dB)
	 */
	virtual std::vector<Power> getThresholds() const =0 ;

	/**
	 * Output bundle
	 * @param os	Output stream
	 */
	virtual void show(std::ostream& os = std::cout) const =0 ;

	/**
	 * Check for equal settings
	 * @param rhs	Carrier bundle to compare with
	 * @return true if settings are equal
	 */
	virtual bool operator==(const ICarrierBundle& rhs) const =0 ;
	virtual bool operator!=(const ICarrierBundle& rhs) const =0 ;
	virtual bool operator==(std::shared_ptr<ICarrierBundle> rhs) const =0 ;
	virtual bool operator!=(std::shared_ptr<ICarrierBundle> rhs) const =0 ;

	/**
	 * Get the bundle bandwidth
	 */
	virtual BundleBw getBw() const =0 ;

	/**
	 * Get the bundle gap
	 */
	virtual BundleGap getGap() const =0 ;

	/**
	 * Get the number of active carriers in the bundle
	 */
	virtual unsigned getNumCarriers() const =0 ;

	/**
	 * Get the sum of the carrier BWs
	 * e.g. If 2 carriers LTE5 and LTE10, sunBw will be 15M
	 */
	virtual Frequency getSumBw() const =0 ;

	/**
	 * Get the maximum gap between the carriers
	 */
	virtual Frequency getMaxGap() const =0 ;

	/**
	 * Get the carrier average centre frequency
	 * e.g. if the centre frequencies are 755.5 and 789.5 the average is 772.5
	 */
	virtual Frequency getAveCentre() const =0 ;
} ;

}

#endif /* ICARRIERBUNDLE_H_ */
