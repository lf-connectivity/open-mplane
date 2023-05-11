/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanSoftwareManagement.cpp
 * \brief     Module ORanSoftwareManagement interface
 *
 *
 * \details   This file defines the YANG module o-ran-software-management
 interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-software-management"
 *            YANG Filename:    "o-ran-software-management.yang"
 *            Module Prefix:    "o-ran-swm"
 *            Module namespace: "urn:o-ran:software-management:1.0"
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
#include "YangModuleORanSoftwareManagement.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanSoftwareManagement_NS;

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
// Container:   software-inventory
// Description: Contains information about each software slot and its content.
// -----------------------------------------------------------------------------
CntSoftwareInventory::CntSoftwareInventory(uint32_t id)
    : YangContainer("software-inventory", id) {}

CntSoftwareInventory::~CntSoftwareInventory() {}

YangResult_E
CntSoftwareInventory::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /software-inventory/slot-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpSlotGroup slotGroupInst(ITEM_SLOT_GROUP);
  slotGroupInst.initialise();
  addGroup(slotGroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    slot-group
// Description: Contains information about each software slot and its content.
// -----------------------------------------------------------------------------
GrpSlotGroup::GrpSlotGroup(uint32_t id) : YangGroup("slot-group", id) {}

GrpSlotGroup::~GrpSlotGroup() {}

YangResult_E
GrpSlotGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /slot-group/software-slot
  // Description: Information about available software-slots and their software.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstSoftwareSlot softwareSlotInst(ITEM_SOFTWARE_SLOT);
  softwareSlotInst.initialise();
  addList(softwareSlotInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        software-slot
// Description: Information about available software-slots and their software.
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LstSoftwareSlot(uint32_t id)
    : YangList("software-slot", id) {}

GrpSlotGroup::LstSoftwareSlot::~LstSoftwareSlot() {}

YangResult_E
GrpSlotGroup::LstSoftwareSlot::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/name
  // Description: Name of the software package. This shall be unique to identify
  // the software-slot. Type:        string Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/status
  // Description: Indicates the status of the software slot
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/active
  // Description: informs if software stored in particular slot is activated at
  // the moment Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafActive activeInst(ITEM_ACTIVE);
  addLeaf(activeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/running
  // Description: informs if software stored in particular slot is used at the
  // moment Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafRunning runningInst(ITEM_RUNNING);
  addLeaf(runningInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/access
  // Description: Indicates the writability of the slot.
  //              A Read-Only software slot is one which has a factory installed
  //              software-slot
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafAccess accessInst(ITEM_ACCESS);
  addLeaf(accessInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/vendor-code
  // Description: Unique code of the vendor. This is derived from manifest file.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafVendorCode vendorCodeInst(ITEM_VENDOR_CODE);
  addLeaf(vendorCodeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/build-id
  // Description: Identity associated with the software build. This is derived
  // from manifest file. Type:        string Units:
  // -----------------------------------------------------------------------------
  LeafBuildId buildIdInst(ITEM_BUILD_ID);
  addLeaf(buildIdInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/build-name
  // Description: Name of the build. This is derived from manifest file.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafBuildName buildNameInst(ITEM_BUILD_NAME);
  addLeaf(buildNameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/build-version
  // Description: The vendor-specific version string of the software build.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafBuildVersion buildVersionInst(ITEM_BUILD_VERSION);
  addLeaf(buildVersionInst);

  // -----------------------------------------------------------------------------
  // Reference:   /slot-group/software-slot/product-code
  // Description: product code provided by the vendor, specific to the product.
  // This is derived from manifest file. Ref:
  // /ietf-hardware:hardware/ietf-hardware:component/o-ran-hardware:product-code
  // Units:
  // -----------------------------------------------------------------------------
  RefProductCode productCodeInst(ITEM_PRODUCT_CODE);
  addReference(productCodeInst);

  // -----------------------------------------------------------------------------
  // List:        /slot-group/software-slot/files
  // Description: List of all the files present in the software package.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstFiles filesInst(ITEM_FILES);
  filesInst.initialise();
  addList(filesInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/name
// Description: Name of the software package. This shall be unique to identify
// the software-slot.
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

GrpSlotGroup::LstSoftwareSlot::LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/status
// Description: Indicates the status of the software slot
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

GrpSlotGroup::LstSoftwareSlot::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/active
// Description: informs if software stored in particular slot is activated at
// the moment
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LeafActive::LeafActive(uint32_t id)
    : YangLeaf("active", id) {}

GrpSlotGroup::LstSoftwareSlot::LeafActive::~LeafActive() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/running
// Description: informs if software stored in particular slot is used at the
// moment
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LeafRunning::LeafRunning(uint32_t id)
    : YangLeaf("running", id) {}

GrpSlotGroup::LstSoftwareSlot::LeafRunning::~LeafRunning() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/access
// Description: Indicates the writability of the slot.
//              A Read-Only software slot is one which has a factory installed
//              software-slot
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LeafAccess::LeafAccess(uint32_t id)
    : YangLeaf("access", id) {}

GrpSlotGroup::LstSoftwareSlot::LeafAccess::~LeafAccess() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/vendor-code
// Description: Unique code of the vendor. This is derived from manifest file.
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LeafVendorCode::LeafVendorCode(uint32_t id)
    : YangLeaf("vendor-code", id) {}

GrpSlotGroup::LstSoftwareSlot::LeafVendorCode::~LeafVendorCode() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/build-id
// Description: Identity associated with the software build. This is derived
// from manifest file.
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LeafBuildId::LeafBuildId(uint32_t id)
    : YangLeaf("build-id", id) {}

GrpSlotGroup::LstSoftwareSlot::LeafBuildId::~LeafBuildId() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/build-name
// Description: Name of the build. This is derived from manifest file.
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LeafBuildName::LeafBuildName(uint32_t id)
    : YangLeaf("build-name", id) {}

GrpSlotGroup::LstSoftwareSlot::LeafBuildName::~LeafBuildName() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/build-version
// Description: The vendor-specific version string of the software build.
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LeafBuildVersion::LeafBuildVersion(uint32_t id)
    : YangLeaf("build-version", id) {}

GrpSlotGroup::LstSoftwareSlot::LeafBuildVersion::~LeafBuildVersion() {}

// -----------------------------------------------------------------------------
// Reference:   /slot-group/software-slot/product-code
// Description: product code provided by the vendor, specific to the product.
// This is derived from manifest file.
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::RefProductCode::RefProductCode(uint32_t id)
    : YangReference(
          "product-code",
          id,
          "/ietf-hardware:hardware/ietf-hardware:component/"
          "o-ran-hardware:product-code") {}

GrpSlotGroup::LstSoftwareSlot::RefProductCode::~RefProductCode() {}

// -----------------------------------------------------------------------------
// List:        files
// Description: List of all the files present in the software package.
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LstFiles::LstFiles(uint32_t id)
    : YangList("files", id) {}

GrpSlotGroup::LstSoftwareSlot::LstFiles::~LstFiles() {}

YangResult_E
GrpSlotGroup::LstSoftwareSlot::LstFiles::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/files/name
  // Description: Name of the file installed in the slot.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/files/version
  // Description: Version of the file installed in the slot
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafVersion versionInst(ITEM_VERSION);
  addLeaf(versionInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/files/local-path
  // Description: Complete path of the file stored locally
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafLocalPath localPathInst(ITEM_LOCAL_PATH);
  addLeaf(localPathInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /slot-group/software-slot/files/integrity
  // Description: Result of the file integrity check (checksum calculation)
  // during installation. Type:        enum Units:
  // -----------------------------------------------------------------------------
  LeafIntegrity integrityInst(ITEM_INTEGRITY);
  addLeaf(integrityInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/files/name
// Description: Name of the file installed in the slot.
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LstFiles::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

GrpSlotGroup::LstSoftwareSlot::LstFiles::LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/files/version
// Description: Version of the file installed in the slot
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LstFiles::LeafVersion::LeafVersion(uint32_t id)
    : YangLeaf("version", id) {}

GrpSlotGroup::LstSoftwareSlot::LstFiles::LeafVersion::~LeafVersion() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/files/local-path
// Description: Complete path of the file stored locally
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LstFiles::LeafLocalPath::LeafLocalPath(
    uint32_t id)
    : YangLeaf("local-path", id) {}

GrpSlotGroup::LstSoftwareSlot::LstFiles::LeafLocalPath::~LeafLocalPath() {}

// -----------------------------------------------------------------------------
// Leaf:        /slot-group/software-slot/files/integrity
// Description: Result of the file integrity check (checksum calculation) during
// installation.
// -----------------------------------------------------------------------------
GrpSlotGroup::LstSoftwareSlot::LstFiles::LeafIntegrity::LeafIntegrity(
    uint32_t id)
    : YangLeaf("integrity", id) {}

GrpSlotGroup::LstSoftwareSlot::LstFiles::LeafIntegrity::~LeafIntegrity() {}

// -----------------------------------------------------------------------------
// Grouping:    download-input
// Description: Grouping for sw download rpc input
// -----------------------------------------------------------------------------
GrpDownloadInput::GrpDownloadInput(uint32_t id)
    : YangGroup("download-input", id) {}

GrpDownloadInput::~GrpDownloadInput() {}

YangResult_E
GrpDownloadInput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /download-input/remote-file-path
  // Description: URI of the software image including username.
  //              The following format is possible:
  //              sftp://<username>@<host>[:<port>]/path
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafRemoteFilePath remoteFilePathInst(ITEM_REMOTE_FILE_PATH);
  addLeaf(remoteFilePathInst);

  // -----------------------------------------------------------------------------
  // Uses:        /download-input/o-ran-fm:credential-information
  // Module: o-ran-file-management
  // Description:
  // -----------------------------------------------------------------------------
  ModuleORanFileManagement_NS::GrpCredentialInformation
      oRanFmCredentialInformationInst(ITEM_O_RAN_FM_CREDENTIAL_INFORMATION);
  oRanFmCredentialInformationInst.initialise();
  addGroup(oRanFmCredentialInformationInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /download-input/remote-file-path
// Description: URI of the software image including username.
//              The following format is possible:
//              sftp://<username>@<host>[:<port>]/path
// -----------------------------------------------------------------------------
GrpDownloadInput::LeafRemoteFilePath::LeafRemoteFilePath(uint32_t id)
    : YangLeaf("remote-file-path", id) {}

GrpDownloadInput::LeafRemoteFilePath::~LeafRemoteFilePath() {}

// -----------------------------------------------------------------------------
// Grouping:    download-output
// Description: Grouping for sw download rpc output
// -----------------------------------------------------------------------------
GrpDownloadOutput::GrpDownloadOutput(uint32_t id)
    : YangGroup("download-output", id) {}

GrpDownloadOutput::~GrpDownloadOutput() {}

YangResult_E
GrpDownloadOutput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /download-output/status
  // Description: Status of the software files download
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /download-output/error-message
  // Description: Detailed error Message when the status is failed.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafErrorMessage errorMessageInst(ITEM_ERROR_MESSAGE);
  addLeaf(errorMessageInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /download-output/notification-timeout
  // Description: Notification timeout is the time NETCONF client shall
  //              wait for a 'download-event' notification from O-RU. If there
  //              is no 'download-event' notification received within
  //              notification-timeout, NETCONF client shall assume the download
  //              timeout/failure, and follow necessary steps.
  // Type:        int32
  // Units:       seconds
  // -----------------------------------------------------------------------------
  LeafNotificationTimeout notificationTimeoutInst(ITEM_NOTIFICATION_TIMEOUT);
  addLeaf(notificationTimeoutInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /download-output/status
// Description: Status of the software files download
// -----------------------------------------------------------------------------
GrpDownloadOutput::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

GrpDownloadOutput::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /download-output/error-message
// Description: Detailed error Message when the status is failed.
// -----------------------------------------------------------------------------
GrpDownloadOutput::LeafErrorMessage::LeafErrorMessage(uint32_t id)
    : YangLeaf("error-message", id) {}

GrpDownloadOutput::LeafErrorMessage::~LeafErrorMessage() {}

// -----------------------------------------------------------------------------
// Leaf:        /download-output/notification-timeout
// Description: Notification timeout is the time NETCONF client shall
//              wait for a 'download-event' notification from O-RU. If there is
//              no 'download-event' notification received within
//              notification-timeout, NETCONF client shall assume the download
//              timeout/failure, and follow necessary steps.
// -----------------------------------------------------------------------------
GrpDownloadOutput::LeafNotificationTimeout::LeafNotificationTimeout(uint32_t id)
    : YangLeaf("notification-timeout", id) {}

GrpDownloadOutput::LeafNotificationTimeout::~LeafNotificationTimeout() {}

// -----------------------------------------------------------------------------
// Grouping:    install-input
// Description: Grouping for sw installation rpc input
// -----------------------------------------------------------------------------
GrpInstallInput::GrpInstallInput(uint32_t id)
    : YangGroup("install-input", id) {}

GrpInstallInput::~GrpInstallInput() {}

YangResult_E
GrpInstallInput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:   /install-input/slot-name
  // Description: software-slot to which the software shall be installed to.
  // Ref:         /software-inventory/software-slot/name
  // Units:
  // -----------------------------------------------------------------------------
  RefSlotName slotNameInst(ITEM_SLOT_NAME);
  addReference(slotNameInst);

  // -----------------------------------------------------------------------------
  // List:        /install-input/file-names
  // Description: Names of the files within software package to be installed
  // Array Key:
  // -----------------------------------------------------------------------------
  LstFileNames fileNamesInst(ITEM_FILE_NAMES);
  fileNamesInst.initialise();
  addList(fileNamesInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /install-input/slot-name
// Description: software-slot to which the software shall be installed to.
// -----------------------------------------------------------------------------
GrpInstallInput::RefSlotName::RefSlotName(uint32_t id)
    : YangReference("slot-name", id, "/software-inventory/software-slot/name") {
}

GrpInstallInput::RefSlotName::~RefSlotName() {}

// -----------------------------------------------------------------------------
// List:        file-names
// Description: Names of the files within software package to be installed
// -----------------------------------------------------------------------------
GrpInstallInput::LstFileNames::LstFileNames(uint32_t id)
    : YangList("file-names", id) {}

GrpInstallInput::LstFileNames::~LstFileNames() {}

YangResult_E
GrpInstallInput::LstFileNames::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Grouping:    install-output
// Description: Grouping for sw installation rpc output
// -----------------------------------------------------------------------------
GrpInstallOutput::GrpInstallOutput(uint32_t id)
    : YangGroup("install-output", id) {}

GrpInstallOutput::~GrpInstallOutput() {}

YangResult_E
GrpInstallOutput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /install-output/status
  // Description: Status of the software package install.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /install-output/error-message
  // Description: Detailed error Message when the status is failed.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafErrorMessage errorMessageInst(ITEM_ERROR_MESSAGE);
  addLeaf(errorMessageInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /install-output/status
// Description: Status of the software package install.
// -----------------------------------------------------------------------------
GrpInstallOutput::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

GrpInstallOutput::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /install-output/error-message
// Description: Detailed error Message when the status is failed.
// -----------------------------------------------------------------------------
GrpInstallOutput::LeafErrorMessage::LeafErrorMessage(uint32_t id)
    : YangLeaf("error-message", id) {}

GrpInstallOutput::LeafErrorMessage::~LeafErrorMessage() {}

// -----------------------------------------------------------------------------
// Grouping:    activate-input
// Description: Grouping for sw activation rpc input
// -----------------------------------------------------------------------------
GrpActivateInput::GrpActivateInput(uint32_t id)
    : YangGroup("activate-input", id) {}

GrpActivateInput::~GrpActivateInput() {}

YangResult_E
GrpActivateInput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:   /activate-input/slot-name
  // Description: Slot name on which software has to be activated.
  // Ref:         /software-inventory/software-slot/name
  // Units:
  // -----------------------------------------------------------------------------
  RefSlotName slotNameInst(ITEM_SLOT_NAME);
  addReference(slotNameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /activate-input/slot-name
// Description: Slot name on which software has to be activated.
// -----------------------------------------------------------------------------
GrpActivateInput::RefSlotName::RefSlotName(uint32_t id)
    : YangReference("slot-name", id, "/software-inventory/software-slot/name") {
}

GrpActivateInput::RefSlotName::~RefSlotName() {}

// -----------------------------------------------------------------------------
// Grouping:    activate-output
// Description: Grouping for sw activation rpc output
// -----------------------------------------------------------------------------
GrpActivateOutput::GrpActivateOutput(uint32_t id)
    : YangGroup("activate-output", id) {}

GrpActivateOutput::~GrpActivateOutput() {}

YangResult_E
GrpActivateOutput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /activate-output/status
  // Description: Status of the software files activation
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /activate-output/error-message
  // Description: Detailed error Message when the status is failed.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafErrorMessage errorMessageInst(ITEM_ERROR_MESSAGE);
  addLeaf(errorMessageInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /activate-output/notification-timeout
  // Description: Timeout on client waiting for the activate event
  // Type:        int32
  // Units:       seconds
  // -----------------------------------------------------------------------------
  LeafNotificationTimeout notificationTimeoutInst(ITEM_NOTIFICATION_TIMEOUT);
  addLeaf(notificationTimeoutInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /activate-output/status
// Description: Status of the software files activation
// -----------------------------------------------------------------------------
GrpActivateOutput::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

GrpActivateOutput::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /activate-output/error-message
// Description: Detailed error Message when the status is failed.
// -----------------------------------------------------------------------------
GrpActivateOutput::LeafErrorMessage::LeafErrorMessage(uint32_t id)
    : YangLeaf("error-message", id) {}

GrpActivateOutput::LeafErrorMessage::~LeafErrorMessage() {}

// -----------------------------------------------------------------------------
// Leaf:        /activate-output/notification-timeout
// Description: Timeout on client waiting for the activate event
// -----------------------------------------------------------------------------
GrpActivateOutput::LeafNotificationTimeout::LeafNotificationTimeout(uint32_t id)
    : YangLeaf("notification-timeout", id) {}

GrpActivateOutput::LeafNotificationTimeout::~LeafNotificationTimeout() {}

// -----------------------------------------------------------------------------
// Grouping:    download-notification
// Description: Grouping for notification event structure for download
// completion
// -----------------------------------------------------------------------------
GrpDownloadNotification::GrpDownloadNotification(uint32_t id)
    : YangGroup("download-notification", id) {}

GrpDownloadNotification::~GrpDownloadNotification() {}

YangResult_E
GrpDownloadNotification::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /download-notification/file-name
  // Description: File name of downloaded software package
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafFileName fileNameInst(ITEM_FILE_NAME);
  addLeaf(fileNameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /download-notification/status
  // Description: Status of finished operation execution
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /download-notification/error-message
  // Description: Detailed description of faulty situation
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafErrorMessage errorMessageInst(ITEM_ERROR_MESSAGE);
  addLeaf(errorMessageInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /download-notification/file-name
// Description: File name of downloaded software package
// -----------------------------------------------------------------------------
GrpDownloadNotification::LeafFileName::LeafFileName(uint32_t id)
    : YangLeaf("file-name", id) {}

GrpDownloadNotification::LeafFileName::~LeafFileName() {}

// -----------------------------------------------------------------------------
// Leaf:        /download-notification/status
// Description: Status of finished operation execution
// -----------------------------------------------------------------------------
GrpDownloadNotification::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

GrpDownloadNotification::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /download-notification/error-message
// Description: Detailed description of faulty situation
// -----------------------------------------------------------------------------
GrpDownloadNotification::LeafErrorMessage::LeafErrorMessage(uint32_t id)
    : YangLeaf("error-message", id) {}

GrpDownloadNotification::LeafErrorMessage::~LeafErrorMessage() {}

// -----------------------------------------------------------------------------
// Grouping:    install-notification
// Description: Grouping for notification event structure for installation
// completion
// -----------------------------------------------------------------------------
GrpInstallNotification::GrpInstallNotification(uint32_t id)
    : YangGroup("install-notification", id) {}

GrpInstallNotification::~GrpInstallNotification() {}

YangResult_E
GrpInstallNotification::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /install-notification/status
  // Description: Status of finished operation execution
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /install-notification/error-message
  // Description: Detailed description of faulty situation
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafErrorMessage errorMessageInst(ITEM_ERROR_MESSAGE);
  addLeaf(errorMessageInst);

  // -----------------------------------------------------------------------------
  // Reference:   /install-notification/slot-name
  // Description: Name of the slot to which software was installed.
  // Ref:         /software-inventory/software-slot/name
  // Units:
  // -----------------------------------------------------------------------------
  RefSlotName slotNameInst(ITEM_SLOT_NAME);
  addReference(slotNameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /install-notification/status
// Description: Status of finished operation execution
// -----------------------------------------------------------------------------
GrpInstallNotification::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

GrpInstallNotification::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /install-notification/error-message
// Description: Detailed description of faulty situation
// -----------------------------------------------------------------------------
GrpInstallNotification::LeafErrorMessage::LeafErrorMessage(uint32_t id)
    : YangLeaf("error-message", id) {}

GrpInstallNotification::LeafErrorMessage::~LeafErrorMessage() {}

// -----------------------------------------------------------------------------
// Reference:   /install-notification/slot-name
// Description: Name of the slot to which software was installed.
// -----------------------------------------------------------------------------
GrpInstallNotification::RefSlotName::RefSlotName(uint32_t id)
    : YangReference("slot-name", id, "/software-inventory/software-slot/name") {
}

GrpInstallNotification::RefSlotName::~RefSlotName() {}

// -----------------------------------------------------------------------------
// Grouping:    activation-notification
// Description: Grouping for notification event structure for activation
// completion
// -----------------------------------------------------------------------------
GrpActivationNotification::GrpActivationNotification(uint32_t id)
    : YangGroup("activation-notification", id) {}

GrpActivationNotification::~GrpActivationNotification() {}

YangResult_E
GrpActivationNotification::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /activation-notification/status
  // Description: Status of finished operation execution
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /activation-notification/return-code
  // Description: status code return when the software is tried to activate
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafReturnCode returnCodeInst(ITEM_RETURN_CODE);
  addLeaf(returnCodeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /activation-notification/error-message
  // Description: Detailed description of faulty situation
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafErrorMessage errorMessageInst(ITEM_ERROR_MESSAGE);
  addLeaf(errorMessageInst);

  // -----------------------------------------------------------------------------
  // Reference:   /activation-notification/slot-name
  // Description: Name of the slot which was activated
  // Ref:         /software-inventory/software-slot/name
  // Units:
  // -----------------------------------------------------------------------------
  RefSlotName slotNameInst(ITEM_SLOT_NAME);
  addReference(slotNameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /activation-notification/status
// Description: Status of finished operation execution
// -----------------------------------------------------------------------------
GrpActivationNotification::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

GrpActivationNotification::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /activation-notification/return-code
// Description: status code return when the software is tried to activate
// -----------------------------------------------------------------------------
GrpActivationNotification::LeafReturnCode::LeafReturnCode(uint32_t id)
    : YangLeaf("return-code", id) {}

GrpActivationNotification::LeafReturnCode::~LeafReturnCode() {}

// -----------------------------------------------------------------------------
// Leaf:        /activation-notification/error-message
// Description: Detailed description of faulty situation
// -----------------------------------------------------------------------------
GrpActivationNotification::LeafErrorMessage::LeafErrorMessage(uint32_t id)
    : YangLeaf("error-message", id) {}

GrpActivationNotification::LeafErrorMessage::~LeafErrorMessage() {}

// -----------------------------------------------------------------------------
// Reference:   /activation-notification/slot-name
// Description: Name of the slot which was activated
// -----------------------------------------------------------------------------
GrpActivationNotification::RefSlotName::RefSlotName(uint32_t id)
    : YangReference("slot-name", id, "/software-inventory/software-slot/name") {
}

GrpActivationNotification::RefSlotName::~RefSlotName() {}

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
// Notification:download-event
// Description: Notification event structure for download completion
// -----------------------------------------------------------------------------
NotifDownloadEvent::NotifDownloadEvent(uint32_t id)
    : YangNotif("download-event", id) {}

NotifDownloadEvent::~NotifDownloadEvent() {}

YangResult_E
NotifDownloadEvent::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /download-event/download-notification
  // Description:
  // -----------------------------------------------------------------------------
  GrpDownloadNotification downloadNotificationInst(ITEM_DOWNLOAD_NOTIFICATION);
  downloadNotificationInst.initialise();
  addGroup(downloadNotificationInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Notification:install-event
// Description: Notification event structure for installation completion
// -----------------------------------------------------------------------------
NotifInstallEvent::NotifInstallEvent(uint32_t id)
    : YangNotif("install-event", id) {}

NotifInstallEvent::~NotifInstallEvent() {}

YangResult_E
NotifInstallEvent::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /install-event/install-notification
  // Description:
  // -----------------------------------------------------------------------------
  GrpInstallNotification installNotificationInst(ITEM_INSTALL_NOTIFICATION);
  installNotificationInst.initialise();
  addGroup(installNotificationInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Notification:activation-event
// Description: Notification event structure for activation completion
// -----------------------------------------------------------------------------
NotifActivationEvent::NotifActivationEvent(uint32_t id)
    : YangNotif("activation-event", id) {}

NotifActivationEvent::~NotifActivationEvent() {}

YangResult_E
NotifActivationEvent::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /activation-event/activation-notification
  // Description:
  // -----------------------------------------------------------------------------
  GrpActivationNotification activationNotificationInst(
      ITEM_ACTIVATION_NOTIFICATION);
  activationNotificationInst.initialise();
  addGroup(activationNotificationInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-software-management
// Description: This module defines operations and configuration for the
// management of software packages.
//              This module is derived out of
//              opencpe-firmware-mgmt@2014-02-06.yang
//
//              Copyright 2019 the O-RAN Alliance.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
//              CONTRIBUTORS 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES,
//              INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//              MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//              DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
//              CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//              SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//              LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
//              USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
//              AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//              LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
//              IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//              THE POSSIBILITY OF SUCH DAMAGE.
//
//              Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following
//              conditions are met:
//
//              * Redistributions of source code must retain the above copyright
//              notice, this list of conditions and the above disclaimer.
//              * Redistributions in binary form must reproduce the above
//              copyright notice, this list of conditions and the above
//              disclaimer in the documentation and/or other materials provided
//              with the distribution.
//              * Neither the Members of the O-RAN Alliance nor the names of its
//              contributors may be used to endorse or promote products derived
//              from this software without specific prior written permission.
// -----------------------------------------------------------------------------
ModuleORanSoftwareManagement::ModuleORanSoftwareManagement(uint32_t id)
    : YangModule(
          "o-ran-software-management",
          "o-ran-software-management.yang",
          "o-ran-swm",
          "urn:o-ran:software-management:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /software-inventory
  // Description: Contains information about each software slot and its content.
  // -----------------------------------------------------------------------------
  CntSoftwareInventory softwareInventoryInst(ITEM_SOFTWARE_INVENTORY);
  softwareInventoryInst.initialise();
  addContainer(softwareInventoryInst);

  // -----------------------------------------------------------------------------
  // Notification:/download-event
  // Description: Notification event structure for download completion
  // -----------------------------------------------------------------------------
  NotifDownloadEvent downloadEventInst(ITEM_DOWNLOAD_EVENT);
  downloadEventInst.initialise();
  addNotification(downloadEventInst);

  // -----------------------------------------------------------------------------
  // Notification:/install-event
  // Description: Notification event structure for installation completion
  // -----------------------------------------------------------------------------
  NotifInstallEvent installEventInst(ITEM_INSTALL_EVENT);
  installEventInst.initialise();
  addNotification(installEventInst);

  // -----------------------------------------------------------------------------
  // Notification:/activation-event
  // Description: Notification event structure for activation completion
  // -----------------------------------------------------------------------------
  NotifActivationEvent activationEventInst(ITEM_ACTIVATION_EVENT);
  activationEventInst.initialise();
  addNotification(activationEventInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanSoftwareManagement::~ModuleORanSoftwareManagement() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanSoftwareManagement::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanSoftwareManagement>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanSoftwareManagement::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
