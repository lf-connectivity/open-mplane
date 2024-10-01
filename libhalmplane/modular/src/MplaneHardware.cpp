/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneHardware.h"
#include "ModuleLoader.h"


bool halmplane_get_ietf_hardware(ietf_hardware_t* hw)
{
  bool status = 1;
  void* fptr;

  fptr = _loader()->get("bool halmplane_get_ietf_hardware(ietf_hardware_t* hw)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((bool (*)(ietf_hardware_t* hw)) fptr)(hw);
    }

  return status;
}

int halmplane_registerHwStateChange(halmplane_notificationHwStateChange_cb_t cb)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_registerHwStateChange(halmplane_notificationHwStateChange_cb_t)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(halmplane_notificationHwStateChange_cb_t)) fptr)(cb);
    }

  return status;
}

int halmplane_registerHwStateOper(halmplane_notificationHwStateOper_cb_t cb)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_registerHwStateOper(halmplane_notificationHwStateOper_cb_t)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(halmplane_notificationHwStateOper_cb_t)) fptr)(cb);
    }

  return status;
}

halmplane_error_t halmplane_get_energysaving_state(hw_component_t* hw_comp)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_energysaving_state(hw_component_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(hw_component_t*)) fptr)(hw_comp);
    }
  return status;
}

halmplane_error_t halmplane_get_availability_type(hw_component_t* hw_comp)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_availability_type(hw_component_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(hw_component_t*)) fptr)(hw_comp);
    }
  return status;
}

halmplane_error_t halmplane_get_label_content(hw_component_t* hw_comp)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_label_content(hw_component_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(hw_component_t*)) fptr)(hw_comp);
    }
  return status;
}

halmplane_error_t halmplane_get_product_code(hw_component_t* hw_comp)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_product_code(hw_component_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(hw_component_t*)) fptr)(hw_comp);
    }
  return status;
}

halmplane_error_t halmplane_is_energy_saving_enabled(hw_component_t* hw_comp)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_is_energy_saving_enabled(hw_component_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(hw_component_t*)) fptr)(hw_comp);
    }
  return status;
}

halmplane_error_t halmplane_get_dying_gasp_support(hw_component_t* hw_comp)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_dying_gasp_support(hw_component_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(hw_component_t*)) fptr)(hw_comp);
    }
  return status;
}

halmplane_error_t halmplane_get_last_service_date(hw_component_t* hw_comp)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_last_service_date(hw_component_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(hw_component_t*)) fptr)(hw_comp);
    }
  return status;
}

halmplane_error_t halmplane_get_o_ran_name(hw_component_t* hw_comp)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_o_ran_name(hw_component_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(hw_component_t*)) fptr)(hw_comp);
    }
  return status;
}
