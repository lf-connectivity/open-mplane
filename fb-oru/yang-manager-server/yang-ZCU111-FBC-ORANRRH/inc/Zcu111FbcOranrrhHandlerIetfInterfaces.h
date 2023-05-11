/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerIetfInterfaces.h
 * \brief     IETF interfaces module handler
 *
 *
 * \details   IETF interfaces module handler
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFINTERFACES_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFINTERFACES_H_

#include <string>
#include <memory>
#include <map>
#include <ctime>

#include "NetDevice.h"

#include "YangMgrServer.h"
#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerIetfInterfaces
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerIetfInterfaces : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerIetfInterfaces(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerIetfInterfaces();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

	/*
	 * Add a vlan interface entry
	 */
	void addVlanInterface(const std::string & ethName,
	                      const std::string & desc,
	                      const std::string & macAddr,
	                      const std::string & ipAddr,
	                      UINT16 vlanId,
	                      const std::string & baseEthName);

protected:
	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath,
	                         std::shared_ptr<YangParam> oldValue,
	                         std::shared_ptr<YangParam> newValue);

private:
	//=========================================================================================================
	// State data
	//=========================================================================================================
	/*
	 * Create an interface list entry in the sysrepo
	 */
	void createInterfaceListEntry(std::shared_ptr<ILeafContainer> dataSte,
	                              const std::string & ethName,
								  uint8_t portNumber,
	                              const std::string & ipAddr,
	                              UINT64 speed = 0);

	/*
	 * Create interface statistics container
	 */
	void createStatistics(std::shared_ptr<ILeafContainer> dataSte,
	                      const std::string & ethName);

	/*
	 * Create interface IPV4 container
	 */
	void createIpv4(std::shared_ptr<ILeafContainer> dataSte,
	                const std::string & ipAddr);

	/*
	 * Create interface IPV6 container
	 */
	void createIpv6(std::shared_ptr<ILeafContainer> dataSte);

	//=========================================================================================================
	// Configuration data
	//=========================================================================================================
	/*
	 * Add an interface entry
	 */
	bool addInterface(const std::string & ethName,
	                  const std::string & desc,
	                  UINT8 portNumber,
	                  const std::string & macAddr,
	                  const std::string & ipAddrV4,
	                  const std::string & ipAddrV6,
	                  UINT8 prefixLength,
	                  bool isVlan,
	                  UINT16 vlanId,
	                  const std::string & baseEthName);

	/*
	 * Add IPV4 container to interface entry
	 */
	void addIpv4(std::map<std::string, std::string> & dataCfg,
	             const std::string & ipAddr);

	/*
	 * Add IPV6 container to interface entry
	 */
	void addIpv6(std::map<std::string, std::string> & dataCfg,
	             const std::string & ipAddr,
	             UINT8 prefixLength);

	/*
	 * Add class of service container to interface entry
	 */
	void addClassOfService(std::map<std::string, std::string> & dataCfg,
	                       UINT8 markingUPlane,
	                       UINT8 markingCPlane,
	                       UINT8 markingMPlane,
	                       UINT8 markingSPlane,
	                       UINT8 markingOther,
	                       std::map<std::string, UINT8> markingEnhUPlane);

	/*
	 * Add port reference container to interface entry
	 */
	void addPortReference(std::map<std::string, std::string> & dataCfg,
	                      UINT8 portNumber);

	/*
	 * Add address list to interface ipv4 entry
	 */
	void addIpv4Address(std::map<std::string, std::string> & dataCfg,
	                    YangPath & pathIpv,
	                    const std::string & ipAddr);

	/*
	 * Add address list to interface ipv6 entry
	 */
	void addIpv6Address(std::map<std::string, std::string> & dataCfg,
	                    YangPath & pathIpv,
	                    const std::string & ipAddr,
	                    UINT8 prefixLength);

	/*
	 * Add autoconf container to interface IPV6 entry
	 */
	void addIpv6Autoconf(std::map<std::string, std::string> & dataCfg,
	                     YangPath & pathIpv);

	/*
	 * Add neighbour address list to interface ipv entry
	 */
	void addIpvNeighbor(std::map<std::string, std::string> & dataCfg,
	                    YangPath & pathIpv,
	                    const std::string & ipAddr,
	                    const std::string & linkLayerAddr);

	/*
	 * Add dscp markings to interface ipv4/ipv6 entry
	 */
	void addIpvDscpMarkings(std::map<std::string, std::string> & dataCfg,
	                        YangPath & pathIpv,
	                        UINT8 markingMPlane,
	                        UINT8 markingUPlane,
	                        UINT8 markingCPlane,
	                        UINT8 markingSPlane,
	                        UINT8 markingOther,
	                        std::map<std::string, UINT8> markingEnhUPlane);

	/*
	 * Add enhanced-uplane-markings list entry to interface ipv entry
	 */
	void addIpvEnhancedUplaneMarkings(std::map<std::string, std::string> & dataCfg,
	                                  YangPath & pathIpv,
	                                  const std::string & upMarkingName,
	                                  UINT8 enhancedMarking);

	//=========================================================================================================
	// Helper Functions
	//=========================================================================================================
	/*
	 * Check if module feature is enabled
	 */
	bool isModuleFeatureEnabled(const std::string & feature);

	/*
	 * Get network device information
	 */
	std::shared_ptr<NetDevice> getNetDevice(const std::string & name);

	//=========================================================================================================
	// Parameters
	//=========================================================================================================
	/*
	 * Callbacks
	 */
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;

	/*
	 * Parent path
	 */
	YangPath mPathParent;

	/*
	 * Interface link up or down
	 */
	bool mInterfaceUp;

	/*
	 * Time the interface entered its current operational state
	 */
	std::map<std::string, std::string> mLastChangeTime;

	/*
	 * Interface discontinuity time
	 */
	std::map<std::string, std::string> mDiscontinuityTime;

	/*
	 * Number of interfaces
	 */
	static UINT32 mNumInterfaces;
};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFINTERFACES_H_ */
