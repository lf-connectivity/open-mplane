#ifndef _RTIMSGHANDLERPARSER_H_
#define _RTIMSGHANDLERPARSER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiMsgParser.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <cstdint>
#include <vector>
#include <string>
#include "SocketHandler.h"
#include "SocketClient.h"

#include "IRtiMsgParser.h"
#include "ITelnet.h"
#include "RtiSettings.h"
#include "RtiMsgEditor.h"
#include "RtiTelnet.h"
#include "DirNode.h"

namespace Mplane {

class RtiDirEntry ;
class DirClass ;

class RtiMsgHandler:
		public SocketHandler,
		public RtiSettings,
		public IRtiMsgParser,
		public ITelnet
{
public:

    RtiMsgHandler();

    virtual ~RtiMsgHandler();

    // IRtiMsgParser

    /**
     * Add the entry to the tree
     * @param entry
     * @return true if added ok
     */
    virtual bool add(RtiDirEntry* entry) override ;

    /**
     * Add the directory entry to the tree, making any intermediate directories as necessary
     * @param dir	Directory node
     * @return true if added ok
     */
    virtual bool addDir(DirClass* dir) override ;

    /**
     * Parse a message which may contain multiple commands separated by a command separator, then get a reply string
     * @param msg	Command string to parse
     * @return reply string
     */
    virtual std::string parseMulti(const std::string& msg) override ;

    /**
     * Parse the command string
     * @param msg	Command string
     * @return reply string
     */
    virtual std::string parse(const std::string& msg) override ;

    /**
     * Allow the message parser to add any common arguments to a function call. The string is expected to be of the
     * form used by DataVariantList to create a list of arguments
     * @param callArgs	String defining the calling arguments
     * @return a (possibly modified) string defining the calling arguments
     */
    virtual std::string setCallArgs(const std::string& callArgs) const override ;

    /**
     * Allow the message parser to add any common returns from a function call. The string is expected to be of the
     * form used by DataVariantList to create a list of arguments
     * @param returnArgs	String defining the return variables
     * @return a (possibly modified) string defining the return variables
     */
    virtual std::string setReturnArgs(const std::string& returnArgs) const override ;

    /**
     * Attempt to set the working directory
     * @param dir
     * @return true if directory changed
     */
    virtual bool setWorkingDir(const std::string& dir) override ;

    /**
     * Get the current working directory
     * @return working directory node
     */
    virtual RtiDirEntry* getWorkingDir() const override ;

    /**
     * Get the constant part of the prompt
     * @return prompt string
     */
    virtual std::string getPrompt() const override ;


    /**
     * Enter or leave super user mode
     * @param superUser True to enter super user mode
     */
    virtual void setSuperUser(bool superUser) override ;

    /**
     * Are we in super user mode or not
     */
    virtual bool isSuperUser() const override ;



    // TCP port interface

    /**
     * Create a tcp port for use with the test interface
     * @param type
     * @param port
     * @param maxConnections
     * @param failReason String set on failure
     * @return true if port opened ok
     */
    virtual bool tcpPortOpen(ITcpPortIoTypes::TcpPortType type, unsigned port, unsigned maxConnections,
    		std::string& failReason) override ;

    /**
     * Close an opened port
     * @param port
     * @param failReason String set on failure
     * @return true if port closed ok
     */
    virtual bool tcpPortClose(unsigned port, std::string& failReason) override ;

    /**
     * Show information about all ports
     * @param os
     */
    virtual void tcpPortShow(std::ostream& os) override ;

    /**
     * Send the message to all clients connected to this port
     * @param port
     * @param msg	String to send
     */
    virtual void tcpPortSend(unsigned port, const std::string& msg) override ;

    /**
     * Send the message to all clients connected to this port
     * @param port
     * @param msg	String to send
     */
    virtual void tcpPortSend(unsigned port, const std::vector<uint8_t>& msg) override ;

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time
	 * @return false if not received the full data within the specified time
	 */
	virtual bool tcpPortReceive(unsigned port, std::vector<uint8_t>& data,
			unsigned expectedSize, unsigned timeoutSecs) override ;

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time. Uses the specified
	 * callback to pass data to the user
	 * @return false if not received the full data within the specified time
	 */
	virtual bool tcpPortReceive(unsigned port, ITcpPortIoTypes::ReceiveCallback callback, unsigned expectedSize,
			unsigned timeoutSecs) override ;

    /**
     * Is this TCP port open
     * @param port
     * @return true if port opened
     */
    virtual bool tcpIsPortOpen(unsigned port) override ;

    /**
     * Method used to change the binary of the socket.
     * @param true sets socket as binary which handles binary messages (including NUL chars); false
     * treats messages as text teminating on NUL
     */
    virtual void tcpPortSetBinary(unsigned port, bool binary) override ;



    // ITelnet

	/**
	 * Send a message to the telnet interface
	 * @param msg
	 */
    virtual bool send(const std::string& msg) override ;

	/**
	 * Receive a message from the telnet interface
	 * @param msg
	 */
    virtual int recv(std::string& msg) override ;


protected:

    /**
     * Attempt to handle the command as a built-in command
     * @param command
     * @return reply string or empty if not handled
     */
    std::string procCommand(const std::string& command ) ;

    /** send output asynchronous to the normal command handling
     *
     * @param data
     * @return 0 if ok
     */
    virtual int sendOutput(const std::string& data) ;

protected:
    // Socket handler
    virtual int handler();

private:
    // Get the list of all the paths in the tree
    std::vector<std::string> getDirPaths(const DirNodePtr& dirNode) ;

    // given the list of absolute paths, return the list of paths relative to this path
    std::vector<std::string> getRelPaths(const std::vector<std::string>& absPaths, const std::string& path) ;

    // given a list of paths possibly with a path separator, produce a list of just those with separators but with
    // the separator converted to '.'
    std::vector<std::string> getDotPaths(const std::vector<std::string>& paths) ;

    // is this path hidden from the current user
    bool isPathHidden(DirNodePtr node) const ;

protected:

    RtiDirEntry* mTreeRoot ;		//<! top of "directory tree" of classes/functions
    RtiDirEntry* mCwd ;				//<! current working "directory"

    bool mRtiConnected;

    bool mThereWasAnException;

    bool mSuperUser ;
};


}
#endif /* _RTIMSGHANDLERPARSER_H_ */
