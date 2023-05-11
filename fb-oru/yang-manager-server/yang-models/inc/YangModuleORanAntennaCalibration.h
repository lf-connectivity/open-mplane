#ifndef _MODULE_O_RAN_ANTENNA_CALIBRATION_H_
#define _MODULE_O_RAN_ANTENNA_CALIBRATION_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanAntennaCalibration.h
 * \brief     Module ORanAntennaCalibration interface
 *
 *
 * \details   This file defines the YANG module o-ran-antenna-calibration interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-antenna-calibration"
 *            YANG Filename:    "o-ran-antenna-calibration.yang"
 *            Module Prefix:    "o-ran-antcal"
 *            Module namespace: "urn:o-ran:antcal:1.0"
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

namespace ModuleORanAntennaCalibration_NS {

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
// Container:   /antenna-calibration
// Description: Describes the antenna calibration top node
// -----------------------------------------------------------------------------
class CntAntennaCalibration : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_ANTENNA_CALIBRATION,  // Use GrpAntennaCalibration
	};

	CntAntennaCalibration(uint32_t id);
	~CntAntennaCalibration();

	YangResult_E initialise(void);

}; // CntAntennaCalibration


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /antenna-calibration-capabilities
// Description: container for collection of leafs for antenna calibration
// -----------------------------------------------------------------------------
class GrpAntennaCalibrationCapabilities : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_SELF_CALIBRATION_SUPPORT,  // LeafSelfCalibrationSupport
		ITEM_NUMBER_OF_CALIBRATION_SYMBOLS_PER_BLOCK_DL,  // LeafNumberOfCalibrationSymbolsPerBlockDl
		ITEM_NUMBER_OF_CALIBRATION_SYMBOLS_PER_BLOCK_UL,  // LeafNumberOfCalibrationSymbolsPerBlockUl
		ITEM_INTERVAL_BETWEEN_CALIBRATION_BLOCKS,  // LeafIntervalBetweenCalibrationBlocks
		ITEM_NUMBER_OF_CALIBRATION_BLOCKS_PER_STEP_DL,  // LeafNumberOfCalibrationBlocksPerStepDl
		ITEM_NUMBER_OF_CALIBRATION_BLOCKS_PER_STEP_UL,  // LeafNumberOfCalibrationBlocksPerStepUl
		ITEM_INTERVAL_BETWEEN_CALIBRATION_STEPS,  // LeafIntervalBetweenCalibrationSteps
		ITEM_NUMBER_OF_CALIBRATION_STEPS,  // LeafNumberOfCalibrationSteps
	};

	GrpAntennaCalibrationCapabilities(uint32_t id);
	~GrpAntennaCalibrationCapabilities();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /antenna-calibration-capabilities/self-calibration-support
	// Description: Indicates whether O-RU supports self-calibration or not.
	//
	//              When true, indicates O-RU can initiate calibration without receiving an
	//              rpc
	// -----------------------------------------------------------------------------
	class LeafSelfCalibrationSupport : public YangLeaf
	{
	public:

		LeafSelfCalibrationSupport(uint32_t id);
		~LeafSelfCalibrationSupport();

	}; // LeafSelfCalibrationSupport

	// -----------------------------------------------------------------------------
	// Leaf:        /antenna-calibration-capabilities/number-of-calibration-symbols-per-block-dl
	// Description: Indicates how many consecutive symbols are required for DL antenna
	//              calibration operation
	// -----------------------------------------------------------------------------
	class LeafNumberOfCalibrationSymbolsPerBlockDl : public YangLeaf
	{
	public:

		LeafNumberOfCalibrationSymbolsPerBlockDl(uint32_t id);
		~LeafNumberOfCalibrationSymbolsPerBlockDl();

	}; // LeafNumberOfCalibrationSymbolsPerBlockDl

	// -----------------------------------------------------------------------------
	// Leaf:        /antenna-calibration-capabilities/number-of-calibration-symbols-per-block-ul
	// Description: Indicates how many consecutive symbols are required for UL antenna
	//              calibration operation
	// -----------------------------------------------------------------------------
	class LeafNumberOfCalibrationSymbolsPerBlockUl : public YangLeaf
	{
	public:

		LeafNumberOfCalibrationSymbolsPerBlockUl(uint32_t id);
		~LeafNumberOfCalibrationSymbolsPerBlockUl();

	}; // LeafNumberOfCalibrationSymbolsPerBlockUl

	// -----------------------------------------------------------------------------
	// Leaf:        /antenna-calibration-capabilities/interval-between-calibration-blocks
	// Description: if time interval is required between consecutive antenna calibration
	//              operation, defines this time value as unit of symbols.
	//
	//              A common value is used here for the intervals
	//              between DL-DL blocks, UL-UL blocks, DL-UL blocks and UL-DL blocks,
	//              which is the largest minimum interval required between any two adjacent
	//              calibration blocks.
	// -----------------------------------------------------------------------------
	class LeafIntervalBetweenCalibrationBlocks : public YangLeaf
	{
	public:

		LeafIntervalBetweenCalibrationBlocks(uint32_t id);
		~LeafIntervalBetweenCalibrationBlocks();

	}; // LeafIntervalBetweenCalibrationBlocks

	// -----------------------------------------------------------------------------
	// Leaf:        /antenna-calibration-capabilities/number-of-calibration-blocks-per-step-dl
	// Description: Indicates how many blocks are required for one step of DL antenna
	//              calibration operation
	// -----------------------------------------------------------------------------
	class LeafNumberOfCalibrationBlocksPerStepDl : public YangLeaf
	{
	public:

		LeafNumberOfCalibrationBlocksPerStepDl(uint32_t id);
		~LeafNumberOfCalibrationBlocksPerStepDl();

	}; // LeafNumberOfCalibrationBlocksPerStepDl

	// -----------------------------------------------------------------------------
	// Leaf:        /antenna-calibration-capabilities/number-of-calibration-blocks-per-step-ul
	// Description: Indicates how many blocks are required for one step of UL antenna
	//              calibration operation
	// -----------------------------------------------------------------------------
	class LeafNumberOfCalibrationBlocksPerStepUl : public YangLeaf
	{
	public:

		LeafNumberOfCalibrationBlocksPerStepUl(uint32_t id);
		~LeafNumberOfCalibrationBlocksPerStepUl();

	}; // LeafNumberOfCalibrationBlocksPerStepUl

	// -----------------------------------------------------------------------------
	// Leaf:        /antenna-calibration-capabilities/interval-between-calibration-steps
	// Description: If time interval is required between consecutive step of antenna
	//              calibration operation, defines this time value as unit of radio frames
	// -----------------------------------------------------------------------------
	class LeafIntervalBetweenCalibrationSteps : public YangLeaf
	{
	public:

		LeafIntervalBetweenCalibrationSteps(uint32_t id);
		~LeafIntervalBetweenCalibrationSteps();

	}; // LeafIntervalBetweenCalibrationSteps

	// -----------------------------------------------------------------------------
	// Leaf:        /antenna-calibration-capabilities/number-of-calibration-steps
	// Description: Indicates how many steps are required for whole DL/UL antenna
	//              calibration operation
	// -----------------------------------------------------------------------------
	class LeafNumberOfCalibrationSteps : public YangLeaf
	{
	public:

		LeafNumberOfCalibrationSteps(uint32_t id);
		~LeafNumberOfCalibrationSteps();

	}; // LeafNumberOfCalibrationSteps

}; // GrpAntennaCalibrationCapabilities

