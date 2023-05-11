/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISRxCal.h
 * \brief     Virtual interface to RRX calibration classes
 *
 *
 * \details
 *
 */


#ifndef ISRXCAL_H_
#define ISRXCAL_H_

#include <memory>
#include <list>
#include <vector>
#include <map>

#include "Frequency.h"
#include "Power.h"
#include "Temperature.h"

namespace Mplane {

class ISRxOpenLoop
{
public:
	ISRxOpenLoop() {}
	virtual ~ISRxOpenLoop() {}

	/**
	 * Get the path associated with the calibration data.
	 * @return Srx path
	 */
	virtual int getPath() =0 ;

	/**
	 * Get the SRX path temperature coefficient.
	 *
	 * @return temperature coefficient
	 */
	virtual float getCoefficient() =0 ;

	/**
	 * Get the calibration date
	 * @return
	 */
	virtual std::string getDate() =0 ;

	/**
	 * Find the dBfs to dbM conversion factor given the current attenuator setting,
	 * frequency and temperature. This is used to convert the SRX RSSI reading from
	 * dBfs to the actual dBm power.
	 *
	 * @param frequency
	 * @param rfDsa
	 * @param temperature
	 * @return  power correction factor.
	 */
	virtual Power dBfsTodBm( Frequency frequency, Power rfDsa, float temperature ) =0 ;

	/**
	 * Look through the calibration file for the attenuation value that matches the nearest
	 * target measurement power.
	 *
	 * @param frequency
	 * @param target measure power
	 * @return
	 */
	virtual Power findNearestAttenuation( Frequency frequency, Power target ) = 0;

};

class ISRxCal
{
public:
	ISRxCal() {}
	virtual ~ISRxCal() {}

    virtual std::shared_ptr<ISRxOpenLoop> getSRxOpenLoop( int path ) =0 ;
};

}

#endif /* ISRXCAL_H_ */
