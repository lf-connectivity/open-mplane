/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SfpData.cpp
 * \brief
 *
 *
 * \details
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "stringfunc.hpp"

#include "IFpgaMgr.h"
#include "SfpData.h"

// Uncomment for debug
//#define DEBUG

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
static const unsigned A0_SIZE{96} ;
static const unsigned A2_SIZE{128} ;
static const unsigned Ax_SIZE{256} ;

static const unsigned A0_IDENTIFIER{0} ;
static const unsigned A0_CONNECTOR_TYPE{2} ;
static const unsigned A0_RATE_ID{12} ;
static const unsigned A0_VENDOR_NAME{20} ;
static const unsigned A0_VENDOR_NAME_LEN{15} ;
static const unsigned A0_VENDOR_PART{40} ;
static const unsigned A0_VENDOR_PART_LEN{15} ;
static const unsigned A0_VENDOR_REV{56} ;
static const unsigned A0_VENDOR_REV_LEN{3} ;
static const unsigned A0_MAX_RATE_ID{66} ;
static const unsigned A0_MIN_RATE_ID{67} ;
static const unsigned A0_VENDOR_SN{68} ;
static const unsigned A0_VENDOR_SN_LEN{15} ;
static const unsigned A0_DIAGNOSTIC_TYPE{92} ;
static const unsigned A0_RX_POWER_TYPE_BIT{3} ;
static const unsigned A0_SFF8472_COMPLIANCE_CODE{94} ;

static const unsigned A2_TEMPERATURE{96} ;
static const unsigned A2_SUPPLY_VOLTAGE{98} ;
static const unsigned A2_TX_BIAS_CURRENT{100} ;
static const unsigned A2_TX_POWER{102} ;
static const unsigned A2_RX_POWER{104} ;

//=============================================================================================================
// TYPES
//=============================================================================================================

#ifdef OFF_TARGET
class SfpData::SfpTestData {
public:
	SfpTestData() :
		mA0({
		//  0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15
//			0x03, 0x04, 0x07, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x63, 0x00, 0x02, 0x14,
			0x03, 0x04, 0x07, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x66, 0x00, 0x02, 0x14,
			0x00, 0x00, 0x00, 0x00, 0x4f, 0x50, 0x4e, 0x45, 0x58, 0x54, 0x20, 0x49, 0x4e, 0x43, 0x20, 0x20,
			0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x0b, 0x40, 0x54, 0x52, 0x46, 0x35, 0x39, 0x31, 0x36, 0x41,
			0x56, 0x4c, 0x42, 0x34, 0x41, 0x57, 0x20, 0x20, 0x41, 0x31, 0x41, 0x20, 0x05, 0x1e, 0x00, 0x12,
			0x00, 0x1a, 0x00, 0x00, 0x43, 0x31, 0x30, 0x4c, 0x30, 0x31, 0x30, 0x32, 0x32, 0x20, 0x20, 0x20,
			0x20, 0x20, 0x20, 0x20, 0x31, 0x30, 0x31, 0x31, 0x31, 0x37, 0x20, 0x20, 0x58, 0xf0, 0x01, 0x93,

			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		}),
		mA2({
			0x5A, 0x00, 0xD8, 0x00, 0x55, 0x00, 0xDD, 0x00, 0x90, 0x88, 0x71, 0x48, 0x8C, 0xA0, 0x75, 0x30,
			0x21, 0x34, 0x01, 0xF4, 0x1B, 0x58, 0x03, 0xE8, 0x1F, 0x07, 0x03, 0xE8, 0x15, 0xF7, 0x04, 0xEB,
			0x31, 0x2D, 0x00, 0x3F, 0x27, 0x10, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
			0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB5,
			0x2F, 0x47, 0x82, 0xAE, 0x0F, 0x76, 0x0E, 0xC8, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
			0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		})
	{}

	~SfpTestData() {}

	bool readSfp(unsigned addr, unsigned reg, std::vector<UINT8>& data)
	{
		std::vector<UINT8>* dp(checkParams(addr, reg)) ;
		if (!dp)
			return false ;

		std::copy(dp->begin()+reg, dp->end(), data.begin()) ;
		return true ;
	}

	bool writeByte(unsigned addr, unsigned reg, UINT8 value)
	{
		std::vector<UINT8>* dp(checkParams(addr, reg)) ;
		if (!dp)
			return false ;

		(*dp)[reg] = value ;
		return true ;
	}

