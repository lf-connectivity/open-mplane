/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPulseTable.h
 * \brief     Virtual interface to CFR pulse table data
 *
 *
 * \details
 *
 */


#ifndef IPULSETABLE_H_
#define IPULSETABLE_H_

#include <memory>
#include <vector>
#include "ICarrier.h"
#include "ICarrierHardwareTypes.h"

namespace Mplane {

class IPulseTable {
public:
	IPulseTable() {}
	virtual ~IPulseTable() {}

	/**
	 * Get singleton instance
	 */
	static std::shared_ptr<IPulseTable> getInstance() ;

	/**
	 * Given the parameters, returns the appropriate pulse data
	 */
	virtual const std::vector<float>* getPulseData(
		const ICarrierHardwareTypes::AirstdType airstd,
		const ICarrierHardwareTypes::ChbwType chbw
	) const =0 ;

	/**
	 * Given the parameters, returns the appropriate pulse data
	 */
	virtual const std::vector<float>* getNrfr1PulseData(
		const ICarrierHardwareTypes::AirstdType airstd,
		const ICarrierHardwareTypes::ChbwType chbw,
		const ICarrier::ScsType scs
	) const =0 ;

} ;

}

#endif /* IPULSETABLE_H_ */
