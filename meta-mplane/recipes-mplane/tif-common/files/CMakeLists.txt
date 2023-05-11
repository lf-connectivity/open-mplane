# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(tif-common)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(Rti/inc)
include_directories(../tif/common/Model/inc)
include_directories(../tif/helper/common/Model/inc)
include_directories(../tif/helper/common/core/inc)
include_directories(helper/common/Model/inc)
include_directories(helper/common/core/inc)

add_library(tif-common
  # bin-src files are used for a standalone executable Rti
  #Rti/bin-src/RtiMain.cpp
  #Rti/bin-src/TestInterfaceFactory.cpp
  Rti/src/Ati.cpp
  Rti/src/CmdNode/DirCmd.cpp
  Rti/src/CmdNode/EntryCmd.cpp
  Rti/src/Nodes/DirClass.cpp
  Rti/src/Nodes/EntryFunc.cpp
  Rti/src/Nodes/EntryVar.cpp
  Rti/src/Nodes/RtiDirEntry.cpp
  Rti/src/Nodes/TestReadVar.cpp
  Rti/src/Nodes/TestVar.cpp
  Rti/src/Nodes/TestWriteVar.cpp
  Rti/src/RtiMsgEditor.cpp
  Rti/src/RtiMsgHandler.cpp
  Rti/src/RtiSettings.cpp
  Rti/src/RtiTelnet.cpp
  Rti/src/ScriptsNode/DirScripts.cpp
  Rti/src/ScriptsNode/DirScriptsBase.cpp
  Rti/src/ScriptsNode/EntryScripts.cpp
  Rti/src/SettingsNode/EntrySettings.cpp
  Rti/src/TestInterfaceBase.cpp
  Rti/src/Tif.cpp
  helper/common/Model/src/DiscoveryTestHelper.cpp
  helper/common/Model/src/DpdTestHelper.cpp
  helper/common/core/src/FpgaCommsHelper.cpp
  helper/common/core/src/SettingsHelper.cpp
  helper/common/core/src/SharedArbTestHelper.cpp
  helper/common/core/src/TcpPortHelper.cpp
  ../tif/helper/common/Model/src/AgcTestHelper.cpp
  ../tif/helper/common/Model/src/AlarmsTestHelper.cpp
  ../tif/helper/common/Model/src/CalTestHelper.cpp
  ../tif/helper/common/Model/src/CarrierFreqOffsetTestHelper.cpp
  ../tif/helper/common/Model/src/CarrierTestHelper.cpp
  ../tif/helper/common/Model/src/CfrTestHelper.cpp
  ../tif/helper/common/Model/src/CifTestHelper.cpp
  ../tif/helper/common/Model/src/DelaysTestHelper.cpp
  ../tif/helper/common/Model/src/DevicesRxadcTestHelper.cpp
  ../tif/helper/common/Model/src/DpdCtrlTestHelper.cpp
  ../tif/helper/common/Model/src/EmbeddedTestHelper.cpp
  ../tif/helper/common/Model/src/EqualiserTestHelper.cpp
  ../tif/helper/common/Model/src/FibreTestHelper.cpp
  ../tif/helper/common/Model/src/FpgaTestHelper.cpp
  ../tif/helper/common/Model/src/FreqConstTestHelper.cpp
  ../tif/helper/common/Model/src/FtpTestHelper.cpp
  ../tif/helper/common/Model/src/GpioTestHelper.cpp
  ../tif/helper/common/Model/src/HeartbeatTestHelper.cpp
  ../tif/helper/common/Model/src/I2cTestHelper.cpp
  ../tif/helper/common/Model/src/ImagesAppTestHelper.cpp
  ../tif/helper/common/Model/src/ImagesFpgaTestHelper.cpp
  ../tif/helper/common/Model/src/ImagesLibTestHelper.cpp
  ../tif/helper/common/Model/src/ImagesOsTestHelper.cpp
  ../tif/helper/common/Model/src/ImagesTestHelper.cpp
  ../tif/helper/common/Model/src/IpListTestHelper.cpp
  ../tif/helper/common/Model/src/IpTestHelper.cpp
  ../tif/helper/common/Model/src/LedTestHelper.cpp
  ../tif/helper/common/Model/src/OranFpgaTestHelper.cpp
  ../tif/helper/common/Model/src/PaTestHelper.cpp
  ../tif/helper/common/Model/src/PsuTestHelper.cpp
  ../tif/helper/common/Model/src/RegDevicesTestHelper.cpp
  ../tif/helper/common/Model/src/RxPortTestHelper.cpp
  ../tif/helper/common/Model/src/SrxPortTestHelper.cpp
  ../tif/helper/common/Model/src/SystemBootTestHelper.cpp
  ../tif/helper/common/Model/src/SystemConfigTestHelper.cpp
  ../tif/helper/common/Model/src/SystemIpTestHelper.cpp
  ../tif/helper/common/Model/src/SystemLoggingTestHelper.cpp
  ../tif/helper/common/Model/src/SystemMemTestHelper.cpp
  ../tif/helper/common/Model/src/SystemTcpTestHelper.cpp
  ../tif/helper/common/Model/src/SystemTestHelper.cpp
  ../tif/helper/common/Model/src/TxPclTestHelper.cpp
  ../tif/helper/common/Model/src/TxPortTestHelper.cpp
  ../tif/helper/common/Model/src/VswrTestHelper.cpp
  ../tif/helper/common/core/src/PowerSaver.cpp
)

