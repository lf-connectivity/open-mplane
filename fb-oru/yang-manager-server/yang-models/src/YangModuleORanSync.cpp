/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanSync.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleORanSync.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleORanSync_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the equipment supports integrated GNSS functionality.
// -----------------------------------------------------------------------------
FeatureGNSS::FeatureGNSS(uint32_t id)
	: YangFeature("GNSS", id)
{
}

FeatureGNSS::~FeatureGNSS()
{
}

// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the equipment supports Anti-jam fuctionality
// -----------------------------------------------------------------------------
FeatureANTIJAM::FeatureANTIJAM(uint32_t id)
	: YangFeature("ANTI-JAM", id)
{
}

FeatureANTIJAM::~FeatureANTIJAM()
{
}


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
// Container:   sync
// Description: Main containter for sync related parameters
// -----------------------------------------------------------------------------
CntSync::CntSync(uint32_t id)
	: YangContainer("sync", id)
{
}

CntSync::~CntSync()
{
}

YangResult_E CntSync::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /sync/sync-group
	// Description:
	// -----------------------------------------------------------------------------
	GrpSyncGroup syncGroupInst(ITEM_SYNC_GROUP);
	syncGroupInst.initialise();
	addGroup(syncGroupInst);



	return YangResult_E::OK;
}





// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    sync-group
// Description:
// -----------------------------------------------------------------------------
GrpSyncGroup::GrpSyncGroup(uint32_t id)
	: YangGroup("sync-group", id)
{
}

GrpSyncGroup::~GrpSyncGroup()
{
}

