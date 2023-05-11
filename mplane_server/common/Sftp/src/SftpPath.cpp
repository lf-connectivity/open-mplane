/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SftpPath.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SftpPath.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::string PATH_ERROR(
    "Invalid remote file path. Expected "
    "'sftp://<username>@<host>[:port]/path'");

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SftpPath::SftpPath(const std::string& remotePath)
    : mValid(false), mUser(""), mHost(""), mPath(""), mPort(0), mError("") {
  // Looking for:
  // sftp://<username>@<host>[:port]/path
  std::size_t spos(remotePath.find("://"));
  if (spos == std::string::npos) {
    spos = 0;
  } else {
    // check for sftp://
    if (remotePath.substr(0, spos) != "sftp") {
      mError = "Unsupported scheme";
      return;
    }
    spos += 3;
  }

  // find user@host
  std::size_t atpos(remotePath.find("@", spos));
  if (atpos == std::string::npos) {
    mError = PATH_ERROR;
    return;
  }
  mUser = remotePath.substr(spos, atpos - spos);

  // Look for optional port
  std::size_t portPos(remotePath.find(":", atpos));

  // find start of path
  std::size_t pathPos(remotePath.find("/", atpos));
  if (pathPos == std::string::npos) {
    mError = PATH_ERROR;
    return;
  }
  mPath = remotePath.substr(pathPos + 1);

  // handle port and host
  if (portPos != std::string::npos) {
    mHost = remotePath.substr(atpos + 1, portPos - atpos - 1);
    std::string portStr(remotePath.substr(portPos + 1, pathPos - portPos - 1));
    try {
      mPort = stoi(portStr);
    } catch (...) {
    }
  } else {
    mHost = remotePath.substr(atpos + 1, pathPos - atpos - 1);
  }

  if (mUser.empty() || mHost.empty() || mPath.empty()) {
    mError = PATH_ERROR;
    return;
  }

  if (mUser.find_first_of(":/@") != std::string::npos) {
    mError = "Invalid user name";
    return;
  }
  if (mHost.find_first_of(":/@") != std::string::npos) {
    mError = "Invalid host name";
    return;
  }
  if (mPath.find_first_of(":@") != std::string::npos) {
    mError = "Invalid path";
    return;
  }

  mValid = true;
}

//-------------------------------------------------------------------------------------------------------------
SftpPath::~SftpPath() {}

//-------------------------------------------------------------------------------------------------------------
bool
SftpPath::isValid() const {
  return mValid;
}

//-------------------------------------------------------------------------------------------------------------
std::string
SftpPath::error() const {
  return mError;
}

//-------------------------------------------------------------------------------------------------------------
std::string
SftpPath::user() const {
  return mUser;
}

//-------------------------------------------------------------------------------------------------------------
std::string
SftpPath::host() const {
  return mHost;
}

//-------------------------------------------------------------------------------------------------------------
std::string
SftpPath::path() const {
  return mPath;
}

//-------------------------------------------------------------------------------------------------------------
unsigned
SftpPath::port() const {
  return mPort;
}
