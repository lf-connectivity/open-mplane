/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_EXTERNAL_IO_H__
#define __MPLANE_EXTERNAL_IO_H__

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "MplaneTypes.h"

/** @struct input_s
 *  @brief Struct representing an input IO
 *
 *  This struct is used to represent an input IO port on the O-RU.
 */
typedef struct input_s {
  const char* name;
  uint8_t port_in;
  bool* line_in;
} input_t;

/** @struct output_s
 *  @brief Struct representing an output IO
 *
 *  This struct is used to represent an output IO port on the O-RU.
 */
typedef struct output_s {
  const char* name;
  uint8_t port_out;
} output_t;

/** @struct output_s
 *  @brief Struct containing a setting to be applied to an output IO
 *
 *  This struct contains a setting, 1 or 0, to an output IO port on the O-RU.
 */
typedef struct output_setting_s {
  const char* name;
  bool* line_out;
} output_setting_t;

/**
 * @struct external_io_s
 * @brief Struct for retrieving IO information from a io port
 *
 * The struct pointers should be set according to the type of the gpio.
 * Only one of the pointers should be set for each external_io_t instance.
 * If it is an input pin, `input` should be set.
 * If it is an output port, `out_setting` should be set.
 */
typedef struct external_io_s {
  input_t* input;
  output_t* output;
  output_setting_t* out_setting;
} external_io_t;

/**
 *  @defgroup ExternalIOFunctions O-RAN ExternalIO Functions
 *  @brief External IO functions - O-RAN WG4 M-Plane Spec Chapter 14.5
 *
 *  An O-RU may have any number of External IO ports, e.g. GPIO pins. The
 *  ExternalIO M-Plane module monitors and controls the ports.
 */

/**
 * @brief For inputs, sets the parameter `line_in` with the value of the port
 *        specified by `name`. For outputs, sets the parameter `line_out` with
 *        the value of the port specified by `name`.
 *
 * @param io The struct mutated by this function.
 *
 * @retval halmplane_error_e::NONE if the external IO value is found
 * @retval halmplane_error_e::UNAVAILABLE if the external IO is not found
 *
 * @ingroup ExternalIOFunctions
 */
halmplane_error_t halmplane_get_io_value(external_io_t* io);

/**
 * @brief Sets the output of the port to the specified value.
 *
 * @param out_setting: The settings applied by this function.
 *
 * @retval halmplane_error_e::NONE if the external IO value is set
 * @retval halmplane_error_e::UNAVAILABLE if the external IO is not set
 *
 * @ingroup ExternalIOFunctions
 */
halmplane_error_t halmplane_set_io_value(output_setting_t* out_setting);

#endif //__MPLANE_EXTERNAL_IO_H__
