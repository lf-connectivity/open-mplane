#ifndef _MODULE_O_RAN_SOFTWARE_MANAGEMENT_H_
#define _MODULE_O_RAN_SOFTWARE_MANAGEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanSoftwareManagement.h
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
// Revision: 2013-07-15
// Notes:
#include "YangModuleIetfInetTypes.h"

// Module:   ietf-hardware
// Revision:
// Notes:
#include "YangModuleIetfHardware.h"

// Module:   o-ran-hardware
// Revision:
// Notes:
#include "YangModuleORanHardware.h"

// Module:   o-ran-file-management
// Revision:
// Notes:
#include "YangModuleORanFileManagement.h"


namespace Mplane {

namespace ModuleORanSoftwareManagement_NS {

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
// Container:   /software-inventory
// Description: Contains information about each software slot and its content.
// -----------------------------------------------------------------------------
class CntSoftwareInventory : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_SLOT_GROUP, // Use GrpSlotGroup
 };

 CntSoftwareInventory(uint32_t id);
 ~CntSoftwareInventory();

 YangResult_E initialise(void);

}; // CntSoftwareInventory


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /slot-group
// Description: Contains information about each software slot and its content.
// -----------------------------------------------------------------------------
class GrpSlotGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_SOFTWARE_SLOT, // LstSoftwareSlot
 };

 GrpSlotGroup(uint32_t id);
 ~GrpSlotGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /slot-group/software-slot
 // Description: Information about available software-slots and their software.
 // -----------------------------------------------------------------------------
 class LstSoftwareSlot : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_STATUS, // LeafStatus
     ITEM_ACTIVE, // LeafActive
     ITEM_RUNNING, // LeafRunning
     ITEM_ACCESS, // LeafAccess
     ITEM_VENDOR_CODE, // LeafVendorCode
     ITEM_BUILD_ID, // LeafBuildId
     ITEM_BUILD_NAME, // LeafBuildName
     ITEM_BUILD_VERSION, // LeafBuildVersion
     ITEM_PRODUCT_CODE, // RefProductCode
     ITEM_FILES, // LstFiles
   };

   LstSoftwareSlot(uint32_t id);
   ~LstSoftwareSlot();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /slot-group/software-slot/name
   // Description: Name of the software package. This shall be unique to
   // identify the software-slot.
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Leaf:        /slot-group/software-slot/status
   // Description: Indicates the status of the software slot
   // -----------------------------------------------------------------------------
   class LeafStatus : public YangLeaf {
    public:
     // Indicates the status of the software slot
     enum class Status_E : uint32_t {
       VALID, // Slot Contains software build considered as proven valid
       INVALID, // software build is not currently used by O-RU. The software is
                // considered by O-RU as damaged (e.g. wrong CRC)
       EMPTY, // W slot does not contain software package.

       Num_Status_E
     };

     LeafStatus(uint32_t id);
     ~LeafStatus();

   }; // LeafStatus

   // -----------------------------------------------------------------------------
   // Leaf:        /slot-group/software-slot/active
   // Description: informs if software stored in particular slot is activated at
   // the moment
   // -----------------------------------------------------------------------------
   class LeafActive : public YangLeaf {
    public:
     LeafActive(uint32_t id);
     ~LeafActive();

   }; // LeafActive

   // -----------------------------------------------------------------------------
   // Leaf:        /slot-group/software-slot/running
   // Description: informs if software stored in particular slot is used at the
   // moment
   // -----------------------------------------------------------------------------
   class LeafRunning : public YangLeaf {
    public:
     LeafRunning(uint32_t id);
     ~LeafRunning();

   }; // LeafRunning

   // -----------------------------------------------------------------------------
   // Leaf:        /slot-group/software-slot/access
   // Description: Indicates the writability of the slot.
   //              A Read-Only software slot is one which has a factory
   //              installed software-slot
   // -----------------------------------------------------------------------------
   class LeafAccess : public YangLeaf {
    public:
     // Indicates the writability of the slot.
     // A Read-Only software slot is one which has a factory installed
     // software-slot
     enum class Access_E : uint32_t {
       READ_ONLY, // slot intended only for factory software,
                  // activation of such software slot means getting back to
                  // factory defaults
       READ_WRITE, // slot used for updating software

       Num_Access_E
     };

     LeafAccess(uint32_t id);
     ~LeafAccess();

   }; // LeafAccess

   // -----------------------------------------------------------------------------
   // Leaf:        /slot-group/software-slot/vendor-code
   // Description: Unique code of the vendor. This is derived from manifest
   // file.
   // -----------------------------------------------------------------------------
   class LeafVendorCode : public YangLeaf {
    public:
     LeafVendorCode(uint32_t id);
     ~LeafVendorCode();

   }; // LeafVendorCode

   // -----------------------------------------------------------------------------
   // Leaf:        /slot-group/software-slot/build-id
   // Description: Identity associated with the software build. This is derived
   // from manifest file.
   // -----------------------------------------------------------------------------
   class LeafBuildId : public YangLeaf {
    public:
     LeafBuildId(uint32_t id);
     ~LeafBuildId();

   }; // LeafBuildId

   // -----------------------------------------------------------------------------
   // Leaf:        /slot-group/software-slot/build-name
   // Description: Name of the build. This is derived from manifest file.
   // -----------------------------------------------------------------------------
   class LeafBuildName : public YangLeaf {
    public:
     LeafBuildName(uint32_t id);
     ~LeafBuildName();

   }; // LeafBuildName

   // -----------------------------------------------------------------------------
   // Leaf:        /slot-group/software-slot/build-version
   // Description: The vendor-specific version string of the software build.
   // -----------------------------------------------------------------------------
   class LeafBuildVersion : public YangLeaf {
    public:
     LeafBuildVersion(uint32_t id);
     ~LeafBuildVersion();

   }; // LeafBuildVersion

   // -----------------------------------------------------------------------------
   // Reference:   /slot-group/software-slot/product-code
   // Description: product code provided by the vendor, specific to the product.
   // This is derived from manifest file.
   // -----------------------------------------------------------------------------
   class RefProductCode : public YangReference {
    public:
     RefProductCode(uint32_t id);
     ~RefProductCode();

   }; // RefProductCode

   // -----------------------------------------------------------------------------
   // List:        /slot-group/software-slot/files
   // Description: List of all the files present in the software package.
   // -----------------------------------------------------------------------------
   class LstFiles : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_NAME, // LeafName
       ITEM_VERSION, // LeafVersion
       ITEM_LOCAL_PATH, // LeafLocalPath
       ITEM_INTEGRITY, // LeafIntegrity
     };

     LstFiles(uint32_t id);
     ~LstFiles();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:        /slot-group/software-slot/files/name
     // Description: Name of the file installed in the slot.
     // -----------------------------------------------------------------------------
     class LeafName : public YangLeaf {
      public:
       LeafName(uint32_t id);
       ~LeafName();

     }; // LeafName

     // -----------------------------------------------------------------------------
     // Leaf:        /slot-group/software-slot/files/version
     // Description: Version of the file installed in the slot
     // -----------------------------------------------------------------------------
     class LeafVersion : public YangLeaf {
      public:
       LeafVersion(uint32_t id);
       ~LeafVersion();

     }; // LeafVersion

     // -----------------------------------------------------------------------------
     // Leaf:        /slot-group/software-slot/files/local-path
     // Description: Complete path of the file stored locally
     // -----------------------------------------------------------------------------
     class LeafLocalPath : public YangLeaf {
      public:
       LeafLocalPath(uint32_t id);
       ~LeafLocalPath();

     }; // LeafLocalPath

     // -----------------------------------------------------------------------------
     // Leaf:        /slot-group/software-slot/files/integrity
     // Description: Result of the file integrity check (checksum calculation)
     // during installation.
     // -----------------------------------------------------------------------------
     class LeafIntegrity : public YangLeaf {
      public:
       // Result of the file integrity check (checksum calculation) during
       // installation.
       enum class Integrity_E : uint32_t {
         OK, // OK - indicates that file integrity is correct
         NOK, // NOK - indicates corrupted file

         Num_Integrity_E
       };

       LeafIntegrity(uint32_t id);
       ~LeafIntegrity();

     }; // LeafIntegrity

   }; // LstFiles

 }; // LstSoftwareSlot

}; // GrpSlotGroup

