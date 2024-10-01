/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneBeamforming.h"
#include "ModuleLoader.h"


halmplane_error_t halmplane_apply_beamforming_file(char* filepath)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_apply_beamforming_file(char*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(char*)) fptr)(filepath);
    }
  return status;
}
