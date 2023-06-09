# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(yang-manager-server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

include_directories(ConfigParser/inc)
include_directories(Dot1agdMonitoringService/inc)
include_directories(LinuxPtpService/inc)
include_directories(NetopeerMonitoringService/inc)
include_directories(OranAlarms/inc)
include_directories(OranDelays/inc)
include_directories(OranFaults/inc)
include_directories(OranFm/inc)
include_directories(OranNetworking/inc)
include_directories(OranPerformanceMgmt/inc)
include_directories(OranSupervision/inc)
include_directories(RadioDatastore/inc)
include_directories(services-ORANRRH/inc)
include_directories(services-ZCU111-FBC-ORANRRH/inc)
include_directories(ssh/inc)
include_directories(yang-ZCU111-FBC-ORANRRH/inc)
include_directories(yang-handlers/inc)
include_directories(yang-manager-service/inc)
include_directories(yang-manager/inc)
include_directories(yang-models/inc)
include_directories(yang-sysrepo/inc)

add_library(yang-manager-server
  ConfigParser/src/YangConfig.cpp
  ConfigParser/src/YangConfigDownload.cpp
  ConfigParser/src/YangConfigParser.cpp
  ConfigParser/src/YangConfigSingleton.cpp
  ConfigParser/src/YangElement.cpp
  ConfigParser/src/YangElementFactories.cpp
  Dot1agdMonitoringService/src/Dot1agdMonService.cpp
  Dot1agdMonitoringService/src/Dot1agdMonServiceSingleton.cpp
  LinuxPtpService/src/LinuxPtpService.cpp
  LinuxPtpService/src/LinuxPtpServiceSingleton.cpp
  NetopeerMonitoringService/src/NetopeerMonService.cpp
  NetopeerMonitoringService/src/NetopeerMonServiceSingleton.cpp
  OranAlarms/src/CUPlaneConnectivityMajorAlarm.cpp
  OranAlarms/src/CUPlaneConnectivityMinorAlarm.cpp
  OranAlarms/src/OranAlarms.cpp
  OranAlarms/src/OranAlarmsSingleton.cpp
  OranDelays/src/OranDelays.cpp
  OranDelays/src/OranDelaysSingleton.cpp
  OranFaults/src/CUPlaneConnectivityMajorFault.cpp
  OranFaults/src/CUPlaneConnectivityMinorFault.cpp
  OranFaults/src/CUPlaneMsgContentMajorFault.cpp
  OranFaults/src/CUPlaneMsgContentMinorFault.cpp
  OranFaults/src/OranFaults.cpp
  OranFaults/src/OranFaultsSingleton.cpp
  OranFm/src/FaultConfigFile.cpp
  OranFm/src/OranAlarmEntry.cpp
  OranFm/src/OranAlarmMapping.cpp
  OranFm/src/OranFaultConfigData.cpp
  OranFm/src/OranFm.cpp
  OranNetworking/src/DhcpOptions.cpp
  OranNetworking/src/OranNetAddrDhcp.cpp
  OranNetworking/src/OranNetAddrDhcpVlan.cpp
  OranPerformanceMgmt/src/PerformanceMgmtService.cpp
  OranPerformanceMgmt/src/PerformanceMgmtSingleton.cpp
  OranPerformanceMgmt/src/RxWindowMeasurement.cpp
  OranPerformanceMgmt/src/TransceiverMeasurement.cpp
  OranSupervision/src/CUPlaneConnectService.cpp
  OranSupervision/src/CUPlaneConnectServiceSingleton.cpp
  OranSupervision/src/CUPlaneMonitor.cpp
  OranSupervision/src/CUPlaneMonitorSingleton.cpp
  OranSupervision/src/MPlaneConnectivityService.cpp
  OranSupervision/src/MPlaneConnectivityServiceSingleton.cpp
  RadioDatastore/src/RadioDatastore.cpp
  logging/src/LoggerFactory.cpp
  services-ORANRRH/src/YangOranrrhServices.cpp
  services-ZCU111-FBC-ORANRRH/src/YangZcu111FbcOranrrhServices.cpp
  services-ZCU111-FBC-ORANRRH/src/YangZcu111ServicesFactory.cpp
  services-ZCU111-FBC-ORANRRH/src/Zcu111FbcLinuxPtpServiceSingleton.cpp
  ssh/src/SftpMgr.cpp
  ssh/src/SftpSession.cpp
  ssh/src/SshSession.cpp
  yang-ZCU111-FBC-ORANRRH/src/CallbackORanSoftwareMgr.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerIetfHardware.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerIetfInterfaces.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerIetfNetconfAcm.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerIetfNetconfServer.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerMgr.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanAld.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanAldPort.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanDelayManagement.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanDhcp.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanEcpriDelay.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanFileManagement.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanFm.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanLbm.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanLog.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanModuleCap.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanMplaneInt.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanOperations.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanPerformanceMgmt.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanProcessingElement.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanSoftwareManagement.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanSupervision.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanSync.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanSyncNotif.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanTrace.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanTransceiver.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanTroubleshooting.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanUplaneConf.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanUserMgmt.cpp
  yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhYangCarrierMgr.cpp
  yang-handlers/src/XpathUtils.cpp
  yang-handlers/src/YangCarrierMgr.cpp
  yang-handlers/src/YangHandler.cpp
  yang-handlers/src/YangHandlerMgr.cpp
  yang-handlers/src/YangPersist.cpp
  yang-manager-service/src/YangMgrService.cpp
  yang-manager/src/YangModule.cpp
  yang-manager/src/YangModuleMgr.cpp
  yang-manager/src/YangParam.cpp
  yang-manager/src/YangParamUtils.cpp
  yang-manager/src/YangUtils.cpp
  yang-models/src/YangMgrServer.cpp
  yang-models/src/YangModuleIanaHardware.cpp
  yang-models/src/YangModuleIanaIfType.cpp
  yang-models/src/YangModuleIetfCryptoTypes.cpp
  yang-models/src/YangModuleIetfDhcpv6Types.cpp
  yang-models/src/YangModuleIetfHardware.cpp
  yang-models/src/YangModuleIetfInetTypes.cpp
  yang-models/src/YangModuleIetfInterfaces.cpp
  yang-models/src/YangModuleIetfIp.cpp
  yang-models/src/YangModuleIetfNetconfAcm.cpp
  yang-models/src/YangModuleIetfNetconfMonitoring.cpp
  yang-models/src/YangModuleIetfYangLibrary.cpp
  yang-models/src/YangModuleIetfYangTypes.cpp
  yang-models/src/YangModuleORanAld.cpp
  yang-models/src/YangModuleORanAldPort.cpp
  yang-models/src/YangModuleORanAntennaCalibration.cpp
  yang-models/src/YangModuleORanCompressionFactors.cpp
  yang-models/src/YangModuleORanDelayManagement.cpp
  yang-models/src/YangModuleORanDhcp.cpp
  yang-models/src/YangModuleORanEcpriDelay.cpp
  yang-models/src/YangModuleORanExternalio.cpp
  yang-models/src/YangModuleORanFan.cpp
  yang-models/src/YangModuleORanFileManagement.cpp
  yang-models/src/YangModuleORanFm.cpp
  yang-models/src/YangModuleORanHardware.cpp
  yang-models/src/YangModuleORanInterfaces.cpp
  yang-models/src/YangModuleORanLaa.cpp
  yang-models/src/YangModuleORanLaaOperations.cpp
  yang-models/src/YangModuleORanLbm.cpp
  yang-models/src/YangModuleORanModuleCap.cpp
  yang-models/src/YangModuleORanMplaneInt.cpp
  yang-models/src/YangModuleORanOperations.cpp
  yang-models/src/YangModuleORanPerformanceManagement.cpp
  yang-models/src/YangModuleORanProcessingElement.cpp
  yang-models/src/YangModuleORanSoftwareManagement.cpp
  yang-models/src/YangModuleORanSupervision.cpp
  yang-models/src/YangModuleORanSync.cpp
  yang-models/src/YangModuleORanTrace.cpp
  yang-models/src/YangModuleORanTransceiver.cpp
  yang-models/src/YangModuleORanTroubleshooting.cpp
  yang-models/src/YangModuleORanUdpEcho.cpp
  yang-models/src/YangModuleORanUplaneConf.cpp
  yang-models/src/YangModuleORanUsermgmt.cpp
  yang-sysrepo/src/LeafContainer.cpp
  yang-sysrepo/src/RadioDatastoreSysrepo.cpp
  yang-sysrepo/src/SysrepoGetitemsCallback.cpp
  yang-sysrepo/src/SysrepoUtils.cpp
  yang-sysrepo/src/YangHandlerSysrepo.cpp
  yang-sysrepo/src/YangHandlerSysrepo/HandlerCallback.cpp
  yang-sysrepo/src/YangHandlerSysrepo/RpcCallback.cpp
  yang-sysrepo/src/YangHandlerSysrepoUnlogged.cpp
  yang-sysrepo/src/YangParamSysrepo.cpp
  yang-sysrepo/src/YangUserAuth.cpp
)

