/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Tif.cpp
 * \brief     Mop up ITif static values
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ITif.h"

using namespace Mplane ;


//=============================================================================================================
// SENTINEL CLASSES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class NullRtiMsgParser : public virtual IRtiMsgParser
{
public:
	NullRtiMsgParser() {}
    virtual ~NullRtiMsgParser() {}

    /**
     * Add the entry to the tree
     * @param entry
     * @return true if added ok
     */
    virtual bool add(RtiDirEntry* entry) { return false; }

    /**
     * Add the directory entry to the tree, making any intermediate directories as necessary
     * @param dir	Directory node
     * @return true if added ok
     */
    virtual bool addDir(DirClass* dir) { return false; }


    /**
     * Parse a message which may contain multiple commands separated by a command separator, then get a reply string
     * @param msg	Command string to parse
     * @return reply string
     */
    virtual std::string parseMulti(const std::string& msg) override { return ""; }


    /**
     * Parse a message and get a reply string
     * @param msg	Command string to parse
     * @return reply string
     */
    virtual std::string parse(const std::string& msg) { return ""; }

    /**
     * Allow the message parser to add any common arguments to a function call. The string is expected to be of the
     * form used by DataVariantList to create a list of arguments
     * @param callArgs	String defining the calling arguments
     * @return a (possibly modified) string defining the calling arguments
     */
    virtual std::string setCallArgs(const std::string& callArgs) const { return ""; }

    /**
     * Allow the message parser to add any common returns from a function call. The string is expected to be of the
     * form used by DataVariantList to create a list of arguments
     * @param returnArgs	String defining the return variables
     * @return a (possibly modified) string defining the return variables
     */
    virtual std::string setReturnArgs(const std::string& returnArgs) const { return ""; }

    /**
     * Attempt to set the working directory
     * @param dir
     * @return true if directory changed
     */
    virtual bool setWorkingDir(const std::string& dir) { return false; }

    /**
     * Get the current working directory
     * @return working directory node
     */
    virtual RtiDirEntry* getWorkingDir() const { return nullptr; }

    /**
     * Get the constant part of the prompt
     * @return prompt string
     */
    virtual std::string getPrompt() const { return ""; }

    /** send output asynchronous to the normal command handling
     *
     * @param data
     * @return 0 if ok
     */
    virtual int sendOutput(const std::string& data) { return -1; }

    /**
     * Enter or leave super user mode
     * @param superUser True to enter super user mode
     */
    virtual void setSuperUser(bool superUser) { return ; }

    /**
     * Are we in super user mode or not
     */
    virtual bool isSuperUser() const { return false; }


    // TCP port access

    /**
     * Create a tcp port for use with the test interface
     * @param type
     * @param port
     * @param maxConnections
     * @param failReason String set on failure
     * @return true if port opened ok
     */
    virtual bool tcpPortOpen(ITcpPortIoTypes::TcpPortType type, unsigned port, unsigned maxConnections, std::string& failReason) { return false; }

    /**
     * Close an opened port
     * @param port
     * @param failReason String set on failure
     * @return true if port closed ok
     */
    virtual bool tcpPortClose(unsigned port, std::string& failReason) { return false; }

    /**
     * Show information about all ports
     * @param os
     */
    virtual void tcpPortShow(std::ostream& os) { return ; }

    /**
     * Send the message to all clients connected to this port
     * @param port
     * @param msg	String to send
     */
    virtual void tcpPortSend(unsigned port, const std::string& msg) { return ; }

    /**
     * Send the message to all clients connected to this port
     * @param port
     * @param msg	String to send
     */
    virtual void tcpPortSend(unsigned port, const std::vector<uint8_t>& msg) { return ; }

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time
	 * @return false if not received the full data within the specified time
	 */
	virtual bool tcpPortReceive(unsigned port, std::vector<uint8_t>& data, unsigned expectedSize,
			unsigned timeoutSecs) { return false; }

	/**
	 * Receive a fixed sized set of data on this input port within the specified timeout time. Uses the specified
	 * callback to pass data to the user
	 * @return false if not received the full data within the specified time
	 */
	virtual bool tcpPortReceive(unsigned port, ITcpPortIoTypes::ReceiveCallback callback, unsigned expectedSize,
			unsigned timeoutSecs) { return false; }

	/**
     * Is this TCP port open
     * @param port
     * @return true if port opened
     */
    virtual bool tcpIsPortOpen(unsigned port) { return false; }

    /**
     * Method used to change the binary of the socket.
     * @param true sets socket as binary which handles binary messages (including NUL chars); false
     * treats messages as text teminating on NUL
     */
    virtual void tcpPortSetBinary(unsigned port, bool binary) { return ; }

};


//-------------------------------------------------------------------------------------------------------------
class NullRtiSettings : public virtual IRtiSettings
{
public:
    virtual ~NullRtiSettings() {};

    /**
     * Is this setting a valid name
     * @param name	Setting name
     * @return true if setting name is valid
     */
    virtual bool has(const std::string& name) const { return false; }

    /**
     * Get the setting value
     * @param name	Setting name
     * @return the setting value
     */
    virtual std::shared_ptr<DataVariant> get(const std::string& name) const { return std::shared_ptr<DataVariant>(); }

    /**
     * Get the setting value
     * @param name	Setting name
     * @return the setting value
     */
    virtual std::string getComment(const std::string& name) const { return ""; }

    /**
     * Change the setting value
     * @param name	Setting name
     * @param value	string containing the new value
     * @return true if able to set the value; false otherwise
     */
    virtual bool set(const std::string& name, const std::string& value) { return false; }

    /**
     * Returns an iterator that points at the start of the settings list
     * @return iterator at start of list
     */
    virtual std::vector< std::shared_ptr<DataVariant> >::const_iterator begin(void) const { return std::vector< std::shared_ptr<DataVariant> >().begin() ;}

    /**
     * Returns an iterator that points at the end of the settings list
     * @return iterator at end of list
     */
    virtual std::vector< std::shared_ptr<DataVariant> >::const_iterator end(void) const { return std::vector< std::shared_ptr<DataVariant> >().end() ;}

};



//=============================================================================================================
// ITifControl
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRtiMsgParser> ITifControl::NULL_MSG_PARSER{std::make_shared<NullRtiMsgParser>()} ;
std::shared_ptr<IRtiSettings> ITifControl::NULL_SETTINGS{std::make_shared<NullRtiSettings>()} ;
