/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812Voltage.h
 * \brief     Voltage sensor for Amc7812 SPI emulator
 *
 *
 * \details
 *
 */


#ifndef AMC7812VOLTAGE_H_
#define AMC7812VOLTAGE_H_

#include <memory>
#include "Amc7812Profile.h"

namespace Mplane {

/*!
 * \class Amc7812Voltage
 */
class Amc7812Voltage : public Amc7812Profile {
public:
	static std::shared_ptr<IAmc7812Handler> factory(const std::string& name,
			float convertOffset, float convertFactor,
			float minVoltage, float maxVoltage, float step) ;

	Amc7812Voltage(const std::string& name, float convertOffset, float convertFactor,
			float minVoltage, float maxVoltage, float step) ;
	virtual ~Amc7812Voltage() ;
} ;

}

#endif /* AMC7812VOLTAGE_H_ */
