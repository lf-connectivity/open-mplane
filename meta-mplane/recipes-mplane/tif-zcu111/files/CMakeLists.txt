# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(tif-zcu111)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(Model/inc)
include_directories(../helper/ZCU111/Model/inc)
include_directories(../helper/ORANRRH/Model/inc)

add_library(tif-zcu111
  Model/src/Zcu111UsedTestInterface.cpp
  Model/src/Zcu111CpriTestHandler.cpp
  ../helper/ZCU111/Model/src/CarrierHwTestHelper.cpp
  ../helper/ZCU111/Model/src/RadioStateTestHelper.cpp
  ../helper/ZCU111/Model/src/WaveformFileTestHelper.cpp
  ../helper/ZCU111/Model/src/WaveformTestHelper.cpp
  ../helper/ZCU111/Model/src/WaveformWrxcalTestHelper.cpp
  ../helper/ORANRRH/Model/src/Dot1agdMonTestHelper.cpp
  ../helper/ORANRRH/Model/src/NetopeerMonTestHelper.cpp
  ../helper/ORANRRH/Model/src/YangConfigTestHelper.cpp
  ../helper/ORANRRH/Model/src/YangManagerTestHelper.cpp
  ../helper/ORANRRH/Model/src/YangTestTestHelper.cpp
)

install(TARGETS tif-zcu111 DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  Model/inc/Zcu111CpriTestHandler.h
  Model/inc/Zcu111TestInterface.h
  ../helper/ZCU111/Model/inc/CarrierHwTestHelper.h
  ../helper/ZCU111/Model/inc/RadioStateTestHelper.h
  ../helper/ZCU111/Model/inc/WaveformFileTestHelper.h
  ../helper/ZCU111/Model/inc/WaveformTestHelper.h
  ../helper/ZCU111/Model/inc/WaveformWrxcalTestHelper.h
  ../helper/ORANRRH/Model/inc/Dot1agdMonTestHelper.h
  ../helper/ORANRRH/Model/inc/NetopeerMonTestHelper.h
  ../helper/ORANRRH/Model/inc/YangConfigTestHelper.h
  ../helper/ORANRRH/Model/inc/YangManagerTestHelper.h
  ../helper/ORANRRH/Model/inc/YangTestTestHelper.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
