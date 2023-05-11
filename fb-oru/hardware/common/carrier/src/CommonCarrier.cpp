
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrier.cpp
 * \brief     Implementation of Common Carrier Data base class
 *
 *
 * \details   Implementation of Common Carrier Data base class
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <algorithm>
#include <memory>

#include "ITxPort.h"
#include "IRxPort.h"
#include "IAppSettings.h"
#include "IAppSettingsFactory.h"

#include "stringfunc.hpp"
#include "CarrierUtils.hpp"
#include "CommonCarrier.h"

using namespace Mplane;



//=============================================================================================================
// MACROS
//=============================================================================================================
#define GET_VALUE(nm) \
	Mutex::Lock lock(mCarrierMutex) ; \
	return nm

#define VALUE_CHANGED(nm) \
	Mutex::Lock lock(mCarrierMutex) ; \
	return mChangedFlags.nm

#define SET_VALUE(nm, val) \
	Mutex::Lock lock(mCarrierMutex) ; \
	\
	/* track changes */ \
	if (nm != val) \
	{ \
		mChangedFlags.nm = true ; \
		mChangedFlags.mIsChanged = true ; \
	} \
	nm = val

#define CHANGED(nm) \
	(mChangedFlags.nm ? "*" : "")


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================
static const Frequency zeroFrequency{0ULL};

//-------------------------------------------------------------------------------------------------------------
static const std::vector<std::string> state_table{
	//    STATE_DISABLE = 0,
	"DISABLE",
	//    STATE_ENABLE,
	"ENABLE",
	//    STATE_OTHER
	"OTHER",
};

std::string ICarrier::stateToStr(ICarrier::State state)
{
	return state_table[state] ;
}

ICarrier::State ICarrier::strToState(const std::string& stateStr)
{
	auto entry(std::find(state_table.begin(), state_table.end(), stateStr)) ;
	if (entry == state_table.end())
		return ICarrier::STATE_OTHER ;

	return static_cast<ICarrier::State>(std::distance(state_table.begin(), entry)) ;
}

std::set<std::string> ICarrier::getAllStates()
{
	std::set<std::string> all ;

	// HACK: At present we only support ENABLE or DISABLE
//	for (auto entry : state_table)
//		all.insert(entry) ;

	all.insert(state_table[0]) ;
	all.insert(state_table[1]) ;
	return all ;
}

//-------------------------------------------------------------------------------------------------------------
static const std::vector<std::string> signals_table{
	//	SIGTYPE_NONE	= 0,
	"NONE",
	//    SIGTYPE_TX,
	"TX",
	//    SIGTYPE_CW,
	"CW",
	//    SIGTYPE_OTHER
	"OTHER",
};

std::string ICarrier::signalsToStr(ICarrier::Signals signals)
{
	return signals_table[signals] ;
}

ICarrier::Signals ICarrier::strToSignals(const std::string& signalsStr)
{
	auto entry(std::find(signals_table.begin(), signals_table.end(), signalsStr)) ;
	if (entry == signals_table.end())
		return ICarrier::SIGTYPE_NONE ;

	return static_cast<ICarrier::Signals>(std::distance(signals_table.begin(), entry)) ;
}

std::set<std::string> ICarrier::getAllSignals()
{
	std::set<std::string> all ;
	for (auto entry : signals_table)
		all.insert(entry) ;
	return all ;
}

//-------------------------------------------------------------------------------------------------------------
static const std::vector<std::string> prefix_len_table{
	//	PREFIX_LENGTH_NORMAL    = 0,
	"NORMAL",
	//  PREFIX_LENGTH_EXTENDED	= 1
	"EXTENDED",
	//  PREFIX_NONE
	"NONE"
};

std::string ICarrier::prefixLenToStr(ICarrier::CyclicPrefixLenType prefixLen)
{
	return prefix_len_table[prefixLen] ;
}

ICarrier::CyclicPrefixLenType ICarrier::strToPrefixLen(const std::string& PrefixLenStr)
{
	auto entry(std::find(prefix_len_table.begin(), prefix_len_table.end(), PrefixLenStr)) ;
	if (entry == prefix_len_table.end())
		return ICarrier::PREFIX_NONE ;

	return static_cast<ICarrier::CyclicPrefixLenType>(std::distance(prefix_len_table.begin(), entry)) ;
}

//-------------------------------------------------------------------------------------------------------------
static const std::vector<std::string> type_table{
	//	CARRTYPE_NONE	= 0,
	"NONE",
	//	CARRTYPE_LTE1_4	= 1,
	"LTE1_4",
	//	CARRTYPE_LTE3	= 2,
	"LTE3",
	//	CARRTYPE_LTE5	= 3,
	"LTE5",
	//	CARRTYPE_LTE10	= 4,
	"LTE10",
	//	CARRTYPE_LTE15	= 5,
	"LTE15",
	//	CARRTYPE_LTE20	= 6,
	"LTE20",

	//	CARRTYPE_WCDMA	= 7,
	"WCDMA",

	// PIM settings
	//    CARRTYPE_PIM1_4	= 8,
	"PIM1_4",
	//    CARRTYPE_PIM3		= 9,
	"PIM3",
	//    CARRTYPE_PIM5		= 10,
	"PIM5",
	//    CARRTYPE_PIM10	= 11,
	"PIM10",
	//    CARRTYPE_PIM15	= 12,
	"PIM15",
	//    CARRTYPE_PIM20	= 13,
	"PIM20",

	// CARRTYPE_IBW153_6 = 100Mhz BW cloecked at 153.6
	"IBW153_6",

	// CARRTYPE_IBW122_88 = 100MHz BW clocked at 122.88
	"IBW122_88",

	//	CARRTYPE_5GNR5
	"5GNR5",
	//	CARRTYPE_5GNR10
	"5GNR10",
	//	CARRTYPE_5GNR15
	"5GNR15",
	//	CARRTYPE_5GNR20
	"5GNR20",
	//	CARRTYPE_5GNR25
	"5GNR25",
	//	CARRTYPE_5GNR30
	"5GNR30",
	//	CARRTYPE_5GNR40
	"5GNR40",
	//	CARRTYPE_5GNR50
	"5GNR50",
	//	CARRTYPE_5GNR60
	"5GNR60",
	//	CARRTYPE_5GNR70
	"5GNR70",
	//	CARRTYPE_5GNR80
	"5GNR80",
	//	CARRTYPE_5GNR90
	"5GNR90",
	//	CARRTYPE_5GNR100
	"5GNR100",

	// 5G NB-IoT
//	CARRTYPE_NBIOT		= 29,
	"NB-IOT",
};

