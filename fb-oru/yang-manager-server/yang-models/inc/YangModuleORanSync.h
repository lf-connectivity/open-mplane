#ifndef _MODULE_O_RAN_SYNC_H_
#define _MODULE_O_RAN_SYNC_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanSync.h
 * \brief     Module ORanSync interface
 *
 *
 * \details   This file defines the YANG module o-ran-sync interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-sync"
 *            YANG Filename:    "o-ran-sync.yang"
 *            Module Prefix:    "o-ran-sync"
 *            Module namespace: "urn:o-ran:sync:1.0"
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

// Module:   ietf-interfaces
// Revision:
// Notes:
#include "YangModuleIetfInterfaces.h"

// Module:   o-ran-interfaces
// Revision:
// Notes:
#include "YangModuleORanInterfaces.h"


namespace Mplane {

namespace ModuleORanSync_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************


// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the equipment supports integrated GNSS functionality.
// -----------------------------------------------------------------------------
class FeatureGNSS : public YangFeature
{
public:
	FeatureGNSS(uint32_t id);
	~FeatureGNSS();

}; // FeatureGNSS

// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the equipment supports Anti-jam fuctionality
// -----------------------------------------------------------------------------
class FeatureANTIJAM : public YangFeature
{
public:
	FeatureANTIJAM(uint32_t id);
	~FeatureANTIJAM();

}; // FeatureANTIJAM


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
// Container:   /sync
// Description: Main containter for sync related parameters
// -----------------------------------------------------------------------------
class CntSync : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_SYNC_GROUP,  // Use GrpSyncGroup
	};

	CntSync(uint32_t id);
	~CntSync();

	YangResult_E initialise(void);

}; // CntSync


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /sync-group
// Description:
// -----------------------------------------------------------------------------
class GrpSyncGroup : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_SYNC_STATUS,  // CntSyncStatus
		ITEM_SYNC_CAPABILITY,  // CntSyncCapability
		ITEM_PTP_CONFIG,  // CntPtpConfig
		ITEM_PTP_STATUS,  // CntPtpStatus
		ITEM_SYNCE_CONFIG,  // CntSynceConfig
		ITEM_SYNCE_STATUS,  // CntSynceStatus
		ITEM_GNSS_CONFIG,  // CntGnssConfig
		ITEM_GNSS_STATUS,  // CntGnssStatus
	};

	GrpSyncGroup(uint32_t id);
	~GrpSyncGroup();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/sync-status
	// Description: Object of this class provides synchronization state of the module.
	// -----------------------------------------------------------------------------
	class CntSyncStatus : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_SYNC_STATE,  // LeafSyncState
			ITEM_SUPPORTED_REFERENCE_TYPES,  // LstSupportedReferenceTypes
		};

		CntSyncStatus(uint32_t id);
		~CntSyncStatus();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/sync-status/sync-state
		// Description: State of DU synchronization
		// -----------------------------------------------------------------------------
		class LeafSyncState : public YangLeaf
		{
		public:

			// State of DU synchronization
			enum class SyncState_E : uint32_t
			{
				LOCKED,	// equipment is in the locked mode, as defined in ITU-T G.810
				HOLDOVER,	// equipment clock is in holdover mode
				FREERUN,	// equipment clock isn't locked to an input reference, and is not in the holdover mode

				Num_SyncState_E
			};

			LeafSyncState(uint32_t id);
			~LeafSyncState();

		}; // LeafSyncState

		// -----------------------------------------------------------------------------
		// List:        /sync-group/sync-status/supported-reference-types
		// Description: Type of a synchronization supported source.
		// -----------------------------------------------------------------------------
		class LstSupportedReferenceTypes : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_ITEM,  // LeafItem
			};

			LstSupportedReferenceTypes(uint32_t id);
			~LstSupportedReferenceTypes();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/sync-status/supported-reference-types/item
			// Description: supported reference-type
			// -----------------------------------------------------------------------------
			class LeafItem : public YangLeaf
			{
			public:

				// supported reference-type
				enum class Item_E : uint32_t
				{
					GNSS,	// GPS can be taken as a synchronization source
					PTP,	// Precision Time Protocol can be taken as a synchronization source
					SYNCE,	// Synchronous Ethernet can be taken as a synchronization source

					Num_Item_E
				};

				LeafItem(uint32_t id);
				~LeafItem();

			}; // LeafItem

		}; // LstSupportedReferenceTypes

	}; // CntSyncStatus

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/sync-capability
	// Description: Object of this class provides synchronization capabilities of the module.
	// -----------------------------------------------------------------------------
	class CntSyncCapability : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_SYNC_T_TSC,  // LeafSyncTTsc
		};

		CntSyncCapability(uint32_t id);
		~CntSyncCapability();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/sync-capability/sync-t-tsc
		// Description: This will provide information about T-TSC capability
		// -----------------------------------------------------------------------------
		class LeafSyncTTsc : public YangLeaf
		{
		public:

			// This will provide information about T-TSC capability
			enum class SyncTTsc_E : uint32_t
			{
				CLASS_B,	// Standard class B accuracy for synchronization is supported by the device
				ENCHANCED,	// Enchanced accuracy for synchronization is supported by the device

				Num_SyncTTsc_E
			};

			LeafSyncTTsc(uint32_t id);
			~LeafSyncTTsc();

		}; // LeafSyncTTsc

	}; // CntSyncCapability

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/ptp-config
	// Description: This MO defines configuration of Precise Time Protocol.
	// -----------------------------------------------------------------------------
	class CntPtpConfig : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_DOMAIN_NUMBER,  // LeafDomainNumber
			ITEM_PTP_PROFILE,  // LeafPtpProfile
			ITEM_G_8275_1_CONFIG,  // CntG82751Config
			ITEM_G_8275_2_CONFIG,  // CntG82752Config
			ITEM_ACCEPTED_CLOCK_CLASSES,  // LstAcceptedClockClasses
		};

		CntPtpConfig(uint32_t id);
		~CntPtpConfig();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/ptp-config/domain-number
		// Description: This parameter indicates Domain Number for PTP announce messages.
		// -----------------------------------------------------------------------------
		class LeafDomainNumber : public YangLeaf
		{
		public:

			LeafDomainNumber(uint32_t id);
			~LeafDomainNumber();

		}; // LeafDomainNumber

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/ptp-config/ptp-profile
		// Description: Type of profile to be used in ptp setting
		// -----------------------------------------------------------------------------
		class LeafPtpProfile : public YangLeaf
		{
		public:

			// Type of profile to be used in ptp setting
			enum class PtpProfile_E : uint32_t
			{
				G_8275_1,	// Usage of multicast over ethernet
				G_8275_2,	// Usage of unicast over IP

				Num_PtpProfile_E
			};

			LeafPtpProfile(uint32_t id);
			~LeafPtpProfile();

		}; // LeafPtpProfile

		// -----------------------------------------------------------------------------
		// Container:   /sync-group/ptp-config/g-8275-1-config
		// Description: Container allowing for configuration of G8275.1
		// -----------------------------------------------------------------------------
		class CntG82751Config : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_MULTICAST_MAC_ADDRESS,  // LeafMulticastMacAddress
				ITEM_DELAY_ASYMMETRY,  // LeafDelayAsymmetry
			};

			CntG82751Config(uint32_t id);
			~CntG82751Config();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-config/g-8275-1-config/multicast-mac-address
			// Description: The parameter defines destination MAC address, used by the DU in the egress PTP messages.
			// -----------------------------------------------------------------------------
			class LeafMulticastMacAddress : public YangLeaf
			{
			public:

				// The parameter defines destination MAC address, used by the DU in the egress PTP messages.
				enum class MulticastMacAddress_E : uint32_t
				{
					FORWARDABLE,	// means, that PTP shall use 01-1B-19-00-00-00 destination MAC address
					NONFORWARDABLE,	// means, that PTP shall use 01-80-C2-00-00-0E destination MAC address

					Num_MulticastMacAddress_E
				};

				LeafMulticastMacAddress(uint32_t id);
				~LeafMulticastMacAddress();

			}; // LeafMulticastMacAddress

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-config/g-8275-1-config/delay-asymmetry
			// Description: Defines static phase error in the recovered PTP timing signal to be compensated at the O-RU.
			//              The error is defined in units of nanoseconds in the range ±10 000 ns.
			// -----------------------------------------------------------------------------
			class LeafDelayAsymmetry : public YangLeaf
			{
			public:

				LeafDelayAsymmetry(uint32_t id);
				~LeafDelayAsymmetry();

			}; // LeafDelayAsymmetry

		}; // CntG82751Config

		// -----------------------------------------------------------------------------
		// Container:   /sync-group/ptp-config/g-8275-2-config
		// Description: Container used for configuration of G8275.2 profile
		// -----------------------------------------------------------------------------
		class CntG82752Config : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_LOG_INTER_SYNC_PERIOD,  // LeafLogInterSyncPeriod
				ITEM_LOG_INTER_ANNOUNCE_PERIOD,  // LeafLogInterAnnouncePeriod
				ITEM_LOCAL_IP_PORT,  // RefLocalIpPort
				ITEM_MASTER_IP_CONFIGURATION,  // LstMasterIpConfiguration
			};

			CntG82752Config(uint32_t id);
			~CntG82752Config();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-config/g-8275-2-config/log-inter-sync-period
			// Description: The parameter defines number of sync message during 1 second
			// -----------------------------------------------------------------------------
			class LeafLogInterSyncPeriod : public YangLeaf
			{
			public:

				LeafLogInterSyncPeriod(uint32_t id);
				~LeafLogInterSyncPeriod();

			}; // LeafLogInterSyncPeriod

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-config/g-8275-2-config/log-inter-announce-period
			// Description: The parameter defines number of announce message during 1 second
			// -----------------------------------------------------------------------------
			class LeafLogInterAnnouncePeriod : public YangLeaf
			{
			public:

				LeafLogInterAnnouncePeriod(uint32_t id);
				~LeafLogInterAnnouncePeriod();

			}; // LeafLogInterAnnouncePeriod

			// -----------------------------------------------------------------------------
			// Reference:   /sync-group/ptp-config/g-8275-2-config/local-ip-port
			// Description: Reference to interface name corresponding to IP interface
			//              used for G.8275.2
			// -----------------------------------------------------------------------------
			class RefLocalIpPort : public YangReference
			{
			public:

				RefLocalIpPort(uint32_t id);
				~RefLocalIpPort();

			}; // RefLocalIpPort

			// -----------------------------------------------------------------------------
			// List:        /sync-group/ptp-config/g-8275-2-config/master-ip-configuration
			// Description: The parameter defines list of ip configuration of devices acting as ptp signal source.
			// -----------------------------------------------------------------------------
			class LstMasterIpConfiguration : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_LOCAL_PRIORITY,  // LeafLocalPriority
					ITEM_IP_ADDRESS,  // LeafIpAddress
				};

				LstMasterIpConfiguration(uint32_t id);
				~LstMasterIpConfiguration();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /sync-group/ptp-config/g-8275-2-config/master-ip-configuration/local-priority
				// Description: The parameter defines local priority or underlying master IP address.
				// -----------------------------------------------------------------------------
				class LeafLocalPriority : public YangLeaf
				{
				public:

					LeafLocalPriority(uint32_t id);
					~LeafLocalPriority();

				}; // LeafLocalPriority

				// -----------------------------------------------------------------------------
				// Leaf:        /sync-group/ptp-config/g-8275-2-config/master-ip-configuration/ip-address
				// Description: the parameter defines master IP address.
				// -----------------------------------------------------------------------------
				class LeafIpAddress : public YangLeaf
				{
				public:

					LeafIpAddress(uint32_t id);
					~LeafIpAddress();

				}; // LeafIpAddress

			}; // LstMasterIpConfiguration

		}; // CntG82752Config

		// -----------------------------------------------------------------------------
		// List:        /sync-group/ptp-config/accepted-clock-classes
		// Description: Contains list of PTP acceptable Clock Classes, sorted in the descending order.
		// -----------------------------------------------------------------------------
		class LstAcceptedClockClasses : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_CLOCK_CLASSES,  // LeafClockClasses
			};

			LstAcceptedClockClasses(uint32_t id);
			~LstAcceptedClockClasses();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-config/accepted-clock-classes/clock-classes
			// Description: PTP Clock Class accepted by the O-RU
			// -----------------------------------------------------------------------------
			class LeafClockClasses : public YangLeaf
			{
			public:

				LeafClockClasses(uint32_t id);
				~LeafClockClasses();

			}; // LeafClockClasses

		}; // LstAcceptedClockClasses

	}; // CntPtpConfig

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/ptp-status
	// Description: ptp status container
	// -----------------------------------------------------------------------------
	class CntPtpStatus : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_REPORTING_PERIOD,  // LeafReportingPeriod
			ITEM_LOCK_STATE,  // LeafLockState
			ITEM_CLOCK_CLASS,  // LeafClockClass
			ITEM_CLOCK_IDENTITY,  // LeafClockIdentity
			ITEM_PARTIAL_TIMING_SUPPORTED,  // LeafPartialTimingSupported
			ITEM_SOURCES,  // LstSources
		};

		CntPtpStatus(uint32_t id);
		~CntPtpStatus();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/ptp-status/reporting-period
		// Description: This parameter defines minimum period in seconds between reports,
		//              sent by the NETCONF Client, for parameters in this container.
		// -----------------------------------------------------------------------------
		class LeafReportingPeriod : public YangLeaf
		{
		public:

			LeafReportingPeriod(uint32_t id);
			~LeafReportingPeriod();

		}; // LeafReportingPeriod

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/ptp-status/lock-state
		// Description: This parameter indicates, whether the integrated ordinary clock is
		//              synchronizing to the reference, recovered from PTP signal.
		//              The exact definition when to indicate locked or unlocked is up to specific
		//              implementation.
		// -----------------------------------------------------------------------------
		class LeafLockState : public YangLeaf
		{
		public:

			// This parameter indicates, whether the integrated ordinary clock is
			// synchronizing to the reference, recovered from PTP signal.
			// The exact definition when to indicate locked or unlocked is up to specific
			// implementation.
			enum class LockState_E : uint32_t
			{
				LOCKED,	// The integrated ordinary clock is synchronizing to the reference, recovered from PTP flow
				UNLOCKED,	// The integrated ordinary clock is not synchronizing to the reference, recovered from PTP flow

				Num_LockState_E
			};

			LeafLockState(uint32_t id);
			~LeafLockState();

		}; // LeafLockState

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/ptp-status/clock-class
		// Description: This parameter contains the clock class of the clock, controlled by the O-RU
		// -----------------------------------------------------------------------------
		class LeafClockClass : public YangLeaf
		{
		public:

			LeafClockClass(uint32_t id);
			~LeafClockClass();

		}; // LeafClockClass

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/ptp-status/clock-identity
		// Description: This parameter contains identity of the clock,
		//               according to IEEE 1588-2008 defintion, controlled by the O-RU.
		//              The string shall be formatted as an 8-octet hex value with the '0x' prefix.
		// -----------------------------------------------------------------------------
		class LeafClockIdentity : public YangLeaf
		{
		public:

			LeafClockIdentity(uint32_t id);
			~LeafClockIdentity();

		}; // LeafClockIdentity

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/ptp-status/partial-timing-supported
		// Description: Provides information wheter G.8275.2 (partial timing support from network) is supported.
		// -----------------------------------------------------------------------------
		class LeafPartialTimingSupported : public YangLeaf
		{
		public:

			LeafPartialTimingSupported(uint32_t id);
			~LeafPartialTimingSupported();

		}; // LeafPartialTimingSupported

		// -----------------------------------------------------------------------------
		// List:        /sync-group/ptp-status/sources
		// Description: Synchronisation sources
		// -----------------------------------------------------------------------------
		class LstSources : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_STATE,  // LeafState
				ITEM_TWO_STEP_FLAG,  // LeafTwoStepFlag
				ITEM_LEAP61,  // LeafLeap61
				ITEM_LEAP59,  // LeafLeap59
				ITEM_CURRENT_UTC_OFFSET_VALID,  // LeafCurrentUtcOffsetValid
				ITEM_PTP_TIMESCALE,  // LeafPtpTimescale
				ITEM_TIME_TRACEABLE,  // LeafTimeTraceable
				ITEM_FREQUENCY_TRACEABLE,  // LeafFrequencyTraceable
				ITEM_SOURCE_CLOCK_IDENTITY,  // LeafSourceClockIdentity
				ITEM_SOURCE_PORT_NUMBER,  // LeafSourcePortNumber
				ITEM_CURRENT_UTC_OFFSET,  // LeafCurrentUtcOffset
				ITEM_PRIORITY1,  // LeafPriority1
				ITEM_CLOCK_CLASS,  // LeafClockClass
				ITEM_CLOCK_ACCURACY,  // LeafClockAccuracy
				ITEM_OFFSET_SCALED_LOG_VARIANCE,  // LeafOffsetScaledLogVariance
				ITEM_PRIORITY2,  // LeafPriority2
				ITEM_GRANDMASTER_CLOCK_IDENTITY,  // LeafGrandmasterClockIdentity
				ITEM_STEPS_REMOVED,  // LeafStepsRemoved
				ITEM_TIME_SOURCE,  // LeafTimeSource
				ITEM_LOCAL_PORT_NUMBER,  // RefLocalPortNumber
			};

			LstSources(uint32_t id);
			~LstSources();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/state
			// Description: This parameter indicates status of the PTP source
			// -----------------------------------------------------------------------------
			class LeafState : public YangLeaf
			{
			public:

				// This parameter indicates status of the PTP source
				enum class State_E : uint32_t
				{
					PARENT,	// Indicates that this source is the current master clock, i.e. the clock,
							// which the clock, controlled by the Netconf Server, is synchronized to
					OK,	// Indicates that this source is an alternate master, which the clock,
							// controlled by the Netconf Server, can potentially synchronize to,
							// i.e. clock class and priority, announced by the master clock is lower,
							// compared to those of the clock, controlled by the Netconf Server,
							// and and the clock class is accepted
					NOK,	// Indicates that this source is an alternate master, which the clock,
							// controlled by the Netconf Server, has an operational connection to,
							// but the class or priority of the master clock is higher or equal
							// to those of the clock, controlled by the Netconf Server,
							// or the clock class is not accepted
					DISABLED,	// Indicates that this source is an alternate master, which the clock,
							// controlled by the Netconf Server, has no operational connection to

					Num_State_E
				};

				LeafState(uint32_t id);
				~LeafState();

			}; // LeafState

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/two-step-flag
			// Description: This parameter reflects status of the twoStepFlag attribute in Sync messages,
			//              received from the PTP source.
			// -----------------------------------------------------------------------------
			class LeafTwoStepFlag : public YangLeaf
			{
			public:

				LeafTwoStepFlag(uint32_t id);
				~LeafTwoStepFlag();

			}; // LeafTwoStepFlag

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/leap61
			// Description: This parameter reflects status of the leap61 flag in Announce messages,
			//              received from the PTP source.
			//              When true, the last minute of the current UTC day contains 61 seconds.
			// -----------------------------------------------------------------------------
			class LeafLeap61 : public YangLeaf
			{
			public:

				LeafLeap61(uint32_t id);
				~LeafLeap61();

			}; // LeafLeap61

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/leap59
			// Description: This parameter reflects status of the leap59 flag in Announce messages,
			//              received from the PTP source.
			//              When true, the last minute of the current UTC day contains 59 seconds.
			// -----------------------------------------------------------------------------
			class LeafLeap59 : public YangLeaf
			{
			public:

				LeafLeap59(uint32_t id);
				~LeafLeap59();

			}; // LeafLeap59

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/current-utc-offset-valid
			// Description: This parameter reflects status of the currentUtcOffsetValid flag in
			//              Announce messages, received from the PTP source.
			//              When true, the current UTC offset is valid.
			// -----------------------------------------------------------------------------
			class LeafCurrentUtcOffsetValid : public YangLeaf
			{
			public:

				LeafCurrentUtcOffsetValid(uint32_t id);
				~LeafCurrentUtcOffsetValid();

			}; // LeafCurrentUtcOffsetValid

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/ptp-timescale
			// Description: This parameter reflects status of the ptpTimescale flag in Announce
			//              messages, received from the PTP source.
			//
			//              When set, the clock timescale of the grandmaster clock is PTP;
			//              otherwise, the timescale is ARB (arbitrary)
			// -----------------------------------------------------------------------------
			class LeafPtpTimescale : public YangLeaf
			{
			public:

				LeafPtpTimescale(uint32_t id);
				~LeafPtpTimescale();

			}; // LeafPtpTimescale

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/time-traceable
			// Description: This parameter reflects status of the timeTraceable flag in Announce
			//              messages, received from the PTP source.
			//
			//              When true, the timescale and the currentUtcOffset are traceable to a
			//              primary reference
			// -----------------------------------------------------------------------------
			class LeafTimeTraceable : public YangLeaf
			{
			public:

				LeafTimeTraceable(uint32_t id);
				~LeafTimeTraceable();

			}; // LeafTimeTraceable

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/frequency-traceable
			// Description: This parameter reflects status of the frequencyTraceable flag in
			//              Announce messages, received from the PTP source.
			//
			//              When true, the frequency determining the timescale is traceable to a
			//              primary reference
			// -----------------------------------------------------------------------------
			class LeafFrequencyTraceable : public YangLeaf
			{
			public:

				LeafFrequencyTraceable(uint32_t id);
				~LeafFrequencyTraceable();

			}; // LeafFrequencyTraceable

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/source-clock-identity
			// Description: This parameter reflects value of the sourceClockIdentity attribute in
			//              Announce messages, received from the PTP source.
			//
			//              The string shall be formatted as an 8-octet hex value with the '0x'
			//              prefix.
			// -----------------------------------------------------------------------------
			class LeafSourceClockIdentity : public YangLeaf
			{
			public:

				LeafSourceClockIdentity(uint32_t id);
				~LeafSourceClockIdentity();

			}; // LeafSourceClockIdentity

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/source-port-number
			// Description: This parameter reflects value of the sourcePortNumber attribute in
			//              Announce messages, received from the PTP source.
			// -----------------------------------------------------------------------------
			class LeafSourcePortNumber : public YangLeaf
			{
			public:

				LeafSourcePortNumber(uint32_t id);
				~LeafSourcePortNumber();

			}; // LeafSourcePortNumber

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/current-utc-offset
			// Description: The offset between TAI and UTC when the epoch of the PTP system is
			//              the PTP epoch, i.e., when ptp-timescale is TRUE; otherwise, the value
			//              has no meaning
			// -----------------------------------------------------------------------------
			class LeafCurrentUtcOffset : public YangLeaf
			{
			public:

				LeafCurrentUtcOffset(uint32_t id);
				~LeafCurrentUtcOffset();

			}; // LeafCurrentUtcOffset

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/priority1
			// Description: This parameter reflects value of the priority1 attribute in Announce
			//              messages, received from the PTP source.
			// -----------------------------------------------------------------------------
			class LeafPriority1 : public YangLeaf
			{
			public:

				LeafPriority1(uint32_t id);
				~LeafPriority1();

			}; // LeafPriority1

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/clock-class
			// Description: This parameter reflects value of the clockClass attribute in
			//              Announce messages, received from the PTP source.
			// -----------------------------------------------------------------------------
			class LeafClockClass : public YangLeaf
			{
			public:

				LeafClockClass(uint32_t id);
				~LeafClockClass();

			}; // LeafClockClass

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/clock-accuracy
			// Description: This parameter reflects value of the clockAccuracy attribute in
			//              Announce messages, received from the PTP source.
			// -----------------------------------------------------------------------------
			class LeafClockAccuracy : public YangLeaf
			{
			public:

				LeafClockAccuracy(uint32_t id);
				~LeafClockAccuracy();

			}; // LeafClockAccuracy

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/offset-scaled-log-variance
			// Description: This parameter reflects value of the offsetScaledLogVariance
			//              attribute in Announce messages, received from the PTP source.
			// -----------------------------------------------------------------------------
			class LeafOffsetScaledLogVariance : public YangLeaf
			{
			public:

				LeafOffsetScaledLogVariance(uint32_t id);
				~LeafOffsetScaledLogVariance();

			}; // LeafOffsetScaledLogVariance

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/priority2
			// Description: This parameter reflects value of the priority2 attribute in Announce
			//              messages, received from the PTP source.
			// -----------------------------------------------------------------------------
			class LeafPriority2 : public YangLeaf
			{
			public:

				LeafPriority2(uint32_t id);
				~LeafPriority2();

			}; // LeafPriority2

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/grandmaster-clock-identity
			// Description: This parameter reflects value of the grandmasterClockIdentity
			//              attribute in Announce messages, received from the PTP source.
			//
			//              The string shall be formatted as an 8-octet hex value with the '0x'
			//              prefix.
			// -----------------------------------------------------------------------------
			class LeafGrandmasterClockIdentity : public YangLeaf
			{
			public:

				LeafGrandmasterClockIdentity(uint32_t id);
				~LeafGrandmasterClockIdentity();

			}; // LeafGrandmasterClockIdentity

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/steps-removed
			// Description: This parameter reflects value of the stepsRemoved attribute in
			//              Announce messages, received from the PTP source.
			//
			//              It indicates the number of communication paths traversed
			//              between the local clock and the grandmaster clock.
			// -----------------------------------------------------------------------------
			class LeafStepsRemoved : public YangLeaf
			{
			public:

				LeafStepsRemoved(uint32_t id);
				~LeafStepsRemoved();

			}; // LeafStepsRemoved

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/ptp-status/sources/time-source
			// Description: This parameter reflects value of the timeSource attribute in
			//              Announce messages, received from the PTP source.
			// -----------------------------------------------------------------------------
			class LeafTimeSource : public YangLeaf
			{
			public:

				LeafTimeSource(uint32_t id);
				~LeafTimeSource();

			}; // LeafTimeSource

			// -----------------------------------------------------------------------------
			// Reference:   /sync-group/ptp-status/sources/local-port-number
			// Description: This is reference to portNumber of ExternalEthernetPort to identify the port,
			//              where the PTP signal is located.
			// -----------------------------------------------------------------------------
			class RefLocalPortNumber : public YangReference
			{
			public:

				RefLocalPortNumber(uint32_t id);
				~RefLocalPortNumber();

			}; // RefLocalPortNumber

		}; // LstSources

	}; // CntPtpStatus

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/synce-config
	// Description: This container defines the configuration of SyncE
	// -----------------------------------------------------------------------------
	class CntSynceConfig : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_SSM_TIMEOUT,  // LeafSsmTimeout
			ITEM_ACCEPTANCE_LIST_OF_SSM,  // LstAcceptanceListOfSsm
		};

		CntSynceConfig(uint32_t id);
		~CntSynceConfig();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/synce-config/ssm-timeout
		// Description: The parameter contains the value of maximum duration in seconds for which the actual SSM value may be different than configured values.
		// -----------------------------------------------------------------------------
		class LeafSsmTimeout : public YangLeaf
		{
		public:

			LeafSsmTimeout(uint32_t id);
			~LeafSsmTimeout();

		}; // LeafSsmTimeout

		// -----------------------------------------------------------------------------
		// List:        /sync-group/synce-config/acceptance-list-of-ssm
		// Description: The parameter contains the list of SyncE acceptable SSMs.
		// -----------------------------------------------------------------------------
		class LstAcceptanceListOfSsm : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstAcceptanceListOfSsm(uint32_t id);
			~LstAcceptanceListOfSsm();

			YangResult_E initialise(void);

		}; // LstAcceptanceListOfSsm

	}; // CntSynceConfig

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/synce-status
	// Description: SyncE status container
	// -----------------------------------------------------------------------------
	class CntSynceStatus : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_REPORTING_PERIOD,  // LeafReportingPeriod
			ITEM_LOCK_STATE,  // LeafLockState
			ITEM_SOURCES,  // LstSources
		};

		CntSynceStatus(uint32_t id);
		~CntSynceStatus();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/synce-status/reporting-period
		// Description: This parameter defines minimum period in seconds between reports,
		//              sent by the NETCONF client, for parameters in this container.
		// -----------------------------------------------------------------------------
		class LeafReportingPeriod : public YangLeaf
		{
		public:

			LeafReportingPeriod(uint32_t id);
			~LeafReportingPeriod();

		}; // LeafReportingPeriod

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/synce-status/lock-state
		// Description: This parameter indicates, whether the integrated ordinary clock is
		//              synchronizing to the reference, recovered from SyncE signal.
		//
		//              The exact definition when to indicate locked or unlocked is up to
		//              specific implementation.
		// -----------------------------------------------------------------------------
		class LeafLockState : public YangLeaf
		{
		public:

			// This parameter indicates, whether the integrated ordinary clock is
			// synchronizing to the reference, recovered from SyncE signal.
			//
			// The exact definition when to indicate locked or unlocked is up to
			// specific implementation.
			enum class LockState_E : uint32_t
			{
				LOCKED,	// The integrated ordinary clock is synchronizing to the reference, recovered from SyncE signal
				UNLOCKED,	// The integrated ordinary clock is not synchronizing to the reference, recovered from SyncE signal

				Num_LockState_E
			};

			LeafLockState(uint32_t id);
			~LeafLockState();

		}; // LeafLockState

		// -----------------------------------------------------------------------------
		// List:        /sync-group/synce-status/sources
		// Description: This parameter contains characteristics of SyncE sources of the clock, controlled by the O-RU.
		// -----------------------------------------------------------------------------
		class LstSources : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_STATE,  // LeafState
				ITEM_QUALITY_LEVEL,  // LeafQualityLevel
				ITEM_LOCAL_PORT_NUMBER,  // RefLocalPortNumber
			};

			LstSources(uint32_t id);
			~LstSources();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/synce-status/sources/state
			// Description: This parameter indicates status of the SyncE source
			// -----------------------------------------------------------------------------
			class LeafState : public YangLeaf
			{
			public:

				// This parameter indicates status of the SyncE source
				enum class State_E : uint32_t
				{
					PARENT,	// Indicates that this source is the current master clock, i.e. the clock,
							// which the clock, controlled by the Netconf Server, is synchronized to
					OK,	// Indicates that this source is an alternate master, which the clock,
							// controlled by the Netconf Server, can potentially synchronize to,
							// i.e. clock class and priority, announced by the master clock is lower,
							// compared to those of the clock, controlled by the Netconf Server,
							// and and the clock class is accepted
					NOK,	// Indicates that this source is an alternate master, which the clock,
							// controlled by the Netconf Server, has an operational connection to,
							// but the class or priority of the master clock is higher or equal
							// to those of the clock, controlled by the Netconf Server,
							// or the clock class is not accepted
					DISABLED,	// Indicates that this source is an alternate master, which the clock,
							// controlled by the Netconf Server, has no operational connection to

					Num_State_E
				};

				LeafState(uint32_t id);
				~LeafState();

			}; // LeafState

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/synce-status/sources/quality-level
			// Description: This parameter contains value of the SSM clock quality level,
			//              received in SSM messages from the SyncE source.
			// -----------------------------------------------------------------------------
			class LeafQualityLevel : public YangLeaf
			{
			public:

				LeafQualityLevel(uint32_t id);
				~LeafQualityLevel();

			}; // LeafQualityLevel

			// -----------------------------------------------------------------------------
			// Reference:   /sync-group/synce-status/sources/local-port-number
			// Description: This is reference to portNumber of ExternalEthernetPort to identify
			//              the port, where the SyncE signal is located.
			// -----------------------------------------------------------------------------
			class RefLocalPortNumber : public YangReference
			{
			public:

				RefLocalPortNumber(uint32_t id);
				~RefLocalPortNumber();

			}; // RefLocalPortNumber

		}; // LstSources

	}; // CntSynceStatus

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/gnss-config
	// Description: This container defines the configuration of Global Navigation Satellite System (GNSS).
	// -----------------------------------------------------------------------------
	class CntGnssConfig : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_ENABLE,  // LeafEnable
			ITEM_POLARITY,  // LeafPolarity
			ITEM_CABLE_DELAY,  // LeafCableDelay
			ITEM_ANTI_JAM_ENABLE,  // LeafAntiJamEnable
			ITEM_SATELLITE_CONSTELATION_LIST,  // LstSatelliteConstelationList
		};

		CntGnssConfig(uint32_t id);
		~CntGnssConfig();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/gnss-config/enable
		// Description: This parameter defines if GNSS receiver shall be enabled or not.
		// -----------------------------------------------------------------------------
		class LeafEnable : public YangLeaf
		{
		public:

			LeafEnable(uint32_t id);
			~LeafEnable();

		}; // LeafEnable

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/gnss-config/polarity
		// Description: This parameter defines pulse polarity
		// -----------------------------------------------------------------------------
		class LeafPolarity : public YangLeaf
		{
		public:

			// This parameter defines pulse polarity
			enum class Polarity_E : uint32_t
			{
				POSITIVE,	// POSITIVE
				NEGATIVE,	// NEGATIVE

				Num_Polarity_E
			};

			LeafPolarity(uint32_t id);
			~LeafPolarity();

		}; // LeafPolarity

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/gnss-config/cable-delay
		// Description: This parameter is used to compensate cable delay.
		// -----------------------------------------------------------------------------
		class LeafCableDelay : public YangLeaf
		{
		public:

			LeafCableDelay(uint32_t id);
			~LeafCableDelay();

		}; // LeafCableDelay

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/gnss-config/anti-jam-enable
		// Description: This parameter is used to enable or disable anti-jamming.
		// -----------------------------------------------------------------------------
		class LeafAntiJamEnable : public YangLeaf
		{
		public:

			LeafAntiJamEnable(uint32_t id);
			~LeafAntiJamEnable();

		}; // LeafAntiJamEnable

		// -----------------------------------------------------------------------------
		// List:        /sync-group/gnss-config/satellite-constelation-list
		// Description: This parameter defines list of constellations to be used to acquire synchronization.
		// -----------------------------------------------------------------------------
		class LstSatelliteConstelationList : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstSatelliteConstelationList(uint32_t id);
			~LstSatelliteConstelationList();

			YangResult_E initialise(void);

		}; // LstSatelliteConstelationList

	}; // CntGnssConfig

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/gnss-status
	// Description: Provides information about state of gps receiver
	// -----------------------------------------------------------------------------
	class CntGnssStatus : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_REPORTING_PERIOD,  // LeafReportingPeriod
			ITEM_NAME,  // LeafName
			ITEM_GNSS_SYNC_STATUS,  // LeafGnssSyncStatus
			ITEM_GNSS_DATA,  // CntGnssData
		};

		CntGnssStatus(uint32_t id);
		~CntGnssStatus();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/gnss-status/reporting-period
		// Description: This parameter defines minimum period in seconds between reports,
		//              sent by the NETCONF Client, for parameters in this container.
		// -----------------------------------------------------------------------------
		class LeafReportingPeriod : public YangLeaf
		{
		public:

			LeafReportingPeriod(uint32_t id);
			~LeafReportingPeriod();

		}; // LeafReportingPeriod

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/gnss-status/name
		// Description: A name that is unique that identifies a GNSS instance.
		//              This name may be used in fault management to refer to a
		//              fault source or affected object
		// -----------------------------------------------------------------------------
		class LeafName : public YangLeaf
		{
		public:

			LeafName(uint32_t id);
			~LeafName();

		}; // LeafName

		// -----------------------------------------------------------------------------
		// Leaf:        /sync-group/gnss-status/gnss-sync-status
		// Description: when available, indicates the status of the gnss receiver.
		// -----------------------------------------------------------------------------
		class LeafGnssSyncStatus : public YangLeaf
		{
		public:

			// when available, indicates the status of the gnss receiver.
			enum class GnssSyncStatus_E : uint32_t
			{
				SYNCHRONIZED,	// GNSS functionality is synchronized
				ACQUIRING_SYNC,	// GNSS functionality is acquiring sync
				ANTENNA_DISCONNECTED,	// GNSS functionality has its antenna disconnected
				BOOTING,	// GNSS functionality is booting
				ANTENNA_SHORT_CIRCUIT,	// GNSS functionality has an antenna short circuit

				Num_GnssSyncStatus_E
			};

			LeafGnssSyncStatus(uint32_t id);
			~LeafGnssSyncStatus();

		}; // LeafGnssSyncStatus

		// -----------------------------------------------------------------------------
		// Container:   /sync-group/gnss-status/gnss-data
		// Description: GPS data contained
		// -----------------------------------------------------------------------------
		class CntGnssData : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_SATELLITES_TRACKED,  // LeafSatellitesTracked
				ITEM_LOCATION,  // CntLocation
			};

			CntGnssData(uint32_t id);
			~CntGnssData();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /sync-group/gnss-status/gnss-data/satellites-tracked
			// Description: Number of satellites tracked
			// -----------------------------------------------------------------------------
			class LeafSatellitesTracked : public YangLeaf
			{
			public:

				LeafSatellitesTracked(uint32_t id);
				~LeafSatellitesTracked();

			}; // LeafSatellitesTracked

			// -----------------------------------------------------------------------------
			// Container:   /sync-group/gnss-status/gnss-data/location
			// Description: Containes information about geo location
			// -----------------------------------------------------------------------------
			class CntLocation : public YangContainer
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_ALTITUDE,  // LeafAltitude
					ITEM_LATITUDE,  // LeafLatitude
					ITEM_LONGITUDE,  // LeafLongitude
				};

				CntLocation(uint32_t id);
				~CntLocation();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /sync-group/gnss-status/gnss-data/location/altitude
				// Description: Distance above the sea level.
				// -----------------------------------------------------------------------------
				class LeafAltitude : public YangLeaf
				{
				public:

					LeafAltitude(uint32_t id);
					~LeafAltitude();

				}; // LeafAltitude

				// -----------------------------------------------------------------------------
				// Leaf:        /sync-group/gnss-status/gnss-data/location/latitude
				// Description: Relative position north or south on the Earth's surface.
				// -----------------------------------------------------------------------------
				class LeafLatitude : public YangLeaf
				{
				public:

					LeafLatitude(uint32_t id);
					~LeafLatitude();

				}; // LeafLatitude

				// -----------------------------------------------------------------------------
				// Leaf:        /sync-group/gnss-status/gnss-data/location/longitude
				// Description: Angular distance east or west on the Earth's surface.
				// -----------------------------------------------------------------------------
				class LeafLongitude : public YangLeaf
				{
				public:

					LeafLongitude(uint32_t id);
					~LeafLongitude();

				}; // LeafLongitude

			}; // CntLocation

		}; // CntGnssData

	}; // CntGnssStatus

}; // GrpSyncGroup


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
// Notification:/synchronization-state-change
// Description: Notification used to inform about synchronization state change
// -----------------------------------------------------------------------------
class NotifSynchronizationStateChange : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_SYNC_STATE,  // RefSyncState
	};

	NotifSynchronizationStateChange(uint32_t id);
	~NotifSynchronizationStateChange();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Reference:   /synchronization-state-change/sync-state
	// Description: State of equipment synchronization is notified at state change
	// -----------------------------------------------------------------------------
	class RefSyncState : public YangReference
	{
	public:

		RefSyncState(uint32_t id);
		~RefSyncState();

	}; // RefSyncState

}; // NotifSynchronizationStateChange

