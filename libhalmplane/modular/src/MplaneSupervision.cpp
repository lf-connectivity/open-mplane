/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneSupervision.h"
#include "ModuleLoader.h"
/**
 * Get CU monitoring interval
 *
 */
uint32_t halmplane_get_cu_supervison_interval(void)
{
  uint32_t interval = 1;
  void* fptr;

  fptr = _loader()->get("uint32_t halmplane_get_cu_supervison_interval()");
  if(fptr == NULL)
    {
      interval = 1;
    }
  else
    {
      interval = ((uint32_t (*)()) fptr)();
    }

  return interval;
}
/**
 * Set CU monitoring interval, return 0 for success OR error code.
 *
 */

uint32_t halmplane_set_cu_supervison_interval(uint32_t cu_monitoring_interval)
{
  uint32_t interval = 1;
  void* fptr;

  fptr = _loader()->get("uint32_t halmplane_set_cu_supervison_interval(uint32_t)");
  if(fptr == NULL)
    {
      interval = 1;
    }
  else
    {
      interval = ((uint32_t (*)(uint32_t)) fptr)(cu_monitoring_interval);
    }

  return interval;
}

