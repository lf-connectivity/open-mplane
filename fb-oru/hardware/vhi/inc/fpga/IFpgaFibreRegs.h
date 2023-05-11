#ifndef _IFIBRE_REGS_DEF_H_
#define _IFIBRE_REGS_DEF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaFibreRegs.h
 * \brief     FPGA Fibre registers virtual interface
 *
 *
 * \details   This file defines the FPGA Fibre registers.
 *
 *             ** Auto-generated file, do not edit **
 *
 *
 */
#include <memory>

#include <memory>
#include "GlobalTypeDefs.h"
#include "IFpgaKernel.h"
#include "IFpgaRegs.h"


namespace Mplane
{

class IFpgaFibreRegs : public virtual IFpgaRegs
{
public:
	IFpgaFibreRegs() {}
	virtual ~IFpgaFibreRegs(void) {} ;

    /** \brief  Does FPGA have a FIBRE registers block
     *
     *  \return true if the FPGA instance does actually support a Fibre registers block
     */
    virtual bool hasFibreRegisters(void) =0 ;

    /*! \brief  Get base address
     *
     *  Get the base address of the Fibre registers (if supported)
     *
     *  \return base address of Fibre registers; 0 if not supported
     */
    virtual UINT32 getFibreBlockAddr(void) =0 ;

    /*! \brief  Lock mutex
     *
     *  Lock the mutex protecting this region of fpga registers
     *
     */
    virtual void mutexLock(void) =0 ;

    /*! \brief  Unlock mutex
     *
     *  Unlock the mutex protecting this region of fpga registers
     *
     */
    virtual void mutexUnLock(void) =0 ;

    /*! \brief  Get fpga kernel
     *
     *  Get the fpga kernel driver
     *
     *  \return pointer to fpga kernel
     */
    virtual std::shared_ptr<IFpgaKernel> kernel() const =0 ;

    // == Accessors ==

