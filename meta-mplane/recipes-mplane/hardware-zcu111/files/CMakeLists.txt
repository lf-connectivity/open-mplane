# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(hardware-zcu111)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(Faults/inc)
include_directories(bootEnv/inc)
include_directories(carrier/inc)
include_directories(carrier/inc/ORAN)
include_directories(carrier/inc/CPRI)
include_directories(carrier/inc/CFR)
include_directories(carrier/inc/CarrierHardware)
include_directories(delay/inc)
include_directories(equaliser/inc)
include_directories(fpga/inc)
include_directories(led/inc)
include_directories(ports/inc)
include_directories(powermon/inc)
include_directories(psumon/inc)
include_directories(radio/inc)
include_directories(remoteProc/inc)
include_directories(resamplerData/inc)
include_directories(rfBandData/inc)
include_directories(rfconst/inc)
include_directories(rfdc/inc)
include_directories(rfdc/librfdc)

include_directories(../shared/zcu111-radio/Faults/inc)
include_directories(../shared/zcu111-radio/OtherFaults/inc)
include_directories(../shared/zcu111-radio/PowerFaults/inc)
include_directories(../shared/zcu111-radio/TemperatureFaults/inc)
include_directories(../shared/zcu111-radio/orxPort/inc)

add_library(hardware-zcu111
  Faults/src/RrhFaults.cpp
  Faults/src/RrhFaultsSingleton.cpp
  bootEnv/src/Zcu111BootEnv.cpp
  carrier/src/CFR/CpgStage.cpp
  carrier/src/CFR/PulseTable.cpp
  # TODO Add compile options for CPRI/ORAN
  #carrier/src/CPRI/Zcu111CarrierHardware.cpp
  carrier/src/ORAN/Zcu111CarrierHardware.cpp
  carrier/src/CarrierHardware/CarrierDelay.cpp
  carrier/src/CarrierHardware/ChainModel.cpp
  carrier/src/CarrierHardware/FibreChain.cpp
  carrier/src/CarrierHardware/FibreDelay.cpp
  carrier/src/CarrierHardware/FibreDelayMgr.cpp
  carrier/src/CarrierHardware/FibreModel.cpp
  carrier/src/CarrierHardware/FlexiChainInfo.cpp
  carrier/src/CarrierHardware/Zcu111CarrierTypes.cpp
  carrier/src/ORAN/Zcu111CarrierHardware.cpp
  carrier/src/Zcu111Carrier.cpp
  carrier/src/Zcu111CarrierCfrWorker.cpp
  carrier/src/Zcu111CarrierChainWorker.cpp
  carrier/src/Zcu111CarrierDpdCfrWorker.cpp
  carrier/src/Zcu111CarrierHardwareData.cpp
  carrier/src/Zcu111CarrierHardwareIeq.cpp
  carrier/src/Zcu111CarrierHardwareList.cpp
  carrier/src/Zcu111CarrierHardwareWeighting.cpp
  carrier/src/Zcu111CarrierListWorker.cpp
  carrier/src/Zcu111CarrierModel.cpp
  carrier/src/Zcu111CarrierServer.cpp
  carrier/src/Zcu111CpriCarrierDelayWorker.cpp
  carrier/src/Zcu111MultiCarrierDpdCfrWorker.cpp
  carrier/src/Zcu111OranCarrierDelayWorker.cpp
  delay/src/Zcu111Delay.cpp
  equaliser/src/Zcu111TxEqualiser.cpp
  fpga/src/Zcu111Ethernet10G.cpp
  fpga/src/Zcu111FpgaKernel.cpp
  fpga/src/Zcu111RtcIEEE1588.cpp
  led/src/Zcu111Led.cpp
  ports/src/Zcu111RxPort.cpp
  ports/src/Zcu111SRxPort.cpp
  ports/src/Zcu111TxPort.cpp
  ports/src/Zcu111TxPortUsingSrxPowerMeasurement.cpp
  powermon/src/PowerMon.cpp
  psumon/src/PsuAlarm.cpp
  psumon/src/PsuMon.cpp
  radio/src/Zcu111Devices.cpp
  radio/src/Zcu111DevicesFactory.cpp
  radio/src/Zcu111GpioExp.cpp
  radio/src/Zcu111HardwareSettings.cpp
  radio/src/Zcu111Modules.cpp
  radio/src/Zcu111Radio.cpp
  radio/src/Zcu111RadioInfo.cpp
  radio/src/Zcu111RxAgc.cpp
  radio/src/Zcu111SRxPort.cpp
  remoteProc/src/Zcu111EmbeddedMgr.cpp
  resamplerData/src/Zcu111RxResamplerConfig.cpp
  resamplerData/src/Zcu111TxResamplerConfig.cpp
  rfBandData/src/Zcu111RxRfBandConfig.cpp
  rfBandData/src/Zcu111TxRfBandConfig.cpp
  rfconst/src/Zcu111RfConst.cpp
  rfdc/src/Rfdc-off-target.cpp
  rfdc/src/Rfdc.cpp
  rfdc/src/RfdcRxSynthDriver.cpp
  rfdc/src/RfdcSynthDriver.cpp
  rfdc/src/RfdcTxSynthDriver.cpp
  sysReboot-factory/src/Zcu111SystemRebootSingleton.cpp
)

