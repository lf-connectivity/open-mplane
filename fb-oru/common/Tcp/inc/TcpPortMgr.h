/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TcpPortMgr.h
 * \brief     Manages the tcp ports
 *
 *
 * \details
 *
 */


#ifndef TCPPORTMGR_H_
#define TCPPORTMGR_H_

#include <string>
#include <ostream>
#include <memory>
#include <map>
#include <vector>
#include <cstdint>

#include "Mutex.h"
#include "ITcpPortIoTypes.h"

namespace Mplane {

class TcpPortIo ;

class TcpPortMgr {
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<TcpPortMgr> getInstance() ;

	TcpPortMgr() ;
	virtual ~TcpPortMgr() ;

    /**
     * Create a tcp port for use with the test interface
     * @param type
     * @param port
     * @param maxConnections
     * @param failReason String set on failure
     * @return true if port opened ok
     */
    virtual bool portOpen(ITcpPortIoTypes::TcpPortType type, unsigned port, unsigned maxConnections,
    		std::string& failReason) ;

    /**
     * Close an opened port
     * @param port
     * @param failReason String set on failure
     * @return true if port closed ok
     */
    virtual bool portClose(unsigned port, std::string& failReason) ;

    /**
     * Show information about a port
     * @param os
     */
    virtual void portShow(unsigned port, std::ostream& os) ;

    /**
     * Show information about all ports
     * @param os
     */
    virtual void show(std::ostream& os) ;

    /**
     * Send the message to all clients connected to this port
     * @param port
     * @param msg	String to send
     */
    virtual void portSend(unsigned port, const std::string& msg) ;

    /**
     * Send the message to all clients connected to this port
     * @param port
     * @param msg	String to send
     */
    virtual void portSend(unsigned port, const std::vector<uint8_t>& msg) ;

    /**
     * Send the message to all clients connected to this port
     * @param port
     * @param fmt	String printf format
     */
    virtual void portSend(unsigned port, char const* fmt, ... )
		__attribute__ ((format (printf, 3, 4))) ;

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time
	 * @return false if not received the full data within the specified time
	 */
	virtual bool portReceive(unsigned port, std::vector<uint8_t>& data, unsigned expectedSize, unsigned timeoutSecs) ;

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time. Uses the specified
	 * callback to pass data to the user
	 * @return false if not received the full data within the specified time
	 */
	virtual bool portReceive(unsigned port, ITcpPortIoTypes::ReceiveCallback callback, unsigned expectedSize, unsigned timeoutSecs) ;

	/**
     * Is this TCP port open
     * @param port
     * @return true if port opened
     */
    virtual bool isPortOpen(unsigned port) ;

    /**
     * Method used to change the binary of the socket.
     * @param true sets socket as binary which handles binary messages (including NUL chars); false
     * treats messages as text terminating on NUL
     */
    virtual void setBinary(unsigned port, bool binary) ;

	/**
	 * Close all opened ports
	 */
	virtual void closePorts() ;


private:
    Mutex mMutex ;
    std::map< unsigned, std::shared_ptr<TcpPortIo> > mTcpPorts ;

} ;

}

#endif /* TCPPORTMGR_H_ */
