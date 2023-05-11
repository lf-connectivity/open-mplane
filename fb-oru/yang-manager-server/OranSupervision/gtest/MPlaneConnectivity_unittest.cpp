/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MPlaneConnectivity_unittest.cpp
 * \brief     Google Test of M-Plane connectivity service
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the M-Plane connectivity service.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "MPlaneConnectivityService.h"

using namespace Mplane;

#define SESSION1 0
#define SESSION2 1
#define SESSION3 2

//=============================================================================================================
// Command Objects
//=============================================================================================================
class CmdDef
{
public:
	enum class CmdType
	{
		CHK_STATE,
		REGISTER,
		CHK_TIMER,
		SET_INTERVAL,
		CHK_INTERVAL,
		SERVICE,
		KICK,
		CHK_SUPERVISOR,
		CHK_NOTIF_COUNT,
		CHK_SESSION_COUNT,
		ADD_SESSION,
		REMOVE_SESSION,
	};

	CmdDef(CmdType type, ReturnType::State retVal) :
		mType(type), mRetVal(retVal) {}
	virtual ~CmdDef() {}

	virtual CmdType type() const { return mType; }

	virtual ReturnType::State retVal() const { return mRetVal; }

	virtual std::string typeStr() const
	{
		std::string typeStr;

		switch(mType)
		{
			case CmdType::CHK_STATE:         typeStr = "CHK_STATE";         break;
			case CmdType::REGISTER:          typeStr = "REGISTER";          break;
			case CmdType::CHK_TIMER:         typeStr = "CHK_TIMER";         break;
			case CmdType::SET_INTERVAL:      typeStr = "SET_INTERVAL";      break;
			case CmdType::CHK_INTERVAL:      typeStr = "CHK_INTERVAL";      break;
			case CmdType::SERVICE:           typeStr = "SERVICE";           break;
			case CmdType::KICK:              typeStr = "KICK";              break;
			case CmdType::CHK_SUPERVISOR:    typeStr = "CHK_SUPERVISOR";    break;
			case CmdType::CHK_NOTIF_COUNT:   typeStr = "CHK_NOTIF_COUNT";   break;
			case CmdType::CHK_SESSION_COUNT: typeStr = "CHK_SESSION_COUNT"; break;
			case CmdType::ADD_SESSION:       typeStr = "ADD_SESSION";       break;
			case CmdType::REMOVE_SESSION:    typeStr = "REMOVE_SESSION";    break;
			default: break;
		}
		return typeStr;
	}

protected:

private:
	const CmdType mType;
	ReturnType::State mRetVal;
};

class CmdCheckState : public CmdDef
{
public:
	CmdCheckState(ReturnType::State retVal, const MPlaneConnectivityService::ServiceState_T & state)
		: CmdDef(CmdDef::CmdType::CHK_STATE, retVal)
		, mState(state)
	{
	}
	virtual ~CmdCheckState() {}

	IMPlaneConnectivityService::ServiceState_T getState() const { return mState; }

protected:

private:
	IMPlaneConnectivityService::ServiceState_T mState;
};

class CmdRegisterNotify : public CmdDef
{
public:
	CmdRegisterNotify(ReturnType::State retVal, IMPlaneConnectivityService::NotifTimerExpiredNotifyFunc func)
		: CmdDef(CmdDef::CmdType::REGISTER, retVal)
		, mFunc(func)
	{
	}
	virtual ~CmdRegisterNotify() {}

	IMPlaneConnectivityService::NotifTimerExpiredNotifyFunc func() const { return mFunc; }

protected:

private:
	IMPlaneConnectivityService::NotifTimerExpiredNotifyFunc mFunc;
};

class CmdCheckTimer : public CmdDef
{
public:
	CmdCheckTimer(ReturnType::State retVal, UINT16 timer)
		: CmdDef(CmdDef::CmdType::CHK_TIMER, retVal)
		, mTimer(timer)
	{
	}
	virtual ~CmdCheckTimer() {}

	UINT16 getTimer() const { return mTimer; }

protected:

private:
	UINT16 mTimer;
};

class CmdSetInterval : public CmdDef
{
public:
	CmdSetInterval(ReturnType::State retVal, UINT16 interval)
		: CmdDef(CmdDef::CmdType::SET_INTERVAL, retVal)
		, mInterval(interval)
	{
	}
	virtual ~CmdSetInterval() {}

