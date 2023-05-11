/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanUplaneConf.cpp
 * \brief     Module ORanUplaneConf interface
 *
 *
 * \details   This file defines the YANG module o-ran-uplane-conf interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-uplane-conf"
 *            YANG Filename:    "o-ran-uplane-conf.yang"
 *            Module Prefix:    "o-ran-uplane-conf"
 *            Module namespace: "urn:o-ran:uplane-conf:1.0"
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
#include "YangModuleORanUplaneConf.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleORanUplaneConf_NS;

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
// Container:   user-plane-configuration
// Description: top level container for user plane configuration
// -----------------------------------------------------------------------------
CntUserPlaneConfiguration::CntUserPlaneConfiguration(uint32_t id)
	: YangContainer("user-plane-configuration", id)
{
}

CntUserPlaneConfiguration::~CntUserPlaneConfiguration()
{
}

YangResult_E CntUserPlaneConfiguration::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /user-plane-configuration/uplane-conf-group
	// Description:
	// -----------------------------------------------------------------------------
	GrpUplaneConfGroup uplaneConfGroupInst(ITEM_UPLANE_CONF_GROUP);
	uplaneConfGroupInst.initialise();
	addGroup(uplaneConfGroupInst);



	return YangResult_E::OK;
}





// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    laa-carrier-config
// Description: Carrier Configuration for support of LAA.
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::GrpLaaCarrierConfig(uint32_t id)
	: YangGroup("laa-carrier-config", id)
{
}

GrpLaaCarrierConfig::~GrpLaaCarrierConfig()
{
}

