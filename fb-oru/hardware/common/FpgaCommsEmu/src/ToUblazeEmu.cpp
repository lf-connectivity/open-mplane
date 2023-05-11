/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ToUblazeEmu.cpp
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
#include "ToUblazeEmu.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const unsigned WAIT_TIMEOUT_MS = 500 ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ToUblazeEmu::ToUblazeEmu(UINT32 startAddress, unsigned numAddresses, bool bufferMsgs) :
	CommsEmuHandler("ToUblazeEmu", startAddress, numAddresses, startAddress+SENDER_CTRL_OFFSET),
	mBufferMsgs(bufferMsgs),
	mPduLen( numAddresses*2 - HEADER_LEN-2),
	mTaskRunning(true),
	mMsgMutex(),
	mMsgs(),
	mCallback()
{
	// Need to initialise the send control & receive control words
	memWrite(mStartAddress + SENDER_CTRL_OFFSET, 0, 0xffff) ;
	memWrite(mStartAddress + RECEIVER_CTRL_OFFSET, 0, 0xffff) ;
	setSendClear() ;
	setReceiverReady(true) ;
}

//-------------------------------------------------------------------------------------------------------------
ToUblazeEmu::~ToUblazeEmu()
{
	mTaskRunning = false ;
	Conditional::Lock condLock(mTrigger) ;
	mTrigger.signal() ;
	msSleep(2) ;
}

//-------------------------------------------------------------------------------------------------------------
void ToUblazeEmu::bufferMsgs(bool buffer)
{
	// add to messages
	Mutex::Lock lock(mMsgMutex) ;

	mBufferMsgs = buffer ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<CommsEmuMsg> ToUblazeEmu::getMsgs()
{
	Mutex::Lock lock(mMsgMutex) ;
	std::vector<CommsEmuMsg> msgs ;
	using std::swap ;
	swap(msgs, mMsgs) ;
	return msgs ;
}

//-------------------------------------------------------------------------------------------------------------
bool ToUblazeEmu::setCallback(ToUblazeCallback callback)
{
	Mutex::Lock lock(mMsgMutex) ;
	mCallback = callback ;
	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int ToUblazeEmu::run()
{
    /*
     * Now our thread is running we just enter an infinite loop so we never end.
     * ALl image management is triggered by invocation of class methods, which are explicit action requests.
     */
    while (mTaskRunning)
    {
    	logDebugVerbose("COMMSEMU (to uBlaze) Wait SEND...") ;

        // Wait for SEND=1 - wait forever to this to start
    	do
    	{
			mTrigger.wait() ;
			if (!mTaskRunning)
				return 0 ;
    	} while (!isSend()) ;


    	// Respond
    	setReceiverReady(false) ;

		logDebugVerbose("COMMSEMU (to uBlaze) Process Data") ;

		// get the data
		processData() ;

		logDebugVerbose("COMMSEMU (to uBlaze) Processed Data") ;

    	// Respond
    	setReceiverReady(true) ;
    	setSendClear() ;
    }

    return 0;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
bool ToUblazeEmu::isSend()
{
	UINT16 mem = memRead(mStartAddress + SENDER_CTRL_OFFSET, 0xffff) ;
	return (mem != 0) ;
}

//-------------------------------------------------------------------------------------------------------------
void ToUblazeEmu::setReceiverReady(bool ready)
{
	memWrite(mStartAddress + RECEIVER_CTRL_OFFSET, (ready ? 1 : 0), 0xffff) ;
}

//-------------------------------------------------------------------------------------------------------------
void ToUblazeEmu::setSendClear()
{
	memWrite(mStartAddress + SENDER_CTRL_OFFSET, 0, 0xffff) ;
}

//-------------------------------------------------------------------------------------------------------------
void ToUblazeEmu::processData()
{
	logDebugVerbose("COMMSEMU (to uBlaze) processData() PDU_LEN=%u", mPduLen) ;

	UINT32 offset(DATA_OFFSET) ;
	UINT16 word(memRead(mStartAddress+offset, 0xffff)) ;
	offset += 2 ;

	std::vector<UINT8> data ;
	UINT8 type( (word >> 8) & 0xff ) ;

	UINT16 len(memRead(mStartAddress+offset, 0xffff)) ;
	offset += 2 ;
	unsigned lenWords( (len+1) / 2 ) ;

	logDebugVerbose("COMMSEMU (to uBlaze) Type 0x%02x len=%u", type, len) ;

	unsigned maxNumWords = mPduLen/2 ;
	if (maxNumWords > lenWords)
		maxNumWords = lenWords ;

	for (unsigned numWords = 1; numWords <= maxNumWords; ++numWords)
	{
		UINT16 word(memRead(mStartAddress+offset, 0xffff)) ;
		offset += 2 ;

		data.push_back( (word >> 8) & 0xff ) ;
		data.push_back( word & 0xff ) ;
	}

	// add to messages
	addMsg(CommsEmuMsg(type, data, true)) ;
}

//-------------------------------------------------------------------------------------------------------------
void ToUblazeEmu::addMsg(const CommsEmuMsg& msg)
{
	// add to messages
	Mutex::Lock lock(mMsgMutex) ;

	if (mBufferMsgs)
		mMsgs.push_back(msg) ;

	if (mCallback)
		mCallback(msg) ;
}
