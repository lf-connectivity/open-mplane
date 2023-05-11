/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelayUnitNS.h
 * \brief     Provide support for nanoseconds
 *
 *
 * \details
 *
 */


#ifndef DELAYUNITNS_H_
#define DELAYUNITNS_H_

#include "DelayUnit/DelayUnit.h"

namespace Mplane {

class DelayUnitNS : public DelayUnit
{
public:
	static const DelayUnitNS UNIT ;

	/**
	 * Convert from these units into nanoseconds
	 * @param delay	Delay in these units
	 * @param lineRateMHz	Optional line rate in MHz
	 * @return delay in nanoseconds
	 */
	virtual float to_ns(float delay, float lineRateMHz = 0.0) const { return delay; } ;

	/**
	 * Convert from nanoseconds into these units
	 * @param delay	Delay in nanoseconds
	 * @param lineRateMHz	Optional line rate in MHz
	 * @return delay in these units
	 */
	virtual float from_ns(float delay_ns, float lineRateMHz = 0.0) const { return delay_ns; } ;

	/**
	 * Get a string representation of the units
	 * @return string containing units
	 */
	virtual std::string unitstring() const {
		return "ns";
	} ;

};

} // namespace Mplane


#endif /* DELAYUNITNS_H_ */
