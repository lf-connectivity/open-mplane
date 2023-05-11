/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanOperations.cpp
 * \brief     Module ORanOperations interface
 *
 *
 * \details   This file defines the YANG module o-ran-operations interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-operations"
 *            YANG Filename:    "o-ran-operations.yang"
 *            Module Prefix:    "o-ran-ops"
 *            Module namespace: "urn:o-ran:operations:1.0"
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
#include "YangModuleORanOperations.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleORanOperations_NS;

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
// Container:   operational-info
// Description: a collection of operational infor for the O-RU
// -----------------------------------------------------------------------------
CntOperationalInfo::CntOperationalInfo(uint32_t id)
	: YangContainer("operational-info", id)
{
}

CntOperationalInfo::~CntOperationalInfo()
{
}

YangResult_E CntOperationalInfo::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /operational-info/operational-group
	// Description:
	// -----------------------------------------------------------------------------
	GrpOperationalGroup operationalGroupInst(ITEM_OPERATIONAL_GROUP);
	operationalGroupInst.initialise();
	addGroup(operationalGroupInst);



	return YangResult_E::OK;
}





// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    operational-group
// Description:
// -----------------------------------------------------------------------------
GrpOperationalGroup::GrpOperationalGroup(uint32_t id)
	: YangGroup("operational-group", id)
{
}

GrpOperationalGroup::~GrpOperationalGroup()
{
}

