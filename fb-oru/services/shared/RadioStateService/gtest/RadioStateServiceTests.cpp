/*
 * RadioStateServiceServiceTestCase.cpp
 *
 *  Created on: June 1, 2015
 *      Author: rcooper
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>
#include <sstream>

#include "IRadio.h"
#include "ITxPort.h"
#include "ICarrier.h"
#include "ICarrierServer.h"
#include "IFaultsList.h"

#include "RadioStateService.h"

#include "PaTempMajorAlarm.h"
#include "Cpri0MajorAlarm.h"
#include "HeartBeatMajorAlarm.h"
#include "PaTempMinorAlarm.h"
#include "PllMajorAlarm.h"
//#include "RadioCardPsuAlarm.h"
#include "RadioTempMajorAlarm.h"
#include "RadioTempMinorAlarm.h"
#include "RxMajorAlarm.h"
#include "TxBbIqAlarm.h"
#include "TxDegradedAlarm.h"
#include "TxShutdownAlarm.h"
#include "VswrTxAlarm.h"

#include "RrhAlarms.h"
#include "RrhFaults.h"

#include "VswrTxFaultMajor.h"
#include "DpdTxFaultMinor.h"
#include "DpdTxFaultMajor.h"
#include "TxOverPowerFaultMinor.h"
#include "TxOverPowerFaultMajor.h"
//#include "RadioCardPsuOverVoltageFaultMajor.h"
//#include "RadioCardPsuUnderVoltageFaultMajor.h"
#include "BoardTxOverTemperatureFaultMajor.h"
#include "SrlTxFaultMajor.h"
#include "PopTripTxFaultMajor.h"
#include "PclTxOverPowerFaultMajor.h"
#include "PclTxConvergenceFaultMajor.h"
#include "Cpri0RemoteAlarmIndFaultMajor.h"
#include "Cpri0SapDefectIndFaultMajor.h"
#include "Cpri0LossOfFrameFaultMajor.h"
#include "Cpri0LossOfSignalFaultMajor.h"
#include "TxOverPowerFaultMajor.h"
#include "TxUnderPowerFaultMinor.h"
#include "TxOverPowerFaultMinor.h"
#include "DpdPllLockFaultMajor.h"
#include "TxPllLockFaultMajor.h"
#include "RxPllLockFaultMajor.h"
#include "RefPllLockFaultMajor.h"
//#include "FpgaUnderTemperatureFaultMajor.h"
#include "BoardTxUnderTemperatureFaultMajor.h"
//#include "FpgaOverTemperatureFaultMajor.h"
#include "BoardTxOverTemperatureFaultMajor.h"
#include "SynthClockFault.h"
#include "TxPowerMeasurementFaultMajor.h"
#include "PaUnderTemperatureFaultMajor.h"

#include "OffTargetFPGA.h"


using namespace Mplane;
using namespace std;


namespace Mplane
{

class RadioStateServiceTestCases: public ::testing::Test
{
protected:
    virtual void SetUp();
    virtual void TearDown();
    virtual bool getAlarm( std::string alarmNameToFind );
    virtual void setAlarm( std::string alarmNameToFind );
    virtual void clearAlarm( std::string alarmNameToFind );
    virtual bool getFault( std::string faultNameToFind );
    virtual void setFault( std::string faultNameToFind );
    virtual void clearFault( std::string faultNameToFind );

    virtual void TestFindAlarmAndUpdateFlag();

    virtual void TestFindAlarmAndReset();

    virtual void TestStateShutdown_SynthClk();

    virtual void TestStateShutdown_OverTemp();

    virtual void TestStateShutdown_UnderTemp();

#if RADIO_PSU_ALARM_IMPLEMENTED
    virtual void TestStateShutdown_UnderVolts();
    virtual void TestStateShutdown_OverVolts();
#endif

    virtual void TestStateShutdown_RxPllLock();
    virtual void TestStateShutdown_RefPllLock();
    virtual void TestStateShutdown_TxPllLock();
    virtual void TestStateShutdown_DpdPllLock();

    virtual void TestStateDegraded_OverPower();
    virtual void TestStateShutdown_OverPower();

    virtual void TestStateShutdown_CpriLos();
    virtual void TestStateShutdown_CpriLof();
    virtual void TestStateShutdown_CpriSdi();
    virtual void TestStateShutdown_CpriRai();

    virtual void TestStateDegraded_PclConvergence();
    virtual void TestStateDegraded_PclOverPower();

    virtual void TestStateDegraded_PopTrip();
    virtual void TestStateDegraded_Srl();

    virtual void TestResetFaultStateTxShutdown();
    virtual void TestResetFaultStateAllPathsShutdown();
    virtual void TestResetFaultStateTxDegrade();

    virtual void TestResetFaultStateFromCarrierEnableAll();
    virtual void TestResetFaultStateFromCarrierEnableTx1();
    virtual void TestResetFaultStateFromCarrierEnableTx2();

    virtual void TestStateDegraded_VswrTx();

    virtual void TestStateDegraded_DpdMinorTx();
    virtual void TestStateDegraded_DpdMajorTx();

    virtual void TestServiceDegradedShutdownOnePath();
    virtual void TestServiceDegradedShutdownAllPaths();

    virtual void TestIssue2710VswrShutdownNotReliable();

    virtual void TestIssue2739RepeatedDegradeAssertion();

#if VSWR_IMPLEMENTED
    virtual void TestStateDegraded_VswrTx1_manualShutdown();
    virtual void TestStateDegraded_VswrTx2_manualShutdown();
#endif
#ifdef NOT_USED
    virtual void TestIssue4187_ClearFaults();
#endif
};

void Mplane::RadioStateServiceTestCases::SetUp()
{
}

void Mplane::RadioStateServiceTestCases::TearDown()
{
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestFindAlarmAndUpdateFlag)
{
	RadioStateServiceTestCases::TestFindAlarmAndUpdateFlag();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestFindAlarmAndUpdateFlag()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<RrhFaults> faults( RrhFaults::getInstance() );
	std::shared_ptr<IFaultsList> faultsList( IFaultsList::getInstance() );

    std::shared_ptr<RrhAlarms> alarms( RrhAlarms::getInstance() );

    std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    ASSERT_FALSE( radioState->getAlarm(alarms->mTxShutdownAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mTxDegradedAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mRxMajorAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mVswrTxAlarm[0]) );

    ASSERT_FALSE( radioState->getAlarm(alarms->mTxShutdownAlarm[1]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mTxDegradedAlarm[1]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mRxMajorAlarm[1]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mVswrTxAlarm[1]) );

    ASSERT_FALSE( radioState->getAlarm(alarms->mRadioTempMajorAlarm) );
//    ASSERT_FALSE( radioState->getAlarm(alarms->mRadioCardPsuAlarm) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mCpri0MajorAlarm) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mHeartBeatAlarm) );

    setAlarm(Mplane::Tx1ShutdownAlarm::NAME);
	setAlarm(Mplane::Tx1DegradedAlarm::NAME);
	setAlarm(Mplane::Rx1MajorAlarm::NAME);
	setAlarm(Mplane::VswrTx1Alarm::NAME);

	setAlarm(Mplane::Tx2ShutdownAlarm::NAME);
	setAlarm(Mplane::Tx2DegradedAlarm::NAME);
	setAlarm(Mplane::Rx2MajorAlarm::NAME);
	setAlarm(Mplane::VswrTx2Alarm::NAME);

	setAlarm(Mplane::RadioTempMajorAlarm::NAME);
//	setAlarm(Mplane::RadioCardPsuAlarm::NAME);
	setAlarm(Mplane::Cpri0MajorAlarm::NAME);
	setAlarm(Mplane::HeartBeatAlarm::NAME);

    ASSERT_TRUE( radioState->getAlarm(alarms->mTxShutdownAlarm[0]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mTxDegradedAlarm[0]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mRxMajorAlarm[0]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mVswrTxAlarm[0]) );

    ASSERT_TRUE( radioState->getAlarm(alarms->mTxShutdownAlarm[1]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mTxDegradedAlarm[1]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mRxMajorAlarm[1]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mVswrTxAlarm[1]) );

    ASSERT_TRUE( radioState->getAlarm(alarms->mRadioTempMajorAlarm) );
//    ASSERT_TRUE( radioState->getAlarm(alarms->mRadioCardPsuAlarm) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mCpri0MajorAlarm) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mHeartBeatAlarm) );

    clearAlarm(Mplane::Tx1ShutdownAlarm::NAME);
	clearAlarm(Mplane::Tx1DegradedAlarm::NAME);
	clearAlarm(Mplane::Rx1MajorAlarm::NAME);
	clearAlarm(Mplane::VswrTx1Alarm::NAME);

	clearAlarm(Mplane::Tx2ShutdownAlarm::NAME);
	clearAlarm(Mplane::Tx2DegradedAlarm::NAME);
	clearAlarm(Mplane::Rx2MajorAlarm::NAME);
	clearAlarm(Mplane::VswrTx2Alarm::NAME);

	clearAlarm(Mplane::RadioTempMajorAlarm::NAME);
//	clearAlarm(Mplane::RadioCardPsuAlarm::NAME);
	clearAlarm(Mplane::Cpri0MajorAlarm::NAME);
	clearAlarm(Mplane::HeartBeatAlarm::NAME);

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestFindAlarmAndReset)
{
	RadioStateServiceTestCases::TestFindAlarmAndReset();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestFindAlarmAndReset()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<RrhFaults> faults( RrhFaults::getInstance() );
	std::shared_ptr<IFaultsList> faultsList( IFaultsList::getInstance() );

    std::shared_ptr<RrhAlarms> alarms( RrhAlarms::getInstance() );

    std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    //ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");
    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    ASSERT_FALSE( radioState->getAlarm(alarms->mTxShutdownAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mTxDegradedAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mRxMajorAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mVswrTxAlarm[0]) );

    ASSERT_FALSE( radioState->getAlarm(alarms->mTxShutdownAlarm[1]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mTxDegradedAlarm[1]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mRxMajorAlarm[1]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mVswrTxAlarm[1]) );

    ASSERT_FALSE( radioState->getAlarm(alarms->mRadioTempMajorAlarm) );
//    ASSERT_FALSE( radioState->getAlarm(alarms->mRadioCardPsuAlarm) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mCpri0MajorAlarm) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mHeartBeatAlarm) );

    // Set Alarms
    setAlarm(Mplane::Tx1ShutdownAlarm::NAME);
	setAlarm(Mplane::Tx1DegradedAlarm::NAME);
	setAlarm(Mplane::Rx1MajorAlarm::NAME);
	setAlarm(Mplane::VswrTx1Alarm::NAME);

	setAlarm(Mplane::Tx2ShutdownAlarm::NAME);
	setAlarm(Mplane::Tx2DegradedAlarm::NAME);
	setAlarm(Mplane::Rx2MajorAlarm::NAME);
	setAlarm(Mplane::VswrTx2Alarm::NAME);

	setAlarm(Mplane::RadioTempMajorAlarm::NAME);
//	setAlarm(Mplane::RadioCardPsuAlarm::NAME);
	setAlarm(Mplane::Cpri0MajorAlarm::NAME);
	setAlarm(Mplane::HeartBeatAlarm::NAME);

	setAlarm(Mplane::Pa1TempMajorAlarm::NAME);
	setAlarm(Mplane::Pa2TempMajorAlarm::NAME);
	setAlarm(Mplane::Tx1BbIqAlarm::NAME);
	setAlarm(Mplane::Tx2BbIqAlarm::NAME);

	setAlarm(Mplane::PllMajorAlarm::NAME);
	setAlarm(Mplane::RadioTempMinorAlarm::NAME);
	setAlarm(Mplane::Pa1TempMinorAlarm::NAME);
	setAlarm(Mplane::Pa2TempMinorAlarm::NAME);

	// Check they are active
    ASSERT_TRUE( radioState->getAlarm(alarms->mTxShutdownAlarm[0]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mTxDegradedAlarm[0]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mRxMajorAlarm[0]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mVswrTxAlarm[0]) );

    ASSERT_TRUE( radioState->getAlarm(alarms->mTxShutdownAlarm[1]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mTxDegradedAlarm[1]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mRxMajorAlarm[1]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mVswrTxAlarm[1]) );

    ASSERT_TRUE( radioState->getAlarm(alarms->mRadioTempMajorAlarm) );
//    ASSERT_TRUE( radioState->getAlarm(alarms->mRadioCardPsuAlarm) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mCpri0MajorAlarm) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mHeartBeatAlarm) );

    ASSERT_TRUE( radioState->getAlarm(alarms->mPaTempMajorAlarm[0]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mPaTempMajorAlarm[1]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mTxBbIqAlarm[0]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mTxBbIqAlarm[1]) );

    ASSERT_TRUE( radioState->getAlarm(alarms->mPllMajorAlarm) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mRadioTempMinorAlarm) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mPaTempMinorAlarm[0]) );
    ASSERT_TRUE( radioState->getAlarm(alarms->mPaTempMinorAlarm[1]) );

    // Reset alarms
	ASSERT_TRUE( radioState->resetAlarm(alarms->mTxShutdownAlarm[0]) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mTxDegradedAlarm[0]) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mRxMajorAlarm[0]) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mVswrTxAlarm[0]) );

	ASSERT_TRUE( radioState->resetAlarm(alarms->mPaTempMajorAlarm[0]) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mPaTempMinorAlarm[0]) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mTxBbIqAlarm[0]) );

	ASSERT_TRUE( radioState->resetAlarm(alarms->mTxShutdownAlarm[1]) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mTxDegradedAlarm[1]) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mRxMajorAlarm[1]) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mVswrTxAlarm[1]) );

	ASSERT_TRUE( radioState->resetAlarm(alarms->mPaTempMajorAlarm[1]) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mPaTempMinorAlarm[1]) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mTxBbIqAlarm[1]) );

	ASSERT_TRUE( radioState->resetAlarm(alarms->mRadioTempMajorAlarm) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mRadioTempMinorAlarm) );
//	ASSERT_TRUE( radioState->resetAlarm(alarms->mRadioCardPsuAlarm) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mCpri0MajorAlarm) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mHeartBeatAlarm) );
	ASSERT_TRUE( radioState->resetAlarm(alarms->mPllMajorAlarm) );

    // Check that they are no longer raised
    ASSERT_FALSE( radioState->getAlarm(alarms->mTxShutdownAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mTxDegradedAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mRxMajorAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mVswrTxAlarm[0]) );

    ASSERT_FALSE( radioState->getAlarm(alarms->mTxShutdownAlarm[1]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mTxDegradedAlarm[1]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mRxMajorAlarm[1]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mVswrTxAlarm[1]) );

    ASSERT_FALSE( radioState->getAlarm(alarms->mRadioTempMajorAlarm) );
//    ASSERT_FALSE( radioState->getAlarm(alarms->mRadioCardPsuAlarm) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mCpri0MajorAlarm) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mHeartBeatAlarm) );

    ASSERT_FALSE( radioState->getAlarm(alarms->mPaTempMajorAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mPaTempMajorAlarm[1]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mTxBbIqAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mTxBbIqAlarm[1]) );

    ASSERT_FALSE( radioState->getAlarm(alarms->mPllMajorAlarm) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mRadioTempMinorAlarm) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mPaTempMinorAlarm[0]) );
    ASSERT_FALSE( radioState->getAlarm(alarms->mPaTempMinorAlarm[1]) );
    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_SynthClk)
{
	RadioStateServiceTestCases::TestStateShutdown_SynthClk();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_SynthClk()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::SynthClockFault::NAME );
    setFault( Mplane::SynthClockFault::NAME );
    setFault( Mplane::SynthClockFault::NAME );
    setFault( Mplane::SynthClockFault::NAME );
    setFault( Mplane::SynthClockFault::NAME );
    setFault( Mplane::SynthClockFault::NAME );
    setFault( Mplane::SynthClockFault::NAME );
    setFault( Mplane::SynthClockFault::NAME );
    setFault( Mplane::SynthClockFault::NAME );
    setFault( Mplane::SynthClockFault::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::SynthClockFault::NAME );
    clearFault( Mplane::SynthClockFault::NAME );
    clearFault( Mplane::SynthClockFault::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );
    clearAlarm( Mplane::Rx1MajorAlarm::NAME );
    clearAlarm( Mplane::Rx2MajorAlarm::NAME );
    clearAlarm( Mplane::Rx3MajorAlarm::NAME );
    clearAlarm( Mplane::Rx4MajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier " << std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_OverTemp)
{
	RadioStateServiceTestCases::TestStateShutdown_OverTemp();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_OverTemp()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults Path 1" << std::endl;

    /* Set faults to cause shut down */
    //setFault( Mplane::FpgaOverTemperatureFaultMajor::NAME );
    setFault( Mplane::BoardTx1OverTemperatureFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    EXPECT_TRUE( getAlarm(Mplane::RadioTempMajorAlarm::NAME) );
    EXPECT_TRUE( getAlarm(Mplane::Tx1ShutdownAlarm::NAME) );

    std::cout << "Clearing faults/alarms" << std::endl;

//    clearFault( Mplane::FpgaOverTemperatureFaultMajor::NAME );
    clearFault( Mplane::BoardTx1OverTemperatureFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::RadioTempMajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    std::cout << "Setting faults Path 2" << std::endl;
    setFault( Mplane::BoardTx2OverTemperatureFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    EXPECT_TRUE( getAlarm(Mplane::RadioTempMajorAlarm::NAME) );
    EXPECT_TRUE( getAlarm(Mplane::Tx2ShutdownAlarm::NAME) );

    std::cout << "Clearing faults/alarms" << std::endl;

//    clearFault( Mplane::FpgaOverTemperatureFaultMajor::NAME );
    clearFault( Mplane::BoardTx2OverTemperatureFaultMajor::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::RadioTempMajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    std::cout << "Setting faults Path 3" << std::endl;
    setFault( Mplane::BoardTx3OverTemperatureFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    EXPECT_TRUE( getAlarm(Mplane::RadioTempMajorAlarm::NAME) );
    EXPECT_TRUE( getAlarm(Mplane::Tx3ShutdownAlarm::NAME) );

    std::cout << "Clearing faults/alarms" << std::endl;

//    clearFault( Mplane::FpgaOverTemperatureFaultMajor::NAME );
    clearFault( Mplane::BoardTx3OverTemperatureFaultMajor::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::RadioTempMajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    std::cout << "Setting faults Path 4" << std::endl;
    setFault( Mplane::BoardTx4OverTemperatureFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    EXPECT_TRUE( getAlarm(Mplane::RadioTempMajorAlarm::NAME) );
    EXPECT_TRUE( getAlarm(Mplane::Tx4ShutdownAlarm::NAME) );

    std::cout << "Clearing faults/alarms" << std::endl;

//    clearFault( Mplane::FpgaOverTemperatureFaultMajor::NAME );
    clearFault( Mplane::BoardTx4OverTemperatureFaultMajor::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );
    clearAlarm( Mplane::RadioTempMajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_UnderTemp)
{
	RadioStateServiceTestCases::TestStateShutdown_UnderTemp();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_UnderTemp()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults Path 1" << std::endl;

    /* Set faults to cause shut down */
//    setFault( Mplane::FpgaUnderTemperatureFaultMajor::NAME );
    setFault( Mplane::BoardTx1UnderTemperatureFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

//    clearFault( Mplane::FpgaUnderTemperatureFaultMajor::NAME );
    clearFault( Mplane::BoardTx1UnderTemperatureFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::RadioTempMajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    std::cout << "Setting faults Path 2" << std::endl;

    /* Set faults to cause shut down */
//    setFault( Mplane::FpgaUnderTemperatureFaultMajor::NAME );
    setFault( Mplane::BoardTx2UnderTemperatureFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

//    clearFault( Mplane::FpgaUnderTemperatureFaultMajor::NAME );
    clearFault( Mplane::BoardTx2UnderTemperatureFaultMajor::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::RadioTempMajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    std::cout << "Setting faults Path 3" << std::endl;

    /* Set faults to cause shut down */
//    setFault( Mplane::FpgaUnderTemperatureFaultMajor::NAME );
    setFault( Mplane::BoardTx3UnderTemperatureFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

//    clearFault( Mplane::FpgaUnderTemperatureFaultMajor::NAME );
    clearFault( Mplane::BoardTx3UnderTemperatureFaultMajor::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::RadioTempMajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    std::cout << "Setting faults Path 4" << std::endl;

    /* Set faults to cause shut down */
//    setFault( Mplane::FpgaUnderTemperatureFaultMajor::NAME );
    setFault( Mplane::BoardTx4UnderTemperatureFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

//    clearFault( Mplane::FpgaUnderTemperatureFaultMajor::NAME );
    clearFault( Mplane::BoardTx4UnderTemperatureFaultMajor::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );
    clearAlarm( Mplane::RadioTempMajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

#if 0

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_UnderVolts)
{
	RadioStateServiceTestCases::TestStateShutdown_UnderVolts();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_UnderVolts()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::RadioCardPsuUnderVoltageFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::RadioCardPsuUnderVoltageFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_OverVolts)
{
	RadioStateServiceTestCases::TestStateShutdown_OverVolts();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_OverVolts()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::RadioCardPsuOverVoltageFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::RadioCardPsuOverVoltageFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}
#endif

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_RxPllLock)
{
	RadioStateServiceTestCases::TestStateShutdown_RxPllLock();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_RxPllLock()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::RxPllLockFaultMajor::NAME );
    setFault( Mplane::RxPllLockFaultMajor::NAME );
    setFault( Mplane::RxPllLockFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::RxPllLockFaultMajor::NAME );
    clearFault( Mplane::RxPllLockFaultMajor::NAME );
    clearFault( Mplane::RxPllLockFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );
    clearAlarm( Mplane::Rx1MajorAlarm::NAME );
    clearAlarm( Mplane::Rx2MajorAlarm::NAME );
    clearAlarm( Mplane::Rx3MajorAlarm::NAME );
    clearAlarm( Mplane::Rx4MajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_RefPllLock)
{
	RadioStateServiceTestCases::TestStateShutdown_RefPllLock();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_RefPllLock()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::RefPllLockFaultMajor::NAME );
    setFault( Mplane::RefPllLockFaultMajor::NAME );
    setFault( Mplane::RefPllLockFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::RefPllLockFaultMajor::NAME );
    clearFault( Mplane::RefPllLockFaultMajor::NAME );
    clearFault( Mplane::RefPllLockFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );
    clearAlarm( Mplane::Rx1MajorAlarm::NAME );
    clearAlarm( Mplane::Rx2MajorAlarm::NAME );
    clearAlarm( Mplane::Rx3MajorAlarm::NAME );
    clearAlarm( Mplane::Rx4MajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_TxPllLock)
{
	RadioStateServiceTestCases::TestStateShutdown_TxPllLock();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_TxPllLock()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::TxPllLockFaultMajor::NAME );
    setFault( Mplane::TxPllLockFaultMajor::NAME );
    setFault( Mplane::TxPllLockFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::TxPllLockFaultMajor::NAME );
    clearFault( Mplane::TxPllLockFaultMajor::NAME );
    clearFault( Mplane::TxPllLockFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_DpdPllLock)
{
	RadioStateServiceTestCases::TestStateShutdown_DpdPllLock();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_DpdPllLock()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::DpdPllLockFaultMajor::NAME );
    setFault( Mplane::DpdPllLockFaultMajor::NAME );
    setFault( Mplane::DpdPllLockFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::DpdPllLockFaultMajor::NAME );
    clearFault( Mplane::DpdPllLockFaultMajor::NAME );
    clearFault( Mplane::DpdPllLockFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateDegraded_OverPower)
{
	RadioStateServiceTestCases::TestStateDegraded_OverPower();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateDegraded_OverPower()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    radioState->service();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL_STANDBY == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

    radioState->service();

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults Path 1" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx1OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx1OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx1OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx1OverPowerFaultMinor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Tx1OverPowerFaultMinor::NAME );
    clearAlarm( Mplane::Tx1DegradedAlarm::NAME );

    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 2" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx2OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMinor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Tx2OverPowerFaultMinor::NAME );
    clearAlarm( Mplane::Tx2DegradedAlarm::NAME );

    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    std::cout << "Setting faults Path 3" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx3OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx3OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx3OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx3OverPowerFaultMinor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Tx3OverPowerFaultMinor::NAME );
    clearAlarm( Mplane::Tx3DegradedAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    std::cout << "Setting faults Path 4" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx4OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx4OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx4OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx4OverPowerFaultMinor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Tx4OverPowerFaultMinor::NAME );
    clearAlarm( Mplane::Tx4DegradedAlarm::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_OverPower)
{
	RadioStateServiceTestCases::TestStateShutdown_OverPower();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_OverPower()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults Path 1" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx1OverPowerFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 2" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 3" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx3OverPowerFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 4" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx4OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx4OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx4OverPowerFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Tx4OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx4OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx4OverPowerFaultMajor::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_CpriLos)
{
	RadioStateServiceTestCases::TestStateShutdown_CpriLos();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_CpriLos()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 0 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    setFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    setFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    setFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    setFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    setFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    clearFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    clearFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    clearFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    clearFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    clearFault( Mplane::Cpri0LossOfSignalFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );
    clearAlarm( Mplane::Cpri0MajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_CpriLof)
{
	RadioStateServiceTestCases::TestStateShutdown_CpriLof();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_CpriLof()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 0 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );
    setFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );
    setFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );
    setFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );
    setFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );
    setFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );
    clearFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );
    clearFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );
    clearFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );
    clearFault( Mplane::Cpri0LossOfFrameFaultMajor::NAME );
    clearFault( Mplane::Cpri0SapDefectIndFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );
    clearAlarm( Mplane::Cpri0MajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_CpriSdi)
{
	RadioStateServiceTestCases::TestStateShutdown_CpriSdi();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_CpriSdi()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 0 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Cpri0SapDefectIndFaultMajor::NAME );
    setFault( Mplane::Cpri0SapDefectIndFaultMajor::NAME );
    setFault( Mplane::Cpri0SapDefectIndFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Cpri0SapDefectIndFaultMajor::NAME );
    clearFault( Mplane::Cpri0SapDefectIndFaultMajor::NAME );
    clearFault( Mplane::Cpri0SapDefectIndFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );
    clearAlarm( Mplane::Cpri0MajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}


/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateShutdown_CpriRai)
{
	RadioStateServiceTestCases::TestStateShutdown_CpriRai();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateShutdown_CpriRai()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 0 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Cpri0RemoteAlarmIndicationFaultMajor::NAME );
    setFault( Mplane::Cpri0RemoteAlarmIndicationFaultMajor::NAME );
    setFault( Mplane::Cpri0RemoteAlarmIndicationFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::Cpri0RemoteAlarmIndicationFaultMajor::NAME );
    clearFault( Mplane::Cpri0RemoteAlarmIndicationFaultMajor::NAME );
    clearFault( Mplane::Cpri0RemoteAlarmIndicationFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );
    clearAlarm( Mplane::Cpri0MajorAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateDegraded_PclConvergence)
{
	RadioStateServiceTestCases::TestStateDegraded_PclConvergence();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateDegraded_PclConvergence()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 0 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults Path 1" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PclTx1ConvergenceFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::PclTx1ConvergenceFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 2" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PclTx2ConvergenceFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::PclTx2ConvergenceFaultMajor::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 3" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PclTx3ConvergenceFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::PclTx3ConvergenceFaultMajor::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 4" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PclTx4ConvergenceFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::PclTx4ConvergenceFaultMajor::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateDegraded_PclOverPower)
{
	RadioStateServiceTestCases::TestStateDegraded_PclOverPower();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateDegraded_PclOverPower()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults Path 1" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PclTx1OverPowerFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::PclTx1OverPowerFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 2" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PclTx2OverPowerFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::PclTx2OverPowerFaultMajor::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 3" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PclTx3OverPowerFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::PclTx3OverPowerFaultMajor::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 4" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PclTx4OverPowerFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults/alarms" << std::endl;

    clearFault( Mplane::PclTx4OverPowerFaultMajor::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateDegraded_PopTrip)
{
	RadioStateServiceTestCases::TestStateDegraded_PopTrip();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateDegraded_PopTrip()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults Path 1" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PopTripTx1FaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    std::cout << std::endl << radioState->updateRadioStateFromAlarms() << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::PopTripTx1FaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 2" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PopTripTx2FaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    std::cout << std::endl << radioState->updateRadioStateFromAlarms() << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::PopTripTx2FaultMajor::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 3" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PopTripTx3FaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    std::cout << std::endl << radioState->updateRadioStateFromAlarms() << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::PopTripTx3FaultMajor::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 4" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::PopTripTx4FaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    std::cout << std::endl << radioState->updateRadioStateFromAlarms() << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::PopTripTx4FaultMajor::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateDegraded_Srl)
{
	RadioStateServiceTestCases::TestStateDegraded_Srl();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateDegraded_Srl()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults Path 1" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::SrlTx1FaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::SrlTx1FaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 2" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::SrlTx2FaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::SrlTx2FaultMajor::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 3" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::SrlTx3FaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::SrlTx3FaultMajor::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 4" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::SrlTx4FaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::SrlTx4FaultMajor::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestResetFaultStateTxShutdown)
{
	RadioStateServiceTestCases::TestResetFaultStateTxShutdown();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestResetFaultStateTxShutdown()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults Path 1" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx1PowerMeasurementFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::Tx1PowerMeasurementFaultMajor::NAME );
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 2" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx2PowerMeasurementFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::Tx2PowerMeasurementFaultMajor::NAME );
    clearAlarm( Mplane::Tx2ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 3" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx3PowerMeasurementFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::Tx3PowerMeasurementFaultMajor::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting faults Path 4" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx4PowerMeasurementFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;

    clearFault( Mplane::Tx4PowerMeasurementFaultMajor::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );

    // Check that state goes back to normal after clearing faults
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestResetFaultStateAllPathsShutdown)
{
	RadioStateServiceTestCases::TestResetFaultStateAllPathsShutdown();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestResetFaultStateAllPathsShutdown()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());

	std::stringstream ss ;
	carrierServer->show( ss ) ;
	std::cerr << ss.str() << std::endl ;

	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx4OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx4OverPowerFaultMajor::NAME );
    setFault( Mplane::Tx4OverPowerFaultMajor::NAME );

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx1OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx2OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx3OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx4OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx4OverPowerFaultMajor::NAME );
    clearFault( Mplane::Tx4OverPowerFaultMajor::NAME );

    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestResetFaultStateTxDegrade)
{
	RadioStateServiceTestCases::TestResetFaultStateTxDegrade();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestResetFaultStateTxDegrade()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting faults Path 1" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx1OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx1OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx1OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx1OverPowerFaultMinor::NAME );

    std::cout << "Checking for degraded state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::Tx1OverPowerFaultMinor::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->updateRadioStateFromAlarms() );

	std::cout << "Setting faults Path 2" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::Tx2OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMinor::NAME );
    setFault( Mplane::Tx2OverPowerFaultMinor::NAME );

    std::cout << "Checking for degraded state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::Tx2OverPowerFaultMinor::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->updateRadioStateFromAlarms() );

	carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestResetFaultStateFromCarrierEnableAll)
{
	RadioStateServiceTestCases::TestResetFaultStateFromCarrierEnableAll();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestResetFaultStateFromCarrierEnableAll()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<RrhFaults> faults( RrhFaults::getInstance() );
	std::shared_ptr<IFaultsList> faultsList( IFaultsList::getInstance() );

    std::shared_ptr<RrhAlarms> alarms( RrhAlarms::getInstance() );

    std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

    Frequency frequency(2115000.0, Frequency::KHz);

    txPorts[0]->setFrequency( frequency );
    txPorts[1]->setFrequency( frequency );

    // Setup a 10Mhz LTE carrier on Tx path 1 & 2
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
    ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

    carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
    carrierSetter.setTxPower( 0 );
    carrierSetter.setTxFrequency(frequency);
    carrierSetter.setRxFrequency(frequency);
    carrierSetter.setGroupSizeUp( 4 );
    carrierSetter.setGroupSizeDown( 4 );
    carrierSetter.setTxScaling( -18.0 );
    carrierSetter.setTxContainer( 0, 1 );
    carrierSetter.setTxContainer( 1, 1 );

    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

    std::cout << "Carrier enabled"<< std::endl;

    std::cout << "Checking for normal state"<< std::endl;

    //std::cout << radioState->updateRadioStateFromAlarms() << std::endl;

    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->updateRadioStateFromAlarms() );

    /* Set alarms */
    setAlarm(Mplane::Tx1ShutdownAlarm::NAME);
	setAlarm(Mplane::Tx1DegradedAlarm::NAME);
	setAlarm(Mplane::Rx1MajorAlarm::NAME);
	setAlarm(Mplane::VswrTx1Alarm::NAME);

	setAlarm(Mplane::Tx2ShutdownAlarm::NAME);
	setAlarm(Mplane::Tx2DegradedAlarm::NAME);
	setAlarm(Mplane::Rx2MajorAlarm::NAME);
	setAlarm(Mplane::VswrTx2Alarm::NAME);

	setAlarm(Mplane::RadioTempMajorAlarm::NAME);
//	setAlarm(Mplane::RadioCardPsuAlarm::NAME);
	setAlarm(Mplane::Cpri0MajorAlarm::NAME);
	setAlarm(Mplane::HeartBeatAlarm::NAME);

	std::cout << "Checking for failed state"<< std::endl;

	ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

	std::cout << "Disabling Carrier"<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Carrier disabled"<< std::endl;

    std::cout << "Enabling Carrier"<< std::endl;

    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

    std::cout << "Carrier enabled"<< std::endl;

    //std::cout << radioState->updateRadioStateFromAlarms() << std::endl;
	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Carrier disabled"<< std::endl;

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestResetFaultStateFromCarrierEnableTx2)
{
	RadioStateServiceTestCases::TestResetFaultStateFromCarrierEnableTx2();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestResetFaultStateFromCarrierEnableTx2()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<RrhFaults> faults( RrhFaults::getInstance() );
	std::shared_ptr<IFaultsList> faultsList( IFaultsList::getInstance() );

    std::shared_ptr<RrhAlarms> alarms( RrhAlarms::getInstance() );

    std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

    Frequency frequency(2115000.0, Frequency::KHz);

    txPorts[0]->setFrequency( frequency );
    txPorts[1]->setFrequency( frequency );

    // Setup a 10Mhz LTE carrier on Tx path 2
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
    ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

    carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
    carrierSetter.setTxPower( 0 );
    carrierSetter.setTxFrequency(frequency);
    carrierSetter.setRxFrequency(frequency);
    carrierSetter.setGroupSizeUp( 4 );
    carrierSetter.setGroupSizeDown( 4 );
    carrierSetter.setTxScaling( -18.0 );
    carrierSetter.setTxContainer( 0, 0 );
    carrierSetter.setTxContainer( 1, 1 );
    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->updateRadioStateFromAlarms() );

    /* Set alarms */
	setAlarm(Mplane::Tx2ShutdownAlarm::NAME);
	setAlarm(Mplane::Tx2DegradedAlarm::NAME);
	setAlarm(Mplane::Rx2MajorAlarm::NAME);
	setAlarm(Mplane::VswrTx2Alarm::NAME);

	setAlarm(Mplane::RadioTempMajorAlarm::NAME);
//	setAlarm(Mplane::RadioCardPsuAlarm::NAME);
	setAlarm(Mplane::Cpri0MajorAlarm::NAME);
	setAlarm(Mplane::HeartBeatAlarm::NAME);

    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestResetFaultStateFromCarrierEnableTx1)
{
	RadioStateServiceTestCases::TestResetFaultStateFromCarrierEnableTx1();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestResetFaultStateFromCarrierEnableTx1()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<RrhFaults> faults( RrhFaults::getInstance() );
	std::shared_ptr<IFaultsList> faultsList( IFaultsList::getInstance() );

    std::shared_ptr<RrhAlarms> alarms( RrhAlarms::getInstance() );

    std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

    Frequency frequency(2115000.0, Frequency::KHz);

    txPorts[0]->setFrequency( frequency );
    txPorts[1]->setFrequency( frequency );

    // Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
    ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

    carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
    carrierSetter.setTxPower( 0 );
    carrierSetter.setTxFrequency(frequency);
    carrierSetter.setRxFrequency(frequency);
    carrierSetter.setGroupSizeUp( 4 );
    carrierSetter.setGroupSizeDown( 4 );
    carrierSetter.setTxScaling( -18.0 );
    carrierSetter.setTxContainer( 0, 1 );
    carrierSetter.setTxContainer( 1, 5 );
    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->updateRadioStateFromAlarms() );

    /* Set alarms */
	setAlarm(Mplane::Tx1ShutdownAlarm::NAME);
	setAlarm(Mplane::Tx1DegradedAlarm::NAME);
	setAlarm(Mplane::Rx1MajorAlarm::NAME);
	setAlarm(Mplane::VswrTx1Alarm::NAME);

	setAlarm(Mplane::RadioTempMajorAlarm::NAME);
//	setAlarm(Mplane::RadioCardPsuAlarm::NAME);
	setAlarm(Mplane::Cpri0MajorAlarm::NAME);
	setAlarm(Mplane::HeartBeatAlarm::NAME);

    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));
    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateDegraded_VswrTx)
{
	RadioStateServiceTestCases::TestStateDegraded_VswrTx();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateDegraded_VswrTx()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting Vswr Tx1 Fault" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::VswrTx1FaultMajor::NAME );

    std::cout << "Checking for degraded state " << std::endl;
    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::VswrTx1FaultMajor::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting Vswr Tx2 Fault" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::VswrTx2FaultMajor::NAME );

    std::cout << "Checking for degraded state " << std::endl;
    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::VswrTx2FaultMajor::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateDegraded_DpdMinorTx)
{
	RadioStateServiceTestCases::TestStateDegraded_DpdMinorTx();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateDegraded_DpdMinorTx()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting DPD Tx1 Minor Fault" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::DpdTx1FaultMinor::NAME );
    setFault( Mplane::DpdTx1FaultMinor::NAME );
    setFault( Mplane::DpdTx1FaultMinor::NAME );

    std::cout << "Checking for degraded state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    //ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::DpdTx1FaultMinor::NAME );
    clearFault( Mplane::DpdTx1FaultMinor::NAME );
    clearFault( Mplane::DpdTx1FaultMinor::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting DPD Tx2 Minor Fault" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::DpdTx2FaultMinor::NAME );
    setFault( Mplane::DpdTx2FaultMinor::NAME );
    setFault( Mplane::DpdTx2FaultMinor::NAME );

    std::cout << "Checking for degraded state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    //ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::DpdTx2FaultMinor::NAME );
    clearFault( Mplane::DpdTx2FaultMinor::NAME );
    clearFault( Mplane::DpdTx2FaultMinor::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateDegraded_DpdMajorTx)
{
	RadioStateServiceTestCases::TestStateDegraded_DpdMajorTx();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateDegraded_DpdMajorTx()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting DPD Tx1 Major Fault" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::DpdTx1FaultMajor::NAME );
    setFault( Mplane::DpdTx1FaultMajor::NAME );
    setFault( Mplane::DpdTx1FaultMajor::NAME );
    setFault( Mplane::DpdTx1FaultMajor::NAME );
    setFault( Mplane::DpdTx1FaultMajor::NAME );
    setFault( Mplane::DpdTx1FaultMajor::NAME );

    std::cout << "Checking for degraded state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::DpdTx1FaultMajor::NAME );
    clearFault( Mplane::DpdTx1FaultMajor::NAME );
    clearFault( Mplane::DpdTx1FaultMajor::NAME );
    clearFault( Mplane::DpdTx1FaultMajor::NAME );
    clearFault( Mplane::DpdTx1FaultMajor::NAME );
    clearFault( Mplane::DpdTx1FaultMajor::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	std::cout << "Setting DPD Tx2 Major Fault" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::DpdTx2FaultMajor::NAME );
    setFault( Mplane::DpdTx2FaultMajor::NAME );
    setFault( Mplane::DpdTx2FaultMajor::NAME );
    setFault( Mplane::DpdTx2FaultMajor::NAME );
    setFault( Mplane::DpdTx2FaultMajor::NAME );
    setFault( Mplane::DpdTx2FaultMajor::NAME );

    std::cout << "Checking for degraded state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::DpdTx2FaultMajor::NAME );
    clearFault( Mplane::DpdTx2FaultMajor::NAME );
    clearFault( Mplane::DpdTx2FaultMajor::NAME );
    clearFault( Mplane::DpdTx2FaultMajor::NAME );
    clearFault( Mplane::DpdTx2FaultMajor::NAME );
    clearFault( Mplane::DpdTx2FaultMajor::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestServiceDegradedShutdownOnePath)
{
	RadioStateServiceTestCases::TestServiceDegradedShutdownOnePath();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestServiceDegradedShutdownOnePath()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<RrhFaults> faults( RrhFaults::getInstance() );
	std::shared_ptr<IFaultsList> faultsList( IFaultsList::getInstance() );

    std::shared_ptr<RrhAlarms> alarms( RrhAlarms::getInstance() );

    std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

    Frequency frequency(2115000.0, Frequency::KHz);

    txPorts[0]->setFrequency( frequency );
    txPorts[1]->setFrequency( frequency );

    // Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
    ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

    carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
    carrierSetter.setTxPower( 0 );
    carrierSetter.setTxFrequency(frequency);
    carrierSetter.setRxFrequency(frequency);
    carrierSetter.setGroupSizeUp( 4 );
    carrierSetter.setGroupSizeDown( 4 );
    carrierSetter.setTxScaling( -18.0 );
    carrierSetter.setTxContainer( 0, 1 );
    carrierSetter.setTxContainer( 1, 5 );
    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

    radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    /* Set alarms Path 1 */
	setAlarm(Mplane::Tx1DegradedAlarm::NAME);

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    EXPECT_TRUE(carrierServer->isTxActivePath(0));

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    radioState->service();
	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    /* Set alarms Path 2*/
	setAlarm(Mplane::Tx2DegradedAlarm::NAME);

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    EXPECT_TRUE(carrierServer->isTxActivePath(1));

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    radioState->service();
	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    /* Set alarms Path 3*/
	setAlarm(Mplane::Tx3DegradedAlarm::NAME);

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );
    clearAlarm(Mplane::Tx3DegradedAlarm::NAME);

    radioState->service();
	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    /* Set alarms Path 4*/
	setAlarm(Mplane::Tx4DegradedAlarm::NAME);

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );
    clearAlarm(Mplane::Tx4DegradedAlarm::NAME);

    radioState->service();
	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

	carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestServiceDegradedShutdownAllPaths)
{
	RadioStateServiceTestCases::TestServiceDegradedShutdownAllPaths();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestServiceDegradedShutdownAllPaths()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<RrhFaults> faults( RrhFaults::getInstance() );
	std::shared_ptr<IFaultsList> faultsList( IFaultsList::getInstance() );

    std::shared_ptr<RrhAlarms> alarms( RrhAlarms::getInstance() );

    std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

    Frequency frequency(2115000.0, Frequency::KHz);

    txPorts[0]->setFrequency( frequency );
    txPorts[1]->setFrequency( frequency );

    // Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
    ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

    carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
    carrierSetter.setTxPower( 0 );
    carrierSetter.setTxFrequency(frequency);
    carrierSetter.setRxFrequency(frequency);
    carrierSetter.setGroupSizeUp( 4 );
    carrierSetter.setGroupSizeDown( 4 );
    carrierSetter.setTxScaling( -18.0 );
    carrierSetter.setTxContainer( 0, 1 );
    carrierSetter.setTxContainer( 1, 1 );
    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

    radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    /* Set degraded alarm on Path 1 */
	setAlarm( Mplane::Tx1ShutdownAlarm::NAME);

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    /* Set degraded alarm on Path 2*/
	setAlarm( Mplane::VswrTx2Alarm::NAME);

	radioState->service();
	ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    /* Set degraded alarm on Path 3 */
	setAlarm( Mplane::Tx3ShutdownAlarm::NAME);

	radioState->service();
	ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    /* Set degraded alarm on Path 4 */
	setAlarm( Mplane::VswrTx4Alarm::NAME);

	radioState->service();

	// As all paths are degraded, it should fail
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->getState() );


    // If one of the alarms is cleared it should go to degraded
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME);
    radioState->service();
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    // If all alarms are cleared it should go back to Normal
    clearAlarm( Mplane::VswrTx4Alarm::NAME);
    clearAlarm( Mplane::VswrTx2Alarm::NAME);
    clearAlarm( Mplane::Tx1ShutdownAlarm::NAME);

    radioState->service();
    radioState->showRadioState();
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestIssue2710VswrShutdownNotReliable)
{
	RadioStateServiceTestCases::TestIssue2710VswrShutdownNotReliable();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestIssue2710VswrShutdownNotReliable()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<RrhFaults> faults( RrhFaults::getInstance() );
	std::shared_ptr<IFaultsList> faultsList( IFaultsList::getInstance() );

    std::shared_ptr<RrhAlarms> alarms( RrhAlarms::getInstance() );

    std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

    Frequency frequency(2115000.0, Frequency::KHz);

    txPorts[0]->setFrequency( frequency );
    txPorts[1]->setFrequency( frequency );

    // Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
    ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

    carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
    carrierSetter.setTxPower( 0 );
    carrierSetter.setTxFrequency(frequency);
    carrierSetter.setRxFrequency(frequency);
    carrierSetter.setGroupSizeUp( 4 );
    carrierSetter.setGroupSizeDown( 4 );
    carrierSetter.setTxScaling( -18.0 );
    carrierSetter.setTxContainer( 0, 1 );
    carrierSetter.setTxContainer( 1, 1 );
    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

    radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );
    //EXPECT_TRUE(txPorts[0]->isTxOn());
    //EXPECT_TRUE(txPorts[1]->isTxOn());

    /* Set degraded alarm */
	setAlarm( Mplane::Tx1DegradedAlarm::NAME);

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );
    //EXPECT_TRUE(txPorts[0]->isTxOn());
    //EXPECT_TRUE(txPorts[1]->isTxOn());

    /* Set another degraded alarm */
	setAlarm( Mplane::Tx2DegradedAlarm::NAME);

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );
    //EXPECT_TRUE(txPorts[0]->isTxOn());
    //EXPECT_TRUE(txPorts[1]->isTxOn());

    /* Set vswr tx 1 alarm, but this time it should fail! */
	setAlarm( Mplane::VswrTx1Alarm::NAME);

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->getState() );

    //EXPECT_FALSE(txPorts[0]->isTxOn());
    //EXPECT_TRUE(txPorts[1]->isTxOn());

    /* Set vswr tx 2 alarm, but this time it should fail! */
	setAlarm( Mplane::VswrTx2Alarm::NAME);
	setAlarm( Mplane::VswrTx3Alarm::NAME);
	setAlarm( Mplane::VswrTx4Alarm::NAME);

	radioState->service();

    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->getState() );

    //EXPECT_FALSE(txPorts[0]->isTxOn());
    //EXPECT_FALSE(txPorts[1]->isTxOn());

    radioState->service();

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	clearAlarm( Mplane::VswrTx3Alarm::NAME);
	clearAlarm( Mplane::VswrTx4Alarm::NAME);

    radioState->service();

    radioState->showRadioState();

    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestIssue2739RepeatedDegradeAssertion)
{
	RadioStateServiceTestCases::TestIssue2739RepeatedDegradeAssertion();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestIssue2739RepeatedDegradeAssertion()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    radioState->service();

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 1 );

	radioState->service();

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	radioState->service();

	std::cout << "Setting DPD Tx1 Major Fault" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::DpdTx1FaultMajor::NAME );
    setFault( Mplane::DpdTx1FaultMajor::NAME );
    setFault( Mplane::DpdTx1FaultMajor::NAME );
    setFault( Mplane::DpdTx1FaultMajor::NAME );
    setFault( Mplane::DpdTx1FaultMajor::NAME );
    setFault( Mplane::DpdTx1FaultMajor::NAME );

    radioState->service();

    std::cout << "Checking for degraded state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_DEGRADED == radioState->updateRadioStateFromAlarms() );

    radioState->service();
    radioState->service();
    radioState->service();
    radioState->service();
    radioState->service();

	std::cout << "Setting DPD Tx2 Major Fault" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::DpdTx2FaultMajor::NAME );
    setFault( Mplane::DpdTx2FaultMajor::NAME );
    setFault( Mplane::DpdTx2FaultMajor::NAME );
    setFault( Mplane::DpdTx2FaultMajor::NAME );
    setFault( Mplane::DpdTx2FaultMajor::NAME );
    setFault( Mplane::DpdTx2FaultMajor::NAME );

    setFault( Mplane::DpdTx3FaultMajor::NAME );
    setFault( Mplane::DpdTx3FaultMajor::NAME );
    setFault( Mplane::DpdTx3FaultMajor::NAME );
    setFault( Mplane::DpdTx3FaultMajor::NAME );
    setFault( Mplane::DpdTx3FaultMajor::NAME );
    setFault( Mplane::DpdTx3FaultMajor::NAME );

    setFault( Mplane::DpdTx4FaultMajor::NAME );
    setFault( Mplane::DpdTx4FaultMajor::NAME );
    setFault( Mplane::DpdTx4FaultMajor::NAME );
    setFault( Mplane::DpdTx4FaultMajor::NAME );
    setFault( Mplane::DpdTx4FaultMajor::NAME );
    setFault( Mplane::DpdTx4FaultMajor::NAME );

    radioState->service();

    std::cout << "Checking for failed state " << std::endl;

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_FAILED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_FAILED == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::DpdTx1FaultMajor::NAME );
    clearFault( Mplane::DpdTx1FaultMajor::NAME );
    clearFault( Mplane::DpdTx1FaultMajor::NAME );

    clearFault( Mplane::DpdTx2FaultMajor::NAME );
    clearFault( Mplane::DpdTx2FaultMajor::NAME );
    clearFault( Mplane::DpdTx2FaultMajor::NAME );

    clearFault( Mplane::DpdTx3FaultMajor::NAME );
    clearFault( Mplane::DpdTx3FaultMajor::NAME );
    clearFault( Mplane::DpdTx3FaultMajor::NAME );
    clearAlarm( Mplane::Tx3ShutdownAlarm::NAME );

    clearFault( Mplane::DpdTx4FaultMajor::NAME );
    clearFault( Mplane::DpdTx4FaultMajor::NAME );
    clearFault( Mplane::DpdTx4FaultMajor::NAME );
    clearAlarm( Mplane::Tx4ShutdownAlarm::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

#if VSWR_IMPLEMENTED
/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateDegraded_VswrTx1_manualShutdown)
{
	RadioStateServiceTestCases::TestStateDegraded_VswrTx1_manualShutdown();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateDegraded_VswrTx1_manualShutdown()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    std::shared_ptr<IVswr> vswr = IVswr::getInstance( 0 );
    vswr->setShutdownMode( IVswr::vswrShutdownMode_T::manual);

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 1 );
	carrierSetter.setTxContainer( 1, 5 );

	std::cout << "Enabling carrier " << std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	std::cout << "Carrier Enabled" << std::endl;

	std::cout << "Setting Vswr Tx1 Fault" << std::endl;

    /* Set faults to cause shut down */
    setFault( Mplane::VswrTx1FaultMajor::NAME );

    std::cout << "Checking for degraded state " << std::endl;
    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->updateRadioStateFromAlarms() );

    std::cout << "Clearing faults" << std::endl;
    clearFault( Mplane::VswrTx1FaultMajor::NAME );

    // Clear down all the alarms by toggling the carrier's.
    std::cout << "Disabling carrier "<< std::endl;

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    std::cout << "Enabling carrier "<< std::endl;

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

	std::cout << "Checking for normal state"<< std::endl;
	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestStateDegraded_VswrTx2_manualShutdown)
{
	RadioStateServiceTestCases::TestStateDegraded_VswrTx2_manualShutdown();
}

