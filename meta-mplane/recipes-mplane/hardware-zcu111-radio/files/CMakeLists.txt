# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(hardware-zcu111-radio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(Faults/inc)
include_directories(OtherFaults/inc)
include_directories(PowerFaults/inc)
include_directories(TemperatureFaults/inc)
include_directories(orxPort/inc)

add_library(hardware-zcu111-radio
  Faults/src/RrhFaults.cpp
  Faults/src/RrhFaultsSingleton.cpp
  OtherFaults/src/DpdPllLockFaultMajor.cpp
  OtherFaults/src/DpdPllLockMajorFaultOwner.cpp
  OtherFaults/src/DpdTxFaultMajor.cpp
  OtherFaults/src/DpdTxFaultMinor.cpp
  OtherFaults/src/HeartBeatFaultMajor.cpp
  OtherFaults/src/HeartBeatFaultOwner.cpp
  OtherFaults/src/PclTxConvergenceFaultMajor.cpp
  OtherFaults/src/PclTxMajorFaultOwner.cpp
  OtherFaults/src/PclTxOverPowerFaultMajor.cpp
  OtherFaults/src/PopTripMajorFaultOwner.cpp
  OtherFaults/src/PopTripTxFaultMajor.cpp
  OtherFaults/src/RefPllLockFaultMajor.cpp
  OtherFaults/src/RefPllLockMajorFaultOwner.cpp
  OtherFaults/src/RxPllLockFaultMajor.cpp
  OtherFaults/src/RxPllLockMajorFaultOwner.cpp
  OtherFaults/src/SrlMajorFaultOwner.cpp
  OtherFaults/src/SrlTxFaultMajor.cpp
  OtherFaults/src/TxPllLockFaultMajor.cpp
  OtherFaults/src/TxPllLockMajorFaultOwner.cpp
  OtherFaults/src/VswrTxFaultMajor.cpp
  PowerFaults/src/TxOverPowerFaultMajor.cpp
  PowerFaults/src/TxOverPowerFaultMinor.cpp
  PowerFaults/src/TxOverPowerMajorFaultOwner.cpp
  PowerFaults/src/TxOverPowerMinorFaultOwner.cpp
  PowerFaults/src/TxPowerMeasurementFaultMajor.cpp
  PowerFaults/src/TxUnderPowerFaultMinor.cpp
  PowerFaults/src/TxUnderPowerMinorFaultOwner.cpp
  TemperatureFaults/src/BoardTxOverTemperatureFaultMajor.cpp
  TemperatureFaults/src/BoardTxOverTemperatureFaultMinor.cpp
  TemperatureFaults/src/BoardTxUnderTemperatureFaultMajor.cpp
  TemperatureFaults/src/OverTempMajorFaultOwner.cpp
  TemperatureFaults/src/OverTempMinorFaultOwner.cpp
  TemperatureFaults/src/PaOverTemperatureFaultMajor.cpp
  TemperatureFaults/src/PaOverTemperatureFaultMinor.cpp
  TemperatureFaults/src/PaUnderTemperatureFaultMajor.cpp
  TemperatureFaults/src/UnderTempMajorFaultOwner.cpp
  orxPort/src/Zcu111RrhSRxPort.cpp
  pa/src/Zcu111RrhPaSingleton.cpp
)

install(TARGETS hardware-zcu111-radio DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  Faults/inc/RrhFaults.h
  OtherFaults/inc/DpdPllLockFaultMajor.h
  OtherFaults/inc/DpdPllLockMajorFaultOwner.h
  OtherFaults/inc/DpdTxFaultMajor.h
  OtherFaults/inc/DpdTxFaultMinor.h
  OtherFaults/inc/HeartBeatFaultMajor.h
  OtherFaults/inc/HeartBeatMajorFaultOwner.h
  OtherFaults/inc/PclTxConvergenceFaultMajor.h
  OtherFaults/inc/PclTxMajorFaultOwner.h
  OtherFaults/inc/PclTxOverPowerFaultMajor.h
  OtherFaults/inc/PopTripMajorFaultOwner.h
  OtherFaults/inc/PopTripTxFaultMajor.h
  OtherFaults/inc/RefPllLockFaultMajor.h
  OtherFaults/inc/RefPllLockMajorFaultOwner.h
  OtherFaults/inc/RxPllLockFaultMajor.h
  OtherFaults/inc/RxPllLockMajorFaultOwner.h
  OtherFaults/inc/SrlMajorFaultOwner.h
  OtherFaults/inc/SrlTxFaultMajor.h
  OtherFaults/inc/TxPllLockFaultMajor.h
  OtherFaults/inc/TxPllLockMajorFaultOwner.h
  OtherFaults/inc/VswrTxFaultMajor.h
  PowerFaults/inc/TxOverPowerFaultMajor.h
  PowerFaults/inc/TxOverPowerFaultMinor.h
  PowerFaults/inc/TxOverPowerMajorFaultOwner.h
  PowerFaults/inc/TxOverPowerMinorFaultOwner.h
  PowerFaults/inc/TxPowerMeasurementFaultMajor.h
  PowerFaults/inc/TxUnderPowerFaultMinor.h
  PowerFaults/inc/TxUnderPowerMinorFaultOwner.h
  TemperatureFaults/inc/BoardTxOverTemperatureFaultMajor.h
  TemperatureFaults/inc/BoardTxOverTemperatureFaultMinor.h
  TemperatureFaults/inc/BoardTxUnderTemperatureFaultMajor.h
  TemperatureFaults/inc/OverTempMajorFaultOwner.h
  TemperatureFaults/inc/OverTempMinorFaultOwner.h
  TemperatureFaults/inc/PaOverTemperatureFaultMajor.h
  TemperatureFaults/inc/PaOverTemperatureFaultMinor.h
  TemperatureFaults/inc/PaUnderTemperatureFaultMajor.h
  TemperatureFaults/inc/UnderTempMajorFaultOwner.h
  orxPort/inc/Zcu111RrhSRxPort.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
