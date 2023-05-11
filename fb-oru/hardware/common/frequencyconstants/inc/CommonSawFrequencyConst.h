/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonSawFrequencyConst.h
 * \brief     Base class for SAW filter frequency constants
 *
 *
 * \details
 *
 */


#ifndef COMMONSAWFREQCONST_H_
#define COMMONSAWFREQCONST_H_

#include "ISawFrequencyConst.h"

namespace Mplane {

class CommonSawFrequencyConst : public virtual ISawFrequencyConst {
public:
	virtual ~CommonSawFrequencyConst() ;

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
	CommonSawFrequencyConst() ;

protected:
    Frequency mCentre;
    Frequency mBandwidth;
    Frequency mDigCentre;
} ;

}

#endif /* COMMONSAWFREQCONST_H_ */
