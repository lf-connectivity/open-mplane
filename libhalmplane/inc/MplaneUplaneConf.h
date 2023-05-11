/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_UPLANE_CONFIG_H__
#define __MPLANE_UPLANE_CONFIG_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneCompression.h"
#include "MplaneModuleCapability.h"
#include "MplaneProcessingElements.h"

#define COMMON_TXRX_ARRAY_FIELDS                                          \
  /* Name of the array */                                                 \
  char* name;                                                             \
  /* Number of rows array elements are shaped into (M) */                 \
  uint16_t number_of_rows;                                                \
  /* Number of columns array elements are shaped into (N) */              \
  uint16_t number_of_columns;                                             \
  /* Number of layers array elements are shaped into (Q) */               \
  uint8_t number_of_array_layers;                                         \
  /* Average horizontal distance between array element centers */         \
  int64_t horizontal_spacing;                                             \
  /* Average vertical distance between array element centers */           \
  int64_t vertical_spacing;                                               \
  /* Counter-clockwise rotation around z and y axis */                    \
  struct normal_vector_direction {                                        \
    /* Azimuth value increases from 0 to 90 as it moves from the z to y * \
     * axis" */                                                           \
    int64_t azimuth_angle;                                                \
    /* Azimuth value increases from 0 to 90 as it moves from the z to y * \
     * axis" */                                                           \
    int64_t zenith_angle;                                                 \
  };                                                                      \
  /* Coordinates of the leftmost bottom array element */                  \
  struct leftmost_bottom_array_element_position {                         \
    int64_t x;                                                            \
    int64_t y;                                                            \
    int64_t z;                                                            \
  };                                                                      \
  uint64_t p;                                                             \
  /* Polarisations the array supports */                                  \
  struct {                                                                \
    uint8_t p;                                                            \
    polarisation_type_t polarisation;                                     \
  } * polarisations;                                                      \
  /* Frequency band of the array */                                       \
  uint16_t band_number;

#define COMMON_ENDPOINT_FIELDS                                               \
  char* name;                                                                \
  compression_t compression;                                                 \
  /* Describes the LTE frame structure. The first nibble describes FFT size, \
   * the * second the carrier spacing and slots */                           \
  uint8_t frame_structure;                                                   \
  /* The type of the cyclic prefix */                                        \
  cp_type_t cp_type;                                                         \
  /* The length of the cyclic prefix */                                      \
  uint16_t cp_length;                                                        \
  /* Length of the cyclic prefix used for non-LTE non-NR purposes */         \
  uint16_t cp_length_other;                                                  \
  /* See freqOffset in CUS-Plane */                                          \
  int32_t offset_to_absolute_frequency_center;                               \
  /* List of configured scs */                                               \
  struct {                                                                   \
    scs_config_type_t scs;                                                   \
    uint16_t number_of_prb;                                                  \
  } * number_of_prb_per_scs;                                                 \
  /* Description of the local address of low-level TX/RX endpoints */        \
  struct {                                                                   \
    uint16_t o_du_port_bitmask;                                              \
    uint16_t band_sector_bitmask;                                            \
    uint16_t ccid_bitmask;                                                   \
    uint16_t ru_port_bitmask;                                                \
    uint16_t eaxc_id;                                                        \
  } e_axcid;

typedef enum c_type_e {
  NO_COMPRESSION,
  BLOCK_FLOATING_POINT,
  BLOCK_FLOATING_POINT_SRES,
  BLOCK_SCALING,
  U_LAW,
  MODULATION,
  MODULATION_COMPRESSION,
  MODULATION_COMPRESSION_SRES
} c_type_t;

typedef enum cp_type_e { NORMAL, EXTENDED } cp_type_t;

typedef enum carrier_active_e {
  INACTIVE,
  SLEEP,
  ACTIVE,
} carrier_active_t;

typedef enum carrier_state_e {
  DISABLED,
  BUSY,
  READY,
} carrier_state_t;

typedef enum carrier_type_e {
  NR,
  LTE,
  DSS_LTE_NR,
} carrier_type_t;

