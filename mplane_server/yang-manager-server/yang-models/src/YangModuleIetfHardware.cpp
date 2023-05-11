/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfHardware.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleIetfHardware.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

// Module:   o-ran-hardware
#include "YangModuleORanHardware.h"

using namespace Mplane;
using namespace ModuleIetfHardware_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the device implements
//              the ENTITY-MIB.
// -----------------------------------------------------------------------------
FeatureEntityMib::FeatureEntityMib(uint32_t id)
    : YangFeature("entity-mib", id) {}

FeatureEntityMib::~FeatureEntityMib() {}

// -----------------------------------------------------------------------------
// Feature
// Description: Indicates that ENTITY-STATE-MIB objects are supported
// -----------------------------------------------------------------------------
FeatureHardwareState::FeatureHardwareState(uint32_t id)
    : YangFeature("hardware-state", id) {}

FeatureHardwareState::~FeatureHardwareState() {}

// -----------------------------------------------------------------------------
// Feature
// Description: Indicates that ENTITY-SENSOR-MIB objects are supported
// -----------------------------------------------------------------------------
FeatureHardwareSensor::FeatureHardwareSensor(uint32_t id)
    : YangFeature("hardware-sensor", id) {}

FeatureHardwareSensor::~FeatureHardwareSensor() {}

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
// Container:   hardware
// Description: Data nodes representing components.
//              If the server supports configuration of hardware components,
//              then this data model is instantiated in the configuration
//              datastores supported by the server.  The leaf-list 'datastore'
//              for the module 'ietf-hardware' in the YANG library provides
//              this information.
// -----------------------------------------------------------------------------
CntHardware::CntHardware(uint32_t id) : YangContainer("hardware", id) {}

CntHardware::~CntHardware() {}

