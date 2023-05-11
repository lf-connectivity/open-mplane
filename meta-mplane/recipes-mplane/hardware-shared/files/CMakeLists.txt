# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(hardware-shared)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(waveform/inc)

string(CONCAT SRC
  "waveform/src/WaveMemMgr.cpp;"
  "waveform/src/WaveformControl.cpp;"
  "waveform/src/WaveformHardware.cpp;"
  "waveform/src/WaveformHardware122M88.cpp;"
  "waveform/src/WaveformHardware153M6.cpp;"
  "waveform/src/WaveformHardwareDpdAdc.cpp;"
  "waveform/src/WaveformHardwareFastVss.cpp;"
  "waveform/src/WaveformHardwareFullrate.cpp;"
  "waveform/src/WaveformHardwareRxAdc.cpp;"
  "waveform/src/WaveformHardwareRxFixedRate.cpp;"
  "waveform/src/WaveformManager.cpp;"
)

if ( "${SIMULATOR}" STREQUAL "TRUE" )

  string(CONCAT SRC
    "CpriFibreEmu/src/CpriFibreEmu.cpp;"
  )
  
endif ()

add_library(hardware-shared
  ${SRC}
)

install(TARGETS hardware-shared DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  waveform/inc/WaveMemMgr.h
  waveform/inc/Waveform.h
  waveform/inc/WaveformControl.h
  waveform/inc/WaveformHardware.h
  waveform/inc/WaveformHardware122M88.h
  waveform/inc/WaveformHardware153M6.h
  waveform/inc/WaveformHardwareDpdAdc.h
  waveform/inc/WaveformHardwareFastVss.h
  waveform/inc/WaveformHardwareFullrate.h
  waveform/inc/WaveformHardwareRxAdc.h
  waveform/inc/WaveformHardwareRxFixedRate.h
  waveform/inc/WaveformManager.h
  waveform/inc/WaveformMem.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
