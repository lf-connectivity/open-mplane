/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      INetworkingService.h
 * \brief
 *
 *
 */


#ifndef COMMON_NETWORKINGSERVICE_INC_INETWORKINGSERVICE_H_
#define COMMON_NETWORKINGSERVICE_INC_INETWORKINGSERVICE_H_

#include <memory>
#include <string>

#include "INetAddrPolicy.h"

namespace Mplane {

/*!
 * \class  INetworkingService
 * \brief
 * \details
 *
 */
class INetworkingService {
public:
	INetworkingService() {}
	virtual ~INetworkingService() {}

	/**
	 * Singleton - one instance per interface
	 */
	static std::shared_ptr<INetworkingService> singleton(const std::string& interface) ;

	/**
	 * Get the service's network address policy
	 */
	virtual std::shared_ptr<INetAddrPolicy> getNetAddrPolicy() =0 ;

	/**
	 * Restart the service
	 */
	virtual void restart() =0 ;

	/**
	 * Pause the service
	 */
	virtual void pause() =0 ;

	/**
	 * Enable/disable a named enable flag. Service will be paused until ALL enables are TRUE
	 */
	virtual void startEnable(const std::string& name, bool enable) =0 ;

} ;

}

#endif /* COMMON_NETWORKINGSERVICE_INC_INETWORKINGSERVICE_H_ */
