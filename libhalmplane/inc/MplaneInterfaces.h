/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_INTERFACES_H__
#define __MPLANE_INTERFACES_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneTypes.h"

typedef enum enable_status_e {
  STATUS_ENABLED = 1,
  STATUS_DISABLED
} enable_status_t;

typedef enum interface_status_e {
  STATUS_UP = 1,
  STATUS_DOWN,
  STATUS_TESTING,
  STATUS_UNKNOWN,
  STATUS_DORMANT,
  STATUS_NOT_PRESENT,
  STATUS_LOWER_LAYER_DOWN
} interface_status_t;

typedef struct cos_marking_s {
  uint8_t uPlaneMarking;
  uint8_t cPlaneMarking;
  uint8_t mPlaneMarking;
  uint8_t sPlaneMarking;
  uint8_t otherMarking;
  // TODO: enhanced uplane markings
} cos_marking_t;

typedef struct interface_s {
  const char* name;
  const char* description;
  const char* type;
  bool enabled;
  enable_status_t linkUpDownTrapEnable;
  int l2Mtu;
  bool vlanTagging;
  const char* baseInterface;
  int vlanId;
  const char* macAddress;
  cos_marking_t classOfService;
} interface_t;

halmplane_error_t halmplane_interface_update(interface_t* interface);

halmplane_error_t halmplane_interface_update_description(
    const char* name, const char* description);

halmplane_error_t halmplane_interface_update_type(
    const char* name, const char* type);

halmplane_error_t halmplane_interface_update_enabled(
    const char* name, bool enabled);

halmplane_error_t halmplane_interface_update_l2_mtu(
    const char* name, int l2Mtu);

halmplane_error_t halmplane_interface_update_vlan_tagging(
    const char* name, bool vlanTagging);

halmplane_error_t halmplane_interface_update_base_interface(
    const char* name, const char* baseInterface);

halmplane_error_t halmplane_interface_update_vlan_id(
    const char* name, int vlanId);

halmplane_error_t halmplane_interface_update_mac_address(
    const char* name, const char* macAddress);

// TODO: add callback registration for oper_status, other state data changes

#endif // __MPLANE_INTERFACES_H__
