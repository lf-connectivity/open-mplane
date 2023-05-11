/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HandlerCallback.h
 * \brief     Value change callback for YangHandlerSysrepo
 *
 *
 * \details   Value change callback for YangHandlerSysrepo
 *
 */


#ifndef YANG_SYSREPO_INC_YANGHANDLERSYSREPO_HANDLERCALLBACK_H_
#define YANG_SYSREPO_INC_YANGHANDLERSYSREPO_HANDLERCALLBACK_H_

#include <functional>
#include <string>
#include <memory>
#include <cstdint>

#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Sysrepo.hpp>


namespace Mplane {

class YangHandlerSysrepoUnlogged ;

/*!
 * \class  HandlerCallback
 * \brief
 * \details
 *
 */
class HandlerCallback : public sysrepo::Callback {
public:
 using GetPathsFunc = std::function<std::set<std::string>()>;
 using SetValFunc = std::function<void(std::shared_ptr<sysrepo::Val>)>;
 using ChangeCompleteFunc = std::function<void()>;

 HandlerCallback(
     YangHandlerSysrepoUnlogged* parent,
     GetPathsFunc roFunc,
     SetValFunc setValFunc,
     ChangeCompleteFunc completeFunc);
 virtual ~HandlerCallback();

 //----------------------------------------------------------------------------------------------------------
 /**
  * sysrepo module change callback
  */
 virtual int module_change(
     sysrepo::S_Session sess,
     const char* module_name,
     const char* xpath,
     sr_event_t event,
     uint32_t request_id,
     void* private_data) override;

private:
 // Check for pseudo read-only
 int checkPseudoReadOnly(
     sysrepo::S_Session sess,
     const char* module_name,
     const std::string& xpathString);

 // Handle the change event - validate changes
 int handleChangeEvent(
     sysrepo::S_Session sess,
     const char* module_name,
     const std::string& xpathString);

 // handle the done event
 int handleDoneEvent(
     sysrepo::S_Session sess,
     const char* module_name,
     const std::string& xpathString);

private:
 YangHandlerSysrepoUnlogged* mParent;
 GetPathsFunc mRoPathsFunc;
 SetValFunc mSetValFunc;
 ChangeCompleteFunc mChangeCompleteFunc;
};

}

#endif /* YANG_SYSREPO_INC_YANGHANDLERSYSREPO_HANDLERCALLBACK_H_ */
