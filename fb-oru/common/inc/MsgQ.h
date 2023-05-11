/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MsgQ.h
 * \brief     POSIX.4 message queue
 *
 *
 * \details
 *
 */


#ifndef MSGQ_H_
#define MSGQ_H_

#include <mqueue.h>
#include <vector>
#include <string>

#include "IMsgQ.h"
#include "Mutex.h"

namespace Mplane {

class MsgQ : public virtual IMsgQ {
public:
	/**
	 * Construct a MsgQ with a fix message queue name
	 */
	explicit MsgQ(const std::string& name) ;

	/**
	 * Destroy the MsgQ. Closes any connected message queue and unlinks any queue created
	 */
	virtual ~MsgQ() ;

	/**
	 * Create a new message queue
	 * @param msgSize	Maximum size of a message
	 * @param maxMsgs	Maximum number of messages that can be sent (i.e. message queue buffer size)
	 * @return true if created; false otherwise
	 */
	virtual bool create(unsigned msgSize, unsigned maxMsgs) override ;

	/**
	 * Connect to an existing message queue for writing only
	 * @param blocking	Set to false for non-blocking operation
	 * @return true if connected; false otherwise
	 */
	virtual bool connectRead(bool blocking = true) override ;

	/**
	 * Connect to an existing message queue for reading only
	 * @param blocking	Set to false for non-blocking operation
	 * @return true if connected; false otherwise
	 */
	virtual bool connectWrite(bool blocking = true) override ;

	/**
	 * Close down the message queue (and unlink a created queue)
	 * @return true if closed ok; false if already closed
	 */
	virtual bool close() override ;

	/**
	 * Used to determine if read data is available. Used for non-blocking poll
	 * @return true if data ready; false otherwise
	 */
	virtual bool isDataReady() override ;

	/**
	 * Get read data. For blocking operation will block until data is available and return it. For non-blocking
	 * operation will only return data if any available
	 * @param data
	 * @return true if got data; false otherwise
	 */
	virtual bool getData(std::vector<unsigned char>& data) override ;

	/**
	 * Send some data. For blocking operation will block until can send; for non-blocking operation will
	 * return immediately with false return if unable to send
	 * @param data
	 * @param priority	Set the message priority
	 * @return true if sent; false otherwise
	 */
	virtual bool sendData(const std::vector<unsigned char>& data, unsigned priority=0) override ;

	/**
	 * Get the maximum message size allowed
	 */
	virtual unsigned getMaxMsgSize() const override ;

	/**
	 * Get the message queue name
	 */
	virtual std::string getName() const override ;

private:
	std::string mName ;

	Mutex mMutex ;
	bool mCreated ;
	mqd_t mMqd;
	unsigned mMsgSize ;
	bool mBlocking ;
	std::vector<unsigned char> mBuffer ;
} ;

}

#endif /* MSGQ_H_ */
