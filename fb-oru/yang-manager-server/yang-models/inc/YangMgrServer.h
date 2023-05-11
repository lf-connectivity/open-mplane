#ifndef _YANG_MGR_SERVER_H_
#define _YANG_MGR_SERVER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangMgrServer.h
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
#include "YangModuleMgr.h"

namespace Mplane
{

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// List of modules
enum class Module_E : uint32_t
{
	IanaHardware,
	IanaIfType,
	IetfCryptoTypes,
	IetfDhcpv6Types,
	IetfHardware,
	IetfInetTypes,
	IetfInterfaces,
	IetfIp,
	IetfNetconfAcm,
	IetfNetconfMonitoring,
	IetfYangLibrary,
	IetfYangTypes,
	ORanAldPort,
	ORanAld,
	ORanAntennaCalibration,
	ORanCompressionFactors,
	ORanDelayManagement,
	ORanDhcp,
	ORanEcpriDelay,
	ORanExternalio,
	ORanFan,
	ORanFileManagement,
	ORanFm,
	ORanHardware,
	ORanInterfaces,
	ORanLaaOperations,
	ORanLaa,
	ORanLbm,
	ORanModuleCap,
	ORanMplaneInt,
	ORanOperations,
	ORanPerformanceManagement,
	ORanProcessingElement,
	ORanSoftwareManagement,
	ORanSupervision,
	ORanSync,
	ORanTrace,
	ORanTransceiver,
	ORanTroubleshooting,
	ORanUdpEcho,
	ORanUplaneConf,
	ORanUsermgmt,

	Num_ModuleId_E
};

class YangMgrServer : public YangModuleMgr
{
public:
	YangMgrServer();
	~YangMgrServer();

	/**
	 * Get the module by id
	 */
	virtual std::shared_ptr<IYangModule> getModule(uint32_t moduleId) override;
	std::shared_ptr<IYangModule> getModule(Module_E moduleId);

	/**
	 * Get the number of modules (i.e. max module ID + 1)
	 */
	virtual uint32_t getNumModules(void) const override;

protected:
	/**
	 * Create datastore
	 */
	YangResult_E createDatastore(void);

	/**
	 * Create modules
	 */
	virtual YangResult_E createModules(void);

private:
	YangResult_E createIanaHardware(Module_E id);
	YangResult_E createIanaIfType(Module_E id);
	YangResult_E createIetfCryptoTypes(Module_E id);
	YangResult_E createIetfDhcpv6Types(Module_E id);
	YangResult_E createIetfHardware(Module_E id);
	YangResult_E createIetfInetTypes(Module_E id);
	YangResult_E createIetfInterfaces(Module_E id);
	YangResult_E createIetfIp(Module_E id);
	YangResult_E createIetfNetconfAcm(Module_E id);
	YangResult_E createIetfNetconfMonitoring(Module_E id);
	YangResult_E createIetfYangLibrary(Module_E id);
	YangResult_E createIetfYangTypes(Module_E id);
	YangResult_E createORanAldPort(Module_E id);
	YangResult_E createORanAld(Module_E id);
	YangResult_E createORanAntennaCalibration(Module_E id);
	YangResult_E createORanCompressionFactors(Module_E id);
	YangResult_E createORanDelayManagement(Module_E id);
	YangResult_E createORanDhcp(Module_E id);
	YangResult_E createORanEcpriDelay(Module_E id);
	YangResult_E createORanExternalio(Module_E id);
	YangResult_E createORanFan(Module_E id);
	YangResult_E createORanFileManagement(Module_E id);
	YangResult_E createORanFm(Module_E id);
	YangResult_E createORanHardware(Module_E id);
	YangResult_E createORanInterfaces(Module_E id);
	YangResult_E createORanLaaOperations(Module_E id);
	YangResult_E createORanLaa(Module_E id);
	YangResult_E createORanLbm(Module_E id);
	YangResult_E createORanModuleCap(Module_E id);
	YangResult_E createORanMplaneInt(Module_E id);
	YangResult_E createORanOperations(Module_E id);
	YangResult_E createORanPerformanceManagement(Module_E id);
	YangResult_E createORanProcessingElement(Module_E id);
	YangResult_E createORanSoftwareManagement(Module_E id);
	YangResult_E createORanSupervision(Module_E id);
	YangResult_E createORanSync(Module_E id);
	YangResult_E createORanTrace(Module_E id);
	YangResult_E createORanTransceiver(Module_E id);
	YangResult_E createORanTroubleshooting(Module_E id);
	YangResult_E createORanUdpEcho(Module_E id);
	YangResult_E createORanUplaneConf(Module_E id);
	YangResult_E createORanUsermgmt(Module_E id);

};

} /* namespace Mplane */

#endif /* _YANG_MGR_SERVER_H_ */
