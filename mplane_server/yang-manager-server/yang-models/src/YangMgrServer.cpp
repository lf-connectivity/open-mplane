/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangMgrServer.cpp
 * \brief     YANG module manager
 *
 *
 * \details   This file defines the YANG module manager.
 *
 *             ** Auto-generated file, do not edit **
 *
 * Add user description here
 * %%->

 * <-%%
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangMgrServer.h"
#include "RadioDatastoreSysrepo.h"

// YANG models
#include "YangModuleIanaHardware.h"
#include "YangModuleIanaIfType.h"
#include "YangModuleIetfCryptoTypes.h"
#include "YangModuleIetfDhcpv6Types.h"
#include "YangModuleIetfHardware.h"
#include "YangModuleIetfInetTypes.h"
#include "YangModuleIetfInterfaces.h"
#include "YangModuleIetfIp.h"
#include "YangModuleIetfNetconfAcm.h"
#include "YangModuleIetfNetconfMonitoring.h"
#include "YangModuleIetfYangLibrary.h"
#include "YangModuleIetfYangTypes.h"
#include "YangModuleORanAld.h"
#include "YangModuleORanAldPort.h"
#include "YangModuleORanAntennaCalibration.h"
#include "YangModuleORanCompressionFactors.h"
#include "YangModuleORanDelayManagement.h"
#include "YangModuleORanDhcp.h"
#include "YangModuleORanEcpriDelay.h"
#include "YangModuleORanExternalio.h"
#include "YangModuleORanFan.h"
#include "YangModuleORanFileManagement.h"
#include "YangModuleORanFm.h"
#include "YangModuleORanHardware.h"
#include "YangModuleORanInterfaces.h"
#include "YangModuleORanLaa.h"
#include "YangModuleORanLaaOperations.h"
#include "YangModuleORanLbm.h"
#include "YangModuleORanModuleCap.h"
#include "YangModuleORanMplaneInt.h"
#include "YangModuleORanOperations.h"
#include "YangModuleORanPerformanceManagement.h"
#include "YangModuleORanProcessingElement.h"
#include "YangModuleORanSoftwareManagement.h"
#include "YangModuleORanSupervision.h"
#include "YangModuleORanSync.h"
#include "YangModuleORanTrace.h"
#include "YangModuleORanTransceiver.h"
#include "YangModuleORanTroubleshooting.h"
#include "YangModuleORanUdpEcho.h"
#include "YangModuleORanUplaneConf.h"
#include "YangModuleORanUsermgmt.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

// ------------------------------------------------------------------------------------------------------------
YangMgrServer::YangMgrServer() : YangModuleMgr() {}

// ------------------------------------------------------------------------------------------------------------
YangMgrServer::~YangMgrServer() {}

// ------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangModule>
YangMgrServer::getModule(Module_E id) {
  return YangModuleMgr::getModule((uint32_t)id);
}

// ------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangModule>
YangMgrServer::getModule(uint32_t id) {
  return YangModuleMgr::getModule(id);
}

