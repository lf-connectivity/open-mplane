#ifndef _MODULE_O_RAN_FILE_MANAGEMENT_H_
#define _MODULE_O_RAN_FILE_MANAGEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanFileManagement.h
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

// Module:   ietf-crypto-types
// Revision:
// Notes:
#include "YangModuleIetfCryptoTypes.h"


namespace Mplane {

namespace ModuleORanFileManagement_NS {

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

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /file-path-grouping
// Description: Complete logical path of the file to upload/download
//              (no wildcard is allowed) ex : /o-RAN/log/syslog.1
// -----------------------------------------------------------------------------
class GrpFilePathGrouping : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_LOCAL_LOGICAL_FILE_PATH,  // LeafLocalLogicalFilePath
		ITEM_REMOTE_FILE_PATH,  // LeafRemoteFilePath
	};

	GrpFilePathGrouping(uint32_t id);
	~GrpFilePathGrouping();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /file-path-grouping/local-logical-file-path
	// Description: Local logical file path
	// -----------------------------------------------------------------------------
	class LeafLocalLogicalFilePath : public YangLeaf
	{
	public:

		LeafLocalLogicalFilePath(uint32_t id);
		~LeafLocalLogicalFilePath();

	}; // LeafLocalLogicalFilePath

	// -----------------------------------------------------------------------------
	// Leaf:        /file-path-grouping/remote-file-path
	// Description: URI specifying the remote-file-path on O-DU/NMS.
	//              Format:sftp://<username>@<host>[:port]/path
	// -----------------------------------------------------------------------------
	class LeafRemoteFilePath : public YangLeaf
	{
	public:

		LeafRemoteFilePath(uint32_t id);
		~LeafRemoteFilePath();

	}; // LeafRemoteFilePath

}; // GrpFilePathGrouping

// -----------------------------------------------------------------------------
// Grouping:    /output-status-grouping
// Description: Status grouping
// -----------------------------------------------------------------------------
class GrpOutputStatusGrouping : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_STATUS,  // LeafStatus
		ITEM_REJECT_REASON,  // LeafRejectReason
	};

	GrpOutputStatusGrouping(uint32_t id);
	~GrpOutputStatusGrouping();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /output-status-grouping/status
	// Description: Operation status
	// -----------------------------------------------------------------------------
	class LeafStatus : public YangLeaf
	{
	public:

		// Operation status
		enum class Status_E : uint32_t
		{
			SUCCESS,	//
			FAILURE,	//

			Num_Status_E
		};

		LeafStatus(uint32_t id);
		~LeafStatus();

	}; // LeafStatus

	// -----------------------------------------------------------------------------
	// Leaf:        /output-status-grouping/reject-reason
	// Description:
	// -----------------------------------------------------------------------------
	class LeafRejectReason : public YangLeaf
	{
	public:

		LeafRejectReason(uint32_t id);
		~LeafRejectReason();

	}; // LeafRejectReason

}; // GrpOutputStatusGrouping

// -----------------------------------------------------------------------------
// Grouping:    /credential-information
// Description: Type of authentication to use for SFTP upload or download.
// -----------------------------------------------------------------------------
class GrpCredentialInformation : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_CREDENTIALS,  // ChoiceCredentials
	};

	GrpCredentialInformation(uint32_t id);
	~GrpCredentialInformation();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Choice:      /credential-information/credentials
	// Description:
	// -----------------------------------------------------------------------------
	class ChoiceCredentials : public YangChoice
	{
	public:
		// Choice Option
		enum : uint32_t
		{
			ITEM_PASSWORD,  // OptPassword
			ITEM_CERTIFICATE,  // OptCertificate
		};

		ChoiceCredentials(uint32_t id);
		~ChoiceCredentials();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Option: /credential-information/credentials[password]
		// -----------------------------------------------------------------------------
		class OptPassword : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_PASSWORD,  // CntPassword
				ITEM_SERVER,  // CntServer
			};

			OptPassword(uint32_t id);
			~OptPassword();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Container:   /credential-information/credentials[password]/password
			// Description: password for O-RU authentication method in use
			// -----------------------------------------------------------------------------
			class CntPassword : public YangContainer
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_PASSWORD,  // LeafPassword
				};

				CntPassword(uint32_t id);
				~CntPassword();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /credential-information/credentials[password]/password/password
				// Description: password needed for O-RU authentication.
				// -----------------------------------------------------------------------------
				class LeafPassword : public YangLeaf
				{
				public:

					LeafPassword(uint32_t id);
					~LeafPassword();

				}; // LeafPassword

			}; // CntPassword

			// -----------------------------------------------------------------------------
			// Container:   /credential-information/credentials[password]/server
			// Description: Key for sFTP server authentication
			// -----------------------------------------------------------------------------
			class CntServer : public YangContainer
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_KEYS,  // LstKeys
				};

				CntServer(uint32_t id);
				~CntServer();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// List:        /credential-information/credentials[password]/server/keys
				// Description: List of allowed algorithms with its keys
				// -----------------------------------------------------------------------------
				class LstKeys : public YangList
				{
				public:
					// Item IDs
					enum : uint32_t
					{
						ITEM_CT_PUBLIC_KEY_GROUPING,  // Use GrpCtPublicKeyGrouping
					};

					LstKeys(uint32_t id);
					~LstKeys();

					YangResult_E initialise(void);

				}; // LstKeys

			}; // CntServer

		}; // OptPassword


		// -----------------------------------------------------------------------------
		// Option: /credential-information/credentials[certificate]
		// -----------------------------------------------------------------------------
		class OptCertificate : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_CERTIFICATE,  // CntCertificate
			};

			OptCertificate(uint32_t id);
			~OptCertificate();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Container:   /credential-information/credentials[certificate]/certificate
			// Description: certificate authentication method in use
			// -----------------------------------------------------------------------------
			class CntCertificate : public YangContainer
			{
			public:
				// Item IDs
				enum : uint32_t
				{
				};

				CntCertificate(uint32_t id);
				~CntCertificate();

				YangResult_E initialise(void);

			}; // CntCertificate

		}; // OptCertificate

	}; // ChoiceCredentials

}; // GrpCredentialInformation

