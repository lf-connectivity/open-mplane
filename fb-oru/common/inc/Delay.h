/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Delay.h
 * \brief     Delay class
 *
 *
 * \details   Delay class that can be extended to understand multiple delay units and do calculations based on those
 * units
 *
 */


#ifndef DELAY_H_
#define DELAY_H_

#include <iostream>

#include "DelayUnit/IDelayUnit.h"
#include "ComparisonOperators.hpp"

// Need nanosecs as the default
#include "DelayUnit/DelayUnitNS.h"
#include "DelayUnit/DelayUnitUI.h"
//#include "DelayUnit/DelayUnitCLK.h"
//#include "DelayUnit/DelayUnitCLK128.h"
#include "DelayUnit/DelayUnitBF.h"

namespace Mplane {

class Delay : public ComparisonOperators< Delay >
{
public:
	// Use static constant instances of classes derived from IDelayUnit like an "expandable enum"
	static const DelayUnitNS& NS ;
	static const DelayUnitUI& UI ;
//	static const DelayUnitCLK& CLK ;
//	static const DelayUnitCLK128& CLK128 ;
	static const DelayUnitBF& BF ;


	/**
	 * default constructor
	 */
	Delay(float delay = 0.0, const IDelayUnit& unit = Delay::NS, float lineRateMHz = 3072.0) ;

	/**
	 * constructor based on copying the value of the other delay but using new units (use other line rate)
	 */
	Delay(const Delay& other, const IDelayUnit& unit) ;

	/**
	 * constructor based on copying the value of the other delay but using new units and a new line rate
	 */
	Delay(const Delay& other, const IDelayUnit& unit, float lineRateMHz) ;


	/**
	 * destructor
	 */
	~Delay() {} ;

	/**
	 * Get float representation of delay in specified units
	 * @param unit Required units
	 * @return delay value
	 */
	float get(const IDelayUnit& unit = Delay::NS) const ;

	/**
	 * Get float representation of delay in specified units
	 * @param unit Required units
	 * @param lineRateMHz Line rate required for the delay (used for UI and CLK delays)
	 * @return delay value
	 */
	float get(const IDelayUnit& unit, float lineRateMHz) const ;

	/**
	 * Get units
	 * @return units value
	 */
	const IDelayUnit& getUnit() const ;

	/**
	 * Get line rate
	 * @return line rate the delay was created with (MHz)
	 */
	float getLineRate() const ;

	/**
	 * Get integer representation of delay in specified units
	 * @param unit Required units
	 * @return integer delay value
	 */
	int getInt(const IDelayUnit& unit = Delay::NS) const ;

	/**
	 * Rounds the delay itself down to the delay's units
	 * @return as well as rounding the delay this method also returns the rounded delay
	 */
	Delay& round() ;

	/**
	 * Rounds the delay itself down to the specified units, changing the delay's units in the process
	 * @param unit Required units
	 * @return as well as rounding the delay this method also returns the rounded delay
	 */
	Delay& round(const IDelayUnit& unit) ;

	/**
	 * Rounds the delay itself down to the specified units, changing the delay's units and line rate in the process
	 * @param unit Required units
	 * @param lineRateMHz Line rate required for the delay (used for UI and CLK delays)
	 * @return as well as rounding the delay this method also returns the rounded delay
	 */
	Delay& round(const IDelayUnit& unit, float lineRateMHz) ;

	/**
	 * Rounds the delay itself up to the delay's units
	 * @return as well as rounding the delay this method also returns the rounded delay
	 */
	Delay& ceil() ;

	/**
	 * Rounds the delay itself up to the specified units, changing the delay's units in the process
	 * @param unit Required units
	 * @return as well as rounding the delay this method also returns the rounded delay
	 */
	Delay& ceil(const IDelayUnit& unit) ;

	/**
	 * Rounds the delay itself up to the specified units, changing the delay's units and line rate in the process
	 * @param unit Required units
	 * @param lineRateMHz Line rate required for the delay (used for UI and CLK delays)
	 * @return as well as rounding the delay this method also returns the rounded delay
	 */
	Delay& ceil(const IDelayUnit& unit, float lineRateMHz) ;

	/**
	 * Floors the delay itself down to the delay's units
	 * @return as well as rounding the delay this method also returns the rounded delay
	 */
	Delay& floor() ;

	/**
	 * Floors the delay itself down to the specified units, changing the delay's units in the process
	 * @param unit Required units
	 * @return as well as rounding the delay this method also returns the rounded delay
	 */
	Delay& floor(const IDelayUnit& unit) ;

