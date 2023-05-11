/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITestDpdVswr.h
 * \brief     Interface object for data passed to TESTDPD client interested in VSWR measurements
 *
 *
 * \details
 *
 */


#ifndef ITESTDPDVSWR_H_
#define ITESTDPDVSWR_H_

#include "data/IDpdData.h"
#include "Power.h"

namespace Mplane {

class ITestDpdVswr : public virtual IDpdData {
public:
	ITestDpdVswr() {}
	virtual ~ITestDpdVswr() {}

	/**
	 * Get the VSWR power measurement for a TX port
	 * @param port 0-based index
	 * @return measurement
	 */
	virtual Power getMeasurement(unsigned port) const =0 ;

} ;

}

#endif /* ITESTDPDVSWR_H_ */
