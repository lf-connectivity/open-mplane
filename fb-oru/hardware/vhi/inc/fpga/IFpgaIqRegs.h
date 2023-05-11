#ifndef _IIQ_REGS_DEF_H_
#define _IIQ_REGS_DEF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaIqRegs.h
 * \brief     FPGA Iq registers virtual interface
 *
 *
 * \details   This file defines the FPGA Iq registers.
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

class IFpgaIqRegs : public virtual IFpgaRegs
{
public:
	IFpgaIqRegs() {}
	virtual ~IFpgaIqRegs(void) {} ;

    /** \brief  Does FPGA have a IQ registers block
     *
     *  \return true if the FPGA instance does actually support a Iq registers block
     */
    virtual bool hasIqRegisters(void) =0 ;

    /*! \brief  Get base address
     *
     *  Get the base address of the Iq registers (if supported)
     *
     *  \return base address of Iq registers; 0 if not supported
     */
    virtual UINT32 getIqBlockAddr(void) =0 ;

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
     * Read field FIBRE_PATH at 0x70000 bits [3..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_fibrePath(unsigned fibreiq) const =0 ;


    /**
     * Read field FIBRE_PATH at 0x70000 bits [3..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fibrePath(unsigned fibreiq) const =0 ;




    /**
     * Read field FIBRE_IQ_TYPE at 0x70000 bits [7..4]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_fibreIqType(unsigned fibreiq) const =0 ;


    /**
     * Read field FIBRE_IQ_TYPE at 0x70000 bits [7..4]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fibreIqType(unsigned fibreiq) const =0 ;




    /**
     * Read field FIBRE_IQ_STREAM at 0x70002 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_fibreIqStream(unsigned fibreiq) const =0 ;


    /**
     * Read field FIBRE_IQ_STREAM at 0x70002 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fibreIqStream(unsigned fibreiq) const =0 ;




    /**
     * Read field RF_CHAIN_CONNECTION at 0x70004 bits [4..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_rfChainConnection(unsigned fibreiq) const =0 ;

    /**
     * Write field RF_CHAIN_CONNECTION at 0x70004 bits [4..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rfChainConnection(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field RF_CHAIN_CONNECTION at 0x70004 bits [4..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rfChainConnection(unsigned fibreiq) const =0 ;

    /**
     * Write field RF_CHAIN_CONNECTION at 0x70004 bits [4..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rfChainConnection(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field RF_CHAIN_CONNECTION in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rfChainConnection(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SNDL_ENABLE at 0x70008 bits [15]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_sndlEnable(unsigned fibreiq) const =0 ;

    /**
     * Write field SNDL_ENABLE at 0x70008 bits [15]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sndlEnable(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field SNDL_ENABLE at 0x70008 bits [15]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sndlEnable(unsigned fibreiq) const =0 ;

    /**
     * Write field SNDL_ENABLE at 0x70008 bits [15]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sndlEnable(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field SNDL_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sndlEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SNUL_ENABLE at 0x7000a bits [15]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_snulEnable(unsigned fibreiq) const =0 ;

    /**
     * Write field SNUL_ENABLE at 0x7000a bits [15]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_snulEnable(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field SNUL_ENABLE at 0x7000a bits [15]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_snulEnable(unsigned fibreiq) const =0 ;

    /**
     * Write field SNUL_ENABLE at 0x7000a bits [15]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_snulEnable(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field SNUL_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_snulEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FIBRE_IQ_STREAM_LOOPBACK at 0x70028 bits [0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_fibreIqStreamLoopback(unsigned fibreiq) const =0 ;

    /**
     * Write field FIBRE_IQ_STREAM_LOOPBACK at 0x70028 bits [0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fibreIqStreamLoopback(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field FIBRE_IQ_STREAM_LOOPBACK at 0x70028 bits [0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fibreIqStreamLoopback(unsigned fibreiq) const =0 ;

    /**
     * Write field FIBRE_IQ_STREAM_LOOPBACK at 0x70028 bits [0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fibreIqStreamLoopback(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field FIBRE_IQ_STREAM_LOOPBACK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fibreIqStreamLoopback(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field START_CONTAINER at 0x70080 bits [7..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_startContainer(unsigned fibreiq) const =0 ;

    /**
     * Write field START_CONTAINER at 0x70080 bits [7..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_startContainer(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field START_CONTAINER at 0x70080 bits [7..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_startContainer(unsigned fibreiq) const =0 ;

    /**
     * Write field START_CONTAINER at 0x70080 bits [7..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_startContainer(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field START_CONTAINER in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_startContainer(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field END_CONTAINER at 0x70080 bits [15..8]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_endContainer(unsigned fibreiq) const =0 ;

    /**
     * Write field END_CONTAINER at 0x70080 bits [15..8]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_endContainer(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field END_CONTAINER at 0x70080 bits [15..8]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_endContainer(unsigned fibreiq) const =0 ;

    /**
     * Write field END_CONTAINER at 0x70080 bits [15..8]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_endContainer(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field END_CONTAINER in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_endContainer(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_DELAY at 0x70082 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_ulDelay(unsigned fibreiq) const =0 ;

    /**
     * Write field UL_DELAY at 0x70082 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ulDelay(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field UL_DELAY at 0x70082 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulDelay(unsigned fibreiq) const =0 ;

    /**
     * Write field UL_DELAY at 0x70082 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ulDelay(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field UL_DELAY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ulDelay(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DL_DELAY at 0x70084 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_dlDelay(unsigned fibreiq) const =0 ;

    /**
     * Write field DL_DELAY at 0x70084 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dlDelay(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field DL_DELAY at 0x70084 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlDelay(unsigned fibreiq) const =0 ;

    /**
     * Write field DL_DELAY at 0x70084 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dlDelay(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field DL_DELAY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dlDelay(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CPRI_FIBRE at 0x70086 bits [1..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_cpriFibre(unsigned fibreiq) const =0 ;

    /**
     * Write field CPRI_FIBRE at 0x70086 bits [1..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cpriFibre(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field CPRI_FIBRE at 0x70086 bits [1..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cpriFibre(unsigned fibreiq) const =0 ;

    /**
     * Write field CPRI_FIBRE at 0x70086 bits [1..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cpriFibre(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field CPRI_FIBRE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cpriFibre(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UL_DELAY_ACTUAL at 0x70088 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_ulDelayActual(unsigned fibreiq) const =0 ;


    /**
     * Read field UL_DELAY_ACTUAL at 0x70088 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulDelayActual(unsigned fibreiq) const =0 ;






};


} /* namespace Mplane */

#endif /* _IIQ_REGS_DEF_H_ */
