/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsEmulator.h
 * \brief     Emulates comms with FPGA
 *
 *
 * \details   Emulates the comms protocol between PPC and FPGA. Provides a test interface for stimulating error conditions etc.
 *
 */


#ifndef FPGACOMMSEMULATOR_H_
#define FPGACOMMSEMULATOR_H_

#include <map>
#include <memory>
#include <vector>

#include "GlobalTypeDefs.h"
#include "Mutex.h"

namespace Mplane {

class CommsEmuMsg ;
class ToUblazeEmu ;
class FromUblazeEmu ;

class FpgaCommsEmulator {
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<FpgaCommsEmulator> getInstance() ;

	virtual ~FpgaCommsEmulator() ;

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
	 * Send one or messages (PDU) immediately
	 */
	virtual bool sendMsg(const CommsEmuMsg& msg) ;
	virtual bool sendMsgs(const std::vector<CommsEmuMsg>& msgs) ;

	/**
	 * Schedule a response for whenever we get the specified command
	 * @param command	Command word to match with incoming commands. Response sent on match
	 * @param msg		Msg (PDU) to send as a response
	 * @return true if scheduled ok
	 */
	virtual bool scheduleResponse(UINT16 command, const CommsEmuMsg& msg) ;

	/**
	 * Cause the write pointer (sender control) to be set to an invalid value
	 * @param ptr	Invalid value
	 */
	virtual void sendInvalidPtr(UINT16 ptr = 0xFFFF) ;

protected:
	FpgaCommsEmulator(unsigned toUblazeAddr, unsigned toUblazeLen,
			unsigned fromUblazeAddr, unsigned fromUblazeLen) ;

private:
	void toUblazeMsgHandler(const CommsEmuMsg& msg) ;

private:
	std::shared_ptr<ToUblazeEmu>	mToUblaze ;
	std::shared_ptr<FromUblazeEmu>	mFromUblaze ;

	// Any scheduled responses
	Mutex mMutex ;
	std::map<UINT16, std::vector<CommsEmuMsg>>	mScheduledResponses ;
} ;

}

#endif /* FPGACOMMSEMULATOR_H_ */
