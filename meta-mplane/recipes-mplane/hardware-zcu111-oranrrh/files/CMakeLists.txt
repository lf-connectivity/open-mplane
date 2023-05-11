# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(hardware-zcu111-oranrrh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(FaultsCUPlane/inc)
include_directories(FibreDummy/inc)
include_directories(carrier/inc)
include_directories(freqconst/inc)
include_directories(radio/inc)
include_directories(regData/inc)
include_directories(txport/inc)

include_directories(../shared/zcu111-radio/Faults/inc)
include_directories(../shared/zcu111-radio/OtherFaults/inc)
include_directories(../shared/zcu111-radio/PowerFaults/inc)
include_directories(../shared/zcu111-radio/TemperatureFaults/inc)
include_directories(../shared/zcu111-radio/orxPort/inc)

add_library(hardware-zcu111-oranrrh
  FaultsCUPlane/src/FaultCUPlaneConnectivityMajor.cpp
  FaultsCUPlane/src/FaultCUPlaneConnectivityMinor.cpp
  FaultsCUPlane/src/FaultCUPlaneMsgContentMajor.cpp
  FaultsCUPlane/src/FaultCUPlaneMsgContentMinor.cpp
  FibreDummy/src/FibreDummy.cpp
  carrier-factories/src/Zcu111OranrrhCarrierHardwareDataSingleton.cpp
  carrier-factories/src/Zcu111OranrrhCarrierHardwareListSingleton.cpp
  carrier-factories/src/Zcu111OranrrhCarrierModelSingleton.cpp
  carrier-factories/src/Zcu111OranrrhCarrierServerSingleton.cpp
  carrier/src/Zcu111OranrrhCarrierHardwareData.cpp
  carrier/src/Zcu111OranrrhCarrierModel.cpp
  carrier/src/Zcu111OranrrhCarrierServer.cpp
  carrier/src/Zcu111OranrrhFreqPolicy.cpp
  freqconst/src/Zcu111RxFrequencyConst.cpp
  freqconst/src/Zcu111RxFrequencyConstFactory.cpp
  freqconst/src/Zcu111TxFrequencyConst.cpp
  freqconst/src/Zcu111TxFrequencyConstFactory.cpp
  radio/src/Zcu111OranrrhAldPortSingleton.cpp
  radio/src/Zcu111OranrrhBootEnvSingleton.cpp
  radio/src/Zcu111OranrrhCpriSingleton.cpp
  radio/src/Zcu111OranrrhEqualiserFactory.cpp
  radio/src/Zcu111OranrrhHardwareSettingsSingleton.cpp
  radio/src/Zcu111OranrrhLedControlFactory.cpp
  radio/src/Zcu111OranrrhRadio.cpp
  radio/src/Zcu111OranrrhRadioFactory.cpp
  radio/src/Zcu111OranrrhResamplerConfigSingleton.cpp
  radio/src/Zcu111OranrrhRfBandFactory.cpp
  radio/src/Zcu111OranrrhRfConstFactory.cpp
  radio/src/Zcu111OranrrhRxAgcSingleton.cpp
  radio/src/Zcu111OranrrhRxPortSingleton.cpp
  radio/src/Zcu111OranrrhSRxPortSingleton.cpp
  radio/src/Zcu111OranrrhSfpDataSingleton.cpp
  radio/src/Zcu111OranrrhTxPortSingleton.cpp
  radioConfig/src/OranrrhRadioConfigFactory.cpp
  regData/src/Zcu111OranRrhLmk04208InitData.cpp
  regData/src/Zcu111OranRrhLmx2594InitData.cpp
  regData/src/Zcu111OranRrhMcp23S17SpiInitData.cpp
  regData/src/Zcu111OranRrhRegData.cpp
  regData/src/Zcu111OranRrhRegDataSingleton.cpp
  regData/src/Zcu111OranRrhSI5382aI2cInitData.cpp
  sysClock-factory/src/Zcu111RrhSystemClockInputSingleton.cpp
  txport/src/Zcu111OranrrhTxPort.cpp

  ../shared/zcu111-radio/Faults/src/RrhFaults.cpp
  ../shared/zcu111-radio/Faults/src/RrhFaultsSingleton.cpp
  ../shared/zcu111-radio/OtherFaults/src/DpdPllLockFaultMajor.cpp
  ../shared/zcu111-radio/OtherFaults/src/DpdPllLockMajorFaultOwner.cpp
  ../shared/zcu111-radio/OtherFaults/src/DpdTxFaultMajor.cpp
  ../shared/zcu111-radio/OtherFaults/src/DpdTxFaultMinor.cpp
  ../shared/zcu111-radio/OtherFaults/src/HeartBeatFaultMajor.cpp
  ../shared/zcu111-radio/OtherFaults/src/HeartBeatFaultOwner.cpp
  ../shared/zcu111-radio/OtherFaults/src/PclTxConvergenceFaultMajor.cpp
  ../shared/zcu111-radio/OtherFaults/src/PclTxMajorFaultOwner.cpp
  ../shared/zcu111-radio/OtherFaults/src/PclTxOverPowerFaultMajor.cpp
  ../shared/zcu111-radio/OtherFaults/src/PopTripMajorFaultOwner.cpp
  ../shared/zcu111-radio/OtherFaults/src/PopTripTxFaultMajor.cpp
  ../shared/zcu111-radio/OtherFaults/src/RefPllLockFaultMajor.cpp
  ../shared/zcu111-radio/OtherFaults/src/RefPllLockMajorFaultOwner.cpp
  ../shared/zcu111-radio/OtherFaults/src/RxPllLockFaultMajor.cpp
  ../shared/zcu111-radio/OtherFaults/src/RxPllLockMajorFaultOwner.cpp
  ../shared/zcu111-radio/OtherFaults/src/SrlMajorFaultOwner.cpp
  ../shared/zcu111-radio/OtherFaults/src/SrlTxFaultMajor.cpp
  ../shared/zcu111-radio/OtherFaults/src/TxPllLockFaultMajor.cpp
  ../shared/zcu111-radio/OtherFaults/src/TxPllLockMajorFaultOwner.cpp
  ../shared/zcu111-radio/OtherFaults/src/VswrTxFaultMajor.cpp
  ../shared/zcu111-radio/PowerFaults/src/TxOverPowerFaultMajor.cpp
  ../shared/zcu111-radio/PowerFaults/src/TxOverPowerFaultMinor.cpp
  ../shared/zcu111-radio/PowerFaults/src/TxOverPowerMajorFaultOwner.cpp
  ../shared/zcu111-radio/PowerFaults/src/TxOverPowerMinorFaultOwner.cpp
  ../shared/zcu111-radio/PowerFaults/src/TxPowerMeasurementFaultMajor.cpp
  ../shared/zcu111-radio/PowerFaults/src/TxUnderPowerFaultMinor.cpp
  ../shared/zcu111-radio/PowerFaults/src/TxUnderPowerMinorFaultOwner.cpp
  ../shared/zcu111-radio/TemperatureFaults/src/BoardTxOverTemperatureFaultMajor.cpp
  ../shared/zcu111-radio/TemperatureFaults/src/BoardTxOverTemperatureFaultMinor.cpp
  ../shared/zcu111-radio/TemperatureFaults/src/BoardTxUnderTemperatureFaultMajor.cpp
  ../shared/zcu111-radio/TemperatureFaults/src/OverTempMajorFaultOwner.cpp
  ../shared/zcu111-radio/TemperatureFaults/src/OverTempMinorFaultOwner.cpp
  ../shared/zcu111-radio/TemperatureFaults/src/PaOverTemperatureFaultMajor.cpp
  ../shared/zcu111-radio/TemperatureFaults/src/PaOverTemperatureFaultMinor.cpp
  ../shared/zcu111-radio/TemperatureFaults/src/PaUnderTemperatureFaultMajor.cpp
  ../shared/zcu111-radio/TemperatureFaults/src/UnderTempMajorFaultOwner.cpp
  ../shared/zcu111-radio/orxPort/src/Zcu111RrhSRxPort.cpp
  ../shared/zcu111-radio/pa/src/Zcu111RrhPaSingleton.cpp

)