install(TARGETS hardware-zcu111 DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  # RrhFaults.h is included in hardware-zcu111-radio
  #Faults/inc/RrhFaults.h
  bootEnv/inc/Zcu111BootEnv.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_LTE_10MHz_15kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_LTE_15MHz_15kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_LTE_20MHz_15kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_LTE_5MHz_15kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_10MHz_15kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_10MHz_30kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_10MHz_60kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_15MHz_15kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_15MHz_30kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_15MHz_60kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_20MHz_15kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_20MHz_30kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_20MHz_60kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_25MHz_15kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_25MHz_30kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_25MHz_60kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_30MHz_15kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_30MHz_30kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_30MHz_60kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_5MHz_15kHz.h
  carrier/inc/CFR/CfrCancellationPulses/CancelPulse_NRFR1_5MHz_30kHz.h
  carrier/inc/CFR/CpgStage.h
  carrier/inc/CFR/PulseTable.h
  carrier/inc/CarrierHardware/CarrierDelay.h
  carrier/inc/CarrierHardware/ChainModel.h
  carrier/inc/CarrierHardware/FibreChain.h
  carrier/inc/CarrierHardware/FibreDelay.h
  carrier/inc/CarrierHardware/FibreDelayMgr.h
  carrier/inc/CarrierHardware/FibreModel.h
  carrier/inc/CarrierHardware/FlexiChainInfo.h
  carrier/inc/CarrierHardware/Zcu111CarrierTypes.h
  carrier/inc/Zcu111Carrier.h
  carrier/inc/Zcu111CarrierCfrWorker.h
  carrier/inc/Zcu111CarrierChainWorker.h
  carrier/inc/Zcu111CarrierDpdCfrWorker.h
  carrier/inc/Zcu111CarrierHardware.h
  carrier/inc/Zcu111CarrierHardwareData.h
  carrier/inc/Zcu111CarrierHardwareIeq.h
  carrier/inc/Zcu111CarrierHardwareList.h
  carrier/inc/Zcu111CarrierHardwareWeighting.h
  carrier/inc/Zcu111CarrierListWorker.h
  carrier/inc/Zcu111CarrierModel.h
  carrier/inc/Zcu111CarrierServer.h
  carrier/inc/Zcu111CpriCarrierDelayWorker.h
  carrier/inc/Zcu111MultiCarrierDpdCfrWorker.h
  carrier/inc/Zcu111OranCarrierDelayWorker.h
  delay/inc/Zcu111Delay.h
  equaliser/inc/Zcu111TxEqualiser.h
  fpga/inc/Zcu111Ethernet10G.h
  fpga/inc/Zcu111FpgaKernel.h
  fpga/inc/Zcu111RtcIEEE1588.h
  led/inc/Zcu111Led.h
  ports/inc/Zcu111RxPort.h
  ports/inc/Zcu111SRxPort.h
  ports/inc/Zcu111TxPort.h
  ports/inc/Zcu111TxPortUsingSrxPowerMeasurement.h
  powermon/inc/PowerMon.h
  psumon/inc/PsuAlarm.h
  psumon/inc/PsuMon.h
  radio/inc/Zcu111Devices.h
  radio/inc/Zcu111GpioExp.h
  radio/inc/Zcu111HardwareSettings.h
  radio/inc/Zcu111Modules.h
  radio/inc/Zcu111Radio.h
  radio/inc/Zcu111RadioInfo.h
  radio/inc/Zcu111RxAgc.h
  remoteProc/inc/Zcu111EmbeddedMgr.h
  resamplerData/inc/Zcu111RxResamplerConfig.h
  resamplerData/inc/Zcu111TxResamplerConfig.h
  rfBandData/inc/Zcu111RxRfBandConfig.h
  rfBandData/inc/Zcu111TxRfBandConfig.h
  rfconst/inc/Zcu111RfConst.h
  rfdc/inc/Rfdc.h
  rfdc/inc/RfdcAdcDriver.h
  rfdc/inc/RfdcRxSynthDriver.h
  rfdc/inc/RfdcSynthDriver.h
  rfdc/inc/RfdcTxSynthDriver.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY
  carrier/inc/CFR
  carrier/inc/ORAN
  carrier/inc/CPRI
  carrier/inc/CarrierHardware

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
