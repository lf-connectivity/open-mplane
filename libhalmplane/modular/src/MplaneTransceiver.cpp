/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneTransceiver.h"
#include "ModuleLoader.h"

/**
 * Get port transceivers for the specified port_number from HAL
 * Returns 0 if successfull else error code.
 */
int halmplane_get_port_transceivers(port_transceivers_t* transceivers)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_get_port_transceivers(port_transceivers_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(port_transceivers_t*)) fptr)(transceivers);
    }

  return status;
}