/* ------------------------------------------------------------------------- */
void Mplane::RadioStateServiceTestCases::TestStateDegraded_VswrTx2_manualShutdown()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    RadioStateService * radioState = new RadioStateService();

    std::shared_ptr<IVswr> vswr = IVswr::getInstance( 0 );
    vswr->setShutdownMode( IVswr::vswrShutdownMode_T::manual);

    ASSERT_TRUE(radioState != 0);

    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");

    radioState->showRadioState();

    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );

	Frequency frequency(2115000.0, Frequency::KHz);

	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );

	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 0 );
	carrierSetter.setTxContainer( 1, 1 );
	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

    /* Set faults to cause shut down */
    setFault( Mplane::VswrTx2FaultMajor::NAME );

    /* Test the updateRadioStateFromMap() method - RADIO_STATE_DEGRADED */
    ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->updateRadioStateFromAlarms() );

    clearFault( Mplane::VswrTx2FaultMajor::NAME );

    // Clear down all the faults and alarms by toggling the carrier's.
    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();

	ASSERT_TRUE( IRadioState::RADIO_STATE_NORMAL == radioState->getState() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    delete radioState;
}
#endif

#ifdef NOT_USED
// NOTE: I've completely failed to reproduce this issue in the following test. May need to come back to this if
// the fix turns out to not completely work

