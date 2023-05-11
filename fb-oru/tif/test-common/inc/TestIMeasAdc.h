/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIMeasAdc.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTIMEASADC_H_
#define TESTIMEASADC_H_

#include "IMeasAdc.h"

namespace Mplane {

class TestIMeasAdc : public virtual IMeasAdc {
public:
	TestIMeasAdc() ;
	virtual ~TestIMeasAdc() ;

    /**
     * Get RX ADC RMS reading.
     * @param power Reference to Power value set with the ADC reading on success
     * @return RT_OK when measurement is ok
     */
    virtual ReturnType::State getAdcRms(Power &power) override ;


    /**
     * Get RX ADC RMS reading.
     * @param power Reference to Power value set with the ADC reading on success
     * @param adcRaw Reference to value set with the ADC raw reading on success
     * @return RT_OK when measurement is ok
     */
    virtual ReturnType::State getAdcRms(Power &power, unsigned& adcRaw) override ;
} ;

}

#endif /* TESTIMEASADC_H_ */
