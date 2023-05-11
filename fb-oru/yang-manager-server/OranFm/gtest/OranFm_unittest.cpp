/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranFm_unittest.cpp
 * \brief     Oran Delays unit tests
 *
 *
 * \details   ORAN Delays unit tests.
 *
 */

#include "OranFm.h"

#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <memory>

#include "Alarm.h"
#include "ILeafContainer.h"
#include "LeafContainer.h"
#include "ISendNotification.h"
#include "YangParam.h"
#include "YangParamUtils.h"

using namespace Mplane;
using namespace std;

const unsigned VENDOR_FAULT(1000) ;

/*!
 * \brief A class to catch the send notification message from OramFm
 */
class CatchNotification : public ISendNotification
{
public:
	YangResult_E sendNotification(const std::string & xpath, std::shared_ptr<YangParams> params) final override
	{
		LastParams = params;
		return YangResult_E::OK;
	}
	std::shared_ptr<YangParams> LastParams;
};

class TestOranFm: public ::testing::Test
{
public:
	TestOranFm()
	: mWarningAlarm("TestWarning", "", IAlarm::ALARM_WARNING)
	, mTwoAffectedAlarm("TestTwoAffected", "", IAlarm::ALARM_MAJOR)
	, mNoAffectedAlarm("TestNoAffected", "", IAlarm::ALARM_CRITICAL)
	, mNonConfigAlarm("nonConfig", "", IAlarm::ALARM_MAJOR)
	{	}

	virtual void SetUp()
	{
		mWarningAlarm.setStatus(true);
		mTwoAffectedAlarm.setStatus(true);
		mNoAffectedAlarm.setStatus(true);
		mNonConfigAlarm.setStatus(true);
		mCallback = make_shared<LeafContainer>();
		mFault = make_shared<OranFm> (mNotificationTray, mCallback);
		mNotificationTray.LastParams.reset();
	}

	virtual void TearDown()
	{
	}
protected:
	shared_ptr<ILeafContainer> mCallback;
	shared_ptr<OranFm> mFault;

	CatchNotification mNotificationTray;
	Alarm mWarningAlarm;
	Alarm mTwoAffectedAlarm;
	Alarm mNoAffectedAlarm;
	Alarm mNonConfigAlarm;
	const size_t mFaultIdIndex = 0;
	const size_t mFauldSourceIndex = 1;
	const size_t mAffectedObjectsIndex = 2;
	const size_t mFaultSeverityIndex = 3;
	const size_t mIsClearedIndex = 4;
	const size_t mFaultTextIndex = 5;
	const size_t mEventTimeIndex = 6;

private:
};

/*!
 * \test Various cases of add and removing alarms. Check that correct number of alarms are there
 */
TEST_F(TestOranFm, Update_AddRemoveAlarms)
{
	// Add 2 different alarms, but add one of them twice
	mFault->update(mNonConfigAlarm);
	mFault->update(mNonConfigAlarm);
	mFault->update(mTwoAffectedAlarm);

//std::cerr << "LEAF contents:" << std::endl ;
//mCallback->dump() ;

	// We should see only 2 alarms
	EXPECT_EQ(2UL, mCallback->contents().size());

	// Remove one of the alarms, check it vanishes
	mNonConfigAlarm.setStatus(false);		// Alarm is inactive
	mFault->update(mNonConfigAlarm);
	EXPECT_EQ(1UL, mCallback->contents().size());

	// Remove it again, no effect because not there anyway
	mFault->update(mNonConfigAlarm);
	EXPECT_EQ(1UL, mCallback->contents().size());

	// Add a warning alarm, warnings should be ignored
	mFault->update(mWarningAlarm);
	EXPECT_EQ(1UL, mCallback->contents().size());
}

/*
 * \test Add an alarm that is in the config file.
 * When I do an <rpc><get>, does the alarm fill in all the details correctly?
 */
TEST_F(TestOranFm, Update_NewAlarmInGetList)
{
	// Add a new alarm
	mFault->update(mTwoAffectedAlarm);

	// Retrieve the alarm
	auto allContents = mCallback->contents();
	auto addedContents = allContents[0];
	auto contents = addedContents->contents();

	// Check alarm as expected
	EXPECT_EQ(7UL, contents.size());
	EXPECT_STREQ("fault-id", contents[mFaultIdIndex]->name().c_str());
	EXPECT_STREQ("fault-source", contents[mFauldSourceIndex]->name().c_str());
	EXPECT_TRUE(contents[mFauldSourceIndex]->value().length() >= 1);					// Fault source cannot be an empty string

	// Should be 1 affected objects
	EXPECT_STREQ("affected-objects", contents[mAffectedObjectsIndex]->name().c_str());
	auto affectedObjectList = contents[mAffectedObjectsIndex]->contents();
	EXPECT_EQ(1UL, affectedObjectList.size());
	EXPECT_STREQ("Unknown", affectedObjectList[0]->value().c_str());

	// fault - severity = major
	EXPECT_STREQ("fault-severity", contents[mFaultSeverityIndex]->name().c_str());
	EXPECT_STREQ("MAJOR", contents[mFaultSeverityIndex]->value().c_str());

	// is-cleared = false
	EXPECT_STREQ("is-cleared", contents[mIsClearedIndex]->name().c_str());
	EXPECT_STREQ("false", contents[mIsClearedIndex]->value().c_str());

	EXPECT_STREQ("fault-text", contents[mFaultTextIndex]->name().c_str());
	EXPECT_STREQ("event-time", contents[mEventTimeIndex]->name().c_str());
}


