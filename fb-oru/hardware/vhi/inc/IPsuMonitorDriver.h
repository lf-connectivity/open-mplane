/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPsuMonitorDriver.h
 * \brief     API to psu monitor driver
 *
 *
 * \details   Provides interface to the driver that communicates with a PSU monitor device
 *
 */


#ifndef VHI_INC_IPSUMONITORDRIVER_H_
#define VHI_INC_IPSUMONITORDRIVER_H_

#include <vector>
#include <string>

#include "GlobalTypeDefs.h"
#include "Power.h"

namespace Mplane {

/*!
 * \class  IPsuMonitorDriver
 * \brief
 * \details
 *
 */
class IPsuMonitorDriver {
public:
	IPsuMonitorDriver() {}
	virtual ~IPsuMonitorDriver() {}

    /*! \brief  Initialise the driver
     *
     */
    virtual ReturnType::State initialise ( void ) =0;

    /**
     * Get the name of the driver
     */
    virtual std::string name() const =0 ;


    /*! \brief  Debug output
     *
     */
    virtual void show ( void ) =0;

    /**
     * Get the power reading (if possible, may return 0)
     */
    virtual float power() =0 ;

    /**
     * Get the voltage reading (if possible, may return 0)
     */
    virtual float voltage() =0 ;

    /**
     * Get the current reading (if possible, may return 0)
     */
    virtual float current() =0 ;

    /**
     * Does this monitor support power measurement
     */
    virtual bool isPowerSupported() const =0 ;

    /**
     * Does this monitor support voltage measurement
     */
    virtual bool isVoltageSupported() const =0 ;

    /**
     * Does this monitor support current measurement
     */
    virtual bool isCurrentSupported() const =0 ;



} ;

}

#endif /* VHI_INC_IPSUMONITORDRIVER_H_ */
