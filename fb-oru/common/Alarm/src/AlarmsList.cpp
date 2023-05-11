/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmsList.cpp
 * \brief     Manages lists of IAlarm objects
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdexcept>

#include "IAlarm.h"
#include "AlarmsList.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

class AlarmsListInst : public AlarmsList
{
public:
	AlarmsListInst() : AlarmsList() {}
	virtual ~AlarmsListInst() {}
};
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAlarmsList> IAlarmsList::getInstance()
{
	static std::shared_ptr<IAlarmsList> instance(std::make_shared<AlarmsListInst>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AlarmsList::~AlarmsList()
{
}

//-------------------------------------------------------------------------------------------------------------
void AlarmsList::addAlarm(std::shared_ptr<IAlarm> alarm)
{
	Mutex::Lock lock(mAlarmsListMutex) ;

	// check there's not already an entry
	auto entry(mAlarmsList.find(alarm->getName())) ;
	if (entry != mAlarmsList.end())
		throw std::invalid_argument("AlarmsList adding Alarm '" + alarm->getName() + "' already registered") ;

	// Add the alarm
	mAlarmsList[alarm->getName()] = alarm ;

}

//-------------------------------------------------------------------------------------------------------------
void AlarmsList::show(std::ostream& os) const
{
	Mutex::Lock lock(mAlarmsListMutex) ;
	for (auto entry : mAlarmsList)
	{
		entry.second->show(os) ;
	}
}
//-------------------------------------------------------------------------------------------------------------
void AlarmsList::showNamesAndIds(std::ostream& os) const
{
    Mutex::Lock lock(mAlarmsListMutex);

    os << "Available alarm Id's and Names -" << std::endl ;
	os << "    Id Name" << std::endl ;

    for (auto entry : mAlarmsList)
    {
    	entry.second->showNameAndId(os) ;
    }
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<IAlarm> > AlarmsList::getActiveAlarms() const
{
	std::vector<std::shared_ptr<IAlarm>> alarms ;

	Mutex::Lock lock(mAlarmsListMutex) ;
	for (auto entry : mAlarmsList)
	{
		if (entry.second->isAlarmActive())
			alarms.push_back(entry.second) ;
	}

	return alarms ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<IAlarm> > Mplane::AlarmsList::getAlarms() const
{
	std::vector<std::shared_ptr<IAlarm>> alarms ;

	Mutex::Lock lock(mAlarmsListMutex) ;
	for (auto entry : mAlarmsList)
	{
		alarms.push_back(entry.second) ;
	}

	return alarms ;
}


//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> AlarmsList::getNames() const
{
	std::vector<std::string> names ;

	Mutex::Lock lock(mAlarmsListMutex) ;
	for (auto entry : mAlarmsList)
	{
		names.push_back(entry.first) ;
	}

	return names ;
}

//-------------------------------------------------------------------------------------------------------------
int AlarmsList::getSize() const
{
	Mutex::Lock lock(mAlarmsListMutex) ;
	return mAlarmsList.size() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAlarm> AlarmsList::getAlarm(const std::string& name) const
{
	Mutex::Lock lock(mAlarmsListMutex) ;

	// check for valid entry
	auto entry(mAlarmsList.find(name)) ;
	if (entry == mAlarmsList.end())
		return std::shared_ptr<IAlarm>() ;

	// Add the alarm
	return mAlarmsList.at(name) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAlarm> AlarmsList::getAlarm(const unsigned int ident) const
{
    Mutex::Lock lock(mAlarmsListMutex);

    std::string name;


    // Find the entry with the corresponding ident
    for (auto findEntryById : mAlarmsList)
    {
    	if( ident == findEntryById.second->getId() )
    	{
    		/* Retrieve the name to use */
    		name = findEntryById.second->getName();

    		/* Break out of the loop early */
    		break;
    	}
    }

    /* Using the name we just found, check that there is an entry and we didn't just get to the end */
    auto entry(mAlarmsList.find(name)) ;
	if (entry == mAlarmsList.end())
		return std::shared_ptr<IAlarm>() ;

	// return the alarm
	return std::shared_ptr<IAlarm>(mAlarmsList.at(name).get(), [](IAlarm*){}) ;
}
//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AlarmsList::AlarmsList() :
	Loggable("AlarmsList", "AL"),
	mAlarmsList(),
	mAlarmsListMutex()
{
}

//=============================================================================================================
// TEST
//=============================================================================================================
#ifdef OFF_TARGET
//-------------------------------------------------------------------------------------------------------------
bool Mplane::AlarmsList::removeAlarm(const std::string& name)
{
    Mutex::Lock lock(mAlarmsListMutex);

	// check there's an entry
	auto entry(mAlarmsList.find(name)) ;
	if (entry == mAlarmsList.end())
		return false ;

	// remove the fault
	mAlarmsList.erase(entry) ;
	return true ;
}

#endif
