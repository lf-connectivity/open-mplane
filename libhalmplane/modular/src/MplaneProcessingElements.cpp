/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneProcessingElements.h"
#include "ModuleLoader.h"

halmplane_error_t halmplane_update_ru_element(ru_elements_t* ru_element)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_update_ru_element(ru_elements_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(ru_elements_t*)) fptr)(ru_element);
    }
  return status;
}

