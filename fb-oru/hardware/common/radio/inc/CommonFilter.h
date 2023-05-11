#ifndef _RADIO_HARDWARE_COMMONFILTER_H_
#define _RADIO_HARDWARE_COMMONFILTER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonFilter.h
 * \brief     A file to contain the common implementation of a generic Filter.
 *
 *
 * \details   This file defines the common implementation of a generic Filter
 *            and expands on it if necessary.
 *
 */

#include "IFilter.h"
#include <string>

namespace Mplane
{

class CommonFilterPortData: public IFilter::IPortData
{
public:
    virtual ~CommonFilterPortData(){};
    /**
     * Return the measured forward power.
     * @return a reference to the forward power
     */
    virtual const Power & getForward() const;
    /**
     * Return the measured reverse power.
     * @return a reference to the reverse power
     */
    virtual const Power & getReverse() const;
    /**
     * Return the measured wide band digital power.
     * @return a reference to the wide band digital power
     */
    virtual const Power & getDigital() const;
    /**
     * Return the measured filter temperature.
     * @return a reference to the filter temperature
     */
    virtual const float & getTemperature() const;

    void setForward( Power power );

    void setReverse( Power power );

    void setDigital( Power power );

    void setTemperature( float temperature );

protected:
    Power mForward;
    Power mReverse;
    Power mDigital;
    float mTemperature;

};

class CommonFilter: public IFilter
{

public:

    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *  This is pure virtual and MUST be implemented by inheritors.
     *
     *  Means that this CommonFilter class does not provide any Filter-type
     *  specific initialisation. That is left to the inheritors who know what
     *  filter module is being used.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResult - eg. to ReturnType::RT_OK if all is ok
     *  mInitResultString - eg. to "Filter INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit() = 0;

    /**
     * This method is called during a shutdown request to set the radio hardware to
     * a safe state as soon as possible.
     *
     * \return true if successful, false otherwise
     */
    virtual bool shutdown(void);

    /**
     * This method is used to retrieve the filter data associated with a specific
     * transmit port.
     *
     * @param port a zero based TX port index
     * @return a reference to the current filter data for port
     */
    virtual IFilter::IPortData* getData( int port ) =0; /* throw ( std::invalid_argument) */


    /*! \brief  Dump the Filter status
     *
     *  Dump the state of the Filter to the console or log file
     */
    virtual void show(void);

    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param index  zero-based index of the Filter
     *  \param number one-based Filter number
     *  \param name   name string for the Filter
     */
    CommonFilter(int index, int number, const char* name);

    /*! \brief Destructor
     *
     */
    virtual ~CommonFilter();


private:

};

} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONFILTER_H_ */
