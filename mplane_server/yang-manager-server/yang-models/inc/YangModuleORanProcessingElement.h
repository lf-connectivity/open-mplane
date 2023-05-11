#ifndef _MODULE_O_RAN_PROCESSING_ELEMENT_H_
#define _MODULE_O_RAN_PROCESSING_ELEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanProcessingElement.h
 * \brief     Module ORanProcessingElement interface
 *
 *
 * \details   This file defines the YANG module o-ran-processing-element
 interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-processing-element"
 *            YANG Filename:    "o-ran-processing-element.yang"
 *            Module Prefix:    "o-ran-elements"
 *            Module namespace: "urn:o-ran:processing-element:1.0"
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

// Module:   ietf-interfaces
// Revision:
// Notes:
#include "YangModuleIetfInterfaces.h"

// Module:   ietf-ip
// Revision:
// Notes:
#include "YangModuleIetfIp.h"

// Module:   o-ran-interfaces
// Revision:
// Notes:
#include "YangModuleORanInterfaces.h"


namespace Mplane {

namespace ModuleORanProcessingElement_NS {

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
// Container:   /processing-elements
// Description: a model defining the mapping between transport flows and arbitrary
//              O-RAN processing elements. A processing element may be then defined for
//              handling connectivity or delay procedures, or defined with a corresponding
//              eaxcid for CU plane operations
// -----------------------------------------------------------------------------
class CntProcessingElements : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_PE_GROUP, // Use GrpPeGroup
 };

 CntProcessingElements(uint32_t id);
 ~CntProcessingElements();

