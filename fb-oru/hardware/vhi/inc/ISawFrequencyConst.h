/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I.h
 * \brief     Virtual interface to SAW filter related frequency constants
 *
 *
 * \details
 *
 */


#ifndef ISAWFREQCONST_H_
#define ISAWFREQCONST_H_

#include <memory>
#include "Frequency.h"

namespace Mplane {

class ISawFrequencyConst {
public:
	ISawFrequencyConst() {}
	virtual ~ISawFrequencyConst() {}

    /**
     * Method to return the SAW filter's centre frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getCentre() const = 0;

    /**
     * Method to return the SAW filter's bandwidth frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getBandwidth() const = 0;

    /**
     * Method to return the digital centre frequency.
     * @return Frequency constant data
     */
    virtual const Frequency getDigitalCentre() const = 0;


} ;

class ISawFrequencyConstFactory
{
public:
    /**
     * Singleton
     */
    static std::shared_ptr<ISawFrequencyConst> getInterface();

};


}

#endif /* ISAWFREQCONST_H_ */
