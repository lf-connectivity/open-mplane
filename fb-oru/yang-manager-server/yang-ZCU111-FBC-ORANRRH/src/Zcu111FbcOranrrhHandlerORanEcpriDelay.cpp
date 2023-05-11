/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanEcpriDelay.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <string>
#include <memory>

#include "ILoggable.h"
#include "IBootEnv.h"
#include "YangMgrServer.h"
#include "SysrepoGetitemsCallback.h"

#include "Zcu111FbcOranrrhHandlerORanEcpriDelay.h"
#include <MplaneEcpri.h>

using namespace Mplane;
using namespace std;

//module: o-ran-ecpri-delay
//  +--rw ecpri-delay-message
//     +--ro ru-compensation
//     |  +--ro tcv2? uint32
//     |  +--ro tcv1? uint32
//     +--rw enable-message5?   boolean
//     +--rw message5-sessions
//        +--rw session-parameters* [session-id]
//           +--rw session-id               uint32
//           +--rw processing-element-name? leafref
//           +--ro flow-state
//              +--ro responses-transmitted? uint32
//              +--ro requests-transmitted?  uint32
//              +--ro followups-transmitted? uint32


//=============================================================================================================
// LOCAL
//=============================================================================================================
//=============================================================================================================
// PUBLIC
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanEcpriDelay::Zcu111FbcOranrrhHandlerORanEcpriDelay(std::shared_ptr<IYangModuleMgr> moduleMgr)
: YangHandlerSysrepo("o-ran-ecpri-delay", moduleMgr, "Zcu111FbcOranrrhHandlerORanEcpriDelay")
, mCallback(std::make_shared <SysrepoGetitemsCallback> (path("ecpri-delay-message")))
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanEcpriDelay::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false;

    // Get settings from HAL
	std::shared_ptr<ILeafContainer> declarations = mCallback->addContainer("ecpri-delay-message");
    //declarations->addLeaf("enable-message5", mplane::message5Enabled());
	std::shared_ptr<ILeafContainer> compensation = declarations->addContainer("ru-compensation");
	std::shared_ptr<ILeafContainer> sessions = declarations->addContainer("message5-sessions");

	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe();

	logDebugVerbose("oran ecpri delay done");

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanEcpriDelay::valueChange(const std::string &xpath,
		std::shared_ptr<YangParam> oldValue,
		std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanEcpriDelay::valueChange() - %s", xpath.c_str());
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
