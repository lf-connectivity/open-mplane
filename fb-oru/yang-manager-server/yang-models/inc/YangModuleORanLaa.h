#ifndef _MODULE_O_RAN_LAA_H_
#define _MODULE_O_RAN_LAA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanLaa.h
 * \brief     Module ORanLaa interface
 *
 *
 * \details   This file defines the YANG module o-ran-laa interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-laa"
 *            YANG Filename:    "o-ran-laa.yang"
 *            Module Prefix:    "o-ran-laa"
 *            Module namespace: "urn:o-ran:laa:1.0"
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

// Module:   o-ran-module-cap
// Revision: 2019-07-03
// Notes:
#include "YangModuleORanModuleCap.h"


namespace Mplane {

namespace ModuleORanLaa_NS {

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
// Container:   /laa-config
// Description: Container to specify all LAA specific configuration
// -----------------------------------------------------------------------------
class CntLaaConfig : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_LAA_CONFIGURATION,  // Use GrpLaaConfiguration
	};

	CntLaaConfig(uint32_t id);
	~CntLaaConfig();

	YangResult_E initialise(void);

}; // CntLaaConfig


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /laa-configuration
// Description: Grouping for LAA configuration
// -----------------------------------------------------------------------------
class GrpLaaConfiguration : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_NUMBER_OF_LAA_SCARRIERS,  // LeafNumberOfLaaScarriers
		ITEM_MULTI_CARRIER_TYPE,  // LeafMultiCarrierType
		ITEM_MULTI_CARRIER_TX,  // LeafMultiCarrierTx
		ITEM_MULTI_CARRIER_FREEZE,  // LeafMultiCarrierFreeze
		ITEM_LAA_ENDING_DWPTS_SUPPORTED,  // LeafLaaEndingDwptsSupported
		ITEM_LAA_STARTING_IN_SECOND_SLOT_SUPPORTED,  // LeafLaaStartingInSecondSlotSupported
	};

	GrpLaaConfiguration(uint32_t id);
	~GrpLaaConfiguration();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-configuration/number-of-laa-scarriers
	// Description: Number of LAA secondary carriers to be supported at O-RU.
	// -----------------------------------------------------------------------------
	class LeafNumberOfLaaScarriers : public YangLeaf
	{
	public:

		LeafNumberOfLaaScarriers(uint32_t id);
		~LeafNumberOfLaaScarriers();

	}; // LeafNumberOfLaaScarriers

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-configuration/multi-carrier-type
	// Description: This value indicates the list of multi carrier types which as per the document,
	//              3GPP TS 36.213 V13.6.0 (2017-06) 15.1.5 Channel access procedure for transmission(s) on multiple carriers.
	// -----------------------------------------------------------------------------
	class LeafMultiCarrierType : public YangLeaf
	{
	public:

		// This value indicates the list of multi carrier types which as per the document,
		// 3GPP TS 36.213 V13.6.0 (2017-06) 15.1.5 Channel access procedure for transmission(s) on multiple carriers.
		enum class MultiCarrierType_E : uint32_t
		{
			A1,	//
			A2,	//
			B1,	//
			B2,	//

			Num_MultiCarrierType_E
		};

		LeafMultiCarrierType(uint32_t id);
		~LeafMultiCarrierType();

	}; // LeafMultiCarrierType

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-configuration/multi-carrier-tx
	// Description: This value indicates whether self-deferral is activated or not.
	// -----------------------------------------------------------------------------
	class LeafMultiCarrierTx : public YangLeaf
	{
	public:

		LeafMultiCarrierTx(uint32_t id);
		~LeafMultiCarrierTx();

	}; // LeafMultiCarrierTx

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-configuration/multi-carrier-freeze
	// Description: This value indicates if the absence of other technology in the unlicensed band can be guaranteed.
	// -----------------------------------------------------------------------------
	class LeafMultiCarrierFreeze : public YangLeaf
	{
	public:

		LeafMultiCarrierFreeze(uint32_t id);
		~LeafMultiCarrierFreeze();

	}; // LeafMultiCarrierFreeze

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-configuration/laa-ending-dwpts-supported
	// Description: This value indicates whether LAA ending in DwPTS is supported.
	// -----------------------------------------------------------------------------
	class LeafLaaEndingDwptsSupported : public YangLeaf
	{
	public:

		LeafLaaEndingDwptsSupported(uint32_t id);
		~LeafLaaEndingDwptsSupported();

	}; // LeafLaaEndingDwptsSupported

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-configuration/laa-starting-in-second-slot-supported
	// Description: This value indicates whether LAA starting in second slot is supported
	// -----------------------------------------------------------------------------
	class LeafLaaStartingInSecondSlotSupported : public YangLeaf
	{
	public:

		LeafLaaStartingInSecondSlotSupported(uint32_t id);
		~LeafLaaStartingInSecondSlotSupported();

	}; // LeafLaaStartingInSecondSlotSupported

}; // GrpLaaConfiguration


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
// Module:      o-ran-laa
// Description: This module defines the configuration for Carrier-selection and dynamic frequency selection (DFS).
//              Also this module defines operations for DFS measurement.
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
class ModuleORanLaa : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_LAA_CONFIG,  // CntLaaConfig
	};

	ModuleORanLaa(uint32_t id);
	~ModuleORanLaa();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanLaa_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_LAA_H_ */
