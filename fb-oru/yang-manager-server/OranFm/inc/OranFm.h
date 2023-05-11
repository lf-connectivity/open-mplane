/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ORanFm.h
 * \brief     ORAN Fault Manager implements o-ran-fm.yang
 *
 *
 * \details   Implements the alarm notifications in o-ran-fm.yang.
 * The implementation is based on the ORAN-WG4.MP.0-v02.00.00 specification chapter 8.
 * It registers itself as an observer to all alarms.
 * Whenever an alarm is triggered, a notification is sent and an alarm is added to the alarm list is updated.
 * Whenever an alarm is cleared, a notification is sent and and the alarm is removed from the alarm list.
 * Further information about each alarm is found in FaultConfig.xml.
*/

#ifndef ORANFM_H_
#define ORANFM_H_

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <memory>
#include <map>
#include <string>
#include <iostream>

#include "Observer.hpp"

#include "ILeafContainer.h"
#include "ISendNotification.h"

#include "Alarm.h"

#include "MplaneAlarms.h"
#include "MplanePerformanceMgmt.h"

namespace Mplane
{

class OranFm : public Observer<IAlarm>
{
public:
	OranFm(ISendNotification &notifier, std::shared_ptr<ILeafContainer> callback, bool testNoConfig = false);
	~OranFm();

	/*!
	 * \brief Attach all the possible alarms to this object, so that they are observed
	 */
	void AttachAlarms();

	/*!
	 * \brief Remove all the possible alarms attached to this object
	 */
	void DetachAlarms();

	// Observer requires these methods
	const char* name() const override;

	/*!
	 * \brief When a new alarm has been raised or cleared, this is called via the Observer
	 */
	void update(IAlarm &subject) override;

	void show(std::shared_ptr<IAlarm> alarm);
	void show();

	int initDummyThread();
	void threadFunc(void* arg);

	static void* static_threadFunc(void *this_ptr)
	{
		Mplane::OranFm *pEvOranFmObj  = (Mplane::OranFm *) this_ptr;
		pEvOranFmObj->threadFunc(NULL);
		return NULL;
	}

private:
	void UpdateGetList(IAlarm &alarm);
	std::shared_ptr<YangParams> makeNotification(IAlarm &alarm, const std::string &notifPath);
	void FillInComponent(std::shared_ptr<ILeafContainer> component, IAlarm &alarm);
	void registerHalAlarms();

	std::string path(const std::string & path) const;
	bool IsAlarmWarning(const IAlarm &alarm) const;

	static std::vector<std::shared_ptr<Alarm>> ListAlarms();
	static std::string GetRootCause(const IAlarm &alarm);
	static std::string GetCurrentYangTime();
	static struct tm GetCurrentTime();

	const std::shared_ptr<ILeafContainer> mCallback;
	std::map<int, std::shared_ptr<ILeafContainer>> mAlarmsAdded;	// ID values of alarms already added to the list
	ISendNotification &mNotifier;
};

}

#endif /* ORANFM_H_ */
