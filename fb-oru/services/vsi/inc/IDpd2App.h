/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpd2App.h
 * \brief     Virtual interface to 2nd gen DPD application
 *
 *
 * \details
 *
 */


#ifndef IDPDAPP_H_
#define IDPDAPP_H_

#include <cstdint>
#include <memory>
#include <string>
#include <functional>

namespace Mplane {

class IDpd2App {
public:
	IDpd2App() {}
	virtual ~IDpd2App() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IDpd2App> getInstance() ;

	/**
	 * Start the DPD application running
	 */
	virtual bool start() =0 ;

	/**
	 * Is the DPD application up and running
	 */
	virtual bool isDpdRunning() const =0 ;

	/**
	 * Provide an interface to the C code for it to wait until the capture is completed or timed out
	 * @param timeoutMs
	 * @return true if done; false if timed out
	 */
	virtual bool waitCaptureDone(unsigned timeoutMs) =0 ;

	// Host interface

	using HostPollFunc = std::function<void()> ;
	using HostShutdownFunc = std::function<void(void* data)> ;
	using HostCommandReceivedFunc = std::function<void(const char* cmd)> ;

	virtual int hostInit(const char *ept_name, HostPollFunc poll, HostShutdownFunc shutdown, HostCommandReceivedFunc cmdReceived) =0 ;

	virtual void hostRelease() =0 ;

	virtual int hostOpen(const char *filename, int flags, int mode) =0 ;

	virtual int hostRead(int fd, uint8_t *buffer, int buflen) =0 ;

	virtual int hostWrite(int fd, const uint8_t *buffer, int buflen) =0 ;

	virtual int hostClose(int fd) =0 ;

	virtual int hostTerminate() =0 ;

	virtual bool hostCommandReceived() =0 ;

	virtual bool hostGetCommand(uint8_t* command, unsigned max_command_len) =0 ;

	virtual bool hostCommandReply(uint8_t* reply, unsigned reply_len) =0 ;

} ;

}

#endif /* IDPDAPP_H_ */