    /**
     * Read field FIBRE_TYPE at 0x40000 bits [3..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_fibreType(unsigned fibre) const =0 ;


    /**
     * Read field FIBRE_TYPE at 0x40000 bits [3..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fibreType(unsigned fibre) const =0 ;




    /**
     * Read field FIBRE_BLK_RESET at 0x40000 bits [15]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_fibreBlkReset(unsigned fibre) const =0 ;

    /**
     * Write field FIBRE_BLK_RESET at 0x40000 bits [15]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fibreBlkReset(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field FIBRE_BLK_RESET at 0x40000 bits [15]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fibreBlkReset(unsigned fibre) const =0 ;

    /**
     * Write field FIBRE_BLK_RESET at 0x40000 bits [15]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fibreBlkReset(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field FIBRE_BLK_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fibreBlkReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MINOR_REVISION at 0x40002 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_minorRevision(unsigned fibre) const =0 ;


    /**
     * Read field MINOR_REVISION at 0x40002 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_minorRevision(unsigned fibre) const =0 ;




    /**
     * Read field MAJOR_REVISION at 0x40002 bits [15..8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_majorRevision(unsigned fibre) const =0 ;


    /**
     * Read field MAJOR_REVISION at 0x40002 bits [15..8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_majorRevision(unsigned fibre) const =0 ;




    /**
     * Read field DL_FIBRE_IQ_STREAMS at 0x40004 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_dlFibreIqStreams(unsigned fibre) const =0 ;


    /**
     * Read field DL_FIBRE_IQ_STREAMS at 0x40004 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlFibreIqStreams(unsigned fibre) const =0 ;




    /**
     * Read field UL_FIBRE_IQ_STREAMS at 0x40006 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ulFibreIqStreams(unsigned fibre) const =0 ;


    /**
     * Read field UL_FIBRE_IQ_STREAMS at 0x40006 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulFibreIqStreams(unsigned fibre) const =0 ;




    /**
     * Read field XILINX_CORE_MINOR_REVISION at 0x40008 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_xilinxCoreMinorRevision(unsigned fibre) const =0 ;


    /**
     * Read field XILINX_CORE_MINOR_REVISION at 0x40008 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xilinxCoreMinorRevision(unsigned fibre) const =0 ;




    /**
     * Read field XILINX_CORE_MAJOR_REVISION at 0x40008 bits [15..8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_xilinxCoreMajorRevision(unsigned fibre) const =0 ;


    /**
     * Read field XILINX_CORE_MAJOR_REVISION at 0x40008 bits [15..8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xilinxCoreMajorRevision(unsigned fibre) const =0 ;




    /**
     * Read field SFP_NUMBER at 0x4000a bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_SFP_Number(unsigned fibre) const =0 ;


    /**
     * Read field SFP_NUMBER at 0x4000a bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_SFP_Number(unsigned fibre) const =0 ;




    /**
     * Read field VIRTUAL_TO_PHYSICAL_ENABLE at 0x4000a bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_virtualToPhysicalEnable(unsigned fibre) const =0 ;


    /**
     * Read field VIRTUAL_TO_PHYSICAL_ENABLE at 0x4000a bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_virtualToPhysicalEnable(unsigned fibre) const =0 ;




    /**
     * Read field TX_ALARM_RESET at 0x40200 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txAlarmReset(unsigned fibre) const =0 ;

    /**
     * Write field TX_ALARM_RESET at 0x40200 bits [0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txAlarmReset(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field TX_ALARM_RESET at 0x40200 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txAlarmReset(unsigned fibre) const =0 ;

    /**
     * Write field TX_ALARM_RESET at 0x40200 bits [0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txAlarmReset(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field TX_ALARM_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txAlarmReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_ALARM_SDI at 0x40200 bits [1]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txAlarmSdi(unsigned fibre) const =0 ;

    /**
     * Write field TX_ALARM_SDI at 0x40200 bits [1]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txAlarmSdi(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field TX_ALARM_SDI at 0x40200 bits [1]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txAlarmSdi(unsigned fibre) const =0 ;

    /**
     * Write field TX_ALARM_SDI at 0x40200 bits [1]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txAlarmSdi(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field TX_ALARM_SDI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txAlarmSdi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SLAVE_TX_EN at 0x40200 bits [2]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_slaveTxEn(unsigned fibre) const =0 ;

    /**
     * Write field SLAVE_TX_EN at 0x40200 bits [2]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_slaveTxEn(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field SLAVE_TX_EN at 0x40200 bits [2]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_slaveTxEn(unsigned fibre) const =0 ;

    /**
     * Write field SLAVE_TX_EN at 0x40200 bits [2]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_slaveTxEn(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field SLAVE_TX_EN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_slaveTxEn(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field L1_TIMER_EXPIRED at 0x40200 bits [4]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_l1TimerExpired(unsigned fibre) const =0 ;

    /**
     * Write field L1_TIMER_EXPIRED at 0x40200 bits [4]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_l1TimerExpired(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field L1_TIMER_EXPIRED at 0x40200 bits [4]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_l1TimerExpired(unsigned fibre) const =0 ;

    /**
     * Write field L1_TIMER_EXPIRED at 0x40200 bits [4]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_l1TimerExpired(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field L1_TIMER_EXPIRED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_l1TimerExpired(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field VS_NEG_COMPLETE at 0x40200 bits [5]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_vsNegComplete(unsigned fibre) const =0 ;

    /**
     * Write field VS_NEG_COMPLETE at 0x40200 bits [5]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_vsNegComplete(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field VS_NEG_COMPLETE at 0x40200 bits [5]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vsNegComplete(unsigned fibre) const =0 ;

    /**
     * Write field VS_NEG_COMPLETE at 0x40200 bits [5]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_vsNegComplete(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field VS_NEG_COMPLETE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_vsNegComplete(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BYPASS_SYNC at 0x40200 bits [6]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_bypassSync(unsigned fibre) const =0 ;

    /**
     * Write field BYPASS_SYNC at 0x40200 bits [6]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bypassSync(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field BYPASS_SYNC at 0x40200 bits [6]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bypassSync(unsigned fibre) const =0 ;

    /**
     * Write field BYPASS_SYNC at 0x40200 bits [6]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bypassSync(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field BYPASS_SYNC in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bypassSync(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FORWARDING_PORT at 0x40200 bits [7]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_forwardingPort(unsigned fibre) const =0 ;

    /**
     * Write field FORWARDING_PORT at 0x40200 bits [7]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_forwardingPort(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field FORWARDING_PORT at 0x40200 bits [7]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_forwardingPort(unsigned fibre) const =0 ;

    /**
     * Write field FORWARDING_PORT at 0x40200 bits [7]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_forwardingPort(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field FORWARDING_PORT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_forwardingPort(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field IQ_PATH_LOOPBACK at 0x40200 bits [12]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_iqPathLoopback(unsigned fibre) const =0 ;

    /**
     * Write field IQ_PATH_LOOPBACK at 0x40200 bits [12]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_iqPathLoopback(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field IQ_PATH_LOOPBACK at 0x40200 bits [12]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_iqPathLoopback(unsigned fibre) const =0 ;

    /**
     * Write field IQ_PATH_LOOPBACK at 0x40200 bits [12]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_iqPathLoopback(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field IQ_PATH_LOOPBACK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_iqPathLoopback(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PREF_PROTOCOL at 0x40202 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_prefProtocol(unsigned fibre) const =0 ;

    /**
     * Write field PREF_PROTOCOL at 0x40202 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_prefProtocol(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field PREF_PROTOCOL at 0x40202 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_prefProtocol(unsigned fibre) const =0 ;

    /**
     * Write field PREF_PROTOCOL at 0x40202 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_prefProtocol(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field PREF_PROTOCOL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_prefProtocol(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CPRI_LINE_RATES_REG at 0x40204 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_cpriLineRatesReg(unsigned fibre) const =0 ;

    /**
     * Write field CPRI_LINE_RATES_REG at 0x40204 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cpriLineRatesReg(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field CPRI_LINE_RATES_REG at 0x40204 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cpriLineRatesReg(unsigned fibre) const =0 ;

    /**
     * Write field CPRI_LINE_RATES_REG at 0x40204 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cpriLineRatesReg(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field CPRI_LINE_RATES_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cpriLineRatesReg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CPRI_ETH_PTR_REG at 0x40206 bits [5..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_cpriEthPtrReg(unsigned fibre) const =0 ;

    /**
     * Write field CPRI_ETH_PTR_REG at 0x40206 bits [5..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cpriEthPtrReg(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field CPRI_ETH_PTR_REG at 0x40206 bits [5..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cpriEthPtrReg(unsigned fibre) const =0 ;

    /**
     * Write field CPRI_ETH_PTR_REG at 0x40206 bits [5..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cpriEthPtrReg(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field CPRI_ETH_PTR_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cpriEthPtrReg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_SEED_LO at 0x40208 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txSeedLo(unsigned fibre) const =0 ;

    /**
     * Write field TX_SEED_LO at 0x40208 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txSeedLo(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field TX_SEED_LO at 0x40208 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txSeedLo(unsigned fibre) const =0 ;

    /**
     * Write field TX_SEED_LO at 0x40208 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txSeedLo(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field TX_SEED_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txSeedLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_SEED_HI at 0x4020a bits [14..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txSeedHi(unsigned fibre) const =0 ;

    /**
     * Write field TX_SEED_HI at 0x4020a bits [14..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txSeedHi(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field TX_SEED_HI at 0x4020a bits [14..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txSeedHi(unsigned fibre) const =0 ;

    /**
     * Write field TX_SEED_HI at 0x4020a bits [14..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txSeedHi(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field TX_SEED_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txSeedHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field STAT_CODE at 0x4020c bits [3..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_statCode(unsigned fibre) const =0 ;


    /**
     * Read field STAT_CODE at 0x4020c bits [3..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_statCode(unsigned fibre) const =0 ;




    /**
     * Read field STAT_ALARM at 0x4020c bits [7]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_statAlarm(unsigned fibre) const =0 ;


    /**
     * Read field STAT_ALARM at 0x4020c bits [7]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_statAlarm(unsigned fibre) const =0 ;




    /**
     * Read field MGTPLL_LOCK at 0x4020c bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_mgtpllLock(unsigned fibre) const =0 ;


    /**
     * Read field MGTPLL_LOCK at 0x4020c bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mgtpllLock(unsigned fibre) const =0 ;




    /**
     * Read field MGT_TX_CLOCK_LOCK at 0x4020c bits [9]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_mgtTxClockLock(unsigned fibre) const =0 ;


    /**
     * Read field MGT_TX_CLOCK_LOCK at 0x4020c bits [9]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mgtTxClockLock(unsigned fibre) const =0 ;




    /**
     * Read field MGT_RX_CLOCK_LOCK at 0x4020c bits [10]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_mgtRxClockLock(unsigned fibre) const =0 ;


    /**
     * Read field MGT_RX_CLOCK_LOCK at 0x4020c bits [10]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mgtRxClockLock(unsigned fibre) const =0 ;




    /**
     * Read field SFPLOS at 0x4020c bits [11]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_sfplos(unsigned fibre) const =0 ;


    /**
     * Read field SFPLOS at 0x4020c bits [11]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfplos(unsigned fibre) const =0 ;




    /**
     * Read field LOS at 0x4020c bits [12]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_los(unsigned fibre) const =0 ;

    /**
     * Write field LOS at 0x4020c bits [12]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_los(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field LOS at 0x4020c bits [12]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_los(unsigned fibre) const =0 ;

    /**
     * Write field LOS at 0x4020c bits [12]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_los(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field LOS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_los(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LOF at 0x4020c bits [13]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_lof(unsigned fibre) const =0 ;

    /**
     * Write field LOF at 0x4020c bits [13]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_lof(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field LOF at 0x4020c bits [13]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_lof(unsigned fibre) const =0 ;

    /**
     * Write field LOF at 0x4020c bits [13]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_lof(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field LOF in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_lof(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RAI at 0x4020c bits [14]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_rai(unsigned fibre) const =0 ;

    /**
     * Write field RAI at 0x4020c bits [14]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rai(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field RAI at 0x4020c bits [14]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rai(unsigned fibre) const =0 ;

    /**
     * Write field RAI at 0x4020c bits [14]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rai(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field RAI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rai(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SDI at 0x4020c bits [15]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_sdi(unsigned fibre) const =0 ;

    /**
     * Write field SDI at 0x4020c bits [15]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sdi(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field SDI at 0x4020c bits [15]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sdi(unsigned fibre) const =0 ;

    /**
     * Write field SDI at 0x4020c bits [15]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sdi(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field SDI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sdi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CUR_PROTOCOL at 0x4020e bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_curProtocol(unsigned fibre) const =0 ;


    /**
     * Read field CUR_PROTOCOL at 0x4020e bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_curProtocol(unsigned fibre) const =0 ;




    /**
     * Read field CUR_LINE_RATE at 0x40210 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_curLineRate(unsigned fibre) const =0 ;


    /**
     * Read field CUR_LINE_RATE at 0x40210 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_curLineRate(unsigned fibre) const =0 ;




    /**
     * Read field CUR_ETH_POINTER at 0x40212 bits [5..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_curEthPointer(unsigned fibre) const =0 ;


    /**
     * Read field CUR_ETH_POINTER at 0x40212 bits [5..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_curEthPointer(unsigned fibre) const =0 ;




    /**
     * Read field RX_SEED_LO at 0x40214 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_rxSeedLo(unsigned fibre) const =0 ;


    /**
     * Read field RX_SEED_LO at 0x40214 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxSeedLo(unsigned fibre) const =0 ;




    /**
     * Read field RX_SEED_HI at 0x40216 bits [14..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_rxSeedHi(unsigned fibre) const =0 ;


    /**
     * Read field RX_SEED_HI at 0x40216 bits [14..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxSeedHi(unsigned fibre) const =0 ;




    /**
     * Read field BARREL_SHIFT at 0x40218 bits [6..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_barrelShift(unsigned fibre) const =0 ;


    /**
     * Read field BARREL_SHIFT at 0x40218 bits [6..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_barrelShift(unsigned fibre) const =0 ;




    /**
     * Read field R21_LO at 0x4021a bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_r21Lo(unsigned fibre) const =0 ;


    /**
     * Read field R21_LO at 0x4021a bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_r21Lo(unsigned fibre) const =0 ;




    /**
     * Read field R21_HI at 0x4021c bits [1..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_r21Hi(unsigned fibre) const =0 ;


    /**
     * Read field R21_HI at 0x4021c bits [1..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_r21Hi(unsigned fibre) const =0 ;




    /**
     * Read field CDCFIFO_DELAY at 0x4021c bits [15..2]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_cdcfifoDelay(unsigned fibre) const =0 ;


    /**
     * Read field CDCFIFO_DELAY at 0x4021c bits [15..2]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cdcfifoDelay(unsigned fibre) const =0 ;




    /**
     * Read field RX_BIT_WIDTH at 0x4021e bits [4..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_rxBitWidth(unsigned fibre) const =0 ;

    /**
     * Write field RX_BIT_WIDTH at 0x4021e bits [4..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxBitWidth(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field RX_BIT_WIDTH at 0x4021e bits [4..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxBitWidth(unsigned fibre) const =0 ;

    /**
     * Write field RX_BIT_WIDTH at 0x4021e bits [4..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxBitWidth(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field RX_BIT_WIDTH in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxBitWidth(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BIT_REVERSE at 0x4021e bits [5]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_bitReverse(unsigned fibre) const =0 ;

    /**
     * Write field BIT_REVERSE at 0x4021e bits [5]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bitReverse(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field BIT_REVERSE at 0x4021e bits [5]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bitReverse(unsigned fibre) const =0 ;

    /**
     * Write field BIT_REVERSE at 0x4021e bits [5]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bitReverse(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field BIT_REVERSE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bitReverse(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field IDLE_SAMPLES at 0x4021e bits [6]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_idleSamples(unsigned fibre) const =0 ;

    /**
     * Write field IDLE_SAMPLES at 0x4021e bits [6]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_idleSamples(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field IDLE_SAMPLES at 0x4021e bits [6]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_idleSamples(unsigned fibre) const =0 ;

    /**
     * Write field IDLE_SAMPLES at 0x4021e bits [6]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_idleSamples(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field IDLE_SAMPLES in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_idleSamples(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_BIT_WIDTH at 0x4021e bits [12..8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txBitWidth(unsigned fibre) const =0 ;

    /**
     * Write field TX_BIT_WIDTH at 0x4021e bits [12..8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txBitWidth(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field TX_BIT_WIDTH at 0x4021e bits [12..8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txBitWidth(unsigned fibre) const =0 ;

    /**
     * Write field TX_BIT_WIDTH at 0x4021e bits [12..8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txBitWidth(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field TX_BIT_WIDTH in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txBitWidth(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAIT_SAMPLES at 0x40220 bits [3..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_waitSamples(unsigned fibre) const =0 ;

    /**
     * Write field WAIT_SAMPLES at 0x40220 bits [3..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waitSamples(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field WAIT_SAMPLES at 0x40220 bits [3..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waitSamples(unsigned fibre) const =0 ;

    /**
     * Write field WAIT_SAMPLES at 0x40220 bits [3..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waitSamples(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field WAIT_SAMPLES in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waitSamples(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_WAIT_SAMPLES at 0x40220 bits [7..4]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txWaitSamples(unsigned fibre) const =0 ;

    /**
     * Write field TX_WAIT_SAMPLES at 0x40220 bits [7..4]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txWaitSamples(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field TX_WAIT_SAMPLES at 0x40220 bits [7..4]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txWaitSamples(unsigned fibre) const =0 ;

    /**
     * Write field TX_WAIT_SAMPLES at 0x40220 bits [7..4]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txWaitSamples(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field TX_WAIT_SAMPLES in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txWaitSamples(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_START_FRAME at 0x40226 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_rxStartFrame(unsigned fibre) const =0 ;

    /**
     * Write field RX_START_FRAME at 0x40226 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxStartFrame(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field RX_START_FRAME at 0x40226 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxStartFrame(unsigned fibre) const =0 ;

    /**
     * Write field RX_START_FRAME at 0x40226 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxStartFrame(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field RX_START_FRAME in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxStartFrame(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FRAMEDIFF at 0x40228 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_framediff(unsigned fibre) const =0 ;


    /**
     * Read field FRAMEDIFF at 0x40228 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_framediff(unsigned fibre) const =0 ;




    /**
     * Read field VSS_ADDR at 0x4022a bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_vssAddr(unsigned fibre) const =0 ;

    /**
     * Write field VSS_ADDR at 0x4022a bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_vssAddr(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field VSS_ADDR at 0x4022a bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vssAddr(unsigned fibre) const =0 ;

    /**
     * Write field VSS_ADDR at 0x4022a bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_vssAddr(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field VSS_ADDR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_vssAddr(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field VSS_WE at 0x4022a bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_vssWe(unsigned fibre) const =0 ;

    /**
     * Write field VSS_WE at 0x4022a bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_vssWe(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field VSS_WE at 0x4022a bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vssWe(unsigned fibre) const =0 ;

    /**
     * Write field VSS_WE at 0x4022a bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_vssWe(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field VSS_WE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_vssWe(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field VSS_PAGE_REQ at 0x4022a bits [9]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_vssPageReq(unsigned fibre) const =0 ;

    /**
     * Write field VSS_PAGE_REQ at 0x4022a bits [9]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_vssPageReq(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field VSS_PAGE_REQ at 0x4022a bits [9]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vssPageReq(unsigned fibre) const =0 ;

    /**
     * Write field VSS_PAGE_REQ at 0x4022a bits [9]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_vssPageReq(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field VSS_PAGE_REQ in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_vssPageReq(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field VSS_CUR_PAGE at 0x4022a bits [10]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_vssCurPage(unsigned fibre) const =0 ;


    /**
     * Read field VSS_CUR_PAGE at 0x4022a bits [10]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vssCurPage(unsigned fibre) const =0 ;




    /**
     * Read field VSS_WRITE_DATA at 0x4022c bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_vssWriteData(unsigned fibre) const =0 ;

    /**
     * Write field VSS_WRITE_DATA at 0x4022c bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_vssWriteData(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field VSS_WRITE_DATA at 0x4022c bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vssWriteData(unsigned fibre) const =0 ;

    /**
     * Write field VSS_WRITE_DATA at 0x4022c bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_vssWriteData(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field VSS_WRITE_DATA in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_vssWriteData(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field VSS_READ_DATA at 0x4022e bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_vssReadData(unsigned fibre) const =0 ;


    /**
     * Read field VSS_READ_DATA at 0x4022e bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vssReadData(unsigned fibre) const =0 ;




    /**
     * Read field CPRI_HDLC_REG at 0x40230 bits [2..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_cpriHdlcReg(unsigned fibre) const =0 ;

    /**
     * Write field CPRI_HDLC_REG at 0x40230 bits [2..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cpriHdlcReg(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field CPRI_HDLC_REG at 0x40230 bits [2..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cpriHdlcReg(unsigned fibre) const =0 ;

    /**
     * Write field CPRI_HDLC_REG at 0x40230 bits [2..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cpriHdlcReg(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field CPRI_HDLC_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cpriHdlcReg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CUR_HDLC_RATE at 0x40232 bits [2..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_curHdlcRate(unsigned fibre) const =0 ;


    /**
     * Read field CUR_HDLC_RATE at 0x40232 bits [2..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_curHdlcRate(unsigned fibre) const =0 ;




    /**
     * Read field ETH_RST at 0x40234 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ethRst(unsigned fibre) const =0 ;

    /**
     * Write field ETH_RST at 0x40234 bits [0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ethRst(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field ETH_RST at 0x40234 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ethRst(unsigned fibre) const =0 ;

    /**
     * Write field ETH_RST at 0x40234 bits [0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ethRst(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field ETH_RST in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ethRst(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FRAMEDIFF_ADJUST at 0x40236 bits [6..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_framediffAdjust(unsigned fibre) const =0 ;


    /**
     * Read field FRAMEDIFF_ADJUST at 0x40236 bits [6..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_framediffAdjust(unsigned fibre) const =0 ;




    /**
     * Read field REMOTE_LOS at 0x40238 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_remoteLos(unsigned fibre) const =0 ;


    /**
     * Read field REMOTE_LOS at 0x40238 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_remoteLos(unsigned fibre) const =0 ;




    /**
     * Read field REMOTE_LOF at 0x40238 bits [1]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_remoteLof(unsigned fibre) const =0 ;


    /**
     * Read field REMOTE_LOF at 0x40238 bits [1]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_remoteLof(unsigned fibre) const =0 ;




    /**
     * Read field REMOTE_RAI at 0x40238 bits [2]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_remoteRai(unsigned fibre) const =0 ;


    /**
     * Read field REMOTE_RAI at 0x40238 bits [2]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_remoteRai(unsigned fibre) const =0 ;




    /**
     * Read field RX_REID at 0x40248 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_rxReid(unsigned fibre) const =0 ;


    /**
     * Read field RX_REID at 0x40248 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxReid(unsigned fibre) const =0 ;




    /**
     * Read field TX_CDC_FIFO_DELAY at 0x4024c bits [13..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txCdcFifoDelay(unsigned fibre) const =0 ;


    /**
     * Read field TX_CDC_FIFO_DELAY at 0x4024c bits [13..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txCdcFifoDelay(unsigned fibre) const =0 ;




    /**
     * Read field NODE_BFN_TX_FRAME_DLY at 0x40250 bits [6..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nodeBfnTxFrameDly(unsigned fibre) const =0 ;

    /**
     * Write field NODE_BFN_TX_FRAME_DLY at 0x40250 bits [6..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nodeBfnTxFrameDly(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field NODE_BFN_TX_FRAME_DLY at 0x40250 bits [6..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_nodeBfnTxFrameDly(unsigned fibre) const =0 ;

    /**
     * Write field NODE_BFN_TX_FRAME_DLY at 0x40250 bits [6..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_nodeBfnTxFrameDly(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field NODE_BFN_TX_FRAME_DLY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_nodeBfnTxFrameDly(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field VSS_BAD_MSG_ERROR_CODE at 0x402c0 bits [2..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_vssBadMsgErrorCode(unsigned fibre) const =0 ;


    /**
     * Read field VSS_BAD_MSG_ERROR_CODE at 0x402c0 bits [2..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vssBadMsgErrorCode(unsigned fibre) const =0 ;




    /**
     * Read field VSS_BAD_MSG_ERROR_CODE_RESET at 0x402c0 bits [7]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_vssBadMsgErrorCodeReset(unsigned fibre) const =0 ;

    /**
     * Write field VSS_BAD_MSG_ERROR_CODE_RESET at 0x402c0 bits [7]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_vssBadMsgErrorCodeReset(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field VSS_BAD_MSG_ERROR_CODE_RESET at 0x402c0 bits [7]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vssBadMsgErrorCodeReset(unsigned fibre) const =0 ;

    /**
     * Write field VSS_BAD_MSG_ERROR_CODE_RESET at 0x402c0 bits [7]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_vssBadMsgErrorCodeReset(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field VSS_BAD_MSG_ERROR_CODE_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_vssBadMsgErrorCodeReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SFP_RATE at 0x40300 bits [1..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_sfpRate(unsigned fibre) const =0 ;

    /**
     * Write field SFP_RATE at 0x40300 bits [1..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sfpRate(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field SFP_RATE at 0x40300 bits [1..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfpRate(unsigned fibre) const =0 ;

    /**
     * Write field SFP_RATE at 0x40300 bits [1..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sfpRate(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field SFP_RATE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sfpRate(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SFP_TX_DISABLE at 0x40300 bits [4]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_sfpTxDisable(unsigned fibre) const =0 ;

    /**
     * Write field SFP_TX_DISABLE at 0x40300 bits [4]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sfpTxDisable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field SFP_TX_DISABLE at 0x40300 bits [4]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfpTxDisable(unsigned fibre) const =0 ;

    /**
     * Write field SFP_TX_DISABLE at 0x40300 bits [4]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sfpTxDisable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field SFP_TX_DISABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sfpTxDisable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SFP_PLL_RESET at 0x40300 bits [5]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_sfpPllReset(unsigned fibre) const =0 ;

    /**
     * Write field SFP_PLL_RESET at 0x40300 bits [5]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sfpPllReset(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field SFP_PLL_RESET at 0x40300 bits [5]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfpPllReset(unsigned fibre) const =0 ;

    /**
     * Write field SFP_PLL_RESET at 0x40300 bits [5]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sfpPllReset(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field SFP_PLL_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sfpPllReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SFP_MODULE_LOS at 0x40300 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_sfpModuleLos(unsigned fibre) const =0 ;


    /**
     * Read field SFP_MODULE_LOS at 0x40300 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfpModuleLos(unsigned fibre) const =0 ;




    /**
     * Read field SFP_TX_FAULT at 0x40300 bits [9]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_sfpTxFault(unsigned fibre) const =0 ;


    /**
     * Read field SFP_TX_FAULT at 0x40300 bits [9]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfpTxFault(unsigned fibre) const =0 ;




    /**
     * Read field SFP_MOD_ABS at 0x40300 bits [12]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_sfpModAbs(unsigned fibre) const =0 ;


    /**
     * Read field SFP_MOD_ABS at 0x40300 bits [12]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfpModAbs(unsigned fibre) const =0 ;




    /**
     * Read field SFP_PWR_FAULT_N at 0x40300 bits [13]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_sfpPwrFaultN(unsigned fibre) const =0 ;


    /**
     * Read field SFP_PWR_FAULT_N at 0x40300 bits [13]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfpPwrFaultN(unsigned fibre) const =0 ;




    /**
     * Read field SFP_PLL_INT at 0x40300 bits [14]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_sfpPllInt(unsigned fibre) const =0 ;


    /**
     * Read field SFP_PLL_INT at 0x40300 bits [14]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfpPllInt(unsigned fibre) const =0 ;




    /**
     * Read field EYE_SCAN_ENABLE at 0x40308 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_eyeScanEnable(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_ENABLE at 0x40308 bits [0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_eyeScanEnable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field EYE_SCAN_ENABLE at 0x40308 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_eyeScanEnable(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_ENABLE at 0x40308 bits [0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_eyeScanEnable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field EYE_SCAN_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_eyeScanEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field EYE_SCAN_ADDR_RESET at 0x40308 bits [1]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_eyeScanAddrReset(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_ADDR_RESET at 0x40308 bits [1]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_eyeScanAddrReset(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field EYE_SCAN_ADDR_RESET at 0x40308 bits [1]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_eyeScanAddrReset(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_ADDR_RESET at 0x40308 bits [1]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_eyeScanAddrReset(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field EYE_SCAN_ADDR_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_eyeScanAddrReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field EYE_SCAN_BUFFER_FULL_RESUME at 0x40308 bits [2]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_eyeScanBufferFullResume(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_BUFFER_FULL_RESUME at 0x40308 bits [2]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_eyeScanBufferFullResume(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field EYE_SCAN_BUFFER_FULL_RESUME at 0x40308 bits [2]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_eyeScanBufferFullResume(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_BUFFER_FULL_RESUME at 0x40308 bits [2]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_eyeScanBufferFullResume(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field EYE_SCAN_BUFFER_FULL_RESUME in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_eyeScanBufferFullResume(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field EYE_SCAN_DONE at 0x40308 bits [3]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_eyeScanDone(unsigned fibre) const =0 ;


    /**
     * Read field EYE_SCAN_DONE at 0x40308 bits [3]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_eyeScanDone(unsigned fibre) const =0 ;




    /**
     * Read field EYE_SCAN_BUFF_SIZE at 0x40308 bits [7..4]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_eyeScanBuffSize(unsigned fibre) const =0 ;


    /**
     * Read field EYE_SCAN_BUFF_SIZE at 0x40308 bits [7..4]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_eyeScanBuffSize(unsigned fibre) const =0 ;




    /**
     * Read field EYE_SCAN_MAX_PRESCALE at 0x40308 bits [12..8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_eyeScanMaxPrescale(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_MAX_PRESCALE at 0x40308 bits [12..8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_eyeScanMaxPrescale(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field EYE_SCAN_MAX_PRESCALE at 0x40308 bits [12..8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_eyeScanMaxPrescale(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_MAX_PRESCALE at 0x40308 bits [12..8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_eyeScanMaxPrescale(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field EYE_SCAN_MAX_PRESCALE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_eyeScanMaxPrescale(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field EYE_SCAN_VERT_STEP at 0x4030a bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_eyeScanVertStep(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_VERT_STEP at 0x4030a bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_eyeScanVertStep(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field EYE_SCAN_VERT_STEP at 0x4030a bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_eyeScanVertStep(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_VERT_STEP at 0x4030a bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_eyeScanVertStep(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field EYE_SCAN_VERT_STEP in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_eyeScanVertStep(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field EYE_SCAN_HORIZ_STEP at 0x4030a bits [15..8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_eyeScanHorizStep(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_HORIZ_STEP at 0x4030a bits [15..8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_eyeScanHorizStep(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field EYE_SCAN_HORIZ_STEP at 0x4030a bits [15..8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_eyeScanHorizStep(unsigned fibre) const =0 ;

    /**
     * Write field EYE_SCAN_HORIZ_STEP at 0x4030a bits [15..8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_eyeScanHorizStep(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field EYE_SCAN_HORIZ_STEP in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_eyeScanHorizStep(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field EYE_SCAN_HIGH_WORD at 0x4030c bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_eyeScanHighWord(unsigned fibre) const =0 ;


    /**
     * Read field EYE_SCAN_HIGH_WORD at 0x4030c bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_eyeScanHighWord(unsigned fibre) const =0 ;




    /**
     * Read field EYE_SCAN_LOW_WORD at 0x4030e bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_eyeScanLowWord(unsigned fibre) const =0 ;


    /**
     * Read field EYE_SCAN_LOW_WORD at 0x4030e bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_eyeScanLowWord(unsigned fibre) const =0 ;





    /**
     * Read combined register XILINX_CORE_REVISION at 0x40008 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_xilinxCoreRevision(unsigned fibre) const =0 ;







    /**
     * Read combined register XILINX_CORE_REVISION at 0x40008 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xilinxCoreRevision(unsigned fibre) const =0 ;



    /**
     * Read combined register TX_SEED at 0x4020a bits [30..0]
     * \return field value
     */
    virtual const FpgaVal read_txSeed(unsigned fibre) const =0 ;






    /**
     * Write combined field TX_SEED at 0x4020a bits [30..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txSeed(unsigned fibre, FpgaVal value) =0 ;






    /**
     * Read combined register TX_SEED at 0x4020a bits [30..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txSeed(unsigned fibre) const =0 ;






    /**
     * Write combined field TX_SEED at 0x4020a bits [30..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txSeed(unsigned fibre, FpgaVal value) =0 ;


    /**
     * Read combined register FIBRE_STATUS at 0x4020c bits [15..7,3..0]
     * \return field value
     */
    virtual const FpgaVal read_fibreStatus(unsigned fibre) const =0 ;







    /**
     * Read combined register FIBRE_STATUS at 0x4020c bits [15..7,3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fibreStatus(unsigned fibre) const =0 ;



    /**
     * Read combined register RX_SEED at 0x40216 bits [30..0]
     * \return field value
     */
    virtual const FpgaVal read_rxSeed(unsigned fibre) const =0 ;







    /**
     * Read combined register RX_SEED at 0x40216 bits [30..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxSeed(unsigned fibre) const =0 ;




};


} /* namespace Mplane */

#endif /* _IFIBRE_REGS_DEF_H_ */