	UINT16 getInterval() const { return mInterval; }

protected:

private:
	UINT16 mInterval;
};

class CmdCheckInterval : public CmdDef
{
public:
	CmdCheckInterval(ReturnType::State retVal, UINT16 interval)
		: CmdDef(CmdDef::CmdType::CHK_INTERVAL, retVal)
		, mInterval(interval)
	{
	}
	virtual ~CmdCheckInterval() {}

	UINT16 getInterval() const { return mInterval; }

protected:

private:
	UINT16 mInterval;
};

class CmdService : public CmdDef
{
public:
	CmdService(ReturnType::State retVal)
		: CmdService(retVal, 1) {}
	CmdService(ReturnType::State retVal, UINT32 count)
		: CmdDef(CmdDef::CmdType::SERVICE, retVal)
		, mCount(count)
	{
	}
	virtual ~CmdService() {}

	UINT32 getCount() const { return mCount; }

protected:

private:
	UINT32 mCount;
};

class CmdKick : public CmdDef
{
public:
	CmdKick(ReturnType::State retVal,
	        UINT32 session,
	        UINT16 interval,
	        UINT16 guard)
		: CmdDef(CmdDef::CmdType::KICK, retVal)
		, mSession(session)
		, mInterval(interval)
		, mGuard(guard)
		{}
	virtual ~CmdKick() {}

	UINT32 getSession() const { return mSession; }
	UINT16 getInterval() const { return mInterval; }
	UINT16 getGuard() const { return mGuard; }

protected:

private:
	UINT32 mSession;
	UINT16 mInterval;
	UINT16 mGuard;
};

class CmdCheckSupervisor : public CmdDef
{
public:
	CmdCheckSupervisor(ReturnType::State retVal,
	                   UINT32 session,
	                   bool expired)
		: CmdDef(CmdDef::CmdType::CHK_SUPERVISOR, retVal)
		, mSession(session)
		, mExpired(expired)
	{
	}
	virtual ~CmdCheckSupervisor() {}

	UINT32 getSession() const { return mSession; }
	bool isSupervisorExpired() const { return mExpired; }

protected:

private:
	UINT32 mSession;
	bool mExpired;

};

class CmdCheckNotifCount : public CmdDef
{
public:
	CmdCheckNotifCount(ReturnType::State retVal, UINT32 notifCount)
		: CmdDef(CmdDef::CmdType::CHK_NOTIF_COUNT, retVal)
		, mNotifCount(notifCount)
	{
	}
	virtual ~CmdCheckNotifCount() {}

	UINT16 getNotifCount() const { return mNotifCount; }

protected:

private:
	UINT32 mNotifCount;

};

class CmdCheckSessionCount : public CmdDef
{
public:
	CmdCheckSessionCount(ReturnType::State retVal, UINT16 sessionCount)
		: CmdDef(CmdDef::CmdType::CHK_SESSION_COUNT, retVal)
		, mSessionCount(sessionCount)
	{
	}
	virtual ~CmdCheckSessionCount() {}

	UINT16 getSessionCount() const { return mSessionCount; }

protected:

private:
	UINT32 mSessionCount;

};

class CmdAddSession : public CmdDef
{
public:
	CmdAddSession(ReturnType::State retVal)
		: CmdDef(CmdDef::CmdType::ADD_SESSION, retVal)
	{
	}
	virtual ~CmdAddSession() {}

protected:

private:

};

class CmdRemoveSession : public CmdDef
{
public:
	CmdRemoveSession(ReturnType::State retVal)
		: CmdDef(CmdDef::CmdType::REMOVE_SESSION, retVal)
	{
	}
	virtual ~CmdRemoveSession() {}

protected:

private:

};

class MPlaneConnectivityService_Tester : public MPlaneConnectivityService
{
public:
	MPlaneConnectivityService_Tester()
		: MPlaneConnectivityService()
	{
		Loggable::setLevel(ILoggable::LogDebugLevel::LOG_DEBUG_VERBOSE);
	}
	virtual ~MPlaneConnectivityService_Tester() {}

	virtual int service() override
	{
		return MPlaneConnectivityService::service();
	}

	//-------------------------------------------------------------------------------------------------------------
	virtual std::vector<UINT32> getSessionIds()
	{
		return mSessionIds;
	}

