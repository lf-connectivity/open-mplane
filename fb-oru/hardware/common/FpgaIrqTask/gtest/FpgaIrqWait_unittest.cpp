/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqWait_unittest.cpp
 * \brief     Google Test of FpgaIrqWait
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaIrqWait class.
 *
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
#include "TaskEvent.h"
#include "IFpgaIrqEmu.h"
#include "FpgaIrqWait.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
class IrqTrigger : public TaskEvent {
public:
	IrqTrigger(std::shared_ptr<IFpgaIrqEmu> irqEmu, unsigned irq) :
		TaskEvent(),
		mIrqEmu(irqEmu),
		mIrq(irq),
		mDelayMs(0)
	{}

	virtual ~IrqTrigger() {}

	virtual void triggerAfter(unsigned delayMs)
	{
		mDelayMs = delayMs ;
		event() ;
	}

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override
	{
		Task::msSleep(mDelayMs) ;
		mIrqEmu->raiseIrq(mIrq) ;
		return true ;
	}

private:
	std::shared_ptr<IFpgaIrqEmu> mIrqEmu ;
	unsigned mIrq ;
	unsigned mDelayMs ;
};

//-------------------------------------------------------------------------------------------------------------
TEST(FpgaIrqWait, Event)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<FpgaIrqWait> irqWait( std::make_shared<FpgaIrqWait>(0) ) ;

	std::shared_ptr<IFpgaIrqEmu> irqEmu(IFpgaIrqEmu::getInstance()) ;

	IrqTrigger irqTrigger(irqEmu, 0) ;

//	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;

	// Should time out
	EXPECT_FALSE(irqWait->wait(300)) ;

	// schedule an IRQ after 200ms
	irqTrigger.triggerAfter(200) ;

	// Should now trigger
	EXPECT_TRUE(irqWait->wait(400)) ;


	// Schedule another trigger - then wait indefinitely
	irqTrigger.triggerAfter(200) ;
	EXPECT_TRUE(irqWait->wait()) ;


	// Handle early IRQs
	std::cerr << "Early IRQ test\n" ;
	irqTrigger.triggerAfter(2) ;
	Task::msSleep(100) ;
	EXPECT_TRUE(irqWait->wait(400)) << "Failed to see early IRQ" ;	// this should have seen the earlier IRQ?


	std::cout << test_info->name() << " - DONE" <<  std::endl;

}
