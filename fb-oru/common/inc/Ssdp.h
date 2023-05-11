/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ssdp.h
 * \brief     Provides singleton for Simple Services Discovery Protocol
 *
 *
 * \details   Supports discovery of any Mplane RRH's in a network using SSDP. Uses a Task to initialise the worker objects
 * 				after waiting for the specified network interface to be up with an assigned IP address. Once initialised the
 * 				Task exits and leaves the worker objects to handle the execution
 *
 */


#ifndef SSDP_H_
#define SSDP_H_

#include <memory>
#include <string>

#include "INetStatus.h"

#include "TaskEvent.h"

namespace Mplane {

class NetDevice ;
class MulticastSocket ;
class SsdpReceiver ;
class SsdpSender ;

class Ssdp : public TaskEvent, public Observer<INetStatus, const INetChange&> {
public:
	/**
	 * SSDP multicast ip address and port
	 */
	static const std::string SSDP_ADDRESS ;
	static const unsigned SSDP_PORT ;

	/**
	 * Constructor
	 * @param application
	 * @param appVersion
	 * @param netInterface
	 * @param cacheAgeSecs
	 * @param xmlPath
	 */
	Ssdp(const std::string& application, const std::string& appVersion,
		const std::string& netInterface,
		unsigned cacheAgeSecs = 1800,
		const std::string& xmlPath = "") ;
	virtual ~Ssdp() ;

	/**
	 * Get the interface IP address
	 */
	virtual std::string getIp() const ;

	/**
	 * Get the SSDP UUID of this node
	 */
	virtual std::string getUuid() const ;

	/**
	 * Get the cache max age in seconds. This is the maximum time between "alive" notifications
	 */
	virtual unsigned getCacheAge() const ;

	/**
	 * Get the number of M-SEARCH messages responded to. An M-SEARCH is sent out by a controlling entity to discover what's connected
	 * to the network
	 */
	virtual unsigned getSearchCount() const ;

	/**
	 * Get the number of NOTIFY messages sent. This node sends out notifications randomly (within a max delay period) in order to tell
	 * all controlling entities of it's presence
	 */
	virtual unsigned getNotifyCount() const ;

	/**
	 * Add additional fields to the response message
	 */
	virtual void injectExtraFields(const std::map<std::string, std::string>& fields) ;


	// Observer interface
public:
    /**
     * This is an alternative callback method that allows the subject matter
     * provider to supply additional data that relates to the subject type.
     * This default implementation must be overridden by the observer.
     * @param subject
     * @param data
     */
    virtual void update(INetStatus& subject, const INetChange& data) override ;

    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const override ;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:
    // Wait until this interface is up AND has an ip address
    std::shared_ptr<NetDevice> waitInterface(const std::string& interfaceName) const ;

    // Create a UUID
    std::string createUuid(const std::string& mac) const ;

    // stop the RX & TX children
    void stopSsdp() ;

private:
    std::string mApp ;
    std::string mAppVersion ;
    std::string mNetInterface ;
    unsigned mCacheAgeSecs ;
    std::string mXmlPath ;

    std::string mUuid ;
    std::string mIfAddress ;
	std::shared_ptr<MulticastSocket> mSock ;
	std::shared_ptr<SsdpReceiver> mRx ;
	std::shared_ptr<SsdpSender> mTx ;

    std::map<std::string, std::string> mExtraFields ;
} ;

}

#endif /* SSDP_H_ */
