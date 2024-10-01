/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneEcpri.h"
#include "ModuleLoader.h"


/**
 * Check if message5 is enabled on RU.
 *
 * Returns true or false.
 */
bool halmplane_message5Enabled(void)
{
  bool status = 0;
  void* fptr;

  fptr = _loader()->get("bool halmplane_message5Enabled()");
  if(fptr == NULL)
    {
      status = 0;
    }
  else
    {
      status = ((bool (*)()) fptr)();
    }
  return status;
}