// -----------------------------------------------------------------------------
// Grouping:    /retrieve-input
// Description: Grouping for information retrieval RPC input
// -----------------------------------------------------------------------------
class GrpRetrieveInput : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_LOGICAL_PATH,  // LeafLogicalPath
		ITEM_FILE_NAME_FILTER,  // LeafFileNameFilter
	};

	GrpRetrieveInput(uint32_t id);
	~GrpRetrieveInput();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /retrieve-input/logical-path
	// Description: O-RAN unit of which the files are to be listed.
	//              ex :  O-RAN/log, o-RAN/PM, O-RAN/transceiver
	// -----------------------------------------------------------------------------
	class LeafLogicalPath : public YangLeaf
	{
	public:

		LeafLogicalPath(uint32_t id);
		~LeafLogicalPath();

	}; // LeafLogicalPath

	// -----------------------------------------------------------------------------
	// Leaf:        /retrieve-input/file-name-filter
	// Description: Filter which are to be applied on the result list of file names (* is allowed as wild-card).
	// -----------------------------------------------------------------------------
	class LeafFileNameFilter : public YangLeaf
	{
	public:

		LeafFileNameFilter(uint32_t id);
		~LeafFileNameFilter();

	}; // LeafFileNameFilter

}; // GrpRetrieveInput

// -----------------------------------------------------------------------------
// Grouping:    /retrieve-output
// Description: Grouping for information retrieval RPC output
// -----------------------------------------------------------------------------
class GrpRetrieveOutput : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_FILE_LIST,  // LstFileList
		ITEM_OUTPUT_STATUS_GROUPING,  // Use GrpOutputStatusGrouping
	};

	GrpRetrieveOutput(uint32_t id);
	~GrpRetrieveOutput();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /retrieve-output/file-list
	// Description: List of files in the unit with the filter applied.
	// -----------------------------------------------------------------------------
	class LstFileList : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
		};

		LstFileList(uint32_t id);
		~LstFileList();

		YangResult_E initialise(void);

	}; // LstFileList

}; // GrpRetrieveOutput


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
// Notification:/file-upload-notification
// Description:
// -----------------------------------------------------------------------------
class NotifFileUploadNotification : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_FILE_PATH_GROUPING,  // Use GrpFilePathGrouping
		ITEM_OUTPUT_STATUS_GROUPING,  // Use GrpOutputStatusGrouping
	};

	NotifFileUploadNotification(uint32_t id);
	~NotifFileUploadNotification();

	YangResult_E initialise(void);

}; // NotifFileUploadNotification

// -----------------------------------------------------------------------------
// Notification:/file-download-event
// Description:
// -----------------------------------------------------------------------------
class NotifFileDownloadEvent : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_FILE_PATH_GROUPING,  // Use GrpFilePathGrouping
		ITEM_OUTPUT_STATUS_GROUPING,  // Use GrpOutputStatusGrouping
	};

	NotifFileDownloadEvent(uint32_t id);
	~NotifFileDownloadEvent();

	YangResult_E initialise(void);

}; // NotifFileDownloadEvent


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-file-management
// Description: This module defines the configuration and operations for handling upload.
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
class ModuleORanFileManagement : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_FILE_UPLOAD_NOTIFICATION,  // NotifFileUploadNotification
		ITEM_FILE_DOWNLOAD_EVENT,  // NotifFileDownloadEvent
	};

	ModuleORanFileManagement(uint32_t id);
	~ModuleORanFileManagement();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanFileManagement_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_FILE_MANAGEMENT_H_ */
