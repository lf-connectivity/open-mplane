/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TcpPortHelper.h
 * \brief     Helper class for TcpPort
 *
 *
 * \details
 *
 */


#ifndef TCPPORTHELPER_H_
#define TCPPORTHELPER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "DataVariant.h"

#include "IRtiMsgParser.h"

namespace Mplane {

class TcpPortHelper {
public:
	/**
	 * Create a TcpPort helper connected to the specified port
	 * @param msgParser
	 * @param portVarName
	 * @param callList
	 */
	TcpPortHelper(IRtiMsgParser& msgParser, const std::string& portVarName, DataVariantList *callList) ;

	virtual ~TcpPortHelper() ;

    /**
     * Send the message to all clients connected to this port
     * @param msg	String to send
     */
    void send(const std::string& msg) ;

    /**
     * Send the message to all clients connected to this port
     * @param msg	String to send
     */
    void send(const std::vector<uint8_t>& msg) ;

    /**
     * Send the message to all clients connected to this port
     * @param fmt	String printf format
     */
    void send(char const* fmt, ... )
		__attribute__ ((format (printf, 2, 3))) ;

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time
	 * @return false if not received the full data within the specified time
	 */
	bool receive(std::vector<uint8_t>& data, unsigned expectedSize, unsigned timeoutSecs) ;

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time. Uses the specified
	 * callback to pass data to the user
	 * @return false if not received the full data within the specified time
	 */
	bool receive(ITcpPortIoTypes::ReceiveCallback callback, unsigned expectedSize,
			unsigned timeoutSecs) ;

	/**
	 * Check the port number for validity and to ensure that the TCP port is open. Sets the error in the returnList otherwise
	 * @param portVarName
	 * @param callList
	 * @param returnList
	 * @return true if port number ok
	 */
	static bool portValid(IRtiMsgParser& msgParser, const std::string& portVarName, DataVariantList *callList, DataVariantList *returnList) ;

private:
	IRtiMsgParser& mMsgParser ;
	unsigned mPort ;
} ;

}

#endif /* TCPPORTHELPER_H_ */
