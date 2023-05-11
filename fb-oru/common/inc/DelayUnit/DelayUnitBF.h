/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelayUnitBF.h
 * \brief     Provide support for basic frames
 *
 *
 * \details
 *
 */


#ifndef DELAYUNITBF_H_
#define DELAYUNITBF_H_

#include "DelayUnit/DelayUnit.h"

namespace Mplane {

class DelayUnitBF : public DelayUnit
{
public:
	static const DelayUnitBF UNIT ;

	/**
	 * Convert from these units into nanoseconds
	 * @param delay	Delay in these units
	 * @param lineRateMHz	Optional line rate in MHz
	 * @return delay in nanoseconds
	 */
	virtual float to_ns(float delay, float lineRateMHz = 0.0) const  ;

	/**
	 * Convert from nanoseconds into these units
	 * @param delay	Delay in nanoseconds
	 * @param lineRateMHz	Optional line rate in MHz
	 * @return delay in these units
	 */
	virtual float from_ns(float delay_ns, float lineRateMHz = 0.0) const  ;

	/**
	 * Get a string representation of the units
	 * @return string containing units
	 */
	virtual std::string unitstring() const {
		return "BF";
	} ;

};

} // namespace Mplane


#endif /* DELAYUNITBF_H_ */
