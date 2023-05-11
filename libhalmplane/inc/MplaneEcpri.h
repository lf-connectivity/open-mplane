/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_ECPRI_H__
#define __MPLANE_ECPRI_H__

#include <stdbool.h>

/**
 * Check if message5 is enabled on RU.
 *
 * Returns true or false.
 */
bool halmplane_message5Enabled(void);

#if 0

typedef struct ietf_hardware_component_s
{
    char name[256];
    char class[256];
    char parent[256];
    sint32_t parent_rel_pos;
    char alias[256];
    char asset_id[256];
    char uri[256];
} halmplane_ietf_hardware_component_t;

typedef struct ietf_hardware_state_s
{
    bool energy_saving_enabled;
    char oran_name[256];
} halmplane_ietf_hardware_state_t;

typedef struct oran_hardware_s
{
    bool energy_saving_enabled;
    char oran_name[256];
} halmplane_oran_hardware_t;

bool halmplane_set_ietf_hardware (halmplane_oran_hardware_t hw);

#endif

#endif // __MPLANE_ECPRI_H__