	//-------------------------------------------------------------------------------------------------------------
	virtual UINT32 getSessionCount()
	{
		return mSessionIds.size();
	}

	//-------------------------------------------------------------------------------------------------------------
	virtual void addSession()
	{
		mSessionIds.push_back(mSessionIds.size());
	}

	//-------------------------------------------------------------------------------------------------------------
	virtual void removeSession()
	{
		mSessionIds.pop_back();
	}

private:

	std::vector<UINT32> mSessionIds;

};

class TestDef
{
public:
	TestDef(const std::string & name, bool dispName, bool dispInfo, std::vector<std::shared_ptr<CmdDef>> cmdDefs)
		: mName(name)
		, mDispName(dispName)
		, mDispInfo(dispInfo)
		, mCmdDefs(cmdDefs)
	{
	}
	virtual ~TestDef() {}

	void runTest()
	{
		if (mDispName || mDispInfo)
		{
			std::cout << std::endl;
			std::cout << "TEST: '" << mName << "'" << std::endl;
		}

		std::unique_ptr<MPlaneConnectivityService_Tester> MPlane(std::make_unique<MPlaneConnectivityService_Tester>());

		// Run each command in turn
		for (auto testCmd : mCmdDefs)
		{
			std::string cmdStr;

			switch (testCmd->type())
			{
				case CmdDef::CmdType::CHK_STATE:
					{
					auto cmd(std::dynamic_pointer_cast<CmdCheckState>(testCmd));
					cmdStr += " State='" + MPlaneConnectivityService::toStateString(cmd->getState()) + "'";
					EXPECT_EQ(MPlane->getState(), cmd->getState());
					}
					break;
				case CmdDef::CmdType::REGISTER:
					{
					auto cmd(std::dynamic_pointer_cast<CmdRegisterNotify>(testCmd));
					MPlane->registerNotifTimerExpired(cmd->func());
					}
					break;
				case CmdDef::CmdType::CHK_TIMER:
					{
					auto cmd(std::dynamic_pointer_cast<CmdCheckTimer>(testCmd));
					cmdStr += " Timer='" + std::to_string(cmd->getTimer()) + "'";
					EXPECT_EQ(MPlane->getTimer(), cmd->getTimer());
					}
					break;
				case CmdDef::CmdType::SET_INTERVAL:
					{
					auto cmd(std::dynamic_pointer_cast<CmdSetInterval>(testCmd));
					cmdStr += " Interval='" + std::to_string(cmd->getInterval()) + "'";
					EXPECT_EQ(MPlane->setInterval(cmd->getInterval()), cmd->retVal());
					}
					break;
				case CmdDef::CmdType::CHK_INTERVAL:
					{
					auto cmd(std::dynamic_pointer_cast<CmdCheckInterval>(testCmd));
					cmdStr += " Interval='" + std::to_string(cmd->getInterval()) + "'";
					EXPECT_EQ(MPlane->getInterval(), cmd->getInterval());
					}
					break;
				case CmdDef::CmdType::SERVICE:
					{
					auto cmd(std::dynamic_pointer_cast<CmdService>(testCmd));
					UINT32 count = cmd->getCount();
					while (count--)
					{
						MPlane->service();
					}
					}
					break;
				case CmdDef::CmdType::KICK:
					{
					auto cmd(std::dynamic_pointer_cast<CmdKick>(testCmd));
					std::string updateAt;
					cmdStr += " Session='" + std::to_string(cmd->getSession()) + "'";
					cmdStr += " Interval='" + std::to_string(cmd->getInterval()) + "'";
					cmdStr += " Guard='" + std::to_string(cmd->getGuard()) + "'";
					MPlane->kick(cmd->getSession(), cmd->getInterval(), cmd->getGuard(), updateAt);
					}
					break;
				case CmdDef::CmdType::CHK_SUPERVISOR:
					{
					auto cmd(std::dynamic_pointer_cast<CmdCheckSupervisor>(testCmd));
					cmdStr += " Session='" + std::to_string(cmd->getSession()) + "'";
					cmdStr += " SupervisionExpired='" + std::to_string(cmd->isSupervisorExpired()) + "'";
					EXPECT_EQ(MPlane->isSupervisorExpired(cmd->getSession()), cmd->isSupervisorExpired());
					}
					break;
				case CmdDef::CmdType::CHK_NOTIF_COUNT:
					{
					auto cmd(std::dynamic_pointer_cast<CmdCheckNotifCount>(testCmd));
					cmdStr += " NotifCount='" + std::to_string(cmd->getNotifCount()) + "'";
					EXPECT_EQ(getNotifCount(), cmd->getNotifCount());
					}
					break;
				case CmdDef::CmdType::CHK_SESSION_COUNT:
					{
					auto cmd(std::dynamic_pointer_cast<CmdCheckSessionCount>(testCmd));
					cmdStr += " SessionCount='" + std::to_string(cmd->getSessionCount()) + "'";
					EXPECT_EQ(MPlane->getSessionCount(), cmd->getSessionCount());
					}
					break;
				case CmdDef::CmdType::ADD_SESSION:
					{
					auto cmd(std::dynamic_pointer_cast<CmdAddSession>(testCmd));
					UINT32 expectedCount = (MPlane->getSessionCount()+1);
					MPlane->addSession();
					EXPECT_EQ(MPlane->getSessionCount(), expectedCount);
					}
					break;
				case CmdDef::CmdType::REMOVE_SESSION:
					{
					auto cmd(std::dynamic_pointer_cast<CmdRemoveSession>(testCmd));
					UINT32 expectedCount = MPlane->getSessionCount();
					if (expectedCount)
					{
						expectedCount--;
					}
					MPlane->removeSession();
					EXPECT_EQ(MPlane->getSessionCount(), expectedCount);
					}
					break;
				default:
					std::cerr << "[error] Unknown CmdType ID - '" << testCmd->typeStr() << "'" << std::endl;
					break;
			}
			if (mDispInfo)
			{
				std::string retStr(" Return='RT" + std::string(ReturnType::getState(testCmd->retVal())) + "'");
				std::cout << "  CMD[" << std::setw(8) << std::left << testCmd->typeStr() << "]" << retStr << cmdStr << std::endl;
			}
		}
		resetNotifCount();
	}

