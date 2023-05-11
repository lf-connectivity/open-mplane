/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IMsgQ.h
 * \brief
 *
 *
 * \details   Virtual interface to POSIX message queues
 *
 */


#ifndef IMSGQ_H_
#define IMSGQ_H_

#include <memory>
#include <string>
#include <vector>

namespace Mplane {

/*!
 * \class IMsgQ
 */
class IMsgQ {
public:
	IMsgQ() {}
	virtual ~IMsgQ() {}

	/**
	 * Factory method
	 */
	static std::shared_ptr<IMsgQ> factory(const std::string& name) ;


	/**
	 * Create a new message queue
	 * @param msgSize	Maximum size of a message
	 * @param maxMsgs	Maximum number of messages that can be sent (i.e. message queue buffer size)
	 * @return true if created; false otherwise
	 */
	virtual bool create(unsigned msgSize, unsigned maxMsgs) =0 ;

	/**
	 * Connect to an existing message queue for writing only
	 * @param blocking	Set to false for non-blocking operation
	 * @return true if connected; false otherwise
	 */
	virtual bool connectRead(bool blocking = true) =0 ;

	/**
	 * Connect to an existing message queue for reading only
	 * @param blocking	Set to false for non-blocking operation
	 * @return true if connected; false otherwise
	 */
	virtual bool connectWrite(bool blocking = true) =0 ;

	/**
	 * Close down the message queue (and unlink a created queue)
	 * @return true if closed ok; false if already closed
	 */
	virtual bool close() =0 ;

	/**
	 * Used to determine if read data is available. Used for non-blocking poll
	 * @return true if data ready; false otherwise
	 */
	virtual bool isDataReady() =0 ;

	/**
	 * Get read data. For blocking operation will block until data is available and return it. For non-blocking
	 * operation will only return data if any available
	 * @param data
	 * @return true if got data; false otherwise
	 */
	virtual bool getData(std::vector<unsigned char>& data) =0 ;

	/**
	 * Send some data. For blocking operation will block until can send; for non-blocking operation will
	 * return immediately with false return if unable to send
	 * @param data
	 * @param priority	Set the message priority
	 * @return true if sent; false otherwise
	 */
	virtual bool sendData(const std::vector<unsigned char>& data, unsigned priority=0) =0 ;

	/**
	 * Get the maximum message size allowed
	 */
	virtual unsigned getMaxMsgSize() const =0 ;

	/**
	 * Get the message queue name
	 */
	virtual std::string getName() const =0 ;



} ;

}

#endif /* IMSGQ_H_ */
