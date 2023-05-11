/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaSpiBus.h
 * \brief     Base-level FPGA SPI bus
 *
 *
 * \details   FPGA SPI bus access implementation
 *
 */


#ifndef COMMON_BUS_INC_FPGASPIBUS_H_
#define COMMON_BUS_INC_FPGASPIBUS_H_

#include "SpiBus.h"
#include "ISpiBusSettings.h"
#include "GlobalTypeDefs.h"

namespace Mplane {

/*!
 * \class  FpgaSpiBus
 * \brief
 * \details
 *
 */
class FpgaSpiBus : public SpiBus {
public:

	static const uint8_t CLOCK_DIV;
	static const uint8_t READ_OPPOSITE_EDGE;

	FpgaSpiBus(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<ISpiBusReadonlySettings> busSettings) ;
	virtual ~FpgaSpiBus() ;


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

	/**
	 * Check if SPI transaction is complete before a timeout
	 */
	virtual bool isTransactionSuccessful();

	/// Virtual functions to be implemented by inheriting classes

	/**
	 * Set the control 1 register
	 */
	virtual void setControlReg1(uint8_t readLen, uint8_t writeLen, uint8_t polarity, bool rdOppEdge) = 0;

	/**
	 * Set the control 2 register
	 */
	virtual void setControlReg2(uint8_t div, uint8_t phase, bool enable) = 0;

	/**
	 * Start the SPI transaction
	 */
	virtual void startSpiTransaction() = 0;

	/**
	 * Write the data to be sent on the bus
	 */
	virtual void setupWriteData(uint16_t low, uint16_t high) = 0;

	/**
	 * Read the data received on the bus
	 */
	virtual void readData(uint32_t& data) = 0;

	/**
	 * Check if SPI transaction is complete
	 */
	virtual bool isTransactionComplete() = 0;

private:

	void fillWriteData(uint32_t offset, std::vector<uint8_t> &bytes, uint8_t& numOffsetBytes);

	bool executeRequest(std::vector<uint8_t> bytes, uint8_t numBytesToRead);


} ;

}

#endif /* COMMON_BUS_INC_FPGASPIBUS_H_ */