YangResult_E GrpLaaCarrierConfig::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /laa-carrier-config/ed-threshold-pdsch
	// Description: This value indicates Energy Detection(ED) threshold for LBT for PDSCH and for measurements in dBm.
	// Type:        int8
	// Units:       dBm
	// -----------------------------------------------------------------------------
	LeafEdThresholdPdsch edThresholdPdschInst(ITEM_ED_THRESHOLD_PDSCH);
	addLeaf(edThresholdPdschInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-carrier-config/ed-threshold-drs
	// Description: This value indicates Energy Detection(ED) threshold for LBT for DRS in dBm.
	// Type:        int8
	// Units:       dBm
	// -----------------------------------------------------------------------------
	LeafEdThresholdDrs edThresholdDrsInst(ITEM_ED_THRESHOLD_DRS);
	addLeaf(edThresholdDrsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-carrier-config/tx-antenna-ports
	// Description: This value indicates Tx antenna ports for DRS (1, 2, 4)
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafTxAntennaPorts txAntennaPortsInst(ITEM_TX_ANTENNA_PORTS);
	addLeaf(txAntennaPortsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-carrier-config/transmission-power-for-drs
	// Description: This value indicates offset of Cell specific reference Signal(CRS) power to reference signal power (dB).
	//              DRS signal consists of CRS, PSS, SSS, and optionally CSI-RS.
	// Type:        int8
	// Units:       decibels
	// -----------------------------------------------------------------------------
	LeafTransmissionPowerForDrs transmissionPowerForDrsInst(ITEM_TRANSMISSION_POWER_FOR_DRS);
	addLeaf(transmissionPowerForDrsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-carrier-config/dmtc-period
	// Description: This value indicates DRS measurement timing configuration (DMTC) period in ms
	// Type:        enum
	// Units:       milliseconds
	// -----------------------------------------------------------------------------
	LeafDmtcPeriod dmtcPeriodInst(ITEM_DMTC_PERIOD);
	addLeaf(dmtcPeriodInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-carrier-config/dmtc-offset
	// Description: This value indicates dmtc offset in Subframes.
	// Type:        uint8
	// Units:       subframes
	// -----------------------------------------------------------------------------
	LeafDmtcOffset dmtcOffsetInst(ITEM_DMTC_OFFSET);
	addLeaf(dmtcOffsetInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-carrier-config/lbt-timer
	// Description: This value indicates LBT Timer in milliseconds.
	// Type:        uint16
	// Units:       milliseconds
	// -----------------------------------------------------------------------------
	LeafLbtTimer lbtTimerInst(ITEM_LBT_TIMER);
	addLeaf(lbtTimerInst);

	// -----------------------------------------------------------------------------
	// List:        /laa-carrier-config/max-cw-usage-counter
	// Description:
	// Array Key:
	// -----------------------------------------------------------------------------
	LstMaxCwUsageCounter maxCwUsageCounterInst(ITEM_MAX_CW_USAGE_COUNTER);
	maxCwUsageCounterInst.initialise();
	addList(maxCwUsageCounterInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /laa-carrier-config/ed-threshold-pdsch
// Description: This value indicates Energy Detection(ED) threshold for LBT for PDSCH and for measurements in dBm.
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::LeafEdThresholdPdsch::LeafEdThresholdPdsch(uint32_t id)
	: YangLeaf("ed-threshold-pdsch", id)
{
}

GrpLaaCarrierConfig::LeafEdThresholdPdsch::~LeafEdThresholdPdsch()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /laa-carrier-config/ed-threshold-drs
// Description: This value indicates Energy Detection(ED) threshold for LBT for DRS in dBm.
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::LeafEdThresholdDrs::LeafEdThresholdDrs(uint32_t id)
	: YangLeaf("ed-threshold-drs", id)
{
}

GrpLaaCarrierConfig::LeafEdThresholdDrs::~LeafEdThresholdDrs()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /laa-carrier-config/tx-antenna-ports
// Description: This value indicates Tx antenna ports for DRS (1, 2, 4)
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::LeafTxAntennaPorts::LeafTxAntennaPorts(uint32_t id)
	: YangLeaf("tx-antenna-ports", id)
{
}

GrpLaaCarrierConfig::LeafTxAntennaPorts::~LeafTxAntennaPorts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /laa-carrier-config/transmission-power-for-drs
// Description: This value indicates offset of Cell specific reference Signal(CRS) power to reference signal power (dB).
//              DRS signal consists of CRS, PSS, SSS, and optionally CSI-RS.
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::LeafTransmissionPowerForDrs::LeafTransmissionPowerForDrs(uint32_t id)
	: YangLeaf("transmission-power-for-drs", id)
{
}

GrpLaaCarrierConfig::LeafTransmissionPowerForDrs::~LeafTransmissionPowerForDrs()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /laa-carrier-config/dmtc-period
// Description: This value indicates DRS measurement timing configuration (DMTC) period in ms
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::LeafDmtcPeriod::LeafDmtcPeriod(uint32_t id)
	: YangLeaf("dmtc-period", id)
{
}

GrpLaaCarrierConfig::LeafDmtcPeriod::~LeafDmtcPeriod()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /laa-carrier-config/dmtc-offset
// Description: This value indicates dmtc offset in Subframes.
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::LeafDmtcOffset::LeafDmtcOffset(uint32_t id)
	: YangLeaf("dmtc-offset", id)
{
}

GrpLaaCarrierConfig::LeafDmtcOffset::~LeafDmtcOffset()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /laa-carrier-config/lbt-timer
// Description: This value indicates LBT Timer in milliseconds.
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::LeafLbtTimer::LeafLbtTimer(uint32_t id)
	: YangLeaf("lbt-timer", id)
{
}

GrpLaaCarrierConfig::LeafLbtTimer::~LeafLbtTimer()
{
}

// -----------------------------------------------------------------------------
// List:        max-cw-usage-counter
// Description:
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::LstMaxCwUsageCounter::LstMaxCwUsageCounter(uint32_t id)
	: YangList("max-cw-usage-counter", id)
{
}

GrpLaaCarrierConfig::LstMaxCwUsageCounter::~LstMaxCwUsageCounter()
{
}

YangResult_E GrpLaaCarrierConfig::LstMaxCwUsageCounter::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /laa-carrier-config/max-cw-usage-counter/priority
	// Description: This value provides the priority class traffic for which the counter is calculated.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafPriority priorityInst(ITEM_PRIORITY);
	addLeaf(priorityInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /laa-carrier-config/max-cw-usage-counter/counter-value
	// Description: This value indicates the maximum value of counter
	//              which shows how many max congestion window value is used for backoff
	//              number of priority class traffic. This value is defined at 3GPP 36.213
	//              section 15.1.3 as K.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafCounterValue counterValueInst(ITEM_COUNTER_VALUE);
	addLeaf(counterValueInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /laa-carrier-config/max-cw-usage-counter/priority
// Description: This value provides the priority class traffic for which the counter is calculated.
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::LstMaxCwUsageCounter::LeafPriority::LeafPriority(uint32_t id)
	: YangLeaf("priority", id)
{
}

GrpLaaCarrierConfig::LstMaxCwUsageCounter::LeafPriority::~LeafPriority()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /laa-carrier-config/max-cw-usage-counter/counter-value
// Description: This value indicates the maximum value of counter
//              which shows how many max congestion window value is used for backoff
//              number of priority class traffic. This value is defined at 3GPP 36.213
//              section 15.1.3 as K.
// -----------------------------------------------------------------------------
GrpLaaCarrierConfig::LstMaxCwUsageCounter::LeafCounterValue::LeafCounterValue(uint32_t id)
	: YangLeaf("counter-value", id)
{
}

GrpLaaCarrierConfig::LstMaxCwUsageCounter::LeafCounterValue::~LeafCounterValue()
{
}





// -----------------------------------------------------------------------------
// Grouping:    eaxc
// Description: One eAxC identifier (eAxC ID) comprises a band and sector
//              identifier (BandSector_ID), a component-carrier identifier (CC_ID) and a
//              spatial stream identifier (RU_Port_ID).
//
//              In this version of the specification, one eAxC contains only one spatial
//              stream (i.e. one beam per subcarrier) at a time.
//
//              Bit allocation is subdivided as follows:
//              *    O_DU_Port_ID: Used to differentiate processing units at O-DU
//              *    BandSector_ID: Aggregated cell identifier
//              *    CC_ID: distinguishes Carrier Components
//              *    RU_Port_ID: Used to differentiate spatial streams or beams on the O-RU
//
//              The bitwidth of each of the above fields is variable this model is supposed to check
//               if we are occpying bits continuously but we do not have to occupy all 16 bits
// -----------------------------------------------------------------------------
GrpEaxc::GrpEaxc(uint32_t id)
	: YangGroup("eaxc", id)
{
}

GrpEaxc::~GrpEaxc()
{
}

YangResult_E GrpEaxc::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /eaxc/o-du-port-bitmask
	// Description: mask for eaxc-id bits used to encode O-DU Port ID
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafODuPortBitmask oDuPortBitmaskInst(ITEM_O_DU_PORT_BITMASK);
	addLeaf(oDuPortBitmaskInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /eaxc/band-sector-bitmask
	// Description: mask for eaxc-id bits used to encode the band sector ID
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafBandSectorBitmask bandSectorBitmaskInst(ITEM_BAND_SECTOR_BITMASK);
	addLeaf(bandSectorBitmaskInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /eaxc/ccid-bitmask
	// Description: mask for eaxc-id bits used to encode the component carrier id
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafCcidBitmask ccidBitmaskInst(ITEM_CCID_BITMASK);
	addLeaf(ccidBitmaskInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /eaxc/ru-port-bitmask
	// Description: mask for eaxc-id bits used to encode the O-RU Port ID
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafRuPortBitmask ruPortBitmaskInst(ITEM_RU_PORT_BITMASK);
	addLeaf(ruPortBitmaskInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /eaxc/eaxc-id
	// Description: encoded value of eaxcid to be read by CU-Plane
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafEaxcId eaxcIdInst(ITEM_EAXC_ID);
	addLeaf(eaxcIdInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /eaxc/o-du-port-bitmask
// Description: mask for eaxc-id bits used to encode O-DU Port ID
// -----------------------------------------------------------------------------
GrpEaxc::LeafODuPortBitmask::LeafODuPortBitmask(uint32_t id)
	: YangLeaf("o-du-port-bitmask", id)
{
}

GrpEaxc::LeafODuPortBitmask::~LeafODuPortBitmask()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /eaxc/band-sector-bitmask
// Description: mask for eaxc-id bits used to encode the band sector ID
// -----------------------------------------------------------------------------
GrpEaxc::LeafBandSectorBitmask::LeafBandSectorBitmask(uint32_t id)
	: YangLeaf("band-sector-bitmask", id)
{
}

GrpEaxc::LeafBandSectorBitmask::~LeafBandSectorBitmask()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /eaxc/ccid-bitmask
// Description: mask for eaxc-id bits used to encode the component carrier id
// -----------------------------------------------------------------------------
GrpEaxc::LeafCcidBitmask::LeafCcidBitmask(uint32_t id)
	: YangLeaf("ccid-bitmask", id)
{
}

GrpEaxc::LeafCcidBitmask::~LeafCcidBitmask()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /eaxc/ru-port-bitmask
// Description: mask for eaxc-id bits used to encode the O-RU Port ID
// -----------------------------------------------------------------------------
GrpEaxc::LeafRuPortBitmask::LeafRuPortBitmask(uint32_t id)
	: YangLeaf("ru-port-bitmask", id)
{
}

GrpEaxc::LeafRuPortBitmask::~LeafRuPortBitmask()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /eaxc/eaxc-id
// Description: encoded value of eaxcid to be read by CU-Plane
// -----------------------------------------------------------------------------
GrpEaxc::LeafEaxcId::LeafEaxcId(uint32_t id)
	: YangLeaf("eaxc-id", id)
{
}

GrpEaxc::LeafEaxcId::~LeafEaxcId()
{
}



// -----------------------------------------------------------------------------
// Grouping:    parameters
// Description: Grouping of all parameters common between UL and DL
// -----------------------------------------------------------------------------
GrpParameters::GrpParameters(uint32_t id)
	: YangGroup("parameters", id)
{
}

GrpParameters::~GrpParameters()
{
}

YangResult_E GrpParameters::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/name
	// Description: Unique name of array antenna
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/number-of-rows
	// Description: Number of rows array elements are shaped into - M
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafNumberOfRows numberOfRowsInst(ITEM_NUMBER_OF_ROWS);
	addLeaf(numberOfRowsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/number-of-columns
	// Description: Number of columns array elements are shaped into - N
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafNumberOfColumns numberOfColumnsInst(ITEM_NUMBER_OF_COLUMNS);
	addLeaf(numberOfColumnsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/number-of-array-layers
	// Description: Number of array layers array elements are shaped into - Q
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafNumberOfArrayLayers numberOfArrayLayersInst(ITEM_NUMBER_OF_ARRAY_LAYERS);
	addLeaf(numberOfArrayLayersInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/horizontal-spacing
	// Description: Average distance between centers of nearby AE in horizontal direction (in array coordinates system)
	// Type:        dec64
	// Units:       Meter
	// -----------------------------------------------------------------------------
	LeafHorizontalSpacing horizontalSpacingInst(ITEM_HORIZONTAL_SPACING);
	addLeaf(horizontalSpacingInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/vertical-spacing
	// Description: Average distance between centers of nearby AE in vertical direction (in array coordinates system)
	// Type:        dec64
	// Units:       Meter
	// -----------------------------------------------------------------------------
	LeafVerticalSpacing verticalSpacingInst(ITEM_VERTICAL_SPACING);
	addLeaf(verticalSpacingInst);

	// -----------------------------------------------------------------------------
	// Reference:   /parameters/band-number
	// Description: This parameter informing which frequency band particular antenna
	//              array is serving for.
	//              Intended use is to deal with multiband solutions.
	// Ref:         /o-ran-module-cap:module-capability/o-ran-module-cap:band-capabilities/o-ran-module-cap:band-number
	// Units:
	// -----------------------------------------------------------------------------
	RefBandNumber bandNumberInst(ITEM_BAND_NUMBER);
	addReference(bandNumberInst);

	// -----------------------------------------------------------------------------
	// List:        /parameters/polarisations
	// Description: List of supported polarisations.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstPolarisations polarisationsInst(ITEM_POLARISATIONS);
	polarisationsInst.initialise();
	addList(polarisationsInst);

	// -----------------------------------------------------------------------------
	// Container:   /parameters/normal-vector-direction
	// Description: Counter-clockwise rotation around z and y axis.
	// -----------------------------------------------------------------------------
	CntNormalVectorDirection normalVectorDirectionInst(ITEM_NORMAL_VECTOR_DIRECTION);
	normalVectorDirectionInst.initialise();
	addContainer(normalVectorDirectionInst);

	// -----------------------------------------------------------------------------
	// Container:   /parameters/leftmost-bottom-array-element-position
	// Description: Structure describing position of leftmost, bottom array element.
	// -----------------------------------------------------------------------------
	CntLeftmostBottomArrayElementPosition leftmostBottomArrayElementPositionInst(ITEM_LEFTMOST_BOTTOM_ARRAY_ELEMENT_POSITION);
	leftmostBottomArrayElementPositionInst.initialise();
	addContainer(leftmostBottomArrayElementPositionInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/name
// Description: Unique name of array antenna
// -----------------------------------------------------------------------------
GrpParameters::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpParameters::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/number-of-rows
// Description: Number of rows array elements are shaped into - M
// -----------------------------------------------------------------------------
GrpParameters::LeafNumberOfRows::LeafNumberOfRows(uint32_t id)
	: YangLeaf("number-of-rows", id)
{
}

GrpParameters::LeafNumberOfRows::~LeafNumberOfRows()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/number-of-columns
// Description: Number of columns array elements are shaped into - N
// -----------------------------------------------------------------------------
GrpParameters::LeafNumberOfColumns::LeafNumberOfColumns(uint32_t id)
	: YangLeaf("number-of-columns", id)
{
}

GrpParameters::LeafNumberOfColumns::~LeafNumberOfColumns()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/number-of-array-layers
// Description: Number of array layers array elements are shaped into - Q
// -----------------------------------------------------------------------------
GrpParameters::LeafNumberOfArrayLayers::LeafNumberOfArrayLayers(uint32_t id)
	: YangLeaf("number-of-array-layers", id)
{
}

GrpParameters::LeafNumberOfArrayLayers::~LeafNumberOfArrayLayers()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/horizontal-spacing
// Description: Average distance between centers of nearby AE in horizontal direction (in array coordinates system)
// -----------------------------------------------------------------------------
GrpParameters::LeafHorizontalSpacing::LeafHorizontalSpacing(uint32_t id)
	: YangLeaf("horizontal-spacing", id)
{
}

GrpParameters::LeafHorizontalSpacing::~LeafHorizontalSpacing()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/vertical-spacing
// Description: Average distance between centers of nearby AE in vertical direction (in array coordinates system)
// -----------------------------------------------------------------------------
GrpParameters::LeafVerticalSpacing::LeafVerticalSpacing(uint32_t id)
	: YangLeaf("vertical-spacing", id)
{
}

GrpParameters::LeafVerticalSpacing::~LeafVerticalSpacing()
{
}

// -----------------------------------------------------------------------------
// Reference:   /parameters/band-number
// Description: This parameter informing which frequency band particular antenna
//              array is serving for.
//              Intended use is to deal with multiband solutions.
// -----------------------------------------------------------------------------
GrpParameters::RefBandNumber::RefBandNumber(uint32_t id)
	: YangReference("band-number", id, "/o-ran-module-cap:module-capability/o-ran-module-cap:band-capabilities/o-ran-module-cap:band-number")
{
}

GrpParameters::RefBandNumber::~RefBandNumber()
{
}

// -----------------------------------------------------------------------------
// List:        polarisations
// Description: List of supported polarisations.
// -----------------------------------------------------------------------------
GrpParameters::LstPolarisations::LstPolarisations(uint32_t id)
	: YangList("polarisations", id)
{
}

GrpParameters::LstPolarisations::~LstPolarisations()
{
}

YangResult_E GrpParameters::LstPolarisations::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/polarisations/p
	// Description: Polarisation index. See CUS-plane
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafP pInst(ITEM_P);
	addLeaf(pInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/polarisations/polarisation
	// Description: Type of polarisation supported by array.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafPolarisation polarisationInst(ITEM_POLARISATION);
	addLeaf(polarisationInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/polarisations/p
// Description: Polarisation index. See CUS-plane
// -----------------------------------------------------------------------------
GrpParameters::LstPolarisations::LeafP::LeafP(uint32_t id)
	: YangLeaf("p", id)
{
}

GrpParameters::LstPolarisations::LeafP::~LeafP()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/polarisations/polarisation
// Description: Type of polarisation supported by array.
// -----------------------------------------------------------------------------
GrpParameters::LstPolarisations::LeafPolarisation::LeafPolarisation(uint32_t id)
	: YangLeaf("polarisation", id)
{
}

GrpParameters::LstPolarisations::LeafPolarisation::~LeafPolarisation()
{
}



// -----------------------------------------------------------------------------
// Container:   normal-vector-direction
// Description: Counter-clockwise rotation around z and y axis.
// -----------------------------------------------------------------------------
GrpParameters::CntNormalVectorDirection::CntNormalVectorDirection(uint32_t id)
	: YangContainer("normal-vector-direction", id)
{
}

GrpParameters::CntNormalVectorDirection::~CntNormalVectorDirection()
{
}

YangResult_E GrpParameters::CntNormalVectorDirection::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/normal-vector-direction/azimuth-angle
	// Description: Azimuth angle, counter-clockwise rotation around z-axis. Value 'zero' points to broad-side, value '90' points to y-axis
	// Type:        dec64
	// Units:       Degrees
	// -----------------------------------------------------------------------------
	LeafAzimuthAngle azimuthAngleInst(ITEM_AZIMUTH_ANGLE);
	addLeaf(azimuthAngleInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/normal-vector-direction/zenith-angle
	// Description: Zenith angle, counter-clockwise rotation around y-axis. Value 'zero' points to zenith, value '90' points to horizon
	// Type:        dec64
	// Units:       Degrees
	// -----------------------------------------------------------------------------
	LeafZenithAngle zenithAngleInst(ITEM_ZENITH_ANGLE);
	addLeaf(zenithAngleInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/normal-vector-direction/azimuth-angle
// Description: Azimuth angle, counter-clockwise rotation around z-axis. Value 'zero' points to broad-side, value '90' points to y-axis
// -----------------------------------------------------------------------------
GrpParameters::CntNormalVectorDirection::LeafAzimuthAngle::LeafAzimuthAngle(uint32_t id)
	: YangLeaf("azimuth-angle", id)
{
}

GrpParameters::CntNormalVectorDirection::LeafAzimuthAngle::~LeafAzimuthAngle()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/normal-vector-direction/zenith-angle
// Description: Zenith angle, counter-clockwise rotation around y-axis. Value 'zero' points to zenith, value '90' points to horizon
// -----------------------------------------------------------------------------
GrpParameters::CntNormalVectorDirection::LeafZenithAngle::LeafZenithAngle(uint32_t id)
	: YangLeaf("zenith-angle", id)
{
}

GrpParameters::CntNormalVectorDirection::LeafZenithAngle::~LeafZenithAngle()
{
}




// -----------------------------------------------------------------------------
// Container:   leftmost-bottom-array-element-position
// Description: Structure describing position of leftmost, bottom array element.
// -----------------------------------------------------------------------------
GrpParameters::CntLeftmostBottomArrayElementPosition::CntLeftmostBottomArrayElementPosition(uint32_t id)
	: YangContainer("leftmost-bottom-array-element-position", id)
{
}

GrpParameters::CntLeftmostBottomArrayElementPosition::~CntLeftmostBottomArrayElementPosition()
{
}

YangResult_E GrpParameters::CntLeftmostBottomArrayElementPosition::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/leftmost-bottom-array-element-position/x
	// Description: X dimension of position of leftmost, bottom array element
	// Type:        dec64
	// Units:       Meter
	// -----------------------------------------------------------------------------
	LeafX xInst(ITEM_X);
	addLeaf(xInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/leftmost-bottom-array-element-position/y
	// Description: Y dimension of position of leftmost, bottom array element
	// Type:        dec64
	// Units:       Meter
	// -----------------------------------------------------------------------------
	LeafY yInst(ITEM_Y);
	addLeaf(yInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /parameters/leftmost-bottom-array-element-position/z
	// Description: Z dimension of position of leftmost, bottom array element
	// Type:        dec64
	// Units:       Meter
	// -----------------------------------------------------------------------------
	LeafZ zInst(ITEM_Z);
	addLeaf(zInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/leftmost-bottom-array-element-position/x
// Description: X dimension of position of leftmost, bottom array element
// -----------------------------------------------------------------------------
GrpParameters::CntLeftmostBottomArrayElementPosition::LeafX::LeafX(uint32_t id)
	: YangLeaf("x", id)
{
}

GrpParameters::CntLeftmostBottomArrayElementPosition::LeafX::~LeafX()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/leftmost-bottom-array-element-position/y
// Description: Y dimension of position of leftmost, bottom array element
// -----------------------------------------------------------------------------
GrpParameters::CntLeftmostBottomArrayElementPosition::LeafY::LeafY(uint32_t id)
	: YangLeaf("y", id)
{
}

GrpParameters::CntLeftmostBottomArrayElementPosition::LeafY::~LeafY()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /parameters/leftmost-bottom-array-element-position/z
// Description: Z dimension of position of leftmost, bottom array element
// -----------------------------------------------------------------------------
GrpParameters::CntLeftmostBottomArrayElementPosition::LeafZ::LeafZ(uint32_t id)
	: YangLeaf("z", id)
{
}

GrpParameters::CntLeftmostBottomArrayElementPosition::LeafZ::~LeafZ()
{
}






// -----------------------------------------------------------------------------
// Grouping:    array-choice
// Description: Elements which groups choice for antenna type
// -----------------------------------------------------------------------------
GrpArrayChoice::GrpArrayChoice(uint32_t id)
	: YangGroup("array-choice", id)
{
}

GrpArrayChoice::~GrpArrayChoice()
{
}

YangResult_E GrpArrayChoice::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Choice:      /array-choice/antenna-type
	// Description: Choice for antenna type
	// Type:        AntennaType_E
	// Units:       -
	// -----------------------------------------------------------------------------
	ChoiceAntennaType antennaTypeInst(ITEM_ANTENNA_TYPE);
	antennaTypeInst.initialise();
	addChoice(antennaTypeInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Choice:      antenna-type
// Description: Choice for antenna type
// -----------------------------------------------------------------------------
GrpArrayChoice::ChoiceAntennaType::ChoiceAntennaType(uint32_t id)
	: YangChoice("antenna-type", id)
{
}

GrpArrayChoice::ChoiceAntennaType::~ChoiceAntennaType()
{
}

YangResult_E GrpArrayChoice::ChoiceAntennaType::initialise(void)
{

	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptTx tx(ITEM_TX);
	tx.initialise();
	addOption(tx);


	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptRx rx(ITEM_RX);
	rx.initialise();
	addOption(rx);



	return YangResult_E::OK;
}


// -------------------------------------------------------------------------
// Option:      /array-choice/antenna-type[tx]
// -------------------------------------------------------------------------
GrpArrayChoice::ChoiceAntennaType::OptTx::OptTx(uint32_t id)
	: YangChoiceOption("tx", id)
{
}

GrpArrayChoice::ChoiceAntennaType::OptTx::~OptTx()
{
}

YangResult_E GrpArrayChoice::ChoiceAntennaType::OptTx::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /array-choice/antenna-type[tx]/tx-array-name
	// Description: Leafref to tx array if such is choosen
	// Ref:         /o-ran-uplane-conf:user-plane-configuration/o-ran-uplane-conf:tx-arrays/o-ran-uplane-conf:name
	// Units:
	// -----------------------------------------------------------------------------
	RefTxArrayName txArrayNameInst(ITEM_TX_ARRAY_NAME);
	addReference(txArrayNameInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /array-choice/antenna-type[tx]/tx-array-name
// Description: Leafref to tx array if such is choosen
// -----------------------------------------------------------------------------
GrpArrayChoice::ChoiceAntennaType::OptTx::RefTxArrayName::RefTxArrayName(uint32_t id)
	: YangReference("tx-array-name", id, "/o-ran-uplane-conf:user-plane-configuration/o-ran-uplane-conf:tx-arrays/o-ran-uplane-conf:name")
{
}

GrpArrayChoice::ChoiceAntennaType::OptTx::RefTxArrayName::~RefTxArrayName()
{
}



// -------------------------------------------------------------------------
// Option:      /array-choice/antenna-type[rx]
// -------------------------------------------------------------------------
GrpArrayChoice::ChoiceAntennaType::OptRx::OptRx(uint32_t id)
	: YangChoiceOption("rx", id)
{
}

GrpArrayChoice::ChoiceAntennaType::OptRx::~OptRx()
{
}

YangResult_E GrpArrayChoice::ChoiceAntennaType::OptRx::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /array-choice/antenna-type[rx]/rx-array-name
	// Description: Leafref to rx array if such is choosen
	// Ref:         /o-ran-uplane-conf:user-plane-configuration/o-ran-uplane-conf:rx-arrays/o-ran-uplane-conf:name
	// Units:
	// -----------------------------------------------------------------------------
	RefRxArrayName rxArrayNameInst(ITEM_RX_ARRAY_NAME);
	addReference(rxArrayNameInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /array-choice/antenna-type[rx]/rx-array-name
// Description: Leafref to rx array if such is choosen
// -----------------------------------------------------------------------------
GrpArrayChoice::ChoiceAntennaType::OptRx::RefRxArrayName::RefRxArrayName(uint32_t id)
	: YangReference("rx-array-name", id, "/o-ran-uplane-conf:user-plane-configuration/o-ran-uplane-conf:rx-arrays/o-ran-uplane-conf:name")
{
}

GrpArrayChoice::ChoiceAntennaType::OptRx::RefRxArrayName::~RefRxArrayName()
{
}








// -----------------------------------------------------------------------------
// Grouping:    scs-config
// Description: It groups all parameters related to SCS configuration
// -----------------------------------------------------------------------------
GrpScsConfig::GrpScsConfig(uint32_t id)
	: YangGroup("scs-config", id)
{
}

GrpScsConfig::~GrpScsConfig()
{
}

YangResult_E GrpScsConfig::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /scs-config/frame-structure
	// Description: This parameter defines the frame structure. The first 4 bits define the FFT/iFFT size
	//              being used for all IQ data processing related to this message.
	//              The second 4 bits define the sub carrier spacing as well as the number of slots per 1ms sub-frame
	//              according to 3GPP TS 38.211, taking for completeness also 3GPP TS 36.211 into account
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafFrameStructure frameStructureInst(ITEM_FRAME_STRUCTURE);
	addLeaf(frameStructureInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /scs-config/cp-type
	// Description: Provides type of CP (cyclic prefix) if section type 3 is not used or type of CP cannot be determined from cpLength.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafCpType cpTypeInst(ITEM_CP_TYPE);
	addLeaf(cpTypeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /scs-config/cp-length
	// Description: Used for symbol 0 for NR & LTE, and symbol 7*2u for NR.
	//              See CUS-plane
	// Type:        uint16
	// Units:       Ts
	// -----------------------------------------------------------------------------
	LeafCpLength cpLengthInst(ITEM_CP_LENGTH);
	addLeaf(cpLengthInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /scs-config/cp-length-other
	// Description: Used for other symbols than by cp-length above
	// Type:        uint16
	// Units:       Ts
	// -----------------------------------------------------------------------------
	LeafCpLengthOther cpLengthOtherInst(ITEM_CP_LENGTH_OTHER);
	addLeaf(cpLengthOtherInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /scs-config/offset-to-absolute-frequency-center
	// Description: This provides value of freqOffset to be used if section type 3 is not used. See freqOffset in CUS-plane.
	// Type:        int32
	// Units:
	// -----------------------------------------------------------------------------
	LeafOffsetToAbsoluteFrequencyCenter offsetToAbsoluteFrequencyCenterInst(ITEM_OFFSET_TO_ABSOLUTE_FREQUENCY_CENTER);
	addLeaf(offsetToAbsoluteFrequencyCenterInst);

	// -----------------------------------------------------------------------------
	// List:        /scs-config/number-of-prb-per-scs
	// Description: List of configured for each SCS that will be used.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstNumberOfPrbPerScs numberOfPrbPerScsInst(ITEM_NUMBER_OF_PRB_PER_SCS);
	numberOfPrbPerScsInst.initialise();
	addList(numberOfPrbPerScsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /scs-config/frame-structure
// Description: This parameter defines the frame structure. The first 4 bits define the FFT/iFFT size
//              being used for all IQ data processing related to this message.
//              The second 4 bits define the sub carrier spacing as well as the number of slots per 1ms sub-frame
//              according to 3GPP TS 38.211, taking for completeness also 3GPP TS 36.211 into account
// -----------------------------------------------------------------------------
GrpScsConfig::LeafFrameStructure::LeafFrameStructure(uint32_t id)
	: YangLeaf("frame-structure", id)
{
}

GrpScsConfig::LeafFrameStructure::~LeafFrameStructure()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /scs-config/cp-type
// Description: Provides type of CP (cyclic prefix) if section type 3 is not used or type of CP cannot be determined from cpLength.
// -----------------------------------------------------------------------------
GrpScsConfig::LeafCpType::LeafCpType(uint32_t id)
	: YangLeaf("cp-type", id)
{
}

GrpScsConfig::LeafCpType::~LeafCpType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /scs-config/cp-length
// Description: Used for symbol 0 for NR & LTE, and symbol 7*2u for NR.
//              See CUS-plane
// -----------------------------------------------------------------------------
GrpScsConfig::LeafCpLength::LeafCpLength(uint32_t id)
	: YangLeaf("cp-length", id)
{
}

GrpScsConfig::LeafCpLength::~LeafCpLength()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /scs-config/cp-length-other
// Description: Used for other symbols than by cp-length above
// -----------------------------------------------------------------------------
GrpScsConfig::LeafCpLengthOther::LeafCpLengthOther(uint32_t id)
	: YangLeaf("cp-length-other", id)
{
}

GrpScsConfig::LeafCpLengthOther::~LeafCpLengthOther()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /scs-config/offset-to-absolute-frequency-center
// Description: This provides value of freqOffset to be used if section type 3 is not used. See freqOffset in CUS-plane.
// -----------------------------------------------------------------------------
GrpScsConfig::LeafOffsetToAbsoluteFrequencyCenter::LeafOffsetToAbsoluteFrequencyCenter(uint32_t id)
	: YangLeaf("offset-to-absolute-frequency-center", id)
{
}

GrpScsConfig::LeafOffsetToAbsoluteFrequencyCenter::~LeafOffsetToAbsoluteFrequencyCenter()
{
}

// -----------------------------------------------------------------------------
// List:        number-of-prb-per-scs
// Description: List of configured for each SCS that will be used.
// -----------------------------------------------------------------------------
GrpScsConfig::LstNumberOfPrbPerScs::LstNumberOfPrbPerScs(uint32_t id)
	: YangList("number-of-prb-per-scs", id)
{
}

GrpScsConfig::LstNumberOfPrbPerScs::~LstNumberOfPrbPerScs()
{
}

YangResult_E GrpScsConfig::LstNumberOfPrbPerScs::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /scs-config/number-of-prb-per-scs/scs
	// Description: Value corresponds to SCS values defined for frameStructure in C-plane.
	//              Note: set of allowed values is restricted by SCS derived from values in supported-frame-structures.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafScs scsInst(ITEM_SCS);
	addLeaf(scsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /scs-config/number-of-prb-per-scs/number-of-prb
	// Description: Determines max number of PRBs that will be used in all sections per one symbol.
	//              This is affecting allocation of resources to endpoint. Value shall not exceed constrains
	//              defined by max-prb-per-symbol of endpoint type. In addition sum (over all used epoints
	//              within a group of endpoints sharing resources) of number-of-prb rounded up to
	//              nearest value from prb-capacity-allocation-granularity shall not exceed max-prb-per-symbol of the group.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafNumberOfPrb numberOfPrbInst(ITEM_NUMBER_OF_PRB);
	addLeaf(numberOfPrbInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /scs-config/number-of-prb-per-scs/scs
// Description: Value corresponds to SCS values defined for frameStructure in C-plane.
//              Note: set of allowed values is restricted by SCS derived from values in supported-frame-structures.
// -----------------------------------------------------------------------------
GrpScsConfig::LstNumberOfPrbPerScs::LeafScs::LeafScs(uint32_t id)
	: YangLeaf("scs", id)
{
}

GrpScsConfig::LstNumberOfPrbPerScs::LeafScs::~LeafScs()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /scs-config/number-of-prb-per-scs/number-of-prb
// Description: Determines max number of PRBs that will be used in all sections per one symbol.
//              This is affecting allocation of resources to endpoint. Value shall not exceed constrains
//              defined by max-prb-per-symbol of endpoint type. In addition sum (over all used epoints
//              within a group of endpoints sharing resources) of number-of-prb rounded up to
//              nearest value from prb-capacity-allocation-granularity shall not exceed max-prb-per-symbol of the group.
// -----------------------------------------------------------------------------
GrpScsConfig::LstNumberOfPrbPerScs::LeafNumberOfPrb::LeafNumberOfPrb(uint32_t id)
	: YangLeaf("number-of-prb", id)
{
}

GrpScsConfig::LstNumberOfPrbPerScs::LeafNumberOfPrb::~LeafNumberOfPrb()
{
}





// -----------------------------------------------------------------------------
// Grouping:    tx-common-array-carrier-elements
// Description: This grouping containes all common parameters for tx-array-carriers and rx-array-carriers
// -----------------------------------------------------------------------------
GrpTxCommonArrayCarrierElements::GrpTxCommonArrayCarrierElements(uint32_t id)
	: YangGroup("tx-common-array-carrier-elements", id)
{
}

GrpTxCommonArrayCarrierElements::~GrpTxCommonArrayCarrierElements()
{
}

YangResult_E GrpTxCommonArrayCarrierElements::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /tx-common-array-carrier-elements/absolute-frequency-center
	// Description: Absolute Radio Frequency Channel Number - indirectly indicates RF center carrier frequency of signal.
	//              Reflected in arfcn.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafAbsoluteFrequencyCenter absoluteFrequencyCenterInst(ITEM_ABSOLUTE_FREQUENCY_CENTER);
	addLeaf(absoluteFrequencyCenterInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /tx-common-array-carrier-elements/center-of-channel-bandwidth
	// Description: Center frequency of channel bandwidth in Hz. Common for all numerologies.
	// Type:        uint64
	// Units:       Hz
	// -----------------------------------------------------------------------------
	LeafCenterOfChannelBandwidth centerOfChannelBandwidthInst(ITEM_CENTER_OF_CHANNEL_BANDWIDTH);
	addLeaf(centerOfChannelBandwidthInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /tx-common-array-carrier-elements/channel-bandwidth
	// Description: Width of carrier given in Hertz
	// Type:        uint64
	// Units:       Hz
	// -----------------------------------------------------------------------------
	LeafChannelBandwidth channelBandwidthInst(ITEM_CHANNEL_BANDWIDTH);
	addLeaf(channelBandwidthInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /tx-common-array-carrier-elements/active
	// Description: Indicates if transmission is enabled for this array carriers. Note that Netconf server uses state parameter
	//              to indicate actual state of array carriers operation. When array carriers is in sleep status,
	//              Netconf server rejects all other operation request to tx-array-carriers object except either request to change from sleep
	//              to active status or delete MO operation (see 4.8) to the object.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafActive activeInst(ITEM_ACTIVE);
	addLeaf(activeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /tx-common-array-carrier-elements/state
	// Description: Indicates state of array carriers activation operation
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafState stateInst(ITEM_STATE);
	addLeaf(stateInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /tx-common-array-carrier-elements/type
	// Description: Type of carrier. Indicates array-carrier technology.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafType typeInst(ITEM_TYPE);
	addLeaf(typeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /tx-common-array-carrier-elements/duplex-scheme
	// Description: Type of duplex scheme O-RU supports.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafDuplexScheme duplexSchemeInst(ITEM_DUPLEX_SCHEME);
	addLeaf(duplexSchemeInst);

	// -----------------------------------------------------------------------------
	// Reference:   /tx-common-array-carrier-elements/rw-duplex-scheme
	// Description: Config true type of duplex scheme.
	// Ref:         /user-plane-configuration/tx-array-carriers[name=current()/../name]/duplex-scheme
	// Units:
	// -----------------------------------------------------------------------------
	RefRwDuplexScheme rwDuplexSchemeInst(ITEM_RW_DUPLEX_SCHEME);
	addReference(rwDuplexSchemeInst);

	// -----------------------------------------------------------------------------
	// Reference:   /tx-common-array-carrier-elements/rw-type
	// Description: Config true type of carrier.
	// Ref:         /user-plane-configuration/tx-array-carriers[name=current()/../name]/type
	// Units:
	// -----------------------------------------------------------------------------
	RefRwType rwTypeInst(ITEM_RW_TYPE);
	addReference(rwTypeInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /tx-common-array-carrier-elements/absolute-frequency-center
// Description: Absolute Radio Frequency Channel Number - indirectly indicates RF center carrier frequency of signal.
//              Reflected in arfcn.
// -----------------------------------------------------------------------------
GrpTxCommonArrayCarrierElements::LeafAbsoluteFrequencyCenter::LeafAbsoluteFrequencyCenter(uint32_t id)
	: YangLeaf("absolute-frequency-center", id)
{
}

GrpTxCommonArrayCarrierElements::LeafAbsoluteFrequencyCenter::~LeafAbsoluteFrequencyCenter()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /tx-common-array-carrier-elements/center-of-channel-bandwidth
// Description: Center frequency of channel bandwidth in Hz. Common for all numerologies.
// -----------------------------------------------------------------------------
GrpTxCommonArrayCarrierElements::LeafCenterOfChannelBandwidth::LeafCenterOfChannelBandwidth(uint32_t id)
	: YangLeaf("center-of-channel-bandwidth", id)
{
}

GrpTxCommonArrayCarrierElements::LeafCenterOfChannelBandwidth::~LeafCenterOfChannelBandwidth()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /tx-common-array-carrier-elements/channel-bandwidth
// Description: Width of carrier given in Hertz
// -----------------------------------------------------------------------------
GrpTxCommonArrayCarrierElements::LeafChannelBandwidth::LeafChannelBandwidth(uint32_t id)
	: YangLeaf("channel-bandwidth", id)
{
}

GrpTxCommonArrayCarrierElements::LeafChannelBandwidth::~LeafChannelBandwidth()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /tx-common-array-carrier-elements/active
// Description: Indicates if transmission is enabled for this array carriers. Note that Netconf server uses state parameter
//              to indicate actual state of array carriers operation. When array carriers is in sleep status,
//              Netconf server rejects all other operation request to tx-array-carriers object except either request to change from sleep
//              to active status or delete MO operation (see 4.8) to the object.
// -----------------------------------------------------------------------------
GrpTxCommonArrayCarrierElements::LeafActive::LeafActive(uint32_t id)
	: YangLeaf("active", id)
{
}

GrpTxCommonArrayCarrierElements::LeafActive::~LeafActive()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /tx-common-array-carrier-elements/state
// Description: Indicates state of array carriers activation operation
// -----------------------------------------------------------------------------
GrpTxCommonArrayCarrierElements::LeafState::LeafState(uint32_t id)
	: YangLeaf("state", id)
{
}

GrpTxCommonArrayCarrierElements::LeafState::~LeafState()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /tx-common-array-carrier-elements/type
// Description: Type of carrier. Indicates array-carrier technology.
// -----------------------------------------------------------------------------
GrpTxCommonArrayCarrierElements::LeafType::LeafType(uint32_t id)
	: YangLeaf("type", id)
{
}

GrpTxCommonArrayCarrierElements::LeafType::~LeafType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /tx-common-array-carrier-elements/duplex-scheme
// Description: Type of duplex scheme O-RU supports.
// -----------------------------------------------------------------------------
GrpTxCommonArrayCarrierElements::LeafDuplexScheme::LeafDuplexScheme(uint32_t id)
	: YangLeaf("duplex-scheme", id)
{
}

GrpTxCommonArrayCarrierElements::LeafDuplexScheme::~LeafDuplexScheme()
{
}

// -----------------------------------------------------------------------------
// Reference:   /tx-common-array-carrier-elements/rw-duplex-scheme
// Description: Config true type of duplex scheme.
// -----------------------------------------------------------------------------
GrpTxCommonArrayCarrierElements::RefRwDuplexScheme::RefRwDuplexScheme(uint32_t id)
	: YangReference("rw-duplex-scheme", id, "/user-plane-configuration/tx-array-carriers[name=current()/../name]/duplex-scheme")
{
}

GrpTxCommonArrayCarrierElements::RefRwDuplexScheme::~RefRwDuplexScheme()
{
}

// -----------------------------------------------------------------------------
// Reference:   /tx-common-array-carrier-elements/rw-type
// Description: Config true type of carrier.
// -----------------------------------------------------------------------------
GrpTxCommonArrayCarrierElements::RefRwType::RefRwType(uint32_t id)
	: YangReference("rw-type", id, "/user-plane-configuration/tx-array-carriers[name=current()/../name]/type")
{
}

GrpTxCommonArrayCarrierElements::RefRwType::~RefRwType()
{
}



// -----------------------------------------------------------------------------
// Grouping:    rx-common-array-carrier-elements
// Description: This grouping containes all common parameters for tx-array-carriers and rx-array-carriers
// -----------------------------------------------------------------------------
GrpRxCommonArrayCarrierElements::GrpRxCommonArrayCarrierElements(uint32_t id)
	: YangGroup("rx-common-array-carrier-elements", id)
{
}

GrpRxCommonArrayCarrierElements::~GrpRxCommonArrayCarrierElements()
{
}

YangResult_E GrpRxCommonArrayCarrierElements::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /rx-common-array-carrier-elements/absolute-frequency-center
	// Description: Absolute Radio Frequency Channel Number - indirectly indicates RF center carrier frequency of signal.
	//              Reflected in arfcn.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafAbsoluteFrequencyCenter absoluteFrequencyCenterInst(ITEM_ABSOLUTE_FREQUENCY_CENTER);
	addLeaf(absoluteFrequencyCenterInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /rx-common-array-carrier-elements/center-of-channel-bandwidth
	// Description: Center frequency of channel bandwidth in Hz. Common for all numerologies.
	// Type:        uint64
	// Units:       Hz
	// -----------------------------------------------------------------------------
	LeafCenterOfChannelBandwidth centerOfChannelBandwidthInst(ITEM_CENTER_OF_CHANNEL_BANDWIDTH);
	addLeaf(centerOfChannelBandwidthInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /rx-common-array-carrier-elements/channel-bandwidth
	// Description: Width of carrier given in Hertz
	// Type:        uint64
	// Units:       Hz
	// -----------------------------------------------------------------------------
	LeafChannelBandwidth channelBandwidthInst(ITEM_CHANNEL_BANDWIDTH);
	addLeaf(channelBandwidthInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /rx-common-array-carrier-elements/active
	// Description: Indicates if transmission is enabled for this array carriers. Note that Netconf server uses state parameter
	//              to indicate actual state of array carriers operation. When array carriers is in sleep status,
	//              Netconf server rejects all other operation request to tx-array-carriers object except either request to change from sleep
	//              to active status or delete MO operation (see 4.8) to the object.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafActive activeInst(ITEM_ACTIVE);
	addLeaf(activeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /rx-common-array-carrier-elements/state
	// Description: Indicates state of array carriers activation operation
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafState stateInst(ITEM_STATE);
	addLeaf(stateInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /rx-common-array-carrier-elements/type
	// Description: Type of carrier. Indicates array-carrier technology.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafType typeInst(ITEM_TYPE);
	addLeaf(typeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /rx-common-array-carrier-elements/duplex-scheme
	// Description: Type of duplex scheme O-RU supports.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafDuplexScheme duplexSchemeInst(ITEM_DUPLEX_SCHEME);
	addLeaf(duplexSchemeInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /rx-common-array-carrier-elements/absolute-frequency-center
// Description: Absolute Radio Frequency Channel Number - indirectly indicates RF center carrier frequency of signal.
//              Reflected in arfcn.
// -----------------------------------------------------------------------------
GrpRxCommonArrayCarrierElements::LeafAbsoluteFrequencyCenter::LeafAbsoluteFrequencyCenter(uint32_t id)
	: YangLeaf("absolute-frequency-center", id)
{
}

GrpRxCommonArrayCarrierElements::LeafAbsoluteFrequencyCenter::~LeafAbsoluteFrequencyCenter()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /rx-common-array-carrier-elements/center-of-channel-bandwidth
// Description: Center frequency of channel bandwidth in Hz. Common for all numerologies.
// -----------------------------------------------------------------------------
GrpRxCommonArrayCarrierElements::LeafCenterOfChannelBandwidth::LeafCenterOfChannelBandwidth(uint32_t id)
	: YangLeaf("center-of-channel-bandwidth", id)
{
}

GrpRxCommonArrayCarrierElements::LeafCenterOfChannelBandwidth::~LeafCenterOfChannelBandwidth()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /rx-common-array-carrier-elements/channel-bandwidth
// Description: Width of carrier given in Hertz
// -----------------------------------------------------------------------------
GrpRxCommonArrayCarrierElements::LeafChannelBandwidth::LeafChannelBandwidth(uint32_t id)
	: YangLeaf("channel-bandwidth", id)
{
}

GrpRxCommonArrayCarrierElements::LeafChannelBandwidth::~LeafChannelBandwidth()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /rx-common-array-carrier-elements/active
// Description: Indicates if transmission is enabled for this array carriers. Note that Netconf server uses state parameter
//              to indicate actual state of array carriers operation. When array carriers is in sleep status,
//              Netconf server rejects all other operation request to tx-array-carriers object except either request to change from sleep
//              to active status or delete MO operation (see 4.8) to the object.
// -----------------------------------------------------------------------------
GrpRxCommonArrayCarrierElements::LeafActive::LeafActive(uint32_t id)
	: YangLeaf("active", id)
{
}

GrpRxCommonArrayCarrierElements::LeafActive::~LeafActive()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /rx-common-array-carrier-elements/state
// Description: Indicates state of array carriers activation operation
// -----------------------------------------------------------------------------
GrpRxCommonArrayCarrierElements::LeafState::LeafState(uint32_t id)
	: YangLeaf("state", id)
{
}

GrpRxCommonArrayCarrierElements::LeafState::~LeafState()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /rx-common-array-carrier-elements/type
// Description: Type of carrier. Indicates array-carrier technology.
// -----------------------------------------------------------------------------
GrpRxCommonArrayCarrierElements::LeafType::LeafType(uint32_t id)
	: YangLeaf("type", id)
{
}

GrpRxCommonArrayCarrierElements::LeafType::~LeafType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /rx-common-array-carrier-elements/duplex-scheme
// Description: Type of duplex scheme O-RU supports.
// -----------------------------------------------------------------------------
GrpRxCommonArrayCarrierElements::LeafDuplexScheme::LeafDuplexScheme(uint32_t id)
	: YangLeaf("duplex-scheme", id)
{
}

GrpRxCommonArrayCarrierElements::LeafDuplexScheme::~LeafDuplexScheme()
{
}



// -----------------------------------------------------------------------------
// Grouping:    endpoint-section-capacity
// Description: Parameters describing section capacity where section is undestood as number of different sectionId values
// -----------------------------------------------------------------------------
GrpEndpointSectionCapacity::GrpEndpointSectionCapacity(uint32_t id)
	: YangGroup("endpoint-section-capacity", id)
{
}

GrpEndpointSectionCapacity::~GrpEndpointSectionCapacity()
{
}

YangResult_E GrpEndpointSectionCapacity::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /endpoint-section-capacity/max-control-sections-per-data-section
	// Description: Max number of C-plane sections (C-plane section is part of C-plane message that carries 'section fields')
	//              referring to same U-plane section (U-plane section is part of U-plane message that carries
	//              'section header fields' and 'PRB fields') that is supported by endpoint.
	//              Note that additional limitations specific for each section type apply on top of this number.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafMaxControlSectionsPerDataSection maxControlSectionsPerDataSectionInst(ITEM_MAX_CONTROL_SECTIONS_PER_DATA_SECTION);
	addLeaf(maxControlSectionsPerDataSectionInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /endpoint-section-capacity/max-sections-per-symbol
	// Description: Max number of sections within one symbol that can be processed by endpoint
	//              or processed collectively by group of endpoints sharing capacity
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafMaxSectionsPerSymbol maxSectionsPerSymbolInst(ITEM_MAX_SECTIONS_PER_SYMBOL);
	addLeaf(maxSectionsPerSymbolInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /endpoint-section-capacity/max-sections-per-slot
	// Description: Max number of sections within one slot that can be processed by endpoint
	//              or processed collectively by group of endpoints sharing capacity.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafMaxSectionsPerSlot maxSectionsPerSlotInst(ITEM_MAX_SECTIONS_PER_SLOT);
	addLeaf(maxSectionsPerSlotInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /endpoint-section-capacity/max-control-sections-per-data-section
// Description: Max number of C-plane sections (C-plane section is part of C-plane message that carries 'section fields')
//              referring to same U-plane section (U-plane section is part of U-plane message that carries
//              'section header fields' and 'PRB fields') that is supported by endpoint.
//              Note that additional limitations specific for each section type apply on top of this number.
// -----------------------------------------------------------------------------
GrpEndpointSectionCapacity::LeafMaxControlSectionsPerDataSection::LeafMaxControlSectionsPerDataSection(uint32_t id)
	: YangLeaf("max-control-sections-per-data-section", id)
{
}

GrpEndpointSectionCapacity::LeafMaxControlSectionsPerDataSection::~LeafMaxControlSectionsPerDataSection()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /endpoint-section-capacity/max-sections-per-symbol
// Description: Max number of sections within one symbol that can be processed by endpoint
//              or processed collectively by group of endpoints sharing capacity
// -----------------------------------------------------------------------------
GrpEndpointSectionCapacity::LeafMaxSectionsPerSymbol::LeafMaxSectionsPerSymbol(uint32_t id)
	: YangLeaf("max-sections-per-symbol", id)
{
}

GrpEndpointSectionCapacity::LeafMaxSectionsPerSymbol::~LeafMaxSectionsPerSymbol()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /endpoint-section-capacity/max-sections-per-slot
// Description: Max number of sections within one slot that can be processed by endpoint
//              or processed collectively by group of endpoints sharing capacity.
// -----------------------------------------------------------------------------
GrpEndpointSectionCapacity::LeafMaxSectionsPerSlot::LeafMaxSectionsPerSlot(uint32_t id)
	: YangLeaf("max-sections-per-slot", id)
{
}

GrpEndpointSectionCapacity::LeafMaxSectionsPerSlot::~LeafMaxSectionsPerSlot()
{
}



// -----------------------------------------------------------------------------
// Grouping:    endpoint-beam-capacity
// Description: Parameters describing beam capacity where number of beams is understood as number of different beamId values
// -----------------------------------------------------------------------------
GrpEndpointBeamCapacity::GrpEndpointBeamCapacity(uint32_t id)
	: YangGroup("endpoint-beam-capacity", id)
{
}

GrpEndpointBeamCapacity::~GrpEndpointBeamCapacity()
{
}

YangResult_E GrpEndpointBeamCapacity::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /endpoint-beam-capacity/max-beams-per-symbol
	// Description: Max number of beams within one symbol that can be processed by endpoint
	//              or processed collectively by group of endpoints sharing capacity
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafMaxBeamsPerSymbol maxBeamsPerSymbolInst(ITEM_MAX_BEAMS_PER_SYMBOL);
	addLeaf(maxBeamsPerSymbolInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /endpoint-beam-capacity/max-beams-per-slot
	// Description: Max number of beams within one slot that can be processed by endpoint
	//              or processed collectively by group of endpoints sharing capacity
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafMaxBeamsPerSlot maxBeamsPerSlotInst(ITEM_MAX_BEAMS_PER_SLOT);
	addLeaf(maxBeamsPerSlotInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /endpoint-beam-capacity/max-beams-per-symbol
// Description: Max number of beams within one symbol that can be processed by endpoint
//              or processed collectively by group of endpoints sharing capacity
// -----------------------------------------------------------------------------
GrpEndpointBeamCapacity::LeafMaxBeamsPerSymbol::LeafMaxBeamsPerSymbol(uint32_t id)
	: YangLeaf("max-beams-per-symbol", id)
{
}

GrpEndpointBeamCapacity::LeafMaxBeamsPerSymbol::~LeafMaxBeamsPerSymbol()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /endpoint-beam-capacity/max-beams-per-slot
// Description: Max number of beams within one slot that can be processed by endpoint
//              or processed collectively by group of endpoints sharing capacity
// -----------------------------------------------------------------------------
GrpEndpointBeamCapacity::LeafMaxBeamsPerSlot::LeafMaxBeamsPerSlot(uint32_t id)
	: YangLeaf("max-beams-per-slot", id)
{
}

GrpEndpointBeamCapacity::LeafMaxBeamsPerSlot::~LeafMaxBeamsPerSlot()
{
}



// -----------------------------------------------------------------------------
// Grouping:    endpoint-prb-capacity
// Description: Attributes presenting processing capacity related to PRB.
// -----------------------------------------------------------------------------
GrpEndpointPrbCapacity::GrpEndpointPrbCapacity(uint32_t id)
	: YangGroup("endpoint-prb-capacity", id)
{
}

GrpEndpointPrbCapacity::~GrpEndpointPrbCapacity()
{
}

YangResult_E GrpEndpointPrbCapacity::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /endpoint-prb-capacity/max-prb-per-symbol
	// Description: Max number of prbs within one symbol that can be processed by endpoint
	//              or processed collectively by group of endpoints sharing capacity
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafMaxPrbPerSymbol maxPrbPerSymbolInst(ITEM_MAX_PRB_PER_SYMBOL);
	addLeaf(maxPrbPerSymbolInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /endpoint-prb-capacity/max-prb-per-symbol
// Description: Max number of prbs within one symbol that can be processed by endpoint
//              or processed collectively by group of endpoints sharing capacity
// -----------------------------------------------------------------------------
GrpEndpointPrbCapacity::LeafMaxPrbPerSymbol::LeafMaxPrbPerSymbol(uint32_t id)
	: YangLeaf("max-prb-per-symbol", id)
{
}

GrpEndpointPrbCapacity::LeafMaxPrbPerSymbol::~LeafMaxPrbPerSymbol()
{
}



// -----------------------------------------------------------------------------
// Grouping:    endpoint-numerology-capacity
// Description: Attributes presenting processing capacity related to numerology.
//
//              This leaf contains valid data only when multiple-numerology-supported
//              is set to true.
// -----------------------------------------------------------------------------
GrpEndpointNumerologyCapacity::GrpEndpointNumerologyCapacity(uint32_t id)
	: YangGroup("endpoint-numerology-capacity", id)
{
}

GrpEndpointNumerologyCapacity::~GrpEndpointNumerologyCapacity()
{
}

YangResult_E GrpEndpointNumerologyCapacity::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /endpoint-numerology-capacity/max-numerologies-per-symbol
	// Description: Max number of numerologies within one symbol that can be processed by endpoint
	//              or processed collectively by group of endpoints sharing capacity
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafMaxNumerologiesPerSymbol maxNumerologiesPerSymbolInst(ITEM_MAX_NUMEROLOGIES_PER_SYMBOL);
	addLeaf(maxNumerologiesPerSymbolInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /endpoint-numerology-capacity/max-numerologies-per-symbol
// Description: Max number of numerologies within one symbol that can be processed by endpoint
//              or processed collectively by group of endpoints sharing capacity
// -----------------------------------------------------------------------------
GrpEndpointNumerologyCapacity::LeafMaxNumerologiesPerSymbol::LeafMaxNumerologiesPerSymbol(uint32_t id)
	: YangLeaf("max-numerologies-per-symbol", id)
{
}

GrpEndpointNumerologyCapacity::LeafMaxNumerologiesPerSymbol::~LeafMaxNumerologiesPerSymbol()
{
}



// -----------------------------------------------------------------------------
// Grouping:    uplane-conf-group
// Description: Grouping for uplane configuration related parameters
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::GrpUplaneConfGroup(uint32_t id)
	: YangGroup("uplane-conf-group", id)
{
}

GrpUplaneConfGroup::~GrpUplaneConfGroup()
{
}

YangResult_E GrpUplaneConfGroup::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/low-level-tx-links
	// Description: Object model for low-level-tx-link configuration
	// Array Key:
	// -----------------------------------------------------------------------------
	LstLowLevelTxLinks lowLevelTxLinksInst(ITEM_LOW_LEVEL_TX_LINKS);
	lowLevelTxLinksInst.initialise();
	addList(lowLevelTxLinksInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/low-level-rx-links
	// Description: Object model for low-level-rx-links configuration
	// Array Key:
	// -----------------------------------------------------------------------------
	LstLowLevelRxLinks lowLevelRxLinksInst(ITEM_LOW_LEVEL_RX_LINKS);
	lowLevelRxLinksInst.initialise();
	addList(lowLevelRxLinksInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/endpoint-types
	// Description: Properties of endpoint that are common to multiple endpoints if such are identified
	// Array Key:
	// -----------------------------------------------------------------------------
	LstEndpointTypes endpointTypesInst(ITEM_ENDPOINT_TYPES);
	endpointTypesInst.initialise();
	addList(endpointTypesInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/endpoint-capacity-sharing-groups
	// Description: Represents groups of endpoints that share capacity. Depending on O-RU implementation,
	//              processing resources that handle CU-plane (e.g. memory to keep sections and beams)
	//              could be allocated per endpoint or shared between several endpoints.
	//              To address this O-RU shall reports own capability per endpoint (see endpoint-types)
	//              and per group of endpoints sharing capacity.
	//              If endpoint is in multiple groups then resulting constraint is minimum over all groups.
	//              Note: values of parameters representing capacity that is not shared between endpoints in a group shall be set to max value of specific parameter; this effectively removes related constraint.
	//
	// Array Key:
	// -----------------------------------------------------------------------------
	LstEndpointCapacitySharingGroups endpointCapacitySharingGroupsInst(ITEM_ENDPOINT_CAPACITY_SHARING_GROUPS);
	endpointCapacitySharingGroupsInst.initialise();
	addList(endpointCapacitySharingGroupsInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/static-low-level-tx-endpoints
	// Description: Object model for static-low-level-tx-endpoints configuration
	// Array Key:
	// -----------------------------------------------------------------------------
	LstStaticLowLevelTxEndpoints staticLowLevelTxEndpointsInst(ITEM_STATIC_LOW_LEVEL_TX_ENDPOINTS);
	staticLowLevelTxEndpointsInst.initialise();
	addList(staticLowLevelTxEndpointsInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/static-low-level-rx-endpoints
	// Description: Object model for static-low-level-rx-endpoints configuration
	// Array Key:
	// -----------------------------------------------------------------------------
	LstStaticLowLevelRxEndpoints staticLowLevelRxEndpointsInst(ITEM_STATIC_LOW_LEVEL_RX_ENDPOINTS);
	staticLowLevelRxEndpointsInst.initialise();
	addList(staticLowLevelRxEndpointsInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/low-level-tx-endpoints
	// Description: Object model for low-level-tx-endpoints configuration - augmented static-low-level-tx-endpoints by local-address
	//              which cannot be added to static low-level-tx-endpoints as we cannot have modificable element in static object
	// Array Key:
	// -----------------------------------------------------------------------------
	LstLowLevelTxEndpoints lowLevelTxEndpointsInst(ITEM_LOW_LEVEL_TX_ENDPOINTS);
	lowLevelTxEndpointsInst.initialise();
	addList(lowLevelTxEndpointsInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/low-level-rx-endpoints
	// Description: Object model for low-level-rx-endpoint configuration - augmented static-low-level-rx-endpoints by local-address
	//              which cannot be added to static low-level-rx-endpoints as we cannot have modificable element in static object
	// Array Key:
	// -----------------------------------------------------------------------------
	LstLowLevelRxEndpoints lowLevelRxEndpointsInst(ITEM_LOW_LEVEL_RX_ENDPOINTS);
	lowLevelRxEndpointsInst.initialise();
	addList(lowLevelRxEndpointsInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/tx-array-carriers
	// Description: Object model for tx-array-carriers configuration
	// Array Key:
	// -----------------------------------------------------------------------------
	LstTxArrayCarriers txArrayCarriersInst(ITEM_TX_ARRAY_CARRIERS);
	txArrayCarriersInst.initialise();
	addList(txArrayCarriersInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/rx-array-carriers
	// Description: Object model for rx-array-carriers configuration
	// Array Key:
	// -----------------------------------------------------------------------------
	LstRxArrayCarriers rxArrayCarriersInst(ITEM_RX_ARRAY_CARRIERS);
	rxArrayCarriersInst.initialise();
	addList(rxArrayCarriersInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/tx-arrays
	// Description: Structure describing TX array parameters
	// Array Key:
	// -----------------------------------------------------------------------------
	LstTxArrays txArraysInst(ITEM_TX_ARRAYS);
	txArraysInst.initialise();
	addList(txArraysInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/rx-arrays
	// Description: Structure describing RX array parameters
	// Array Key:
	// -----------------------------------------------------------------------------
	LstRxArrays rxArraysInst(ITEM_RX_ARRAYS);
	rxArraysInst.initialise();
	addList(rxArraysInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/relations
	// Description: Structure describing relations between array elements
	// Array Key:
	// -----------------------------------------------------------------------------
	LstRelations relationsInst(ITEM_RELATIONS);
	relationsInst.initialise();
	addList(relationsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        low-level-tx-links
// Description: Object model for low-level-tx-link configuration
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelTxLinks::LstLowLevelTxLinks(uint32_t id)
	: YangList("low-level-tx-links", id)
{
}

GrpUplaneConfGroup::LstLowLevelTxLinks::~LstLowLevelTxLinks()
{
}

YangResult_E GrpUplaneConfGroup::LstLowLevelTxLinks::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/low-level-tx-links/name
	// Description: Unique name of low-level-tx-link object.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/low-level-tx-links/processing-element
	// Description: Contains name of processing-element to be used as transport by low-level-tx-link
	// Ref:         /o-ran-processing-element:processing-elements/o-ran-processing-element:ru-elements/o-ran-processing-element:name
	// Units:
	// -----------------------------------------------------------------------------
	RefProcessingElement processingElementInst(ITEM_PROCESSING_ELEMENT);
	addReference(processingElementInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/low-level-tx-links/tx-array-carrier
	// Description: Contains name of tx-array-carriers MO to be used as transport by low-level-tx-link
	// Ref:         /user-plane-configuration/tx-array-carriers/name
	// Units:
	// -----------------------------------------------------------------------------
	RefTxArrayCarrier txArrayCarrierInst(ITEM_TX_ARRAY_CARRIER);
	addReference(txArrayCarrierInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/low-level-tx-links/low-level-tx-endpoint
	// Description: Contains name of low-level-tx-endpoints MO to be used as transport by low-level-tx-link
	// Ref:         /user-plane-configuration/low-level-tx-endpoints/name
	// Units:
	// -----------------------------------------------------------------------------
	RefLowLevelTxEndpoint lowLevelTxEndpointInst(ITEM_LOW_LEVEL_TX_ENDPOINT);
	addReference(lowLevelTxEndpointInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/low-level-tx-links/name
// Description: Unique name of low-level-tx-link object.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelTxLinks::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpUplaneConfGroup::LstLowLevelTxLinks::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/low-level-tx-links/processing-element
// Description: Contains name of processing-element to be used as transport by low-level-tx-link
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelTxLinks::RefProcessingElement::RefProcessingElement(uint32_t id)
	: YangReference("processing-element", id, "/o-ran-processing-element:processing-elements/o-ran-processing-element:ru-elements/o-ran-processing-element:name")
{
}

GrpUplaneConfGroup::LstLowLevelTxLinks::RefProcessingElement::~RefProcessingElement()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/low-level-tx-links/tx-array-carrier
// Description: Contains name of tx-array-carriers MO to be used as transport by low-level-tx-link
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelTxLinks::RefTxArrayCarrier::RefTxArrayCarrier(uint32_t id)
	: YangReference("tx-array-carrier", id, "/user-plane-configuration/tx-array-carriers/name")
{
}

GrpUplaneConfGroup::LstLowLevelTxLinks::RefTxArrayCarrier::~RefTxArrayCarrier()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/low-level-tx-links/low-level-tx-endpoint
// Description: Contains name of low-level-tx-endpoints MO to be used as transport by low-level-tx-link
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelTxLinks::RefLowLevelTxEndpoint::RefLowLevelTxEndpoint(uint32_t id)
	: YangReference("low-level-tx-endpoint", id, "/user-plane-configuration/low-level-tx-endpoints/name")
{
}

GrpUplaneConfGroup::LstLowLevelTxLinks::RefLowLevelTxEndpoint::~RefLowLevelTxEndpoint()
{
}



// -----------------------------------------------------------------------------
// List:        low-level-rx-links
// Description: Object model for low-level-rx-links configuration
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxLinks::LstLowLevelRxLinks(uint32_t id)
	: YangList("low-level-rx-links", id)
{
}

GrpUplaneConfGroup::LstLowLevelRxLinks::~LstLowLevelRxLinks()
{
}

YangResult_E GrpUplaneConfGroup::LstLowLevelRxLinks::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/low-level-rx-links/name
	// Description: Unique name of low-level-rx-links object.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/low-level-rx-links/processing-element
	// Description: Contains name of processing-element to be used as transport by LowLevelTxLink
	// Ref:         /o-ran-processing-element:processing-elements/o-ran-processing-element:ru-elements/o-ran-processing-element:name
	// Units:
	// -----------------------------------------------------------------------------
	RefProcessingElement processingElementInst(ITEM_PROCESSING_ELEMENT);
	addReference(processingElementInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/low-level-rx-links/rx-array-carrier
	// Description: Contains name of rx-array-carriers MO to be used as transport by low-level-rx-links
	// Ref:         /user-plane-configuration/rx-array-carriers/name
	// Units:
	// -----------------------------------------------------------------------------
	RefRxArrayCarrier rxArrayCarrierInst(ITEM_RX_ARRAY_CARRIER);
	addReference(rxArrayCarrierInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/low-level-rx-links/low-level-rx-endpoint
	// Description: Contains name of low-level-rx-endpoints MO to be used as transport by low-level-rx-links
	// Ref:         /user-plane-configuration/low-level-rx-endpoints/name
	// Units:
	// -----------------------------------------------------------------------------
	RefLowLevelRxEndpoint lowLevelRxEndpointInst(ITEM_LOW_LEVEL_RX_ENDPOINT);
	addReference(lowLevelRxEndpointInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/low-level-rx-links/user-plane-uplink-marking
	// Description: Parameter to set the non-default marking for user-plane
	// Ref:         /o-ran-processing-element:processing-elements/o-ran-processing-element:enhanced-uplane-mapping/o-ran-processing-element:uplane-mapping/o-ran-processing-element:up-marking-name
	// Units:
	// -----------------------------------------------------------------------------
	RefUserPlaneUplinkMarking userPlaneUplinkMarkingInst(ITEM_USER_PLANE_UPLINK_MARKING);
	addReference(userPlaneUplinkMarkingInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/low-level-rx-links/name
// Description: Unique name of low-level-rx-links object.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxLinks::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpUplaneConfGroup::LstLowLevelRxLinks::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/low-level-rx-links/processing-element
// Description: Contains name of processing-element to be used as transport by LowLevelTxLink
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxLinks::RefProcessingElement::RefProcessingElement(uint32_t id)
	: YangReference("processing-element", id, "/o-ran-processing-element:processing-elements/o-ran-processing-element:ru-elements/o-ran-processing-element:name")
{
}

GrpUplaneConfGroup::LstLowLevelRxLinks::RefProcessingElement::~RefProcessingElement()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/low-level-rx-links/rx-array-carrier
// Description: Contains name of rx-array-carriers MO to be used as transport by low-level-rx-links
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxLinks::RefRxArrayCarrier::RefRxArrayCarrier(uint32_t id)
	: YangReference("rx-array-carrier", id, "/user-plane-configuration/rx-array-carriers/name")
{
}

GrpUplaneConfGroup::LstLowLevelRxLinks::RefRxArrayCarrier::~RefRxArrayCarrier()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/low-level-rx-links/low-level-rx-endpoint
// Description: Contains name of low-level-rx-endpoints MO to be used as transport by low-level-rx-links
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxLinks::RefLowLevelRxEndpoint::RefLowLevelRxEndpoint(uint32_t id)
	: YangReference("low-level-rx-endpoint", id, "/user-plane-configuration/low-level-rx-endpoints/name")
{
}

GrpUplaneConfGroup::LstLowLevelRxLinks::RefLowLevelRxEndpoint::~RefLowLevelRxEndpoint()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/low-level-rx-links/user-plane-uplink-marking
// Description: Parameter to set the non-default marking for user-plane
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxLinks::RefUserPlaneUplinkMarking::RefUserPlaneUplinkMarking(uint32_t id)
	: YangReference("user-plane-uplink-marking", id, "/o-ran-processing-element:processing-elements/o-ran-processing-element:enhanced-uplane-mapping/o-ran-processing-element:uplane-mapping/o-ran-processing-element:up-marking-name")
{
}

GrpUplaneConfGroup::LstLowLevelRxLinks::RefUserPlaneUplinkMarking::~RefUserPlaneUplinkMarking()
{
}



// -----------------------------------------------------------------------------
// List:        endpoint-types
// Description: Properties of endpoint that are common to multiple endpoints if such are identified
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointTypes::LstEndpointTypes(uint32_t id)
	: YangList("endpoint-types", id)
{
}

GrpUplaneConfGroup::LstEndpointTypes::~LstEndpointTypes()
{
}

YangResult_E GrpUplaneConfGroup::LstEndpointTypes::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/endpoint-types/id
	// Description: Identifies type of endpoints sharing same properties. Values shall start with 0 and shall be allocated without gaps.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafId idInst(ITEM_ID);
	addLeaf(idInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/endpoint-types/managed-delay-support
	// Description: Type of delay supported by the endpoint
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafManagedDelaySupport managedDelaySupportInst(ITEM_MANAGED_DELAY_SUPPORT);
	addLeaf(managedDelaySupportInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/endpoint-types/multiple-numerology-supported
	// Description: Indicates whether the endpoint type supports multiple numerologies
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafMultipleNumerologySupported multipleNumerologySupportedInst(ITEM_MULTIPLE_NUMEROLOGY_SUPPORTED);
	addLeaf(multipleNumerologySupportedInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/endpoint-types/max-numerology-change-duration
	// Description: Maximum gap of endpoint operation that will be caused by changing of
	//              numerology.
	//
	//              This time is required for reconfiguration and flushing of pipes.
	//
	//              This leaf contains valid data only when multiple-numerology-supported
	//              is set to true.
	// Type:        uint16
	// Units:       Ts
	// -----------------------------------------------------------------------------
	LeafMaxNumerologyChangeDuration maxNumerologyChangeDurationInst(ITEM_MAX_NUMEROLOGY_CHANGE_DURATION);
	addLeaf(maxNumerologyChangeDurationInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/endpoint-types/supported-frame-structures
	// Description: List of supported values of frame structure
	// Array Key:
	// -----------------------------------------------------------------------------
	LstSupportedFrameStructures supportedFrameStructuresInst(ITEM_SUPPORTED_FRAME_STRUCTURES);
	supportedFrameStructuresInst.initialise();
	addList(supportedFrameStructuresInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/endpoint-types/prb-capacity-allocation-granularity
	// Description: List of capacity allocation steps. O-RU allocates PRB capacity rounding it up to nearest value N
	//              from prb-capacity-allocation-granularity such that M >= number-of-prb-per-scs.
	//              See also number-of-prb-per-scs/number-of-prb.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstPrbCapacityAllocationGranularity prbCapacityAllocationGranularityInst(ITEM_PRB_CAPACITY_ALLOCATION_GRANULARITY);
	prbCapacityAllocationGranularityInst.initialise();
	addList(prbCapacityAllocationGranularityInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/endpoint-types/supported-section-types
	// Description: Indicates section types and extensions endpoints of this type support
	// Array Key:
	// -----------------------------------------------------------------------------
	LstSupportedSectionTypes supportedSectionTypesInst(ITEM_SUPPORTED_SECTION_TYPES);
	supportedSectionTypesInst.initialise();
	addList(supportedSectionTypesInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/endpoint-types/endpoint-section-capacity
	// Description:
	// -----------------------------------------------------------------------------
	GrpEndpointSectionCapacity endpointSectionCapacityInst(ITEM_ENDPOINT_SECTION_CAPACITY);
	endpointSectionCapacityInst.initialise();
	addGroup(endpointSectionCapacityInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/endpoint-types/endpoint-beam-capacity
	// Description:
	// -----------------------------------------------------------------------------
	GrpEndpointBeamCapacity endpointBeamCapacityInst(ITEM_ENDPOINT_BEAM_CAPACITY);
	endpointBeamCapacityInst.initialise();
	addGroup(endpointBeamCapacityInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/endpoint-types/endpoint-prb-capacity
	// Description:
	// -----------------------------------------------------------------------------
	GrpEndpointPrbCapacity endpointPrbCapacityInst(ITEM_ENDPOINT_PRB_CAPACITY);
	endpointPrbCapacityInst.initialise();
	addGroup(endpointPrbCapacityInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/endpoint-types/endpoint-numerology-capacity
	// Description:
	// -----------------------------------------------------------------------------
	GrpEndpointNumerologyCapacity endpointNumerologyCapacityInst(ITEM_ENDPOINT_NUMEROLOGY_CAPACITY);
	endpointNumerologyCapacityInst.initialise();
	addGroup(endpointNumerologyCapacityInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/endpoint-types/id
// Description: Identifies type of endpoints sharing same properties. Values shall start with 0 and shall be allocated without gaps.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointTypes::LeafId::LeafId(uint32_t id)
	: YangLeaf("id", id)
{
}

GrpUplaneConfGroup::LstEndpointTypes::LeafId::~LeafId()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/endpoint-types/managed-delay-support
// Description: Type of delay supported by the endpoint
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointTypes::LeafManagedDelaySupport::LeafManagedDelaySupport(uint32_t id)
	: YangLeaf("managed-delay-support", id)
{
}

GrpUplaneConfGroup::LstEndpointTypes::LeafManagedDelaySupport::~LeafManagedDelaySupport()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/endpoint-types/multiple-numerology-supported
// Description: Indicates whether the endpoint type supports multiple numerologies
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointTypes::LeafMultipleNumerologySupported::LeafMultipleNumerologySupported(uint32_t id)
	: YangLeaf("multiple-numerology-supported", id)
{
}

GrpUplaneConfGroup::LstEndpointTypes::LeafMultipleNumerologySupported::~LeafMultipleNumerologySupported()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/endpoint-types/max-numerology-change-duration
// Description: Maximum gap of endpoint operation that will be caused by changing of
//              numerology.
//
//              This time is required for reconfiguration and flushing of pipes.
//
//              This leaf contains valid data only when multiple-numerology-supported
//              is set to true.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointTypes::LeafMaxNumerologyChangeDuration::LeafMaxNumerologyChangeDuration(uint32_t id)
	: YangLeaf("max-numerology-change-duration", id)
{
}

GrpUplaneConfGroup::LstEndpointTypes::LeafMaxNumerologyChangeDuration::~LeafMaxNumerologyChangeDuration()
{
}

// -----------------------------------------------------------------------------
// List:        supported-frame-structures
// Description: List of supported values of frame structure
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointTypes::LstSupportedFrameStructures::LstSupportedFrameStructures(uint32_t id)
	: YangList("supported-frame-structures", id)
{
}

GrpUplaneConfGroup::LstEndpointTypes::LstSupportedFrameStructures::~LstSupportedFrameStructures()
{
}

YangResult_E GrpUplaneConfGroup::LstEndpointTypes::LstSupportedFrameStructures::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        prb-capacity-allocation-granularity
// Description: List of capacity allocation steps. O-RU allocates PRB capacity rounding it up to nearest value N
//              from prb-capacity-allocation-granularity such that M >= number-of-prb-per-scs.
//              See also number-of-prb-per-scs/number-of-prb.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointTypes::LstPrbCapacityAllocationGranularity::LstPrbCapacityAllocationGranularity(uint32_t id)
	: YangList("prb-capacity-allocation-granularity", id)
{
}

GrpUplaneConfGroup::LstEndpointTypes::LstPrbCapacityAllocationGranularity::~LstPrbCapacityAllocationGranularity()
{
}

YangResult_E GrpUplaneConfGroup::LstEndpointTypes::LstPrbCapacityAllocationGranularity::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        supported-section-types
// Description: Indicates section types and extensions endpoints of this type support
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointTypes::LstSupportedSectionTypes::LstSupportedSectionTypes(uint32_t id)
	: YangList("supported-section-types", id)
{
}

GrpUplaneConfGroup::LstEndpointTypes::LstSupportedSectionTypes::~LstSupportedSectionTypes()
{
}

YangResult_E GrpUplaneConfGroup::LstEndpointTypes::LstSupportedSectionTypes::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/endpoint-types/supported-section-types/section-type
	// Description: This parameter determines the characteristics of U-plane data to be transferred or received from a beam with one pattern id.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafSectionType sectionTypeInst(ITEM_SECTION_TYPE);
	addLeaf(sectionTypeInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/endpoint-types/supported-section-types/supported-section-extensions
	// Description: This parameter provides the extension types supported by the O-RU
	//              which provides additional parameters specific to the subject data extension
	// Array Key:
	// -----------------------------------------------------------------------------
	LstSupportedSectionExtensions supportedSectionExtensionsInst(ITEM_SUPPORTED_SECTION_EXTENSIONS);
	supportedSectionExtensionsInst.initialise();
	addList(supportedSectionExtensionsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/endpoint-types/supported-section-types/section-type
// Description: This parameter determines the characteristics of U-plane data to be transferred or received from a beam with one pattern id.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointTypes::LstSupportedSectionTypes::LeafSectionType::LeafSectionType(uint32_t id)
	: YangLeaf("section-type", id)
{
}

GrpUplaneConfGroup::LstEndpointTypes::LstSupportedSectionTypes::LeafSectionType::~LeafSectionType()
{
}

// -----------------------------------------------------------------------------
// List:        supported-section-extensions
// Description: This parameter provides the extension types supported by the O-RU
//              which provides additional parameters specific to the subject data extension
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointTypes::LstSupportedSectionTypes::LstSupportedSectionExtensions::LstSupportedSectionExtensions(uint32_t id)
	: YangList("supported-section-extensions", id)
{
}

GrpUplaneConfGroup::LstEndpointTypes::LstSupportedSectionTypes::LstSupportedSectionExtensions::~LstSupportedSectionExtensions()
{
}

YangResult_E GrpUplaneConfGroup::LstEndpointTypes::LstSupportedSectionTypes::LstSupportedSectionExtensions::initialise(void)
{


	return YangResult_E::OK;
}







// -----------------------------------------------------------------------------
// List:        endpoint-capacity-sharing-groups
// Description: Represents groups of endpoints that share capacity. Depending on O-RU implementation,
//              processing resources that handle CU-plane (e.g. memory to keep sections and beams)
//              could be allocated per endpoint or shared between several endpoints.
//              To address this O-RU shall reports own capability per endpoint (see endpoint-types)
//              and per group of endpoints sharing capacity.
//              If endpoint is in multiple groups then resulting constraint is minimum over all groups.
//              Note: values of parameters representing capacity that is not shared between endpoints in a group shall be set to max value of specific parameter; this effectively removes related constraint.
//
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::LstEndpointCapacitySharingGroups(uint32_t id)
	: YangList("endpoint-capacity-sharing-groups", id)
{
}

GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::~LstEndpointCapacitySharingGroups()
{
}

YangResult_E GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/endpoint-capacity-sharing-groups/id
	// Description: Identifies group of endpoints sharing resources.
	//              Values shall start with 0 and shall be allocated without gaps.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafId idInst(ITEM_ID);
	addLeaf(idInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/endpoint-capacity-sharing-groups/max-endpoints
	// Description: Indicates how many endpoints in the group can be used4 simultaneously
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafMaxEndpoints maxEndpointsInst(ITEM_MAX_ENDPOINTS);
	addLeaf(maxEndpointsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/endpoint-capacity-sharing-groups/max-managed-delay-endpoints
	// Description: Number of endpoints supporting managed delay that can be used (configured for use) at a time
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafMaxManagedDelayEndpoints maxManagedDelayEndpointsInst(ITEM_MAX_MANAGED_DELAY_ENDPOINTS);
	addLeaf(maxManagedDelayEndpointsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/endpoint-capacity-sharing-groups/max-non-managed-delay-endpoints
	// Description: Number of endpoints supporting non-managed delay that can be used (configured for use) at a time
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafMaxNonManagedDelayEndpoints maxNonManagedDelayEndpointsInst(ITEM_MAX_NON_MANAGED_DELAY_ENDPOINTS);
	addLeaf(maxNonManagedDelayEndpointsInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/endpoint-capacity-sharing-groups/endpoint-section-capacity
	// Description:
	// -----------------------------------------------------------------------------
	GrpEndpointSectionCapacity endpointSectionCapacityInst(ITEM_ENDPOINT_SECTION_CAPACITY);
	endpointSectionCapacityInst.initialise();
	addGroup(endpointSectionCapacityInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/endpoint-capacity-sharing-groups/endpoint-beam-capacity
	// Description:
	// -----------------------------------------------------------------------------
	GrpEndpointBeamCapacity endpointBeamCapacityInst(ITEM_ENDPOINT_BEAM_CAPACITY);
	endpointBeamCapacityInst.initialise();
	addGroup(endpointBeamCapacityInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/endpoint-capacity-sharing-groups/endpoint-prb-capacity
	// Description:
	// -----------------------------------------------------------------------------
	GrpEndpointPrbCapacity endpointPrbCapacityInst(ITEM_ENDPOINT_PRB_CAPACITY);
	endpointPrbCapacityInst.initialise();
	addGroup(endpointPrbCapacityInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/endpoint-capacity-sharing-groups/endpoint-numerology-capacity
	// Description:
	// -----------------------------------------------------------------------------
	GrpEndpointNumerologyCapacity endpointNumerologyCapacityInst(ITEM_ENDPOINT_NUMEROLOGY_CAPACITY);
	endpointNumerologyCapacityInst.initialise();
	addGroup(endpointNumerologyCapacityInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/endpoint-capacity-sharing-groups/id
// Description: Identifies group of endpoints sharing resources.
//              Values shall start with 0 and shall be allocated without gaps.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::LeafId::LeafId(uint32_t id)
	: YangLeaf("id", id)
{
}

GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::LeafId::~LeafId()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/endpoint-capacity-sharing-groups/max-endpoints
// Description: Indicates how many endpoints in the group can be used4 simultaneously
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::LeafMaxEndpoints::LeafMaxEndpoints(uint32_t id)
	: YangLeaf("max-endpoints", id)
{
}

GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::LeafMaxEndpoints::~LeafMaxEndpoints()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/endpoint-capacity-sharing-groups/max-managed-delay-endpoints
// Description: Number of endpoints supporting managed delay that can be used (configured for use) at a time
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::LeafMaxManagedDelayEndpoints::LeafMaxManagedDelayEndpoints(uint32_t id)
	: YangLeaf("max-managed-delay-endpoints", id)
{
}

GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::LeafMaxManagedDelayEndpoints::~LeafMaxManagedDelayEndpoints()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/endpoint-capacity-sharing-groups/max-non-managed-delay-endpoints
// Description: Number of endpoints supporting non-managed delay that can be used (configured for use) at a time
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::LeafMaxNonManagedDelayEndpoints::LeafMaxNonManagedDelayEndpoints(uint32_t id)
	: YangLeaf("max-non-managed-delay-endpoints", id)
{
}

GrpUplaneConfGroup::LstEndpointCapacitySharingGroups::LeafMaxNonManagedDelayEndpoints::~LeafMaxNonManagedDelayEndpoints()
{
}



// -----------------------------------------------------------------------------
// List:        static-low-level-tx-endpoints
// Description: Object model for static-low-level-tx-endpoints configuration
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::LstStaticLowLevelTxEndpoints(uint32_t id)
	: YangList("static-low-level-tx-endpoints", id)
{
}

GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::~LstStaticLowLevelTxEndpoints()
{
}

YangResult_E GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/static-low-level-tx-endpoints/name
	// Description: Unique name of static-low-level-tx-endpoints object.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/static-low-level-tx-endpoints/array
	// Description: Contains distname of tx-arrays, particular low-level-tx-endpoints is in hardware dependency with.
	//              Note: single instance of tx-arrays can be referenced by many instances of low-level-tx-endpoints
	//              (e.g. to allow DU to handle multiple fronthauls and multiple component carriers).
	// Ref:         /user-plane-configuration/tx-arrays/name
	// Units:
	// -----------------------------------------------------------------------------
	RefArray arrayInst(ITEM_ARRAY);
	addReference(arrayInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/static-low-level-tx-endpoints/endpoint-type
	// Description: Reference to endpoint type capabilities list element supported by this endpoint
	// Ref:         ../../endpoint-types/id
	// Units:
	// -----------------------------------------------------------------------------
	RefEndpointType endpointTypeInst(ITEM_ENDPOINT_TYPE);
	addReference(endpointTypeInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/static-low-level-tx-endpoints/restricted-interfaces
	// Description: Optionally used to indicate that a low-level link is constrained to operate only via a subset of the available interfaces.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstRestrictedInterfaces restrictedInterfacesInst(ITEM_RESTRICTED_INTERFACES);
	restrictedInterfacesInst.initialise();
	addList(restrictedInterfacesInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/static-low-level-tx-endpoints/capacity-sharing-groups
	// Description: Reference to capacities of sharing-groups supported by this endpoint
	// Array Key:
	// -----------------------------------------------------------------------------
	LstCapacitySharingGroups capacitySharingGroupsInst(ITEM_CAPACITY_SHARING_GROUPS);
	capacitySharingGroupsInst.initialise();
	addList(capacitySharingGroupsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/static-low-level-tx-endpoints/name
// Description: Unique name of static-low-level-tx-endpoints object.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/static-low-level-tx-endpoints/array
// Description: Contains distname of tx-arrays, particular low-level-tx-endpoints is in hardware dependency with.
//              Note: single instance of tx-arrays can be referenced by many instances of low-level-tx-endpoints
//              (e.g. to allow DU to handle multiple fronthauls and multiple component carriers).
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::RefArray::RefArray(uint32_t id)
	: YangReference("array", id, "/user-plane-configuration/tx-arrays/name")
{
}

GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::RefArray::~RefArray()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/static-low-level-tx-endpoints/endpoint-type
// Description: Reference to endpoint type capabilities list element supported by this endpoint
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::RefEndpointType::RefEndpointType(uint32_t id)
	: YangReference("endpoint-type", id, "../../endpoint-types/id")
{
}

GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::RefEndpointType::~RefEndpointType()
{
}

// -----------------------------------------------------------------------------
// List:        restricted-interfaces
// Description: Optionally used to indicate that a low-level link is constrained to operate only via a subset of the available interfaces.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::LstRestrictedInterfaces::LstRestrictedInterfaces(uint32_t id)
	: YangList("restricted-interfaces", id)
{
}

GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::LstRestrictedInterfaces::~LstRestrictedInterfaces()
{
}

YangResult_E GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::LstRestrictedInterfaces::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        capacity-sharing-groups
// Description: Reference to capacities of sharing-groups supported by this endpoint
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::LstCapacitySharingGroups::LstCapacitySharingGroups(uint32_t id)
	: YangList("capacity-sharing-groups", id)
{
}

GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::LstCapacitySharingGroups::~LstCapacitySharingGroups()
{
}

YangResult_E GrpUplaneConfGroup::LstStaticLowLevelTxEndpoints::LstCapacitySharingGroups::initialise(void)
{


	return YangResult_E::OK;
}





// -----------------------------------------------------------------------------
// List:        static-low-level-rx-endpoints
// Description: Object model for static-low-level-rx-endpoints configuration
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::LstStaticLowLevelRxEndpoints(uint32_t id)
	: YangList("static-low-level-rx-endpoints", id)
{
}

GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::~LstStaticLowLevelRxEndpoints()
{
}

YangResult_E GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/static-low-level-rx-endpoints/name
	// Description: Unique name of static-low-level-rx-endpoints object.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/static-low-level-rx-endpoints/array
	// Description: Contains distname of rx-arrays, particular low-level-rx-endpoints is in hardware dependency with.
	//              Note: single instance of rx-arrays can be referenced by many instances of low-level-rx-endpoints
	//              (e.g. to allow DU to handle multiple fronthauls and multiple component carriers).
	// Ref:         /user-plane-configuration/rx-arrays/name
	// Units:
	// -----------------------------------------------------------------------------
	RefArray arrayInst(ITEM_ARRAY);
	addReference(arrayInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/static-low-level-rx-endpoints/endpoint-type
	// Description: Reference to endpoint type capabilities list element supported by this endpoint
	// Ref:         ../../endpoint-types/id
	// Units:
	// -----------------------------------------------------------------------------
	RefEndpointType endpointTypeInst(ITEM_ENDPOINT_TYPE);
	addReference(endpointTypeInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/static-low-level-rx-endpoints/restricted-interfaces
	// Description: Optionally used to indicate that a low-level link is constrained to operate only via a subset of the available interfaces.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstRestrictedInterfaces restrictedInterfacesInst(ITEM_RESTRICTED_INTERFACES);
	restrictedInterfacesInst.initialise();
	addList(restrictedInterfacesInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/static-low-level-rx-endpoints/capacity-sharing-groups
	// Description: Reference to capacities of sharing-groups supported by this endpoint
	// Array Key:
	// -----------------------------------------------------------------------------
	LstCapacitySharingGroups capacitySharingGroupsInst(ITEM_CAPACITY_SHARING_GROUPS);
	capacitySharingGroupsInst.initialise();
	addList(capacitySharingGroupsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/static-low-level-rx-endpoints/name
// Description: Unique name of static-low-level-rx-endpoints object.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/static-low-level-rx-endpoints/array
// Description: Contains distname of rx-arrays, particular low-level-rx-endpoints is in hardware dependency with.
//              Note: single instance of rx-arrays can be referenced by many instances of low-level-rx-endpoints
//              (e.g. to allow DU to handle multiple fronthauls and multiple component carriers).
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::RefArray::RefArray(uint32_t id)
	: YangReference("array", id, "/user-plane-configuration/rx-arrays/name")
{
}

GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::RefArray::~RefArray()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/static-low-level-rx-endpoints/endpoint-type
// Description: Reference to endpoint type capabilities list element supported by this endpoint
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::RefEndpointType::RefEndpointType(uint32_t id)
	: YangReference("endpoint-type", id, "../../endpoint-types/id")
{
}

GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::RefEndpointType::~RefEndpointType()
{
}

// -----------------------------------------------------------------------------
// List:        restricted-interfaces
// Description: Optionally used to indicate that a low-level link is constrained to operate only via a subset of the available interfaces.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::LstRestrictedInterfaces::LstRestrictedInterfaces(uint32_t id)
	: YangList("restricted-interfaces", id)
{
}

GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::LstRestrictedInterfaces::~LstRestrictedInterfaces()
{
}

YangResult_E GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::LstRestrictedInterfaces::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        capacity-sharing-groups
// Description: Reference to capacities of sharing-groups supported by this endpoint
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::LstCapacitySharingGroups::LstCapacitySharingGroups(uint32_t id)
	: YangList("capacity-sharing-groups", id)
{
}

GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::LstCapacitySharingGroups::~LstCapacitySharingGroups()
{
}

YangResult_E GrpUplaneConfGroup::LstStaticLowLevelRxEndpoints::LstCapacitySharingGroups::initialise(void)
{


	return YangResult_E::OK;
}





// -----------------------------------------------------------------------------
// List:        low-level-tx-endpoints
// Description: Object model for low-level-tx-endpoints configuration - augmented static-low-level-tx-endpoints by local-address
//              which cannot be added to static low-level-tx-endpoints as we cannot have modificable element in static object
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelTxEndpoints::LstLowLevelTxEndpoints(uint32_t id)
	: YangList("low-level-tx-endpoints", id)
{
}

GrpUplaneConfGroup::LstLowLevelTxEndpoints::~LstLowLevelTxEndpoints()
{
}

YangResult_E GrpUplaneConfGroup::LstLowLevelTxEndpoints::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/low-level-tx-endpoints/name
	// Description: Unique name of low-level-tx-endpoint object. Reference to static object
	// Ref:         /user-plane-configuration/static-low-level-tx-endpoints/name
	// Units:
	// -----------------------------------------------------------------------------
	RefName nameInst(ITEM_NAME);
	addReference(nameInst);

	// -----------------------------------------------------------------------------
	// Container:   /uplane-conf-group/low-level-tx-endpoints/compression
	// Description: Container which consists of global configurable parameters for compression
	// -----------------------------------------------------------------------------
	CntCompression compressionInst(ITEM_COMPRESSION);
	compressionInst.initialise();
	addContainer(compressionInst);

	// -----------------------------------------------------------------------------
	// Container:   /uplane-conf-group/low-level-tx-endpoints/e-axcid
	// Description: Contains local address of low level TX endpoint offered by Netconf server.
	// -----------------------------------------------------------------------------
	CntEAxcid eAxcidInst(ITEM_E_AXCID);
	eAxcidInst.initialise();
	addContainer(eAxcidInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/low-level-tx-endpoints/scs-config
	// Description:
	// -----------------------------------------------------------------------------
	GrpScsConfig scsConfigInst(ITEM_SCS_CONFIG);
	scsConfigInst.initialise();
	addGroup(scsConfigInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/low-level-tx-endpoints/name
// Description: Unique name of low-level-tx-endpoint object. Reference to static object
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelTxEndpoints::RefName::RefName(uint32_t id)
	: YangReference("name", id, "/user-plane-configuration/static-low-level-tx-endpoints/name")
{
}

GrpUplaneConfGroup::LstLowLevelTxEndpoints::RefName::~RefName()
{
}

// -----------------------------------------------------------------------------
// Container:   compression
// Description: Container which consists of global configurable parameters for compression
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelTxEndpoints::CntCompression::CntCompression(uint32_t id)
	: YangContainer("compression", id)
{
}

GrpUplaneConfGroup::LstLowLevelTxEndpoints::CntCompression::~CntCompression()
{
}

YangResult_E GrpUplaneConfGroup::LstLowLevelTxEndpoints::CntCompression::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/low-level-tx-endpoints/compression/cf:compression-details
	// Module: o-ran-compression-factors
	// Description:
	// -----------------------------------------------------------------------------
	ModuleORanCompressionFactors_NS::GrpCompressionDetails cfCompressionDetailsInst(ITEM_CF_COMPRESSION_DETAILS);
	cfCompressionDetailsInst.initialise();
	addGroup(cfCompressionDetailsInst);



	return YangResult_E::OK;
}




// -----------------------------------------------------------------------------
// Container:   e-axcid
// Description: Contains local address of low level TX endpoint offered by Netconf server.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelTxEndpoints::CntEAxcid::CntEAxcid(uint32_t id)
	: YangContainer("e-axcid", id)
{
}

GrpUplaneConfGroup::LstLowLevelTxEndpoints::CntEAxcid::~CntEAxcid()
{
}

YangResult_E GrpUplaneConfGroup::LstLowLevelTxEndpoints::CntEAxcid::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/low-level-tx-endpoints/e-axcid/eaxc
	// Description:
	// -----------------------------------------------------------------------------
	GrpEaxc eaxcInst(ITEM_EAXC);
	eaxcInst.initialise();
	addGroup(eaxcInst);



	return YangResult_E::OK;
}






// -----------------------------------------------------------------------------
// List:        low-level-rx-endpoints
// Description: Object model for low-level-rx-endpoint configuration - augmented static-low-level-rx-endpoints by local-address
//              which cannot be added to static low-level-rx-endpoints as we cannot have modificable element in static object
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxEndpoints::LstLowLevelRxEndpoints(uint32_t id)
	: YangList("low-level-rx-endpoints", id)
{
}

GrpUplaneConfGroup::LstLowLevelRxEndpoints::~LstLowLevelRxEndpoints()
{
}

YangResult_E GrpUplaneConfGroup::LstLowLevelRxEndpoints::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/low-level-rx-endpoints/non-time-managed-delay-enabled
	// Description: Tells if non time managed delay shall be enabled
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafNonTimeManagedDelayEnabled nonTimeManagedDelayEnabledInst(ITEM_NON_TIME_MANAGED_DELAY_ENABLED);
	addLeaf(nonTimeManagedDelayEnabledInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/low-level-rx-endpoints/name
	// Description: Unique name of low-level-rx-endpoint object. Reference to static object
	// Ref:         /user-plane-configuration/static-low-level-rx-endpoints/name
	// Units:
	// -----------------------------------------------------------------------------
	RefName nameInst(ITEM_NAME);
	addReference(nameInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/low-level-rx-endpoints/ul-fft-sampling-offsets
	// Description: List of FFT sampling offsets configured for each SCS that will be used.
	//              Client shall configure one element for each SCS that will be used.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstUlFftSamplingOffsets ulFftSamplingOffsetsInst(ITEM_UL_FFT_SAMPLING_OFFSETS);
	ulFftSamplingOffsetsInst.initialise();
	addList(ulFftSamplingOffsetsInst);

	// -----------------------------------------------------------------------------
	// Container:   /uplane-conf-group/low-level-rx-endpoints/compression
	// Description: Container which consists of global configurable parameters for compression
	// -----------------------------------------------------------------------------
	CntCompression compressionInst(ITEM_COMPRESSION);
	compressionInst.initialise();
	addContainer(compressionInst);

	// -----------------------------------------------------------------------------
	// Container:   /uplane-conf-group/low-level-rx-endpoints/e-axcid
	// Description: Contains local address of low level RX endpoint offered by Netconf server.
	// -----------------------------------------------------------------------------
	CntEAxcid eAxcidInst(ITEM_E_AXCID);
	eAxcidInst.initialise();
	addContainer(eAxcidInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/low-level-rx-endpoints/scs-config
	// Description:
	// -----------------------------------------------------------------------------
	GrpScsConfig scsConfigInst(ITEM_SCS_CONFIG);
	scsConfigInst.initialise();
	addGroup(scsConfigInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/low-level-rx-endpoints/non-time-managed-delay-enabled
// Description: Tells if non time managed delay shall be enabled
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxEndpoints::LeafNonTimeManagedDelayEnabled::LeafNonTimeManagedDelayEnabled(uint32_t id)
	: YangLeaf("non-time-managed-delay-enabled", id)
{
}

GrpUplaneConfGroup::LstLowLevelRxEndpoints::LeafNonTimeManagedDelayEnabled::~LeafNonTimeManagedDelayEnabled()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/low-level-rx-endpoints/name
// Description: Unique name of low-level-rx-endpoint object. Reference to static object
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxEndpoints::RefName::RefName(uint32_t id)
	: YangReference("name", id, "/user-plane-configuration/static-low-level-rx-endpoints/name")
{
}

GrpUplaneConfGroup::LstLowLevelRxEndpoints::RefName::~RefName()
{
}

// -----------------------------------------------------------------------------
// List:        ul-fft-sampling-offsets
// Description: List of FFT sampling offsets configured for each SCS that will be used.
//              Client shall configure one element for each SCS that will be used.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxEndpoints::LstUlFftSamplingOffsets::LstUlFftSamplingOffsets(uint32_t id)
	: YangList("ul-fft-sampling-offsets", id)
{
}

GrpUplaneConfGroup::LstLowLevelRxEndpoints::LstUlFftSamplingOffsets::~LstUlFftSamplingOffsets()
{
}

YangResult_E GrpUplaneConfGroup::LstLowLevelRxEndpoints::LstUlFftSamplingOffsets::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/low-level-rx-endpoints/ul-fft-sampling-offsets/scs
	// Description: Value corresponds to SCS values defined for frameStructure in C-plane
	//              Note: set of allowed values is restricted by SCS derived from values in supported-frame-structures.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafScs scsInst(ITEM_SCS);
	addLeaf(scsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/low-level-rx-endpoints/ul-fft-sampling-offsets/ul-fft-sampling-offset
	// Description: Determines time advance of capture window for FFT.
	//              Value represents time advance of capture window start in relation to the end of CP. Unit is Ts.
	//              Note: value of this parameter is usually set to '0' (zero) for PRACH channels.
	//              Any phase offset resulting from the non-zero value of this parameter is handled in O-DU.
	// Type:        uint16
	// Units:       Ts
	// -----------------------------------------------------------------------------
	LeafUlFftSamplingOffset ulFftSamplingOffsetInst(ITEM_UL_FFT_SAMPLING_OFFSET);
	addLeaf(ulFftSamplingOffsetInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/low-level-rx-endpoints/ul-fft-sampling-offsets/scs
// Description: Value corresponds to SCS values defined for frameStructure in C-plane
//              Note: set of allowed values is restricted by SCS derived from values in supported-frame-structures.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxEndpoints::LstUlFftSamplingOffsets::LeafScs::LeafScs(uint32_t id)
	: YangLeaf("scs", id)
{
}

GrpUplaneConfGroup::LstLowLevelRxEndpoints::LstUlFftSamplingOffsets::LeafScs::~LeafScs()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/low-level-rx-endpoints/ul-fft-sampling-offsets/ul-fft-sampling-offset
// Description: Determines time advance of capture window for FFT.
//              Value represents time advance of capture window start in relation to the end of CP. Unit is Ts.
//              Note: value of this parameter is usually set to '0' (zero) for PRACH channels.
//              Any phase offset resulting from the non-zero value of this parameter is handled in O-DU.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxEndpoints::LstUlFftSamplingOffsets::LeafUlFftSamplingOffset::LeafUlFftSamplingOffset(uint32_t id)
	: YangLeaf("ul-fft-sampling-offset", id)
{
}

GrpUplaneConfGroup::LstLowLevelRxEndpoints::LstUlFftSamplingOffsets::LeafUlFftSamplingOffset::~LeafUlFftSamplingOffset()
{
}



// -----------------------------------------------------------------------------
// Container:   compression
// Description: Container which consists of global configurable parameters for compression
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxEndpoints::CntCompression::CntCompression(uint32_t id)
	: YangContainer("compression", id)
{
}

GrpUplaneConfGroup::LstLowLevelRxEndpoints::CntCompression::~CntCompression()
{
}

YangResult_E GrpUplaneConfGroup::LstLowLevelRxEndpoints::CntCompression::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/low-level-rx-endpoints/compression/cf:compression-details
	// Module: o-ran-compression-factors
	// Description:
	// -----------------------------------------------------------------------------
	ModuleORanCompressionFactors_NS::GrpCompressionDetails cfCompressionDetailsInst(ITEM_CF_COMPRESSION_DETAILS);
	cfCompressionDetailsInst.initialise();
	addGroup(cfCompressionDetailsInst);



	return YangResult_E::OK;
}




// -----------------------------------------------------------------------------
// Container:   e-axcid
// Description: Contains local address of low level RX endpoint offered by Netconf server.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstLowLevelRxEndpoints::CntEAxcid::CntEAxcid(uint32_t id)
	: YangContainer("e-axcid", id)
{
}

GrpUplaneConfGroup::LstLowLevelRxEndpoints::CntEAxcid::~CntEAxcid()
{
}

YangResult_E GrpUplaneConfGroup::LstLowLevelRxEndpoints::CntEAxcid::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/low-level-rx-endpoints/e-axcid/eaxc
	// Description:
	// -----------------------------------------------------------------------------
	GrpEaxc eaxcInst(ITEM_EAXC);
	eaxcInst.initialise();
	addGroup(eaxcInst);



	return YangResult_E::OK;
}






// -----------------------------------------------------------------------------
// List:        tx-array-carriers
// Description: Object model for tx-array-carriers configuration
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrayCarriers::LstTxArrayCarriers(uint32_t id)
	: YangList("tx-array-carriers", id)
{
}

GrpUplaneConfGroup::LstTxArrayCarriers::~LstTxArrayCarriers()
{
}

YangResult_E GrpUplaneConfGroup::LstTxArrayCarriers::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/tx-array-carriers/name
	// Description: Unique name of tx-array-carriers object.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/tx-array-carriers/gain
	// Description: Transmission gain in dB. Value applicable to each array element carrier belonging to array carrier.
	// Type:        dec64
	// Units:       dB
	// -----------------------------------------------------------------------------
	LeafGain gainInst(ITEM_GAIN);
	addLeaf(gainInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/tx-array-carriers/downlink-radio-frame-offset
	// Description: This parameter is used for offsetting the starting position of 10ms radio frame.
	//              Note: The value should have same value within DU to all tx-array-carrierss that have same frequency and bandwidth.
	//              Note2: Unit is 1/1.2288e9 Hz and accuracy is 1/4 Tc. Then, its range is calculated 0..12288000.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafDownlinkRadioFrameOffset downlinkRadioFrameOffsetInst(ITEM_DOWNLINK_RADIO_FRAME_OFFSET);
	addLeaf(downlinkRadioFrameOffsetInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/tx-array-carriers/downlink-sfn-offset
	// Description: This parameter is used for offsetting SFN value.
	//              Unit is in 10ms.
	//              Note: The value should have same value within DU to all tx-array-carrierss that have same frequency and bandwidth.
	// Type:        int16
	// Units:
	// -----------------------------------------------------------------------------
	LeafDownlinkSfnOffset downlinkSfnOffsetInst(ITEM_DOWNLINK_SFN_OFFSET);
	addLeaf(downlinkSfnOffsetInst);

	// -----------------------------------------------------------------------------
	// Reference:   /uplane-conf-group/tx-array-carriers/band-number
	// Description: This parameter informing which frequency band particular antenna
	//              array is serving for.
	//              Intended use is to deal with multiband solutions.
	// Ref:         /o-ran-module-cap:module-capability/o-ran-module-cap:band-capabilities/o-ran-module-cap:band-number
	// Units:
	// -----------------------------------------------------------------------------
	RefBandNumber bandNumberInst(ITEM_BAND_NUMBER);
	addReference(bandNumberInst);

	// -----------------------------------------------------------------------------
	// Container:   /uplane-conf-group/tx-array-carriers/lte-tdd-frame
	// Description: Container which consists of global configurable parameters for tdd Frame
	// -----------------------------------------------------------------------------
	CntLteTddFrame lteTddFrameInst(ITEM_LTE_TDD_FRAME);
	lteTddFrameInst.initialise();
	addContainer(lteTddFrameInst);

	// -----------------------------------------------------------------------------
	// Container:   /uplane-conf-group/tx-array-carriers/laa-carrier-configuration
	// Description: Container to specify LAA feature related carrier configuration.
	// -----------------------------------------------------------------------------
	CntLaaCarrierConfiguration laaCarrierConfigurationInst(ITEM_LAA_CARRIER_CONFIGURATION);
	laaCarrierConfigurationInst.initialise();
	addContainer(laaCarrierConfigurationInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/tx-array-carriers/tx-common-array-carrier-elements
	// Description:
	// -----------------------------------------------------------------------------
	GrpTxCommonArrayCarrierElements txCommonArrayCarrierElementsInst(ITEM_TX_COMMON_ARRAY_CARRIER_ELEMENTS);
	txCommonArrayCarrierElementsInst.initialise();
	addGroup(txCommonArrayCarrierElementsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/tx-array-carriers/name
// Description: Unique name of tx-array-carriers object.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrayCarriers::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpUplaneConfGroup::LstTxArrayCarriers::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/tx-array-carriers/gain
// Description: Transmission gain in dB. Value applicable to each array element carrier belonging to array carrier.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrayCarriers::LeafGain::LeafGain(uint32_t id)
	: YangLeaf("gain", id)
{
}

GrpUplaneConfGroup::LstTxArrayCarriers::LeafGain::~LeafGain()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/tx-array-carriers/downlink-radio-frame-offset
// Description: This parameter is used for offsetting the starting position of 10ms radio frame.
//              Note: The value should have same value within DU to all tx-array-carrierss that have same frequency and bandwidth.
//              Note2: Unit is 1/1.2288e9 Hz and accuracy is 1/4 Tc. Then, its range is calculated 0..12288000.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrayCarriers::LeafDownlinkRadioFrameOffset::LeafDownlinkRadioFrameOffset(uint32_t id)
	: YangLeaf("downlink-radio-frame-offset", id)
{
}

GrpUplaneConfGroup::LstTxArrayCarriers::LeafDownlinkRadioFrameOffset::~LeafDownlinkRadioFrameOffset()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/tx-array-carriers/downlink-sfn-offset
// Description: This parameter is used for offsetting SFN value.
//              Unit is in 10ms.
//              Note: The value should have same value within DU to all tx-array-carrierss that have same frequency and bandwidth.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrayCarriers::LeafDownlinkSfnOffset::LeafDownlinkSfnOffset(uint32_t id)
	: YangLeaf("downlink-sfn-offset", id)
{
}

GrpUplaneConfGroup::LstTxArrayCarriers::LeafDownlinkSfnOffset::~LeafDownlinkSfnOffset()
{
}

// -----------------------------------------------------------------------------
// Reference:   /uplane-conf-group/tx-array-carriers/band-number
// Description: This parameter informing which frequency band particular antenna
//              array is serving for.
//              Intended use is to deal with multiband solutions.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrayCarriers::RefBandNumber::RefBandNumber(uint32_t id)
	: YangReference("band-number", id, "/o-ran-module-cap:module-capability/o-ran-module-cap:band-capabilities/o-ran-module-cap:band-number")
{
}

GrpUplaneConfGroup::LstTxArrayCarriers::RefBandNumber::~RefBandNumber()
{
}

// -----------------------------------------------------------------------------
// Container:   lte-tdd-frame
// Description: Container which consists of global configurable parameters for tdd Frame
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrayCarriers::CntLteTddFrame::CntLteTddFrame(uint32_t id)
	: YangContainer("lte-tdd-frame", id)
{
}

GrpUplaneConfGroup::LstTxArrayCarriers::CntLteTddFrame::~CntLteTddFrame()
{
}

YangResult_E GrpUplaneConfGroup::LstTxArrayCarriers::CntLteTddFrame::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/tx-array-carriers/lte-tdd-frame/subframe-assignment
	// Description: Indicates DL/UL subframe configuration as specified in
	//              3GPP TS 36.211 [v15.3.0, table 4.2-2]
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafSubframeAssignment subframeAssignmentInst(ITEM_SUBFRAME_ASSIGNMENT);
	addLeaf(subframeAssignmentInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/tx-array-carriers/lte-tdd-frame/special-subframe-pattern
	// Description: Indicates TDD special subframe configuration as in TS 36.211
	//              [v15.3.0, table 4.2-1]
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafSpecialSubframePattern specialSubframePatternInst(ITEM_SPECIAL_SUBFRAME_PATTERN);
	addLeaf(specialSubframePatternInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/tx-array-carriers/lte-tdd-frame/subframe-assignment
// Description: Indicates DL/UL subframe configuration as specified in
//              3GPP TS 36.211 [v15.3.0, table 4.2-2]
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrayCarriers::CntLteTddFrame::LeafSubframeAssignment::LeafSubframeAssignment(uint32_t id)
	: YangLeaf("subframe-assignment", id)
{
}

GrpUplaneConfGroup::LstTxArrayCarriers::CntLteTddFrame::LeafSubframeAssignment::~LeafSubframeAssignment()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/tx-array-carriers/lte-tdd-frame/special-subframe-pattern
// Description: Indicates TDD special subframe configuration as in TS 36.211
//              [v15.3.0, table 4.2-1]
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrayCarriers::CntLteTddFrame::LeafSpecialSubframePattern::LeafSpecialSubframePattern(uint32_t id)
	: YangLeaf("special-subframe-pattern", id)
{
}

GrpUplaneConfGroup::LstTxArrayCarriers::CntLteTddFrame::LeafSpecialSubframePattern::~LeafSpecialSubframePattern()
{
}




// -----------------------------------------------------------------------------
// Container:   laa-carrier-configuration
// Description: Container to specify LAA feature related carrier configuration.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrayCarriers::CntLaaCarrierConfiguration::CntLaaCarrierConfiguration(uint32_t id)
	: YangContainer("laa-carrier-configuration", id)
{
}

GrpUplaneConfGroup::LstTxArrayCarriers::CntLaaCarrierConfiguration::~CntLaaCarrierConfiguration()
{
}

YangResult_E GrpUplaneConfGroup::LstTxArrayCarriers::CntLaaCarrierConfiguration::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/tx-array-carriers/laa-carrier-configuration/laa-carrier-config
	// Description:
	// -----------------------------------------------------------------------------
	GrpLaaCarrierConfig laaCarrierConfigInst(ITEM_LAA_CARRIER_CONFIG);
	laaCarrierConfigInst.initialise();
	addGroup(laaCarrierConfigInst);



	return YangResult_E::OK;
}






// -----------------------------------------------------------------------------
// List:        rx-array-carriers
// Description: Object model for rx-array-carriers configuration
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrayCarriers::LstRxArrayCarriers(uint32_t id)
	: YangList("rx-array-carriers", id)
{
}

GrpUplaneConfGroup::LstRxArrayCarriers::~LstRxArrayCarriers()
{
}

YangResult_E GrpUplaneConfGroup::LstRxArrayCarriers::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/rx-array-carriers/name
	// Description: Unique name of rx-array-carriers object.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/rx-array-carriers/downlink-radio-frame-offset
	// Description: This parameter is used for offsetting the starting position of 10ms radio frame.
	//              Note: The value should have same value within DU to all tx-array-carrierss that have same frequency and bandwidth.
	//              Note2: Unit is 1/1.2288e9 Hz and accuracy is 1/4 Tc. Then, its range is calculated 0..12288000.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafDownlinkRadioFrameOffset downlinkRadioFrameOffsetInst(ITEM_DOWNLINK_RADIO_FRAME_OFFSET);
	addLeaf(downlinkRadioFrameOffsetInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/rx-array-carriers/downlink-sfn-offset
	// Description: This parameter is used for offsetting SFN value.
	//              Unit is in 10ms.
	//              Note: The value should have same value within DU to all tx-array-carrierss that have same frequency and bandwidth.
	// Type:        int16
	// Units:
	// -----------------------------------------------------------------------------
	LeafDownlinkSfnOffset downlinkSfnOffsetInst(ITEM_DOWNLINK_SFN_OFFSET);
	addLeaf(downlinkSfnOffsetInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/rx-array-carriers/gain-correction
	// Description: Gain correction of RF path linked with array element or array layers
	// Type:        dec64
	// Units:       dB
	// -----------------------------------------------------------------------------
	LeafGainCorrection gainCorrectionInst(ITEM_GAIN_CORRECTION);
	addLeaf(gainCorrectionInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/rx-array-carriers/n-ta-offset
	// Description: Value of configurable N-TA offset
	//              units are Tc=~0.5ns=1/1.96608GHz
	// Type:        uint32
	// Units:       Tc
	// -----------------------------------------------------------------------------
	LeafNTaOffset nTaOffsetInst(ITEM_N_TA_OFFSET);
	addLeaf(nTaOffsetInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/rx-array-carriers/rx-common-array-carrier-elements
	// Description:
	// -----------------------------------------------------------------------------
	GrpRxCommonArrayCarrierElements rxCommonArrayCarrierElementsInst(ITEM_RX_COMMON_ARRAY_CARRIER_ELEMENTS);
	rxCommonArrayCarrierElementsInst.initialise();
	addGroup(rxCommonArrayCarrierElementsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/rx-array-carriers/name
// Description: Unique name of rx-array-carriers object.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrayCarriers::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpUplaneConfGroup::LstRxArrayCarriers::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/rx-array-carriers/downlink-radio-frame-offset
// Description: This parameter is used for offsetting the starting position of 10ms radio frame.
//              Note: The value should have same value within DU to all tx-array-carrierss that have same frequency and bandwidth.
//              Note2: Unit is 1/1.2288e9 Hz and accuracy is 1/4 Tc. Then, its range is calculated 0..12288000.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrayCarriers::LeafDownlinkRadioFrameOffset::LeafDownlinkRadioFrameOffset(uint32_t id)
	: YangLeaf("downlink-radio-frame-offset", id)
{
}

GrpUplaneConfGroup::LstRxArrayCarriers::LeafDownlinkRadioFrameOffset::~LeafDownlinkRadioFrameOffset()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/rx-array-carriers/downlink-sfn-offset
// Description: This parameter is used for offsetting SFN value.
//              Unit is in 10ms.
//              Note: The value should have same value within DU to all tx-array-carrierss that have same frequency and bandwidth.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrayCarriers::LeafDownlinkSfnOffset::LeafDownlinkSfnOffset(uint32_t id)
	: YangLeaf("downlink-sfn-offset", id)
{
}

GrpUplaneConfGroup::LstRxArrayCarriers::LeafDownlinkSfnOffset::~LeafDownlinkSfnOffset()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/rx-array-carriers/gain-correction
// Description: Gain correction of RF path linked with array element or array layers
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrayCarriers::LeafGainCorrection::LeafGainCorrection(uint32_t id)
	: YangLeaf("gain-correction", id)
{
}

GrpUplaneConfGroup::LstRxArrayCarriers::LeafGainCorrection::~LeafGainCorrection()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/rx-array-carriers/n-ta-offset
// Description: Value of configurable N-TA offset
//              units are Tc=~0.5ns=1/1.96608GHz
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrayCarriers::LeafNTaOffset::LeafNTaOffset(uint32_t id)
	: YangLeaf("n-ta-offset", id)
{
}

GrpUplaneConfGroup::LstRxArrayCarriers::LeafNTaOffset::~LeafNTaOffset()
{
}



// -----------------------------------------------------------------------------
// List:        tx-arrays
// Description: Structure describing TX array parameters
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrays::LstTxArrays(uint32_t id)
	: YangList("tx-arrays", id)
{
}

GrpUplaneConfGroup::LstTxArrays::~LstTxArrays()
{
}

YangResult_E GrpUplaneConfGroup::LstTxArrays::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/tx-arrays/max-gain
	// Description: Max gain of RF path linked with array element (minimum over elements of array) or array layers
	// Type:        dec64
	// Units:       dB
	// -----------------------------------------------------------------------------
	LeafMaxGain maxGainInst(ITEM_MAX_GAIN);
	addLeaf(maxGainInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/tx-arrays/independent-power-budget
	// Description: If true then every element of array has own, power budget independent from power budget of other elements.
	//              Else all elements of array that are at same row and column and have same polarization share power budget
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafIndependentPowerBudget independentPowerBudgetInst(ITEM_INDEPENDENT_POWER_BUDGET);
	addLeaf(independentPowerBudgetInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/tx-arrays/capabilities
	// Description: List of capabilities related to this tx-array
	// Array Key:
	// -----------------------------------------------------------------------------
	LstCapabilities capabilitiesInst(ITEM_CAPABILITIES);
	capabilitiesInst.initialise();
	addList(capabilitiesInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/tx-arrays/parameters
	// Description:
	// -----------------------------------------------------------------------------
	GrpParameters parametersInst(ITEM_PARAMETERS);
	parametersInst.initialise();
	addGroup(parametersInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/tx-arrays/max-gain
// Description: Max gain of RF path linked with array element (minimum over elements of array) or array layers
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrays::LeafMaxGain::LeafMaxGain(uint32_t id)
	: YangLeaf("max-gain", id)
{
}

GrpUplaneConfGroup::LstTxArrays::LeafMaxGain::~LeafMaxGain()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/tx-arrays/independent-power-budget
// Description: If true then every element of array has own, power budget independent from power budget of other elements.
//              Else all elements of array that are at same row and column and have same polarization share power budget
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrays::LeafIndependentPowerBudget::LeafIndependentPowerBudget(uint32_t id)
	: YangLeaf("independent-power-budget", id)
{
}

GrpUplaneConfGroup::LstTxArrays::LeafIndependentPowerBudget::~LeafIndependentPowerBudget()
{
}

// -----------------------------------------------------------------------------
// List:        capabilities
// Description: List of capabilities related to this tx-array
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstTxArrays::LstCapabilities::LstCapabilities(uint32_t id)
	: YangList("capabilities", id)
{
}

GrpUplaneConfGroup::LstTxArrays::LstCapabilities::~LstCapabilities()
{
}

YangResult_E GrpUplaneConfGroup::LstTxArrays::LstCapabilities::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/tx-arrays/capabilities/mcap:support-for-dl
	// Module: o-ran-module-cap
	// Description:
	// -----------------------------------------------------------------------------
	ModuleORanModuleCap_NS::GrpSupportForDl mcapSupportForDlInst(ITEM_MCAP_SUPPORT_FOR_DL);
	mcapSupportForDlInst.initialise();
	addGroup(mcapSupportForDlInst);



	return YangResult_E::OK;
}





// -----------------------------------------------------------------------------
// List:        rx-arrays
// Description: Structure describing RX array parameters
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrays::LstRxArrays(uint32_t id)
	: YangList("rx-arrays", id)
{
}

GrpUplaneConfGroup::LstRxArrays::~LstRxArrays()
{
}

YangResult_E GrpUplaneConfGroup::LstRxArrays::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/rx-arrays/capabilities
	// Description: List of capabilities related to this rx-array
	// Array Key:
	// -----------------------------------------------------------------------------
	LstCapabilities capabilitiesInst(ITEM_CAPABILITIES);
	capabilitiesInst.initialise();
	addList(capabilitiesInst);

	// -----------------------------------------------------------------------------
	// Container:   /uplane-conf-group/rx-arrays/gain-correction-range
	// Description: Array gain correction factor
	// -----------------------------------------------------------------------------
	CntGainCorrectionRange gainCorrectionRangeInst(ITEM_GAIN_CORRECTION_RANGE);
	gainCorrectionRangeInst.initialise();
	addContainer(gainCorrectionRangeInst);

	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/rx-arrays/parameters
	// Description:
	// -----------------------------------------------------------------------------
	GrpParameters parametersInst(ITEM_PARAMETERS);
	parametersInst.initialise();
	addGroup(parametersInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        capabilities
// Description: List of capabilities related to this rx-array
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrays::LstCapabilities::LstCapabilities(uint32_t id)
	: YangList("capabilities", id)
{
}

GrpUplaneConfGroup::LstRxArrays::LstCapabilities::~LstCapabilities()
{
}

YangResult_E GrpUplaneConfGroup::LstRxArrays::LstCapabilities::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/rx-arrays/capabilities/mcap:support-for-ul
	// Module: o-ran-module-cap
	// Description:
	// -----------------------------------------------------------------------------
	ModuleORanModuleCap_NS::GrpSupportForUl mcapSupportForUlInst(ITEM_MCAP_SUPPORT_FOR_UL);
	mcapSupportForUlInst.initialise();
	addGroup(mcapSupportForUlInst);



	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// Container:   gain-correction-range
// Description: Array gain correction factor
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrays::CntGainCorrectionRange::CntGainCorrectionRange(uint32_t id)
	: YangContainer("gain-correction-range", id)
{
}

GrpUplaneConfGroup::LstRxArrays::CntGainCorrectionRange::~CntGainCorrectionRange()
{
}

YangResult_E GrpUplaneConfGroup::LstRxArrays::CntGainCorrectionRange::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/rx-arrays/gain-correction-range/max
	// Description: Array gain correction factor - maximum allowed value
	// Type:        dec64
	// Units:       dB
	// -----------------------------------------------------------------------------
	LeafMax maxInst(ITEM_MAX);
	addLeaf(maxInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/rx-arrays/gain-correction-range/min
	// Description: Array gain correction factor - minimum allowed value
	// Type:        dec64
	// Units:       dB
	// -----------------------------------------------------------------------------
	LeafMin minInst(ITEM_MIN);
	addLeaf(minInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/rx-arrays/gain-correction-range/max
// Description: Array gain correction factor - maximum allowed value
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrays::CntGainCorrectionRange::LeafMax::LeafMax(uint32_t id)
	: YangLeaf("max", id)
{
}

GrpUplaneConfGroup::LstRxArrays::CntGainCorrectionRange::LeafMax::~LeafMax()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/rx-arrays/gain-correction-range/min
// Description: Array gain correction factor - minimum allowed value
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRxArrays::CntGainCorrectionRange::LeafMin::LeafMin(uint32_t id)
	: YangLeaf("min", id)
{
}

GrpUplaneConfGroup::LstRxArrays::CntGainCorrectionRange::LeafMin::~LeafMin()
{
}






// -----------------------------------------------------------------------------
// List:        relations
// Description: Structure describing relations between array elements
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRelations::LstRelations(uint32_t id)
	: YangList("relations", id)
{
}

GrpUplaneConfGroup::LstRelations::~LstRelations()
{
}

YangResult_E GrpUplaneConfGroup::LstRelations::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/relations/entity
	// Description: Relation entity. Used as a key for list of relations.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafEntity entityInst(ITEM_ENTITY);
	addLeaf(entityInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/relations/types
	// Description: Defines relation type and pairs for array elements for given arrays
	// Array Key:
	// -----------------------------------------------------------------------------
	LstTypes typesInst(ITEM_TYPES);
	typesInst.initialise();
	addList(typesInst);

	// -----------------------------------------------------------------------------
	// Container:   /uplane-conf-group/relations/array1
	// Description: Defnes name for first array
	// -----------------------------------------------------------------------------
	CntArray1 array1Inst(ITEM_ARRAY1);
	array1Inst.initialise();
	addContainer(array1Inst);

	// -----------------------------------------------------------------------------
	// Container:   /uplane-conf-group/relations/array2
	// Description: Defnes name for second array
	// -----------------------------------------------------------------------------
	CntArray2 array2Inst(ITEM_ARRAY2);
	array2Inst.initialise();
	addContainer(array2Inst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/relations/entity
// Description: Relation entity. Used as a key for list of relations.
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRelations::LeafEntity::LeafEntity(uint32_t id)
	: YangLeaf("entity", id)
{
}

GrpUplaneConfGroup::LstRelations::LeafEntity::~LeafEntity()
{
}

// -----------------------------------------------------------------------------
// List:        types
// Description: Defines relation type and pairs for array elements for given arrays
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRelations::LstTypes::LstTypes(uint32_t id)
	: YangList("types", id)
{
}

GrpUplaneConfGroup::LstRelations::LstTypes::~LstTypes()
{
}

YangResult_E GrpUplaneConfGroup::LstRelations::LstTypes::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/relations/types/relation-type
	// Description: Type of relation between array elements
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafRelationType relationTypeInst(ITEM_RELATION_TYPE);
	addLeaf(relationTypeInst);

	// -----------------------------------------------------------------------------
	// List:        /uplane-conf-group/relations/types/pairs
	// Description: defines related array elements
	// Array Key:
	// -----------------------------------------------------------------------------
	LstPairs pairsInst(ITEM_PAIRS);
	pairsInst.initialise();
	addList(pairsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/relations/types/relation-type
// Description: Type of relation between array elements
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRelations::LstTypes::LeafRelationType::LeafRelationType(uint32_t id)
	: YangLeaf("relation-type", id)
{
}

GrpUplaneConfGroup::LstRelations::LstTypes::LeafRelationType::~LeafRelationType()
{
}

// -----------------------------------------------------------------------------
// List:        pairs
// Description: defines related array elements
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRelations::LstTypes::LstPairs::LstPairs(uint32_t id)
	: YangList("pairs", id)
{
}

GrpUplaneConfGroup::LstRelations::LstTypes::LstPairs::~LstPairs()
{
}

YangResult_E GrpUplaneConfGroup::LstRelations::LstTypes::LstPairs::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/relations/types/pairs/element-array1
	// Description: Tells about id of element from array1
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafElementArray1 elementArray1Inst(ITEM_ELEMENT_ARRAY1);
	addLeaf(elementArray1Inst);

	// -----------------------------------------------------------------------------
	// Leaf:        /uplane-conf-group/relations/types/pairs/element-array2
	// Description: Tells about id of element from array2
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafElementArray2 elementArray2Inst(ITEM_ELEMENT_ARRAY2);
	addLeaf(elementArray2Inst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/relations/types/pairs/element-array1
// Description: Tells about id of element from array1
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRelations::LstTypes::LstPairs::LeafElementArray1::LeafElementArray1(uint32_t id)
	: YangLeaf("element-array1", id)
{
}

GrpUplaneConfGroup::LstRelations::LstTypes::LstPairs::LeafElementArray1::~LeafElementArray1()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /uplane-conf-group/relations/types/pairs/element-array2
// Description: Tells about id of element from array2
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRelations::LstTypes::LstPairs::LeafElementArray2::LeafElementArray2(uint32_t id)
	: YangLeaf("element-array2", id)
{
}

GrpUplaneConfGroup::LstRelations::LstTypes::LstPairs::LeafElementArray2::~LeafElementArray2()
{
}





// -----------------------------------------------------------------------------
// Container:   array1
// Description: Defnes name for first array
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRelations::CntArray1::CntArray1(uint32_t id)
	: YangContainer("array1", id)
{
}

GrpUplaneConfGroup::LstRelations::CntArray1::~CntArray1()
{
}

YangResult_E GrpUplaneConfGroup::LstRelations::CntArray1::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/relations/array1/array-choice
	// Description:
	// -----------------------------------------------------------------------------
	GrpArrayChoice arrayChoiceInst(ITEM_ARRAY_CHOICE);
	arrayChoiceInst.initialise();
	addGroup(arrayChoiceInst);



	return YangResult_E::OK;
}




// -----------------------------------------------------------------------------
// Container:   array2
// Description: Defnes name for second array
// -----------------------------------------------------------------------------
GrpUplaneConfGroup::LstRelations::CntArray2::CntArray2(uint32_t id)
	: YangContainer("array2", id)
{
}

GrpUplaneConfGroup::LstRelations::CntArray2::~CntArray2()
{
}

YangResult_E GrpUplaneConfGroup::LstRelations::CntArray2::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /uplane-conf-group/relations/array2/array-choice
	// Description:
	// -----------------------------------------------------------------------------
	GrpArrayChoice arrayChoiceInst(ITEM_ARRAY_CHOICE);
	arrayChoiceInst.initialise();
	addGroup(arrayChoiceInst);



	return YangResult_E::OK;
}








// -----------------------------------------------------------------------------
// Grouping:    tx-array-notification-group
// Description: Grouping for tx-array for notification
// -----------------------------------------------------------------------------
GrpTxArrayNotificationGroup::GrpTxArrayNotificationGroup(uint32_t id)
	: YangGroup("tx-array-notification-group", id)
{
}

GrpTxArrayNotificationGroup::~GrpTxArrayNotificationGroup()
{
}

YangResult_E GrpTxArrayNotificationGroup::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /tx-array-notification-group/tx-array-carriers
	// Description: notification of state change for tx-array-carriers
	// Array Key:
	// -----------------------------------------------------------------------------
	LstTxArrayCarriers txArrayCarriersInst(ITEM_TX_ARRAY_CARRIERS);
	txArrayCarriersInst.initialise();
	addList(txArrayCarriersInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        tx-array-carriers
// Description: notification of state change for tx-array-carriers
// -----------------------------------------------------------------------------
GrpTxArrayNotificationGroup::LstTxArrayCarriers::LstTxArrayCarriers(uint32_t id)
	: YangList("tx-array-carriers", id)
{
}

GrpTxArrayNotificationGroup::LstTxArrayCarriers::~LstTxArrayCarriers()
{
}

YangResult_E GrpTxArrayNotificationGroup::LstTxArrayCarriers::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /tx-array-notification-group/tx-array-carriers/name
	// Description: name of tx-array-carriers is notified at state change
	// Ref:         /user-plane-configuration/tx-array-carriers/name
	// Units:
	// -----------------------------------------------------------------------------
	RefName nameInst(ITEM_NAME);
	addReference(nameInst);

	// -----------------------------------------------------------------------------
	// Reference:   /tx-array-notification-group/tx-array-carriers/state
	// Description: state of tx-array-carriers is notified at state change
	// Ref:         /user-plane-configuration/tx-array-carriers/state
	// Units:
	// -----------------------------------------------------------------------------
	RefState stateInst(ITEM_STATE);
	addReference(stateInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /tx-array-notification-group/tx-array-carriers/name
// Description: name of tx-array-carriers is notified at state change
// -----------------------------------------------------------------------------
GrpTxArrayNotificationGroup::LstTxArrayCarriers::RefName::RefName(uint32_t id)
	: YangReference("name", id, "/user-plane-configuration/tx-array-carriers/name")
{
}

GrpTxArrayNotificationGroup::LstTxArrayCarriers::RefName::~RefName()
{
}

// -----------------------------------------------------------------------------
// Reference:   /tx-array-notification-group/tx-array-carriers/state
// Description: state of tx-array-carriers is notified at state change
// -----------------------------------------------------------------------------
GrpTxArrayNotificationGroup::LstTxArrayCarriers::RefState::RefState(uint32_t id)
	: YangReference("state", id, "/user-plane-configuration/tx-array-carriers/state")
{
}

GrpTxArrayNotificationGroup::LstTxArrayCarriers::RefState::~RefState()
{
}





// -----------------------------------------------------------------------------
// Grouping:    rx-array-notification-group
// Description: Grouping for rx-array for notification
// -----------------------------------------------------------------------------
GrpRxArrayNotificationGroup::GrpRxArrayNotificationGroup(uint32_t id)
	: YangGroup("rx-array-notification-group", id)
{
}

GrpRxArrayNotificationGroup::~GrpRxArrayNotificationGroup()
{
}

YangResult_E GrpRxArrayNotificationGroup::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /rx-array-notification-group/rx-array-carriers
	// Description: Notification used to inform about state change of rx-array-carriers
	// Array Key:
	// -----------------------------------------------------------------------------
	LstRxArrayCarriers rxArrayCarriersInst(ITEM_RX_ARRAY_CARRIERS);
	rxArrayCarriersInst.initialise();
	addList(rxArrayCarriersInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        rx-array-carriers
// Description: Notification used to inform about state change of rx-array-carriers
// -----------------------------------------------------------------------------
GrpRxArrayNotificationGroup::LstRxArrayCarriers::LstRxArrayCarriers(uint32_t id)
	: YangList("rx-array-carriers", id)
{
}

GrpRxArrayNotificationGroup::LstRxArrayCarriers::~LstRxArrayCarriers()
{
}

YangResult_E GrpRxArrayNotificationGroup::LstRxArrayCarriers::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /rx-array-notification-group/rx-array-carriers/name
	// Description: name of rx-array-carriers is notified at state change
	// Ref:         /user-plane-configuration/rx-array-carriers/name
	// Units:
	// -----------------------------------------------------------------------------
	RefName nameInst(ITEM_NAME);
	addReference(nameInst);

	// -----------------------------------------------------------------------------
	// Reference:   /rx-array-notification-group/rx-array-carriers/state
	// Description: state of rx-array-carriers is notified at state change
	// Ref:         /user-plane-configuration/rx-array-carriers/state
	// Units:
	// -----------------------------------------------------------------------------
	RefState stateInst(ITEM_STATE);
	addReference(stateInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /rx-array-notification-group/rx-array-carriers/name
// Description: name of rx-array-carriers is notified at state change
// -----------------------------------------------------------------------------
GrpRxArrayNotificationGroup::LstRxArrayCarriers::RefName::RefName(uint32_t id)
	: YangReference("name", id, "/user-plane-configuration/rx-array-carriers/name")
{
}

GrpRxArrayNotificationGroup::LstRxArrayCarriers::RefName::~RefName()
{
}

// -----------------------------------------------------------------------------
// Reference:   /rx-array-notification-group/rx-array-carriers/state
// Description: state of rx-array-carriers is notified at state change
// -----------------------------------------------------------------------------
GrpRxArrayNotificationGroup::LstRxArrayCarriers::RefState::RefState(uint32_t id)
	: YangReference("state", id, "/user-plane-configuration/rx-array-carriers/state")
{
}

GrpRxArrayNotificationGroup::LstRxArrayCarriers::RefState::~RefState()
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
// Notification:tx-array-carriers-state-change
// Description: Notification used to inform about state change of tx-array-carriers
// -----------------------------------------------------------------------------
NotifTxArrayCarriersStateChange::NotifTxArrayCarriersStateChange(uint32_t id)
	: YangNotif("tx-array-carriers-state-change", id)
{
}

NotifTxArrayCarriersStateChange::~NotifTxArrayCarriersStateChange()
{
}

YangResult_E NotifTxArrayCarriersStateChange::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /tx-array-carriers-state-change/tx-array-notification-group
	// Description:
	// -----------------------------------------------------------------------------
	GrpTxArrayNotificationGroup txArrayNotificationGroupInst(ITEM_TX_ARRAY_NOTIFICATION_GROUP);
	txArrayNotificationGroupInst.initialise();
	addGroup(txArrayNotificationGroupInst);



	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// Notification:rx-array-carriers-state-change
// Description: Notification used to inform about state change of tx-array-carriers
// -----------------------------------------------------------------------------
NotifRxArrayCarriersStateChange::NotifRxArrayCarriersStateChange(uint32_t id)
	: YangNotif("rx-array-carriers-state-change", id)
{
}

NotifRxArrayCarriersStateChange::~NotifRxArrayCarriersStateChange()
{
}

YangResult_E NotifRxArrayCarriersStateChange::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /rx-array-carriers-state-change/rx-array-notification-group
	// Description:
	// -----------------------------------------------------------------------------
	GrpRxArrayNotificationGroup rxArrayNotificationGroupInst(ITEM_RX_ARRAY_NOTIFICATION_GROUP);
	rxArrayNotificationGroupInst.initialise();
	addGroup(rxArrayNotificationGroupInst);



	return YangResult_E::OK;
}




// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-uplane-conf
// Description: This module defines the module capabilities for
//              the O-RAN Radio Unit U-Plane configuration.
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
ModuleORanUplaneConf::ModuleORanUplaneConf(uint32_t id)
	: YangModule ("o-ran-uplane-conf",
	              "o-ran-uplane-conf.yang",
	              "o-ran-uplane-conf",
	              "urn:o-ran:uplane-conf:1.0",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Container:   /user-plane-configuration
	// Description: top level container for user plane configuration
	// -----------------------------------------------------------------------------
	CntUserPlaneConfiguration userPlaneConfigurationInst(ITEM_USER_PLANE_CONFIGURATION);
	userPlaneConfigurationInst.initialise();
	addContainer(userPlaneConfigurationInst);

	// -----------------------------------------------------------------------------
	// Notification:/tx-array-carriers-state-change
	// Description: Notification used to inform about state change of tx-array-carriers
	// -----------------------------------------------------------------------------
	NotifTxArrayCarriersStateChange txArrayCarriersStateChangeInst(ITEM_TX_ARRAY_CARRIERS_STATE_CHANGE);
	txArrayCarriersStateChangeInst.initialise();
	addNotification(txArrayCarriersStateChangeInst);

	// -----------------------------------------------------------------------------
	// Notification:/rx-array-carriers-state-change
	// Description: Notification used to inform about state change of tx-array-carriers
	// -----------------------------------------------------------------------------
	NotifRxArrayCarriersStateChange rxArrayCarriersStateChangeInst(ITEM_RX_ARRAY_CARRIERS_STATE_CHANGE);
	rxArrayCarriersStateChangeInst.initialise();
	addNotification(rxArrayCarriersStateChangeInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleORanUplaneConf::~ModuleORanUplaneConf()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleORanUplaneConf::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleORanUplaneConf>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleORanUplaneConf::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
