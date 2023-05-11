#ifndef _MODULE_O_RAN_FAN_H_
#define _MODULE_O_RAN_FAN_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanFan.h
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


namespace Mplane {

namespace ModuleORanFan_NS {

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
// Container:   /fan-tray
// Description: top level tree covering off operational state of the fans
// -----------------------------------------------------------------------------
class CntFanTray : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_FAN_GROUPING,  // Use GrpFanGrouping
	};

	CntFanTray(uint32_t id);
	~CntFanTray();

	YangResult_E initialise(void);

}; // CntFanTray


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /fan-grouping
// Description:
// -----------------------------------------------------------------------------
class GrpFanGrouping : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_FAN_STATE,  // LstFanState
	};

	GrpFanGrouping(uint32_t id);
	~GrpFanGrouping();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /fan-grouping/fan-state
	// Description: a list of the fans based on their unique names
	// -----------------------------------------------------------------------------
	class LstFanState : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_NAME,  // LeafName
			ITEM_FAN_LOCATION,  // LeafFanLocation
			ITEM_PRESENT_AND_OPERATING,  // LeafPresentAndOperating
			ITEM_VENDOR_CODE,  // LeafVendorCode
			ITEM_FAN_SPEED,  // LeafFanSpeed
			ITEM_TARGET_SPEED,  // LeafTargetSpeed
		};

		LstFanState(uint32_t id);
		~LstFanState();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /fan-grouping/fan-state/name
		// Description: A name that is unique that identifies a fan instance.
		//              This name may be used in fault management to refer to a fault source
		//              or affected object
		// -----------------------------------------------------------------------------
		class LeafName : public YangLeaf
		{
		public:

			LeafName(uint32_t id);
			~LeafName();

		}; // LeafName

		// -----------------------------------------------------------------------------
		// Leaf:        /fan-grouping/fan-state/fan-location
		// Description: A number indicating the location of the FAN in the fan tray
		// -----------------------------------------------------------------------------
		class LeafFanLocation : public YangLeaf
		{
		public:

			LeafFanLocation(uint32_t id);
			~LeafFanLocation();

		}; // LeafFanLocation

		// -----------------------------------------------------------------------------
		// Leaf:        /fan-grouping/fan-state/present-and-operating
		// Description: Indicates if a fan is present and operating in the location
		// -----------------------------------------------------------------------------
		class LeafPresentAndOperating : public YangLeaf
		{
		public:

			LeafPresentAndOperating(uint32_t id);
			~LeafPresentAndOperating();

		}; // LeafPresentAndOperating

		// -----------------------------------------------------------------------------
		// Leaf:        /fan-grouping/fan-state/vendor-code
		// Description: Indicates fan vendor code. Fan vendors are detected with ID pins
		//              using 3 bits digital inputs.
		//
		//              Optional node included when the NETCONF Server has determined
		//              the fan vendor code.
		// -----------------------------------------------------------------------------
		class LeafVendorCode : public YangLeaf
		{
		public:

			LeafVendorCode(uint32_t id);
			~LeafVendorCode();

		}; // LeafVendorCode

		// -----------------------------------------------------------------------------
		// Leaf:        /fan-grouping/fan-state/fan-speed
		// Description: Measured fan speed. Expressed as percentage of max fan speed.
		//
		//              Optional node included when the fan speed can be measured.
		// -----------------------------------------------------------------------------
		class LeafFanSpeed : public YangLeaf
		{
		public:

			LeafFanSpeed(uint32_t id);
			~LeafFanSpeed();

		}; // LeafFanSpeed

		// -----------------------------------------------------------------------------
		// Leaf:        /fan-grouping/fan-state/target-speed
		// Description: the target speed of the fan
		// -----------------------------------------------------------------------------
		class LeafTargetSpeed : public YangLeaf
		{
		public:

			LeafTargetSpeed(uint32_t id);
			~LeafTargetSpeed();

		}; // LeafTargetSpeed

	}; // LstFanState

}; // GrpFanGrouping


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
class ModuleORanFan : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_FAN_TRAY,  // CntFanTray
	};

	ModuleORanFan(uint32_t id);
	~ModuleORanFan();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanFan_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_FAN_H_ */
