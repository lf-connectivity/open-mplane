/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetStatus_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "NetStatus.h"

using namespace Mplane ;


//=============================================================================================================
// CONST
//=============================================================================================================
const std::string ipFile("./ip.log") ;
const unsigned updateRateMs(200) ;

//=============================================================================================================
// CLASS
//=============================================================================================================

class TestNetStat : public Observer<INetStatus, const INetChange&> {
public:
    virtual void update(INetStatus& subject, const INetChange& data) override
    {
    	std::cerr << "TestNetStat::update - '" << data.getInterface() <<
    			"' : '" << data.getIp() << "' " <<
    			INetChange::stateStr(data.getState()) << std::endl ;

    	EXPECT_EQ(expectedInterface, data.getInterface()) ;
    	EXPECT_EQ(expectedIp, data.getIp()) ;
    	EXPECT_EQ(expectedState, data.getState()) ;


    	expectedInterface.clear() ;
    	expectedIp.clear() ;
    	expectedState = INetChange::NetState::NET_DISCONNECTED ;

    	++count ;

    }

    virtual const char* name() const override
	{
    	return "TestNetStat" ;
	}


    void changeEvent(const INetChange& change)
    {
    	expectedInterface = change.getInterface() ;
    	expectedIp = change.getIp() ;
    	expectedState = change.getState() ;

		std::ofstream outfile;

		std::string stateStr("DISCONNECTED") ;
		if (change.getState() == INetChange::NetState::NET_STATIC)
			stateStr = "STATIC" ;
		else if (change.getState() == INetChange::NetState::NET_DHCP)
			stateStr = "DHCP" ;

		outfile.open(ipFile, std::ios_base::app);
		outfile << stateStr << ":" << change.getInterface() << ":" << change.getIp() << std::endl;

		outfile.close() ;
    }

public:
    unsigned count ;
    std::string expectedInterface ;
    std::string expectedIp ;
    INetChange::NetState expectedState ;
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST(NetStatus, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	TestNetStat observer ;

	NetStatus::mTestIpLogPath = ipFile ;
	NetStatus::mTestUpdateRateMs = updateRateMs ;

	Path::remove(ipFile) ;

	observer.count = 0 ;

	std::shared_ptr<INetStatus> netStatus(NetStatus::getInstance()) ;
	netStatus->attach(observer) ;

	EXPECT_TRUE( netStatus->getInterface().empty() ) ;
	EXPECT_EQ( "0.0.0.0", netStatus->getIp() ) ;
	EXPECT_EQ( INetChange::NetState::NET_DISCONNECTED, netStatus->getState() ) ;
	EXPECT_EQ( "0.0.0.0", netStatus->getIp("not-there") ) ;
	EXPECT_EQ( INetChange::NetState::NET_DISCONNECTED, netStatus->getState("not-there") ) ;


	Task::msSleep(2*updateRateMs) ;

	observer.changeEvent(NetChange("vlanbr", "169.254.0.33", INetChange::NetState::NET_STATIC)) ;
	Task::msSleep(2*updateRateMs) ;
	EXPECT_EQ(1u, observer.count) ;
	EXPECT_EQ( "vlanbr", netStatus->getInterface() ) ;
	EXPECT_EQ( "169.254.0.33", netStatus->getIp() ) ;
	EXPECT_EQ( INetChange::NetState::NET_STATIC, netStatus->getState() ) ;
	EXPECT_EQ( "169.254.0.33", netStatus->getIp("vlanbr") ) ;
	EXPECT_EQ( INetChange::NetState::NET_STATIC, netStatus->getState("vlanbr") ) ;
	EXPECT_EQ( "0.0.0.0", netStatus->getIp("eth1") ) ;
	EXPECT_EQ( INetChange::NetState::NET_DISCONNECTED, netStatus->getState("eth1") ) ;

	observer.changeEvent(NetChange("vlanbr", "10.15.160.193", INetChange::NetState::NET_DHCP)) ;
	Task::msSleep(2*updateRateMs) ;
	EXPECT_EQ(2u, observer.count) ;
	EXPECT_EQ( "vlanbr", netStatus->getInterface() ) ;
	EXPECT_EQ( "10.15.160.193", netStatus->getIp() ) ;
	EXPECT_EQ( INetChange::NetState::NET_DHCP, netStatus->getState() ) ;
	EXPECT_EQ( "10.15.160.193", netStatus->getIp("vlanbr") ) ;
	EXPECT_EQ( INetChange::NetState::NET_DHCP, netStatus->getState("vlanbr") ) ;
	EXPECT_EQ( "0.0.0.0", netStatus->getIp("eth1") ) ;
	EXPECT_EQ( INetChange::NetState::NET_DISCONNECTED, netStatus->getState("eth1") ) ;

	observer.changeEvent(NetChange("vlanbr", "10.15.160.193", INetChange::NetState::NET_DHCP)) ;
	Task::msSleep(2*updateRateMs) ;
	EXPECT_EQ(2u, observer.count) ;
	EXPECT_EQ( "vlanbr", netStatus->getInterface() ) ;
	EXPECT_EQ( "10.15.160.193", netStatus->getIp() ) ;
	EXPECT_EQ( INetChange::NetState::NET_DHCP, netStatus->getState() ) ;
	EXPECT_EQ( "10.15.160.193", netStatus->getIp("vlanbr") ) ;
	EXPECT_EQ( INetChange::NetState::NET_DHCP, netStatus->getState("vlanbr") ) ;
	EXPECT_EQ( "0.0.0.0", netStatus->getIp("eth1") ) ;
	EXPECT_EQ( INetChange::NetState::NET_DISCONNECTED, netStatus->getState("eth1") ) ;

	observer.changeEvent(NetChange("eth1", "10.1.2.3", INetChange::NetState::NET_STATIC)) ;
	Task::msSleep(2*updateRateMs) ;
	EXPECT_EQ(3u, observer.count) ;
	EXPECT_EQ( "eth1", netStatus->getInterface() ) ;
	EXPECT_EQ( "10.1.2.3", netStatus->getIp() ) ;
	EXPECT_EQ( INetChange::NetState::NET_STATIC, netStatus->getState() ) ;
	EXPECT_EQ( "10.15.160.193", netStatus->getIp("vlanbr") ) ;
	EXPECT_EQ( INetChange::NetState::NET_DHCP, netStatus->getState("vlanbr") ) ;
	EXPECT_EQ( "10.1.2.3", netStatus->getIp("eth1") ) ;
	EXPECT_EQ( INetChange::NetState::NET_STATIC, netStatus->getState("eth1") ) ;

	observer.changeEvent(NetChange("vlanbr", "10.15.160.194", INetChange::NetState::NET_DHCP)) ;
	Task::msSleep(2*updateRateMs) ;
	EXPECT_EQ(4u, observer.count) ;
	EXPECT_EQ( "vlanbr", netStatus->getInterface() ) ;
	EXPECT_EQ( "10.15.160.194", netStatus->getIp() ) ;
	EXPECT_EQ( INetChange::NetState::NET_DHCP, netStatus->getState() ) ;
	EXPECT_EQ( "10.15.160.194", netStatus->getIp("vlanbr") ) ;
	EXPECT_EQ( INetChange::NetState::NET_DHCP, netStatus->getState("vlanbr") ) ;
	EXPECT_EQ( "10.1.2.3", netStatus->getIp("eth1") ) ;
	EXPECT_EQ( INetChange::NetState::NET_STATIC, netStatus->getState("eth1") ) ;

	observer.changeEvent(NetChange("eth1", "0.0.0.0", INetChange::NetState::NET_DISCONNECTED)) ;
	Task::msSleep(2*updateRateMs) ;
	EXPECT_EQ(5u, observer.count) ;
	EXPECT_EQ( "eth1", netStatus->getInterface() ) ;
	EXPECT_EQ( "0.0.0.0", netStatus->getIp() ) ;
	EXPECT_EQ( INetChange::NetState::NET_DISCONNECTED, netStatus->getState() ) ;
	EXPECT_EQ( "10.15.160.194", netStatus->getIp("vlanbr") ) ;
	EXPECT_EQ( INetChange::NetState::NET_DHCP, netStatus->getState("vlanbr") ) ;
	EXPECT_EQ( "0.0.0.0", netStatus->getIp("eth1") ) ;
	EXPECT_EQ( INetChange::NetState::NET_DISCONNECTED, netStatus->getState("eth1") ) ;



}
