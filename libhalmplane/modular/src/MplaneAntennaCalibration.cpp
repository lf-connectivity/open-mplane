/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneAntennaCalibration.h"
#include "ModuleLoader.h"


halmplane_error_t halmplane_start_antenna_calibration(const antenna_calibration_data_t* acd)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_start_antenna_calibration(const antenna_calibration_data_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const antenna_calibration_data_t*)) fptr)(acd);
    }
  return status;
}
