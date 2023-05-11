# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(applications-common-specific)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(RadioApp/inc)

add_library(applications-common-specific
  RadioApp/src/CommonPostInit.cpp
  RadioApp/src/RadioApp.cpp
)

install(TARGETS applications-common-specific DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  RadioApp/inc/CommonPostInit.h
  RadioApp/inc/RadioApp.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