// -----------------------------------------------------------------------------
// Grouping:    /download-input
// Description: Grouping for sw download rpc input
// -----------------------------------------------------------------------------
class GrpDownloadInput : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_REMOTE_FILE_PATH, // LeafRemoteFilePath
   ITEM_O_RAN_FM_CREDENTIAL_INFORMATION, // Use GrpORanFmCredentialInformation
 };

 GrpDownloadInput(uint32_t id);
 ~GrpDownloadInput();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /download-input/remote-file-path
 // Description: URI of the software image including username.
 //              The following format is possible:
 //              sftp://<username>@<host>[:<port>]/path
 // -----------------------------------------------------------------------------
 class LeafRemoteFilePath : public YangLeaf {
  public:
   LeafRemoteFilePath(uint32_t id);
   ~LeafRemoteFilePath();

 }; // LeafRemoteFilePath

}; // GrpDownloadInput

// -----------------------------------------------------------------------------
// Grouping:    /download-output
// Description: Grouping for sw download rpc output
// -----------------------------------------------------------------------------
class GrpDownloadOutput : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_STATUS, // LeafStatus
   ITEM_ERROR_MESSAGE, // LeafErrorMessage
   ITEM_NOTIFICATION_TIMEOUT, // LeafNotificationTimeout
 };

 GrpDownloadOutput(uint32_t id);
 ~GrpDownloadOutput();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /download-output/status
 // Description: Status of the software files download
 // -----------------------------------------------------------------------------
 class LeafStatus : public YangLeaf {
  public:
   // Status of the software files download
   enum class Status_E : uint32_t {
     STARTED, // Operation has been started without error.
     FAILED, // Operation cannot be started because of error, more detailed
             // information can be found in error-message.

     Num_Status_E
   };

   LeafStatus(uint32_t id);
   ~LeafStatus();

 }; // LeafStatus

 // -----------------------------------------------------------------------------
 // Leaf:        /download-output/error-message
 // Description: Detailed error Message when the status is failed.
 // -----------------------------------------------------------------------------
 class LeafErrorMessage : public YangLeaf {
  public:
   LeafErrorMessage(uint32_t id);
   ~LeafErrorMessage();

 }; // LeafErrorMessage

 // -----------------------------------------------------------------------------
 // Leaf:        /download-output/notification-timeout
 // Description: Notification timeout is the time NETCONF client shall
 //              wait for a 'download-event' notification from O-RU. If there is
 //              no 'download-event' notification received within
 //              notification-timeout, NETCONF client shall assume the download
 //              timeout/failure, and follow necessary steps.
 // -----------------------------------------------------------------------------
 class LeafNotificationTimeout : public YangLeaf {
  public:
   LeafNotificationTimeout(uint32_t id);
   ~LeafNotificationTimeout();

 }; // LeafNotificationTimeout

}; // GrpDownloadOutput

