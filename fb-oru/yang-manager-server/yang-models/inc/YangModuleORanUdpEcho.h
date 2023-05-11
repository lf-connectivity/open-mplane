#ifndef _MODULE_O_RAN_UDP_ECHO_H_
#define _MODULE_O_RAN_UDP_ECHO_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanUdpEcho.h
 * \brief     Module ORanUdpEcho interface
 *
 *
 * \details   This file defines the YANG module o-ran-udp-echo interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-udp-echo"
 *            YANG Filename:    "o-ran-udp-echo.yang"
 *            Module Prefix:    "o-ran-echo"
 *            Module namespace: "urn:o-ran:udpecho:1.0"
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

// Module:   o-ran-interfaces
// Revision:
// Notes:
#include "YangModuleORanInterfaces.h"


namespace Mplane {

namespace ModuleORanUdpEcho_NS {

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
// Container:   /udp-echo
// Description: container for udp echo
// -----------------------------------------------------------------------------
class CntUdpEcho : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_UDP_ECHO_GROUP,  // Use GrpUdpEchoGroup
	};

	CntUdpEcho(uint32_t id);
	~CntUdpEcho();

	YangResult_E initialise(void);

}; // CntUdpEcho


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /udp-echo-group
// Description:
// -----------------------------------------------------------------------------
class GrpUdpEchoGroup : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_ENABLE_UDP_ECHO,  // LeafEnableUdpEcho
		ITEM_DSCP_CONFIG,  // LeafDscpConfig
		ITEM_ECHO_REPLIES_TRANSMITTED,  // LeafEchoRepliesTransmitted
	};

	GrpUdpEchoGroup(uint32_t id);
	~GrpUdpEchoGroup();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /udp-echo-group/enable-udp-echo
	// Description: whether O-RU's UDP ech server is enabled
	// -----------------------------------------------------------------------------
	class LeafEnableUdpEcho : public YangLeaf
	{
	public:

		LeafEnableUdpEcho(uint32_t id);
		~LeafEnableUdpEcho();

	}; // LeafEnableUdpEcho

	// -----------------------------------------------------------------------------
	// Leaf:        /udp-echo-group/dscp-config
	// Description: configuration of UDP echo DSCP
	// -----------------------------------------------------------------------------
	class LeafDscpConfig : public YangLeaf
	{
	public:

		// configuration of UDP echo DSCP
		enum class DscpConfig_E : uint32_t
		{
			REFLECTIVE,	// DSCP in echoed datagrams is copied from received datagram
			EF,	// DSCP in echoed datagrams is always be set to expeditied
					// forwarding Per Hop Behaviour.

			Num_DscpConfig_E
		};

		LeafDscpConfig(uint32_t id);
		~LeafDscpConfig();

	}; // LeafDscpConfig

	// -----------------------------------------------------------------------------
	// Leaf:        /udp-echo-group/echo-replies-transmitted
	// Description: The total number of UDP echo replies transmitted by the O-RU.
	// -----------------------------------------------------------------------------
	class LeafEchoRepliesTransmitted : public YangLeaf
	{
	public:

		LeafEchoRepliesTransmitted(uint32_t id);
		~LeafEchoRepliesTransmitted();

	}; // LeafEchoRepliesTransmitted

}; // GrpUdpEchoGroup


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
// Module:      o-ran-udp-echo
// Description: This module covers off aspects of interface transport
//              verification for UDP/IP based C/U plane connections based on UDP Echo.
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
class ModuleORanUdpEcho : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_UDP_ECHO,  // CntUdpEcho
	};

	ModuleORanUdpEcho(uint32_t id);
	~ModuleORanUdpEcho();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanUdpEcho_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_UDP_ECHO_H_ */
