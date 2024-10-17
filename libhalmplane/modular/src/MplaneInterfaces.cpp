/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "MplaneInterfaces.h"
#include "ModuleLoader.h"

halmplane_error_t halmplane_interface_update(interface_t* interface)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_interface_update(interface_t*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(interface_t*)) fptr)(interface);
    }
  return status;
}

halmplane_error_t halmplane_interface_update_description(const char* name, const char* description)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_interface_update_description(const char*, const char*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const char*, const char*)) fptr)(name, description);
    }
  return status;
}

halmplane_error_t halmplane_interface_update_type(const char* name, const char* type)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_interface_update_type(const char*, const char*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const char*, const char*)) fptr)(name, type);
    }
  return status;
}

halmplane_error_t halmplane_interface_update_enabled(const char* name, bool enabled)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_interface_update_enabled(const char*, bool)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const char*, bool)) fptr)(name, enabled);
    }
  return status;
}

halmplane_error_t halmplane_interface_update_l2_mtu(const char* name, int l2Mtu)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_interface_update_l2_mtu(const char*, int)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const char*, int)) fptr)(name, l2Mtu);
    }
  return status;
}

halmplane_error_t halmplane_interface_update_vlan_tagging(const char* name, bool vlanTagging)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_interface_update_vlan_tagging(const char*, bool)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const char*, bool)) fptr)(name, vlanTagging);
    }
  return status;
}

halmplane_error_t halmplane_interface_update_base_interface(const char* name, const char* baseInterface)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_interface_update_base_interface(const char*, const char*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const char*, const char*)) fptr)(name, baseInterface);
    }
  return status;
}

halmplane_error_t halmplane_interface_update_vlan_id(const char* name, int vlanId)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_interface_update_vlan_id(const char*, int)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const char*, int)) fptr)(name, vlanId);
    }
  return status;
}

halmplane_error_t halmplane_interface_update_mac_address(const char* name, const char* macAddress)
{
  halmplane_error_t status = UNAVAILABLE;
  void* fptr;

  fptr = _loader()->get("halmplane_error_t halmplane_interface_update_mac_address(const char*, const char*)");
  if(fptr == NULL)
    {
      status = UNIMPLEMENTED;
    }
  else
    {
      status = ((halmplane_error_t (*)(const char*, const char*)) fptr)(name, macAddress);
    }  
  return status;
}