// -----------------------------------------------------------------------------
// Grouping:    /install-input
// Description: Grouping for sw installation rpc input
// -----------------------------------------------------------------------------
class GrpInstallInput : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_SLOT_NAME, // RefSlotName
   ITEM_FILE_NAMES, // LstFileNames
 };

 GrpInstallInput(uint32_t id);
 ~GrpInstallInput();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Reference:   /install-input/slot-name
 // Description: software-slot to which the software shall be installed to.
 // -----------------------------------------------------------------------------
 class RefSlotName : public YangReference {
  public:
   RefSlotName(uint32_t id);
   ~RefSlotName();

 }; // RefSlotName

 // -----------------------------------------------------------------------------
 // List:        /install-input/file-names
 // Description: Names of the files within software package to be installed
 // -----------------------------------------------------------------------------
 class LstFileNames : public YangList {
  public:
   // Item IDs
   enum : uint32_t {};

   LstFileNames(uint32_t id);
   ~LstFileNames();

   YangResult_E initialise(void);

 }; // LstFileNames

}; // GrpInstallInput

// -----------------------------------------------------------------------------
// Grouping:    /install-output
// Description: Grouping for sw installation rpc output
// -----------------------------------------------------------------------------
class GrpInstallOutput : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_STATUS, // LeafStatus
   ITEM_ERROR_MESSAGE, // LeafErrorMessage
 };

 GrpInstallOutput(uint32_t id);
 ~GrpInstallOutput();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /install-output/status
 // Description: Status of the software package install.
 // -----------------------------------------------------------------------------
 class LeafStatus : public YangLeaf {
  public:
   // Status of the software package install.
   enum class Status_E : uint32_t {
     STARTED, // Operation has been started without error.
     FAILED, // Operation cannot be started because of error, more detailed
             // information can be found in error-message.

     Num_Status_E
   };

   LeafStatus(uint32_t id);
   ~LeafStatus();

 }; // LeafStatus

 // -----------------------------------------------------------------------------
 // Leaf:        /install-output/error-message
 // Description: Detailed error Message when the status is failed.
 // -----------------------------------------------------------------------------
 class LeafErrorMessage : public YangLeaf {
  public:
   LeafErrorMessage(uint32_t id);
   ~LeafErrorMessage();

 }; // LeafErrorMessage

}; // GrpInstallOutput

