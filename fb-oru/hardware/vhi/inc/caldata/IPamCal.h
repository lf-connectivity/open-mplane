/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPamCal.h
 * \brief     Virtual interface to PAM calibration classes
 *
 *
 * \details
 *
 */


#ifndef IPAMCAL_H_
#define IPAMCAL_H_

#include <memory>
#include <list>
#include <vector>
#include <map>
#include <string>

#include "Frequency.h"
#include "Power.h"
#include "Temperature.h"

namespace Mplane {


class IPaGainStep
{
public:
	IPaGainStep() {}
	virtual ~IPaGainStep() {}

	virtual int getPath() = 0 ;

	virtual float getCoefficient() = 0 ;

    virtual float getStepCoefficient() = 0;

	virtual std::string getDate() = 0 ;

    virtual bool getData( Frequency frequency, Power power, float &radioCalTemperature, float &pamCalTemperature,
    		unsigned int &vvaPwm, Power &lowGainOutputPower, Power &highGainOutputPower ) = 0;
};

class IPamCal
{
public:
	IPamCal() {}
	virtual ~IPamCal() {}

    /**
     * Method used to get access to the PA Gain step calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    virtual std::shared_ptr<IPaGainStep> getPaGainStep( int path ) = 0 ;
};

}

#endif /* IPAMCAL_H_ */
