/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SfpData.h
 * \brief     Device interface to SFP module to read the EEPROM data
 *
 *
 * \details
 *
 */


#ifndef SFPDATA_H_
#define SFPDATA_H_

#include <memory>
#include <string>
#include <vector>

#include "Mutex.h"
#include "ISfpData.h"
#include "bus/II2cBus.h"


namespace Mplane {

class IFpgaFibreRegs ;

class SfpData : public virtual ISfpData {
public:
	explicit SfpData(unsigned port, std::shared_ptr<II2cBus> i2cA0,
			std::shared_ptr<II2cBus> i2cA1) ;
	virtual ~SfpData() ;

	/**
	 * Returns the port number
	 */
	virtual unsigned getPort() const override ;

	/**
	 * Is the SFP fitted
	 * @return true if SFP fitted and data is available
	 */
	virtual bool sfpIsPresent() override ;

	/**
	 * Get the supported line rate (in MB/sec)
	 */
	virtual unsigned sfpSupportedRateMBps() override ;

	/**
	 * Get the max line rate (in MB/sec)
	 */
	virtual unsigned sfpMaxRateMBps() override ;

	/**
	 * Get the min line rate (in MB/sec)
	 */
	virtual unsigned sfpMinRateMBps() override ;

	/**
	 * Get serial number
	 */
	virtual std::string sfpVendorSN() override ;

	/**
	 * Get vendor name
	 */
	virtual std::string sfpVendorName() override ;

	/**
	 * Get vendor part
	 */
	virtual std::string sfpVendorPart() override ;

	/**
	 * Get vendor revision
	 */
	virtual std::string sfpVendorRev() override ;

	/**
	 * Get rx power type
	 */
	virtual RxPowerType sfpRxPowerType() override ;

	/**
	 * Get the SFP rx power in uW
	 */
	virtual double sfpRxPowerMicroW() override ;

	/**
	 * Get the SFP tx power in uW
	 */
	virtual double sfpTxPowerMicroW() override ;

	/**
	 * Get the SFP rx power in mW
	 */
	virtual double sfpRxPowerMilliW() override ;

	/**
	 * Get the SFP tx power in mW
	 */
	virtual double sfpTxPowerMilliW() override ;

	/**
	 * Get the tx bias current in mA
	 */
	virtual double sfpTxBiasCurrent() override ;

	/**
	 * Get the supply voltage in mV
	 */
	virtual double sfpSupplyVoltage() override ;

	/**
	 * Get the module temperature in degrees C
	 */
	virtual float sfpTemperature() override ;

	/**
	 * Get SFF8472 compliance code
	 */
	virtual UINT8 sfpComplianceCode() override ;

	/**
	 * Get connector type of the transceiver
	 */
	virtual UINT8 sfpConnectorType() override ;

	/**
	 * Get identifier of the transceiver
	 */
	virtual UINT8 sfpIdentifier() override ;

	/**
	 * Re-read the SFP data
	 */
	virtual void sfpUpdate() override ;

	/**
	 * Returns the raw data from the A0 and A2 addressable areas
	 * @param a0Bytes
	 * @param a2Bytes
	 * @return true if sfp is fitted
	 */
	virtual bool sfpRawData(std::vector<UINT8>& a0Bytes, std::vector<UINT8>& a2Bytes) override ;

	/**
	 * Read/modify/write an SFP register in 0xA2 address space
	 */
	virtual bool sfpModifyA2Reg(unsigned reg, UINT8 byte, UINT8 mask) override ;

protected:
	// Checks to see if the 'SFP module absent' bit has changed - if it has then may need to reload
	void checkRefresh() ;

	// Get the current state of the module absent bit from the fpga
	bool sfpModuleAbsent() const ;

	// Read the device to load up the data buffers
	bool loadData() ;

	// Read the device to load up the data buffers
	bool loadA2Data() ;

	// low-level read from the i2c device
	bool readSfp(std::shared_ptr<II2cBus> i2c, unsigned reg, std::vector<UINT8>& data) ;

	// debug
	void dumpData(unsigned port, unsigned addr, const std::vector<UINT8>& data) ;

	// convert the next 2 bytes from the SFP data into an unsigned value
	unsigned toUnsigned(std::vector<UINT8>& data, unsigned index) const ;

	// convert the next 2 bytes from the SFP data into an integer value
	int toInt(std::vector<UINT8>& data, unsigned index) const ;

	// Read the device temperature information
	bool loadTempData();

private:
	unsigned mPort ;
	Mutex mMutex ;
	std::vector<UINT8> mA0Data ;
	std::vector<UINT8> mA2Data ;
	bool mSfpPresent ;
	bool mSfpModuleAbsent ;
	unsigned mRateMBps ;
	unsigned mMaxRateMBps ;
	unsigned mMinRateMBps ;
	std::string mVendorName ;
	std::string mVendorPart ;
	std::string mVendorRev ;
	std::string mVendorSerialNumber ;
	double mRxPowerMicroWatt ;
	double mTxPowerMicroWatt ;
	double mTxBiasCurrentmA ;
	double mSupplyVoltagemV ;
	ISfpData::RxPowerType mRxPowerType;
	UINT8 mComplianceCode;
	UINT8 mConnectorType;
	UINT8 mTransceiverIdentifier;

	UINT16 mTemperature ; //!> 2's Compliment representation of the SFP temperature.

	// For fpga fibre reg access
	std::shared_ptr<IFpgaFibreRegs> mFpga ;
	std::shared_ptr<II2cBus> mI2cA0;
	std::shared_ptr<II2cBus> mI2cA2;

#ifdef OFF_TARGET
	class SfpTestData ;
	std::shared_ptr<SfpTestData>	mTestData ;
#endif
} ;

}

#endif /* SFPDATA_H_ */
