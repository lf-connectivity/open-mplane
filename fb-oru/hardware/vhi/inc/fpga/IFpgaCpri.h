/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaCpri.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef VHI_INC_FPGA_IFPGACPRI_H_
#define VHI_INC_FPGA_IFPGACPRI_H_

#include <memory>
#include "GlobalTypeDefs.h"
#include "IFpgaKernel.h"
#include "IFpgaRegs.h"

namespace Mplane {

/*!
 * \class  IFpgaCpri
 * \brief
 * \details
 *
 */
class IFpgaCpri : public virtual IFpgaRegs
{
public:
	IFpgaCpri() {}
	virtual ~IFpgaCpri() {}

    /*! \brief  Get fpga kernel
     *
     *  Get the fpga kernel driver
     *
     *  \return pointer to fpga kernel
     */
    virtual std::shared_ptr<IFpgaKernel> kernel() const =0 ;

    /*! @brief  CPRI remote alarms in the FPGA
     *
     *  Stores remote alarms latched on this interface.
     */
    class CpriRemoteAlarms
    {
    public:
        CpriRemoteAlarms() :
            remoteRST(false),
            remoteRAI(false),
            remoteSDI(false),
            remoteLOS(false),
            remoteLOF(false) {};
        bool remoteRST;
        bool remoteRAI;
        bool remoteSDI;
        bool remoteLOS;
        bool remoteLOF;
    };

    enum CpriLineSpeed
    {
        CPRI_10137MBITS = 0x0080,
        CPRI_9830MBITS = 0x0040,
        CPRI_6144MBITS = 0x0020,
        CPRI_4915MBITS = 0x0010,
        CPRI_3072MBITS = 0x0008,
        CPRI_2457MBITS = 0x0004,
        CPRI_1228MBITS = 0x0002,
        CPRI_614MBITS  = 0x0001
    };

    enum CpriStatus
    {
        CPRI_RESET         = 0,
        CPRI_L1_SYNC       = 1,
        CPRI_VERSION_SETUP = 2,
        CPRI_PARAM_SETUP   = 3,
        CPRI_PASSIVE_MODE  = 0xB,
        CPRI_OPERATIONAL   = 0xF
    };


	//  Functions for CPRI core control
    virtual void cpriCoreInit(UINT32 fibre) =0 ;
    virtual void takeCpriOutOfReset(UINT32 fibre) =0 ;
    virtual void putCpriIntoReset(UINT32 fibre) =0 ;
    virtual bool isCpriOutOfReset(UINT32 fibre) =0 ;
    virtual void resetCpriCore(UINT32 fibre) =0 ;
    virtual CpriStatus cpriStatusCode(UINT32 fibre) =0 ;
    virtual void setCpriPreferredProtocolVersion(UINT32 fibre, UINT16 prefProtValue) =0 ;
    virtual UINT16 getCpriPreferredProtocolVersion(UINT32 fibre) =0 ;
    virtual UINT16 getCpriCurrentProtocolVersion(UINT32 fibre) =0 ;
    virtual bool cpriIsAlarmActive(UINT32 fibre) =0 ;
    virtual CpriRemoteAlarms cpriReadRemoteAlarms(UINT32 fibre) =0 ;
    virtual bool cpriIsSfpLosAlarmActive(UINT32 fibre) =0 ;
    virtual bool cpriIsLosAlarmActive(UINT32 fibre) =0 ;
    virtual bool cpriIsLofAlarmActive(UINT32 fibre) =0 ;
    virtual bool cpriIsMasterPort(UINT32 fibre) =0 ;
    virtual void cpriSetPortMasterMode(UINT32 fibre) =0 ;
    virtual void cpriSetPortSlaveMode(UINT32 fibre) =0 ;
    virtual UINT16 cpriGetCurrentEthernetPointer(UINT32 fibre) =0 ;
    virtual void cpriSetCurrentEthernetPointer(UINT32 fibre, UINT16 ethPtr) =0 ;
    virtual UINT16 cpriReadRxSubChannelWord(UINT32 fibre, UINT16 wordId) =0 ;
    virtual void cpriResetEthernet(UINT32 fibre) =0 ;
    virtual UINT16 cpriGetGTPBarrelShift(UINT32 fibre) =0 ;
    virtual void cpriSetGTPBarrelShift(UINT32 fibre, UINT16 shiftValue) =0 ;
    virtual void cpriSetPreferredEthernetPointer(UINT32 fibre, UINT16 prefEthPtrValue) =0 ;
    virtual UINT16 cpriGetPreferredEthernetPointer(UINT32 fibre) =0 ;
    virtual void cpriSetPreferredHdlcRate(UINT32 fibre, UINT16 prefHdlcRateValue) =0 ;
    virtual UINT16 cpriGetPreferredHdlcRate(UINT32 fibre) =0 ;
    virtual CpriLineSpeed cpriReadCurrentLineSpeed(UINT32 fibre) =0 ;
    virtual UINT16 cpriGetLineSpeedCapability(UINT32 fibre) =0 ;
    virtual void cpriSetLineSpeedCapability(UINT32 fibre, UINT16 cpriRate) =0 ;
    virtual void cpriEnableTransmitResetRequest(UINT32 fibre) =0 ;
    virtual void cpriDisableTransmitResetRequest(UINT32 fibre) =0 ;
    virtual bool cpriIsTransmitResetAckActive(UINT32 fibre) =0 ;
    virtual void cpriSlaveTransmitEnable(UINT32 fibre) =0 ;
    virtual void cpriSlaveTransmitDisable(UINT32 fibre) =0 ;
    virtual bool cpriIsSlaveTransmitEnabled(UINT32 fibre) =0 ;
    virtual void cpriSetTxAlarmSdi(UINT32 fibre) =0 ;
    virtual void cpriClearTxAlarmSdi(UINT32 fibre) =0 ;
    virtual bool cpriIsSapDefectActive(UINT32 fibre) =0 ;
    virtual UINT32 cpriReadR21coarseTimer(UINT32 fibre) =0 ;
    virtual UINT16 cpriReadR21FifoTransitTime(UINT32 fibre) =0 ;
    virtual UINT16 cpriReadTopologyPMRE(UINT32 fibre) =0 ;
    virtual UINT16 cpriReadTopologyLinkId(UINT32 fibre) =0 ;
    virtual UINT16 cpriReadTopologyReID(UINT32 fibre) =0 ;
    virtual void cpriWriteTopologyReID(UINT32 fibre, UINT16 reid) =0 ;
    virtual UINT16 cpriGetCoreRevision(UINT32 fibre) =0 ;
    virtual bool cpriGetMgtPllLock(UINT32 fibre) =0 ;
    virtual bool cpriGetMgtTxClockLock(UINT32 fibre) =0 ;
    virtual bool cpriGetMgtRxClockLock(UINT32 fibre) =0 ;


} ;

}

#endif /* VHI_INC_FPGA_IFPGACPRI_H_ */
