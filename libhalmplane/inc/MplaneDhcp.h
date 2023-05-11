/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_DHCP_H__
#define __MPLANE_DHCP_H__

#include <stdbool.h>
#include <stdint.h>

typedef enum protocol_e {
  // TODO
} protocol_t;

typedef struct ca_ra_servers_s {
  // ca_ra_server_id servers; no definition
  // ietf_inet_types:port_number port_number; no definition
  char* ca_ra_path;
  char* subject_name;
  protocol_t protocol;
} ca_ra_servers_t;

typedef struct segw_s {
  uint32_t gateways;
} segw_t;

typedef struct netconf_clients_s {
  // netconf_client_id client;
  char* client; // Type - string or int ??
  // ietf_inet_types:port_number optional_port; no definition
} netconf_clients_t;

typedef struct dhcpv4_s {
  char* client_id;
  // ietf_inet_types:ip_address dhcp_server_identifier; no dedfinition
  char* domain_name;
  // ietf_inet_types:ip_address domain_name_servers; no definition
  uint32_t interface_mtu;
  // ietf_inet_types:ip_address default_gateways; no definition
  netconf_clients_t clients;
  ca_ra_servers_t ca_ra_servrs;
  segw_t dhcpv4_seg;
} dhcpv4_t;

typedef struct duid_llt_s {
  uint16_t duid_llt_hardware_type;
  // ietf_yang_types:timeticks duid_llt_time; no definition
  // ietf_yang_types:mac_address duid_llt_link_layer_addr; no definition
} duid_llt_t;

typedef struct duid_en_s {
  uint32_t duid_en_enterprise_number;
  char* duid_en_identifier;
} duid_en_t;

typedef struct duid_ll_s {
  uint16_t duid_ll_hardware_type;
  // ietf_yang_types:mac_address duid_ll_link_layer_addr; no definition
} duid_ll_t;

typedef struct duid_uuid_s {
  // ietf_yang_types:uuid uuid; no definition
} duid_uuid_t;

typedef struct duid_unknown_s {
  uint8_t* data; // hex dump
} duid_unknown_t;

typedef union duid_type_u {
  duid_llt_t llt;
  duid_en_t en;
  duid_ll_t ll;
  duid_uuid_t uuid;
  duid_unknown_t unknown;
} duid_type_t;

typedef struct dhcp_client_identifier_s {
  uint16_t type_code;
  duid_type_t duid_type;
} dhcp_client_identifier_t;

typedef struct dhcp_server_identifier_s {
  uint16_t type_code;
  duid_type_t duid_type;
} dhcp_server_identifier_t;

typedef struct dhcpv6_s {
  dhcp_client_identifier_t client_idntr;
  dhcp_server_identifier_t server_idntr;
  char* domain_name;
  // ietf_inet_types:ip_address domain_name_servers;  no definition
  netconf_clients_t clients;
  ca_ra_servers_t ca_ra_servrs;
  segw_t dhcpv6_seg;
} dhcpv6_t;

typedef struct m_plane_dhcp_s {
  uint32_t private_enterprise_num;
  char* vendor_class_data;
} m_plane_dhcp_t;

typedef struct dhcp_interfaces_s {
  // ietf_interfaces:interface_ref interface; no definition
  dhcpv4_t v4;
  dhcpv6_t v6;
} dhcp_interfaces_t;

typedef struct dhcp_s {
  dhcp_interfaces_t interface;
  m_plane_dhcp_t mplane_dhcp;
} dhcp_t;

#endif // __MPLANE_DHCP_H__
