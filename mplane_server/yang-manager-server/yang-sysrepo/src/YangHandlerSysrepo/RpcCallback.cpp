/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RpcCallback.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangHandlerSysrepo/RpcCallback.h"
#include "SysrepoUtils.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RpcCallback::RpcCallback(const std::string& rpcXpath, RpcFunc func)
    : mXpath(rpcXpath), mFunc(func) {}

//-------------------------------------------------------------------------------------------------------------
RpcCallback::~RpcCallback() {}

//-------------------------------------------------------------------------------------------------------------
int
RpcCallback::rpc(
    sysrepo::S_Session session,
    const char* op_path,
    const sysrepo::S_Vals input,
    sr_event_t event,
    uint32_t request_id,
    sysrepo::S_Vals_Holder output,
    void* private_data) {
  // convert input args
  std::shared_ptr<YangParams> callList(SysrepoUtils::valsToParams(input));
  std::shared_ptr<YangParams> retList(std::make_shared<YangParams>());

  // call rpc func
  if (!mFunc(session, mXpath, callList, retList))
    return -1;

  // Convert return params
  SysrepoUtils::paramsToValsHolder(retList, output);

  return 0;
}
