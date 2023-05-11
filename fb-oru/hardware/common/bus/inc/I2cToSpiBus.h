/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cToSpiBus.h
 * \brief     Models a device that converts the I2c bus into an SPI bus
 *
 *
 * \details   The default read/write methods map to an ISpiBus, but collect the data and then transport it via an I2cBus
 * 				so that the data is correctly sent to the physical I2cToSpi bridge device over I2c
 *
 */


#ifndef COMMON_BUS_INC_I2CTOSPIBUS_H_
#define COMMON_BUS_INC_I2CTOSPIBUS_H_

#include "II2cToSpiBus.h"
#include "SpiBus.h"

namespace Mplane {

/*!
 * \class  I2cToSpiBus
 * \brief
 * \details   Bridge class is created by giving it the concrete class that provides the I2c bus for this device. This class then
 * 			manages the SPI data formatting
 *
 */
class I2cToSpiBus : public virtual II2cToSpiBus, public SpiBus {
public:
	/**
	 * spiSelect is a 0-based index that selects the spi device. The default behaviour is to shift a 1 to the index position
	 * and use that value as the I2c offset
	 */
	I2cToSpiBus(std::shared_ptr<II2cBus> i2c, std::shared_ptr<IBusReadonlySettings> busSettings, unsigned spiSelect) ;
	virtual ~I2cToSpiBus() ;

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
	 * Write a byte to a particular offset address / register in the device
	 */
	virtual bool doWriteByte(uint32_t offset, uint8_t byte) override ;

	/**
	 * Write a short to a particular offset address / register in the device
	 */
	virtual bool doWriteShort(uint32_t offset, uint16_t shortVal) override ;

	/**
	 * Write a word to a particular offset address / register in the device
	 */
	virtual bool doWriteWord(uint32_t offset, uint32_t word) override ;

	/**
	 * Read a byte from a particular offset address / register in the device
	 */
	virtual bool doReadByte(uint32_t offset, uint8_t& byte) override ;

	/**
	 * Read a short from a particular offset address / register in the device
	 */
	virtual bool doReadShort(uint32_t offset, uint16_t& shortVal) override ;

	/**
	 * Read a word from a particular offset address / register in the device
	 */
	virtual bool doReadWord(uint32_t offset, uint32_t& word) override ;


private:
	std::shared_ptr<II2cBus> mI2c ;

protected:
	uint32_t mOffset ;
} ;

}

#endif /* COMMON_BUS_INC_I2CTOSPIBUS_H_ */
