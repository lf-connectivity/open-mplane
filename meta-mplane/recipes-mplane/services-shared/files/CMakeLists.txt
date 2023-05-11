# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(services-shared)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(Alarms/inc)
include_directories(EthSniffer/inc)
include_directories(FibreControlService/inc)
include_directories(RadioDpd2Service/inc)
include_directories(RadioStateService/inc)
include_directories(TxService/inc)
include_directories(trace/inc)
include_directories(troubleshooting/inc)

add_library(services-shared
  Alarms/src/Cpri0MajorAlarm.cpp
  Alarms/src/HeartBeatAlarm.cpp
  Alarms/src/PaTempMajorAlarm.cpp
  Alarms/src/PaTempMinorAlarm.cpp
  Alarms/src/PllMajorAlarm.cpp
  Alarms/src/RadioTempMajorAlarm.cpp
  Alarms/src/RadioTempMinorAlarm.cpp
  Alarms/src/RrhAlarms.cpp
  Alarms/src/RrhAlarmsSingleton.cpp
  Alarms/src/RxMajorAlarm.cpp
  Alarms/src/TxBbIqAlarm.cpp
  Alarms/src/TxDegradedAlarm.cpp
  Alarms/src/TxDpdMinorAlarm.cpp
  Alarms/src/TxShutdownAlarm.cpp
  Alarms/src/VswrTxAlarm.cpp
  EthSniffer/src/PacketSniffer.cpp
  FibreControlService/src/RrhCpriFactory.cpp
  FibreControlService/src/RrhCpriPortHandling.cpp
  RadioDpd2Service/src/DpdMajorAlarm.cpp
  RadioDpd2Service/src/DpdMinorAlarm.cpp
  RadioDpd2Service/src/RadioDpd2Service.cpp
  RadioStateService/src/RadioStateFactory.cpp
  RadioStateService/src/RadioStateService.cpp
  TxService/src/RrhTxPowerControl.cpp
  TxService/src/RrhTxPowerControlFactory.cpp
  trace/src/TraceExampleFile.cpp
  trace/src/TraceHelper.cpp
  troubleshooting/src/TroubleshootCarrierFile.cpp
  troubleshooting/src/TroubleshootCarrierhwFile.cpp
  troubleshooting/src/TroubleshootHelper.cpp
  troubleshooting/src/TroubleshootRxFile.cpp
  troubleshooting/src/TroubleshootTxFile.cpp
)

install(TARGETS services-shared DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  Alarms/inc/Cpri0MajorAlarm.h
  Alarms/inc/HeartBeatMajorAlarm.h
  Alarms/inc/PaTempMajorAlarm.h
  Alarms/inc/PaTempMinorAlarm.h
  Alarms/inc/PllMajorAlarm.h
  Alarms/inc/RadioTempMajorAlarm.h
  Alarms/inc/RadioTempMinorAlarm.h
  Alarms/inc/RrhAlarms.h
  Alarms/inc/RxMajorAlarm.h
  Alarms/inc/TxBbIqAlarm.h
  Alarms/inc/TxDegradedAlarm.h
  Alarms/inc/TxDpdMinorAlarm.h
  Alarms/inc/TxShutdownAlarm.h
  Alarms/inc/VswrTxAlarm.h
  EthSniffer/inc/IPacketSniffer.h
  EthSniffer/inc/PacketSniffer.h
  FibreControlService/inc/RrhCpriPortHandling.h
  RadioDpd2Service/inc/DpdMajorAlarm.h
  RadioDpd2Service/inc/DpdMinorAlarm.h
  RadioDpd2Service/inc/RadioDpd2Service.h
  RadioStateService/inc/RadioStateService.h
  TxService/inc/RrhTxPowerControl.h
  trace/inc/TraceExampleFile.h
  trace/inc/TraceHelper.h
  troubleshooting/inc/TroubleshootCarrierFile.h
  troubleshooting/inc/TroubleshootCarrierhwFile.h
  troubleshooting/inc/TroubleshootHelper.h
  troubleshooting/inc/TroubleshootRxFile.h
  troubleshooting/inc/TroubleshootTxFile.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
