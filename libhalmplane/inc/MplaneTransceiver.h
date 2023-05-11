/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_TRANSCEIVER_H__
#define __MPLANE_TRANSCEIVER_H__

typedef struct leafref_s {
  char* path;
  void* value;
} leafref_t;

typedef struct additional_multi_lane_reporting_s {
  uint8_t lane;
  uint64_t rx_power;
  uint64_t tx_bias_current;
  uint64_t tx_power;
} additional_multi_lane_reporting_t;

typedef struct port_transceivers_s {
  // o_ran_interfaces:port_number port_number; // ?? more ?? no definition
  char* name;
  bool present;
  char* vendor_id;
  char* vendor_part;
  char* vendor_rev;
  char* serial_no;
  /* no definition
  sff8472_compliance_code_t SFF8472_compliance_code; no definition
  connector_type_t connector_type;
  rx_power_type_t rx_power_type:
  identifier_t identifier;
  */
  uint32_t nominal_bitrate;
  uint8_t low_bitrate_margin;
  uint8_t high_bitrate_margin;
  uint64_t rx_power;
  uint64_t tx_power;
  uint64_t tx_bias_current;
  uint64_t voltage;
  uint64_t temperature;
  additional_multi_lane_reporting_t multi_lane;
} port_transceivers_t;

/**
 * Get port transceivers for the specified port_number from HAL
 * Returns 0 if successfull else error code.
 */
int halmplane_get_port_transceivers(port_transceivers_t* transceivers);

#endif //__MPLANE_TRANSCEIVER_H__
