#ifndef _ICHAIN_REGS_DEF_H_
#define _ICHAIN_REGS_DEF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaChainRegs.h
 * \brief     FPGA Chain registers virtual interface
 *
 *
 * \details   This file defines the FPGA Chain registers.
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

class IFpgaChainRegs : public virtual IFpgaRegs
{
public:
	IFpgaChainRegs() {}
	virtual ~IFpgaChainRegs(void) {} ;

    /** \brief  Does FPGA have a CHAIN registers block
     *
     *  \return true if the FPGA instance does actually support a Chain registers block
     */
    virtual bool hasChainRegisters(void) =0 ;

    /*! \brief  Get base address
     *
     *  Get the base address of the Chain registers (if supported)
     *
     *  \return base address of Chain registers; 0 if not supported
     */
    virtual UINT32 getChainBlockAddr(void) =0 ;

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
     * Read field DL_RF_CHAIN_PATH at 0x78000 bits [3..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlRfChainPath(unsigned chainiq) const =0 ;


    /**
     * Read field DL_RF_CHAIN_PATH at 0x78000 bits [3..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlRfChainPath(unsigned chainiq) const =0 ;




    /**
     * Read field DL_RF_CHAIN_TYPE at 0x78000 bits [11..8]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlRfChainType(unsigned chainiq) const =0 ;


    /**
     * Read field DL_RF_CHAIN_TYPE at 0x78000 bits [11..8]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlRfChainType(unsigned chainiq) const =0 ;




    /**
     * Read field DL_RF_CHAIN_IQ_STREAM at 0x78002 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlRfChainIqStream(unsigned chainiq) const =0 ;


    /**
     * Read field DL_RF_CHAIN_IQ_STREAM at 0x78002 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlRfChainIqStream(unsigned chainiq) const =0 ;




    /**
     * Read field DL_RF_CHAIN_ANT_PORT at 0x78004 bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlRfChainAntPort(unsigned chainiq) const =0 ;


    /**
     * Read field DL_RF_CHAIN_ANT_PORT at 0x78004 bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlRfChainAntPort(unsigned chainiq) const =0 ;




    /**
     * Read field DL_RF_CHAIN_AIR_STD at 0x78006 bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlRfChainAirStd(unsigned chainiq) const =0 ;

    /**
     * Write field DL_RF_CHAIN_AIR_STD at 0x78006 bits [7..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dlRfChainAirStd(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field DL_RF_CHAIN_AIR_STD at 0x78006 bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlRfChainAirStd(unsigned chainiq) const =0 ;

    /**
     * Write field DL_RF_CHAIN_AIR_STD at 0x78006 bits [7..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dlRfChainAirStd(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field DL_RF_CHAIN_AIR_STD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dlRfChainAirStd(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_RF_CHAIN_AIR_STD at 0x78006 bits [15..8]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulRfChainAirStd(unsigned chainiq) const =0 ;

    /**
     * Write field UL_RF_CHAIN_AIR_STD at 0x78006 bits [15..8]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulRfChainAirStd(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_RF_CHAIN_AIR_STD at 0x78006 bits [15..8]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulRfChainAirStd(unsigned chainiq) const =0 ;

    /**
     * Write field UL_RF_CHAIN_AIR_STD at 0x78006 bits [15..8]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulRfChainAirStd(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_RF_CHAIN_AIR_STD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulRfChainAirStd(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_RF_CHAIN_PATH at 0x78008 bits [3..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulRfChainPath(unsigned chainiq) const =0 ;


    /**
     * Read field UL_RF_CHAIN_PATH at 0x78008 bits [3..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulRfChainPath(unsigned chainiq) const =0 ;




    /**
     * Read field UL_RF_CHAIN_TYPE at 0x78008 bits [11..8]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulRfChainType(unsigned chainiq) const =0 ;


    /**
     * Read field UL_RF_CHAIN_TYPE at 0x78008 bits [11..8]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulRfChainType(unsigned chainiq) const =0 ;




    /**
     * Read field UL_RF_CHAIN_IQ_STREAM at 0x7800a bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulRfChainIqStream(unsigned chainiq) const =0 ;


    /**
     * Read field UL_RF_CHAIN_IQ_STREAM at 0x7800a bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulRfChainIqStream(unsigned chainiq) const =0 ;




    /**
     * Read field UL_RF_CHAIN_ANT_PORT at 0x7800c bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulRfChainAntPort(unsigned chainiq) const =0 ;


    /**
     * Read field UL_RF_CHAIN_ANT_PORT at 0x7800c bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulRfChainAntPort(unsigned chainiq) const =0 ;




    /**
     * Read field FIBRE_CONNECTION at 0x7800e bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_fibreConnection(unsigned chainiq) const =0 ;

    /**
     * Write field FIBRE_CONNECTION at 0x7800e bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fibreConnection(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field FIBRE_CONNECTION at 0x7800e bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fibreConnection(unsigned chainiq) const =0 ;

    /**
     * Write field FIBRE_CONNECTION at 0x7800e bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fibreConnection(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field FIBRE_CONNECTION in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fibreConnection(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DL_UNDERPOWER at 0x78010 bits [1]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlUnderpower(unsigned chainiq) const =0 ;


    /**
     * Read field DL_UNDERPOWER at 0x78010 bits [1]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlUnderpower(unsigned chainiq) const =0 ;




    /**
     * Read field DL_OVERPOWER at 0x78010 bits [2]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlOverpower(unsigned chainiq) const =0 ;


    /**
     * Read field DL_OVERPOWER at 0x78010 bits [2]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlOverpower(unsigned chainiq) const =0 ;




    /**
     * Read field DL_SHUTDOWN at 0x78010 bits [3]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlShutdown(unsigned chainiq) const =0 ;


    /**
     * Read field DL_SHUTDOWN at 0x78010 bits [3]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlShutdown(unsigned chainiq) const =0 ;




    /**
     * Read field DL_TSSI at 0x78012 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlTssi(unsigned chainiq) const =0 ;


    /**
     * Read field DL_TSSI at 0x78012 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlTssi(unsigned chainiq) const =0 ;




    /**
     * Read field UL_RSSI_LO at 0x78014 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulRssiLo(unsigned chainiq) const =0 ;


    /**
     * Read field UL_RSSI_LO at 0x78014 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulRssiLo(unsigned chainiq) const =0 ;




    /**
     * Read field UL_RSSI_HI at 0x78016 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulRssiHi(unsigned chainiq) const =0 ;


    /**
     * Read field UL_RSSI_HI at 0x78016 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulRssiHi(unsigned chainiq) const =0 ;




    /**
     * Read field DL_SYNC_FAIL at 0x78018 bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlSyncFail(unsigned chainiq) const =0 ;


    /**
     * Read field DL_SYNC_FAIL at 0x78018 bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlSyncFail(unsigned chainiq) const =0 ;




    /**
     * Read field DL_OFLOW at 0x78018 bits [1]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlOflow(unsigned chainiq) const =0 ;


    /**
     * Read field DL_OFLOW at 0x78018 bits [1]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlOflow(unsigned chainiq) const =0 ;




    /**
     * Read field DL_UFLOW at 0x78018 bits [2]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlUflow(unsigned chainiq) const =0 ;


    /**
     * Read field DL_UFLOW at 0x78018 bits [2]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlUflow(unsigned chainiq) const =0 ;




    /**
     * Read field DL_SYNC at 0x78018 bits [4]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlSync(unsigned chainiq) const =0 ;


    /**
     * Read field DL_SYNC at 0x78018 bits [4]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlSync(unsigned chainiq) const =0 ;




    /**
     * Read field UL_SYNC_FAIL at 0x78018 bits [8]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulSyncFail(unsigned chainiq) const =0 ;


    /**
     * Read field UL_SYNC_FAIL at 0x78018 bits [8]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulSyncFail(unsigned chainiq) const =0 ;




    /**
     * Read field UL_OFLOW at 0x78018 bits [9]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulOflow(unsigned chainiq) const =0 ;


    /**
     * Read field UL_OFLOW at 0x78018 bits [9]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulOflow(unsigned chainiq) const =0 ;




    /**
     * Read field UL_UFLOW at 0x78018 bits [10]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulUflow(unsigned chainiq) const =0 ;


    /**
     * Read field UL_UFLOW at 0x78018 bits [10]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulUflow(unsigned chainiq) const =0 ;




    /**
     * Read field UL_SYNC at 0x78018 bits [12]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulSync(unsigned chainiq) const =0 ;


    /**
     * Read field UL_SYNC at 0x78018 bits [12]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulSync(unsigned chainiq) const =0 ;




    /**
     * Read field DL_SAMP_BUF_SIZE at 0x7801a bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlSampBufSize(unsigned chainiq) const =0 ;


    /**
     * Read field DL_SAMP_BUF_SIZE at 0x7801a bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlSampBufSize(unsigned chainiq) const =0 ;




    /**
     * Read field UL_SAMP_BUF_SIZE at 0x7801a bits [15..8]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulSampBufSize(unsigned chainiq) const =0 ;


    /**
     * Read field UL_SAMP_BUF_SIZE at 0x7801a bits [15..8]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulSampBufSize(unsigned chainiq) const =0 ;




    /**
     * Read field DL_WCDMA_RPT_EN_FAST at 0x7801c bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlWcdmaRptEnFast(unsigned chainiq) const =0 ;

    /**
     * Write field DL_WCDMA_RPT_EN_FAST at 0x7801c bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dlWcdmaRptEnFast(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field DL_WCDMA_RPT_EN_FAST at 0x7801c bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlWcdmaRptEnFast(unsigned chainiq) const =0 ;

    /**
     * Write field DL_WCDMA_RPT_EN_FAST at 0x7801c bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dlWcdmaRptEnFast(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field DL_WCDMA_RPT_EN_FAST in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dlWcdmaRptEnFast(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_WCDMA_RPT_EN_FAST at 0x7801c bits [1]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulWcdmaRptEnFast(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WCDMA_RPT_EN_FAST at 0x7801c bits [1]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulWcdmaRptEnFast(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_WCDMA_RPT_EN_FAST at 0x7801c bits [1]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulWcdmaRptEnFast(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WCDMA_RPT_EN_FAST at 0x7801c bits [1]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulWcdmaRptEnFast(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_WCDMA_RPT_EN_FAST in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulWcdmaRptEnFast(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DL_WCDMA_RPT_EN_SLOW at 0x7801c bits [2]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlWcdmaRptEnSlow(unsigned chainiq) const =0 ;

    /**
     * Write field DL_WCDMA_RPT_EN_SLOW at 0x7801c bits [2]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dlWcdmaRptEnSlow(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field DL_WCDMA_RPT_EN_SLOW at 0x7801c bits [2]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlWcdmaRptEnSlow(unsigned chainiq) const =0 ;

    /**
     * Write field DL_WCDMA_RPT_EN_SLOW at 0x7801c bits [2]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dlWcdmaRptEnSlow(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field DL_WCDMA_RPT_EN_SLOW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dlWcdmaRptEnSlow(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_WCDMA_RPT_EN_SLOW at 0x7801c bits [3]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulWcdmaRptEnSlow(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WCDMA_RPT_EN_SLOW at 0x7801c bits [3]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulWcdmaRptEnSlow(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_WCDMA_RPT_EN_SLOW at 0x7801c bits [3]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulWcdmaRptEnSlow(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WCDMA_RPT_EN_SLOW at 0x7801c bits [3]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulWcdmaRptEnSlow(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_WCDMA_RPT_EN_SLOW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulWcdmaRptEnSlow(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WCDMA_RPT_NFAST at 0x7801e bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_wcdmaRptNfast(unsigned chainiq) const =0 ;

    /**
     * Write field WCDMA_RPT_NFAST at 0x7801e bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_wcdmaRptNfast(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field WCDMA_RPT_NFAST at 0x7801e bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wcdmaRptNfast(unsigned chainiq) const =0 ;

    /**
     * Write field WCDMA_RPT_NFAST at 0x7801e bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_wcdmaRptNfast(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field WCDMA_RPT_NFAST in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_wcdmaRptNfast(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_WCDMA_RPT_SYS_GAIN at 0x78020 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulWcdmaRptSysGain(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WCDMA_RPT_SYS_GAIN at 0x78020 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulWcdmaRptSysGain(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_WCDMA_RPT_SYS_GAIN at 0x78020 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulWcdmaRptSysGain(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WCDMA_RPT_SYS_GAIN at 0x78020 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulWcdmaRptSysGain(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_WCDMA_RPT_SYS_GAIN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulWcdmaRptSysGain(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_WCDMA_KNUMERATOR at 0x78022 bits [8..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulWcdmaKnumerator(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WCDMA_KNUMERATOR at 0x78022 bits [8..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulWcdmaKnumerator(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_WCDMA_KNUMERATOR at 0x78022 bits [8..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulWcdmaKnumerator(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WCDMA_KNUMERATOR at 0x78022 bits [8..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulWcdmaKnumerator(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_WCDMA_KNUMERATOR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulWcdmaKnumerator(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_WCDMA_LOG2_N at 0x78024 bits [4..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulWcdmaLog2N(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WCDMA_LOG2_N at 0x78024 bits [4..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulWcdmaLog2N(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_WCDMA_LOG2_N at 0x78024 bits [4..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulWcdmaLog2N(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WCDMA_LOG2_N at 0x78024 bits [4..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulWcdmaLog2N(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_WCDMA_LOG2_N in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulWcdmaLog2N(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WCDMA_EN_SEL at 0x78026 bits [3..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_wcdmaEnSel(unsigned chainiq) const =0 ;

    /**
     * Write field WCDMA_EN_SEL at 0x78026 bits [3..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_wcdmaEnSel(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field WCDMA_EN_SEL at 0x78026 bits [3..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wcdmaEnSel(unsigned chainiq) const =0 ;

    /**
     * Write field WCDMA_EN_SEL at 0x78026 bits [3..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_wcdmaEnSel(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field WCDMA_EN_SEL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_wcdmaEnSel(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RF_CHAIN_CHAN_BW at 0x7802e bits [4..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_rfChainChanBw(unsigned chainiq) const =0 ;

    /**
     * Write field RF_CHAIN_CHAN_BW at 0x7802e bits [4..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rfChainChanBw(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field RF_CHAIN_CHAN_BW at 0x7802e bits [4..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rfChainChanBw(unsigned chainiq) const =0 ;

    /**
     * Write field RF_CHAIN_CHAN_BW at 0x7802e bits [4..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rfChainChanBw(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field RF_CHAIN_CHAN_BW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rfChainChanBw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SAMPLE_RATE_N at 0x78030 bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_sampleRateN(unsigned chainiq) const =0 ;

    /**
     * Write field SAMPLE_RATE_N at 0x78030 bits [7..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sampleRateN(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field SAMPLE_RATE_N at 0x78030 bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sampleRateN(unsigned chainiq) const =0 ;

    /**
     * Write field SAMPLE_RATE_N at 0x78030 bits [7..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sampleRateN(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field SAMPLE_RATE_N in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sampleRateN(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SAMPLE_RATE_A at 0x78032 bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_sampleRateA(unsigned chainiq) const =0 ;

    /**
     * Write field SAMPLE_RATE_A at 0x78032 bits [7..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sampleRateA(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field SAMPLE_RATE_A at 0x78032 bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sampleRateA(unsigned chainiq) const =0 ;

    /**
     * Write field SAMPLE_RATE_A at 0x78032 bits [7..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sampleRateA(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field SAMPLE_RATE_A in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sampleRateA(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SAMPLE_RATE_B at 0x78034 bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_sampleRateB(unsigned chainiq) const =0 ;

    /**
     * Write field SAMPLE_RATE_B at 0x78034 bits [7..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sampleRateB(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field SAMPLE_RATE_B at 0x78034 bits [7..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sampleRateB(unsigned chainiq) const =0 ;

    /**
     * Write field SAMPLE_RATE_B at 0x78034 bits [7..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sampleRateB(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field SAMPLE_RATE_B in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sampleRateB(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DL_PROCESSING at 0x78036 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlProcessing(unsigned chainiq) const =0 ;

    /**
     * Write field DL_PROCESSING at 0x78036 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dlProcessing(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field DL_PROCESSING at 0x78036 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlProcessing(unsigned chainiq) const =0 ;

    /**
     * Write field DL_PROCESSING at 0x78036 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dlProcessing(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field DL_PROCESSING in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dlProcessing(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_PROCESSING at 0x78038 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulProcessing(unsigned chainiq) const =0 ;

    /**
     * Write field UL_PROCESSING at 0x78038 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulProcessing(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_PROCESSING at 0x78038 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulProcessing(unsigned chainiq) const =0 ;

    /**
     * Write field UL_PROCESSING at 0x78038 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulProcessing(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_PROCESSING in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulProcessing(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RESYNC_DL at 0x7803a bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_resyncDl(unsigned chainiq) const =0 ;

    /**
     * Write field RESYNC_DL at 0x7803a bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_resyncDl(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field RESYNC_DL at 0x7803a bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_resyncDl(unsigned chainiq) const =0 ;

    /**
     * Write field RESYNC_DL at 0x7803a bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_resyncDl(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field RESYNC_DL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_resyncDl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RESYNC_UL at 0x7803a bits [1]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_resyncUl(unsigned chainiq) const =0 ;

    /**
     * Write field RESYNC_UL at 0x7803a bits [1]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_resyncUl(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field RESYNC_UL at 0x7803a bits [1]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_resyncUl(unsigned chainiq) const =0 ;

    /**
     * Write field RESYNC_UL at 0x7803a bits [1]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_resyncUl(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field RESYNC_UL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_resyncUl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field IQ_LOOPBACK at 0x7803a bits [4]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_iqLoopback(unsigned chainiq) const =0 ;

    /**
     * Write field IQ_LOOPBACK at 0x7803a bits [4]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_iqLoopback(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field IQ_LOOPBACK at 0x7803a bits [4]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_iqLoopback(unsigned chainiq) const =0 ;

    /**
     * Write field IQ_LOOPBACK at 0x7803a bits [4]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_iqLoopback(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field IQ_LOOPBACK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_iqLoopback(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SCALE_FACTOR at 0x7803c bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_scaleFactor(unsigned chainiq) const =0 ;

    /**
     * Write field SCALE_FACTOR at 0x7803c bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_scaleFactor(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field SCALE_FACTOR at 0x7803c bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_scaleFactor(unsigned chainiq) const =0 ;

    /**
     * Write field SCALE_FACTOR at 0x7803c bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_scaleFactor(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field SCALE_FACTOR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_scaleFactor(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DL_FREQ_OFFSET_LO at 0x7803e bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlFreqOffsetLo(unsigned chainiq) const =0 ;

    /**
     * Write field DL_FREQ_OFFSET_LO at 0x7803e bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dlFreqOffsetLo(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field DL_FREQ_OFFSET_LO at 0x7803e bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlFreqOffsetLo(unsigned chainiq) const =0 ;

    /**
     * Write field DL_FREQ_OFFSET_LO at 0x7803e bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dlFreqOffsetLo(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field DL_FREQ_OFFSET_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dlFreqOffsetLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DL_FREQ_OFFSET_HI at 0x78040 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlFreqOffsetHi(unsigned chainiq) const =0 ;

    /**
     * Write field DL_FREQ_OFFSET_HI at 0x78040 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dlFreqOffsetHi(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field DL_FREQ_OFFSET_HI at 0x78040 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlFreqOffsetHi(unsigned chainiq) const =0 ;

    /**
     * Write field DL_FREQ_OFFSET_HI at 0x78040 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dlFreqOffsetHi(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field DL_FREQ_OFFSET_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dlFreqOffsetHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DL_FREQ_OFFSET_UPDATED at 0x78042 bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlFreqOffsetUpdated(unsigned chainiq) const =0 ;

    /**
     * Write field DL_FREQ_OFFSET_UPDATED at 0x78042 bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dlFreqOffsetUpdated(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field DL_FREQ_OFFSET_UPDATED at 0x78042 bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlFreqOffsetUpdated(unsigned chainiq) const =0 ;

    /**
     * Write field DL_FREQ_OFFSET_UPDATED at 0x78042 bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dlFreqOffsetUpdated(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field DL_FREQ_OFFSET_UPDATED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dlFreqOffsetUpdated(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_FREQ_OFFSET_LO at 0x78044 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulFreqOffsetLo(unsigned chainiq) const =0 ;

    /**
     * Write field UL_FREQ_OFFSET_LO at 0x78044 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulFreqOffsetLo(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_FREQ_OFFSET_LO at 0x78044 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulFreqOffsetLo(unsigned chainiq) const =0 ;

    /**
     * Write field UL_FREQ_OFFSET_LO at 0x78044 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulFreqOffsetLo(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_FREQ_OFFSET_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulFreqOffsetLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_FREQ_OFFSET_HI at 0x78046 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulFreqOffsetHi(unsigned chainiq) const =0 ;

    /**
     * Write field UL_FREQ_OFFSET_HI at 0x78046 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulFreqOffsetHi(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_FREQ_OFFSET_HI at 0x78046 bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulFreqOffsetHi(unsigned chainiq) const =0 ;

    /**
     * Write field UL_FREQ_OFFSET_HI at 0x78046 bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulFreqOffsetHi(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_FREQ_OFFSET_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulFreqOffsetHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_FILTER_BANK_SEL at 0x78048 bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulFilterBankSel(unsigned chainiq) const =0 ;

    /**
     * Write field UL_FILTER_BANK_SEL at 0x78048 bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulFilterBankSel(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_FILTER_BANK_SEL at 0x78048 bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulFilterBankSel(unsigned chainiq) const =0 ;

    /**
     * Write field UL_FILTER_BANK_SEL at 0x78048 bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulFilterBankSel(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_FILTER_BANK_SEL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulFilterBankSel(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_FREQ_OFFSET_UPDATED at 0x7804a bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulFreqOffsetUpdated(unsigned chainiq) const =0 ;

    /**
     * Write field UL_FREQ_OFFSET_UPDATED at 0x7804a bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulFreqOffsetUpdated(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_FREQ_OFFSET_UPDATED at 0x7804a bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulFreqOffsetUpdated(unsigned chainiq) const =0 ;

    /**
     * Write field UL_FREQ_OFFSET_UPDATED at 0x7804a bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulFreqOffsetUpdated(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_FREQ_OFFSET_UPDATED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulFreqOffsetUpdated(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WEIGHTING at 0x7804c bits [9..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_weighting(unsigned chainiq) const =0 ;

    /**
     * Write field WEIGHTING at 0x7804c bits [9..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_weighting(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field WEIGHTING at 0x7804c bits [9..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_weighting(unsigned chainiq) const =0 ;

    /**
     * Write field WEIGHTING at 0x7804c bits [9..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_weighting(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field WEIGHTING in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_weighting(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ENABLE at 0x7804c bits [10]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_enable(unsigned chainiq) const =0 ;

    /**
     * Write field ENABLE at 0x7804c bits [10]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_enable(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field ENABLE at 0x7804c bits [10]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_enable(unsigned chainiq) const =0 ;

    /**
     * Write field ENABLE at 0x7804c bits [10]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_enable(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_ADCRSSI_LO at 0x7804e bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulAdcrssiLo(unsigned chainiq) const =0 ;


    /**
     * Read field UL_ADCRSSI_LO at 0x7804e bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulAdcrssiLo(unsigned chainiq) const =0 ;




    /**
     * Read field UL_ADCRSSI_HI at 0x78050 bits [10..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulAdcrssiHi(unsigned chainiq) const =0 ;


    /**
     * Read field UL_ADCRSSI_HI at 0x78050 bits [10..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulAdcrssiHi(unsigned chainiq) const =0 ;




    /**
     * Read field UL_RSSI_RX_FE_ATTEN at 0x78052 bits [2..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulRssiRxFeAtten(unsigned chainiq) const =0 ;


    /**
     * Read field UL_RSSI_RX_FE_ATTEN at 0x78052 bits [2..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulRssiRxFeAtten(unsigned chainiq) const =0 ;




    /**
     * Read field UL_WEIGHTING at 0x78054 bits [9..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulWeighting(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WEIGHTING at 0x78054 bits [9..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulWeighting(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_WEIGHTING at 0x78054 bits [9..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulWeighting(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WEIGHTING at 0x78054 bits [9..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulWeighting(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_WEIGHTING in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulWeighting(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DL_TSSI_DECIMAL at 0x78056 bits [5..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_dlTssiDecimal(unsigned chainiq) const =0 ;


    /**
     * Read field DL_TSSI_DECIMAL at 0x78056 bits [5..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlTssiDecimal(unsigned chainiq) const =0 ;




    /**
     * Read field IEQ_ADDR at 0x78058 bits [3..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ieqAddr(unsigned chainiq) const =0 ;

    /**
     * Write field IEQ_ADDR at 0x78058 bits [3..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ieqAddr(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field IEQ_ADDR at 0x78058 bits [3..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ieqAddr(unsigned chainiq) const =0 ;

    /**
     * Write field IEQ_ADDR at 0x78058 bits [3..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ieqAddr(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field IEQ_ADDR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ieqAddr(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field IEQ_COEFF_IMAG at 0x7805a bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ieqCoeffImag(unsigned chainiq) const =0 ;

    /**
     * Write field IEQ_COEFF_IMAG at 0x7805a bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ieqCoeffImag(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field IEQ_COEFF_IMAG at 0x7805a bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ieqCoeffImag(unsigned chainiq) const =0 ;

    /**
     * Write field IEQ_COEFF_IMAG at 0x7805a bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ieqCoeffImag(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field IEQ_COEFF_IMAG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ieqCoeffImag(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field IEQ_COEFF_REAL at 0x7805c bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ieqCoeffReal(unsigned chainiq) const =0 ;

    /**
     * Write field IEQ_COEFF_REAL at 0x7805c bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ieqCoeffReal(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field IEQ_COEFF_REAL at 0x7805c bits [15..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ieqCoeffReal(unsigned chainiq) const =0 ;

    /**
     * Write field IEQ_COEFF_REAL at 0x7805c bits [15..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ieqCoeffReal(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field IEQ_COEFF_REAL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ieqCoeffReal(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field IEQ_COEFF_BANK at 0x7805e bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ieqCoeffBank(unsigned chainiq) const =0 ;

    /**
     * Write field IEQ_COEFF_BANK at 0x7805e bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ieqCoeffBank(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field IEQ_COEFF_BANK at 0x7805e bits [0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ieqCoeffBank(unsigned chainiq) const =0 ;

    /**
     * Write field IEQ_COEFF_BANK at 0x7805e bits [0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ieqCoeffBank(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field IEQ_COEFF_BANK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ieqCoeffBank(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_WEIGHT_CHBW_DATA at 0x78060 bits [9..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulWeightChbwData(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WEIGHT_CHBW_DATA at 0x78060 bits [9..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulWeightChbwData(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_WEIGHT_CHBW_DATA at 0x78060 bits [9..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulWeightChbwData(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WEIGHT_CHBW_DATA at 0x78060 bits [9..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulWeightChbwData(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_WEIGHT_CHBW_DATA in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulWeightChbwData(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_WEIGHT_CHBW_UNUSED at 0x78060 bits [11..10]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulWeightChbwUnused(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WEIGHT_CHBW_UNUSED at 0x78060 bits [11..10]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulWeightChbwUnused(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_WEIGHT_CHBW_UNUSED at 0x78060 bits [11..10]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulWeightChbwUnused(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WEIGHT_CHBW_UNUSED at 0x78060 bits [11..10]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulWeightChbwUnused(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_WEIGHT_CHBW_UNUSED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulWeightChbwUnused(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_WEIGHT_CHBW_BW at 0x78060 bits [15..12]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_ulWeightChbwBw(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WEIGHT_CHBW_BW at 0x78060 bits [15..12]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulWeightChbwBw(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field UL_WEIGHT_CHBW_BW at 0x78060 bits [15..12]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulWeightChbwBw(unsigned chainiq) const =0 ;

    /**
     * Write field UL_WEIGHT_CHBW_BW at 0x78060 bits [15..12]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulWeightChbwBw(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field UL_WEIGHT_CHBW_BW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulWeightChbwBw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ADDITIONAL_UL_DELAY at 0x7806a bits [11..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_AdditionalUlDelay(unsigned chainiq) const =0 ;

    /**
     * Write field ADDITIONAL_UL_DELAY at 0x7806a bits [11..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_AdditionalUlDelay(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Read field ADDITIONAL_UL_DELAY at 0x7806a bits [11..0]
     * \param chainiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_AdditionalUlDelay(unsigned chainiq) const =0 ;

    /**
     * Write field ADDITIONAL_UL_DELAY at 0x7806a bits [11..0]
     * \param chainiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_AdditionalUlDelay(unsigned chainiq, FpgaVal value) =0 ;

    /**
     * Write field ADDITIONAL_UL_DELAY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_AdditionalUlDelay(FpgaVal* buff, FpgaVal value) =0 ;



    /**
     * Read combined register UL_RSSI at 0x78016 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_ulRssi(unsigned chainiq) const =0 ;







    /**
     * Read combined register UL_RSSI at 0x78016 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulRssi(unsigned chainiq) const =0 ;



    /**
     * Read combined register DL_FREQ_OFFSET at 0x78040 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_dlFreqOffset(unsigned chainiq) const =0 ;






    /**
     * Write combined field DL_FREQ_OFFSET at 0x78040 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dlFreqOffset(unsigned chainiq, FpgaVal value) =0 ;






    /**
     * Read combined register DL_FREQ_OFFSET at 0x78040 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlFreqOffset(unsigned chainiq) const =0 ;






    /**
     * Write combined field DL_FREQ_OFFSET at 0x78040 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dlFreqOffset(unsigned chainiq, FpgaVal value) =0 ;


    /**
     * Read combined register UL_FREQ_OFFSET at 0x78046 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_ulFreqOffset(unsigned chainiq) const =0 ;






    /**
     * Write combined field UL_FREQ_OFFSET at 0x78046 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulFreqOffset(unsigned chainiq, FpgaVal value) =0 ;






    /**
     * Read combined register UL_FREQ_OFFSET at 0x78046 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulFreqOffset(unsigned chainiq) const =0 ;






    /**
     * Write combined field UL_FREQ_OFFSET at 0x78046 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulFreqOffset(unsigned chainiq, FpgaVal value) =0 ;


    /**
     * Read combined register UL_ADCRSSI at 0x78050 bits [26..0]
     * \return field value
     */
    virtual const FpgaVal read_ulAdcrssi(unsigned chainiq) const =0 ;







    /**
     * Read combined register UL_ADCRSSI at 0x78050 bits [26..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulAdcrssi(unsigned chainiq) const =0 ;



    /**
     * Read combined register UL_WEIGHT_CHBW at 0x78060 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_ulWeightChbw(unsigned chainiq) const =0 ;






    /**
     * Write combined field UL_WEIGHT_CHBW at 0x78060 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulWeightChbw(unsigned chainiq, FpgaVal value) =0 ;






    /**
     * Read combined register UL_WEIGHT_CHBW at 0x78060 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulWeightChbw(unsigned chainiq) const =0 ;






    /**
     * Write combined field UL_WEIGHT_CHBW at 0x78060 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulWeightChbw(unsigned chainiq, FpgaVal value) =0 ;



};


} /* namespace Mplane */

#endif /* _ICHAIN_REGS_DEF_H_ */