YangResult_E GrpSyncGroup::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Container:   /sync-group/sync-status
	// Description: Object of this class provides synchronization state of the module.
	// -----------------------------------------------------------------------------
	CntSyncStatus syncStatusInst(ITEM_SYNC_STATUS);
	syncStatusInst.initialise();
	addContainer(syncStatusInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/sync-capability
	// Description: Object of this class provides synchronization capabilities of the module.
	// -----------------------------------------------------------------------------
	CntSyncCapability syncCapabilityInst(ITEM_SYNC_CAPABILITY);
	syncCapabilityInst.initialise();
	addContainer(syncCapabilityInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/ptp-config
	// Description: This MO defines configuration of Precise Time Protocol.
	// -----------------------------------------------------------------------------
	CntPtpConfig ptpConfigInst(ITEM_PTP_CONFIG);
	ptpConfigInst.initialise();
	addContainer(ptpConfigInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/ptp-status
	// Description: ptp status container
	// -----------------------------------------------------------------------------
	CntPtpStatus ptpStatusInst(ITEM_PTP_STATUS);
	ptpStatusInst.initialise();
	addContainer(ptpStatusInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/synce-config
	// Description: This container defines the configuration of SyncE
	// -----------------------------------------------------------------------------
	CntSynceConfig synceConfigInst(ITEM_SYNCE_CONFIG);
	synceConfigInst.initialise();
	addContainer(synceConfigInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/synce-status
	// Description: SyncE status container
	// -----------------------------------------------------------------------------
	CntSynceStatus synceStatusInst(ITEM_SYNCE_STATUS);
	synceStatusInst.initialise();
	addContainer(synceStatusInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/gnss-config
	// Description: This container defines the configuration of Global Navigation Satellite System (GNSS).
	// -----------------------------------------------------------------------------
	CntGnssConfig gnssConfigInst(ITEM_GNSS_CONFIG);
	gnssConfigInst.initialise();
	addContainer(gnssConfigInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/gnss-status
	// Description: Provides information about state of gps receiver
	// -----------------------------------------------------------------------------
	CntGnssStatus gnssStatusInst(ITEM_GNSS_STATUS);
	gnssStatusInst.initialise();
	addContainer(gnssStatusInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   sync-status
// Description: Object of this class provides synchronization state of the module.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSyncStatus::CntSyncStatus(uint32_t id)
	: YangContainer("sync-status", id)
{
}

GrpSyncGroup::CntSyncStatus::~CntSyncStatus()
{
}

YangResult_E GrpSyncGroup::CntSyncStatus::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/sync-status/sync-state
	// Description: State of DU synchronization
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafSyncState syncStateInst(ITEM_SYNC_STATE);
	addLeaf(syncStateInst);

	// -----------------------------------------------------------------------------
	// List:        /sync-group/sync-status/supported-reference-types
	// Description: Type of a synchronization supported source.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstSupportedReferenceTypes supportedReferenceTypesInst(ITEM_SUPPORTED_REFERENCE_TYPES);
	supportedReferenceTypesInst.initialise();
	addList(supportedReferenceTypesInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/sync-status/sync-state
// Description: State of DU synchronization
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSyncStatus::LeafSyncState::LeafSyncState(uint32_t id)
	: YangLeaf("sync-state", id)
{
}

GrpSyncGroup::CntSyncStatus::LeafSyncState::~LeafSyncState()
{
}

// -----------------------------------------------------------------------------
// List:        supported-reference-types
// Description: Type of a synchronization supported source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSyncStatus::LstSupportedReferenceTypes::LstSupportedReferenceTypes(uint32_t id)
	: YangList("supported-reference-types", id)
{
}

GrpSyncGroup::CntSyncStatus::LstSupportedReferenceTypes::~LstSupportedReferenceTypes()
{
}

YangResult_E GrpSyncGroup::CntSyncStatus::LstSupportedReferenceTypes::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/sync-status/supported-reference-types/item
	// Description: supported reference-type
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafItem itemInst(ITEM_ITEM);
	addLeaf(itemInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/sync-status/supported-reference-types/item
// Description: supported reference-type
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSyncStatus::LstSupportedReferenceTypes::LeafItem::LeafItem(uint32_t id)
	: YangLeaf("item", id)
{
}

GrpSyncGroup::CntSyncStatus::LstSupportedReferenceTypes::LeafItem::~LeafItem()
{
}






// -----------------------------------------------------------------------------
// Container:   sync-capability
// Description: Object of this class provides synchronization capabilities of the module.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSyncCapability::CntSyncCapability(uint32_t id)
	: YangContainer("sync-capability", id)
{
}

GrpSyncGroup::CntSyncCapability::~CntSyncCapability()
{
}

YangResult_E GrpSyncGroup::CntSyncCapability::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/sync-capability/sync-t-tsc
	// Description: This will provide information about T-TSC capability
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafSyncTTsc syncTTscInst(ITEM_SYNC_T_TSC);
	addLeaf(syncTTscInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/sync-capability/sync-t-tsc
// Description: This will provide information about T-TSC capability
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSyncCapability::LeafSyncTTsc::LeafSyncTTsc(uint32_t id)
	: YangLeaf("sync-t-tsc", id)
{
}

GrpSyncGroup::CntSyncCapability::LeafSyncTTsc::~LeafSyncTTsc()
{
}




// -----------------------------------------------------------------------------
// Container:   ptp-config
// Description: This MO defines configuration of Precise Time Protocol.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntPtpConfig(uint32_t id)
	: YangContainer("ptp-config", id)
{
}

GrpSyncGroup::CntPtpConfig::~CntPtpConfig()
{
}

YangResult_E GrpSyncGroup::CntPtpConfig::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-config/domain-number
	// Description: This parameter indicates Domain Number for PTP announce messages.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafDomainNumber domainNumberInst(ITEM_DOMAIN_NUMBER);
	addLeaf(domainNumberInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-config/ptp-profile
	// Description: Type of profile to be used in ptp setting
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafPtpProfile ptpProfileInst(ITEM_PTP_PROFILE);
	addLeaf(ptpProfileInst);

	// -----------------------------------------------------------------------------
	// List:        /sync-group/ptp-config/accepted-clock-classes
	// Description: Contains list of PTP acceptable Clock Classes, sorted in the descending order.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstAcceptedClockClasses acceptedClockClassesInst(ITEM_ACCEPTED_CLOCK_CLASSES);
	acceptedClockClassesInst.initialise();
	addList(acceptedClockClassesInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/ptp-config/g-8275-1-config
	// Description: Container allowing for configuration of G8275.1
	// -----------------------------------------------------------------------------
	CntG82751Config g82751ConfigInst(ITEM_G_8275_1_CONFIG);
	g82751ConfigInst.initialise();
	addContainer(g82751ConfigInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/ptp-config/g-8275-2-config
	// Description: Container used for configuration of G8275.2 profile
	// -----------------------------------------------------------------------------
	CntG82752Config g82752ConfigInst(ITEM_G_8275_2_CONFIG);
	g82752ConfigInst.initialise();
	addContainer(g82752ConfigInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-config/domain-number
// Description: This parameter indicates Domain Number for PTP announce messages.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::LeafDomainNumber::LeafDomainNumber(uint32_t id)
	: YangLeaf("domain-number", id)
{
}

GrpSyncGroup::CntPtpConfig::LeafDomainNumber::~LeafDomainNumber()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-config/ptp-profile
// Description: Type of profile to be used in ptp setting
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::LeafPtpProfile::LeafPtpProfile(uint32_t id)
	: YangLeaf("ptp-profile", id)
{
}

GrpSyncGroup::CntPtpConfig::LeafPtpProfile::~LeafPtpProfile()
{
}

// -----------------------------------------------------------------------------
// List:        accepted-clock-classes
// Description: Contains list of PTP acceptable Clock Classes, sorted in the descending order.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::LstAcceptedClockClasses::LstAcceptedClockClasses(uint32_t id)
	: YangList("accepted-clock-classes", id)
{
}

GrpSyncGroup::CntPtpConfig::LstAcceptedClockClasses::~LstAcceptedClockClasses()
{
}

YangResult_E GrpSyncGroup::CntPtpConfig::LstAcceptedClockClasses::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-config/accepted-clock-classes/clock-classes
	// Description: PTP Clock Class accepted by the O-RU
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafClockClasses clockClassesInst(ITEM_CLOCK_CLASSES);
	addLeaf(clockClassesInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-config/accepted-clock-classes/clock-classes
// Description: PTP Clock Class accepted by the O-RU
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::LstAcceptedClockClasses::LeafClockClasses::LeafClockClasses(uint32_t id)
	: YangLeaf("clock-classes", id)
{
}

GrpSyncGroup::CntPtpConfig::LstAcceptedClockClasses::LeafClockClasses::~LeafClockClasses()
{
}



// -----------------------------------------------------------------------------
// Container:   g-8275-1-config
// Description: Container allowing for configuration of G8275.1
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntG82751Config::CntG82751Config(uint32_t id)
	: YangContainer("g-8275-1-config", id)
{
}

GrpSyncGroup::CntPtpConfig::CntG82751Config::~CntG82751Config()
{
}

YangResult_E GrpSyncGroup::CntPtpConfig::CntG82751Config::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-config/g-8275-1-config/multicast-mac-address
	// Description: The parameter defines destination MAC address, used by the DU in the egress PTP messages.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafMulticastMacAddress multicastMacAddressInst(ITEM_MULTICAST_MAC_ADDRESS);
	addLeaf(multicastMacAddressInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-config/g-8275-1-config/delay-asymmetry
	// Description: Defines static phase error in the recovered PTP timing signal to be compensated at the O-RU.
	//              The error is defined in units of nanoseconds in the range ±10 000 ns.
	// Type:        int16
	// Units:
	// -----------------------------------------------------------------------------
	LeafDelayAsymmetry delayAsymmetryInst(ITEM_DELAY_ASYMMETRY);
	addLeaf(delayAsymmetryInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-config/g-8275-1-config/multicast-mac-address
// Description: The parameter defines destination MAC address, used by the DU in the egress PTP messages.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntG82751Config::LeafMulticastMacAddress::LeafMulticastMacAddress(uint32_t id)
	: YangLeaf("multicast-mac-address", id)
{
}

GrpSyncGroup::CntPtpConfig::CntG82751Config::LeafMulticastMacAddress::~LeafMulticastMacAddress()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-config/g-8275-1-config/delay-asymmetry
// Description: Defines static phase error in the recovered PTP timing signal to be compensated at the O-RU.
//              The error is defined in units of nanoseconds in the range ±10 000 ns.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntG82751Config::LeafDelayAsymmetry::LeafDelayAsymmetry(uint32_t id)
	: YangLeaf("delay-asymmetry", id)
{
}

GrpSyncGroup::CntPtpConfig::CntG82751Config::LeafDelayAsymmetry::~LeafDelayAsymmetry()
{
}




// -----------------------------------------------------------------------------
// Container:   g-8275-2-config
// Description: Container used for configuration of G8275.2 profile
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntG82752Config::CntG82752Config(uint32_t id)
	: YangContainer("g-8275-2-config", id)
{
}

GrpSyncGroup::CntPtpConfig::CntG82752Config::~CntG82752Config()
{
}

YangResult_E GrpSyncGroup::CntPtpConfig::CntG82752Config::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-config/g-8275-2-config/log-inter-sync-period
	// Description: The parameter defines number of sync message during 1 second
	// Type:        int8
	// Units:
	// -----------------------------------------------------------------------------
	LeafLogInterSyncPeriod logInterSyncPeriodInst(ITEM_LOG_INTER_SYNC_PERIOD);
	addLeaf(logInterSyncPeriodInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-config/g-8275-2-config/log-inter-announce-period
	// Description: The parameter defines number of announce message during 1 second
	// Type:        int8
	// Units:
	// -----------------------------------------------------------------------------
	LeafLogInterAnnouncePeriod logInterAnnouncePeriodInst(ITEM_LOG_INTER_ANNOUNCE_PERIOD);
	addLeaf(logInterAnnouncePeriodInst);

	// -----------------------------------------------------------------------------
	// Reference:   /sync-group/ptp-config/g-8275-2-config/local-ip-port
	// Description: Reference to interface name corresponding to IP interface
	//              used for G.8275.2
	// Ref:         /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name
	// Units:
	// -----------------------------------------------------------------------------
	RefLocalIpPort localIpPortInst(ITEM_LOCAL_IP_PORT);
	addReference(localIpPortInst);

	// -----------------------------------------------------------------------------
	// List:        /sync-group/ptp-config/g-8275-2-config/master-ip-configuration
	// Description: The parameter defines list of ip configuration of devices acting as ptp signal source.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstMasterIpConfiguration masterIpConfigurationInst(ITEM_MASTER_IP_CONFIGURATION);
	masterIpConfigurationInst.initialise();
	addList(masterIpConfigurationInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-config/g-8275-2-config/log-inter-sync-period
// Description: The parameter defines number of sync message during 1 second
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntG82752Config::LeafLogInterSyncPeriod::LeafLogInterSyncPeriod(uint32_t id)
	: YangLeaf("log-inter-sync-period", id)
{
}

GrpSyncGroup::CntPtpConfig::CntG82752Config::LeafLogInterSyncPeriod::~LeafLogInterSyncPeriod()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-config/g-8275-2-config/log-inter-announce-period
// Description: The parameter defines number of announce message during 1 second
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntG82752Config::LeafLogInterAnnouncePeriod::LeafLogInterAnnouncePeriod(uint32_t id)
	: YangLeaf("log-inter-announce-period", id)
{
}

GrpSyncGroup::CntPtpConfig::CntG82752Config::LeafLogInterAnnouncePeriod::~LeafLogInterAnnouncePeriod()
{
}

// -----------------------------------------------------------------------------
// Reference:   /sync-group/ptp-config/g-8275-2-config/local-ip-port
// Description: Reference to interface name corresponding to IP interface
//              used for G.8275.2
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntG82752Config::RefLocalIpPort::RefLocalIpPort(uint32_t id)
	: YangReference("local-ip-port", id, "/ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name")
{
}

GrpSyncGroup::CntPtpConfig::CntG82752Config::RefLocalIpPort::~RefLocalIpPort()
{
}

// -----------------------------------------------------------------------------
// List:        master-ip-configuration
// Description: The parameter defines list of ip configuration of devices acting as ptp signal source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntG82752Config::LstMasterIpConfiguration::LstMasterIpConfiguration(uint32_t id)
	: YangList("master-ip-configuration", id)
{
}

GrpSyncGroup::CntPtpConfig::CntG82752Config::LstMasterIpConfiguration::~LstMasterIpConfiguration()
{
}

YangResult_E GrpSyncGroup::CntPtpConfig::CntG82752Config::LstMasterIpConfiguration::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-config/g-8275-2-config/master-ip-configuration/local-priority
	// Description: The parameter defines local priority or underlying master IP address.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafLocalPriority localPriorityInst(ITEM_LOCAL_PRIORITY);
	addLeaf(localPriorityInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-config/g-8275-2-config/master-ip-configuration/ip-address
	// Description: the parameter defines master IP address.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafIpAddress ipAddressInst(ITEM_IP_ADDRESS);
	addLeaf(ipAddressInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-config/g-8275-2-config/master-ip-configuration/local-priority
// Description: The parameter defines local priority or underlying master IP address.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntG82752Config::LstMasterIpConfiguration::LeafLocalPriority::LeafLocalPriority(uint32_t id)
	: YangLeaf("local-priority", id)
{
}

GrpSyncGroup::CntPtpConfig::CntG82752Config::LstMasterIpConfiguration::LeafLocalPriority::~LeafLocalPriority()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-config/g-8275-2-config/master-ip-configuration/ip-address
// Description: the parameter defines master IP address.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpConfig::CntG82752Config::LstMasterIpConfiguration::LeafIpAddress::LeafIpAddress(uint32_t id)
	: YangLeaf("ip-address", id)
{
}

GrpSyncGroup::CntPtpConfig::CntG82752Config::LstMasterIpConfiguration::LeafIpAddress::~LeafIpAddress()
{
}









// -----------------------------------------------------------------------------
// Container:   ptp-status
// Description: ptp status container
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::CntPtpStatus(uint32_t id)
	: YangContainer("ptp-status", id)
{
}

GrpSyncGroup::CntPtpStatus::~CntPtpStatus()
{
}

YangResult_E GrpSyncGroup::CntPtpStatus::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/reporting-period
	// Description: This parameter defines minimum period in seconds between reports,
	//              sent by the NETCONF Client, for parameters in this container.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafReportingPeriod reportingPeriodInst(ITEM_REPORTING_PERIOD);
	addLeaf(reportingPeriodInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/lock-state
	// Description: This parameter indicates, whether the integrated ordinary clock is
	//              synchronizing to the reference, recovered from PTP signal.
	//              The exact definition when to indicate locked or unlocked is up to specific
	//              implementation.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafLockState lockStateInst(ITEM_LOCK_STATE);
	addLeaf(lockStateInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/clock-class
	// Description: This parameter contains the clock class of the clock, controlled by the O-RU
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafClockClass clockClassInst(ITEM_CLOCK_CLASS);
	addLeaf(clockClassInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/clock-identity
	// Description: This parameter contains identity of the clock,
	//               according to IEEE 1588-2008 defintion, controlled by the O-RU.
	//              The string shall be formatted as an 8-octet hex value with the '0x' prefix.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafClockIdentity clockIdentityInst(ITEM_CLOCK_IDENTITY);
	addLeaf(clockIdentityInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/partial-timing-supported
	// Description: Provides information wheter G.8275.2 (partial timing support from network) is supported.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafPartialTimingSupported partialTimingSupportedInst(ITEM_PARTIAL_TIMING_SUPPORTED);
	addLeaf(partialTimingSupportedInst);

	// -----------------------------------------------------------------------------
	// List:        /sync-group/ptp-status/sources
	// Description: Synchronisation sources
	// Array Key:
	// -----------------------------------------------------------------------------
	LstSources sourcesInst(ITEM_SOURCES);
	sourcesInst.initialise();
	addList(sourcesInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/reporting-period
// Description: This parameter defines minimum period in seconds between reports,
//              sent by the NETCONF Client, for parameters in this container.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LeafReportingPeriod::LeafReportingPeriod(uint32_t id)
	: YangLeaf("reporting-period", id)
{
}

GrpSyncGroup::CntPtpStatus::LeafReportingPeriod::~LeafReportingPeriod()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/lock-state
// Description: This parameter indicates, whether the integrated ordinary clock is
//              synchronizing to the reference, recovered from PTP signal.
//              The exact definition when to indicate locked or unlocked is up to specific
//              implementation.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LeafLockState::LeafLockState(uint32_t id)
	: YangLeaf("lock-state", id)
{
}

GrpSyncGroup::CntPtpStatus::LeafLockState::~LeafLockState()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/clock-class
// Description: This parameter contains the clock class of the clock, controlled by the O-RU
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LeafClockClass::LeafClockClass(uint32_t id)
	: YangLeaf("clock-class", id)
{
}

GrpSyncGroup::CntPtpStatus::LeafClockClass::~LeafClockClass()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/clock-identity
// Description: This parameter contains identity of the clock,
//               according to IEEE 1588-2008 defintion, controlled by the O-RU.
//              The string shall be formatted as an 8-octet hex value with the '0x' prefix.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LeafClockIdentity::LeafClockIdentity(uint32_t id)
	: YangLeaf("clock-identity", id)
{
}

GrpSyncGroup::CntPtpStatus::LeafClockIdentity::~LeafClockIdentity()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/partial-timing-supported
// Description: Provides information wheter G.8275.2 (partial timing support from network) is supported.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LeafPartialTimingSupported::LeafPartialTimingSupported(uint32_t id)
	: YangLeaf("partial-timing-supported", id)
{
}

GrpSyncGroup::CntPtpStatus::LeafPartialTimingSupported::~LeafPartialTimingSupported()
{
}

// -----------------------------------------------------------------------------
// List:        sources
// Description: Synchronisation sources
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LstSources(uint32_t id)
	: YangList("sources", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::~LstSources()
{
}

YangResult_E GrpSyncGroup::CntPtpStatus::LstSources::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/state
	// Description: This parameter indicates status of the PTP source
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafState stateInst(ITEM_STATE);
	addLeaf(stateInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/two-step-flag
	// Description: This parameter reflects status of the twoStepFlag attribute in Sync messages,
	//              received from the PTP source.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafTwoStepFlag twoStepFlagInst(ITEM_TWO_STEP_FLAG);
	addLeaf(twoStepFlagInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/leap61
	// Description: This parameter reflects status of the leap61 flag in Announce messages,
	//              received from the PTP source.
	//              When true, the last minute of the current UTC day contains 61 seconds.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafLeap61 leap61Inst(ITEM_LEAP61);
	addLeaf(leap61Inst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/leap59
	// Description: This parameter reflects status of the leap59 flag in Announce messages,
	//              received from the PTP source.
	//              When true, the last minute of the current UTC day contains 59 seconds.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafLeap59 leap59Inst(ITEM_LEAP59);
	addLeaf(leap59Inst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/current-utc-offset-valid
	// Description: This parameter reflects status of the currentUtcOffsetValid flag in
	//              Announce messages, received from the PTP source.
	//              When true, the current UTC offset is valid.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafCurrentUtcOffsetValid currentUtcOffsetValidInst(ITEM_CURRENT_UTC_OFFSET_VALID);
	addLeaf(currentUtcOffsetValidInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/ptp-timescale
	// Description: This parameter reflects status of the ptpTimescale flag in Announce
	//              messages, received from the PTP source.
	//
	//              When set, the clock timescale of the grandmaster clock is PTP;
	//              otherwise, the timescale is ARB (arbitrary)
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafPtpTimescale ptpTimescaleInst(ITEM_PTP_TIMESCALE);
	addLeaf(ptpTimescaleInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/time-traceable
	// Description: This parameter reflects status of the timeTraceable flag in Announce
	//              messages, received from the PTP source.
	//
	//              When true, the timescale and the currentUtcOffset are traceable to a
	//              primary reference
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafTimeTraceable timeTraceableInst(ITEM_TIME_TRACEABLE);
	addLeaf(timeTraceableInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/frequency-traceable
	// Description: This parameter reflects status of the frequencyTraceable flag in
	//              Announce messages, received from the PTP source.
	//
	//              When true, the frequency determining the timescale is traceable to a
	//              primary reference
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafFrequencyTraceable frequencyTraceableInst(ITEM_FREQUENCY_TRACEABLE);
	addLeaf(frequencyTraceableInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/source-clock-identity
	// Description: This parameter reflects value of the sourceClockIdentity attribute in
	//              Announce messages, received from the PTP source.
	//
	//              The string shall be formatted as an 8-octet hex value with the '0x'
	//              prefix.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafSourceClockIdentity sourceClockIdentityInst(ITEM_SOURCE_CLOCK_IDENTITY);
	addLeaf(sourceClockIdentityInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/source-port-number
	// Description: This parameter reflects value of the sourcePortNumber attribute in
	//              Announce messages, received from the PTP source.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafSourcePortNumber sourcePortNumberInst(ITEM_SOURCE_PORT_NUMBER);
	addLeaf(sourcePortNumberInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/current-utc-offset
	// Description: The offset between TAI and UTC when the epoch of the PTP system is
	//              the PTP epoch, i.e., when ptp-timescale is TRUE; otherwise, the value
	//              has no meaning
	// Type:        int16
	// Units:
	// -----------------------------------------------------------------------------
	LeafCurrentUtcOffset currentUtcOffsetInst(ITEM_CURRENT_UTC_OFFSET);
	addLeaf(currentUtcOffsetInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/priority1
	// Description: This parameter reflects value of the priority1 attribute in Announce
	//              messages, received from the PTP source.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafPriority1 priority1Inst(ITEM_PRIORITY1);
	addLeaf(priority1Inst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/clock-class
	// Description: This parameter reflects value of the clockClass attribute in
	//              Announce messages, received from the PTP source.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafClockClass clockClassInst(ITEM_CLOCK_CLASS);
	addLeaf(clockClassInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/clock-accuracy
	// Description: This parameter reflects value of the clockAccuracy attribute in
	//              Announce messages, received from the PTP source.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafClockAccuracy clockAccuracyInst(ITEM_CLOCK_ACCURACY);
	addLeaf(clockAccuracyInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/offset-scaled-log-variance
	// Description: This parameter reflects value of the offsetScaledLogVariance
	//              attribute in Announce messages, received from the PTP source.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafOffsetScaledLogVariance offsetScaledLogVarianceInst(ITEM_OFFSET_SCALED_LOG_VARIANCE);
	addLeaf(offsetScaledLogVarianceInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/priority2
	// Description: This parameter reflects value of the priority2 attribute in Announce
	//              messages, received from the PTP source.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafPriority2 priority2Inst(ITEM_PRIORITY2);
	addLeaf(priority2Inst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/grandmaster-clock-identity
	// Description: This parameter reflects value of the grandmasterClockIdentity
	//              attribute in Announce messages, received from the PTP source.
	//
	//              The string shall be formatted as an 8-octet hex value with the '0x'
	//              prefix.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafGrandmasterClockIdentity grandmasterClockIdentityInst(ITEM_GRANDMASTER_CLOCK_IDENTITY);
	addLeaf(grandmasterClockIdentityInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/steps-removed
	// Description: This parameter reflects value of the stepsRemoved attribute in
	//              Announce messages, received from the PTP source.
	//
	//              It indicates the number of communication paths traversed
	//              between the local clock and the grandmaster clock.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafStepsRemoved stepsRemovedInst(ITEM_STEPS_REMOVED);
	addLeaf(stepsRemovedInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/ptp-status/sources/time-source
	// Description: This parameter reflects value of the timeSource attribute in
	//              Announce messages, received from the PTP source.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafTimeSource timeSourceInst(ITEM_TIME_SOURCE);
	addLeaf(timeSourceInst);

	// -----------------------------------------------------------------------------
	// Reference:   /sync-group/ptp-status/sources/local-port-number
	// Description: This is reference to portNumber of ExternalEthernetPort to identify the port,
	//              where the PTP signal is located.
	// Ref:         /ietf-interfaces:interfaces/ietf-interfaces:interface/o-ran-interfaces:port-reference/o-ran-interfaces:port-number
	// Units:
	// -----------------------------------------------------------------------------
	RefLocalPortNumber localPortNumberInst(ITEM_LOCAL_PORT_NUMBER);
	addReference(localPortNumberInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/state
// Description: This parameter indicates status of the PTP source
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafState::LeafState(uint32_t id)
	: YangLeaf("state", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafState::~LeafState()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/two-step-flag
// Description: This parameter reflects status of the twoStepFlag attribute in Sync messages,
//              received from the PTP source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafTwoStepFlag::LeafTwoStepFlag(uint32_t id)
	: YangLeaf("two-step-flag", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafTwoStepFlag::~LeafTwoStepFlag()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/leap61
// Description: This parameter reflects status of the leap61 flag in Announce messages,
//              received from the PTP source.
//              When true, the last minute of the current UTC day contains 61 seconds.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafLeap61::LeafLeap61(uint32_t id)
	: YangLeaf("leap61", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafLeap61::~LeafLeap61()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/leap59
// Description: This parameter reflects status of the leap59 flag in Announce messages,
//              received from the PTP source.
//              When true, the last minute of the current UTC day contains 59 seconds.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafLeap59::LeafLeap59(uint32_t id)
	: YangLeaf("leap59", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafLeap59::~LeafLeap59()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/current-utc-offset-valid
// Description: This parameter reflects status of the currentUtcOffsetValid flag in
//              Announce messages, received from the PTP source.
//              When true, the current UTC offset is valid.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafCurrentUtcOffsetValid::LeafCurrentUtcOffsetValid(uint32_t id)
	: YangLeaf("current-utc-offset-valid", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafCurrentUtcOffsetValid::~LeafCurrentUtcOffsetValid()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/ptp-timescale
// Description: This parameter reflects status of the ptpTimescale flag in Announce
//              messages, received from the PTP source.
//
//              When set, the clock timescale of the grandmaster clock is PTP;
//              otherwise, the timescale is ARB (arbitrary)
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafPtpTimescale::LeafPtpTimescale(uint32_t id)
	: YangLeaf("ptp-timescale", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafPtpTimescale::~LeafPtpTimescale()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/time-traceable
// Description: This parameter reflects status of the timeTraceable flag in Announce
//              messages, received from the PTP source.
//
//              When true, the timescale and the currentUtcOffset are traceable to a
//              primary reference
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafTimeTraceable::LeafTimeTraceable(uint32_t id)
	: YangLeaf("time-traceable", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafTimeTraceable::~LeafTimeTraceable()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/frequency-traceable
// Description: This parameter reflects status of the frequencyTraceable flag in
//              Announce messages, received from the PTP source.
//
//              When true, the frequency determining the timescale is traceable to a
//              primary reference
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafFrequencyTraceable::LeafFrequencyTraceable(uint32_t id)
	: YangLeaf("frequency-traceable", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafFrequencyTraceable::~LeafFrequencyTraceable()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/source-clock-identity
// Description: This parameter reflects value of the sourceClockIdentity attribute in
//              Announce messages, received from the PTP source.
//
//              The string shall be formatted as an 8-octet hex value with the '0x'
//              prefix.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafSourceClockIdentity::LeafSourceClockIdentity(uint32_t id)
	: YangLeaf("source-clock-identity", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafSourceClockIdentity::~LeafSourceClockIdentity()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/source-port-number
// Description: This parameter reflects value of the sourcePortNumber attribute in
//              Announce messages, received from the PTP source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafSourcePortNumber::LeafSourcePortNumber(uint32_t id)
	: YangLeaf("source-port-number", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafSourcePortNumber::~LeafSourcePortNumber()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/current-utc-offset
// Description: The offset between TAI and UTC when the epoch of the PTP system is
//              the PTP epoch, i.e., when ptp-timescale is TRUE; otherwise, the value
//              has no meaning
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafCurrentUtcOffset::LeafCurrentUtcOffset(uint32_t id)
	: YangLeaf("current-utc-offset", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafCurrentUtcOffset::~LeafCurrentUtcOffset()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/priority1
// Description: This parameter reflects value of the priority1 attribute in Announce
//              messages, received from the PTP source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafPriority1::LeafPriority1(uint32_t id)
	: YangLeaf("priority1", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafPriority1::~LeafPriority1()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/clock-class
// Description: This parameter reflects value of the clockClass attribute in
//              Announce messages, received from the PTP source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafClockClass::LeafClockClass(uint32_t id)
	: YangLeaf("clock-class", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafClockClass::~LeafClockClass()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/clock-accuracy
// Description: This parameter reflects value of the clockAccuracy attribute in
//              Announce messages, received from the PTP source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafClockAccuracy::LeafClockAccuracy(uint32_t id)
	: YangLeaf("clock-accuracy", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafClockAccuracy::~LeafClockAccuracy()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/offset-scaled-log-variance
// Description: This parameter reflects value of the offsetScaledLogVariance
//              attribute in Announce messages, received from the PTP source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafOffsetScaledLogVariance::LeafOffsetScaledLogVariance(uint32_t id)
	: YangLeaf("offset-scaled-log-variance", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafOffsetScaledLogVariance::~LeafOffsetScaledLogVariance()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/priority2
// Description: This parameter reflects value of the priority2 attribute in Announce
//              messages, received from the PTP source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafPriority2::LeafPriority2(uint32_t id)
	: YangLeaf("priority2", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafPriority2::~LeafPriority2()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/grandmaster-clock-identity
// Description: This parameter reflects value of the grandmasterClockIdentity
//              attribute in Announce messages, received from the PTP source.
//
//              The string shall be formatted as an 8-octet hex value with the '0x'
//              prefix.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafGrandmasterClockIdentity::LeafGrandmasterClockIdentity(uint32_t id)
	: YangLeaf("grandmaster-clock-identity", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafGrandmasterClockIdentity::~LeafGrandmasterClockIdentity()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/steps-removed
// Description: This parameter reflects value of the stepsRemoved attribute in
//              Announce messages, received from the PTP source.
//
//              It indicates the number of communication paths traversed
//              between the local clock and the grandmaster clock.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafStepsRemoved::LeafStepsRemoved(uint32_t id)
	: YangLeaf("steps-removed", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafStepsRemoved::~LeafStepsRemoved()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/ptp-status/sources/time-source
// Description: This parameter reflects value of the timeSource attribute in
//              Announce messages, received from the PTP source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::LeafTimeSource::LeafTimeSource(uint32_t id)
	: YangLeaf("time-source", id)
{
}

GrpSyncGroup::CntPtpStatus::LstSources::LeafTimeSource::~LeafTimeSource()
{
}

// -----------------------------------------------------------------------------
// Reference:   /sync-group/ptp-status/sources/local-port-number
// Description: This is reference to portNumber of ExternalEthernetPort to identify the port,
//              where the PTP signal is located.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntPtpStatus::LstSources::RefLocalPortNumber::RefLocalPortNumber(uint32_t id)
	: YangReference("local-port-number", id, "/ietf-interfaces:interfaces/ietf-interfaces:interface/o-ran-interfaces:port-reference/o-ran-interfaces:port-number")
{
}

GrpSyncGroup::CntPtpStatus::LstSources::RefLocalPortNumber::~RefLocalPortNumber()
{
}






// -----------------------------------------------------------------------------
// Container:   synce-config
// Description: This container defines the configuration of SyncE
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSynceConfig::CntSynceConfig(uint32_t id)
	: YangContainer("synce-config", id)
{
}

GrpSyncGroup::CntSynceConfig::~CntSynceConfig()
{
}

YangResult_E GrpSyncGroup::CntSynceConfig::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/synce-config/ssm-timeout
	// Description: The parameter contains the value of maximum duration in seconds for which the actual SSM value may be different than configured values.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafSsmTimeout ssmTimeoutInst(ITEM_SSM_TIMEOUT);
	addLeaf(ssmTimeoutInst);

	// -----------------------------------------------------------------------------
	// List:        /sync-group/synce-config/acceptance-list-of-ssm
	// Description: The parameter contains the list of SyncE acceptable SSMs.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstAcceptanceListOfSsm acceptanceListOfSsmInst(ITEM_ACCEPTANCE_LIST_OF_SSM);
	acceptanceListOfSsmInst.initialise();
	addList(acceptanceListOfSsmInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/synce-config/ssm-timeout
// Description: The parameter contains the value of maximum duration in seconds for which the actual SSM value may be different than configured values.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSynceConfig::LeafSsmTimeout::LeafSsmTimeout(uint32_t id)
	: YangLeaf("ssm-timeout", id)
{
}

GrpSyncGroup::CntSynceConfig::LeafSsmTimeout::~LeafSsmTimeout()
{
}

// -----------------------------------------------------------------------------
// List:        acceptance-list-of-ssm
// Description: The parameter contains the list of SyncE acceptable SSMs.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSynceConfig::LstAcceptanceListOfSsm::LstAcceptanceListOfSsm(uint32_t id)
	: YangList("acceptance-list-of-ssm", id)
{
}

GrpSyncGroup::CntSynceConfig::LstAcceptanceListOfSsm::~LstAcceptanceListOfSsm()
{
}

YangResult_E GrpSyncGroup::CntSynceConfig::LstAcceptanceListOfSsm::initialise(void)
{


	return YangResult_E::OK;
}






// -----------------------------------------------------------------------------
// Container:   synce-status
// Description: SyncE status container
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSynceStatus::CntSynceStatus(uint32_t id)
	: YangContainer("synce-status", id)
{
}

GrpSyncGroup::CntSynceStatus::~CntSynceStatus()
{
}

YangResult_E GrpSyncGroup::CntSynceStatus::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/synce-status/reporting-period
	// Description: This parameter defines minimum period in seconds between reports,
	//              sent by the NETCONF client, for parameters in this container.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafReportingPeriod reportingPeriodInst(ITEM_REPORTING_PERIOD);
	addLeaf(reportingPeriodInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/synce-status/lock-state
	// Description: This parameter indicates, whether the integrated ordinary clock is
	//              synchronizing to the reference, recovered from SyncE signal.
	//
	//              The exact definition when to indicate locked or unlocked is up to
	//              specific implementation.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafLockState lockStateInst(ITEM_LOCK_STATE);
	addLeaf(lockStateInst);

	// -----------------------------------------------------------------------------
	// List:        /sync-group/synce-status/sources
	// Description: This parameter contains characteristics of SyncE sources of the clock, controlled by the O-RU.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstSources sourcesInst(ITEM_SOURCES);
	sourcesInst.initialise();
	addList(sourcesInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/synce-status/reporting-period
// Description: This parameter defines minimum period in seconds between reports,
//              sent by the NETCONF client, for parameters in this container.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSynceStatus::LeafReportingPeriod::LeafReportingPeriod(uint32_t id)
	: YangLeaf("reporting-period", id)
{
}

GrpSyncGroup::CntSynceStatus::LeafReportingPeriod::~LeafReportingPeriod()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/synce-status/lock-state
// Description: This parameter indicates, whether the integrated ordinary clock is
//              synchronizing to the reference, recovered from SyncE signal.
//
//              The exact definition when to indicate locked or unlocked is up to
//              specific implementation.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSynceStatus::LeafLockState::LeafLockState(uint32_t id)
	: YangLeaf("lock-state", id)
{
}

GrpSyncGroup::CntSynceStatus::LeafLockState::~LeafLockState()
{
}

// -----------------------------------------------------------------------------
// List:        sources
// Description: This parameter contains characteristics of SyncE sources of the clock, controlled by the O-RU.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSynceStatus::LstSources::LstSources(uint32_t id)
	: YangList("sources", id)
{
}

GrpSyncGroup::CntSynceStatus::LstSources::~LstSources()
{
}

YangResult_E GrpSyncGroup::CntSynceStatus::LstSources::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/synce-status/sources/state
	// Description: This parameter indicates status of the SyncE source
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafState stateInst(ITEM_STATE);
	addLeaf(stateInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/synce-status/sources/quality-level
	// Description: This parameter contains value of the SSM clock quality level,
	//              received in SSM messages from the SyncE source.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafQualityLevel qualityLevelInst(ITEM_QUALITY_LEVEL);
	addLeaf(qualityLevelInst);

	// -----------------------------------------------------------------------------
	// Reference:   /sync-group/synce-status/sources/local-port-number
	// Description: This is reference to portNumber of ExternalEthernetPort to identify
	//              the port, where the SyncE signal is located.
	// Ref:         /ietf-interfaces:interfaces/ietf-interfaces:interface/o-ran-interfaces:port-reference/o-ran-interfaces:port-number
	// Units:
	// -----------------------------------------------------------------------------
	RefLocalPortNumber localPortNumberInst(ITEM_LOCAL_PORT_NUMBER);
	addReference(localPortNumberInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/synce-status/sources/state
// Description: This parameter indicates status of the SyncE source
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSynceStatus::LstSources::LeafState::LeafState(uint32_t id)
	: YangLeaf("state", id)
{
}

GrpSyncGroup::CntSynceStatus::LstSources::LeafState::~LeafState()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/synce-status/sources/quality-level
// Description: This parameter contains value of the SSM clock quality level,
//              received in SSM messages from the SyncE source.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSynceStatus::LstSources::LeafQualityLevel::LeafQualityLevel(uint32_t id)
	: YangLeaf("quality-level", id)
{
}

GrpSyncGroup::CntSynceStatus::LstSources::LeafQualityLevel::~LeafQualityLevel()
{
}

// -----------------------------------------------------------------------------
// Reference:   /sync-group/synce-status/sources/local-port-number
// Description: This is reference to portNumber of ExternalEthernetPort to identify
//              the port, where the SyncE signal is located.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntSynceStatus::LstSources::RefLocalPortNumber::RefLocalPortNumber(uint32_t id)
	: YangReference("local-port-number", id, "/ietf-interfaces:interfaces/ietf-interfaces:interface/o-ran-interfaces:port-reference/o-ran-interfaces:port-number")
{
}

GrpSyncGroup::CntSynceStatus::LstSources::RefLocalPortNumber::~RefLocalPortNumber()
{
}






// -----------------------------------------------------------------------------
// Container:   gnss-config
// Description: This container defines the configuration of Global Navigation Satellite System (GNSS).
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssConfig::CntGnssConfig(uint32_t id)
	: YangContainer("gnss-config", id)
{
}

GrpSyncGroup::CntGnssConfig::~CntGnssConfig()
{
}

YangResult_E GrpSyncGroup::CntGnssConfig::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-config/enable
	// Description: This parameter defines if GNSS receiver shall be enabled or not.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafEnable enableInst(ITEM_ENABLE);
	addLeaf(enableInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-config/polarity
	// Description: This parameter defines pulse polarity
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafPolarity polarityInst(ITEM_POLARITY);
	addLeaf(polarityInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-config/cable-delay
	// Description: This parameter is used to compensate cable delay.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafCableDelay cableDelayInst(ITEM_CABLE_DELAY);
	addLeaf(cableDelayInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-config/anti-jam-enable
	// Description: This parameter is used to enable or disable anti-jamming.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafAntiJamEnable antiJamEnableInst(ITEM_ANTI_JAM_ENABLE);
	addLeaf(antiJamEnableInst);

	// -----------------------------------------------------------------------------
	// List:        /sync-group/gnss-config/satellite-constelation-list
	// Description: This parameter defines list of constellations to be used to acquire synchronization.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstSatelliteConstelationList satelliteConstelationListInst(ITEM_SATELLITE_CONSTELATION_LIST);
	satelliteConstelationListInst.initialise();
	addList(satelliteConstelationListInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-config/enable
// Description: This parameter defines if GNSS receiver shall be enabled or not.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssConfig::LeafEnable::LeafEnable(uint32_t id)
	: YangLeaf("enable", id)
{
}

GrpSyncGroup::CntGnssConfig::LeafEnable::~LeafEnable()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-config/polarity
// Description: This parameter defines pulse polarity
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssConfig::LeafPolarity::LeafPolarity(uint32_t id)
	: YangLeaf("polarity", id)
{
}

GrpSyncGroup::CntGnssConfig::LeafPolarity::~LeafPolarity()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-config/cable-delay
// Description: This parameter is used to compensate cable delay.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssConfig::LeafCableDelay::LeafCableDelay(uint32_t id)
	: YangLeaf("cable-delay", id)
{
}

GrpSyncGroup::CntGnssConfig::LeafCableDelay::~LeafCableDelay()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-config/anti-jam-enable
// Description: This parameter is used to enable or disable anti-jamming.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssConfig::LeafAntiJamEnable::LeafAntiJamEnable(uint32_t id)
	: YangLeaf("anti-jam-enable", id)
{
}

GrpSyncGroup::CntGnssConfig::LeafAntiJamEnable::~LeafAntiJamEnable()
{
}

// -----------------------------------------------------------------------------
// List:        satellite-constelation-list
// Description: This parameter defines list of constellations to be used to acquire synchronization.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssConfig::LstSatelliteConstelationList::LstSatelliteConstelationList(uint32_t id)
	: YangList("satellite-constelation-list", id)
{
}

GrpSyncGroup::CntGnssConfig::LstSatelliteConstelationList::~LstSatelliteConstelationList()
{
}

YangResult_E GrpSyncGroup::CntGnssConfig::LstSatelliteConstelationList::initialise(void)
{


	return YangResult_E::OK;
}






// -----------------------------------------------------------------------------
// Container:   gnss-status
// Description: Provides information about state of gps receiver
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssStatus::CntGnssStatus(uint32_t id)
	: YangContainer("gnss-status", id)
{
}

GrpSyncGroup::CntGnssStatus::~CntGnssStatus()
{
}

YangResult_E GrpSyncGroup::CntGnssStatus::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-status/reporting-period
	// Description: This parameter defines minimum period in seconds between reports,
	//              sent by the NETCONF Client, for parameters in this container.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafReportingPeriod reportingPeriodInst(ITEM_REPORTING_PERIOD);
	addLeaf(reportingPeriodInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-status/name
	// Description: A name that is unique that identifies a GNSS instance.
	//              This name may be used in fault management to refer to a
	//              fault source or affected object
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-status/gnss-sync-status
	// Description: when available, indicates the status of the gnss receiver.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafGnssSyncStatus gnssSyncStatusInst(ITEM_GNSS_SYNC_STATUS);
	addLeaf(gnssSyncStatusInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/gnss-status/gnss-data
	// Description: GPS data contained
	// -----------------------------------------------------------------------------
	CntGnssData gnssDataInst(ITEM_GNSS_DATA);
	gnssDataInst.initialise();
	addContainer(gnssDataInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-status/reporting-period
// Description: This parameter defines minimum period in seconds between reports,
//              sent by the NETCONF Client, for parameters in this container.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssStatus::LeafReportingPeriod::LeafReportingPeriod(uint32_t id)
	: YangLeaf("reporting-period", id)
{
}

GrpSyncGroup::CntGnssStatus::LeafReportingPeriod::~LeafReportingPeriod()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-status/name
// Description: A name that is unique that identifies a GNSS instance.
//              This name may be used in fault management to refer to a
//              fault source or affected object
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssStatus::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpSyncGroup::CntGnssStatus::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-status/gnss-sync-status
// Description: when available, indicates the status of the gnss receiver.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssStatus::LeafGnssSyncStatus::LeafGnssSyncStatus(uint32_t id)
	: YangLeaf("gnss-sync-status", id)
{
}

GrpSyncGroup::CntGnssStatus::LeafGnssSyncStatus::~LeafGnssSyncStatus()
{
}

// -----------------------------------------------------------------------------
// Container:   gnss-data
// Description: GPS data contained
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssStatus::CntGnssData::CntGnssData(uint32_t id)
	: YangContainer("gnss-data", id)
{
}

GrpSyncGroup::CntGnssStatus::CntGnssData::~CntGnssData()
{
}

YangResult_E GrpSyncGroup::CntGnssStatus::CntGnssData::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-status/gnss-data/satellites-tracked
	// Description: Number of satellites tracked
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafSatellitesTracked satellitesTrackedInst(ITEM_SATELLITES_TRACKED);
	addLeaf(satellitesTrackedInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync-group/gnss-status/gnss-data/location
	// Description: Containes information about geo location
	// -----------------------------------------------------------------------------
	CntLocation locationInst(ITEM_LOCATION);
	locationInst.initialise();
	addContainer(locationInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-status/gnss-data/satellites-tracked
// Description: Number of satellites tracked
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssStatus::CntGnssData::LeafSatellitesTracked::LeafSatellitesTracked(uint32_t id)
	: YangLeaf("satellites-tracked", id)
{
}

GrpSyncGroup::CntGnssStatus::CntGnssData::LeafSatellitesTracked::~LeafSatellitesTracked()
{
}

// -----------------------------------------------------------------------------
// Container:   location
// Description: Containes information about geo location
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssStatus::CntGnssData::CntLocation::CntLocation(uint32_t id)
	: YangContainer("location", id)
{
}

GrpSyncGroup::CntGnssStatus::CntGnssData::CntLocation::~CntLocation()
{
}

YangResult_E GrpSyncGroup::CntGnssStatus::CntGnssData::CntLocation::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-status/gnss-data/location/altitude
	// Description: Distance above the sea level.
	// Type:        int64
	// Units:       millimeter
	// -----------------------------------------------------------------------------
	LeafAltitude altitudeInst(ITEM_ALTITUDE);
	addLeaf(altitudeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-status/gnss-data/location/latitude
	// Description: Relative position north or south on the Earth's surface.
	// Type:        dec64
	// Units:
	// -----------------------------------------------------------------------------
	LeafLatitude latitudeInst(ITEM_LATITUDE);
	addLeaf(latitudeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /sync-group/gnss-status/gnss-data/location/longitude
	// Description: Angular distance east or west on the Earth's surface.
	// Type:        dec64
	// Units:
	// -----------------------------------------------------------------------------
	LeafLongitude longitudeInst(ITEM_LONGITUDE);
	addLeaf(longitudeInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-status/gnss-data/location/altitude
// Description: Distance above the sea level.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssStatus::CntGnssData::CntLocation::LeafAltitude::LeafAltitude(uint32_t id)
	: YangLeaf("altitude", id)
{
}

GrpSyncGroup::CntGnssStatus::CntGnssData::CntLocation::LeafAltitude::~LeafAltitude()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-status/gnss-data/location/latitude
// Description: Relative position north or south on the Earth's surface.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssStatus::CntGnssData::CntLocation::LeafLatitude::LeafLatitude(uint32_t id)
	: YangLeaf("latitude", id)
{
}

GrpSyncGroup::CntGnssStatus::CntGnssData::CntLocation::LeafLatitude::~LeafLatitude()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /sync-group/gnss-status/gnss-data/location/longitude
// Description: Angular distance east or west on the Earth's surface.
// -----------------------------------------------------------------------------
GrpSyncGroup::CntGnssStatus::CntGnssData::CntLocation::LeafLongitude::LeafLongitude(uint32_t id)
	: YangLeaf("longitude", id)
{
}

GrpSyncGroup::CntGnssStatus::CntGnssData::CntLocation::LeafLongitude::~LeafLongitude()
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
// -----------------------------------------------------------------------------
// Notification:synchronization-state-change
// Description: Notification used to inform about synchronization state change
// -----------------------------------------------------------------------------
NotifSynchronizationStateChange::NotifSynchronizationStateChange(uint32_t id)
	: YangNotif("synchronization-state-change", id)
{
}

NotifSynchronizationStateChange::~NotifSynchronizationStateChange()
{
}

YangResult_E NotifSynchronizationStateChange::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /synchronization-state-change/sync-state
	// Description: State of equipment synchronization is notified at state change
	// Ref:         /sync/sync-status/sync-state
	// Units:
	// -----------------------------------------------------------------------------
	RefSyncState syncStateInst(ITEM_SYNC_STATE);
	addReference(syncStateInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /synchronization-state-change/sync-state
// Description: State of equipment synchronization is notified at state change
// -----------------------------------------------------------------------------
NotifSynchronizationStateChange::RefSyncState::RefSyncState(uint32_t id)
	: YangReference("sync-state", id, "/sync/sync-status/sync-state")
{
}

NotifSynchronizationStateChange::RefSyncState::~RefSyncState()
{
}



// -----------------------------------------------------------------------------
// Notification:ptp-state-change
// Description: Notification used to inform about ptp synchronization state change
// -----------------------------------------------------------------------------
NotifPtpStateChange::NotifPtpStateChange(uint32_t id)
	: YangNotif("ptp-state-change", id)
{
}

NotifPtpStateChange::~NotifPtpStateChange()
{
}

YangResult_E NotifPtpStateChange::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /ptp-state-change/ptp-state
	// Description: ptp-state-change notification is signalled from equipment at state change
	// Ref:         /sync/ptp-status/lock-state
	// Units:
	// -----------------------------------------------------------------------------
	RefPtpState ptpStateInst(ITEM_PTP_STATE);
	addReference(ptpStateInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /ptp-state-change/ptp-state
// Description: ptp-state-change notification is signalled from equipment at state change
// -----------------------------------------------------------------------------
NotifPtpStateChange::RefPtpState::RefPtpState(uint32_t id)
	: YangReference("ptp-state", id, "/sync/ptp-status/lock-state")
{
}

NotifPtpStateChange::RefPtpState::~RefPtpState()
{
}



// -----------------------------------------------------------------------------
// Notification:synce-state-change
// Description: Notification used to inform about synce synchronization state change
// -----------------------------------------------------------------------------
NotifSynceStateChange::NotifSynceStateChange(uint32_t id)
	: YangNotif("synce-state-change", id)
{
}

NotifSynceStateChange::~NotifSynceStateChange()
{
}

YangResult_E NotifSynceStateChange::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /synce-state-change/synce-state
	// Description: synce-state change notification is signalled from equipment at state change
	// Ref:         /sync/synce-status/lock-state
	// Units:
	// -----------------------------------------------------------------------------
	RefSynceState synceStateInst(ITEM_SYNCE_STATE);
	addReference(synceStateInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /synce-state-change/synce-state
// Description: synce-state change notification is signalled from equipment at state change
// -----------------------------------------------------------------------------
NotifSynceStateChange::RefSynceState::RefSynceState(uint32_t id)
	: YangReference("synce-state", id, "/sync/synce-status/lock-state")
{
}

NotifSynceStateChange::RefSynceState::~RefSynceState()
{
}



// -----------------------------------------------------------------------------
// Notification:gnss-state-change
// Description: Notification used to inform about gnss synchronization state change
// -----------------------------------------------------------------------------
NotifGnssStateChange::NotifGnssStateChange(uint32_t id)
	: YangNotif("gnss-state-change", id)
{
}

NotifGnssStateChange::~NotifGnssStateChange()
{
}

YangResult_E NotifGnssStateChange::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /gnss-state-change/gnss-state
	// Description: gnss-state-change notification is signalled from equipment at state change
	// Ref:         /sync/gnss-status/gnss-sync-status
	// Units:
	// -----------------------------------------------------------------------------
	RefGnssState gnssStateInst(ITEM_GNSS_STATE);
	addReference(gnssStateInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /gnss-state-change/gnss-state
// Description: gnss-state-change notification is signalled from equipment at state change
// -----------------------------------------------------------------------------
NotifGnssStateChange::RefGnssState::RefGnssState(uint32_t id)
	: YangReference("gnss-state", id, "/sync/gnss-status/gnss-sync-status")
{
}

NotifGnssStateChange::RefGnssState::~RefGnssState()
{
}




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
ModuleORanSync::ModuleORanSync(uint32_t id)
	: YangModule ("o-ran-sync",
	              "o-ran-sync.yang",
	              "o-ran-sync",
	              "urn:o-ran:sync:1.0",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Feature
	// Description: This feature indicates that the equipment supports integrated GNSS functionality.
	// -----------------------------------------------------------------------------
	FeatureGNSS GNSSInst(ITEM_GNSS);
	addFeature(GNSSInst);

	// -----------------------------------------------------------------------------
	// Feature
	// Description: This feature indicates that the equipment supports Anti-jam fuctionality
	// -----------------------------------------------------------------------------
	FeatureANTIJAM ANTIJAMInst(ITEM_ANTI_JAM);
	addFeature(ANTIJAMInst);

	// -----------------------------------------------------------------------------
	// Container:   /sync
	// Description: Main containter for sync related parameters
	// -----------------------------------------------------------------------------
	CntSync syncInst(ITEM_SYNC);
	syncInst.initialise();
	addContainer(syncInst);

	// -----------------------------------------------------------------------------
	// Notification:/synchronization-state-change
	// Description: Notification used to inform about synchronization state change
	// -----------------------------------------------------------------------------
	NotifSynchronizationStateChange synchronizationStateChangeInst(ITEM_SYNCHRONIZATION_STATE_CHANGE);
	synchronizationStateChangeInst.initialise();
	addNotification(synchronizationStateChangeInst);

	// -----------------------------------------------------------------------------
	// Notification:/ptp-state-change
	// Description: Notification used to inform about ptp synchronization state change
	// -----------------------------------------------------------------------------
	NotifPtpStateChange ptpStateChangeInst(ITEM_PTP_STATE_CHANGE);
	ptpStateChangeInst.initialise();
	addNotification(ptpStateChangeInst);

	// -----------------------------------------------------------------------------
	// Notification:/synce-state-change
	// Description: Notification used to inform about synce synchronization state change
	// -----------------------------------------------------------------------------
	NotifSynceStateChange synceStateChangeInst(ITEM_SYNCE_STATE_CHANGE);
	synceStateChangeInst.initialise();
	addNotification(synceStateChangeInst);

	// -----------------------------------------------------------------------------
	// Notification:/gnss-state-change
	// Description: Notification used to inform about gnss synchronization state change
	// -----------------------------------------------------------------------------
	NotifGnssStateChange gnssStateChangeInst(ITEM_GNSS_STATE_CHANGE);
	gnssStateChangeInst.initialise();
	addNotification(gnssStateChangeInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleORanSync::~ModuleORanSync()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleORanSync::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleORanSync>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleORanSync::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
