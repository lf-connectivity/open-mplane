/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranYangHandlerMgr.cpp
 * \brief     Sets up the handlers for a variety of RU modules.
 *
 *
 * \details   Registered handlers are stored in a vector for the class.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "OranYangHandlerMgr.h"

#include "IetfInterfacesHandler.h"
#include "IetfNetconfAcmHandler.h"
#include "IetfNetconfServerHandler.h"
#include "OranModuleCapHandler.h"
#include "OranProcessingElementHandler.h"
#include "OranUplaneConfHandler.h"
#include "OranUserMgmtHandler.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangHandlerMgr>
IYangHandlerMgr::create(std::shared_ptr<IYangModuleMgr> moduleMgr) {
  static std::shared_ptr<IYangHandlerMgr> instance(
      std::make_shared<OranYangHandlerMgr>(moduleMgr));
  return instance;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangHandlerMgr>
IYangHandlerMgr::singleton() {
  // pass in dummy (unused) variable
  return create(std::shared_ptr<IYangModuleMgr>());
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranYangHandlerMgr::OranYangHandlerMgr(
    std::shared_ptr<IYangModuleMgr> moduleMgr)
    : YangHandlerMgr(moduleMgr) {
  registerHandler(std::make_shared<IetfInterfacesHandler>(moduleMgr));
  registerHandler(std::make_shared<IetfNetconfAcmHandler>(moduleMgr));
  registerHandler(std::make_shared<IetfNetconfServerHandler>(moduleMgr));
  registerHandler(std::make_shared<OranModuleCapHandler>(moduleMgr));
  registerHandler(std::make_shared<OranProcessingElementHandler>(moduleMgr));
  registerHandler(std::make_shared<OranUplaneConfHandler>(moduleMgr));
  registerHandler(std::make_shared<OranUserMgmtHandler>(moduleMgr));
}

//-------------------------------------------------------------------------------------------------------------
OranYangHandlerMgr::~OranYangHandlerMgr() {}
