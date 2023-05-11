#ifndef _IRTIMSGPARSER_H_
#define _IRTIMSGPARSER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRtiMsgParser.h
 * \brief     Interface to RTI message parser
 *
 *
 * \details   Interface to RTI message parser
 *
 */

#include <ostream>
#include <string>
#include <cstdint>
#include <vector>

#include "ITcpPortIoTypes.h"

namespace Mplane {

class RtiDirEntry ;
class DirClass ;

class IRtiMsgParser
{
public:
    virtual ~IRtiMsgParser() {};

    /**
     * Add the entry to the tree
     * @param entry
     * @return true if added ok
     */
    virtual bool add(RtiDirEntry* entry) = 0 ;

    /**
     * Add the directory entry to the tree, making any intermediate directories as necessary
     * @param dir	Directory node
     * @return true if added ok
     */
    virtual bool addDir(DirClass* dir) = 0 ;



    /**
     * Parse a message which may contain multiple commands separated by a command separator, then get a reply string
     * @param msg	Command string to parse
     * @return reply string
     */
    virtual std::string parseMulti(const std::string& msg) = 0;

    /**
     * Parse a message and get a reply string
     * @param msg	Command string to parse
     * @return reply string
     */
    virtual std::string parse(const std::string& msg) = 0;

    /**
     * Allow the message parser to add any common arguments to a function call. The string is expected to be of the
     * form used by DataVariantList to create a list of arguments
     * @param callArgs	String defining the calling arguments
     * @return a (possibly modified) string defining the calling arguments
     */
    virtual std::string setCallArgs(const std::string& callArgs) const = 0 ;

    /**
     * Allow the message parser to add any common returns from a function call. The string is expected to be of the
     * form used by DataVariantList to create a list of arguments
     * @param returnArgs	String defining the return variables
     * @return a (possibly modified) string defining the return variables
     */
    virtual std::string setReturnArgs(const std::string& returnArgs) const = 0 ;

    /**
     * Attempt to set the working directory
     * @param dir
     * @return true if directory changed
     */
    virtual bool setWorkingDir(const std::string& dir) = 0 ;

    /**
     * Get the current working directory
     * @return working directory node
     */
    virtual RtiDirEntry* getWorkingDir() const = 0 ;

    /**
     * Get the constant part of the prompt
     * @return prompt string
     */
    virtual std::string getPrompt() const = 0 ;

    /** send output asynchronous to the normal command handling
     *
     * @param data
     * @return 0 if ok
     */
    virtual int sendOutput(const std::string& data) = 0 ;

    /**
     * Enter or leave super user mode
     * @param superUser True to enter super user mode
     */
    virtual void setSuperUser(bool superUser) =0 ;

    /**
     * Are we in super user mode or not
     */
    virtual bool isSuperUser() const =0 ;


    // TCP port access

    /**
     * Create a tcp port for use with the test interface
     * @param type
     * @param port
     * @param maxConnections
     * @param failReason String set on failure
     * @return true if port opened ok
     */
    virtual bool tcpPortOpen(ITcpPortIoTypes::TcpPortType type, unsigned port, unsigned maxConnections, std::string& failReason) =0 ;

    /**
     * Close an opened port
     * @param port
     * @param failReason String set on failure
     * @return true if port closed ok
     */
    virtual bool tcpPortClose(unsigned port, std::string& failReason) =0 ;

    /**
     * Show information about all ports
     * @param os
     */
    virtual void tcpPortShow(std::ostream& os) =0 ;

    /**
     * Send the message to all clients connected to this port
     * @param port
     * @param msg	String to send
     */
    virtual void tcpPortSend(unsigned port, const std::string& msg) =0 ;

    /**
     * Send the message to all clients connected to this port
     * @param port
     * @param msg	String to send
     */
    virtual void tcpPortSend(unsigned port, const std::vector<uint8_t>& msg) =0 ;

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time
	 * @return false if not received the full data within the specified time
	 */
	virtual bool tcpPortReceive(unsigned port, std::vector<uint8_t>& data, unsigned expectedSize,
			unsigned timeoutSecs) =0 ;

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time. Uses the specified
	 * callback to pass data to the user
	 * @return false if not received the full data within the specified time
	 */
	virtual bool tcpPortReceive(unsigned port, ITcpPortIoTypes::ReceiveCallback callback, unsigned expectedSize,
			unsigned timeoutSecs) =0 ;

	/**
     * Is this TCP port open
     * @param port
     * @return true if port opened
     */
    virtual bool tcpIsPortOpen(unsigned port) =0 ;

    /**
     * Method used to change the binary of the socket.
     * @param true sets socket as binary which handles binary messages (including NUL chars); false
     * treats messages as text teminating on NUL
     */
    virtual void tcpPortSetBinary(unsigned port, bool binary) =0 ;



};


}
#endif /* _IRTIMSGPARSER_H_ */
