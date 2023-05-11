/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TcpPortIoHandler.h
 * \brief     Socket handler for tcp ports
 *
 *
 * \details
 *
 */


#ifndef TCPPORTIOHANDLER_H_
#define TCPPORTIOHANDLER_H_

#include <string>
#include <vector>

#include "Mutex.h"
#include "Conditional.h"
#include "QueueBuffer.hpp"
#include "SocketHandler.h"
#include "ITcpPortIoTypes.h"

namespace Mplane {

class TcpPortIoHandler : public SocketHandler
{
public:
	using super = SocketHandler ;

	/**
	 * Constructor for tcp port handler
	 * @param type in/out/inout
	 * @param port		Port being served (for information only)
	 * @param instance	Current instance number (for information only)
	 * @param maxConnections	Total number of instances (for information only)
	 */
	TcpPortIoHandler(ITcpPortIoTypes::TcpPortType type,
			unsigned port, unsigned instance, unsigned maxConnections) ;

	virtual ~TcpPortIoHandler() ;

	/**
	 * Allows the application to send this message out to a connected client on this port
	 */
	virtual bool send(const std::string& msg) ;

	/**
	 * Allows the application to send this message out to a connected client on this port
	 */
	virtual bool send(const std::vector<uint8_t>& msg) ;

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time
	 * @return false if not received the full data within the specified time
	 */
	virtual bool receive(std::vector<uint8_t>& data, unsigned expectedSize, unsigned timeoutSecs) ;

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time. Uses the specified
	 * callback to pass data to the user
	 * @return false if not received the full data within the specified time
	 */
	virtual bool receive(ITcpPortIoTypes::ReceiveCallback callback, unsigned expectedSize, unsigned timeoutSecs) ;




	/**
	 * Show details about this port
	 * @param os Output stream
	 */
	virtual void show(std::ostream& os) ;

	/**
	 * Static member function which formats the show() information into fixed columns
	 */
	static void showFormat(std::ostream& os,
			const std::string& portStr,
			const std::string& typeStr,
			const std::string& instanceStr,
			const std::string& connectionStr) ;


protected:
    /**
     * This method MUST be implemented as the receive/send loop
     * of the super class socket handler.
     * @return error indicator
     */
    virtual int handler() override ;

private:
	/**
	 * Does the data send
	 */
    void sendData(const std::string& msg) ;

    // tidy up after receive
    void receiveEnd() ;

private:
    ITcpPortIoTypes::TcpPortType mType ;
    unsigned mPort ;
    unsigned mInstance ;
    unsigned mMaxConnections ;
    QueueBuffer<std::string> mQueue ;

    // Set to ip address of connection when connection
    std::string mConnection ;

    // PORT IN settings
    Mutex mInMutex ;
    unsigned mInSize;			// expected total size
    unsigned mReceivedBytes ;	// total bytes received so far
//    std::vector<uint8_t>* mInBuffer ;
    ITcpPortIoTypes::ReceiveCallback mCallback ;	// Callback for storing the data
    Conditional mInDoneSignal ;
} ;

}

#endif /* TCPPORTIOHANDLER_H_ */