typedef enum duplex_scheme_e {
  TDD,
  FDD,
} duplex_scheme_t;

typedef struct lte_tdd_frame_s {
  /* no definition
  subframe_assignment_t subframe_assignment;
  special_subframe_pattern_t special_subframe_pattern;
  */
} lte_tdd_frame_t;

typedef struct max_cw_usage_counter_s {
  // enum PRIORITY priority; no definition
  uint8_t counter_value;
} max_cw_usage_counter_t;

typedef struct laa_carrier_configuration_s {
  int8_t ed_threshold_pdsch;
  int8_t ed_threshold_drs;
  uint8_t tx_antenna_ports;
  int8_t transmission_power_for_drs;
  // dmtc_period_t dmtc_period; no definition
  uint8_t dmtc_offset;
  uint16_t lbt_timer;
  max_cw_usage_counter_t usage_counter;
} laa_carrier_configuration_t;

typedef struct tx_array_carriers_s {
  char* name;
  uint32_t absolute_frequency_center;
  uint64_t center_of_channel_bandwidth;
  uint64_t channel_bandwidth;
  carrier_active_t active;
  carrier_state_t state;
  carrier_type_t type;
  duplex_scheme_t duplex_scheme;
  lte_tdd_frame_t tx_tdd_frame;
  laa_carrier_configuration_t laa_carrier_cfg;
  uint64_t gain;
  uint32_t downlink_radio_frame_offset;
  int16_t downlink_sfn_offset;
} tx_array_carriers_t;

typedef struct user_plane_compression_s {
  uint8_t iq_bitwidth;
  c_type_t c_type;
  compression_format_t c_format;
} user_plane_compression_t;

typedef struct number_of_prb_per_scs_s {
  scs_config_type_t scs;
  uint16_t number_of_prb;
} number_of_prb_per_scs_t;

typedef struct e_axcid_s {
  uint16_t o_du_port_bitmask;
  uint16_t band_sector_bitmask;
  uint16_t ccid_bitmask;
  uint16_t ru_port_bitmask;
  uint16_t eaxc_id;
} e_axcid_t;

typedef struct rx_array_carriers_s {
  char* name;
  uint32_t absolute_frequency_center;
  uint64_t center_of_channel_bandwidth;
  uint64_t channel_bandwidth;
  /* no definitions
  enum ACTIVE active;
  enum STATE state;
  enum TYPE type;
  enum DUPLEX_SCHEME duplex_scheme;
  */
  uint32_t downlink_radio_frame_offset;
  int16_t downlink_sfn_offset;
  uint64_t gain_correction;
  uint32_t n_ta_offset;
} rx_array_carriers_t;

typedef struct supported_section_types_t {
  uint8_t section_type;
  uint8_t supported_section_extensions;
} supported_section_types_s;

typedef struct endpoint_types_t {
  uint16_t id;
  supported_section_types_t section_types;
  uint8_t supported_frame_structures;
  // managed_delay_support_t managed_delay_support; no definition
  bool multiple_numerology_supported;
  uint16_t max_numerology_change_duration;
  uint8_t max_control_sections_per_data_section;
  uint16_t max_sections_per_symbol;
  uint16_t max_sections_per_slot;
  uint16_t max_beams_per_symbol;
  uint16_t max_beams_per_slot;
  uint16_t max_prb_per_symbol;
  uint16_t prb_capacity_allocation_granularity;
  uint16_t max_numerologies_per_symbol;
} endpoint_types_s;

typedef struct endpoint_capacity_sharing_groups_s {
  uint16_t id;
  uint8_t max_control_sections_per_data_section;
  uint16_t max_sections_per_symbol;
  uint16_t max_sections_per_slot;
  uint16_t max_beams_per_symbol;
  uint16_t max_beams_per_slot;
  uint16_t max_prb_per_symbol;
  uint16_t max_numerologies_per_symbol;
  uint16_t max_endpoints;
  uint16_t max_managed_delay_endpoints;
  uint16_t max_non_managed_delay_endpoints;
} endpoint_capacity_sharing_groups_t;

