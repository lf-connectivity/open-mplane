/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRemoteMsgHandler.h
 * \brief     Virtual interface to remote message handler
 *
 *
 * \details   Virtual interface to allow a factory to create the appropriate instance
 *
 */


#ifndef COMMON_REMOTEPROC_INC_IREMOTEMSGHANDLER_H_
#define COMMON_REMOTEPROC_INC_IREMOTEMSGHANDLER_H_

#include <functional>
#include <memory>
#include <vector>
#include <set>
#include <string>

#include "DataVariant.h"
#include "IHostFileMgr.h"

namespace Mplane {

/*!
 * \class  IRemoteMsgHandler
 * \brief
 * \details
 *
 */
class IRemoteMsgHandler {
public:
	IRemoteMsgHandler() {}
	virtual ~IRemoteMsgHandler() {}

	/**
	 * Factory to create each of the instances of message handler - one per remote processor
	 */
	static std::shared_ptr<IRemoteMsgHandler> factory(unsigned remoteId) ;

	/**
	 * Load the remote processor with the specified firmware, start it up, and connect up the channel
	 */
	virtual bool connect(const std::string& firmware) =0 ;

	/**
	 * Shutdown the remote processor
	 */
	virtual bool disconnect() =0 ;

	/**
	 * Is the handler running?
	 */
	virtual bool isActive() const =0 ;

	/**
	 * Is the event loop running?
	 */
	virtual bool isEventLoop() const =0 ;

	/**
	 * Send a command string to the remote processor
	 */
	virtual bool sendCommand(const std::string& cmd,
			const std::vector<DataVariant>& attributes,
			const std::set<std::string>& varNames,
			std::vector<DataVariant>& replyAttributes,
			unsigned timeoutMs) =0 ;


	/**
	 * Start/stop the event loop handling messages from the processor
	 */
	virtual bool eventLoop(bool start) =0 ;

	/**
	 * Get any error string
	 */
	virtual std::string error() =0 ;


	/**
	 * Either start or stop the processor
	 */
	virtual bool procSetState(bool start) =0 ;

	/**
	 * get the current processor state
	 */
	virtual int procState() =0 ;

	/**
	 * Get the file manager for this handler
	 */
	virtual std::shared_ptr<IHostFileMgr> fileMgr() =0 ;


	/**
	 * define the command received callback
	 */
	using CommandReceivedFunc = std::function<void(const std::string& cmd)> ;

	/**
	 * Register a callback for when a command is received
	 */
	virtual void registerCmdReceivedFunc(CommandReceivedFunc func) =0 ;


	/**
	 * Define the event PDU received callback
	 *
	 * Callback is called with the payload converted to a string and a map of the variable/value pairs
	 */
	using EventFunc = std::function<void(const std::string& payload, const std::map<std::string, DataVariant>& attributes)> ;

	/**
	 * Define the alarm PDU received callback
	 *
	 * Callback is called with the payload converted to a string and a map of the variable/value pairs
	 */
	using AlarmFunc = std::function<void(const std::string& payload, const std::map<std::string, DataVariant>& attributes)> ;


	/**
	 * Register a callback for when an event PDU is received
	 */
	virtual void registerEventFunc(EventFunc func) =0 ;

	/**
	 * Register a callback for when an alarm PDU is received
	 */
	virtual void registerAlarmFunc(AlarmFunc func) =0 ;


} ;

}

#endif /* COMMON_REMOTEPROC_INC_IREMOTEMSGHANDLER_H_ */
