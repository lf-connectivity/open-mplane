/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_PROCESSING_ELEMENTS_H__
#define __MPLANE_PROCESSING_ELEMENTS_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneTypes.h"

typedef struct up_markings_ethernet_s {
  const char* up_cos_name;
} up_markings_ethernet_t;

typedef struct up_markings_ipv4_s {
  const char* upv4_dscp_name;
} up_markings_ipv4_t;

typedef struct up_markings_ipv6_s {
  const char* upv6_dscp_name;
} up_markings_ipv6_t;

typedef union up_markings_u {
  up_markings_ethernet_t ethernet;
  up_markings_ipv4_t ipv4;
  up_markings_ipv6_t ipv6;
} up_markings_t;

typedef struct uplane_mapping_s {
  const char* up_marking_name;
  up_markings_t up_markings;
} uplane_mapping_t;

typedef struct aliasmac_flow_s {
  /* no definition
  o_ran_interfaces:alias_macs ru_aliasmac_address;
  o_ran_interfaces:vlan_id vlan_id;
  ietf_yang_types:mac_address o_du_mac_address;
  */
} aliasmac_flow_t;

typedef struct eth_flow_s {
  const char* ru_mac_address;
  uint16_t vlan_id;
  const char* o_du_mac_address;
} eth_flow_t;

typedef struct ru_ipv4_address_s {
  // ru_ipv4_address; no definition  //
  // /ietf_interfaces:interfaces/ietf_interfaces:interface[ietf_interfaces:name
  // =
  // current()/../../interface_name]/ietf_ip:ipv4/ietf_ip:address/ietf_ip:ip</ru_ipv4_address>
} ru_ipv4_address_t;

typedef struct ru_ipv6_address_s {
  // ru_ipv6_address; no definition
  // //:interfaces/ietf_interfaces:interface[ietf_interfaces:name =
  // current()/../../interface_name]/ietf_ip:ipv6/ietf_ip:address/ietf_ip:ip</ru_ipv6_address>
} ru_ipv6_address_t;

typedef struct udpip_flow_s {
  /* no definition
  ru_ip_address_t address;
  ietf_inet_types:ip_address o_du_ip_address;
  ietf_inet_types:port_number ru_ephemeral_udp_port;
  ietf_inet_types:port_number o_du_ephemeral_udp_port;
  ietf_inet_types:port_number ecpri_destination_udp;
  */
} udpip_flow_t;

typedef struct transport_flow_s {
  const char* interface_name;
  aliasmac_flow_t amac_flow;
  eth_flow_t e_flow;
  udpip_flow_t u_flow;
} transport_flow_t;

typedef struct ru_elements_s {
  const char* name;
  transport_flow_t t_flow;
} ru_elements_t;

typedef enum transport_session_type_s {
  ETH_INTERFACE,
  UDPIP_INTERFACE,
  ALIASMAC_INTERFACE,
  SHARED_CELL_ETH_INTERFACE,
} transport_session_type_t;

typedef struct enhanced_uplane_mapping_s {
  up_markings_t markings;
  uplane_mapping_t mapping;
} enhanced_uplane_mapping_t;

typedef struct processing_elements_s {
  uint16_t maximum_number_of_transport_flows;
  transport_session_type_t transport_session_type;
  enhanced_uplane_mapping_t e_uplane_map;
  ru_elements_t ru_elems;
} processing_elements_t;

halmplane_error_t halmplane_update_ru_element(ru_elements_t* ru_element);

#endif // __MPLANE_PROCESSING_ELEMENTS_H__
