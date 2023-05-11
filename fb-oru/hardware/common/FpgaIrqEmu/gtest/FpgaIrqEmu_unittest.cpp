/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqEmu_unittest.cpp
 * \brief     Google Test of FpgaIrqEmu
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaIrqEmu class.
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <iostream>

#include <memory>
#include "Task.h"
#include "FpgaIrqEmu.h"

using namespace Mplane;

class IrqListener : public Task {
public:
	IrqListener(unsigned bitNum, int fd) :
		Task(Task::PRIORITY_LOW, Task::SMALL_STACK,
			std::string("IrqListen" + std::to_string(bitNum)).c_str(),
			"IrqListen"),
		mBitNum(bitNum),
		mFd(fd),
		mEvents()
	{
		std::cerr << "Listener " << mBitNum << " created" << std::endl ;
		start() ;
	}

	virtual ~IrqListener()
	{
		if (mFd > 0)
			::close(mFd) ;
	}

    virtual int run() override
	{
    	while (1)
    	{
    		std::cerr << "Listener " << mBitNum << " read..." << std::endl ;
    		char buff[1024] ;
    		int num = ::read(mFd, buff, sizeof(buff)) ;
    		std::cerr << "Listener " << mBitNum << " got " << num << std::endl ;
    		if (num <= 0)
    		{
    			std::cerr << "Listener " << mBitNum << " received " << num << std::endl ;
    			return 1 ;
    		}

    		buff[num] = '\0' ;
    		mEvents.push_back(buff) ;
    	}

    	return 0 ;
	}

    unsigned mBitNum ;
    int mFd ;
    std::vector<std::string> mEvents ;
};


//-------------------------------------------------------------------------------------------------------------
TEST(FpgaIrqEmu, Params)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFpgaIrqEmu> irqEmu(IFpgaIrqEmu::getInstance()) ;

	// Test params - these should all fail
	EXPECT_FALSE( irqEmu->open("dummy", O_RDONLY) > 0 ) ;
	EXPECT_FALSE( irqEmu->open("dummy.100", O_RDONLY) > 0 ) ;
	EXPECT_FALSE( irqEmu->open("dummy.1.100", O_RDONLY) > 0 ) ;
	EXPECT_FALSE( irqEmu->close(10) > 0 ) ;
	EXPECT_FALSE( irqEmu->close(10) > 0 ) ;
	EXPECT_FALSE( irqEmu->raiseIrq(100) ) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(FpgaIrqEmu, Irq0Params)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFpgaIrqEmu> irqEmu(IFpgaIrqEmu::getInstance()) ;

	int fd = irqEmu->open("/dev/fpga-irq.0", O_RDONLY) ;
	EXPECT_TRUE( fd > 0 ) ;
	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
	EXPECT_TRUE( irqEmu->close(fd) == 0 ) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(FpgaIrqEmu, Irq0Events)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFpgaIrqEmu> irqEmu(IFpgaIrqEmu::getInstance()) ;

	int fd = irqEmu->open("/dev/fpga-irq.0", O_RDONLY) ;
	EXPECT_TRUE( fd > 0 ) ;

	// Create listener
	IrqListener listener(0, fd) ;
	EXPECT_EQ(0u, listener.mEvents.size()) ;

	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
	while (listener.mEvents.size() < 1) Task::msSleep(100) ;
	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
	while (listener.mEvents.size() < 2) Task::msSleep(100) ;
	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
	while (listener.mEvents.size() < 3) Task::msSleep(100) ;
	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
	while (listener.mEvents.size() < 4) Task::msSleep(100) ;
	EXPECT_EQ(4u, listener.mEvents.size()) ;

	EXPECT_TRUE( irqEmu->close(fd) == 0 ) ;
}