	bool readByte(unsigned addr, unsigned reg, uint8_t& byte)
	{
		std::vector<UINT8>* dp(checkParams(addr, reg)) ;
		if (!dp)
			return false ;

		byte = (*dp)[reg] ;
		return true ;
	}

private:
	std::vector<UINT8>* checkParams(unsigned addr, unsigned reg)
	{
		std::vector<UINT8>* dp(nullptr) ;
		if (addr == 0x50)
			dp = &mA0 ;
		if (addr == 0x51)
			dp = &mA2 ;
		if (!dp)
			return nullptr ;

		if (reg >= dp->size())
			return nullptr ;

		return dp ;
	}

private:
	std::vector<UINT8> mA0 ;
	std::vector<UINT8> mA2 ;
};
#endif

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SfpData::SfpData(unsigned port, std::shared_ptr<II2cBus> i2cA0,
		std::shared_ptr<II2cBus> i2cA1) :
	mPort(port),
	mMutex(),
	mA0Data(),
	mA2Data(),
	mSfpPresent(false),
	mSfpModuleAbsent(true),
	mRateMBps(0),
	mMaxRateMBps(0),
	mMinRateMBps(0),
	mVendorName(""),
	mVendorPart(""),
	mVendorRev(""),
	mVendorSerialNumber(""),
	mRxPowerMicroWatt(0.0),
	mTxPowerMicroWatt(0.0),
	mTxBiasCurrentmA(0.0),
	mSupplyVoltagemV(0.0),
	mRxPowerType(ISfpData::RxPowerType::RX_POWER_TYPE_OMA),
	mComplianceCode(0xFF),
	mConnectorType(0),
	mTransceiverIdentifier(0),
	mTemperature(0.0),
	mFpga( IFpgaMgr::getIFpgaFibreRegs() ),
	mI2cA0(i2cA0),
	mI2cA2(i2cA1)

#ifdef OFF_TARGET
	,mTestData(std::make_shared<SfpTestData>())
#endif

{
	loadData() ;
}

//-------------------------------------------------------------------------------------------------------------
SfpData::~SfpData()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned SfpData::getPort() const
{
	return mPort ;
}


//-------------------------------------------------------------------------------------------------------------
bool SfpData::sfpIsPresent()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mSfpPresent ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SfpData::sfpSupportedRateMBps()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mRateMBps ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SfpData::sfpMaxRateMBps()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mMaxRateMBps ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SfpData::sfpMinRateMBps()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mMinRateMBps ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SfpData::sfpVendorName()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mVendorName ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SfpData::sfpVendorPart()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mVendorPart ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SfpData::sfpVendorRev()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mVendorRev ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SfpData::sfpVendorSN()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mVendorSerialNumber ;
}

//-------------------------------------------------------------------------------------------------------------
double SfpData::sfpRxPowerMicroW()
{
	Mutex::Lock lock(mMutex) ;

	loadA2Data() ;
	return mRxPowerMicroWatt ;
}

//-------------------------------------------------------------------------------------------------------------
double SfpData::sfpTxPowerMicroW()
{
	Mutex::Lock lock(mMutex) ;

	loadA2Data() ;
	return mTxPowerMicroWatt ;
}

//-------------------------------------------------------------------------------------------------------------
double SfpData::sfpRxPowerMilliW()
{
	Mutex::Lock lock(mMutex) ;

	loadA2Data() ;
	return mRxPowerMicroWatt/(double)1000.0 ;
}

//-------------------------------------------------------------------------------------------------------------
double SfpData::sfpTxPowerMilliW()
{
	Mutex::Lock lock(mMutex) ;

	loadA2Data() ;
	return mTxPowerMicroWatt/(double)1000.0 ;
}

//-------------------------------------------------------------------------------------------------------------
ISfpData::RxPowerType SfpData::sfpRxPowerType()
{
	Mutex::Lock lock(mMutex) ;

	loadA2Data() ;
	return mRxPowerType ;
}

//-------------------------------------------------------------------------------------------------------------
double SfpData::sfpTxBiasCurrent()
{
	Mutex::Lock lock(mMutex) ;

	loadA2Data() ;
	return mTxBiasCurrentmA ;
}

