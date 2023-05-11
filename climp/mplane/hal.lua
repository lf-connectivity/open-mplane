-- Copyright (c) Meta Platforms, Inc. and affiliates.
--
-- This source code is licensed under the MIT license found in the
-- LICENSE file in the root directory of this source tree.

--- HAL function definitions
-- @module mplane.hal

local ffi = require "ffi"
local halFunc = ffi.load("libhalmplane.so")

-- "MplaneTypes.h"
ffi.cdef[[

typedef enum {
  NONE = 0,
  UNIMPLEMENTED,
  UNAVAILABLE,
  FILE_OPEN_ERROR,
  FILE_READ_ERROR,
  FILE_WRITE_ERROR,
  INVALID_ARG,
  DEVICE_ERROR,
} halmplane_error_t;

]]

-- "MplaneExternalio.h"
ffi.cdef[[

typedef struct {
  const char* name;
  bool *line_out;
} output_setting_t;
typedef struct {
  const char* name;
  uint8_t port_in;
  bool *line_in;
} input_t;
typedef struct {
  const char* name;
  uint8_t port_out;
} output_t;
typedef struct {
  input_t *input;
  output_t *output;
  output_setting_t *out_setting;
} external_io_t;

halmplane_error_t halmplane_get_io_value(external_io_t *io);
halmplane_error_t halmplane_set_io_value (output_setting_t *out_setting);

]]

-- "MplaneFan.h"
ffi.cdef[[

typedef struct {
    const char *name;
    uint8_t *fan_location;
    bool *present_and_operating;
    uint8_t *vendor_code;
    uint8_t *fan_speed;
    uint16_t *target_speed;
} fan_state_t;

halmplane_error_t halmplane_get_fan_name (fan_state_t *fan_state);
halmplane_error_t halmplane_get_fan_present_and_operating (fan_state_t *fan_state);
halmplane_error_t halmplane_get_fan_location(fan_state_t *fan_state);
halmplane_error_t halmplane_get_fan_vendor_code(fan_state_t *fan_state);
halmplane_error_t halmplane_get_fan_speed(fan_state_t *fan_state);
halmplane_error_t halmplane_get_fan_target_speed(fan_state_t *fan_state);

]]

-- "MplaneHardware.h"
ffi.cdef[[

typedef const char* date_time_t;

typedef enum {
    ADMIN_STATE_UNKNOWN = 1,
    ADMIN_STATE_LOCKED,
    ADMIN_STATE_UNLOCKED,
}admin_state_t;

typedef enum {
    OPER_STATE_UNKNOWN = 1,
    OPER_STATE_DISABLED,
    OPER_STATE_ENABLED,
    OPER_STATE_TESTING,
} oper_state_t;

typedef enum {
    USAGE_STATE_UNKNOWN = 1,
    USAGE_STATE_IDLE,
    USAGE_STATE_ACTIVE,
    USAGE_STATE_BUSY,
} usage_state_t;

typedef enum {
    ALARM_STATE_UNKNOWN = 0,
    ALARM_STATE_UNDER_REPAIR  = 1,
    ALARM_STATE_CRITICAL = 2,
    ALARM_STATE_MAJOR = 4,
    ALARM_STATE_MINOR = 8,
    ALARM_STATE_WARNING = 16,
    ALARM_STATE_INDETERMINATE = 32,
} alarm_state_t;


typedef enum {
    STANDBY_STATE_UNKNOWN = 1,
    STANDBY_STATE_HOT_STANDBY,
    STANDBY_STATE_COLD_STANDBY,
    STANDBY_STATE_PROVIDING_SERVICE,
} standby_state_t;

typedef enum {
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

typedef enum {
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

typedef enum {
    SENSOR_STATUS_OK,
    SENSOR_STATUS_UNAVAILABLE,
    SENSOR_STATUS_NONOPERATIONAL,
} sensor_status_t;

typedef enum {
    ENERGY_SAVING_STATE_UNKNOWN,
    ENERGY_SAVING_STATE_SLEEPING,
    ENERGY_SAVING_STATE_AWAKE,
} energy_saving_state_t;

typedef enum {
    AVAILABILITY_TYPE_UNKNOWN,
    AVAILABILITY_TYPE_NORMAL,
    AVAILABILITY_TYPE_DEGRADED,
    AVAILABILITY_TYPE_FAULTY,
} availability_type_t;

typedef struct {
    date_time_t state_last_changed;
    admin_state_t admin_state;
    oper_state_t oper_state;
    usage_state_t usage_state;
    alarm_state_t alarm_state;
    standby_state_t standby_state;
    energy_saving_state_t energy_saving_state;
    availability_type_t availability_type;
} ietf_hw_state_t;

typedef struct {
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

typedef struct {
    bool *model_name;
    bool *serial_number;
} label_content_t;

typedef enum {
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

typedef struct {
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
    ietf_hw_state_t state;
    ietf_hw_sensor_data_t sensor_data;

    energy_saving_state_t *energy_saving_state;
    availability_type_t *availability_type;
    label_content_t *label_content;
    const char* product_code;
    bool *energy_saving_enabled;
    bool *dying_gasp_support;
    date_time_t last_service_date;
    const char* o_ran_name;
} hw_component_t;

typedef struct {
    date_time_t last_change;
    hw_component_t hw_component;
} ietf_hardware_t;

halmplane_error_t halmplane_get_energysaving_state(hw_component_t *hw_comp);
halmplane_error_t halmplane_get_availability_type(hw_component_t *hw_comp);
halmplane_error_t halmplane_get_label_content(hw_component_t *hw_comp);
halmplane_error_t halmplane_is_energy_saving_enabled(hw_component_t *hw_comp);
halmplane_error_t halmplane_get_product_code(hw_component_t *hw_comp);
halmplane_error_t halmplane_get_dying_gasp_support(hw_component_t *hw_comp);
halmplane_error_t halmplane_get_last_service_date(hw_component_t *hw_comp);
halmplane_error_t halmplane_get_o_ran_name(hw_component_t *hw_comp);

]]
return halFunc
