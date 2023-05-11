/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_PERFORMANCE_MGMT_H__
#define __MPLANE_PERFORMANCE_MGMT_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneTypes.h"

typedef struct oran_perf_meas_s {
  double rssi;
} halmplane_oran_perf_meas_t;

typedef void (*halmplane_oran_perf_meas_cb_t)(
    const halmplane_oran_perf_meas_t* perf_meas, void* store);
int halmplane_registerOranPerfMeasCallback(
    halmplane_oran_perf_meas_cb_t callback);
const halmplane_oran_perf_meas_cb_t get_perf_meas_cb_ptr(void);

// Get Rssi for the specified interface; Valid values: 0 - 3
// Returns 0 - success or a non zero vlaue for error code
int halmplane_getRssi(uint8_t interface, double* rssiValue);

typedef struct transceiver_measurement_result_value_s {
  decimal64_t value;
  date_time_t time;
} transceiver_measurement_result_value_t;

typedef struct transceiver_measurement_result_s {
  transceiver_object_unit_t object_unit;
  // leafref to
  // if:interfaces/if:interface/o-ran-int:port-reference/o-ran-int:port-number
  char* object_unit_id;
  uint32_t frequency_table;
} transceiver_measurement_result_t;

typedef enum transceiver_measurement_object_e {
  TXRX_MEASUREMENT_OBJECT_RX_POWER = 0,
  TXRX_MEASUREMENT_OBJECT_RX_POWER_LANE_2,
  TXRX_MEASUREMENT_OBJECT_RX_POWER_LANE_3,
  TXRX_MEASUREMENT_OBJECT_RX_POWER_LANE_4,
  TXRX_MEASUREMENT_OBJECT_TX_POWER,
  TXRX_MEASUREMENT_OBJECT_TX_POWER_LANE_2,
  TXRX_MEASUREMENT_OBJECT_TX_POWER_LANE_3,
  TXRX_MEASUREMENT_OBJECT_TX_POWER_LANE_4,
  TXRX_MEASUREMENT_OBJECT_TX_BIAS_COUNT,
  TXRX_MEASUREMENT_OBJECT_TX_BIAS_COUNT_LANE_2,
  TXRX_MEASUREMENT_OBJECT_TX_BIAS_COUNT_LANE_3,
  TXRX_MEASUREMENT_OBJECT_TX_BIAS_COUNT_LANE_4,
  TXRX_MEASUREMENT_OBJECT_VOLTAGE,
  TXRX_MEASUREMENT_OBJECT_TEMPERATURE,
} transceiver_measurement_object_t;

typedef enum transceiver_report_info_e {
  REPORT_INFO_MAXIMUM = 0,
  REPORT_INFO_MINIMUM,
  REPORT_INFO_FIRST,
  REPORT_INFO_LATEST,
  REPORT_INFO_FREQUENCY_TABLE,
  REPORT_INFO_MAX_REPORTING_TYPE,
} transceiver_report_info_t;

typedef enum transceiver_object_unit_e {
  PORT_NUMBER = 0,
} transceiver_object_unit_t;

typedef enum function_e {
  FUNCTION_RAW = 0,
  FUNCTION_LOG_10,
} function_t;

typedef struct transceiver_measurement_objects_s {
  transceiver_measurement_object_t measurement_object;
  bool active;
  bool report_type[MAX_REPORTING_TYPE];
  object_unit_t object_unit;
  function_t function;
  uint16_t bin_count;
  decimal64_t lower_bound;
  decimal64_t upper_bound;
} transceiver_measurement_objects_t;

typedef struct transceiver_stats_s {
  transceiver_measurement_object_t measurement_object;
  date_time_t start_time;
  date_time_t end_time;
  transceiver_measurement_result_t* results_per_port;
} transceiver_stats_t;

/* Rx Window measurement
 */

typedef enum rx_window_measurement_object_e {
  RX_ON_TIME = 0,
  RX_EARLY,
  RX_LATE,
  RX_CORRUPT,
  RX_DUPL,
  RX_TOTAL,
  RX_ON_TIME_C,
  RX_EARLY_C,
  RX_LATE_C,
  RX_SEQID_ERR,
  RX_SEQID_ERR_C,
  RX_ERR_DROP,
} rx_window_measurement_object_t;

typedef enum rx_window_object_unit_e {
  RU = 0,
  TRANSPORT,
  EAXC_ID,
} rx_window_object_unit_t;

typedef enum rx_window_report_info_e { COUNT = 0 } rx_window_report_info_t;

typedef struct rx_window_measurement_objects_s {
  rx_window_measurement_object_t measurement_object;
  bool active;
  rx_window_object_unit_t object_unit;
  rx_window_report_info_t report_info;
} rx_window_measurement_objects_t;

typedef struct rx_window_object_name_count_s {
  char* name;
  uint64_t count;
  uint16_t eaxc_id; // applicable onlue for EAXC_ID object unit
} rx_window_object_name_count_t;

