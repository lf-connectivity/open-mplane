/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Bus.cpp
 * \brief     Base-level implementation of IBus
 *
 *
 * \details   Base-level implementation of IBus
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>
#include <algorithm>

#include "BusLock.hpp"
#include "Bus.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Bus::Bus(const std::string &busName, const std::string &busDetails, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	mError(""),
	mBusName(busName),
	mBusDetails(busDetails),
	mBusLock(busLock),
	mDeviceLock( std::make_shared<BusLock>() ),
	mBusSettings(busSettings),
	mDebug(false)
{
}

//-------------------------------------------------------------------------------------------------------------
Bus::~Bus()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string Bus::error()
{
	std::string err ;
	using std::swap ;
	swap(err, mError) ;
	return err ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Bus::busName() const
{
	return mBusName ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Bus::busDetails() const
{
	return mBusDetails ;
}

//-------------------------------------------------------------------------------------------------------------
void Bus::setDebug(bool debug)
{
	mDebug = debug ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::commandsList(const std::vector<IBus::BusCommand> &commands,
		std::vector<IBus::BusCommand> &readback, bool busAtomic,
		bool deviceAtomic)
{
	if (busAtomic)
	{
		deviceAtomic = false ;

		// Lock the bus (for Linux this is probably a NO OP)
		std::shared_ptr<IBusLocker> lock(mBusLock->locker());

		// Lock the device
		std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
	}

	readback.clear() ;

	// Execute the list of commands
	for (auto& command : commands)
	{
		switch (command.type())
		{
		case IBus::BUS_WRITE_BYTE:
		{
			if (deviceAtomic)
			{
				// Lock the bus (for Linux this is probably a NO OP)
				std::shared_ptr<IBusLocker> lock(mBusLock->locker());

				// Lock the device
				std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
			}

			if (!doWriteByte(command.offset(), command.data8()))
				return false ;

			if (mMonitor.empty())
				continue ;

			for (auto mon : mMonitor)
				mon->updateWrite(command.offset(), (uint32_t)command.data8()) ;

		}
		break ;

		case IBus::BUS_WRITE_SHORT:
		{
			if (deviceAtomic)
			{
				// Lock the bus (for Linux this is probably a NO OP)
				std::shared_ptr<IBusLocker> lock(mBusLock->locker());

				// Lock the device
				std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
			}

			if (!doWriteShort(command.offset(), command.data16()))
				return false ;

			if (mMonitor.empty())
				continue ;

			for (auto mon : mMonitor)
				mon->updateWrite(command.offset(), (uint32_t)command.data16()) ;

		}
		break ;

		case IBus::BUS_WRITE_WORD:
		{
			if (deviceAtomic)
			{
				// Lock the bus (for Linux this is probably a NO OP)
				std::shared_ptr<IBusLocker> lock(mBusLock->locker());

				// Lock the device
				std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
			}

			if (!doWriteWord(command.offset(), command.data()))
				return false ;


			if (mMonitor.empty())
				continue ;

			for (auto mon : mMonitor)
				mon->updateWrite(command.offset(), command.data()) ;

		}
		break ;

		case IBus::BUS_WRITE_DATA:
		{
			if (deviceAtomic)
			{
				// Lock the bus (for Linux this is probably a NO OP)
				std::shared_ptr<IBusLocker> lock(mBusLock->locker());

				// Lock the device
				std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
			}

			if (!doWriteData(command.bytes()))
				return false ;

			if (mMonitor.empty())
				continue ;

			for (auto mon : mMonitor)
				mon->updateWrite(command.bytes()) ;

		}
		break ;

		case IBus::BUS_WRITE_DATA_OFFSET:
		{
			if (deviceAtomic)
			{
				// Lock the bus (for Linux this is probably a NO OP)
				std::shared_ptr<IBusLocker> lock(mBusLock->locker());

				// Lock the device
				std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
			}

			if (!doWriteData(command.offset(), command.bytes()))
				return false ;

			if (mMonitor.empty())
				continue ;

			for (auto mon : mMonitor)
				mon->updateWrite(command.offset(), command.bytes()) ;

		}
		break ;

		case IBus::BUS_READ_BYTE:
		{
			if (deviceAtomic)
			{
				// Lock the bus (for Linux this is probably a NO OP)
				std::shared_ptr<IBusLocker> lock(mBusLock->locker());

				// Lock the device
				std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
			}

			uint8_t val ;
			if (!doReadByte(command.offset(), val))
				return false ;

			readback.push_back( IBus::BusCommand(command.type(), command.offset(), (uint32_t)val) ) ;

			if (mMonitor.empty())
				continue ;

			for (auto mon : mMonitor)
				mon->updateRead(command.offset(), (uint32_t)val) ;

		}
		break ;

		case IBus::BUS_READ_SHORT:
		{
			if (deviceAtomic)
			{
				// Lock the bus (for Linux this is probably a NO OP)
				std::shared_ptr<IBusLocker> lock(mBusLock->locker());

				// Lock the device
				std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
			}

			uint16_t val ;
			if (!doReadShort(command.offset(), val))
				return false ;

			readback.push_back( IBus::BusCommand(command.type(), command.offset(), (uint32_t)val) ) ;

			if (mMonitor.empty())
				continue ;

			for (auto mon : mMonitor)
				mon->updateRead(command.offset(), (uint32_t)val) ;

		}
		break ;

		case IBus::BUS_READ_WORD:
		{
			if (deviceAtomic)
			{
				// Lock the bus (for Linux this is probably a NO OP)
				std::shared_ptr<IBusLocker> lock(mBusLock->locker());

				// Lock the device
				std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
			}

			uint32_t val ;
			if (!doReadWord(command.offset(), val))
				return false ;

			readback.push_back( IBus::BusCommand(command.type(), command.offset(), val) ) ;

			if (mMonitor.empty())
				continue ;

			for (auto mon : mMonitor)
				mon->updateRead(command.offset(), val) ;

		}
		break ;

		case IBus::BUS_READ_DATA:
		{
			if (deviceAtomic)
			{
				// Lock the bus (for Linux this is probably a NO OP)
				std::shared_ptr<IBusLocker> lock(mBusLock->locker());

				// Lock the device
				std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
			}

			std::vector<uint8_t> bytes ;
			if (!doReadData(bytes, command.bytes().size()))
				return false ;

			readback.push_back( IBus::BusCommand(command.type(), bytes) ) ;

			if (mMonitor.empty())
				continue ;

			for (auto mon : mMonitor)
				mon->updateRead(bytes) ;

		}
		break ;

		case IBus::BUS_READ_DATA_OFFSET:
		{
			if (deviceAtomic)
			{
				// Lock the bus (for Linux this is probably a NO OP)
				std::shared_ptr<IBusLocker> lock(mBusLock->locker());

				// Lock the device
				std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());
			}

			std::vector<uint8_t> bytes ;
			if (!doReadData(command.offset(), bytes, command.bytes().size()))
				return false ;

			readback.push_back( IBus::BusCommand(command.type(), command.offset(), bytes) ) ;

			if (mMonitor.empty())
				continue ;

			for (auto mon : mMonitor)
				mon->updateRead(command.offset(), bytes) ;

		}
		break ;


		case IBus::BUS_WAIT_MS:
			usleep( command.waitMs() * 1000 ) ;
			break ;

		default:
			return setError("Unexpected command type") ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::commandsList(const std::vector<IBus::BusCommand> &commands,
		bool busAtomic, bool deviceAtomic)
{
	std::vector<IBus::BusCommand> readback ;
	return commandsList(commands, readback, busAtomic, deviceAtomic) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::writeData(const std::vector<uint8_t> &bytes)
{
	// Lock the bus (for Linux this is probably a NO OP)
	std::shared_ptr<IBusLocker> lock(mBusLock->locker());

	// Lock the device
	std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());

	// execute
	if (!doWriteData(bytes))
		return false ;

	if (mMonitor.empty())
		return true ;

	for (auto mon : mMonitor)
		mon->updateWrite(bytes) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::readData(std::vector<uint8_t> &bytes, unsigned numBytes)
{
	// Lock the bus (for Linux this is probably a NO OP)
	std::shared_ptr<IBusLocker> lock(mBusLock->locker());

	// Lock the device
	std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());

	// execute
	bytes.clear() ;
	if (!doReadData(bytes, numBytes))
		return false ;

	if (mMonitor.empty())
		return true ;

	for (auto mon : mMonitor)
		mon->updateRead(bytes) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::writeData(uint32_t offset, const std::vector<uint8_t> &bytes)
{
	// Lock the bus (for Linux this is probably a NO OP)
	std::shared_ptr<IBusLocker> lock(mBusLock->locker());

	// Lock the device
	std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());

	// execute
	if (!doWriteData(offset, bytes))
		return false ;

	if (mMonitor.empty())
		return true ;

	for (auto mon : mMonitor)
		mon->updateWrite(offset, bytes) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::readData(uint32_t offset, std::vector<uint8_t> &bytes, unsigned numBytes)
{
	if (debug())
		std::cerr << "I2cBusLinux::readData" << " LOCKING BUS .." << std::endl ;


	// Lock the bus (for Linux this is probably a NO OP)
	std::shared_ptr<IBusLocker> lock(mBusLock->locker());

	if (debug())
		std::cerr << "I2cBusLinux::doReadData" << " LOCKED BUS .." << std::endl ;

	if (debug())
		std::cerr << "I2cBusLinux::readData" << " LOCKING DEVICE .." << std::endl ;

	// Lock the device
	std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());

	if (debug())
		std::cerr << "I2cBusLinux::doReadData" << " LOCKED DEVICE .." << std::endl ;

	// execute
	bytes.clear() ;
	if (!doReadData(offset, bytes, numBytes))
		return false ;

	if (mMonitor.empty())
		return true ;

	for (auto mon : mMonitor)
		mon->updateRead(offset, bytes) ;

	return true ;

}

//-------------------------------------------------------------------------------------------------------------
bool Bus::writeByte(uint32_t offset, uint8_t byte)
{
	// Lock the bus (for Linux this is probably a NO OP)
	std::shared_ptr<IBusLocker> lock(mBusLock->locker());

	// Lock the device
	std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());

	// execute
	if (!doWriteByte(offset, byte))
		return false ;

	if (mMonitor.empty())
		return true ;

	for (auto mon : mMonitor)
		mon->updateWrite(offset, (uint32_t)byte) ;

	return true ;

}

//-------------------------------------------------------------------------------------------------------------
bool Bus::writeShort(uint32_t offset, uint16_t shortVal)
{
	// Lock the bus (for Linux this is probably a NO OP)
	std::shared_ptr<IBusLocker> lock(mBusLock->locker());

	// Lock the device
	std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());

	// execute
	if (! doWriteShort(offset, shortVal) )
		return false ;

	if (mMonitor.empty())
		return true ;

	for (auto mon : mMonitor)
		mon->updateWrite(offset, (uint32_t)shortVal) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::writeWord(uint32_t offset, uint32_t word)
{
	// Lock the bus (for Linux this is probably a NO OP)
	std::shared_ptr<IBusLocker> lock(mBusLock->locker());

	// Lock the device
	std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());

	// execute
	if (! doWriteWord(offset, word) )
		return false ;

	if (mMonitor.empty())
		return true ;

	for (auto mon : mMonitor)
		mon->updateWrite(offset, word) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::readByte(uint32_t offset, uint8_t &byte)
{
	// Lock the bus (for Linux this is probably a NO OP)
	std::shared_ptr<IBusLocker> lock(mBusLock->locker());

	// Lock the device
	std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());

	// execute
	if (! doReadByte(offset, byte) )
		return false ;

	if (mMonitor.empty())
		return true ;

	for (auto mon : mMonitor)
		mon->updateRead(offset, (uint32_t)byte) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::readShort(uint32_t offset, uint16_t &shortVal)
{
	// Lock the bus (for Linux this is probably a NO OP)
	std::shared_ptr<IBusLocker> lock(mBusLock->locker());

	// Lock the device
	std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());

	// execute
	if (! doReadShort(offset, shortVal) )
		return false ;

	if (mMonitor.empty())
		return true ;

	for (auto mon : mMonitor)
		mon->updateRead(offset, (uint32_t)shortVal) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::readWord(uint32_t offset, uint32_t &word)
{
	// Lock the bus (for Linux this is probably a NO OP)
	std::shared_ptr<IBusLocker> lock(mBusLock->locker());

	// Lock the device
	std::shared_ptr<IBusLocker> devlock(mDeviceLock->locker());

	// execute
	if (! doReadWord(offset, word) )
		return false ;

	if (mMonitor.empty())
		return true ;

	for (auto mon : mMonitor)
		mon->updateRead(offset, word) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IBusReadonlySettings> Mplane::Bus::settings() const
{
	return mBusSettings ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::Bus::registerMonitor(std::shared_ptr<IBusMonitor> monitor)
{
	auto p(std::find(mMonitor.begin(), mMonitor.end(), monitor)) ;
	if (p != mMonitor.end())
		return ;

	mMonitor.push_back(monitor) ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::Bus::unregisterMonitor(std::shared_ptr<IBusMonitor> monitor)
{
	auto p(std::find(mMonitor.begin(), mMonitor.end(), monitor)) ;
	if (p == mMonitor.end())
		return ;

	mMonitor.erase(p) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Bus::setError(const std::string &error)
{
	if (!mError.empty())
		mError += "\n" ;
	mError += error ;

	if (mDebug)
		std::cerr << "Bus[" << mBusName << ":" << mBusDetails << "] Error: " << error << std::endl ;

	return false ;
}

#if 0
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IBusLock> Bus::busLock()
{
	return mBusLock ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IBusLock> Bus::deviceLock()
{
	return mDeviceLock ;
}
#endif

//-------------------------------------------------------------------------------------------------------------
bool Bus::debug() const
{
	return mDebug ;
}


//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Bus::doWriteData(const std::vector<uint8_t> &bytes)
{
	return setError("writeData not supported") ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::doReadData(std::vector<uint8_t> &bytes, unsigned numBytes)
{
	return setError("readData not supported") ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::doWriteData(uint32_t offset, const std::vector<uint8_t> &bytes)
{
	return setError("writeData (offset) not supported") ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::doReadData(uint32_t offset, std::vector<uint8_t> &bytes, unsigned numBytes)
{
	return setError("readData (offset) not supported") ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::doWriteByte(uint32_t offset, uint8_t byte)
{
	return setError("writeByte not supported") ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::doWriteShort(uint32_t offset, uint16_t shortVal)
{
	return setError("writeShort not supported") ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::doWriteWord(uint32_t offset, uint32_t word)
{
	return setError("writeWord not supported") ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::doReadByte(uint32_t offset, uint8_t &byte)
{
	return setError("readByte not supported") ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::doReadShort(uint32_t offset, uint16_t &shortVal)
{
	return setError("readShort not supported") ;
}

//-------------------------------------------------------------------------------------------------------------
bool Bus::doReadWord(uint32_t offset, uint32_t &word)
{
	return setError("readWord not supported") ;
}
