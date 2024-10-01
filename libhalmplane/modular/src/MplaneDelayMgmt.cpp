/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneDelayMgmt.h"
#include "ModuleLoader.h"

int halmplane_setDUToRUDelayMgmnt(o_ru_delay_management_s* ru_delay_mgmt)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_setDUToRUDelayMgmnt(o_ru_delay_management_s*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(o_ru_delay_management_s*)) fptr)(ru_delay_mgmt);
    }
  return status;
}
