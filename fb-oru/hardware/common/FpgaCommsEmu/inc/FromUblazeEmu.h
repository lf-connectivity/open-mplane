/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FromUblazeEmu.h
 * \brief     Handles the comes to PPC from uBlaze
 *
 *
 * \details
 *
 */


#ifndef FROMUBLAZEEMU_H_
#define FROMUBLAZEEMU_H_

#include "CommsEmuHandler.h"

namespace Mplane {

class FromUblazeEmu : public CommsEmuHandler
{
public:
	/**
	 * Create a DPD comms handler for channel2 (PPC -> uBlaze)
	 * @param startAddress
	 * @param numAddresses
	 */
	FromUblazeEmu(UINT32 startAddress, unsigned numAddresses) ;
	virtual ~FromUblazeEmu() ;

	/**
	 * Send one or messages
	 */
	virtual bool sendMsg(const CommsEmuMsg& msg) ;
	virtual bool sendMsgs(const std::vector<CommsEmuMsg>& msgs) ;

	/**
	 * Cause the write pointer (sender control) to be set to an invalid value
	 * @param ptr	Invalid value
	 */
	virtual void sendInvalidPtr(UINT16 ptr = 0xFFFF) ;

protected:
    /**
     * This is the Task method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     *
     * \return the exit status of task process
     */
    virtual int run() override;

    bool resync() ;
    bool invalidPtr(INT16 ptr) ;

private:
	void memWriteBytes(const UINT32 address, const UINT8 byteHi, const UINT8 byteLo) ;

    void setSenderControl(INT16 value);
    INT16 getSenderControl();
    void setReceiverControl(INT16 value);
    INT16 getReceiverControl();
    bool isReceiverControl(INT16 value);

	bool sendPdu(const CommsEmuMsg& msg);
    void addMsg(const CommsEmuMsg& msg);



private:
    unsigned mFifoLen ;
    unsigned mFifoPduLen ;
    bool mTaskRunning ;
    Conditional mSendStart ;
    Conditional mSendComplete ;

    Mutex mMsgMutex ;
    std::vector<CommsEmuMsg> mMsgs ;
    UINT16 mTestPtr ;
} ;

}

#endif /* FROMUBLAZEEMU_H_ */
