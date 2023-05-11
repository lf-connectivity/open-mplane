/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelaysMgr.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <algorithm>

#include "ITxPort.h"
#include "IRxPort.h"

#include "stringfunc.hpp"

#include "DelaysMgr.h"

using namespace Mplane ;

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::map<IDelaysMgr::DelayAttr, std::string> DELAY_NAMES{
	{ IDelaysMgr::DELAY_NONE,		"DELAY_NONE" },

	{ IDelaysMgr::OFFSET_DELAY,		"OFFSET_DELAY" },
	{ IDelaysMgr::FRAMEDIFF,		"FRAMEDIFF" },
	{ IDelaysMgr::THRUDELAY_UP,		"THRUDELAY_UP" },
	{ IDelaysMgr::THRUDELAY_DOWN,	"THRUDELAY_DOWN" },

	{ IDelaysMgr::EXTDELAY_UP,		"EXTDELAY_UP" },
	{ IDelaysMgr::EXTDELAY_DOWN,	"EXTDELAY_DOWN" },

	{ IDelaysMgr::ANTDELAY_UP,		"ANTDELAY_UP" },
	{ IDelaysMgr::ANTDELAY_DOWN,	"ANTDELAY_DOWN" },
	{ IDelaysMgr::ADJDELAY_UP,		"ADJDELAY_UP" },
	{ IDelaysMgr::ADJDELAY_DOWN,	"ADJDELAY_DOWN" },
	{ IDelaysMgr::FRAMEOFF_UP,		"FRAMEOFF_UP" },
	{ IDelaysMgr::FRAMEOFF_DOWN,	"FRAMEOFF_DOWN" },
	{ IDelaysMgr::T12,				"FRAME_ADJUST" },
	{ IDelaysMgr::CPRI_UP,			"CPRI_UP" },
	{ IDelaysMgr::CPRI_DOWN,		"CPRI_DOWN" },
	{ IDelaysMgr::CPRI_FRAME_RX,	"CPRI_FRAME_RX" },
	{ IDelaysMgr::CPRI_FRAME_TX,	"CPRI_FRAME_TX" },

} ;

const std::map<IDelaysMgr::DelayAttr, std::string> DELAY_UNITS{
	{ IDelaysMgr::DELAY_NONE,		"" },

	{ IDelaysMgr::OFFSET_DELAY,		"ns" },
	{ IDelaysMgr::FRAMEDIFF,		"BF" },
	{ IDelaysMgr::THRUDELAY_UP,		"ns" },
	{ IDelaysMgr::THRUDELAY_DOWN,	"ns" },

	{ IDelaysMgr::EXTDELAY_UP,		"ns" },
	{ IDelaysMgr::EXTDELAY_DOWN,	"ns" },

	{ IDelaysMgr::ANTDELAY_UP,		"ns" },
	{ IDelaysMgr::ANTDELAY_DOWN,	"ns" },
	{ IDelaysMgr::ADJDELAY_UP,		"ns" },
	{ IDelaysMgr::ADJDELAY_DOWN,	"ns" },
	{ IDelaysMgr::FRAMEOFF_UP,		"BF" },
	{ IDelaysMgr::FRAMEOFF_DOWN,	"BF" },
	{ IDelaysMgr::T12,				"ns" },
	{ IDelaysMgr::CPRI_UP,			"ns" },
	{ IDelaysMgr::CPRI_DOWN,		"ns" },
	{ IDelaysMgr::CPRI_FRAME_RX,	"ns" },
	{ IDelaysMgr::CPRI_FRAME_TX,	"ns" },

} ;

// List of delays which have no antenna (or carrier)
const std::vector<IDelaysMgr::DelayAttr> DELAY_ATTR{
	IDelaysMgr::OFFSET_DELAY,
	IDelaysMgr::FRAMEDIFF,
	IDelaysMgr::THRUDELAY_UP,
	IDelaysMgr::THRUDELAY_DOWN,
	IDelaysMgr::CPRI_UP,
	IDelaysMgr::CPRI_DOWN,
	IDelaysMgr::CPRI_FRAME_RX,
	IDelaysMgr::CPRI_FRAME_TX,
} ;