/* ************************************************************************** */
TEST_F(RadioStateServiceTestCases, TestIssue4187_ClearFaults)
{
	RadioStateServiceTestCases::TestIssue4187_ClearFaults();
}
void Mplane::RadioStateServiceTestCases::TestIssue4187_ClearFaults()
{
	// NOTE: This relies on the previous tests being run

	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NONE) ;
    ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "RadioStateService");
    ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "FT");
    ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "AL");

    OffTargetFPGA& fpgaEmu( OffTargetFPGA::getInstance() ) ;
    fpgaEmu.writeField("txPllLockAlarm", 1) ;
    std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

    std::shared_ptr<RadioStateService> radioState(std::make_shared<RadioStateService>());
    ASSERT_TRUE(radioState.get() != nullptr);
    radioState->showRadioState();

    std::cout << "Checking initial state" << std::endl;
    ASSERT_TRUE( IRadioState::RADIO_STATE_INITIAL == radioState->getState() );

	radioState->service();
    radioState->showRadioState();

    // update faults
    std::cerr << "Should show TX PLL fault" << std::endl ;
    faultsList->updateFaults() ;
    faultsList->updateFaults() ;
    faultsList->updateFaults() ;
    faultsList->show() ;

	radioState->service();
    radioState->showRadioState();

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );
	Frequency frequency(2115000.0, Frequency::KHz);
	txPorts[0]->setFrequency( frequency );
	txPorts[1]->setFrequency( frequency );

	// Setup a 10Mhz LTE carrier on Tx path 1
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());
	ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );
	carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
	carrierSetter.setTxPower( 0 );
	carrierSetter.setTxFrequency(frequency);
	carrierSetter.setRxFrequency(frequency);
	carrierSetter.setGroupSizeUp( 4 );
	carrierSetter.setGroupSizeDown( 4 );
	carrierSetter.setTxScaling( -18.0 );
	carrierSetter.setTxContainer( 0, 0 );
	carrierSetter.setTxContainer( 1, 1 );
	carrierSetter.setState(ICarrier::STATE_ENABLE);
    std::cout << "Enabling carrier "<< std::endl;
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();
    radioState->showRadioState();
	EXPECT_EQ( IRadioState::RADIO_STATE_NORMAL, radioState->getState() );

    // toggle carrier enable to try clearing alarms
    std::cout << "Disabling carrier "<< std::endl;
	carrierSetter.setState(ICarrier::STATE_DISABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));
	radioState->service();
    radioState->showRadioState();

    std::cout << "Enabling carrier "<< std::endl;
	carrierSetter.setState(ICarrier::STATE_ENABLE);
	EXPECT_TRUE(carrierServer->setCarrier(carrierSetter));

	radioState->service();
    radioState->showRadioState();
	EXPECT_EQ( IRadioState::RADIO_STATE_NORMAL, radioState->getState() );


	std::cout << "** TEST END **" << std::endl ;
    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));
    clearFault( Mplane::Pa1UnderTemperatureFaultMajor::NAME );

}
#endif

