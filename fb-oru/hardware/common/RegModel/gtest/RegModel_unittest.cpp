/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegModel_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <vector>
#include <string>
#include <iostream>

#include "stringfunc.hpp"

// Uncomment (here or in file that includes this header) to gather expected register writes
//#define GATHER_SEQUENCES

#include "RegModel_fixture.h"
#include "OffTargetFPGA.h"

#include "RegModel.h"
#include "PagedRegModel.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(RegModelTestFixture, Regs4_30)
{
	RegModel model1("model1", 2, 30, 30) ;

    EXPECT_TRUE(!model1.regIsSet(0)) ;
    EXPECT_TRUE(!model1.regIsSet(1)) ;
    EXPECT_TRUE(!model1.regIsSet(2)) ;
    EXPECT_TRUE(!model1.regIsSet(3)) ;

    EXPECT_EQ(model1.regValue(0), 0x0u) ;
    EXPECT_EQ(model1.regValue(1), 0x0u) ;
    EXPECT_EQ(model1.regValue(2), 0x0u) ;
    EXPECT_EQ(model1.regValue(3), 0x0u) ;

    model1.updateWrite(1, 0xFEEDFACE) ;

    EXPECT_TRUE(!model1.regIsSet(0)) ;
    EXPECT_TRUE( model1.regIsSet(1)) ;
    EXPECT_TRUE(!model1.regIsSet(2)) ;
    EXPECT_TRUE(!model1.regIsSet(3)) ;

    EXPECT_EQ(model1.regValue(0), 0x0u) ;
    EXPECT_EQ(model1.regValue(1), 0x3EEDFACEu) ;
    EXPECT_EQ(model1.regValue(2), 0x0u) ;
    EXPECT_EQ(model1.regValue(3), 0x0u) ;

    std::vector<uint32_t> devValues(model1.deviceValues()) ;
    EXPECT_EQ(devValues[0], 0x0u) ;
    EXPECT_EQ(devValues[1], 0x7EEDFACEu) ;
    EXPECT_EQ(devValues[2], 0x0u) ;
    EXPECT_EQ(devValues[3], 0x0u) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(RegModelTestFixture, Regs4_8)
{
	RegModel model2("model2", 2, 8, 8) ;

    EXPECT_TRUE(!model2.regIsSet(0)) ;
    EXPECT_TRUE(!model2.regIsSet(1)) ;
    EXPECT_TRUE(!model2.regIsSet(2)) ;
    EXPECT_TRUE(!model2.regIsSet(3)) ;

    EXPECT_EQ(model2.regValue(0), 0x0u) ;
    EXPECT_EQ(model2.regValue(1), 0x0u) ;
    EXPECT_EQ(model2.regValue(2), 0x0u) ;
    EXPECT_EQ(model2.regValue(3), 0x0u) ;

    model2.updateWrite(1, 0xFEEDFACE) ;

    EXPECT_TRUE(!model2.regIsSet(0)) ;
    EXPECT_TRUE( model2.regIsSet(1)) ;
    EXPECT_TRUE(!model2.regIsSet(2)) ;
    EXPECT_TRUE(!model2.regIsSet(3)) ;

    EXPECT_EQ(model2.regValue(0), 0x0u) ;
    EXPECT_EQ(model2.regValue(1), 0xCEu) ;
    EXPECT_EQ(model2.regValue(2), 0x0u) ;
    EXPECT_EQ(model2.regValue(3), 0x0u) ;

    std::vector<std::string> names(IRegModelMgr::singleton()->names()) ;
    for (auto name : names)
    	std::cerr << "Model " << name << std::endl ;

    IRegModel* model2p(IRegModelMgr::singleton()->regModel("model2")) ;

    model2.updateWrite(3, 0x55AA) ;

    EXPECT_TRUE(!model2p->regIsSet(0)) ;
    EXPECT_TRUE( model2p->regIsSet(1)) ;
    EXPECT_TRUE(!model2p->regIsSet(2)) ;
    EXPECT_TRUE( model2p->regIsSet(3)) ;

    EXPECT_EQ(model2p->regValue(0), 0x0u) ;
    EXPECT_EQ(model2p->regValue(1), 0xCEu) ;
    EXPECT_EQ(model2p->regValue(2), 0x0u) ;
    EXPECT_EQ(model2p->regValue(3), 0xAAu) ;

    std::vector<SetVal<uint32_t>> regs(model2p->regs()) ;
    for (unsigned i=0; i < regs.size(); ++i)
    {
    	printf("R%u : 0x%08x %s\n", i, regs[i].get(), (regs[i].isSet() ? "" : "** NOT SET **") ) ;
    }

    std::vector<uint32_t> devValues(model2p->deviceValues()) ;
    EXPECT_EQ(devValues[0], 0x0u) ;
    EXPECT_EQ(devValues[1], 0x1CEu) ;
    EXPECT_EQ(devValues[2], 0x0u) ;
    EXPECT_EQ(devValues[3], 0x3AAu) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(RegModelTestFixture, PagedReg)
{
	PagedRegModel model3("model3", 2, 8, 32, 2, 1) ;

	EXPECT_TRUE(model3.isPaged());
	model3.setReadPage(0);
    EXPECT_TRUE(!model3.regIsSet(0)) ;
    EXPECT_TRUE(!model3.regIsSet(1)) ;
    EXPECT_TRUE(!model3.regIsSet(2)) ;
    EXPECT_TRUE(!model3.regIsSet(3)) ;

    EXPECT_EQ(model3.regValue(0), 0x0u) ;
    EXPECT_EQ(model3.regValue(1), 0x0u) ;
    EXPECT_EQ(model3.regValue(2), 0x0u) ;
    EXPECT_EQ(model3.regValue(3), 0x0u) ;

    model3.updateWrite(1, 0) ;
    model3.updateWrite(0, 0xAB) ;

    EXPECT_TRUE( model3.regIsSet(0)) ;
    EXPECT_TRUE( model3.regIsSet(1)) ;
    EXPECT_TRUE(!model3.regIsSet(2)) ;
    EXPECT_TRUE(!model3.regIsSet(3)) ;

    EXPECT_EQ(model3.regValue(0), 0xABu) ;
    EXPECT_EQ(model3.regValue(1), 0x0u) ;
    EXPECT_EQ(model3.regValue(2), 0x0u) ;
    EXPECT_EQ(model3.regValue(3), 0x0u) ;

    std::vector<std::string> names(IRegModelMgr::singleton()->names()) ;
    for (auto name : names)
    	std::cerr << "Model " << name << std::endl ;

    IRegModel* model3p(IRegModelMgr::singleton()->regModel("model3")) ;

    model3.updateWrite(3, 0x55) ;

    EXPECT_TRUE( model3p->regIsSet(0)) ;
    EXPECT_TRUE( model3p->regIsSet(1)) ;
    EXPECT_TRUE(!model3p->regIsSet(2)) ;
    EXPECT_TRUE( model3p->regIsSet(3)) ;

    EXPECT_EQ(model3p->regValue(0), 0xABu) ;
    EXPECT_EQ(model3p->regValue(1), 0x0u) ;
    EXPECT_EQ(model3p->regValue(2), 0x0u) ;
    EXPECT_EQ(model3p->regValue(3), 0x55u) ;

    std::vector<SetVal<uint32_t>> regs(model3p->regs()) ;
    for (unsigned i=0; i < regs.size(); ++i)
    {
    	printf("R%u : 0x%08x %s\n", i, regs[i].get(), (regs[i].isSet() ? "" : "** NOT SET **") ) ;
    }

    std::vector<uint32_t> devValues(model3p->deviceValues()) ;
    EXPECT_EQ(devValues[0], 0xABu) ;
    EXPECT_EQ(devValues[1], 0x0u) ;
    EXPECT_EQ(devValues[2], 0x0u) ;
    EXPECT_EQ(devValues[3], 0x55u) ;

    model3.setReadPage(1);
    EXPECT_TRUE(!model3.regIsSet(0)) ;
	EXPECT_TRUE(!model3.regIsSet(1)) ;
	EXPECT_TRUE(!model3.regIsSet(2)) ;
	EXPECT_TRUE(!model3.regIsSet(3)) ;

	EXPECT_EQ(model3.regValue(0), 0x0u) ;
	EXPECT_EQ(model3.regValue(1), 0x0u) ;
	EXPECT_EQ(model3.regValue(2), 0x0u) ;
	EXPECT_EQ(model3.regValue(3), 0x0u) ;

	model3.updateWrite(1, 1) ;
	model3.updateWrite(3, 0xC8) ;
	EXPECT_EQ(model3.regValue(0), 0x0u) ;
	EXPECT_EQ(model3.regValue(1), 0x1u) ;
	EXPECT_EQ(model3.regValue(2), 0x0u) ;
	EXPECT_EQ(model3.regValue(3), 0xC8u) ;

}
