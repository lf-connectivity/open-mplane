/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MPLANE_SYNC_H__
#define __MPLANE_SYNC_H__

#include <stdbool.h>
#include <stdint.h>

#include "MplaneTypes.h"

/* @enum ptp_profile_t
 * @brief Type of profile to be used in PTP setting
 *
 * @var ptp_profile_t::G_8275_1
 *     Usage of multicast over ethernet
 * @var ptp_profile_t::G_8275_2
 *     Usage of unicast over IP
 **/
typedef enum ptp_profile_e { G_8275_1, G_8275_2 } ptp_profile_t;

/** @enum multicast_mac_address_t
 * @brief The parameter defines destination MAC address, used by the DU in the
 * egress PTP messages.
 *
 * @var multicast_mac_address_t::FORWARDABLE
 *     means, that PTP shall use 01-1B-19-00-00-00 destination MAC address
 * @var multicast_mac_address_t::NONFORWARDABLE
 *     means, that PTP shall use 01-80-C2-00-00-0E destination MAC address
 */
typedef enum multicast_mac_address_e {
  MULTICAST_MAC_ADDRESS_FORWARDABLE,
  MULTICAST_MAC_ADDRESS_NONFORWARDABLE
} multicast_mac_address_t;

/** @struct ptp_config_s
 *  @brief PTP configuration
 */
typedef struct ptp_config_s {
  uint8_t domain_number;
  uint8_t* accepted_block_classes;
  ptp_profile_t ptp_profile;
  struct {
    multi_cast_mac_address_t multicast_mac_address;
    int16_t delay_asymmetry;
  } g_8275_1_config;
  struct {
    char* local_ip_port;
    struct {
      uint8_t local_priority;
      char* ip_address;
    } * master_ip_configuration;
    int8_t log_inter_sync_period;
    int8_t log_inter_announce_period;
  } g_8275_2_config;
} ptp_config_t;

/** @struct ptp_status_s
 *  @brief PTP status
 */
typedef struct ptp_status_s {
  uint8_t reporting_period;
  enum { LOCKED, UNLOCKED } lock_state;
  uint8_t clock_class;
  char* clock_identity;
  bool partial_timing_supported;
  struct {
    char* local_port_number;
    enum { PARENT, OK, NOK, DISABLED } state;
    bool two_step_flag;
    bool leap61;
    bool leap59;
    bool current_utc_offset_valid;
    bool ptp_timescale;
    bool time_traceable;
    bool frequency_traceable;
    char* source_clock_identity;
    uint16_t source_port_number;
    int16_t current_utc_offset;
    uint8_t priority1;
    uint8_t clock_class;
    uint8_t clock_accuracy;
    uint16_t offset_scaled_log_variance;
    uint8_t priority2;
    char* grandmaster_clock_identity;
    uint16_t steps_removed;
    uint8_t time_source;
  } * sources;
} ptp_status_t;

/** @struct synce_config_s
 *  @brief SyncE Configuration
 */
typedef struct sync_config_s {
  enum {
    PRC,
    PRS,
    SSU_A,
    SSU_B,
    ST2,
    ST3,
    ST3E,
    EEC1,
    EEC2,
    DNU,
    NONE
  } *
      acceptable_list_of_ssm;
  uint16_t timeout;
} synce_config_t;

/** @struct synce_status_s
 *  @brief SyncE status
 */
typedef struct synce_status_s {
  uint8_t reporting_period;
  struct {
    char* local_port_number;
    enum { LOCKED, UNLOCKED } state;
    uint8_t quality_level;
  } sources;
} synce_status_t;

/** @struct gnass_config_s
 *  @brief GNSS Configuration
 */
typedef struct gnss_config_s {
  bool enable;
  enum { GPS, GLONASS, GALILEO, BEIDOU } * satellite_constelation_list;
  enum { POSITIVE, NEGATIVE } polarity;
  uint16_t cable_delay;
  bool anti_jam_enable;
} gnss_config_t;

typedef struct gnss_state_s {
  uint8_t reporting_period;
  char* name;
  enum {
    SYNCHRONIZED,
    ACQUIRING - SYNC,
    ANTENNA - DISCONNECTED,
    BOOTING,
    ANTENNA - SHORT - CIRCUIT
  } gnss_sync_status;
  struct {
    uint8_t satellites_tracked;
    struct {
      int64_t altitude;
      double latitude;
      double longitude;
    } location;
  } gnss_data;
} gnss_status_t;

/**
 *  @defgroup SyncFunctions O-RAN Synchronization Aspect Functions
 *  @brief Synchronization aspect functions - O-RAN WG4 M-Plane Spec Chapter 13.
 *  This module contains functions for configuring the Synchronization Plane
 *  (S-Plane) between the O-RU and O-DU. The S-Plane is part of the Open
 *  Fronthaul Interface. Three S-Plane submodules are configurable:
 *
 *  - Precision Time Protocol (PTP)
 *  - SyncE
 *  - Global Navigation Satellite System (GNSS)
 *
 *  The HAL contains the following functions for configuring these submodules:
 *
 *  - halmplane_set_gnss_config()
 *  - halmplane_set_ptp_config()
 *  - halmplane_set_synce_config()
 *
 *  The M-Plane specifications provide procedures for reporting the status of
 *  the S-Plane submodules. The M-Plane server will use the following functions
 *  to retrieve the state of the S-Plane submodules:
 *
 *  - halmplane_get_gnss_status()
 *  - halmplane_get_ptp_status()
 *  - halmplane_get_synce_status()
 */

/**
 * @brief set PTP Configuration on O-RU
 *
 * @param ptp_config The PTP configuration to apply
 *
 * Returns 0 if successfully applied PTP configuration, 1 otherwise.
 *
 * @ingroup SyncFunctions
 */
halmplane_error_t halmplane_set_ptp_config(const ptp_config_t ptp_config);

/**
 * @brief get PTP status on O-RU
 *
 * @param ptp_status an empty PTP status struct filled by this function.
 *
 * Returns 0 if successfully retrieved PTP status, 1 otherwise.
 *
 * @ingroup SyncFunctions
 */
halmplane_error_t halmplane_get_ptp_status(ptp_status_t* ptp_status);

/**
 * @brief set SyncE Configuration on O-RU
 *
 * @param synce_config The SyncE configuration to apply
 *
 * Returns 0 if successfully applied SyncE configuration, 1 otherwise.
 *
 * @ingroup SyncFunctions
 */
halmplane_error_t halmplane_set_synce_config(const synce_config_t synce_config);

/**
 * @brief get SyncE status on O-RU
 *
 * @param synce_status an empty SyncE status struct filled by this function.
 *
 * Returns 0 if successfully retrieved SyncE status, 1 otherwise.
 *
 * @ingroup SyncFunctions
 */
halmplane_error_t halmplane_get_synce_status(synce_status_t* synce_status);

/**
 * @brief set GNSS Configuration on O-RU
 *
 * @param gnss_config The GNSS configuration to apply
 *
 * Returns 0 if successfully applied GNSS configuration, 1 otherwise.
 *
 * @ingroup SyncFunctions
 */
halmplane_error_t halmplane_set_gnss_config(const gnss_config_t gnss_config);

/**
 * @brief get GNSS status on O-RU
 *
 * @param gnss_status an empty GNSS status struct filled by this function.
 *
 * Returns 0 if successfully retrieved GNSS status, 1 otherwise.
 *
 * @ingroup SyncFunctions
 */
halmplane_error_t halmplane_get_gnss_status(gnss_status_t* gnss_status);

#endif // __MPLANE_SYNC_H__
