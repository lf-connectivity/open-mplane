/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ina226_unittest.cpp
 * \brief     Google Test of INA226
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the INA226 class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <regex>

#include <memory>
#include "Ina226LinuxMgr.h"

using namespace Mplane ;

const std::string GTEST_DATA("../../../psu/gtest/");

//-------------------------------------------------------------------------------------------------------------
TEST(INA226, devices)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// Point manager at our dummy sysfs
	std::shared_ptr<Ina226LinuxMgr> mgr(std::make_shared<Ina226LinuxMgr>()) ;
	mgr->setSysfs(GTEST_DATA + "hwmon") ;

    std::map<std::string, std::string> names{
    	{ "ina226_u59", "VCCINT_IO_BRAM_PS_SDFEC" },
    	{ "ina226_u61", "VCC1V8" },
    	{ "ina226_u63", "VCCINT_RF" },
    	{ "ina226_u66", "MGT1V2" },
    	{ "ina226_u60", "VCC1V2" },
    	{ "ina226_u3",  "DAC_AVTT" },
    	{ "ina226_u64", "VADJ_FMC" },
    	{ "ina226_u65", "MGT1V8" },
    	{ "ina226_u67", "VCCINT" },
    	{ "ina226_u69", "MGTAVCC" },
    	{ "ina226_u71", "DAC_AVCCAUX" },
    	{ "ina226_u73", "ADC_AVCCAUX" },
    	{ "ina226_u77", "ADC_AVCC" },
    	{ "ina226_u79", "DAC_AVCC" },
    } ;

	mgr->setMapping(names) ;

	std::map<std::string, std::vector<float>> expected{
		{ "DAC_AVTT", { 1.252, 0.262, 0.212 } },
		{ "VCCINT_IO_BRAM_PS_SDFEC", { 0.85, 1.5, 1.755 } },
		{ "VCC1V2", { 1.198, 0.437, 0.368 } },
		{ "VCC1V8", { 1.805, 0.8, 0.441 } },
		{ "VCCINT_RF", { 0.848, 2.725, 3.199 } },
		{ "VADJ_FMC", { 0.098, 0, 0 } },
		{ "MGT1V8", { 1.795, 0.087, 0.05 } },
		{ "MGT1V2", { 1.202, 0.55, 0.453 } },
		{ "VCCINT", { 0.857, 12.906, 15.053 } },
		{ "MGTAVCC", { 0.903, 0.156, 0.155 } },
		{ "DAC_AVCCAUX", { 1.805, 0.312, 0.172 } },
		{ "ADC_AVCCAUX", { 1.815, 2.462, 1.356 } },
		{ "ADC_AVCC", { 0.927, 1.15, 1.23 } },
		{ "DAC_AVCC", { 0.928, 1.087, 1.168 } },
	} ;

    for (auto entry : names)
    {
    	auto ina226(mgr->getMonitor(entry.second)) ;
    	if (!ina226)
    		FAIL() << "Missing device: " << entry.first << " " << entry.second ;

    	std::cerr << "Checking: " << entry.first << " " << entry.second <<
    			" " << ina226->voltage() << "V " <<
				" " << ina226->power() << "W" <<
				" " << ina226->current() << "A" <<
				std::endl ;

    	// check against expected set
    	auto exp(expected[entry.second]) ;
    	ASSERT_NEAR(ina226->voltage(), exp[0], 0.001) ;
    	ASSERT_NEAR(ina226->power(), exp[1], 0.001) ;
    	ASSERT_NEAR(ina226->current(), exp[2], 0.001) ;
    }

}
