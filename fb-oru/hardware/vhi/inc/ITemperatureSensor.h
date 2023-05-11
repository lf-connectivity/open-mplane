/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITemperatureSensor.h
 * \brief     A file to define generic interface to temperature sensor implementation
 *
 *
 * \details   A file to define generic interface to a Temperature sensor implementation
 *
 */
#ifndef _VHI_ITEMPERATURE_SENSOR__H_
#define _VHI_ITEMPERATURE_SENSOR__H_

#include "Temperature.h"
#include "IDevice.h"

namespace Mplane
{

/*! \brief  Generic Temperature Sensor interface
 *
 *  A generic virtual interface base class defining an interface to a
 *  temperature sensor device.
 *
 *  This class is designed to be implemented as a polymorphic base class
 *  for all temperature sensor device programming classes.
 */
class ITemperatureSensor: public virtual IDevice
{
public:

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

protected:

    ITemperatureSensor() {};

    /*! \brief Destructor
     *
     */
    virtual ~ITemperatureSensor() { };
};

} /* namespace Mplane */

#endif /* _VHI_ITEMPERATURE_SENSOR__H_ */
