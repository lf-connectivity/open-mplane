/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      INetopeerMonService.cpp
 * \brief     Netopeer Monitoring service
 *
 *
 * \details   Responsible for monitoring the Netopeer application .
 *
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "IAppOptions.h"

#include "NetopeerMonService.h"

#ifdef OFF_TARGET
#define DISABLE_NETOPEER_MONITORING
#endif

using namespace Mplane;

#define NETOPEER_CMD "netopeer2-server"

const std::string mSysrepoPath = "/dev/shm";

const std::string NetopeerMonService::mServiceStatusStoppedStr = "Stopped";
const std::string NetopeerMonService::mServiceStatusRunningStr = "Running";
const std::string NetopeerMonService::mServiceStatusFailedStr = "Failed";

const std::string NetopeerMonService::mEnabledStr = "Enabled";
const std::string NetopeerMonService::mDisabledStr = "Disabled";

const std::chrono::duration<int> NetopeerMonService::mKillNetopeerServerTime =
    std::chrono::seconds(5);

std::string NetopeerMonService::mNetopeerCommandStr;

// =============================================================================
Mplane::NetopeerMonService::NetopeerMonService()
    : Service(
          SERVICE_LOW_PRIORITY,
          SMALL_STACK,
          1000, // update stuff every 1000 msec
          "NetopeerMonService",
          "NETOPEER"),
      mServiceState(INetopeerMonService::serviceStatus_T::STOPPED),
      mMonitorServiceState(INetopeerMonService::enableDisable_T::ENABLE),
      mAutoRestartProcess(INetopeerMonService::enableDisable_T::DISABLE),
      mFailedCount(0),
      mReportOnlyOnce(false) {
  std::string appPath(
      IAppOptions::getInstance()->getOption("netopeer-path").toString());
  if (appPath.empty()) {
    throw std::runtime_error("The app option 'netopeer-path' must be set.");
  }

  mNetopeerCommandStr = appPath + "/" NETOPEER_CMD;
}

// =============================================================================
Mplane::NetopeerMonService::~NetopeerMonService() {}

// =============================================================================
ReturnType::State
Mplane::NetopeerMonService::startService(void) {
  ReturnType::State returnValue = ReturnType::RT_ERROR;

  if (mServiceState == serviceStatus_T::RUNNING) {
    // If we are already running
    returnValue = ReturnType::RT_OK;
  } else {
    if (spawnNetopeerServer() == ReturnType::RT_OK) {
      mServiceState = serviceStatus_T::RUNNING;
      returnValue = ReturnType::RT_OK;
    } else {
      mServiceState = serviceStatus_T::FAILED;
      eventError("NetopeerMonService::startService() - start process failed!");
    }
  }

  return returnValue;
}

// =============================================================================
ReturnType::State
Mplane::NetopeerMonService::restartService(void) {
  ReturnType::State stopReturn = stopService();

  if (stopReturn == ReturnType::RT_OK) {
    ReturnType::State startReturn = startService();

    if (startReturn == ReturnType::RT_OK) {
      return ReturnType::RT_OK;
    } else {
      eventError(
          "NetopeerMonService::restartService() - failed to start process");
    }
  } else {
    eventError("NetopeerMonService::restartService() - failed to stop process");
  }
  return ReturnType::RT_ERROR;
}

// =============================================================================
ReturnType::State
Mplane::NetopeerMonService::stopService(void) {
  ReturnType::State returnValue = ReturnType::RT_OK;

  if (mServiceState == serviceStatus_T::STOPPED) {
    returnValue = ReturnType::RT_OK;
  } else {
    mNetopeerProcess.terminate();
    if (mNetopeerProcess.wait_for(mKillNetopeerServerTime)) {
      mServiceState = serviceStatus_T::STOPPED;
      clearSysrepo();
    } else {
      returnValue = ReturnType::RT_ERROR;
      mServiceState = serviceStatus_T::FAILED;
    }
  }
  return returnValue;
}

// =============================================================================
INetopeerMonService::serviceStatus_T
Mplane::NetopeerMonService::getServiceStatus(void) {
  return mServiceState;
}

// =============================================================================
std::string
Mplane::NetopeerMonService::getServiceStatusString(void) {
  std::string state;

  switch (mServiceState) {
    case STOPPED:
      state = mServiceStatusStoppedStr;
      break;
    case RUNNING:
      state = mServiceStatusRunningStr;
      break;
    case FAILED:
      state = mServiceStatusFailedStr;
      break;
    default:
      state = mServiceStatusFailedStr;
      break;
  }
  return state;
}

// =============================================================================
void
Mplane::NetopeerMonService::setMonitorServiceState(
    enableDisable_T enableDisableMonitor) {
  mMonitorServiceState = enableDisableMonitor;
}

// =============================================================================
INetopeerMonService::enableDisable_T
Mplane::NetopeerMonService::getMonitorServiceState(void) {
  return mMonitorServiceState;
}

// =============================================================================
std::string
Mplane::NetopeerMonService::getMonitorServiceStateString(void) {
  return (
      mMonitorServiceState == enableDisable_T::ENABLE ? mEnabledStr
                                                      : mDisabledStr);
}

