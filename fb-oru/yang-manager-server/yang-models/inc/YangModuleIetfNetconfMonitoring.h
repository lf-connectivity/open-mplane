#ifndef _MODULE_IETF_NETCONF_MONITORING_H_
#define _MODULE_IETF_NETCONF_MONITORING_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfNetconfMonitoring.h
 * \brief     Module IetfNetconfMonitoring interface
 *
 *
 * \details   This file defines the YANG module ietf-netconf-monitoring interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-netconf-monitoring"
 *            YANG Filename:    "ietf-netconf-monitoring.yang"
 *            Module Prefix:    "ncm"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-netconf-monitoring"
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

// Module:   ietf-yang-types
// Revision:
// Notes:
#include "YangModuleIetfYangTypes.h"

// Module:   ietf-inet-types
// Revision:
// Notes:
#include "YangModuleIetfInetTypes.h"


namespace Mplane {

namespace ModuleIetfNetconfMonitoring_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// Enumeration of possible NETCONF datastore types.
enum class NetconfDatastoreType_E : uint32_t
{
	RUNNING,	//
	CANDIDATE,	//
	STARTUP,	//

	Num_NetconfDatastoreType_E
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
// -----------------------------------------------------------------------------
// Container:   /netconf-state
// Description: The netconf-state container is the root of the monitoring
//              data model.
// -----------------------------------------------------------------------------
class CntNetconfState : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_CAPABILITIES,  // CntCapabilities
		ITEM_DATASTORES,  // CntDatastores
		ITEM_SCHEMAS,  // CntSchemas
		ITEM_SESSIONS,  // CntSessions
		ITEM_STATISTICS,  // CntStatistics
	};

