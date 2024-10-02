/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <map>
#include "libtinyxml2/tinyxml2.h"
#include "HalMplane.h"
#include "MplaneInterfaces.h"
#include "MplaneProcessingElements.h"
#include "MplaneUplaneConf.h"

using namespace tinyxml2;

int halmplane_init()
{
    return 0;
}

int halmplane_config(tinyxml2::XMLDocument* doc)
{
  return 0;
}

int halmplane_exit()
{
    return 0;
}

typedef struct
{
  const char* key;
  void* ptr;
} labeled_ptr_t;

static labeled_ptr_t api_functions[] = {
  // HalMplane.h
  {"int halmplane_init()",
   (void*)(int (*)()) halmplane_init},
  {"int halmplane_config(XMLDocument*)",
   (void*)(int (*)(XMLDocument*)) halmplane_config},
  {"int halmplane_exit()",
   (void*)(int (*)()) halmplane_exit},

  // MplaneInterfaces.h
  {"halmplane_error_t halmplane_interface_update(interface_t*)",
   (void*)(halmplane_error_t (*)(interface_t*)) halmplane_interface_update},
  {"halmplane_error_t halmplane_interface_update_description(const char*, const char*)",
   (void*)(halmplane_error_t (*)(const char*, const char*)) halmplane_interface_update_description},
  {"halmplane_error_t halmplane_interface_update_type(const char*, const char*)",
   (void*)(halmplane_error_t (*)(const char*, const char*)) halmplane_interface_update_type},
  {"halmplane_error_t halmplane_interface_update_enabled(const char*, bool)",
   (void*)(halmplane_error_t (*)(const char*, bool)) halmplane_interface_update_enabled},
  {"halmplane_error_t halmplane_interface_update_l2_mtu(const char*, int)",
   (void*)(halmplane_error_t (*)(const char*, int)) halmplane_interface_update_l2_mtu},
  {"halmplane_error_t halmplane_interface_update_vlan_tagging(const char*, bool)",
   (void*)(halmplane_error_t (*)(const char*, bool)) halmplane_interface_update_vlan_tagging},
  {"halmplane_error_t halmplane_interface_update_base_interface(const char*, const char*)",
   (void*)(halmplane_error_t (*)(const char*, const char*)) halmplane_interface_update_base_interface},
  {"halmplane_error_t halmplane_interface_update_vlan_id(const char*, int)",
   (void*)(halmplane_error_t (*)(const char*, int)) halmplane_interface_update_vlan_id},
  {"halmplane_error_t halmplane_interface_update_mac_address(const char*, const char*)",
   (void*)(halmplane_error_t (*)(const char*, const char*)) halmplane_interface_update_mac_address},

  // MplaneProcessingElements.h
  {"halmplane_error_t halmplane_update_ru_element(ru_elements_t*)",
   (void*)(halmplane_error_t (*)(ru_elements_t*)) halmplane_update_ru_element},

  // MplaneUplaneConf.h
  {"int halmplane_setUPlaneConfiguration(user_plane_configuration_t*)",
   (void*)(int (*)(user_plane_configuration_t*)) halmplane_setUPlaneConfiguration},
  {"int halmplane_update_rx_eaxc(const char*, e_axcid_t*)",
   (void*)(int (*)(const char*, e_axcid_t*)) halmplane_update_rx_eaxc},
  {"int halmplane_update_tx_eaxc(const char*, e_axcid_t*)",
   (void*)(int (*)(const char*, e_axcid_t*)) halmplane_update_tx_eaxc},
  {"int halmplane_update_rx_endpoint_compression(const char*, compression_t*)",
   (void*)(int (*)(const char*, compression_t*)) halmplane_update_rx_endpoint_compression},
  {"int halmplane_update_tx_endpoint_compression(const char*, compression_t*)",
   (void*) (int (*)(const char*, compression_t*)) halmplane_update_tx_endpoint_compression},
  {"int halmplane_update_rx_endpoint_compression_dyn_config(const char*, dynamic_compression_configuration_t*)",
   (void*)(int (*)(const char*, dynamic_compression_configuration_t*)) halmplane_update_rx_endpoint_compression_dyn_config},
  {"int halmplane_update_tx_endpoint_compression_dyn_config(const char*, dynamic_compression_configuration_t*)",
   (void*) (int (*)(const char*, dynamic_compression_configuration_t*)) halmplane_update_tx_endpoint_compression_dyn_config},
  {"int halmplane_register_rx_carrier_state_cb(halmplane_carrier_state_cb_t)",
   (void*)(int (*)(halmplane_carrier_state_cb_t)) halmplane_register_rx_carrier_state_cb},
  {"int halmplane_register_tx_carrier_state_cb(halmplane_carrier_state_cb_t)",
   (void*)(int (*)(halmplane_carrier_state_cb_t)) halmplane_register_tx_carrier_state_cb},

  {NULL, NULL}
};


extern "C"
{
  void *function_map()
  {
    std::map<std::string, void*> *registered_functions;
    registered_functions = new std::map<std::string, void*>();

    int i = 0;
    while(api_functions[i].key != NULL)
      {
	(*registered_functions)[api_functions[i].key] = api_functions[i].ptr;
	i++;
      }
    return registered_functions;
  }
}