typedef struct ul_fft_sampling_offsets_s {
  scs_config_type_t scs;
  uint16_t ul_fft_sampling_offset;
} ul_fft_sampling_offsets_t;

typedef struct user_plane_capabilities_s {
  uint64_t max_supported_frequency_dl;
  uint64_t min_supported_frequency_dl;
  uint64_t max_supported_bandwidth_dl;
  uint32_t max_num_carriers_dl;
  uint64_t max_carrier_bandwidth_dl;
  uint64_t min_carrier_bandwidth_dl;
} user_plane_capabilities_t;

typedef struct compression_s {
  uint8_t iq_bitwidth;
  compression_type_t compression_type;
  c_type_t compression_format;
  union {
    uint8_t exponent;
    uint8_t sres_exponent;
    uint8_t block_scalar;
    struct {
      uint8_t comp_bit_width;
      uint8_t comp_shift;
    };
    struct {
      uint8_t active_beam_space_coeficient_mask;
      uint8_t block_scaler;
    };
    struct {
      uint8_t csf;
      uint16_t mod_comp_scaler;
    };
    struct {
      uint8_t sres_csf;
      uint16_t sres_mod_comp_scaler;
    };
  };
} compression_t;

typedef struct dynamic_compression_configuration_s {
  uint16_t id;
  uint8_t iq_bitwidth;
  const char* compression_method; // XXX: use enum? YANG enum names contain "-"
  // uint8_t fs_offset;
} dynamic_compression_configuration_t;

typedef enum polarisation_type_e {
  MINUS_45 = 0,
  ZERO,
  PLUS_45,
  PLUS_90
} polarisation_type_t;

typedef struct polarisations_s {
  uint8_t p;
  polarisation_type_t pol_type;
} polarisations_t;

typedef struct leftmost_bottom_array_element_position_s {
  uint64_t x;
  uint64_t y;
  uint64_t z;
} leftmost_bottom_array_element_position_t;

typedef struct normal_vector_direction_s {
  uint64_t azimuth_angle;
  uint64_t zenith_angle;
} normal_vector_direction_t;

typedef struct tx_arrays_s {
  char* name;
  uint16_t number_of_rows;
  uint16_t number_of_columns;
  uint8_t number_of_array_layers;
  uint64_t horizontal_spacing;
  uint64_t vertical_spacing;
  normal_vector_direction_t vector_direction;
  leftmost_bottom_array_element_position_t elem_position;
  polarisations_t pol;
  // band_capabilities/o_ran_module_cap:band_number band_number;
  uint16_t band_number;
  uint64_t max_gain;
  bool independent_power_budget;
  user_plane_capabilities_t capabilities;
} tx_arrays_t;

typedef struct static_low_level_tx_endpoints_s {
  char* name;
  // ietf_interfaces:name restricted_interfaces;
  tx_arrays_t arr;
  uint16_t endpoint_type; // endpoint_types/id
  uint16_t capacity_sharing_groups; // endpoint_capacity_sharing_groups/id
} static_low_level_tx_endpoints_t;

typedef struct user_plane_ul_capabilities_s {
  uint64_t max_supported_frequency_ul;
  uint64_t min_supported_frequency_ul;
  uint64_t max_supported_bandwidth_ul;
  uint32_t max_num_carriers_ul;
  uint64_t max_carrier_bandwidth_ul;
  uint64_t min_carrier_bandwidth_ul;
} user_plane_ul_capabilities_t;

typedef struct gain_correction_range_s {
  uint64_t max;
  uint64_t min;
} gain_correction_range_t;

typedef struct rx_arrays_s {
  char* name;
  uint16_t number_of_rows;
  uint16_t number_of_columns;
  uint8_t number_of_array_layers;
  uint64_t horizontal_spacing;
  uint64_t vertical_spacing;
  normal_vector_direction_t direction;
  leftmost_bottom_array_element_position_t array_position;
  polarisations_t pol;
  // band_capabilities/o_ran_module_cap:band_number band_number;
  uint16_t band_number;
  gain_correction_range_t gain_corrn_range;
  user_plane_ul_capabilities_t capabilities;
} rx_arrays_t;

