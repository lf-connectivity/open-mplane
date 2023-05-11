/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <fcntl.h>
#include <string>

extern "C" {

#include "MplaneExternalio.h"
}

namespace {
const int kStartPin{338};
const int kNumPins{174};
const int kPortValueSize{2};
} // namespace

using std::string;

/**
 * Checks if the name corresponds to a valid GPIO port
 * Returns true if the port is valid, false otherwise
 */
bool is_valid_io_port(const string &name) {
    // check if the io port is a LED
    if (name == "heartbeat") {
        return true;
    }

    if (name == "mmc0::") {
        return true;
    }

    // check if pin number is within the range of valid gpio numbers
    if (name.rfind("gpio", 0) == 0) {
        int pinNumber = stoi(name.substr(4));
        return ((pinNumber >= kStartPin) && (pinNumber < kStartPin + kNumPins));
    }
    return false;
}

/**
 * Gets the filename which contains the value of the GPIO
 * Returns an error if any, NONE otherwise
 */
halmplane_error_t get_value_file_name(const string &name, string &file_name) {
    // check if name is a valid port
    if (!is_valid_io_port(name)) {
        return INVALID_ARG;
    }

    // check if the port is an LED or a GPIO
    string fn = "/sys/class/";

    if (name.find("gpio") != string::npos) {
        fn += "gpio/" + name + "/value";
    } else {
        fn += "leds/" + name + "/brightness";
    }

    file_name = fn;
    return NONE;
}

/**
 * For inputs, sets the parameter `line_in` with the value of the port specified by `name`
 * For outputs, sets the parameter `line_out` with the value of the port specified by `name`
 * Returns an error if any, NONE otherwise
 */
halmplane_error_t halmplane_get_io_value(external_io_t *io) {
    string io_name;
    bool *setting;

    // check if io is input or output
    if (io->input != NULL) {
        io_name = io->input->name;
        setting = io->input->line_in;
    } else {
        io_name = io->out_setting->name;
        setting = io->out_setting->line_out;
    }

    string file_name;
    halmplane_error_t err = get_value_file_name(io_name, file_name);

    // invalid port
    if (err != NONE) {
        return err;
    }

    // open the file for reading the value
    int valuefd = open(file_name.c_str(), O_RDONLY);
    if (valuefd < 0) {
        return FILE_OPEN_ERROR;
    }

    // read the value in the file
    char value[kPortValueSize];
    if (read(valuefd, &value, kPortValueSize) < 0) {
        return FILE_READ_ERROR;
    }
    close(valuefd);

    // set passed in variable to the value in the file
    *setting = (value[0] == '1');

    return NONE;
}

/**
 * Sets the output of the port to the specified value
 * Returns an error if any, NONE otherwise
 */
halmplane_error_t halmplane_set_io_value(output_setting_t *out_setting) {
    string file_name;
    halmplane_error_t err =
        get_value_file_name(string(out_setting->name), file_name);

    // invalid port
    if (err != NONE) {
        return err;
    }

    // opens the file for writing
    int valuefd = open(file_name.c_str(), O_WRONLY);
    if (valuefd < 0) {
        return FILE_OPEN_ERROR;
    }

    // write the correct value to the output file
    if (write(valuefd, (*(out_setting->line_out) ? "1" : "0"), kPortValueSize) <
        kPortValueSize) {
        return FILE_WRITE_ERROR;
    }

    close(valuefd);
    return NONE;
}
