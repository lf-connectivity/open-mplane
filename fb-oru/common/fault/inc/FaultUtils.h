/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultUtils.h
 * \brief     Fault helper utilities - static methods
 *
 *
 * \details
 *
 */


#ifndef FAULTUTILS_H_
#define FAULTUTILS_H_

#include <memory>
#include "IFault.h"

namespace Mplane {

/*!
 * \class FaultUtils
 */
class FaultUtils {
public:

	/**
	 * Process an under temperature fault. When the temperature goes below the trip threshold then the fault is raised. When the temperature rises
	 * above the clear threshold then the fault is cleared.
	 * @param fault
	 * @param temperature
	 * @param tripThreshold
	 * @param clearThreshold
	 * @return whether fault is raised or not
	 */
	static bool setUnderTemperatureFault(std::shared_ptr<IFault> fault, float temperature,
			float tripThreshold, float clearThreshold) ;

	/**
	 * Process an over temperature fault. When the temperature goes above the trip threshold then the fault is raised. When the temperature falls
	 * below the clear threshold then the fault is cleared.
	 * @param fault
	 * @param temperature
	 * @param tripThreshold
	 * @param clearThreshold
	 * @return whether fault is raised or not
	 */
	static bool setOverTemperatureFault(std::shared_ptr<IFault> fault, float temperature,
			float tripThreshold, float clearThreshold) ;
} ;

}

#endif /* FAULTUTILS_H_ */
