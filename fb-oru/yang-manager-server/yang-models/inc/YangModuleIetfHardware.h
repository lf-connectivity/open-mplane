#ifndef _MODULE_IETF_HARDWARE_H_
#define _MODULE_IETF_HARDWARE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfHardware.h
 * \brief     Module IetfHardware interface
 *
 *
 * \details   This file defines the YANG module ietf-hardware interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-hardware"
 *            YANG Filename:    "ietf-hardware.yang"
 *            Module Prefix:    "hw"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-hardware"
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

// Module:   ietf-inet-types
// Revision:
// Notes:
#include "YangModuleIetfInetTypes.h"

// Module:   ietf-yang-types
// Revision:
// Notes:
#include "YangModuleIetfYangTypes.h"

// Module:   iana-hardware
// Revision:
// Notes:
#include "YangModuleIanaHardware.h"


namespace Mplane {

namespace ModuleIetfHardware_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// Represents the various possible administrative states.
enum class AdminState_E : uint32_t
{
	UNKNOWN,	// The resource is unable to report administrative state.
	LOCKED,	// The resource is administratively prohibited from use.
	SHUTTING_DOWN,	// The resource usage is administratively limited to current
			// instances of use.
	UNLOCKED,	// The resource is not administratively prohibited from
			// use.

	Num_AdminState_E
};

// Represents the possible values of operational states.
enum class OperState_E : uint32_t
{
	UNKNOWN,	// The resource is unable to report its operational state.
	DISABLED,	// The resource is totally inoperable.
	ENABLED,	// The resource is partially or fully operable.
	TESTING,	// The resource is currently being tested and cannot
			// therefore report whether or not it is operational.

	Num_OperState_E
};

// Represents the possible values of usage states.
enum class UsageState_E : uint32_t
{
	UNKNOWN,	// The resource is unable to report usage state.
	IDLE,	// The resource is servicing no users.
	ACTIVE,	// The resource is currently in use, and it has sufficient
			// spare capacity to provide for additional users.
	BUSY,	// The resource is currently in use, but it currently has no
			// spare capacity to provide for additional users.

	Num_UsageState_E
};

// Represents the possible values of standby states.
enum class StandbyState_E : uint32_t
{
	UNKNOWN,	// The resource is unable to report standby state.
	HOT_STANDBY,	// The resource is not providing service, but it will be
			// immediately able to take over the role of the resource to
			// be backed up, without the need for initialization
			// activity, and will contain the same information as the
			// resource to be backed up.
	COLD_STANDBY,	// The resource is to back up another resource, but it will
			// not be immediately able to take over the role of a
			// resource to be backed up and will require some
			// initialization activity.
	PROVIDING_SERVICE,	// The resource is providing service.

	Num_StandbyState_E
};

// A node using this data type represents the sensor measurement
// data type associated with a physical sensor value.  The actual
// data units are determined by examining a node of this type
// together with the associated sensor-value-scale node.
// A node of this type SHOULD be defined together with nodes of
// type sensor-value-scale and type sensor-value-precision.
// These three types are used to identify the semantics of a node
// of type sensor-value.
enum class SensorValueType_E : uint32_t
{
	OTHER,	// A measure other than those listed below.
	UNKNOWN,	// An unknown measurement or arbitrary, relative numbers
	VOLTS_AC,	// A measure of electric potential (alternating current).
	VOLTS_DC,	// A measure of electric potential (direct current).
	AMPERES,	// A measure of electric current.
	WATTS,	// A measure of power.
	HERTZ,	// A measure of frequency.
	CELSIUS,	// A measure of temperature.
	PERCENT_RH,	// A measure of percent relative humidity.
	RPM,	// A measure of shaft revolutions per minute.
	CMM,	// A measure of cubic meters per minute (airflow).
	TRUTH_VALUE,	// Value is one of 1 (true) or 2 (false)

	Num_SensorValueType_E
};

// A node using this data type represents a data scaling factor,
// represented with an International System of Units (SI) prefix.
// The actual data units are determined by examining a node of
// this type together with the associated sensor-value-type.
// A node of this type SHOULD be defined together with nodes of
// type sensor-value-type and type sensor-value-precision.
// Together, associated nodes of these three types are used to
// identify the semantics of a node of type sensor-value.
enum class SensorValueScale_E : uint32_t
{
	YOCTO,	// Data scaling factor of 10^-24.
	ZEPTO,	// Data scaling factor of 10^-21.
	ATTO,	// Data scaling factor of 10^-18.
	FEMTO,	// Data scaling factor of 10^-15.
	PICO,	// Data scaling factor of 10^-12.
	NANO,	// Data scaling factor of 10^-9.
	MICRO,	// Data scaling factor of 10^-6.
	MILLI,	// Data scaling factor of 10^-3.
	UNITS,	// Data scaling factor of 10^0.
	KILO,	// Data scaling factor of 10^3.
	MEGA,	// Data scaling factor of 10^6.
	GIGA,	// Data scaling factor of 10^9.
	TERA,	// Data scaling factor of 10^12.
	PETA,	// Data scaling factor of 10^15.
	EXA,	// Data scaling factor of 10^18.
	ZETTA,	// Data scaling factor of 10^21.
	YOTTA,	// Data scaling factor of 10^24.