	CntNetconfState(uint32_t id);
	~CntNetconfState();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Container:   /netconf-state/capabilities
	// Description: Contains the list of NETCONF capabilities supported by the
	//              server.
	// -----------------------------------------------------------------------------
	class CntCapabilities : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_CAPABILITY,  // LstCapability
		};

		CntCapabilities(uint32_t id);
		~CntCapabilities();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// List:        /netconf-state/capabilities/capability
		// Description: List of NETCONF capabilities supported by the server.
		// -----------------------------------------------------------------------------
		class LstCapability : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstCapability(uint32_t id);
			~LstCapability();

			YangResult_E initialise(void);

		}; // LstCapability

	}; // CntCapabilities

	// -----------------------------------------------------------------------------
	// Container:   /netconf-state/datastores
	// Description: Contains the list of NETCONF configuration datastores.
	// -----------------------------------------------------------------------------
	class CntDatastores : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_DATASTORE,  // LstDatastore
		};

		CntDatastores(uint32_t id);
		~CntDatastores();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// List:        /netconf-state/datastores/datastore
		// Description: List of NETCONF configuration datastores supported by
		//              the NETCONF server and related information.
		// -----------------------------------------------------------------------------
		class LstDatastore : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_NAME,  // LeafName
				ITEM_LOCKS,  // CntLocks
			};

			LstDatastore(uint32_t id);
			~LstDatastore();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /netconf-state/datastores/datastore/name
			// Description: Name of the datastore associated with this list entry.
			// -----------------------------------------------------------------------------
			class LeafName : public YangLeaf
			{
			public:

				// Name of the datastore associated with this list entry.
				enum class Name_E : uint32_t
				{

					Num_Name_E
				};

				LeafName(uint32_t id);
				~LeafName();

			}; // LeafName

			// -----------------------------------------------------------------------------
			// Container:   /netconf-state/datastores/datastore/locks
			// Description: The NETCONF <lock> and <partial-lock> operations allow
			//              a client to lock specific resources in a datastore.  The
			//              NETCONF server will prevent changes to the locked
			//              resources by all sessions except the one that acquired
			//              the lock(s).
			//              Monitoring information is provided for each datastore
			//              entry including details such as the session that acquired
			//              the lock, the type of lock (global or partial) and the
			//              list of locked resources.  Multiple locks per datastore
			//              are supported.
			// -----------------------------------------------------------------------------
			class CntLocks : public YangContainer
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_LOCK_INFO,  // GrpLockInfo
					ITEM_LOCK_TYPE,  // ChoiceLockType
				};

				CntLocks(uint32_t id);
				~CntLocks();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Grouping:    /netconf-state/datastores/datastore/locks/lock-info
				// Description: Lock related parameters, common to both global and
				//              partial locks.
				// -----------------------------------------------------------------------------
				class GrpLockInfo : public YangGroup
				{
				public:
					// Item IDs
					enum : uint32_t
					{
						ITEM_LOCKED_BY_SESSION,  // LeafLockedBySession
						ITEM_LOCKED_TIME,  // LeafLockedTime
					};

					GrpLockInfo(uint32_t id);
					~GrpLockInfo();

					YangResult_E initialise(void);

					// -----------------------------------------------------------------------------
					// Leaf:        /netconf-state/datastores/datastore/locks/lock-info/locked-by-session
					// Description: The session ID of the session that has locked
					//              this resource.  Both a global lock and a partial
					//              lock MUST contain the NETCONF session-id.
					//              If the lock is held by a session that is not managed
					//              by the NETCONF server (e.g., a CLI session), a session
					//              id of 0 (zero) is reported.
					// -----------------------------------------------------------------------------
					class LeafLockedBySession : public YangLeaf
					{
					public:

						LeafLockedBySession(uint32_t id);
						~LeafLockedBySession();

					}; // LeafLockedBySession

					// -----------------------------------------------------------------------------
					// Leaf:        /netconf-state/datastores/datastore/locks/lock-info/locked-time
					// Description: The date and time of when the resource was
					//              locked.
					// -----------------------------------------------------------------------------
					class LeafLockedTime : public YangLeaf
					{
					public:

						LeafLockedTime(uint32_t id);
						~LeafLockedTime();

					}; // LeafLockedTime

				}; // GrpLockInfo

				// -----------------------------------------------------------------------------
				// Choice:      /netconf-state/datastores/datastore/locks/lock-type
				// Description: Indicates if a global lock or a set of partial locks
				//              are set.
				// -----------------------------------------------------------------------------
				class ChoiceLockType : public YangChoice
				{
				public:
					// Choice Option
					enum : uint32_t
					{
						ITEM_GLOBAL_LOCK,  // OptGlobalLock
						ITEM_PARTIAL_LOCK,  // OptPartialLock
					};

					ChoiceLockType(uint32_t id);
					~ChoiceLockType();

					YangResult_E initialise(void);

					// -----------------------------------------------------------------------------
					// Option: /netconf-state/datastores/datastore/locks/lock-type[global-lock]
					// -----------------------------------------------------------------------------
					class OptGlobalLock : public YangChoiceOption
					{
					public:
						// Item IDs
						enum : uint32_t
						{
							ITEM_GLOBAL_LOCK,  // CntGlobalLock
						};

						OptGlobalLock(uint32_t id);
						~OptGlobalLock();

						YangResult_E initialise(void);

						// -----------------------------------------------------------------------------
						// Container:   /netconf-state/datastores/datastore/locks/lock-type[global-lock]/global-lock
						// Description: Present if the global lock is set.
						// -----------------------------------------------------------------------------
						class CntGlobalLock : public YangContainer
						{
						public:
							// Item IDs
							enum : uint32_t
							{
								ITEM_LOCK_INFO,  // Use GrpLockInfo
							};

							CntGlobalLock(uint32_t id);
							~CntGlobalLock();

							YangResult_E initialise(void);

						}; // CntGlobalLock

					}; // OptGlobalLock


					// -----------------------------------------------------------------------------
					// Option: /netconf-state/datastores/datastore/locks/lock-type[partial-lock]
					// -----------------------------------------------------------------------------
					class OptPartialLock : public YangChoiceOption
					{
					public:
						// Item IDs
						enum : uint32_t
						{
							ITEM_PARTIAL_LOCK,  // LstPartialLock
						};

						OptPartialLock(uint32_t id);
						~OptPartialLock();

						YangResult_E initialise(void);

						// -----------------------------------------------------------------------------
						// List:        /netconf-state/datastores/datastore/locks/lock-type[partial-lock]/partial-lock
						// Description: List of partial locks.
						// -----------------------------------------------------------------------------
						class LstPartialLock : public YangList
						{
						public:
							// Item IDs
							enum : uint32_t
							{
								ITEM_LOCK_ID,  // LeafLockId
								ITEM_SELECT,  // LstSelect
								ITEM_LOCKED_NODE,  // LstLockedNode
								ITEM_LOCK_INFO,  // Use GrpLockInfo
							};

							LstPartialLock(uint32_t id);
							~LstPartialLock();

							YangResult_E initialise(void);

							// -----------------------------------------------------------------------------
							// Leaf:        /netconf-state/datastores/datastore/locks/lock-type[partial-lock]/partial-lock/lock-id
							// Description: This is the lock id returned in the <partial-lock>
							//              response.
							// -----------------------------------------------------------------------------
							class LeafLockId : public YangLeaf
							{
							public:

								LeafLockId(uint32_t id);
								~LeafLockId();

							}; // LeafLockId

							// -----------------------------------------------------------------------------
							// List:        /netconf-state/datastores/datastore/locks/lock-type[partial-lock]/partial-lock/select
							// Description: The xpath expression that was used to request
							//              the lock.  The select expression indicates the
							//              original intended scope of the lock.
							// -----------------------------------------------------------------------------
							class LstSelect : public YangList
							{
							public:
								// Item IDs
								enum : uint32_t
								{
								};

								LstSelect(uint32_t id);
								~LstSelect();

								YangResult_E initialise(void);

							}; // LstSelect

							// -----------------------------------------------------------------------------
							// List:        /netconf-state/datastores/datastore/locks/lock-type[partial-lock]/partial-lock/locked-node
							// Description: The list of instance-identifiers (i.e., the
							//              locked nodes).
							//              The scope of the partial lock is defined by the list
							//              of locked nodes.
							// -----------------------------------------------------------------------------
							class LstLockedNode : public YangList
							{
							public:
								// Item IDs
								enum : uint32_t
								{
								};

								LstLockedNode(uint32_t id);
								~LstLockedNode();

								YangResult_E initialise(void);

							}; // LstLockedNode

						}; // LstPartialLock

					}; // OptPartialLock

				}; // ChoiceLockType

			}; // CntLocks

		}; // LstDatastore

	}; // CntDatastores

	// -----------------------------------------------------------------------------
	// Container:   /netconf-state/schemas
	// Description: Contains the list of data model schemas supported by the
	//              server.
	// -----------------------------------------------------------------------------
	class CntSchemas : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_SCHEMA,  // LstSchema
		};

		CntSchemas(uint32_t id);
		~CntSchemas();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// List:        /netconf-state/schemas/schema
		// Description: List of data model schemas supported by the server.
		// -----------------------------------------------------------------------------
		class LstSchema : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_IDENTIFIER,  // LeafIdentifier
				ITEM_VERSION,  // LeafVersion
				ITEM_FORMAT,  // LeafFormat
				ITEM_NAMESPACE,  // LeafNamespace
				ITEM_LOCATION,  // LstLocation
			};

			LstSchema(uint32_t id);
			~LstSchema();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /netconf-state/schemas/schema/identifier
			// Description: Identifier to uniquely reference the schema.  The
			//              identifier is used in the <get-schema> operation and may
			//              be used for other purposes such as file retrieval.
			//              For modeling languages that support or require a data
			//              model name (e.g., YANG module name) the identifier MUST
			//              match that name.  For YANG data models, the identifier is
			//              the name of the module or submodule.  In other cases, an
			//              identifier such as a filename MAY be used instead.
			// -----------------------------------------------------------------------------
			class LeafIdentifier : public YangLeaf
			{
			public:

				LeafIdentifier(uint32_t id);
				~LeafIdentifier();

			}; // LeafIdentifier

			// -----------------------------------------------------------------------------
			// Leaf:        /netconf-state/schemas/schema/version
			// Description: Version of the schema supported.  Multiple versions MAY be
			//              supported simultaneously by a NETCONF server.  Each
			//              version MUST be reported individually in the schema list,
			//              i.e., with same identifier, possibly different location,
			//              but different version.
			//              For YANG data models, version is the value of the most
			//              recent YANG 'revision' statement in the module or
			//              submodule, or the empty string if no 'revision' statement
			//              is present.
			// -----------------------------------------------------------------------------
			class LeafVersion : public YangLeaf
			{
			public:

				LeafVersion(uint32_t id);
				~LeafVersion();

			}; // LeafVersion

			// -----------------------------------------------------------------------------
			// Leaf:        /netconf-state/schemas/schema/format
			// Description: The data modeling language the schema is written
			//              in (currently xsd, yang, yin, rng, or rnc).
			//              For YANG data models, 'yang' format MUST be supported and
			//              'yin' format MAY also be provided.
			// -----------------------------------------------------------------------------
			class LeafFormat : public YangLeaf
			{
			public:

				LeafFormat(uint32_t id);
				~LeafFormat();

			}; // LeafFormat

			// -----------------------------------------------------------------------------
			// Leaf:        /netconf-state/schemas/schema/namespace
			// Description: The XML namespace defined by the data model.
			//              For YANG data models, this is the module's namespace.
			//              If the list entry describes a submodule, this field
			//              contains the namespace of the module to which the
			//              submodule belongs.
			// -----------------------------------------------------------------------------
			class LeafNamespace : public YangLeaf
			{
			public:

				LeafNamespace(uint32_t id);
				~LeafNamespace();

			}; // LeafNamespace

			// -----------------------------------------------------------------------------
			// List:        /netconf-state/schemas/schema/location
			// Description: One or more locations from which the schema can be
			//              retrieved.  This list SHOULD contain at least one
			//              entry per schema.
			//              A schema entry may be located on a remote file system
			//              (e.g., reference to file system for ftp retrieval) or
			//              retrieved directly from a server supporting the
			//              <get-schema> operation (denoted by the value 'NETCONF').
			// -----------------------------------------------------------------------------
			class LstLocation : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
				};

				LstLocation(uint32_t id);
				~LstLocation();

				YangResult_E initialise(void);

			}; // LstLocation

		}; // LstSchema

	}; // CntSchemas

	// -----------------------------------------------------------------------------
	// Container:   /netconf-state/sessions
	// Description: The sessions container includes session-specific data for
	//              NETCONF management sessions.  The session list MUST include
	//              all currently active NETCONF sessions.
	// -----------------------------------------------------------------------------
	class CntSessions : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_SESSION,  // LstSession
		};

		CntSessions(uint32_t id);
		~CntSessions();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// List:        /netconf-state/sessions/session
		// Description: All NETCONF sessions managed by the NETCONF server
		//              MUST be reported in this list.
		// -----------------------------------------------------------------------------
		class LstSession : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_SESSION_ID,  // LeafSessionId
				ITEM_TRANSPORT,  // LeafTransport
				ITEM_USERNAME,  // LeafUsername
				ITEM_SOURCE_HOST,  // LeafSourceHost
				ITEM_LOGIN_TIME,  // LeafLoginTime
				ITEM_COMMON_COUNTERS,  // Use GrpCommonCounters
			};

			LstSession(uint32_t id);
			~LstSession();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /netconf-state/sessions/session/session-id
			// Description: Unique identifier for the session.  This value is the
			//              NETCONF session identifier, as defined in RFC 4741.
			// -----------------------------------------------------------------------------
			class LeafSessionId : public YangLeaf
			{
			public:

				LeafSessionId(uint32_t id);
				~LeafSessionId();

			}; // LeafSessionId

			// -----------------------------------------------------------------------------
			// Leaf:        /netconf-state/sessions/session/transport
			// Description: Identifies the transport for each session, e.g.,
			//              'netconf-ssh', 'netconf-soap', etc.
			// -----------------------------------------------------------------------------
			class LeafTransport : public YangLeaf
			{
			public:

				LeafTransport(uint32_t id);
				~LeafTransport();

			}; // LeafTransport

			// -----------------------------------------------------------------------------
			// Leaf:        /netconf-state/sessions/session/username
			// Description: The username is the client identity that was authenticated
			//              by the NETCONF transport protocol.  The algorithm used to
			//              derive the username is NETCONF transport protocol specific
			//              and in addition specific to the authentication mechanism
			//              used by the NETCONF transport protocol.
			// -----------------------------------------------------------------------------
			class LeafUsername : public YangLeaf
			{
			public:

				LeafUsername(uint32_t id);
				~LeafUsername();

			}; // LeafUsername

			// -----------------------------------------------------------------------------
			// Leaf:        /netconf-state/sessions/session/source-host
			// Description: Host identifier of the NETCONF client.  The value
			//              returned is implementation specific (e.g., hostname,
			//              IPv4 address, IPv6 address)
			// -----------------------------------------------------------------------------
			class LeafSourceHost : public YangLeaf
			{
			public:

				LeafSourceHost(uint32_t id);
				~LeafSourceHost();

			}; // LeafSourceHost

			// -----------------------------------------------------------------------------
			// Leaf:        /netconf-state/sessions/session/login-time
			// Description: Time at the server at which the session was established.
			// -----------------------------------------------------------------------------
			class LeafLoginTime : public YangLeaf
			{
			public:

				LeafLoginTime(uint32_t id);
				~LeafLoginTime();

			}; // LeafLoginTime

		}; // LstSession

	}; // CntSessions

	// -----------------------------------------------------------------------------
	// Container:   /netconf-state/statistics
	// Description: Statistical data pertaining to the NETCONF server.
	// -----------------------------------------------------------------------------
	class CntStatistics : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_NETCONF_START_TIME,  // LeafNetconfStartTime
			ITEM_IN_BAD_HELLOS,  // LeafInBadHellos
			ITEM_IN_SESSIONS,  // LeafInSessions
			ITEM_DROPPED_SESSIONS,  // LeafDroppedSessions
			ITEM_COMMON_COUNTERS,  // Use GrpCommonCounters
		};

		CntStatistics(uint32_t id);
		~CntStatistics();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /netconf-state/statistics/netconf-start-time
		// Description: Date and time at which the management subsystem was
		//              started.
		// -----------------------------------------------------------------------------
		class LeafNetconfStartTime : public YangLeaf
		{
		public:

			LeafNetconfStartTime(uint32_t id);
			~LeafNetconfStartTime();

		}; // LeafNetconfStartTime

		// -----------------------------------------------------------------------------
		// Leaf:        /netconf-state/statistics/in-bad-hellos
		// Description: Number of sessions silently dropped because an
		//              invalid <hello> message was received.  This includes <hello>
		//              messages with a 'session-id' attribute, bad namespace, and
		//              bad capability declarations.
		// -----------------------------------------------------------------------------
		class LeafInBadHellos : public YangLeaf
		{
		public:

			LeafInBadHellos(uint32_t id);
			~LeafInBadHellos();

		}; // LeafInBadHellos

		// -----------------------------------------------------------------------------
		// Leaf:        /netconf-state/statistics/in-sessions
		// Description: Number of sessions started.  This counter is incremented
		//              when a <hello> message with a <session-id> is sent.
		//              'in-sessions' - 'in-bad-hellos' =
		//                 'number of correctly started netconf sessions'
		// -----------------------------------------------------------------------------
		class LeafInSessions : public YangLeaf
		{
		public:

			LeafInSessions(uint32_t id);
			~LeafInSessions();

		}; // LeafInSessions

		// -----------------------------------------------------------------------------
		// Leaf:        /netconf-state/statistics/dropped-sessions
		// Description: Number of sessions that were abnormally terminated, e.g.,
		//              due to idle timeout or transport close.  This counter is not
		//              incremented when a session is properly closed by a
		//              <close-session> operation, or killed by a <kill-session>
		//              operation.
		// -----------------------------------------------------------------------------
		class LeafDroppedSessions : public YangLeaf
		{
		public:

			LeafDroppedSessions(uint32_t id);
			~LeafDroppedSessions();

		}; // LeafDroppedSessions

	}; // CntStatistics

}; // CntNetconfState


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /common-counters
// Description: Counters that exist both per session, and also globally,
//              accumulated from all sessions.
// -----------------------------------------------------------------------------
class GrpCommonCounters : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_IN_RPCS,  // LeafInRpcs
		ITEM_IN_BAD_RPCS,  // LeafInBadRpcs
		ITEM_OUT_RPC_ERRORS,  // LeafOutRpcErrors
		ITEM_OUT_NOTIFICATIONS,  // LeafOutNotifications
	};

	GrpCommonCounters(uint32_t id);
	~GrpCommonCounters();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /common-counters/in-rpcs
	// Description: Number of correct <rpc> messages received.
	// -----------------------------------------------------------------------------
	class LeafInRpcs : public YangLeaf
	{
	public:

		LeafInRpcs(uint32_t id);
		~LeafInRpcs();

	}; // LeafInRpcs

	// -----------------------------------------------------------------------------
	// Leaf:        /common-counters/in-bad-rpcs
	// Description: Number of messages received when an <rpc> message was expected,
	//              that were not correct <rpc> messages.  This includes XML parse
	//              errors and errors on the rpc layer.
	// -----------------------------------------------------------------------------
	class LeafInBadRpcs : public YangLeaf
	{
	public:

		LeafInBadRpcs(uint32_t id);
		~LeafInBadRpcs();

	}; // LeafInBadRpcs

	// -----------------------------------------------------------------------------
	// Leaf:        /common-counters/out-rpc-errors
	// Description: Number of <rpc-reply> messages sent that contained an
	//              <rpc-error> element.
	// -----------------------------------------------------------------------------
	class LeafOutRpcErrors : public YangLeaf
	{
	public:

		LeafOutRpcErrors(uint32_t id);
		~LeafOutRpcErrors();

	}; // LeafOutRpcErrors

	// -----------------------------------------------------------------------------
	// Leaf:        /common-counters/out-notifications
	// Description: Number of <notification> messages sent.
	// -----------------------------------------------------------------------------
	class LeafOutNotifications : public YangLeaf
	{
	public:

		LeafOutNotifications(uint32_t id);
		~LeafOutNotifications();

	}; // LeafOutNotifications

}; // GrpCommonCounters


// *****************************************************************************
// Lists
// *****************************************************************************

// *****************************************************************************
// Choices
// *****************************************************************************

// *****************************************************************************
// Notifications
// *****************************************************************************

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      ietf-netconf-monitoring
// Description: NETCONF Monitoring Module.
//              All elements in this module are read-only.
//              Copyright (c) 2010 IETF Trust and the persons identified as
//              authors of the code. All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD
//              License set forth in Section 4.c of the IETF Trust's
//              Legal Provisions Relating to IETF Documents
//              (http://trustee.ietf.org/license-info).
//              This version of this YANG module is part of RFC 6022; see
//              the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
class ModuleIetfNetconfMonitoring : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_NETCONF_STATE,  // CntNetconfState
	};

	ModuleIetfNetconfMonitoring(uint32_t id);
	~ModuleIetfNetconfMonitoring();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleIetfNetconfMonitoring_NS */

} /* namespace Mplane */

#endif /* _MODULE_IETF_NETCONF_MONITORING_H_ */
