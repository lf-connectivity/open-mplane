/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangUserAuth.h
 * \brief     Collection of methods for SSH user authentication
 *
 *
 * \details   Methods that can retrieve the appropriate parameters to create an SSH session
 *
 */


#ifndef YANG_SYSREPO_INC_YANGUSERAUTH_H_
#define YANG_SYSREPO_INC_YANGUSERAUTH_H_

#include <vector>
#include <memory>
#include <string>

#include "ISshSession.h"
#include "ISftpMgr.h"

#include "YangParam.h"

namespace Mplane {

/*!
 * \class  YangUserAuth
 * \brief
 * \details
 *
 */
class YangUserAuth {
public:
 /**
  * Convert string into an SSH key type
  */
 static ssh_keytypes_e strToKeytype(const std::string& typeStr);

 /**
  * Given a set of YangParams, pulls out the common parameters used in multiple
  * rpcs that specify the authentication arguments for authenticating the user
  * and server
  *
  */
 static bool authParams(
     std::shared_ptr<YangParams> callList,
     std::string& authData,
     ISftpMgr::AuthenticationType& authType,
     std::vector<ISshSession::PublicKey>& serverKeys);
} ;

}

#endif /* YANG_SYSREPO_INC_YANGUSERAUTH_H_ */
