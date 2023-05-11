/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IGpioExpDriver.h
 * \brief     A file to define generic interface to a GPIO expander device driver
 *
 *
 * \details   A file to define generic interface to a GPIO expander device driver
 *
 */

#ifndef _VRH_IGPIOEXPDRIVER_H_
#define _VRH_IGPIOEXPDRIVER_H_

#include <stdexcept>
#include <memory>
#include "GlobalTypeDefs.h"


namespace Mplane
{

/*! \brief  Generic GPIO expander driver interface
 *
 *  A generic virtual interface base class defining an interface to a
 *  GPIO expander.
 *  The interface contains configuration and control aspects.
 *
 *  The aim for creating the IGpioExpDriver interface is to make the GPIO expander
 *  device independent of the chip / library used.
 *
 */
class IGpioExpDriver
{
public:

    IGpioExpDriver() {};

    virtual ~IGpioExpDriver(){};

	/**
	 * Initialise the driver
	 */
	virtual ReturnType::State initialise( void ) = 0;

    /*! \brief  Dump the Gpio expander status
     *
     *  Dump the state of the Gpio expander driver to the log file
     */
    virtual void show ( std::ostream& os ) = 0;

    /*! \brief  Dump the Gpio expander status
     *
     *  Dump the state of the Gpio expander driver to the console
     */
    virtual void show ( void ) = 0;

    /**
     * This pure virtual method is used to write a value to the selected port. By using
     * the mask, only the required bits in the port can be written
     *
     * @param port 0 base port selector
     * @param value raw value to be written
     * @return true if write successful
     */
    virtual ReturnType::State write8BitPort( int port, UINT8 value, UINT8 mask = 0xFF ) = 0;

    /**
     * This pure virtual method is used to read a value of the selected port.
     *
     * @param port 0 base port selector
     * @param value value read
     * @return true if read successful
     */
    virtual ReturnType::State read8BitPort( int port, UINT8& value ) = 0;

    /**
     * This pure virtual method is used to set direction of the pins on the selected port.
     *
     * @param port - 0 base port selector
     * @param dir - 8 bits for 8 pins on the port (1 = input, 0 = output)
     * @param mask - If it is possible to set direction of individual pins,
     * then the mask shall be used to decide which pin directions to set
     * @return true if set direction successful
     */
    virtual ReturnType::State setDirection( int port, UINT8 dir, UINT8 mask ) = 0;
};

}

#endif /* _VRH_IGPIOEXPDRIVER_H_ */