// -----------------------------------------------------------------------------
// Grouping:    /activate-input
// Description: Grouping for sw activation rpc input
// -----------------------------------------------------------------------------
class GrpActivateInput : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_SLOT_NAME, // RefSlotName
 };

 GrpActivateInput(uint32_t id);
 ~GrpActivateInput();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Reference:   /activate-input/slot-name
 // Description: Slot name on which software has to be activated.
 // -----------------------------------------------------------------------------
 class RefSlotName : public YangReference {
  public:
   RefSlotName(uint32_t id);
   ~RefSlotName();

 }; // RefSlotName

}; // GrpActivateInput

// -----------------------------------------------------------------------------
// Grouping:    /activate-output
// Description: Grouping for sw activation rpc output
// -----------------------------------------------------------------------------
class GrpActivateOutput : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_STATUS, // LeafStatus
   ITEM_ERROR_MESSAGE, // LeafErrorMessage
   ITEM_NOTIFICATION_TIMEOUT, // LeafNotificationTimeout
 };

 GrpActivateOutput(uint32_t id);
 ~GrpActivateOutput();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /activate-output/status
 // Description: Status of the software files activation
 // -----------------------------------------------------------------------------
 class LeafStatus : public YangLeaf {
  public:
   // Status of the software files activation
   enum class Status_E : uint32_t {
     STARTED, // Operation has been started without error.
     FAILED, // Operation cannot be started because of error, more detailed
             // information can be found in error-message.

     Num_Status_E
   };

   LeafStatus(uint32_t id);
   ~LeafStatus();

 }; // LeafStatus

 // -----------------------------------------------------------------------------
 // Leaf:        /activate-output/error-message
 // Description: Detailed error Message when the status is failed.
 // -----------------------------------------------------------------------------
 class LeafErrorMessage : public YangLeaf {
  public:
   LeafErrorMessage(uint32_t id);
   ~LeafErrorMessage();

 }; // LeafErrorMessage

 // -----------------------------------------------------------------------------
 // Leaf:        /activate-output/notification-timeout
 // Description: Timeout on client waiting for the activate event
 // -----------------------------------------------------------------------------
 class LeafNotificationTimeout : public YangLeaf {
  public:
   LeafNotificationTimeout(uint32_t id);
   ~LeafNotificationTimeout();

 }; // LeafNotificationTimeout

}; // GrpActivateOutput

