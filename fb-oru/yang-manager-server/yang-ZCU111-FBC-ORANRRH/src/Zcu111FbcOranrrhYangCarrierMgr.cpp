/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhYangCarrierMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <set>

#include "config.h"

#include "ICarrierServer.h"
#include "ICarrier.h"
#include "ICarrierModel.h"
#include "IFrequencyConst.h"
#include "ICarrierHardware.h"

#include "CarrierHardware/ChainModel.h"
#include "CarrierHardware/FibreModel.h"
#include "CarrierHardware/FlexiChainInfo.h"
#include "Zcu111CarrierHardwareData.h"

#include "Zcu111FbcOranrrhYangCarrierMgr.h"

using namespace Mplane;

//=============================================================================================================
// LINKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
struct Zcu111FbcOranrrhYangCarrierMgr::Link {
	Link() : mName(), mEndpointName(), mCarrierName() {}
	Link(const std::string& name, const std::string& endpoint, const std::string& carrierName) :
		mName(name),
		mEndpointName(endpoint),
		mCarrierName(carrierName)
	{}
	~Link() {}

	void merge(std::shared_ptr<Link> rhs)
	{
		if (!rhs->mEndpointName.empty())
			mEndpointName = rhs->mEndpointName ;
		if (!rhs->mCarrierName.empty())
			mCarrierName = rhs->mCarrierName ;
	}

	bool empty() const
	{
		if (!mEndpointName.empty())
			return false ;
		if (!mCarrierName.empty())
			return false ;
		return true ;
	}

	void show()
	{
		std::cerr << "LINK[" << mName << "] endpoint=" << mEndpointName << " carrier=" << mCarrierName << std::endl  ;
	}

	std::string mName ;
	std::string mEndpointName ;
	std::string mCarrierName ;
};

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {

	// Coding from page 71 ORAN-WG4.CUS.0-v2.00
	const std::map<ICarrier::FFTsizeType, unsigned> FFT_CODE {
		{ ICarrier::FFT_NONE, 0x00 },
		{ ICarrier::FFT_128,  0x07 },
		{ ICarrier::FFT_256,  0x08 },
		{ ICarrier::FFT_512,  0x09 },
		{ ICarrier::FFT_1024, 0x0A },
		{ ICarrier::FFT_2048, 0x0B },
		{ ICarrier::FFT_4096, 0x0C },
		{ ICarrier::FFT_1536, 0x0D },
	};

	unsigned fftCode(ICarrier::FFTsizeType fft)
	{
		return FFT_CODE.at(fft) ;
	}

	// Channel bandwidth mappings
	const std::map<ICarrierHardwareTypes::ChbwType, uint64_t> CHBW_MAP{
		{ ICarrierHardwareTypes::CHBW_3500, 	  3500000 },
		{ ICarrierHardwareTypes::CHBW_5000, 	  5000000 },
		{ ICarrierHardwareTypes::CHBW_7000, 	  7000000 },
		{ ICarrierHardwareTypes::CHBW_10000, 	 10000000 },
		{ ICarrierHardwareTypes::CHBW_1400, 	  1400000 },
		{ ICarrierHardwareTypes::CHBW_3000, 	  3000000 },
		{ ICarrierHardwareTypes::CHBW_15000, 	 15000000 },
		{ ICarrierHardwareTypes::CHBW_20000, 	 20000000 },

		{ ICarrierHardwareTypes::CHBW_153600, 	153600000 },

		{ ICarrierHardwareTypes::CHBW_122880, 	122880000 },

		{ ICarrierHardwareTypes::CHBW_25000, 	 25000000 },
		{ ICarrierHardwareTypes::CHBW_30000, 	 30000000 },
		{ ICarrierHardwareTypes::CHBW_40000, 	 40000000 },
		{ ICarrierHardwareTypes::CHBW_50000, 	 50000000 },
		{ ICarrierHardwareTypes::CHBW_60000, 	 60000000 },
		{ ICarrierHardwareTypes::CHBW_70000, 	 70000000 },
		{ ICarrierHardwareTypes::CHBW_80000, 	 80000000 },
		{ ICarrierHardwareTypes::CHBW_90000, 	 90000000 },
		{ ICarrierHardwareTypes::CHBW_100000, 	100000000 },

		{ ICarrierHardwareTypes::CHBW_UNSET, 	0 },
	};

	uint64_t chbwMap(ICarrierHardwareTypes::ChbwType chbw)
	{
		if (CHBW_MAP.find(chbw) == CHBW_MAP.end())
			return 0 ;

		return CHBW_MAP.at(chbw) ;
	}

	unsigned calcMaxPrb(unsigned chainType)
	{
		unsigned maxPrb(0) ;

		std::vector<ICarrierHardwareTypes::ChbwType> supported(FlexiChainInfo::supportedChbw(chainType)) ;
		for (auto chbw : supported)
		{
			unsigned maxNumSubcarriers = FlexiChainInfo::calcNumSubcarriers(chbw) ;
			if (FlexiChainInfo::isChain5G(chainType))
			{
				for(unsigned scs = static_cast<unsigned>(ICarrier::SCS_1kHz25); scs <= static_cast<unsigned>(ICarrier::SCS_240kHz); ++scs)
				{
					unsigned numSubcarriers = FlexiChainInfo::calcNumSubcarriers(chbw, true, static_cast<ICarrier::ScsType>(scs)) ;
					if (maxNumSubcarriers < numSubcarriers)
						maxNumSubcarriers = numSubcarriers ;
				}
			}

			unsigned prb(maxNumSubcarriers / 12) ;
			if (maxPrb < prb)
				maxPrb = prb ;
		}
		return maxPrb ;
	}

}


