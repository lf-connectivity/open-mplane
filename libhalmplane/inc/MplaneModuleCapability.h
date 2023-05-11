/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_MODULE_CAPABILITY_H__
#define __MPLANE_MODULE_CAPABILITY_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneTypes.h"

#define SUPPORT_FOR_DL_FIELDS          \
  uint64_t max_supported_frequency_dl; \
  uint64_t min_supported_frequency_dl; \
  uint64_t max_supported_bandwidth_dl; \
  uint32_t max_num_carriers_dl;        \
  uint64_t max_carrier_bandwidth_dl;   \
  uint64_t min_carrier_bandwidth_dl;

#define SUPPORT_FOR_UL_FIELDS          \
  uint64_t max_supported_frequency_ul; \
  uint64_t min_supported_frequency_ul; \
  uint64_t max_supported_bandwidth_ul; \
  uint32_t max_num_carriers_ul;        \
  uint64_t max_carrier_bandwidth_ul;   \
  uint64_t min_carrier_bandwidth_ul;

typedef struct compression_method_supported_s {
  compression_type_t compression_type;
  uint8_t bitwidth;
  compression_format_t compression_format;
} compression_method_supported_t;

typedef struct format_of_iq_sample_s {
  bool dynamic_compression_supported;
  bool realtime_variable_bit_width_supported;
  compression_method_supported_t comp_method;
  bool variable_bit_width_per_channel_supported;
  bool syminc_supported;
} format_of_iq_sample_t;

typedef enum ru_supported_category_e {
  CAT_A, // Precoding not supported
  CAT_B, // Supports precoding
} ru_supported_category_t;

typedef enum scs_config_type_e {
  KHZ_15 = 0,
  KHZ_30,
  KHZ_60,
  KHZ_120,
  KHZ_240,
  KHZ_1_25,
  KHZ_3_75,
  KHZ_5,
  KHZ_7_5,
} scs_config_type_t;

typedef struct ul_mixed_num_required_guard_rbs_s {
  scs_config_type_t scs_a;
  scs_config_type_t scs_b;
  uint8_t number_of_guard_rbs_ul;
} ul_mixed_num_required_guard_rbs_t;

typedef struct dl_mixed_num_required_guard_rbs_s {
  scs_config_type_t scs_a;
  scs_config_type_t scs_b;
  uint8_t number_of_guard_rbs_dl;
} dl_mixed_num_required_guard_rbs_t;

typedef struct ru_capabilities_s {
  ru_supported_category_t ru_supported_category;
  uint8_t number_of_ru_ports_ul;
  uint8_t number_of_ru_ports_dl;
  uint8_t number_of_spatial_streams;
  decimal64_t max_power_per_pa_antenna;
  decimal64_t min_power_per_pa_antenna;
  uint8_t fronthaul_split_option;
  format_of_iq_sample_t iq_sample;
  ul_mixed_num_required_guard_rbs_t* ul_mixed_num_required_guard_rbs;
  dl_mixed_num_required_guard_rbs_t* dl_mixed_num_required_guard_rbs;
  bool energy_saving_by_transmission_blanks;
  bool dynamic_transport_delay_management_supported;
} ru_capabilities_t;

typedef struct sub_band_frequency_ranges_s {
  char* sub_band;
  uint64_t max_supported_frequency_dl;
  uint64_t min_supported_frequency_dl;
} sub_band_frequency_ranges_t;

typedef struct rw_sub_band_info_s {
  sub_band_frequency_ranges_t freq_ranges;
  uint8_t number_of_laa_scarriers;
  uint16_t maximum_laa_buffer_size;
  uint16_t maximum_processing_time;
  bool self_configure;
} rw_sub_band_info_t;

typedef struct band_capabilities_s {
  uint16_t band_number;
  rw_sub_band_info_t sub_band;
  SUPPORT_FOR_DL_FIELDS
  SUPPORT_FOR_UL_FIELDS
  uint8_t max_num_component_carriers;
  uint16_t max_num_bands;
  uint8_t max_num_sectors;
  uint64_t max_power_per_antenna;
  uint64_t min_power_per_antenna;
  uint8_t codebook_configuration_ng;
  uint8_t codebook_configuration_n1;
  uint8_t codebook_configuration_n2;
} band_capabilities_t;

typedef struct module_capability_s {
  ru_capabilities_t ru_cap;
  band_capabilities_t* band_cap;
  rw_sub_band_info_t sub_band_info;
} module_capability_t;

int halmplane_setDUToRUModuleCapability(module_capability_t* mod_capability);

#endif //__MPLANE_MODULE_CAPABILITY_H__
