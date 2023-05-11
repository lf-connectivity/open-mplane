#ifndef _MODULE_IETF_IP_H_
#define _MODULE_IETF_IP_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfIp.h
 * \brief     Module IetfIp interface
 *
 *
 * \details   This file defines the YANG module ietf-ip interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-ip"
 *            YANG Filename:    "ietf-ip.yang"
 *            Module Prefix:    "ip"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-ip"
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

// Module:   ietf-interfaces
// Revision:
// Notes:
#include "YangModuleIetfInterfaces.h"

// Module:   ietf-inet-types
// Revision:
// Notes:
#include "YangModuleIetfInetTypes.h"

// Module:   ietf-yang-types
// Revision:
// Notes:
#include "YangModuleIetfYangTypes.h"


namespace Mplane {

namespace ModuleIetfIp_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// The origin of an address.
enum class IpAddressOrigin_E : uint32_t {
  OTHER, // None of the following.
  STATIC, // Indicates that the address has been statically
          // configured -- for example, using the Network Configuration
          // Protocol (NETCONF) or a command line interface.
  DHCP, // Indicates an address that has been assigned to this
        // system by a DHCP server.
  LINK_LAYER, // Indicates an address created by IPv6 stateless
              // autoconfiguration that embeds a link-layer address in its
              // interface identifier.
  RANDOM, // Indicates an address chosen by the system at
          // random, e.g., an IPv4 address within 169.254/16, a
          // temporary address as described in RFC 4941, or a
          // semantically opaque address as described in RFC 7217.

  Num_IpAddressOrigin_E
};

// The origin of a neighbor entry.
enum class NeighborOrigin_E : uint32_t {
  OTHER, // None of the following.
  STATIC, // Indicates that the mapping has been statically
          // configured -- for example, using NETCONF or a command line
          // interface.
  DYNAMIC, // Indicates that the mapping has been dynamically resolved
           // using, for example, IPv4 ARP or the IPv6 Neighbor
           // Discovery protocol.

  Num_NeighborOrigin_E
};

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: Indicates support for configuring non-contiguous
//              subnet masks.
// -----------------------------------------------------------------------------
class FeatureIpv4NonContiguousNetmasks : public YangFeature
{
public:
 FeatureIpv4NonContiguousNetmasks(uint32_t id);
 ~FeatureIpv4NonContiguousNetmasks();

}; // FeatureIpv4NonContiguousNetmasks

// -----------------------------------------------------------------------------
// Feature
// Description: Indicates support for privacy extensions for stateless address
//              autoconfiguration in IPv6.
// -----------------------------------------------------------------------------
class FeatureIpv6PrivacyAutoconf : public YangFeature
{
public:
 FeatureIpv6PrivacyAutoconf(uint32_t id);
 ~FeatureIpv6PrivacyAutoconf();

}; // FeatureIpv6PrivacyAutoconf


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
// Module:      ietf-ip
// Description: This module contains a collection of YANG definitions for
//              managing IP implementations.
//              Copyright (c) 2018 IETF Trust and the persons identified as
//              authors of the code.  All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD License
//              set forth in Section 4.c of the IETF Trust's Legal Provisions
//              Relating to IETF Documents
//              (https://trustee.ietf.org/license-info).
//              This version of this YANG module is part of RFC 8344; see
//              the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
class ModuleIetfIp : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_IPV4_NON_CONTIGUOUS_NETMASKS, // Feature
   ITEM_IPV6_PRIVACY_AUTOCONF, // Feature
 };

 ModuleIetfIp(uint32_t id);
 ~ModuleIetfIp();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleIetfIp_NS */

} /* namespace Mplane */

#endif /* _MODULE_IETF_IP_H_ */