// =============================================================================
Mplane::NetopeerMonService::CtlState
Mplane::NetopeerMonService::shutdown() {
#ifdef DEBUG_SERVICE
  std::cerr << "Service[" << getName()
            << "] shutdown() mState=" << getStateName(mState)
            << " mControl=" << getControlName(mControl)
            << " Task.isRunning=" << isRunning() << std::endl;
#endif
  // If Task isn't running then we've stopped
  if (!isRunning()) {
    mState = ServiceShutdown;
    return Shutdown;
  }

  stopService();

  // Task running so it's safe to signal to the Sevice thread
  Conditional::Lock lock(mNotify);
  if (mState == ServiceRunning) {
    mControl = Shutdown;
    mNotify.signal();
    return Shutdown;
  }
  return Noop;
}

// =============================================================================
void
Mplane::NetopeerMonService::show() {
  eventInfo("NetopeerMonService::show()");
}

// =============================================================================
int
Mplane::NetopeerMonService::service() {
  Mutex::Lock lock(mMutex); // Protect from the Test Interface

#ifndef DISABLE_NETOPEER_MONITORING
  if (mMonitorServiceState == enableDisable_T::ENABLE) {

    if (mNetopeerProcess.running()) {
      mServiceState = serviceStatus_T::RUNNING;
    } else {
      if (mAutoRestartProcess == enableDisable_T::ENABLE) {
        // netopeer2 stopped, removing possible corrupted sysrepo files from
        // shared memory
        clearSysrepo();

        eventError(
            "NetopeerMonService::service() - netopeer2 is not running, "
            "attempting to restart.");

        // Increment the failed counter
        mFailedCount++;

        if (spawnNetopeerServer() == ReturnType::RT_OK) {
          mServiceState = serviceStatus_T::RUNNING;
        } else {
          mServiceState = serviceStatus_T::FAILED;
          eventError(
              "NetopeerMonService::startService() - start process failed!");
        }
      }
    }
  } else // mMonitorServiceState != enableDisable_T::ENABLE
  {
    if (mReportOnlyOnce == false) {
      eventError(
          "NetopeerMonService::service() - Netopeer2 not running. Auto restart "
          "disabled.");
      mReportOnlyOnce = true;
    }
    mServiceState = serviceStatus_T::FAILED;
  }
#endif // DISABLE_NETOPEER_MONITORING
  return 0;
}

// =============================================================================
// Warning! This function won't do anything as the base class function has not
// been overridden
void
Mplane::NetopeerMonService::doReset() {}

// =============================================================================
ReturnType::State
Mplane::NetopeerMonService::spawnNetopeerServer(void) {
  ReturnType::State returnValue = ReturnType::RT_ERROR;

  DataVariant netopeerDbgOption(
      IAppOptions::getInstance()->getOption("netopeerdbg"));
  std::string netopeerDbgOptionStr = netopeerDbgOption.toString();
  netopeerDbgOption.setLimits("0", "2", "1");
  if (netopeerDbgOption.checkLimits()) {
    // Remove leading zeros, unless 0
    UINT32 value = std::stoul(netopeerDbgOptionStr);
    netopeerDbgOptionStr = std::to_string(value);
  } else {
    // DEFAULT
    netopeerDbgOptionStr = "1";
  }
  std::string netopeerCmdFullStr =
      mNetopeerCommandStr + " -d -v " + netopeerDbgOptionStr;

  mNetopeerProcess = bp::child(netopeerCmdFullStr.c_str());

  // hack: wait a bit for netopeer2-server, it will exit if there is another
  // instance running already
  usleep(1000 * 1000);

  if (mNetopeerProcess.running()) {
    returnValue = ReturnType::RT_OK;
  } else {
    returnValue = ReturnType::RT_ERROR;
  }

  return returnValue;
}

void
Mplane::NetopeerMonService::clearSysrepo(void) {
  eventInfo(
      "NetopeerMonService::service() - Removing sysrepo files from shared "
      "memory folder");
  bp::system("rm -rf " + mSysrepoPath + "/sr_*"); // XXX: rm util is
                                                  // system-specific
  bp::system("rm -rf " + mSysrepoPath + "/srsub_*"); // XXX: rm util is
                                                     // system-specific
}

// =============================================================================
void
Mplane::NetopeerMonService::setAutoRestart(
    enableDisable_T enableDisableAutoRestart) {
  mAutoRestartProcess = enableDisableAutoRestart;
}

// =============================================================================
INetopeerMonService::enableDisable_T
Mplane::NetopeerMonService::getAutoRestart(void) {
  return mAutoRestartProcess;
}

// =============================================================================
std::string
Mplane::NetopeerMonService::getAutoRestartString(void) {
  return (
      mAutoRestartProcess == enableDisable_T::ENABLE ? mEnabledStr
                                                     : mDisabledStr);
}

// =============================================================================
UINT32
Mplane::NetopeerMonService::getAppFailedCount(void) { return mFailedCount; }

// =============================================================================
void
Mplane::NetopeerMonService::clrAppFailedCount(void) {
  mFailedCount = 0;
}
