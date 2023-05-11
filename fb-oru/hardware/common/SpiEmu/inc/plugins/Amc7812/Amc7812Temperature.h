/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812Temperature.h
 * \brief     Temperature sensor for Amc7812 SPI emulator
 *
 *
 * \details
 *
 */


#ifndef AMC7812TEMPERATURE_H_
#define AMC7812TEMPERATURE_H_

#include <memory>
#include "Amc7812Profile.h"

namespace Mplane {

/*!
 * \class Amc7812Temperature
 */
class Amc7812Temperature : public Amc7812Profile {
public:
	static std::shared_ptr<IAmc7812Handler> factory(const std::string& name,
			float convertOffset, float convertFactor,
			float startTemp, float endTemp, float step) ;

	Amc7812Temperature(const std::string& name, float convertOffset, float convertFactor,
			float startTemp, float endTemp, float step) ;
	virtual ~Amc7812Temperature() ;
} ;

}

#endif /* AMC7812TEMPERATURE_H_ */