std::string ICarrier::typeToStr(ICarrier::Type type)
{
	return type_table[type] ;
}

ICarrier::Type ICarrier::strToType(const std::string& typeStr)
{
	auto entry(std::find(type_table.begin(), type_table.end(), typeStr)) ;
	if (entry == type_table.end())
		return ICarrier::CARRTYPE_NONE ;

	return static_cast<ICarrier::Type>(std::distance(type_table.begin(), entry)) ;
}

std::set<std::string> ICarrier::getAllTypes()
{
	std::set<std::string> all ;
	for (auto entry : type_table)
		all.insert(entry) ;
	return all ;
}

std::set<std::string> ICarrier::getRrhTypes()
{
	std::set<std::string> types ;
	for (auto entry : type_table)
	{
		if (
			(entry.find("LTE") == std::string::npos) &&
			(entry.find("NR") == std::string::npos) &&
			(entry.find("NB-IOT") == std::string::npos)
		)
			continue ;
		types.insert(entry) ;
	}

	return types ;
}

std::set<std::string> ICarrier::getPimTypes()
{
	std::set<std::string> types(getRrhTypes()) ;
	for (auto entry : type_table)
	{
		if (entry.find("PIM") == std::string::npos)
			continue ;
		types.insert(entry) ;
	}
	return types ;
}

//-------------------------------------------------------------------------------------------------------------
static const std::vector<std::string> scs_table{
//	SCS_NONE,
	"NONE",
//	SCS_1kHz25,
	"1.25KHZ",
//	SCS_3kHz75,
	"3.75KHZ",
//	SCS_5kHz,
	"5KHZ",
//	SCS_7kHz5,
	"7.25KHZ",
//	SCS_15kHz,
	"15KHZ",
//	SCS_30kHz,
	"30KHZ",
//	SCS_60kHz,
	"60KHZ",
//	SCS_120kHz,
	"120KHZ",
//	SCS_240kHz,
	"240KHZ",

};

std::string ICarrier::scsToStr(ICarrier::ScsType scs)
{
	return scs_table[ (unsigned)scs ] ;
}

ICarrier::ScsType ICarrier::strToScs(const std::string& scsStr)
{
	auto entry(std::find(scs_table.begin(), scs_table.end(), scsStr)) ;
	if (entry == scs_table.end())
		return ICarrier::SCS_NONE ;

	return static_cast<ICarrier::ScsType>(std::distance(scs_table.begin(), entry)) ;
}


//-------------------------------------------------------------------------------------------------------------
static const std::vector<std::string> fftsize_table{
	//	FFT_NONE,
		"NONE",
	//	FFT_128,
		"128",
	//	FFT_256,
		"256",
	//	FFT_512,
		"512",
	//	FFT_1024,
		"1024",
	//	FFT_1536,
		"1536",
	//	FFT_2048,
		"2048",
	//	FFT_4096,
		"4096",
};

std::string ICarrier::fftsizeToStr(ICarrier::FFTsizeType fftsize)
{
	return fftsize_table[ (unsigned)fftsize ] ;
}

ICarrier::FFTsizeType ICarrier::strToFftsize(const std::string& fftsizeStr)
{
	auto entry(std::find(fftsize_table.begin(), fftsize_table.end(), fftsizeStr)) ;
	if (entry == fftsize_table.end())
		return ICarrier::FFT_NONE ;

	return static_cast<ICarrier::FFTsizeType>(std::distance(fftsize_table.begin(), entry)) ;
}

//-------------------------------------------------------------------------------------------------------------
static const std::vector<std::string> mode_table{
	//	MODE_LTE,
		"LTE",
	//	MODE_5GNR,
		"5GNR",
};

std::string ICarrier::modeToStr(ICarrier::ModeType mode)
{
	return mode_table[ (unsigned)mode ] ;
}

