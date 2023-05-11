/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanFileManagement.cpp
 * \brief     Module ORanFileManagement interface
 *
 *
 * \details   This file defines the YANG module o-ran-file-management interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-file-management"
 *            YANG Filename:    "o-ran-file-management.yang"
 *            Module Prefix:    "o-ran-file-mgmt"
 *            Module namespace: "urn:o-ran:file-management:1.0"
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
#include "YangModuleORanFileManagement.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanFileManagement_NS;

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

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    file-path-grouping
// Description: Complete logical path of the file to upload/download
//              (no wildcard is allowed) ex : /o-RAN/log/syslog.1
// -----------------------------------------------------------------------------
GrpFilePathGrouping::GrpFilePathGrouping(uint32_t id)
    : YangGroup("file-path-grouping", id) {}

GrpFilePathGrouping::~GrpFilePathGrouping() {}

YangResult_E
GrpFilePathGrouping::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /file-path-grouping/local-logical-file-path
  // Description: Local logical file path
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafLocalLogicalFilePath localLogicalFilePathInst(
      ITEM_LOCAL_LOGICAL_FILE_PATH);
  addLeaf(localLogicalFilePathInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /file-path-grouping/remote-file-path
  // Description: URI specifying the remote-file-path on O-DU/NMS.
  //              Format:sftp://<username>@<host>[:port]/path
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafRemoteFilePath remoteFilePathInst(ITEM_REMOTE_FILE_PATH);
  addLeaf(remoteFilePathInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /file-path-grouping/local-logical-file-path
// Description: Local logical file path
// -----------------------------------------------------------------------------
GrpFilePathGrouping::LeafLocalLogicalFilePath::LeafLocalLogicalFilePath(
    uint32_t id)
    : YangLeaf("local-logical-file-path", id) {}

GrpFilePathGrouping::LeafLocalLogicalFilePath::~LeafLocalLogicalFilePath() {}

// -----------------------------------------------------------------------------
// Leaf:        /file-path-grouping/remote-file-path
// Description: URI specifying the remote-file-path on O-DU/NMS.
//              Format:sftp://<username>@<host>[:port]/path
// -----------------------------------------------------------------------------
GrpFilePathGrouping::LeafRemoteFilePath::LeafRemoteFilePath(uint32_t id)
    : YangLeaf("remote-file-path", id) {}

GrpFilePathGrouping::LeafRemoteFilePath::~LeafRemoteFilePath() {}

// -----------------------------------------------------------------------------
// Grouping:    output-status-grouping
// Description: Status grouping
// -----------------------------------------------------------------------------
GrpOutputStatusGrouping::GrpOutputStatusGrouping(uint32_t id)
    : YangGroup("output-status-grouping", id) {}

GrpOutputStatusGrouping::~GrpOutputStatusGrouping() {}

YangResult_E
GrpOutputStatusGrouping::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /output-status-grouping/status
  // Description: Operation status
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /output-status-grouping/reject-reason
  // Description:
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafRejectReason rejectReasonInst(ITEM_REJECT_REASON);
  addLeaf(rejectReasonInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /output-status-grouping/status
// Description: Operation status
// -----------------------------------------------------------------------------
GrpOutputStatusGrouping::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

GrpOutputStatusGrouping::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /output-status-grouping/reject-reason
// Description:
// -----------------------------------------------------------------------------
GrpOutputStatusGrouping::LeafRejectReason::LeafRejectReason(uint32_t id)
    : YangLeaf("reject-reason", id) {}

GrpOutputStatusGrouping::LeafRejectReason::~LeafRejectReason() {}

// -----------------------------------------------------------------------------
// Grouping:    credential-information
// Description: Type of authentication to use for SFTP upload or download.
// -----------------------------------------------------------------------------
GrpCredentialInformation::GrpCredentialInformation(uint32_t id)
    : YangGroup("credential-information", id) {}

GrpCredentialInformation::~GrpCredentialInformation() {}

YangResult_E
GrpCredentialInformation::initialise(void) {
  // -----------------------------------------------------------------------------
  // Choice:      /credential-information/credentials
  // Description:
  // Type:        Credentials_E
  // Units:       -
  // -----------------------------------------------------------------------------
  ChoiceCredentials credentialsInst(ITEM_CREDENTIALS);
  credentialsInst.initialise();
  addChoice(credentialsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Choice:      credentials
// Description:
// -----------------------------------------------------------------------------
GrpCredentialInformation::ChoiceCredentials::ChoiceCredentials(uint32_t id)
    : YangChoice("credentials", id) {}

GrpCredentialInformation::ChoiceCredentials::~ChoiceCredentials() {}

YangResult_E
GrpCredentialInformation::ChoiceCredentials::initialise(void) {

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptPassword password(ITEM_PASSWORD);
  password.initialise();
  addOption(password);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptCertificate certificate(ITEM_CERTIFICATE);
  certificate.initialise();
  addOption(certificate);

  return YangResult_E::OK;
}

// -------------------------------------------------------------------------
// Option:      /credential-information/credentials[password]
// -------------------------------------------------------------------------
GrpCredentialInformation::ChoiceCredentials::OptPassword::OptPassword(
    uint32_t id)
    : YangChoiceOption("password", id) {}

GrpCredentialInformation::ChoiceCredentials::OptPassword::~OptPassword() {}

YangResult_E
GrpCredentialInformation::ChoiceCredentials::OptPassword::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:   /credential-information/credentials[password]/password
  // Description: password for O-RU authentication method in use
  // -----------------------------------------------------------------------------
  CntPassword passwordInst(ITEM_PASSWORD);
  passwordInst.initialise();
  addContainer(passwordInst);

  // -----------------------------------------------------------------------------
  // Container:   /credential-information/credentials[password]/server
  // Description: Key for sFTP server authentication
  // -----------------------------------------------------------------------------
  CntServer serverInst(ITEM_SERVER);
  serverInst.initialise();
  addContainer(serverInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   password
// Description: password for O-RU authentication method in use
// -----------------------------------------------------------------------------
GrpCredentialInformation::ChoiceCredentials::OptPassword::CntPassword::
    CntPassword(uint32_t id)
    : YangContainer("password", id) {}

GrpCredentialInformation::ChoiceCredentials::OptPassword::CntPassword::
    ~CntPassword() {}

YangResult_E
GrpCredentialInformation::ChoiceCredentials::OptPassword::CntPassword::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf: /credential-information/credentials[password]/password/password
  // Description: password needed for O-RU authentication.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafPassword passwordInst(ITEM_PASSWORD);
  addLeaf(passwordInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /credential-information/credentials[password]/password/password
// Description: password needed for O-RU authentication.
// -----------------------------------------------------------------------------
GrpCredentialInformation::ChoiceCredentials::OptPassword::CntPassword::
    LeafPassword::LeafPassword(uint32_t id)
    : YangLeaf("password", id) {}

GrpCredentialInformation::ChoiceCredentials::OptPassword::CntPassword::
    LeafPassword::~LeafPassword() {}

// -----------------------------------------------------------------------------
// Container:   server
// Description: Key for sFTP server authentication
// -----------------------------------------------------------------------------
GrpCredentialInformation::ChoiceCredentials::OptPassword::CntServer::CntServer(
    uint32_t id)
    : YangContainer("server", id) {}

GrpCredentialInformation::ChoiceCredentials::OptPassword::CntServer::
    ~CntServer() {}

YangResult_E
GrpCredentialInformation::ChoiceCredentials::OptPassword::CntServer::initialise(
    void) {
  // -----------------------------------------------------------------------------
  // List:        /credential-information/credentials[password]/server/keys
  // Description: List of allowed algorithms with its keys
  // Array Key:
  // -----------------------------------------------------------------------------
  LstKeys keysInst(ITEM_KEYS);
  keysInst.initialise();
  addList(keysInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        keys
// Description: List of allowed algorithms with its keys
// -----------------------------------------------------------------------------
GrpCredentialInformation::ChoiceCredentials::OptPassword::CntServer::LstKeys::
    LstKeys(uint32_t id)
    : YangList("keys", id) {}

GrpCredentialInformation::ChoiceCredentials::OptPassword::CntServer::LstKeys::
    ~LstKeys() {}

YangResult_E
GrpCredentialInformation::ChoiceCredentials::OptPassword::CntServer::LstKeys::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:
  // /credential-information/credentials[password]/server/keys/ct:public-key-grouping
  // Module: ietf-crypto-types
  // Description:
  // -----------------------------------------------------------------------------
  ModuleIetfCryptoTypes_NS::GrpPublicKeyGrouping ctPublicKeyGroupingInst(
      ITEM_CT_PUBLIC_KEY_GROUPING);
  ctPublicKeyGroupingInst.initialise();
  addGroup(ctPublicKeyGroupingInst);

  return YangResult_E::OK;
}

// -------------------------------------------------------------------------
// Option:      /credential-information/credentials[certificate]
// -------------------------------------------------------------------------
GrpCredentialInformation::ChoiceCredentials::OptCertificate::OptCertificate(
    uint32_t id)
    : YangChoiceOption("certificate", id) {}

GrpCredentialInformation::ChoiceCredentials::OptCertificate::~OptCertificate() {
}

YangResult_E
GrpCredentialInformation::ChoiceCredentials::OptCertificate::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:   /credential-information/credentials[certificate]/certificate
  // Description: certificate authentication method in use
  // -----------------------------------------------------------------------------
  CntCertificate certificateInst(ITEM_CERTIFICATE);
  certificateInst.initialise();
  addContainer(certificateInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   certificate
// Description: certificate authentication method in use
// -----------------------------------------------------------------------------
GrpCredentialInformation::ChoiceCredentials::OptCertificate::CntCertificate::
    CntCertificate(uint32_t id)
    : YangContainer("certificate", id) {}

GrpCredentialInformation::ChoiceCredentials::OptCertificate::CntCertificate::
    ~CntCertificate() {}

YangResult_E
GrpCredentialInformation::ChoiceCredentials::OptCertificate::CntCertificate::
    initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Grouping:    retrieve-input
// Description: Grouping for information retrieval RPC input
// -----------------------------------------------------------------------------
GrpRetrieveInput::GrpRetrieveInput(uint32_t id)
    : YangGroup("retrieve-input", id) {}

GrpRetrieveInput::~GrpRetrieveInput() {}

YangResult_E
GrpRetrieveInput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /retrieve-input/logical-path
  // Description: O-RAN unit of which the files are to be listed.
  //              ex :  O-RAN/log, o-RAN/PM, O-RAN/transceiver
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafLogicalPath logicalPathInst(ITEM_LOGICAL_PATH);
  addLeaf(logicalPathInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /retrieve-input/file-name-filter
  // Description: Filter which are to be applied on the result list of file
  // names (* is allowed as wild-card). Type:        string Units:
  // -----------------------------------------------------------------------------
  LeafFileNameFilter fileNameFilterInst(ITEM_FILE_NAME_FILTER);
  addLeaf(fileNameFilterInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /retrieve-input/logical-path
// Description: O-RAN unit of which the files are to be listed.
//              ex :  O-RAN/log, o-RAN/PM, O-RAN/transceiver
// -----------------------------------------------------------------------------
GrpRetrieveInput::LeafLogicalPath::LeafLogicalPath(uint32_t id)
    : YangLeaf("logical-path", id) {}

GrpRetrieveInput::LeafLogicalPath::~LeafLogicalPath() {}

// -----------------------------------------------------------------------------
// Leaf:        /retrieve-input/file-name-filter
// Description: Filter which are to be applied on the result list of file names
// (* is allowed as wild-card).
// -----------------------------------------------------------------------------
GrpRetrieveInput::LeafFileNameFilter::LeafFileNameFilter(uint32_t id)
    : YangLeaf("file-name-filter", id) {}

GrpRetrieveInput::LeafFileNameFilter::~LeafFileNameFilter() {}

// -----------------------------------------------------------------------------
// Grouping:    retrieve-output
// Description: Grouping for information retrieval RPC output
// -----------------------------------------------------------------------------
GrpRetrieveOutput::GrpRetrieveOutput(uint32_t id)
    : YangGroup("retrieve-output", id) {}

GrpRetrieveOutput::~GrpRetrieveOutput() {}

YangResult_E
GrpRetrieveOutput::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /retrieve-output/file-list
  // Description: List of files in the unit with the filter applied.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstFileList fileListInst(ITEM_FILE_LIST);
  fileListInst.initialise();
  addList(fileListInst);

  // -----------------------------------------------------------------------------
  // Uses:        /retrieve-output/output-status-grouping
  // Description:
  // -----------------------------------------------------------------------------
  GrpOutputStatusGrouping outputStatusGroupingInst(ITEM_OUTPUT_STATUS_GROUPING);
  outputStatusGroupingInst.initialise();
  addGroup(outputStatusGroupingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        file-list
// Description: List of files in the unit with the filter applied.
// -----------------------------------------------------------------------------
GrpRetrieveOutput::LstFileList::LstFileList(uint32_t id)
    : YangList("file-list", id) {}

GrpRetrieveOutput::LstFileList::~LstFileList() {}

YangResult_E
GrpRetrieveOutput::LstFileList::initialise(void) {

  return YangResult_E::OK;
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
// Notification:file-upload-notification
// Description:
// -----------------------------------------------------------------------------
NotifFileUploadNotification::NotifFileUploadNotification(uint32_t id)
    : YangNotif("file-upload-notification", id) {}

NotifFileUploadNotification::~NotifFileUploadNotification() {}

YangResult_E
NotifFileUploadNotification::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /file-upload-notification/file-path-grouping
  // Description:
  // -----------------------------------------------------------------------------
  GrpFilePathGrouping filePathGroupingInst(ITEM_FILE_PATH_GROUPING);
  filePathGroupingInst.initialise();
  addGroup(filePathGroupingInst);

  // -----------------------------------------------------------------------------
  // Uses:        /file-upload-notification/output-status-grouping
  // Description:
  // -----------------------------------------------------------------------------
  GrpOutputStatusGrouping outputStatusGroupingInst(ITEM_OUTPUT_STATUS_GROUPING);
  outputStatusGroupingInst.initialise();
  addGroup(outputStatusGroupingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Notification:file-download-event
// Description:
// -----------------------------------------------------------------------------
NotifFileDownloadEvent::NotifFileDownloadEvent(uint32_t id)
    : YangNotif("file-download-event", id) {}

NotifFileDownloadEvent::~NotifFileDownloadEvent() {}

YangResult_E
NotifFileDownloadEvent::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /file-download-event/file-path-grouping
  // Description:
  // -----------------------------------------------------------------------------
  GrpFilePathGrouping filePathGroupingInst(ITEM_FILE_PATH_GROUPING);
  filePathGroupingInst.initialise();
  addGroup(filePathGroupingInst);

  // -----------------------------------------------------------------------------
  // Uses:        /file-download-event/output-status-grouping
  // Description:
  // -----------------------------------------------------------------------------
  GrpOutputStatusGrouping outputStatusGroupingInst(ITEM_OUTPUT_STATUS_GROUPING);
  outputStatusGroupingInst.initialise();
  addGroup(outputStatusGroupingInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-file-management
// Description: This module defines the configuration and operations for
// handling upload.
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
ModuleORanFileManagement::ModuleORanFileManagement(uint32_t id)
    : YangModule(
          "o-ran-file-management",
          "o-ran-file-management.yang",
          "o-ran-file-mgmt",
          "urn:o-ran:file-management:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Notification:/file-upload-notification
  // Description:
  // -----------------------------------------------------------------------------
  NotifFileUploadNotification fileUploadNotificationInst(
      ITEM_FILE_UPLOAD_NOTIFICATION);
  fileUploadNotificationInst.initialise();
  addNotification(fileUploadNotificationInst);

  // -----------------------------------------------------------------------------
  // Notification:/file-download-event
  // Description:
  // -----------------------------------------------------------------------------
  NotifFileDownloadEvent fileDownloadEventInst(ITEM_FILE_DOWNLOAD_EVENT);
  fileDownloadEventInst.initialise();
  addNotification(fileDownloadEventInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanFileManagement::~ModuleORanFileManagement() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanFileManagement::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanFileManagement>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanFileManagement::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
