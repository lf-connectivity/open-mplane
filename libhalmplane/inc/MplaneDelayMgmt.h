/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_DELAY_MGMT_H__
#define __MPLANE_DELAY_MGMT_H__

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t bandwidth;

typedef struct transport_delay_s {
  uint32_t t12_min;
  uint32_t t12_max;
  uint32_t t34_min;
  uint32_t t34_max;
} transport_delay_t;

typedef struct du_delay_profile_s {
  uint32_t t1a_max_up;
  uint32_t tx_max;
  uint32_t ta4_max;
  uint32_t rx_max;
} du_delay_profile_t;

typedef struct adaptive_delay_configuration_s {
  bandwidth bw;
  uint32_t subcarrier_spacing;
  du_delay_profile_t du_delay_profile;
  transport_delay_t transport_delay;
} adaptive_delay_configuration_t;

typedef struct ru_delay_profile_s {
  /*
      "the minimum O-RU data processing delay between receiving IQ data
      message over the fronthaul interface and transmitting
      the corresponding first IQ sample at the antenna";

  */
  uint32_t t2a_min_up;

  /*
      "the earliest allowable time when a data packet is received before
      the corresponding first IQ sample is transmitted at the antenna";
  */
  uint32_t t2a_max_up;
  /*
      "the minimum O-RU data processing delay between receiving downlink
      real time control plane message over the fronthaul interface and
      transmitting the corresponding first IQ sample at the antenna";
  */
  uint32_t t2a_min_cp_dl;
  /*i
      "the earliest allowable time when a downlink real time control message
      is received before the corresponding first IQ sample is transmitted at
      the antenna";
  */
  uint32_t t2a_max_cp_dl;
  /*
      "the time difference (advance) between the reception window for
      downlink real time Control messages and reception window for the
      corresponding IQ data messages.";
  */
  uint32_t tcp_adv_dl;
  uint32_t ta3_min;
  uint32_t ta3_max;
  uint32_t t2a_min_cp_ul;
  uint32_t t2a_max_cp_ul;
} ru_delay_profile_t;

typedef struct o_ru_delay_management_s {
  bandwidth bw;
  uint32_t subcarrier_spacing;
  ru_delay_profile_t ru_delay_prof;
  // adaptive_delay_configuration_t adapt_delay_config; To Be Added
} o_ru_delay_management_t;

int halmplane_setDUToRUDelayMgmnt(o_ru_delay_management_s* ru_delay_mgmt);

#endif // __MPLANE_DELAY_MGMT_H__
