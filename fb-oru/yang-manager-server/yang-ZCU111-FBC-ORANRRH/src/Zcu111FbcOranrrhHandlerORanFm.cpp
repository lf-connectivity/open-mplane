/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanFm.cpp
 * \brief     Implements o-ran-fm.yang by using OranFm.cpp
 *
 *
 * \details
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <string>
#include <memory>

#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"
#include "Zcu111FbcOranrrhHandlerORanFm.h"
#include "OranFm.h"

using namespace std;

namespace Mplane
{

// Displays the attached alarms at the end of initialisation - Remove when TIF command added.
//#define SHOW_ATTACHED_ALARMS

/*
 +--ro active-alarm-list
     +--ro active-alarms*
        +--ro fault-id          uint16			Alarm::getId(), it needs to be an int
        +--ro fault-source      string			Alarm::getRootCause()
        +--ro affected-objects*					from xml file
        |  +--ro name  string
        +--ro fault-severity    enumeration		from xml file
        +--ro is-cleared        boolean			Alarm::isAlarmActive(if true, will not be in the list, but can be in notification)
        +--ro fault-text?       string			description from xml file
        +--ro event-time        yang:date-and-time	  Alarm::getTimeStamp

  notifications:
    +---n alarm-notif
       +--ro fault-id          uint16
       +--ro fault-source      string
       +--ro affected-objects*
       |  +--ro name  string
       +--ro fault-severity    enumeration
       +--ro is-cleared        boolean
       +--ro fault-text?       string
       +--ro event-time        yang:date-and-time

 */


//=============================================================================================================
// LOCAL
//=============================================================================================================
//=============================================================================================================
// PUBLIC
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanFm::Zcu111FbcOranrrhHandlerORanFm(std::shared_ptr<IYangModuleMgr> moduleMgr)
: YangHandlerSysrepo("o-ran-fm", moduleMgr, "Zcu111FbcOranrrhHandlerORanFm")
, mCallback(std::make_shared <SysrepoGetitemsCallback> (path("active-alarm-list")))
, mAlarmFault(*this, mCallback)
{}

Zcu111FbcOranrrhHandlerORanFm::~Zcu111FbcOranrrhHandlerORanFm()
{
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanFm::initialise()
{
	// daisy chain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false;
	getItemsSubscribe(mCallback->path(), mCallback);

	mAlarmFault.AttachAlarms();

#if defined (SHOW_ATTACHED_ALARMS)
	// Show attached alarms
	mAlarmFault.show();
#endif

	return true;
}


}