	Num_SensorValueScale_E
};

// A node using this data type represents the operational status
// of a physical sensor.
enum class SensorStatus_E : uint32_t
{
	OK,	// Indicates that the server can obtain the sensor value.
	UNAVAILABLE,	// Indicates that the server presently cannot obtain the
			// sensor value.
	NONOPERATIONAL,	// Indicates that the server believes the sensor is broken.
			// The sensor could have a hard failure (disconnected wire)
			// or a soft failure such as out-of-range, jittery, or wildly
			// fluctuating readings.

	Num_SensorStatus_E
};


// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the device implements
//              the ENTITY-MIB.
// -----------------------------------------------------------------------------
class FeatureEntityMib : public YangFeature
{
public:
	FeatureEntityMib(uint32_t id);
	~FeatureEntityMib();

}; // FeatureEntityMib

// -----------------------------------------------------------------------------
// Feature
// Description: Indicates that ENTITY-STATE-MIB objects are supported
// -----------------------------------------------------------------------------
class FeatureHardwareState : public YangFeature
{
public:
	FeatureHardwareState(uint32_t id);
	~FeatureHardwareState();

}; // FeatureHardwareState

// -----------------------------------------------------------------------------
// Feature
// Description: Indicates that ENTITY-SENSOR-MIB objects are supported
// -----------------------------------------------------------------------------
class FeatureHardwareSensor : public YangFeature
{
public:
	FeatureHardwareSensor(uint32_t id);
	~FeatureHardwareSensor();

}; // FeatureHardwareSensor


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
// Container:   /hardware
// Description: Data nodes representing components.
//              If the server supports configuration of hardware components,
//              then this data model is instantiated in the configuration
//              datastores supported by the server.  The leaf-list 'datastore'
//              for the module 'ietf-hardware' in the YANG library provides
//              this information.
// -----------------------------------------------------------------------------
class CntHardware : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_LAST_CHANGE,  // LeafLastChange
		ITEM_COMPONENT,  // LstComponent
	};

	CntHardware(uint32_t id);
	~CntHardware();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /hardware/last-change
	// Description: The time the '/hardware/component' list changed in the
	//              operational state.
	// -----------------------------------------------------------------------------
	class LeafLastChange : public YangLeaf
	{
	public:

		LeafLastChange(uint32_t id);
		~LeafLastChange();

	}; // LeafLastChange

	// -----------------------------------------------------------------------------
	// List:        /hardware/component
	// Description: List of components.
	//              When the server detects a new hardware component, it
	//              initializes a list entry in the operational state.
	//              If the server does not support configuration of hardware
	//              components, list entries in the operational state are
	//              initialized with values for all nodes as detected by the
	//              implementation.
	//              Otherwise, this procedure is followed:
	//                1. If there is an entry in the '/hardware/component' list
	//                   in the intended configuration with values for the nodes
	//                   'class', 'parent', and 'parent-rel-pos' that are equal
	//                   to the detected values, then the list entry in the
	//                   operational state is initialized with the configured
	//                   values, including the 'name'.
	//                2. Otherwise (i.e., there is no matching configuration
	//                   entry), the list entry in the operational state is
	//                   initialized with values for all nodes as detected by
	//                   the implementation.
	//              If the '/hardware/component' list in the intended
	//              configuration is modified, then the system MUST behave as if
	//              it re-initializes itself and follow the procedure in (1).
	// -----------------------------------------------------------------------------
	class LstComponent : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_NAME,  // LeafName
			ITEM_CLASS,  // LeafClass
			ITEM_PHYSICAL_INDEX,  // LeafPhysicalIndex
			ITEM_DESCRIPTION,  // LeafDescription
			ITEM_PARENT_REL_POS,  // LeafParentRelPos
			ITEM_HARDWARE_REV,  // LeafHardwareRev
			ITEM_FIRMWARE_REV,  // LeafFirmwareRev
			ITEM_SOFTWARE_REV,  // LeafSoftwareRev
			ITEM_SERIAL_NUM,  // LeafSerialNum
			ITEM_MFG_NAME,  // LeafMfgName
			ITEM_MODEL_NAME,  // LeafModelName
			ITEM_ALIAS,  // LeafAlias
			ITEM_ASSET_ID,  // LeafAssetId
			ITEM_IS_FRU,  // LeafIsFru
			ITEM_MFG_DATE,  // LeafMfgDate
			ITEM_UUID,  // LeafUuid
			ITEM_PRODUCT_CODE,  // LeafProductCode
			ITEM_ENERGY_SAVING_ENABLED,  // LeafEnergySavingEnabled
			ITEM_PARENT,  // RefParent
			ITEM_O_RAN_NAME,  // RefORanName
			ITEM_STATE,  // CntState
			ITEM_SENSOR_DATA,  // CntSensorData
			ITEM_LABEL_CONTENT,  // CntLabelContent
			ITEM_CONTAINS_CHILD,  // LstContainsChild
			ITEM_URI,  // LstUri
		};

		LstComponent(uint32_t id);
		~LstComponent();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/name
		// Description: The name assigned to this component.
		//              This name is not required to be the same as
		//              entPhysicalName.
		// -----------------------------------------------------------------------------
		class LeafName : public YangLeaf
		{
		public:

			LeafName(uint32_t id);
			~LeafName();

		}; // LeafName

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/class
		// Description: An indication of the general hardware type of the
		//              component.
		// -----------------------------------------------------------------------------
		class LeafClass : public YangLeaf
		{
		public:

			LeafClass(uint32_t id);
			~LeafClass();

		}; // LeafClass

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/physical-index
		// Description: The entPhysicalIndex for the entPhysicalEntry represented
		//              by this list entry.
		// -----------------------------------------------------------------------------
		class LeafPhysicalIndex : public YangLeaf
		{
		public:

			LeafPhysicalIndex(uint32_t id);
			~LeafPhysicalIndex();

		}; // LeafPhysicalIndex

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/description
		// Description: A textual description of the component.  This node should
		//              contain a string that identifies the manufacturer's name
		//              for the component and should be set to a distinct value
		//              for each version or model of the component.
		// -----------------------------------------------------------------------------
		class LeafDescription : public YangLeaf
		{
		public:

			LeafDescription(uint32_t id);
			~LeafDescription();

		}; // LeafDescription

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/parent-rel-pos
		// Description: An indication of the relative position of this child
		//              component among all its sibling components.  Sibling
		//              components are defined as components that:
		//                o share the same value of the 'parent' node and
		//                o share a common base identity for the 'class' node.
		//              Note that the last rule gives implementations flexibility
		//              in how components are numbered.  For example, some
		//              implementations might have a single number series for all
		//              components derived from 'ianahw:port', while some others
		//              might have different number series for different
		//              components with identities derived from 'ianahw:port' (for
		//              example, one for registered jack 45 (RJ45) and one for
		//              small form-factor pluggable (SFP)).
		// -----------------------------------------------------------------------------
		class LeafParentRelPos : public YangLeaf
		{
		public:

			LeafParentRelPos(uint32_t id);
			~LeafParentRelPos();

		}; // LeafParentRelPos

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/hardware-rev
		// Description: The vendor-specific hardware revision string for the
		//              component.  The preferred value is the hardware revision
		//              identifier actually printed on the component itself (if
		//              present).
		// -----------------------------------------------------------------------------
		class LeafHardwareRev : public YangLeaf
		{
		public:

			LeafHardwareRev(uint32_t id);
			~LeafHardwareRev();

		}; // LeafHardwareRev

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/firmware-rev
		// Description: The vendor-specific firmware revision string for the
		//              component.
		// -----------------------------------------------------------------------------
		class LeafFirmwareRev : public YangLeaf
		{
		public:

			LeafFirmwareRev(uint32_t id);
			~LeafFirmwareRev();

		}; // LeafFirmwareRev

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/software-rev
		// Description: The vendor-specific software revision string for the
		//              component.
		// -----------------------------------------------------------------------------
		class LeafSoftwareRev : public YangLeaf
		{
		public:

			LeafSoftwareRev(uint32_t id);
			~LeafSoftwareRev();

		}; // LeafSoftwareRev

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/serial-num
		// Description: The vendor-specific serial number string for the
		//              component.  The preferred value is the serial number
		//              string actually printed on the component itself (if
		//              present).
		// -----------------------------------------------------------------------------
		class LeafSerialNum : public YangLeaf
		{
		public:

			LeafSerialNum(uint32_t id);
			~LeafSerialNum();

		}; // LeafSerialNum

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/mfg-name
		// Description: The name of the manufacturer of this physical component.
		//              The preferred value is the manufacturer name string
		//              actually printed on the component itself (if present).
		//              Note that comparisons between instances of the
		//              'model-name', 'firmware-rev', 'software-rev', and
		//              'serial-num' nodes are only meaningful amongst components
		//              with the same value of 'mfg-name'.
		//              If the manufacturer name string associated with the
		//              physical component is unknown to the server, then this
		//              node is not instantiated.
		// -----------------------------------------------------------------------------
		class LeafMfgName : public YangLeaf
		{
		public:

			LeafMfgName(uint32_t id);
			~LeafMfgName();

		}; // LeafMfgName

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/model-name
		// Description: The vendor-specific model name identifier string
		//              associated with this physical component.  The preferred
		//              value is the customer-visible part number, which may be
		//              printed on the component itself.
		//              If the model name string associated with the physical
		//              component is unknown to the server, then this node is not
		//              instantiated.
		// -----------------------------------------------------------------------------
		class LeafModelName : public YangLeaf
		{
		public:

			LeafModelName(uint32_t id);
			~LeafModelName();

		}; // LeafModelName

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/alias
		// Description: An 'alias' name for the component, as specified by a
		//              network manager, that provides a non-volatile 'handle' for
		//              the component.
		//              If no configured value exists, the server MAY set the
		//              value of this node to a locally unique value in the
		//              operational state.
		//              A server implementation MAY map this leaf to the
		//              entPhysicalAlias MIB object.  Such an implementation needs
		//              to use some mechanism to handle the differences in size
		//              and characters allowed between this leaf and
		//              entPhysicalAlias.  The definition of such a mechanism is
		//              outside the scope of this document.
		// -----------------------------------------------------------------------------
		class LeafAlias : public YangLeaf
		{
		public:

			LeafAlias(uint32_t id);
			~LeafAlias();

		}; // LeafAlias

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/asset-id
		// Description: This node is a user-assigned asset tracking identifier for
		//              the component.
		//              A server implementation MAY map this leaf to the
		//              entPhysicalAssetID MIB object.  Such an implementation
		//              needs to use some mechanism to handle the differences in
		//              size and characters allowed between this leaf and
		//              entPhysicalAssetID.  The definition of such a mechanism is
		//              outside the scope of this document.
		// -----------------------------------------------------------------------------
		class LeafAssetId : public YangLeaf
		{
		public:

			LeafAssetId(uint32_t id);
			~LeafAssetId();

		}; // LeafAssetId

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/is-fru
		// Description: This node indicates whether or not this component is
		//              considered a 'field-replaceable unit' by the vendor.  If
		//              this node contains the value 'true', then this component
		//              identifies a field-replaceable unit.  For all components
		//              that are permanently contained within a field-replaceable
		//              unit, the value 'false' should be returned for this
		//              node.
		// -----------------------------------------------------------------------------
		class LeafIsFru : public YangLeaf
		{
		public:

			LeafIsFru(uint32_t id);
			~LeafIsFru();

		}; // LeafIsFru

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/mfg-date
		// Description: The date of manufacturing of the managed component.
		// -----------------------------------------------------------------------------
		class LeafMfgDate : public YangLeaf
		{
		public:

			LeafMfgDate(uint32_t id);
			~LeafMfgDate();

		}; // LeafMfgDate

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/uuid
		// Description: A Universally Unique Identifier of the component.
		// -----------------------------------------------------------------------------
		class LeafUuid : public YangLeaf
		{
		public:

			LeafUuid(uint32_t id);
			~LeafUuid();

		}; // LeafUuid

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/product-code
		// Description: O-RAN term that is distinct from model-name in ietf-hardware.
		// -----------------------------------------------------------------------------
		class LeafProductCode : public YangLeaf
		{
		public:

			LeafProductCode(uint32_t id);
			~LeafProductCode();

		}; // LeafProductCode

		// -----------------------------------------------------------------------------
		// Leaf:        /hardware/component/energy-saving-enabled
		// Description: This parameter can enable O-RAN unit to be switched to energy
		//              saving mode.
		//              TRUE indicates to switch the energy saving mode.
		//              FALSE indicates to cancel the energy saving mode.
		//              At the energy saving mode, all power of whole O-RAN unit becomes
		//              lowest level whereas M-plane is still available
		// -----------------------------------------------------------------------------
		class LeafEnergySavingEnabled : public YangLeaf
		{
		public:

			LeafEnergySavingEnabled(uint32_t id);
			~LeafEnergySavingEnabled();

		}; // LeafEnergySavingEnabled

		// -----------------------------------------------------------------------------
		// Reference:   /hardware/component/parent
		// Description: The name of the component that physically contains this
		//              component.
		//              If this leaf is not instantiated, it indicates that this
		//              component is not contained in any other component.
		//              In the event that a physical component is contained by
		//              more than one physical component (e.g., double-wide
		//              modules), this node contains the name of one of these
		//              components.  An implementation MUST use the same name
		//              every time this node is instantiated.
		// -----------------------------------------------------------------------------
		class RefParent : public YangReference
		{
		public:

			RefParent(uint32_t id);
			~RefParent();

		}; // RefParent

		// -----------------------------------------------------------------------------
		// Reference:   /hardware/component/o-ran-name
		// Description: O-RAN name needed to bind and match with the name of hw element,
		//              to be compliant with O-RAN naming convention.
		// -----------------------------------------------------------------------------
		class RefORanName : public YangReference
		{
		public:

			RefORanName(uint32_t id);
			~RefORanName();

		}; // RefORanName

		// -----------------------------------------------------------------------------
		// Container:   /hardware/component/state
		// Description: State-related nodes
		// -----------------------------------------------------------------------------
		class CntState : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_STATE_LAST_CHANGED,  // LeafStateLastChanged
				ITEM_ADMIN_STATE,  // LeafAdminState
				ITEM_OPER_STATE,  // LeafOperState
				ITEM_USAGE_STATE,  // LeafUsageState
				ITEM_ALARM_STATE,  // LeafAlarmState
				ITEM_STANDBY_STATE,  // LeafStandbyState
				ITEM_POWER_STATE,  // LeafPowerState
				ITEM_AVAILABILITY_STATE,  // LeafAvailabilityState
			};

			CntState(uint32_t id);
			~CntState();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/state/state-last-changed
			// Description: The date and time when the value of any of the
			//              admin-state, oper-state, usage-state, alarm-state, or
			//              standby-state changed for this component.
			//              If there has been no change since the last
			//              re-initialization of the local system, this node
			//              contains the date and time of local system
			//              initialization.  If there has been no change since the
			//              component was added to the local system, this node
			//              contains the date and time of the insertion.
			// -----------------------------------------------------------------------------
			class LeafStateLastChanged : public YangLeaf
			{
			public:

				LeafStateLastChanged(uint32_t id);
				~LeafStateLastChanged();

			}; // LeafStateLastChanged

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/state/admin-state
			// Description: The administrative state for this component.
			//              This node refers to a component's administrative
			//              permission to service both other components within its
			//              containment hierarchy as well other users of its
			//              services defined by means outside the scope of this
			//              module.
			//              Some components exhibit only a subset of the remaining
			//              administrative state values.  Some components cannot be
			//              locked; hence, this node exhibits only the 'unlocked'
			//              state.  Other components cannot be shut down gracefully;
			//              hence, this node does not exhibit the 'shutting-down'
			//              state.
			// -----------------------------------------------------------------------------
			class LeafAdminState : public YangLeaf
			{
			public:

				// The administrative state for this component.
				// This node refers to a component's administrative
				// permission to service both other components within its
				// containment hierarchy as well other users of its
				// services defined by means outside the scope of this
				// module.
				// Some components exhibit only a subset of the remaining
				// administrative state values.  Some components cannot be
				// locked; hence, this node exhibits only the 'unlocked'
				// state.  Other components cannot be shut down gracefully;
				// hence, this node does not exhibit the 'shutting-down'
				// state.
				enum class AdminState_E : uint32_t
				{

					Num_AdminState_E
				};

				LeafAdminState(uint32_t id);
				~LeafAdminState();

			}; // LeafAdminState

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/state/oper-state
			// Description: The operational state for this component.
			//              Note that this node does not follow the administrative
			//              state.  An administrative state of 'down' does not
			//              predict an operational state of 'disabled'.
			//              Note that some implementations may not be able to
			//              accurately report oper-state while the admin-state node
			//              has a value other than 'unlocked'.  In these cases, this
			//              node MUST have a value of 'unknown'.
			// -----------------------------------------------------------------------------
			class LeafOperState : public YangLeaf
			{
			public:

				// The operational state for this component.
				// Note that this node does not follow the administrative
				// state.  An administrative state of 'down' does not
				// predict an operational state of 'disabled'.
				// Note that some implementations may not be able to
				// accurately report oper-state while the admin-state node
				// has a value other than 'unlocked'.  In these cases, this
				// node MUST have a value of 'unknown'.
				enum class OperState_E : uint32_t
				{

					Num_OperState_E
				};

				LeafOperState(uint32_t id);
				~LeafOperState();

			}; // LeafOperState

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/state/usage-state
			// Description: The usage state for this component.
			//              This node refers to a component's ability to service
			//              more components in a containment hierarchy.
			//              Some components will exhibit only a subset of the usage
			//              state values.  Components that are unable to ever
			//              service any components within a containment hierarchy
			//              will always have a usage state of 'busy'.  In some
			//              cases, a component will be able to support only one
			//              other component within its containment hierarchy and
			//              will therefore only exhibit values of 'idle' and
			//              'busy'.
			// -----------------------------------------------------------------------------
			class LeafUsageState : public YangLeaf
			{
			public:

				// The usage state for this component.
				// This node refers to a component's ability to service
				// more components in a containment hierarchy.
				// Some components will exhibit only a subset of the usage
				// state values.  Components that are unable to ever
				// service any components within a containment hierarchy
				// will always have a usage state of 'busy'.  In some
				// cases, a component will be able to support only one
				// other component within its containment hierarchy and
				// will therefore only exhibit values of 'idle' and
				// 'busy'.
				enum class UsageState_E : uint32_t
				{

					Num_UsageState_E
				};

				LeafUsageState(uint32_t id);
				~LeafUsageState();

			}; // LeafUsageState

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/state/alarm-state
			// Description: The alarm state for this component.  It does not
			//              include the alarms raised on child components within its
			//              containment hierarchy.
			// -----------------------------------------------------------------------------
			class LeafAlarmState : public YangLeaf
			{
			public:

				LeafAlarmState(uint32_t id);
				~LeafAlarmState();

			}; // LeafAlarmState

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/state/standby-state
			// Description: The standby state for this component.
			//              Some components will exhibit only a subset of the
			//              remaining standby state values.  If this component
			//              cannot operate in a standby role, the value of this node
			//              will always be 'providing-service'.
			// -----------------------------------------------------------------------------
			class LeafStandbyState : public YangLeaf
			{
			public:

				// The standby state for this component.
				// Some components will exhibit only a subset of the
				// remaining standby state values.  If this component
				// cannot operate in a standby role, the value of this node
				// will always be 'providing-service'.
				enum class StandbyState_E : uint32_t
				{

					Num_StandbyState_E
				};

				LeafStandbyState(uint32_t id);
				~LeafStandbyState();

			}; // LeafStandbyState

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/state/power-state
			// Description: The current power saving state for this component.
			//              Note - hw:/hardware/compnent/state/standby-state defined in RFC 4268 is
			//              used for redundancy purposes and not power saving operations.
			// -----------------------------------------------------------------------------
			class LeafPowerState : public YangLeaf
			{
			public:

				// The current power saving state for this component.
				// Note - hw:/hardware/compnent/state/standby-state defined in RFC 4268 is
				// used for redundancy purposes and not power saving operations.
				enum class PowerState_E : uint32_t
				{

					Num_PowerState_E
				};

				LeafPowerState(uint32_t id);
				~LeafPowerState();

			}; // LeafPowerState

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/state/availability-state
			// Description: Equipment's availability-state is derived by matching active faults
			//              and their impact to module's operation and enables an equipment to indicate
			//              that even though it may have one or more critical alarms, it can continue
			//              to serve traffic.
			// -----------------------------------------------------------------------------
			class LeafAvailabilityState : public YangLeaf
			{
			public:

				// Equipment's availability-state is derived by matching active faults
				// and their impact to module's operation and enables an equipment to indicate
				// that even though it may have one or more critical alarms, it can continue
				// to serve traffic.
				enum class AvailabilityState_E : uint32_t
				{

					Num_AvailabilityState_E
				};

				LeafAvailabilityState(uint32_t id);
				~LeafAvailabilityState();

			}; // LeafAvailabilityState

		}; // CntState

		// -----------------------------------------------------------------------------
		// Container:   /hardware/component/sensor-data
		// Description: Sensor-related nodes.
		// -----------------------------------------------------------------------------
		class CntSensorData : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_VALUE,  // LeafValue
				ITEM_VALUE_TYPE,  // LeafValueType
				ITEM_VALUE_SCALE,  // LeafValueScale
				ITEM_VALUE_PRECISION,  // LeafValuePrecision
				ITEM_OPER_STATUS,  // LeafOperStatus
				ITEM_UNITS_DISPLAY,  // LeafUnitsDisplay
				ITEM_VALUE_TIMESTAMP,  // LeafValueTimestamp
				ITEM_VALUE_UPDATE_RATE,  // LeafValueUpdateRate
			};

			CntSensorData(uint32_t id);
			~CntSensorData();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/sensor-data/value
			// Description: The most recent measurement obtained by the server
			//              for this sensor.
			//              A client that periodically fetches this node should also
			//              fetch the nodes 'value-type', 'value-scale', and
			//              'value-precision', since they may change when the value
			//              is changed.
			// -----------------------------------------------------------------------------
			class LeafValue : public YangLeaf
			{
			public:

				LeafValue(uint32_t id);
				~LeafValue();

			}; // LeafValue

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/sensor-data/value-type
			// Description: The type of data units associated with the
			//              sensor value
			// -----------------------------------------------------------------------------
			class LeafValueType : public YangLeaf
			{
			public:

				// The type of data units associated with the
				// sensor value
				enum class ValueType_E : uint32_t
				{

					Num_ValueType_E
				};

				LeafValueType(uint32_t id);
				~LeafValueType();

			}; // LeafValueType

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/sensor-data/value-scale
			// Description: The (power of 10) scaling factor associated
			//              with the sensor value
			// -----------------------------------------------------------------------------
			class LeafValueScale : public YangLeaf
			{
			public:

				// The (power of 10) scaling factor associated
				// with the sensor value
				enum class ValueScale_E : uint32_t
				{

					Num_ValueScale_E
				};

				LeafValueScale(uint32_t id);
				~LeafValueScale();

			}; // LeafValueScale

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/sensor-data/value-precision
			// Description: The number of decimal places of precision
			//              associated with the sensor value
			// -----------------------------------------------------------------------------
			class LeafValuePrecision : public YangLeaf
			{
			public:

				LeafValuePrecision(uint32_t id);
				~LeafValuePrecision();

			}; // LeafValuePrecision

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/sensor-data/oper-status
			// Description: The operational status of the sensor.
			// -----------------------------------------------------------------------------
			class LeafOperStatus : public YangLeaf
			{
			public:

				// The operational status of the sensor.
				enum class OperStatus_E : uint32_t
				{

					Num_OperStatus_E
				};

				LeafOperStatus(uint32_t id);
				~LeafOperStatus();

			}; // LeafOperStatus

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/sensor-data/units-display
			// Description: A textual description of the data units that should be
			//              used in the display of the sensor value.
			// -----------------------------------------------------------------------------
			class LeafUnitsDisplay : public YangLeaf
			{
			public:

				LeafUnitsDisplay(uint32_t id);
				~LeafUnitsDisplay();

			}; // LeafUnitsDisplay

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/sensor-data/value-timestamp
			// Description: The time the status and/or value of this sensor was last
			//              obtained by the server.
			// -----------------------------------------------------------------------------
			class LeafValueTimestamp : public YangLeaf
			{
			public:

				LeafValueTimestamp(uint32_t id);
				~LeafValueTimestamp();

			}; // LeafValueTimestamp

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/sensor-data/value-update-rate
			// Description: An indication of the frequency that the server updates
			//              the associated 'value' node, represented in
			//              milliseconds.  The value zero indicates:
			//               - the sensor value is updated on demand (e.g.,
			//                 when polled by the server for a get-request),
			//               - the sensor value is updated when the sensor
			//                 value changes (event-driven), or
			//               - the server does not know the update rate.
			// -----------------------------------------------------------------------------
			class LeafValueUpdateRate : public YangLeaf
			{
			public:

				LeafValueUpdateRate(uint32_t id);
				~LeafValueUpdateRate();

			}; // LeafValueUpdateRate

		}; // CntSensorData

		// -----------------------------------------------------------------------------
		// Container:   /hardware/component/label-content
		// Description: Which set of attributes are printed on the Radio Unit's label
		// -----------------------------------------------------------------------------
		class CntLabelContent : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_MODEL_NAME,  // LeafModelName
				ITEM_SERIAL_NUMBER,  // LeafSerialNumber
			};

			CntLabelContent(uint32_t id);
			~CntLabelContent();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/label-content/model-name
			// Description: indicates whether model-name is included on the equipment's label
			// -----------------------------------------------------------------------------
			class LeafModelName : public YangLeaf
			{
			public:

				LeafModelName(uint32_t id);
				~LeafModelName();

			}; // LeafModelName

			// -----------------------------------------------------------------------------
			// Leaf:        /hardware/component/label-content/serial-number
			// Description: indicates whether serial number is included on the equipment's label
			// -----------------------------------------------------------------------------
			class LeafSerialNumber : public YangLeaf
			{
			public:

				LeafSerialNumber(uint32_t id);
				~LeafSerialNumber();

			}; // LeafSerialNumber

		}; // CntLabelContent

		// -----------------------------------------------------------------------------
		// List:        /hardware/component/contains-child
		// Description: The name of the contained component.
		// -----------------------------------------------------------------------------
		class LstContainsChild : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstContainsChild(uint32_t id);
			~LstContainsChild();

			YangResult_E initialise(void);

		}; // LstContainsChild

		// -----------------------------------------------------------------------------
		// List:        /hardware/component/uri
		// Description: This node contains identification information about the
		//              component.
		// -----------------------------------------------------------------------------
		class LstUri : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstUri(uint32_t id);
			~LstUri();

			YangResult_E initialise(void);

		}; // LstUri

	}; // LstComponent

}; // CntHardware


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
// -----------------------------------------------------------------------------
// Notification:/hardware-state-change
// Description: A hardware-state-change notification is generated when the
//              value of /hardware/last-change changes in the operational
//              state.
// -----------------------------------------------------------------------------
class NotifHardwareStateChange : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
	};

	NotifHardwareStateChange(uint32_t id);
	~NotifHardwareStateChange();

	YangResult_E initialise(void);

}; // NotifHardwareStateChange

