/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanSupervision.cpp
 * \brief     Module ORanSupervision interface
 *
 *
 * \details   This file defines the YANG module o-ran-supervision interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-supervision"
 *            YANG Filename:    "o-ran-supervision.yang"
 *            Module Prefix:    "o-ran-supervision"
 *            Module namespace: "urn:o-ran:supervision:1.0"
 *
 * Add user description here
 *
 * %%->

 * <-%%
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleORanSupervision.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleORanSupervision_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************

// *****************************************************************************
// Leafs
// *****************************************************************************

// *****************************************************************************
// References
// *****************************************************************************

// *****************************************************************************
// Containers
// *****************************************************************************
// -----------------------------------------------------------------------------
// Container:   supervision
// Description:
// -----------------------------------------------------------------------------
CntSupervision::CntSupervision(uint32_t id)
	: YangContainer("supervision", id)
{
}

CntSupervision::~CntSupervision()
{
}

YangResult_E CntSupervision::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /supervision/supervision-group
	// Description:
	// -----------------------------------------------------------------------------
	GrpSupervisionGroup supervisionGroupInst(ITEM_SUPERVISION_GROUP);
	supervisionGroupInst.initialise();
	addGroup(supervisionGroupInst);



	return YangResult_E::OK;
}





// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    watchdog-input
// Description:
// -----------------------------------------------------------------------------
GrpWatchdogInput::GrpWatchdogInput(uint32_t id)
	: YangGroup("watchdog-input", id)
{
}

GrpWatchdogInput::~GrpWatchdogInput()
{
}

