/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_ALARMS_H__
#define __MPLANE_ALARMS_H__

#include <stdbool.h>
#include <stdint.h>

typedef enum halmplane_oran_fault_severity_e {
  ORAN_FAULT_SEVERITY_CRITICAL,
  ORAN_FAULT_SEVERITY_MAJOR,
  ORAN_FAULT_SEVERITY_MINOR,
  ORAN_FAULT_SEVERITY_WARNING,
} halmplane_oran_fault_severity_t;

// Based O-RAN fault management yang
// module: o-ran-fm
//   +--ro active-alarm-list
//      +--ro active-alarms*
//         +--ro fault-id          uint16
//         +--ro fault-source      string
//         +--ro affected-objects*
//         |  +--ro name  string
//         +--ro fault-severity    enumeration
//         +--ro is-cleared        boolean
//         +--ro fault-text?       string
//         +--ro event-time        yang:date-and-time
typedef struct halmplane_oran_alarm_s {
  uint16_t fault_id;
  char* fault_source;
  char** affected_objects; // array of c-strings, 1-100 c-strings total
  halmplane_oran_fault_severity_e fault_severity;
  bool is_cleared;
  uint64_t event_time;
  char* fault_text;
  uint64_t fault_time; // Unix timestamp
} halmplane_oran_alarm_t;

typedef void (*halmplane_oran_alarm_cb_t)(
    const halmplane_oran_alarm_t* alarm, void* store);

int halmplane_registerOranAlarmCallback(halmplane_oran_alarm_cb_t callback);

#endif // __MPLANE_ALARMS_H__
