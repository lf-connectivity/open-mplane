/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SocketProxy.h
 * \brief     Forwards data to/from a second socket
 *
 *
 * \details   Used with SocketHandler to allow one SocketHandler to filter messages for a second. The SocketHandler
 * 				is started with a file descriptor. This proxy is given that file descriptor and creates a new socket
 * 				to use to communicate with another SocketHandler (this new socket file descriptor being available via
 * 				getFd()).
 *
 * 				Any incoming messages are passed through this proxy and out, via the new socket, to the second SocketHandler.
 *
 *
 */


#ifndef SOCKETPROXY_H_
#define SOCKETPROXY_H_

#include <string>
#include <memory>
#include <string>

#include "Mutex.h"
#include "Task.h"

namespace Mplane {
class SocketMaster ;
class SocketSlave ;

class SocketProxy : public Task {
public:
	SocketProxy() ;
	virtual ~SocketProxy() ;

	/**
	 * Get the file descriptor (for the slave)
	 */
	int getFd() const ;

	/**
	 * Non-blocking: sends a message
	 */
	void sendMsg(const std::string& msg) ;

	/**
	 * Non-blocking: returns any reply chars
	 * @return reply chars or empty string
	 */
	std::string getReply() ;

    /**
     * Method checks the status of the (master) socket, ie it has a valid socket file
     * descriptor number
     * @return false, socket is closed, true socket is valid.
     */
    virtual bool isValid() const;

    /**
     * Method used to close the currently open master & slave socket
     */
    virtual bool close();


protected:
    /**
     * This is the method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     * @return the exit status of task process
     */
    virtual int run() override ;

private:
    void createSockets() ;

private:
    static Mutex mCreateMutex ;
    static int mProxyPort ;

private:
    std::shared_ptr<SocketMaster> mSockMaster ;
    std::shared_ptr<SocketSlave> mSockSlave ;
    Mutex mMutex ;
    std::string mReply ;
} ;

}

#endif /* SOCKETPROXY_H_ */
