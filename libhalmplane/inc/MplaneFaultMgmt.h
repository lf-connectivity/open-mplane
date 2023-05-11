/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_FAULT_MGMT_H__
#define __MPLANE_FAULT_MGMT_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneAlarms.h"
#include "MplaneTypes.h"

typedef struct fm_affected_objects_s {
  char* name;
} fm_affected_objects_t;

typedef struct active_alarms_s {
  uint16_t fault_id;
  char* fault_source;
  fm_affected_objects_t affected_objects;
  halmplane_oran_fault_severity_t fault_severity;
  bool is_cleared;
  char* fault_text;
  date_time_t event_time;
} active_alarms_t;

typedef struct fm_s {
  active_alarms_t alarm_list;
} fm_t;

#endif //__MPLANE_FAULT_MGMT_H__
