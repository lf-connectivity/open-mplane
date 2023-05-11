/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDelayUnit.h
 * \brief     Delay unit interface specification
 *
 *
 * \details   Interface to delay units classes. A delay unit knows how to convert delays from it's own units into
 * nanoseconds and back again. It also knows whether it uses the fibre line rate.
 *
 */


#ifndef IDELAYUNIT_H_
#define IDELAYUNIT_H_

#include <string>

namespace Mplane {

class IDelayUnit {
public:
	/**
	 * Does this delay unit need to know the line rate in order to convert to/from ns
	 * @return true if it uses the line rate; false otherwise
	 */
	virtual bool usesLineRate() const = 0 ;

	/**
	 * Convert from these units into nanoseconds
	 * @param delay	Delay in these units
	 * @param lineRateMHz	Optional line rate in MHz
	 * @return delay in nanoseconds
	 */
	virtual float to_ns(float delay, float lineRateMHz = 3072.0) const = 0 ;

	/**
	 * Convert from nanoseconds into these units
	 * @param delay	Delay in nanoseconds
	 * @param lineRateMHz	Optional line rate in MHz
	 * @return delay in these units
	 */
	virtual float from_ns(float delay_ns, float lineRateMHz = 3072.0) const = 0 ;

	/**
	 * Get a string representation of the units
	 * @param lineRateMHz	Optional line rate in MHz
	 * @return string containing units and optionally the line rate if it's used
	 */
	virtual std::string tostring(float lineRateMHz = 3072.0) const = 0 ;

	/**
	 * Get a string representation of the units
	 * @return string containing units
	 */
	virtual std::string unitstring() const = 0 ;


	virtual ~IDelayUnit() {}
};

} // namespace Mplane

#endif /* IDELAYUNIT_H_ */