YangResult_E
CntHardware::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/last-change
  // Description: The time the '/hardware/component' list changed in the
  //              operational state.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafLastChange lastChangeInst(ITEM_LAST_CHANGE);
  addLeaf(lastChangeInst);

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
  // Array Key:
  // -----------------------------------------------------------------------------
  LstComponent componentInst(ITEM_COMPONENT);
  componentInst.initialise();
  addList(componentInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/last-change
// Description: The time the '/hardware/component' list changed in the
//              operational state.
// -----------------------------------------------------------------------------
CntHardware::LeafLastChange::LeafLastChange(uint32_t id)
    : YangLeaf("last-change", id) {}

CntHardware::LeafLastChange::~LeafLastChange() {}

// -----------------------------------------------------------------------------
// List:        component
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
CntHardware::LstComponent::LstComponent(uint32_t id)
    : YangList("component", id) {}

CntHardware::LstComponent::~LstComponent() {}

YangResult_E
CntHardware::LstComponent::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/name
  // Description: The name assigned to this component.
  //              This name is not required to be the same as
  //              entPhysicalName.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/class
  // Description: An indication of the general hardware type of the
  //              component.
  // Type:        ???IDENT
  // Units:
  // -----------------------------------------------------------------------------
  LeafClass classInst(ITEM_CLASS);
  addLeaf(classInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/physical-index
  // Description: The entPhysicalIndex for the entPhysicalEntry represented
  //              by this list entry.
  // Type:        int32
  // Units:
  // -----------------------------------------------------------------------------
  LeafPhysicalIndex physicalIndexInst(ITEM_PHYSICAL_INDEX);
  addLeaf(physicalIndexInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/description
  // Description: A textual description of the component.  This node should
  //              contain a string that identifies the manufacturer's name
  //              for the component and should be set to a distinct value
  //              for each version or model of the component.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafDescription descriptionInst(ITEM_DESCRIPTION);
  addLeaf(descriptionInst);

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
  // Type:        int32
  // Units:
  // -----------------------------------------------------------------------------
  LeafParentRelPos parentRelPosInst(ITEM_PARENT_REL_POS);
  addLeaf(parentRelPosInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/hardware-rev
  // Description: The vendor-specific hardware revision string for the
  //              component.  The preferred value is the hardware revision
  //              identifier actually printed on the component itself (if
  //              present).
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafHardwareRev hardwareRevInst(ITEM_HARDWARE_REV);
  addLeaf(hardwareRevInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/firmware-rev
  // Description: The vendor-specific firmware revision string for the
  //              component.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafFirmwareRev firmwareRevInst(ITEM_FIRMWARE_REV);
  addLeaf(firmwareRevInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/software-rev
  // Description: The vendor-specific software revision string for the
  //              component.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafSoftwareRev softwareRevInst(ITEM_SOFTWARE_REV);
  addLeaf(softwareRevInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/serial-num
  // Description: The vendor-specific serial number string for the
  //              component.  The preferred value is the serial number
  //              string actually printed on the component itself (if
  //              present).
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafSerialNum serialNumInst(ITEM_SERIAL_NUM);
  addLeaf(serialNumInst);

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
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafMfgName mfgNameInst(ITEM_MFG_NAME);
  addLeaf(mfgNameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/model-name
  // Description: The vendor-specific model name identifier string
  //              associated with this physical component.  The preferred
  //              value is the customer-visible part number, which may be
  //              printed on the component itself.
  //              If the model name string associated with the physical
  //              component is unknown to the server, then this node is not
  //              instantiated.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafModelName modelNameInst(ITEM_MODEL_NAME);
  addLeaf(modelNameInst);

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
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafAlias aliasInst(ITEM_ALIAS);
  addLeaf(aliasInst);

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
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafAssetId assetIdInst(ITEM_ASSET_ID);
  addLeaf(assetIdInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/is-fru
  // Description: This node indicates whether or not this component is
  //              considered a 'field-replaceable unit' by the vendor.  If
  //              this node contains the value 'true', then this component
  //              identifies a field-replaceable unit.  For all components
  //              that are permanently contained within a field-replaceable
  //              unit, the value 'false' should be returned for this
  //              node.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafIsFru isFruInst(ITEM_IS_FRU);
  addLeaf(isFruInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/mfg-date
  // Description: The date of manufacturing of the managed component.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafMfgDate mfgDateInst(ITEM_MFG_DATE);
  addLeaf(mfgDateInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/uuid
  // Description: A Universally Unique Identifier of the component.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafUuid uuidInst(ITEM_UUID);
  addLeaf(uuidInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/product-code
  // Description: O-RAN term that is distinct from model-name in ietf-hardware.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafProductCode productCodeInst(ITEM_PRODUCT_CODE);
  addLeaf(productCodeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/energy-saving-enabled
  // Description: This parameter can enable O-RAN unit to be switched to energy
  //              saving mode.
  //              TRUE indicates to switch the energy saving mode.
  //              FALSE indicates to cancel the energy saving mode.
  //              At the energy saving mode, all power of whole O-RAN unit
  //              becomes lowest level whereas M-plane is still available
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafEnergySavingEnabled energySavingEnabledInst(ITEM_ENERGY_SAVING_ENABLED);
  addLeaf(energySavingEnabledInst);

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
  // Ref:         ../../component/name
  // Units:
  // -----------------------------------------------------------------------------
  RefParent parentInst(ITEM_PARENT);
  addReference(parentInst);

  // -----------------------------------------------------------------------------
  // Reference:   /hardware/component/o-ran-name
  // Description: O-RAN name needed to bind and match with the name of hw
  // element,
  //              to be compliant with O-RAN naming convention.
  // Ref: /ietf-hardware:hardware/ietf-hardware:component/ietf-hardware:name
  // Units:
  // -----------------------------------------------------------------------------
  RefORanName oRanNameInst(ITEM_O_RAN_NAME);
  addReference(oRanNameInst);

  // -----------------------------------------------------------------------------
  // List:        /hardware/component/contains-child
  // Description: The name of the contained component.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstContainsChild containsChildInst(ITEM_CONTAINS_CHILD);
  containsChildInst.initialise();
  addList(containsChildInst);

  // -----------------------------------------------------------------------------
  // List:        /hardware/component/uri
  // Description: This node contains identification information about the
  //              component.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstUri uriInst(ITEM_URI);
  uriInst.initialise();
  addList(uriInst);

  // -----------------------------------------------------------------------------
  // Container:   /hardware/component/state
  // Description: State-related nodes
  // -----------------------------------------------------------------------------
  CntState stateInst(ITEM_STATE);
  stateInst.initialise();
  addContainer(stateInst);

  // -----------------------------------------------------------------------------
  // Container:   /hardware/component/sensor-data
  // Description: Sensor-related nodes.
  // -----------------------------------------------------------------------------
  CntSensorData sensorDataInst(ITEM_SENSOR_DATA);
  sensorDataInst.initialise();
  addContainer(sensorDataInst);

  // -----------------------------------------------------------------------------
  // Container:   /hardware/component/label-content
  // Description: Which set of attributes are printed on the Radio Unit's label
  // -----------------------------------------------------------------------------
  CntLabelContent labelContentInst(ITEM_LABEL_CONTENT);
  labelContentInst.initialise();
  addContainer(labelContentInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/name
// Description: The name assigned to this component.
//              This name is not required to be the same as
//              entPhysicalName.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

CntHardware::LstComponent::LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/class
// Description: An indication of the general hardware type of the
//              component.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafClass::LeafClass(uint32_t id)
    : YangLeaf("class", id) {}

CntHardware::LstComponent::LeafClass::~LeafClass() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/physical-index
// Description: The entPhysicalIndex for the entPhysicalEntry represented
//              by this list entry.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafPhysicalIndex::LeafPhysicalIndex(uint32_t id)
    : YangLeaf("physical-index", id) {}

CntHardware::LstComponent::LeafPhysicalIndex::~LeafPhysicalIndex() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/description
// Description: A textual description of the component.  This node should
//              contain a string that identifies the manufacturer's name
//              for the component and should be set to a distinct value
//              for each version or model of the component.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafDescription::LeafDescription(uint32_t id)
    : YangLeaf("description", id) {}

CntHardware::LstComponent::LeafDescription::~LeafDescription() {}

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
CntHardware::LstComponent::LeafParentRelPos::LeafParentRelPos(uint32_t id)
    : YangLeaf("parent-rel-pos", id) {}

CntHardware::LstComponent::LeafParentRelPos::~LeafParentRelPos() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/hardware-rev
// Description: The vendor-specific hardware revision string for the
//              component.  The preferred value is the hardware revision
//              identifier actually printed on the component itself (if
//              present).
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafHardwareRev::LeafHardwareRev(uint32_t id)
    : YangLeaf("hardware-rev", id) {}

CntHardware::LstComponent::LeafHardwareRev::~LeafHardwareRev() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/firmware-rev
// Description: The vendor-specific firmware revision string for the
//              component.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafFirmwareRev::LeafFirmwareRev(uint32_t id)
    : YangLeaf("firmware-rev", id) {}

CntHardware::LstComponent::LeafFirmwareRev::~LeafFirmwareRev() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/software-rev
// Description: The vendor-specific software revision string for the
//              component.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafSoftwareRev::LeafSoftwareRev(uint32_t id)
    : YangLeaf("software-rev", id) {}

CntHardware::LstComponent::LeafSoftwareRev::~LeafSoftwareRev() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/serial-num
// Description: The vendor-specific serial number string for the
//              component.  The preferred value is the serial number
//              string actually printed on the component itself (if
//              present).
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafSerialNum::LeafSerialNum(uint32_t id)
    : YangLeaf("serial-num", id) {}

CntHardware::LstComponent::LeafSerialNum::~LeafSerialNum() {}

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
CntHardware::LstComponent::LeafMfgName::LeafMfgName(uint32_t id)
    : YangLeaf("mfg-name", id) {}

CntHardware::LstComponent::LeafMfgName::~LeafMfgName() {}

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
CntHardware::LstComponent::LeafModelName::LeafModelName(uint32_t id)
    : YangLeaf("model-name", id) {}

CntHardware::LstComponent::LeafModelName::~LeafModelName() {}

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
CntHardware::LstComponent::LeafAlias::LeafAlias(uint32_t id)
    : YangLeaf("alias", id) {}

CntHardware::LstComponent::LeafAlias::~LeafAlias() {}

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
CntHardware::LstComponent::LeafAssetId::LeafAssetId(uint32_t id)
    : YangLeaf("asset-id", id) {}

CntHardware::LstComponent::LeafAssetId::~LeafAssetId() {}

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
CntHardware::LstComponent::LeafIsFru::LeafIsFru(uint32_t id)
    : YangLeaf("is-fru", id) {}

CntHardware::LstComponent::LeafIsFru::~LeafIsFru() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/mfg-date
// Description: The date of manufacturing of the managed component.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafMfgDate::LeafMfgDate(uint32_t id)
    : YangLeaf("mfg-date", id) {}

CntHardware::LstComponent::LeafMfgDate::~LeafMfgDate() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/uuid
// Description: A Universally Unique Identifier of the component.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafUuid::LeafUuid(uint32_t id)
    : YangLeaf("uuid", id) {}

CntHardware::LstComponent::LeafUuid::~LeafUuid() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/product-code
// Description: O-RAN term that is distinct from model-name in ietf-hardware.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafProductCode::LeafProductCode(uint32_t id)
    : YangLeaf("product-code", id) {}

CntHardware::LstComponent::LeafProductCode::~LeafProductCode() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/energy-saving-enabled
// Description: This parameter can enable O-RAN unit to be switched to energy
//              saving mode.
//              TRUE indicates to switch the energy saving mode.
//              FALSE indicates to cancel the energy saving mode.
//              At the energy saving mode, all power of whole O-RAN unit becomes
//              lowest level whereas M-plane is still available
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LeafEnergySavingEnabled::LeafEnergySavingEnabled(
    uint32_t id)
    : YangLeaf("energy-saving-enabled", id) {}

CntHardware::LstComponent::LeafEnergySavingEnabled::~LeafEnergySavingEnabled() {
}

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
CntHardware::LstComponent::RefParent::RefParent(uint32_t id)
    : YangReference("parent", id, "../../component/name") {}

CntHardware::LstComponent::RefParent::~RefParent() {}

// -----------------------------------------------------------------------------
// Reference:   /hardware/component/o-ran-name
// Description: O-RAN name needed to bind and match with the name of hw element,
//              to be compliant with O-RAN naming convention.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::RefORanName::RefORanName(uint32_t id)
    : YangReference(
          "o-ran-name",
          id,
          "/ietf-hardware:hardware/ietf-hardware:component/"
          "ietf-hardware:name") {}

CntHardware::LstComponent::RefORanName::~RefORanName() {}

// -----------------------------------------------------------------------------
// List:        contains-child
// Description: The name of the contained component.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LstContainsChild::LstContainsChild(uint32_t id)
    : YangList("contains-child", id) {}

CntHardware::LstComponent::LstContainsChild::~LstContainsChild() {}

YangResult_E
CntHardware::LstComponent::LstContainsChild::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        uri
// Description: This node contains identification information about the
//              component.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::LstUri::LstUri(uint32_t id) : YangList("uri", id) {}

CntHardware::LstComponent::LstUri::~LstUri() {}

YangResult_E
CntHardware::LstComponent::LstUri::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   state
// Description: State-related nodes
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntState::CntState(uint32_t id)
    : YangContainer("state", id) {}

CntHardware::LstComponent::CntState::~CntState() {}

YangResult_E
CntHardware::LstComponent::CntState::initialise(void) {
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
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafStateLastChanged stateLastChangedInst(ITEM_STATE_LAST_CHANGED);
  addLeaf(stateLastChangedInst);

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
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafAdminState adminStateInst(ITEM_ADMIN_STATE);
  addLeaf(adminStateInst);

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
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafOperState operStateInst(ITEM_OPER_STATE);
  addLeaf(operStateInst);

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
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafUsageState usageStateInst(ITEM_USAGE_STATE);
  addLeaf(usageStateInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/state/alarm-state
  // Description: The alarm state for this component.  It does not
  //              include the alarms raised on child components within its
  //              containment hierarchy.
  // Type:        ???BITS
  // Units:
  // -----------------------------------------------------------------------------
  LeafAlarmState alarmStateInst(ITEM_ALARM_STATE);
  addLeaf(alarmStateInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/state/standby-state
  // Description: The standby state for this component.
  //              Some components will exhibit only a subset of the
  //              remaining standby state values.  If this component
  //              cannot operate in a standby role, the value of this node
  //              will always be 'providing-service'.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStandbyState standbyStateInst(ITEM_STANDBY_STATE);
  addLeaf(standbyStateInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/state/power-state
  // Description: The current power saving state for this component.
  //              Note - hw:/hardware/compnent/state/standby-state defined in
  //              RFC 4268 is used for redundancy purposes and not power saving
  //              operations.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafPowerState powerStateInst(ITEM_POWER_STATE);
  addLeaf(powerStateInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/state/availability-state
  // Description: Equipment's availability-state is derived by matching active
  // faults
  //              and their impact to module's operation and enables an
  //              equipment to indicate that even though it may have one or more
  //              critical alarms, it can continue to serve traffic.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafAvailabilityState availabilityStateInst(ITEM_AVAILABILITY_STATE);
  addLeaf(availabilityStateInst);

  return YangResult_E::OK;
}

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
CntHardware::LstComponent::CntState::LeafStateLastChanged::LeafStateLastChanged(
    uint32_t id)
    : YangLeaf("state-last-changed", id) {}

CntHardware::LstComponent::CntState::LeafStateLastChanged::
    ~LeafStateLastChanged() {}

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
CntHardware::LstComponent::CntState::LeafAdminState::LeafAdminState(uint32_t id)
    : YangLeaf("admin-state", id) {}

CntHardware::LstComponent::CntState::LeafAdminState::~LeafAdminState() {}

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
CntHardware::LstComponent::CntState::LeafOperState::LeafOperState(uint32_t id)
    : YangLeaf("oper-state", id) {}

CntHardware::LstComponent::CntState::LeafOperState::~LeafOperState() {}

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
CntHardware::LstComponent::CntState::LeafUsageState::LeafUsageState(uint32_t id)
    : YangLeaf("usage-state", id) {}

CntHardware::LstComponent::CntState::LeafUsageState::~LeafUsageState() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/state/alarm-state
// Description: The alarm state for this component.  It does not
//              include the alarms raised on child components within its
//              containment hierarchy.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntState::LeafAlarmState::LeafAlarmState(uint32_t id)
    : YangLeaf("alarm-state", id) {}

CntHardware::LstComponent::CntState::LeafAlarmState::~LeafAlarmState() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/state/standby-state
// Description: The standby state for this component.
//              Some components will exhibit only a subset of the
//              remaining standby state values.  If this component
//              cannot operate in a standby role, the value of this node
//              will always be 'providing-service'.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntState::LeafStandbyState::LeafStandbyState(
    uint32_t id)
    : YangLeaf("standby-state", id) {}

CntHardware::LstComponent::CntState::LeafStandbyState::~LeafStandbyState() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/state/power-state
// Description: The current power saving state for this component.
//              Note - hw:/hardware/compnent/state/standby-state defined in RFC
//              4268 is used for redundancy purposes and not power saving
//              operations.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntState::LeafPowerState::LeafPowerState(uint32_t id)
    : YangLeaf("power-state", id) {}

CntHardware::LstComponent::CntState::LeafPowerState::~LeafPowerState() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/state/availability-state
// Description: Equipment's availability-state is derived by matching active
// faults
//              and their impact to module's operation and enables an equipment
//              to indicate that even though it may have one or more critical
//              alarms, it can continue to serve traffic.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntState::LeafAvailabilityState::
    LeafAvailabilityState(uint32_t id)
    : YangLeaf("availability-state", id) {}

CntHardware::LstComponent::CntState::LeafAvailabilityState::
    ~LeafAvailabilityState() {}

// -----------------------------------------------------------------------------
// Container:   sensor-data
// Description: Sensor-related nodes.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntSensorData::CntSensorData(uint32_t id)
    : YangContainer("sensor-data", id) {}

CntHardware::LstComponent::CntSensorData::~CntSensorData() {}

YangResult_E
CntHardware::LstComponent::CntSensorData::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/sensor-data/value
  // Description: The most recent measurement obtained by the server
  //              for this sensor.
  //              A client that periodically fetches this node should also
  //              fetch the nodes 'value-type', 'value-scale', and
  //              'value-precision', since they may change when the value
  //              is changed.
  // Type:        int32
  // Units:
  // -----------------------------------------------------------------------------
  LeafValue valueInst(ITEM_VALUE);
  addLeaf(valueInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/sensor-data/value-type
  // Description: The type of data units associated with the
  //              sensor value
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafValueType valueTypeInst(ITEM_VALUE_TYPE);
  addLeaf(valueTypeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/sensor-data/value-scale
  // Description: The (power of 10) scaling factor associated
  //              with the sensor value
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafValueScale valueScaleInst(ITEM_VALUE_SCALE);
  addLeaf(valueScaleInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/sensor-data/value-precision
  // Description: The number of decimal places of precision
  //              associated with the sensor value
  // Type:        int8
  // Units:
  // -----------------------------------------------------------------------------
  LeafValuePrecision valuePrecisionInst(ITEM_VALUE_PRECISION);
  addLeaf(valuePrecisionInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/sensor-data/oper-status
  // Description: The operational status of the sensor.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafOperStatus operStatusInst(ITEM_OPER_STATUS);
  addLeaf(operStatusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/sensor-data/units-display
  // Description: A textual description of the data units that should be
  //              used in the display of the sensor value.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafUnitsDisplay unitsDisplayInst(ITEM_UNITS_DISPLAY);
  addLeaf(unitsDisplayInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/sensor-data/value-timestamp
  // Description: The time the status and/or value of this sensor was last
  //              obtained by the server.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafValueTimestamp valueTimestampInst(ITEM_VALUE_TIMESTAMP);
  addLeaf(valueTimestampInst);

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
  // Type:        uint32
  // Units:       milliseconds
  // -----------------------------------------------------------------------------
  LeafValueUpdateRate valueUpdateRateInst(ITEM_VALUE_UPDATE_RATE);
  addLeaf(valueUpdateRateInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/sensor-data/value
// Description: The most recent measurement obtained by the server
//              for this sensor.
//              A client that periodically fetches this node should also
//              fetch the nodes 'value-type', 'value-scale', and
//              'value-precision', since they may change when the value
//              is changed.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntSensorData::LeafValue::LeafValue(uint32_t id)
    : YangLeaf("value", id) {}

CntHardware::LstComponent::CntSensorData::LeafValue::~LeafValue() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/sensor-data/value-type
// Description: The type of data units associated with the
//              sensor value
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntSensorData::LeafValueType::LeafValueType(
    uint32_t id)
    : YangLeaf("value-type", id) {}

CntHardware::LstComponent::CntSensorData::LeafValueType::~LeafValueType() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/sensor-data/value-scale
// Description: The (power of 10) scaling factor associated
//              with the sensor value
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntSensorData::LeafValueScale::LeafValueScale(
    uint32_t id)
    : YangLeaf("value-scale", id) {}

CntHardware::LstComponent::CntSensorData::LeafValueScale::~LeafValueScale() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/sensor-data/value-precision
// Description: The number of decimal places of precision
//              associated with the sensor value
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntSensorData::LeafValuePrecision::
    LeafValuePrecision(uint32_t id)
    : YangLeaf("value-precision", id) {}

CntHardware::LstComponent::CntSensorData::LeafValuePrecision::
    ~LeafValuePrecision() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/sensor-data/oper-status
// Description: The operational status of the sensor.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntSensorData::LeafOperStatus::LeafOperStatus(
    uint32_t id)
    : YangLeaf("oper-status", id) {}

CntHardware::LstComponent::CntSensorData::LeafOperStatus::~LeafOperStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/sensor-data/units-display
// Description: A textual description of the data units that should be
//              used in the display of the sensor value.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntSensorData::LeafUnitsDisplay::LeafUnitsDisplay(
    uint32_t id)
    : YangLeaf("units-display", id) {}

CntHardware::LstComponent::CntSensorData::LeafUnitsDisplay::
    ~LeafUnitsDisplay() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/sensor-data/value-timestamp
// Description: The time the status and/or value of this sensor was last
//              obtained by the server.
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntSensorData::LeafValueTimestamp::
    LeafValueTimestamp(uint32_t id)
    : YangLeaf("value-timestamp", id) {}

CntHardware::LstComponent::CntSensorData::LeafValueTimestamp::
    ~LeafValueTimestamp() {}

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
CntHardware::LstComponent::CntSensorData::LeafValueUpdateRate::
    LeafValueUpdateRate(uint32_t id)
    : YangLeaf("value-update-rate", id) {}

CntHardware::LstComponent::CntSensorData::LeafValueUpdateRate::
    ~LeafValueUpdateRate() {}

// -----------------------------------------------------------------------------
// Container:   label-content
// Description: Which set of attributes are printed on the Radio Unit's label
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntLabelContent::CntLabelContent(uint32_t id)
    : YangContainer("label-content", id) {}

CntHardware::LstComponent::CntLabelContent::~CntLabelContent() {}

YangResult_E
CntHardware::LstComponent::CntLabelContent::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/label-content/model-name
  // Description: indicates whether model-name is included on the equipment's
  // label Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafModelName modelNameInst(ITEM_MODEL_NAME);
  addLeaf(modelNameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /hardware/component/label-content/serial-number
  // Description: indicates whether serial number is included on the equipment's
  // label Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafSerialNumber serialNumberInst(ITEM_SERIAL_NUMBER);
  addLeaf(serialNumberInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/label-content/model-name
// Description: indicates whether model-name is included on the equipment's
// label
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntLabelContent::LeafModelName::LeafModelName(
    uint32_t id)
    : YangLeaf("model-name", id) {}

CntHardware::LstComponent::CntLabelContent::LeafModelName::~LeafModelName() {}

// -----------------------------------------------------------------------------
// Leaf:        /hardware/component/label-content/serial-number
// Description: indicates whether serial number is included on the equipment's
// label
// -----------------------------------------------------------------------------
CntHardware::LstComponent::CntLabelContent::LeafSerialNumber::LeafSerialNumber(
    uint32_t id)
    : YangLeaf("serial-number", id) {}

CntHardware::LstComponent::CntLabelContent::LeafSerialNumber::
    ~LeafSerialNumber() {}

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
// Notification:hardware-state-change
// Description: A hardware-state-change notification is generated when the
//              value of /hardware/last-change changes in the operational
//              state.
// -----------------------------------------------------------------------------
NotifHardwareStateChange::NotifHardwareStateChange(uint32_t id)
    : YangNotif("hardware-state-change", id) {}

NotifHardwareStateChange::~NotifHardwareStateChange() {}

YangResult_E
NotifHardwareStateChange::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Notification:hardware-state-oper-enabled
// Description: A hardware-state-oper-enabled notification signifies that a
//              component has transitioned into the 'enabled' state.
// -----------------------------------------------------------------------------
NotifHardwareStateOperEnabled::NotifHardwareStateOperEnabled(uint32_t id)
    : YangNotif("hardware-state-oper-enabled", id) {}

NotifHardwareStateOperEnabled::~NotifHardwareStateOperEnabled() {}

YangResult_E
NotifHardwareStateOperEnabled::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:   /hardware-state-oper-enabled/name
  // Description: The name of the component that has transitioned into the
  //              'enabled' state.
  // Ref:         /hardware/component/name
  // Units:
  // -----------------------------------------------------------------------------
  RefName nameInst(ITEM_NAME);
  addReference(nameInst);

  // -----------------------------------------------------------------------------
  // Reference:   /hardware-state-oper-enabled/admin-state
  // Description: The administrative state for the component.
  // Ref:         /hardware/component/state/admin-state
  // Units:
  // -----------------------------------------------------------------------------
  RefAdminState adminStateInst(ITEM_ADMIN_STATE);
  addReference(adminStateInst);

  // -----------------------------------------------------------------------------
  // Reference:   /hardware-state-oper-enabled/alarm-state
  // Description: The alarm state for the component.
  // Ref:         /hardware/component/state/alarm-state
  // Units:
  // -----------------------------------------------------------------------------
  RefAlarmState alarmStateInst(ITEM_ALARM_STATE);
  addReference(alarmStateInst);

  // -----------------------------------------------------------------------------
  // Reference:   /hardware-state-oper-enabled/availability-state
  // Description: The availability-state of the O-RU.
  // Ref:
  // /ietf-hardware:hardware/ietf-hardware:component/ietf-hardware:state/o-ran-hardware:availability-state
  // Units:
  // -----------------------------------------------------------------------------
  RefAvailabilityState availabilityStateInst(ITEM_AVAILABILITY_STATE);
  addReference(availabilityStateInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /hardware-state-oper-enabled/name
// Description: The name of the component that has transitioned into the
//              'enabled' state.
// -----------------------------------------------------------------------------
NotifHardwareStateOperEnabled::RefName::RefName(uint32_t id)
    : YangReference("name", id, "/hardware/component/name") {}

NotifHardwareStateOperEnabled::RefName::~RefName() {}

// -----------------------------------------------------------------------------
// Reference:   /hardware-state-oper-enabled/admin-state
// Description: The administrative state for the component.
// -----------------------------------------------------------------------------
NotifHardwareStateOperEnabled::RefAdminState::RefAdminState(uint32_t id)
    : YangReference(
          "admin-state", id, "/hardware/component/state/admin-state") {}

NotifHardwareStateOperEnabled::RefAdminState::~RefAdminState() {}

// -----------------------------------------------------------------------------
// Reference:   /hardware-state-oper-enabled/alarm-state
// Description: The alarm state for the component.
// -----------------------------------------------------------------------------
NotifHardwareStateOperEnabled::RefAlarmState::RefAlarmState(uint32_t id)
    : YangReference(
          "alarm-state", id, "/hardware/component/state/alarm-state") {}

NotifHardwareStateOperEnabled::RefAlarmState::~RefAlarmState() {}

// -----------------------------------------------------------------------------
// Reference:   /hardware-state-oper-enabled/availability-state
// Description: The availability-state of the O-RU.
// -----------------------------------------------------------------------------
NotifHardwareStateOperEnabled::RefAvailabilityState::RefAvailabilityState(
    uint32_t id)
    : YangReference(
          "availability-state",
          id,
          "/ietf-hardware:hardware/ietf-hardware:component/ietf-hardware:state/"
          "o-ran-hardware:availability-state") {}

NotifHardwareStateOperEnabled::RefAvailabilityState::~RefAvailabilityState() {}

// -----------------------------------------------------------------------------
// Notification:hardware-state-oper-disabled
// Description: A hardware-state-oper-disabled notification signifies that a
//              component has transitioned into the 'disabled' state.
// -----------------------------------------------------------------------------
NotifHardwareStateOperDisabled::NotifHardwareStateOperDisabled(uint32_t id)
    : YangNotif("hardware-state-oper-disabled", id) {}

NotifHardwareStateOperDisabled::~NotifHardwareStateOperDisabled() {}

YangResult_E
NotifHardwareStateOperDisabled::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:   /hardware-state-oper-disabled/name
  // Description: The name of the component that has transitioned into the
  //              'disabled' state.
  // Ref:         /hardware/component/name
  // Units:
  // -----------------------------------------------------------------------------
  RefName nameInst(ITEM_NAME);
  addReference(nameInst);

  // -----------------------------------------------------------------------------
  // Reference:   /hardware-state-oper-disabled/admin-state
  // Description: The administrative state for the component.
  // Ref:         /hardware/component/state/admin-state
  // Units:
  // -----------------------------------------------------------------------------
  RefAdminState adminStateInst(ITEM_ADMIN_STATE);
  addReference(adminStateInst);

  // -----------------------------------------------------------------------------
  // Reference:   /hardware-state-oper-disabled/alarm-state
  // Description: The alarm state for the component.
  // Ref:         /hardware/component/state/alarm-state
  // Units:
  // -----------------------------------------------------------------------------
  RefAlarmState alarmStateInst(ITEM_ALARM_STATE);
  addReference(alarmStateInst);

  // -----------------------------------------------------------------------------
  // Reference:   /hardware-state-oper-disabled/availability-state
  // Description: The availability-state of the O-RU.
  // Ref:
  // /ietf-hardware:hardware/ietf-hardware:component/ietf-hardware:state/o-ran-hardware:availability-state
  // Units:
  // -----------------------------------------------------------------------------
  RefAvailabilityState availabilityStateInst(ITEM_AVAILABILITY_STATE);
  addReference(availabilityStateInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /hardware-state-oper-disabled/name
// Description: The name of the component that has transitioned into the
//              'disabled' state.
// -----------------------------------------------------------------------------
NotifHardwareStateOperDisabled::RefName::RefName(uint32_t id)
    : YangReference("name", id, "/hardware/component/name") {}

NotifHardwareStateOperDisabled::RefName::~RefName() {}

// -----------------------------------------------------------------------------
// Reference:   /hardware-state-oper-disabled/admin-state
// Description: The administrative state for the component.
// -----------------------------------------------------------------------------
NotifHardwareStateOperDisabled::RefAdminState::RefAdminState(uint32_t id)
    : YangReference(
          "admin-state", id, "/hardware/component/state/admin-state") {}

NotifHardwareStateOperDisabled::RefAdminState::~RefAdminState() {}

// -----------------------------------------------------------------------------
// Reference:   /hardware-state-oper-disabled/alarm-state
// Description: The alarm state for the component.
// -----------------------------------------------------------------------------
NotifHardwareStateOperDisabled::RefAlarmState::RefAlarmState(uint32_t id)
    : YangReference(
          "alarm-state", id, "/hardware/component/state/alarm-state") {}

NotifHardwareStateOperDisabled::RefAlarmState::~RefAlarmState() {}

// -----------------------------------------------------------------------------
// Reference:   /hardware-state-oper-disabled/availability-state
// Description: The availability-state of the O-RU.
// -----------------------------------------------------------------------------
NotifHardwareStateOperDisabled::RefAvailabilityState::RefAvailabilityState(
    uint32_t id)
    : YangReference(
          "availability-state",
          id,
          "/ietf-hardware:hardware/ietf-hardware:component/ietf-hardware:state/"
          "o-ran-hardware:availability-state") {}

NotifHardwareStateOperDisabled::RefAvailabilityState::~RefAvailabilityState() {}

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
ModuleIetfHardware::ModuleIetfHardware(uint32_t id)
    : YangModule(
          "ietf-hardware",
          "ietf-hardware.yang",
          "hw",
          "urn:ietf:params:xml:ns:yang:ietf-hardware",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Feature
  // Description: This feature indicates that the device implements
  //              the ENTITY-MIB.
  // -----------------------------------------------------------------------------
  FeatureEntityMib entityMibInst(ITEM_ENTITY_MIB);
  addFeature(entityMibInst);

  // -----------------------------------------------------------------------------
  // Feature
  // Description: Indicates that ENTITY-STATE-MIB objects are supported
  // -----------------------------------------------------------------------------
  FeatureHardwareState hardwareStateInst(ITEM_HARDWARE_STATE);
  addFeature(hardwareStateInst);

  // -----------------------------------------------------------------------------
  // Feature
  // Description: Indicates that ENTITY-SENSOR-MIB objects are supported
  // -----------------------------------------------------------------------------
  FeatureHardwareSensor hardwareSensorInst(ITEM_HARDWARE_SENSOR);
  addFeature(hardwareSensorInst);

  // -----------------------------------------------------------------------------
  // Container:   /hardware
  // Description: Data nodes representing components.
  //              If the server supports configuration of hardware components,
  //              then this data model is instantiated in the configuration
  //              datastores supported by the server.  The leaf-list 'datastore'
  //              for the module 'ietf-hardware' in the YANG library provides
  //              this information.
  // -----------------------------------------------------------------------------
  CntHardware hardwareInst(ITEM_HARDWARE);
  hardwareInst.initialise();
  addContainer(hardwareInst);

  // -----------------------------------------------------------------------------
  // Notification:/hardware-state-change
  // Description: A hardware-state-change notification is generated when the
  //              value of /hardware/last-change changes in the operational
  //              state.
  // -----------------------------------------------------------------------------
  NotifHardwareStateChange hardwareStateChangeInst(ITEM_HARDWARE_STATE_CHANGE);
  hardwareStateChangeInst.initialise();
  addNotification(hardwareStateChangeInst);

  // -----------------------------------------------------------------------------
  // Notification:/hardware-state-oper-enabled
  // Description: A hardware-state-oper-enabled notification signifies that a
  //              component has transitioned into the 'enabled' state.
  // -----------------------------------------------------------------------------
  NotifHardwareStateOperEnabled hardwareStateOperEnabledInst(
      ITEM_HARDWARE_STATE_OPER_ENABLED);
  hardwareStateOperEnabledInst.initialise();
  addNotification(hardwareStateOperEnabledInst);

  // -----------------------------------------------------------------------------
  // Notification:/hardware-state-oper-disabled
  // Description: A hardware-state-oper-disabled notification signifies that a
  //              component has transitioned into the 'disabled' state.
  // -----------------------------------------------------------------------------
  NotifHardwareStateOperDisabled hardwareStateOperDisabledInst(
      ITEM_HARDWARE_STATE_OPER_DISABLED);
  hardwareStateOperDisabledInst.initialise();
  addNotification(hardwareStateOperDisabledInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleIetfHardware::~ModuleIetfHardware() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleIetfHardware::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleIetfHardware>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleIetfHardware::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
