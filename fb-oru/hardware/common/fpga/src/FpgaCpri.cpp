/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCpri.cpp
 * \brief     Implementation of the CommonFPGA class CPRI accessors
 *
 *
 * \details   This file contains the implementation of the hardware mFpga
 *            CommonFPGA class.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include <memory>
#include "IFpgaMgr.h"
#include "FpgaCpri.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCpri::FpgaCpri() :
	mFibreRegs(IFpgaMgr::getIFpgaFibreRegs())
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCpri::~FpgaCpri()
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaKernel> FpgaCpri::kernel() const
{
	return mFibreRegs->kernel() ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriCoreInit(UINT32 fibre)
{
	// set the bypass sync bit
    (void)mFibreRegs->write_bypassSync(fibre, 1);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::takeCpriOutOfReset(UINT32 fibre)
{
    (void)mFibreRegs->write_fibreBlkReset(fibre, 0);

    // Must now re-init core
    cpriCoreInit(fibre) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::putCpriIntoReset(UINT32 fibre)
{
    (void)mFibreRegs->write_fibreBlkReset(fibre, 1);

    // an alternative is to set the line rate of 0, as that keeps the CPRI core in reset
    // cpriSetLineSpeedCapability(fibre, 0);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::isCpriOutOfReset(UINT32 fibre)
{
    bool isOut = (mFibreRegs->read_fibreBlkReset(fibre) == 0) ? true : false;

    return isOut;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::resetCpriCore(UINT32 fibre)
{
    putCpriIntoReset(fibre);
    takeCpriOutOfReset(fibre);
}

//-------------------------------------------------------------------------------------------------------------
IFpgaCpri::CpriStatus FpgaCpri::cpriStatusCode(UINT32 fibre)
{
	return (IFpgaCpri::CpriStatus)mFibreRegs->read_statCode(fibre);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::setCpriPreferredProtocolVersion(UINT32 fibre, UINT16 prefProtValue)
{
    (void)mFibreRegs->write_prefProtocol(fibre, prefProtValue);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::getCpriPreferredProtocolVersion(UINT32 fibre)
{
    return mFibreRegs->read_prefProtocol(fibre);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::getCpriCurrentProtocolVersion(UINT32 fibre)
{
    return mFibreRegs->read_curProtocol(fibre);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriIsAlarmActive(UINT32 fibre)
{
    if ( mFibreRegs->read_statAlarm(fibre) == 0 )
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------------------------
IFpgaCpri::CpriRemoteAlarms FpgaCpri::cpriReadRemoteAlarms(UINT32 fibre)
{
    IFpgaCpri::CpriRemoteAlarms alarms;

    alarms.remoteLOS = 0;
    alarms.remoteLOF = 0;
    alarms.remoteRAI = 0;
    alarms.remoteSDI = 0;
    alarms.remoteRST = 0;

    return alarms;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriIsSfpLosAlarmActive(UINT32 fibre)
{
    return (mFibreRegs->read_sfplos(fibre) == 0 ? false : true);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriIsLosAlarmActive(UINT32 fibre)
{
    return (mFibreRegs->read_los(fibre) == 0 ? false : true);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriIsLofAlarmActive(UINT32 fibre)
{
    return (mFibreRegs->read_lof(fibre) == 0 ? false : true);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriIsMasterPort(UINT32 fibre)
{
    return (mFibreRegs->read_forwardingPort(fibre) == 0 ? false : true);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriSetPortMasterMode(UINT32 fibre)
{
    (void)mFibreRegs->write_forwardingPort(fibre, 1);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriSetPortSlaveMode(UINT32 fibre)
{
    (void)mFibreRegs->write_forwardingPort(fibre, 0);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriGetCurrentEthernetPointer(UINT32 fibre)
{
    return mFibreRegs->read_curEthPointer(fibre);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriSetCurrentEthernetPointer(UINT32 fibre, UINT16 ethPtr)
{
    // no interface through the FPGA
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriReadRxSubChannelWord(UINT32 fibre, UINT16 wordId)
{
    // no interface through the FPGA
    return 0;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriResetEthernet(UINT32 fibre)
{
    (void)mFibreRegs->write_ethRst(fibre, 1);
    (void)mFibreRegs->write_ethRst(fibre, 0);
    return;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriGetGTPBarrelShift(UINT32 fibre)
{
    return mFibreRegs->read_barrelShift(fibre);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriSetGTPBarrelShift(UINT32 fibre, UINT16 shiftValue)
{
    // no interface through the FPGA
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriSetPreferredEthernetPointer(UINT32 fibre, UINT16 prefEthPtrValue)
{
    (void)mFibreRegs->write_cpriEthPtrReg(fibre, prefEthPtrValue);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriGetPreferredEthernetPointer(UINT32 fibre)
{
    return mFibreRegs->read_cpriEthPtrReg(fibre);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriSetPreferredHdlcRate(UINT32 fibre, UINT16 prefHdlcRateValue)
{
    (void)mFibreRegs->write_cpriHdlcReg(fibre, prefHdlcRateValue);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriGetPreferredHdlcRate(UINT32 fibre)
{
    return mFibreRegs->read_cpriHdlcReg(fibre);
}

//-------------------------------------------------------------------------------------------------------------
FpgaCpri::CpriLineSpeed FpgaCpri::cpriReadCurrentLineSpeed(UINT32 fibre)
{
    return (FpgaCpri::CpriLineSpeed)mFibreRegs->read_curLineRate(fibre);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriGetLineSpeedCapability(UINT32 fibre)
{
    return mFibreRegs->read_cpriLineRatesReg(fibre);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriSetLineSpeedCapability(UINT32 fibre, UINT16 cpriRate)
{
    (void)mFibreRegs->write_cpriLineRatesReg(fibre, cpriRate);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriEnableTransmitResetRequest(UINT32 fibre)
{
    (void)mFibreRegs->write_txAlarmReset(fibre, 1);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriDisableTransmitResetRequest(UINT32 fibre)
{
    (void)mFibreRegs->write_txAlarmReset(fibre, 0);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriIsTransmitResetAckActive(UINT32 fibre)
{
    return (mFibreRegs->read_txAlarmReset(fibre) == 0) ? false : true;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriSlaveTransmitEnable(UINT32 fibre)
{
    (void)mFibreRegs->write_slaveTxEn(fibre, 1);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriSlaveTransmitDisable(UINT32 fibre)
{
    (void)mFibreRegs->write_slaveTxEn(fibre, 0);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriIsSlaveTransmitEnabled(UINT32 fibre)
{
    return (mFibreRegs->read_slaveTxEn(fibre) == 0) ? false : true;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriSetTxAlarmSdi(UINT32 fibre)
{
    (void)mFibreRegs->write_txAlarmSdi(fibre, 1);
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriClearTxAlarmSdi(UINT32 fibre)
{
    (void)mFibreRegs->write_txAlarmSdi(fibre, 0);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriIsSapDefectActive(UINT32 fibre)
{
    return (mFibreRegs->read_txAlarmSdi(fibre) == 0) ? false : true;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 FpgaCpri::cpriReadR21coarseTimer(UINT32 fibre)
{
    UINT32 regValue = (UINT32) mFibreRegs->read_r21Hi(fibre);

    regValue = regValue << 16 ;

    regValue += (UINT32) mFibreRegs->read_r21Lo(fibre);

    regValue &= regValue & 0x3ffff;

    return regValue;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriReadR21FifoTransitTime(UINT32 fibre)
{
    return mFibreRegs->read_cdcfifoDelay(fibre);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriReadTopologyPMRE(UINT32 fibre)
{
    // no interface through the FPGA
    return 0;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriReadTopologyLinkId(UINT32 fibre)
{
    // no interface through the FPGA
    return 0;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriReadTopologyReID(UINT32 fibre)
{
    // no interface through the FPGA
    return 0;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCpri::cpriWriteTopologyReID(UINT32 fibre, UINT16 reid)
{
    // no interface through the FPGA
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriGetMgtPllLock(UINT32 fibre)
{
    return (mFibreRegs->read_mgtpllLock(fibre) == 0) ? false : true;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriGetMgtTxClockLock(UINT32 fibre)
{
    return (mFibreRegs->read_mgtTxClockLock(fibre) == 0) ? false : true;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCpri::cpriGetMgtRxClockLock(UINT32 fibre)
{
    return (mFibreRegs->read_mgtRxClockLock(fibre) == 0) ? false : true;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaCpri::cpriGetCoreRevision(UINT32 fibre)
{
    return mFibreRegs->read_xilinxCoreRevision(fibre);
}
