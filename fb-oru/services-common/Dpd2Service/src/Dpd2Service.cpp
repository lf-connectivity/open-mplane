/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Dpd2Service.cpp
 * \brief     Service DPD messages
 *
 *
 * \details   Creates a framework for the DPD services
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Dpd2Service.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const unsigned Dpd2Service::TIMEOUT_MS(5000);

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class Dpd2Service::Monitor {
public:
	Monitor(const std::string& name, unsigned tx, const std::string& event,
			IDpdControl::MonitorFunc func,
			const std::set<std::string>& requiredAttributes) :
		mName(name),
		mTx(tx),
		mFunc(func),
		mRequired(requiredAttributes),
		mValues()
	{
		addCommon(tx, event) ;
	}

	Monitor(const std::string& name, unsigned tx, const std::string& event,
			IDpdControl::MonitorFunc func,
			const std::vector<DataVariant>& attributeValues = std::vector<DataVariant>{}) :
		mName(name),
		mTx(tx),
		mFunc(func),
		mRequired(),
		mValues()
	{
		addValues(attributeValues) ;
		addCommon(tx, event) ;
	}

	Monitor(const std::string& name,
			IDpdControl::MonitorFunc func,
			const std::vector<DataVariant>& attributeValues = std::vector<DataVariant>{}) :
		mName(name),
		mTx(255),
		mFunc(func),
		mRequired(),
		mValues()
	{
		addValues(attributeValues) ;
	}


	std::string name() const
	{
		return mName ;
	}

	void call(const std::map<std::string, DataVariant> &attributes)
	{
		mFunc(attributes) ;
	}

	bool check(const std::map<std::string, DataVariant> &attributes)
	{
		bool result(true) ;
		if (!mRequired.empty())
		{
			// check that all required attributes are present
			for (auto attr : mRequired)
			{
				if (attributes.find(attr) != attributes.end())
					continue ;

				// missing attribute so stop
				result = false ;
				break ;
			}
		}

		if (result && !mValues.empty())
		{
			// check that all required attributes are present
			for (auto expected : mValues)
			{
				if (attributes.find(expected.getName()) == attributes.end())
				{
					// missing attribute so stop
					result = false ;
					break ;
				}

				// check vaue
				DataVariant got(attributes.at(expected.getName())) ;
				if (got.toString() == expected.toString())
					continue ;

				// mismatch attribute so stop
				result = false ;
				break ;
			}
		}

		return result ;
	}

private:
	void addCommon(unsigned tx, const std::string& event)
	{
		DataVariant dvTx(DataVariantType::Int, "tx", std::to_string(tx)) ;
		DataVariant dvEvent(DataVariantType::String, "event", event) ;

		mRequired.insert(dvTx.getName()) ;
		mRequired.insert(dvEvent.getName()) ;

		mValues.push_back(dvTx) ;
		mValues.push_back(dvEvent) ;
	}

	void addValues(const std::vector<DataVariant>& attributeValues)
	{
		mValues = attributeValues ;
		for (auto dv : mValues)
		{
			mRequired.insert(dv.getName()) ;
		}
	}

private:
	std::string mName ;
	unsigned mTx ;
	IDpdControl::MonitorFunc mFunc ;

    std::set<std::string> mRequired ;
    std::vector<DataVariant> mValues ;


};