// ----------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void Mplane::RadioStateServiceTestCases::setAlarm( std::string alarmNameToFind )
{
	std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;
	std::vector<std::shared_ptr<IAlarm>> alarms(alarmsList->getAlarms()) ;

	bool alarmFound = false;

	for (auto alarm : alarms)
	{
		std::string alarmName = alarm->getName() ;

		if( alarmName == alarmNameToFind )
		{
			alarm->setStatus(true);

			std::cout << "Set - Alarm found :" << alarmNameToFind.c_str() << std::endl;
			alarmFound = true;

			return;
		}
	}

	if( false == alarmFound )
	{
		std::cout << "Set - Alarm not found :" << alarmNameToFind.c_str() << std::endl;
	}
}

bool Mplane::RadioStateServiceTestCases::getAlarm( std::string alarmNameToFind )
{
	std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;
	std::vector<std::shared_ptr<IAlarm>> alarms(alarmsList->getAlarms()) ;

	bool alarmFound = false;

	for (auto alarm : alarms)
	{
		std::string alarmName = alarm->getName() ;

		if( alarmName == alarmNameToFind )
		{
			return alarm->isAlarmActive() ;
		}
	}

	if( false == alarmFound )
	{
		std::cout << "Get - Alarm not found :" << alarmNameToFind.c_str() << std::endl;
	}

	return false;
}

