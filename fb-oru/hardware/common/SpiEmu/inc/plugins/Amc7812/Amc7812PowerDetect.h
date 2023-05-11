/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812PowerDetect.h
 * \brief     TX power detector
 *
 *
 * \details   An Amc7812 ADC used for TX power detection in the system. Emulates the required TX power to drive a PCL
 *
 */


#ifndef AMC7812POWERDETECT_H_
#define AMC7812POWERDETECT_H_

#include <memory>
#include "Power.h"
#include "Amc7812Handler.h"

namespace Mplane {

/*!
 * \class Amc7812PowerDetect
 */
class Amc7812PowerDetect : public Amc7812Handler {
public:
	/**
	 * Factory to create new handler for Amc7812 ADC
	 * @param name
	 */
	static std::shared_ptr<IAmc7812Handler> factory(const std::string& name, unsigned txPort) ;

	Amc7812PowerDetect(const std::string& name, unsigned txPort) ;
	virtual ~Amc7812PowerDetect() ;

protected:
	// simplified hook - for read data just implement this to get the data and update any parameters
	virtual float getValue(unsigned address) ;

private:
	Power getCwPower() ;
	Power getIfAtten() ;
	Power getRfAtten() ;
	Power getDigScaling() ;

private:
	unsigned mTxPort ;
	Power mTargetPower ;
} ;

}

#endif /* AMC7812POWERDETECT_H_ */
