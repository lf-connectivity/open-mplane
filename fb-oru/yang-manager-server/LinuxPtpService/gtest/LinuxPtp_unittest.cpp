/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LinuxPtp_unittest.cpp
 * \brief     LinuxPtp unit tests
 *
 *
 * \details   LinuxPtp unit tests.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "TestLinuxPtp.h"
#include "ILinuxPtpService.h"
#include "LinuxPtpService.h"
#include "IAppOptions.h"
#include "INetworkingService.h"
#include "NetworkingService.h"
#include "NetAddrPolicyMock.h"
#include "PacketSnifferMock.h"
#include "PllMajorAlarm.h"
#include "Alarm.h"

using namespace Mplane;

namespace Mplane
{

class AppOptionsMock : public IAppOptions {
public:
	AppOptionsMock():mDataVariant("ethbb=eth1"){};
	virtual ~AppOptionsMock() {}

	/**
	 * Singleton creation - called with the command line args
	 * @param argc
	 * @param argv
	 * @param applicationDescription - a string that describes the application
	 * @param optionsSpecification - a vector of IAppOtionSpec objects
	 * @return shared pointer to singleton
	 */
	static std::shared_ptr<IAppOptions> createInstance(int argc, const char** argv,
		const std::string& applicationDescription,
		const std::vector< std::shared_ptr<IAppOptionSpec> >& optionsSpecification) ;

	/**
	 * Singleton access
	 * @return shared pointer to singleton
	 */
	static std::shared_ptr<IAppOptions> getInstance() ;

	/**
	 * Get the option given by the name
	 * @param name
	 * @return DataVariant containing the option named
	 */
	virtual const DataVariant getOption(const std::string& name) const
	{
		return mDataVariant;
	}

protected:

	static std::shared_ptr<IAppOptions> singleton(int argc,
			const char** argv, const std::string& applicationDescription,
			const std::vector<std::shared_ptr<IAppOptionSpec> >& optionsSpecification);

	DataVariant mDataVariant;

} ;

std::shared_ptr<IAppOptions> IAppOptions::getInstance()
{
	static std::shared_ptr<IAppOptions> instance = std::make_shared<AppOptionsMock>();
	return instance;
}

std::shared_ptr<IAppOptions> IAppOptions::createInstance(int argc, const char** argv,
		const std::string& applicationDescription,
		const std::vector< std::shared_ptr<IAppOptionSpec> >& optionsSpecification)
{
	return getInstance();
}

std::shared_ptr<IAppOptions> IAppOptions::singleton(int argc,
			const char** argv, const std::string& applicationDescription,
			const std::vector<std::shared_ptr<IAppOptionSpec> >& optionsSpecification)
{
	return getInstance();
}
}

class TestClass : public ::testing::Test
{
public:

    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << std::endl << "*** " << test_info->test_case_name()
                << " Tests ***" << std::endl;
        std::cout << test_info->name() << " - SETUP" << std::endl;

        // Do the setup here
        Mplane::ILoggable::setGroupLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_NORMAL, "YANG") ;

        mLinuxPtp = new TestLinuxPtp();

        try
        {
        	make_alarm<PllMajorAlarm>();
        }
        catch (...)
        {
        	// Ignore the exception as we should be adding the alarm only once
        }

        std::cout << test_info->name() << " - SETUP complete" << std::endl;
    }

    virtual void TearDown()
	{
	  const ::testing::TestInfo* const test_info =
			  ::testing::UnitTest::GetInstance()->current_test_info();

	  std::cout << test_info->name() << " - TEARDOWN" << std::endl;

	  // Do the tear down here
	  delete mLinuxPtp;

	  auto ns(std::dynamic_pointer_cast<NetworkingService>(INetworkingService::singleton("ethbb"))) ;
	  ns->event() ;

	  auto policy(std::dynamic_pointer_cast<NetAddrPolicyMock>(ns->getNetAddrPolicy())) ;

	  // Interface is up
	  policy->setInterface(false);

	  ns->event();

	  std::cout << test_info->name() << " - TEARDOWN complete" << std::endl;
	}

    TestLinuxPtp * mLinuxPtp;
protected:

private:

};

