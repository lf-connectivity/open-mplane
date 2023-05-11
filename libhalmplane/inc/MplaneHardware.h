/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_ORAN_HARDWARE_H__
#define __MPLANE_ORAN_HARDWARE_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneTypes.h"

typedef char* date_time_t;

typedef enum admin_state_e {
  ADMIN_STATE_UNKNOWN = 1,
  ADMIN_STATE_LOCKED,
  ADMIN_STATE_UNLOCKED,
} admin_state_t;

typedef enum oper_state_e {
  OPER_STATE_UNKNOWN = 1,
  OPER_STATE_DISABLED,
  OPER_STATE_ENABLED,
  OPER_STATE_TESTING,
} oper_state_t;

typedef enum usage_state_e {
  USAGE_STATE_UNKNOWN = 1,
  USAGE_STATE_IDLE,
  USAGE_STATE_ACTIVE,
  USAGE_STATE_BUSY,
} usage_state_t;

typedef enum alarm_state_e {
  ALARM_STATE_UNKNOWN = 0,
  ALARM_STATE_UNDER_REPAIR = 1,
  ALARM_STATE_CRITICAL = 2,
  ALARM_STATE_MAJOR = 4,
  ALARM_STATE_MINOR = 8,
  ALARM_STATE_WARNING = 16,
  ALARM_STATE_INDETERMINATE = 32,
} alarm_state_t;

typedef enum standby_state_e {
  STANDBY_STATE_UNKNOWN = 1,
  STANDBY_STATE_HOT_STANDBY,
  STANDBY_STATE_COLD_STANDBY,
  STANDBY_STATE_PROVIDING_SERVICE,
} standby_state_t;

typedef enum sensor_value_type_e {
  SENSOR_VALUE_TYPE_OTHER = 0,
  SENSOR_VALUE_TYPE_UNKNOWN,
  SENSOR_VALUE_TYPE_VOLTS_AC,
  SENSOR_VALUE_TYPE_VOLTS_DC,
  SENSOR_VALUE_TYPE_AMPERES,
  SENSOR_VALUE_TYPE_WATTS,
  SENSOR_VALUE_TYPE_HERTZ,
  SENSOR_VALUE_TYPE_CELSIUS,
  SENSOR_VALUE_TYPE_PERCENT_RH,
  SENSOR_VALUE_TYPE_RPM,
  SENSOR_VALUE_TYPE_CMM,
  SENSOR_VALUE_TYPE_TRUTH_VALUE,
} sensor_value_type_t;

typedef enum sensor_value_scale_e {
  SENSOR_VALUE_SCALE_YOCTO,
  SENSOR_VALUE_SCALE_ZEPTO,
  SENSOR_VALUE_SCALE_ATTO,
  SENSOR_VALUE_SCALE_FEMTO,
  SENSOR_VALUE_SCALE_PICO,
  SENSOR_VALUE_SCALE_NANO,
  SENSOR_VALUE_SCALE_MICRO,
  SENSOR_VALUE_SCALE_MILLI,
  SENSOR_VALUE_SCALE_UNITS,
  SENSOR_VALUE_SCALE_KILO,
  SENSOR_VALUE_SCALE_MEGA,
  SENSOR_VALUE_SCALE_GIGA,
  SENSOR_VALUE_SCALE_TERA,
  SENSOR_VALUE_SCALE_PETA,
  SENSOR_VALUE_SCALE_EXA,
  SENSOR_VALUE_SCALE_ZETTA,
  SENSOR_VALUE_SCALE_YOTTA,
} sensor_value_scale_t;

typedef enum sensor_status_e {
  SENSOR_STATUS_OK,
  SENSOR_STATUS_UNAVAILABLE,
  SENSOR_STATUS_NONOPERATIONAL,
} sensor_status_t;

typedef enum energy_saving_state_e {
  ENERGY_SAVING_STATE_UNKNOWN,
  ENERGY_SAVING_STATE_SLEEPING,
  ENERGY_SAVING_STATE_AWAKE,
} energy_saving_state_t;

