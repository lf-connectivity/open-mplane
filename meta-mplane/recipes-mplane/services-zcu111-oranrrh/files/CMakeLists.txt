# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(services-zcu111-oranrrh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(AppControl/inc)
include_directories(ImageManagement/inc)
include_directories(UpdateService/inc)

add_library(services-zcu111-oranrrh
  AppControl/src/CdiNetworkingService.cpp
  AppControl/src/OranNetworkingService.cpp
  AppControl/src/OranrrhNetworkingSingleton.cpp
  AppControl/src/PacketSnifferSingleton.cpp
  AppControl/src/Zcu111AppControl.cpp
  AppControl/src/Zcu111AppControlFactory.cpp
  AppControl/src/Zcu111FbcOranrrhServices.cpp
  #AppControl/src/Zcu111ImageManagementSingleton.cpp
  AppControl/src/Zcu111ServicesFactory.cpp
  ImageManagement/src/Zcu111FbcSoftwareFactory.cpp
  ImageManagement/src/Zcu111OranAppImage.cpp
  ImageManagement/src/Zcu111OranImageManagement.cpp
  ImageManagement/src/Zcu111OranOsImage.cpp
  UpdateService/src/Zcu111OranRrhUpdateService.cpp
)

install(TARGETS services-zcu111-oranrrh DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  AppControl/inc/CdiNetworkingService.h
  AppControl/inc/OranNetworkingService.h
  AppControl/inc/Zcu111AppControl.h
  AppControl/inc/Zcu111FbcOranrrhServices.h
  ImageManagement/inc/Zcu111OranAppImage.h
  ImageManagement/inc/Zcu111OranImageManagement.h
  ImageManagement/inc/Zcu111OranOsImage.h
  UpdateService/inc/Zcu111OranRrhUpdateService.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