//=============================================================================================================
// PUBLIC IDPDCONTROL STATIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
bool IDpdControl::pushInt(std::vector<DataVariant>& list, const std::string& name, int value)
{
	DataVariant dv(name, std::string("INT")) ;
	dv.set(value) ;
	list.push_back(dv) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool IDpdControl::pushFloat(std::vector<DataVariant>& list, const std::string& name, float value)
{
    DataVariant dv(name, std::string("FLOAT")) ;
    dv.set(value) ;
    list.push_back(dv) ;
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool IDpdControl::pushBool(std::vector<DataVariant>& list, const std::string& name, bool value,
		const std::map<bool, std::string>& enumValues)
{
	DataVariant dv(name, std::string("ENUM(") + enumValues.at(false) + ":" + enumValues.at(true) + ")") ;
	dv.set(value) ;
	list.push_back(dv) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool IDpdControl::pushEnum(std::vector<DataVariant>& list,
		const std::string& name, const std::string& value,
		const std::string& enumValues)
{
	DataVariant dv(name, std::string("ENUM(") + enumValues + ")") ;
	dv.set(value) ;
	list.push_back(dv) ;
	return true ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Dpd2Service::Dpd2Service() :
	TaskEvent(Task::PRIORITY_MEDIUM, Task::SMALL_STACK, "Dpd2Service", "TX"),
	mMsgHandler(),
	mCmdMutex(),
	mMutex(),
	mEvents(),
	mAlarms(),
	mEventMonitors(),
	mAlarmMonitors()
{
	std::shared_ptr<IEmbeddedMgr> mgr(IEmbeddedMgr::singleton()) ;
	mMsgHandler = (mgr->msgHandler(0)) ;

	mMsgHandler->registerEventFunc([this](const std::string& payload, const std::map<std::string, DataVariant>& attributes){
		eventCallback(payload, attributes) ;
	}) ;

	mMsgHandler->registerAlarmFunc([this](const std::string& payload, const std::map<std::string, DataVariant>& attributes){
		alarmCallback(payload, attributes) ;
	}) ;

}

//-------------------------------------------------------------------------------------------------------------
Dpd2Service::~Dpd2Service()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Dpd2Service::resetDpd(unsigned tx)
{
	std::unique_lock<std::mutex> lock(mCmdMutex) ;

	return sendCommand("reset", tx) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Dpd2Service::startDpd(unsigned tx)
{
	return startDpd(tx, TIMEOUT_MS) ;
}


//-------------------------------------------------------------------------------------------------------------
bool Dpd2Service::startDpd(unsigned tx, unsigned timeoutMs)
{
	std::unique_lock<std::mutex> lock(mCmdMutex) ;

	return sendCommand("start", tx, std::vector<DataVariant>{}, timeoutMs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Dpd2Service::stopDpd(unsigned tx)
{
	std::unique_lock<std::mutex> lock(mCmdMutex) ;

	return sendCommand("stop", tx) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Dpd2Service::setPapr(unsigned tx, const Power& papr)
{
	std::unique_lock<std::mutex> lock(mCmdMutex) ;

	// TBD
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool Dpd2Service::setSRxAtten(unsigned tx, const Power& atten)
{
	std::unique_lock<std::mutex> lock(mCmdMutex) ;

	// TBD
	return false ;
}


//-------------------------------------------------------------------------------------------------------------
bool Dpd2Service::setParams(unsigned tx, const std::vector<DataVariant> &params)
{
	std::unique_lock<std::mutex> lock(mCmdMutex) ;

	return sendCommand("set", tx, params) ;
}


//-------------------------------------------------------------------------------------------------------------
void Dpd2Service::addEventMonitor(const std::string &name, unsigned tx,
		const std::string &event, MonitorFunc func,
		const std::vector<DataVariant>& attributeValues)
{
	std::shared_ptr<Monitor> monitor(std::make_shared<Monitor>(name, tx, event, func, attributeValues)) ;
	std::unique_lock<std::mutex> lock(mMutex) ;
	mEventMonitors[name] = monitor ;
}

//-------------------------------------------------------------------------------------------------------------
void Dpd2Service::addEventMonitor(const std::string &name, MonitorFunc func,
		const std::vector<DataVariant>& attributeValues)
{
	std::shared_ptr<Monitor> monitor(std::make_shared<Monitor>(name, func, attributeValues)) ;
	std::unique_lock<std::mutex> lock(mMutex) ;
	mEventMonitors[name] = monitor ;
}

//-------------------------------------------------------------------------------------------------------------
void Dpd2Service::delEventMonitor(const std::string &name)
{
	std::unique_lock<std::mutex> lock(mMutex) ;
	if (mEventMonitors.find(name) == mEventMonitors.end())
		return ;
	mEventMonitors.erase(name) ;
}

//-------------------------------------------------------------------------------------------------------------
void Dpd2Service::addAlarmMonitor(const std::string &name, IDpdControl::MonitorFunc func,
		const std::vector<DataVariant> &attributeValues)
{
	std::shared_ptr<Monitor> monitor(std::make_shared<Monitor>(name, func, attributeValues)) ;
	std::unique_lock<std::mutex> lock(mMutex) ;
	mAlarmMonitors[name] = monitor ;
}

//-------------------------------------------------------------------------------------------------------------
void Dpd2Service::delAlarmMonitor(const std::string &name)
{
	std::unique_lock<std::mutex> lock(mMutex) ;
	if (mAlarmMonitors.find(name) == mAlarmMonitors.end())
		return ;
	mAlarmMonitors.erase(name) ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Dpd2Service::runEvent()
{
	std::map<std::string, DataVariant> event ;
	std::map<std::string, DataVariant> alarm ;
	std::vector<std::shared_ptr<Monitor>> triggeredEventMonitors ;
	std::vector<std::shared_ptr<Monitor>> triggeredAlarmMonitors ;

	do
	{
		event.clear() ;
		alarm.clear() ;
		triggeredEventMonitors.clear() ;
		triggeredAlarmMonitors.clear() ;

		// Handle events
		{
			std::unique_lock<std::mutex> lock(mMutex) ;
			if (!mEvents.empty())
			{
				event = mEvents.front() ;
				mEvents.pop() ;

				// process any monitors
				if (!mEventMonitors.empty())
				{
					for (auto entry : mEventMonitors)
					{
						if (entry.second->check(event))
						{
							triggeredEventMonitors.push_back(entry.second) ;
						}
					}
				}
			}
		}

		if (!event.empty())
		{
			// dispatch to event monitors
			if (!triggeredEventMonitors.empty())
			{
				for (auto mon : triggeredEventMonitors)
				{
					mon->call(event) ;
				}
			}
		}


		// Handle alarms
		{
			std::unique_lock<std::mutex> lock(mMutex) ;
			if (!mAlarms.empty())
			{
				alarm = mAlarms.front() ;
				mAlarms.pop() ;
			}

			// process any monitors
			if (!mAlarmMonitors.empty())
			{
				for (auto entry : mAlarmMonitors)
				{
					if (entry.second->check(alarm))
					{
						triggeredAlarmMonitors.push_back(entry.second) ;
					}
				}
			}

		}

		if (!alarm.empty())
		{
			// dispatch to alarm monitors
			if (!triggeredAlarmMonitors.empty())
			{
				for (auto mon : triggeredAlarmMonitors)
				{
					mon->call(alarm) ;
				}
			}
		}

	} while(!event.empty() || !alarm.empty()) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Dpd2Service::sendCommand(std::string command, unsigned tx, const std::vector<DataVariant>& params, unsigned timeout)
{
	std::vector<DataVariant> attributes(params) ;
	std::set<std::string> varNames ;
	std::vector<DataVariant> replyAttributes ;
	bool ret = false;

	// Add attribute for Tx
	pushInt(attributes, "tx", tx) ;

	ret = mMsgHandler->sendCommand(command, attributes, varNames, replyAttributes, timeout);
	if (ret)
	{
		for (auto& attr : replyAttributes)
		{
			if (attr.getName() == "response")
			{
				if (attr.toString() == "NACK")
				{
					ret = false;
				}
			}
		}
	}

	return ret ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Dpd2Service::eventCallback(const std::string &payloadStr, const std::map<std::string, DataVariant>& attributes)
{
	// TODO connect this up to the rest of the application
	(void)payloadStr;
//	std::cerr << "Dpd2Service::EVENT [" << payloadStr << "]" <<  std::endl ;

	std::unique_lock<std::mutex> lock(mMutex) ;
	mEvents.push(attributes) ;
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void Dpd2Service::alarmCallback(const std::string &payloadStr, const std::map<std::string, DataVariant>& attributes)
{
	// TODO connect this up to the rest of the application
	(void)payloadStr;
//	std::cerr << "Dpd2Service::ALARM [" << payloadStr << "]" <<  std::endl ;

	std::unique_lock<std::mutex> lock(mMutex) ;
	mAlarms.push(attributes) ;
	event() ;
}
