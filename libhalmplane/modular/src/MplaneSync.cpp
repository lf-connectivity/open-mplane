/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneSync.h"
#include "ModuleLoader.h"


halmplane_error_t halmplane_set_ptp_config(const ptp_config_t ptp_config)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_set_ptp_config(const ptp_config_t)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const ptp_config_t)) fptr)(ptp_config);
    }
  return status;
}

halmplane_error_t halmplane_get_ptp_status(ptp_status_t* ptp_status)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_ptp_status(ptp_status_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(ptp_status_t*)) fptr)(ptp_status);
    }
  return status;
}

halmplane_error_t halmplane_set_synce_config(const synce_config_t synce_config)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_set_synce_config(const synce_config_t)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const synce_config_t)) fptr)(synce_config);
    }
  return status;
}

halmplane_error_t halmplane_get_synce_status(synce_status_t* synce_status)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_synce_status(synce_status_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(synce_status_t*)) fptr)(synce_status);
    }
  return status;
}

halmplane_error_t halmplane_set_gnss_config(const gnss_config_t gnss_config)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_set_gnss_config(const gnss_config_t)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const gnss_config_t)) fptr)(gnss_config);
    }
  return status;
}

halmplane_error_t halmplane_get_gnss_status(gnss_status_t* gnss_status)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_gnss_status(gnss_status_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(gnss_status_t*)) fptr)(gnss_status);
    }
  return status;
}
