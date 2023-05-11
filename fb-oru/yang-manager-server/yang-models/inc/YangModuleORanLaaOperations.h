#ifndef _MODULE_O_RAN_LAA_OPERATIONS_H_
#define _MODULE_O_RAN_LAA_OPERATIONS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanLaaOperations.h
 * \brief     Module ORanLaaOperations interface
 *
 *
 * \details   This file defines the YANG module o-ran-laa-operations interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-laa-operations"
 *            YANG Filename:    "o-ran-laa-operations.yang"
 *            Module Prefix:    "o-ran-laa-operations"
 *            Module namespace: "urn:o-ran:laa-operations:1.0"
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
// Revision:
// Notes:
#include "YangModuleORanModuleCap.h"


namespace Mplane {

namespace ModuleORanLaaOperations_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// This value indicates the list of bands supported as per the document,
// 3GPP TS 36.104 V14.2.0 (2016-12), 'Section 5.5 Operation bands'.
enum class BandNum_E : uint32_t
{
	BAND_46_SUBBAND_A,	// 46a: 5150 MHz 	-	5250 MHz
	BAND_46_SUBBAND_B,	// 46b: 5250 MHz 	-	5350 MHz
	BAND_46_SUBBAND_C,	// 46c: 5470 MHz 	-	5725 MHz
	BAND_46_SUBBAND_D1,	// 46d1: 5725 MHz 	-	5850 MHz
	BAND_46_SUBBAND_D2,	// 46d2: 5850 MHz 	-	5925 MHz

	Num_BandNum_E
};


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

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /band-configuration
// Description: Grouping for band configuration
// -----------------------------------------------------------------------------
class GrpBandConfiguration : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_BAND_NUMBER,  // LeafBandNumber
		ITEM_CHANNEL_CENTER_FREQUENCY,  // LstChannelCenterFrequency
	};

	GrpBandConfiguration(uint32_t id);
	~GrpBandConfiguration();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /band-configuration/band-number
	// Description: This value indicates the list of bands supported as per the document,
	//              3GPP TS 36.104 V14.2.0 (2016-12), 'Section 5.5 Operation bands'.
	// -----------------------------------------------------------------------------
	class LeafBandNumber : public YangLeaf
	{
	public:

		// This value indicates the list of bands supported as per the document,
		// 3GPP TS 36.104 V14.2.0 (2016-12), 'Section 5.5 Operation bands'.
		enum class BandNumber_E : uint32_t
		{

			Num_BandNumber_E
		};

		LeafBandNumber(uint32_t id);
		~LeafBandNumber();

	}; // LeafBandNumber

	// -----------------------------------------------------------------------------
	// List:        /band-configuration/channel-center-frequency
	// Description: This value indicates carrier center frequency in KHz
	// -----------------------------------------------------------------------------
	class LstChannelCenterFrequency : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
		};

		LstChannelCenterFrequency(uint32_t id);
		~LstChannelCenterFrequency();

		YangResult_E initialise(void);

	}; // LstChannelCenterFrequency

}; // GrpBandConfiguration

// -----------------------------------------------------------------------------
// Grouping:    /measurement-parameters
// Description: Grouping for measurement parameters
// -----------------------------------------------------------------------------
class GrpMeasurementParameters : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_DURATION_PER_CHANNEL,  // LeafDurationPerChannel
		ITEM_MAXIMUM_RESPONSE_TIME,  // LeafMaximumResponseTime
	};

	GrpMeasurementParameters(uint32_t id);
	~GrpMeasurementParameters();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /measurement-parameters/duration-per-channel
	// Description: This value indicates measurement duration per channel in milliseconds.
	// -----------------------------------------------------------------------------
	class LeafDurationPerChannel : public YangLeaf
	{
	public:

		LeafDurationPerChannel(uint32_t id);
		~LeafDurationPerChannel();

	}; // LeafDurationPerChannel

	// -----------------------------------------------------------------------------
	// Leaf:        /measurement-parameters/maximum-response-time
	// Description: This value indicates maximum response time (i.e., timer) in seconds.
	// -----------------------------------------------------------------------------
	class LeafMaximumResponseTime : public YangLeaf
	{
	public:

		LeafMaximumResponseTime(uint32_t id);
		~LeafMaximumResponseTime();

	}; // LeafMaximumResponseTime

}; // GrpMeasurementParameters

