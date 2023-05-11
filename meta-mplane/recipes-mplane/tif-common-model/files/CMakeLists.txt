# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(tif-common-model)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(Model/inc)

add_library(tif-common-model
  Model/src/CommonModelAlarmsTestHandler.cpp
  Model/src/CommonModelCalTestHandler.cpp
  Model/src/CommonModelI2cTestHandler.cpp
  Model/src/CommonModelImagesAppTestHandler.cpp
  Model/src/CommonModelImagesFpgaTestHandler.cpp
  Model/src/CommonModelImagesLibTestHandler.cpp
  Model/src/CommonModelImagesOsTestHandler.cpp
  Model/src/CommonModelImagesTestHandler.cpp
  Model/src/CommonModelSystemBootTestHandler.cpp
  Model/src/CommonModelSystemLoggingTestHandler.cpp
  Model/src/CommonModelSystemMemTestHandler.cpp
  Model/src/CommonModelSystemTcpTestHandler.cpp
  Model/src/CommonModelSystemTestHandler.cpp
  Model/src/TestInterface.cpp
)

install(TARGETS tif-common-model DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  Model/inc/CommonModelAlarmsTestHandler.h
  Model/inc/CommonModelCalTestHandler.h
  Model/inc/CommonModelI2cTestHandler.h
  Model/inc/CommonModelImagesAppTestHandler.h
  Model/inc/CommonModelImagesFpgaTestHandler.h
  Model/inc/CommonModelImagesLibTestHandler.h
  Model/inc/CommonModelImagesOsTestHandler.h
  Model/inc/CommonModelImagesTestHandler.h
  Model/inc/CommonModelSystemBootTestHandler.h
  Model/inc/CommonModelSystemLoggingTestHandler.h
  Model/inc/CommonModelSystemMemTestHandler.h
  Model/inc/CommonModelSystemTcpTestHandler.h
  Model/inc/CommonModelSystemTestHandler.h
  Model/inc/TestInterface.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
