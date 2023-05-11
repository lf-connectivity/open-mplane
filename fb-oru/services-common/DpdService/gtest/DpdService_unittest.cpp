/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdService_unittests.cpp
 * \brief     DPD services unit tests
 *
 *
 *
 */

#include "gtest/gtest.h"


#include <string.h>
#include <iostream>


#include "ITxPort.h"
#include "IFpgaComms.h"
#include "Task.h"


#include "client/ITestDpdAlarmClient.h"
#include "client/ITestDpdVswrClient.h"
#include "data/ITestDpdAlarm.h"
#include "data/ITestDpdVswr.h"

#include "data/TestDpdAlarm.h"
#include "data/TestDpdVswr.h"

#include "TestDpdComms.h"
#include "FpgaCommsMsgMonitor.h"
#include "DpdService.h"


using namespace Mplane;


using namespace std;

//============================================================================================================================================

//--------------------------------------------------------------------------------------------------------------------------------------------
class AlarmClient : public virtual ITestDpdAlarmClient
{
public:
	AlarmClient() : mCount(0) {}
	virtual ~AlarmClient() {}

    virtual void update(ITestDpdAlarmClient& subject, const ITestDpdAlarm& data) {
    	std::cerr << "Got alarm" <<std::endl ;
    	++mCount ;
    }

    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const { return "AlarmClient"; }

public:
    unsigned mCount ;
};

//--------------------------------------------------------------------------------------------------------------------------------------------
class VswrClient : public virtual ITestDpdVswrClient
{
public:
	VswrClient() : mCount(0) {}
	virtual ~VswrClient() {}

    virtual void update(ITestDpdVswrClient& subject, const ITestDpdVswr& data) {
    	std::cerr << "Got VSWR measurement" <<std::endl ;
    	++mCount ;
    }

    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const { return "VswrClient"; }

public:
    unsigned mCount ;
};


//--------------------------------------------------------------------------------------------------------------------------------------------
class TestDpdService : public DpdService,
	public Subject<ITestDpdAlarmClient, const ITestDpdAlarm&>,
	public Subject<ITestDpdVswrClient, const ITestDpdVswr&>
{
public:
	TestDpdService() : DpdService() {

		addMonitor(std::make_shared<FpgaCommsMsgMonitor>("err",
			[this](std::map<std::string, DataVariant> attributes){
				handleEvent<TestDpdAlarm, ITestDpdAlarm, ITestDpdAlarmClient>(attributes);
			})
		) ;

		addMonitor(std::make_shared<FpgaCommsMsgMonitor>("revGerr",
			[this](std::map<std::string, DataVariant> attributes){
				handleEvent<TestDpdVswr, ITestDpdVswr, ITestDpdVswrClient>(attributes);
			})
		) ;

	}
	virtual ~TestDpdService() {}

	void attachAlarm(ITestDpdAlarmClient& client)
	{
		static_cast< Subject<ITestDpdAlarmClient, const ITestDpdAlarm&>* >(this)->attach(client) ;
	}

	void attachVswr( ITestDpdVswrClient& client)
	{
		static_cast< Subject<ITestDpdVswrClient, const ITestDpdVswr&>* >(this)->attach(client) ;
	}


};

//=============================================================================================================
// IDpdControl SINGLETON
//=============================================================================================================

std::shared_ptr<IDpdControl> IDpdControl::getInterface()
{
static std::shared_ptr<IDpdControl> interface(std::make_shared<TestDpdService>());

	return interface ;
}


//============================================================================================================================================

