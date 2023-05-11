/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISwrCal.h
 * \brief     Virtual interface to RRX calibration classes
 *
 *
 * \details
 *
 */


#ifndef ISWRCAL_H_
#define ISWRCAL_H_

#include <memory>
#include <list>
#include <vector>
#include <map>

#include "Frequency.h"
#include "Power.h"
#include "Temperature.h"

namespace Mplane {

/**
 * This interface defines the methods used access calibration data associated with
 * calibrating the amplifier reverse path power measurement.
 *
 * This measurement is used in VSWR monitoring to check the health
 * of the antenna connection to the power amplifier.
 */
class ISwrOpenLoop
{
public:
	ISwrOpenLoop() {}
	virtual ~ISwrOpenLoop() {}

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

class ISwrCal
{
public:
	ISwrCal() {}
	virtual ~ISwrCal() {}

    virtual std::shared_ptr<ISwrOpenLoop> getSwrOpenLoop( int path ) =0 ;
};

}

#endif /* ISWRCAL_H_ */
