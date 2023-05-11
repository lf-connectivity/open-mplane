/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITxCalPort.h
 * \brief     Calibration and low-level access to TX port
 *
 *
 * \details
 *
 */


#ifndef ITXCALPORT_H_
#define ITXCALPORT_H_

#include <memory>
#include <vector>
#include "Frequency.h"
#include "GlobalTypeDefs.h"

namespace Mplane {

class ITxCalPort {
public:
	ITxCalPort() {}
	virtual ~ITxCalPort() {}

    /*! \brief  Get the calibration frequency
     *
     *  Method to retrieve the calibration frequency. This is the base frequency
     *  at which the transmit path is calibrated.
     *
     *  The frequency returned is in units of kHz.
     *
     *  \return Tx port calibration frequency in kHz
     */
    virtual const Frequency getCalFrequency(void) const = 0;

    /**
     * Method used to update the calibration data associated with the output power-detector
     * @param coeff
     * @param offset
     * @param calPower
     * @return
     */
    virtual ReturnType::State setPowerDetCal( float coeff,
                                              float offset,
                                              float calPower ) = 0;

    /**
     * Method used to measure the average power from the power detector.
     *
     * @return average RF power measured by the power detector.
     */
    virtual int getAvgRawRfPower() =0 ;

    /**
     * Method used to return the spread of the raw values in the RF power moving average.
     *
     * @return
     */
    virtual int getRawRfPowerVariantion() =0 ;

    /**
     * Method used to read the raw RF power ADC reading.
     * @return
     */
    virtual int getRawRfPower() =0 ;

    /**
     * Method used to set the RAW VVA attenuation using the pulse width modulation count value.
     * @param pwm
     */
    virtual ReturnType::State setRawRFAtten( unsigned int pwm ) =0 ;



} ;

/**
 * The ITxCalPortFactory is a polymorphic Tx port interface factory that allows a
 * specific radio implementation to set the number of Tx ports supported by
 * that particular hardware implementation, create the actual Tx port, again
 * specific to the radio implementation and return them as a vector that is
 * stored in the common radio implementation.
 *
 * @note This factory must be implemented by each radio type where its physical
 * characteristics have nothing in common with any existing implementation.
 */
class ITxCalPortFactory
{
public:
    /**
     * This interface must be implemented by each radio implementation
     * type. The caller passes in a variable by reference that will be used to
     * return the number of ports created. The return value, is a vector of
     * pointers to the common ITxCalPort interface.
     *
     * Any radio specific implementation code that is aware of the actual Tx port
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * \param maxPorts a reference to a variable that is used to return the number of ports
     * \return a vector containing maxPorts Rx ports interface pointers.
     */
    static std::vector< std::shared_ptr<ITxCalPort> > createPorts( int &maxPorts );

    /**
     * This interface must be implemented by each radio implementation
     * type. Returns a previous created list of ports. The return value, is a vector of
     * pointers to the common ITxCalPort interface.
     *
     * Any radio specific implementation code that is aware of the actual Tx port
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * \return a vector containing maxPorts Rx ports interface pointers.
     */
    static std::vector< std::shared_ptr<ITxCalPort> > getPorts( );
};


}

#endif /* ITXCALPORT_H_ */
