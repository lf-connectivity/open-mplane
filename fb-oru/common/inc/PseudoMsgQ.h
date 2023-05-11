/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PseudoMsgQ.h
 * \brief
 *
 *
 * \details   Class which implements the IMsgQ interface but doesn't use any POSIX message queues (just connects via buffers)
 * 			Used to port code which used to be split and communicate via MsgQ but has now been combined into a single application.
 * 			This is a stepping stone toward proper full integration
 *
 */


#ifndef PSEUDOMSGQ_H_
#define PSEUDOMSGQ_H_

#include <memory>
#include <queue>
#include <vector>
#include <string>

#include "IMsgQ.h"
#include "Mutex.h"
#include "Conditional.h"

namespace Mplane {

/*!
 * \class PseudoMsgQ
 */
class PseudoMsgQ : public virtual IMsgQ {
public:
	/**
	 * Construct a MsgQ with a fix message queue name
	 */
	explicit PseudoMsgQ(const std::string& name) ;

	/**
	 * Destroy the MsgQ. Closes any connected message queue and unlinks any queue created
	 */
	virtual ~PseudoMsgQ() ;

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

protected:
	bool transferData(const std::vector<unsigned char>& data) ;

private:
	std::string mName ;

	Mutex mMutex ;
	Conditional mCond ;
	bool mCreator ;
	bool mConnected ;
	bool mWriter ;
	bool mBlocking ;

	// receive buffers
	std::queue<std::vector<unsigned char>> mBuffer ;

	// Manage the pseudo message queues
	class PseudoMsgMgr ;
	friend class PseudoMsgMgr ;
	std::shared_ptr<PseudoMsgMgr> mMsgMgr ;
} ;

}

#endif /* PSEUDOMSGQ_H_ */
