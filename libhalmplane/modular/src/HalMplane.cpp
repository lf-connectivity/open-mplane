/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <iostream>
#include "libtinyxml2/tinyxml2.h"
#include "HalMplane.h"

#include "ModuleLoader.h"

using namespace tinyxml2;

#if 0
/* example function table
 * this code not needed here but may be copied to an appropriate place in any libhalmplane/<board>
 * that wants the ability to run as a loadable module for convenient loading into the function map
 *
 * in that context, functions not provided by the implementation may be removed from the table
 *
 * There should be only one function of each name (no overloading) but name is still mangled
 * -- explicit casting gets a pointer to the correct function regardless of overloading or mangling
 *
 */

#include "HalMplane.h"
#include "MplaneAlarms.h"
#include "MplaneAld.h"
#include "MplaneAntennaCalibration.h"
#include "MplaneBeamforming.h"
#include "MplaneCompression.h"
#include "MplaneDelayMgmt.h"
#include "MplaneDhcp.h"
#include "MplaneEcpri.h"
#include "MplaneExternalio.h"
#include "MplaneFan.h"
#include "MplaneFaultMgmt.h"
#include "MplaneHardware.h"
#include "MplaneInterfaces.h"
#include "MplaneModuleCapability.h"
//#include "MplanePerformanceMgmt.h"
#include "MplaneProcessingElements.h"
#include "MplaneSupervision.h"
#include "MplaneSync.h"
#include "MplaneTransceiver.h"
#include "MplaneTypes.h"
#include "MplaneUplaneConf.h"


typedef struct
{
  const char* key;
  void* ptr;
} labeled_ptr_t;

