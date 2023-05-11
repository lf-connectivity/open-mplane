/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LogList.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <exception>
#include <iostream>
#include <sstream>

#include "stringfunc.hpp"

#include "IBootEnv.h"
#include "LogList.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned LogList::NAME_WIDTH  = 50 ;
const unsigned LogList::GROUP_WIDTH = 20 ;
const unsigned LogList::LEVEL_WIDTH = 10 ;

/**
 * Variable names used to set/save logging settings in the environment
 */
std::string ILoggable::GROUP_LOG_ENV_VARNAME{"GROUPLOG"} ;
std::string ILoggable::INST_LOG_ENV_VARNAME{"INSTLOG"} ;

//=============================================================================================================
// LOCAL
//=============================================================================================================

namespace {

	// Create an environment variable value from the current settings
	std::string envStr(const std::map<std::string, ILoggable::LogDebugLevel>& levels)
	{
		std::string value ;
		for (auto& entry : levels)
		{
			if (entry.second == ILoggable::LOG_DEBUG_NONE)
				continue ;

			if (!value.empty())
				value += ":" ;

			value += entry.first + "=" + ILoggable::levelStr(entry.second) ;
		}

		return value ;
	}
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LogList::LogList() :
	mMutex(),
	mUniqueNames(),
	mUniqueMap(),
	mInstanceLevels(),
	mGroupLevels(),
	mList(),
	mAllowRegistration(true)
{
}

//-------------------------------------------------------------------------------------------------------------
LogList::~LogList()
{
}

//-------------------------------------------------------------------------------------------------------------
bool LogList::add(ILoggable* logger)
{
	Mutex::Lock lock(mMutex) ;

	// reject all if not allowing new registration
	if (!mAllowRegistration)
		return false ;
//		throw std::runtime_error("Cannot register new objects as Loggable") ;

	// reject if already in the list - assumes instance name was created using uniqueInstanceName() method
	std::string instanceName(logger->getInstanceName()) ;
	auto entry( mList.find(instanceName) ) ;
	if (entry != mList.end())
		return false ;

	// Add to list
	mList[instanceName] = logger ;

	// Check for previously set group/instance log levels
	ILoggable::LogDebugLevel level(ILoggable::LOG_DEBUG_NONE) ;

	ILoggable::LogDebugLevel groupLevel(getGroupLevel(logger->getGroupName(), level)) ;
	ILoggable::LogDebugLevel instanceLevel(getInstanceLevel(instanceName, level)) ;

	if (level < groupLevel)
		level = groupLevel ;
	if (level < instanceLevel)
		level = instanceLevel ;

	// set level
	logger->setLevel(level) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool LogList::del(ILoggable* logger)
{
	Mutex::Lock lock(mMutex) ;

	// reject if not already in the list
	std::string instanceName(logger->getInstanceName()) ;
	auto entry( mList.find(instanceName) ) ;
	if (entry == mList.end())
		return false ;

	// Ok to del
	mList.erase(entry) ;

	// Now check the unique count - if we still have a counter decrement it
	auto mapEntry(mUniqueNames.find(mUniqueMap[instanceName])) ;
	if (mapEntry == mUniqueNames.end())
		return true ;

	if (--mapEntry->second == 0)
	{
		// all done so erase this entry
		mUniqueNames.erase(mapEntry) ;
	}

	// NOTE: We don't care about the mUniqueMap map, it will just be overwritten with new data as required,
	// so we don't need to delete anything from it

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void LogList::show(std::ostream& os) const
{
	Mutex::Lock lock(mMutex) ;

	os << "-- Loggable Objects List --" << std::endl ;


	os << padLeft("Name", NAME_WIDTH) << padLeft("Group", GROUP_WIDTH) << padLeft("Level", LEVEL_WIDTH) << std::endl ;
	os << padLeft("----", NAME_WIDTH) << padLeft("-----", GROUP_WIDTH) << padLeft("-----", LEVEL_WIDTH) << std::endl ;

	for (auto entry : mList)
	{
		// Skip any names beginning with '.' (i.e. hidden)
		if (entry.first[0] == '.')
			continue ;

		ILoggable* loggable(entry.second) ;
		os << 	padLeft(entry.first, NAME_WIDTH, ' ') <<
				padLeft(loggable->getGroupName(), GROUP_WIDTH, ' ') <<
				padLeft(ILoggable::levelStr(loggable->getLevel()), LEVEL_WIDTH) <<
				std::endl ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void LogList::setLevel(ILoggable::LogDebugLevel level)
{
	Mutex::Lock lock(mMutex) ;

	// Save the level in the level maps (so that any objects created after this setting will get the correct level)
	for (auto& entry : mInstanceLevels)
	{
		// save level
		entry.second = level ;
	}
	for (auto& entry : mGroupLevels)
	{
		// save level
		entry.second = level ;
	}

	// Now set all ILoggable objects' level
	for (auto entry : mList)
	{
		// set level
		entry.second->setLevel(level) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool LogList::setGroupLevel(ILoggable::LogDebugLevel level, const std::string& groupName)
{
	Mutex::Lock lock(mMutex) ;

	// save setting for later
	setGroupLevel(groupName, level) ;

	// case insensitive match
	std::string groupNameLower(toLower(groupName)) ;
	bool found = false ;
	for (auto& entry : mList)
	{
		if (toLower(entry.second->getGroupName()) != groupNameLower)
			continue ;

		found = true ;

		// set level
		entry.second->setLevel(level) ;
	}
	return found ;
}

//-------------------------------------------------------------------------------------------------------------
bool LogList::setInstanceLevel(ILoggable::LogDebugLevel level, const std::string& instanceName)
{
	Mutex::Lock lock(mMutex) ;

	// save setting for later
	setInstanceLevel(instanceName, level) ;

	// process if exact match
	auto entry( mList.find(instanceName) ) ;
	if (entry != mList.end())
	{
		// Ok to set
		entry->second->setLevel(level) ;
		return true ;
	}

	// case insensitive match
	std::string nameLower(toLower(instanceName)) ;
	for (auto& entryRef : mList)
	{
		if (toLower(entryRef.first) == nameLower)
		{
			// Ok to set
			entryRef.second->setLevel(level) ;
			return true ;
		}
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::string LogList::uniqueInstanceName(const std::string& name)
{
	Mutex::Lock lock(mMutex) ;

	// reject if not allowing new registration
	if (!mAllowRegistration)
		return name ;

	std::string nameCopy(validName(name, "unnamed")) ;

	// check for uniqueness
	auto entry(mUniqueNames.find(nameCopy)) ;
	if (entry == mUniqueNames.end())
	{
		mUniqueNames[nameCopy] = 1 ;
		mUniqueMap[nameCopy] = nameCopy ;
		return nameCopy ;
	}

	// Already have same name - create a unique one
	std::string uniqueName( nameCopy + "-" + std::to_string(mUniqueNames[nameCopy]++) ) ;
	mUniqueMap[uniqueName] = nameCopy ;

	return uniqueName ;
}

//-------------------------------------------------------------------------------------------------------------
std::string LogList::validGroupName(const std::string& name) const
{
	return validName(name, "GLOBAL") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string LogList::validName(const std::string& name, const std::string& defaultName) const
{
	std::string nameCopy(name) ;
	if (nameCopy.empty())
		nameCopy = defaultName ;
	nameCopy = replaceChars(nameCopy, " ", '_') ;

	return nameCopy ;
}

//-------------------------------------------------------------------------------------------------------------
bool LogList::save() const
{
	// Create a text string containing the variable settings
	std::map<std::string, std::string> vars ;
	vars[ILoggable::GROUP_LOG_ENV_VARNAME] = envStr(mGroupLevels) ;
	vars[ILoggable::INST_LOG_ENV_VARNAME] = envStr(mInstanceLevels) ;

	// Write the variables
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;

	return bootEnv->setVar(vars) ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::LogList::closeRegistration()
{
	Mutex::Lock lock(mMutex) ;
	mAllowRegistration = false ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ILoggable::LogDebugLevel LogList::getGroupLevel(const std::string& groupName, ILoggable::LogDebugLevel defaultLevel)
{
	std::string lowerName(toLower(groupName)) ;
	auto entry(mGroupLevels.find(lowerName)) ;
	if (entry == mGroupLevels.end())
	{
		// Create a new group level entry
		mGroupLevels[lowerName] = defaultLevel ;
	}
	return mGroupLevels[lowerName] ;
}

//-------------------------------------------------------------------------------------------------------------
ILoggable::LogDebugLevel LogList::getInstanceLevel(const std::string& instanceName, ILoggable::LogDebugLevel defaultLevel)
{
	std::string lowerName(toLower(instanceName)) ;
	auto entry(mInstanceLevels.find(lowerName)) ;
	if (entry == mInstanceLevels.end())
	{
		// Create a new group level entry
		mInstanceLevels[lowerName] = defaultLevel ;
	}
	return mInstanceLevels[lowerName] ;
}

//-------------------------------------------------------------------------------------------------------------
void LogList::setGroupLevel(const std::string& groupName, ILoggable::LogDebugLevel level)
{
	std::string lowerName(toLower(groupName)) ;
	mGroupLevels[lowerName] = level ;
}

//-------------------------------------------------------------------------------------------------------------
void LogList::setInstanceLevel(const std::string& instanceName, ILoggable::LogDebugLevel level)
{
	std::string lowerName(toLower(instanceName)) ;
	mInstanceLevels[lowerName] = level ;
}
