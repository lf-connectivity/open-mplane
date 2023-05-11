/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITelnet.h
 * \brief     Telnet send/receive interface
 *
 *
 * \details
 *
 */


#ifndef ITELNET_H_
#define ITELNET_H_


namespace Mplane {


/**
 * Define the interface for the object that provides the data to/from the telnet session
 */
class ITelnetSend {
public:
	ITelnetSend() {}
	virtual ~ITelnetSend() {}

	/**
	 * Send a message to the telnet interface
	 * @param msg
	 */
	virtual bool send(const std::string& msg) = 0 ;

};


/**
 * Define the interface for the object that provides the data from the telnet session
 */
class ITelnetRecv {
public:
	ITelnetRecv() {}
	virtual ~ITelnetRecv() {}

	/**
	 * Receive a message from the telnet interface
	 * @param msg
	 */
	virtual int recv(std::string& msg) = 0 ;
};

/**
 * Send and receive
 */
class ITelnet : public ITelnetSend, public ITelnetRecv {
public:
	ITelnet() {}
	virtual ~ITelnet() {}

} ;

}

#endif /* ITELNET_H_ */