	static void notificationTimerExpired()
	{
		std::cout << "\t\t *** Notification timer has expired! ***" << std::endl;
		mNotifCount++;
	}

	static UINT32 getNotifCount()
	{
		return mNotifCount;
	}

	static void resetNotifCount()
	{
		mNotifCount = 0;
	}

private:
	const std::string mName;
	bool mDispName;
	bool mDispInfo;
	std::vector<std::shared_ptr<CmdDef>> mCmdDefs;
	static UINT32 mNotifCount;
};
UINT32 TestDef::mNotifCount = 0;

//===================================================================================================================
class MPlaneConnectivityServiceTests : public ::testing::Test
{
public:
	MPlaneConnectivityServiceTests() {}
	virtual ~MPlaneConnectivityServiceTests() {}

	/*! @brief Setup the test
	 */
	virtual void SetUp()
	{
		const ::testing::TestInfo* const test_info =
		  ::testing::UnitTest::GetInstance()->current_test_info();

		std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
		std::cout << test_info->name() << " - START" <<  std::endl;
	}

	/*! @brief Tear down the test
	 */
	virtual void TearDown()
	{
	}

protected:

private:

};

//=============================================================================================================
// TESTS
//=============================================================================================================
#define DEFAULT_NOTIF_INTERVAL  60

//-------------------------------------------------------------------------------------------------------------
TEST(MPlaneConnectivityService, Initialise)
{
	const bool dispTestName = true;
	const bool dispTestInfo = true;

	std::vector<TestDef> testData
	{
		{
			"Initialise then Register",
			dispTestName, dispTestInfo,
			{
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::UNINIT ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Initialise
				std::make_shared<CmdSetInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Register
				std::make_shared<CmdRegisterNotify>( ReturnType::State::RT_OK, TestDef::notificationTimerExpired ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Service - Handle initial expiry
				std::make_shared<CmdService>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL-10)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL-20)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL-30)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL-40)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL-50)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 2 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL - 10)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 2 ),
			},
		},
		{
			"Register then Initialise",
			dispTestName, dispTestInfo,
			{
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::UNINIT ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Register
				std::make_shared<CmdRegisterNotify>( ReturnType::State::RT_OK, TestDef::notificationTimerExpired ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::UNINIT ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Initialise
				std::make_shared<CmdSetInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Service - Handle initial expiry
				std::make_shared<CmdService>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL-10)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL-20)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL-30)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL-40)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL-50)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 2 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, (DEFAULT_NOTIF_INTERVAL - 10)),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 2 ),
			},
		},
	};
	// Run each test in turn
	for (auto test : testData)
	{
		test.runTest();
	}
}

