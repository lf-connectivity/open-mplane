/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaMonitor_unittest.cpp
 * \brief     Google Test of FpgaMonitor
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaMonitor class.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>

#include <memory>
#include "FpgaMonitor.h"
#include "OffTargetFPGA.h"

using namespace Mplane;

static std::string mon("") ;

void callback(unsigned address, UINT16 newValue, UINT16 oldValue, UINT16 mask)
{
	std::stringstream ss ;
	ss << std::hex << "MONITOR: 0x" << address << " Value 0x" << oldValue << " -> 0x" << newValue <<
			" (mask 0x" << mask << ")" << std::dec ;

	mon = ss.str() ;
	std::cerr << mon << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(FpgaMonitor, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFpgaMonitor> monitor(IFpgaMonitor::getInstance()) ;

	std::cout << test_info->name() << " - END" <<  std::endl;
}


//-------------------------------------------------------------------------------------------------------------
TEST(FpgaMonitor, Monitor1)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFpgaMonitor> monitor(IFpgaMonitor::getInstance()) ;

    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;
    fpgaEmu->reset() ;

    unsigned address = 0x4000 ;
    fpgaEmu->writeReg(address, 0x0, 0xffff) ;

    mon = "" ;
    monitor->addRegister(address, 0xFFFF, callback) ;
    sleep(1) ;
    EXPECT_EQ(std::string("MONITOR: 0x4000 Value 0x0 -> 0x0 (mask 0xffff)"), mon) ;

    mon = "" ;
    fpgaEmu->writeReg(address, 1, 0xffff) ;
    sleep(1) ;
    EXPECT_EQ(std::string("MONITOR: 0x4000 Value 0x0 -> 0x1 (mask 0xffff)"), mon) ;

    mon = "" ;
    fpgaEmu->writeReg(address, 2, 0xffff) ;
    sleep(1) ;
    EXPECT_EQ(std::string("MONITOR: 0x4000 Value 0x1 -> 0x2 (mask 0xffff)"), mon) ;

    mon = "" ;
    fpgaEmu->writeReg(address, 3, 0xffff) ;
    sleep(1) ;
    EXPECT_EQ(std::string("MONITOR: 0x4000 Value 0x2 -> 0x3 (mask 0xffff)"), mon) ;

    monitor->delRegister(address, 0xFFFF) ;
    sleep(1) ;

    mon = "" ;
    fpgaEmu->writeReg(address, 4, 0xffff) ;
    sleep(1) ;
    EXPECT_EQ(std::string(""), mon) ;

    std::cout << test_info->name() << " - END" <<  std::endl;
}


//-------------------------------------------------------------------------------------------------------------
TEST(FpgaMonitor, Monitor1Leak)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFpgaMonitor> monitor(IFpgaMonitor::getInstance()) ;

    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;
    fpgaEmu->reset() ;

    unsigned address = 0x4000 ;
    fpgaEmu->writeReg(address, 0x0, 0xffff) ;
    monitor->addRegister(address, 0xFFFF, callback) ;

    mon = "" ;
    fpgaEmu->writeReg(address, 1, 0xffff) ;
    sleep(1) ;
    EXPECT_EQ(std::string("MONITOR: 0x4000 Value 0x0 -> 0x1 (mask 0xffff)"), mon) ;

    monitor->delRegister(address, 0xFFFF) ;
    sleep(1) ;

    mon = "" ;
    fpgaEmu->writeReg(address, 4, 0xffff) ;
    sleep(1) ;
    EXPECT_EQ(std::string(""), mon) ;

	std::cout << test_info->name() << " - END" <<  std::endl;
}


//-------------------------------------------------------------------------------------------------------------
TEST(FpgaFpc, FpcInit)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFpgaMonitor> monitor(IFpgaMonitor::getInstance()) ;

	// get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    unsigned address = 0x50248 ;
    monitor->addRegister(address, 0xFFFF, callback) ;

    fpgaEmu->reset() ;

    fpgaEmu->writeReg(address, 0x3f, 0xffff) ;

    mon = "" ;
    sleep(1) ;
    EXPECT_EQ(std::string("MONITOR: 0x50248 Value 0xdead -> 0x3f (mask 0xffff)"), mon) ;

    monitor->delRegister(address, 0xFFFF) ;

	std::cout << test_info->name() << " - END" <<  std::endl;
}



//-------------------------------------------------------------------------------------------------------------
TEST(FpgaPa, PaGainManual)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFpgaMonitor> monitor(IFpgaMonitor::getInstance()) ;

	// get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    unsigned address = 0x50242 ;
    monitor->addRegister(address, 0xFFFF, callback) ;

    fpgaEmu->reset() ;

    fpgaEmu->writeReg(address, 0x01, 0xffff) ;

    mon = "" ;
    sleep(1) ;
    EXPECT_EQ(std::string("MONITOR: 0x50242 Value 0xdead -> 0x1 (mask 0xffff)"), mon) ;

    fpgaEmu->writeReg(address, 0x00, 0xffff) ;
    sleep(1) ;
    fpgaEmu->writeReg(address, 0x8000, 0xffff) ;
    sleep(1) ;
    fpgaEmu->writeReg(address, 0x8001, 0xffff) ;
    sleep(1) ;
    EXPECT_EQ(std::string("MONITOR: 0x50242 Value 0x8000 -> 0x8001 (mask 0xffff)"), mon) ;

    monitor->delRegister(address, 0xFFFF) ;

    std::cout << test_info->name() << " - END" <<  std::endl;
}
