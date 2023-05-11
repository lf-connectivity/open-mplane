/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812Profile.h
 * \brief     Data generator that creates data for SPI read based on a profile
 *
 *
 * \details
 *
 */


#ifndef AMC7812READER_H_
#define AMC7812READER_H_

#include <memory>
#include <functional>

#include "Amc7812Handler.h"

namespace Mplane {

/*!
 * \class Amc7812Profile
 */
class Amc7812Profile : public Amc7812Handler {
public:
	Amc7812Profile(const std::string& name, const std::string& measurement,
			float convertOffset, float convertFactor,
			float min, float max, float step) ;
	virtual ~Amc7812Profile() ;

protected:
	// Data generation profile
	using ProfileFunc = std::function<float(float& value, float& min, float& max, float& step)> ;

	// Set the profile to be used
	virtual void setProfile(ProfileFunc profile) ;

	// Set initial conditions
	virtual void setValue(float value) ;

	// Some useful profiles

	// Ramp up from min to max then ripple under max
	static float profileRampUp(float& value, float& min, float& max, float& step) ;

	// Saw between min and max
	static float profileSaw(float& value, float& min, float& max, float& step) ;

protected:
	// Hooks - override in derived objects
	virtual float getValue(unsigned address) override ;

private:
	std::string mMeasurement ;
	ProfileFunc mProfile ;
	float mMin ;
	float mMax ;
	float mStep ;
	float mValue ;
} ;

}

#endif /* AMC7812READER_H_ */
