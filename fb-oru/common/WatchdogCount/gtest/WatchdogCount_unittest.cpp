/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WatchdogCount_unittest.cpp
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
#include <memory>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <map>
#include <vector>

#include <gtest/gtest.h>

#include "WatchdogCount.h"

using namespace Mplane ;

//=============================================================================================================
// DEFINITIONS
//=============================================================================================================

//=============================================================================================================
// Watchdog Command Objects
//=============================================================================================================
class CmdDef
{
public:
	enum class CmdType
	{
		CHKSTATE,
		INIT1,
		INIT2,
		INIT3,
		REGISTER,
		START,
		STOP,
		TICK,
		KICK,
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
			case CmdType::CHKSTATE: typeStr = "CHKSTATE"; break;
			case CmdType::INIT1:    typeStr = "INIT1";    break;
			case CmdType::INIT2:    typeStr = "INIT2";    break;
			case CmdType::INIT3:    typeStr = "INIT3";    break;
			case CmdType::REGISTER: typeStr = "REGISTER"; break;
			case CmdType::START:    typeStr = "START";    break;
			case CmdType::STOP:     typeStr = "STOP";     break;
			case CmdType::TICK:     typeStr = "TICK";     break;
			case CmdType::KICK:     typeStr = "KICK";     break;
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
	CmdCheckState(ReturnType::State retVal, const WatchdogCount::WatchdogState_T & expectedState) :
		CmdDef(CmdDef::CmdType::CHKSTATE, retVal), mExpState(expectedState) {}
	virtual ~CmdCheckState() {}

	WatchdogCount::WatchdogState_T getState() const { return mExpState; }

protected:

	WatchdogCount::WatchdogState_T mExpState;

private:

};

class CmdInit1 : public CmdDef
{
public:
	CmdInit1(ReturnType::State retVal, bool freeRun) :
		CmdDef(CmdDef::CmdType::INIT1, retVal), mFreeRun(freeRun) {}
	virtual ~CmdInit1() {}

	bool freeRun() const { return mFreeRun; }

protected:
	CmdInit1(CmdDef::CmdType type, ReturnType::State retVal, bool freeRun) :
		CmdDef(type, retVal), mFreeRun(freeRun) {}

	bool mFreeRun;

private:

};

class CmdInit2 : public CmdInit1
{
public:
	CmdInit2(ReturnType::State retVal, bool freeRun, uint32_t cntMax) :
		CmdInit1(CmdDef::CmdType::INIT2, retVal, freeRun), mCntMax(cntMax) { }
	virtual ~CmdInit2() {}

	uint32_t cntMax() const { return mCntMax; }

protected:
	CmdInit2(CmdDef::CmdType type, ReturnType::State retVal, bool freeRun, uint32_t cntMax) :
		CmdInit1(type, retVal, freeRun), mCntMax(cntMax) {}

	uint32_t mCntMax;

private:

};

class CmdInit3 : public CmdInit2
{
public:
	CmdInit3(ReturnType::State retVal, bool freeRun, uint32_t cntMin, uint32_t cntMax) :
		CmdInit2(CmdDef::CmdType::INIT3, retVal, freeRun, cntMax), mCntMin(cntMin) {}
	virtual ~CmdInit3() {}

	uint32_t cntMin() const { return mCntMin; }

protected:
	uint32_t mCntMin;

private:

};

class CmdReg : public CmdDef
{
public:
	CmdReg(ReturnType::State retVal, WatchdogCount::ExpiryFunc func) :
		CmdDef(CmdDef::CmdType::REGISTER, retVal), mFunc(func) {}
	virtual ~CmdReg() {}

	WatchdogCount::ExpiryFunc func() const { return mFunc; }

protected:
	WatchdogCount::ExpiryFunc mFunc;

private:

};

class CmdStart : public CmdDef
{
public:
	CmdStart(ReturnType::State retVal, uint32_t cntVal) :
		CmdDef(CmdDef::CmdType::START, retVal), mCntVal(cntVal) {}
	~CmdStart() {}

