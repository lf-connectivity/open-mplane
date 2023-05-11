/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_BEAMFORMING_H__
#define __MPLANE_BEAMFORMING_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneCompression.h"
#include "MplaneTypes.h"

/** @enum beamforming_type_t
 *  @brief Enumeration for spectrum utilization strategy used by a beam.
 *
 *  @var beamforming_type_t::FREQUENCY
 *      Frequency Division Duplex (FDD)
 *  @var beamforming_type_t::TIME
 *      Time Division Duplex (TDD)
 *  @var beamforming_type_t::HYBRID
 *      A mix of TDD and FDD
 */
typedef enum beamforming_type_e { FREQUENCY, TIME, HYBRID } beamforming_type_t;

/** @enum time_granularity_t
 *  @brief An enum for the minimum time division in a TDD beam
 *
 *  @var time_granularity_t::SLOT
 *      TDD slot resolution
 *  @var time_granularity_t::SYMBOL
 *      TDD symbol resolution
 */
typedef enum time_granularity_e { SLOT, SYMBOL } time_granularity_t;

/** @enum frequency_granularity_t
 *  @brief An enum for the minimal frequency division in a FDD beam
 *
 *  @var frequency_granularity_t::CC
 *      Carrier component granularity
 *  @var frequency_granularity_t::BAND
 *      Band granularity
 */
typedef enum frequency_granularity_e { CC, BAND } frequency_granularity_t;

/** @struct beamforming_type_frequency_t
 *  @brief Struct containing beamforming configuration data for frequency
 * spectrum usage
 */
typedef struct beamforming_type_frequency_s {
  /** Maximum number of beam ids for these data */
  uint16_t max_number_of_beam_ids;
  /** First beam id this configuration applies to */
  uint16_t initial_beam_id;
  /** Bitwidth used in compression */
  uint8_t iq_bitwidth;
  /** Compression applied to I/Q samples. STATIC or DYNAMIC */
  compression_type_t compression_type;
  /** Deprecated */
  uint8_t bitwidth;
  /** Compression format applied to samples */
  compression_format_t compression_format;
  /** Parameters for compression format */
  compression_format_config_t compression_format_config;
  /** Alternative compression strategies supported by this O-RU */
  additional_compression_method_supported_t*
      additional_compression_method_supported;
} beamforming_type_frequency_t;

/** @struct beamforming_type_time_t
 *  @brief Struct containing beamforming configuration data for time spectrum
 * usage
 */
typedef struct beamforming_type_time_s {
  /** Maximum number of beam ids for these data */
  uint16_t max_number_of_beam_ids;
  /** First beam id this configuration applies to */
  uint16_t initial_beam_id;
  /** Frequency granularity per carrier component (CC) or per band (BAND) */
  frequency_granularity_t frequency_granularity;
  /** Time granularity per slot (SLOT) or per symbol (SYMBOL) */
  time_granularity_t time_granularity;
  /** Bitwidth used in compression */
  uint8_t iq_bitwidth;
  /** Compression applied to I/Q samples. STATIC or DYNAMIC */
  compression_type_t compression_type;
  /** Deprecated */
  uint8_t bitwidth;
  /** Compression format applied to samples */
  compression_format_t compression_format;
  /** Parameters for compression format */
  compression_format_config_t compression_format_config;
  /** alternative compression strategies supported by this o-ru */
  additional_compression_method_supported_t*
      additioal_compression_method_supported;
} beamforming_type_time_t;

/** @struct beamforming_type_hybrid_t
 *  @brief Contains beamforming configuration data for hybrid spectrum usage
 */
typedef struct beamforming_type_hybrid_s {
  /** Maximum number of beam ids for these data */
  uint16_t max_number_of_beam_ids;
  /** First beam id this configuration applies to */
  uint16_t initial_beam_id;
  /** Frequency granularity per carrier component (CC) or per band (BAND) */
  frequency_granularity_t frequency_granularity;
  /** Time granularity per slot (SLOT) or per symbol (SYMBOL) */
  time_granularity_t time_granularity;
  /** Bitwidth used in compression */
  uint8_t iq_bitwidth;
  /** Compression applied to I/Q samples. STATIC or DYNAMIC */
  compression_type_t compression_type;
  /** Deprecated */
  uint8_t bitwidth;
  /** Compression format applied to samples */
  compression_format_t compression_format;
  /** Parameters for compression format */
  compression_format_config_t compression_format_config;
  /** alternative compression strategies supported by this o-ru */
  additional_compression_method_supported_t*
      additioal_compression_method_supported;
} beamforming_type_hybrid_t;

/** @union beamforming_static_properties_t
 *  @brief Beamforming configuration data specific to spectrum usage technique
 */
typedef union beamforming_type_config_u {
  /** Frequency (FDD) spectrum usage data */
  beamforming_type_frequency_t frequency;
  /** Time (TDD) spectrum usage data */
  beamforming_type_time_t time;
  /** Hybrid spectrum usage data */
  beamforming_type_hybrid_t hybrid;
} beamforming_type_config_t;

/**
 * Configuration constructs
 */

/** @struct beamforming_static_properties_t
 *  @brief Beamforming configuration data
 */
typedef struct beamforming_static_properties_s {
  /** boolean indicating if beamforming weights may be updated via he M-Plane.
   * *      Only true if the O-RU has MODIFY-BF-CONFIG enabled */
  bool rt_bf_weights_update_support;
  /** The beamforming spectrum usage technique */
  beamforming_type_t beamforming_type;
  /** The beamforming configuration data based on the spectrum usage technique
   */
  beamforming_type_config_t beamforming_type_config;
  /** The number of beams available for configuration on the O-RU */
  uint16_t number_of_beams;
} beamforming_static_properties_t;

/** @struct beamforming_static_properties_t
 *  @brief Top level beamforming configuration struct
 */
typedef struct oran_beamforming_config_s {
  /** 4G/5G band number */
  int band_number;
  /** A reference to o-ran-uplane-conf:user-plane-configuration:tx-arrays */
  void* tx_array;
  /** A reference to o-ran-uplane-conf:user-plane-configuration:rx-arrays */
  void* rx_array;
  /** A beamforming_static_properties_t struct, contains configuration data */
  beamforming_static_properties_t static_properties;
} oran_beamforming_config_t;

/**
 *  @defgroup BeamformingFunctions O-RAN Beamforming Functions
 *  @brief Beamforming functions - O-RAN WG4 M-Plane Spec Chapter 15.4
 *
 *  The M-Plane allows clients to select from predefined beamforming
 *  configuration files on the O-RU. This HAL module contains a large number of
 *  struct types reflecting the O-RAN beamforming yang module, however the sole
 *  HAL function contained in this module need not make use of these structs.
 */

/**
 * @brief Apply beamforming configuration from file on the O-RU
 *
 * @param file The beamforming configuration file path
 *
 * @retval halmplane_error_e::NONE if successfully applied beamforming
 * configuration
 * @retval halmplane_error_e::UNAVAILABLE if beamforming is not available
 * @retval halmplane_error_e::INVALID_ARG if there is an beamforming
 * configuration error
 * @retval halmplane_error_e::DEVICE_ERROR if beamforming configuration fails
 *
 * @ingroup BeamformingFunctions
 */
halmplane_error_t halmplane_apply_beamforming_file(char* filepath);

#endif // __MPLANE_BEAMFORMING_H__