// -----------------------------------------------------------------------------
// Grouping:    /download-notification
// Description: Grouping for notification event structure for download completion
// -----------------------------------------------------------------------------
class GrpDownloadNotification : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_FILE_NAME, // LeafFileName
   ITEM_STATUS, // LeafStatus
   ITEM_ERROR_MESSAGE, // LeafErrorMessage
 };

 GrpDownloadNotification(uint32_t id);
 ~GrpDownloadNotification();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /download-notification/file-name
 // Description: File name of downloaded software package
 // -----------------------------------------------------------------------------
 class LeafFileName : public YangLeaf {
  public:
   LeafFileName(uint32_t id);
   ~LeafFileName();

 }; // LeafFileName

 // -----------------------------------------------------------------------------
 // Leaf:        /download-notification/status
 // Description: Status of finished operation execution
 // -----------------------------------------------------------------------------
 class LeafStatus : public YangLeaf {
  public:
   // Status of finished operation execution
   enum class Status_E : uint32_t {
     COMPLETED, // Operation completed successfully
     AUTHENTICATION_ERROR, // source available, wrong credentials
     PROTOCOL_ERROR, // SFTP errors
     FILE_NOT_FOUND, // source not available.
     APPLICATION_ERROR, // Application related errors
     TIMEOUT, // Timeout waiting for download

     Num_Status_E
   };

   LeafStatus(uint32_t id);
   ~LeafStatus();

 }; // LeafStatus

 // -----------------------------------------------------------------------------
 // Leaf:        /download-notification/error-message
 // Description: Detailed description of faulty situation
 // -----------------------------------------------------------------------------
 class LeafErrorMessage : public YangLeaf {
  public:
   LeafErrorMessage(uint32_t id);
   ~LeafErrorMessage();

 }; // LeafErrorMessage

}; // GrpDownloadNotification

// -----------------------------------------------------------------------------
// Grouping:    /install-notification
// Description: Grouping for notification event structure for installation completion
// -----------------------------------------------------------------------------
class GrpInstallNotification : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_STATUS, // LeafStatus
   ITEM_ERROR_MESSAGE, // LeafErrorMessage
   ITEM_SLOT_NAME, // RefSlotName
 };

 GrpInstallNotification(uint32_t id);
 ~GrpInstallNotification();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /install-notification/status
 // Description: Status of finished operation execution
 // -----------------------------------------------------------------------------
 class LeafStatus : public YangLeaf {
  public:
   // Status of finished operation execution
   enum class Status_E : uint32_t {
     COMPLETED, // Operation completed successfully
     FILE_ERROR, // operation on the file resulted in in error, disk
                 // failure, not enough disk space, incompatible file
                 // format
     INTEGRITY_ERROR, // file is corrupted
     APPLICATION_ERROR, // operation failed due to internal reason

     Num_Status_E
   };

   LeafStatus(uint32_t id);
   ~LeafStatus();

 }; // LeafStatus

 // -----------------------------------------------------------------------------
 // Leaf:        /install-notification/error-message
 // Description: Detailed description of faulty situation
 // -----------------------------------------------------------------------------
 class LeafErrorMessage : public YangLeaf {
  public:
   LeafErrorMessage(uint32_t id);
   ~LeafErrorMessage();

 }; // LeafErrorMessage

 // -----------------------------------------------------------------------------
 // Reference:   /install-notification/slot-name
 // Description: Name of the slot to which software was installed.
 // -----------------------------------------------------------------------------
 class RefSlotName : public YangReference {
  public:
   RefSlotName(uint32_t id);
   ~RefSlotName();

 }; // RefSlotName

}; // GrpInstallNotification

