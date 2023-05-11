/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <fcntl.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>

extern "C" {
#include "MplaneFan.h"
}

namespace {
const char *kfanName{"COFAN 30-4988-10"}; // name/model of the fan
const char *ki2cFile{"/dev/i2c-0"}; // file name of the i2c bus of the gpio expander

const int kFanLocation{0};        // location of the fan in the fan tray
const int kExpanderAddress{0x20}; // The I2C address of the GPIO expander
const int kReadInputReg{0x02};    // register for reading the input values
const int kFanFailPin{1};         // pin 1 is the fan fail pin
const int kFullSpeed{100};        // fan speed at 100%
const int kFullSpeedTarget{6000}; // fan can rotate 6000rpm
} // namespace

using std::string;

/**
 * Sets the `name` member of fan_state
 * Returns an error if any, NONE otherwise
 */
halmplane_error_t halmplane_get_fan_name(fan_state_t *fan_state) {
    fan_state->name = kfanName;
    return NONE;
}

/**
 * Sets the `fan_location` member of fan_state
 * Returns an error if any, NONE otherwise
 */
halmplane_error_t halmplane_get_fan_location(fan_state_t *fan_state) {
    *(fan_state->fan_location) = kFanLocation;
    return NONE;
}

/**
 * Sets the `present_and_operating` member of fan_state
 * Returns an error if any, NONE otherwise
 */
halmplane_error_t halmplane_get_fan_present_and_operating(fan_state_t *fan_state) {
    int file;

    if ((file = open(ki2cFile, O_RDWR)) < 0) {
        return FILE_OPEN_ERROR;
    }

    if (ioctl(file, I2C_SLAVE_FORCE, kExpanderAddress) < 0) {
        return DEVICE_ERROR;
    }
    uint8_t data = i2c_smbus_read_byte_data(file, kReadInputReg);

    if (data == -1) {
        return DEVICE_ERROR;
    }

    //~FANFAIL is pin 1, so if (0x02 & data) == 0x02, then the fan is operating
    *(fan_state->present_and_operating) =
        (((1 << kFanFailPin) & data) == (1 << kFanFailPin));

    return NONE;
}

/**
 * Sets the `vendor_code` member of fan_state
 * Returns an error if any, NONE otherwise
 */
halmplane_error_t halmplane_get_fan_vendor_code(fan_state_t *fan_state) {
    return UNIMPLEMENTED;
}

/**
 * Sets the `fan_speed` member of fan_state
 * Returns an error if any, NONE otherwise
 * speed information is only available if the fan is present and operating
 */
halmplane_error_t halmplane_get_fan_speed(fan_state_t *fan_state) {
    bool operating;
    fan_state->present_and_operating = &operating;
    halmplane_error_t status =
        halmplane_get_fan_present_and_operating(fan_state);
    if (!*(fan_state->present_and_operating)) {
        return UNAVAILABLE;
    }
    *(fan_state->fan_speed) = kFullSpeed;

    return NONE;
}

/**
 * Sets the `target_speed` member of fan_state
 * Returns an error if any, NONE otherwise
 * target_speed information is only available if the fan is present and
 * operating
 */
halmplane_error_t halmplane_get_fan_target_speed(fan_state_t *fan_state) {
    bool operating;
    fan_state->present_and_operating = &operating;
    halmplane_error_t status =
        halmplane_get_fan_present_and_operating(fan_state);
    if (!*(fan_state->present_and_operating)) {
        return UNAVAILABLE;
    }
    *(fan_state->target_speed) = kFullSpeedTarget;
    return NONE;
}
