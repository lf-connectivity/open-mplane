/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IetfNetconfServerHandler.h
 * \brief     IETF NETCONF Server configuration module handler
 *
 *
 * \details   IETF NETCONF Server configuration module handler
 *
 */

#ifndef INC_IETFNETCONFSERVER_HANDLER_H_
#define INC_IETFNETCONFSERVER_HANDLER_H_

#include <string>
#include <memory>

#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  IetfNetconfServerHandler
 * \brief
 * \details
 *
 */
class IetfNetconfServerHandler : public YangHandlerSysrepo
{
public:
 IetfNetconfServerHandler(std::shared_ptr<IYangModuleMgr> moduleMgr);
 virtual ~IetfNetconfServerHandler();

 /*
  * Run the initialisation of the handler (can only be done once the rest of the
  * YANG framework is up)
  */
 virtual bool initialise() override;

protected:
 /*!
  \brief Module change hook - called by module_change() method to have this
  class validate the proposed values changes \param params A YangParams pointer
  containing all of the changed values \return SR_ERR_OK if the values are
  validated; SR_ERR_VALIDATION_FAILED on validation failure. Can return any
  other sysrepo error status as necessary.
  */
 virtual int validate(
     std::shared_ptr<YangParams> params,
     std::shared_ptr<YangParams> deletedParams);

 /**
  * Module change hook - called by module_change() method with filtered events
  */
 virtual void valueChange(
     const std::string& xpath,
     std::shared_ptr<YangParam> oldValue,
     std::shared_ptr<YangParam> newValue);

private:
 bool addCallHomeClient(std::string url, std::string port);
 bool deleteCallHomeClient(std::string url, std::string port);
};

}

#endif /* INC_IETFNETCONFSERVER_HANDLER_H_ */
