/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneAld.h"
#include "ModuleLoader.h"


halmplane_error_t halmplane_ald_get_counters(halmplane_ald_communication_output_t* ald_status)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_ald_get_counters(halmplane_ald_communication_output_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(halmplane_ald_communication_output_t*)) fptr)(ald_status);
    }
  return status;
}

halmplane_error_t halmplane_ald_get_status(halmplane_ald_communication_output_t* ald_status)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_ald_get_status(halmplane_ald_communication_output_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(halmplane_ald_communication_output_t*)) fptr)(ald_status);
    }
  return status;
}  

halmplane_error_t halmplane_ald_response(halmplane_ald_communication_input_s* ald_req, uint16_t msg_size)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_ald_response(halmplane_ald_communication_input_s*, uint16_t)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(halmplane_ald_communication_input_s*, uint16_t)) fptr)(ald_req, msg_size);
    }
  return status;
}

halmplane_error_t halmplane_ald_request(halmplane_ald_communication_input_t* ald_req, uint16_t msg_size)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_ald_request(halmplane_ald_communication_input_t*, uint16_t)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(halmplane_ald_communication_input_s*, uint16_t)) fptr)(ald_req, msg_size);
    }
  return status;
}

halmplane_error_t halmplane_ald_set_receive_mode(halmplane_ald_communication_input_s* ald_req, uint16_t msg_size)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_ald_set_receive_mode(halmplane_ald_communication_input_s*, uint16_t)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(halmplane_ald_communication_input_s*, uint16_t)) fptr)(ald_req, msg_size);
    }
  return status;
}
