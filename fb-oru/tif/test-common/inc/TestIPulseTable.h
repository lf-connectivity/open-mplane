/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIPulseTable.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTIPULSETABLE_H_
#define TESTIPULSETABLE_H_

#include "IPulseTable.h"

namespace Mplane {

class TestIPulseTable : virtual public IPulseTable {
public:
	TestIPulseTable() : mNoData() {}
	virtual ~TestIPulseTable() {}

	/**
	 * Given the parameters, returns the appropriate pulse data
	 */
	virtual const std::vector<int>& getPulseData(
		const ICarrierHardwareTypes::AirstdType airstd,
		const ICarrierHardwareTypes::ChbwType chbw,
		const CfrRate cfrRate
	) const override { return mNoData; }


private:
	std::vector<int> mNoData ;
} ;

}

#endif /* TESTIPULSETABLE_H_ */
