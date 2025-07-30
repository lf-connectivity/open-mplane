/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MPlaneConnectivityService.h
 * \brief     ORAN M-Plane Connectivity Service
 *
 *
 * \details   Responsible for supervising each NETCONF client connection.
 *
 */

#ifndef _MPLANE_CONNECTIVITY_SERVICE_H_
#define _MPLANE_CONNECTIVITY_SERVICE_H_

#include <cstdlib>
#include <cstdbool>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <map>

#include "Service.h"
#include "IMPlaneConnectivityService.h"
#include "WatchdogCount.h"

namespace Mplane
{

class MPlaneConnectivityService : public Service, public IMPlaneConnectivityService
{
public:
	MPlaneConnectivityService();
	virtual ~MPlaneConnectivityService();

	/*
	 * Returns the current service state
	 */
	virtual ServiceState_T getState() const;

	/*
	 * Get current notification timer value
	 */
	virtual UINT16 getTimer() const;

	/*
	 * Set notification interval
	 */
	virtual ReturnType::State setInterval(UINT16 interval);

	/*
	 * Get current notification interval
	 */
	virtual UINT16 getInterval() const;

	/*
	 * Get specific notification interval
	 */
	virtual UINT16 getInterval(UINT32 sessionId) const;

	/*
	 * Get specific supervision guard time
	 */
	virtual UINT16 getGuard(UINT32 sessionId) const;

	/*
	 * Get specified supervision monitoring time
	 */
	virtual UINT32 getMonitoring(UINT32 sessionId) const;

	/*
	 * Has an M-Plane supervisor expired?
	 */
	virtual bool isSupervisorExpired(UINT32 sessionId) const;

	/*
	 * Kick M-Plane connectivity service
	 */
	virtual ReturnType::State kick(UINT32 sessionId,
	                               UINT16 interval,
	                               UINT16 guard,
	                               std::string & nextUpdateAt);

	/**
	 * Register a callback for when the notification timer expires
	 */
	virtual void registerNotifTimerExpired(NotifTimerExpiredNotifyFunc func);

	/*
	 * Returns the specified state as a string
	 */
	static std::string toStateString(ServiceState_T state);

protected:
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
	virtual int service() override;

	/**
	 * Method called by the service start() method, to register this service with
	 * any particular Observer/Notify interface implementation.
	 *
	 * @note This method must be implemented by the inheriting service in order
	 * for it to register as an observer of other objects.
	 *
	 * @return true if registration successful.
	 */
	virtual bool registerObservers() override;

	/**
	 * Method called as a result of the radio control process calling reset
	 * in the service. By default the base class implementation does nothing.
	 */
	virtual void doReset() override;

private:
	//=========================================================================================================
	// Helper Functions
	//=========================================================================================================

	/*
	 * Sets the current service state
	 */
	virtual void setState(ServiceState_T state);

	/*
	 * Get a list of available open sysrepo sessions
	 */
	virtual std::vector<UINT32> getSessionIds();

	/*
	 * Add an M-Plane supervisor
	 */
	virtual ReturnType::State addSupervisor(UINT32 id);

	/*
	 * Remove an M-Plane supervisor
	 */
	virtual ReturnType::State removeSupervisor(UINT32 id);

	/*
	 * Get minimum interval
	 */
	virtual UINT16 getMinInterval() const;

	/*
	 * Returns true if all intervals have been set (non-zero)
	 */
	virtual bool areAllIntervalsSet() const;

	//=========================================================================================================
	// Parameters
	//=========================================================================================================

	// Service state
	ServiceState_T mState;

	// Interval between sending notifications
	UINT16 mNotifInterval;

	// Notification timer used to send periodically send supervision notifications
	UINT16 mNotifTimer;

	// Callback functions called when notification timer expires
	std::vector<NotifTimerExpiredNotifyFunc> mNotifTimerExpiredFunc;

	class Supervisor
	{
	public:
		typedef enum
		{
			UNINIT,
			OFF,
			ON,
			EXPIRED,
			FAULT,
		} State_T;

		Supervisor(MPlaneConnectivityService & service, UINT32 id);
		~Supervisor();

		ReturnType::State configure(UINT16 interval, UINT16 guardTime);

		ReturnType::State start();
		ReturnType::State stop();
		ReturnType::State tick();

		State_T state() const;
		UINT32 id() const;

		UINT16 getInterval() const;
		UINT16 getGuard() const;

		bool isSupervisorExpired() const;

	private:
		ReturnType::State initialise();

		// Parent service
		MPlaneConnectivityService & mService;

		// Supervisor state
		State_T mStateSupervisor;

		// Watchdog ID
		UINT32 mId;

		// Time settings
		UINT16 mInterval;
		UINT16 mGuardTime;

		// Watchdog counter used to monitor M-Plane connectivity
		std::shared_ptr<WatchdogCount> mWatchdog;
	};
	std::vector<std::shared_ptr<Supervisor>> mSupervisors;

	// Debug
	static std::map<ServiceState_T, std::string> mStateStr;
};

} /* namespace Mplane */

#endif /* _MPLANE_CONNECTIVITY_SERVICE_H_ */
