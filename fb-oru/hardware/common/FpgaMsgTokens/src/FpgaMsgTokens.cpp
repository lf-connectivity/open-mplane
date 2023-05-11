/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaMsgTokens.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdexcept>
#include <utility>
#include <algorithm>

#include "ILoggable.h"
#include "FpgaMsgTokens.h"

using namespace Mplane;


using MapEntry = std::map<std::string, unsigned>::value_type ;
using TypesEntry = std::map<std::string, std::string>::value_type ;

#if 0
#define THROW_INVALID(msg) \
	eventWarning(msg) ; \
	throw std::invalid_argument(msg)
#endif

#define THROW_INVALID(msg) \
	ILoggable::logEventWarning(msg)


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaMsgTokens::FpgaMsgTokens(unsigned apiVersion,
		const std::map<std::string, unsigned>& commandMap,
		const std::map<std::string, unsigned>& stateMap,
		const std::map<std::string, unsigned>& tokenMap,
		const std::map<std::string, StateType>& stateTypes) :

	mApiVersion(apiVersion),
	mCommandMap(commandMap),
	mStateMap(stateMap),
	mTokenMap(tokenMap),
	mStateTypes(stateTypes),

	// derived ranges
	mCommandRange{minMaxMap(mCommandMap)},
	mStateRange{minMaxMap(mStateMap)},
	mTokenRange{minMaxMap(mTokenMap)},

	// create reverse lookups
	mRevCommandMap{revMap(mCommandMap, mCommandRange)},
	mRevStateMap{revMap(mStateMap, mStateRange)},
	mRevTokenMap{revMap(mTokenMap, mTokenRange)},
	mRevStateTypes{revTypeMap(mStateTypes, mStateRange)}
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaMsgTokens::~FpgaMsgTokens() {
}