TEST_F(TestClass, lockProcedure)
{
	mLinuxPtp->setLockOutcome(true);
	mLinuxPtp->initialise();

	mLinuxPtp->serviceLinuxPtp();

	// Verify initial state
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_INTERFACE);

	auto ns(std::dynamic_pointer_cast<NetworkingService>(INetworkingService::singleton("ethbb"))) ;
	ns->event() ;

	auto policy(std::dynamic_pointer_cast<NetAddrPolicyMock>(ns->getNetAddrPolicy())) ;

	// Interface is up
	policy->setInterface(true);

	ns->event();

	Task::msSleep(100) ;

	mLinuxPtp->setAcceptableSsmCode(ILinuxPtpConfig::DNU, true);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	std::shared_ptr<PacketSnifferMock> sniffer = std::dynamic_pointer_cast<PacketSnifferMock>(IPacketSniffer::singleton(""));

	unsigned char data[] =
	{
		0x01, 0x80, 0xc2, 0x00, 0x00, 0x02,       // Destination MAC address
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       // Source MAC address
		0x88, 0x09,                               // Ethertype
		0x0A,                                     // Slow protocol subtype
		0x00, 0x19, 0xA7,                         // ITU-OUI
		0x00, 0x01,                               // ITU subtype
		0x10,                                     // Version
		0x00, 0x00, 0x00,                         // Reserved
		0x01, 0x00, 0x04, 0x0B                    // QL TLV
	};
	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that PTP starts
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::PTP_START);

	Task::msSleep(100) ;

	mLinuxPtp->serviceLinuxPtp();

	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::DETECT_PTP_LOCK_STATUS);

	Task::msSleep(100) ;

	mLinuxPtp->serviceLinuxPtp();
	mLinuxPtp->serviceLinuxPtp();

	// Verify that PTP is locked
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::PTP_LOCKED);
	EXPECT_EQ(mLinuxPtp->getPtpLockStatus(), ILinuxPtp::LockStatus_T::LOCKED);

	// Verify that post lock check is done
	mLinuxPtp->serviceLinuxPtp();
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::DETECT_AIRFRAME_LOCK);

	mLinuxPtp->serviceLinuxPtp();
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::CHECK_POST_PTP_LOCK_STATUS);

	// Verify some parameters
	EXPECT_EQ(mLinuxPtp->getRuClockClass(), 248);
	EXPECT_EQ(mLinuxPtp->getRuClockIdentity(), "0xCC11223344556677");
	EXPECT_EQ(mLinuxPtp->getCurrentUtcOffset(), 45);
	EXPECT_EQ(mLinuxPtp->getCurrentUtcOffsetValidFlag(), true);
	EXPECT_EQ(mLinuxPtp->getStepsRemoved(), 55);
	EXPECT_EQ(mLinuxPtp->getPriority1(), 240);
	EXPECT_EQ(mLinuxPtp->getPriority2(), 136);
	EXPECT_EQ(mLinuxPtp->getSourceClockIdentity(), "0xCC112233445566AA");


	// Change some params
	mLinuxPtp->setRuClockClass(7);
	mLinuxPtp->setRuClockIdentity("0xDD223388445566AA");
	LinuxPtp::PtpSourceStatus param;
	param.mTwoStepFlag = true;
	param.mLeap61 = true;
	param.mLeap59 = true;
	param.mCurrentUtcOffset = 45;
	param.mCurrentUtcOffsetValid = true;
	param.mPtpTimescale = true;
	param.mTimeTraceable = false;
	param.mFreqTraceable = true;
	param.mTimeSource = 0xA3;
	param.mStepsRemoved = 55;
	param.mPriority1 = 245;
	param.mPriority2 = 132;
	param.mClockClass = 8;
	param.mClockAccuracy = 0x42;
	param.mOffsetScaledLogVariance = 0x8e9c;
	param.mGrandmasterIdentity = "0xCC11443344556688";
	param.mSourceClockIdentity = "0xCC11EE33445566AA";
	mLinuxPtp->setPtpParams(param);

	// Verify that the parameters are not updated immediately
	EXPECT_EQ(mLinuxPtp->getRuClockClass(), 248);
	EXPECT_EQ(mLinuxPtp->getRuClockIdentity(), "0xCC11223344556677");
	EXPECT_EQ(mLinuxPtp->getPtpSourceState(), LinuxPtp::SourceState_T::DISABLED);
	EXPECT_EQ(mLinuxPtp->getFrequencyTraceableFlag(), false);

	// Verify that the clock class change is picked up after a delay
	Task::msSleep(LinuxPtp::mParamsRefreshMs + 1);
	EXPECT_EQ(mLinuxPtp->getRuClockClass(), 7);
	EXPECT_EQ(mLinuxPtp->getRuClockIdentity(), "0xDD223388445566AA");
	EXPECT_EQ(mLinuxPtp->getPtpSourceState(), LinuxPtp::SourceState_T::DISABLED);
	EXPECT_EQ(mLinuxPtp->getFrequencyTraceableFlag(), true);

	// Verify that airframe is locked
	mLinuxPtp->serviceLinuxPtp();
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::AIRFRAME_LOCKED);
	EXPECT_EQ(mLinuxPtp->getPtpLockStatus(), ILinuxPtp::LockStatus_T::LOCKED);

	// Verify the state as NOK as the clock class is > max acceptable clock class
	EXPECT_EQ(mLinuxPtp->getPtpSourceState(), LinuxPtp::SourceState_T::NOK);
}


