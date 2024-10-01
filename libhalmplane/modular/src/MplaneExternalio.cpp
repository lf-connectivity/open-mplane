/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneExternalio.h"
#include "ModuleLoader.h"


halmplane_error_t halmplane_get_io_value(external_io_t* io)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_get_io_value(external_io_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(external_io_t*)) fptr)(io);
    }
  return status;
}

halmplane_error_t halmplane_set_io_value(output_setting_t* out_setting)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_set_io_value(output_setting_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(output_setting_t*)) fptr)(out_setting);
    }
  return status;
}
