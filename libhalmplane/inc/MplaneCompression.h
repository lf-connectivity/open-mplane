/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_COMPRESSION_H__
#define __MPLANE_COMPRESSION_H__

#include <stdbool.h>
#include <stdint.h>

typedef enum compression_type_e { STATIC, DYNAMIC } compression_type_t;

typedef struct no_compression_s {
} no_compression_t;

typedef struct block_floating_point_s {
  uint8_t exponent;
} block_floating_point_t;

typedef struct block_scaling_s {
  uint8_t block_scalar;
} block_scaling_t;

typedef struct u_law_s {
  uint8_t comp_bit_width;
  uint8_t comp_shift;
} u_law_t;

typedef struct beam_space_compression_s {
  uint8_t active_beam_space_coeficient_mask; // XXX Typo in YANG?
  uint8_t block_scaler;
} beam_space_compression_t;

typedef struct modulation_compression_s {
  uint8_t csf;
  uint16_t mod_comp_scaler;
} modulation_compression_t;

typedef union compression_format_config_u {
  no_compression_t no_compression;
  block_floating_point_t block_floating_point;
  block_scaling_t block_scaling;
  u_law_t u_law;
  beam_space_compression_t beam_space_compression;
  modulation_compression_t modulation_compression;
} compression_format_config_t;

typedef union compression_format_u {
  void* no_compression;
  block_floating_point_t block_floating_point;
  block_scaling_t block_scaling;
  u_law_t u_law;
  beam_space_compression_t beam_space_compression;
  modulation_compression_t modulation_compression;
} compression_format_t;

typedef struct additional_compression_method_supported_s {
  uint8_t iq_bitwidth;
  compression_type_t compression_type;
  uint8_t bitwidth;
  compression_format_t compression_format;
} additional_compression_method_supported_t;

#endif // __MPLANE_COMPRESSION_H__