// -----------------------------------------------------------------------------
// Notification:/ptp-state-change
// Description: Notification used to inform about ptp synchronization state change
// -----------------------------------------------------------------------------
class NotifPtpStateChange : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_PTP_STATE,  // RefPtpState
	};

	NotifPtpStateChange(uint32_t id);
	~NotifPtpStateChange();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Reference:   /ptp-state-change/ptp-state
	// Description: ptp-state-change notification is signalled from equipment at state change
	// -----------------------------------------------------------------------------
	class RefPtpState : public YangReference
	{
	public:

		RefPtpState(uint32_t id);
		~RefPtpState();

	}; // RefPtpState

}; // NotifPtpStateChange

// -----------------------------------------------------------------------------
// Notification:/synce-state-change
// Description: Notification used to inform about synce synchronization state change
// -----------------------------------------------------------------------------
class NotifSynceStateChange : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_SYNCE_STATE,  // RefSynceState
	};

	NotifSynceStateChange(uint32_t id);
	~NotifSynceStateChange();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Reference:   /synce-state-change/synce-state
	// Description: synce-state change notification is signalled from equipment at state change
	// -----------------------------------------------------------------------------
	class RefSynceState : public YangReference
	{
	public:

		RefSynceState(uint32_t id);
		~RefSynceState();

	}; // RefSynceState

}; // NotifSynceStateChange

