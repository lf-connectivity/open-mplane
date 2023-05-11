/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneUplaneConf.h"

low_level_tx_endpoint_t tx_endpoint_1{
    .name = "endpoint_1",
    .compression =
        {
            .iq_bitwidth = 14,
            .compression_type = compression_type_t::STATIC,
            .compression_format = c_type_t::BLOCK_FLOATING_POINT,
            .exponent = 8,
        },
    .frame_structure = 8,
    .cp_type = cp_type_t::NORMAL,
    .cp_length = 16,
    .cp_length_other = 16,
    .offset_to_absolute_frequency_center = 0,
    .number_of_prb_per_scs = 0,
    .e_axcid = {
        .o_du_port_bitmask = 0,
        .band_sector_bitmask = 0,
        .ccid_bitmask = 0,
        .ru_port_bitmask = 0,
        .eaxc_id = 0}};

low_level_tx_endpoint_t tx_endpoint_2{
    .name = "endpoint_2",
    .compression =
        {
            .iq_bitwidth = 14,
            .compression_type = compression_type_t::STATIC,
            .compression_format = c_type_t::BLOCK_FLOATING_POINT,
            .exponent = 8,
        },
    .frame_structure = 8,
    .cp_type = cp_type_t::NORMAL,
    .cp_length = 16,
    .cp_length_other = 16,
    .offset_to_absolute_frequency_center = 0,
    .number_of_prb_per_scs = 0,
    .e_axcid = {
        .o_du_port_bitmask = 0,
        .band_sector_bitmask = 0,
        .ccid_bitmask = 0,
        .ru_port_bitmask = 0,
        .eaxc_id = 0}};

low_level_tx_endpoint_t example_tx_endpoints[] = {tx_endpoint_1, tx_endpoint_2};

int
halmplane_setUPlaneConfiguration(user_plane_configuration_t* uplane_cfg) {
  return 0;
}

int
halmplane_get_tx_array(const char* name, tx_array_t* tx_arrays) {
  return 0;
}

int
halmplane_get_rx_array(const char* name, rx_array_t* rx_arrays) {
  return 0;
}

const char**
halmplane_get_tx_array_names() {
  return 0;
}

const char**
halmplane_get_rx_array_names() {
  return 0;
}

int
halmplane_get_low_level_tx_endpoint(
    const char* name, low_level_tx_endpoint_t* tx_endpoints) {
  return 0;
}

int
halmplane_get_low_level_rx_endpoint(
    const char* name, low_level_rx_endpoint_t* rx_endpoints) {
  return 0;
}

int
halmplane_get_low_level_tx_endpoints(
    low_level_tx_endpoint_t** tx_endpoints, int* n_endpoints) {
  *tx_endpoints = example_tx_endpoints;
  *n_endpoints = 2;
  return 0;
}

int
halmplane_get_low_level_rx_endpoints(
    low_level_rx_endpoint_t** rx_endpoints, int* n_endpoints) {
  return 0;
}

int
halmplane_tx_carrier_state_change(
    const char* name,
    uint64_t chbw,
    uint64_t center,
    double gain,
    const char* new_state,
    int do_apply) {
  return 0;
}

int
halmplane_rx_carrier_state_change(
    const char* name,
    uint64_t chbw,
    uint64_t center,
    double gain_correction,
    const char* new_state,
    int do_apply) {
  return 0;
}

int
halmplane_update_rx_eaxc(const char* endpoint_name, e_axcid_t* eaxc) {
  return 0;
}

int
halmplane_update_tx_eaxc(const char* endpoint_name, e_axcid_t* eaxc) {
  return 0;
}

int
halmplane_update_rx_endpoint_compression(
    const char* endpoint_name, compression_t* compression) {
  return 0;
}

int
halmplane_update_tx_endpoint_compression(
    const char* endpoint_name, compression_t* compression) {
  return 0;
}

int
halmplane_update_rx_endpoint_compression_dyn_config(
    const char* endpoint_name, dynamic_compression_configuration_t* config) {
  return 0;
}

int
halmplane_update_tx_endpoint_compression_dyn_config(
    const char* endpoint_name, dynamic_compression_configuration_t* config) {
  return 0;
}

int
halmplane_register_rx_carrier_state_cb(halmplane_carrier_state_cb_t cb) {
  return 0;
}

int
halmplane_register_tx_carrier_state_cb(halmplane_carrier_state_cb_t cb) {
  return 0;
}
