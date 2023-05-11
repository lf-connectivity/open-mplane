/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISfpData.h
 * \brief     Virtual interface to SFP data information
 *
 *
 * \details   Provides interface for retrieving SFP information
 *
 */


#ifndef ISFPDATA_H_
#define ISFPDATA_H_

#include <memory>
#include <vector>
#include <string>

#include "GlobalTypeDefs.h"

namespace Mplane {

class ISfpData {
public:
	ISfpData() {}
	virtual ~ISfpData() {}

	enum class RxPowerType
	{
		RX_POWER_TYPE_OMA,
		RX_POWER_TYPE_AVP
	};

	/**
	 * Get physical port number for this virtual fibre index
	 */
	static int getPhysicalPortNum(int virtualFibreIndex) ;

	/**
	 * Get singleton for this port
	 */
	static std::shared_ptr<ISfpData> getInstance(int port) ;

	/**
	 * Get all SFPs
	 */
	static std::vector< std::shared_ptr<ISfpData> > getSfps( void ) ;


	/**
	 * Returns the port number
	 */
	virtual unsigned getPort() const =0 ;

	/**
	 * Is the SFP fitted
	 * @return true if SFP fitted and data is available
	 */
	virtual bool sfpIsPresent() =0 ;

	/**
	 * Get the supported line rate (in MB/sec)
	 */
	virtual unsigned sfpSupportedRateMBps() =0 ;

	/**
	 * Get the max line rate (in MB/sec)
	 */
	virtual unsigned sfpMaxRateMBps() =0 ;

	/**
	 * Get the min line rate (in MB/sec)
	 */
	virtual unsigned sfpMinRateMBps() =0 ;

	/**
	 * Get serial number
	 */
	virtual std::string sfpVendorSN() =0 ;

	/**
	 * Get vendor name
	 */
	virtual std::string sfpVendorName() =0 ;

	/**
	 * Get vendor part
	 */
	virtual std::string sfpVendorPart() =0 ;

	/**
	 * Get vendor revision
	 */
	virtual std::string sfpVendorRev() =0 ;

	/**
	 * Get rx power type
	 */
	virtual RxPowerType sfpRxPowerType() =0 ;

	/**
	 * Get the SFP rx power in uW
	 */
	virtual double sfpRxPowerMicroW() =0 ;

	/**
	 * Get the SFP tx power in uW
	 */
	virtual double sfpTxPowerMicroW() =0 ;

	/**
	 * Get the SFP rx power in mW
	 */
	virtual double sfpRxPowerMilliW() =0 ;

	/**
	 * Get the SFP tx power in mW
	 */
	virtual double sfpTxPowerMilliW() =0 ;

	/**
	 * Get the tx bias current in mA
	 */
	virtual double sfpTxBiasCurrent() =0 ;

	/**
	 * Get the supply voltage in mV
	 */
	virtual double sfpSupplyVoltage() =0 ;

	/**
	 * Get the module temperature in degrees C
	 */
	virtual float sfpTemperature() =0 ;

	/**
	 * Get SFF8472 compliance code
	 */
	virtual UINT8 sfpComplianceCode() =0 ;

	/**
	 * Get connector type of the transceiver
	 */
	virtual UINT8 sfpConnectorType() =0 ;

	/**
	 * Get identifier of the transceiver
	 */
	virtual UINT8 sfpIdentifier() =0 ;

	/**
	 * Re-read the SFP data
	 */
	virtual void sfpUpdate() =0 ;

	/**
	 * Returns the raw data from the A0 and A2 addressable areas
	 * @param a0Bytes
	 * @param a2Bytes
	 * @return true if sfp is fitted
	 */
	virtual bool sfpRawData(std::vector<UINT8>& a0Bytes, std::vector<UINT8>& a2Bytes) =0 ;

	/**
	 * Read/modify/write an SFP register in 0xA2 address space
	 */
	virtual bool sfpModifyA2Reg(unsigned reg, UINT8 byte, UINT8 mask) =0 ;
} ;

}

#endif /* ISFPDATA_H_ */