// -----------------------------------------------------------------------------
// Notification:/gnss-state-change
// Description: Notification used to inform about gnss synchronization state change
// -----------------------------------------------------------------------------
class NotifGnssStateChange : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_GNSS_STATE,  // RefGnssState
	};

	NotifGnssStateChange(uint32_t id);
	~NotifGnssStateChange();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Reference:   /gnss-state-change/gnss-state
	// Description: gnss-state-change notification is signalled from equipment at state change
	// -----------------------------------------------------------------------------
	class RefGnssState : public YangReference
	{
	public:

		RefGnssState(uint32_t id);
		~RefGnssState();

	}; // RefGnssState

}; // NotifGnssStateChange


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-sync
// Description: This module defines synchronization mechanism for the O-RAN Equipment.
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
class ModuleORanSync : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_GNSS,  // Feature
		ITEM_ANTI_JAM,  // Feature
		ITEM_SYNC,  // CntSync
		ITEM_SYNCHRONIZATION_STATE_CHANGE,  // NotifSynchronizationStateChange
		ITEM_PTP_STATE_CHANGE,  // NotifPtpStateChange
		ITEM_SYNCE_STATE_CHANGE,  // NotifSynceStateChange
		ITEM_GNSS_STATE_CHANGE,  // NotifGnssStateChange
	};

	ModuleORanSync(uint32_t id);
	~ModuleORanSync();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanSync_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_SYNC_H_ */