/*
 * \test A warning alarm does NOT send notification
 */
TEST_F(TestOranFm, Update_WarningNoNotify)
{
	mFault->update(mWarningAlarm);
	auto yangParams =  mNotificationTray.LastParams;
	EXPECT_EQ(nullptr,  yangParams.get());
}

/*
 * \test When a new alarm appears or vanishes, sendNotification is called
 */

TEST_F(TestOranFm, Update_Notifies)
{
	{
	// Add new alarm that is not in the config file
	mFault->update(mNonConfigAlarm);
	auto yangParams =  mNotificationTray.LastParams;
	ASSERT_NE(nullptr,  yangParams.get());
	EXPECT_EQ(7UL, yangParams->getNumParams());
	EXPECT_TRUE(yangParams->getString(mFauldSourceIndex).length() > 1);		// some fault text still expected
	}

	{
	// New alarm in with 2 affected objects
	mNotificationTray.LastParams.reset();
	mFault->update(mTwoAffectedAlarm);
	auto yangParams =  mNotificationTray.LastParams;

	std::string error ;

	EXPECT_EQ(std::to_string(mTwoAffectedAlarm.getId() + VENDOR_FAULT), YangParamUtils::toString(yangParams->getParam(mFaultIdIndex), error));
	EXPECT_EQ("MAJOR", yangParams->getString(mFaultSeverityIndex));
	EXPECT_EQ(7UL, yangParams->getNumParams());								// 1 affected objects
	EXPECT_EQ(false, yangParams->getBool(mIsClearedIndex));				// New alarms not cleared
	}

	{
	// Clearing alarm sends a notification
	mTwoAffectedAlarm.setStatus(false);
	mNotificationTray.LastParams.reset();
	mFault->update(mTwoAffectedAlarm);
	auto yangParams =  mNotificationTray.LastParams;
	EXPECT_EQ("MAJOR", yangParams->getString(mFaultSeverityIndex));		// Is fault severity correct?
	EXPECT_EQ(7UL, yangParams->getNumParams());								// 1 affected objects
	EXPECT_EQ(true, yangParams->getBool(mIsClearedIndex));				// This alarm is cleared
	}

}
/*
 * \test <rpc><get> has the details filled in correctly?
 */
TEST_F(TestOranFm, Update_FillsInDetails)
{
	// Add a new alarm
	mFault->update(mTwoAffectedAlarm);

	// Retrieve the alarm
	auto allContents = mCallback->contents();
	auto addedContents = allContents[0];
	auto contents = addedContents->contents();

	// Check alarm as expected
	EXPECT_EQ(7UL, contents.size());
	EXPECT_STREQ("fault-id", contents[mFaultIdIndex]->name().c_str());
	EXPECT_EQ(std::to_string(mTwoAffectedAlarm.getId() + VENDOR_FAULT), contents[mFaultIdIndex]->value());

	EXPECT_STREQ("fault-source", contents[mFauldSourceIndex]->name().c_str());

	EXPECT_STREQ("affected-objects", contents[mAffectedObjectsIndex]->name().c_str());
	auto affectedObjectList = contents[mAffectedObjectsIndex]->contents();
	EXPECT_EQ(1UL, affectedObjectList.size());

	EXPECT_STREQ("fault-severity", contents[mFaultSeverityIndex]->name().c_str());
	EXPECT_STREQ("MAJOR", contents[mFaultSeverityIndex]->value().c_str());

	EXPECT_STREQ("false", contents[mIsClearedIndex]->value().c_str());
}

/*
 * \test What if FaultConfig.xml is missing?
 * \details I should still get alarm data back, but no details from config file
 */
TEST_F(TestOranFm, Update_ConfigFileMissing)
{
	OranFm fault(mNotificationTray, mCallback, true);
	// Add a new alarm
	fault.update(mTwoAffectedAlarm);

	// Retrieve the alarm
	auto allContents = mCallback->contents();
	auto addedContents = allContents[0];
	auto contents = addedContents->contents();

	// Should still have 7 entries in alarm, but no affected objects
	EXPECT_EQ(7UL, contents.size());
	auto affectedObjectList = contents[mAffectedObjectsIndex]->contents();
	EXPECT_EQ(std::to_string(mTwoAffectedAlarm.getId() + VENDOR_FAULT), contents[mFaultIdIndex]->value());
	EXPECT_EQ(1UL, affectedObjectList.size());
}