typedef struct static_low_level_rx_endpoints_s {
  char* name;
  // ietf_interfaces:name restricted_interfaces;
  rx_arrays_t rx_arrays;
  uint16_t endpoint_type_id;
  uint16_t capacity_sharing_groups;
} static_low_level_rx_endpoints_t;

typedef struct user_plane_config_antenna_array_s {
  union {
    char* tx_array_name; // ref to o_ran_uplane_conf:name</tx_array_name>
    char* rx_array_name; // ref to o_ran_uplane_conf:name</rx_array_name>
  };
} user_plane_config_antenna_array_t;

typedef struct user_plane_config_antenna_types_s {
  // relation_type_t relation_type; //no definition
  uint16_t element_array1;
  uint16_t element_array2;
} user_plane_config_antenna_types_t;

typedef struct user_plane_confg_relations_s {
  uint16_t entity;
  user_plane_config_antenna_array_t array1;
  user_plane_config_antenna_array_t array2;
  user_plane_config_antenna_types_t types;
} user_plane_confg_relations_t;

typedef struct array_carrier_state_change_notification_info_s {
  char* name;
  carrier_state_t state_change;
} array_carrier_state_change_notification_info_t;

/** @struct tx_array_t
 *  @brief TX array
 */
typedef struct tx_array_s {
  COMMON_TXRX_ARRAY_FIELDS
  int64_t max_gain;
  bool independent_power_budget;
  struct {
    SUPPORT_FOR_DL_FIELDS
  } * capabilities;
} tx_array_t;

/** @struct static_low_level_endpoint_s
 *  @brief TX or RX endpoint entry.
 */
typedef struct static_low_level_endpoint_s {
  char* name;
  char** restricted_interfaces;
  char* array;
  uint16_t endpoint_type;
  uint16_t* capacity_sharing_groups;
} static_low_level_tx_endpoint_t;

/** @struct rx_array_t
 *  @brief RX array
 */
typedef struct rx_array_s {
  COMMON_TXRX_ARRAY_FIELDS
  struct gain_correction_factor {
    int64_t max;
    int64_t min;
  };
  struct {
    SUPPORT_FOR_UL_FIELDS
  } * capabilities;
} rx_array_t;

typedef struct low_level_tx_endpoint_s {
  COMMON_ENDPOINT_FIELDS
} low_level_tx_endpoint_t;

typedef struct low_level_tx_links_s {
  char* name;
  // processing_elements_t processing_element; no definition
  tx_array_carriers_t tx_array_carrier;
  low_level_tx_endpoint_t low_level_tx_endpoint;
} low_level_tx_links_t;

typedef struct low_level_rx_endpoint_s {
  COMMON_ENDPOINT_FIELDS
  struct {
    scs_config_type_t scs;
    uint16_t ul_fft_sampling_offset;
  } * ul_fft_sampling_offsets;
  bool non_time_managed_delay_enable = false;
} low_level_rx_endpoint_t;

typedef struct low_level_rx_links_s {
  char* name;
  // processing_elements_t processing_element; no definition
  rx_array_carriers_t rx_array_carrier;
  low_level_rx_endpoint_t low_level_rx_endpoint;
  // TODO: define a struct for the following field.
  // o_ran_processing_element:up_marking_name user_plane_uplink_marking;
} low_level_rx_links_t;

typedef struct user_plane_configuration_s {
  low_level_tx_links_t ll_tx_links;
  low_level_rx_links_t ll_rx_links;
  endpoint_types_t ep_types;
  endpoint_capacity_sharing_groups_t ep_groups;
  static_low_level_tx_endpoints_t s_ll_tx_endpoints;
  static_low_level_rx_endpoints_t s_ll_rx_endpointsl;
  low_level_tx_endpoint_t ll_tx_endpoint;
  low_level_rx_endpoint_t ll_rx_endpoint;
  tx_array_carriers_t tx_a_carriers;
  rx_array_carriers_t rx_a_carriers;
  tx_arrays_t tx_a;
  rx_arrays_t rx_a;
  user_plane_confg_relations_t relations;
} user_plane_configuration_t;