// -----------------------------------------------------------------------------
// Grouping:    /antenna-calibration
// Description: Describe the grouping set of antenna calibration
// -----------------------------------------------------------------------------
class GrpAntennaCalibration : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_ANTENNA_CALIBRATION_CAPABILITIES,  // CntAntennaCalibrationCapabilities
		ITEM_SELF_CALIBRATION_POLICY,  // CntSelfCalibrationPolicy
	};

	GrpAntennaCalibration(uint32_t id);
	~GrpAntennaCalibration();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Container:   /antenna-calibration/antenna-calibration-capabilities
	// Description: Describes the antenna calibration capabilities
	// -----------------------------------------------------------------------------
	class CntAntennaCalibrationCapabilities : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_ANTENNA_CALIBRATION_CAPABILITIES,  // Use GrpAntennaCalibrationCapabilities
		};

		CntAntennaCalibrationCapabilities(uint32_t id);
		~CntAntennaCalibrationCapabilities();

		YangResult_E initialise(void);

	}; // CntAntennaCalibrationCapabilities

	// -----------------------------------------------------------------------------
	// Container:   /antenna-calibration/self-calibration-policy
	// Description: Describes the self calibration policy of the operator
	// -----------------------------------------------------------------------------
	class CntSelfCalibrationPolicy : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_SELF_CALIBRATION_ALLOWED,  // LeafSelfCalibrationAllowed
		};

		CntSelfCalibrationPolicy(uint32_t id);
		~CntSelfCalibrationPolicy();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /antenna-calibration/self-calibration-policy/self-calibration-allowed
		// Description: whether the self-calibration is allowed configured by operator.
		// -----------------------------------------------------------------------------
		class LeafSelfCalibrationAllowed : public YangLeaf
		{
		public:

			LeafSelfCalibrationAllowed(uint32_t id);
			~LeafSelfCalibrationAllowed();

		}; // LeafSelfCalibrationAllowed

	}; // CntSelfCalibrationPolicy

}; // GrpAntennaCalibration


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
// Notification:/antenna-calibration-required
// Description: this notification indicates that the antenna calibration is required in O-RU
// -----------------------------------------------------------------------------
class NotifAntennaCalibrationRequired : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_DL_CALIBRATION_FREQUENCY_CHUNK,  // LstDlCalibrationFrequencyChunk
		ITEM_UL_CALIBRATION_FREQUENCY_CHUNK,  // LstUlCalibrationFrequencyChunk
	};

	NotifAntennaCalibrationRequired(uint32_t id);
	~NotifAntennaCalibrationRequired();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /antenna-calibration-required/dl-calibration-frequency-chunk
	// Description: min/max frequency of dl spectrum chunk affected by calibration process
	// -----------------------------------------------------------------------------
	class LstDlCalibrationFrequencyChunk : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_START_CALIBRATION_FREQUENCY_DL,  // LeafStartCalibrationFrequencyDl
			ITEM_END_CALIBRATION_FREQUENCY_DL,  // LeafEndCalibrationFrequencyDl
		};

		LstDlCalibrationFrequencyChunk(uint32_t id);
		~LstDlCalibrationFrequencyChunk();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /antenna-calibration-required/dl-calibration-frequency-chunk/start-calibration-frequency-dl
		// Description: lowest frequency value in Hz of the frequency range is required for
		//              DL antenna calibration operation.
		// -----------------------------------------------------------------------------
		class LeafStartCalibrationFrequencyDl : public YangLeaf
		{
		public:

			LeafStartCalibrationFrequencyDl(uint32_t id);
			~LeafStartCalibrationFrequencyDl();

		}; // LeafStartCalibrationFrequencyDl

		// -----------------------------------------------------------------------------
		// Leaf:        /antenna-calibration-required/dl-calibration-frequency-chunk/end-calibration-frequency-dl
		// Description: highest frequency value in Hz of the frequency range is required for
		//              DL antenna calibration operation.
		// -----------------------------------------------------------------------------
		class LeafEndCalibrationFrequencyDl : public YangLeaf
		{
		public:

			LeafEndCalibrationFrequencyDl(uint32_t id);
			~LeafEndCalibrationFrequencyDl();

		}; // LeafEndCalibrationFrequencyDl

	}; // LstDlCalibrationFrequencyChunk

	// -----------------------------------------------------------------------------
	// List:        /antenna-calibration-required/ul-calibration-frequency-chunk
	// Description: min/max frequency of ul spectrum chunk affected by calibration process
	// -----------------------------------------------------------------------------
	class LstUlCalibrationFrequencyChunk : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_START_CALIBRATION_FREQUENCY_UL,  // LeafStartCalibrationFrequencyUl
			ITEM_END_CALIBRATION_FREQUENCY_UL,  // LeafEndCalibrationFrequencyUl
		};

		LstUlCalibrationFrequencyChunk(uint32_t id);
		~LstUlCalibrationFrequencyChunk();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /antenna-calibration-required/ul-calibration-frequency-chunk/start-calibration-frequency-ul
		// Description: lowest frequency value in Hz of the frequency range is required for
		//              UL antenna calibration operation.
		// -----------------------------------------------------------------------------
		class LeafStartCalibrationFrequencyUl : public YangLeaf
		{
		public:

			LeafStartCalibrationFrequencyUl(uint32_t id);
			~LeafStartCalibrationFrequencyUl();

		}; // LeafStartCalibrationFrequencyUl

		// -----------------------------------------------------------------------------
		// Leaf:        /antenna-calibration-required/ul-calibration-frequency-chunk/end-calibration-frequency-ul
		// Description: highest frequency value in Hz of the frequency range is required for
		//              UL antenna calibration operation.
		// -----------------------------------------------------------------------------
		class LeafEndCalibrationFrequencyUl : public YangLeaf
		{
		public:

			LeafEndCalibrationFrequencyUl(uint32_t id);
			~LeafEndCalibrationFrequencyUl();

		}; // LeafEndCalibrationFrequencyUl

	}; // LstUlCalibrationFrequencyChunk

}; // NotifAntennaCalibrationRequired

