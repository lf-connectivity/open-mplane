/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __MODULE_LOADER_H__
#define __MODULE_LOADER_H__

#include <cstddef>
#include <map>
#include <string>
#include <dlfcn.h>


class ModuleLoader
{
private:
  const char* libname;
  void* dlhandle;
  std::map<std::string, void*> *registered_functions;

public:
  ModuleLoader();
  void open(const char* libname);
  void* get(const char* ftag);
};


ModuleLoader* _loader();


#endif
