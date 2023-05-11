/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IBus.h
 * \brief     Virtual interface to the bus of a specific device
 *
 *
 * \details   Each physical device will have one (or more) busses used to communicate with that device. This virtual interface
 * 			  provides a common API for all device busses (I2C, SPI etc) abstracting away from any implementation details. Devices
 * 			  can then be provided with an instance of a class that implements this API and the device class can use these common methods
 * 			  to communicate with the physical device over whatever bus it uses.
 *
 * 			  Most likely a device will need access to some methods specific to the physical bus (e.g. SPI speed setting?) in which case the
 * 			  device can do a cast to a more specific virtual interface provided under vhi/inc/bus.
 *
 * 			  The intention of using this framework is to support the following use cases:
 *
 * 			  1. An SPI device can be written in a way that means the device will operate correctly whether it is physically connected
 * 			  to an SPI bus connected to the processor or to a bus provided by an FPGA. The implementation of the IBus will be one class
 * 			  for the processor bus (i.e. a Linux SPI driver); another for the FPGA (i.e. a driver accessing the appropriate FPGA regs)
 *
 * 			  2. An IBus implementation can be written that supports both I2c and SPI such that it implements SPI access (that the device
 * 			  uses) but is actually connected to I2c. This would then provide the bridge mechanism for where a device is connected via an
 * 			  I2c to SPI bridge chip. The SPI device code stays the same (as in [1]) but we just provide it with a new IBus implementation
 * 			  that implements the bridge
 *
 */


#ifndef VHI_INC_IBUS_H_
#define VHI_INC_IBUS_H_

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

#include "IBusSettings.h"
#include "IBusMonitor.h"

namespace Mplane {

/*!
 * \class  IBus
 * \brief
 * \details
 *
 */
class IBus {
public:
	IBus() {}
	virtual ~IBus() {}

	/**
	 * Command types supported
	 */
	enum BusCommandType {
		BUS_WRITE_BYTE,
		BUS_WRITE_SHORT,
		BUS_WRITE_WORD,
		BUS_WRITE_DATA,			//<! data write of vector of bytes (no offset specified)
		BUS_WRITE_DATA_OFFSET,	//<! data write of vector of bytes to an offset
		BUS_READ_BYTE,
		BUS_READ_SHORT,
		BUS_READ_WORD,
		BUS_READ_DATA,			//<! data read of vector of bytes (no offset specified)
		BUS_READ_DATA_OFFSET,	//<! data read of vector of bytes from an offset
		BUS_WAIT_MS,
	};

	class BusCommand {
	public:
		BusCommand(BusCommandType type, uint32_t arg1, uint32_t arg2, const std::vector<uint8_t>& bytes) :
			mType(type), mArg1(arg1), mArg2(arg2), mBytes(bytes) {}

		BusCommand(BusCommandType type, uint32_t arg1, uint32_t arg2) :
			BusCommand(type, arg1, arg2, std::vector<uint8_t>()) {}

		BusCommand(BusCommandType type, uint32_t arg1) :
			BusCommand(type, arg1, 0, std::vector<uint8_t>()) {}

		BusCommand(BusCommandType type, uint32_t arg1, const std::vector<uint8_t>& bytes) :
			BusCommand(type, arg1, 0, bytes) {}

		BusCommand(BusCommandType type, const std::vector<uint8_t>& bytes) :
			BusCommand(type, 0, 0, bytes) {}

		inline BusCommandType type() const { return mType; }
		inline unsigned waitMs() const { return mArg1; }
		inline uint32_t offset() const { return mArg1; }
		inline uint16_t offset16() const { return (uint16_t)(mArg1 & 0xffff) ; }
		inline uint8_t offset8() const { return (uint8_t)(mArg1 & 0xff) ; }

		inline uint32_t data() const { return mArg2; }
		inline uint16_t data16() const { return (uint16_t)(mArg2 & 0xffff) ; }
		inline uint8_t data8() const { return (uint8_t)(mArg2 & 0xff) ; }

		inline void setData(uint32_t val) { mArg2 = val ; }
		inline void setData16(uint16_t val) { mArg2 = (uint32_t)val ; }
		inline void setData8(uint8_t val) { mArg2 = (uint32_t)val ; }

