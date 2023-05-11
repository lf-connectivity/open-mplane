/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __FB_ORU_PERFORMANCE_MGMT_H__
#define __FB_ORU_PERFORMANCE_MGMT_H__

#include "MplanePerformanceMgmt.h"

typedef struct MplanePerfMeasInfo
{
    halmplane_oran_perf_meas_cb_t cb_ptr;
} MplanePerfMeasInfo;

int fb_oru_registerOranPerfMeasCallback(const halmplane_oran_perf_meas_cb_t callback);

const halmplane_oran_perf_meas_cb_t get_perf_meas_cb_ptr(void);

int fb_oru_getRssi (uint8_t interface, double *rssiValue);

#endif // __FB_ORU_PERFORMANCE_MGMT_H__