//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangCarrierMgr> IYangCarrierMgr::singleton()
{
	static std::shared_ptr<IYangCarrierMgr> instance( std::make_shared<Zcu111FbcOranrrhYangCarrierMgr>() ) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhYangCarrierMgr::Zcu111FbcOranrrhYangCarrierMgr() :
	YangCarrierMgr(),
	mInitialised(false),
	mNumTx(0),
	mNumRx(0),
	mNumStreamsPerChain(),
	mTotalStreams(),
	mMinChbw(ICarrierHardwareTypes::CHBW_UNSET),
	mMaxChbw(ICarrierHardwareTypes::CHBW_UNSET),
	mUlStreamMap(),
	mDlStreamMap(),
	mRxLinks(),
	mTxLinks(),
	mRxCarriers(),
	mTxCarriers()
{
	initData() ;

	// DEBUG
	std::cerr << "UL map" << std::endl ;
	for (auto entry : mUlStreamMap)
	{
		std::cerr << entry.first << " = [" << entry.second.first << " " << entry.second.second << "]" << std::endl ;
	}
	std::cerr << "DL map" << std::endl ;
	for (auto entry : mDlStreamMap)
	{
		std::cerr << entry.first << " = [" << entry.second.first << " " << entry.second.second << "]" << std::endl ;
	}

}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhYangCarrierMgr::~Zcu111FbcOranrrhYangCarrierMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhYangCarrierMgr::initialise()
{
	if (mInitialised)
		return true ;

	std::cerr << "Zcu111FbcOranrrhYangCarrierMgr::initialise()" << std::endl ;

	std::shared_ptr<ICarrierModel> model(ICarrierModel::getInstance()) ;
	std::shared_ptr<ICarrierScheduler> scheduler(std::dynamic_pointer_cast<ICarrierScheduler>(model)) ;

	auto ulScheduler = [this](const unsigned carrierIndex, const unsigned antenna,
			const ICarrierHardwareTypes::AirstdType airstd, const ICarrierHardwareTypes::ChbwType chbw, const unsigned fibre,
			unsigned& fibreIndex, unsigned& chain, unsigned& chainIndex)->ICarrierHardwareTypes::ScheduleStatus
	{
		return this->scheduleUl(carrierIndex, antenna, airstd, chbw, fibre,
				fibreIndex, chain, chainIndex) ;
	} ;
	auto dlScheduler = [this](const unsigned carrierIndex, const unsigned antenna,
			const ICarrierHardwareTypes::AirstdType airstd, const ICarrierHardwareTypes::ChbwType chbw, const unsigned fibre,
			unsigned& fibreIndex, unsigned& chain, unsigned& chainIndex)->ICarrierHardwareTypes::ScheduleStatus
	{
		return this->scheduleDl(carrierIndex, antenna, airstd, chbw, fibre,
				fibreIndex, chain, chainIndex) ;
	} ;

	if (!scheduler->setStaticScheduling(ulScheduler, dlScheduler))
		return false ;

//	initData() ;
	if (!createEndpointTypes())
		return false ;
	if (!createEndpointCapacitySharingGroups())
		return false ;
	if (!createTxArrays())
		return false ;
	if (!createRxArrays())
		return false ;
	if (!createStaticLowLevelTxEndpoints())
		return false ;
	if (!createStaticLowLevelRxEndpoints())
		return false ;

//// DEBUG
//std::cerr << "UL map" << std::endl ;
//for (auto entry : mUlStreamMap)
//{
//	std::cerr << entry.first << " = [" << entry.second.first << " " << entry.second.second << "]" << std::endl ;
//}
//std::cerr << "DL map" << std::endl ;
//for (auto entry : mDlStreamMap)
//{
//	std::cerr << entry.first << " = [" << entry.second.first << " " << entry.second.second << "]" << std::endl ;
//}

	mInitialised = true ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::pair<unsigned, unsigned> Zcu111FbcOranrrhYangCarrierMgr::lookupUlEndpoint(const std::string &endpointName)
{
	if (mUlStreamMap.find(endpointName) == mUlStreamMap.end())
		return std::make_pair(0u,0u) ;

	return mUlStreamMap[endpointName] ;
}

//-------------------------------------------------------------------------------------------------------------
std::pair<unsigned, unsigned> Zcu111FbcOranrrhYangCarrierMgr::lookupDlEndpoint(const std::string &endpointName)
{
	if (mDlStreamMap.find(endpointName) == mDlStreamMap.end())
		return std::make_pair(0u,0u) ;

	return mDlStreamMap[endpointName] ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Zcu111FbcOranrrhYangCarrierMgr::numTx() const
{
	return mNumTx ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Zcu111FbcOranrrhYangCarrierMgr::numRx() const
{
	return mNumRx ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhYangCarrierMgr::updateRxLink(
		const std::string &name, const std::string &endpoint,
		const std::string &carrierName)
{
	std::shared_ptr link(std::make_shared<Link>(name, endpoint, carrierName)) ;

	auto entry(mRxLinks.find(name)) ;
	if (link->empty())
	{
		if (entry == mRxLinks.end())
			return ;

		mRxLinks.erase(entry) ;
		return ;
	}

	if (entry == mRxLinks.end())
		mRxLinks[name] = link ;
	else
		entry->second->merge(link) ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhYangCarrierMgr::updateTxLink(
		const std::string &name, const std::string &endpoint,
		const std::string &carrierName)
{
	std::shared_ptr link(std::make_shared<Link>(name, endpoint, carrierName)) ;

	auto entry(mTxLinks.find(name)) ;
	if (link->empty())
	{
		if (entry == mTxLinks.end())
			return ;

		mTxLinks.erase(entry) ;
		return ;
	}

	if (entry == mTxLinks.end())
		mTxLinks[name] = link ;
	else
		entry->second->merge(link) ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhYangCarrierMgr::updateRxCarrier(const std::string &carrierName, ILeafContainer::LeafFunc stateFunc,
		ILeafContainer::LeafFunc activeFunc)
{
	// skip if already present
	if (mRxCarriers.find(carrierName) != mRxCarriers.end())
		return ;

	// add new carrier
	std::shared_ptr<ILeafContainer> parent(leafContainer()) ;
	std::shared_ptr<ILeafContainer> arrayCarriers(parent->addContainer("rx-array-carriers")) ;
	arrayCarriers->addLeaf("name", carrierName) ;
	arrayCarriers->addLeaf("duplex-scheme", BUILD_DUPLEX) ;
	arrayCarriers->addLeaf("state", stateFunc) ;
	arrayCarriers->addLeaf("active", activeFunc) ;

	// Map from carrier name to endpoint
	std::string endpoint ;
	for (auto entry : mRxLinks)
	{
		if (entry.second->mCarrierName != carrierName)
			continue ;

		endpoint = entry.second->mEndpointName ;
		break ;
	}

	if (endpoint.empty())
		return ;

	// lookup chain features
	std::pair<unsigned, unsigned> cciq(lookupUlEndpoint(endpoint)) ;
	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );
	const ChainCarrierInfo& chainInfo(hardwareData->getUlChainInfo(cciq.first)) ;

//std::cerr << "RX chain " << cciq.first << " carrier " << carrierName << " endpoint " << endpoint << " type " << chainInfo.chain_type << " " << (FlexiChainInfo::isChain5G(chainInfo.chain_type) ? "5G" : "LTE") << std::endl ;
	if (FlexiChainInfo::isChain5G(chainInfo.chain_type))
	{
		arrayCarriers->addLeaf("type", "NR") ;
	}
	else
	{
		arrayCarriers->addLeaf("type", "LTE") ;
	}

}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhYangCarrierMgr::updateTxCarrier(const std::string &carrierName, ILeafContainer::LeafFunc stateFunc,
		ILeafContainer::LeafFunc activeFunc)
{
	// skip if already present
	if (mTxCarriers.find(carrierName) != mTxCarriers.end())
		return ;

	// add new carrier
	std::shared_ptr<ILeafContainer> parent(leafContainer()) ;
	std::shared_ptr<ILeafContainer> arrayCarriers(parent->addContainer("tx-array-carriers")) ;
	arrayCarriers->addLeaf("name", carrierName) ;
	arrayCarriers->addLeaf("duplex-scheme", BUILD_DUPLEX) ;
	arrayCarriers->addLeaf("state", stateFunc) ;
	arrayCarriers->addLeaf("active", activeFunc) ;

	// Map from carrier name to endpoint
	std::string endpoint ;
	for (auto entry : mTxLinks)
	{
		if (entry.second->mCarrierName != carrierName)
			continue ;

		endpoint = entry.second->mEndpointName ;
		break ;
	}

	if (endpoint.empty())
		return ;

	// lookup chain features
	std::pair<unsigned, unsigned> cciq(lookupDlEndpoint(endpoint)) ;
	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );
	const ChainCarrierInfo& chainInfo(hardwareData->getDlChainInfo(cciq.first)) ;

//std::cerr << "TX chain " << cciq.first << " carrier " << carrierName << " endpoint " << endpoint << " type " << chainInfo.chain_type << " " << (FlexiChainInfo::isChain5G(chainInfo.chain_type) ? "5G" : "LTE") << std::endl ;
	if (FlexiChainInfo::isChain5G(chainInfo.chain_type))
	{
		arrayCarriers->addLeaf("type", "NR") ;
	}
	else
	{
		arrayCarriers->addLeaf("type", "LTE") ;
	}

}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ICarrierHardwareTypes::ScheduleStatus Zcu111FbcOranrrhYangCarrierMgr::scheduleUl(
		const unsigned carrierIndex, const unsigned antenna,
		const ICarrierHardwareTypes::AirstdType airstd,
		const ICarrierHardwareTypes::ChbwType chbw, const unsigned fibre,
		unsigned &fibreIndex, unsigned &chain, unsigned &chainIndex)
{
	std::string name(rxEndpointName(antenna, carrierIndex)) ;
	if (mDlStreamMap.find(name) == mUlStreamMap.end())
		return ICarrierHardwareTypes::SCHEDULE_FAIL ;

	auto entry(mUlStreamMap[name]) ;
	chain = entry.first ;
	chainIndex = entry.second ;
	fibreIndex = chainIndex ;

//std::cerr << "Zcu111FbcOranrrhYangCarrierMgr::scheduleUl(ci=" << carrierIndex << ", ant=" << antenna << ") chain=" <<
//		chain << " iq=" << chainIndex << std::endl ;

	return ICarrierHardwareTypes::SCHEDULE_OK ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrierHardwareTypes::ScheduleStatus Zcu111FbcOranrrhYangCarrierMgr::scheduleDl(
		const unsigned carrierIndex, const unsigned antenna,
		const ICarrierHardwareTypes::AirstdType airstd,
		const ICarrierHardwareTypes::ChbwType chbw, const unsigned fibre,
		unsigned &fibreIndex, unsigned &chain, unsigned &chainIndex)
{
	std::string name(txEndpointName(antenna, carrierIndex)) ;
	if (mDlStreamMap.find(name) == mDlStreamMap.end())
		return ICarrierHardwareTypes::SCHEDULE_FAIL ;

	auto entry(mDlStreamMap[name]) ;
	chain = entry.first ;
	chainIndex = entry.second ;
	fibreIndex = chainIndex ;

//std::cerr << "Zcu111FbcOranrrhYangCarrierMgr::scheduleDl(ci=" << carrierIndex << ", ant=" << antenna << ") chain=" <<
//		chain << " iq=" << chainIndex << std::endl ;

	return ICarrierHardwareTypes::SCHEDULE_OK ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Zcu111FbcOranrrhYangCarrierMgr::frameStructure(ICarrier::FFTsizeType fft, ICarrier::ScsType scs)
{
	unsigned value = FlexiChainInfo::scsCoding(scs) & 0xf ;
	value += (fftCode(fft) << 4) & 0xf0 ;
	return value ;
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhYangCarrierMgr::initData()
{
	mNumStreamsPerChain.clear() ;
	mTotalStreams.clear() ;
	mMinChbw = ICarrierHardwareTypes::CHBW_UNSET ;
	mMaxChbw = ICarrierHardwareTypes::CHBW_UNSET ;


	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );

	// Get chain info
	unsigned total(0) ;
	for (unsigned chain=0; chain < hardwareData->getNumUlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getUlChainInfo(chain)) ;
		mNumStreamsPerChain.push_back( chainInfo.num_iq_streams ) ;
		mTotalStreams.push_back( total ) ;

		total += chainInfo.num_iq_streams ;

		std::vector<ICarrierHardwareTypes::ChbwType> supported(FlexiChainInfo::supportedChbw(chainInfo.chain_type)) ;
		for (auto chbw : supported)
		{
			if (mMinChbw == ICarrierHardwareTypes::CHBW_UNSET)
			{
				mMinChbw = chbw ;
			}
			else
			{
				if (chbwMap(mMinChbw) > chbwMap(chbw))
					mMinChbw = chbw ;
			}

			if (mMaxChbw == ICarrierHardwareTypes::CHBW_UNSET)
			{
				mMaxChbw = chbw ;
			}
			else
			{
				if (chbwMap(mMaxChbw) < chbwMap(chbw))
					mMaxChbw = chbw ;
			}
		}
	}

	// add a sentinel value that is the total number of streams
	mTotalStreams.push_back( total ) ;


	initUlMap() ;
	initDlMap() ;
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhYangCarrierMgr::initUlMap()
{
	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );

	mUlStreamMap.clear() ;

	/**
	 * Name is created using the format: txXccY
	 * Where X = antenna number, Y = chain index
	 * In this case, chain index == component carrier number
	 */

	unsigned totalIq(mTotalStreams[hardwareData->getNumUlchains()]) ;
	for (unsigned chain=0; chain < hardwareData->getNumUlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getUlChainInfo(chain)) ;

		// Get the antenna information for each stream
		unsigned chainIq( chainInfo.iq_stream_start ) ;
		for (auto ant : chainInfo.antenna)
		{
			std::string name(rxEndpointName(ant, chain)) ;
			mUlStreamMap[name] = std::make_pair(chain, chainIq) ;

			// PRACH
			name = prachEndpointName(ant, chain) ;
			mUlStreamMap[name] = std::make_pair(chain, totalIq + chainIq) ;

			++chainIq ;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhYangCarrierMgr::initDlMap()
{
	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );

	mDlStreamMap.clear() ;

	/**
	 * Name is created using the format: txXccY
	 * Where X = antenna number, Y = chain index
	 * In this case, chain index == component carrier number
	 */

	for (unsigned chain=0; chain < hardwareData->getNumDlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getDlChainInfo(chain)) ;

		// Get the antenna information for each stream
		unsigned chainIq( chainInfo.iq_stream_start ) ;
		for (auto ant : chainInfo.antenna)
		{
			std::string name(txEndpointName(ant, chain)) ;
			mDlStreamMap[name] = std::make_pair(chain, chainIq) ;

			++chainIq ;
		}
	}

}



//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhYangCarrierMgr::createEndpointTypes()
{
	std::shared_ptr<ILeafContainer> parent(leafContainer()) ;

	/**
	 * Map each chain into 2 endpoint types: 1 for normal channels, 1 for PRACH
	 * Each type id is: NORMAL = chain id * 2 ; PRACH = chain id * 2 + 1
	 */

	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );

	// Get chain info
	for (unsigned chain=0; chain < hardwareData->getNumUlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getUlChainInfo(chain)) ;

		// Create endpoint type

		//	     +--ro endpoint-types* [id]
		//	     |  +--ro id                                       uint16
		//	     |  +--ro supported-section-types* [section-type]
		//	     |  |  +--ro section-type                    uint8
		//	     |  |  +--ro supported-section-extensions*   uint8
		//	     |  +--ro supported-frame-structures*              uint8
		//	     |  +--ro managed-delay-support?                   enumeration
		//	     |  +--ro multiple-numerology-supported?           boolean <true>
		//	     |  +--ro max-numerology-change-duration?          uint16
		//	     |  +--ro max-control-sections-per-data-section?   uint8
		//	     |  +--ro max-sections-per-symbol?                 uint16
		//	     |  +--ro max-sections-per-slot?                   uint16
		//	     |  +--ro max-beams-per-symbol?                    uint16
		//	     |  +--ro max-beams-per-slot?                      uint16
		//	     |  +--ro max-prb-per-symbol?                      uint16
		//	     |  +--ro prb-capacity-allocation-granularity*     uint16
		//	     |  +--ro max-numerologies-per-symbol?             uint16

		unsigned maxPrb(calcMaxPrb(chainInfo.chain_type)) ;
		std::vector<ICarrierHardwareTypes::ChbwType> supported(FlexiChainInfo::supportedChbw(chainInfo.chain_type)) ;

		// normal channels
		auto endpointType = parent->addContainer("endpoint-types") ;
		endpointType->addLeafInt("id", (2*chain)) ;
		auto sectionTypes = endpointType->addContainer("supported-section-types") ;
		sectionTypes->addLeafInt("section-type", 1) ;
//		sectionTypes->addLeafInt("supported-section-extensions", 0) ;

//		std::cout << "endpoint-types: id=" << 2*chain << std::endl ;
//		std::cout << "  section-type=1" << std::endl ;

		// frame structs
		std::set<unsigned> frameStructSet ;
		for (auto chbw : supported)
		{
			// LTE
			ICarrier::FFTsizeType fft(FlexiChainInfo::calcFftsize(chbw)) ;
			unsigned frameStruct ;
			if (fft != ICarrier::FFT_NONE)
			{
				frameStruct = frameStructure(fft, ICarrier::SCS_15kHz) ;
				if (frameStructSet.find(frameStruct) == frameStructSet.end())
				{
					frameStructSet.insert(frameStruct) ;
//					std::cout << "  supported-frame-structures[]=0x" << std::hex << frameStruct << std::dec << std::endl ;
					endpointType->addLeafInt("supported-frame-structures", frameStruct) ;
				}
			}

			// 5G
			if (FlexiChainInfo::isChain5G(chainInfo.chain_type))
			{
				for(unsigned scs = static_cast<unsigned>(ICarrier::SCS_1kHz25); scs <= static_cast<unsigned>(ICarrier::SCS_240kHz); ++scs)
				{
					ICarrier::ScsType scsType(static_cast<ICarrier::ScsType>(scs)) ;
					fft = FlexiChainInfo::calcFftsize(chbw, true, scsType) ;
					if (fft == ICarrier::FFT_NONE)
						continue ;

					frameStruct = frameStructure(fft, scsType) ;
					if (frameStructSet.find(frameStruct) == frameStructSet.end())
					{
						frameStructSet.insert(frameStruct) ;
//						std::cout << "  supported-frame-structures[]=0x" << std::hex << frameStruct << std::dec << std::endl ;
						endpointType->addLeafInt("supported-frame-structures", frameStruct) ;
					}
				}
			}
		}

//		std::cout << "  managed-delay-support=MANAGED" << std::endl ;
//		std::cout << "  multiple-numerology-supported=false" << std::endl ;
//		std::cout << "  max-numerology-change-duration=0" << std::endl ;
//		std::cout << "  max-control-sections-per-data-section=1" << std::endl ;
//		std::cout << "  max-sections-per-symbol=64" << std::endl ;
//		std::cout << "  max-sections-per-slot=64" << std::endl ;
//		std::cout << "  max-beams-per-symbol=1" << std::endl ;
//		std::cout << "  max-beams-per-slot=1" << std::endl ;
//		std::cout << "  max-prb-per-symbol=" << maxPrb << std::endl ;
//		std::cout << "  prb-capacity-allocation-granularity=1" << std::endl ;
//		std::cout << "  max-numerologies-per-symbol=1" << std::endl ;

		endpointType->addLeaf("managed-delay-support", "MANAGED") ;
		endpointType->addLeaf("multiple-numerology-supported", "false") ;
		endpointType->addLeaf("max-numerology-change-duration", "0") ;
		endpointType->addLeaf("max-control-sections-per-data-section", "1") ;
		endpointType->addLeaf("max-sections-per-symbol", "64") ;
		endpointType->addLeaf("max-sections-per-slot", "64") ;
		endpointType->addLeaf("max-beams-per-symbol", "1") ;
		endpointType->addLeaf("max-beams-per-slot", "1") ;
		endpointType->addLeafInt("max-prb-per-symbol", maxPrb) ;
		endpointType->addLeaf("prb-capacity-allocation-granularity", "1") ;
		endpointType->addLeaf("max-numerologies-per-symbol", "1") ;


		// PRACH
		endpointType = parent->addContainer("endpoint-types") ;
		endpointType->addLeafInt("id", (2*chain + 1)) ;
		sectionTypes = endpointType->addContainer("supported-section-types") ;
		sectionTypes->addLeafInt("section-type", 3) ;
//		sectionTypes->addLeafInt("supported-section-extensions", 0) ;
//		std::cout << "Endpoint type (PRACH): id=" << 2*chain +1 << std::endl ;
//		std::cout << "  section-type=3" << std::endl ;

		// frame structs
//		std::cout << "    supported-frame-structures=0xAC" << std::endl ;
		endpointType->addLeafInt("supported-frame-structures", 0xAC) ;
#ifdef DUPLEX_TDD
//		std::cout << "    supported-frame-structures=0x8F" << std::endl ;
		endpointType->addLeafInt("supported-frame-structures", 0x8F) ;
#endif
//		std::cout << "  managed-delay-support=MANAGED" << std::endl ;
//		std::cout << "  multiple-numerology-supported=false" << std::endl ;
//		std::cout << "  max-numerology-change-duration=0" << std::endl ;
//		std::cout << "  max-control-sections-per-data-section=1" << std::endl ;
//		std::cout << "  max-sections-per-symbol=64" << std::endl ;
//		std::cout << "  max-sections-per-slot=64" << std::endl ;
//		std::cout << "  max-beams-per-symbol=1" << std::endl ;
//		std::cout << "  max-beams-per-slot=1" << std::endl ;
//		std::cout << "  max-prb-per-symbol=70" << std::endl ;
//		std::cout << "  prb-capacity-allocation-granularity=1" << std::endl ;
//		std::cout << "  max-numerologies-per-symbol=1" << std::endl ;

		endpointType->addLeaf("managed-delay-support", "MANAGED") ;
		endpointType->addLeaf("multiple-numerology-supported", "false") ;
		endpointType->addLeaf("max-numerology-change-duration", "0") ;
		endpointType->addLeaf("max-control-sections-per-data-section", "1") ;
		endpointType->addLeaf("max-sections-per-symbol", "64") ;
		endpointType->addLeaf("max-sections-per-slot", "64") ;
		endpointType->addLeaf("max-beams-per-symbol", "1") ;
		endpointType->addLeaf("max-beams-per-slot", "1") ;
		endpointType->addLeafInt("max-prb-per-symbol", 70) ;
		endpointType->addLeaf("prb-capacity-allocation-granularity", "1") ;
		endpointType->addLeaf("max-numerologies-per-symbol", "1") ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhYangCarrierMgr::createEndpointCapacitySharingGroups()
{
	std::shared_ptr<ILeafContainer> parent(leafContainer()) ;
	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );

	/**
	 * Create 1 entry per tx/rx static endpoint
	 */

	/*
	 * Indexing is done with TX first 0..N-1, then RX N..2N-1, then PRACH 2N..3N-1
	 *
	 */

	// TX
	for (unsigned chain=0; chain < hardwareData->getNumDlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getDlChainInfo(chain)) ;
		unsigned maxPrb(calcMaxPrb(chainInfo.chain_type)) ;

		// Get the antenna information for each stream
		unsigned chainIq( chainInfo.iq_stream_start ) ;
		for (auto ant : chainInfo.antenna)
		{
			(void)ant ;
			createEndpointCapacitySharingGroup(parent, chainIq, maxPrb) ;
			++chainIq ;
		}
	}

	// RX
	unsigned totalIq(mTotalStreams[hardwareData->getNumUlchains()]) ;
	for (unsigned chain=0; chain < hardwareData->getNumUlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getUlChainInfo(chain)) ;
		unsigned maxPrb(calcMaxPrb(chainInfo.chain_type)) ;

		// Get the antenna information for each stream
		unsigned chainIq( chainInfo.iq_stream_start ) ;
		for (auto ant : chainInfo.antenna)
		{
			(void)ant ;
			// RX
			createEndpointCapacitySharingGroup(parent, (totalIq + chainIq), maxPrb) ;
			++chainIq ;
		}
	}

	// PRACH
	for (unsigned chain=0; chain < hardwareData->getNumUlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getUlChainInfo(chain)) ;

		// Get the antenna information for each stream
		unsigned chainIq( chainInfo.iq_stream_start ) ;
		for (auto ant : chainInfo.antenna)
		{
			(void)ant ;

			// PRACH
			createEndpointCapacitySharingGroup(parent, (2*totalIq + chainIq), 70) ;
			++chainIq ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhYangCarrierMgr::createEndpointCapacitySharingGroup(std::shared_ptr<ILeafContainer> parent,
		unsigned id, unsigned maxPrb)
{
//    |  +--ro id                                       uint16
//    |  +--ro max-control-sections-per-data-section?   uint8
//    |  +--ro max-sections-per-symbol?                 uint16
//    |  +--ro max-sections-per-slot?                   uint16
//    |  +--ro max-beams-per-symbol?                    uint16
//    |  +--ro max-beams-per-slot?                      uint16
//    |  +--ro max-prb-per-symbol?                      uint16
//    |  +--ro max-numerologies-per-symbol?             uint16
//    |  +--ro max-endpoints?                           uint16
//    |  +--ro max-managed-delay-endpoints?             uint16
//    |  +--ro max-non-managed-delay-endpoints?         uint16

	auto endpointCap = parent->addContainer("endpoint-capacity-sharing-groups") ;
	endpointCap->addLeafInt("id", id) ;
	endpointCap->addLeaf("max-control-sections-per-data-section", "1") ;
	endpointCap->addLeaf("max-sections-per-symbol", "0") ;
	endpointCap->addLeaf("max-sections-per-slot", "0") ;
	endpointCap->addLeaf("max-beams-per-symbol", "0") ;
	endpointCap->addLeaf("max-beams-per-slot", "0") ;
	endpointCap->addLeafInt("max-prb-per-symbol", maxPrb) ;
	endpointCap->addLeaf("max-numerologies-per-symbol", "0") ;
	endpointCap->addLeaf("max-endpoints", "0") ;
	endpointCap->addLeaf("max-managed-delay-endpoints", "0") ;
	endpointCap->addLeaf("max-non-managed-delay-endpoints", "0") ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhYangCarrierMgr::createTxArrays()
{
	// get the total number of TX antennas

	std::shared_ptr<ILeafContainer> parent(leafContainer()) ;
	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );

	// Get chain info
	mNumTx = 0 ;
	for (unsigned chain=0; chain < hardwareData->getNumDlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getDlChainInfo(chain)) ;

		// Get the antenna information for each UL stream
		for (auto ant : chainInfo.antenna)
		{
			if (mNumTx < (ant+1))
				mNumTx = ant+1 ;
		}
	}

	// check against the carrier settings
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance()) ;
	ICarrierSetter& carrier(carrierServer->getCarrierSetter(0));
	if (mNumTx > carrier.getNumberTxPaths())
		mNumTx = carrier.getNumberTxPaths() ;


//    +--ro tx-arrays* [name]
//    |  +--ro name                                      string
//    |  +--ro number-of-rows                            uint16
//    |  +--ro number-of-columns                         uint16
//    |  +--ro number-of-array-layers                    uint8
//    |  +--ro horizontal-spacing?                       decimal64
//    |  +--ro vertical-spacing?                         decimal64
//    |  +--ro normal-vector-direction
//    |  |  +--ro azimuth-angle?   decimal64
//    |  |  +--ro zenith-angle?    decimal64
//    |  +--ro leftmost-bottom-array-element-position
//    |  |  +--ro x?   decimal64
//    |  |  +--ro y?   decimal64
//    |  |  +--ro z?   decimal64
//    |  +--ro polarisations* [p]
//    |  |  +--ro p               uint8
//    |  |  +--ro polarisation    polarisation_type
//    |  +--ro band-number                               -> /o-ran-module-cap:module-capability/o-ran-module-cap:band-capabilities/o-ran-module-cap:band-number
//    |  +--ro max-gain                                  decimal64
//    |  +--ro independent-power-budget                  boolean
//    |  +--ro capabilities*
//    |     +--ro max-supported-frequency-dl?   uint64
//    |     +--ro min-supported-frequency-dl?   uint64
//    |     +--ro max-supported-bandwidth-dl?   uint64
//    |     +--ro max-num-carriers-dl?          uint32
//    |     +--ro max-carrier-bandwidth-dl?     uint64
//    |     +--ro min-carrier-bandwidth-dl?     uint64

	for (unsigned tx=0; tx < mNumTx; ++tx)
	{
		std::string name("tx" + std::to_string(tx)) ;
		auto txarray = parent->addContainer("tx-arrays") ;
		createArray(txarray, name) ;

	//	txarray->addLeaf("max-gain", "???") ;
		txarray->addLeaf("independent-power-budget", "false") ;

		std::shared_ptr<ITxFrequencyConst> freqConst(ITxFrequencyConstFactory::getInterface()) ;
		Frequency minFreq(freqConst->getMinimum()) ;
		uint64_t txMinFreq(minFreq.getUint()) ;
		Frequency maxFreq(freqConst->getMaximum()) ;
		uint64_t txMaxFreq(maxFreq.getUint()) ;

		auto capabilities = txarray->addContainer("capabilities") ;
		capabilities->addLeafUInt64("max-supported-frequency-dl", txMaxFreq) ;
		capabilities->addLeafUInt64("min-supported-frequency-dl", txMinFreq) ;
		capabilities->addLeafUInt64("max-supported-bandwidth-dl", (txMaxFreq - txMinFreq)) ;
		capabilities->addLeafUInt32("max-num-carriers-dl", mNumStreamsPerChain.size()) ;
		capabilities->addLeafUInt64("max-carrier-bandwidth-dl", chbwMap(mMaxChbw)) ;
		capabilities->addLeafUInt64("min-carrier-bandwidth-dl", chbwMap(mMinChbw)) ;

	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhYangCarrierMgr::createRxArrays()
{
	std::shared_ptr<ILeafContainer> parent(leafContainer()) ;
	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );

	// Get chain info
	mNumRx = 0 ;
	for (unsigned chain=0; chain < hardwareData->getNumUlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getUlChainInfo(chain)) ;

		// Get the antenna information for each UL stream
		for (auto ant : chainInfo.antenna)
		{
			if (mNumRx < (ant+1))
				mNumRx = ant+1 ;
		}
	}

	// check against the carrier settings
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance()) ;
	ICarrierSetter& carrier(carrierServer->getCarrierSetter(0));
	if (mNumRx > carrier.getNumberRxPaths())
		mNumRx = carrier.getNumberRxPaths() ;



//    +--ro rx-arrays* [name]
//    |  +--ro name                                      string
//    |  +--ro number-of-rows                            uint16
//    |  +--ro number-of-columns                         uint16
//    |  +--ro number-of-array-layers                    uint8
//    |  +--ro horizontal-spacing?                       decimal64
//    |  +--ro vertical-spacing?                         decimal64
//    |  +--ro normal-vector-direction
//    |  |  +--ro azimuth-angle?   decimal64
//    |  |  +--ro zenith-angle?    decimal64
//    |  +--ro leftmost-bottom-array-element-position
//    |  |  +--ro x?   decimal64
//    |  |  +--ro y?   decimal64
//    |  |  +--ro z?   decimal64
//    |  +--ro polarisations* [p]
//    |  |  +--ro p               uint8
//    |  |  +--ro polarisation    polarisation_type
//    |  +--ro band-number                               -> /o-ran-module-cap:module-capability/o-ran-module-cap:band-capabilities/o-ran-module-cap:band-number
//    |  +--ro gain-correction-range
//    |  |  +--ro max    decimal64
//    |  |  +--ro min    decimal64
//    |  +--ro capabilities*
//    |     +--ro max-supported-frequency-ul?   uint64
//    |     +--ro min-supported-frequency-ul?   uint64
//    |     +--ro max-supported-bandwidth-ul?   uint64
//    |     +--ro max-num-carriers-ul?          uint32
//    |     +--ro max-carrier-bandwidth-ul?     uint64
//    |     +--ro min-carrier-bandwidth-ul?     uint64

	for (unsigned rx=0; rx < mNumRx; ++rx)
	{
		std::string name("rx" + std::to_string(rx)) ;
		auto rxarray = parent->addContainer("rx-arrays") ;
		createArray(rxarray, name) ;

		// gain-correction-range ???

		std::shared_ptr<IRxFrequencyConst> freqConst(IRxFrequencyConstFactory::getInterface()) ;
		Frequency minFreq(freqConst->getMinimum()) ;
		uint64_t rxMinFreq(minFreq.getUint()) ;
		Frequency maxFreq(freqConst->getMaximum()) ;
		uint64_t rxMaxFreq(maxFreq.getUint()) ;

		auto capabilities = rxarray->addContainer("capabilities") ;
		capabilities->addLeafUInt64("max-supported-frequency-ul", rxMaxFreq) ;
		capabilities->addLeafUInt64("min-supported-frequency-ul", rxMinFreq) ;
		capabilities->addLeafUInt64("max-supported-bandwidth-ul", (rxMaxFreq - rxMinFreq)) ;
		capabilities->addLeafUInt32("max-num-carriers-ul", mNumStreamsPerChain.size()) ;
		capabilities->addLeafUInt64("max-carrier-bandwidth-ul", chbwMap(mMaxChbw)) ;
		capabilities->addLeafUInt64("min-carrier-bandwidth-ul", chbwMap(mMinChbw)) ;

	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhYangCarrierMgr::createArray(std::shared_ptr<ILeafContainer> array, const std::string &name)
{
//    |  +--ro name                                      string
//    |  +--ro number-of-rows                            uint16
//    |  +--ro number-of-columns                         uint16
//    |  +--ro number-of-array-layers                    uint8
//    |  +--ro horizontal-spacing?                       decimal64
//    |  +--ro vertical-spacing?                         decimal64
//    |  +--ro normal-vector-direction
//    |  |  +--ro azimuth-angle?   decimal64
//    |  |  +--ro zenith-angle?    decimal64
//    |  +--ro leftmost-bottom-array-element-position
//    |  |  +--ro x?   decimal64
//    |  |  +--ro y?   decimal64
//    |  |  +--ro z?   decimal64
//    |  +--ro polarisations* [p]
//    |  |  +--ro p               uint8
//    |  |  +--ro polarisation    polarisation_type
//    |  +--ro band-number                               -> /o-ran-module-cap:module-capability/o-ran-module-cap:band-capabilities/o-ran-module-cap:band-number

	array->addLeaf("name", name) ;
	array->addLeaf("number-of-rows", "1") ;
	array->addLeaf("number-of-columns", "1") ;
	array->addLeaf("number-of-columns", "1") ;
	array->addLeaf("number-of-array-layers", "1") ;
	array->addLeaf("horizontal-spacing", "0.0") ;
	array->addLeaf("vertical-spacing", "0.0") ;
	auto direction = array->addContainer("normal-vector-direction") ;
	direction->addLeaf("azimuth-angle", "0.0") ;
	direction->addLeaf("zenith-angle", "0.0") ;
	auto leftmost = array->addContainer("leftmost-bottom-array-element-position") ;
	leftmost->addLeaf("x", "0.0") ;
	leftmost->addLeaf("y", "0.0") ;
	leftmost->addLeaf("z", "0.0") ;
	auto polarisations = array->addContainer("polarisations") ;
	polarisations->addLeaf("p", "0") ;
	polarisations->addLeaf("polarisation", "MINUS_45") ;
//	array->addLeaf("band-number", "???") ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhYangCarrierMgr::createStaticLowLevelTxEndpoints()
{
	std::shared_ptr<ILeafContainer> parent(leafContainer()) ;
	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );

//	mDlStreamMap.clear() ;

	/**
	 * Name is created using the format: txXccY
	 * Where X = antenna number, Y = chain index
	 * In this case, chain index == component carrier number
	 */

	for (unsigned chain=0; chain < hardwareData->getNumDlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getDlChainInfo(chain)) ;

		// Get the antenna information for each stream
		unsigned chainIq( chainInfo.iq_stream_start ) ;
		for (auto ant : chainInfo.antenna)
		{
			std::string name(txEndpointName(ant, chain)) ;
//			mDlStreamMap[name] = std::make_pair(chain, chainIq) ;

//		     +--ro static-low-level-tx-endpoints* [name]
//		     |  +--ro name                       string
//		     |  +--ro restricted-interfaces*     -> /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name
//		     |  +--ro array                      -> /user-plane-configuration/tx-arrays/name
//		     |  +--ro endpoint-type?             -> ../../endpoint-types/id
//		     |  +--ro capacity-sharing-groups*   -> ../../endpoint-capacity-sharing-groups/id

			auto endpoint = parent->addContainer("static-low-level-tx-endpoints") ;
			endpoint->addLeaf("name", name) ;
			endpoint->addLeaf("array", std::string("tx") + std::to_string(ant)) ;
			endpoint->addLeafInt("endpoint-type", (2*chain)) ;
			endpoint->addLeafInt("capacity-sharing-groups", chainIq) ;

			++chainIq ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhYangCarrierMgr::createStaticLowLevelRxEndpoints()
{
	std::shared_ptr<ILeafContainer> parent(leafContainer()) ;
	auto hardwareData( std::dynamic_pointer_cast<Zcu111CarrierHardwareData>(ICarrierHardwareData::getInstance()) );

//	mUlStreamMap.clear() ;

	/**
	 * Name is created using the format: txXccY
	 * Where X = antenna number, Y = chain index
	 * In this case, chain index == component carrier number
	 */

	unsigned totalIq(mTotalStreams[hardwareData->getNumUlchains()]) ;
	for (unsigned chain=0; chain < hardwareData->getNumUlchains(); ++chain)
	{
		const ChainCarrierInfo& chainInfo(hardwareData->getUlChainInfo(chain)) ;

		// Get the antenna information for each stream
		unsigned chainIq( chainInfo.iq_stream_start ) ;
		for (auto ant : chainInfo.antenna)
		{
			std::string name(rxEndpointName(ant, chain)) ;
//			mUlStreamMap[name] = std::make_pair(chain, chainIq) ;

//		     +--ro static-low-level-rx-endpoints* [name]
//		     |  +--ro name                       string
//		     |  +--ro restricted-interfaces*     -> /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name
//		     |  +--ro array                      -> /user-plane-configuration/tx-arrays/name
//		     |  +--ro endpoint-type?             -> ../../endpoint-types/id
//		     |  +--ro capacity-sharing-groups*   -> ../../endpoint-capacity-sharing-groups/id

			auto endpoint = parent->addContainer("static-low-level-rx-endpoints") ;
			endpoint->addLeaf("name", name) ;
			endpoint->addLeaf("array", std::string("rx") + std::to_string(ant)) ;
			endpoint->addLeafInt("endpoint-type", (2*chain)) ;
			endpoint->addLeafInt("capacity-sharing-groups", (totalIq + chainIq)) ;

			// PRACH
			name = prachEndpointName(ant, chain) ;
//			mUlStreamMap[name] = std::make_pair(chain, totalIq + chainIq) ;

			endpoint = parent->addContainer("static-low-level-rx-endpoints") ;
			endpoint->addLeaf("name", name) ;
			endpoint->addLeaf("array", std::string("rx") + std::to_string(ant)) ;
			endpoint->addLeafInt("endpoint-type", (2*chain + 1)) ;
			endpoint->addLeafInt("capacity-sharing-groups", (2*totalIq + chainIq)) ;

			++chainIq ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111FbcOranrrhYangCarrierMgr::txEndpointName(unsigned ant, unsigned cc)
{
	return endpointName("tx", ant, cc) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111FbcOranrrhYangCarrierMgr::rxEndpointName(unsigned ant, unsigned cc)
{
	return endpointName("rx", ant, cc) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111FbcOranrrhYangCarrierMgr::prachEndpointName(unsigned ant, unsigned cc)
{
	return endpointName("prach", ant, cc) ;
}