// List of delays which have antenna (but no carrier)
const std::vector<IDelaysMgr::DelayAttr> TX_DELAY_ATTR{
	IDelaysMgr::EXTDELAY_DOWN,
};

const std::vector<IDelaysMgr::DelayAttr> RX_DELAY_ATTR{
	IDelaysMgr::EXTDELAY_UP,
};


// List of delays which have antenna and carrier
const std::vector<IDelaysMgr::DelayAttr> CARRIER_TX_DELAY_ATTR{
	IDelaysMgr::ANTDELAY_DOWN,
	IDelaysMgr::ADJDELAY_DOWN,
	IDelaysMgr::FRAMEOFF_DOWN,
	IDelaysMgr::T12,
} ;

const std::vector<IDelaysMgr::DelayAttr> CARRIER_RX_DELAY_ATTR{
	IDelaysMgr::ANTDELAY_UP,
	IDelaysMgr::ADJDELAY_UP,
	IDelaysMgr::FRAMEOFF_UP,
} ;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {

/**
 * Utility that displays the contents of a vector prefixing each output by "[idx]"
 * NOTE: Expects the vector to be 0-based
 * @param vec	The vector to show
 * @param units	Units of the value
 * @param os	Output stream
 */
template <typename T>
inline void showVectorUnits(const std::vector<T>& vec, const std::string& units, std::ostream& os = std::cout)
{
	for (unsigned idx = 0; idx < vec.size(); ++idx)
	{
		if (idx > 0)
			os << " " ;
		os << "[" << idx << "]:" << vec.at(idx) << " " << units ;
	}
}

}

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<DelaysMgr> DelaysMgr::getInstance()
{
	static std::shared_ptr<DelaysMgr> instance(std::make_shared<DelaysMgr>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string IDelaysMgr::attrString(IDelaysMgr::DelayAttr attr)
{
	auto entry(DELAY_NAMES.find(attr)) ;
	if (entry == DELAY_NAMES.end())
		return "UNKNOWN" ;

	return entry->second ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DelaysMgr::DelaysMgr() :
	Loggable("DelaysMgr", "DM"),

	mMutex(),
    mNumTx(0),
    mNumRx(0),
    mNumCarriers(0),
    mError(""),

    mNonPathAttr(),
    mPathAttr(),
    mCarrierAttr(),
    mTxAttr(),
    mRxAttr(),

    mAdjDelayLimitDelayDown(0),
    mAdjDelayLimitStepDown(0),
    mAdjDelayLimitDelayUp(0),
    mAdjDelayLimitStepUp(0),

	mDelays(),
	mPathDelays(),
	mCarrierDelays(),
	mMidbandDelays(),

	// Hardware callbacks
	mHwDelayCallbacks(),
	mHwPathCallbacks(),
	mHwCarrierCallbacks(),

	// Application callbacks
	mAppDelayCallbacks(),
	mAppPathCallbacks(),
	mAppCarrierCallbacks()

{
//	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "DelaysMgr") ;
}

//-------------------------------------------------------------------------------------------------------------
DelaysMgr::~DelaysMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string DelaysMgr::getError()
{
	std::string error("") ;
	using std::swap ;
	Mutex::Lock lock(mMutex) ;
	swap(error, mError) ;
	return error ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::reset()
{
	Mutex::Lock lock(mMutex) ;

    mNumTx = 0 ;
    mNumRx = 0 ;
    mNumCarriers = 0 ;
	mError.clear() ;

    mNonPathAttr.clear() ;
    mPathAttr.clear() ;
    mCarrierAttr.clear() ;
    mTxAttr.clear() ;
    mRxAttr.clear() ;

    mAdjDelayLimitDelayDown = 0 ;
    mAdjDelayLimitStepDown = 0 ;
    mAdjDelayLimitDelayUp = 0 ;
    mAdjDelayLimitStepUp = 0 ;

	mDelays.clear() ;
	mPathDelays.clear() ;
	mCarrierDelays.clear() ;
	mMidbandDelays.clear() ;

	// Hardware callbacks
	mHwDelayCallbacks.clear() ;
	mHwPathCallbacks.clear() ;
	mHwCarrierCallbacks.clear() ;

	// Application callbacks
	mAppDelayCallbacks.clear() ;
	mAppPathCallbacks.clear() ;
	mAppCarrierCallbacks.clear() ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::initialise(unsigned numTx, unsigned numRx, unsigned numCarriers)
{
	Mutex::Lock lock(mMutex) ;

	mError.clear() ;
	mNumTx = numTx ;
	mNumRx = numRx ;
	mNumCarriers = numCarriers ;

	// Set up the maps
	for (auto attr : DELAY_ATTR)
	{
		mDelays[attr] = 0 ;
		mHwDelayCallbacks[attr] = SetDelay() ;
		mAppDelayCallbacks[attr] = SetDelay() ;
		mNonPathAttr[attr] = true ;
	}

	for (auto attr : TX_DELAY_ATTR)
	{
    	std::vector<unsigned> delays(numTx, 0) ;
		mPathDelays[attr] = delays ;
		mHwPathCallbacks[attr] = SetAntDelay() ;
		mAppPathCallbacks[attr] = SetAntDelay() ;
		mPathAttr[attr] = true ;
		mTxAttr[attr] = true ;
	}
	for (auto attr : RX_DELAY_ATTR)
	{
    	std::vector<unsigned> delays(numRx, 0) ;
		mPathDelays[attr] = delays ;
		mHwPathCallbacks[attr] = SetAntDelay() ;
		mAppPathCallbacks[attr] = SetAntDelay() ;
		mPathAttr[attr] = true ;
		mRxAttr[attr] = true ;
	}

	for (auto attr : CARRIER_TX_DELAY_ATTR)
	{
		std::vector< std::vector<SetVal<unsigned>> > delays ;
        for (unsigned i=0; i < numCarriers; ++i)
        {
        	std::vector<SetVal<unsigned>> cdelays(numTx, SetVal<unsigned>() ) ;
        	delays.push_back(cdelays) ;
        }
		mCarrierDelays[attr] = delays ;
		mMidbandDelays[attr] = std::vector<unsigned>(numTx, 0) ;
		mHwCarrierCallbacks[attr] = SetCarrierDelay() ;
		mAppCarrierCallbacks[attr] = SetCarrierDelay() ;
		mCarrierAttr[attr] = true ;
		mTxAttr[attr] = true ;
	}
	for (auto attr : CARRIER_RX_DELAY_ATTR)
	{
		std::vector< std::vector<SetVal<unsigned>> > delays ;
        for (unsigned i=0; i < numCarriers; ++i)
        {
        	std::vector<SetVal<unsigned>> cdelays(numRx, SetVal<unsigned>() ) ;
        	delays.push_back(cdelays) ;
        }
		mCarrierDelays[attr] = delays ;
		mMidbandDelays[attr] = std::vector<unsigned>(numRx, 0) ;
		mHwCarrierCallbacks[attr] = SetCarrierDelay() ;
		mAppCarrierCallbacks[attr] = SetCarrierDelay() ;
		mCarrierAttr[attr] = true ;
		mRxAttr[attr] = true ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void DelaysMgr::show(std::ostream& os) const
{
	if (!mError.empty())
		os << "ERROR: " << mError << std::endl ;

	const unsigned NAME_WIDTH{20} ;
	os << "Delays" << std::endl ;
	for (auto entry : mNonPathAttr)
	{
		IDelaysMgr::DelayAttr attr(entry.first) ;
		os << " * " << padLeft(IDelaysMgr::attrString(attr), NAME_WIDTH, '.') << ": " <<
				mDelays.at(attr) <<
				" " << DELAY_UNITS.at(attr) <<
				std::endl ;
	}
	for (auto entry : mPathAttr)
	{
		IDelaysMgr::DelayAttr attr(entry.first) ;
		os << " * " << padLeft(IDelaysMgr::attrString(attr), NAME_WIDTH, '.') << ": "  ;
		showVectorUnits(mPathDelays.at(attr), DELAY_UNITS.at(attr), os) ;
		os << std::endl ;
	}

	os << " * Midband " << std::endl  ;
	for (auto entry : mCarrierAttr)
	{
		IDelaysMgr::DelayAttr attr(entry.first) ;
		os << " * * " << padLeft(IDelaysMgr::attrString(attr), NAME_WIDTH, '.') << ": "  ;
		showVectorUnits(mMidbandDelays.at(attr), DELAY_UNITS.at(attr), os) ;
		os << std::endl ;
	}
	for (unsigned carrier=0; carrier < mNumCarriers; ++carrier)
	{
		os << " * Carrier " << carrier << std::endl  ;
		for (auto entry : mCarrierAttr)
		{
			IDelaysMgr::DelayAttr attr(entry.first) ;
			os << " * * " << padLeft(IDelaysMgr::attrString(attr), NAME_WIDTH, '.') << ": "  ;
			showVectorUnits(mCarrierDelays.at(attr).at(carrier), DELAY_UNITS.at(attr), os) ;
			os << std::endl ;
		}
	}
	os << std::endl ;
}


//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::hwSetDelay(IDelaysMgr::DelayAttr attr, unsigned delay)
{
	logDebugNormal("Delays: HW Set %s = %u", IDelaysMgr::attrString(attr).c_str(), delay) ;

	if (!checkDelay(attr))
		return false ;

	// set delay
	{
		Mutex::Lock lock(mMutex) ;
		mDelays[attr] = delay ;
	}

	// callback
	auto callback(mAppDelayCallbacks.find(attr)) ;
	if (callback == mAppDelayCallbacks.end())
		return true ;

	if (callback->second)
		(callback->second)(delay) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::hwSetPathDelay(IDelaysMgr::DelayAttr attr, unsigned antenna, unsigned delay)
{
	logDebugNormal("Delays: HW Set Ant%u %s = %u", antenna, IDelaysMgr::attrString(attr).c_str(), delay) ;

	if (!checkPathDelay(attr, antenna))
		return false ;

	// set delay
	{
		Mutex::Lock lock(mMutex) ;
		mPathDelays[attr][antenna] = delay ;
	}

	// callback
	auto callback(mAppPathCallbacks.find(attr)) ;
	if (callback == mAppPathCallbacks.end())
		return true ;

	if (callback->second)
		(callback->second)(antenna, delay) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::hwSetCarrierDelay(IDelaysMgr::DelayAttr attr,
		unsigned carrierIndex, unsigned antenna, unsigned delay)
{
	logDebugNormal("Delays: HW Set Carrier%u Ant%u %s = %u", carrierIndex, antenna, IDelaysMgr::attrString(attr).c_str(), delay) ;

	if (!checkCarrierDelay(attr, carrierIndex, antenna))
		return false ;

	// set delay
	{
		Mutex::Lock lock(mMutex) ;
		mCarrierDelays[attr][carrierIndex][antenna].set(delay) ;
	}

	// callback
	auto callback(mAppCarrierCallbacks.find(attr)) ;
	if (callback == mAppCarrierCallbacks.end())
		return true ;

	if (callback->second)
		(callback->second)(carrierIndex, antenna, delay) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::hwSetMidbandDelay(IDelaysMgr::DelayAttr attr, unsigned antenna, unsigned delay)
{
	logDebugNormal("Delays: HW Set MIDBAND Ant%u %s = %u", antenna, IDelaysMgr::attrString(attr).c_str(), delay) ;

	// This is a carrier delay - just nail the index to 0 for midband
	if (!checkCarrierDelay(attr, 0, antenna))
		return false ;

	// set delay
	{
		Mutex::Lock lock(mMutex) ;
		mMidbandDelays[attr][antenna] = delay ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::hwRegisterDelayCallback(IDelaysMgr::DelayAttr attr,
		SetDelay callback)
{
	if (!isNonPathAttr(attr))
		return false ;

	mHwDelayCallbacks[attr] = callback ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::hwRegisterPathDelayCallback(IDelaysMgr::DelayAttr attr,
		SetAntDelay callback)
{
	if (!isPathAttr(attr))
		return false ;

	mHwPathCallbacks[attr] = callback ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::hwRegisterCarrierDelayCallback(IDelaysMgr::DelayAttr attr,
		SetCarrierDelay callback)
{
	if (!isCarrierAttr(attr))
		return false ;

	mHwCarrierCallbacks[attr] = callback ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::hwDeregisterCallback(IDelaysMgr::DelayAttr attr)
{
	if (isNonPathAttr(attr))
	{
		mHwDelayCallbacks[attr] = SetDelay() ;
		return true ;
	}

	if (isPathAttr(attr))
	{
		mHwPathCallbacks[attr] = SetAntDelay() ;
		return true ;
	}

	if (isCarrierAttr(attr))
	{
		mHwCarrierCallbacks[attr] = SetCarrierDelay() ;
		return true ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::hwSetFrameDiff(unsigned frames)
{
	return hwSetDelay(IDelaysMgr::FRAMEDIFF, frames) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::hwSetAdjDelayLimit(unsigned delayDown, unsigned stepDown, unsigned delayUp, unsigned stepUp)
{
    mAdjDelayLimitDelayDown = delayDown ;
    mAdjDelayLimitStepDown = stepDown ;
    mAdjDelayLimitDelayUp = delayUp ;
    mAdjDelayLimitStepUp = stepUp ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::appSetDelay(IDelaysMgr::DelayAttr attr, unsigned delay)
{
	logDebugNormal("Delays: APP Set %s = %u", IDelaysMgr::attrString(attr).c_str(), delay) ;

	if (!checkDelay(attr))
		return false ;

	// set delay
	{
		Mutex::Lock lock(mMutex) ;
		mDelays[attr] = delay ;
	}

	// callback
	auto callback(mHwDelayCallbacks.find(attr)) ;
	if (callback == mHwDelayCallbacks.end())
		return true ;

	if (callback->second)
		(callback->second)(delay) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::appSetPathDelay(IDelaysMgr::DelayAttr attr, unsigned antenna, unsigned delay)
{
	logDebugNormal("Delays: APP Set Ant%u %s = %u",  antenna, IDelaysMgr::attrString(attr).c_str(), delay) ;

	if (!checkPathDelay(attr, antenna))
		return false ;

	// set delay
	{
		Mutex::Lock lock(mMutex) ;
		mPathDelays[attr][antenna] = delay ;
	}

	// callback
	auto callback(mHwPathCallbacks.find(attr)) ;
	if (callback == mHwPathCallbacks.end())
		return true ;

	if (callback->second)
		(callback->second)(antenna, delay) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::appSetCarrierDelay(IDelaysMgr::DelayAttr attr,
		unsigned carrierIndex, unsigned antenna, unsigned delay)
{
	logDebugNormal("Delays: APP Set Carrier%u Ant%u %s = %u", carrierIndex, antenna, IDelaysMgr::attrString(attr).c_str(), delay) ;

	if (!checkCarrierDelay(attr, carrierIndex, antenna))
		return false ;

	// set delay
	{
		Mutex::Lock lock(mMutex) ;
		mCarrierDelays[attr][carrierIndex][antenna].set(delay) ;
	}

	// callback
	auto callback(mHwCarrierCallbacks.find(attr)) ;
	if (callback == mHwCarrierCallbacks.end())
		return true ;

	if (callback->second)
		(callback->second)(carrierIndex, antenna, delay) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::appRegisterDelayCallback(IDelaysMgr::DelayAttr attr,
		SetDelay callback)
{
	if (!isNonPathAttr(attr))
		return false ;

	mAppDelayCallbacks[attr] = callback ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::appRegisterPathDelayCallback(IDelaysMgr::DelayAttr attr,
		SetAntDelay callback)
{
	if (!isPathAttr(attr))
		return false ;

	mAppPathCallbacks[attr] = callback ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::appRegisterCarrierDelayCallback(IDelaysMgr::DelayAttr attr,
		SetCarrierDelay callback)
{
	if (!isCarrierAttr(attr))
		return false ;

	mAppCarrierCallbacks[attr] = callback ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::appDeregisterCallback(IDelaysMgr::DelayAttr attr)
{
	if (isNonPathAttr(attr))
	{
		mAppDelayCallbacks[attr] = SetDelay() ;
		return true ;
	}

	if (isPathAttr(attr))
	{
		mAppPathCallbacks[attr] = SetAntDelay() ;
		return true ;
	}

	if (isCarrierAttr(attr))
	{
		mAppCarrierCallbacks[attr] = SetCarrierDelay() ;
		return true ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned DelaysMgr::getFrameDiff() const
{
	return getDelay(IDelaysMgr::FRAMEDIFF) ;
}

//-------------------------------------------------------------------------------------------------------------
void DelaysMgr::getAdjDelayLimit(unsigned & delayDown,
		unsigned & stepDown, unsigned & delayUp, unsigned & stepUp) const
{
	delayDown = mAdjDelayLimitDelayDown ;
	stepDown = mAdjDelayLimitStepDown ;
	delayUp = mAdjDelayLimitDelayUp ;
	stepUp = mAdjDelayLimitStepUp ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned DelaysMgr::getDelay(IDelaysMgr::DelayAttr attr) const
{
	if (!checkDelay(attr))
		return false ;

	// get delay
	Mutex::Lock lock(mMutex) ;
	unsigned delay = mDelays.at(attr) ;
	logDebugNormal("Delays: Get %s = %u", IDelaysMgr::attrString(attr).c_str(), delay) ;
	return delay ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned DelaysMgr::getPathDelay(IDelaysMgr::DelayAttr attr, unsigned antenna) const
{
	if (!checkPathDelay(attr, antenna))
		return false ;

	// get delay
	Mutex::Lock lock(mMutex) ;
	unsigned delay = mPathDelays.at(attr).at(antenna) ;
	logDebugNormal("Delays: Get Ant%u %s = %u", antenna, IDelaysMgr::attrString(attr).c_str(), delay) ;
	return delay ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned DelaysMgr::getCarrierDelay(IDelaysMgr::DelayAttr attr,
		unsigned carrierIndex, unsigned antenna) const
{
	if (!checkCarrierDelay(attr, carrierIndex, antenna))
		return false ;

	// get delay
	Mutex::Lock lock(mMutex) ;
	const SetVal<unsigned>& setval(mCarrierDelays.at(attr).at(carrierIndex).at(antenna)) ;
	unsigned carrierDelay = setval.get() ;
	unsigned delay = carrierDelay ;

	unsigned midbandDelay(mMidbandDelays.at(attr).at(antenna)) ;
	if (!setval.isSet())
		delay = midbandDelay ;

	logDebugNormal("Delays: Get Carrier%u Ant%u %s = %u [carrier=%u %s, midband=%u]",
		carrierIndex, antenna, IDelaysMgr::attrString(attr).c_str(), delay,
		carrierDelay, (setval.isSet() ? "SET" : "UNSET"),
		midbandDelay
	) ;
	return delay ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::checkAttr(IDelaysMgr::DelayAttr attr) const
{
	if (!isNonPathAttr(attr))
	{
		setError(IDelaysMgr::attrString(attr) + " is not a simple delay") ;
		return false ;
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::checkPathAttr(IDelaysMgr::DelayAttr attr, unsigned antenna) const
{
	if (!isPathAttr(attr))
	{
		setError(IDelaysMgr::attrString(attr) + " is not an antenna delay") ;
		return false ;
	}

	if (isTxAttr(attr))
	{
		if (antenna >= mNumTx)
		{
			setError("Invalid TX index") ;
			return false ;
		}
	}

	if (isRxAttr(attr))
	{
		if (antenna >= mNumRx)
		{
			setError("Invalid RX index") ;
			return false ;
		}
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::checkCarrierAttr(IDelaysMgr::DelayAttr attr, unsigned carrierIndex, unsigned antenna) const
{
	if (!isCarrierAttr(attr))
	{
		setError(IDelaysMgr::attrString(attr) + " is not a carrier delay") ;
		return false ;
	}

	if (carrierIndex >= mNumCarriers)
	{
		setError("Invalid carrier index") ;
		return false ;
	}

	if (isTxAttr(attr))
	{
		if (antenna >= mNumTx)
		{
			setError("Invalid TX index") ;
			return false ;
		}
	}

	if (isRxAttr(attr))
	{
		if (antenna >= mNumRx)
		{
			setError("Invalid RX index") ;
			return false ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::checkDelay(IDelaysMgr::DelayAttr attr) const
{
	if (!checkAttr(attr))
		return false ;

	auto entry(mDelays.find(attr)) ;
	if (entry == mDelays.end())
	{
		setError("Invalid delay attribute") ;
		return false ;
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::checkPathDelay(IDelaysMgr::DelayAttr attr, unsigned antenna) const
{
	if (!checkPathAttr(attr, antenna))
		return false ;

	auto entry(mPathDelays.find(attr)) ;
	if (entry == mPathDelays.end())
	{
		setError("Invalid delay attribute") ;
		return false ;
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::checkCarrierDelay(IDelaysMgr::DelayAttr attr, unsigned carrierIndex, unsigned antenna) const
{
	if (!checkCarrierAttr(attr, carrierIndex, antenna))
		return false ;

	auto entry(mCarrierDelays.find(attr)) ;
	if (entry == mCarrierDelays.end())
	{
		setError("Invalid delay attribute") ;
		return false ;
	}

	return true ;
}



//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::isNonPathAttr(IDelaysMgr::DelayAttr attr) const
{
	auto entry(mNonPathAttr.find(attr)) ;
	if (entry == mNonPathAttr.end())
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::isPathAttr(IDelaysMgr::DelayAttr attr) const
{
	auto entry(mPathAttr.find(attr)) ;
	if (entry == mPathAttr.end())
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::isCarrierAttr(IDelaysMgr::DelayAttr attr) const
{
	auto entry(mCarrierAttr.find(attr)) ;
	if (entry == mCarrierAttr.end())
		return false ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::isTxAttr(IDelaysMgr::DelayAttr attr) const
{
	auto entry(mTxAttr.find(attr)) ;
	if (entry == mTxAttr.end())
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DelaysMgr::isRxAttr(IDelaysMgr::DelayAttr attr) const
{
	auto entry(mRxAttr.find(attr)) ;
	if (entry == mRxAttr.end())
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void DelaysMgr::setError(const std::string& error) const
{
	logDebugNormal("Delays: ERROR %s", error.c_str()) ;

	Mutex::Lock lock(mMutex) ;
	if (!mError.empty())
		mError += "\n" ;
	mError += error ;
}