// -----------------------------------------------------------------------------
// Notification:/antenna-calibration-result
// Description: This notification indicates the antenna calibration result
// -----------------------------------------------------------------------------
class NotifAntennaCalibrationResult : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_STATUS,  // LeafStatus
		ITEM_DETAILED_REASON,  // LeafDetailedReason
	};

	NotifAntennaCalibrationResult(uint32_t id);
	~NotifAntennaCalibrationResult();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /antenna-calibration-result/status
	// Description: Status of the antenna calibration procedure which has been triggered
	//              by accepting an start-antenna-calibration RPC.
	// -----------------------------------------------------------------------------
	class LeafStatus : public YangLeaf
	{
	public:

		// Status of the antenna calibration procedure which has been triggered
		// by accepting an start-antenna-calibration RPC.
		enum class Status_E : uint32_t
		{
			SUCCESS,	// O-RU has succeeded in calibrating its antenna
			FAILURE,	// O-RU attemted to calibrate its antenna, but the procedure failed.

			Num_Status_E
		};

		LeafStatus(uint32_t id);
		~LeafStatus();

	}; // LeafStatus

	// -----------------------------------------------------------------------------
	// Leaf:        /antenna-calibration-result/detailed-reason
	// Description: Detailed reason when the status is FAILURE, e.g.,
	//              O-RU cannot complete the antenna calibration
	//              because of lack of memory, self-calibration failure, etc
	// -----------------------------------------------------------------------------
	class LeafDetailedReason : public YangLeaf
	{
	public:

		LeafDetailedReason(uint32_t id);
		~LeafDetailedReason();

	}; // LeafDetailedReason

}; // NotifAntennaCalibrationResult


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-antenna-calibration
// Description: This module defines the configuration required for supporting the optional
//              antenna calibration functionality.
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
class ModuleORanAntennaCalibration : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_ANTENNA_CALIBRATION,  // CntAntennaCalibration
		ITEM_ANTENNA_CALIBRATION_REQUIRED,  // NotifAntennaCalibrationRequired
		ITEM_ANTENNA_CALIBRATION_RESULT,  // NotifAntennaCalibrationResult
	};

	ModuleORanAntennaCalibration(uint32_t id);
	~ModuleORanAntennaCalibration();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanAntennaCalibration_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_ANTENNA_CALIBRATION_H_ */
