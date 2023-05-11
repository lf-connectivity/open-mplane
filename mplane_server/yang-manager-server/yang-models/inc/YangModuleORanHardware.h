#ifndef _MODULE_O_RAN_HARDWARE_H_
#define _MODULE_O_RAN_HARDWARE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanHardware.h
 * \brief     Module ORanHardware interface
 *
 *
 * \details   This file defines the YANG module o-ran-hardware interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-hardware"
 *            YANG Filename:    "o-ran-hardware.yang"
 *            Module Prefix:    "o-ran-hw"
 *            Module namespace: "urn:o-ran:hardware:1.0"
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

// Module:   ietf-hardware
// Revision:
// Notes:
#include "YangModuleIetfHardware.h"

// Module:   iana-hardware
// Revision:
// Notes:
#include "YangModuleIanaHardware.h"


namespace Mplane {

namespace ModuleORanHardware_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// new typedef since ietf-hardware only covers pwer-state
// for redundancy purposes and not power saving operations.
enum class EnergysavingState_E : uint32_t {
  UNKNOWN, // The Radio Unit is unable to report energy saving state.
  SLEEPING, // The Radio Unit is in a sleep state. The NETCONF management plane
            // connection is functioning. Other functions and hardware which are
            // not needed for management plane may be in energy saving mode.
  AWAKE, // The Radio Unit is not in an energy saving state.

  Num_EnergysavingState_E
};

// Equipment's availability-state is derived by matching active faults
// and their impact to module's operation and enables an equipment to indicate
// that even though it may have one or more critical alarms, it can continue
// to serve traffic.
enum class AvailabilityType_E : uint32_t {
  UNKNOWN, // The Radio Unit is unable to report its availability state.
  NORMAL, // The equipment is functioning correctly.
  DEGRADED, // The equipment may be reporting a major alarm or may be reporting
            // a critical alarm that is only impacting one or more subcomponent,
            // but where the equipment's implementation permit it to continue
            // operation (server traffic) in a degraded state.
            //
            // Used for example, when the equipment has M identical
            // sub-components and when a critical alarm is imapcting only N
            // subcomponents, where N<M.
  FAULTY, // The (sub-)components impacted by the critical alarm(s) impact the
          // ability of the equipment to continue operation (serve traffic).

  Num_AvailabilityType_E
};

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: Indicates that the Radio Unit supports energy saving state.
// -----------------------------------------------------------------------------
class FeatureENERGYSAVING : public YangFeature
{
public:
 FeatureENERGYSAVING(uint32_t id);
 ~FeatureENERGYSAVING();

}; // FeatureENERGYSAVING


// *****************************************************************************
// Leafs
// *****************************************************************************

// *****************************************************************************
// References
// *****************************************************************************

// *****************************************************************************
// Containers
// *****************************************************************************

// *****************************************************************************
// Groupings
// *****************************************************************************


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
// Module:      o-ran-hardware
// Description: This module defines the YANG definitions for managng the O-RAN
// hardware.
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
class ModuleORanHardware : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ENERGYSAVING, // Feature
 };

 ModuleORanHardware(uint32_t id);
 ~ModuleORanHardware();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanHardware_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_HARDWARE_H_ */
