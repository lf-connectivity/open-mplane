/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommsEmuHandler.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CommsEmuHandler.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const unsigned COMMSEMU_PRIORITY = 10 ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::CommsEmuHandler::CommsEmuHandler(const std::string& name,
		UINT32 startAddress, unsigned numAddresses, UINT32 triggerAddress) :
	Task(COMMSEMU_PRIORITY, Task::MEDIUM_STACK, name.c_str(), "CommsEmu"),

	mTrigger(),
	mStartAddress(startAddress),
	mNumAddresses(numAddresses),
	mTriggerAddress(triggerAddress),

	mFpga(OffTargetFPGA::getInstance()),
	mMutex(),
	mRegs(numAddresses, 0xDDDD)
{
//	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "CommsEmu") ;

	// register ourself to handle COMMS memory
	mFpga->registerHandler(mStartAddress, mStartAddress+(mNumAddresses-1)*2,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readHandler(address, mask) ;
		}
	) ;

	logDebugNormal("COMMSEMU %s registered 0x%05x .. 0x%05x", name.c_str(), mStartAddress, mStartAddress+(mNumAddresses-1)*2) ;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::CommsEmuHandler::~CommsEmuHandler()
{
	// un-register ourself
	mFpga->unRegisterHandler(mStartAddress, mStartAddress+(mNumAddresses-1)*2) ;

	logDebugNormal("COMMSEMU un-registered 0x%05x .. 0x%05x", mStartAddress, mStartAddress+(mNumAddresses-1)*2) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
UINT16 Mplane::CommsEmuHandler::memWrite(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	logDebugVerbose("COMMSEMU write 0x%05x: 0x%04x / 0x%04x", address, value, mask) ;

	// convert address to offset
	if (address < mStartAddress)
		return 0xFEED ;

	unsigned offset = (address - mStartAddress) / 2 ;
	if (offset >= mNumAddresses)
		return 0xFEED ;

	Mutex::Lock lock(mMutex) ;
	UINT16 mem = mRegs[offset] ;
	mem = (mem & ~mask) | (value & mask) ;
	mRegs[offset] = mem ;
	return mem ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 Mplane::CommsEmuHandler::memRead(const UINT32 address, const UINT16 mask)
{

	// convert address to offset
	if (address < mStartAddress)
		return 0xFEED ;

	unsigned offset = (address - mStartAddress) / 2 ;
	if (offset >= mNumAddresses)
		return 0xFEED ;

	Mutex::Lock lock(mMutex) ;
	UINT16 mem = mRegs[offset] & mask ;

//	logDebugVerbose("COMMSEMU read 0x%05x: 0x%04x / 0x%04x", address, mem, mask) ;
	return mem ;
}



//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
UINT16 Mplane::CommsEmuHandler::writeHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	// write to memory
	UINT16 mem(memWrite(address, value, mask)) ;

	// if we've written to the trigger location, trigger the task
	if (address == mTriggerAddress)
	{
		logDebugVerbose("COMMSEMU write handler 0x%05x (trigger)", address) ;

		Conditional::Lock condLock(mTrigger) ;
		mTrigger.signal() ;
	}

	return mem ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 Mplane::CommsEmuHandler::readHandler(const UINT32 address, const UINT16 mask)
{
	// read memory
	return memRead(address, mask) ;
}
