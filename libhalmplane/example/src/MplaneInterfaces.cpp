/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneInterfaces.h"

halmplane_error_t
halmplane_interface_update(interface_t* interface) {
  return NONE;
}

halmplane_error_t
halmplane_interface_update_description(
    const char* name, const char* description) {
  return NONE;
}

halmplane_error_t
halmplane_interface_update_type(const char* name, const char* type) {
  return NONE;
}

halmplane_error_t
halmplane_interface_update_enabled(const char* name, bool enabled) {
  return NONE;
}

halmplane_error_t
halmplane_interface_update_l2_mtu(const char* name, int l2Mtu) {
  return NONE;
}

halmplane_error_t
halmplane_interface_update_vlan_tagging(const char* name, bool vlanTagging) {
  return NONE;
}
halmplane_error_t
halmplane_interface_update_base_interface(
    const char* name, const char* baseInterface) {
  return NONE;
}

halmplane_error_t
halmplane_interface_update_vlan_id(const char* name, int vlanId) {
  return NONE;
}

halmplane_error_t
halmplane_interface_update_mac_address(
    const char* name, const char* macAddress) {
  return NONE;
}