	uint32_t cntVal() const { return mCntVal; }

protected:
	uint32_t mCntVal;

private:

};

class CmdStop : public CmdDef
{
public:
	CmdStop(ReturnType::State retVal) :
		CmdDef(CmdDef::CmdType::STOP, retVal) {}
	~CmdStop() {}

protected:

private:

};

class CmdKick : public CmdDef
{
public:
	CmdKick(ReturnType::State retVal) :
		CmdDef(CmdDef::CmdType::KICK, retVal) {}
	~CmdKick() {}

protected:

private:

};

class CmdTick : public CmdDef
{
public:
	CmdTick(ReturnType::State retVal) :
		CmdDef(CmdDef::CmdType::TICK, retVal) {}
	~CmdTick() {}

protected:

private:

};

class TestDef
{
public:
	TestDef(const std::string & name, bool dispName, bool dispInfo, std::vector<std::shared_ptr<CmdDef>> cmdDefs) :
		mName(name), mDispName(dispName), mDispInfo(dispInfo), mCmdDefs(cmdDefs) {}
	~TestDef() {}

	void runTest()
	{
		std::unique_ptr<WatchdogCount> watchdog(std::make_unique<WatchdogCount>());

		if (mDispName || mDispInfo)
		{
			std::cout << std::endl;
			std::cout << "TEST: '" << mName << "'" << std::endl;
		}

		// Run each command in turn
		for (auto testCmd : mCmdDefs)
		{
			uint32_t preCmdCount = watchdog->getCounter();
			std::string cmdStr;

			switch (testCmd->type())
			{
				case CmdDef::CmdType::CHKSTATE:
					{
					auto cmd(std::dynamic_pointer_cast<CmdCheckState>(testCmd));
					cmdStr += " State='" + WatchdogCount::toStateString(cmd->getState()) + "'";
					EXPECT_EQ(watchdog->getState(), cmd->getState());
					}
					break;
				case CmdDef::CmdType::INIT1:
					{
					auto cmd(std::dynamic_pointer_cast<CmdInit1>(testCmd));
					cmdStr += " FreeRun='" + std::to_string(cmd->freeRun()) + "'";
					EXPECT_EQ(watchdog->initialise(cmd->freeRun()), cmd->retVal());
					}
					break;
				case CmdDef::CmdType::INIT2:
					{
					auto cmd(std::dynamic_pointer_cast<CmdInit2>(testCmd));
					cmdStr += " FreeRun='" + std::to_string(cmd->freeRun()) + "'";
					cmdStr += " Max='" + std::to_string(cmd->cntMax()) + "'";
					EXPECT_EQ(watchdog->initialise(cmd->cntMax(), cmd->freeRun()), cmd->retVal());
					}
					break;
				case CmdDef::CmdType::INIT3:
					{
					auto cmd(std::dynamic_pointer_cast<CmdInit3>(testCmd));
					cmdStr += " FreeRun='" + std::to_string(cmd->freeRun()) + "'";
					cmdStr += " Min='" + std::to_string(cmd->cntMin()) + "'";
					cmdStr += " Max='" + std::to_string(cmd->cntMax()) + "'";
					EXPECT_EQ(watchdog->initialise(cmd->cntMin(), cmd->cntMax(), cmd->freeRun()), cmd->retVal());
					}
					break;
				case CmdDef::CmdType::REGISTER:
					{
						auto cmd(std::dynamic_pointer_cast<CmdReg>(testCmd));
						EXPECT_EQ(watchdog->registerTimeoutHandler(cmd->func()), cmd->retVal());
					}
					break;
				case CmdDef::CmdType::START:
					{
					auto cmd(std::dynamic_pointer_cast<CmdStart>(testCmd));
					EXPECT_EQ(watchdog->start(cmd->cntVal()), cmd->retVal());
					}
					break;
				case CmdDef::CmdType::STOP:
					{
					auto cmd(std::dynamic_pointer_cast<CmdStop>(testCmd));
					EXPECT_EQ(watchdog->stop(), cmd->retVal());
					}
					break;
				case CmdDef::CmdType::TICK:
					{
					auto cmd(std::dynamic_pointer_cast<CmdTick>(testCmd));
					EXPECT_EQ(watchdog->tick(), cmd->retVal());
					}
					break;
				case CmdDef::CmdType::KICK:
					{
					auto cmd(std::dynamic_pointer_cast<CmdKick>(testCmd));
					EXPECT_EQ(watchdog->kick(), cmd->retVal());
					}
					break;
				default:
					std::cerr << "[error] Unknown CmdType ID - '" << testCmd->typeStr() << "'" << std::endl;
					break;
			}
			if (mDispInfo)
			{
				std::string retStr(" Return='RT" + std::string(ReturnType::getState(testCmd->retVal())) + "'");
				std::string cntStr(" Counter='" + std::to_string(preCmdCount) + "=>" + std::to_string(watchdog->getCounter()) + "'");
				std::cout << "  CMD[" << std::setw(8) << std::left << testCmd->typeStr() << "]" << retStr << cntStr << cmdStr << std::endl;
			}
		}
		watchdog.reset();
	}