//-------------------------------------------------------------------------------------------------------------
double SfpData::sfpSupplyVoltage()
{
	Mutex::Lock lock(mMutex) ;

	loadA2Data() ;
	return mSupplyVoltagemV ;
}

//-------------------------------------------------------------------------------------------------------------
UINT8 SfpData::sfpComplianceCode()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mComplianceCode ;
}

//-------------------------------------------------------------------------------------------------------------
UINT8 SfpData::sfpConnectorType()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mConnectorType ;
}

//-------------------------------------------------------------------------------------------------------------
UINT8 SfpData::sfpIdentifier()
{
	Mutex::Lock lock(mMutex) ;

	checkRefresh() ;
	return mTransceiverIdentifier ;
}

//-------------------------------------------------------------------------------------------------------------
/**
 * ATG Requirements Traceability. Do not remove
 *
 * \satisfy{@req_8403{142}}
 */
float SfpData::sfpTemperature()
{
	Mutex::Lock lock(mMutex) ;

    // Load the temperature data, which is in 2's complement and
    loadTempData() ;
	UINT16 twosCompliment = mTemperature;

    float temperature;

    // Temperature is in 2's complement
    if( twosCompliment > 0x8000 )
    {
        // temperature is a negative value invert and add 1
        twosCompliment = ~twosCompliment;
        twosCompliment += 1;

        // Add the negative sign and adjust for the 1/256 resolution.
        temperature = (float)-(twosCompliment / 256.0) ;
    }
    else
    {
        temperature = (float)twosCompliment / 256.0 ;
    }
	return temperature ;
}



//-------------------------------------------------------------------------------------------------------------
void SfpData::sfpUpdate()
{
	Mutex::Lock lock(mMutex) ;

	loadData() ;
}

//-------------------------------------------------------------------------------------------------------------
bool SfpData::sfpRawData(std::vector<UINT8>& a0Bytes, std::vector<UINT8>& a2Bytes)
{
	Mutex::Lock lock(mMutex) ;

	loadData() ;
	loadA2Data() ;

	a0Bytes = mA0Data ;
	a2Bytes = mA2Data ;

	return mSfpPresent ;
}

//-------------------------------------------------------------------------------------------------------------
bool SfpData::sfpModifyA2Reg(unsigned reg, UINT8 byte, UINT8 mask)
{
	Mutex::Lock lock(mMutex) ;

#ifdef OFF_TARGET
{
	uint8_t data ;
	if (!mTestData->readByte(0x51, reg, data))
		return false ;

	data = (data & ~mask) | (byte & mask) ;

	return mTestData->writeByte(0x51, reg, data) ;
}
#endif

	std::vector<IBus::BusCommand> commands ;
	std::vector<IBus::BusCommand> readback ;
	std::vector<uint8_t> data(1, 0);

	// Read the data from the register address
	commands.push_back(IBus::BusCommand(IBus::BUS_READ_DATA_OFFSET, reg, data)) ;

	/// Executes the list of commands as an atomic set
	if (mI2cA2->commandsList(commands, readback))
	{
		// Check if the readback has the data that we need
		if (readback.size() == 1 && readback[0].type() == IBus::BUS_READ_DATA_OFFSET &&
				readback[0].offset() == reg)
		{
			// Update the data using the value that is provided
			data[0] = (data[0] & ~mask) | (byte & mask) ;

			// Write the modified register value
			commands.clear();
			commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_DATA_OFFSET, reg, data));

			if (mI2cA2->commandsList(commands))
			{
				return true;
			}
		}
	}

	return false;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void SfpData::checkRefresh()
{
	// skip if module absent hasn't changed
	if (mSfpModuleAbsent == sfpModuleAbsent())
		return ;

	// Refresh
	loadData() ;
}


