/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanFan.cpp
 * \brief     Module ORanFan interface
 *
 *
 * \details   This file defines the YANG module o-ran-fan interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-fan"
 *            YANG Filename:    "o-ran-fan.yang"
 *            Module Prefix:    "o-ran-fan"
 *            Module namespace: "urn:o-ran:fan:1.0"
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
#include "YangModuleORanFan.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleORanFan_NS;

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
// Container:   fan-tray
// Description: top level tree covering off operational state of the fans
// -----------------------------------------------------------------------------
CntFanTray::CntFanTray(uint32_t id)
	: YangContainer("fan-tray", id)
{
}

CntFanTray::~CntFanTray()
{
}

YangResult_E CntFanTray::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /fan-tray/fan-grouping
	// Description:
	// -----------------------------------------------------------------------------
	GrpFanGrouping fanGroupingInst(ITEM_FAN_GROUPING);
	fanGroupingInst.initialise();
	addGroup(fanGroupingInst);



	return YangResult_E::OK;
}





// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    fan-grouping
// Description:
// -----------------------------------------------------------------------------
GrpFanGrouping::GrpFanGrouping(uint32_t id)
	: YangGroup("fan-grouping", id)
{
}

GrpFanGrouping::~GrpFanGrouping()
{
}

YangResult_E GrpFanGrouping::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /fan-grouping/fan-state
	// Description: a list of the fans based on their unique names
	// Array Key:
	// -----------------------------------------------------------------------------
	LstFanState fanStateInst(ITEM_FAN_STATE);
	fanStateInst.initialise();
	addList(fanStateInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        fan-state
// Description: a list of the fans based on their unique names
// -----------------------------------------------------------------------------
GrpFanGrouping::LstFanState::LstFanState(uint32_t id)
	: YangList("fan-state", id)
{
}

GrpFanGrouping::LstFanState::~LstFanState()
{
}

YangResult_E GrpFanGrouping::LstFanState::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /fan-grouping/fan-state/name
	// Description: A name that is unique that identifies a fan instance.
	//              This name may be used in fault management to refer to a fault source
	//              or affected object
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /fan-grouping/fan-state/fan-location
	// Description: A number indicating the location of the FAN in the fan tray
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafFanLocation fanLocationInst(ITEM_FAN_LOCATION);
	addLeaf(fanLocationInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /fan-grouping/fan-state/present-and-operating
	// Description: Indicates if a fan is present and operating in the location
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafPresentAndOperating presentAndOperatingInst(ITEM_PRESENT_AND_OPERATING);
	addLeaf(presentAndOperatingInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /fan-grouping/fan-state/vendor-code
	// Description: Indicates fan vendor code. Fan vendors are detected with ID pins
	//              using 3 bits digital inputs.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the fan vendor code.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafVendorCode vendorCodeInst(ITEM_VENDOR_CODE);
	addLeaf(vendorCodeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /fan-grouping/fan-state/fan-speed
	// Description: Measured fan speed. Expressed as percentage of max fan speed.
	//
	//              Optional node included when the fan speed can be measured.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafFanSpeed fanSpeedInst(ITEM_FAN_SPEED);
	addLeaf(fanSpeedInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /fan-grouping/fan-state/target-speed
	// Description: the target speed of the fan
	// Type:        uint16
	// Units:       rpm
	// -----------------------------------------------------------------------------
	LeafTargetSpeed targetSpeedInst(ITEM_TARGET_SPEED);
	addLeaf(targetSpeedInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /fan-grouping/fan-state/name
// Description: A name that is unique that identifies a fan instance.
//              This name may be used in fault management to refer to a fault source
//              or affected object
// -----------------------------------------------------------------------------
GrpFanGrouping::LstFanState::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpFanGrouping::LstFanState::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /fan-grouping/fan-state/fan-location
// Description: A number indicating the location of the FAN in the fan tray
// -----------------------------------------------------------------------------
GrpFanGrouping::LstFanState::LeafFanLocation::LeafFanLocation(uint32_t id)
	: YangLeaf("fan-location", id)
{
}

GrpFanGrouping::LstFanState::LeafFanLocation::~LeafFanLocation()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /fan-grouping/fan-state/present-and-operating
// Description: Indicates if a fan is present and operating in the location
// -----------------------------------------------------------------------------
GrpFanGrouping::LstFanState::LeafPresentAndOperating::LeafPresentAndOperating(uint32_t id)
	: YangLeaf("present-and-operating", id)
{
}

GrpFanGrouping::LstFanState::LeafPresentAndOperating::~LeafPresentAndOperating()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /fan-grouping/fan-state/vendor-code
// Description: Indicates fan vendor code. Fan vendors are detected with ID pins
//              using 3 bits digital inputs.
//
//              Optional node included when the NETCONF Server has determined
//              the fan vendor code.
// -----------------------------------------------------------------------------
GrpFanGrouping::LstFanState::LeafVendorCode::LeafVendorCode(uint32_t id)
	: YangLeaf("vendor-code", id)
{
}

GrpFanGrouping::LstFanState::LeafVendorCode::~LeafVendorCode()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /fan-grouping/fan-state/fan-speed
// Description: Measured fan speed. Expressed as percentage of max fan speed.
//
//              Optional node included when the fan speed can be measured.
// -----------------------------------------------------------------------------
GrpFanGrouping::LstFanState::LeafFanSpeed::LeafFanSpeed(uint32_t id)
	: YangLeaf("fan-speed", id)
{
}

GrpFanGrouping::LstFanState::LeafFanSpeed::~LeafFanSpeed()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /fan-grouping/fan-state/target-speed
// Description: the target speed of the fan
// -----------------------------------------------------------------------------
GrpFanGrouping::LstFanState::LeafTargetSpeed::LeafTargetSpeed(uint32_t id)
	: YangLeaf("target-speed", id)
{
}

GrpFanGrouping::LstFanState::LeafTargetSpeed::~LeafTargetSpeed()
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
// Module:      o-ran-fan
// Description: This module defines the state of the O-RAN equipment's fans.
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
ModuleORanFan::ModuleORanFan(uint32_t id)
	: YangModule ("o-ran-fan",
	              "o-ran-fan.yang",
	              "o-ran-fan",
	              "urn:o-ran:fan:1.0",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Container:   /fan-tray
	// Description: top level tree covering off operational state of the fans
	// -----------------------------------------------------------------------------
	CntFanTray fanTrayInst(ITEM_FAN_TRAY);
	fanTrayInst.initialise();
	addContainer(fanTrayInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleORanFan::~ModuleORanFan()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleORanFan::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleORanFan>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleORanFan::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
