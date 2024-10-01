/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneFan.h"
#include "ModuleLoader.h"


halmplane_error_t halmplane_get_fan_name(fan_state_t* fan_state)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_fan_name(fan_state_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(fan_state_t*)) fptr)(fan_state);
    }
  return status;
}

halmplane_error_t halmplane_get_fan_location(fan_state_t* fan_state)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_fan_location(fan_state_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(fan_state_t*)) fptr)(fan_state);
    }
  return status;
}

halmplane_error_t halmplane_get_fan_present_and_operating(fan_state_t* fan_state)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_fan_present_and_operating(fan_state_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(fan_state_t*)) fptr)(fan_state);
    }
  return status;
}

halmplane_error_t halmplane_get_fan_vendor_code(fan_state_t* fan_state)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_fan_vendor_code(fan_state_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(fan_state_t*)) fptr)(fan_state);
    }
  return status;
}

halmplane_error_t halmplane_get_fan_speed(fan_state_t* fan_state)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_fan_speed(fan_state_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(fan_state_t*)) fptr)(fan_state);
    }
  return status;
}

halmplane_error_t halmplane_get_fan_target_speed(fan_state_t* fan_state)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_fan_target_speed(fan_state_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(fan_state_t*)) fptr)(fan_state);
    }
  return status;
}