// -----------------------------------------------------------------------------
// Grouping:    /activation-notification
// Description: Grouping for notification event structure for activation completion
// -----------------------------------------------------------------------------
class GrpActivationNotification : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_STATUS, // LeafStatus
   ITEM_RETURN_CODE, // LeafReturnCode
   ITEM_ERROR_MESSAGE, // LeafErrorMessage
   ITEM_SLOT_NAME, // RefSlotName
 };

 GrpActivationNotification(uint32_t id);
 ~GrpActivationNotification();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /activation-notification/status
 // Description: Status of finished operation execution
 // -----------------------------------------------------------------------------
 class LeafStatus : public YangLeaf {
  public:
   // Status of finished operation execution
   enum class Status_E : uint32_t {
     COMPLETED, // Operation completed successfully
     APPLICATION_ERROR, // Operation finished with error, more details can
                        // by found in error-message

     Num_Status_E
   };

   LeafStatus(uint32_t id);
   ~LeafStatus();

 }; // LeafStatus

 // -----------------------------------------------------------------------------
 // Leaf:        /activation-notification/return-code
 // Description: status code return when the software is tried to
 // activate
 // -----------------------------------------------------------------------------
 class LeafReturnCode : public YangLeaf {
  public:
   LeafReturnCode(uint32_t id);
   ~LeafReturnCode();

 }; // LeafReturnCode

 // -----------------------------------------------------------------------------
 // Leaf:        /activation-notification/error-message
 // Description: Detailed description of faulty situation
 // -----------------------------------------------------------------------------
 class LeafErrorMessage : public YangLeaf {
  public:
   LeafErrorMessage(uint32_t id);
   ~LeafErrorMessage();

 }; // LeafErrorMessage

 // -----------------------------------------------------------------------------
 // Reference:   /activation-notification/slot-name
 // Description: Name of the slot which was activated
 // -----------------------------------------------------------------------------
 class RefSlotName : public YangReference {
  public:
   RefSlotName(uint32_t id);
   ~RefSlotName();

 }; // RefSlotName

}; // GrpActivationNotification


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
// Notification:/download-event
// Description: Notification event structure for download completion
// -----------------------------------------------------------------------------
class NotifDownloadEvent : public YangNotif
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_DOWNLOAD_NOTIFICATION, // Use GrpDownloadNotification
 };

 NotifDownloadEvent(uint32_t id);
 ~NotifDownloadEvent();

 YangResult_E initialise(void);

}; // NotifDownloadEvent

// -----------------------------------------------------------------------------
// Notification:/install-event
// Description: Notification event structure for installation completion
// -----------------------------------------------------------------------------
class NotifInstallEvent : public YangNotif
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_INSTALL_NOTIFICATION, // Use GrpInstallNotification
 };

 NotifInstallEvent(uint32_t id);
 ~NotifInstallEvent();

 YangResult_E initialise(void);

}; // NotifInstallEvent

// -----------------------------------------------------------------------------
// Notification:/activation-event
// Description: Notification event structure for activation completion
// -----------------------------------------------------------------------------
class NotifActivationEvent : public YangNotif
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ACTIVATION_NOTIFICATION, // Use GrpActivationNotification
 };

 NotifActivationEvent(uint32_t id);
 ~NotifActivationEvent();

 YangResult_E initialise(void);

}; // NotifActivationEvent


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
class ModuleORanSoftwareManagement : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_SOFTWARE_INVENTORY, // CntSoftwareInventory
   ITEM_DOWNLOAD_EVENT, // NotifDownloadEvent
   ITEM_INSTALL_EVENT, // NotifInstallEvent
   ITEM_ACTIVATION_EVENT, // NotifActivationEvent
 };

 ModuleORanSoftwareManagement(uint32_t id);
 ~ModuleORanSoftwareManagement();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanSoftwareManagement_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_SOFTWARE_MANAGEMENT_H_ */
