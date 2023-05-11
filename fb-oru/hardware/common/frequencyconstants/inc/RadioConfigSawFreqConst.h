/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonSawFreqConst.h
 * \brief     Get the SAW frequency constants from the IRadioConfig singleton
 *
 *
 * \details   Get the SAW frequency constants from the IRadioConfig singleton
 *
 */


#ifndef RADIOCONFIGSAWFREQCONST_H_
#define RADIOCONFIGSAWFREQCONST_H_


#include "ISawFrequencyConst.h"

namespace Mplane {

class RadioConfigSawFreqConst : public virtual ISawFrequencyConst {
public:
	virtual ~RadioConfigSawFreqConst() ;

    /**
     * Method to return the SAW filter's centre frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getCentre() const override ;

    /**
     * Method to return the SAW filter's bandwidth frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getBandwidth() const override ;

    /**
     * Method to return the digital centre frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getDigitalCentre() const override ;


protected:
    RadioConfigSawFreqConst() ;

private:
    Frequency mCentre;
    Frequency mBandwidth;
    Frequency mDigCentre;
} ;

}

#endif /* RADIOCONFIGSAWFREQCONST_H_ */
