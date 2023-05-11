/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteMsgHandlerShim.h
 * \brief     A remote message handler shim layer
 *
 *
 * \details   Provides a lightweight IRemoteMsgHandler layer with direct connections to the remote processor host comms.
 * 				Used when the "remote" app is embedded in the main Linux application
 *
 */


#ifndef COMMON_REMOTEPROC_INC_REMOTEMSGHANDLERSHIM_H_
#define COMMON_REMOTEPROC_INC_REMOTEMSGHANDLERSHIM_H_

#include <memory>
#include <atomic>
#include <condition_variable>
#include <mutex>

#include "RemoteMsgHandlerBase.h"

namespace Mplane {

/*!
 * \class  RemoteMsgHandlerShim
 * \brief
 * \details
 *
 */
class RemoteMsgHandlerShim : public RemoteMsgHandlerBase {
public:
	RemoteMsgHandlerShim(unsigned index, std::shared_ptr<IFpgaMsgTokens> tokens) ;
	virtual ~RemoteMsgHandlerShim() ;

	/**
	 * Load the remote processor with the specified firmware, start it up, and connect up the channel
	 */
	virtual bool connect(const std::string& firmware) override ;

	/**
	 * Shutdown the remote processor
	 */
	virtual bool disconnect() override ;

	/**
	 * Send a command string to the remote processor
	 */
	virtual bool sendCommand(const std::string& cmd,
			const std::vector<DataVariant>& attributes,
			const std::set<std::string>& varNames,
			std::vector<DataVariant>& replyAttributes,
			unsigned timeoutMs) override ;

	// Helper methods

	virtual int hostOpen(const char *filename, int flags, int mode) ;

	virtual int hostRead(int fd, uint8_t *buffer, int buflen) ;

	virtual int hostWrite(int fd, const uint8_t *buffer, int buflen) ;

	virtual int hostClose(int fd) ;

	virtual bool hostCommandReceived() ;

	virtual bool hostGetCommand(uint8_t* command, unsigned max_command_len) ;

	virtual bool hostCommandReply(uint8_t* reply, unsigned reply_len) ;



private:
	std::mutex mMsgMutex ;
	std::string mCmd ;
	std::string mCmdReply ;
	std::atomic<bool> mGotReply ;
	std::condition_variable mReplyCv ;
} ;

}

#endif /* COMMON_REMOTEPROC_INC_REMOTEMSGHANDLERSHIM_H_ */