TEST_F(TestClass, lockFail)
{
	mLinuxPtp->setLockOutcome(false);
	mLinuxPtp->initialise();

	mLinuxPtp->serviceLinuxPtp();

	// Verify initial state
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_INTERFACE);

	auto ns(std::dynamic_pointer_cast<NetworkingService>(INetworkingService::singleton("ethbb"))) ;
	ns->event() ;

	auto policy(std::dynamic_pointer_cast<NetAddrPolicyMock>(ns->getNetAddrPolicy())) ;

	// Interface is up
	policy->setInterface(true);

	ns->event();

	Task::msSleep(100) ;

	mLinuxPtp->setAcceptableSsmCode(ILinuxPtpConfig::DNU, true);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	std::shared_ptr<PacketSnifferMock> sniffer = std::dynamic_pointer_cast<PacketSnifferMock>(IPacketSniffer::singleton(""));

	unsigned char data[] =
	{
		0x01, 0x80, 0xc2, 0x00, 0x00, 0x02,       // Destination MAC address
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       // Source MAC address
		0x88, 0x09,                               // Ethertype
		0x0A,                                     // Slow protocol subtype
		0x00, 0x19, 0xA7,                         // ITU-OUI
		0x00, 0x01,                               // ITU subtype
		0x10,                                     // Version
		0x00, 0x00, 0x00,                         // Reserved
		0x01, 0x00, 0x04, 0x0B                    // QL TLV
	};
	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that PTP starts
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::PTP_START);

	Task::msSleep(100) ;

	mLinuxPtp->serviceLinuxPtp();

	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::DETECT_PTP_LOCK_STATUS);

	Task::msSleep(100) ;

	mLinuxPtp->serviceLinuxPtp();
	mLinuxPtp->serviceLinuxPtp();

	// Verify that PTP is locked
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::PTP_LOCKED);
	EXPECT_EQ(mLinuxPtp->getPtpLockStatus(), ILinuxPtp::LockStatus_T::LOCKED);

	// Verify that post lock check is done
	mLinuxPtp->serviceLinuxPtp();
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::DETECT_AIRFRAME_LOCK);

	mLinuxPtp->serviceLinuxPtp();
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::CHECK_POST_PTP_LOCK_STATUS);

	// Verify that PTP is retried
	mLinuxPtp->serviceLinuxPtp();
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::DETECT_PTP_LOCK_STATUS);

}

TEST_F(TestClass, NoEsmcPDU)
{
	mLinuxPtp->setLockOutcome(true);
	mLinuxPtp->initialise();

	mLinuxPtp->serviceLinuxPtp();

	// Verify initial state
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_INTERFACE);

	auto ns(std::dynamic_pointer_cast<NetworkingService>(INetworkingService::singleton("ethbb"))) ;
	ns->event() ;

	auto policy(std::dynamic_pointer_cast<NetAddrPolicyMock>(ns->getNetAddrPolicy())) ;

	// Interface is up
	policy->setInterface(true);

	ns->event();

	Task::msSleep(100) ;

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	Task::msSleep(1000) ;

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);
}

TEST_F(TestClass, PacketNotEsmcPDU)
{
	mLinuxPtp->setLockOutcome(true);
	mLinuxPtp->initialise();

	mLinuxPtp->serviceLinuxPtp();

	// Verify initial state
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_INTERFACE);

	auto ns(std::dynamic_pointer_cast<NetworkingService>(INetworkingService::singleton("ethbb"))) ;
	ns->event() ;

	auto policy(std::dynamic_pointer_cast<NetAddrPolicyMock>(ns->getNetAddrPolicy())) ;

	// Interface is up
	policy->setInterface(true);

	ns->event();

	Task::msSleep(100) ;

	mLinuxPtp->setAcceptableSsmCode(ILinuxPtpConfig::DNU, true);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	std::shared_ptr<PacketSnifferMock> sniffer = std::dynamic_pointer_cast<PacketSnifferMock>(IPacketSniffer::singleton(""));

	// Destination MAC address is wrong
	unsigned char data[] =
	{
		0x01, 0x80, 0xc1, 0x00, 0x00, 0x02,       // Destination MAC address
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       // Source MAC address
		0x88, 0x09,                               // Ethertype
		0x0A,                                     // Slow protocol subtype
		0x00, 0x19, 0xA7,                         // ITU-OUI
		0x00, 0x01,                               // ITU subtype
		0x10,                                     // Version
		0x00, 0x00, 0x00,                         // Reserved
		0x01, 0x00, 0x04, 0x0B                    // QL TLV
	};
	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	// Destination MAC is correct, ether type is not
	data[2] = 0xC2;
	data[12] = 0x81;

	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	// Destination MAC is correct, ether type is correct, slow protocol sub-type is not
	data[12] = 0x88;
	data[14] = 0x0B;

	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	// Destination MAC, ether type and slow protocol sub-type correct, ITU-OUI is not
	data[14] = 0x0A;
	data[16] = 0x44;

	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	// Destination MAC, ether type, slow protocol sub-type and ITU-OUI correct, QL TLV is not
	data[16] = 0x19;
	data[24] = 0x02;

	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	// Destination MAC, ether type, slow protocol sub-type and ITU-OUI correct, QL TLV is not
	data[24] = 0x00;
	data[25] = 0x02;

	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	EXPECT_EQ(mLinuxPtp->getSynceLockStatus(), ILinuxPtpStatus::LockStatus_T::NOT_LOCKED);
}

