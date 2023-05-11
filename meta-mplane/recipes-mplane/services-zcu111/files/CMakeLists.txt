# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(services-zcu111)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(ImageManagement/inc)
include_directories(networking/inc)

add_library(services-zcu111
  ImageManagement/src/Zcu111ImageManagement.cpp
  ImageManagement/src/Zcu111OsImage.cpp
  networking/src/LoRestart.cpp
  networking/src/Zcu111BaseNetworkingService.cpp
  networking/src/Zcu111NetworkingService.cpp
)

install(TARGETS services-zcu111 DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  ImageManagement/inc/Zcu111ImageManagement.h
  ImageManagement/inc/Zcu111OsImage.h
  networking/inc/LoRestart.h
  networking/inc/Zcu111BaseNetworkingService.h
  networking/inc/Zcu111NetworkingService.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
