/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITxIfCal.h
 * \brief     Virtual interface to TX IF calibration classes
 *
 *
 * \details
 *
 */


#ifndef ITXIFCAL_H_
#define ITXIFCAL_H_

#include <memory>
#include <list>
#include <vector>
#include <map>

#include "FrequencyOffset.h"
#include "Power.h"
#include "Temperature.h"

namespace Mplane {


class ITxIfResponse
{
public:
	ITxIfResponse() {}
	virtual ~ITxIfResponse() {}

	virtual int getPath() =0 ;

    virtual float getTemperature() =0 ;

	virtual std::string getDate() =0 ;

	virtual bool getGain( FrequencyOffset frequencyOffset, Power &gain ) =0 ;
};

class ITxIfCal
{
public:
	ITxIfCal() {}
	virtual ~ITxIfCal() {}

	/**
	 * Utility method - uses the parameters to select the appropriate section of the cal data
	 * and return the gain.
	 * @return true if able to find suitable gain; false otherwise
	 */
	static bool getGain(int path, const FrequencyOffset& freqOffset, Power& gain) ;

	/**
	 * Get the Rx IF response for the specified path
	 * @param path
	 * @return
	 */
    virtual std::shared_ptr<ITxIfResponse> getTxIfResponse( int path ) =0 ;

    /**
     * Get version string
     * @return
     */
    virtual std::string getVersion() const =0 ;

    /**
     * Get country string
     * @return
     */
    virtual std::string getCountry() const =0 ;

    /**
     * Get facility string
     * @return
     */
    virtual std::string getFacility() const =0 ;

    /**
     * Get operator string
     * @return
     */
    virtual std::string getOperator() const =0 ;
};

}

#endif /* ITXIFCAL_H_ */