YangResult_E GrpWatchdogInput::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /watchdog-input/supervision-notification-interval
	// Description: The interval in seconds at which supervision notifications are sent.
	//              If not specified the default value of 60 seconds shall apply.
	// Type:        uint16
	// Units:       seconds
	// -----------------------------------------------------------------------------
	LeafSupervisionNotificationInterval supervisionNotificationIntervalInst(ITEM_SUPERVISION_NOTIFICATION_INTERVAL);
	addLeaf(supervisionNotificationIntervalInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /watchdog-input/guard-timer-overhead
	// Description: This is overhead added to the supervision timer used to calculate the
	//              supervision wathcdog timer. i.e.,
	//
	//              supervision timer = notification timer + guard-timer-overhead
	//
	//              If not specified the default value of 10 seconds shall apply.
	//
	//              Failure to send this rpc again within the timeout sets the radio into
	//              'loss of supervision' state.
	//
	//              NOTE - The supervision timer MUST not be less that the confimed
	//              timeout timer (when the feature is supported).
	//
	//              This type of constraint (using an RPCs input) cannot be formally
	//              expressed in YANG.
	// Type:        uint16
	// Units:       seconds
	// -----------------------------------------------------------------------------
	LeafGuardTimerOverhead guardTimerOverheadInst(ITEM_GUARD_TIMER_OVERHEAD);
	addLeaf(guardTimerOverheadInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /watchdog-input/supervision-notification-interval
// Description: The interval in seconds at which supervision notifications are sent.
//              If not specified the default value of 60 seconds shall apply.
// -----------------------------------------------------------------------------
GrpWatchdogInput::LeafSupervisionNotificationInterval::LeafSupervisionNotificationInterval(uint32_t id)
	: YangLeaf("supervision-notification-interval", id)
{
}

GrpWatchdogInput::LeafSupervisionNotificationInterval::~LeafSupervisionNotificationInterval()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /watchdog-input/guard-timer-overhead
// Description: This is overhead added to the supervision timer used to calculate the
//              supervision wathcdog timer. i.e.,
//
//              supervision timer = notification timer + guard-timer-overhead
//
//              If not specified the default value of 10 seconds shall apply.
//
//              Failure to send this rpc again within the timeout sets the radio into
//              'loss of supervision' state.
//
//              NOTE - The supervision timer MUST not be less that the confimed
//              timeout timer (when the feature is supported).
//
//              This type of constraint (using an RPCs input) cannot be formally
//              expressed in YANG.
// -----------------------------------------------------------------------------
GrpWatchdogInput::LeafGuardTimerOverhead::LeafGuardTimerOverhead(uint32_t id)
	: YangLeaf("guard-timer-overhead", id)
{
}

GrpWatchdogInput::LeafGuardTimerOverhead::~LeafGuardTimerOverhead()
{
}



// -----------------------------------------------------------------------------
// Grouping:    watchdog-output
// Description:
// -----------------------------------------------------------------------------
GrpWatchdogOutput::GrpWatchdogOutput(uint32_t id)
	: YangGroup("watchdog-output", id)
{
}

GrpWatchdogOutput::~GrpWatchdogOutput()
{
}

YangResult_E GrpWatchdogOutput::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /watchdog-output/next-update-at
	// Description: Indicates the time when the next supervision notification is expected.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafNextUpdateAt nextUpdateAtInst(ITEM_NEXT_UPDATE_AT);
	addLeaf(nextUpdateAtInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /watchdog-output/next-update-at
// Description: Indicates the time when the next supervision notification is expected.
// -----------------------------------------------------------------------------
GrpWatchdogOutput::LeafNextUpdateAt::LeafNextUpdateAt(uint32_t id)
	: YangLeaf("next-update-at", id)
{
}

GrpWatchdogOutput::LeafNextUpdateAt::~LeafNextUpdateAt()
{
}



// -----------------------------------------------------------------------------
// Grouping:    supervision-group
// Description:
// -----------------------------------------------------------------------------
GrpSupervisionGroup::GrpSupervisionGroup(uint32_t id)
	: YangGroup("supervision-group", id)
{
}

GrpSupervisionGroup::~GrpSupervisionGroup()
{
}

YangResult_E GrpSupervisionGroup::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Container:   /supervision-group/cu-plane-monitoring
	// Description: container describing operation of CU plane monitoring
	// -----------------------------------------------------------------------------
	CntCuPlaneMonitoring cuPlaneMonitoringInst(ITEM_CU_PLANE_MONITORING);
	cuPlaneMonitoringInst.initialise();
	addContainer(cuPlaneMonitoringInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   cu-plane-monitoring
// Description: container describing operation of CU plane monitoring
// -----------------------------------------------------------------------------
GrpSupervisionGroup::CntCuPlaneMonitoring::CntCuPlaneMonitoring(uint32_t id)
	: YangContainer("cu-plane-monitoring", id)
{
}

GrpSupervisionGroup::CntCuPlaneMonitoring::~CntCuPlaneMonitoring()
{
}

YangResult_E GrpSupervisionGroup::CntCuPlaneMonitoring::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /supervision-group/cu-plane-monitoring/configured-cu-monitoring-interval
	// Description: This value corresponds to the configured value of the timer used by
	//              the O-RU to monitor the C/U plane connection.
	//
	//              A value of 0 means that the O-RU's shall disable its CU plane
	//              monitoring.
	//
	//              A NETCONF client should configure the value according to the
	//              configuration of the PHY layer and/or C/U plane section types
	//              supported and/or any fault tolerant operation. For example,
	//
	//              i) when opertaing with an O-DU supporting non-LAA LTE, this value can
	//              be configured to a value according to the repetition time of
	//              transmitted reference symbols across the fronthaul interface
	//              ii) when opertaing with an O-DU supporting C-Plane Section Type 0,
	//              this value can configured to a value according to the minimum
	//              repetition interval of section type 0.
	//              iii) when operating with an O-DU supporting fault tolerant operation,
	//              this value can be configured according to the fault tolerant heartbeat
	//              interval
	// Type:        uint8
	// Units:       milliseconds
	// -----------------------------------------------------------------------------
	LeafConfiguredCuMonitoringInterval configuredCuMonitoringIntervalInst(ITEM_CONFIGURED_CU_MONITORING_INTERVAL);
	addLeaf(configuredCuMonitoringIntervalInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /supervision-group/cu-plane-monitoring/configured-cu-monitoring-interval
// Description: This value corresponds to the configured value of the timer used by
//              the O-RU to monitor the C/U plane connection.
//
//              A value of 0 means that the O-RU's shall disable its CU plane
//              monitoring.
//
//              A NETCONF client should configure the value according to the
//              configuration of the PHY layer and/or C/U plane section types
//              supported and/or any fault tolerant operation. For example,
//
//              i) when opertaing with an O-DU supporting non-LAA LTE, this value can
//              be configured to a value according to the repetition time of
//              transmitted reference symbols across the fronthaul interface
//              ii) when opertaing with an O-DU supporting C-Plane Section Type 0,
//              this value can configured to a value according to the minimum
//              repetition interval of section type 0.
//              iii) when operating with an O-DU supporting fault tolerant operation,
//              this value can be configured according to the fault tolerant heartbeat
//              interval
// -----------------------------------------------------------------------------
GrpSupervisionGroup::CntCuPlaneMonitoring::LeafConfiguredCuMonitoringInterval::LeafConfiguredCuMonitoringInterval(uint32_t id)
	: YangLeaf("configured-cu-monitoring-interval", id)
{
}

GrpSupervisionGroup::CntCuPlaneMonitoring::LeafConfiguredCuMonitoringInterval::~LeafConfiguredCuMonitoringInterval()
{
}







// *****************************************************************************
// Lists
// *****************************************************************************

// *****************************************************************************
// Choices
// *****************************************************************************

// *****************************************************************************
// Notifications
// *****************************************************************************
// -----------------------------------------------------------------------------
// Notification:supervision-notification
// Description: Notification to indicate that NETCONF management interface is up
//              and also indicate the values of the timers for this NETCONF session
// -----------------------------------------------------------------------------
NotifSupervisionNotification::NotifSupervisionNotification(uint32_t id)
	: YangNotif("supervision-notification", id)
{
}

NotifSupervisionNotification::~NotifSupervisionNotification()
{
}

YangResult_E NotifSupervisionNotification::initialise(void)
{


	return YangResult_E::OK;
}




// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-supervision
// Description: This module defines the configuration data and supervision RPCs that are
//              used to detect loss M-Plane and CU-Plane connectivity.
//
//              Copyright 2019 the O-RAN Alliance.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
//              AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//              IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//              ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//              LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//              CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//              SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//              INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//              ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//              POSSIBILITY OF SUCH DAMAGE.
//
//              Redistribution and use in source and binary forms, with or without
//              modification, are permitted provided that the following conditions are met:
//
//              * Redistributions of source code must retain the above copyright notice,
//              this list of conditions and the above disclaimer.
//              * Redistributions in binary form must reproduce the above copyright notice,
//              this list of conditions and the above disclaimer in the documentation
//              and/or other materials provided with the distribution.
//              * Neither the Members of the O-RAN Alliance nor the names of its
//              contributors may be used to endorse or promote products derived from
//              this software without specific prior written permission.
// -----------------------------------------------------------------------------
ModuleORanSupervision::ModuleORanSupervision(uint32_t id)
	: YangModule ("o-ran-supervision",
	              "o-ran-supervision.yang",
	              "o-ran-supervision",
	              "urn:o-ran:supervision:1.0",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Container:   /supervision
	// Description:
	// -----------------------------------------------------------------------------
	CntSupervision supervisionInst(ITEM_SUPERVISION);
	supervisionInst.initialise();
	addContainer(supervisionInst);

	// -----------------------------------------------------------------------------
	// Notification:/supervision-notification
	// Description: Notification to indicate that NETCONF management interface is up
	//              and also indicate the values of the timers for this NETCONF session
	// -----------------------------------------------------------------------------
	NotifSupervisionNotification supervisionNotificationInst(ITEM_SUPERVISION_NOTIFICATION);
	supervisionNotificationInst.initialise();
	addNotification(supervisionNotificationInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleORanSupervision::~ModuleORanSupervision()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleORanSupervision::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleORanSupervision>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleORanSupervision::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