	static ReturnType::State expiredHandler1()
	{
		std::cout << "\t\t *** Handler[1] Watchdog has expired! ***" << std::endl;
		return ReturnType::State::RT_OK;
	}
	static ReturnType::State expiredHandler2()
	{
		std::cout << "\t\t *** Handler[2] Watchdog has expired! ***" << std::endl;
		return ReturnType::State::RT_OK;
	}

private:
	const std::string mName;
	bool mDispName;
	bool mDispInfo;
	std::vector<std::shared_ptr<CmdDef>> mCmdDefs;
};

//===================================================================================================================
class WatchdogCountTests : public ::testing::Test
{
public:
	WatchdogCountTests() {}
	virtual ~WatchdogCountTests() {}

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

private:

};

//=============================================================================================================
// TESTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST(WatchdogCount, Initialise)
{
	const bool dispTestName = true;
	const bool dispTestInfo = true;

	std::vector<TestDef> testData
	{
		{
			"Valid, initialise()",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit1>( ReturnType::State::RT_OK, false ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Valid, initialise(Max)",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit2>( ReturnType::State::RT_OK, false, 20 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Valid, initialise(Min, Max)",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 20 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Valid, initialise(Min, Max), Min > 0",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 10, 20 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Valid, initialise(Min, Max), Min == Max",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 10, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Valid, initialise(Min, Max), valid then valid",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 20 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Initialise
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 5, 25 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Invalid, initialise(Max), Max == 0",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit2>( ReturnType::State::RT_SYNTAX_ERROR, false, 0 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::FAULT ),
			},
		},
		{
			"Invalid, initialise(Min, Max), Min == Max == 0",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_SYNTAX_ERROR, false, 0, 0 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::FAULT ),
			},
		},
		{
			"Invalid, initialise(Min, Max), Min > Max",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_SYNTAX_ERROR, false, 20, 0 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::FAULT ),
			},
		},
		{
			"Invalid, initialise(Min, Max), valid then invalid",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 20 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Initialise
				std::make_shared<CmdInit2>( ReturnType::State::RT_SYNTAX_ERROR, false, 0 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::FAULT ),
			},
		},
		{
			"Invalid, initialise(Min, Max), invalid then valid",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit2>( ReturnType::State::RT_SYNTAX_ERROR, false, 0 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::FAULT ),

				// Initialise
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 20 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Invalid, initialise(Min, Max), invalid then invalid",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit2>( ReturnType::State::RT_SYNTAX_ERROR, false, 0 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::FAULT ),

				// Initialise
				std::make_shared<CmdInit2>( ReturnType::State::RT_SYNTAX_ERROR, false, 0 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::FAULT ),
			},
		},
		{
			"Invalid, initialise(), whilst running",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 5 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Initialise
				std::make_shared<CmdInit1>( ReturnType::State::RT_NOT_ALLOWED, false ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
			},
		},
		{
			"Invalid, initialise(Max), whilst running",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 5 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Initialise
				std::make_shared<CmdInit2>( ReturnType::State::RT_NOT_ALLOWED, false, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
			},
		},
		{
			"Invalid, initialise(Min, Max), whilst running",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 5 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Initialise
				std::make_shared<CmdInit3>( ReturnType::State::RT_NOT_ALLOWED, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
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
TEST(WatchdogCount, Operational)
{
	const bool dispTestName = true;
	const bool dispTestInfo = true;

	std::vector<TestDef> testData
	{
		{
			"Valid, Operational",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Register
				std::make_shared<CmdReg>( ReturnType::State::RT_OK, TestDef::expiredHandler1 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 5 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Kick
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdKick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Kick
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdKick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Kick
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdKick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Kick
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdKick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Kick
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdKick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Kick
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdKick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Kick
				std::make_shared<CmdKick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Stop
				std::make_shared<CmdStop>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
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
TEST(WatchdogCount, InvalidUninitialised)
{
	const bool dispTestName = true;
	const bool dispTestInfo = true;

	std::vector<TestDef> testData
	{
		{
			"Invalid, uninit=>start",
			dispTestName, dispTestInfo,
			{
				// Uninitialised
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_NOT_INITIALISED, 4 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
			},
		},
		{
			"Invalid, uninit=>stop",
			dispTestName, dispTestInfo,
			{
				// Uninitialised
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),

				// Stop
				std::make_shared<CmdStop>( ReturnType::State::RT_NOT_INITIALISED ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
			},
		},
		{
			"Invalid, uninit=>tick",
			dispTestName, dispTestInfo,
			{
				// Uninitialised
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),

				// Tick
				std::make_shared<CmdTick>( ReturnType::State::RT_NOT_INITIALISED ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
			},
		},
		{
			"Invalid, uninit=>kick",
			dispTestName, dispTestInfo,
			{
				// Uninitialised
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),

				// Kick
				std::make_shared<CmdKick>( ReturnType::State::RT_NOT_INITIALISED ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
			},
		},
		{
			"Invalid, uninit=>register",
			dispTestName, dispTestInfo,
			{
				// Uninitialised
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),

				// Register
				std::make_shared<CmdReg>( ReturnType::State::RT_NOT_INITIALISED, nullptr ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
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
TEST(WatchdogCount, InvalidNoStart)
{
	const bool dispTestName = true;
	const bool dispTestInfo = true;

	std::vector<TestDef> testData
	{
		{
			"Invalid, init=>stop",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Stop
				std::make_shared<CmdStop>( ReturnType::State::RT_INUSE ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Invalid, init=>tick",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Tick
				std::make_shared<CmdTick>( ReturnType::State::RT_NOT_ALLOWED ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Invalid, init=>kick",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Kick
				std::make_shared<CmdKick>( ReturnType::State::RT_NOT_ALLOWED ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
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
TEST(WatchdogCount, InvalidRegistration)
{
	const bool dispTestName = true;
	const bool dispTestInfo = true;

	std::vector<TestDef> testData
	{
		{
			"Invalid, register null",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Register
				std::make_shared<CmdReg>( ReturnType::State::RT_SYNTAX_ERROR, nullptr ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Invalid, register whilst running",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 5 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Register
				std::make_shared<CmdReg>( ReturnType::State::RT_NOT_ALLOWED, TestDef::expiredHandler1 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
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
TEST(WatchdogCount, WatchdogExpired)
{
	const bool dispTestName = true;
	const bool dispTestInfo = true;

	std::vector<TestDef> testData
	{
		{
			"Expiry, no registered handlers",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 5 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_NOT_INITIALISED ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Stop
				std::make_shared<CmdStop>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Expiry, single handler",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Register
				std::make_shared<CmdReg>( ReturnType::State::RT_OK, TestDef::expiredHandler1 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 5 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Stop
				std::make_shared<CmdStop>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
			},
		},
		{
			"Expiry, multiple handlers",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, false, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Register
				std::make_shared<CmdReg>( ReturnType::State::RT_OK, TestDef::expiredHandler1 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Register
				std::make_shared<CmdReg>( ReturnType::State::RT_OK, TestDef::expiredHandler2 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 5 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Stop
				std::make_shared<CmdStop>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),
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
TEST(WatchdogCount, FreeRunning)
{
	const bool dispTestName = true;
	const bool dispTestInfo = true;

	std::vector<TestDef> testData
	{
		{
			"Free running, initialise()",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit1>( ReturnType::State::RT_OK, true ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Register
				std::make_shared<CmdReg>( ReturnType::State::RT_OK, TestDef::expiredHandler1 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 4 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Kick
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdKick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),
			},
		},
		{
			"Free running, initialise(Max)",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit2>( ReturnType::State::RT_OK, true, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Register
				std::make_shared<CmdReg>( ReturnType::State::RT_OK, TestDef::expiredHandler1 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 3 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Kick
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdKick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),
			},
		},
		{
			"Free running, initialise(Min, Max)",
			dispTestName, dispTestInfo,
			{
				// Initialise
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::UNINIT ),
				std::make_shared<CmdInit3>( ReturnType::State::RT_OK, true, 0, 10 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Register
				std::make_shared<CmdReg>( ReturnType::State::RT_OK, TestDef::expiredHandler1 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::STOPPED ),

				// Start
				std::make_shared<CmdStart>( ReturnType::State::RT_OK, 6 ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Kick
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdKick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),

				// Tick[n] => Expired
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::RUNNING ),
				std::make_shared<CmdTick>( ReturnType::State::RT_OK ),
				std::make_shared<CmdCheckState>( ReturnType::State::RT_OK, WatchdogCount::WatchdogState_T::EXPIRED ),
			},
		},
	};
	// Run each test in turn
	for (auto test : testData)
	{
		test.runTest();
	}
}
