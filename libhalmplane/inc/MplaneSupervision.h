/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_SUPERVISION_H__
#define __MPLANE_SUPERVISION_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct supervision_s {
  uint32_t configured_cu_monitoring_interval;
} supervision_t;

/**
 * Get CU monitoring interval
 *
 */
uint32_t halmplane_get_cu_supervison_interval(void);

/**
 * Set CU monitoring interval, return 0 for success OR error code.
 *
 */

uint32_t halmplane_set_cu_supervison_interval(
    uint32_t cu_monitoring_interval);

#endif // __MPLANE_SUPERVISION_H__