//-------------------------------------------------------------------------------------------------------------
int FpgaMsgTokens::getToken(const std::string& tokenStr) const
{
	auto entry(mTokenMap.find(tokenStr)) ;
	if (entry == mTokenMap.end())
	{
		THROW_INVALID("Invalid token "+tokenStr) ;
		return -1 ;
	}
	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaMsgTokens::getTokenStr(unsigned token) const
{
	if (!isToken(token))
	{
		THROW_INVALID("Invalid token id "+std::to_string(token)) ;
		return "" ;
	}

	unsigned normalised(token - mTokenRange.first) ;
	return mRevTokenMap.at(normalised) ;
}

//-------------------------------------------------------------------------------------------------------------
int FpgaMsgTokens::getCmdToken(const std::string& tokenStr) const
{
	auto entry(mCommandMap.find(tokenStr)) ;
	if (entry == mCommandMap.end())
	{
		THROW_INVALID("Invalid command string "+tokenStr) ;
		return -1 ;
	}
	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaMsgTokens::getCmdTokenStr(unsigned token) const
{
	if (!isCmdToken(token))
	{
		THROW_INVALID("Invalid command id "+std::to_string(token)) ;
		return "" ;
	}

	unsigned normalised(token - mCommandRange.first) ;
	return mRevCommandMap.at(normalised) ;
}

//-------------------------------------------------------------------------------------------------------------
int FpgaMsgTokens::getStateToken(const std::string& tokenStr) const
{
	auto entry(mStateMap.find(tokenStr)) ;
	if (entry == mStateMap.end())
	{
		THROW_INVALID("Invalid state string "+tokenStr) ;
		return -1 ;
	}

	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaMsgTokens::getStateTokenStr(unsigned token) const
{
	if (!isStateToken(token))
	{
		THROW_INVALID("Invalid state id "+std::to_string(token)) ;
		return "" ;
	}

	unsigned normalised(token - mStateRange.first) ;
	return mRevStateMap.at(normalised) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned FpgaMsgTokens::getApiVersion() const
{
	return mApiVersion ;
}


//-------------------------------------------------------------------------------------------------------------
bool FpgaMsgTokens::isCmdToken(unsigned token) const
{
	if (token >= mCommandRange.first && token <= mCommandRange.second)
		return true ;

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaMsgTokens::isStateToken(unsigned token) const
{
	if (token >= mStateRange.first && token <= mStateRange.second)
		return true ;

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaMsgTokens::isToken(unsigned token) const
{
	if (token >= mTokenRange.first && token <= mTokenRange.second)
		return true ;

	return false ;
}


//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> FpgaMsgTokens::getCmds() const
{
	std::vector<std::string> cmds ;
	for (auto const& entry : mCommandMap)
	{
		cmds.push_back(entry.first) ;
	}
	return cmds ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> FpgaMsgTokens::getStates() const
{
	std::vector<std::string> states ;
	for (auto const& entry : mStateMap)
	{
		states.push_back(entry.first) ;
	}
	return states ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaMsgTokens::isCmdToken(const std::string& tokenStr) const
{
	auto entry(mCommandMap.find(tokenStr)) ;
	if (entry == mCommandMap.end())
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaMsgTokens::isStateToken(const std::string& tokenStr) const
{
	auto entry(mStateMap.find(tokenStr)) ;
	if (entry == mStateMap.end())
		return false ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool FpgaMsgTokens::isToken(const std::string& tokenStr) const
{
	auto entry(mTokenMap.find(tokenStr)) ;
	if (entry == mTokenMap.end())
		return false ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
std::string FpgaMsgTokens::getStateTypeStr(const std::string& tokenStr) const
{
	auto entry(mStateTypes.find(tokenStr)) ;
	if (entry == mStateTypes.end())
	{
		THROW_INVALID("Invalid state "+tokenStr) ;
		return "" ;
	}
	return entry->second.typeStr ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaMsgTokens::getStateTypeStr(unsigned token) const
{
	if (!isStateToken(token))
	{
		THROW_INVALID("Invalid state id "+ std::to_string(token)) ;
		return "" ;
	}

	unsigned normalised(token - mStateRange.first) ;
	return mRevStateTypes.at(normalised).typeStr ;
}

//-------------------------------------------------------------------------------------------------------------
DataVariantType::Type FpgaMsgTokens::getStateType(const std::string& tokenStr) const
{
	auto entry(mStateTypes.find(tokenStr)) ;
	if (entry == mStateTypes.end())
	{
		THROW_INVALID("Invalid state "+tokenStr) ;
		return DataVariantType::None ;
	}
	return entry->second.type ;
}

//-------------------------------------------------------------------------------------------------------------
DataVariantType::Type FpgaMsgTokens::getStateType(unsigned token) const
{
	if (!isStateToken(token))
	{
		THROW_INVALID("Invalid state id "+ std::to_string(token)) ;
		return DataVariantType::None ;
	}

	unsigned normalised(token - mStateRange.first) ;
	return mRevStateTypes.at(normalised).type ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaMsgTokens::getStateDefault(const std::string& tokenStr) const
{
	auto entry(mStateTypes.find(tokenStr)) ;
	if (entry == mStateTypes.end())
	{
		THROW_INVALID("Invalid state "+tokenStr) ;
		return "" ;
	}
	return entry->second.defaultVal ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaMsgTokens::getStateDefault(unsigned token) const
{
	if (!isStateToken(token))
	{
		THROW_INVALID("Invalid state id "+std::to_string(token)) ;
		return "" ;
	}

	unsigned normalised(token - mStateRange.first) ;
	return mRevStateTypes.at(normalised).defaultVal ;
}

//=============================================================================================================
// PRIVATE STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::pair<unsigned, unsigned> FpgaMsgTokens::minMaxMap(const std::map<std::string, unsigned>& map) const
{
	// get min value
	auto minIt( std::min_element(map.begin(), map.end(),
		[](const std::map<std::string, unsigned>::value_type& l, const std::map<std::string, unsigned>::value_type& r) -> bool {
			return l.second < r.second ;
		}
	) ) ;

	// get max value
	auto maxIt( std::max_element(map.begin(), map.end(),
		[](const std::map<std::string, unsigned>::value_type& l, const std::map<std::string, unsigned>::value_type& r) -> bool {
			return l.second < r.second ;
		}
	) ) ;

	return std::pair<unsigned, unsigned>{minIt->second, maxIt->second} ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> FpgaMsgTokens::revMap(const std::map<std::string, unsigned>& map,
		const std::pair<unsigned, unsigned>& range) const
{
	std::vector<std::string> rev ;

	unsigned start{range.first} ;
	for (unsigned id=start; id <= range.second; ++id)
	{
		auto entry(std::find_if(map.begin(), map.end(), [id](const MapEntry& p){
			return p.second == id ;
		})) ;
		if (entry == map.end())
		{
			rev.push_back("UNKNOWN") ;
			continue ;
		}

		rev.push_back(entry->first) ;
	}

	return rev ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<FpgaMsgTokens::StateType> FpgaMsgTokens::revTypeMap(
		const std::map<std::string, StateType>& map,
		const std::pair<unsigned, unsigned>& range) const
{
	std::vector<StateType> rev ;

	unsigned start{range.first} ;
	for (unsigned id=start; id <= range.second; ++id)
	{
		// Get the token string with this id
		std::string tokenStr(getStateTokenStr(id)) ;

		// look up variable type
		auto entry(map.find(tokenStr)) ;
		if (entry == map.end())
		{
			rev.push_back(StateType{"None", DataVariantType::None, ""}) ;
			continue ;
		}

		rev.push_back(entry->second) ;
	}

	return rev ;
}
