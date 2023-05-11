#ifndef _IWCDMA_REGS_DEF_H_
#define _IWCDMA_REGS_DEF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaWcdmaRegs.h
 * \brief     FPGA Wcdma registers virtual interface
 *
 *
 * \details   This file defines the FPGA Wcdma registers.
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

class IFpgaWcdmaRegs : public virtual IFpgaRegs
{
public:
	IFpgaWcdmaRegs() {}
	virtual ~IFpgaWcdmaRegs(void) {} ;

    /** \brief  Does FPGA have a WCDMA registers block
     *
     *  \return true if the FPGA instance does actually support a Wcdma registers block
     */
    virtual bool hasWcdmaRegisters(void) =0 ;

    /*! \brief  Get base address
     *
     *  Get the base address of the Wcdma registers (if supported)
     *
     *  \return base address of Wcdma registers; 0 if not supported
     */
    virtual UINT32 getWcdmaBlockAddr(void) =0 ;

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
     * Read field RP3_ADDRESS at 0x40400 bits [12..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_rp3Address(unsigned fibre) const =0 ;

    /**
     * Write field RP3_ADDRESS at 0x40400 bits [12..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rp3Address(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field RP3_ADDRESS at 0x40400 bits [12..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rp3Address(unsigned fibre) const =0 ;

    /**
     * Write field RP3_ADDRESS at 0x40400 bits [12..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rp3Address(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field RP3_ADDRESS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rp3Address(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BLOCK_ENABLE at 0x40400 bits [15]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_blockEnable(unsigned fibre) const =0 ;

    /**
     * Write field BLOCK_ENABLE at 0x40400 bits [15]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_blockEnable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field BLOCK_ENABLE at 0x40400 bits [15]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_blockEnable(unsigned fibre) const =0 ;

    /**
     * Write field BLOCK_ENABLE at 0x40400 bits [15]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_blockEnable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field BLOCK_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_blockEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX0_DL_IQ_STREAM at 0x40402 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index0DlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX0_DL_IQ_STREAM at 0x40402 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index0DlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX0_DL_IQ_STREAM at 0x40402 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index0DlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX0_DL_IQ_STREAM at 0x40402 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index0DlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX0_DL_IQ_STREAM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index0DlIqStream(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX0_ENABLE at 0x40402 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index0Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX0_ENABLE at 0x40402 bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index0Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX0_ENABLE at 0x40402 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index0Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX0_ENABLE at 0x40402 bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index0Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX0_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index0Enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX1_DL_IQ_STREAM at 0x40404 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index1DlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX1_DL_IQ_STREAM at 0x40404 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index1DlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX1_DL_IQ_STREAM at 0x40404 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index1DlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX1_DL_IQ_STREAM at 0x40404 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index1DlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX1_DL_IQ_STREAM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index1DlIqStream(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX1_ENABLE at 0x40404 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index1Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX1_ENABLE at 0x40404 bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index1Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX1_ENABLE at 0x40404 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index1Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX1_ENABLE at 0x40404 bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index1Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX1_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index1Enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX2_UL_IQ_STREAM at 0x40406 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index2UlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX2_UL_IQ_STREAM at 0x40406 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index2UlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX2_UL_IQ_STREAM at 0x40406 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index2UlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX2_UL_IQ_STREAM at 0x40406 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index2UlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX2_UL_IQ_STREAM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index2UlIqStream(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX2_ENABLE at 0x40406 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index2Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX2_ENABLE at 0x40406 bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index2Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX2_ENABLE at 0x40406 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index2Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX2_ENABLE at 0x40406 bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index2Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX2_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index2Enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX3_UL_IQ_STREAM at 0x40408 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index3UlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX3_UL_IQ_STREAM at 0x40408 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index3UlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX3_UL_IQ_STREAM at 0x40408 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index3UlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX3_UL_IQ_STREAM at 0x40408 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index3UlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX3_UL_IQ_STREAM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index3UlIqStream(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX3_ENABLE at 0x40408 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index3Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX3_ENABLE at 0x40408 bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index3Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX3_ENABLE at 0x40408 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index3Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX3_ENABLE at 0x40408 bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index3Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX3_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index3Enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX4_UL_IQ_STREAM at 0x4040a bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index4UlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX4_UL_IQ_STREAM at 0x4040a bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index4UlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX4_UL_IQ_STREAM at 0x4040a bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index4UlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX4_UL_IQ_STREAM at 0x4040a bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index4UlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX4_UL_IQ_STREAM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index4UlIqStream(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX4_ENABLE at 0x4040a bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index4Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX4_ENABLE at 0x4040a bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index4Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX4_ENABLE at 0x4040a bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index4Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX4_ENABLE at 0x4040a bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index4Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX4_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index4Enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX5_UL_IQ_STREAM at 0x4040c bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index5UlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX5_UL_IQ_STREAM at 0x4040c bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index5UlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX5_UL_IQ_STREAM at 0x4040c bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index5UlIqStream(unsigned fibre) const =0 ;

    /**
     * Write field INDEX5_UL_IQ_STREAM at 0x4040c bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index5UlIqStream(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX5_UL_IQ_STREAM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index5UlIqStream(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field INDEX5_ENABLE at 0x4040c bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_index5Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX5_ENABLE at 0x4040c bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_index5Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field INDEX5_ENABLE at 0x4040c bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_index5Enable(unsigned fibre) const =0 ;

    /**
     * Write field INDEX5_ENABLE at 0x4040c bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_index5Enable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field INDEX5_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_index5Enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RULES1 at 0x40800 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txRules1(unsigned fibre) const =0 ;

    /**
     * Write field TX_RULES1 at 0x40800 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txRules1(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field TX_RULES1 at 0x40800 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txRules1(unsigned fibre) const =0 ;

    /**
     * Write field TX_RULES1 at 0x40800 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txRules1(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field TX_RULES1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txRules1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RULES2 at 0x40802 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txRules2(unsigned fibre) const =0 ;

    /**
     * Write field TX_RULES2 at 0x40802 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txRules2(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field TX_RULES2 at 0x40802 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txRules2(unsigned fibre) const =0 ;

    /**
     * Write field TX_RULES2 at 0x40802 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txRules2(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field TX_RULES2 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txRules2(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RULES3 at 0x40804 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txRules3(unsigned fibre) const =0 ;

    /**
     * Write field TX_RULES3 at 0x40804 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txRules3(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field TX_RULES3 at 0x40804 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txRules3(unsigned fibre) const =0 ;

    /**
     * Write field TX_RULES3 at 0x40804 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txRules3(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field TX_RULES3 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txRules3(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RULES4 at 0x40806 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_txRules4(unsigned fibre) const =0 ;

    /**
     * Write field TX_RULES4 at 0x40806 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txRules4(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field TX_RULES4 at 0x40806 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txRules4(unsigned fibre) const =0 ;

    /**
     * Write field TX_RULES4 at 0x40806 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txRules4(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field TX_RULES4 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txRules4(FpgaVal* buff, FpgaVal value) =0 ;




};


} /* namespace Mplane */

#endif /* _IWCDMA_REGS_DEF_H_ */