	/**
	 * Floors the delay itself down to the specified units, changing the delay's units and line rate in the process
	 * @param unit Required units
	 * @param lineRateMHz Line rate required for the delay (used for UI and CLK delays)
	 * @return as well as rounding the delay this method also returns the rounded delay
	 */
	Delay& floor(const IDelayUnit& unit, float lineRateMHz) ;


	/**
	 * Changes the delay's units
	 * @param unit New units
	 * @return the changed delay
	 */
	Delay& setUnit(const IDelayUnit& unit) ;

	/**
	 * Changes the delay's units and line rate
	 * @param unit New units
	 * @param lineRateMHz New line rate
	 * @return the changed delay
	 */
	Delay& setUnit(const IDelayUnit& unit, float lineRateMHz) ;


	/**
	 * Output delay
	 * @param os	Output stream
	 */
	void show(std::ostream& os = std::cout) const ;

	/**
	 * Add a delta to the value
	 * @param delta	Offset to add
	 * @return reference to the updated delay
	 */
	Delay& add(const Delay& delta) ;

	/**
	 * Subtract a delta from the value
	 * @param delta	Offset to subtract
	 * @return reference to the updated delay
	 */
	Delay& sub(const Delay& delta) ;

	/**
	 * Add delay to this
	 * @param rhs	Delay to add
	 * @return reference to this
	 */
	Delay& operator+=(const Delay& rhs) ;

	/**
	 * Add delay to this
	 * @param rhs	Delay to add
	 * @return reference to this
	 */
	Delay& operator+=(const float rhs) ;

	/**
	 * Subtract delay from this
	 * @param rhs	Delay to Subtract
	 * @return reference to this
	 */
	Delay& operator-=(const Delay& rhs) ;

	/**
	 * Subtract delay from this
	 * @param rhs	Delay to Subtract
	 * @return reference to this
	 */
	Delay& operator-=(const float rhs) ;

	/**
     * @param rhs
     * @return return true if frequencies equal
     */
    virtual bool operator==(const Delay& rhs) const
	{
		return getInt(Delay::NS) == rhs.getInt(Delay::NS) ;
	}

    /**
     * Less than operator - provided for ComparisonOperators<>
     * @param rhs
     * @return return true if this < rhs frequency
     */
    virtual bool operator<(const Delay& rhs) const
	{
		return getInt(Delay::NS) < rhs.getInt(Delay::NS) ;
	}

private:
	/**
	 * Real delay in units defined by the IDelayUnit
	 */
	float mDelay ;

	/**
	 * Delay units - need a pointer to ensure we use the virtual methods properly. Since each DelayUnit has to create
	 * a static const of itself, we're safe keeping a pointer to it.
	 */
	const IDelayUnit* mUnit ;

	/**
	 * Line rate (in MHz) when this delay was created
	 */
	float mLineRateMHz ;
};


} // namespace Mplane


// Define some operators
inline std::ostream& operator << (std::ostream& os, const Mplane::Delay& delay)
{
	delay.show(os) ;
	return os;
}

// Add delay to something
inline Mplane::Delay operator + (const Mplane::Delay& lhs, const float& rhs)
{
	Mplane::Delay updated(lhs, lhs.getUnit()) ;
	updated.add(Mplane::Delay(rhs)) ;
	return updated ;
}

inline Mplane::Delay operator + (const float& lhs, const Mplane::Delay& rhs)
{
	Mplane::Delay updated(lhs) ;
	updated.add(rhs) ;
	return updated ;
}

inline Mplane::Delay operator + (const Mplane::Delay& lhs, const Mplane::Delay& rhs)
{
	Mplane::Delay updated(lhs, lhs.getUnit()) ;
	updated.add(rhs) ;
	return updated ;
}



// Subtract delay from something
inline Mplane::Delay operator - (const Mplane::Delay& lhs, const float& rhs)
{
	Mplane::Delay updated(lhs, lhs.getUnit()) ;
	updated.sub(Mplane::Delay(rhs)) ;
	return updated ;
}

inline Mplane::Delay operator - (const float& lhs, const Mplane::Delay& rhs)
{
	Mplane::Delay updated(lhs) ;
	updated.sub(rhs) ;
	return updated ;
}

inline Mplane::Delay operator - (const Mplane::Delay& lhs, const Mplane::Delay& rhs)
{
	Mplane::Delay updated(lhs, lhs.getUnit()) ;
	updated.sub(rhs) ;
	return updated ;
}

#endif /* DELAY_H_ */
