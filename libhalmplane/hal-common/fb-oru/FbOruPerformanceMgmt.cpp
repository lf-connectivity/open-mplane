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

MplanePerfMeasInfo fb_oru_perfMeasInfo;

int fb_oru_registerOranPerfMeasCallback(const halmplane_oran_perf_meas_cb_t callback) {
    fb_oru_perfMeasInfo.cb_ptr = callback;
    return 0;
}

const halmplane_oran_perf_meas_cb_t get_perf_meas_cb_ptr(void){
    return fb_oru_perfMeasInfo.cb_ptr;
}

int fb_oru_getRssi (uint8_t interface, double *rssiValue) {

   	if (interface > 4) {
		return -1;
	}

   	std::shared_ptr<IMeasRssi> rxRssi(IMeasRssi::getInterface(interface));
    if (!rxRssi) {
        return -1;
	}

    Power rssi (rxRssi->getRssi());
	*rssiValue = rssi.get();
	return 0;
}
