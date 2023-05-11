/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRxCal.h
 * \brief     Virtual interface to RX calibration classes
 *
 *
 * \details
 *
 */


#ifndef IRXCAL_H_
#define IRXCAL_H_

#include <memory>
#include <list>
#include <vector>
#include <map>

#include "Frequency.h"
#include "Power.h"
#include "Temperature.h"

namespace Mplane {


class IRxOpenLoop
{
public:
	IRxOpenLoop() {}
	virtual ~IRxOpenLoop() {}

	virtual int getPath() =0 ;

	virtual float getCoefficient() =0 ;

	virtual float getGainTarget() = 0;

	virtual std::string getDate() =0 ;

	virtual bool getIfAtten( Frequency frequency, Power &ifAtten ) =0 ;
	virtual bool getIfAtten( Frequency frequency, Power &ifAtten, Temperature& calTemperature ) =0 ;

	virtual bool getRfAtten( Frequency frequency, Power amplitude, Power &rfAtten ) =0 ;
    virtual bool getRfAttenAndScaler( Power amplitude, Frequency frequency, Power tempCompIdeal, Power &rfAtten, Power &scaler ) =0 ;
    virtual Power getTempCompTarget(Frequency frequency, Power target, float temperature) = 0;
	virtual bool getNearestGainReduction(Power reduction, Frequency frequency, Power &nearestIFDSARed, Power &nearestGainRed) =0;

	virtual Power dBfsTodBm( Frequency frequency, Power rfDsa, float temperature ) =0 ;
	virtual Power dBfsTodBm(Frequency frequency, Power rfDsa) = 0;
	virtual Power getRfdsaForFrequency(Frequency frequency) = 0;
};

class IRxCal
{
public:
	IRxCal() {}
	virtual ~IRxCal() {}

    virtual std::shared_ptr<IRxOpenLoop> getRxOpenLoop( int path ) =0 ;
};

}

#endif /* IRXCAL_H_ */
