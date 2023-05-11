/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "FbOruPerformanceMgmt.h"
#include "IMeasRssi.h"


using Mplane::IMeasRssi;
using Mplane::Power;

int halmplane_registerOranPerfMeasCallback(const halmplane_oran_perf_meas_cb_t callback) {
    return fb_oru_registerOranPerfMeasCallback(callback);
}

int halmplane_getRssi (uint8_t interface, double *rssiValue) {
    return fb_oru_getRssi(interface, rssiValue);
}