/**
 *  @defgroup UplaneConfFunctions O-RAN U-Plane Configuration Functions
 *  @brief U-Plane configuration functions - O-RAN WG4 M-Plane Spec Chapter 15.2
 *
 *  The user plane (U-Plane) is part of the Open Fronthaul interface between the
 *  O-RU and the O-DU. This module allows for U-Plane configuration on the O-RU
 *  via the M-Plane.
 */

/**
 * @brief Get tx_array by name.
 *
 * @param name The name designating the tx_array
 * @param tx_arrays Details about the tx_array specified by name
 *
 * Returns 0 if successfully found tx_array, 1 Otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_get_tx_array(const char* name, tx_array_t* tx_array);

/**
 * @brief Get all tx_array names.
 *
 * Returns all known tx_array names
 *
 * @ingroup UplaneConfFunctions
 */
const char** halmplane_get_tx_array_names();

/**
 * @brief Get low_level_tx_endpoint by name.
 *
 * @param name The name designating the low_level_tx_endpoint.
 * @param tx_endpoint Details about the low_level_tx_endpoint specified by name
 *                    Filled out by this function.
 *
 * Returns 0 if successfully found low_level_tx_endpoint, 1 Otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_get_low_level_tx_endpoint(
    const char* name, low_level_tx_endpoint_t* tx_endpoint);

/**
 * @brief Get all low_level_tx_endpoints.
 *
 * @param tx_endpoints The low_level_tx_endpoint details provided by this
 *                     function.
 * @param tx_endpoint Details about the low_level_tx_endpoint specified by name.
 *
 * Returns 0 if successfully found low_level_tx_endpoints, 1 Otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_get_low_level_tx_endpoints(
    low_level_tx_endpoint_t** tx_endpoints, int* n_endpoints);

/**
 * @brief Get rx_array by name.
 *
 * @param name The name designating the rx_array.
 * @param rx_arrays Details about the rx_array specified by name.
 *
 * Returns 0 if successfully found rx_array, 1 Otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_get_rx_array(const char* name, rx_array_t* rx_arrays);

/**
 * @brief Get all rx_array names.
 *
 * Returns all known rx_array names.
 *
 * @ingroup UplaneConfFunctions
 */
const char** halmplane_get_rx_array_names();

