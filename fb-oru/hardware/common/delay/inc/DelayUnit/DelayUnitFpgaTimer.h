/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelayUnitUI.h
 * \brief     Provide support for fpga timer units
 *
 *
 * \details
 *
 */


#ifndef DELAYUNITFPGATIMER_H_
#define DELAYUNITFPGATIMER_H_

#include "DelayUnit/DelayUnit.h"

namespace Mplane {

class DelayUnitFpgaTimer : public DelayUnit
{
public:
	static const DelayUnitFpgaTimer UNIT ;

	/**
	 * Convert from these units into nanoseconds
	 * @param delay	Delay in these units
	 * @param lineRateMHz	Optional line rate in MHz
	 * @return delay in nanoseconds
	 */
	virtual float to_ns(float delay, float lineRateMHz = 3072.0) const  ;

	/**
	 * Convert from nanoseconds into these units
	 * @param delay	Delay in nanoseconds
	 * @param lineRateMHz	Optional line rate in MHz
	 * @return delay in these units
	 */
	virtual float from_ns(float delay_ns, float lineRateMHz = 3072.0) const  ;

	/**
	 * Get a string representation of the units
	 * @return string containing units
	 */
	virtual std::string unitstring() const {
		return "FpgaTimer";
	} ;

};

} // namespace Mplane


#endif /* DELAYUNITFPGATIMER_H_ */