// ------------------------------------------------------------------------------------------------------------
uint32_t
YangMgrServer::getNumModules(void) const {
  return static_cast<uint32_t>(Module_E::Num_ModuleId_E);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createDatastore(void) {
  if ((mRadioDs = std::make_shared<RadioDatastoreSysrepo>()) == nullptr) {
    std::cerr << "Failed to create datastore" << std::endl;
    return YangResult_E::FAIL;
  }

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createModules(void) {
  YangResult_E result = YangResult_E::FAIL;

  // Create YANG modules
  createIanaHardware(Module_E::IanaHardware);
  createIanaIfType(Module_E::IanaIfType);
  createIetfCryptoTypes(Module_E::IetfCryptoTypes);
  createIetfDhcpv6Types(Module_E::IetfDhcpv6Types);
  createIetfHardware(Module_E::IetfHardware);
  createIetfInetTypes(Module_E::IetfInetTypes);
  createIetfInterfaces(Module_E::IetfInterfaces);
  createIetfIp(Module_E::IetfIp);
  createIetfNetconfAcm(Module_E::IetfNetconfAcm);
  createIetfNetconfMonitoring(Module_E::IetfNetconfMonitoring);
  createIetfYangLibrary(Module_E::IetfYangLibrary);
  createIetfYangTypes(Module_E::IetfYangTypes);
  createORanAldPort(Module_E::ORanAldPort);
  createORanAld(Module_E::ORanAld);
  createORanAntennaCalibration(Module_E::ORanAntennaCalibration);
  createORanCompressionFactors(Module_E::ORanCompressionFactors);
  createORanDelayManagement(Module_E::ORanDelayManagement);
  createORanDhcp(Module_E::ORanDhcp);
  createORanEcpriDelay(Module_E::ORanEcpriDelay);
  createORanExternalio(Module_E::ORanExternalio);
  createORanFan(Module_E::ORanFan);
  createORanFileManagement(Module_E::ORanFileManagement);
  createORanFm(Module_E::ORanFm);
  createORanHardware(Module_E::ORanHardware);
  createORanInterfaces(Module_E::ORanInterfaces);
  createORanLaaOperations(Module_E::ORanLaaOperations);
  createORanLaa(Module_E::ORanLaa);
  createORanLbm(Module_E::ORanLbm);
  createORanModuleCap(Module_E::ORanModuleCap);
  createORanMplaneInt(Module_E::ORanMplaneInt);
  createORanOperations(Module_E::ORanOperations);
  createORanPerformanceManagement(Module_E::ORanPerformanceManagement);
  createORanProcessingElement(Module_E::ORanProcessingElement);
  createORanSoftwareManagement(Module_E::ORanSoftwareManagement);
  createORanSupervision(Module_E::ORanSupervision);
  createORanSync(Module_E::ORanSync);
  createORanTrace(Module_E::ORanTrace);
  createORanTransceiver(Module_E::ORanTransceiver);
  createORanTroubleshooting(Module_E::ORanTroubleshooting);
  createORanUdpEcho(Module_E::ORanUdpEcho);
  createORanUplaneConf(Module_E::ORanUplaneConf);
  createORanUsermgmt(Module_E::ORanUsermgmt);

  result = YangResult_E::OK;

  return result;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIanaHardware(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIanaHardware_NS::ModuleIanaHardware::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIanaIfType(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIanaIfType_NS::ModuleIanaIfType::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIetfCryptoTypes(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIetfCryptoTypes_NS::ModuleIetfCryptoTypes::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIetfDhcpv6Types(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIetfDhcpv6Types_NS::ModuleIetfDhcpv6Types::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIetfHardware(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIetfHardware_NS::ModuleIetfHardware::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIetfInetTypes(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIetfInetTypes_NS::ModuleIetfInetTypes::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIetfInterfaces(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIetfInterfaces_NS::ModuleIetfInterfaces::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIetfIp(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIetfIp_NS::ModuleIetfIp::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIetfNetconfAcm(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIetfNetconfAcm_NS::ModuleIetfNetconfAcm::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIetfNetconfMonitoring(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIetfNetconfMonitoring_NS::ModuleIetfNetconfMonitoring::createModule(
          moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIetfYangLibrary(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIetfYangLibrary_NS::ModuleIetfYangLibrary::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createIetfYangTypes(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleIetfYangTypes_NS::ModuleIetfYangTypes::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanAldPort(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanAldPort_NS::ModuleORanAldPort::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanAld(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanAld_NS::ModuleORanAld::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanAntennaCalibration(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanAntennaCalibration_NS::ModuleORanAntennaCalibration::
          createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanCompressionFactors(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanCompressionFactors_NS::ModuleORanCompressionFactors::
          createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanDelayManagement(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanDelayManagement_NS::ModuleORanDelayManagement::createModule(
          moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanDhcp(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanDhcp_NS::ModuleORanDhcp::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanEcpriDelay(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanEcpriDelay_NS::ModuleORanEcpriDelay::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanExternalio(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanExternalio_NS::ModuleORanExternalio::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanFan(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanFan_NS::ModuleORanFan::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanFileManagement(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanFileManagement_NS::ModuleORanFileManagement::createModule(
          moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanFm(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanFm_NS::ModuleORanFm::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanHardware(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanHardware_NS::ModuleORanHardware::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanInterfaces(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanInterfaces_NS::ModuleORanInterfaces::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanLaaOperations(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanLaaOperations_NS::ModuleORanLaaOperations::createModule(
          moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanLaa(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanLaa_NS::ModuleORanLaa::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanLbm(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanLbm_NS::ModuleORanLbm::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanModuleCap(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanModuleCap_NS::ModuleORanModuleCap::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanMplaneInt(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanMplaneInt_NS::ModuleORanMplaneInt::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanOperations(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanOperations_NS::ModuleORanOperations::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanPerformanceManagement(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanPerformanceManagement_NS::ModuleORanPerformanceManagement::
          createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanProcessingElement(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanProcessingElement_NS::ModuleORanProcessingElement::createModule(
          moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanSoftwareManagement(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanSoftwareManagement_NS::ModuleORanSoftwareManagement::
          createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanSupervision(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanSupervision_NS::ModuleORanSupervision::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanSync(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanSync_NS::ModuleORanSync::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanTrace(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanTrace_NS::ModuleORanTrace::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanTransceiver(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanTransceiver_NS::ModuleORanTransceiver::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanTroubleshooting(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanTroubleshooting_NS::ModuleORanTroubleshooting::createModule(
          moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanUdpEcho(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanUdpEcho_NS::ModuleORanUdpEcho::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanUplaneConf(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanUplaneConf_NS::ModuleORanUplaneConf::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}

// ------------------------------------------------------------------------------------------------------------
YangResult_E
YangMgrServer::createORanUsermgmt(Module_E id) {
  uint32_t moduleId = (uint32_t)id;

  // Create module
  std::shared_ptr<YangModule> module(
      ModuleORanUsermgmt_NS::ModuleORanUsermgmt::createModule(moduleId));

  // Add module to module manager list.
  addModule(module);

  return YangResult_E::OK;
}