YangResult_E GrpOperationalGroup::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/re-call-home-no-ssh-timer
	// Description: A common timer used by the O-RAN equipment to trigger the repeated call
	//              home procedure to all identified call home servers to which the O-RAN
	//              equipment has not already an established SSH connection.
	//
	//              A value of 0 means that the O-RAN equipment shall disable operation
	//              of the timer triggered NETCONF call home procedure.
	// Type:        uint16
	// Units:       seconds
	// -----------------------------------------------------------------------------
	LeafReCallHomeNoSshTimer reCallHomeNoSshTimerInst(ITEM_RE_CALL_HOME_NO_SSH_TIMER);
	addLeaf(reCallHomeNoSshTimerInst);

	// -----------------------------------------------------------------------------
	// Container:   /operational-group/declarations
	// Description: WG4 Specific Declarations of supported version of standards
	// -----------------------------------------------------------------------------
	CntDeclarations declarationsInst(ITEM_DECLARATIONS);
	declarationsInst.initialise();
	addContainer(declarationsInst);

	// -----------------------------------------------------------------------------
	// Container:   /operational-group/operational-state
	// Description: Operational state for the O-RAN network element
	// -----------------------------------------------------------------------------
	CntOperationalState operationalStateInst(ITEM_OPERATIONAL_STATE);
	operationalStateInst.initialise();
	addContainer(operationalStateInst);

	// -----------------------------------------------------------------------------
	// Container:   /operational-group/clock
	// Description: System date and time properties used by all working groups.
	// -----------------------------------------------------------------------------
	CntClock clockInst(ITEM_CLOCK);
	clockInst.initialise();
	addContainer(clockInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/re-call-home-no-ssh-timer
// Description: A common timer used by the O-RAN equipment to trigger the repeated call
//              home procedure to all identified call home servers to which the O-RAN
//              equipment has not already an established SSH connection.
//
//              A value of 0 means that the O-RAN equipment shall disable operation
//              of the timer triggered NETCONF call home procedure.
// -----------------------------------------------------------------------------
GrpOperationalGroup::LeafReCallHomeNoSshTimer::LeafReCallHomeNoSshTimer(uint32_t id)
	: YangLeaf("re-call-home-no-ssh-timer", id)
{
}

GrpOperationalGroup::LeafReCallHomeNoSshTimer::~LeafReCallHomeNoSshTimer()
{
}

// -----------------------------------------------------------------------------
// Container:   declarations
// Description: WG4 Specific Declarations of supported version of standards
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntDeclarations::CntDeclarations(uint32_t id)
	: YangContainer("declarations", id)
{
}

GrpOperationalGroup::CntDeclarations::~CntDeclarations()
{
}

YangResult_E GrpOperationalGroup::CntDeclarations::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/declarations/ru-instance-id
	// Description: a unique instance identifier that may be used to identify a
	//              particular hardware instance, e.g., when used performing hierarchical
	//              management via the O-DU.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafRuInstanceId ruInstanceIdInst(ITEM_RU_INSTANCE_ID);
	addLeaf(ruInstanceIdInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/declarations/supported-mplane-version
	// Description: Parameter provides highest M-Plane specification version device is compliant with.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafSupportedMplaneVersion supportedMplaneVersionInst(ITEM_SUPPORTED_MPLANE_VERSION);
	addLeaf(supportedMplaneVersionInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/declarations/supported-cusplane-version
	// Description: Parameter provides highest CUS-Plane specification version device is compliant with.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafSupportedCusplaneVersion supportedCusplaneVersionInst(ITEM_SUPPORTED_CUSPLANE_VERSION);
	addLeaf(supportedCusplaneVersionInst);

	// -----------------------------------------------------------------------------
	// List:        /operational-group/declarations/supported-header-mechanism
	// Description: list provides information regarding type and version of headers.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstSupportedHeaderMechanism supportedHeaderMechanismInst(ITEM_SUPPORTED_HEADER_MECHANISM);
	supportedHeaderMechanismInst.initialise();
	addList(supportedHeaderMechanismInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/declarations/ru-instance-id
// Description: a unique instance identifier that may be used to identify a
//              particular hardware instance, e.g., when used performing hierarchical
//              management via the O-DU.
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntDeclarations::LeafRuInstanceId::LeafRuInstanceId(uint32_t id)
	: YangLeaf("ru-instance-id", id)
{
}

GrpOperationalGroup::CntDeclarations::LeafRuInstanceId::~LeafRuInstanceId()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/declarations/supported-mplane-version
// Description: Parameter provides highest M-Plane specification version device is compliant with.
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntDeclarations::LeafSupportedMplaneVersion::LeafSupportedMplaneVersion(uint32_t id)
	: YangLeaf("supported-mplane-version", id)
{
}

GrpOperationalGroup::CntDeclarations::LeafSupportedMplaneVersion::~LeafSupportedMplaneVersion()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/declarations/supported-cusplane-version
// Description: Parameter provides highest CUS-Plane specification version device is compliant with.
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntDeclarations::LeafSupportedCusplaneVersion::LeafSupportedCusplaneVersion(uint32_t id)
	: YangLeaf("supported-cusplane-version", id)
{
}

GrpOperationalGroup::CntDeclarations::LeafSupportedCusplaneVersion::~LeafSupportedCusplaneVersion()
{
}

// -----------------------------------------------------------------------------
// List:        supported-header-mechanism
// Description: list provides information regarding type and version of headers.
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntDeclarations::LstSupportedHeaderMechanism::LstSupportedHeaderMechanism(uint32_t id)
	: YangList("supported-header-mechanism", id)
{
}

GrpOperationalGroup::CntDeclarations::LstSupportedHeaderMechanism::~LstSupportedHeaderMechanism()
{
}

YangResult_E GrpOperationalGroup::CntDeclarations::LstSupportedHeaderMechanism::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/declarations/supported-header-mechanism/protocol
	// Description: Transport protocol type.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafProtocol protocolInst(ITEM_PROTOCOL);
	addLeaf(protocolInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/declarations/supported-header-mechanism/ecpri-concatenation-support
	// Description: This leaf is used to indicate whether the O-RU supports the optional
	//              eCPRI concatenation capability
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafEcpriConcatenationSupport ecpriConcatenationSupportInst(ITEM_ECPRI_CONCATENATION_SUPPORT);
	addLeaf(ecpriConcatenationSupportInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/declarations/supported-header-mechanism/protocol-version
	// Description: Header protocol version.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafProtocolVersion protocolVersionInst(ITEM_PROTOCOL_VERSION);
	addLeaf(protocolVersionInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/declarations/supported-header-mechanism/protocol
// Description: Transport protocol type.
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntDeclarations::LstSupportedHeaderMechanism::LeafProtocol::LeafProtocol(uint32_t id)
	: YangLeaf("protocol", id)
{
}

GrpOperationalGroup::CntDeclarations::LstSupportedHeaderMechanism::LeafProtocol::~LeafProtocol()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/declarations/supported-header-mechanism/ecpri-concatenation-support
// Description: This leaf is used to indicate whether the O-RU supports the optional
//              eCPRI concatenation capability
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntDeclarations::LstSupportedHeaderMechanism::LeafEcpriConcatenationSupport::LeafEcpriConcatenationSupport(uint32_t id)
	: YangLeaf("ecpri-concatenation-support", id)
{
}

GrpOperationalGroup::CntDeclarations::LstSupportedHeaderMechanism::LeafEcpriConcatenationSupport::~LeafEcpriConcatenationSupport()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/declarations/supported-header-mechanism/protocol-version
// Description: Header protocol version.
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntDeclarations::LstSupportedHeaderMechanism::LeafProtocolVersion::LeafProtocolVersion(uint32_t id)
	: YangLeaf("protocol-version", id)
{
}

GrpOperationalGroup::CntDeclarations::LstSupportedHeaderMechanism::LeafProtocolVersion::~LeafProtocolVersion()
{
}






// -----------------------------------------------------------------------------
// Container:   operational-state
// Description: Operational state for the O-RAN network element
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntOperationalState::CntOperationalState(uint32_t id)
	: YangContainer("operational-state", id)
{
}

GrpOperationalGroup::CntOperationalState::~CntOperationalState()
{
}

YangResult_E GrpOperationalGroup::CntOperationalState::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/operational-state/restart-cause
	// Description: the cause for the last restart of the O-RAN Network Element
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafRestartCause restartCauseInst(ITEM_RESTART_CAUSE);
	addLeaf(restartCauseInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/operational-state/restart-datetime
	// Description: The system date and time when the system last restarted.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafRestartDatetime restartDatetimeInst(ITEM_RESTART_DATETIME);
	addLeaf(restartDatetimeInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/operational-state/restart-cause
// Description: the cause for the last restart of the O-RAN Network Element
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntOperationalState::LeafRestartCause::LeafRestartCause(uint32_t id)
	: YangLeaf("restart-cause", id)
{
}

GrpOperationalGroup::CntOperationalState::LeafRestartCause::~LeafRestartCause()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/operational-state/restart-datetime
// Description: The system date and time when the system last restarted.
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntOperationalState::LeafRestartDatetime::LeafRestartDatetime(uint32_t id)
	: YangLeaf("restart-datetime", id)
{
}

GrpOperationalGroup::CntOperationalState::LeafRestartDatetime::~LeafRestartDatetime()
{
}




// -----------------------------------------------------------------------------
// Container:   clock
// Description: System date and time properties used by all working groups.
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntClock::CntClock(uint32_t id)
	: YangContainer("clock", id)
{
}

GrpOperationalGroup::CntClock::~CntClock()
{
}

YangResult_E GrpOperationalGroup::CntClock::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/clock/timezone-name
	// Description: An optional TZ database name to use for the system,
	//              such as 'Europe/Stockholm'
	//
	//              Time zone name is an informative leaf and is NOT used in the
	//              managed element to convert local time zone.
	//
	//              The managed element may include time zone name in measurement or
	//              fault data.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafTimezoneName timezoneNameInst(ITEM_TIMEZONE_NAME);
	addLeaf(timezoneNameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /operational-group/clock/timezone-utc-offset
	// Description: The number of minutes to add to UTC time to
	//              identify the time zone for this system.  For example,
	//              'UTC - 8:00 hours' would be represented as '-480'.
	// Type:        int16
	// Units:       minutes
	// -----------------------------------------------------------------------------
	LeafTimezoneUtcOffset timezoneUtcOffsetInst(ITEM_TIMEZONE_UTC_OFFSET);
	addLeaf(timezoneUtcOffsetInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/clock/timezone-name
// Description: An optional TZ database name to use for the system,
//              such as 'Europe/Stockholm'
//
//              Time zone name is an informative leaf and is NOT used in the
//              managed element to convert local time zone.
//
//              The managed element may include time zone name in measurement or
//              fault data.
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntClock::LeafTimezoneName::LeafTimezoneName(uint32_t id)
	: YangLeaf("timezone-name", id)
{
}

GrpOperationalGroup::CntClock::LeafTimezoneName::~LeafTimezoneName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /operational-group/clock/timezone-utc-offset
// Description: The number of minutes to add to UTC time to
//              identify the time zone for this system.  For example,
//              'UTC - 8:00 hours' would be represented as '-480'.
// -----------------------------------------------------------------------------
GrpOperationalGroup::CntClock::LeafTimezoneUtcOffset::LeafTimezoneUtcOffset(uint32_t id)
	: YangLeaf("timezone-utc-offset", id)
{
}

GrpOperationalGroup::CntClock::LeafTimezoneUtcOffset::~LeafTimezoneUtcOffset()
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

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-operations
// Description: This module defines the YANG model used for O-RAN operations.
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
ModuleORanOperations::ModuleORanOperations(uint32_t id)
	: YangModule ("o-ran-operations",
	              "o-ran-operations.yang",
	              "o-ran-ops",
	              "urn:o-ran:operations:1.0",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Container:   /operational-info
	// Description: a collection of operational infor for the O-RU
	// -----------------------------------------------------------------------------
	CntOperationalInfo operationalInfoInst(ITEM_OPERATIONAL_INFO);
	operationalInfoInst.initialise();
	addContainer(operationalInfoInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleORanOperations::~ModuleORanOperations()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleORanOperations::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleORanOperations>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleORanOperations::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