// -----------------------------------------------------------------------------
// Grouping:    /channel-result-element
// Description: Grouping for channel result element
// -----------------------------------------------------------------------------
class GrpChannelResultElement : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MEASURED_CHANNEL,  // LeafMeasuredChannel
		ITEM_OCCUPANCY_RATIO,  // LeafOccupancyRatio
		ITEM_AVERAGE_RSSI,  // LeafAverageRssi
	};

	GrpChannelResultElement(uint32_t id);
	~GrpChannelResultElement();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /channel-result-element/measured-channel
	// Description: This value indicates carrier center frequency for which the result is computed in KHz.
	// -----------------------------------------------------------------------------
	class LeafMeasuredChannel : public YangLeaf
	{
	public:

		LeafMeasuredChannel(uint32_t id);
		~LeafMeasuredChannel();

	}; // LeafMeasuredChannel

	// -----------------------------------------------------------------------------
	// Leaf:        /channel-result-element/occupancy-ratio
	// Description: This value indicates occupancy ratio in percentage.
	// -----------------------------------------------------------------------------
	class LeafOccupancyRatio : public YangLeaf
	{
	public:

		LeafOccupancyRatio(uint32_t id);
		~LeafOccupancyRatio();

	}; // LeafOccupancyRatio

	// -----------------------------------------------------------------------------
	// Leaf:        /channel-result-element/average-rssi
	// Description: This value indicates average RSSI in dBm
	// -----------------------------------------------------------------------------
	class LeafAverageRssi : public YangLeaf
	{
	public:

		LeafAverageRssi(uint32_t id);
		~LeafAverageRssi();

	}; // LeafAverageRssi

}; // GrpChannelResultElement

// -----------------------------------------------------------------------------
// Grouping:    /band-result-element
// Description: Grouping for band result element
// -----------------------------------------------------------------------------
class GrpBandResultElement : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_BAND_NUMBER,  // LeafBandNumber
		ITEM_MEASUREMENT_SUCCESS,  // LeafMeasurementSuccess
		ITEM_FAILURE_MESSAGE,  // LeafFailureMessage
		ITEM_CHANNEL_RESULT,  // LstChannelResult
	};

	GrpBandResultElement(uint32_t id);
	~GrpBandResultElement();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /band-result-element/band-number
	// Description: This value indicates the band for which the result is computed.
	// -----------------------------------------------------------------------------
	class LeafBandNumber : public YangLeaf
	{
	public:

		// This value indicates the band for which the result is computed.
		enum class BandNumber_E : uint32_t
		{

			Num_BandNumber_E
		};

		LeafBandNumber(uint32_t id);
		~LeafBandNumber();

	}; // LeafBandNumber

	// -----------------------------------------------------------------------------
	// Leaf:        /band-result-element/measurement-success
	// Description: This value indicates whether the measurement is successful for the given band.
	// -----------------------------------------------------------------------------
	class LeafMeasurementSuccess : public YangLeaf
	{
	public:

		LeafMeasurementSuccess(uint32_t id);
		~LeafMeasurementSuccess();

	}; // LeafMeasurementSuccess

	// -----------------------------------------------------------------------------
	// Leaf:        /band-result-element/failure-message
	// Description: This value indicates the detailed error message for failure of the measurement at O-RU.
	// -----------------------------------------------------------------------------
	class LeafFailureMessage : public YangLeaf
	{
	public:

		// This value indicates the detailed error message for failure of the measurement at O-RU.
		enum class FailureMessage_E : uint32_t
		{
			TIMEOUT,	// Timed out waiting for measurement completion.

			Num_FailureMessage_E
		};

		LeafFailureMessage(uint32_t id);
		~LeafFailureMessage();

	}; // LeafFailureMessage

	// -----------------------------------------------------------------------------
	// List:        /band-result-element/channel-result
	// Description: Results for a particular channel
	// -----------------------------------------------------------------------------
	class LstChannelResult : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_CHANNEL_RESULT_ELEMENT,  // Use GrpChannelResultElement
		};

		LstChannelResult(uint32_t id);
		~LstChannelResult();

		YangResult_E initialise(void);

	}; // LstChannelResult

}; // GrpBandResultElement


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
// Notification:/measurement-result
// Description: Notification to provide the results of carrier selection and DFS.
// -----------------------------------------------------------------------------
class NotifMeasurementResult : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_BAND_RESULT,  // LstBandResult
	};

	NotifMeasurementResult(uint32_t id);
	~NotifMeasurementResult();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /measurement-result/band-result
	// Description: Results for a particular sub band under band 46.
	// -----------------------------------------------------------------------------
	class LstBandResult : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_BAND_RESULT_ELEMENT,  // Use GrpBandResultElement
		};

		LstBandResult(uint32_t id);
		~LstBandResult();

		YangResult_E initialise(void);

	}; // LstBandResult

}; // NotifMeasurementResult


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-laa-operations
// Description: This module defines the operations for DFS measurement.
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
class ModuleORanLaaOperations : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MEASUREMENT_RESULT,  // NotifMeasurementResult
	};

	ModuleORanLaaOperations(uint32_t id);
	~ModuleORanLaaOperations();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanLaaOperations_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_LAA_OPERATIONS_H_ */