		inline std::vector<uint8_t> bytes() const { return mBytes; }
		inline void setBytes(const std::vector<uint8_t>& bytes) { mBytes = bytes; }

	private:
		BusCommandType mType ;
		uint32_t mArg1 ; //<! First arg. Used as offset or timeout
		uint32_t mArg2 ; //<! Second arg. Used as read/write data
		std::vector<uint8_t> mBytes ;
	};

	/**
	 * Execute a command list. Any read commands will result ina value added to the readback list. By default, all commands are performed
	 * with the bus locked until the complete list is performed (i.e. the method is atomic like all other methods). Since performing
	 * a list of commands is generally useful but could be interleaved with other accesses, it can be specified that the bus is not locked
	 * over the whole list - just locked during each command
	 */
	virtual bool commandsList(const std::vector<BusCommand>& commands, std::vector<BusCommand>& readback, bool busAtomic = true, bool deviceAtomic = true) =0 ;

	/**
	 * Execute a command list. A simplified variant that can be used when there are no readbacks.
	 */
	virtual bool commandsList(const std::vector<BusCommand>& commands, bool busAtomic = true, bool deviceAtomic = true) =0 ;

	/**
	 * Write a block of bytes.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool writeData(const std::vector<uint8_t>& bytes) =0 ;

	/**
	 * Read a block of bytes. If specified number of bytes is 0 then reads
	 * whatever data is available
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool readData(std::vector<uint8_t>& bytes, unsigned numBytes=0) =0 ;

	/**
	 * Write a block of bytes to a particular offset.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool writeData(uint32_t offset, const std::vector<uint8_t>& bytes) =0 ;

	/**
	 * Read a block of bytes from a specific offset.
	 * If specified number of bytes is 0 then reads whatever data is available
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool readData(uint32_t offset, std::vector<uint8_t>& bytes, unsigned numBytes=0) =0 ;

	/**
	 * Write a byte to a particular offset address / register in the device
	 */
	virtual bool writeByte(uint32_t offset, uint8_t byte) =0 ;

	/**
	 * Write a short to a particular offset address / register in the device
	 */
	virtual bool writeShort(uint32_t offset, uint16_t shortVal) =0 ;

	/**
	 * Write a word to a particular offset address / register in the device
	 */
	virtual bool writeWord(uint32_t offset, uint32_t word) =0 ;

	/**
	 * Read a byte from a particular offset address / register in the device
	 */
	virtual bool readByte(uint32_t offset, uint8_t& byte) =0 ;

	/**
	 * Read a short from a particular offset address / register in the device
	 */
	virtual bool readShort(uint32_t offset, uint16_t& shortVal) =0 ;

	/**
	 * Read a word from a particular offset address / register in the device
	 */
	virtual bool readWord(uint32_t offset, uint32_t& word) =0 ;

	/**
	 * Error string set whenever any method fails. Reading the error string clears the internal error string
	 */
	virtual std::string error() =0 ;

	/**
	 * DEBUG: Returns the bus name string. For example could be "I2C on Linux" or "SPI on FPGA"
	 */
	virtual std::string busName() const =0 ;

	/**
	 * DEBUG: Returns the bus details string. This might be, for example, the I2c address of the device endpoint for this
	 * bus instance
	 */
	virtual std::string busDetails() const =0 ;

	/**
	 * DEBUG: Enable/disable debug
	 */
	virtual void setDebug(bool debug) =0 ;

	/**
	 * Access the read-only set of settings for this IBus
	 */
	virtual std::shared_ptr<IBusReadonlySettings> settings() const =0 ;

	/**
	 * Register a bus monitor with this bus. The bus monitor methods will be called for any bus transactions
	 */
	virtual void registerMonitor(std::shared_ptr<IBusMonitor> monitor) =0 ;

	/**
	 * Un-register any bus monitor
	 */
	virtual void unregisterMonitor(std::shared_ptr<IBusMonitor> monitor) =0 ;

} ;

}

#endif /* VHI_INC_IBUS_H_ */
