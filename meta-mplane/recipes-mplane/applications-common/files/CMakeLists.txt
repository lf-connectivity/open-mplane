# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(applications-common)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(Application/inc)
include_directories(BuildFeature/inc)
include_directories(vappi/inc)

add_library(applications-common
  Application/src/Application.cpp
  BuildFeature/src/BuildFeature.cpp
  BuildFeature/src/BuildFeatureList.cpp
)

install(TARGETS applications-common DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  Application/inc/Application.h
  BuildFeature/inc/BuildFeature.h
  BuildFeature/inc/BuildFeatureList.h
  vappi/inc/IApplication.h
  vappi/inc/IBuildFeature.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
