/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetworkingService.h
 * \brief
 *
 *
 */


#ifndef COMMON_NETWORKINGSERVICE_INC_NETWORKINGSERVICE_H_
#define COMMON_NETWORKINGSERVICE_INC_NETWORKINGSERVICE_H_

#include <string>
#include <memory>
#include <atomic>

#include "INetAddrPolicy.h"
#include "TaskPeriodicEvent.h"
#include "INetworkingService.h"

namespace Mplane {

/*!
 * \class  NetworkingService
 * \brief
 * \details
 *
 */
class NetworkingService : public virtual INetworkingService, public TaskPeriodicEvent {
public:
	NetworkingService(const std::string& interface) ;
	virtual ~NetworkingService() ;

    static const unsigned int SERVICE_PERIOD = 100;  // 100 msec service period

	/**
	 * Get the service's network address policy
	 */
	virtual std::shared_ptr<INetAddrPolicy> getNetAddrPolicy() override ;

	/**
	 * Restart the service
	 */
	virtual void restart() override ;

	/**
	 * Pause the service
	 */
	virtual void pause() override ;

	/**
	 * Enable/disable a named enable flag. Service will be paused until ALL enables are TRUE
	 */
	virtual void startEnable(const std::string& name, bool enable) override ;


protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;


protected:
	// add an allocator
	void addAllocator(std::shared_ptr<INetAddr> addrAllocator) ;

	// get the network interface
	std::string netInterface() const ;

	// check the interface's MAC id against a value stored in UBOOT env and set it to match the env if it doesn't
	// already. Method is given the UBOOT env variable name from which to get the MAC id
	// NOTE: If env variable does not exist, then this method silently returns
	void checkMac(const std::string& macEnvVarName) ;

private:
	std::string mNetInterface ;
    std::shared_ptr<INetAddrPolicy> mNetPolicy ;
    std::atomic<bool> mPaused ;
    std::atomic<bool> mEnable ;

    // A collection of named enables. Need ALL of them to be TRUE to allow the service to run
    std::map<std::string, bool> mStartEnables ;
} ;

}


#endif /* COMMON_NETWORKINGSERVICE_INC_NETWORKINGSERVICE_H_ */
