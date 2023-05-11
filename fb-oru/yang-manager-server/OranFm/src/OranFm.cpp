/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ORanFm.cpp
 * \brief     ORAN Fault Manager implements o-ran-fm.yang
 *
 *
 * \details   Implements the alarm notifications in o-ran-fm.yang.
 * The implementation is based on the ORAN-WG4.MP.0-v02.00.00 specification chapter 8.
 * It registers itself as an observer to all alarms.
 * Whenever an alarm is triggered, a notification is sent and an alarm is added to the alarm list is updated.
 * Whenever an alarm is cleared , a notification is sent and and the alarm is removed from the alarm list.
 * Further information about each alarm is found in FaultConfig.xml.
 *
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include <chrono>
#include <thread>

#include "YangParamUtils.h"
#include "YangUtils.h"

#include "OranFm.h"

//using namespace std;
using namespace Mplane ;

// Map radio alarms to ORAN fault ids
const std::map<std::string, unsigned> ALARMS_MAP{
	{ "AlarmCUPlaneConnectivityMinor", 1 },
	{ "AlarmCUPlaneConnectivityMajor", 2 },
	{ "RadioTempMinorAlarm", 1 },
	{ "RadioTempMajorAlarm", 2 },
	{ "Tx1DegradedAlarm", 9 },
	{ "Tx2DegradedAlarm", 9 },
	{ "Tx3DegradedAlarm", 9 },
	{ "Tx4DegradedAlarm", 9 },
} ;

const unsigned USER_FAULT_ID(1000) ;

OranFm::OranFm(ISendNotification &notifier, std::shared_ptr<ILeafContainer> callback, bool testNoConfig)
	: mCallback(callback)
	, mAlarmsAdded()
	, mNotifier(notifier)
{
}

OranFm::~OranFm()
{
	DetachAlarms();
}

void OranFm::AttachAlarms()
{
	auto allAlarms = ListAlarms();
	for (auto alarm : allAlarms)
	{
		alarm->attach(*this);
	}
}

void OranFm::DetachAlarms()
{
	auto allAlarms = ListAlarms();
	for (auto alarm : allAlarms)
	{
		alarm->detach(*this);
	}
}

const char * OranFm::name() const
{
	return "AlarmListen";
}

void OranFm::update(IAlarm &alarm)
{
	if (!IsAlarmWarning(alarm))			// Warnings are ignored
	{
		const std::string notifPath(path("alarm-notif"));
		auto params = makeNotification(alarm, notifPath);
		mNotifier.sendNotification(notifPath, params);
		UpdateGetList(alarm);
	}
}

void OranFm::show(std::shared_ptr<IAlarm> alarm)
{
	std::cout << "AlarmId:" << alarm->getId() << std::endl;
	alarm->show() ;
}

void OranFm::show()
{
	auto allAlarms = ListAlarms();
	for (auto alarm : allAlarms)
	{
		show(alarm);
	}
}

/*!
 * \brief Return the current time as a struct tm
 */
struct tm OranFm::GetCurrentTime()
{
	time_t t = time(NULL);
	struct tm lt = { 0 };
	localtime_r(&t, &lt);
	return lt;
}

/*!
 * \brief Return the current time in the standard yang:date time format
 */
std::string OranFm::GetCurrentYangTime()
{
	struct tm timeNow = GetCurrentTime();
	return YangUtils::getDateTime(&timeNow);
}

/*!
 * \brief List all the alarms on the system
 * \return An array of alarms
 */
std::vector<std::shared_ptr<Alarm>> OranFm::ListAlarms()
{
	auto alarmsList = IAlarmsList::getInstance();
	auto namesList = alarmsList->getNames();
	std::vector<std::shared_ptr<Alarm>> alarmList;
	for (auto &name : namesList)
	{
		auto alarm = alarmsList->getAlarm(name);
		std::shared_ptr<Alarm> realAlarm = std::dynamic_pointer_cast<Alarm> (alarm);
		alarmList.push_back(realAlarm);
	}
	return alarmList;
}

std::string OranFm::path(const std::string &path) const
{
	return ("/o-ran-fm:" + path);
}




/*!
 * \brief Given an alarm object create a notification object
 * \return The notification that can go to sendNotification
 */
