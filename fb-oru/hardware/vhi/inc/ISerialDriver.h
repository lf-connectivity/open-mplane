/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISerialDriver.h
 * \brief     A file to define generic interface to a Terminal Serial driver
 *
 *
 * \details   A file to define generic interface to Terminal Serial driver
 *
 */

#ifndef _VRH_ISERIALDRIVER_H_
#define _VRH_ISERIALDRIVER_H_

// Includes go here, before the namespace
#include "GlobalTypeDefs.h"
#include <memory>
#include <vector>
#include "ISerialDataReceived.h"
#include "Observer.hpp"

namespace Mplane
{

/*! \brief  Generic Terminal Serial driver interface
 *
 *  A virtual interface base class defining an interface to Terminal Serial driver.
 *  The interface contains control aspects.
 *
 *  The serial driver is expected to open the serial port in the constructor
 *  Hence there is no method to explicitly open the port.
 *
 *  The serial driver is responsible for notifying any observers of ISerialDataReceived
 *  when there is new serial data available. So it needs to implement a way to detect
 *  and store new serial data.
 */
class ISerialDriver: public ISerialDataReceived, public Subject<ISerialDataReceived>
{
public:

    /*! \brief Constructor
     *
     */
	ISerialDriver() { };

    /**
     * Method to query whether serial driver opened successfully
     */
	virtual bool isOpen(void) = 0;

    /**
     * Method to write data to the serial device
     */
	virtual bool write(unsigned char* data, unsigned int dataLen) = 0;

    /**
     * Method to get the data. This is called by the observers of ISerialDataReceived when they are
     * notified about new data being available.
     */
	virtual SerialData getSerialData( void ) = 0;

    /*! \brief Destructor
     *
     */
    virtual ~ISerialDriver() { };
};

} /* namespace Mplane */

#endif /* _VRH_ISERIALDRIVER_H_ */
