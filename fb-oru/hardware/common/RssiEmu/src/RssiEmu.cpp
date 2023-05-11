/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RssiEmu.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>
#include <fcntl.h>

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "xstringfunc.hpp"
#include "ICalData.h"
#include "ISRxCalData.h"
#include "ISRxCal.h"

//#include "IFpgaMgr.h"
#include "RssiEmu.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
//#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTF(fmt, args...)	printf(fmt, ##args)
#else
#define DEBUG_PRINTF(fmt, args...)
#endif

static const unsigned PERIOD_MS{200} ;

static const unsigned ADDR_FWD_LOW{0x4} ;
static const unsigned ADDR_FWD_HIGH{0x6} ;

static const unsigned ADDR_REV_LOW{0x8} ;
static const unsigned ADDR_REV_HIGH{0xA} ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RssiEmu::RssiEmu(unsigned tx) :
	TaskPeriodicEvent(PERIOD_MS, Task::PRIORITY_MEDIUM, Task::MEDIUM_STACK, "RssiEmu" + std::to_string(tx), "RssiEmu"),
	mIndex(tx),
	mTxPort( ITxPortFactory::getPorts()[tx] ),

	mEmuMutex(),
	mFpga(OffTargetFPGA::getInstance()),
	mRfAtten(0.0),
	mRfPower(0.0),
	mRssiFwdLow(0),
	mRssiFwdHigh(0),
	mRssiRevLow(0),
	mRssiRevHigh(0)

{
	//	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RssiEmu") ;
	DEBUG_PRINTF("RssiEmu @ %p\n", this) ;

	unsigned antennaBase(0x50000 + mIndex*0x1000) ;

	// register ourself to handle the memory locations
	mFpga->registerHandler(antennaBase+ADDR_FWD_LOW, antennaBase+ADDR_FWD_LOW,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeFwdLowHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readFwdLowHandler(address, mask) ;
		}
	) ;

	mFpga->registerHandler(antennaBase+ADDR_FWD_HIGH, antennaBase+ADDR_FWD_HIGH,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeFwdHighHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readFwdHighHandler(address, mask) ;
		}
	) ;

	mFpga->registerHandler(antennaBase+ADDR_REV_LOW, antennaBase+ADDR_REV_LOW,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeRevLowHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readRevLowHandler(address, mask) ;
		}
	) ;

	mFpga->registerHandler(antennaBase+ADDR_REV_HIGH, antennaBase+ADDR_REV_HIGH,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeRevHighHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readRevHighHandler(address, mask) ;
		}
	) ;

	show() ;

}