install(TARGETS yang-manager-server DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  ConfigParser/inc/YangConfig.h
  ConfigParser/inc/YangConfigDownload.h
  ConfigParser/inc/YangConfigParser.h
  ConfigParser/inc/YangElement.h
  Dot1agdMonitoringService/inc/Dot1agdMonService.h
  LinuxPtpService/inc/LinuxPtpService.h
  NetopeerMonitoringService/inc/NetopeerMonService.h
  OranAlarms/inc/CUPlaneConnectivityMajorAlarm.h
  OranAlarms/inc/CUPlaneConnectivityMinorAlarm.h
  OranAlarms/inc/OranAlarms.h
  OranDelays/inc/OranDelays.h
  OranFaults/inc/CUPlaneConnectivityMajorFault.h
  OranFaults/inc/CUPlaneConnectivityMinorFault.h
  OranFaults/inc/CUPlaneMsgContentMajorFault.h
  OranFaults/inc/CUPlaneMsgContentMinorFault.h
  OranFaults/inc/OranFaults.h
  OranFm/inc/FaultConfigFile.h
  OranFm/inc/OranAlarmEntry.h
  OranFm/inc/OranAlarmMapping.h
  OranFm/inc/OranFaultConfigData.h
  OranFm/inc/OranFm.h
  OranNetworking/inc/DhcpOptions.h
  OranNetworking/inc/OranNetAddrDhcp.h
  OranNetworking/inc/OranNetAddrDhcpVlan.h
  OranPerformanceMgmt/inc/PerformanceMgmtService.h
  OranPerformanceMgmt/inc/RxWindowMeasurement.h
  OranPerformanceMgmt/inc/TransceiverMeasurement.h
  OranSupervision/inc/CUPlaneConnectService.h
  OranSupervision/inc/CUPlaneMonitor.h
  OranSupervision/inc/MPlaneConnectivityService.h
  RadioDatastore/inc/RadioDatastore.h
  services-ORANRRH/inc/YangOranrrhServices.h
  services-ZCU111-FBC-ORANRRH/inc/YangZcu111FbcOranrrhServices.h
  ssh/inc/SftpMgr.h
  ssh/inc/SftpSession.h
  ssh/inc/SshSession.h
  yang-ZCU111-FBC-ORANRRH/inc/CallbackORanSoftwareMgr.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerIetfHardware.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerIetfInterfaces.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerIetfNetconfAcm.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerIetfNetconfServer.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerMgr.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanAld.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanAldPort.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanDelayManagement.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanDhcp.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanEcpriDelay.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanFileManagement.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanFm.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanLbm.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanLog.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanModuleCap.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanMplaneInt.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanOperations.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanPerformanceMgmt.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanProcessingElement.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanSoftwareManagement.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanSupervision.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanSync.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanSyncNotif.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanTrace.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanTransceiver.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanTroubleshooting.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanUplaneConf.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhHandlerORanUserMgmt.h
  yang-ZCU111-FBC-ORANRRH/inc/Zcu111FbcOranrrhYangCarrierMgr.h
  yang-handlers/inc/XpathUtils.h
  yang-handlers/inc/YangCarrierMgr.h
  yang-handlers/inc/YangDelayManagementMgr.h
  yang-handlers/inc/YangHandler.h
  yang-handlers/inc/YangHandlerMgr.h
  yang-handlers/inc/YangPersist.h
  yang-manager-service/inc/YangMgrService.h
  yang-manager/inc/YangModule.h
  yang-manager/inc/YangModuleMgr.h
  yang-manager/inc/YangParam.h
  yang-manager/inc/YangParamUtils.h
  yang-manager/inc/YangTypes.h
  yang-manager/inc/YangUtils.h
  yang-models/inc/YangMgrServer.h
  yang-models/inc/YangModuleIanaHardware.h
  yang-models/inc/YangModuleIanaIfType.h
  yang-models/inc/YangModuleIetfCryptoTypes.h
  yang-models/inc/YangModuleIetfDhcpv6Types.h
  yang-models/inc/YangModuleIetfHardware.h
  yang-models/inc/YangModuleIetfInetTypes.h
  yang-models/inc/YangModuleIetfInterfaces.h
  yang-models/inc/YangModuleIetfIp.h
  yang-models/inc/YangModuleIetfNetconfAcm.h
  yang-models/inc/YangModuleIetfNetconfMonitoring.h
  yang-models/inc/YangModuleIetfYangLibrary.h
  yang-models/inc/YangModuleIetfYangTypes.h
  yang-models/inc/YangModuleORanAld.h
  yang-models/inc/YangModuleORanAldPort.h
  yang-models/inc/YangModuleORanAntennaCalibration.h
  yang-models/inc/YangModuleORanCompressionFactors.h
  yang-models/inc/YangModuleORanDelayManagement.h
  yang-models/inc/YangModuleORanDhcp.h
  yang-models/inc/YangModuleORanEcpriDelay.h
  yang-models/inc/YangModuleORanExternalio.h
  yang-models/inc/YangModuleORanFan.h
  yang-models/inc/YangModuleORanFileManagement.h
  yang-models/inc/YangModuleORanFm.h
  yang-models/inc/YangModuleORanHardware.h
  yang-models/inc/YangModuleORanInterfaces.h
  yang-models/inc/YangModuleORanLaa.h
  yang-models/inc/YangModuleORanLaaOperations.h
  yang-models/inc/YangModuleORanLbm.h
  yang-models/inc/YangModuleORanModuleCap.h
  yang-models/inc/YangModuleORanMplaneInt.h
  yang-models/inc/YangModuleORanOperations.h
  yang-models/inc/YangModuleORanPerformanceManagement.h
  yang-models/inc/YangModuleORanProcessingElement.h
  yang-models/inc/YangModuleORanSoftwareManagement.h
  yang-models/inc/YangModuleORanSupervision.h
  yang-models/inc/YangModuleORanSync.h
  yang-models/inc/YangModuleORanTrace.h
  yang-models/inc/YangModuleORanTransceiver.h
  yang-models/inc/YangModuleORanTroubleshooting.h
  yang-models/inc/YangModuleORanUdpEcho.h
  yang-models/inc/YangModuleORanUplaneConf.h
  yang-models/inc/YangModuleORanUsermgmt.h
  yang-sysrepo/inc/LeafContainer.h
  yang-sysrepo/inc/RadioDatastoreSysrepo.h
  yang-sysrepo/inc/SysrepoGetitemsCallback.h
  yang-sysrepo/inc/SysrepoUtils.h
  yang-sysrepo/inc/YangHandlerSysrepo.h
  yang-sysrepo/inc/YangHandlerSysrepo/HandlerCallback.h
  yang-sysrepo/inc/YangHandlerSysrepo/RpcCallback.h
  yang-sysrepo/inc/YangHandlerSysrepoUnlogged.h
  yang-sysrepo/inc/YangParamSysrepo.h
  yang-sysrepo/inc/YangUserAuth.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY
  yang-sysrepo/inc/YangHandlerSysrepo

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