static labeled_ptr_t api_functions[] = {
  // HalMplane.h
  {"int halmplane_init(XMLDocument*)",
   (void*)(int (*)(XMLDocument*)) halmplane_init},
  {"int halmplane_exit()",
   (void*)(int (*)()) halmplane_exit},

  // MplaneAlarms.h
  {"int halmplane_registerOranAlarmCallback(halmplane_oran_alarm_cb_t)",
   (void*)(int (*)(halmplane_oran_alarm_cb_t)) halmplane_registerOranAlarmCallback},

  // MplaneAld.h
  {"halmplane_error_t halmplane_ald_get_counters(halmplane_ald_communication_output_t*)",
   (void*)(halmplane_error_t (*)(halmplane_ald_communication_output_t*)) halmplane_ald_get_counters},
  {"halmplane_error_t halmplane_ald_get_status(halmplane_ald_communication_output_t*)",
   (void*)(halmplane_error_t (*)(halmplane_ald_communication_output_t*)) halmplane_ald_get_status},
  {"halmplane_error_t halmplane_ald_response(halmplane_ald_communication_input_s*, uint16_t)",
   (void*)(halmplane_error_t (*)(halmplane_ald_communication_input_s*, uint16_t)) halmplane_ald_response},
  {"halmplane_error_t halmplane_ald_request(halmplane_ald_communication_input_t*, uint16_t)",
   (void*)(halmplane_error_t (*)(halmplane_ald_communication_input_t*, uint16_t)) halmplane_ald_request},
  {"halmplane_error_t halmplane_ald_set_receive_mode(halmplane_ald_communication_input_s*, uint16_t)",
   (void*)(halmplane_error_t (*)(halmplane_ald_communication_input_s*, uint16_t)) halmplane_ald_set_receive_mode},

  // MplaneAntennaCalibration.h
  {"halmplane_error_t halmplane_start_antenna_calibration(const antenna_calibration_data_t*)",
   (void*)(halmplane_error_t (*)(const antenna_calibration_data_t*)) halmplane_start_antenna_calibration},

  // MplaneBeamforming.h
  {"halmplane_error_t halmplane_apply_beamforming_file(char*)",
   (void*)(halmplane_error_t (*)(char*)) halmplane_apply_beamforming_file},

  // MplaneDelayMgmt.h
  {"int halmplane_setDUToRUDelayMgmnt(o_ru_delay_management_s*)",
   (void*)(int (*)(o_ru_delay_management_s*)) halmplane_setDUToRUDelayMgmnt},

  // MplaneEcpri.h
  {"bool halmplane_message5Enabled()",
   (void*)(bool (*)()) halmplane_message5Enabled},

  // MplaneExternalio.h
  {"halmplane_error_t halmplane_get_io_value(external_io_t*)",
   (void*)(halmplane_error_t (*)(external_io_t*)) halmplane_get_io_value},
  {"halmplane_error_t halmplane_set_io_value(output_setting_t*)",
   (void*)(halmplane_error_t (*)(output_setting_t*)) halmplane_set_io_value},

  // MplaneFan.h
  {"halmplane_error_t halmplane_get_fan_name(fan_state_t*)",
   (void*)(halmplane_error_t (*)(fan_state_t*)) halmplane_get_fan_name},
  {"halmplane_error_t halmplane_get_fan_location(fan_state_t*)",
   (void*)(halmplane_error_t (*)(fan_state_t*)) halmplane_get_fan_location},
  {"halmplane_error_t halmplane_get_fan_present_and_operating(fan_state_t*)",
   (void*)(halmplane_error_t (*)(fan_state_t*)) halmplane_get_fan_present_and_operating},
  {"halmplane_error_t halmplane_get_fan_vendor_code(fan_state_t*)",
   (void*)(halmplane_error_t (*)(fan_state_t*)) halmplane_get_fan_vendor_code},
  {"halmplane_error_t halmplane_get_fan_speed(fan_state_t*)",
   (void*)(halmplane_error_t (*)(fan_state_t*)) halmplane_get_fan_speed},
  {"halmplane_error_t halmplane_get_fan_target_speed(fan_state_t*)",
   (void*)(halmplane_error_t (*)(fan_state_t*)) halmplane_get_fan_target_speed},

  // MplaneHardware.h
  {"bool halmplane_get_ietf_hardware(ietf_hardware_t* hw)",
   (void*)(bool (*)(ietf_hardware_t* hw)) halmplane_get_ietf_hardware},
  {"int halmplane_registerHwStateChange(halmplane_notificationHwStateChange_cb_t)",
   (void*)(int (*)(halmplane_notificationHwStateChange_cb_t)) halmplane_registerHwStateChange},
  {"int halmplane_registerHwStateOper(halmplane_notificationHwStateOper_cb_t)",
   (void*)(int (*)(halmplane_notificationHwStateOper_cb_t)) halmplane_registerHwStateOper},
  {"halmplane_error_t halmplane_get_energysaving_state(hw_component_t*)",
   (void*)(halmplane_error_t (*)(hw_component_t*)) halmplane_get_energysaving_state},
  {"halmplane_error_t halmplane_get_availability_type(hw_component_t*)",
   (void*)(halmplane_error_t (*)(hw_component_t*)) halmplane_get_availability_type},
  {"halmplane_error_t halmplane_get_label_content(hw_component_t*)",
   (void*)(halmplane_error_t (*)(hw_component_t*)) halmplane_get_label_content},
  {"halmplane_error_t halmplane_get_product_code(hw_component_t*)",
   (void*)(halmplane_error_t (*)(hw_component_t*)) halmplane_get_product_code},
  {"halmplane_error_t halmplane_is_energy_saving_enabled(hw_component_t*)",
   (void*)(halmplane_error_t (*)(hw_component_t*)) halmplane_is_energy_saving_enabled},
  {"halmplane_error_t halmplane_get_dying_gasp_support(hw_component_t*)",
   (void*)(halmplane_error_t (*)(hw_component_t*)) halmplane_get_dying_gasp_support},
  {"halmplane_error_t halmplane_get_last_service_date(hw_component_t*)",
   (void*)(halmplane_error_t (*)(hw_component_t*)) halmplane_get_last_service_date},
  {"halmplane_error_t halmplane_get_o_ran_name(hw_component_t*)",
   (void*)(halmplane_error_t (*)(hw_component_t*)) halmplane_get_o_ran_name},

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

  // MplaneModuleCapability.h
  {"int halmplane_setDUToRUModuleCapability(module_capability_t*)",
   (void*)(int (*)(module_capability_t*)) halmplane_setDUToRUModuleCapability},

  
  /*
   * MplanePerformanceMgmt.h includes types with no definition
   */
  //  {"int halmplane_registerOranPerfMeasCallback(halmplane_oran_perf_meas_cb_t)", (int (*)(halmplane_oran_perf_meas_cb_t)) halmplane_registerOranPerfMeasCallback},
  //{"const halmplane_oran_perf_meas_cb_t get_perf_meas_cb_ptr()", (const halmplane_oran_perf_meas_cb_t (*)()) get_perf_meas_cb_ptr},
  //{"int halmplane_getRssi(uint8_t, double*)", (int (*)(uint8_t, double*)) halmplane_getRssi},
  //{"int halmplane_configPerfMeasurementParams(struct performance_measurement_params_t*)", (int (*)(struct performance_measurement_params_t*)) halmplane_configPerfMeasurementParams},
  //{"int halmplane_activateTransceiverMeasObjects(struct transceiver_measurement_objects_t, halmplane_transceiver_meas_cb_t)", (int (*)(struct transceiver_measurement_objects_t, halmplane_transceiver_meas_cb_t)) halmplane_activateTransceiverMeasObjects},
  //{"int halmplane_activateRxWindowMeasObjects(struct rx_window_measurement_objects_t, halmplane_rx_window_meas_cb_t)", (int (struct (*)rx_window_measurement_objects_t, halmplane_rx_window_meas_cb_t)) halmplane_activateRxWindowMeasObjects},
  //{"int halmplane_activateTxMeasObjects(const struct tx_measurement_objects_t, halmplane_tx_stats_meas_cb_t)", (int (*)(const struct tx_measurement_objects_t, halmplane_tx_stats_meas_cb_t)) halmplane_activateTxMeasObjects},
  //{"int halmplane_activateEpeMeasObjects(struct epe_measurement_objects_t, halmplane_epe_meas_cb_t)", (int (*)(struct epe_measurement_objects_t, halmplane_epe_meas_cb_t)) halmplane_activateEpeMeasObjects},

  // MplaneProcessingElements.h
  {"halmplane_error_t halmplane_update_ru_element(ru_elements_t*)",
   (void*)(halmplane_error_t (*)(ru_elements_t*)) halmplane_update_ru_element},

  // MplaneSupervision.h
  {"uint32_t halmplane_get_cu_supervison_interval()",
   (void*)(uint32_t (*)()) halmplane_get_cu_supervison_interval},
  {"uint32_t halmplane_set_cu_supervison_interval(uint32_t)",
   (void*)(uint32_t (*)(uint32_t)) halmplane_set_cu_supervison_interval},

  // MplaneSync.h
  {"halmplane_error_t halmplane_set_ptp_config(const ptp_config_t)",
   (void*)(halmplane_error_t (*)(const ptp_config_t)) halmplane_set_ptp_config},
  {"halmplane_error_t halmplane_get_ptp_status(ptp_status_t*)",
   (void*)(halmplane_error_t (*)(ptp_status_t*)) halmplane_get_ptp_status},
  {"halmplane_error_t halmplane_set_synce_config(const synce_config_t)",
   (void*)(halmplane_error_t (*)(const synce_config_t)) halmplane_set_synce_config},
  {"halmplane_error_t halmplane_get_synce_status(synce_status_t*)",
   (void*)(halmplane_error_t (*)(synce_status_t*)) halmplane_get_synce_status},
  {"halmplane_error_t halmplane_set_gnss_config(const gnss_config_t)",
   (void*)(halmplane_error_t (*)(const gnss_config_t)) halmplane_set_gnss_config},
  {"halmplane_error_t halmplane_get_gnss_status(gnss_status_t*)",
   (void*)(halmplane_error_t (*)(gnss_status_t*)) halmplane_get_gnss_status},

  // MplaneTransceiver.h
  {"int halmplane_get_port_transceivers(port_transceivers_t*)",
   (void*)(int (*)(port_transceivers_t*)) halmplane_get_port_transceivers},

  // MplaneUplaneConf.h
  {"int halmplane_get_tx_array(const char* name, tx_array_t*)",
   (void*)(int (*)(const char* name, tx_array_t*)) halmplane_get_tx_array},
  {"const char** halmplane_get_tx_array_names()",
   (void*)(const char** (*)()) halmplane_get_tx_array_names},
  {"int halmplane_get_low_level_tx_endpoint(const char*, low_level_tx_endpoint_t*)",
   (void*)(int (*)(const char*, low_level_tx_endpoint_t*)) halmplane_get_low_level_tx_endpoint},
  {"int halmplane_get_low_level_tx_endpoints(low_level_tx_endpoint_t**, int*)",
   (void*)(int (*)(low_level_tx_endpoint_t**, int*)) halmplane_get_low_level_tx_endpoints},
  {"int halmplane_get_rx_array(const char*, rx_array_t*)",
   (void*)(int (*)(const char*, rx_array_t*)) halmplane_get_rx_array},
  {"const char** halmplane_get_rx_array_names()",
   (void*)(const char** (*)()) halmplane_get_rx_array_names},
  {"int halmplane_get_low_level_rx_endpoint(const char*, low_level_rx_endpoint_t*)",
   (void*)(int (*)(const char*, low_level_rx_endpoint_t*)) halmplane_get_low_level_rx_endpoint},
  {"int halmplane_get_low_level_rx_endpoints(low_level_rx_endpoint_t**, int*)",
   (void*)(int (*)(low_level_rx_endpoint_t**, int*)) halmplane_get_low_level_rx_endpoints},
  {"int halmplane_tx_carrier_state_change(const char*, uint64_t, uint64_t, double, const char*, int)",
   (void*)(int (*)(const char*, uint64_t, uint64_t, double, const char*, int)) halmplane_tx_carrier_state_change},
  {"int halmplane_rx_carrier_state_change(const char*, uint64_t, uint64_t, double, const char*, int)",
   (void*) (int (*)(const char*, uint64_t, uint64_t, double, const char*, int)) halmplane_rx_carrier_state_change},
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

  // mark end for easy loop termination
  {NULL, NULL}
};
#endif