// rx-window-measurement-result-grouping
typedef struct rx_window_measurement_result_s {
  rx_window_object_name_count_t ru_count;
  rx_window_object_name_count_t* transport_count;
  rx_window_object_name_count_t* eaxc_id_count;
  uint64_t rx_window_measurement_object_t measurement_object;

} rx_window_measurement_result_t;

typedef struct rx_window_stats_s {
  rx_window_measurement_object_t measurement_object;
  date_time_t start_time;
  date_time_t end_time;
  rx_window_measurement_result_t results;
} rx_window_stats_t;

/*
tx_measurement_objects_s

*/

typedef enum tx_measurement_objects_enum_e {
  TX_TOTAL,
  TX_TOTAL_C,
} tx_measurement_objects_enum_t;

typedef enum object_unit_e {
  OBJECT_UNIT_RU = 0,
  OBJECT_UNIT_TRANSPORT,
  OBJECT_UNIT_EAXC_ID
} object_unit_t;

typedef enum tx_measurement_report_info_e {
  TX_MEASUREMENT_REPORT_INFO_COUNT = 0
} tx_measurement_report_info_t;

typedef struct tx_measurement_objects_s {
  tx_measurement_objects_enum_t measurement_object;
  bool active;
  tx_measurement_objects_enum_t object_unit;
  tx_measurement_report_info_t report_info;
} tx_measurement_objects_t;

typedef struct tx_measured_result_s {
  char* name;
  uint64_t count;
} tx_measured_result_t;

typedef struct tx_measurement_result_s {
  tx_measurement_object_unit_t object_unit;
  union {
    object_ru_unit_t ru_object_stats;
    tx_measured_results_t* tx_meas_results;
    object_eaxc_unit_t* eaxc_meas_results;
  }
} tx_measurement_result_t;

typedef struct tx_stats_s {
  tx_measurement_objects_enum_t measurement_object;
  date_time_t start_time;
  date_time_t end_time;
  tx_measurement_result_t results;
} tx_stats_t;

/*
epe-measurement-objects (Energy, Power and Environment)
*/

typedef enum epe_measurement_object_enum_e {
  TEMPERATURE,
  POWER,
} epe_measurement_object_enum_t;

typedef enum epe_measurement_report_info_e {
  EPE_MEASUREMENT_REPORT_INFO_MAXIMUM,
  EPE_MEASUREMENT_REPORT_INFO_MINIMUM,
  EPE_MEASUREMENT_REPORT_INFO_AVERAGE,
} epe_measurement_report_info_t;

typedef struct epe_measurement_objects_s {
  epe_measurement_object_enum_t measurement_object;
  bool active;
  epe_measurement_report_info_t report_info;
} epe_measurement_objects_t;

typedef struct epe_measurement_s {
  uint16_t object_id; // Not sure if there is an enum
  decimal64_t min;
  decimal64_t max;
  decimal64_t average;
} epe_measurement_t;

typedef struct epe_measurement_results_s {
  date_time_t start_time;
  date_time_t end_time;
  epe_measurement_t* meas_results;
} epe_measurement_results_t;

typedef struct object_ru_unit_s {
  char* name;
  uint64_t count;
} object_ru_unit_t;

typedef struct object_transport_unit_s {
  char* name;
  uint64_t count;
} object_transport_unit_t;

typedef struct object_eaxc_unit_s {
  uint16_t eaxc_id;
  uint64_t count;
  char* name;
} object_eaxc_unit_t;

typedef struct performance_measurement_params_s {
  uint16_t transceiver_measurement_interval;
  uint16_t epe_measurement_interval;
  uint16_t tx_window_measurement_interval;
  uint16_t rx_window_measurement_interval;
  uint16_t notification_interval;
} performance_measurement_params_t;

int halmplane_configPerfMeasurementParams(
    struct performance_measurement_params_t* config);

// Configure each measurement object and register call backs for various
// measurement objects.

// Transceiver measurement objects
typedef void (*halmplane_transceiver_meas_cb_t)(
    const struct transceiver_stats_t* meas_result);
int halmplane_activateTransceiverMeasObjects(
    struct transceiver_measurement_objects_t config,
    halmplane_transceiver_meas_cb_t cb);

// Rx Window Measurement Objects
typedef void (*halmplane_rx_window_meas_cb_t)(
    const struct rx_window_measurement_objects_t* perf_meas);
int halmplane_activateRxWindowMeasObjects(
    struct rx_window_measurement_objects_t config,
    halmplane_rx_window_meas_cb_t cb);

// TX Measurement Objects, results are Tx_stats
typedef void (*halmplane_tx_stats_meas_cb_t)(const struct tx_stats_s* stats);
int halmplane_activateTxMeasObjects(
    const struct tx_measurement_objects_t config,
    halmplane_tx_stats_meas_cb_t cb);

// EPE Measurement Objects
typedef void (*halmplane_epe_meas_cb_t)(
    const struct epe_measurement_results_t* perf_meas);
int halmplane_activateEpeMeasObjects(
    struct epe_measurement_objects_t config, halmplane_epe_meas_cb_t cb);

#endif

#endif // __MPLANE_PERFORMANCE_MGMT_H__