//-------------------------------------------------------------------------------------------------------------
TEST(MPlaneConnectivityService, Notifications)
{
	const bool dispTestName = true;
	const bool dispTestInfo = true;

	std::vector<TestDef> testData
	{
		{
			"Notifications 10",
			dispTestName, dispTestInfo,
			{
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::UNINIT ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Initialise
				std::make_shared<CmdSetInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Register
				std::make_shared<CmdRegisterNotify>( ReturnType::State::RT_OK, TestDef::notificationTimerExpired ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Service - Handle initial expiry
				std::make_shared<CmdService>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Add session
				std::make_shared<CmdAddSession>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Kick - Notification (x10), No supervision
				std::make_shared<CmdKick>( ReturnType::State::RT_OK, SESSION1, 10, 0),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 2 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 3 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 4 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 5 ),
			},
		},
		{
			"Notifications 10 -> 20",
			dispTestName, dispTestInfo,
			{
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::UNINIT ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Initialise
				std::make_shared<CmdSetInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Register
				std::make_shared<CmdRegisterNotify>( ReturnType::State::RT_OK, TestDef::notificationTimerExpired ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Service - Handle initial expiry
				std::make_shared<CmdService>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Add session
				std::make_shared<CmdAddSession>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Kick - Notification (x10), No supervision
				std::make_shared<CmdKick>( ReturnType::State::RT_OK, SESSION1, 10, 0),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 2 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 3 ),

				// Kick - Notification (x20), No supervision
				std::make_shared<CmdKick>( ReturnType::State::RT_OK, SESSION1, 20, 0),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 20 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 3 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 20 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 20 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 4 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 20 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 4 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 20 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 20 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 5 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 20 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 5 ),
			},
		},
	};
	// Run each test in turn
	for (auto test : testData)
	{
		test.runTest();
	}
}

//-------------------------------------------------------------------------------------------------------------
TEST(MPlaneConnectivityService, Supervision)
{
	const bool dispTestName = true;
	const bool dispTestInfo = true;

	std::vector<TestDef> testData
	{
		{
			"Supervision 10",
			dispTestName, dispTestInfo,
			{
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::UNINIT ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Initialise
				std::make_shared<CmdSetInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Register
				std::make_shared<CmdRegisterNotify>( ReturnType::State::RT_OK, TestDef::notificationTimerExpired ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 0 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 0 ),

				// Service - Handle initial expiry
				std::make_shared<CmdService>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Add session
				std::make_shared<CmdAddSession>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, DEFAULT_NOTIF_INTERVAL ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Kick - Notification (x10), Guard (x5)
				std::make_shared<CmdKick>( ReturnType::State::RT_OK, SESSION1, 10, 5),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 1 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 2 ),

				// Kick - Notification (x10), Guard (x5)
				std::make_shared<CmdKick>( ReturnType::State::RT_OK, SESSION1, 10, 5),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 2 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 3 ),

				// Kick - Notification (x10), Guard (x5)
				std::make_shared<CmdKick>( ReturnType::State::RT_OK, SESSION1, 10, 5),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 3 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 4 ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 5 ),

				// Watchdog expired
				std::make_shared<CmdCheckSupervisor>( ReturnType::State::RT_OK, SESSION1, true ),

				// Kick (Restart watchdog) - Notification (x10), Guard (x5)
				std::make_shared<CmdKick>( ReturnType::State::RT_OK, SESSION1, 10, 5),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 5 ),
				std::make_shared<CmdCheckSupervisor>( ReturnType::State::RT_OK, SESSION1, false ),

				// Service (x10)
				std::make_shared<CmdService>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, MPlaneConnectivityService::ServiceState_T::RUNNING ),
				std::make_shared<CmdCheckTimer>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckInterval>( ReturnType::State::RT_OK, 10 ),
				std::make_shared<CmdCheckNotifCount>( ReturnType::State::RT_OK, 6 ),
			},
		},
	};
	// Run each test in turn
	for (auto test : testData)
	{
		test.runTest();
	}
}