// -----------------------------------------------------------------------------
// Notification:/hardware-state-oper-enabled
// Description: A hardware-state-oper-enabled notification signifies that a
//              component has transitioned into the 'enabled' state.
// -----------------------------------------------------------------------------
class NotifHardwareStateOperEnabled : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_NAME,  // RefName
		ITEM_ADMIN_STATE,  // RefAdminState
		ITEM_ALARM_STATE,  // RefAlarmState
		ITEM_AVAILABILITY_STATE,  // RefAvailabilityState
	};

	NotifHardwareStateOperEnabled(uint32_t id);
	~NotifHardwareStateOperEnabled();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Reference:   /hardware-state-oper-enabled/name
	// Description: The name of the component that has transitioned into the
	//              'enabled' state.
	// -----------------------------------------------------------------------------
	class RefName : public YangReference
	{
	public:

		RefName(uint32_t id);
		~RefName();

	}; // RefName

	// -----------------------------------------------------------------------------
	// Reference:   /hardware-state-oper-enabled/admin-state
	// Description: The administrative state for the component.
	// -----------------------------------------------------------------------------
	class RefAdminState : public YangReference
	{
	public:

		RefAdminState(uint32_t id);
		~RefAdminState();

	}; // RefAdminState

	// -----------------------------------------------------------------------------
	// Reference:   /hardware-state-oper-enabled/alarm-state
	// Description: The alarm state for the component.
	// -----------------------------------------------------------------------------
	class RefAlarmState : public YangReference
	{
	public:

		RefAlarmState(uint32_t id);
		~RefAlarmState();

	}; // RefAlarmState

	// -----------------------------------------------------------------------------
	// Reference:   /hardware-state-oper-enabled/availability-state
	// Description: The availability-state of the O-RU.
	// -----------------------------------------------------------------------------
	class RefAvailabilityState : public YangReference
	{
	public:

		RefAvailabilityState(uint32_t id);
		~RefAvailabilityState();

	}; // RefAvailabilityState

}; // NotifHardwareStateOperEnabled

