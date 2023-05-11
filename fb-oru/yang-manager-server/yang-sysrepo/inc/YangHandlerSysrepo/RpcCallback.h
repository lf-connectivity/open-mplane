/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RpcCallback.h
 * \brief     RPC callback for YangHandlerSysrepo
 *
 *
 * \details   RPC callback for YangHandlerSysrepo
 *
 */


#ifndef YANG_SYSREPO_INC_YANGHANDLERSYSREPO_RPCCALLBACK_H_
#define YANG_SYSREPO_INC_YANGHANDLERSYSREPO_RPCCALLBACK_H_

#include <functional>
#include <string>
#include <memory>
#include <cstdint>

#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Sysrepo.hpp>

#include "YangParam.h"

namespace Mplane {

/*!
 * \class  RpcCallback
 * \brief
 * \details
 *
 */
class RpcCallback : public sysrepo::Callback {
public:
	/**
	 * RPC callback
	 *
	 * rpcXpath	- Full xpath to rpc
	 * callList - list of input parameters
	 * retList - List of output parameters
	 *
	 * returns TRUE if rpc call was successful
	 */
	using RpcFunc = std::function<bool(std::shared_ptr<sysrepo::Session> session,
			const std::string& rpcXpath,
			std::shared_ptr<YangParams> callList,
			std::shared_ptr<YangParams> retList)> ;



	RpcCallback(const std::string& rpcXpath, RpcFunc func) ;
	virtual ~RpcCallback() ;

	/**
	 * Sysrepo rpc callback
	 */
    int rpc(sysrepo::S_Session session, const char *op_path, const sysrepo::S_Vals input, sr_event_t event, uint32_t request_id,
                sysrepo::S_Vals_Holder output, void *private_data) override ;

private:
    std::string mXpath ;
    RpcFunc mFunc ;
} ;

}

#endif /* YANG_SYSREPO_INC_YANGHANDLERSYSREPO_RPCCALLBACK_H_ */
