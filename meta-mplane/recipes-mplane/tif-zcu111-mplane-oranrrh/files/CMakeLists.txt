# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(tif-zcu111-mplane-oranrrh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(Model/inc)

add_library(tif-zcu111-mplane-oranrrh
  Model/src/Zcu111MplaneOranrrhAgcTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhCarrierHwTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhCarrierTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhDot1agdMonTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhEmbeddedTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhEqualiserTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhFibreTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhFpgaTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhGpioTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhHeartbeatTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhI2cTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhIpListTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhIpTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhNetopeerMonTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhOranFpgaTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhRadioStateTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhRegDevicesTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhRxPortTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhSettings.cpp
  Model/src/Zcu111MplaneOranrrhSrxPortTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhSystemConfigTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhSystemTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhTestInterface.cpp
  Model/src/Zcu111MplaneOranrrhTestInterfaceFactory.cpp
  Model/src/Zcu111MplaneOranrrhTxPortTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhYangConfigTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhYangManagerTestHandler.cpp
  Model/src/Zcu111MplaneOranrrhYangTestTestHandler.cpp
)

install(TARGETS tif-zcu111-mplane-oranrrh DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  Model/inc/Zcu111MplaneOranrrhAgcTestHandler.h
  Model/inc/Zcu111MplaneOranrrhCarrierHwTestHandler.h
  Model/inc/Zcu111MplaneOranrrhCarrierTestHandler.h
  Model/inc/Zcu111MplaneOranrrhDot1agdMonTestHandler.h
  Model/inc/Zcu111MplaneOranrrhEmbeddedTestHandler.h
  Model/inc/Zcu111MplaneOranrrhEqualiserTestHandler.h
  Model/inc/Zcu111MplaneOranrrhFibreTestHandler.h
  Model/inc/Zcu111MplaneOranrrhFpgaTestHandler.h
  Model/inc/Zcu111MplaneOranrrhGpioTestHandler.h
  Model/inc/Zcu111MplaneOranrrhHeartbeatTestHandler.h
  Model/inc/Zcu111MplaneOranrrhI2cTestHandler.h
  Model/inc/Zcu111MplaneOranrrhIpListTestHandler.h
  Model/inc/Zcu111MplaneOranrrhIpTestHandler.h
  Model/inc/Zcu111MplaneOranrrhNetopeerMonTestHandler.h
  Model/inc/Zcu111MplaneOranrrhOranFpgaTestHandler.h
  Model/inc/Zcu111MplaneOranrrhRadioStateTestHandler.h
  Model/inc/Zcu111MplaneOranrrhRegDevicesTestHandler.h
  Model/inc/Zcu111MplaneOranrrhRxPortTestHandler.h
  Model/inc/Zcu111MplaneOranrrhSettings.h
  Model/inc/Zcu111MplaneOranrrhSrxPortTestHandler.h
  Model/inc/Zcu111MplaneOranrrhSystemConfigTestHandler.h
  Model/inc/Zcu111MplaneOranrrhSystemTestHandler.h
  Model/inc/Zcu111MplaneOranrrhTestInterface.h
  Model/inc/Zcu111MplaneOranrrhTxPortTestHandler.h
  Model/inc/Zcu111MplaneOranrrhYangConfigTestHandler.h
  Model/inc/Zcu111MplaneOranrrhYangManagerTestHandler.h
  Model/inc/Zcu111MplaneOranrrhYangTestTestHandler.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
