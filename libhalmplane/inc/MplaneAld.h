/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

/*
 * Header file for Mplane Antenna Line Device (ALD)
 * Operational Requirements of the ALD are explained in section
 * 11.3 of the O-RAN Working Group 4 M-Plane Specification.
 */

#ifndef __MPLANE_ALD_H__
#define __MPLANE_ALD_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneTypes.h"

typedef enum halmplane_ald_communication_status_e {
  // flow control indicator of last requested operation (Status of RPC)
  // TODO
} halmplane_ald_communication_status_t;

typedef struct halmplane_ald_communication_input_s {
  uint8_t port_id;
  void* ald_req_message; // binary data

} halmplane_ald_communication_input_t;

typedef struct halmplane_ald_communication_output_s {
  uint8_t port_id;
  halmplane_ald_communication_status_t status;
  const char* error_message;
  void* ald_resp_message; // binary data
  uint32_t frames_with_wrong_crc;
  uint32_t frames_without_stop_flag;
  uint32_t number_of_received_octets;

} halmplane_ald_communication_output_t;

/**
 * Retrieves and sets the `frames_with_wrong_crc`, `frames_without_stop_flag`,
 * and `number_of_received_octets` counter members of the `ald_status` so that
 * collisions (and other diagnostic information) can be detected in the HDLC
 * branch.
 * @param ald_status YANG model to be populated with the requested information
 * @return Error status code if any, NONE otherwise
 */
halmplane_error_t halmplane_ald_get_counters(
    halmplane_ald_communication_output_t* ald_status);

/**
 * Retrieves and status of last "ald-communication" RPC to requestor and sets
 * the `status` member in `ald_status`.
 * @param ald_status YANG model to be populated with the requested information
 * @return Error status code if any, NONE otherwise
 */
halmplane_error_t halmplane_ald_get_status(
    halmplane_ald_communication_output_t* ald_status);

/**
 * Retrieves the response message from the device and sets it in
 * `ald_resp_message`
 * @param ald_req YANG model containing information about the request
 * @param msg_size size of the `ald_resp_message` member in bytes (max 1200)
 * @return Error status code if any, NONE otherwise
 */
halmplane_error_t halmplane_ald_response(
    halmplane_ald_communication_input_s* ald_req, uint16_t msg_size);

/**
 * Sends a request message `ald_req_message` to the ALD device specified by
 * `port_id`
 * @param ald_req YANG model containing information about the request
 * @param msg_size size of the `ald_resp_message` member in bytes (max 1200)
 * @return Error status code if any, NONE otherwise
 */
halmplane_error_t halmplane_ald_request(
    halmplane_ald_communication_input_t* ald_req, uint16_t msg_size);

/**
 * Sets the ALD device specified by `port_id` to receive mode.
 * @param ald_req YANG model containing information about the request
 * @param msg_size size of the `ald_resp_message` member in bytes (max 1200)
 * @return Error status code if any, NONE otherwise
 */
halmplane_error_t halmplane_ald_set_receive_mode(
    halmplane_ald_communication_input_s* ald_req, uint16_t msg_size);

#endif // __MPLANE_ALD_H__