int halmplane_init(XMLDocument* doc)
{
  void* fptr;
  int module_status = 0;
  const char* libname = NULL;

  if(doc)
    {
      XMLElement* module = doc->FirstChildElement("root")->FirstChildElement("halmplane-board-modular");
      if (module)
	{
	  // Get the file element
	  libname = module->FirstChildElement("file")->Attribute("value");
	  if (!libname)
	    {
	      std::cerr << "file value not found!" << std::endl;
	      return -1;
	    }
	}
      else
	{
	  std::cerr <<  "halmplane-board-modular element not found!" << std::endl;
	  return -1;
	}
    }
  _loader()->open(libname);
  fptr = _loader()->get("int halmplane_init(XMLDocument* doc)");
  if(fptr != NULL)
    {
      module_status = ((int (*)()) fptr)();
      if(module_status != 0)
	{
	  std::cerr << "module init failed " << module_status << std::endl;
	  return module_status;
	}
    }

  return 0;
}


int halmplane_exit()
{
  int module_status = 0;
  void* fptr;
  fptr = _loader()->get("int halmplane_exit()");
  if(fptr != NULL)
    {
      module_status = ((int (*)()) fptr)();
      if(module_status != 0)
	{
	  std::cerr << "module exit failed " << module_status << std::endl;
	  return module_status;
	}
    }
  return 0;
}
