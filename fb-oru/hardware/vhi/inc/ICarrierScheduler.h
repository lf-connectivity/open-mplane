/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrierScheduler.h
 * \brief     Virtual interface to allow carrier scheduling to be overridden
 *
 *
 * \details   Normally carriers are scheduled based on available resources. This interface allows for a "static mapping" to be enforced
 *
 */


#ifndef VHI_INC_ICARRIERSCHEDULER_H_
#define VHI_INC_ICARRIERSCHEDULER_H_

#include <functional>
#include "ICarrierHardwareTypes.h"

namespace Mplane {

/*!
 * \class  ICarrierScheduler
 * \brief
 * \details
 *
 */
class ICarrierScheduler {
public:
	ICarrierScheduler() {}
	virtual ~ICarrierScheduler() {}

	/**
	 * Data used in a scheduling static map
	 */
	using CarrierScheduleFunc = std::function<ICarrierHardwareTypes::ScheduleStatus(const unsigned carrierIndex, const unsigned antenna,
			const ICarrierHardwareTypes::AirstdType airstd, const ICarrierHardwareTypes::ChbwType chbw, const unsigned fibre,
			unsigned& fibreIndex, unsigned& chain, unsigned& chainIndex)> ;

	/**
	 * Set the "map" to use for scheduling carriers
	 */
	virtual bool setStaticScheduling(CarrierScheduleFunc ulSchedule, CarrierScheduleFunc dlSchedule) =0 ;

} ;

}

#endif /* VHI_INC_ICARRIERSCHEDULER_H_ */
