/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      fixture.cpp
 * \brief     test fixture
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdlib.h>
#include <time.h>

#include <string>
#include <iostream>
#include <algorithm>

#include "Task.h"
#include "MsgText.h"
#include "dpd_fixture.h"

using namespace Mplane;


//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void DpdTestFixture::SetUp()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

}


//-------------------------------------------------------------------------------------------------------------------
void DpdTestFixture::TearDown()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << test_info->name() << " - END" <<  std::endl;
}


//-------------------------------------------------------------------------------------------------------------------
bool DpdTestFixture::doRx()
{
    time_t start ;

	// wait for message to ripple through
    time(&start) ;
    while (mRxMsgs.empty())
    {
    	// timeout
        time_t now ;
        time(&now) ;
        if (difftime(now, start) > 2.0)
        {
        	return false ;
        }

        Task::msSleep(100) ;
    }
    return true ;
}

//-------------------------------------------------------------------------------------------------------------------
void DpdTestFixture::handleMsg(std::shared_ptr<IFpgaMsg> msg)
{
	std::cerr << "RX Msg" << std::endl ;
	mRxMsgs.push_back(msg) ;
}

//-------------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> DpdTestFixture::createMsg(const IFpgaPdu& pdu)
{
	switch (pdu.getType())
	{
	case IFpgaPdu::PduDataType::PDU_TYPE_CMD :
	case IFpgaPdu::PduDataType::PDU_TYPE_REPLY :
	case IFpgaPdu::PduDataType::PDU_TYPE_EVENT :
	case IFpgaPdu::PduDataType::PDU_TYPE_LOG :
	case IFpgaPdu::PduDataType::PDU_TYPE_MATLAB :
	case IFpgaPdu::PduDataType::PDU_TYPE_TEXT :
		return std::make_shared<MsgText>(pdu) ;
		break ;
	default:
		return std::shared_ptr<IFpgaMsg>() ;
		break ;
	}

	return std::shared_ptr<IFpgaMsg>() ;
}
