# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(services-common)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(AppControl/inc)
include_directories(AppMonService/inc)
include_directories(AppServices/inc)
include_directories(DigitalPowerService/inc)
include_directories(Discovery/inc)
include_directories(Dpd2Service/inc)
include_directories(DpdService/inc)
include_directories(DpdService/inc/data)
include_directories(EgAppControl/inc)
include_directories(FibreControlService/inc)
include_directories(ImageManagement/inc)
include_directories(MemMon/inc)
include_directories(NetworkingService/inc)
include_directories(TxService/inc)
include_directories(faultChange/inc)
include_directories(faultService/inc)
include_directories(rxService/inc)

add_library(services-common
  AppControl/src/AppControl.cpp
  AppMonService/src/AppMonService.cpp
  AppServices/src/AppServices.cpp
  DigitalPowerService/src/DigitalPowerService.cpp
  Discovery/src/Discovery.cpp
  Discovery/src/DiscoverySingleton.cpp
  Dpd2Service/src/Dpd2Service.cpp  
  DpdService/src/DpdControlBase.cpp
  DpdService/src/DpdControlTx.cpp
  DpdService/src/DpdPapr.cpp
  DpdService/src/DpdService.cpp
  DpdService/src/data/DpdAlarm.cpp
  DpdService/src/data/DpdData.cpp
  DpdService/src/data/DpdInfo.cpp
  DpdService/src/data/DpdPowerMeasure.cpp
  DpdService/src/data/DpdTxpower.cpp
  DpdService/src/data/DpdVswr.cpp
  EgAppControl/src/CommonServices.cpp
  EgAppControl/src/EgAppControl.cpp
  FibreControlService/src/CpriController.cpp
  FibreControlService/src/CpriPortHandling.cpp
  FibreControlService/src/FibreControlService.cpp
  FibreControlService/src/ICpriOAM.cpp
  ImageManagement/src/CommonImageManagement.cpp
  MemMon/src/MemMon.cpp
  NetworkingService/src/NetworkingService.cpp
  TxService/src/TxPowerControl.cpp
  TxService/src/TxPowerControlFactory.cpp
  TxService/src/TxService.cpp
  TxService/src/VswrMon.cpp
  TxService/src/VswrMonFactory.cpp
  faultChange/src/FaultChange.cpp
  faultChange/src/FaultChangeSingleton.cpp
  faultService/src/FaultService.cpp
  rxService/src/RxService.cpp
)

install(TARGETS services-common DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  AppControl/inc/AppControl.h
  AppMonService/inc/AppMonService.h
  AppServices/inc/AppServices.h
  DigitalPowerService/inc/DigitalPowerService.h
  Discovery/inc/Discovery.h
  Dpd2Service/inc/Dpd2Service.h
  DpdService/inc/DpdControlBase.h
  DpdService/inc/DpdControlTx.h
  DpdService/inc/DpdPapr.h
  DpdService/inc/DpdService.h
  DpdService/inc/client/IDpdAlarmClient.h
  DpdService/inc/client/IDpdInfoClient.h
  DpdService/inc/client/IDpdTxpowerClient.h
  DpdService/inc/client/IDpdVswrClient.h
  DpdService/inc/data/DpdAlarm.h
  DpdService/inc/data/DpdData.h
  DpdService/inc/data/DpdInfo.h
  DpdService/inc/data/DpdPowerMeasure.h
  DpdService/inc/data/DpdTxpower.h
  DpdService/inc/data/DpdVswr.h
  DpdService/inc/data/IDpdAlarm.h
  DpdService/inc/data/IDpdData.h
  DpdService/inc/data/IDpdInfo.h
  DpdService/inc/data/IDpdPowerMeasure.h
  DpdService/inc/data/IDpdTxpower.h
  DpdService/inc/data/IDpdVswr.h
  DpdService/inc/subject/IDpdAlarmSubject.h
  DpdService/inc/subject/IDpdInfoSubject.h
  EgAppControl/inc/CommonServices.h
  EgAppControl/inc/EgAppControl.h
  FibreControlService/inc/CpriController.h
  FibreControlService/inc/CpriPortHandling.h
  FibreControlService/inc/FibreControlService.h
  FibreControlService/inc/ICpriOAM.h
  ImageManagement/inc/CommonImageManagement.h
  MemMon/inc/MemMon.h
  NetworkingService/inc/INetworkingService.h
  NetworkingService/inc/NetworkingService.h
  TxService/inc/TxPowerControl.h
  TxService/inc/TxService.h
  TxService/inc/VswrMon.h
  faultChange/inc/FaultChange.h
  faultService/inc/FaultService.h
  rxService/inc/RxService.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY
  DpdService/inc/client
  DpdService/inc/data/
  DpdService/inc/subject

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
