#ifndef _RADIO_HARDWARE_COMMONTEMPERATURESENSOR_H_
#define _RADIO_HARDWARE_COMMONTEMPERATURESENSOR_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTemperatureSensor.h
 * \brief     A file to contain the common implementation of a generic temperature sensor.
 *
 *
 * \details   This file defines the common implementation of a generic temperature sensor
 *            and expands on it if necessary.
 *
 */

// Includes go here, before the namespace
#include <string>
#include <memory>

#include "ITemperatureSensor.h"
#include "Initialise.h"
#include "Device.h"
#include "ITemperatureSensorDriver.h"

namespace Mplane
{

/*! \brief  Generic Temperature sensor interface
 *
 *  A generic virtual interface base class defining an interface to a
 *  temperature sensor device.
 *  The interface contains configuration and control aspects.
 *
 *  It is designed to be implemented as a polymorphic base class
 *  for all temperature sensor device programming classes.
 *
 */
class CommonTemperatureSensor:  public virtual ITemperatureSensor, public Device
{

public:
    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit();

    /*! \brief Pure virtual method to get the temperature
     *
     * \return The Temperature
     */
    virtual const Temperature getTemperature( void ) override;

    /*! \brief  Dump the temperature sensor debug information
     *
     *  Dump the information of the temperature sensor to the console or log file
     */
    virtual void show(std::ostream& os) override;
    virtual void show(void) override;


    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param index  zero-based index of the temperature sensor
     *  \param name   name string for the temperature sensor
     */
    CommonTemperatureSensor( std::shared_ptr<ITemperatureSensorDriver> driver, int index, const std::string& name);

    /*! \brief Destructor
     *
     *  Ensure we can only be destructed via an implementing class
     *
     */
    virtual ~CommonTemperatureSensor();

private:

    /*!
     * The temperature sensor driver that gives access to the hardware
     */
    std::shared_ptr<ITemperatureSensorDriver> mDriver;

};

} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONTEMPERATURESENSOR_H_ */
