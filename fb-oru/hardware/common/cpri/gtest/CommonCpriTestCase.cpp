/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCpriTestCase.cpp
 * \brief     Implementation of the CppUnit test harness for CommonCpri classes
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the CommonCpri classes.
 *
 */



#include "gtest/gtest.h"
#include <string.h>
#include <iostream>

#include "IFpgaMgr.h"
#include "CommonCpri.h"
#include "CommonCpriCore.h"
#include "CommonCpriTestCase.h"
#include "CommonRadio.h"

#include "OffTargetFPGA.h"

using namespace std;
using namespace Mplane;

/*
 * Unit tests
 */
void CommonCpriTestCase::testCreation()
{
    cout << endl << "*** CommonCpriTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

   // ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL) ;

    std::shared_ptr<CommonCpriCore> ccc = std::shared_ptr<CommonCpriCore>(new CommonCpriCore(0, ICpri::CpriPortSlave));

//    ASSERT_TRUE(ccc->mFpga->isInitComplete() == false);

    ASSERT_TRUE(ccc->mCoreId == CPRI_SLAVE_CORE);
    ASSERT_TRUE(ccc->mFibre == 0);
    ASSERT_TRUE(ccc->mCpriReIdIsZeroCount == 0);

    ASSERT_TRUE(IFibre::getInterface()->getFibreType() == IFibre::FibreTypeCpri);
    ASSERT_TRUE(IFibre::getInterface()->getFibreClockSyncSource() == 0);

    std::shared_ptr<CommonCpriCore> ccc2 = std::shared_ptr<CommonCpriCore>(new CommonCpriCore(1, ICpri::CpriPortMaster));

//    ASSERT_TRUE(ccc2->mFpga->isInitComplete() == false);
    ASSERT_TRUE(ccc2->mCoreId == CPRI_MASTER_CORE);
    ASSERT_TRUE(ccc2->mFibre == 1);
    ASSERT_TRUE(ccc2->mCpriReIdIsZeroCount == 0);

// Causes test to fail as there are only 2 ports.
#if 0
    // Another slave port
    std::shared_ptr<CommonCpriCore> ccc3 = std::shared_ptr<CommonCpriCore>(new CommonCpriCore(2, ICpri::CpriPortSlave));

//    ASSERT_TRUE(ccc3->mFpga->isInitComplete() == false);
    ASSERT_TRUE(ccc3->mCoreId == CPRI_SLAVE_CORE);
    ASSERT_TRUE(ccc3->mFibre == 2);
    ASSERT_TRUE(ccc3->mCpriReIdIsZeroCount == 0);
#endif

    ccc->show();
    ccc2->show();

    // Don't call show on ccc3 since it's invalid and when the fpga cpri status reg is read it will read back as invalid (and cause
    // a critical error
//    ccc3->show();

    cout << __func__ << " - END" <<  endl;
}

void CommonCpriTestCase::testCpriCoreSlaveAccess()
{
    cout << __func__ << " - START" <<  endl;

    // create a slave CPRI core
    std::shared_ptr<CommonCpriCore> cccSlave = std::shared_ptr<CommonCpriCore>(new CommonCpriCore(0, ICpri::CpriPortSlave));

    auto commonFpga = IFpgaMgr::getIFpgaFibreRegs() ;
    std::shared_ptr<OffTargetFPGA> OffTargetFPGA = OffTargetFPGA::getInstance();
    UINT32 mFibre = 0;
    UINT16 rdVal = 0;

    // take CPRI core out of reset
    cccSlave->takeCoreOutOfReset();
    ASSERT_TRUE(commonFpga->read_fibreBlkReset(mFibre) == 0);
    ASSERT_TRUE(cccSlave->isCoreOutOfReset() == true);

    // put CPRI core into reset
    cccSlave->putCoreIntoReset();
    ASSERT_TRUE(commonFpga->read_fibreBlkReset(mFibre) == 1);
    ASSERT_TRUE(cccSlave->isCoreOutOfReset() == false);

    // reset CPRI core
    cccSlave->resetCore();
    ASSERT_TRUE(cccSlave->isCoreOutOfReset() == true);

    // check slave mode
    ASSERT_TRUE(cccSlave->isSlave() == true);
    ASSERT_TRUE(cccSlave->isMaster() == false);

    // check the CPRI core status
    // set initial status to RESET
    OffTargetFPGA->writeField("StatCode[0]", IFpgaCpri::CPRI_RESET);
    ASSERT_TRUE(cccSlave->getStatusCode() == ICpriCore::RESET);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getStatusCodeString(cccSlave->getStatusCode()), "RESET") == 0);
    OffTargetFPGA->writeField("StatCode[0]", IFpgaCpri::CPRI_L1_SYNC);
    ASSERT_TRUE(cccSlave->getStatusCode() == ICpriCore::ATTEMPTING_L1_SYNCH);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getStatusCodeString(cccSlave->getStatusCode()), "ATTEMPTING_L1_SYNCH") == 0);
    OffTargetFPGA->writeField("StatCode[0]", IFpgaCpri::CPRI_VERSION_SETUP);
    ASSERT_TRUE(cccSlave->getStatusCode() == ICpriCore::PROTOCOL_VERSION_SETUP);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getStatusCodeString(cccSlave->getStatusCode()), "PROTOCOL_VERSION_SETUP") == 0);
    OffTargetFPGA->writeField("StatCode[0]", IFpgaCpri::CPRI_PARAM_SETUP);
    ASSERT_TRUE(cccSlave->getStatusCode() == ICpriCore::CM_PARAM_SETUP);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getStatusCodeString(cccSlave->getStatusCode()), "CM_PARAM_SETUP") == 0);
    OffTargetFPGA->writeField("StatCode[0]", IFpgaCpri::CPRI_PASSIVE_MODE);
    ASSERT_TRUE(cccSlave->getStatusCode() == ICpriCore::PASSIVE_MODE);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getStatusCodeString(cccSlave->getStatusCode()), "PASSIVE_MODE") == 0);
    OffTargetFPGA->writeField("StatCode[0]", IFpgaCpri::CPRI_OPERATIONAL);
    ASSERT_TRUE(cccSlave->getStatusCode() == ICpriCore::OPERATIONAL);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getStatusCodeString(cccSlave->getStatusCode()), "OPERATIONAL") == 0);

    // set the preferred protocol value
    UINT16 prefProtValue = 0x12; // unreal value
    cccSlave->setPreferredProtocolVersion(prefProtValue);
    ASSERT_TRUE(cccSlave->getPreferredProtocolVersion() == prefProtValue);
    prefProtValue = 0x02; // real value
    cccSlave->setPreferredProtocolVersion(prefProtValue);
    ASSERT_TRUE(cccSlave->getPreferredProtocolVersion() == prefProtValue);

    // set the status alarm to not on
    OffTargetFPGA->writeField("statAlarm[0]", 0x00);
    ASSERT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);
    // set the status alarm to on
    OffTargetFPGA->writeField("statAlarm[0]", 0x01);
    ASSERT_TRUE(cccSlave->isAlarmCurrentlyActive() == true);

    ICpriCore::RemoteAlarms remoteAlarms = cccSlave->readRemoteAlarms();
    ASSERT_TRUE(remoteAlarms.remoteLOS == 0);
    ASSERT_TRUE(remoteAlarms.remoteLOF == 0);
    ASSERT_TRUE(remoteAlarms.remoteRAI == 0);
    ASSERT_TRUE(remoteAlarms.remoteSDI == 0);
    ASSERT_TRUE(remoteAlarms.remoteRST == 0);

    // set no LOS alarm
    OffTargetFPGA->writeField("los[0]", 0x00);
    ASSERT_TRUE(cccSlave->haveLOS() == false);
    // set LOS alarm
    OffTargetFPGA->writeField("los[0]", 0x01);
    ASSERT_TRUE(cccSlave->haveLOS() == true);

    // set no LOF alarm
    OffTargetFPGA->writeField("lof[0]", 0x00);
    ASSERT_TRUE(cccSlave->haveLOF() == false);
    // set LOF alarm
    OffTargetFPGA->writeField("lof[0]", 0x01);
    ASSERT_TRUE(cccSlave->haveLOF() == true);

    // Reset fields
    OffTargetFPGA->writeField("los[0]", 0x00);
    OffTargetFPGA->writeField("lof[0]", 0x00);

    // set the current ethernet pointer value
    OffTargetFPGA->writeReg(0x40212, 0x20);
    ASSERT_TRUE(cccSlave->getCurrentEthernetPointer() == 0x20);
    OffTargetFPGA->writeReg(0x40212, 0x3f);
    ASSERT_TRUE(cccSlave->getCurrentEthernetPointer() == 0x3f);

    // unsupported interface by FPGA
    ASSERT_TRUE(cccSlave->readRxSubChannel2Word0() == 0); // not supported by FPGA, no action taken
    ASSERT_TRUE(cccSlave->readRxSubChannel2Word1() == 0); // not supported by FPGA, no action taken
    ASSERT_TRUE(cccSlave->readRxSubChannel2Word2() == 0); // not supported by FPGA, no action taken
    ASSERT_TRUE(cccSlave->readRxSubChannel2Word3() == 0); // not supported by FPGA, no action taken

    // test the resetting of the ethernet.
    // preset the ethernet reset register value to 0x01
    OffTargetFPGA->writeReg(0x40234, 0x01);
    bool valid = OffTargetFPGA->readReg(0x40234, &rdVal);
    ASSERT_TRUE(valid);
    ASSERT_TRUE(rdVal == 0x01);
    cccSlave->cpriResetEthernet();
    valid = OffTargetFPGA->readReg(0x40234, &rdVal);
    ASSERT_TRUE(rdVal == 0x00);
    OffTargetFPGA->writeReg(0x40234, 0x01);
    valid = OffTargetFPGA->readReg(0x40234, &rdVal);
    ASSERT_TRUE(rdVal == 0x01);
    cccSlave->cpriResetEthernetTx(); // not supported by FPGA
    valid = OffTargetFPGA->readReg(0x40234, &rdVal);
    ASSERT_TRUE(rdVal == 0x01);
    cccSlave->cpriResetEthernetRx(); // not supported by FPGA
    valid = OffTargetFPGA->readReg(0x40234, &rdVal);
    ASSERT_TRUE(rdVal == 0x01);
    cccSlave->cpriResetEthernet();
    valid = OffTargetFPGA->readReg(0x40234, &rdVal);
    ASSERT_TRUE(rdVal == 0x00);

    // Write to register to set the barrel shift to non-zero
    OffTargetFPGA->writeReg(0x40218, 0x21);
    valid = OffTargetFPGA->readReg(0x40218, &rdVal);
    ASSERT_TRUE(rdVal == 0x21);
    // Read barrel shift
    ASSERT_TRUE(cccSlave->getGTPBarrelShiftPos() == 0x21);
    // set the barrel shift
    cccSlave->setGTPBarrelShiftPos(0x32);  // not supported by FPGA
    ASSERT_TRUE(cccSlave->getGTPBarrelShiftPos() == 0x21);

    // Write to register to set the preferred ethernet pointer to non-zero
    OffTargetFPGA->writeReg(0x40206, 20);
    valid = OffTargetFPGA->readReg(0x40206, &rdVal);
    ASSERT_TRUE(rdVal == 20);
    ASSERT_TRUE(cccSlave->getPreferredEthernetPointer() == 20);

    // write the preferred ethernet pointer
    cccSlave->setPreferredEthernetPointer(0x3f);
    ASSERT_TRUE(cccSlave->getPreferredEthernetPointer() == 0x3f);
    valid = OffTargetFPGA->readReg(0x40206, &rdVal);
    ASSERT_TRUE(rdVal == 0x3f);

    // Test the line rates
    OffTargetFPGA->writeReg(0x40210, 0x40);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate9830_4);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentLineRateString(cccSlave->getCurrentLineRate()), "9830.4") == 0);
    OffTargetFPGA->writeReg(0x40210, 0x20);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate6144_0);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentLineRateString(cccSlave->getCurrentLineRate()), "6144.0") == 0);
    OffTargetFPGA->writeReg(0x40210, 0x10);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate4915_2);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentLineRateString(cccSlave->getCurrentLineRate()), "4915.2") == 0);
    OffTargetFPGA->writeReg(0x40210, 0x08);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate3072_0);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentLineRateString(cccSlave->getCurrentLineRate()), "3072.0") == 0);
    OffTargetFPGA->writeReg(0x40210, 0x04);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate2457_6);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentLineRateString(cccSlave->getCurrentLineRate()), "2457.6") == 0);
    OffTargetFPGA->writeReg(0x40210, 0x02);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate1228_8);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentLineRateString(cccSlave->getCurrentLineRate()), "1228.8") == 0);
    OffTargetFPGA->writeReg(0x40210, 0x01);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate614_4);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentLineRateString(cccSlave->getCurrentLineRate()), "614.4") == 0);

    // Read the line rate capability - this is now determined by the SfpData object, which for testbench purposes is set to 3100M
    ICpriCore::LineRateCapability rateCap = cccSlave->getLineRateCapability();
    ASSERT_TRUE(rateCap.capableOfRate614_4 == true);
    ASSERT_TRUE(rateCap.capableOfRate1228_8 == true);
    ASSERT_TRUE(rateCap.capableOfRate2457_6 == true);
    ASSERT_TRUE(rateCap.capableOfRate3072_0 == true);
    ASSERT_TRUE(rateCap.capableOfRate4915_2 == true);
    ASSERT_TRUE(rateCap.capableOfRate6144_0 == true);
    ASSERT_TRUE(rateCap.capableOfRate9830_4 == true);

//    // Test the line rate capability, start off at zero
//    OffTargetFPGA->writeReg(0x40204, 0x00);
//    ICpriCore::LineRateCapability rateCap = cccSlave->getLineRateCapability();
//    ASSERT_TRUE(rateCap.capableOfRate614_4 == false);
//    ASSERT_TRUE(rateCap.capableOfRate1228_8 == false);
//    ASSERT_TRUE(rateCap.capableOfRate2457_6 == false);
//    ASSERT_TRUE(rateCap.capableOfRate3072_0 == false);
//    ASSERT_TRUE(rateCap.capableOfRate4915_2 == false);
//    ASSERT_TRUE(rateCap.capableOfRate6144_0 == false);
//    ASSERT_TRUE(rateCap.capableOfRate9830_4 == false);
//    // now test with one bit set
//    OffTargetFPGA->writeReg(0x40204, 0x01);
//    rateCap = cccSlave->getLineRateCapability();
//    ASSERT_TRUE(rateCap.capableOfRate614_4 == true);
//    ASSERT_TRUE(rateCap.capableOfRate1228_8 == false);
//    ASSERT_TRUE(rateCap.capableOfRate2457_6 == false);
//    ASSERT_TRUE(rateCap.capableOfRate3072_0 == false);
//    ASSERT_TRUE(rateCap.capableOfRate4915_2 == false);
//    ASSERT_TRUE(rateCap.capableOfRate6144_0 == false);
//    ASSERT_TRUE(rateCap.capableOfRate9830_4 == false);
//    // now set the rate using the interface
//    // start with no rate
//    ICpriCore::LineRateCapability rateCaptoSet;
//    cccSlave->setNoLineRateCapability();
//    rateCap = cccSlave->getLineRateCapability();
//    ASSERT_TRUE(rateCap.capableOfRate614_4 == false);
//    ASSERT_TRUE(rateCap.capableOfRate1228_8 == false);
//    ASSERT_TRUE(rateCap.capableOfRate2457_6 == false);
//    ASSERT_TRUE(rateCap.capableOfRate3072_0 == false);
//    ASSERT_TRUE(rateCap.capableOfRate4915_2 == false);
//    ASSERT_TRUE(rateCap.capableOfRate6144_0 == false);
//    ASSERT_TRUE(rateCap.capableOfRate9830_4 == false);
//    // now set the rate using the interface
//    rateCaptoSet.capableOfRate614_4 = true;
//    rateCaptoSet.capableOfRate1228_8 = true;
//    rateCaptoSet.capableOfRate2457_6 = true;
//    rateCaptoSet.capableOfRate3072_0 = true;
//    rateCaptoSet.capableOfRate4915_2 = false;
//    rateCaptoSet.capableOfRate4915_2 = false;
//    rateCaptoSet.capableOfRate6144_0 = false;
//    rateCaptoSet.capableOfRate9830_4 = false;
//    cccSlave->setLineRateCapability(rateCaptoSet);
//    rateCap = cccSlave->getLineRateCapability();
//    ASSERT_TRUE(rateCap.capableOfRate614_4 == true);
//    ASSERT_TRUE(rateCap.capableOfRate1228_8 == true);
//    ASSERT_TRUE(rateCap.capableOfRate2457_6 == true);
//    ASSERT_TRUE(rateCap.capableOfRate3072_0 == true);
//    ASSERT_TRUE(rateCap.capableOfRate4915_2 == false);
//    ASSERT_TRUE(rateCap.capableOfRate6144_0 == false);
//    ASSERT_TRUE(rateCap.capableOfRate9830_4 == false);
//    // now set all rates are capable
//    rateCaptoSet.capableOfRate4915_2 = true;
//    rateCaptoSet.capableOfRate4915_2 = true;
//    rateCaptoSet.capableOfRate6144_0 = true;
//    rateCaptoSet.capableOfRate9830_4 = true;
//    cccSlave->setLineRateCapability(rateCaptoSet);
//    rateCap = cccSlave->getLineRateCapability();
//    ASSERT_TRUE(rateCap.capableOfRate614_4 == true);
//    ASSERT_TRUE(rateCap.capableOfRate1228_8 == true);
//    ASSERT_TRUE(rateCap.capableOfRate2457_6 == true);
//    ASSERT_TRUE(rateCap.capableOfRate3072_0 == true);
//    ASSERT_TRUE(rateCap.capableOfRate4915_2 == true);
//    ASSERT_TRUE(rateCap.capableOfRate6144_0 == true);
//    ASSERT_TRUE(rateCap.capableOfRate9830_4 == true);
//
//    // Write to register field to set tx alarm reset to 0
//    OffTargetFPGA->writeField("txAlarmReset[0]", 0x00);
//    ASSERT_TRUE(cccSlave->isTransmitResetAckActive() == false);
//    cccSlave->enableTransmitResetRequest();
//    ASSERT_TRUE(cccSlave->isTransmitResetAckActive() == true);
//    cccSlave->disableTransmitResetRequest();
//    ASSERT_TRUE(cccSlave->isTransmitResetAckActive() == false);
//
//    // Write to register field to set tx alarm sdi to 0
//    OffTargetFPGA->writeField("txAlarmSdi[0]", 0x00);
//    ASSERT_TRUE(cccSlave->isTransmitSapDefectActive() == false);
//    // Write to register field to set tx alarm sdi to 1
//    OffTargetFPGA->writeField("txAlarmSdi[0]", 0x01);
//    ASSERT_TRUE(cccSlave->isTransmitSapDefectActive() == true);
//
//    // Write to register field to set r21 coarse timer to 0x12345
//    OffTargetFPGA->writeField("r21Lo[0]", 0x2345);
//    OffTargetFPGA->writeField("r21Hi[0]", 0x01);
//    ASSERT_TRUE(cccSlave->getR21CoarseTimer() == 0x12345);
//
//    // write to register field to set r21 FIFO delay to 0x123
//    OffTargetFPGA->writeField("cdcfifoDelay[0]", 0x123);
//    ASSERT_TRUE(cccSlave->getR21FIFOTransitTime() == 0x123);
//
//    // topology is not currently supplied by FPGA register interface
//    // so just test that the interface methods return 0
//    ASSERT_TRUE(cccSlave->getCpriReIdIsZeroCount() == 0);
//    ASSERT_TRUE(cccSlave->getTopologyPMRE() == 0);
//    ASSERT_TRUE(cccSlave->getTopologyLinkId() == 0);
//    ASSERT_TRUE(cccSlave->getTopologyREID() == 0);
//    cccSlave->setTopologyREID(0);
//    ASSERT_TRUE(cccSlave->getTopologyREID() == 0);
//    ASSERT_TRUE(cccSlave->getCpriReIdIsZeroCount() == 2);
//
//    cccSlave->resetCpriReIdIsZeroCount();
//    ASSERT_TRUE(cccSlave->getCpriReIdIsZeroCount() == 0);
//
//    // Write to register field to set Core revision to 0
//    OffTargetFPGA->writeField("xilinxCoreMinorRevision[0]", 0x00);
//    OffTargetFPGA->writeField("xilinxCoreMajorRevision[0]", 0x00);
//    ASSERT_TRUE(cccSlave->getRevision() == 0x0000);
//    // Write to register field to set Core revision to 1.2
//    OffTargetFPGA->writeField("xilinxCoreMinorRevision[0]", 0x02);
//    OffTargetFPGA->writeField("xilinxCoreMajorRevision[0]", 0x01);
//    ASSERT_TRUE(cccSlave->getRevision() == 0x0102);

    cccSlave->show();

    // setup the port
    ICpriCore::CpriPortControl* portControl = new ICpriCore::CpriPortControl();
    portControl->allowableRates.capableOfRate614_4 = true;
    portControl->allowableRates.capableOfRate1228_8 = true;
    portControl->allowableRates.capableOfRate2457_6 = true;
    cccSlave->setPortParameters(*portControl);
    // check that it set up the correct line rate capability
    rateCap = cccSlave->getLineRateCapability();
    ASSERT_TRUE(rateCap.capableOfRate614_4 == true);
    ASSERT_TRUE(rateCap.capableOfRate1228_8 == true);
    ASSERT_TRUE(rateCap.capableOfRate2457_6 == true);
    ASSERT_TRUE(rateCap.capableOfRate3072_0 == true);
    ASSERT_TRUE(rateCap.capableOfRate4915_2 == true);
    ASSERT_TRUE(rateCap.capableOfRate6144_0 == true);
    ASSERT_TRUE(rateCap.capableOfRate9830_4 == true);

    // check the port status
    ICpriCore::CpriPortStatus pstatus = cccSlave->getPortStatus();
    ASSERT_TRUE(pstatus.active == false);
    ASSERT_TRUE(pstatus.mgtPllLock == false);
    ASSERT_TRUE(pstatus.mgtTxClockLock == false);
    ASSERT_TRUE(pstatus.mgtRxClockLock == false);
    ASSERT_TRUE(pstatus.lineRate == ICpriCore::Rate614_4);
    ASSERT_TRUE(pstatus.ethernetMinCMBandwidth == ICpriCore::CMRate480);
    ASSERT_TRUE(pstatus.ethernetMaxCMBandwidth == ICpriCore::CMRate21120);
    ASSERT_TRUE(pstatus.remoteSapDefect == false);
    ASSERT_TRUE(pstatus.remoteLossOfFrame == false);
    ASSERT_TRUE(pstatus.remoteLossOfSync == false);
    ASSERT_TRUE(pstatus.localLossOfFrame == false);
    ASSERT_TRUE(pstatus.localLossOfSync == false);
    ASSERT_TRUE(pstatus.sfpLos == true);

    cccSlave->show();

    // set the clocks are locked
    OffTargetFPGA->writeField("mgtpllLock[0]", 1);
    OffTargetFPGA->writeField("mgtTxClockLock[0]", 1);
    OffTargetFPGA->writeField("mgtRxClockLock[0]", 1);
    // check that the clocks are locked, as this is the gate to entering the next state
    ASSERT_TRUE( ICpri::getInterface()->areClocksLocked(0) == true );
    pstatus = cccSlave->getPortStatus();
    ASSERT_TRUE(pstatus.mgtPllLock == true);
    ASSERT_TRUE(pstatus.mgtTxClockLock == true);
    ASSERT_TRUE(pstatus.mgtRxClockLock == true);

    // set the status alarm to not on
    OffTargetFPGA->writeField("statAlarm[0]", 0x00);
    ASSERT_TRUE(cccSlave->isAlarmCurrentlyActive() == false);
    pstatus = cccSlave->getPortStatus();
    ASSERT_TRUE(pstatus.active == true);

    cccSlave->show();

    // test all the ethernet rates
    ICpriCore::CMRateValue ebw;
    OffTargetFPGA->writeReg(0x40210, 0x01);
    OffTargetFPGA->writeReg(0x40212, 63);
    ASSERT_TRUE(cccSlave->getCurrentEthernetPointer() == 63);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate614_4);

    ebw = cccSlave->getCurrentMinEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate480);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "0.480") == 0);
    ebw = cccSlave->getCurrentMaxEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate21120);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "21.120") == 0);

    OffTargetFPGA->writeReg(0x40210, 0x02);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate1228_8);
    ebw = cccSlave->getCurrentMinEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate960);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "0.960") == 0);
    ebw = cccSlave->getCurrentMaxEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate42240);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "42.240") == 0);

    OffTargetFPGA->writeReg(0x40210, 0x04);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate2457_6);
    ebw = cccSlave->getCurrentMinEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate1920);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "1.920") == 0);
    ebw = cccSlave->getCurrentMaxEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate84480);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "84.480") == 0);

    OffTargetFPGA->writeReg(0x40210, 0x08);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate3072_0);
    ebw = cccSlave->getCurrentMinEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate2400);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "2.400") == 0);
    ebw = cccSlave->getCurrentMaxEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate105600);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "105.600") == 0);

    OffTargetFPGA->writeReg(0x40210, 0x10);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate4915_2);
    ebw = cccSlave->getCurrentMinEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate3840);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "3.840") == 0);
    ebw = cccSlave->getCurrentMaxEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate168960);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "168.960") == 0);

    OffTargetFPGA->writeReg(0x40210, 0x20);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate6144_0);
    ebw = cccSlave->getCurrentMinEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate4800);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "4.800") == 0);
    ebw = cccSlave->getCurrentMaxEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate211200);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "211.200") == 0);

    OffTargetFPGA->writeReg(0x40210, 0x40);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate9830_4);
    ebw = cccSlave->getCurrentMinEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate7680);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "7.680") == 0);
    ebw = cccSlave->getCurrentMaxEthernetRate();
    ASSERT_TRUE(ebw == ICpriCore::CMRate337920);
    ASSERT_TRUE(strcmp((const char *) cccSlave->getCurrentEthernetRateString(ebw), "337.920") == 0);

    // test actual bit rates for the different ethernet pointers
    unsigned int bitRate;
    OffTargetFPGA->writeReg(0x40210, 0x01);
    OffTargetFPGA->writeReg(0x40212, 62);
    ASSERT_TRUE(cccSlave->getCurrentEthernetPointer() == 62);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate614_4);
    bitRate = cccSlave->getCurrentEthernetBitRate(cccSlave->getCurrentEthernetPointer());
    ASSERT_TRUE(cccSlave->getCurrentMinEthernetRate() == ICpriCore::CMRate480);
    ASSERT_TRUE(cccSlave->getCurrentMaxEthernetRate() == ICpriCore::CMRate21120);
    ASSERT_TRUE(bitRate == 960);

    OffTargetFPGA->writeReg(0x40212, 61);
    ASSERT_TRUE(cccSlave->getCurrentEthernetPointer() == 61);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate614_4);
    bitRate = cccSlave->getCurrentEthernetBitRate(cccSlave->getCurrentEthernetPointer());
    ASSERT_TRUE(bitRate == 1440);

    OffTargetFPGA->writeReg(0x40212, 20);
    ASSERT_TRUE(cccSlave->getCurrentEthernetPointer() == 20);
    ASSERT_TRUE(cccSlave->getCurrentLineRate() == ICpriCore::Rate614_4);
    bitRate = cccSlave->getCurrentEthernetBitRate(cccSlave->getCurrentEthernetPointer());
    ASSERT_TRUE(bitRate == 21120);

    cccSlave->show();

    // tidy up
    delete portControl;
    portControl = 0;

    cout << __func__ << " - END" <<  endl;
}

void CommonCpriTestCase::testCpriCoreMasterAccess()
{
    cout << __func__ << " - START" <<  endl;

    // create a master CPRI core
    std::shared_ptr<CommonCpriCore> cccMaster = std::shared_ptr<CommonCpriCore>(new CommonCpriCore(1, ICpri::CpriPortMaster));

    auto commonFpga = IFpgaMgr::getIFpgaFibreRegs() ;
    UINT32 mFibre = 1;

    // take CPRI core out of reset
    cccMaster->takeCoreOutOfReset();
    ASSERT_TRUE(commonFpga->read_fibreBlkReset(mFibre) == 0);
    ASSERT_TRUE(cccMaster->isCoreOutOfReset() == true);

    // put CPRI core into reset
    cccMaster->putCoreIntoReset();
    ASSERT_TRUE(commonFpga->read_fibreBlkReset(mFibre) == 1);
    ASSERT_TRUE(cccMaster->isCoreOutOfReset() == false);

    // reset CPRI core
    cccMaster->resetCore();
    ASSERT_TRUE(cccMaster->isCoreOutOfReset() == true);

    // check master mode
    ASSERT_TRUE(cccMaster->isSlave() == false);
    ASSERT_TRUE(cccMaster->isMaster() == true);

    cccMaster->show();

    cout << __func__ << " - END" <<  endl;
}

void CommonCpriTestCase::testCpriStartup()
{
    cout << __func__ << " - START" <<  endl;

    // Get our CommonCpri
    std::shared_ptr<CommonCpri> cc0 = std::shared_ptr<CommonCpri>(new CommonCpri());

    // should be the same as for cc0 above
    cc0->show();

    ASSERT_TRUE(cc0->initialise() == ReturnType::RT_OK);

    ASSERT_TRUE(cc0->getNumCpriPorts() == 2);
    ASSERT_TRUE(cc0->getNumPorts() == cc0->getNumCpriPorts());
//    ASSERT_TRUE(cc0->getVersion() == (unsigned int)cc0->mFpga->getVersion());
    ASSERT_TRUE(cc0->verifyFpgaVersion() == true);

    cc0->enableCpriLoopback();
    cc0->disableCpriLoopback();
    cc0->fpgaSoftReset();

    ASSERT_TRUE(cc0->isCMRateStable() == true);
    ASSERT_TRUE(cc0->areClocksLocked(0) == true);

    ASSERT_TRUE(cc0->getCpriPortInitialType(0) == ICpri::CpriPortSlave);
    ASSERT_TRUE(cc0->getCpriPortInitialType(1) == ICpri::CpriPortMaster);

    // get the cores from the CommonCpri
    std::shared_ptr<CommonCpriCore> cccSlave1( std::dynamic_pointer_cast<CommonCpriCore>(cc0->getPortCore(0)) );
    std::shared_ptr<CommonCpriCore> cccMaster( std::dynamic_pointer_cast<CommonCpriCore>(cc0->getPortCore(1)) );

//    ASSERT_TRUE(cccSlave1->mFpga->isInitComplete() == false);
    ASSERT_TRUE(cccSlave1->mCoreId == CPRI_SLAVE_CORE);
    ASSERT_TRUE(cccSlave1->mFibre == 0);
//    ASSERT_TRUE(cccMaster->mFpga->isInitComplete() == false);
    ASSERT_TRUE(cccMaster->mCoreId == CPRI_MASTER_CORE);
    ASSERT_TRUE(cccMaster->mFibre == 1);

    // now show the CommonCpri again, this time it will show all the active port states
    cc0->show();

    // Invalid get of a core from an invalid port.
    // Confirm that the assertion test fails.
//    ASSERT_TRUE(cc1->getPortCore(cc1->getNumCpriPorts()) == 0);

    cout << __func__ << " - END" <<  endl;
}

void CommonCpriTestCase::testCpriModeChange()
{
    cout << __func__ << " - START" <<  endl;

    // Get our CommonCpri
    std::shared_ptr<CommonCpri> cc0 = std::shared_ptr<CommonCpri>(new CommonCpri());

    ASSERT_TRUE(cc0->initialise() == ReturnType::RT_OK);
    ASSERT_TRUE(cc0->getNumCpriPorts() == 2);
    ASSERT_TRUE(cc0->getNumPorts() == cc0->getNumCpriPorts());
    ASSERT_TRUE(cc0->getCpriPortInitialType(0) == ICpri::CpriPortSlave);
    ASSERT_TRUE(cc0->getCpriPortInitialType(1) == ICpri::CpriPortMaster);

    // get the cores from the CommonCpri
    std::shared_ptr<CommonCpriCore> cccPort0( std::dynamic_pointer_cast<CommonCpriCore>(cc0->getPortCore(0)) );
    std::shared_ptr<CommonCpriCore> cccPort1( std::dynamic_pointer_cast<CommonCpriCore>(cc0->getPortCore(1)) );

    ASSERT_TRUE(cccPort0->mCoreId == CPRI_SLAVE_CORE);
    ASSERT_TRUE(cccPort1->mCoreId == CPRI_MASTER_CORE);

    // test the invalid mode changes first, cannot change to its current mode
    ASSERT_TRUE(cccPort0->changeMode(ICpri::CpriPortSlave) == false);
    ASSERT_TRUE(cccPort1->changeMode(ICpri::CpriPortMaster) == false);

    // change port 1 from master to slave
    ASSERT_TRUE(cccPort1->changeMode(ICpri::CpriPortSlave) == true);
    ASSERT_TRUE(cccPort0->mCoreId == CPRI_SLAVE_CORE);
    ASSERT_TRUE(cccPort1->mCoreId == CPRI_SLAVE_CORE);

    // change port 0 from slave to master
    ASSERT_TRUE(cccPort0->changeMode(ICpri::CpriPortMaster) == true);
    ASSERT_TRUE(cccPort0->mCoreId == CPRI_MASTER_CORE);
    ASSERT_TRUE(cccPort1->mCoreId == CPRI_SLAVE_CORE);

    // change port 0 from master to slave
    ASSERT_TRUE(cccPort0->changeMode(ICpri::CpriPortSlave) == true);
    ASSERT_TRUE(cccPort0->mCoreId == CPRI_SLAVE_CORE);
    ASSERT_TRUE(cccPort1->mCoreId == CPRI_SLAVE_CORE);

    // change port 1 from slave to inactive
    ASSERT_TRUE(cccPort1->changeMode(ICpri::CpriPortInactive) == true);
    ASSERT_TRUE(cccPort0->mCoreId == CPRI_SLAVE_CORE);
    ASSERT_TRUE(cccPort1->mCoreId == CPRI_INACTIVE_CORE);

    // check slave mode
    ASSERT_TRUE(cccPort0->isSlave() == true);
    ASSERT_TRUE(cccPort1->isMaster() == false);
    ASSERT_TRUE(cccPort1->isSlave() == false);
    ASSERT_TRUE(cccPort1->isInactive() == true);

    cout << __func__ << " - END" <<  endl;
}

/*
 * Unit test fixtures
 */
TEST_F(CommonCpriTestCase, testCreation)
{
    testCreation();
}

TEST_F(CommonCpriTestCase, testCpriCoreSlaveAccess)
{
    testCpriCoreSlaveAccess();
}

TEST_F(CommonCpriTestCase, testCpriCoreMasterAccess)
{
    testCpriCoreMasterAccess();
}

TEST_F(CommonCpriTestCase, testCpriStartup)
{
    testCpriStartup();
}

TEST_F(CommonCpriTestCase, testCpriModeChange)
{
    testCpriModeChange();
}
