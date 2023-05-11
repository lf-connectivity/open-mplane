/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvFreq.h
 * \brief     Virtual interface to FREQ type
 *
 *
 * \details
 *
 */


#ifndef IDVFREQ_H_
#define IDVFREQ_H_

#include "Frequency.h"

namespace Mplane {

class IDvFreq {
public:
	IDvFreq() {}
	virtual ~IDvFreq() {}

    /**
     * Set the value of the the variant to the frequency value.
     *
     * @param value
     */
    virtual bool setFreq( const Frequency& value ) =0 ;

    /**
     * Method returns the current variant value as a frequency
     *
     * @return variant value as a frequency
     */
    virtual Frequency toFreq() const =0 ;
} ;

}

#endif /* IDVFREQ_H_ */
