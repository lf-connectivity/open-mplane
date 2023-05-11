/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonConfigBase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "CommonConfigBase.h"
#include "GlobalTypeDefs.h"

using namespace Mplane;

Mplane::CommonConfigBase::CommonConfigBase(
    const char* objectName, const char* subUnitId)
    : Loggable(objectName, subUnitId),
      mVersion(-1),
      mInfo(""),
      mIsLoaded(false),
      mConfigDownload() {}

std::string
Mplane::CommonConfigBase::getInfo() {
  return mInfo;
}

int
Mplane::CommonConfigBase::getVersion() {
  return mVersion;
}

bool
Mplane::CommonConfigBase::isLoaded() {
  return mIsLoaded;
}

Mplane::CommonConfigBase::~CommonConfigBase() {}

void
Mplane::CommonConfigBase::setLoaded(bool loaded) {
  mIsLoaded = loaded;
}

void
Mplane::CommonConfigBase::setInfo(const std::string& info) {
  mInfo = info;
}

void
Mplane::CommonConfigBase::setVersion(int version) {
  mVersion = version;
}

void
Mplane::CommonConfigBase::setPath(std::shared_ptr<IConfigDownload> download) {
  mConfigDownload = download;
}

std::string
Mplane::CommonConfigBase::getPath() {
  return mConfigDownload->getInstallFilePath();
}
