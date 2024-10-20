/*
 * Copyright (c) Linux Foundation and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ModuleLoader.h"
#include <iostream>


ModuleLoader::ModuleLoader()
{
  libname = "uninitialized";
  dlhandle = NULL;
  registered_functions = new std::map<std::string, void*>();
}

void ModuleLoader::open(const char* libfilename)
{
  libname = libfilename;
  dlhandle = dlmopen(LM_ID_NEWLM, libname, RTLD_NOW|RTLD_DEEPBIND);

  if (!dlhandle) 
    {
      std::cerr << dlerror() << std::endl;
    }
  void* (*rf)() = reinterpret_cast<void* (*)()>(dlsym(dlhandle, "function_map"));
  if(rf)
    {
      if(registered_functions)
	{
	  delete registered_functions;
	}
      registered_functions = (std::map<std::string, void*>*) rf();
    }

  if(!registered_functions)
    {
      registered_functions = new std::map<std::string, void*>();
    }
}

void* ModuleLoader::get(const char* key)
{
  return (*registered_functions)[key];
}


ModuleLoader* _loader()
{
  static ModuleLoader* instanceptr = new ModuleLoader();
  return instanceptr;
}