//--------------------------------------------------------------------------------------------------------------------------------------------
TEST(DpdServiceTests, DpdEvents)
{
	// Set up DPD services
    std::shared_ptr<TestDpdService> services( std::make_shared<TestDpdService>() );

    // Register some clients
    AlarmClient alarmClient ;
    services->attachAlarm(alarmClient) ;

    VswrClient vswrClient ;
    services->attachVswr(vswrClient) ;


    EXPECT_EQ(0, alarmClient.mCount) ;
    EXPECT_EQ(0, vswrClient.mCount) ;

    // Send test EVENT msgs
    std::shared_ptr<TestDpdComms> testComms(std::dynamic_pointer_cast<TestDpdComms>(IFpgaComms::getInterface())) ;

    // send alarm event
    std::shared_ptr<IFpgaMsg> errMsg1(testComms->createMsg(IFpgaPdu::PduDataType::PDU_TYPE_EVENT,
    		"ENUM(OK:UNKNOWN:TIMEALIGNMENT:LOWBB:DCUFAIL:LOWSRX:HIGHSRX:DIMENSIONING:SOLVER:LUTS:NORMALISATION:RANGE:COVERAGE:UPDATESTRATEGY:EFFICIENCY:EXPANSION:INSANE:SPURIOUS) err=UNKNOWN")) ;
    testComms->emulateRxMsg(errMsg1) ;

    // send VSWR event
    std::shared_ptr<IFpgaMsg> vswrMsg1(testComms->createMsg(IFpgaPdu::PduDataType::PDU_TYPE_EVENT,
    		"FLOAT revGerr=12.3")) ;
    testComms->emulateRxMsg(vswrMsg1) ;

    sleep(1) ;

    EXPECT_EQ(1, alarmClient.mCount) ;
    EXPECT_EQ(1, vswrClient.mCount) ;
}


//--------------------------------------------------------------------------------------------------------------------------------------------
TEST(DpdServiceTests, DpdControl)
{
	std::shared_ptr<TestDpdComms> dpdComms(std::dynamic_pointer_cast<TestDpdComms>(IFpgaComms::getInterface())) ;

	// Set up DPD services
    std::shared_ptr<TestDpdService> services( std::make_shared<TestDpdService>() );


    // Repeat tests for all TX ports
    std::map<std::string, DataVariant> attributes ;
    std::string msgString ;

	// Create DPD TX  controllers for each TX path
    std::vector< std::shared_ptr<ITxPort> > txPorts( ITxPortFactory::getPorts() ) ;
	for (unsigned tx=0; tx < txPorts.size(); ++tx)
	{
		//--------------------------------------------------------------
		std::cerr << "TEST: TX" << tx << " reset" << std::endl ;
		EXPECT_TRUE(services->resetDpd(tx)) ;
		Task::msSleep(200) ;
	    attributes = dpdComms->mLastCommand->getAttributes() ;
	    EXPECT_EQ((int)tx, attributes["tx"].toInt()) ;
	    msgString = dpdComms->mLastCommand->toString() ;
	    EXPECT_TRUE(msgString.find("reset") == 0) ;

	    // emulate success count reset
	    std::shared_ptr<IFpgaMsg> msg1(dpdComms->createMsg(IFpgaPdu::PduDataType::PDU_TYPE_EVENT,
	    		"INT tx=" + std::to_string(tx) + " INT success=0")) ;
	    dpdComms->emulateRxMsg(msg1) ;

		//--------------------------------------------------------------
		std::cerr << "TEST: TX" << tx << " stop" << std::endl ;
		EXPECT_TRUE(services->stopDpd(tx)) ;
		Task::msSleep(200) ;
	    attributes = dpdComms->mLastCommand->getAttributes() ;
	    EXPECT_EQ((int)tx, attributes["tx"].toInt()) ;
	    msgString = dpdComms->mLastCommand->toString() ;
	    EXPECT_TRUE(msgString.find("stop") == 0) ;


		//--------------------------------------------------------------
		std::cerr << "TEST: TX" << tx << " start" << std::endl ;

		// first time should fail - success count=0
		EXPECT_FALSE(services->startDpd(tx, 200)) ;

	    // emulate success count inc (other TX)
	    std::shared_ptr<IFpgaMsg> msg2(dpdComms->createMsg(IFpgaPdu::PduDataType::PDU_TYPE_EVENT,
	    		"INT tx=" + std::to_string(2-tx) + " INT success=1")) ;
	    dpdComms->emulateRxMsg(msg2) ;
		Task::msSleep(200) ;

		// should fail - success count=0
		EXPECT_FALSE(services->startDpd(tx, 200)) ;

	    // emulate success count inc
	    std::shared_ptr<IFpgaMsg> msg3(dpdComms->createMsg(IFpgaPdu::PduDataType::PDU_TYPE_EVENT,
	    		"INT tx=" + std::to_string(tx) + " INT success=1")) ;
	    dpdComms->emulateRxMsg(msg3) ;
		Task::msSleep(200) ;

	    attributes = dpdComms->mLastCommand->getAttributes() ;
	    EXPECT_EQ((int)tx, attributes["tx"].toInt()) ;
	    msgString = dpdComms->mLastCommand->toString() ;
	    EXPECT_TRUE(msgString.find("start") == 0) ;
	}

}