std::shared_ptr<YangParams> OranFm::makeNotification(IAlarm &alarm, const std::string &notifPath)
{

	std::string yangTime = GetCurrentYangTime();
	auto params = std::make_shared<YangParams>();

	// Add ID
	unsigned faultId(alarm.getId()) ;
	if (ALARMS_MAP.find(alarm.getName()) != ALARMS_MAP.end())
	{
		// use specific fault id
		faultId = ALARMS_MAP.at(alarm.getName()) ;
	}
	else
	{
		// create a vendor-specific fault id
		faultId += USER_FAULT_ID ;
	}
	params->addParam(faultId, notifPath + "/fault-id");

	// Add root cause
	std::string rootCause = GetRootCause(alarm);
	params->addParam(rootCause, notifPath + "/fault-source");

	// Add affected objects
	params->addParam("Unknown", notifPath + "/affected-objects[1]/name");

	params->addParam(alarm.getSeverityStr(), notifPath + "/fault-severity");
	params->addParam(!alarm.isAlarmActive(), notifPath + "/is-cleared");
	params->addParam(alarm.getDescription(), notifPath + "/fault-text");		// Is alarm state good for fault text?
	params->addParam(yangTime, notifPath + "/event-time");

#if OFF_TARGET
YangParamUtils::show(params) ;
#endif

	return params;
}

/*!
 * \brief call IAlarm::getRootCause(), if the return value is empty replace with 'unknown'
 */
std::string OranFm::GetRootCause(const IAlarm &alarm)
{
	std::string rootCause = alarm.getRootCause();
	if (rootCause.length() == 0)
		rootCause = "unknown";
	return rootCause;
}

void OranFm::FillInComponent(std::shared_ptr<ILeafContainer> component, IAlarm &alarm)
{
	std::string alarmName = alarm.getName();

	unsigned faultId(alarm.getId()) ;
	if (ALARMS_MAP.find(alarm.getName()) != ALARMS_MAP.end())
	{
		// use specific fault id
		faultId = ALARMS_MAP.at(alarm.getName()) ;
	}
	else
	{
		// create a vendor-specific fault id
		faultId += USER_FAULT_ID ;
	}
	component->addLeaf("fault-id", std::to_string(faultId) );

	// NOTE: The "root cause" string from the alarm is just the IFault name string - may need more than this?
	component->addLeaf("fault-source", GetRootCause(alarm));

	/// Add all the affected objects
	auto affectedObjects = component->addContainer("affected-objects");
	affectedObjects->addLeaf("name", "Unknown");

	component->addLeaf("fault-severity", alarm.getSeverityStr());
	component->addLeafBool("is-cleared", false); 		// If cleared, would it be in this list?
	component->addLeaf("fault-text", alarm.getDescription());

	std::string formattedTime = GetCurrentYangTime();
	component->addLeaf("event-time", formattedTime);
}


/*!
 * \brief returns true if this alarm is a warning
 */
bool OranFm::IsAlarmWarning(const IAlarm &alarm) const
{
	return alarm.getSeverityStr() == "WARNING" ;
}

/*!
 * \brief Add/remove/revise a new alarm from the <rpc><get> list
 * \details Whether the alarm is added/removed or updated depends on whether alarm is active or not
 */
void OranFm::UpdateGetList(IAlarm &alarm)
{
	int alarmId = alarm.getId();
	// If this is inactive, remove that container
	// If this alarm was added before, modify that container
	// If this is a new alarm then add a new container to the tree
	if (!alarm.isAlarmActive())
	{
		// Inactive alarm? Remove from list
		auto component = mAlarmsAdded[alarmId];
		mCallback->removeContainer(component);
		mAlarmsAdded.erase(alarmId);
	}
	else if (mAlarmsAdded.count(alarmId) == 0)
	{
		// new alarm? Add to list
		auto component = mCallback->addContainer("active-alarms");
		FillInComponent(component, alarm);
		mAlarmsAdded[alarmId] = component;
	}
	else
	{
		// revised alarm? Update in list.
		auto component = mAlarmsAdded[alarmId];
		FillInComponent(component, alarm);
		component->clear();
	}
}

void OranFm::registerHalAlarms()
{
	initDummyThread();
}

void OranFm::threadFunc(void * arg)
{
	Alarm * oldAlarm = new Alarm("RSSI", "Unknown");
	oldAlarm->setStatus(true);
	while(1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		if (get_perf_meas_cb_ptr())
		{
			halmplane_oran_perf_meas_t pm;
			int retVal = halmplane_getRssi(0, &pm.rssi);
			if (!retVal)
			{
				(get_perf_meas_cb_ptr())(&pm, NULL);
			}
			Alarm * newAlarm = new Alarm("RSSI", std::to_string(pm.rssi));
			newAlarm->setStatus(true);
			oldAlarm->setStatus(false);
			this->update(*newAlarm);
			this->update(*oldAlarm);
			delete oldAlarm;
			oldAlarm = newAlarm;
		}
	}
	return;
}

int OranFm::initDummyThread()
{

	// Thread id
	pthread_t threadId;
	// Create a thread that will function threadFunc()
	int err = pthread_create(&threadId, NULL, &(OranFm::static_threadFunc), (void*)this);
	// Check if thread is created sucessfuly
	if (err)
	{
		std::cout << "Thread creation failed : " << err << std::endl;
		return err;
	}
	else
	{
		std::cout << "Thread Created with ID : " << threadId << std::endl;
	}
	return 0;
}
