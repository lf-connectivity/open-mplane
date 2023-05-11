/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelayUnit.h
 * \brief     Base functionality for delay units. Should be derived from
 *
 *
 * \details
 *
 */


#ifndef DELAYUNIT_H_
#define DELAYUNIT_H_

#include <sstream>
#include "DelayUnit/IDelayUnit.h"

namespace Mplane {

class DelayUnit : public IDelayUnit
{
public:
	/**
	 * Does this delay unit need to know the line rate in order to convert to/from ns
	 * @return true if it uses the line rate; false otherwise
	 */
	virtual bool usesLineRate() const {return false ;} ;

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
	 * Get a string representation of the units including line rate if used
	 * @param lineRateMHz	Optional line rate in MHz
	 * @return string containing units and optionally the line rate if it's used
	 */
	virtual std::string tostring(float lineRateMHz = 3072.0) const {
		std::string str = unitstring() ;
		if (usesLineRate())
		{
			std::stringstream ss(str) ;
			ss << " @ " << lineRateMHz << " MHz" ;
			str += ss.str() ;
		}
		return str ;
	} ;

	/**
	 * Get a string representation of the units
	 * @return string containing units
	 */
	virtual std::string unitstring() const {
		return "";
	} ;

};

} // namespace Mplane


inline bool operator == (const Mplane::IDelayUnit& lhs, const Mplane::IDelayUnit& rhs)
{
	// compare using the unit string
	return lhs.unitstring().compare(rhs.unitstring()) == 0 ;
}

inline bool operator != (const Mplane::IDelayUnit& lhs, const Mplane::IDelayUnit& rhs)
{
	return ! operator == (lhs, rhs) ;
}


#endif /* DELAYUNITNS_H_ */