//-------------------------------------------------------------------------------------------------------------
RssiEmu::~RssiEmu()
{
	unsigned antennaBase(0x50000 + mIndex*0x1000) ;
	mFpga->unRegisterHandler(antennaBase+ADDR_FWD_HIGH) ;
	mFpga->unRegisterHandler(antennaBase+ADDR_FWD_LOW) ;
	mFpga->unRegisterHandler(antennaBase+ADDR_REV_HIGH) ;
	mFpga->unRegisterHandler(antennaBase+ADDR_REV_LOW) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool RssiEmu::runEvent()
{
	Mutex::Lock lock(mEmuMutex) ;

	// get the current RF atten + IF atten
	Power rfAtten( mTxPort->getRFAttenuation() ) ;
	Power ifAtten( mTxPort->getIFAttenuation() ) ;
	rfAtten += ifAtten ;

	// skip if not changed
	if (fabs(rfAtten.get() - mRfAtten.get()) <= 0.01)
		return true ;

	printf("[RssiEmu%u] EVENT : RfAtten=%0.2f dB IfAtten=%0.2f dB\n",
			mIndex, rfAtten.get(), ifAtten.get());

	mRfAtten = rfAtten ;

	// Calculate the expected RSSI with this RF atten
	// For sim, we want rssi=67.914932dB when atten=6dB
	Power newRf = Power(67.914932 + 6.0 + 25.0) - mRfAtten ;

	printf("[RssiEmu%u] EVENT : newRF=%0.2f dB\n",
			mIndex, newRf.get());

	if (newRf == mRfPower)
		newRf += 0.01f ;
	mRfPower = newRf ;

	// get cal correction
	float correction(0.0) ;
	std::shared_ptr<ISRxCalDataContainer> calData(
		std::dynamic_pointer_cast< ISRxCalDataContainer > (ICalDataFactory::getInterface())
	) ;
	std::shared_ptr<ISRxCalData> srxCal(calData->getSRxCal()) ;
    if (srxCal->isLoaded())
    {
		// use the path number to get cal data, not the zero based index
		std::shared_ptr<ISRxOpenLoop> srx(srxCal->getSRxOpenLoop( mIndex+1 ));
		if (srx)
		{
			float temperature = mTxPort->getTemperature().get();
			Frequency frequency = mTxPort->getFrequency();
            correction = srx->dBfsTodBm(frequency, Power(10.0), temperature).get() ;
		}
    }

	// Correct for cal
	float rfUncorrected = mRfPower.get() - correction ;

	// Convert to the equivalent fpga reg readings
	double regVal = 4194304.0 * pow(10.0, (rfUncorrected / 10.0)) ;
	unsigned reg = static_cast<unsigned>(regVal + 0.5) ;
	mRssiFwdLow = static_cast<UINT16>(reg & 0xffff) ;
	mRssiFwdHigh = static_cast<UINT16>((reg >> 16) & 0xffff) ;

	// Calc a dummy reverse - make it ~12db below forward (> VSWR threshold of 6dB)
	rfUncorrected -= 12.9 ;
	regVal = 4194304.0 * pow(10.0, (rfUncorrected / 10.0)) ;
	reg = static_cast<unsigned>(regVal + 0.5) ;
	mRssiRevLow = static_cast<UINT16>(reg & 0xffff) ;
	mRssiRevHigh = static_cast<UINT16>((reg >> 16) & 0xffff) ;

	printf("[RssiEmu%u] EVENT : mRssiFwdHigh=0x%04x mRssiFwdLow=0x%04x mRssiRevHigh=0x%04x mRssiRevLow=0x%04x mRfPower=%.2f dB mRfAtten=%0.2f dB\n",
			mIndex,
			mRssiFwdHigh, mRssiFwdLow,
			mRssiRevHigh, mRssiRevLow,
			mRfPower.get(), mRfAtten.get());

	return true ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
UINT16 RssiEmu::writeFwdLowHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	DEBUG_PRINTF("[RssiEmu%u] write low 0x%05x = 0x%04x / 0x%04x\n", mFibre, address, (unsigned)value, (unsigned)mask) ;

	// IGNORE
	return value & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 RssiEmu::readFwdLowHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	DEBUG_PRINTF("[RssiEmu%u] read low 0x%04x / 0x%04x => 0x%04x\n", mFibre,
		(unsigned)mControl, (unsigned)mask,
		(unsigned)(mControl & mask)
	) ;

	return mRssiFwdLow & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 RssiEmu::writeFwdHighHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	DEBUG_PRINTF("[RssiEmu%u] write high 0x%05x = 0x%04x / 0x%04x\n", mFibre, address, (unsigned)value, (unsigned)mask) ;

	// IGNORE
	return value & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 RssiEmu::readFwdHighHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	DEBUG_PRINTF("[RssiEmu%u] read high 0x%04x / 0x%04x => 0x%04x\n", mFibre,
		(unsigned)mControl, (unsigned)mask,
		(unsigned)(mControl & mask)
	) ;

	return mRssiFwdHigh & mask ;
}



//-------------------------------------------------------------------------------------------------------------
UINT16 RssiEmu::writeRevLowHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	DEBUG_PRINTF("[RssiEmu%u] write low 0x%05x = 0x%04x / 0x%04x\n", mFibre, address, (unsigned)value, (unsigned)mask) ;

	// IGNORE
	return value & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 RssiEmu::readRevLowHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	DEBUG_PRINTF("[RssiEmu%u] read low 0x%04x / 0x%04x => 0x%04x\n", mFibre,
		(unsigned)mControl, (unsigned)mask,
		(unsigned)(mControl & mask)
	) ;

	return mRssiRevLow & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 RssiEmu::writeRevHighHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	DEBUG_PRINTF("[RssiEmu%u] write high 0x%05x = 0x%04x / 0x%04x\n", mFibre, address, (unsigned)value, (unsigned)mask) ;

	// IGNORE
	return value & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 RssiEmu::readRevHighHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	DEBUG_PRINTF("[RssiEmu%u] read high 0x%04x / 0x%04x => 0x%04x\n", mFibre,
		(unsigned)mControl, (unsigned)mask,
		(unsigned)(mControl & mask)
	) ;

	return mRssiRevHigh & mask ;
}



//-------------------------------------------------------------------------------------------------------------
void RssiEmu::show(std::ostream& os)
{
	os << "RssiEmu @ " << this << std::endl ;
	os << "  " << "mIndex        : " << mIndex << std::endl ;
	os << "  " << "mRfAtten      : " << mRfAtten << std::endl ;
	os << "  " << "mRfPower      : " << mRfPower << std::endl ;
	os << "  " << "mRssiFwdLow   : 0x" << std::hex << mRssiFwdLow << std::dec << std::endl ;
	os << "  " << "mRssiFwdHigh  : 0x" << std::hex << mRssiFwdHigh << std::dec << std::endl ;
	os << "  " << "mRssiRevLow   : 0x" << std::hex << mRssiRevLow << std::dec << std::endl ;
	os << "  " << "mRssiRevHigh  : 0x" << std::hex << mRssiRevHigh << std::dec << std::endl ;
}
