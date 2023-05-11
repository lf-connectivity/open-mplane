# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.12)
project(vsi)

include(GNUInstallDirs)

install(FILES
  IAppControl.h
  IAppMonService.h
  IBist.h
  ICpriController.h
  ICpriPortHandler.h
  ICpriTypes.h
  IDiscovery.h
  IDpd2App.h
  IDpdApp.h
  IDpdControl.h
  IEti.h
  IFaultChange.h
  IFibreControl.h
  IMemMon.h
  IOriCtrlMgmt.h
  IPcl.h
  IPsuMonitorService.h
  IRadioState.h
  IServicesCtl.h
  ITifImageCommandHandler.h
  ITxPcl.h
  IVswr.h

  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
