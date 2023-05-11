/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IMPlaneConnectivityService.h
 * \brief     ORAN M-Plane Connectivity Service virtual interface
 *
 *
 * \details   Virtual interface for NETCONF Connectivity supervision Service.
 *
 */

#ifndef _VYMS_INC_IMPLANE_CONNECTIVITY_SERVICE_H_
#define _VYMS_INC_IMPLANE_CONNECTIVITY_SERVICE_H_

#include <memory>
#include <utility>
#include <cstdint>
#include <functional>
#include <vector>
#include <set>

#include "GlobalTypeDefs.h"

namespace Mplane
{

class IMPlaneConnectivityService
{
public:
 IMPlaneConnectivityService() {}
 virtual ~IMPlaneConnectivityService() {}

 typedef enum {
   UNINIT, // Uninitialised
   RUNNING, // Service running with notifications
   PAUSED, // Service running without notifications
   FAULT, // A fault has occurred
 } ServiceState_T;

 /*
  * Create singleton interface
  */
 static std::shared_ptr<IMPlaneConnectivityService> singleton(void);

 /**
  *
  * Callback function for when the notification timer expires
  */
 using NotifTimerExpiredNotifyFunc = std::function<void()>;

 /*
  * Returns the current service state
  */
 virtual ServiceState_T getState() const = 0;

 /*
  * Get current notification timer value
  */
 virtual UINT16 getTimer() const = 0;

 /*
  * Set default notification interval
  */
 virtual ReturnType::State setInterval(UINT16 interval) = 0;

 /*
  * Get current notification interval
  */
 virtual UINT16 getInterval() const = 0;

 /*
  * Get specified notification interval
  */
 virtual UINT16 getInterval(UINT32 sessionId) const = 0;

 /*
  * Get specified supervision guard time
  */
 virtual UINT16 getGuard(UINT32 sessionId) const = 0;

 /*
  * Get specified supervision monitoring time
  */
 virtual UINT32 getMonitoring(UINT32 sessionId) const = 0;

 /*
  * Has an M-Plane supervisor expired?
  */
 virtual bool isSupervisorExpired(UINT32 sessionId) const = 0;

 /*
  * Resets M-Plane connectivity service
  */
 virtual ReturnType::State kick(
     UINT32 sessionId,
     UINT16 interval,
     UINT16 guard,
     std::string& nextUpdateAt) = 0;

 /**
  * Register a callback for when the notification timer expires
  */
 virtual void registerNotifTimerExpired(NotifTimerExpiredNotifyFunc func) = 0;

protected:

private:
 /*
  * Add an M-Plane supervisor
  */
 virtual ReturnType::State addSupervisor(UINT32 id) = 0;

 /*
  * Remove an M-Plane supervisor
  */
 virtual ReturnType::State removeSupervisor(UINT32 id) = 0;
};

}

#endif /* _VYMS_INC_IMPLANE_CONNECTIVITY_SERVICE_H_ */
