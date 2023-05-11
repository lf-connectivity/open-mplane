/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdFromUblazeEmu.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IFpgaCommsConstants.h"
#include "FromUblazeEmu.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//const unsigned SEND_TIMEOUT_MS = 1000 ;
//const unsigned WAIT_TIMEOUT_MS = 500 ;

const unsigned SEND_TIMEOUT_MS = 10000 ;
const unsigned WAIT_TIMEOUT_MS = 5000 ;



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::FromUblazeEmu::FromUblazeEmu(UINT32 startAddress, unsigned numAddresses) :
	CommsEmuHandler("FromUblazeEmu", startAddress, numAddresses, startAddress+RECEIVER_CTRL_OFFSET),
	mFifoLen( numAddresses*2 - HEADER_LEN ),
	mFifoPduLen( (mFifoLen-2)/2 ),
	mTaskRunning(true),
	mSendStart(),
	mSendComplete(),
	mMsgMutex(),
	mMsgs(),
	mTestPtr(0)
{
	// Need to initialise the send control & receive control words
	setSenderControl(CTRL_RESET_REQ) ;
	setReceiverControl(0) ;

	// signal that we've completed all sending
	Conditional::Lock condLock(mSendComplete) ;
	mSendComplete.signal() ;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::FromUblazeEmu::~FromUblazeEmu()
{
	mTaskRunning = false ;
	Conditional::Lock condLock(mTrigger) ;
	mTrigger.signal() ;
	msSleep(2) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::FromUblazeEmu::sendMsg(const CommsEmuMsg& msg)
{
	logDebugNormal("COMMSEMU (from uBlaze) sendMsg: PDU '%s'", msg.getPdu().getData().c_str()) ;
	std::vector<CommsEmuMsg> msgs ;
	msgs.push_back(msg) ;
	return sendMsgs(msgs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::FromUblazeEmu::sendMsgs(const std::vector<CommsEmuMsg>& msgs)
{
	logDebugNormal("COMMSEMU (from uBlaze) sendMsgs") ;

	logDebugVerbose("COMMSEMU (from uBlaze) sendMsgs: wait for send complete") ;

	// wait for send complete or timeout
	if (mSendComplete.wait(SEND_TIMEOUT_MS) == false)
		return false ;

	logDebugVerbose("COMMSEMU (from uBlaze) sendMsgs: start send") ;

	// buffer up the messages
	for (auto msg : msgs)
		addMsg(msg) ;

	// now trigger a send
	Conditional::Lock condLock(mSendStart) ;
	mSendStart.signal() ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::FromUblazeEmu::sendInvalidPtr(UINT16 ptr)
{
	if (ptr < mFifoLen)
		ptr = mFifoLen ;

	// add to messages
	Mutex::Lock lock(mMsgMutex) ;
	mTestPtr = ptr ;

	// now trigger the run task
	Conditional::Lock condLock(mSendStart) ;
	mSendStart.signal() ;

}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int Mplane::FromUblazeEmu::run()
{
	// resync at startup
	resync() ;

    /*
     * Now our thread is running we just enter an infinite loop so we never end.
     * ALl image management is triggered by invocation of class methods, which are explicit action requests.
     */
    while (mTaskRunning)
    {
    	// wait until we need to send something
    	mSendStart.wait() ;

		// if we're causing a fault then do it
		{
			Mutex::Lock lock(mMsgMutex) ;
			if (mTestPtr != 0)
			{
				setSenderControl(mTestPtr) ;
				mTestPtr = 0 ;

				// slight pause to allow PPC to start responding
				msSleep(100) ;
			}
		}

    	// Check for a reset/resync request from receiver
    	INT16 readPtr(getReceiverControl()) ;
    	if (invalidPtr(readPtr))
    	{
    		if (!resync())
    			continue ;
    	}

    	// Process all of the messages
    	{
    		Mutex::Lock lock(mMsgMutex) ;
    		for (auto msg : mMsgs)
    		{
    			if (!sendPdu(msg))
    				break ;
    		}

    		mMsgs.clear() ;
    	}


    	// completed
		Conditional::Lock condLock(mSendComplete) ;
		mSendComplete.signal() ;
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::FromUblazeEmu::resync()
{
	logDebugNormal("COMMSEMU (from uBlaze) **Resync**") ;

	// Reset request
	logDebugVerbose("COMMSEMU (from uBlaze) write-ptr=CTRL_RESET_REQ") ;
	setSenderControl(CTRL_RESET_REQ) ;

	// Wait for receiver to acknowledge reset request
	logDebugVerbose("COMMSEMU (from uBlaze) Wait for reset request ack...") ;
	bool ok ;
	do
	{
		ok = mTrigger.wait(WAIT_TIMEOUT_MS) ;
		if (!mTaskRunning)
			return false ;
    	if (!ok)
    	{
    		// leave in reset state but value allows us to detect that it has timed out
    		setSenderControl(CTRL_ACK_TMO) ;

        	logDebugVerbose("COMMSEMU (from uBlaze) Timed out waiting for reset request ack") ;
        	return false ;
    	}
	} while (ok && !isReceiverControl(CTRL_RESET_ACK)) ;


	// Reset sender
	logDebugVerbose("COMMSEMU (from uBlaze) write-ptr=CTRL_RESET_ACK") ;
	setSenderControl(CTRL_RESET_ACK) ;

	// Wait for receiver to be released
	logDebugVerbose("COMMSEMU (from uBlaze) Wait for receiver to be released...") ;
	do
	{
		ok = mTrigger.wait(WAIT_TIMEOUT_MS) ;
		if (!mTaskRunning)
			return false ;
    	if (!ok)
    	{
    		// leave in reset state but value allows us to detect that it has timed out
    		setSenderControl(CTRL_RELEASE_TMO) ;

        	logDebugVerbose("COMMSEMU (from uBlaze) Timed out waiting for receiver to be released") ;
        	return false ;
    	}
	} while (ok && !isReceiverControl(0)) ;


	// Release sender
	logDebugVerbose("COMMSEMU (from uBlaze) write-ptr=0") ;
	setSenderControl(0) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::FromUblazeEmu::invalidPtr(INT16 ptr)
{
	if ((ptr < 0) || ((UINT16)ptr >= mFifoLen))
		return true ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::FromUblazeEmu::sendPdu(const CommsEmuMsg& msg)
{
	logDebugVerbose("COMMSEMU (from uBlaze) sendPdu: start") ;

	// get the pointers
	INT16 readPtr(getReceiverControl()) ;
	INT16 writePtr(getSenderControl()) ;

	logDebugVerbose("COMMSEMU (from uBlaze) sendPdu: check write ptr") ;

	// check validity
	if (invalidPtr(writePtr))
		return false ;

	logDebugVerbose("COMMSEMU (from uBlaze) sendPdu: check read ptr") ;

	// check for resync request
	if (invalidPtr(readPtr))
	{
		if (!resync())
			return false ;

		// re-read the pointers
		readPtr = getReceiverControl() ;
		writePtr = getSenderControl() ;
	}

	// Pad the PDU to even number of bytes
	std::vector<UINT8> data(msg.getData()) ;
	unsigned dataSize(data.size()) ;
	if (data.size() == 0)
		std::cerr << "ERROR: Sending null PDU" << std::endl ;
	if (data.size() % 2 == 1)
		data.push_back(0) ;

	// calculate the number of bytes required to be written into the memory
	unsigned numBytes = data.size() + HEADER_LEN ;

	logDebugVerbose("COMMSEMU (from uBlaze) sendPdu: number of bytes = %u", numBytes) ;

	// see if there are enough bytes available in memory, otherwise wait
	int availableBytes = 0 ;
	do
	{
		availableBytes = readPtr - writePtr ;
		if (availableBytes <= 0)
			availableBytes += mFifoLen ;

		logDebugVerbose("COMMSEMU (from uBlaze) Available bytes = %d, Read = 0x%04x, Write = 0x%04x",
				availableBytes, readPtr, writePtr) ;

		if ( (unsigned)availableBytes < numBytes)
		{
			// wait for PPC to read some out
	    	bool ok = mTrigger.wait(SEND_TIMEOUT_MS) ;
			if (!mTaskRunning)
				return false ;
			if (!ok)
			{
				logDebugVerbose("COMMSEMU (from uBlaze) Timed out waiting for space in FIFO") ;
				return false ;
			}
			readPtr = getReceiverControl() ;
		}

	} while ( (unsigned)availableBytes < numBytes) ;

	logDebugVerbose("COMMSEMU (from uBlaze) Available bytes = %d, Amount of data to store = %u", availableBytes, (unsigned)data.size()) ;

	// We now have sufficient room in the fifo to store the pdu - write the data into the circular buffer
	unsigned numWords = (data.size() / 2) ;
	memWriteBytes(mStartAddress + DATA_OFFSET + writePtr, msg.getType(), 0) ;
	writePtr += 2 ;
	memWriteBytes(mStartAddress + DATA_OFFSET + writePtr, (dataSize>>8)&0xff, dataSize&0xff) ;
	for (unsigned word=0; word < numWords; ++word)
	{
		// move pointer - wrap at end of buffer
		writePtr += 2 ;
		if ((unsigned)writePtr >= mFifoLen)
			writePtr = 0 ;

		unsigned byte = word*2 ;
		memWriteBytes(mStartAddress + DATA_OFFSET + writePtr, data[byte], data[byte+1]) ;
	}

	// move pointer - wrap at end of buffer
	writePtr += 2 ;
	if ((unsigned)writePtr >= mFifoLen)
		writePtr = 0 ;

	logDebugVerbose("COMMSEMU (from uBlaze) Changing the write ptr = 0x%04x", writePtr) ;

	// update the write pointer
	setSenderControl(writePtr) ;

	logDebugVerbose("COMMSEMU (from uBlaze) sendPdu: complete") ;

	return true ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::FromUblazeEmu::setSenderControl(INT16 value)
{
	memWrite(mStartAddress + SENDER_CTRL_OFFSET, value, 0xffff) ;
}

//-------------------------------------------------------------------------------------------------------------
INT16 Mplane::FromUblazeEmu::getSenderControl()
{
	return (INT16)memRead(mStartAddress + SENDER_CTRL_OFFSET, 0xffff) ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::FromUblazeEmu::setReceiverControl(INT16 value)
{
	memWrite(mStartAddress + RECEIVER_CTRL_OFFSET, value, 0xffff) ;
}

//-------------------------------------------------------------------------------------------------------------
INT16 Mplane::FromUblazeEmu::getReceiverControl()
{
	return (INT16)memRead(mStartAddress + RECEIVER_CTRL_OFFSET, 0xffff) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::FromUblazeEmu::isReceiverControl(INT16 value)
{
	return getReceiverControl() == value ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::FromUblazeEmu::memWriteBytes(const UINT32 address, const UINT8 byteHi, const UINT8 byteLo)
{
	memWrite(address, (byteHi << 8) | (byteLo), 0xffff) ;
}


//-------------------------------------------------------------------------------------------------------------
void Mplane::FromUblazeEmu::addMsg(const CommsEmuMsg& msg)
{
	// add to messages
	Mutex::Lock lock(mMsgMutex) ;
	mMsgs.push_back(msg) ;
}
