/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#if 0
#include "MplanePerformanceMgmt.h"
  /*
   * MplanePerformanceMgmt.h includes types with no definition
   */

int halmplane_registerOranPerfMeasCallback(
    halmplane_oran_perf_meas_cb_t callback);
const halmplane_oran_perf_meas_cb_t get_perf_meas_cb_ptr(void);

// Get Rssi for the specified interface; Valid values: 0 - 3
// Returns 0 - success or a non zero vlaue for error code
int halmplane_getRssi(uint8_t interface, double* rssiValue);

int halmplane_configPerfMeasurementParams(
    struct performance_measurement_params_t* config);

// Configure each measurement object and register call backs for various
// measurement objects.

// Transceiver measurement objects
int halmplane_activateTransceiverMeasObjects(
    struct transceiver_measurement_objects_t config,
    halmplane_transceiver_meas_cb_t cb);

// Rx Window Measurement Objects
int halmplane_activateRxWindowMeasObjects(
    struct rx_window_measurement_objects_t config,
    halmplane_rx_window_meas_cb_t cb);

// TX Measurement Objects, results are Tx_stats
int halmplane_activateTxMeasObjects(
    const struct tx_measurement_objects_t config,
    halmplane_tx_stats_meas_cb_t cb);

// EPE Measurement Objects
int halmplane_activateEpeMeasObjects(
    struct epe_measurement_objects_t config, halmplane_epe_meas_cb_t cb);

#endif
