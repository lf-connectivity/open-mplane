/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TcpPortIo.h
 * \brief     A TCP port server
 *
 *
 * \details   TIF command is used to create a server on this TCP port, with a specified maximum number of connections
 * 				Any data sent to this port from the application is sent on to any connected clients.
 *
 * 				Input data handling is TBD
 *
 */


#ifndef TCPPORTIO_H_
#define TCPPORTIO_H_

#include <ostream>
#include <cstdint>
#include <string>
#include <vector>

#include "SocketServer.h"
#include "ITcpPortIoTypes.h"

namespace Mplane {

class TcpPortIo : public SocketServer
{
public:
	/**
	 * Create a tcp port server
	 * @param type in/out/inout
	 * @param port
	 * @param maxConnections
	 */
	TcpPortIo(ITcpPortIoTypes::TcpPortType type, unsigned port, unsigned maxConnections) ;

	virtual ~TcpPortIo() ;

    /**
     * Method used to change the binary of the socket.
     * @param true sets socket as binary which handles binary messages (including NUL chars); false
     * treats messages as text terminating on NUL
     */
    virtual void setBinary(const bool binary) override ;


	/**
	 * Allows the application to send this message out to all connected clients on this port
	 */
	virtual bool send(const std::string& msg) ;

	/**
	 * Allows the application to send this message out to all connected clients on this port
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

} ;

}

#endif /* TCPPORTIO_H_ */
