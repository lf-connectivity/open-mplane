#ifndef _MODULE_O_RAN_SUPERVISION_H_
#define _MODULE_O_RAN_SUPERVISION_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanSupervision.h
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
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// -----------------------------------------------------------------------------
// Common
// -----------------------------------------------------------------------------

#include "YangModule.h"

// -----------------------------------------------------------------------------
// External Modules
// -----------------------------------------------------------------------------

// Module:   ietf-yang-types
// Revision:
// Notes:
#include "YangModuleIetfYangTypes.h"


namespace Mplane {

namespace ModuleORanSupervision_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

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
// Container:   /supervision
// Description:
// -----------------------------------------------------------------------------
class CntSupervision : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_SUPERVISION_GROUP,  // Use GrpSupervisionGroup
	};

	CntSupervision(uint32_t id);
	~CntSupervision();

	YangResult_E initialise(void);

}; // CntSupervision


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /watchdog-input
// Description:
// -----------------------------------------------------------------------------
class GrpWatchdogInput : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_SUPERVISION_NOTIFICATION_INTERVAL,  // LeafSupervisionNotificationInterval
		ITEM_GUARD_TIMER_OVERHEAD,  // LeafGuardTimerOverhead
	};

	GrpWatchdogInput(uint32_t id);
	~GrpWatchdogInput();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /watchdog-input/supervision-notification-interval
	// Description: The interval in seconds at which supervision notifications are sent.
	//              If not specified the default value of 60 seconds shall apply.
	// -----------------------------------------------------------------------------
	class LeafSupervisionNotificationInterval : public YangLeaf
	{
	public:

		LeafSupervisionNotificationInterval(uint32_t id);
		~LeafSupervisionNotificationInterval();

	}; // LeafSupervisionNotificationInterval

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
	class LeafGuardTimerOverhead : public YangLeaf
	{
	public:

		LeafGuardTimerOverhead(uint32_t id);
		~LeafGuardTimerOverhead();

	}; // LeafGuardTimerOverhead

}; // GrpWatchdogInput

// -----------------------------------------------------------------------------
// Grouping:    /watchdog-output
// Description:
// -----------------------------------------------------------------------------
class GrpWatchdogOutput : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_NEXT_UPDATE_AT,  // LeafNextUpdateAt
	};

	GrpWatchdogOutput(uint32_t id);
	~GrpWatchdogOutput();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /watchdog-output/next-update-at
	// Description: Indicates the time when the next supervision notification is expected.
	// -----------------------------------------------------------------------------
	class LeafNextUpdateAt : public YangLeaf
	{
	public:

		LeafNextUpdateAt(uint32_t id);
		~LeafNextUpdateAt();

	}; // LeafNextUpdateAt

}; // GrpWatchdogOutput

// -----------------------------------------------------------------------------
// Grouping:    /supervision-group
// Description:
// -----------------------------------------------------------------------------
class GrpSupervisionGroup : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_CU_PLANE_MONITORING,  // CntCuPlaneMonitoring
	};

	GrpSupervisionGroup(uint32_t id);
	~GrpSupervisionGroup();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Container:   /supervision-group/cu-plane-monitoring
	// Description: container describing operation of CU plane monitoring
	// -----------------------------------------------------------------------------
	class CntCuPlaneMonitoring : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_CONFIGURED_CU_MONITORING_INTERVAL,  // LeafConfiguredCuMonitoringInterval
		};

		CntCuPlaneMonitoring(uint32_t id);
		~CntCuPlaneMonitoring();

		YangResult_E initialise(void);

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
		class LeafConfiguredCuMonitoringInterval : public YangLeaf
		{
		public:

			LeafConfiguredCuMonitoringInterval(uint32_t id);
			~LeafConfiguredCuMonitoringInterval();

		}; // LeafConfiguredCuMonitoringInterval

	}; // CntCuPlaneMonitoring

}; // GrpSupervisionGroup


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
// Notification:/supervision-notification
// Description: Notification to indicate that NETCONF management interface is up
//              and also indicate the values of the timers for this NETCONF session
// -----------------------------------------------------------------------------
class NotifSupervisionNotification : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
	};

	NotifSupervisionNotification(uint32_t id);
	~NotifSupervisionNotification();

	YangResult_E initialise(void);

}; // NotifSupervisionNotification


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
class ModuleORanSupervision : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_SUPERVISION,  // CntSupervision
		ITEM_SUPERVISION_NOTIFICATION,  // NotifSupervisionNotification
	};

	ModuleORanSupervision(uint32_t id);
	~ModuleORanSupervision();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanSupervision_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_SUPERVISION_H_ */