// -----------------------------------------------------------------------------
// Notification:/hardware-state-oper-disabled
// Description: A hardware-state-oper-disabled notification signifies that a
//              component has transitioned into the 'disabled' state.
// -----------------------------------------------------------------------------
class NotifHardwareStateOperDisabled : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_NAME,  // RefName
		ITEM_ADMIN_STATE,  // RefAdminState
		ITEM_ALARM_STATE,  // RefAlarmState
		ITEM_AVAILABILITY_STATE,  // RefAvailabilityState
	};

	NotifHardwareStateOperDisabled(uint32_t id);
	~NotifHardwareStateOperDisabled();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Reference:   /hardware-state-oper-disabled/name
	// Description: The name of the component that has transitioned into the
	//              'disabled' state.
	// -----------------------------------------------------------------------------
	class RefName : public YangReference
	{
	public:

		RefName(uint32_t id);
		~RefName();

	}; // RefName

	// -----------------------------------------------------------------------------
	// Reference:   /hardware-state-oper-disabled/admin-state
	// Description: The administrative state for the component.
	// -----------------------------------------------------------------------------
	class RefAdminState : public YangReference
	{
	public:

		RefAdminState(uint32_t id);
		~RefAdminState();

	}; // RefAdminState

	// -----------------------------------------------------------------------------
	// Reference:   /hardware-state-oper-disabled/alarm-state
	// Description: The alarm state for the component.
	// -----------------------------------------------------------------------------
	class RefAlarmState : public YangReference
	{
	public:

		RefAlarmState(uint32_t id);
		~RefAlarmState();

	}; // RefAlarmState

	// -----------------------------------------------------------------------------
	// Reference:   /hardware-state-oper-disabled/availability-state
	// Description: The availability-state of the O-RU.
	// -----------------------------------------------------------------------------
	class RefAvailabilityState : public YangReference
	{
	public:

		RefAvailabilityState(uint32_t id);
		~RefAvailabilityState();

	}; // RefAvailabilityState

}; // NotifHardwareStateOperDisabled


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      ietf-hardware
// Description: This module contains a collection of YANG definitions for
//              managing hardware.
//              This data model is designed for the Network Management Datastore
//              Architecture (NMDA) defined in RFC 8342.
//              Copyright (c) 2018 IETF Trust and the persons identified as
//              authors of the code.  All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD License
//              set forth in Section 4.c of the IETF Trust's Legal Provisions
//              Relating to IETF Documents
//              (https://trustee.ietf.org/license-info).
//              This version of this YANG module is part of RFC 8348; see
//              the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
class ModuleIetfHardware : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_ENTITY_MIB,  // Feature
		ITEM_HARDWARE_STATE,  // Feature
		ITEM_HARDWARE_SENSOR,  // Feature
		ITEM_HARDWARE,  // CntHardware
		ITEM_HARDWARE_STATE_CHANGE,  // NotifHardwareStateChange
		ITEM_HARDWARE_STATE_OPER_ENABLED,  // NotifHardwareStateOperEnabled
		ITEM_HARDWARE_STATE_OPER_DISABLED,  // NotifHardwareStateOperDisabled
	};

	ModuleIetfHardware(uint32_t id);
	~ModuleIetfHardware();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleIetfHardware_NS */

} /* namespace Mplane */

#endif /* _MODULE_IETF_HARDWARE_H_ */
