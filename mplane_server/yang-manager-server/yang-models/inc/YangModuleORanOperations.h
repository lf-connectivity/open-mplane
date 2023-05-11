#ifndef _MODULE_O_RAN_OPERATIONS_H_
#define _MODULE_O_RAN_OPERATIONS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanOperations.h
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

// Module:   ietf-netconf-acm
// Revision:
// Notes:
#include "YangModuleIetfNetconfAcm.h"

// Module:   ietf-hardware
// Revision:
// Notes:
#include "YangModuleIetfHardware.h"


namespace Mplane {

namespace ModuleORanOperations_NS {

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
// Container:   /operational-info
// Description: a collection of operational infor for the O-RU
// -----------------------------------------------------------------------------
class CntOperationalInfo : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_OPERATIONAL_GROUP, // Use GrpOperationalGroup
 };

 CntOperationalInfo(uint32_t id);
 ~CntOperationalInfo();

 YangResult_E initialise(void);

}; // CntOperationalInfo


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /operational-group
// Description:
// -----------------------------------------------------------------------------
class GrpOperationalGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_RE_CALL_HOME_NO_SSH_TIMER, // LeafReCallHomeNoSshTimer
   ITEM_DECLARATIONS, // CntDeclarations
   ITEM_OPERATIONAL_STATE, // CntOperationalState
   ITEM_CLOCK, // CntClock
 };

 GrpOperationalGroup(uint32_t id);
 ~GrpOperationalGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /operational-group/re-call-home-no-ssh-timer
 // Description: A common timer used by the O-RAN equipment to trigger
 // the repeated call
 //              home procedure to all identified call home servers to
 //              which the O-RAN equipment has not already an established
 //              SSH connection.
 //
 //              A value of 0 means that the O-RAN equipment shall
 //              disable operation of the timer triggered NETCONF call
 //              home procedure.
 // -----------------------------------------------------------------------------
 class LeafReCallHomeNoSshTimer : public YangLeaf {
  public:
   LeafReCallHomeNoSshTimer(uint32_t id);
   ~LeafReCallHomeNoSshTimer();

 }; // LeafReCallHomeNoSshTimer

 // -----------------------------------------------------------------------------
 // Container:   /operational-group/declarations
 // Description: WG4 Specific Declarations of supported version of
 // standards
 // -----------------------------------------------------------------------------
 class CntDeclarations : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_RU_INSTANCE_ID, // LeafRuInstanceId
     ITEM_SUPPORTED_MPLANE_VERSION, // LeafSupportedMplaneVersion
     ITEM_SUPPORTED_CUSPLANE_VERSION, // LeafSupportedCusplaneVersion
     ITEM_SUPPORTED_HEADER_MECHANISM, // LstSupportedHeaderMechanism
   };

   CntDeclarations(uint32_t id);
   ~CntDeclarations();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /operational-group/declarations/ru-instance-id
   // Description: a unique instance identifier that may be used to
   // identify a
   //              particular hardware instance, e.g., when used
   //              performing hierarchical management via the O-DU.
   // -----------------------------------------------------------------------------
   class LeafRuInstanceId : public YangLeaf {
    public:
     LeafRuInstanceId(uint32_t id);
     ~LeafRuInstanceId();

   }; // LeafRuInstanceId

   // -----------------------------------------------------------------------------
   // Leaf: /operational-group/declarations/supported-mplane-version
   // Description: Parameter provides highest M-Plane specification
   // version device is compliant with.
   // -----------------------------------------------------------------------------
   class LeafSupportedMplaneVersion : public YangLeaf {
    public:
     LeafSupportedMplaneVersion(uint32_t id);
     ~LeafSupportedMplaneVersion();

   }; // LeafSupportedMplaneVersion

   // -----------------------------------------------------------------------------
   // Leaf: /operational-group/declarations/supported-cusplane-version
   // Description: Parameter provides highest CUS-Plane specification
   // version device is compliant with.
   // -----------------------------------------------------------------------------
   class LeafSupportedCusplaneVersion : public YangLeaf {
    public:
     LeafSupportedCusplaneVersion(uint32_t id);
     ~LeafSupportedCusplaneVersion();

   }; // LeafSupportedCusplaneVersion

   // -----------------------------------------------------------------------------
   // List: /operational-group/declarations/supported-header-mechanism
   // Description: list provides information regarding type and version
   // of headers.
   // -----------------------------------------------------------------------------
   class LstSupportedHeaderMechanism : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_PROTOCOL, // LeafProtocol
       ITEM_ECPRI_CONCATENATION_SUPPORT, // LeafEcpriConcatenationSupport
       ITEM_PROTOCOL_VERSION, // LeafProtocolVersion
     };

     LstSupportedHeaderMechanism(uint32_t id);
     ~LstSupportedHeaderMechanism();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /operational-group/declarations/supported-header-mechanism/protocol
     // Description: Transport protocol type.
     // -----------------------------------------------------------------------------
     class LeafProtocol : public YangLeaf {
      public:
       // Transport protocol type.
       enum class Protocol_E : uint32_t {
         ECPRI, // Indicates that an O-RU supports the ecpri header
                // format for the C/U plane
         IEEE_1914_3, // Indicates that an O-RU supports the 1914.3
                      // header format for the C/U plane

         Num_Protocol_E
       };

       LeafProtocol(uint32_t id);
       ~LeafProtocol();

     }; // LeafProtocol

     // -----------------------------------------------------------------------------
     // Leaf:
     // /operational-group/declarations/supported-header-mechanism/ecpri-concatenation-support
     // Description: This leaf is used to indicate whether the O-RU
     // supports the optional
     //              eCPRI concatenation capability
     // -----------------------------------------------------------------------------
     class LeafEcpriConcatenationSupport : public YangLeaf {
      public:
       LeafEcpriConcatenationSupport(uint32_t id);
       ~LeafEcpriConcatenationSupport();

     }; // LeafEcpriConcatenationSupport

     // -----------------------------------------------------------------------------
     // Leaf:
     // /operational-group/declarations/supported-header-mechanism/protocol-version
     // Description: Header protocol version.
     // -----------------------------------------------------------------------------
     class LeafProtocolVersion : public YangLeaf {
      public:
       LeafProtocolVersion(uint32_t id);
       ~LeafProtocolVersion();

     }; // LeafProtocolVersion

   }; // LstSupportedHeaderMechanism

 }; // CntDeclarations

 // -----------------------------------------------------------------------------
 // Container:   /operational-group/operational-state
 // Description: Operational state for the O-RAN network element
 // -----------------------------------------------------------------------------
 class CntOperationalState : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_RESTART_CAUSE, // LeafRestartCause
     ITEM_RESTART_DATETIME, // LeafRestartDatetime
   };

   CntOperationalState(uint32_t id);
   ~CntOperationalState();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /operational-group/operational-state/restart-cause
   // Description: the cause for the last restart of the O-RAN Network
   // Element
   // -----------------------------------------------------------------------------
   class LeafRestartCause : public YangLeaf {
    public:
     // the cause for the last restart of the O-RAN Network Element
     enum class RestartCause_E : uint32_t {
       POWER_ON, // Equipment restarted because it was powered on
       SUPERVISION_WATCHDOG, // Equipment restarted because it's
                             // supervision wathcdog timer wasn't reset
                             // by a NETCONF client (inferring loss of
                             // NETCONF connectivity)
       MPLANE_TRIGGERED_RESTART, // Equipment restarted because of an
                                 // M-plane issued  rpc
       SOFTWARE_FAILURE, // Equipment restarted because of software
                         // failure
       OTHER_WATCHDOG_TIMER, // Equipment restarted because of some other
                             // non NETCONF watchdog timer
       UNKNOWN, // The restart reason for the Equipment is unknown

       Num_RestartCause_E
     };

     LeafRestartCause(uint32_t id);
     ~LeafRestartCause();

   }; // LeafRestartCause

   // -----------------------------------------------------------------------------
   // Leaf:        /operational-group/operational-state/restart-datetime
   // Description: The system date and time when the system last
   // restarted.
   // -----------------------------------------------------------------------------
   class LeafRestartDatetime : public YangLeaf {
    public:
     LeafRestartDatetime(uint32_t id);
     ~LeafRestartDatetime();

   }; // LeafRestartDatetime

 }; // CntOperationalState

 // -----------------------------------------------------------------------------
 // Container:   /operational-group/clock
 // Description: System date and time properties used by all working
 // groups.
 // -----------------------------------------------------------------------------
 class CntClock : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_TIMEZONE_NAME, // LeafTimezoneName
     ITEM_TIMEZONE_UTC_OFFSET, // LeafTimezoneUtcOffset
   };

   CntClock(uint32_t id);
   ~CntClock();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /operational-group/clock/timezone-name
   // Description: An optional TZ database name to use for the
   // system,
   //              such as 'Europe/Stockholm'
   //
   //              Time zone name is an informative leaf and is NOT
   //              used in the managed element to convert local
   //              time zone.
   //
   //              The managed element may include time zone name
   //              in measurement or fault data.
   // -----------------------------------------------------------------------------
   class LeafTimezoneName : public YangLeaf {
    public:
     LeafTimezoneName(uint32_t id);
     ~LeafTimezoneName();

   }; // LeafTimezoneName

   // -----------------------------------------------------------------------------
   // Leaf:        /operational-group/clock/timezone-utc-offset
   // Description: The number of minutes to add to UTC time to
   //              identify the time zone for this system.  For
   //              example, 'UTC - 8:00 hours' would be represented
   //              as '-480'.
   // -----------------------------------------------------------------------------
   class LeafTimezoneUtcOffset : public YangLeaf {
    public:
     LeafTimezoneUtcOffset(uint32_t id);
     ~LeafTimezoneUtcOffset();

   }; // LeafTimezoneUtcOffset

 }; // CntClock

}; // GrpOperationalGroup


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
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
//              CONTRIBUTORS 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES,
//              INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//              MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//              DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
//              CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//              SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//              LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
//              USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
//              AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//              LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
//              IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//              THE POSSIBILITY OF SUCH DAMAGE.
//
//              Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following
//              conditions are met:
//
//              * Redistributions of source code must retain the above copyright
//              notice, this list of conditions and the above disclaimer.
//              * Redistributions in binary form must reproduce the above
//              copyright notice, this list of conditions and the above
//              disclaimer in the documentation and/or other materials provided
//              with the distribution.
//              * Neither the Members of the O-RAN Alliance nor the names of its
//              contributors may be used to endorse or promote products derived
//              from this software without specific prior written permission.
// -----------------------------------------------------------------------------
class ModuleORanOperations : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_OPERATIONAL_INFO, // CntOperationalInfo
 };

 ModuleORanOperations(uint32_t id);
 ~ModuleORanOperations();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanOperations_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_OPERATIONS_H_ */
