#ifndef _RADIO_HARDWARE_COMMONFPGACPRI_H_
#define _RADIO_HARDWARE_COMMONFPGACPRI_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCpri.h
 * \brief     Adds CPRI to fpga.
 *
 *
 * \details   This class provides CPRI access to the fpga
 *
 */

#include <memory>
#include "IFpgaMgr.h"

namespace Mplane
{

class FpgaCpri : public virtual IFpgaCpri
{
public:
    /*! \brief  Constructor
     *
     */
	explicit FpgaCpri();

    /*! Destructor
     *
     *  Destructor, should never be called.
     */
    virtual ~FpgaCpri() ;

    /*! \brief  Get fpga kernel
     *
     *  Get the fpga kernel driver
     *
     *  \return pointer to fpga kernel
     */
    virtual std::shared_ptr<IFpgaKernel> kernel() const override ;


	//  Functions for CPRI core control
    virtual void cpriCoreInit(UINT32 fibre) override ;
    virtual void takeCpriOutOfReset(UINT32 fibre) override ;
    virtual void putCpriIntoReset(UINT32 fibre) override ;
    virtual bool isCpriOutOfReset(UINT32 fibre) override ;
    virtual void resetCpriCore(UINT32 fibre) override ;
    virtual IFpgaCpri::CpriStatus cpriStatusCode(UINT32 fibre) override ;
    virtual void setCpriPreferredProtocolVersion(UINT32 fibre, UINT16 prefProtValue) override ;
    virtual UINT16 getCpriPreferredProtocolVersion(UINT32 fibre) override ;
    virtual UINT16 getCpriCurrentProtocolVersion(UINT32 fibre) override ;
    virtual bool cpriIsAlarmActive(UINT32 fibre) override ;
    virtual IFpgaCpri::CpriRemoteAlarms cpriReadRemoteAlarms(UINT32 fibre) override ;
    virtual bool cpriIsSfpLosAlarmActive(UINT32 fibre) override ;
    virtual bool cpriIsLosAlarmActive(UINT32 fibre) override ;
    virtual bool cpriIsLofAlarmActive(UINT32 fibre) override ;
    virtual bool cpriIsMasterPort(UINT32 fibre) override ;
    virtual void cpriSetPortMasterMode(UINT32 fibre) override ;
    virtual void cpriSetPortSlaveMode(UINT32 fibre) override ;
    virtual UINT16 cpriGetCurrentEthernetPointer(UINT32 fibre) override ;
    virtual void cpriSetCurrentEthernetPointer(UINT32 fibre, UINT16 ethPtr) override ;
    virtual UINT16 cpriReadRxSubChannelWord(UINT32 fibre, UINT16 wordId) override ;
    virtual void cpriResetEthernet(UINT32 fibre) override ;
    virtual UINT16 cpriGetGTPBarrelShift(UINT32 fibre) override ;
    virtual void cpriSetGTPBarrelShift(UINT32 fibre, UINT16 shiftValue) override ;
    virtual void cpriSetPreferredEthernetPointer(UINT32 fibre, UINT16 prefEthPtrValue) override ;
    virtual UINT16 cpriGetPreferredEthernetPointer(UINT32 fibre) override ;
    virtual void cpriSetPreferredHdlcRate(UINT32 fibre, UINT16 prefHdlcRateValue) override ;
    virtual UINT16 cpriGetPreferredHdlcRate(UINT32 fibre) override ;
    virtual IFpgaCpri::CpriLineSpeed cpriReadCurrentLineSpeed(UINT32 fibre) override ;
    virtual UINT16 cpriGetLineSpeedCapability(UINT32 fibre) override ;
    virtual void cpriSetLineSpeedCapability(UINT32 fibre, UINT16 cpriRate) override ;
    virtual void cpriEnableTransmitResetRequest(UINT32 fibre) override ;
    virtual void cpriDisableTransmitResetRequest(UINT32 fibre) override ;
    virtual bool cpriIsTransmitResetAckActive(UINT32 fibre) override ;
    virtual void cpriSlaveTransmitEnable(UINT32 fibre) override ;
    virtual void cpriSlaveTransmitDisable(UINT32 fibre) override ;
    virtual bool cpriIsSlaveTransmitEnabled(UINT32 fibre) override ;
    virtual void cpriSetTxAlarmSdi(UINT32 fibre) override ;
    virtual void cpriClearTxAlarmSdi(UINT32 fibre) override ;
    virtual bool cpriIsSapDefectActive(UINT32 fibre) override ;
    virtual UINT32 cpriReadR21coarseTimer(UINT32 fibre) override ;
    virtual UINT16 cpriReadR21FifoTransitTime(UINT32 fibre) override ;
    virtual UINT16 cpriReadTopologyPMRE(UINT32 fibre) override ;
    virtual UINT16 cpriReadTopologyLinkId(UINT32 fibre) override ;
    virtual UINT16 cpriReadTopologyReID(UINT32 fibre) override ;
    virtual void cpriWriteTopologyReID(UINT32 fibre, UINT16 reid) override ;
    virtual UINT16 cpriGetCoreRevision(UINT32 fibre) override ;
    virtual bool cpriGetMgtPllLock(UINT32 fibre) override ;
    virtual bool cpriGetMgtTxClockLock(UINT32 fibre) override ;
    virtual bool cpriGetMgtRxClockLock(UINT32 fibre) override ;


private:
    std::shared_ptr<IFpgaFibreRegs> mFibreRegs ;
};



} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONFPGACPRI_H_ */
