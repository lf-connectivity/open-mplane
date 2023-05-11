/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITxCal.h
 * \brief     Virtual interface to TX calibration classes
 *
 *
 * \details
 *
 */


#ifndef ITXCAL_H_
#define ITXCAL_H_

#include <memory>
#include <list>
#include <vector>
#include <map>

#include "Frequency.h"
#include "Power.h"
#include "Temperature.h"

namespace Mplane {


class ITxOpenLoop
{
public:
	ITxOpenLoop() {}
	virtual ~ITxOpenLoop() {}

	virtual int getPath() =0 ;

	virtual float getCoefficient() =0 ;

	virtual std::string getDate() =0 ;

    virtual bool getData( Frequency frequency, Power power, float temperature,
            Power &baseBand, Power &correction, Power &rfAtten, float &calTemperature ) = 0;

    virtual bool getData( Frequency frequency, Power &baseBand, Power &rfAtten) = 0;

    virtual bool getPower( Frequency frequency, Power baseBand, Power rfAtten, Power &power) = 0;
};

class ITxCal
{
public:
	ITxCal() {}
	virtual ~ITxCal() {}

    virtual std::shared_ptr<ITxOpenLoop> getTxOpenLoop( int path ) =0 ;
};

}

#endif /* ITXCAL_H_ */
