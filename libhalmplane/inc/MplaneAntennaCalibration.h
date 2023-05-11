/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_ANTENNA_CALIBRATION_H__
#define __MPLANE_ANTENNA_CALIBRATION_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneTypes.h"

/** @struct antenna_calibration_data_s
 *  @brief Struct containing parameters for the O-RU antenna calibration
 *  procedure. See Table 15.5.5-1 in the O-RAN WG4 M-Plane specifications for
 *  more details.
 */
typedef struct antenna_calibration_data_s {
  char* symbol_bitmask_dl;
  char* symbol_bitmask_ul;
  char* slot_bitmask_dl;
  char* slot_bitmask_ul;
  char* frame_bitmask_dl;
  char* frame_bitmask_ul;
  uint8_t calibration_step_size;
  uint8_t calibration_step_number;
  uint16_t start_sfn;
} antenna_calibration_data_t;

/**
 *  @defgroup AntennaCalibrationFunctions O-RAN Antenna Calibration Functions
 *  @brief Antenna calibration functions - O-RAN WG4 M-Plane Spec Chapter 15.5
 *
 *  Antenna calibration is highly hardware-dependent. The M-Plane antenna
 *  calibration module only contains methods for monitoring and scheduling
 *  antenna calibration, and for allocating resources such as slots and frames
 *  to the antenna calibration procedure.
 */

/**
 * @brief Start antenna calibration procedure
 *
 * @retval halmplane_error_e::NONE if successfully started antenna calibration
 * @retval halmplane_error_e::UNAVAILABLE if antenna calibration cannot be
 * started
 * @retval halmplane_error_e::INVALID_ARG if there is an antenna configuration
 * error
 * @retval halmplane_error_e::DEVICE_ERROR if antenna calibration fails
 *
 * @ingroup AntennaCalibrationFunctions
 */
halmplane_error_t halmplane_start_antenna_calibration(
    const* antenna_calibration_data_t);

#endif // __MPLANE_ANTENNA_CALIBRATION_H__
