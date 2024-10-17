/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MplaneUplaneConf.h"
#include "ModuleLoader.h"


int halmplane_get_tx_array(const char* name, tx_array_t* tx_array)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_get_tx_array(const char*, tx_array_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, tx_array_t*)) fptr)(name, tx_array);
    }

  return status;
}

const char** halmplane_get_tx_array_names()
{
  void* fptr;
  const char** names = NULL;
  fptr = _loader()->get("const char** halmplane_get_tx_array_names()");
  if(fptr == NULL)
    {
      names = NULL;
    }
  else
    {
      names = ((const char** (*)()) fptr)();
    }
   
  return names;
}

int halmplane_get_low_level_tx_endpoint(const char* name, low_level_tx_endpoint_t* tx_endpoint)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_get_low_level_tx_endpoint(const char*, low_level_tx_endpoint_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, low_level_tx_endpoint_t*)) fptr)(name, tx_endpoint);
    }

  return status;
}

int halmplane_get_low_level_tx_endpoints(low_level_tx_endpoint_t** tx_endpoints, int* n_endpoints)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_get_low_level_tx_endpoints(low_level_tx_endpoint_t**, int*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(low_level_tx_endpoint_t**, int*)) fptr)(tx_endpoints, n_endpoints);
    }
  return status;
}

int halmplane_get_rx_array(const char* name, rx_array_t* rx_arrays)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_get_rx_array(const char*, rx_array_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, rx_array_t*)) fptr)(name, rx_arrays);
    }
  return status;
}

const char** halmplane_get_rx_array_names()
{
  void* fptr;
  const char** names = NULL;
  fptr = _loader()->get("const char** halmplane_get_rx_array_names()");
  if(fptr == NULL)
    {
      names = NULL;
    }
  else
    {
      names = ((const char** (*)()) fptr)();
    }
   
  return names;
}

int halmplane_get_low_level_rx_endpoint(const char* name, low_level_rx_endpoint_t* rx_endpoint)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_get_low_level_rx_endpoint(const char*, low_level_rx_endpoint_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, low_level_rx_endpoint_t*)) fptr)(name, rx_endpoint);
    }
  return status;
}

int halmplane_get_low_level_rx_endpoints(low_level_rx_endpoint_t** rx_endpoints, int* n_endpoints)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_get_low_level_rx_endpoints(low_level_rx_endpoint_t**, int*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(low_level_rx_endpoint_t**, int*)) fptr)(rx_endpoints, n_endpoints);
    }
  return status;
}

int halmplane_tx_carrier_state_change(const char* name, uint64_t chbw, uint64_t center,
				      double gain, const char* new_state, int do_apply)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_tx_carrier_state_change(const char*, uint64_t, uint64_t, double, const char*, int)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, uint64_t, uint64_t,
			 double, const char*, int)) fptr)(name, chbw, center,
							  gain, new_state, do_apply);
    }
  return status;
}

int halmplane_rx_carrier_state_change(
    const char* name,
    uint64_t chbw,
    uint64_t center,
    double gain_correction,
    const char* new_state,
    int do_apply)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_rx_carrier_state_change(const char*, uint64_t, uint64_t, double, const char*, int)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, uint64_t, uint64_t,
			 double, const char*, int)) fptr)(name, chbw, center,
							  gain_correction, new_state, do_apply);
    }
  return status;
}

int halmplane_setUPlaneConfiguration(user_plane_configuration_t* uplane_cfg)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_setUPlaneConfiguration(user_plane_configuration_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(user_plane_configuration_t*)) fptr)(uplane_cfg);
    }
  return status;
}

int halmplane_update_rx_eaxc(const char* endpoint_name, e_axcid_t* eaxc)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_update_rx_eaxc(const char*, e_axcid_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, e_axcid_t*)) fptr)(endpoint_name, eaxc);
    }
  return status;
}

int halmplane_update_tx_eaxc(const char* endpoint_name, e_axcid_t* eaxc)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_update_tx_eaxc(const char*, e_axcid_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, e_axcid_t*)) fptr)(endpoint_name, eaxc);
    }
  return status;
}

int halmplane_update_rx_endpoint_compression(const char* endpoint_name, compression_t* compression)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_update_rx_endpoint_compression(const char*, compression_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, compression_t*)) fptr)(endpoint_name, compression);
    }
  return status;
}

int halmplane_update_tx_endpoint_compression(const char* endpoint_name, compression_t* compression)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_update_tx_endpoint_compression(const char*, compression_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, compression_t*)) fptr)(endpoint_name, compression);
    }
  return status;
}

int halmplane_update_rx_endpoint_compression_dyn_config(const char* endpoint_name, dynamic_compression_configuration_t* config)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_update_rx_endpoint_compression_dyn_config(const char*, dynamic_compression_configuration_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, dynamic_compression_configuration_t*)) fptr)(endpoint_name, config);
    }
  return status;
}

int halmplane_update_tx_endpoint_compression_dyn_config(const char* endpoint_name, dynamic_compression_configuration_t* config)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_update_tx_endpoint_compression_dyn_config(const char*, dynamic_compression_configuration_t*)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(const char*, dynamic_compression_configuration_t*)) fptr)(endpoint_name, config);
    }
  return status;
}

int halmplane_register_rx_carrier_state_cb(halmplane_carrier_state_cb_t cb)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_register_rx_carrier_state_cb(halmplane_carrier_state_cb_t)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(halmplane_carrier_state_cb_t)) fptr)(cb);
    }
  return status;
}

int halmplane_register_tx_carrier_state_cb(halmplane_carrier_state_cb_t cb)
{
  int status = 1;
  void* fptr;

  fptr = _loader()->get("int halmplane_register_tx_carrier_state_cb(halmplane_carrier_state_cb_t)");
  if(fptr == NULL)
    {
      status = 1;
    }
  else
    {
      status = ((int (*)(halmplane_carrier_state_cb_t)) fptr)(cb);
    }
  return status;
}