/**
 * @brief Get low_level_rx_endpoint by name.
 *
 * @param name The name designating the low_level_rx_endpoint.
 * @param rx_endpoint Details about the low_level_rx_endpoint specified by name
 *                    filled out by this function.
 *
 * Returns 0 if successfully found low_level_rx_endpoint, 1 Otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_get_low_level_rx_endpoint(
    const char* name, low_level_rx_endpoint_t* rx_endpoint);

/**
 * @brief Get all low_level_rx_endpoints.
 *
 * @param rx_endpoints The low_level_rx_endpoint details provided by this
 *                     function.
 * @param rx_endpoint Details about the low_level_rx_endpoint specified by name.
 *
 * Returns 0 if successfully found low_level_rx_endpoints, 1 Otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_get_low_level_rx_endpoints(
    low_level_rx_endpoint_t** rx_endpoints, int* n_endpoints);

/**
 * @brief Apply or validate a tx carrier state change action after a
 *        configuration change.
 *
 * @param name The name of the tx carrier.
 * @param chbw Width of carrier in Hz.
 * @param center Center frequency of channel bandwidth in Hz.
 * @param gain Transmission gain in dB.
 * @param new_state The new carrier state after the state change.
 * @param do_apply Flag whether or not to apply the change action. If 1, apply
 *                 the change action; if 0, only validate the change action.
 * @return 0 if change is successfully applied/validated, 1 otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_tx_carrier_state_change(
    const char* name,
    uint64_t chbw,
    uint64_t center,
    double gain,
    const char* new_state,
    int do_apply);

/**
 * @brief Apply or validate an rx carrier state change action after a
 *        configuration change.
 *
 * @param name The name of the rx carrier.
 * @param chbw Width of carrier in Hz.
 * @param center Center frequency of channel bandwidth in Hz.
 * @param gain_correction Gain correction of RF path linked with array element
 *                        or array layers.
 * @param new_state The new carrier state after the state change.
 * @param do_apply Flag whether or not to apply the change action. If 1, apply
 *                 the change action; if 0, only validate the change action.
 * @return 0 if change is successfully applied/validated, 1 otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_rx_carrier_state_change(
    const char* name,
    uint64_t chbw,
    uint64_t center,
    double gain_correction,
    const char* new_state,
    int do_apply);

/**
 * @brief Set the User-Plane configuration .
 *
 * @param uplane_cfg The U-Plane Configuration to apply.
 *
 * Returns 0 if successfully set U-Plane Configuration, 1 Otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_setUPlaneConfiguration(user_plane_configuration_t* uplane_cfg);

/**
 * @brief Update eaxcid for a low-level-rx-endpoint
 *
 * @param endpoint_name The name of the endpoint.
 * @param eaxc eaxcid data.
 * @return 0 if change is successful, 1 otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_update_rx_eaxc(const char* endpoint_name, e_axcid_t* eaxc);

/**
 * @brief Update eaxcid for a low-level-tx-endpoint
 *
 * @param endpoint_name The name of the endpoint.
 * @param eaxc eaxcid data.
 * @return 0 if change is successful, 1 otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_update_tx_eaxc(const char* endpoint_name, e_axcid_t* eaxc);

/**
 * @brief Update compression data for a low-level-rx-endpoint
 *
 * @param endpoint_name The name of the endpoint.
 * @param compression Compression data.
 * @return 0 if change is successful, 1 otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_update_rx_endpoint_compression(
    const char* endpoint_name, compression_t* compression);

/**
 * @brief Update compression data for a low-level-tx-endpoint
 *
 * @param endpoint_name The name of the endpoint.
 * @param compression Compression data.
 * @return 0 if change is successful, 1 otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_update_tx_endpoint_compression(
    const char* endpoint_name, compression_t* compression);

/**
 * @brief Update dynamic compression configuration for a low-level-rx-endpoint
 *
 * @param endpoint_name The name of the endpoint.
 * @param config Dynamic compression configuration.
 * @return 0 if change is successful, 1 otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_update_rx_endpoint_compression_dyn_config(
    const char* endpoint_name, dynamic_compression_configuration_t* config);

/**
 * @brief Update dynamic compression configuration for a low-level-tx-endpoint
 *
 * @param endpoint_name The name of the endpoint.
 * @param config Dynamic compression configuration.
 * @return 0 if change is successful, 1 otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_update_tx_endpoint_compression_dyn_config(
    const char* endpoint_name, dynamic_compression_configuration_t* config);

typedef void (*halmplane_carrier_state_cb_t)(
    const char* carrier_name, carrier_state_t carrier_state);

/**
 * @brief Register a callback function to be called when the state for an rx
 *        carrier changes.
 *
 * @param cb The callback function, which takes in a carrier name and new
 *           carrier state.
 * @return 0 if successful, 1 otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_register_rx_carrier_state_cb(halmplane_carrier_state_cb_t cb);

/**
 * @brief Register a callback function to be called when the state for a tx
 *        carrier changes.
 *
 * @param cb The callback function, which takes in a carrier name and new
 *           carrier state.
 * @return 0 if successful, 1 otherwise.
 *
 * @ingroup UplaneConfFunctions
 */
int halmplane_register_tx_carrier_state_cb(halmplane_carrier_state_cb_t cb);

#endif //__MPLANE_UPLANE_CONFIG_H__
