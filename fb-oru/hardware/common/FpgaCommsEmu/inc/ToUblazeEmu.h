/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ToUblazeEmu.h
 * \brief     Handles the comes from PPC to uBlaze
 *
 *
 * \details
 *
 */


#ifndef TOUBLAZEEMU_H_
#define TOUBLAZEEMU_H_

#include <functional>
#include "CommsEmuHandler.h"

namespace Mplane {

class ToUblazeEmu : public CommsEmuHandler
{
public:
	/**
	 * Create a DPD comms handler for channel2 (PPC -> uBlaze)
	 * @param startAddress
	 * @param numAddresses
	 * @param bufferMsgs	If true then saves the messages (making them available for getMsgs() method)
	 */
	ToUblazeEmu(UINT32 startAddress, unsigned numAddresses, bool bufferMsgs=false) ;
	virtual ~ToUblazeEmu() ;

	/**
	 * Enable/disable message buffering
	 * @param buffer
	 */
	virtual void bufferMsgs(bool buffer) ;

	/**
	 * Get a list of all the messages received over this interface
	 * @return
	 */
	virtual std::vector<CommsEmuMsg> getMsgs() ;

	/**
	 * Set a callback function that is called whenever a message (PDU) is received by the emulator (from the PPC)
	 */
	using ToUblazeCallback = std::function< void(const CommsEmuMsg&) > ;
	virtual bool setCallback(ToUblazeCallback callback) ;

protected:
    /**
     * This is the Task method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     *
     * \return the exit status of task process
     */
    virtual int run() override;

private:
    bool isSend();
    void setReceiverReady(bool ready);
    void setSendClear();

    void processData();
    void addMsg(const CommsEmuMsg& msg);


private:
    bool mBufferMsgs ;
    unsigned mPduLen ;
    bool mTaskRunning ;

    Mutex mMsgMutex ;
    std::vector<CommsEmuMsg> mMsgs ;

    ToUblazeCallback mCallback ;
} ;

}

#endif /* TOUBLAZEEMU_H_ */
