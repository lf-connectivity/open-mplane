/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <cstddef>
#include "MplaneAlarms.h"
#include "ModuleLoader.h"

int halmplane_registerOranAlarmCallback(halmplane_oran_alarm_cb_t callback)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_registerOranAlarmCallback(halmplane_oran_alarm_cb_t)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(halmplane_oran_alarm_cb_t)) fptr)(callback);
    }

  return status;
}