TEST_F(TestClass, SSMCodeMismatchTimeout)
{
	mLinuxPtp->setLockOutcome(true);
	mLinuxPtp->initialise();

	mLinuxPtp->serviceLinuxPtp();

	// Verify initial state
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_INTERFACE);

	auto ns(std::dynamic_pointer_cast<NetworkingService>(INetworkingService::singleton("ethbb"))) ;
	ns->event() ;

	auto policy(std::dynamic_pointer_cast<NetAddrPolicyMock>(ns->getNetAddrPolicy())) ;

	// Interface is up
	policy->setInterface(true);

	ns->event();

	Task::msSleep(100) ;

	mLinuxPtp->setAcceptableSsmCode(ILinuxPtpConfig::PRC, true);
	mLinuxPtp->setSsmTimeout(2);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	std::shared_ptr<PacketSnifferMock> sniffer = std::dynamic_pointer_cast<PacketSnifferMock>(IPacketSniffer::singleton(""));

	/*********************************************************************/
	// SSM code mismatch
	/*********************************************************************/
	unsigned char data[] =
	{
		0x01, 0x80, 0xc2, 0x00, 0x00, 0x02,       // Destination MAC address
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       // Source MAC address
		0x88, 0x09,                               // Ethertype
		0x0A,                                     // Slow protocol subtype
		0x00, 0x19, 0xA7,                         // ITU-OUI
		0x00, 0x01,                               // ITU subtype
		0x10,                                     // Version
		0x00, 0x00, 0x00,                         // Reserved
		0x01, 0x00, 0x04, 0x0B                    // QL TLV
	};
	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it waits for sync
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	/*********************************************************************/
	// Now match the required SSM code
	/*********************************************************************/
	data[27] = 0x02;

	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it goes to PTP start
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::PTP_START);

	EXPECT_EQ(mLinuxPtp->getSynceLockStatus(), ILinuxPtpStatus::LockStatus_T::LOCKED);

	/*********************************************************************/
	// SYNCE stays locked for the SSM timeout seconds even if it receives
	// mismatched SSM code
	/*********************************************************************/
	data[27] = 0x0B;

	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it continues with PTP locking procedure
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::DETECT_PTP_LOCK_STATUS);

	// Verify that SYNCE state is still locked
	EXPECT_EQ(mLinuxPtp->getSynceLockStatus(), ILinuxPtpStatus::LockStatus_T::LOCKED);

	// SSM timeout elapsed
	for (int i = 0; i < 20; i++)
	{
		Task::msSleep(100) ;

		mLinuxPtp->serviceLinuxPtp();
	}

	// Verify that SYNCE state is not locked
	EXPECT_EQ(mLinuxPtp->getSynceLockStatus(), ILinuxPtpStatus::LockStatus_T::NOT_LOCKED);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that we go back to waiting for ESMC PDU
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

	// Now match the required SSM code
	data[27] = 0x02;

	// Send a mock ESMC PDU packet
	sniffer->dispatchPacket(data, 28);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that it goes to PTP start
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::PTP_START);

	EXPECT_EQ(mLinuxPtp->getSynceLockStatus(), ILinuxPtpStatus::LockStatus_T::LOCKED);

	/*********************************************************************/
	// No ESMC PDU for 5 seconds
	/*********************************************************************/
	for (int i = 0; i < 50; i++)
	{
		Task::msSleep(100) ;

		mLinuxPtp->serviceLinuxPtp();
	}

	// Verify that SYNCE state is not locked
	EXPECT_EQ(mLinuxPtp->getSynceLockStatus(), ILinuxPtpStatus::LockStatus_T::NOT_LOCKED);

	mLinuxPtp->serviceLinuxPtp();

	// Verify that we go back to waiting for ESMC PDU
	EXPECT_EQ(mLinuxPtp->getState(), LinuxPtp::LinuxPtpServiceState::WAIT_FOR_ESMC);

}