install(TARGETS hardware-zcu111-oranrrh DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  FaultsCUPlane/inc/FaultCUPlaneConnectivityMajor.h
  FaultsCUPlane/inc/FaultCUPlaneConnectivityMinor.h
  FaultsCUPlane/inc/FaultCUPlaneMsgContentMajor.h
  FaultsCUPlane/inc/FaultCUPlaneMsgContentMinor.h
  FibreDummy/inc/FibreDummy.h
  carrier/inc/Zcu111OranrrhCarrierHardwareData.h
  carrier/inc/Zcu111OranrrhCarrierModel.h
  carrier/inc/Zcu111OranrrhCarrierServer.h
  carrier/inc/Zcu111OranrrhFreqPolicy.h
  freqconst/inc/Zcu111RxFrequencyConst.h
  freqconst/inc/Zcu111TxFrequencyConst.h
  radio/inc/Zcu111OranrrhRadio.h
  regData/inc/Zcu111OranRrhRegData.h
  txport/inc/Zcu111OranrrhTxPort.h

  ../shared/zcu111-radio/Faults/inc/RrhFaults.h
  ../shared/zcu111-radio/OtherFaults/inc/DpdPllLockFaultMajor.h
  ../shared/zcu111-radio/OtherFaults/inc/DpdPllLockMajorFaultOwner.h
  ../shared/zcu111-radio/OtherFaults/inc/DpdTxFaultMajor.h
  ../shared/zcu111-radio/OtherFaults/inc/DpdTxFaultMinor.h
  ../shared/zcu111-radio/OtherFaults/inc/HeartBeatFaultMajor.h
  ../shared/zcu111-radio/OtherFaults/inc/HeartBeatMajorFaultOwner.h
  ../shared/zcu111-radio/OtherFaults/inc/PclTxConvergenceFaultMajor.h
  ../shared/zcu111-radio/OtherFaults/inc/PclTxMajorFaultOwner.h
  ../shared/zcu111-radio/OtherFaults/inc/PclTxOverPowerFaultMajor.h
  ../shared/zcu111-radio/OtherFaults/inc/PopTripMajorFaultOwner.h
  ../shared/zcu111-radio/OtherFaults/inc/PopTripTxFaultMajor.h
  ../shared/zcu111-radio/OtherFaults/inc/RefPllLockFaultMajor.h
  ../shared/zcu111-radio/OtherFaults/inc/RefPllLockMajorFaultOwner.h
  ../shared/zcu111-radio/OtherFaults/inc/RxPllLockFaultMajor.h
  ../shared/zcu111-radio/OtherFaults/inc/RxPllLockMajorFaultOwner.h
  ../shared/zcu111-radio/OtherFaults/inc/SrlMajorFaultOwner.h
  ../shared/zcu111-radio/OtherFaults/inc/SrlTxFaultMajor.h
  ../shared/zcu111-radio/OtherFaults/inc/TxPllLockFaultMajor.h
  ../shared/zcu111-radio/OtherFaults/inc/TxPllLockMajorFaultOwner.h
  ../shared/zcu111-radio/OtherFaults/inc/VswrTxFaultMajor.h
  ../shared/zcu111-radio/PowerFaults/inc/TxOverPowerFaultMajor.h
  ../shared/zcu111-radio/PowerFaults/inc/TxOverPowerFaultMinor.h
  ../shared/zcu111-radio/PowerFaults/inc/TxOverPowerMajorFaultOwner.h
  ../shared/zcu111-radio/PowerFaults/inc/TxOverPowerMinorFaultOwner.h
  ../shared/zcu111-radio/PowerFaults/inc/TxPowerMeasurementFaultMajor.h
  ../shared/zcu111-radio/PowerFaults/inc/TxUnderPowerFaultMinor.h
  ../shared/zcu111-radio/PowerFaults/inc/TxUnderPowerMinorFaultOwner.h
  ../shared/zcu111-radio/TemperatureFaults/inc/BoardTxOverTemperatureFaultMajor.h
  ../shared/zcu111-radio/TemperatureFaults/inc/BoardTxOverTemperatureFaultMinor.h
  ../shared/zcu111-radio/TemperatureFaults/inc/BoardTxUnderTemperatureFaultMajor.h
  ../shared/zcu111-radio/TemperatureFaults/inc/OverTempMajorFaultOwner.h
  ../shared/zcu111-radio/TemperatureFaults/inc/OverTempMinorFaultOwner.h
  ../shared/zcu111-radio/TemperatureFaults/inc/PaOverTemperatureFaultMajor.h
  ../shared/zcu111-radio/TemperatureFaults/inc/PaOverTemperatureFaultMinor.h
  ../shared/zcu111-radio/TemperatureFaults/inc/PaUnderTemperatureFaultMajor.h
  ../shared/zcu111-radio/TemperatureFaults/inc/UnderTempMajorFaultOwner.h
  ../shared/zcu111-radio/orxPort/inc/Zcu111RrhSRxPort.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