install(TARGETS tif-common DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  Rti/inc/Ati.h
  Rti/inc/CmdNode/DirCmd.h
  Rti/inc/CmdNode/EntryCmd.h
  Rti/inc/IRtiMsgParser.h
  Rti/inc/IRtiSettings.h
  Rti/inc/ITelnet.h
  Rti/inc/ITif.h
  Rti/inc/Nodes/DirClass.h
  Rti/inc/Nodes/EntryFunc.h
  Rti/inc/Nodes/EntryVar.h
  Rti/inc/Nodes/RtiDirEntry.h
  Rti/inc/Nodes/TestReadVar.h
  Rti/inc/Nodes/TestVar.h
  Rti/inc/Nodes/TestWriteVar.h
  Rti/inc/RtiMsgEditor.h
  Rti/inc/RtiMsgHandler.h
  Rti/inc/RtiSettings.h
  Rti/inc/RtiTelnet.h
  Rti/inc/ScriptsNode/DirScripts.h
  Rti/inc/ScriptsNode/DirScriptsBase.h
  Rti/inc/ScriptsNode/EntryScripts.h
  Rti/inc/SettingsNode/EntrySettings.h
  Rti/inc/TestInterfaceBase.h
  Rti/inc/TestInterfaceFactory.h
  helper/common/Model/inc/DiscoveryTestHelper.h
  helper/common/Model/inc/DpdTestHelper.h
  helper/common/core/inc/FpgaCommsHelper.h
  helper/common/core/inc/SettingsHelper.h
  helper/common/core/inc/SharedArbTestHelper.h
  helper/common/core/inc/TcpPortHelper.h
  ../tif/helper/common/Model/inc/AgcTestHelper.h
  ../tif/helper/common/Model/inc/AlarmsTestHelper.h
  ../tif/helper/common/Model/inc/ArbCaptureTestHelper.h
  ../tif/helper/common/Model/inc/ArbCpriTestHelper.h
  ../tif/helper/common/Model/inc/ArbPlaybackTestHelper.h
  ../tif/helper/common/Model/inc/ArbRfTestHelper.h
  ../tif/helper/common/Model/inc/ArbTestHelper.h
  ../tif/helper/common/Model/inc/BistTestHelper.h
  ../tif/helper/common/Model/inc/BncCtlTestHelper.h
  ../tif/helper/common/Model/inc/Br8LedTestHelper.h
  ../tif/helper/common/Model/inc/CalTestHelper.h
  ../tif/helper/common/Model/inc/CarrierFreqOffsetTestHelper.h
  ../tif/helper/common/Model/inc/CarrierTestHelper.h
  ../tif/helper/common/Model/inc/CfrTestHelper.h
  ../tif/helper/common/Model/inc/CifTestHelper.h
  ../tif/helper/common/Model/inc/CpriDelaysTestHelper.h
  ../tif/helper/common/Model/inc/CpriTestHelper.h
  ../tif/helper/common/Model/inc/DelaysTestHelper.h
  ../tif/helper/common/Model/inc/DevicesRxadcTestHelper.h
  ../tif/helper/common/Model/inc/DpdCtrlTestHelper.h
  ../tif/helper/common/Model/inc/EmbeddedTestHelper.h
  ../tif/helper/common/Model/inc/EqualiserTestHelper.h
  ../tif/helper/common/Model/inc/FibreTestHelper.h
  ../tif/helper/common/Model/inc/FpgaTestHelper.h
  ../tif/helper/common/Model/inc/FreqConstTestHelper.h
  ../tif/helper/common/Model/inc/FtpTestHelper.h
  ../tif/helper/common/Model/inc/GpioTestHelper.h
  ../tif/helper/common/Model/inc/HeartbeatTestHelper.h
  ../tif/helper/common/Model/inc/I2cTestHelper.h
  ../tif/helper/common/Model/inc/ImagesAppTestHelper.h
  ../tif/helper/common/Model/inc/ImagesFpgaTestHelper.h
  ../tif/helper/common/Model/inc/ImagesLibTestHelper.h
  ../tif/helper/common/Model/inc/ImagesOsTestHelper.h
  ../tif/helper/common/Model/inc/ImagesTestHelper.h
  ../tif/helper/common/Model/inc/IpListTestHelper.h
  ../tif/helper/common/Model/inc/IpTestHelper.h
  ../tif/helper/common/Model/inc/JdsuTestHelper.h
  ../tif/helper/common/Model/inc/LedTestHelper.h
  ../tif/helper/common/Model/inc/LicenseFeatureTestHelper.h
  ../tif/helper/common/Model/inc/LicenseKeyTestHelper.h
  ../tif/helper/common/Model/inc/LicenseTestHelper.h
  ../tif/helper/common/Model/inc/OranFpgaTestHelper.h
  ../tif/helper/common/Model/inc/PaTestHelper.h
  ../tif/helper/common/Model/inc/PsuTestHelper.h
  ../tif/helper/common/Model/inc/QmcTestHelper.h
  ../tif/helper/common/Model/inc/RegDevicesTestHelper.h
  ../tif/helper/common/Model/inc/RxPortTestHelper.h
  ../tif/helper/common/Model/inc/SrxPortTestHelper.h
  ../tif/helper/common/Model/inc/SystemBootTestHelper.h
  ../tif/helper/common/Model/inc/SystemConfigTestHelper.h
  ../tif/helper/common/Model/inc/SystemIpTestHelper.h
  ../tif/helper/common/Model/inc/SystemLoggingTestHelper.h
  ../tif/helper/common/Model/inc/SystemMemTestHelper.h
  ../tif/helper/common/Model/inc/SystemTcpTestHelper.h
  ../tif/helper/common/Model/inc/SystemTestHelper.h
  ../tif/helper/common/Model/inc/TenMHzRefTestHelper.h
  ../tif/helper/common/Model/inc/TxPclTestHelper.h
  ../tif/helper/common/Model/inc/TxPortTestHelper.h
  ../tif/helper/common/Model/inc/UutTestHelper.h
  ../tif/helper/common/Model/inc/VswrTestHelper.h
  ../tif/helper/common/core/inc/PowerSaver.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY
  Rti/inc/ScriptsNode
  Rti/inc/CmdNode
  Rti/inc/Nodes
  Rti/inc/SettingsNode

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