ICarrier::ModeType ICarrier::strToMode(const std::string& modeStr)
{
	auto entry(std::find(mode_table.begin(), mode_table.end(), modeStr)) ;
	if (entry == mode_table.end())
		return ICarrier::MODE_LTE ;

	return static_cast<ICarrier::ModeType>(std::distance(mode_table.begin(), entry)) ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonCarrier::CommonCarrier(unsigned carrierIndex, unsigned maxTxPaths, unsigned maxRxPaths, bool carrierSetter):
	mRxIFFrequency(0ULL),
	mTxIFFrequency(0ULL),

	mCarrierMutex(),
	mIndex( carrierIndex ),
	mMaxTxPaths( maxTxPaths ),
	mMaxRxPaths( maxRxPaths ),
	mIsCpri(true),
	mTxFrequency(0ULL),
	mRxFrequency(0ULL),
	mTxFrequencyOffset(0),
	mRxFrequencyOffset(0),
	mTxFreqOffsetSet(false),
	mRxFreqOffsetSet(false),
	mState( STATE_DISABLE ),
	mSignalType( SIGTYPE_NONE ),
	mType( CARRTYPE_NONE),
	mPower(0.0),
	mUplinkNoise(0.0),
	mTxScaling(0.0),
	mGrpSizeUp(0),
	mGrpSizeDown(0),
	mLoopback(false),

	mTxContainers( maxTxPaths ),
	mRxContainers( maxRxPaths ),
	mTxFibres( maxTxPaths ),
	mRxFibres( maxRxPaths ),
	mShutdownTx( maxTxPaths ),
	mUlDlConfig(0),
	mSpSuConfig(0),
	mUlPrefixLen(PREFIX_LENGTH_NORMAL),
	mDlPrefixLen(PREFIX_LENGTH_NORMAL),

	mUlScs(ICarrier::SCS_NONE),
	mDlScs(ICarrier::SCS_NONE),
	mUlFftSize(ICarrier::FFT_NONE),
	mDlFftSize(ICarrier::FFT_NONE),

	mDlEaxcId( maxTxPaths ),
	mUlEaxcId( maxRxPaths ),
	mUlMacId(0),

	mMode(ICarrier::MODE_LTE),
	mDlCpSize(0),
	mDlCpOtherSize(0),
	mUlCpSize(0),
	mUlCpOtherSize(0),

	mChangedFlags(maxTxPaths, maxRxPaths),
	mCarrierSetter(carrierSetter)
{
	std::fill(mTxContainers.begin(), mTxContainers.end(), 0) ;
	std::fill(mRxContainers.begin(), mRxContainers.end(), 0) ;
	std::fill(mTxFibres.begin(), mTxFibres.end(), 0) ;
	std::fill(mRxFibres.begin(), mRxFibres.end(), 0) ;
	std::fill(mShutdownTx.begin(), mShutdownTx.end(), false) ;
	std::fill(mDlEaxcId.begin(), mDlEaxcId.end(), 0) ;
	std::fill(mUlEaxcId.begin(), mUlEaxcId.end(), 0) ;
}

//-------------------------------------------------------------------------------------------------------------
CommonCarrier::~CommonCarrier()
{
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getNumberTxPaths(void) const
{
	return mMaxTxPaths;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getNumberRxPaths(void) const
{
	return mMaxRxPaths;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getIndex(void) const
{
	return mIndex;
}

//-------------------------------------------------------------------------------------------------------------
const ICarrier::State CommonCarrier::getState(void) const
{
	GET_VALUE(mState) ;
}

//-------------------------------------------------------------------------------------------------------------
const ICarrier::Signals CommonCarrier::getSigType(void) const
{
	GET_VALUE(mSignalType) ;
}

//-------------------------------------------------------------------------------------------------------------
const ICarrier::Type CommonCarrier::getType(void) const
{
	GET_VALUE(mType) ;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonCarrier::getTxFrequency() const
{
	// For now, assume all/both LO's will be set to the same value
	Frequency txIfFreq(getTxIfFrequency(0)) ;

	Mutex::Lock lock(mCarrierMutex) ;
	Frequency txFreq(mTxFrequency) ;

	// if the frequency offset is set then use it with the LO
	if (mTxFreqOffsetSet)
	{
		// use offset
		txFreq = Frequency( txIfFreq.getDbl(Frequency::KHz) + mTxFrequencyOffset.getDbl(Frequency::KHz), Frequency::KHz ) ;
	}
	return txFreq;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonCarrier::getRxFrequency() const
{
	// For now, assume all/both LO's will be set to the same value
	Frequency rxIfFreq(getRxIfFrequency(0)) ;

	Mutex::Lock lock(mCarrierMutex) ;
	Frequency rxFreq(mRxFrequency) ;

	// if the frequency offset is set then use it with the LO
	if (mRxFreqOffsetSet)
	{
		// use offset
		rxFreq = Frequency( rxIfFreq.getDbl(Frequency::KHz) + mRxFrequencyOffset.getDbl(Frequency::KHz), Frequency::KHz ) ;
	}
	return rxFreq;
}

//-------------------------------------------------------------------------------------------------------------
const FrequencyOffset CommonCarrier::getTxFrequencyOffset() const
{
	GET_VALUE(mTxFrequencyOffset) ;
}

//-------------------------------------------------------------------------------------------------------------
const FrequencyOffset CommonCarrier::getRxFrequencyOffset() const
{
	GET_VALUE(mRxFrequencyOffset) ;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonCarrier::getTxFrequencySetting() const
{
	GET_VALUE(mTxFrequency) ;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonCarrier::getRxFrequencySetting() const
{
	GET_VALUE(mRxFrequency) ;
}


//-------------------------------------------------------------------------------------------------------------
const Power CommonCarrier::getTxPower() const
{
	GET_VALUE(mPower) ;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getTxContainer(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;
	if( (unsigned int)path >= mTxContainers.size() )
		return 0 ;

	// if shutdown on this TX then emulate having zeroes the container
	if (mShutdownTx[path])
		return 0 ;

	// ok to return actual value
	return mTxContainers[ path ];
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getRxContainer(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;
	if( (unsigned int)path < mRxContainers.size() )
	{
		return mRxContainers[ path ];
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getTxFibre(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;
	if( (unsigned int)path < mTxFibres.size() )
	{
		return mTxFibres[ path ];
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getRxFibre(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;
	if( (unsigned int)path < mRxFibres.size() )
	{
		return mRxFibres[ path ];
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getGroupSizeUp() const
{
	GET_VALUE(mGrpSizeUp) ;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getGroupSizeDown() const
{
	GET_VALUE(mGrpSizeDown) ;
}

//-------------------------------------------------------------------------------------------------------------
const Power CommonCarrier::getUplinkNoise() const
{
	GET_VALUE(mUplinkNoise) ;
}

//-------------------------------------------------------------------------------------------------------------
const Power CommonCarrier::getTxScaling() const
{
	GET_VALUE(mTxScaling) ;
}


//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::isCPRI() const
{
	GET_VALUE(mIsCpri) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::isConfigured() const
{
	bool configured = false;
	if( isTx() && ( (getTxFrequency() != zeroFrequency) || isTxFreqOffsetSet() ) )
	{
		configured = true;
	}

	if( isRx() && ( (getRxFrequency() != zeroFrequency) || isRxFreqOffsetSet() ) )
	{
		configured = true;
	}

	return configured;

}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::isTxConfigured() const
{
	bool configured = false;
	if( isTx() && ( (getTxFrequency() != zeroFrequency) || isTxFreqOffsetSet() ) )
	{
		configured = true;
	}

	return configured;

}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::isRxConfigured() const
{
	bool configured = false;
	if( isRx() && ( (getRxFrequency() != zeroFrequency) || isRxFreqOffsetSet() ) )
	{
		configured = true;
	}

	return configured;

}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::isTx() const
{
	bool hasTx = false;

	for( unsigned index = 0 ; index <  mMaxTxPaths ; index++ )
	{
	   if ( ( getTxContainer(index) != 0 ) || ( getDlEaxcId(index) != 0 ) )
	   {
		   hasTx = true;
		   break;
	   }
	}

	return hasTx;

}


//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::isTx(const unsigned txpath) const
{
	if (txpath >= mMaxTxPaths)
		return false ;

	if ( ( getTxContainer(txpath) != 0 ) || ( getDlEaxcId(txpath) != 0 ) )
		return true ;

	return false;
}


//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::isRx() const
{
	bool hasRx = false;
	for( unsigned index = 0 ; index <  mMaxRxPaths ; index++ )
	{
		if ( ( getRxContainer(index) != 0 ) || ( getUlEaxcId(index) != 0 ) )
		{
			hasRx = true;
			break;
		}
	}
	return hasRx;

}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::isRx(const unsigned rxpath) const
{
	if (rxpath >= mMaxRxPaths)
		return false ;

	if ( ( getRxContainer(rxpath) != 0 ) || ( getUlEaxcId(rxpath) != 0 ) )
		return true ;

	return false;
}


//-------------------------------------------------------------------------------------------------------------
const Frequency CommonCarrier::getTxIfFrequency(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if (path >= mMaxTxPaths)
		return Frequency(0.0) ;

	std::vector< std::shared_ptr<ITxPort> > txPorts( ITxPortFactory::getPorts( ) ) ;
	return txPorts.at(path)->getFrequency();
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonCarrier::getRxIfFrequency(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if (path >= mMaxRxPaths)
		return Frequency(0.0) ;

	std::vector< std::shared_ptr<IRxPort> > rxPorts( IRxPortFactory::getPorts( ) ) ;
	return rxPorts.at(path)->getFrequency();
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getLoopback(void) const
{
	GET_VALUE(mLoopback) ;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getUlDlConfig(void) const
{
	GET_VALUE(mUlDlConfig) ;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrier::getSpSuConfig(void) const
{
	GET_VALUE(mSpSuConfig) ;
}

//-------------------------------------------------------------------------------------------------------------
const ICarrier::CyclicPrefixLenType CommonCarrier::getUlPrefixLen(void) const
{
	GET_VALUE(mUlPrefixLen) ;
}

//-------------------------------------------------------------------------------------------------------------
const ICarrier::CyclicPrefixLenType CommonCarrier::getDlPrefixLen(void) const
{
	GET_VALUE(mDlPrefixLen) ;
}


//-------------------------------------------------------------------------------------------------------------
Power CommonCarrier::getRssi(unsigned path, std::string& error) const
{
	return Power(0.0) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getShutdownTx(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mShutdownTx.size())
		return false ;

	return mShutdownTx.at(path) ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrier::ScsType CommonCarrier::getDlScs() const
{
	GET_VALUE(mDlScs) ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrier::FFTsizeType CommonCarrier::getDlFftSize() const
{
	GET_VALUE(mDlFftSize) ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrier::ScsType CommonCarrier::getUlScs() const
{
	GET_VALUE(mUlScs) ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrier::FFTsizeType CommonCarrier::getUlFftSize() const
{
	GET_VALUE(mUlFftSize) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonCarrier::getUlEaxcId(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mUlEaxcId.size())
		return 0 ;

	return mUlEaxcId.at(path) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonCarrier::getDlEaxcId(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mDlEaxcId.size())
		return 0 ;

	return mDlEaxcId.at(path) ;
}

//-------------------------------------------------------------------------------------------------------------
uint64_t CommonCarrier::getUlMacId() const
{
	GET_VALUE(mUlMacId) ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrier::ModeType CommonCarrier::getMode() const
{
	GET_VALUE(mMode) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonCarrier::getUlCpSize() const
{
	GET_VALUE(mUlCpSize) ;
}

unsigned CommonCarrier::getUlCpOtherSize() const
{
	GET_VALUE(mUlCpOtherSize) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonCarrier::getDlCpSize() const
{
	GET_VALUE(mDlCpSize) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonCarrier::getDlCpOtherSize() const
{
	GET_VALUE(mDlCpOtherSize) ;
}



//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::unconfigure()
{
//std::cerr << getIndex() << " CommonCarrier::unconfigure()" << std::endl ;

	bool status = true ;

	{
		Mutex::Lock lock(mCarrierMutex) ;
		mIsCpri = true ;
	}

	// Need to treat the shutdown TX flag slightly different from the rest of the parameters
	// Need to transfer a TRUE value over then immediately clear the setter's shutdown flag.
	// Otherwise the setter's TX container settings will be affected by it's shutdown flag
	{
		Mutex::Lock lock(mCarrierMutex) ;
		std::fill(mShutdownTx.begin(), mShutdownTx.end(), false) ;
	}

//std::cerr << " * clear containers : status=" << status << std::endl ;

	for( unsigned index = 0 ; index < mMaxRxPaths; index++ )
	{
		status &= setRxContainer(index, 0 );
		status &= setRxFibre(index, 0 );
		status &= setUlEaxcId(index, 0 );
	}

	for( unsigned index = 0 ; index < mMaxTxPaths; index++ )
	{
		status &= setTxContainer(index, 0 );
		status &= setTxFibre( index, 0 );
		status &= setDlEaxcId( index, 0 );
	}

//std::cerr << " * clear freq offsets : status=" << status << std::endl ;

	// clear frequency offsets (if supported)
	setRxFrequencyOffset( 0.0 );
	setTxFrequencyOffset( 0.0 );

//std::cerr << " * clear settings : status=" << status << std::endl ;

	status &= setTxPower( 0.0 );

	status &= setRxFrequency( 0.0 );
	status &= setTxFrequency( 0.0 );

	status &= setSigType( ICarrier::SIGTYPE_NONE );
	status &= setType( ICarrier::CARRTYPE_NONE );
	status &= setUplinkNoise( 0.0 );
	status &= setGroupSizeUp( 0 );
	status &= setGroupSizeDown( 0 );
	status &= setTxScaling( 0.0 );
	status &= setLoopback( false );

	status &= setState( ICarrier::STATE_DISABLE );

//std::cerr << " * clear freq offset flags : status=" << status << std::endl ;
	{
		Mutex::Lock lock(mCarrierMutex) ;
		mTxFreqOffsetSet = false ;
		mRxFreqOffsetSet = false ;
	}

	status &= setUlDlConfig(0);
	status &= setSpSuConfig(0);
	status &= setUlPrefixLenConfig(PREFIX_LENGTH_NORMAL);
	status &= setDlPrefixLenConfig(PREFIX_LENGTH_NORMAL);

	status &= setUlScs(ICarrier::SCS_NONE) ;
	status &= setDlScs(ICarrier::SCS_NONE) ;
	status &= setUlFftSize(ICarrier::FFT_NONE) ;
	status &= setDlFftSize(ICarrier::FFT_NONE) ;
	status &= setUlMacId(0) ;

	status &= setMode(ICarrier::MODE_LTE) ;
	status &= setUlCpSize(0) ;
	status &= setUlCpOtherSize(0) ;
	status &= setDlCpSize(0) ;
	status &= setDlCpOtherSize(0) ;


//std::cerr << " unconfig DONE : status=" << status << std::endl ;
	return status ;
}


//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setCarrier(const ICarrier& carrier)
{
	bool status = true ;

	{
		Mutex::Lock lock(mCarrierMutex) ;
		mIsCpri = carrier.isCPRI() ;
	}

	// Need to treat the shutdown TX flag slightly different from the rest of the parameters
	// Need to transfer a TRUE value over then immediately clear the setter's shutdown flag.
	// Otherwise the setter's TX container settings will be affected by it's shutdown flag
	{
		Mutex::Lock lock(mCarrierMutex) ;
		std::fill(mShutdownTx.begin(), mShutdownTx.end(), false) ;
	}
	const CommonCarrier& commonCarrier(dynamic_cast<const CommonCarrier&>(carrier)) ;
	for( unsigned index = 0 ; index < mMaxTxPaths; index++ )
	{
		Mutex::Lock lock(mCarrierMutex) ;
		if (carrier.getShutdownTx( index ))
		{
			mShutdownTx[index] = true ;
		}
		else
		{
			mShutdownTx[index] = false ;
		}

		// This is a bit cheesey - I need to clear the setter's flags, but logically we should only need
		// to be given an ICarrier const. So I've marked the flags as mutable (a bit like mutable Mutex's)
		commonCarrier.mShutdownTx[index] = false ;
	}

	for( unsigned index = 0 ; index < mMaxRxPaths; index++ )
	{
		status &= setRxContainer(index,  carrier.getRxContainer(index) );
		status &= setRxFibre(index,  carrier.getRxFibre(index) );
		status &= setUlEaxcId(index,  carrier.getUlEaxcId(index) );
	}

	for( unsigned index = 0 ; index < mMaxTxPaths; index++ )
	{
		status &= setTxContainer(index,  carrier.getTxContainer(index) );
		status &= setTxFibre( index, carrier.getTxFibre( index ) );
		status &= setDlEaxcId( index, carrier.getDlEaxcId( index ) );
	}

	status &= setTxPower( carrier.getTxPower() );
	status &= setRxFrequency( carrier.getRxFrequencySetting() );
	status &= setTxFrequency( carrier.getTxFrequencySetting() );

	if (commonCarrier.isRxFreqOffsetSet())
		status &= setRxFrequencyOffset( carrier.getRxFrequencyOffset() );
	if (commonCarrier.isTxFreqOffsetSet())
		status &= setTxFrequencyOffset( carrier.getTxFrequencyOffset() );

	status &= setSigType( carrier.getSigType() );
	status &= setType( carrier.getType() );
	status &= setUplinkNoise( carrier.getUplinkNoise() );
	status &= setGroupSizeUp( carrier.getGroupSizeUp() );
	status &= setGroupSizeDown( carrier.getGroupSizeDown() );
	status &= setTxScaling( carrier.getTxScaling() );
	status &= setLoopback( carrier.getLoopback() );

	status &= setState( carrier.getState() );

	status &= setUlDlConfig(carrier.getUlDlConfig());
	status &= setSpSuConfig(carrier.getSpSuConfig());
	status &= setUlPrefixLenConfig(carrier.getUlPrefixLen());
	status &= setDlPrefixLenConfig(carrier.getDlPrefixLen());

	status &= setUlScs(carrier.getUlScs()) ;
	status &= setDlScs(carrier.getDlScs()) ;
	status &= setUlFftSize(carrier.getUlFftSize()) ;
	status &= setDlFftSize(carrier.getDlFftSize()) ;
	status &= setUlMacId(carrier.getUlMacId()) ;

	status &= setMode(carrier.getMode()) ;
	status &= setUlCpSize(carrier.getUlCpSize()) ;
	status &= setUlCpOtherSize(carrier.getUlCpOtherSize()) ;
	status &= setDlCpSize(carrier.getDlCpSize()) ;
	status &= setDlCpOtherSize(carrier.getDlCpOtherSize()) ;


	return status ;
}


//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setState(ICarrier::State state)
{
	Mutex::Lock lock(mCarrierMutex) ;

	// track changes
	if( state == State::STATE_ENABLE || state == State::STATE_DISABLE)
	{
		if (mState != state)
		{
			mChangedFlags.mState = true ;
			mChangedFlags.mIsChanged = true ;
		}
		mState = state;
		return true;
	}
	return false;

}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setTxFrequency(Frequency frequency)
{
	Mutex::Lock lock(mCarrierMutex) ;

	// track changes
	if (mTxFrequency != frequency)
	{
		mChangedFlags.mTxFrequency = true ;
		mChangedFlags.mIsChanged = true ;
	}
	mTxFrequency = frequency;

	// If non-zero then don't use frequency offset
	if (mTxFrequency != 0)
	{
		mTxFrequencyOffset = Frequency(0.0) ;
		mTxFreqOffsetSet = false ;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setRxFrequency(Frequency frequency)
{
	Mutex::Lock lock(mCarrierMutex) ;

	// track changes
	if (mRxFrequency != frequency)
	{
		mChangedFlags.mRxFrequency = true ;
		mChangedFlags.mIsChanged = true ;
	}

	mRxFrequency = frequency;

	// If non-zero then don't use frequency offset
	if (mRxFrequency != 0)
	{
		mRxFrequencyOffset = Frequency(0.0) ;
		mRxFreqOffsetSet = false ;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setTxFrequencyOffset(FrequencyOffset frequency)
{
	SET_VALUE(mTxFrequencyOffset, frequency) ;
	mTxFreqOffsetSet = true ;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setRxFrequencyOffset(FrequencyOffset frequency)
{
	SET_VALUE(mRxFrequencyOffset, frequency) ;
	mRxFreqOffsetSet = true ;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setTxPower(Power power)
{
	SET_VALUE(mPower, power) ;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setSigType(ICarrier::Signals sigType)
{
	SET_VALUE(mSignalType, sigType) ;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setType(ICarrier::Type type)
{
	SET_VALUE(mType, type) ;
	return  true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setTxContainer(unsigned path, unsigned container)
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( (unsigned int)path >= mTxContainers.size())
		return false ;

	// track changes
	if (mTxContainers[ path ] != container)
	{
		mChangedFlags.mTxContainers[ path ] = true ;
		mChangedFlags.mIsChanged = true ;

		// If enabling or disabling then flag this as an TX path change
		if ( (mTxContainers[ path ] == 0) || (container == 0))
			mChangedFlags.mTxPaths[ path ] = true ;
	}

	mTxContainers[ path ] = container;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setRxContainer(unsigned path, unsigned container)
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( (unsigned int)path >= mRxContainers.size())
		return false ;

	// track changes
	if (mRxContainers[ path ] != container)
	{
		mChangedFlags.mRxContainers[ path ] = true ;
		mChangedFlags.mIsChanged = true ;

		// If enabling or disabling then flag this as an RX path change
		if ( (mRxContainers[ path ] == 0) || (container == 0))
			mChangedFlags.mRxPaths[ path ] = true ;
	}

	mRxContainers[ path ] = container;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setTxFibre(unsigned path, unsigned fibre)
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( (unsigned int)path >= mTxFibres.size())
		return false ;

	// track changes
	if (mTxFibres[ path ] != fibre)
	{
		mChangedFlags.mTxFibres[ path ] = true ;
		mChangedFlags.mIsChanged = true ;
	}
	mTxFibres[ path ] = fibre;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setRxFibre(unsigned path, unsigned fibre)
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( (unsigned int)path >= mRxFibres.size())
		return false ;

	// track changes
	if (mRxFibres[ path ] != fibre)
	{
		mChangedFlags.mRxFibres[ path ] = true ;
		mChangedFlags.mIsChanged = true ;
	}

	mRxFibres[ path ] = fibre;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setGroupSizeUp(unsigned grpSizeUp)
{
	SET_VALUE(mGrpSizeUp, grpSizeUp) ;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setGroupSizeDown(unsigned grpSizeDown)
{
	SET_VALUE(mGrpSizeDown, grpSizeDown) ;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setUplinkNoise(Power upLinkNoisedB)
{
	SET_VALUE(mUplinkNoise, upLinkNoisedB) ;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setTxScaling(Power dlScaling)
{
	SET_VALUE(mTxScaling, dlScaling) ;
	return true;
}


//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setLoopback(bool loopBack)
{
	SET_VALUE(mLoopback, loopBack) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setSpSuConfig(unsigned spsuConfig)
{
	SET_VALUE(mSpSuConfig, spsuConfig) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setUlDlConfig(unsigned uldlConfig)
{
	SET_VALUE(mUlDlConfig, uldlConfig) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setUlPrefixLenConfig(ICarrier::CyclicPrefixLenType ulPrefixLen)
{
	SET_VALUE(mUlPrefixLen, ulPrefixLen) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setDlPrefixLenConfig(ICarrier::CyclicPrefixLenType dlPrefixLen)
{
	SET_VALUE(mDlPrefixLen, dlPrefixLen) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setShutdownTx(unsigned path)
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mShutdownTx.size())
		return false ;

	mShutdownTx.at(path) = true ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setUlEaxcId(unsigned path, unsigned eaxcId)
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mUlEaxcId.size())
		return false ;

	// track changes
	if (mUlEaxcId.at(path) != eaxcId)
	{
		mChangedFlags.mUlEaxcId.at(path) = true ;
		mChangedFlags.mIsChanged = true ;
	}

	mUlEaxcId.at(path) = eaxcId ;
	if (eaxcId > 0)
		mIsCpri = false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setDlEaxcId(unsigned path, unsigned eaxcId)
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mDlEaxcId.size())
		return false ;

	// track changes
	if (mDlEaxcId.at(path) != eaxcId)
	{
		mChangedFlags.mDlEaxcId.at(path) = true ;
		mChangedFlags.mIsChanged = true ;
	}

	mDlEaxcId.at(path) = eaxcId ;
	if (eaxcId > 0)
		mIsCpri = false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setDlScs(ScsType scs)
{
	SET_VALUE(mDlScs, scs) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setDlFftSize(FFTsizeType fftSize)
{
	SET_VALUE(mDlFftSize, fftSize) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setUlScs(ScsType scs)
{
	SET_VALUE(mUlScs, scs) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setUlFftSize(FFTsizeType fftSize)
{
	SET_VALUE(mUlFftSize, fftSize) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setUlMacId(uint64_t macid)
{
	SET_VALUE(mUlMacId, macid) ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setMode(ICarrier::ModeType mode)
{
	SET_VALUE(mMode, mode) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setUlCpSize(unsigned sizeTs)
{
	SET_VALUE(mUlCpSize, sizeTs) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setUlCpOtherSize(unsigned sizeTs)
{
	SET_VALUE(mUlCpOtherSize, sizeTs) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setDlCpSize(unsigned sizeTs)
{
	SET_VALUE(mDlCpSize, sizeTs) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::setDlCpOtherSize(unsigned sizeTs)
{
	SET_VALUE(mDlCpOtherSize, sizeTs) ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
void CommonCarrier::showCarrier(std::ostream& os) const
{
	bool carrierIsTx( isTx() ) ;
	bool carrierIsRx( isRx() ) ;
	bool configured( isConfigured() ) ;

	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;

	// Special case for TX containers - create a replica set that reflect the values returned by getTxContainer()
	// This includes the effect of any shutdown flag
	std::vector<unsigned> txContainers;
	for (unsigned path=0; path < mTxContainers.size(); ++path)
	{
		txContainers.push_back( getTxContainer(path)) ;
	}

	Mutex::Lock lock(mCarrierMutex) ;

	os << "Carrier [" << mIndex << "]" <<
			" " << (carrierIsTx ? "DL" : "") << " " << (carrierIsRx ? "UL" : "") << " " <<
			CHANGED(mIsChanged) <<
			std::endl ;

	if (!configured)
	{
		os << " ** Not Configured **" << std::endl ;
		return ;
	}

	os << " * State...........: " << stateToStr(mState) << CHANGED(mState) << std::endl ;
	os << " * Type............: " << typeToStr(mType) << CHANGED(mType) << std::endl ;
	os << " * Signal Type.....: " << signalsToStr(mSignalType) << CHANGED(mSignalType) << std::endl ;
	os << " * Loopback........: " << (mLoopback ? "ON" : "OFF") << CHANGED(mSignalType) << std::endl ;
	os << " * TX Shutdown.....: " ; CarrierUtils::showVector(mShutdownTx, os) ; os << std::endl ;
	os << " * Mode............: " << modeToStr(mMode) << CHANGED(mMode) << std::endl ;

	if (carrierIsTx)
	{
		os << " * Tx Centre Freq..: " << mTxFrequency.getUint(Frequency::KHz) << " kHz" << CHANGED(mTxFrequency) << std::endl ;

		if (mTxFreqOffsetSet)
			os << " * Tx offset.......: " << mTxFrequencyOffset.getUint(Frequency::KHz) << " kHz" << CHANGED(mTxFrequencyOffset) << std::endl ;

		os << " * Power...........: " << mPower << CHANGED(mPower) << std::endl ;
		os << " * Tx Scaling......: " << mTxScaling.get() << CHANGED(mTxScaling) << std::endl ;
		os << " * DL Group size...: " << mGrpSizeDown << CHANGED(mGrpSizeDown) << std::endl ;

		os << " * TX Containers...: " ; CarrierUtils::showVector(txContainers, mChangedFlags.mTxContainers, os) ; os << std::endl ;

		os << " * TX Fibres.......: " ; CarrierUtils::showVector(mTxFibres, mChangedFlags.mTxFibres, os) ; os << std::endl ;

//		os << " * Tx IF Freq......: " << getTxIfFrequency().getUint(Frequency::KHz) << " kHz" << std::endl ;



		os << " * TX SCS..........: " << scsToStr(mDlScs) << CHANGED(mDlScs) << std::endl ;
		os << " * TX FFT..........: " << fftsizeToStr(mDlFftSize) << CHANGED(mDlFftSize) << std::endl ;
		os << " * TX CP0 Size.....: " << mDlCpSize << CHANGED(mDlCpSize) << std::endl ;
		os << " * TX CP1 Size.....: " << mDlCpOtherSize << CHANGED(mDlCpOtherSize) << std::endl ;
		os << " * TX EAXC-ID......: " ; CarrierUtils::showVector(mDlEaxcId, os) ; os << std::endl ;
		os << " * DL Prefix Len...: " << prefixLenToStr(mDlPrefixLen) << CHANGED(mDlPrefixLen) << std::endl ;


	}

	if (carrierIsRx)
	{
		os << " * Rx Centre Freq..: " << mRxFrequency.getUint(Frequency::KHz) << " kHz" << CHANGED(mRxFrequency) << std::endl ;

		if (mRxFreqOffsetSet)
			os << " * Rx offset.......: " << mRxFrequencyOffset.getUint(Frequency::KHz) << " kHz" << CHANGED(mRxFrequencyOffset) << std::endl ;

		os << " * UL Noise........: " << mUplinkNoise << CHANGED(mUplinkNoise) << std::endl ;

		os << " * RX Containers...: " ; CarrierUtils::showVector(mRxContainers, mChangedFlags.mRxContainers, os) ; os << std::endl ;
		os << " * RX Fibres.......: " ; CarrierUtils::showVector(mRxFibres, mChangedFlags.mRxFibres, os) ; os << std::endl ;

		os << " * UL Group size...: " << mGrpSizeUp << CHANGED(mGrpSizeUp) << std::endl ;

//		os << " * Rx IF Freq......: " << getRxIfFrequency().getUint(Frequency::KHz) << " kHz" << std::endl ;

		os << " * RX SCS..........: " << scsToStr(mUlScs) << CHANGED(mUlScs) << std::endl ;
		os << " * RX FFT..........: " << fftsizeToStr(mUlFftSize) << CHANGED(mUlFftSize) << std::endl ;
		os << " * RX CP0 Size.....: " << mUlCpSize << CHANGED(mUlCpSize) << std::endl ;
		os << " * RX CP1 Size.....: " << mUlCpOtherSize << CHANGED(mUlCpOtherSize) << std::endl ;
		os << " * RX EAXC-ID......: " ; CarrierUtils::showVector(mUlEaxcId, os) ; os << std::endl ;
		os << " * UL Prefix Len...: " << prefixLenToStr(mUlPrefixLen) << CHANGED(mUlPrefixLen) << std::endl ;

		os << " * RX MAC..........: " << macToStr(mUlMacId) << CHANGED(mUlMacId) << std::endl ;
	}

	if (appSettings->getDuplex() == IAppSettings::DUPLEX_TDD)
	{
		os << " * TDD " << std::endl ;
		os << " * * UL/DL Config..: " << mUlDlConfig <<	CHANGED(mUlDlConfig) << std::endl ;
		os << " * * SS Config.....: " << mSpSuConfig << CHANGED(mSpSuConfig) << std::endl ;

	}

}



//=============================================================================================================
// CHANGE MONITOR
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonCarrier::ChangeFlags::ChangeFlags(const unsigned maxTxPaths, const unsigned maxRxPaths):
			mIsChanged(false),
			mTxFrequency(false),
			mRxFrequency(false),
			mTxFrequencyOffset(false),
			mRxFrequencyOffset(false),
			mState( false ),
			mSignalType( false ),
			mType( false),
			mPower(false),
			mUplinkNoise(false),
			mTxScaling(false),
			mGrpSizeUp(false),
			mGrpSizeDown(false),
			mLoopback(false),
			mTxContainers( maxTxPaths ),
			mRxContainers( maxRxPaths ),
			mTxFibres( maxTxPaths ),
			mRxFibres( maxRxPaths ),
			mTxPaths( maxTxPaths ),
			mRxPaths( maxRxPaths ),
			mUlDlConfig(false),
			mSpSuConfig(false),
			mUlPrefixLen(false),
			mDlPrefixLen(false),
			mUlScs(false),
			mDlScs(false),
			mUlFftSize(false),
			mDlFftSize(false),

			mDlEaxcId( maxTxPaths ),
			mUlEaxcId( maxRxPaths ),
			mUlMacId(false),

			mMode(false),
			mDlCpSize(false),
			mDlCpOtherSize(false),
			mUlCpSize(false),
			mUlCpOtherSize(false)


{
	std::fill(mTxContainers.begin(), mTxContainers.end(), false) ;
	std::fill(mRxContainers.begin(), mRxContainers.end(), false) ;
	std::fill(mTxFibres.begin(), mTxFibres.end(), false) ;
	std::fill(mRxFibres.begin(), mRxFibres.end(), false) ;
	std::fill(mTxPaths.begin(), mTxPaths.end(), false) ;
	std::fill(mRxPaths.begin(), mRxPaths.end(), false) ;
	std::fill(mDlEaxcId.begin(), mDlEaxcId.end(), false) ;
	std::fill(mUlEaxcId.begin(), mUlEaxcId.end(), false) ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrier::ChangeFlags::clear(void)
{
	std::fill(mTxContainers.begin(), mTxContainers.end(), false) ;
	std::fill(mRxContainers.begin(), mRxContainers.end(), false) ;
	std::fill(mTxFibres.begin(), mTxFibres.end(), false) ;
	std::fill(mRxFibres.begin(), mRxFibres.end(), false) ;
	std::fill(mTxPaths.begin(), mTxPaths.end(), false) ;
	std::fill(mRxPaths.begin(), mRxPaths.end(), false) ;
	std::fill(mDlEaxcId.begin(), mDlEaxcId.end(), false) ;
	std::fill(mUlEaxcId.begin(), mUlEaxcId.end(), false) ;

	mIsChanged = false ;
	mTxFrequency = false ;
	mRxFrequency = false ;
	mTxFrequencyOffset = false ;
	mRxFrequencyOffset = false ;
	mState = false ;
	mSignalType = false ;
	mType = false ;
	mPower = false ;
	mUplinkNoise = false ;
	mGrpSizeUp = false ;
	mGrpSizeDown = false ;
	mLoopback = false ;
	mTxScaling = false ;
	mUlDlConfig = false;
	mSpSuConfig = false;
	mUlPrefixLen = false;
	mDlPrefixLen = false;

	mUlScs = false;
	mDlScs = false;
	mUlFftSize = false;
	mDlFftSize = false;
	mUlMacId = false;

	mMode = false ;
	mDlCpSize = false ;
	mDlCpOtherSize = false ;
	mUlCpSize = false ;
	mUlCpOtherSize = false ;

}

//-------------------------------------------------------------------------------------------------------------
const void CommonCarrier::applyChanges(void)
{
	Mutex::Lock lock(mCarrierMutex) ;
	mChangedFlags.clear() ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getTxContainerChanged(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mChangedFlags.mTxContainers.size())
		return false ;

	return mChangedFlags.mTxContainers[ path ] ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getRxContainerChanged(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mChangedFlags.mRxContainers.size())
		return false ;

	return mChangedFlags.mRxContainers[ path ] ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getTxFibreChanged(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mChangedFlags.mTxFibres.size())
		return false ;

	return mChangedFlags.mTxFibres[ path ] ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getRxFibreChanged(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mChangedFlags.mRxFibres.size())
		return false ;

	return mChangedFlags.mRxFibres[ path ] ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getTxPowerChanged(void) const
{
	VALUE_CHANGED(mPower) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getSigTypeChanged(void) const
{
	VALUE_CHANGED(mSignalType) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getTypeChanged(void) const
{
	VALUE_CHANGED(mType) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getTxFrequencyChanged(void) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	return mChangedFlags.mTxFrequency || mChangedFlags.mTxFrequencyOffset ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getRxFrequencyChanged(void) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	return mChangedFlags.mRxFrequency || mChangedFlags.mRxFrequencyOffset ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getTxFrequencyOffsetChanged(void) const
{
	VALUE_CHANGED(mTxFrequencyOffset) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getRxFrequencyOffsetChanged(void) const
{
	VALUE_CHANGED(mRxFrequencyOffset) ;
}




//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getUplinkNoiseChanged(void) const
{
	VALUE_CHANGED(mUplinkNoise) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getTxScalingChanged(void) const
{
	VALUE_CHANGED(mTxScaling) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getGroupSizeUpChanged(void) const
{
	VALUE_CHANGED(mGrpSizeUp) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getGroupSizeDownChanged(void) const
{
	VALUE_CHANGED(mGrpSizeDown) ;
}


//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getStateChanged(void) const
{
	VALUE_CHANGED(mState) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getLoopbackChanged(void) const
{
	VALUE_CHANGED(mLoopback) ;
}


//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getTxPathChanged(unsigned txpath) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( txpath >= mChangedFlags.mTxPaths.size())
		return false ;

	return mChangedFlags.mTxPaths.at(txpath) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getRxPathChanged(unsigned rxpath) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( rxpath >= mChangedFlags.mRxPaths.size())
		return false ;

	return mChangedFlags.mRxPaths.at(rxpath) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getUlDlConfigChanged(void) const
{
	VALUE_CHANGED(mUlDlConfig) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getSpSuConfigChanged(void) const
{
	VALUE_CHANGED(mSpSuConfig) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getUlPrefixLenChanged(void) const
{
	VALUE_CHANGED(mUlPrefixLen) ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::getDlPrefixLenChanged(void) const
{
	VALUE_CHANGED(mDlPrefixLen) ;
}


//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrier::isChanged(void) const
{
	Mutex::Lock lock(mCarrierMutex) ;
	return mChangedFlags.mIsChanged ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::isSetter() const
{
	return mCarrierSetter ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::isTxFreqOffsetSet() const
{
	Mutex::Lock lock(mCarrierMutex) ;
	return mTxFreqOffsetSet ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::isRxFreqOffsetSet() const
{
	Mutex::Lock lock(mCarrierMutex) ;
	return mRxFreqOffsetSet ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getDlScsChanged() const
{
	VALUE_CHANGED(mDlScs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getDlFftSizeChanged() const
{
	VALUE_CHANGED(mDlFftSize) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getUlScsChanged() const
{
	VALUE_CHANGED(mUlScs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getUlFftSizeChanged() const
{
	VALUE_CHANGED(mUlFftSize) ;
}


//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getUlEaxcIdChanged(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mChangedFlags.mUlEaxcId.size())
		return false ;

	return mChangedFlags.mUlEaxcId.at(path) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getDlEaxcIdChanged(unsigned path) const
{
	Mutex::Lock lock(mCarrierMutex) ;

	if( path >= mChangedFlags.mDlEaxcId.size())
		return false ;

	return mChangedFlags.mDlEaxcId.at(path) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getUlMacIdChanged() const
{
	VALUE_CHANGED(mUlMacId) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getModeChanged() const
{
	VALUE_CHANGED(mMode) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getUlCpSizeChanged() const
{
	VALUE_CHANGED(mUlCpSize) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getUlCpOtherSizeChanged() const
{
	VALUE_CHANGED(mUlCpOtherSize) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getDlCpSizeChanged() const
{
	VALUE_CHANGED(mDlCpSize) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrier::getDlCpOtherSizeChanged() const
{
	VALUE_CHANGED(mDlCpOtherSize) ;
}
