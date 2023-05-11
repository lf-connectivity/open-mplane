/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectService.h
 * \brief     ORAN C/U-Plane Connectivity Service
 *
 *
 * \details   Responsible for monitoring each logical C/U-plane connection associated
 *            with a processing element.
 *
 */

#ifndef _CUPLANE_CONNECT_SERVICE_H_
#define _CUPLANE_CONNECT_SERVICE_H_

#include <cstdlib>
#include <cstdbool>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <map>

#include "ICUPlaneConnectService.h"
#include "WatchdogCount.h"
#include "Service.h"


namespace Mplane
{

class CUPlaneConnectService : public Service, public ICUPlaneConnectService
{
public:
	CUPlaneConnectService();
	virtual ~CUPlaneConnectService();

	typedef enum
	{
		DISABLED,
		RUNNING,
		FAULT,
	} ServiceState_T;

	/*
	 * Adds a supervising connection
	 */
	ReturnType::State addConnection(uint16_t id, uint16_t monitoringInterval);

	/*
	 * Removes a supervising connection
	 */
	ReturnType::State removeConnection(uint16_t id);

	/*
	 * Returns the current service state
	 */
	ServiceState_T getState() const;

protected:
	/*
	 * Sets the current service state
	 */
	void setState(ServiceState_T state);

	/**
	 * Method defined by the Loggable interface must be implemented by all
	 * object to force the display of the objects current status.
	 */
	virtual void show() override;

	/**
	 * Method that MUST be implemented by the inheriting service. The work done
	 * my the service, is implemented by this method.
	 * @return
	 */
	virtual int service();

	/**
	 * Method called as a result of the radio control process calling reset
	 * in the service. By default the base class implementation does nothing.
	 */
	virtual void doReset() override;

private:
	//=========================================================================================================
	// Helper Functions
	//=========================================================================================================

	//=========================================================================================================
	// Parameters
	//=========================================================================================================
	// Service state
	ServiceState_T mState;

	// Watchdog counter used to monitor C/U-Plane connectivity
	WatchdogCount mWatchdog;

	// Mutex to prevent the service from being interrupted by TIF command requests
	mutable Mutex mMutex;

	// Debug
	static std::map<ServiceState_T, std::string> mStateStr;

};

} /* namespace Mplane */

#endif /* _CUPLANE_CONNECT_SERVICE_H_ */
