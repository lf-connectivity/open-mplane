/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriEmu_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <iostream>
#include <fstream>

//#define GATHER_SEQUENCES
#include "CpriEmu_fixture.h"

#include "CpriFibreEmu.h"

using namespace Mplane ;


//=============================================================================================================
// CLASSES
//=============================================================================================================
class CpriEmuTest : public CpriEmuTestFixture
{
public:
	void clear()
	{
		mOutput.clear() ;
	}

	void out(const std::string& line)
	{
		std::cerr << line << std::endl;
		mOutput += line + "\n" ;
	}

	void checkOutput(const std::string& checkLine)
	{
		EXPECT_TRUE(mOutput.find(checkLine) != std::string::npos) ;
	}

	void checkOutput(std::vector<std::string> checkLines)
	{
		for (auto line : checkLines)
			checkOutput(line) ;
	}

public:
	std::string mOutput ;
};

//=============================================================================================================
// CONSTANT
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(CpriEmuTest, Basic)
{
	std::shared_ptr<CpriFibreEmu> fibreEmu0( std::make_shared<CpriFibreEmu>(0) ) ;

    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("statCode[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("curLineRate[0]")) ;
    EXPECT_EQ(0x7f, fpgaEmu->readField("cpriLineRatesReg[0]")) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CpriEmuTest, NoRate)
{
std::cerr << "NoRate: create fibreEmu0" << std::endl ;
	std::shared_ptr<CpriFibreEmu> fibreEmu0( std::make_shared<CpriFibreEmu>(0) ) ;

	std::cerr << "NoRate: get fpga emu" << std::endl ;
    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

	std::cerr << "NoRate: check regs" << std::endl ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("statCode[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("curLineRate[0]")) ;
    EXPECT_EQ(0x7f, fpgaEmu->readField("cpriLineRatesReg[0]")) ;

    // Take out of reset - set preferred rate=0
	std::cerr << "NoRate: set pref rate=0" << std::endl ;
	fpgaEmu->writeField("fibreBlkReset[0]", 0) ;
	fpgaEmu->writeField("cpriLineRatesReg[0]", 0) ;
	EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
	EXPECT_EQ(0u, fpgaEmu->readField("fibreBlkReset[0]")) ;
	EXPECT_EQ(0u, fpgaEmu->readField("cpriLineRatesReg[0]")) ;

	// wait
	std::cerr << "NoRate: wait 4secs" << std::endl ;
	sleep(4) ;

	// should now be still trying to negotiate
	std::cerr << "NoRate:check regs" << std::endl ;
	EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
	EXPECT_EQ(0u, fpgaEmu->readField("fibreBlkReset[0]")) ;
	EXPECT_EQ(1u, fpgaEmu->readField("statCode[0]")) ;
	EXPECT_EQ(0u, fpgaEmu->readField("curLineRate[0]")) ;
	EXPECT_EQ(0u, fpgaEmu->readField("cpriLineRatesReg[0]")) ;

	std::cerr << "NoRate: END" << std::endl ;

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CpriEmuTest, DefaultRate)
{
	std::shared_ptr<CpriFibreEmu> fibreEmu0( std::make_shared<CpriFibreEmu>(0) ) ;

    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

	std::cerr << "DefaultRate: check regs" << std::endl ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("statCode[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("curLineRate[0]")) ;
    EXPECT_EQ(0x7f, fpgaEmu->readField("cpriLineRatesReg[0]")) ;

    // Take out of reset
	std::cerr << "DefaultRate: take out of reset" << std::endl ;
    fpgaEmu->writeField("fibreBlkReset[0]", 0) ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0x7f, fpgaEmu->readField("cpriLineRatesReg[0]")) ;

    // wait
	std::cerr << "DefaultRate: wait 4secs" << std::endl ;
    sleep(4) ;

    // should now be still trying to negotiate
	std::cerr << "DefaultRate: check regs" << std::endl ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0x7f, fpgaEmu->readField("cpriLineRatesReg[0]")) ;
    EXPECT_EQ(0xf, fpgaEmu->readField("statCode[0]")) ;
    EXPECT_EQ(0x40, fpgaEmu->readField("curLineRate[0]")) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CpriEmuTest, SetRate)
{
	std::shared_ptr<CpriFibreEmu> fibreEmu0( std::make_shared<CpriFibreEmu>(0) ) ;

    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("statCode[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("curLineRate[0]")) ;
    EXPECT_EQ(0x7f, fpgaEmu->readField("cpriLineRatesReg[0]")) ;

    // Take out of reset - set preferred rate
	std::cerr << "SetRate: take out of reset, set preferred rate" << std::endl ;
    fpgaEmu->writeField("fibreBlkReset[0]", 0) ;
    fpgaEmu->writeField("cpriLineRatesReg[0]", 0x20) ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0x20, fpgaEmu->readField("cpriLineRatesReg[0]")) ;

    // wait
	std::cerr << "SetRate: wait 4secs" << std::endl ;
    sleep(4) ;

    // should now be still trying to negotiate
    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0xf, fpgaEmu->readField("statCode[0]")) ;
    EXPECT_EQ(0x20, fpgaEmu->readField("curLineRate[0]")) ;
    EXPECT_EQ(0x20, fpgaEmu->readField("cpriLineRatesReg[0]")) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CpriEmuTest, RemoteRate)
{
	std::shared_ptr<CpriFibreEmu> fibreEmu0( std::make_shared<CpriFibreEmu>(0) ) ;

	// Limit remote rates
	fibreEmu0->setRemoteRate(0x10) ;

    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("statCode[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("curLineRate[0]")) ;
    EXPECT_EQ(0x7f, fpgaEmu->readField("cpriLineRatesReg[0]")) ;

    // Take out of reset - set preferred rates
	std::cerr << "SetRate: take out of reset, set preferred rate" << std::endl ;
    fpgaEmu->writeField("fibreBlkReset[0]", 0) ;
    fpgaEmu->writeField("cpriLineRatesReg[0]", 0x70) ;
    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0x70, fpgaEmu->readField("cpriLineRatesReg[0]")) ;

    // wait
	std::cerr << "SetRate: wait 4secs" << std::endl ;
    sleep(4) ;

    // should now be still trying to negotiate
    EXPECT_EQ(1u, fpgaEmu->readField("fibreType[0]")) ;
    EXPECT_EQ(0u, fpgaEmu->readField("fibreBlkReset[0]")) ;
    EXPECT_EQ(0xf, fpgaEmu->readField("statCode[0]")) ;
    EXPECT_EQ(0x10, fpgaEmu->readField("curLineRate[0]")) ;
    EXPECT_EQ(0x70, fpgaEmu->readField("cpriLineRatesReg[0]")) ;


}
