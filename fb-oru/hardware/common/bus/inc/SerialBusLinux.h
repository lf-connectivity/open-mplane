/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialBusLinux.h
 * \brief     Base-level serial bus
 *
 *
 * \details   Base-level serial bus
 *
 */


#ifndef COMMON_BUS_INC_SERIALBUSLINUX_H_
#define COMMON_BUS_INC_SERIALBUSLINUX_H_

#include <mutex>
#include <vector>
#include "SerialBus.h"

namespace Mplane {

/*!
 * \class  SerialBus
 * \brief
 * \details
 *
 */
class SerialBusLinux : public SerialBus {
public:
	SerialBusLinux(const std::string& devicePath, unsigned baudRate, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings) ;
	virtual ~SerialBusLinux() ;


protected:

	std::string mDevicePath ;
	int mDevFd;                           //!> file descriptor used for reading/writing from/to device

	// Implement the data transfer calls

	/**
	 * Write a block of bytes.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doWriteData(const std::vector<uint8_t>& bytes) override ;

	/**
	 * Read a block of bytes. If specified number of bytes is 0 then reads
	 * whatever data is available
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doReadData(std::vector<uint8_t>& bytes, unsigned numBytes=0) override ;

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
     * Method to query whether serial driver opened successfully
     */
	virtual bool isOpen(void);

} ;

}

#endif /* COMMON_BUS_INC_SERIALBUSLINUX_H_ */
