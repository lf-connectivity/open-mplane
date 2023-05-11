# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(vyms)

include(GNUInstallDirs)

install(FILES
  ICUPlaneConnectService.h
  ICUPlaneMonitor.h
  IDhcpOptions.h
  ILeafContainer.h
  ILinuxPtpService.h
  IMPlaneConnectivityService.h
  INetopeerMonService.h
  IOranDelays.h
  IPerformanceMgmt.h
  IRadioDataStore.h
  ISendNotification.h
  IYangCarrierMgr.h
  IYangConfig.h
  IYangConfigParser.h
  IYangDelayManagementMgr.h
  IYangElement.h
  IYangHandler.h
  IYangHandlerMgr.h
  IYangMgrORanInterfaces.h
  IYangMgrORanProcessingElement.h
  IYangModule.h
  IYangModuleMgr.h
  IYangPersist.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
