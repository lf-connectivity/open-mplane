/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ConfigDownloadManagement.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <vector>

#include "ConfigDownloadManagement.h"
#include "stringfunc.hpp"

#include "ConfigDownload.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Set the priority of the task to 1 above lowest
static constexpr int MANAGER_PRIORITY = Task::PRIORITY_MIN + 1;

// tick time in ms
static const unsigned TASK_TICK_MS = 500;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ConfigDownloadManagement::ConfigDownloadManagement()
    : Task(
          MANAGER_PRIORITY,
          Task::MEDIUM_STACK,
          "Config Download Mgr",
          "CONFIG"),

      mTaskRunning(true),
      mServerUrl(""),
      mInjectedInstallDir(""),
      mMutex(),
      mIsDownloading(false),
      mTypeDownloading(),
      mFileName(""),
      mCondEnd(std::shared_ptr<Conditional>()),
      mDownload(std::shared_ptr<IConfigDownload>()),
      mDownloadOk(true),
      mDownloadFailReason(""),
      mStatusObject(IFileStatus::nullObject()),
      mDownloadDoneCallback(),

      mCondStart() {}

//-------------------------------------------------------------------------------------------------------------
ConfigDownloadManagement::~ConfigDownloadManagement() { shutdown(); }

//-------------------------------------------------------------------------------------------------------------
void
ConfigDownloadManagement::shutdown(void) {
  mTaskRunning = false;
  msSleep(2 * TASK_TICK_MS);
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::getAndInstall(
    const std::string& typeName,
    const std::string& _fileName,
    std::shared_ptr<IFileStatus> status,
    std::string& failReason,
    std::shared_ptr<Conditional> endSignal) {
  if (_fileName.empty()) {
    failReason = "Filename not set";
    return false;
  }

  // If image name contains a url, then set url
  std::string fileName(_fileName);
  std::size_t pos(fileName.find_last_of('/'));
  if (pos != std::string::npos) {
    if (!setRemoteUrl(fileName.substr(0, pos), failReason))
      return false;

    fileName = fileName.substr(pos + 1);
  }

  Mutex::Lock lock(mMutex);

  // check settings
  if (mServerUrl.empty()) {
    failReason = "Remote URL not set";
    return false;
  }

  // Get state and mark as downloading if idle
  if (mIsDownloading) {
    failReason =
        "Cannot start a new download until existing download completes";
    return false;
  }

  auto configDownload(getConfigDownload(typeName));
  if (!configDownload) {
    failReason = "Config type " + typeName + " not installed";
    return false;
  }

  mTypeDownloading = typeName;
  mIsDownloading = true;

  // Grab settings for download task
  mFileName = fileName;
  mCondEnd = endSignal;
  mDownloadOk = true;
  mDownloadFailReason.clear();
  mDownload = configDownload;
  mDownloadDoneCallback = std::function<void(void)>();

  // Set up the status reporting object
  setStatusObject(status);
  status->restart(1);

  // Initiate download
  Conditional::Lock condLock(mCondStart);
  mCondStart.signal();

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::getAndInstall(
    const std::string& typeName,
    std::shared_ptr<IFileStatus> status,
    std::string& failReason,
    std::shared_ptr<Conditional> endSignal) {
  return getAndInstall(
      typeName, getInstallFileName(typeName), status, failReason, endSignal);
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::getAndInstall(
    const std::string& typeName,
    const std::string& fileName,
    std::string& failReason,
    std::shared_ptr<Conditional> endSignal) {
  return getAndInstall(
      typeName, fileName, IFileStatus::nullObject(), failReason, endSignal);
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::getAndInstall(
    const std::string& typeName,
    std::string& failReason,
    std::shared_ptr<Conditional> endSignal) {
  return getAndInstall(
      typeName,
      getInstallFileName(typeName),
      IFileStatus::nullObject(),
      failReason,
      endSignal);
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::getAndInstall(
    const std::string& typeName,
    const std::string& fileName,
    std::shared_ptr<IFileStatus> status,
    std::string& failReason) {
  // Create Conditional
  std::shared_ptr<Conditional> endSignal(new Conditional);

  // run download
  if (!getAndInstall(typeName, fileName, status, failReason, endSignal))
    return false;

  // Wait for completion
  endSignal->wait();

  // Check for error
  return isDownloadOk(failReason);
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::getAndInstall(
    const std::string& typeName,
    std::shared_ptr<IFileStatus> status,
    std::string& failReason) {
  // Create Conditional
  std::shared_ptr<Conditional> endSignal(new Conditional);

  // run download
  if (!getAndInstall(
          typeName,
          getInstallFileName(typeName),
          status,
          failReason,
          endSignal))
    return false;

  // Wait for completion
  endSignal->wait();

  // Check for error
  return isDownloadOk(failReason);
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::getAndInstall(
    const std::string& typeName,
    const std::string& fileName,
    std::string& failReason) {
  // Create Conditional
  std::shared_ptr<Conditional> endSignal(new Conditional);

  // run download
  if (!getAndInstall(
          typeName, fileName, IFileStatus::nullObject(), failReason, endSignal))
    return false;

  // Wait for completion
  endSignal->wait();

  // Check for error
  return isDownloadOk(failReason);
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::getAndInstall(
    const std::string& typeName, std::string& failReason) {
  // Create Conditional
  std::shared_ptr<Conditional> endSignal(new Conditional);

  // run download
  if (!getAndInstall(
          typeName,
          getInstallFileName(typeName),
          IFileStatus::nullObject(),
          failReason,
          endSignal))
    return false;

  // Wait for completion
  endSignal->wait();

  // Check for error
  return isDownloadOk(failReason);
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::isDownloading(void) const {
  Mutex::Lock lock(mMutex);
  return mIsDownloading;
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::isDownloadOk(std::string& failReason) const {
  Mutex::Lock lock(mMutex);
  if (!mDownloadOk)
    failReason.assign(mDownloadFailReason);
  return mDownloadOk;
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::setRemoteUrl(
    const std::string& url, std::string& failReason) {
  Mutex::Lock lock(mMutex);
  if (mIsDownloading) {
    failReason = "Unable to change server url while download is in progress";
    return false;
  }

  return setRemoteUrlNoMutex(url, failReason);
}

//-------------------------------------------------------------------------------------------------------------
std::string
ConfigDownloadManagement::getRemoteUrl() {
  return mServerUrl;
}

//-------------------------------------------------------------------------------------------------------------
void
ConfigDownloadManagement::showDetail(std::ostream& os) const {}

//-------------------------------------------------------------------------------------------------------------
void
ConfigDownloadManagement::show(std::ostream& os) const {
  for (auto cs : mConfigDownloadMap) {
    cs.second->show(os);
  }
}

//-------------------------------------------------------------------------------------------------------------
void
ConfigDownloadManagement::show(
    const std::string& typeName, std::ostream& os) const {
  auto configDownload(getConfigDownload(typeName));
  if (!configDownload)
    return;
  configDownload->show(os);
}

//-------------------------------------------------------------------------------------------------------------
std::string
ConfigDownloadManagement::getInstallFileName(
    const std::string& typeName) const {
  auto configDownload(getConfigDownload(typeName));
  if (!configDownload)
    return "";
  return configDownload->getInstallFileName();
}

//-------------------------------------------------------------------------------------------------------------
std::string
ConfigDownloadManagement::getInstallFilePath(
    const std::string& typeName) const {
  auto configDownload(getConfigDownload(typeName));
  if (!configDownload)
    return "";
  return configDownload->getInstallFilePath();
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::testInjectInstallDir(
    const std::string& path, std::string& failReason) {
  Mutex::Lock lock(mMutex);
  mInjectedInstallDir = path;
  for (auto& cs : mConfigDownloadMap) {
    if (!cs.second->testInjectInstallDir(path, failReason))
      return false;
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::addConfigDownloadType(
    std::shared_ptr<IConfigDownload> configDownLoad) {
  Mutex::Lock lock(mMutex);
  mConfigDownloadMap[toUpper(configDownLoad->getName())] = configDownLoad;
  std::string failReason;
  bool ok;
  ok = configDownLoad->initialise(failReason);

  if (!mInjectedInstallDir.empty())
    if (!configDownLoad->testInjectInstallDir(mInjectedInstallDir, failReason))
      return false;

  return ok;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<IConfigDownload>>
ConfigDownloadManagement::getConfigDowloadObjects() {
  std::vector<std::shared_ptr<IConfigDownload>> configDownloads;
  configDownloads.reserve(mConfigDownloadMap.size());

  for (auto configDownload : mConfigDownloadMap) {
    configDownloads.push_back(configDownload.second);
  }

  return configDownloads;
}

//-------------------------------------------------------------------------------------------------------------
std::set<std::string>
ConfigDownloadManagement::getTypes() const {
  std::set<std::string> types;

  for (auto configDownload : mConfigDownloadMap) {
    types.insert(configDownload.second->getTypeName());
  }
  return types;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgrWriter>
ConfigDownloadManagement::getConfigFileWriter(
    const std::string& typeName,
    std::shared_ptr<IFileStatus> statusObj,
    unsigned fileSize,
    std::string& failReason) {
  auto iconfigDownload(getConfigDownload(typeName));
  if (!iconfigDownload) {
    failReason = "Invalid type";
    return std::shared_ptr<IFileMgrWriter>();
  }

  std::shared_ptr<ConfigDownload> configDownload(
      std::dynamic_pointer_cast<ConfigDownload>(iconfigDownload));
  return configDownload->getConfigFileWriter(statusObj, fileSize, failReason);
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::configInstall(
    const std::string& typeName,
    std::shared_ptr<IFileStatus> status,
    ImageConfigWrite configWriteFunc,
    ImageConfigComplete configCompleteFunc,
    std::string& failReason) {
  Mutex::Lock lock(mMutex);

  // Get state and mark as downloading if idle
  if (mIsDownloading) {
    failReason =
        "Cannot start a new download until existing download completes";
    return false;
  }

  if (!configWriteFunc) {
    failReason = "Internal error";
    return false;
  }

  // Ensure that the url is set - if we set a dummy, clean up afterwards
  bool cleanUrl(false);
  if (mServerUrl.empty()) {
    if (!setRemoteUrlNoMutex("tcp-download", failReason))
      return false;
    cleanUrl = true;
  }

  auto configDownload(getConfigDownload(typeName));
  if (!configDownload) {
    failReason = "Config type " + typeName + " not installed";
    return false;
  }

  mTypeDownloading = typeName;
  mIsDownloading = true;

  // Grab settings for download task
  mFileName = "dummy.xml";
  mDownloadOk = true;
  mDownloadFailReason.clear();
  mDownload = configDownload;
  mStatusObject = status;

  // Tell config to use TCP to transfer data
  mDownloadDoneCallback = [this, configCompleteFunc, cleanUrl](void) {
    // Tell config to stop TCP transfer
    mDownload->endTcpTransfer();

    // Clean up url if required
    std::string dummy;
    if (cleanUrl)
      setRemoteUrlNoMutex("", dummy);

    // Configl callback
    if (configCompleteFunc)
      configCompleteFunc();
  };

  // Tell config object to use TCP to transfer data
  mDownload->startTcpTransfer(configWriteFunc);

  // Set up the status reporting object
  setStatusObject(status);
  status->restart(1);

  // Initiate download
  Conditional::Lock condLock(mCondStart);
  mCondStart.signal();

  return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int
ConfigDownloadManagement::run() {
  /*
   * Now our thread is running we just enter an infinite loop so we never end.
   * ALl image management is triggered by invocation of class methods, which are
   * explicit action requests.
   */
  while (mTaskRunning) {
    // keep this task alive
    kickSoftwareWatchdog();

    // Wait for timeout or start of download
    if (mCondStart.wait(TASK_TICK_MS) == true) {
      logDebugNormal(
          "ConfigDownloadManagement - start download : Type=%s",
          mTypeDownloading.c_str());

      // run download
      mDownloadOk = mDownload->getAndInstall(
          mFileName, mStatusObject, mDownloadFailReason);

      // Finish with status
      if (mDownloadOk)
        mStatusObject->success();
      else
        mStatusObject->fail(mDownloadFailReason);

      // run the callback if set
      if (mDownloadDoneCallback)
        mDownloadDoneCallback();

      // tidy up
      setStatusObject(IFileStatus::nullObject());

      // Signal end
      if (mCondEnd.get()) {
        Conditional::Lock lock(*mCondEnd);
        mCondEnd->signal();
      }

      // Switch back to idle state
      setState(false, "");

      logDebugNormal(
          "ConfigDownloadManagement - download complete ok=%d (%s)",
          mDownloadOk,
          mDownloadFailReason.c_str());
    }
  }

  return 0;
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::getState(std::string& typeName) const {
  Mutex::Lock lock(mMutex);
  typeName = mTypeDownloading;
  return mIsDownloading;
}

//-------------------------------------------------------------------------------------------------------------
void
ConfigDownloadManagement::setState(
    bool downloading, const std::string& typeName) {
  Mutex::Lock lock(mMutex);
  mTypeDownloading = typeName;
  mIsDownloading = downloading;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IConfigDownload>
ConfigDownloadManagement::getConfigDownload(const std::string& typeName) const {
  // IConfigDownload name suffix - can be stripped off
  static const std::string CONFIG_SUFFIX_UC{
      toUpper(ConfigDownload::CONFIG_TYPE_SUFFIX)};

  std::string ucTypeName(toUpper(typeName));

  // See if uppercase version of the specified type is in the map
  auto cd(mConfigDownloadMap.find(ucTypeName));
  if (cd != mConfigDownloadMap.end())
    return mConfigDownloadMap.at(ucTypeName);

  // Not present so attempt to find <name>Download
  ucTypeName += CONFIG_SUFFIX_UC;
  cd = mConfigDownloadMap.find(ucTypeName);
  if (cd != mConfigDownloadMap.end())
    return mConfigDownloadMap.at(ucTypeName);

  return std::shared_ptr<IConfigDownload>();
}

//-------------------------------------------------------------------------------------------------------------
bool
ConfigDownloadManagement::setRemoteUrlNoMutex(
    const std::string& url, std::string& failReason) {
  mServerUrl = url;
  for (auto& cs : mConfigDownloadMap) {
    cs.second->setRemoteUrl(url, failReason);
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
void
Mplane::ConfigDownloadManagement::setStatusObject(
    std::shared_ptr<IFileStatus> status) {
  mStatusObject = status;
  for (auto& cs : mConfigDownloadMap) {
    cs.second->setStatusObject(status);
  }
}
