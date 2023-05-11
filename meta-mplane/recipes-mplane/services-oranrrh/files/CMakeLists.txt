# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(services-oranrrh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(AlarmsOran/inc)
include_directories(AppControl/inc)
include_directories(UpdateService/inc)

add_library(services-oranrrh
  AlarmsOran/src/AlarmCUPlaneConnectivityMajor.cpp
  AlarmsOran/src/AlarmCUPlaneConnectivityMinor.cpp
  AppControl/src/OranRrhAppControl.cpp
  AppControl/src/OranRrhDelaysMgrSingleton.cpp
  AppControl/src/OranRrhServices.cpp
  UpdateService/src/OranRrhUpdateService.cpp
)

install(TARGETS services-oranrrh DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  AlarmsOran/inc/AlarmCUPlaneConnectivityMajor.h
  AlarmsOran/inc/AlarmCUPlaneConnectivityMinor.h
  AppControl/inc/OranRrhAppControl.h
  AppControl/inc/OranRrhServices.h
  UpdateService/inc/OranRrhUpdateService.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