typedef enum availability_type_e {
  AVAILABILITY_TYPE_UNKNOWN,
  AVAILABILITY_TYPE_NORMAL,
  AVAILABILITY_TYPE_DEGRADED,
  AVAILABILITY_TYPE_FAULTY,
} availability_type_t;

typedef struct ietf_hw_state_s {
  date_time_t state_last_changed;
  admin_state_t admin_state;
  oper_state_t oper_state;
  usage_state_t usage_state;
  alarm_state_t alarm_state;
  standby_state_t standby_state;
  energy_saving_state_t energy_saving_state;
  availability_type_t availability_type;
} ietf_hw_state_t;

typedef struct ietf_hw_sensor_data_s {
  bool hardware_sensor;
  int32_t value;
  sensor_value_type_t value_type;
  sensor_value_scale_t value_scale;
  int8_t value_precision;
  sensor_status_t oper_status;
  char* units_display;
  date_time_t value_timestamp;
  uint32_t value_update_rate;
} ietf_hw_sensor_data_t;

typedef struct label_content_s {
  bool* model_name; // indicates present or not
  bool* serial_number; // indicates present or not
} label_content_t;

typedef enum hardware_class_e {
  HARDWARE_CLASS_UNKNOWN,
  HARDWARE_CLASS_CHASSIS,
  HARDWARE_CLASS_BACKPLANE,
  HARDWARE_CLASS_CONTAINER,
  HARDWARE_CLASS_POWER_SUPPLY,
  HARDWARE_CLASS_FAN,
  HARDWARE_CLASS_SENSOR,
  HARDWARE_CLASS_MODULE,
  HARDWARE_CLASS_PORT,
  HARDWARE_CLASS_STACK,
  HARDWARE_CLASS_CPU,
  HARDWARE_CLASS_ENERGY_OBJECT,
  HARDWARE_CLASS_BATTERY,
  HARDWARE_CLASS_STORAGE_DRIVE
} hardware_class_t;

typedef struct hw_component_s {
  char* name;
  hardware_class_t cls;
  int32_t physical_index;
  char* description;
  char* parent;
  int32_t parent_rel_pos;
  char* contains_child;
  char* hardware_rev;
  char* firmware_rev;
  char* software_rev;
  char* serial_num;
  char* mfg_name;
  char* model_name;
  char* alias;
  char* asset_id;
  bool is_fru;
  date_time_t mfg_date;
  // ietf_inet_types uri; // TODO: define type
  // ietf_yang_types uuid; // TODO: define type
  ietf_hw_state_t state;
  ietf_hw_sensor_data_t sensor_data;
  // o_ran_hardware
  energy_saving_state_t* energy_saving_state;
  availability_type_t* availability_type;
  label_content_t* label_content;
  const char* product_code;
  bool* energy_saving_enabled;
  bool* dying_gasp_support;
  date_time_t* last_service_date;
  const char* o_ran_name;
} hw_component_t;

typedef struct ietf_hardware_s {
  date_time_t last_change;
  hw_component_t hw_component;
} ietf_hardware_t;

/**
 * Get details associated with a hardware component, specified by
 * ietf_hw_component_s.name param config The ietf_hardware_t struct, filled by
 * this function Returns 0 if successfully reterived config, else 1.
 */
bool halmplane_get_ietf_hardware(ietf_hardware_t* hw);

// Operation State Change Register CB and Notification from FW
typedef void (*halmplane_notificationHwStateChange_cb_t)(oper_state_t state);
int halmplane_registerHwStateChange(
    halmplane_notificationHwStateChange_cb_t cb);

typedef struct notify_hw_state_oper_s {
  bool hardware_state;
  char* name;
  admin_state_t admin_state;
  alarm_state_t alarm_state;
} notify_hw_state_oper_t;

