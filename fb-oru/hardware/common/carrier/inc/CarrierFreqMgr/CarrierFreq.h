/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierFreq.h
 * \brief     Stores the range of frequencies used by a carrier
 *
 *
 * \details
 *
 */


#ifndef CARRIERFREQ_H_
#define CARRIERFREQ_H_

#include "ICarrier.h"
#include "Frequency.h"

namespace Mplane {

class CarrierFreq {
public:
	CarrierFreq() ;
	CarrierFreq(const Frequency& centre, ICarrier::Type carrierType) ;
	virtual ~CarrierFreq() ;

	const Frequency& getCentre() const {
		return mCentre;
	}

	const Frequency& getMax() const {
		return mMax;
	}

	const Frequency& getMin() const {
		return mMin;
	}

private:
	Frequency mCentre ;
	ICarrier::Type mType ;
	Frequency mMin ;
	Frequency mMax ;
} ;

}

#endif /* CARRIERFREQ_H_ */
