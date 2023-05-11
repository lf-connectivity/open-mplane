#ifndef _VRH_IFILTER_H_
#define _VRH_IFILTER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFilter.h
 * \brief     A file to contain a generic interface to a Filter module.
 *
 *
 * \details   This file defines a generic interface to a Filter module.
 *
 */

#include "GlobalTypeDefs.h"
#include "Module.h"
#include <stdexcept>
#include "Power.h"


namespace Mplane
{

/**
 * The FilterPaths enumeration type is used to set specific paths through
 * the filter, which will typically be setup prior to an ADC measurement cycle.
 *
 * The path is selected via a RF switch.
 *
 * A path of None will set the switch into a position that results in an ADC
 * reading of zero.
 */
enum class FilterPaths
{
    Forward     = 1,
    Reverse,
    Temperature,
    None
} ;




/*! \brief  Generic Filter module interface
 *
 * A virtual interface base class defining an interface to a Filter module.
 * The filter module contains hardware for measuring powers on all antenna ports
 * for Tx and VSWR purposes.
 *
 * Devices on the filter include: ADC, mux switch, attenuator, temperature sensor
 *
 * The ADC is located on the filter module to provide the measurement results.
 *
 * The generic filter interface provides methods to access the controlling
 * aspects of the filter and to retrieve the measurements.
 */
class IFilter : public Module
{
public:

    /**
     * A generic filter data structure that defines the typical power and temperature
     * data measured as part of the radio heads filter
     */
    class IPortData
    {
    public:
        virtual ~IPortData(){};
        /**
         * Return the measured forward power.
         * @return a reference to the forward power
         */
        virtual const Power & getForward() const = 0;
        /**
         * Return the measured reverse power.
         * @return a reference to the reverse power
         */
        virtual const Power & getReverse() const = 0;
        /**
         * Return the measured wide band digital power.
         * @return a reference to the wide band digital power
         */
        virtual const Power & getDigital() const = 0;;
        /**
         * Return the measured filter temperature.
         * @return a reference to the filter temperature
         */
        virtual const float & getTemperature() const = 0;
    };

    /**
     *
     * This method is called during a shutdown request to set the radio hardware to
     * a safe state as soon as possible.
     *
     * \return true if successful, false otherwise
     */
    virtual bool shutdown(void) = 0;

    /**
     * This method is used to retrieve the filter data associated with a specific
     * transmit port.
     *
     * @param port a zero based TX port index
     * @return a reference to the current filter data for port
     */
    virtual IFilter::IPortData*  getData( int port ) =0; /* throw ( std::invalid_argument) */


    virtual ~IFilter() { };

protected:

    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     */
    IFilter( int index, int number, const char* name ):
        Module( Module::FILTER, index, number, name ) { };


};


} /* namespace Mplane */

#endif /* _VRH_IFILTER_H_ */
