/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MulticastSocket.h
 * \brief     Creates a UDP socket suitable for multicast
 *
 *
 * \details
 *
 */


#ifndef MulticastSocket_H_
#define MulticastSocket_H_

#include "Socket.h"

namespace Mplane {

class MulticastSocket : public Socket {
public:
	MulticastSocket() ;
	virtual ~MulticastSocket() ;

	/**
	 * Multicast-specific method used to set the ip address and port used for this multicast
	 * @param addr
	 * @param port
	 * @return true if socket can be set up with the supplied settings
	 */
	virtual bool setMulticast(const std::string& addr, unsigned port) ;

    /**
     * This method is used to create a basic AF_INET socket type.
     * @return true if created OK otherwise false
     */
    virtual bool create() override ;
    /**
     * Method used to send a string out on the currently open socket.
     * @param reference to a string to send
     * @return true if sent OK otherwise false.
     */
    virtual bool send(const std::string&) override;
    /**
     * Method used to receive a string on the currently open port.
     * @param reference to string to populate
     * @return number of characters received
     */
    virtual int recv(std::string&) override;

public:
    /**
     * Default address to use for multicast
     */
    static std::string MULTICAST_ADDRESS ;

} ;

}

#endif /* MulticastSocket_H_ */