 YangResult_E initialise(void);

}; // CntProcessingElements


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /pe-group
// Description:
// -----------------------------------------------------------------------------
class GrpPeGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_MAXIMUM_NUMBER_OF_TRANSPORT_FLOWS, // LeafMaximumNumberOfTransportFlows
   ITEM_TRANSPORT_SESSION_TYPE, // LeafTransportSessionType
   ITEM_ENHANCED_UPLANE_MAPPING, // CntEnhancedUplaneMapping
   ITEM_RU_ELEMENTS, // LstRuElements
 };

 GrpPeGroup(uint32_t id);
 ~GrpPeGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /pe-group/maximum-number-of-transport-flows
 // Description: The maximum number of transport flows that can be supported by
 // an O-RU
 // -----------------------------------------------------------------------------
 class LeafMaximumNumberOfTransportFlows : public YangLeaf {
  public:
   LeafMaximumNumberOfTransportFlows(uint32_t id);
   ~LeafMaximumNumberOfTransportFlows();

 }; // LeafMaximumNumberOfTransportFlows

 // -----------------------------------------------------------------------------
 // Leaf:        /pe-group/transport-session-type
 // Description: the type of transport session used for identifying different
 // processing
 //              elements
 // -----------------------------------------------------------------------------
 class LeafTransportSessionType : public YangLeaf {
  public:
   // the type of transport session used for identifying different processing
   // elements
   enum class TransportSessionType_E : uint32_t {
     ETH_INTERFACE, // VLAN based CUS Transport
     UDPIP_INTERFACE, // UDP/IP based CUS Transport
     ALIASMAC_INTERFACE, // Alias MAC address based CUS Transport

     Num_TransportSessionType_E
   };

   LeafTransportSessionType(uint32_t id);
   ~LeafTransportSessionType();

 }; // LeafTransportSessionType

 // -----------------------------------------------------------------------------
 // Container:   /pe-group/enhanced-uplane-mapping
 // Description: a mapping table for enhanced user plane marking
 // -----------------------------------------------------------------------------
 class CntEnhancedUplaneMapping : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_UPLANE_MAPPING, // LstUplaneMapping
   };

   CntEnhancedUplaneMapping(uint32_t id);
   ~CntEnhancedUplaneMapping();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // List:        /pe-group/enhanced-uplane-mapping/uplane-mapping
   // Description: a mapping between up-link name and
   // o-ran-interfaces:up-marking-name
   // -----------------------------------------------------------------------------
   class LstUplaneMapping : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_UP_MARKING_NAME, // LeafUpMarkingName
       ITEM_UP_MARKINGS, // ChoiceUpMarkings
     };

     LstUplaneMapping(uint32_t id);
     ~LstUplaneMapping();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-marking-name
     // Description: a unique up marking name that is used for enhanced
     // up marking
     // -----------------------------------------------------------------------------
     class LeafUpMarkingName : public YangLeaf {
      public:
       LeafUpMarkingName(uint32_t id);
       ~LeafUpMarkingName();

     }; // LeafUpMarkingName

     // -----------------------------------------------------------------------------
     // Choice:
     // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings
     // Description: U-Plane markings
     // -----------------------------------------------------------------------------
     class ChoiceUpMarkings : public YangChoice {
      public:
       // Choice Option
       enum : uint32_t {
         ITEM_ETHERNET, // OptEthernet
         ITEM_IPV4, // OptIpv4
         ITEM_IPV6, // OptIpv6
       };

       ChoiceUpMarkings(uint32_t id);
       ~ChoiceUpMarkings();

       YangResult_E initialise(void);

       // -----------------------------------------------------------------------------
       // Option:
       // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ethernet]
       // -----------------------------------------------------------------------------
       class OptEthernet : public YangChoiceOption {
        public:
         // Item IDs
         enum : uint32_t {
           ITEM_UP_COS_NAME, // RefUpCosName
         };

         OptEthernet(uint32_t id);
         ~OptEthernet();

         YangResult_E initialise(void);

         // -----------------------------------------------------------------------------
         // Reference:
         // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ethernet]/up-cos-name
         // Description: the Ethernet U-plane transport
         // marking as defined in o-ran-interfaces
         // -----------------------------------------------------------------------------
         class RefUpCosName : public YangReference {
          public:
           RefUpCosName(uint32_t id);
           ~RefUpCosName();

         }; // RefUpCosName

       }; // OptEthernet

       // -----------------------------------------------------------------------------
       // Option:
       // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ipv4]
       // -----------------------------------------------------------------------------
       class OptIpv4 : public YangChoiceOption {
        public:
         // Item IDs
         enum : uint32_t {
           ITEM_UPV4_DSCP_NAME, // RefUpv4DscpName
         };

         OptIpv4(uint32_t id);
         ~OptIpv4();

         YangResult_E initialise(void);

         // -----------------------------------------------------------------------------
         // Reference:
         // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ipv4]/upv4-dscp-name
         // Description: the IPv4 U-plane transport marking as
         // defined in o-ran-interfaces
         // -----------------------------------------------------------------------------
         class RefUpv4DscpName : public YangReference {
          public:
           RefUpv4DscpName(uint32_t id);
           ~RefUpv4DscpName();

         }; // RefUpv4DscpName

       }; // OptIpv4

       // -----------------------------------------------------------------------------
       // Option:
       // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ipv6]
       // -----------------------------------------------------------------------------
       class OptIpv6 : public YangChoiceOption {
        public:
         // Item IDs
         enum : uint32_t {
           ITEM_UPV6_DSCP_NAME, // RefUpv6DscpName
         };

         OptIpv6(uint32_t id);
         ~OptIpv6();

         YangResult_E initialise(void);

         // -----------------------------------------------------------------------------
         // Reference:
         // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ipv6]/upv6-dscp-name
         // Description: the IPv6 U-plane transport marking as defined in
         // o-ran-interfaces
         // -----------------------------------------------------------------------------
         class RefUpv6DscpName : public YangReference {
          public:
           RefUpv6DscpName(uint32_t id);
           ~RefUpv6DscpName();

         }; // RefUpv6DscpName

       }; // OptIpv6

     }; // ChoiceUpMarkings

   }; // LstUplaneMapping

 }; // CntEnhancedUplaneMapping

 // -----------------------------------------------------------------------------
 // List:        /pe-group/ru-elements
 // Description: the list of transport definitions for each processing
 // element
 // -----------------------------------------------------------------------------
 class LstRuElements : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_TRANSPORT_FLOW, // CntTransportFlow
   };

   LstRuElements(uint32_t id);
   ~LstRuElements();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /pe-group/ru-elements/name
   // Description: A name that is unique across the O-RU that
   // identifies a processing
   //              element instance.
   //
   //              This name may be used in fault management to
   //              refer to a fault source or affected object
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Container:   /pe-group/ru-elements/transport-flow
   // Description: container for the transport-flow used for CU
   // plane
   // -----------------------------------------------------------------------------
   class CntTransportFlow : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_INTERFACE_NAME, // RefInterfaceName
       ITEM_ALIASMAC_FLOW, // CntAliasmacFlow
       ITEM_ETH_FLOW, // CntEthFlow
       ITEM_UDPIP_FLOW, // CntUdpipFlow
     };

     CntTransportFlow(uint32_t id);
     ~CntTransportFlow();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Reference:
     // /pe-group/ru-elements/transport-flow/interface-name
     // Description: the interface name
     // -----------------------------------------------------------------------------
     class RefInterfaceName : public YangReference {
      public:
       RefInterfaceName(uint32_t id);
       ~RefInterfaceName();

     }; // RefInterfaceName

     // -----------------------------------------------------------------------------
     // Container:
     // /pe-group/ru-elements/transport-flow/aliasmac-flow
     // Description: leafs for virtual mac type data flows
     // -----------------------------------------------------------------------------
     class CntAliasmacFlow : public YangContainer {
      public:
       // Item IDs
       enum : uint32_t {
         ITEM_O_DU_MAC_ADDRESS, // LeafODuMacAddress
         ITEM_RU_ALIASMAC_ADDRESS, // RefRuAliasmacAddress
         ITEM_VLAN_ID, // RefVlanId
       };

       CntAliasmacFlow(uint32_t id);
       ~CntAliasmacFlow();

       YangResult_E initialise(void);

       // -----------------------------------------------------------------------------
       // Leaf:
       // /pe-group/ru-elements/transport-flow/aliasmac-flow/o-du-mac-address
       // Description: O-DU's MAC address used for alias MAC based
       // flow
       // -----------------------------------------------------------------------------
       class LeafODuMacAddress : public YangLeaf {
        public:
         LeafODuMacAddress(uint32_t id);
         ~LeafODuMacAddress();

       }; // LeafODuMacAddress

       // -----------------------------------------------------------------------------
       // Reference:
       // /pe-group/ru-elements/transport-flow/aliasmac-flow/ru-aliasmac-address
       // Description: O-RU's alias MAC address used for alias MAC
       // based flow
       // -----------------------------------------------------------------------------
       class RefRuAliasmacAddress : public YangReference {
        public:
         RefRuAliasmacAddress(uint32_t id);
         ~RefRuAliasmacAddress();

       }; // RefRuAliasmacAddress

       // -----------------------------------------------------------------------------
       // Reference:
       // /pe-group/ru-elements/transport-flow/aliasmac-flow/vlan-id
       // Description: O-RU's VLAN-ID used for alias MAC based flow
       // -----------------------------------------------------------------------------
       class RefVlanId : public YangReference {
        public:
         RefVlanId(uint32_t id);
         ~RefVlanId();

       }; // RefVlanId

     }; // CntAliasmacFlow

     // -----------------------------------------------------------------------------
     // Container:   /pe-group/ru-elements/transport-flow/eth-flow
     // Description: leafs for mac + vlan-id type data flows
     // -----------------------------------------------------------------------------
     class CntEthFlow : public YangContainer {
      public:
       // Item IDs
       enum : uint32_t {
         ITEM_O_DU_MAC_ADDRESS, // LeafODuMacAddress
         ITEM_RU_MAC_ADDRESS, // RefRuMacAddress
         ITEM_VLAN_ID, // RefVlanId
       };

       CntEthFlow(uint32_t id);
       ~CntEthFlow();

       YangResult_E initialise(void);

       // -----------------------------------------------------------------------------
       // Leaf:
       // /pe-group/ru-elements/transport-flow/eth-flow/o-du-mac-address
       // Description: O-DU's MAC address used for Ethernet based
       // flow
       // -----------------------------------------------------------------------------
       class LeafODuMacAddress : public YangLeaf {
        public:
         LeafODuMacAddress(uint32_t id);
         ~LeafODuMacAddress();

       }; // LeafODuMacAddress

       // -----------------------------------------------------------------------------
       // Reference:
       // /pe-group/ru-elements/transport-flow/eth-flow/ru-mac-address
       // Description: O-RU's MAC address used for Ethernet based
       // flow
       // -----------------------------------------------------------------------------
       class RefRuMacAddress : public YangReference {
        public:
         RefRuMacAddress(uint32_t id);
         ~RefRuMacAddress();

       }; // RefRuMacAddress

       // -----------------------------------------------------------------------------
       // Reference:
       // /pe-group/ru-elements/transport-flow/eth-flow/vlan-id
       // Description: O-RU's VLAN-ID used for Ethernet based flow
       // -----------------------------------------------------------------------------
       class RefVlanId : public YangReference {
        public:
         RefVlanId(uint32_t id);
         ~RefVlanId();

       }; // RefVlanId

     }; // CntEthFlow

     // -----------------------------------------------------------------------------
     // Container: /pe-group/ru-elements/transport-flow/udpip-flow
     // Description: leafs for UDP/IP type data flows
     // -----------------------------------------------------------------------------
     class CntUdpipFlow : public YangContainer {
      public:
       // Item IDs
       enum : uint32_t {
         ITEM_O_DU_IP_ADDRESS, // LeafODuIpAddress
         ITEM_RU_EPHEMERAL_UDP_PORT, // LeafRuEphemeralUdpPort
         ITEM_O_DU_EPHEMERAL_UDP_PORT, // LeafODuEphemeralUdpPort
         ITEM_ECPRI_DESTINATION_UDP, // LeafEcpriDestinationUdp
         ITEM_ADDRESS, // ChoiceAddress
       };

       CntUdpipFlow(uint32_t id);
       ~CntUdpipFlow();

       YangResult_E initialise(void);

       // -----------------------------------------------------------------------------
       // Leaf:
       // /pe-group/ru-elements/transport-flow/udpip-flow/o-du-ip-address
       // Description: O-DU's IPv address
       // -----------------------------------------------------------------------------
       class LeafODuIpAddress : public YangLeaf {
        public:
         LeafODuIpAddress(uint32_t id);
         ~LeafODuIpAddress();

       }; // LeafODuIpAddress

       // -----------------------------------------------------------------------------
       // Leaf:
       // /pe-group/ru-elements/transport-flow/udpip-flow/ru-ephemeral-udp-port
       // Description: ephemeral port used by O-RU
       // -----------------------------------------------------------------------------
       class LeafRuEphemeralUdpPort : public YangLeaf {
        public:
         LeafRuEphemeralUdpPort(uint32_t id);
         ~LeafRuEphemeralUdpPort();

       }; // LeafRuEphemeralUdpPort

       // -----------------------------------------------------------------------------
       // Leaf:
       // /pe-group/ru-elements/transport-flow/udpip-flow/o-du-ephemeral-udp-port
       // Description: ephemeral port used by O-DU
       // -----------------------------------------------------------------------------
       class LeafODuEphemeralUdpPort : public YangLeaf {
        public:
         LeafODuEphemeralUdpPort(uint32_t id);
         ~LeafODuEphemeralUdpPort();

       }; // LeafODuEphemeralUdpPort

       // -----------------------------------------------------------------------------
       // Leaf:
       // /pe-group/ru-elements/transport-flow/udpip-flow/ecpri-destination-udp
       // Description: the well known UDP port number used by eCPRI
       // -----------------------------------------------------------------------------
       class LeafEcpriDestinationUdp : public YangLeaf {
        public:
         LeafEcpriDestinationUdp(uint32_t id);
         ~LeafEcpriDestinationUdp();

       }; // LeafEcpriDestinationUdp

       // -----------------------------------------------------------------------------
       // Choice:
       // /pe-group/ru-elements/transport-flow/udpip-flow/address
       // Description: choice of O-RU IPv4 or IPv6 address
       // -----------------------------------------------------------------------------
       class ChoiceAddress : public YangChoice {
        public:
         // Choice Option
         enum : uint32_t {
           ITEM_RU_IPV4_ADDRESS, // OptRuIpv4Address
           ITEM_RU_IPV6_ADDRESS, // OptRuIpv6Address
         };

         ChoiceAddress(uint32_t id);
         ~ChoiceAddress();

         YangResult_E initialise(void);

         // -----------------------------------------------------------------------------
         // Option:
         // /pe-group/ru-elements/transport-flow/udpip-flow/address[ru-ipv4-address]
         // -----------------------------------------------------------------------------
         class OptRuIpv4Address : public YangChoiceOption {
          public:
           // Item IDs
           enum : uint32_t {
             ITEM_RU_IPV4_ADDRESS, // RefRuIpv4Address
           };

           OptRuIpv4Address(uint32_t id);
           ~OptRuIpv4Address();

           YangResult_E initialise(void);

           // -----------------------------------------------------------------------------
           // Reference:
           // /pe-group/ru-elements/transport-flow/udpip-flow/address[ru-ipv4-address]/ru-ipv4-address
           // Description: O-RU's IPv4 address
           // -----------------------------------------------------------------------------
           class RefRuIpv4Address : public YangReference {
            public:
             RefRuIpv4Address(uint32_t id);
             ~RefRuIpv4Address();

           }; // RefRuIpv4Address

         }; // OptRuIpv4Address

         // -----------------------------------------------------------------------------
         // Option:
         // /pe-group/ru-elements/transport-flow/udpip-flow/address[ru-ipv6-address]
         // -----------------------------------------------------------------------------
         class OptRuIpv6Address : public YangChoiceOption {
          public:
           // Item IDs
           enum : uint32_t {
             ITEM_RU_IPV6_ADDRESS, // RefRuIpv6Address
           };

           OptRuIpv6Address(uint32_t id);
           ~OptRuIpv6Address();

           YangResult_E initialise(void);

           // -----------------------------------------------------------------------------
           // Reference:
           // /pe-group/ru-elements/transport-flow/udpip-flow/address[ru-ipv6-address]/ru-ipv6-address
           // Description: O-RU's IPv6 address
           // -----------------------------------------------------------------------------
           class RefRuIpv6Address : public YangReference {
            public:
             RefRuIpv6Address(uint32_t id);
             ~RefRuIpv6Address();

           }; // RefRuIpv6Address

         }; // OptRuIpv6Address

       }; // ChoiceAddress

     }; // CntUdpipFlow

   }; // CntTransportFlow

 }; // LstRuElements

}; // GrpPeGroup


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
// Module:      o-ran-processing-element
// Description: This module defines the YANG definitions for mapping of
// transport flows to
//              processing elements. Three options are supported:
//              i) virtual MAC based mapping
//              ii) MAC addrress + VLAN-ID based mapping
//              iii) UDP/IP based mapping
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
class ModuleORanProcessingElement : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_PROCESSING_ELEMENTS, // CntProcessingElements
 };

 ModuleORanProcessingElement(uint32_t id);
 ~ModuleORanProcessingElement();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanProcessingElement_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_PROCESSING_ELEMENT_H_ */