void Mplane::RadioStateServiceTestCases::clearAlarm( std::string alarmNameToFind )
{
	std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;
	std::vector<std::shared_ptr<IAlarm>> alarms(alarmsList->getAlarms()) ;

	bool alarmFound = false;

	for (auto alarm : alarms)
	{
		std::string alarmName = alarm->getName() ;

		if( alarmName == alarmNameToFind )
		{
			alarm->setStatus(false);

			std::cout << "Clear - Alarm found :" << alarmNameToFind.c_str() << std::endl;
			alarmFound = true;

			return;
		}
	}

	if( false == alarmFound )
	{
		std::cout << "Clear - Alarm not found :" << alarmNameToFind.c_str() << std::endl;
	}
}

void Mplane::RadioStateServiceTestCases::setFault( std::string faultNameToFind )
{
	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

	std::shared_ptr<IFault> fault( faultsList->getFault( faultNameToFind ) );

	fault->setStatus( true );
}

void Mplane::RadioStateServiceTestCases::clearFault( std::string faultNameToFind )
{
	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

	std::shared_ptr<IFault> fault( faultsList->getFault( faultNameToFind ) );

	fault->setStatus( false );
}

bool Mplane::RadioStateServiceTestCases::getFault( std::string faultNameToFind )
{
	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

	std::shared_ptr<IFault> fault( faultsList->getFault( faultNameToFind ) );

	return fault->isFaultPresent();
}

} // end namespace