//-------------------------------------------------------------------------------------------------------------
bool SfpData::loadData()
{
#ifdef DEBUG
	std::cerr << "[SfpData" << mPort << "] loadData" << std::endl ;
#endif

	mRateMBps = 0 ;
	mMaxRateMBps = 0 ;
	mMinRateMBps = 0 ;
	mVendorName = "" ;
	mVendorPart = "" ;
	mVendorRev = "" ;
	mVendorSerialNumber = "" ;
	mComplianceCode = 0xFF;
	mConnectorType = 0;
	mTransceiverIdentifier = 0;
	mRxPowerType = RxPowerType::RX_POWER_TYPE_OMA;

	mA0Data.clear() ;

	// Update the module present state
	mSfpModuleAbsent = sfpModuleAbsent() ;
	mSfpPresent = !mSfpModuleAbsent ;
	if (!mSfpPresent)
		return false ;

#ifdef DEBUG
	std::cerr << "[SfpData" << mPort << "] loadData - reading module..." << std::endl ;
#endif

	// Read the 0xA0 data - if we can't read this section then stop immediately
	std::vector<UINT8> dataA0(Ax_SIZE, 0) ;

	if (!readSfp(mI2cA0, 0, dataA0))
	{
		return false ;
	}

	mA0Data = dataA0 ;

	// Process the A0 data
	mRateMBps = static_cast<unsigned>(mA0Data[A0_RATE_ID]) * 100 ;
	mMaxRateMBps = static_cast<unsigned>(mA0Data[A0_MAX_RATE_ID]) * 100 ;
	mMinRateMBps = static_cast<unsigned>(mA0Data[A0_MIN_RATE_ID]) * 100 ;
	mComplianceCode = mA0Data[A0_SFF8472_COMPLIANCE_CODE];
	mConnectorType = mA0Data[A0_CONNECTOR_TYPE];
	mTransceiverIdentifier = mA0Data[A0_IDENTIFIER];
	mVendorName = trim(std::string(mA0Data.begin()+A0_VENDOR_NAME, mA0Data.begin()+A0_VENDOR_NAME+A0_VENDOR_NAME_LEN)) ;
	mVendorPart = trim(std::string(mA0Data.begin()+A0_VENDOR_PART, mA0Data.begin()+A0_VENDOR_PART+A0_VENDOR_PART_LEN)) ;
	mVendorRev = trim(std::string(mA0Data.begin()+A0_VENDOR_REV, mA0Data.begin()+A0_VENDOR_REV+A0_VENDOR_REV_LEN)) ;
	mVendorSerialNumber = trim(std::string(mA0Data.begin()+A0_VENDOR_SN, mA0Data.begin()+A0_VENDOR_SN+A0_VENDOR_SN_LEN)) ;
	mRxPowerType = ((mA0Data[A0_DIAGNOSTIC_TYPE] & (1 << A0_RX_POWER_TYPE_BIT)) ? RxPowerType::RX_POWER_TYPE_AVP : RxPowerType::RX_POWER_TYPE_OMA);

#ifdef DEBUG
	std::cerr << "[SfpData" << mPort << "] loadData() Rate = " << mRateMBps << std::endl ;
#endif

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SfpData::loadA2Data()
{
#ifdef DEBUG
	std::cerr << "[SfpData" << mPort << "] loadA2Data" << std::endl ;
#endif

	mRxPowerMicroWatt = 0.0 ;
	mTxPowerMicroWatt = 0.0 ;
	mTxBiasCurrentmA = 0.0 ;
	mSupplyVoltagemV = 0.0 ;

	mA2Data.clear() ;

	// Update the module present state
	mSfpModuleAbsent = sfpModuleAbsent() ;
	mSfpPresent = !mSfpModuleAbsent ;
	if (!mSfpPresent)
	{
		return false ;
	}

#ifdef DEBUG
	std::cerr << "[SfpData" << mPort << "] loadA2Data - reading module..." << std::endl ;
#endif

	// Read the 0xA2 data - can't always read this section so just returns 0 for these values
	std::vector<UINT8> dataA2(Ax_SIZE, 0) ;

	if (readSfp(mI2cA2, 0, dataA2))
	{
		mA2Data = dataA2 ;
	}
	else
	{
		return false;
	}

	// Process the A2 data
	if (!mA2Data.empty())
	{
		// Power is received with a resolution of 0.1uW = 1 LSB
		unsigned rxPower = toUnsigned(mA2Data, A2_RX_POWER) ;
		mRxPowerMicroWatt = double(rxPower)/10.0 ;
		unsigned txPower = toUnsigned(mA2Data, A2_TX_POWER) ;
		mTxPowerMicroWatt = double(txPower)/10.0 ;

		// Tx bias current is received with a resolution of 2uA = 1 LSB
		unsigned txBiasCurrent = toUnsigned(mA2Data, A2_TX_BIAS_CURRENT) ;
		mTxBiasCurrentmA = double(txBiasCurrent * 2)/1000.0 ;

		// Supply voltage is received with a resolution of 100uV = 1 LSB
		unsigned supplyVoltage = toUnsigned(mA2Data, A2_SUPPLY_VOLTAGE) ;
		mSupplyVoltagemV = double(supplyVoltage)/10.0 ;

		// Just do a quick read of the 2's complement value. Keep it like this to reduce overhead that can lead
		// the SFP not working properly and the UUT not being assinged and IP address.
		mTemperature = (UINT16)toInt(mA2Data, A2_TEMPERATURE) ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SfpData::loadTempData()
{
    mA2Data.clear() ;

    // Update the module present state
    mSfpModuleAbsent = sfpModuleAbsent() ;
    mSfpPresent = !mSfpModuleAbsent ;
    if (!mSfpPresent)
    {
        return false ;
    }

    // Read the 0xA2 data - can't always read this section so just returns 0 for these values
    std::vector<UINT8> dataA2(Ax_SIZE, 0) ;

    if (readSfp(mI2cA2, 0, dataA2))
    {
        mA2Data = dataA2 ;
    }

    // Process the A2 data
    if (!mA2Data.empty())
    {
        // Quick read of the value which is in 2's complement.
        mTemperature = (UINT16)toInt(mA2Data, A2_TEMPERATURE) ;
    }

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SfpData::sfpModuleAbsent() const
{
	if (mFpga->read_sfpModAbs(mPort) == 1)
	{
		return true ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool SfpData::readSfp(std::shared_ptr<II2cBus> i2c, unsigned reg, std::vector<UINT8>& data)
{
#ifdef OFF_TARGET
	unsigned addr = 0x50;
	if (i2c == mI2cA2)
	{
		addr = 0x51;
	}
	return mTestData->readSfp(addr, reg, data) ;
#endif

    std::vector<IBus::BusCommand> commands ;
    std::vector<IBus::BusCommand> readback ;

    // Read the data from the register address
    commands.push_back(IBus::BusCommand(IBus::BUS_READ_DATA_OFFSET, reg, data)) ;

	/// Executes the list of commands as an atomic set
	if (i2c->commandsList(commands, readback))
	{
		if (readback.size() == 1 && readback[0].type() == IBus::BUS_READ_DATA_OFFSET &&
				readback[0].offset() == reg)
		{
			data = readback[0].bytes();

			return true;
		}
	}

	std::cerr << "SFP-EEPROM::ERROR " << i2c->error() << std::endl ;

	return false;
}

//-------------------------------------------------------------------------------------------------------------
void SfpData::dumpData(unsigned port, unsigned addr, const std::vector<UINT8>& data)
{
#ifdef DEBUG
//	fprintf(stderr, "SfpData%u 0x%02x\n", port, addr) ;
//
//	unsigned n ;
//	for (n = 0; n < data.size(); n += 16)
//	{
//		unsigned i ;
//		for (i = 0; i < 16; i++)
//		{
//			if ((n + i) < data.size())
//			{
//				fprintf(stderr, "%02x ", data[n + i]);
//
//			}
//			else
//			{
//				fprintf(stderr, "   ");
//			}
//		}
//
//		for (i = 0; i < 16; i++)
//		{
//			if ((n + i) < data.size())
//			{
//				unsigned int ch = data[n + i];
//				fprintf(stderr, "%c", isprint(ch) ? ch : '.');
//			}
//			else
//			{
//				fprintf(stderr, " ");
//			}
//		}
//		fprintf(stderr, "\n");
//	}
#endif
}

//-------------------------------------------------------------------------------------------------------------
unsigned SfpData::toUnsigned(std::vector<UINT8>& data, unsigned index) const
{
	if (index+1 >= data.size())
		return 0 ;

	unsigned value(
		((static_cast<unsigned>(data[index]) & 0xff) << 8) |
		(static_cast<unsigned>(data[index+1]) & 0xff)
	) ;
	return value ;
}

//-------------------------------------------------------------------------------------------------------------
int SfpData::toInt(std::vector<UINT8>& data, unsigned index) const
{
	if (index+1 >= data.size())
		return 0 ;

	int value(
		((static_cast<int>(data[index]) & 0xff) << 8) |
		(static_cast<int>(data[index+1]) & 0xff)
	) ;
	return value ;
}