// Operation Enabled/Disabled _ Register CB and Notification from FW
typedef void (*halmplane_notificationHwStateOper_cb_t)(
    const notify_hw_state_oper_t notify, bool state);
int halmplane_registerHwStateOper(
    halmplane_notificationHwStateOper_cb_t cb);

/**
 *  @defgroup HardwareFunctions O-RAN Hardware Functions
 *  @brief Hardware functions - functions for retrieving hardware information
 *  from the O-RU
 *
 *  This module provides basic O-RU hardware details. The functions in this
 *  module correspond to the `o-ran-hardware` module. The functions in this
 *  module fill out fields in the hw_component_t struct.
 */

/**
 * @brief Get energy saving state associated with this hardware component
 * hw_comp->energysaving_state is filled by this function
 *
 * @retval halmplane_error_e::NONE if the energysaving_state is found.
 *
 * @ingroup HardwareFunctions
 */
halmplane_error_t halmplane_get_energysaving_state(hw_component_t* hw_comp);

/**
 * @brief Get the availability type associated with this hardware component.
 *
 * @param hw_comp The hardware component struct mutated by this function.
 *                hw_comp->availability_type is filled by this function
 *
 * @retval halmplane_error_e::NONE if the availability_type is found.
 *
 * @ingroup HardwareFunctions
 */
halmplane_error_t halmplane_get_availability_type(hw_component_t* hw_comp);

/**
 * @brief Get label content details (model name and serial no. present?)
 * associated with this hardware component.
 *
 * @param hw_comp The hardware_component_t struct mutated by this function.
 *                hw_comp->label_content is filled by this function.
 *
 * @retval halmplane_error_e::NONE if the label_content is found.
 *
 * @ingroup HardwareFunctions
 */
halmplane_error_t halmplane_get_label_content(hw_component_t* hw_comp);

/**
 * @brief Get the product code associated with this hardware component.
 *
 * @param hw_comp The hardware_component_t struct mutated by this function.
 *                hw_comp->product_code is filled by this function.
 *
 * @retval halmplane_error_e::NONE if the product_code is found.
 *
 * @ingroup HardwareFunctions
 */
halmplane_error_t halmplane_get_product_code(hw_component_t* hw_comp);

/**
 * @brief Checks if energy saving is enabled on this hardware component.
 *
 * @param hw_comp The hardware_component_t struct mutated by this function.
 *                hw_comp->energy_saving_enabled is filled by this function.
 *
 * @retval halmplane_error_e::NONE if the energy_saving_enable value is found.
 *
 * @ingroup HardwareFunctions
 */
halmplane_error_t halmplane_is_energy_saving_enabled(
    hw_component_t* hw_comp);

/**
 * @brief Checks if dying gasp support is enabled on this hardware component.
 *
 * @param hw_comp The hardware_component_t struct mutated by this function.
 *                hw_comp->dying_gasp_support is filled by this function.
 *
 * @retval halmplane_error_e::NONE if the dying_gasp_support  value is found.
 *
 * @ingroup HardwareFunctions
 */
halmplane_error_t halmplane_get_dying_gasp_support(hw_component_t* hw_comp);

/**
 * @brief Get the last service date of this hardware component.
 *
 * @param hw_comp The hardware_component_t struct mutated by this function.
 *                hw_comp->last_service_date is filled by this function.
 *
 * @retval halmplane_error_e::NONE if the get_last_service_date is found.
 *
 * @ingroup HardwareFunctions
 */
halmplane_error_t halmplane_get_last_service_date(hw_component_t* hw_comp);

/**
 * @brief Get the O-RAN compliant name of this hardware component.
 *
 * @param hw_comp The hardware_component_t struct mutated by this function.
 *                hw_comp->o_ran_name is filled by this function.
 *
 * @retval halmplane_error_e::NONE if the o_ran_name is found.
 *
 * @ingroup HardwareFunctions
 */
halmplane_error_t halmplane_get_o_ran_name(hw_component_t* hw_comp);

#endif // __MPLANE_ORAN_HARDWARE_H__
