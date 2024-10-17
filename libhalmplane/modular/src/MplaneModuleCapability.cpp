/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneCompression.h"
#include "MplaneModuleCapability.h"
#include "ModuleLoader.h"


int halmplane_setDUToRUModuleCapability(module_capability_t* mod_capability)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_setDUToRUModuleCapability(module_capability_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(module_capability_t*)) fptr)(mod_capability);
    }

  return status;
}
