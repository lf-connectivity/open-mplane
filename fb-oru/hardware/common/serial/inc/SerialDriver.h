/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialDriver.h
 * \brief     Provides methods to access the serial device
 *
 *
 * \details   This file defines methods to access the serial device
 *
 */

#ifndef _HARDWARE_SERIALDRIVER_H_
#define _HARDWARE_SERIALDRIVER_H_

#include <vector>
#include "ISerialDataReceived.h"
#include "ISerialDriver.h"
#include "SerialData.h"
#include "Task.h"

namespace Mplane
{

/*! \brief A generic serial driver class.
 *
 * The Serial driver class
 */
class SerialDriver : public ISerialDriver, public Task
{

public:

    /**
     * Simple Serial driver object constructor.
     */
	SerialDriver(std::string devPath, unsigned int baud);

    /**
     * Virtual Serial driver object destructor.
     */
	virtual ~SerialDriver(void);

    /**
     * Method to query whether serial driver opened successfully
     */
	virtual bool isOpen(void);

    /**
     * Method to write data to the serial device
     */
	virtual bool write(unsigned char* data, unsigned int dataLen);

    /**
     * Method to get the data
     */
	virtual SerialData getSerialData( void ) override;


protected:

	int mDevFd;                           //!> file descriptor used for reading/writing from/to device

    /**
     * Method to configure the serial driver
     */
	virtual bool configure(void);

    /**
     * Method to drain the data from the serial device output buffer to the bus
     */
	virtual bool drain(void);

    /**
     * Method to flush the serial device input buffer
     */
	virtual bool flush(void);

    /**
     * This is the method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     * @return the exit status of task process
     */
    virtual int run() override;

private:

	SerialData mData;                     //!> Serial data class instance
	std::string mDevPath;                 //!> Serial device name
	unsigned int mBaud;                   //!> baud rate
    int mReadFd;                          //!> pipe used to wake task on shutdown
    int mWriteFd;
    bool mShutdown;                       //!> flag set when shutting down
};

} /* namespace Mplane */

#endif /* _HARDWARE_SERIALDRIVER_H_ */
