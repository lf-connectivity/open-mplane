/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Bus.h
 * \brief     Base-level implementation of IBus
 *
 *
 * \details   Base-level implementation of IBus
 *
 */


#ifndef COMMON_BUS_INC_BUS_H_
#define COMMON_BUS_INC_BUS_H_

#include <memory>

#include "IBus.h"
#include "IBusLock.h"

namespace Mplane {

/*!
 * \class  Bus
 * \brief
 * \details
 *
 */
class Bus : public virtual IBus {
public:
	Bus(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings) ;
	virtual ~Bus() ;

	/**
	 * Error string set whenever any method fails. Reading the error string clears the internal error string
	 */
	virtual std::string error() override ;

	/**
	 * DEBUG: Returns the bus name string. For example could be "I2C on Linux" or "SPI on FPGA"
	 */
	virtual std::string busName() const override ;

	/**
	 * DEBUG: Returns the bus details string. This might be, for example, the I2c address of the device endpoint for this
	 * bus instance
	 */
	virtual std::string busDetails() const override ;

	/**
	 * DEBUG: Enable/disable debug
	 */
	virtual void setDebug(bool debug) override ;

	/**
	 * Execute a command list. Any read commands will result ina value added to the readback list. By default, all commands are performed
	 * with the bus locked until the complete list is performed (i.e. the method is atomic like all other methods). Since performing
	 * a list of commands is generally useful but could be interleaved with other accesses, it can be specified that the bus is not locked
	 * over the whole list - just locked during each command
	 */
	virtual bool commandsList(const std::vector<IBus::BusCommand>& commands, std::vector<IBus::BusCommand>& readback,
			bool busAtomic = true, bool deviceAtomic = true) override ;

	/**
	 * Execute a command list. A simplified variant that can be used when there are no readbacks.
	 */
	virtual bool commandsList(const std::vector<IBus::BusCommand>& commands,
			bool busAtomic = true, bool deviceAtomic = true) override ;


	/**
	 * Write a block of bytes.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool writeData(const std::vector<uint8_t>& bytes) override ;

	/**
	 * Read a block of bytes. If specified number of bytes is 0 then reads
	 * whatever data is available
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool readData(std::vector<uint8_t>& bytes, unsigned numBytes=0) override ;

	/**
	 * Write a block of bytes to a particular offset.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool writeData(uint32_t offset, const std::vector<uint8_t>& bytes) override ;

	/**
	 * Read a block of bytes from a specific offset.
	 * If specified number of bytes is 0 then reads whatever data is available
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool readData(uint32_t offset, std::vector<uint8_t>& bytes, unsigned numBytes=0) override ;


	/**
	 * Write a byte to a particular offset address / register in the device
	 */
	virtual bool writeByte(uint32_t offset, uint8_t byte) override ;

	/**
	 * Write a short to a particular offset address / register in the device
	 */
	virtual bool writeShort(uint32_t offset, uint16_t shortVal) override ;

	/**
	 * Write a word to a particular offset address / register in the device
	 */
	virtual bool writeWord(uint32_t offset, uint32_t word) override ;

	/**
	 * Read a byte from a particular offset address / register in the device
	 */
	virtual bool readByte(uint32_t offset, uint8_t& byte) override ;

	/**
	 * Read a short from a particular offset address / register in the device
	 */
	virtual bool readShort(uint32_t offset, uint16_t& shortVal) override ;

	/**
	 * Read a word from a particular offset address / register in the device
	 */
	virtual bool readWord(uint32_t offset, uint32_t& word) override ;


	/**
	 * Access the read-only set of settings for this IBus
	 */
	virtual std::shared_ptr<IBusReadonlySettings> settings() const override ;

	/**
	 * Register a bus monitor with this bus. The bus monitor methods will be called for any bus transactions
	 */
	virtual void registerMonitor(std::shared_ptr<IBusMonitor> monitor) override ;

	/**
	 * Un-register any bus monitor
	 */
	virtual void unregisterMonitor(std::shared_ptr<IBusMonitor> monitor) override ;



protected:
	/**
	 * Utility for updating the error string
	 * Always returns false, so can be used to both set the error and return from the calling method
	 */
	bool setError(const std::string& error) ;

#if 0
	/**
	 * Get the lock for the bus that this connected device uses
	 */
	std::shared_ptr<IBusLock> busLock() ;

	/**
	 * Get the lock for this particular device
	 */
	std::shared_ptr<IBusLock> deviceLock() ;
#endif

	/**
	 * Get the debug flag
	 */
	bool debug() const ;

protected:
	// Protected hooks - derived objects need to implement these methods
	// All of these methods expect any locks to have been performed BEFORE being called

	/**
	 * Write a block of bytes.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doWriteData(const std::vector<uint8_t>& bytes) ;

	/**
	 * Read a block of bytes. If specified number of bytes is 0 then reads
	 * whatever data is available
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doReadData(std::vector<uint8_t>& bytes, unsigned numBytes=0) ;

	/**
	 * Write a block of bytes to a particular offset.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doWriteData(uint32_t offset, const std::vector<uint8_t>& bytes) ;

	/**
	 * Read a block of bytes from a specific offset.
	 * If specified number of bytes is 0 then reads whatever data is available
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doReadData(uint32_t offset, std::vector<uint8_t>& bytes, unsigned numBytes=0) ;


	/**
	 * Write a byte to a particular offset address / register in the device
	 */
	virtual bool doWriteByte(uint32_t offset, uint8_t byte) ;

	/**
	 * Write a short to a particular offset address / register in the device
	 */
	virtual bool doWriteShort(uint32_t offset, uint16_t shortVal) ;

	/**
	 * Write a word to a particular offset address / register in the device
	 */
	virtual bool doWriteWord(uint32_t offset, uint32_t word) ;

	/**
	 * Read a byte from a particular offset address / register in the device
	 */
	virtual bool doReadByte(uint32_t offset, uint8_t& byte) ;

	/**
	 * Read a short from a particular offset address / register in the device
	 */
	virtual bool doReadShort(uint32_t offset, uint16_t& shortVal) ;

	/**
	 * Read a word from a particular offset address / register in the device
	 */
	virtual bool doReadWord(uint32_t offset, uint32_t& word) ;

private:
	std::string mError ;
	std::string mBusName ;
	std::string mBusDetails ;
	std::shared_ptr<IBusLock> mBusLock ;
	std::shared_ptr<IBusLock> mDeviceLock ;
	std::shared_ptr<IBusReadonlySettings> mBusSettings ;
	bool mDebug ;
	std::vector<std::shared_ptr<IBusMonitor>> mMonitor ;
} ;

}

#endif /* COMMON_BUS_INC_BUS_H_ */
