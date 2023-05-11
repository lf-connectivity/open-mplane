/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITemperatureSensorDriver.h
 * \brief     A file to define generic interface to temperature sensor driver
 *
 *
 * \details   A file to define generic interface to a Temperature sensor driver
 *
 */
#ifndef _VHI_ITEMPERATURE_SENSOR_DRIVER_H_
#define _VHI_ITEMPERATURE_SENSOR_DRIVER_H_

#include "GlobalTypeDefs.h"
#include "Temperature.h"

namespace Mplane
{

/*! \brief  Generic Temperature Sensor interface
 *
 *  A generic virtual interface base class defining an interface to a
 *  temperature sensor driver.
 *
 *  The aim for creating the ITemperatureSensorDriver interface is to make the Tx, Rx, PA,
 *  temperature sensor device objects independent of the chip/method used for measuring temperature.
 *  The ITemperatureSensorDriver implementations would have the board specific code to
 *  communicate with the chip to initialise and read the temperature.
 *  The individual temperature sensor device object (Tx, Rx, etc) would use one of the
 *  ITemperatureSensorDriver implementations via the virtual interface.
 */
class ITemperatureSensorDriver
{
public:

    /*! \brief Destructor
     *
     */
    virtual ~ITemperatureSensorDriver() { };

	/**
	 * Initialise the driver
	 */
	virtual ReturnType::State initialise( void ) = 0;

    /*! \brief Pure virtual method to get the temperature
     *
     * \return The Temperature
     */
    virtual const Temperature getTemperature( void ) = 0;

    /*! \brief  Dump the temperature sensor debug information
     *
     *  Dump the information of the temperature sensor to the console or log file
     */
    virtual void show(std::ostream& os) =0;
    virtual void show(void) =0;
};

} /* namespace Mplane */

#endif /* _VHI_ITEMPERATURE_SENSOR_DRIVER_H_ */
