/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812Adc.h
 * \brief     Generic ADC emulator
 *
 *
 * \details
 *
 */


#ifndef AMC7812ADC_H_
#define AMC7812ADC_H_

#include <memory>
#include "Amc7812Profile.h"

namespace Mplane {

/*!
 * \class Amc7812Adc
 */
class Amc7812Adc : public Amc7812Profile {
public:
	/**
	 * Factory to create new handler for Amc7812 ADC
	 * @param name
	 * @param convertOffset
	 * @param convertFactor
	 * @param min
	 * @param max
	 * @param step
	 * @return
	 */
	static std::shared_ptr<IAmc7812Handler> factory(const std::string& name,
			float convertOffset, float convertFactor,
			float min, float max, float step) ;

	Amc7812Adc(const std::string& name, float convertOffset, float convertFactor,
			float min, float max, float step) ;
	virtual ~Amc7812Adc() ;
} ;

}

#endif /* AMC7812ADC_H_ */
