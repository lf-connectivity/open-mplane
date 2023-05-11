/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IMeasAdc.h
 * \brief     Virtual interface for measuring wideband ADC value
 *
 *
 * \details
 *
 */


#ifndef IMEASADC_H_
#define IMEASADC_H_

#include <stdexcept>
#include <memory>
#include "GlobalTypeDefs.h"
#include "Power.h"

namespace Mplane {

class IMeasAdc {
public:
	IMeasAdc() {}
	virtual ~IMeasAdc() {}

    /**
     * A static factory interface used to return a shared pointer
     * @param path
     * @return
     */
    static std::shared_ptr<IMeasAdc> getInterface( unsigned path ) ; /* throw ( std::invalid_argument); */

    /**
     * Get RX ADC RMS reading.
     * @param power Reference to Power value set with the ADC reading on success
     * @return RT_OK when measurement is ok
     */
    virtual ReturnType::State getAdcRms(Power &power) =0 ;


    /**
     * Get RX ADC RMS reading.
     * @param power Reference to Power value set with the ADC reading on success
     * @param adcRaw Reference to value set with the ADC raw reading on success
     * @return RT_OK when measurement is ok
     */
    virtual ReturnType::State getAdcRms(Power &power, unsigned& adcRaw) =0 ;


} ;

}

#endif /* IMEASADC_H_ */
