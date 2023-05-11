/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBusLinux.h
 * \brief     I2c bus using Linux devices
 *
 *
 * \details   Implements the I2c bus (implementing II2cBus and IBus virtual interfaces). Actual implementation is via Linux I2c device
 * 				drivers which map to physical devices on the board connected to the processor
 *
 */


#ifndef COMMON_BUS_INC_I2CBUSLINUX_H_
#define COMMON_BUS_INC_I2CBUSLINUX_H_

#include "I2cBus.h"

namespace Mplane {

/*!
 * \class  I2cBusLinux
 * \brief
 * \details
 *
 */
class I2cBusLinux : public I2cBus {
public:
	/**
	 * The Linux bus needs a path for an i2c device (e.g. something like "/dev/i2c-12")
	 * This instance of the bus connects to a particular physical device endpoint, so we need to provide
	 * the I2c address of that endpoint
	 */
	I2cBusLinux(const std::string& devicePath, unsigned i2cAddress, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings) ;

	virtual ~I2cBusLinux() ;

protected:
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
	 * Write a block of bytes to a particular offset.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doWriteData(uint32_t offset, const std::vector<uint8_t>& bytes) override ;

	/**
	 * Read a block of bytes from a specific offset.
	 * If specified number of bytes is 0 then reads whatever data is available
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doReadData(uint32_t offset, std::vector<uint8_t>& bytes, unsigned numBytes=0) override ;

	/**
	 * Write a byte to a particular offset address / register in the device
	 */
	virtual bool doWriteByte(uint32_t offset, uint8_t byte) override ;

	/**
	 * Write a short to a particular offset address / register in the device
	 */
	virtual bool doWriteShort(uint32_t offset, uint16_t shortVal) override ;

	/**
	 * Read a byte from a particular offset address / register in the device
	 */
	virtual bool doReadByte(uint32_t offset, uint8_t& byte) override ;

	/**
	 * Read a short from a particular offset address / register in the device
	 */
	virtual bool doReadShort(uint32_t offset, uint16_t& shortVal) override ;


private:
	std::string mDevicePath ;
	int mFd ;
	bool mSmbWriteByteData ;
	bool mSmbReadByteData ;
	bool mSmbWriteWordData ;
	bool mSmbReadWordData ;
	bool mSmbWriteBlockData ;
	bool mSmbReadBlockData ;
} ;

}

#endif /* COMMON_BUS_INC_I2CBUSLINUX_H_ */
