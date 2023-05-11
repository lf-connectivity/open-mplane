/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_FAN_H__
#define __MPLANE_FAN_H__

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "MplaneTypes.h"
#include "smbus.h"

/** @struct fan_state_s
 * @brief Struct representing a fan on the O-RU.
 */
typedef struct fan_state_s {
  const char* name;
  uint8_t* fan_location;
  bool* present_and_operating;
  uint8_t* vendor_code;
  uint8_t* fan_speed;
  uint16_t* target_speed;
} fan_state_t;

/**
 *  @defgroup FanFunctions O-RAN Fan Functions
 *  @brief Fan functions - `o-ran-fan` module
 *
 *  This module provides Basic cooling fan control and monitoring. The o-ran-fan
 *  module has no detailed description in the O-RAN WG4 M-Plane Spec.
 */

/**
 * @brief Sets the `name` member of fan_state.
 *
 * @param fan_state The struct mutated by this function.
 *
 * Returns an error if any, NONE otherwise
 *
 * @ingroup FanFunctions
 */
halmplane_error_t halmplane_get_fan_name(fan_state_t* fan_state);

/**
 * @brief Sets the `fan_location` member of fan_state.
 *
 * @param fan_state The struct mutated by this function.
 *
 * @retval halmplane_error_e::NONE if a fan is found.
 *
 * @ingroup FanFunctions
 */
halmplane_error_t halmplane_get_fan_location(fan_state_t* fan_state);

/**
 * @brief Sets the `present_and_operating` member of fan_state.
 *
 * @param fan_state The struct mutated by this function.
 *
 * @retval halmplane_error_e::NONE if a fan is found.
 *
 * @ingroup FanFunctions
 */
halmplane_error_t halmplane_get_fan_present_and_operating(
    fan_state_t* fan_state);

/**
 * @brief Sets the `vendor_code` member of fan_state.
 *
 * @param fan_state The struct mutated by this function.
 *
 * @retval halmplane_error_e::NONE if a fan is found.
 *
 * @ingroup FanFunctions
 */
halmplane_error_t halmplane_get_fan_vendor_code(fan_state_t* fan_state);

/**
 * @brief Sets the `fan_speed` member of fan_state.
 *
 * @param fan_state The struct mutated by this function.
 *
 * @retval halmplane_error_e::NONE if a fan is found.
 *
 * @ingroup FanFunctions
 */
halmplane_error_t halmplane_get_fan_speed(fan_state_t* fan_state);

/**
 * @brief Sets the `target_speed` member of fan_state.
 *
 * @param fan_state The struct mutated by this function.
 *
 * @retval halmplane_error_e::NONE if a fan is found.
 *
 * @ingroup FanFunctions
 */
halmplane_error_t halmplane_get_fan_target_speed(fan_state_t* fan_state);

#endif //__MPLANE_FAN_H__
