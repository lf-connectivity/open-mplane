/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MPlaneConnectivityService.cpp
 * \brief     ORAN M-Plane Connectivity Service
 *
 *
 * \details   Responsible for supervising each NETCONF client connection:
 *
 *              1) Monitors each connection using a watchdog timer.
 *              3) Periodically notifies each connected NETCONF client that ORAN supervision is operational.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <string>
#include <memory>

#if !defined (OFF_TARGET)
#include "ISystemReboot.h"
#endif

#include "YangMgrServer.h"
#include "YangMgrService.h"
#include "SysrepoUtils.h"
#include "YangUtils.h"
#include "YangModule.h"

#include "MPlaneConnectivityService.h"

using namespace Mplane;

//=============================================================================================================
// DEFINITIONS
//=============================================================================================================

//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// STATIC
//=============================================================================================================
std::map<MPlaneConnectivityService::ServiceState_T, std::string> MPlaneConnectivityService::mStateStr =
{
	{ ServiceState_T::UNINIT,        "UNINIT"        }, 	// Uninitialised
	{ ServiceState_T::RUNNING,       "RUNNING"       }, 	// Service running with notifications
	{ ServiceState_T::PAUSED,        "PAUSED"        }, 	// Service running without notifications
	{ ServiceState_T::FAULT,         "FAULT"         }, 	// A fault has occurred
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
MPlaneConnectivityService::MPlaneConnectivityService()
	: Service(SERVICE_LOW_PRIORITY,
	          SMALL_STACK,
	          1000, // update stuff every 1000ms
	          "MPlaneConnectivityService",
	          "YANG")
	, mState(ServiceState_T::UNINIT)
	, mNotifInterval(0)
	, mNotifTimer(0)
	, mNotifTimerExpiredFunc()
	, mSupervisors()
{
#ifdef OFF_TARGET
	Loggable::setLevel(ILoggable::LogDebugLevel::LOG_DEBUG_NORMAL);
#endif
	logDebugNormal("%s: No NETCONF sessions running", getName());
}

//-------------------------------------------------------------------------------------------------------------
MPlaneConnectivityService::~MPlaneConnectivityService()
{
}

//-------------------------------------------------------------------------------------------------------------
MPlaneConnectivityService::ServiceState_T MPlaneConnectivityService::getState() const
{
	return mState;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 MPlaneConnectivityService::getTimer() const
{
	return mNotifTimer;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State MPlaneConnectivityService::setInterval(UINT16 interval)
{
	logDebugNormal("%s: Set notification interval [interval=%d]", getName(), interval);

	// Initialise notification interval
	if (mState == ServiceState_T::UNINIT)
	{
		setState(ServiceState_T::RUNNING);
	}

	mNotifInterval = interval;

	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 MPlaneConnectivityService::getInterval() const
{
	return mNotifInterval;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 MPlaneConnectivityService::getInterval(UINT32 sessionId) const
{
	UINT32 idx = 0;
	while (idx < mSupervisors.size())
	{
		if (mSupervisors[idx]->id() == sessionId)
			return mSupervisors[idx]->getGuard();
		idx++;
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 MPlaneConnectivityService::getGuard(UINT32 sessionId) const
{
	UINT32 idx = 0;
	while (idx < mSupervisors.size())
	{
		if (mSupervisors[idx]->id() == sessionId)
			return mSupervisors[idx]->getInterval();
		idx++;
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 MPlaneConnectivityService::getMonitoring(UINT32 sessionId) const
{
	UINT32 idx = 0;
	while (idx < mSupervisors.size())
	{
		if (mSupervisors[idx]->id() == sessionId)
			return (mSupervisors[idx]->getInterval() + mSupervisors[idx]->getGuard());
		idx++;
	}
	return 0;
}

bool MPlaneConnectivityService::isSupervisorExpired(UINT32 sessionId) const
{
	UINT32 idx = 0;
	while (idx < mSupervisors.size())
	{
		if (mSupervisors[idx]->id() == sessionId)
			return (mSupervisors[idx]->isSupervisorExpired());
		idx++;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State MPlaneConnectivityService::kick(UINT32 sessionId,
                                                  UINT16 interval,
                                                  UINT16 guard,
                                                  std::string & nextUpdateAt)
{
#ifdef OFF_TARGET
	if (mState == ServiceState_T::UNINIT)
		throw std::runtime_error("MPlaneConnectivityService: Not initialised");
#endif

// Update monitors

	logDebugNormal("%s: Kick [id=%d interval=%d guard=%d]",
		getName(), sessionId, interval, guard);

	// Find supervisor
	bool foundSupervisor = false;
	UINT32 idx = 0;
	while (idx < mSupervisors.size())
	{
		if (mSupervisors[idx]->id() == sessionId)
		{
			foundSupervisor = true;
			break;
		}
		idx++;
	}

	// No supervisor. Create a new one
	if (!foundSupervisor)
		addSupervisor(sessionId);

	// Update supervisor monitoring
	mSupervisors[idx]->configure(interval, guard);
	if (guard > 0)
	{
		// Start supervisor
		logDebugNormal("%s: Start Supervisor [id=%d monitoringTime=%d]",
			getName(), mSupervisors[idx]->id(), (interval+guard));
		mSupervisors[idx]->start();
	}

	else
	{
		// Stop supervisor
		logDebugNormal("%s: Stop Supervisor [id=%d]", getName(), mSupervisors[idx]->id());
		mSupervisors[idx]->stop();
	}

	// No interval specified, pause notifications
	if ((interval == 0) || (!areAllIntervalsSet()))
	{
		setState(ServiceState_T::PAUSED);
	}

	// Notifications paused. Restart if interval specified.
	else if (mState == ServiceState_T::PAUSED)
	{
		// Restart notifications with specified interval
		if (interval > 0)
		{
			setState(ServiceState_T::RUNNING);
		}
	}

	// Notifications not paused
	else
	{
		setState(ServiceState_T::RUNNING);
	}

// Set time, when next supervision notification is expected

	// No timer interval
	if (mState == ServiceState_T::PAUSED)
	{
		nextUpdateAt.clear();
	}

	// Valid timer interval
	else
	{
		// Use the smallest notification timer interval
		UINT16 minInterval = getMinInterval();
		mNotifInterval = minInterval;
		if (mNotifTimer > minInterval)
		{
			mNotifTimer = mNotifInterval;
		}

		// Calculate time when next supervision notification is expected
		time_t timestamp;
		time(&timestamp);
		timestamp += mNotifTimer + 1;
		nextUpdateAt = YangUtils::getDateTime(timestamp);
		logDebugNormal("%s: Next update at %s", getName(), nextUpdateAt.c_str());
	}

	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
void MPlaneConnectivityService::registerNotifTimerExpired(NotifTimerExpiredNotifyFunc func)
{
	mNotifTimerExpiredFunc.push_back(func);
}

//-------------------------------------------------------------------------------------------------------------
std::string MPlaneConnectivityService::toStateString(ServiceState_T state)
{
	return mStateStr[state];
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void MPlaneConnectivityService::show()
{
	eventInfo("%s[%s]: Show", getName(), mStateStr[mState].c_str());
}

//-------------------------------------------------------------------------------------------------------------
int MPlaneConnectivityService::service()
{
#ifdef OFF_TARGET
	if (mState == ServiceState_T::UNINIT)
		throw std::runtime_error("MPlaneConnectivityService: Not initialised");
#endif

	// Decrement notification timer
	if (mNotifTimer > 0)
	{
		mNotifTimer--;
	}
	logDebugVerbose("%s: Tick [timer=%d]", getName(), mNotifTimer);

	// Check if notification timer has expired
	if (mNotifTimer == 0)
	{
		// Get a list of available open NETCONF sessions
		std::vector<UINT32> ids = getSessionIds();

		// Remove inactive session supervisors
		for (auto supervisor : mSupervisors)
		{
			bool foundSession = false;
			for (auto id : ids)
			{
				if (supervisor->id() == id)
				{
					foundSession = true;
					break;
				}
			}
			if (!foundSession)
				removeSupervisor(supervisor->id());
		}

		// Reset notification timer
		mNotifTimer = mNotifInterval;

		// Do not send notifications when we're paused
		if (mState != ServiceState_T::PAUSED)
		{
			// Notify observers that the notification timer has expired
			for (auto & func : mNotifTimerExpiredFunc)
			{
				func();
			}
		}
	}

	// Update all supervisors
	for (auto supervisor : mSupervisors)
	{
		supervisor->tick();

		// Log fault
		if (supervisor->state() == Supervisor::State_T::FAULT)
		{
/* ToDo: The does not match the spec, if we have more than one connection.
         We should start recovery without losing other connections */
			setState(ServiceState_T::FAULT);
		}
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
bool MPlaneConnectivityService::registerObservers()
{
	// No observers to register
	//eventInfo("%s[%s]: registerObservers", getName(), mStateStr[mState].c_str());
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void MPlaneConnectivityService::doReset()
{
	eventInfo("%s[%s]: Reset", getName(), mStateStr[mState].c_str());
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void MPlaneConnectivityService::setState(ServiceState_T state)
{
	if (state != mState)
	{
		logDebugVerbose("%s: State Change [%s] => [%s]",
			getName(), mStateStr[mState].c_str(), mStateStr[state].c_str());
	}
	mState = state;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<UINT32> MPlaneConnectivityService::getSessionIds()
{
	std::vector<UINT32> sessionIds;
	std::map<std::string, std::map<std::string, std::string>> sessions;

	// Get a list of available open NETCONF sessions
	std::shared_ptr<YangMgrService> yangService(YangMgrService::singleton());
	std::shared_ptr<YangMgrServer> mgr(yangService->getYangMgrServer());
	YangPath pathSession("ietf-netconf-monitoring", "netconf-state");
	pathSession.add("sessions");
	pathSession.add("session");

	// Session ID is the key, so no need to extract the parameter
	sessions = SysrepoUtils::getOperationalKeyValues(mgr, pathSession.pathRootParam(true));
	for (auto & session : sessions)
	{
		sessionIds.push_back((UINT32)std::stoul(session.first));
	}

	return sessionIds;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State MPlaneConnectivityService::addSupervisor(UINT32 id)
{
	std::shared_ptr<Supervisor> supervisor = std::make_shared<Supervisor>(*this, id);
	mSupervisors.push_back(supervisor);

	logDebugNormal("%s: Add Supervisor [id=%d]", getName(), id);

	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State MPlaneConnectivityService::removeSupervisor(UINT32 id)
{
	logDebugNormal("%s: Remove Supervisor [id=%d]", getName(), id);

	ReturnType::State returnValue = ReturnType::RT_ERROR;
	UINT32 numSupervisors = mSupervisors.size();
	// Find and remove connection
	mSupervisors.erase(std::remove_if(mSupervisors.begin(), mSupervisors.end(), [id](auto const & supervisor)
	{
		return (supervisor->id() == id);
	}), mSupervisors.end());

	// Check a supervisor has been removed
	if (mSupervisors.size() == (numSupervisors-1))
	{
		returnValue = ReturnType::RT_OK;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 MPlaneConnectivityService::getMinInterval() const
{
	UINT16 intervalMin = 0xFFFF;

	for (auto supervisor : mSupervisors)
	{
		UINT16 interval = supervisor->getInterval();
		if ((interval > 0) && (interval < intervalMin))
		{
			intervalMin = interval;
		}
	}

	return intervalMin;
}

//-------------------------------------------------------------------------------------------------------------
bool MPlaneConnectivityService::areAllIntervalsSet() const
{
	bool intervalsSet = true;

	for (auto supervisor : mSupervisors)
	{
		if (supervisor->getInterval() == 0)
		{
			intervalsSet = false;
			break;
		}
	}

	return intervalsSet;
}

//-------------------------------------------------------------------------------------------------------------
MPlaneConnectivityService::Supervisor::Supervisor(MPlaneConnectivityService & service, UINT32 id)
	: mService(service)
	, mStateSupervisor(State_T::UNINIT)
	, mId(id)
	, mInterval(0)
	, mGuardTime(0)
	, mWatchdog(std::make_shared<WatchdogCount>())
{
	initialise();
}

//-------------------------------------------------------------------------------------------------------------
MPlaneConnectivityService::Supervisor::~Supervisor()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State MPlaneConnectivityService::Supervisor::configure(UINT16 interval, UINT16 guardTime)
{
	mInterval  = interval;
	mGuardTime = guardTime;

	return ReturnType::State::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State MPlaneConnectivityService::Supervisor::start()
{
	ReturnType::State returnValue = ReturnType::State::RT_ERROR;

	UINT32 monitoringTime = mInterval + mGuardTime;

	if (monitoringTime == 0)
	{
		returnValue = ReturnType::RT_OUT_OF_RANGE;
	}
	else if ((mStateSupervisor == State_T::ON) ||
	         (mStateSupervisor == State_T::OFF) ||
	         (mStateSupervisor == State_T::EXPIRED))
	{
		// Start/Restart watchdog
		returnValue = mWatchdog->start(monitoringTime);

		if (returnValue == ReturnType::State::RT_OK)
		{
			mStateSupervisor = State_T::ON;
		}
		else
		{
			mStateSupervisor = State_T::FAULT;
			mService.logDebugNormal("%s: Watchdog Start Fault [id=%d]", mService.getName(), mId);
		}
	}
	else
	{
		returnValue = ReturnType::RT_NOT_ALLOWED;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State MPlaneConnectivityService::Supervisor::stop()
{
	ReturnType::State returnValue = ReturnType::State::RT_ERROR;

	if (mStateSupervisor == State_T::ON)
	{
		// Stop watchdog
		returnValue = mWatchdog->stop();

		if (returnValue == ReturnType::State::RT_OK)
		{
			mStateSupervisor = State_T::OFF;
		}
		else
		{
			mStateSupervisor = State_T::FAULT;
			mService.logDebugNormal("%s: Watchdog Stop Fault [id=%d]", mService.getName(), mId);
		}
	}
	else
	{
		returnValue = ReturnType::RT_NOT_ALLOWED;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State MPlaneConnectivityService::Supervisor::tick()
{
	ReturnType::State returnValue = ReturnType::State::RT_ERROR;

	// Update watchdog
	if (mWatchdog->isRunning())
	{
		returnValue = mWatchdog->tick();
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
MPlaneConnectivityService::Supervisor::State_T MPlaneConnectivityService::Supervisor::state() const
{
	return mStateSupervisor;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 MPlaneConnectivityService::Supervisor::id() const
{
	return mId;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 MPlaneConnectivityService::Supervisor::getInterval() const
{
	return mInterval;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 MPlaneConnectivityService::Supervisor::getGuard() const
{
	return mGuardTime;
}

bool MPlaneConnectivityService::Supervisor::isSupervisorExpired() const
{
	return (mStateSupervisor == State_T::EXPIRED);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State MPlaneConnectivityService::Supervisor::initialise()
{
	ReturnType::State returnValue = ReturnType::State::RT_ERROR;

	// Initialise, but do not start, the watchdog
	if ((returnValue = mWatchdog->initialise(false)) == ReturnType::State::RT_OK)
	{
		auto watchdogHandler = [this]()->ReturnType::State
		{
			ReturnType::State returnValue = ReturnType::State::RT_ERROR;

			mService.logDebugNormal("%s: Watchdog Expired [id=%d]", mService.getName(), mId);

#if defined (OFF_TARGET)
			stop();
#else
/* ToDo: The does not match the spec, if we have more than one connection.
         We should start recovery without losing other connections */
			// Reboot the system
			std::shared_ptr<ISystemReboot> systemReboot = ISystemReboot::getInstance();
			systemReboot->now();
#endif /* OFF_TARGET_WD_EXPIRE_STOP */

			mStateSupervisor = State_T::EXPIRED;

			returnValue = ReturnType::State::RT_OK;

			return returnValue;
		};
		returnValue = mWatchdog->registerTimeoutHandler(watchdogHandler);
		mStateSupervisor = State_T::OFF;
	}
	else
	{
		mStateSupervisor = State_T::FAULT;
		mService.logDebugNormal("%s: Watchdog Initialise Fault [id=%d]", mService.getName(), mId);
	}

	return returnValue;
}
