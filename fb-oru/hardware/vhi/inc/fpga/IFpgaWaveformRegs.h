#ifndef _IWAVEFORM_REGS_DEF_H_
#define _IWAVEFORM_REGS_DEF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaWaveformRegs.h
 * \brief     FPGA Waveform registers virtual interface
 *
 *
 * \details   This file defines the FPGA Waveform registers.
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

class IFpgaWaveformRegs : public virtual IFpgaRegs
{
public:
	IFpgaWaveformRegs() {}
	virtual ~IFpgaWaveformRegs(void) {} ;

    /** \brief  Does FPGA have a WAVEFORM registers block
     *
     *  \return true if the FPGA instance does actually support a Waveform registers block
     */
    virtual bool hasWaveformRegisters(void) =0 ;

    /*! \brief  Get base address
     *
     *  Get the base address of the Waveform registers (if supported)
     *
     *  \return base address of Waveform registers; 0 if not supported
     */
    virtual UINT32 getWaveformBlockAddr(void) =0 ;

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
     * Read field WAVEFORM_MEM_START_ADDR_LO at 0x580 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformMemStartAddrLo() const =0 ;

    /**
     * Write field WAVEFORM_MEM_START_ADDR_LO at 0x580 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformMemStartAddrLo(FpgaVal value) =0 ;

    /**
     * Read field WAVEFORM_MEM_START_ADDR_LO at 0x580 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformMemStartAddrLo() const =0 ;

    /**
     * Write field WAVEFORM_MEM_START_ADDR_LO at 0x580 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformMemStartAddrLo(FpgaVal value) =0 ;

    /**
     * Write field WAVEFORM_MEM_START_ADDR_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveformMemStartAddrLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVEFORM_MEM_START_ADDR_HI at 0x582 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformMemStartAddrHi() const =0 ;

    /**
     * Write field WAVEFORM_MEM_START_ADDR_HI at 0x582 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformMemStartAddrHi(FpgaVal value) =0 ;

    /**
     * Read field WAVEFORM_MEM_START_ADDR_HI at 0x582 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformMemStartAddrHi() const =0 ;

    /**
     * Write field WAVEFORM_MEM_START_ADDR_HI at 0x582 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformMemStartAddrHi(FpgaVal value) =0 ;

    /**
     * Write field WAVEFORM_MEM_START_ADDR_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveformMemStartAddrHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVEFORM_MEM_END_ADDR_LO at 0x584 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformMemEndAddrLo() const =0 ;

    /**
     * Write field WAVEFORM_MEM_END_ADDR_LO at 0x584 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformMemEndAddrLo(FpgaVal value) =0 ;

    /**
     * Read field WAVEFORM_MEM_END_ADDR_LO at 0x584 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformMemEndAddrLo() const =0 ;

    /**
     * Write field WAVEFORM_MEM_END_ADDR_LO at 0x584 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformMemEndAddrLo(FpgaVal value) =0 ;

    /**
     * Write field WAVEFORM_MEM_END_ADDR_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveformMemEndAddrLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVEFORM_MEM_END_ADDR_HI at 0x586 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformMemEndAddrHi() const =0 ;

    /**
     * Write field WAVEFORM_MEM_END_ADDR_HI at 0x586 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformMemEndAddrHi(FpgaVal value) =0 ;

    /**
     * Read field WAVEFORM_MEM_END_ADDR_HI at 0x586 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformMemEndAddrHi() const =0 ;

    /**
     * Write field WAVEFORM_MEM_END_ADDR_HI at 0x586 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformMemEndAddrHi(FpgaVal value) =0 ;

    /**
     * Write field WAVEFORM_MEM_END_ADDR_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveformMemEndAddrHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVEFORM_READ_LENGTH at 0x588 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformReadLength() const =0 ;

    /**
     * Write field WAVEFORM_READ_LENGTH at 0x588 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformReadLength(FpgaVal value) =0 ;

    /**
     * Read field WAVEFORM_READ_LENGTH at 0x588 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformReadLength() const =0 ;

    /**
     * Write field WAVEFORM_READ_LENGTH at 0x588 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformReadLength(FpgaVal value) =0 ;

    /**
     * Write field WAVEFORM_READ_LENGTH in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveformReadLength(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVEFORM_WRITE_ENABLE at 0x58a bits [0]
     * \return field value
     */
    virtual const FpgaVal read_waveformWriteEnable() const =0 ;

    /**
     * Write field WAVEFORM_WRITE_ENABLE at 0x58a bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformWriteEnable(FpgaVal value) =0 ;

    /**
     * Read field WAVEFORM_WRITE_ENABLE at 0x58a bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformWriteEnable() const =0 ;

    /**
     * Write field WAVEFORM_WRITE_ENABLE at 0x58a bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformWriteEnable(FpgaVal value) =0 ;

    /**
     * Write field WAVEFORM_WRITE_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveformWriteEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVEFORM_WRITE_FIFO_FULL at 0x58a bits [1]
     * \return field value
     */
    virtual const FpgaVal read_waveformWriteFifoFull() const =0 ;


    /**
     * Read field WAVEFORM_WRITE_FIFO_FULL at 0x58a bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformWriteFifoFull() const =0 ;




    /**
     * Read field WAVEFORM_WRITE_FIFO_EMPTY at 0x58a bits [2]
     * \return field value
     */
    virtual const FpgaVal read_waveformWriteFifoEmpty() const =0 ;


    /**
     * Read field WAVEFORM_WRITE_FIFO_EMPTY at 0x58a bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformWriteFifoEmpty() const =0 ;




    /**
     * Read field WAVEFORM_READ_ENABLE at 0x58a bits [4]
     * \return field value
     */
    virtual const FpgaVal read_waveformReadEnable() const =0 ;

    /**
     * Write field WAVEFORM_READ_ENABLE at 0x58a bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformReadEnable(FpgaVal value) =0 ;

    /**
     * Read field WAVEFORM_READ_ENABLE at 0x58a bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformReadEnable() const =0 ;

    /**
     * Write field WAVEFORM_READ_ENABLE at 0x58a bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformReadEnable(FpgaVal value) =0 ;

    /**
     * Write field WAVEFORM_READ_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveformReadEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVEFORM_READ_FIFO_FULL at 0x58a bits [5]
     * \return field value
     */
    virtual const FpgaVal read_waveformReadFifoFull() const =0 ;


    /**
     * Read field WAVEFORM_READ_FIFO_FULL at 0x58a bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformReadFifoFull() const =0 ;




    /**
     * Read field WAVEFORM_READ_FIFO_EMPTY at 0x58a bits [6]
     * \return field value
     */
    virtual const FpgaVal read_waveformReadFifoEmpty() const =0 ;


    /**
     * Read field WAVEFORM_READ_FIFO_EMPTY at 0x58a bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformReadFifoEmpty() const =0 ;




    /**
     * Read field WAVEFORM_WRITE_LO at 0x590 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformWriteLo() const =0 ;

    /**
     * Write field WAVEFORM_WRITE_LO at 0x590 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformWriteLo(FpgaVal value) =0 ;

    /**
     * Read field WAVEFORM_WRITE_LO at 0x590 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformWriteLo() const =0 ;

    /**
     * Write field WAVEFORM_WRITE_LO at 0x590 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformWriteLo(FpgaVal value) =0 ;

    /**
     * Write field WAVEFORM_WRITE_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveformWriteLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVEFORM_WRITE_HI at 0x592 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformWriteHi() const =0 ;

    /**
     * Write field WAVEFORM_WRITE_HI at 0x592 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformWriteHi(FpgaVal value) =0 ;

    /**
     * Read field WAVEFORM_WRITE_HI at 0x592 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformWriteHi() const =0 ;

    /**
     * Write field WAVEFORM_WRITE_HI at 0x592 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformWriteHi(FpgaVal value) =0 ;

    /**
     * Write field WAVEFORM_WRITE_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveformWriteHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVEFORM_READ_LO at 0x594 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformReadLo() const =0 ;


    /**
     * Read field WAVEFORM_READ_LO at 0x594 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformReadLo() const =0 ;




    /**
     * Read field WAVEFORM_READ_HI at 0x596 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformReadHi() const =0 ;


    /**
     * Read field WAVEFORM_READ_HI at 0x596 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformReadHi() const =0 ;




    /**
     * Read field MASTER_PLAYBACK_ENABLE at 0x598 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_masterPlaybackEnable() const =0 ;

    /**
     * Write field MASTER_PLAYBACK_ENABLE at 0x598 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_masterPlaybackEnable(FpgaVal value) =0 ;

    /**
     * Read field MASTER_PLAYBACK_ENABLE at 0x598 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_masterPlaybackEnable() const =0 ;

    /**
     * Write field MASTER_PLAYBACK_ENABLE at 0x598 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_masterPlaybackEnable(FpgaVal value) =0 ;

    /**
     * Write field MASTER_PLAYBACK_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_masterPlaybackEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MASTER_CAPTURE_ENABLE at 0x598 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_masterCaptureEnable() const =0 ;

    /**
     * Write field MASTER_CAPTURE_ENABLE at 0x598 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_masterCaptureEnable(FpgaVal value) =0 ;

    /**
     * Read field MASTER_CAPTURE_ENABLE at 0x598 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_masterCaptureEnable() const =0 ;

    /**
     * Write field MASTER_CAPTURE_ENABLE at 0x598 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_masterCaptureEnable(FpgaVal value) =0 ;

    /**
     * Write field MASTER_CAPTURE_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_masterCaptureEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_ENABLE at 0x5a2 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureEnable() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_ENABLE at 0x5a2 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureEnable(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_ENABLE at 0x5a2 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureEnable() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_ENABLE at 0x5a2 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureEnable(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_DONE at 0x5a2 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureDone() const =0 ;


    /**
     * Read field DPDADC_CAPTURE_DONE at 0x5a2 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureDone() const =0 ;




    /**
     * Read field DPDADC_CAPTURE_READ_RESET at 0x5a2 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureReadReset() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_READ_RESET at 0x5a2 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureReadReset(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_READ_RESET at 0x5a2 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureReadReset() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_READ_RESET at 0x5a2 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureReadReset(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_READ_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureReadReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_STREAM_SINGLE at 0x5a2 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcStreamSingle() const =0 ;

    /**
     * Write field DPDADC_STREAM_SINGLE at 0x5a2 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcStreamSingle(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_STREAM_SINGLE at 0x5a2 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcStreamSingle() const =0 ;

    /**
     * Write field DPDADC_STREAM_SINGLE at 0x5a2 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcStreamSingle(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_STREAM_SINGLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcStreamSingle(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_STREAM_ENABLE at 0x5a2 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureStreamEnable() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_STREAM_ENABLE at 0x5a2 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureStreamEnable(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_STREAM_ENABLE at 0x5a2 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureStreamEnable() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_STREAM_ENABLE at 0x5a2 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureStreamEnable(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_STREAM_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureStreamEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_DATA at 0x5a4 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureData() const =0 ;


    /**
     * Read field DPDADC_CAPTURE_DATA at 0x5a4 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureData() const =0 ;




    /**
     * Read field DPDADC_CAPTURE_TRIGGER_LO at 0x5a6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureTriggerLo() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_TRIGGER_LO at 0x5a6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureTriggerLo(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_TRIGGER_LO at 0x5a6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureTriggerLo() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_TRIGGER_LO at 0x5a6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureTriggerLo(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_TRIGGER_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureTriggerLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_TRIGGER_HI at 0x5a8 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureTriggerHi() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_TRIGGER_HI at 0x5a8 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureTriggerHi(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_TRIGGER_HI at 0x5a8 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureTriggerHi() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_TRIGGER_HI at 0x5a8 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureTriggerHi(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_TRIGGER_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureTriggerHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_DEPTH at 0x5aa bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureDepth() const =0 ;


    /**
     * Read field DPDADC_CAPTURE_DEPTH at 0x5aa bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureDepth() const =0 ;




    /**
     * Read field DPDADC_CAPTURE1_KDEPTH at 0x5aa bits [15..8]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCapture1KDepth() const =0 ;


    /**
     * Read field DPDADC_CAPTURE1_KDEPTH at 0x5aa bits [15..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCapture1KDepth() const =0 ;




    /**
     * Read field DPDADC_CAPTURE_AVE_DEPTH_LO at 0x5b0 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureAveDepthLo() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_DEPTH_LO at 0x5b0 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureAveDepthLo(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_AVE_DEPTH_LO at 0x5b0 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureAveDepthLo() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_DEPTH_LO at 0x5b0 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureAveDepthLo(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_DEPTH_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureAveDepthLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_AVE_DEPTH_HI at 0x5b2 bits [1..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureAveDepthHi() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_DEPTH_HI at 0x5b2 bits [1..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureAveDepthHi(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_AVE_DEPTH_HI at 0x5b2 bits [1..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureAveDepthHi() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_DEPTH_HI at 0x5b2 bits [1..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureAveDepthHi(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_DEPTH_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureAveDepthHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_AVE_NUM_CAPT at 0x5b4 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureAveNumCapt() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_NUM_CAPT at 0x5b4 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureAveNumCapt(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_AVE_NUM_CAPT at 0x5b4 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureAveNumCapt() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_NUM_CAPT at 0x5b4 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureAveNumCapt(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_NUM_CAPT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureAveNumCapt(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_THROTTLE at 0x5b4 bits [11..8]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureThrottle() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_THROTTLE at 0x5b4 bits [11..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureThrottle(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_THROTTLE at 0x5b4 bits [11..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureThrottle() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_THROTTLE at 0x5b4 bits [11..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureThrottle(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_THROTTLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureThrottle(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_DECIMATION at 0x5b4 bits [15..12]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureDecimation() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_DECIMATION at 0x5b4 bits [15..12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureDecimation(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_DECIMATION at 0x5b4 bits [15..12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureDecimation() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_DECIMATION at 0x5b4 bits [15..12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureDecimation(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_DECIMATION in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureDecimation(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH_LO at 0x5b6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureAveTriggerWidthLo() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH_LO at 0x5b6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureAveTriggerWidthLo(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH_LO at 0x5b6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureAveTriggerWidthLo() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH_LO at 0x5b6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureAveTriggerWidthLo(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureAveTriggerWidthLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH_HI at 0x5b8 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureAveTriggerWidthHi() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH_HI at 0x5b8 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureAveTriggerWidthHi(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH_HI at 0x5b8 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureAveTriggerWidthHi() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH_HI at 0x5b8 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureAveTriggerWidthHi(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureAveTriggerWidthHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_AVE_TRIGGER_LO at 0x5ba bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureAveTriggerLo() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_LO at 0x5ba bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureAveTriggerLo(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_AVE_TRIGGER_LO at 0x5ba bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureAveTriggerLo() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_LO at 0x5ba bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureAveTriggerLo(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureAveTriggerLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPDADC_CAPTURE_AVE_TRIGGER_HI at 0x5bc bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureAveTriggerHi() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_HI at 0x5bc bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureAveTriggerHi(FpgaVal value) =0 ;

    /**
     * Read field DPDADC_CAPTURE_AVE_TRIGGER_HI at 0x5bc bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureAveTriggerHi() const =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_HI at 0x5bc bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureAveTriggerHi(FpgaVal value) =0 ;

    /**
     * Write field DPDADC_CAPTURE_AVE_TRIGGER_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdadcCaptureAveTriggerHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVEFORM_MODULE_TYPE at 0x60000 bits [7..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveformModuleType(unsigned waveform) const =0 ;


    /**
     * Read field WAVEFORM_MODULE_TYPE at 0x60000 bits [7..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformModuleType(unsigned waveform) const =0 ;




    /**
     * Read field WAVEFORM_MODULE_PRESENT at 0x60000 bits [15]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveformModulePresent(unsigned waveform) const =0 ;


    /**
     * Read field WAVEFORM_MODULE_PRESENT at 0x60000 bits [15]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformModulePresent(unsigned waveform) const =0 ;




    /**
     * Read field WAVE_START_ADDR_LO at 0x60002 bits [15..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveStartAddrLo(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_START_ADDR_LO at 0x60002 bits [15..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveStartAddrLo(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_START_ADDR_LO at 0x60002 bits [15..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveStartAddrLo(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_START_ADDR_LO at 0x60002 bits [15..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveStartAddrLo(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_START_ADDR_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveStartAddrLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_START_ADDR_HI at 0x60004 bits [9..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveStartAddrHi(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_START_ADDR_HI at 0x60004 bits [9..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveStartAddrHi(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_START_ADDR_HI at 0x60004 bits [9..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveStartAddrHi(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_START_ADDR_HI at 0x60004 bits [9..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveStartAddrHi(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_START_ADDR_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveStartAddrHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_END_ADDR_LO at 0x60006 bits [15..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveEndAddrLo(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_END_ADDR_LO at 0x60006 bits [15..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveEndAddrLo(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_END_ADDR_LO at 0x60006 bits [15..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveEndAddrLo(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_END_ADDR_LO at 0x60006 bits [15..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveEndAddrLo(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_END_ADDR_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveEndAddrLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_END_ADDR_HI at 0x60008 bits [9..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveEndAddrHi(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_END_ADDR_HI at 0x60008 bits [9..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveEndAddrHi(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_END_ADDR_HI at 0x60008 bits [9..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveEndAddrHi(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_END_ADDR_HI at 0x60008 bits [9..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveEndAddrHi(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_END_ADDR_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveEndAddrHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_PLAYBACK_ENABLE at 0x6000a bits [0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_wavePlaybackEnable(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_PLAYBACK_ENABLE at 0x6000a bits [0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_wavePlaybackEnable(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_PLAYBACK_ENABLE at 0x6000a bits [0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wavePlaybackEnable(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_PLAYBACK_ENABLE at 0x6000a bits [0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_wavePlaybackEnable(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_PLAYBACK_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_wavePlaybackEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_CAPTURE_ENABLE at 0x6000a bits [4]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveCaptureEnable(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_CAPTURE_ENABLE at 0x6000a bits [4]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveCaptureEnable(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_CAPTURE_ENABLE at 0x6000a bits [4]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveCaptureEnable(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_CAPTURE_ENABLE at 0x6000a bits [4]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveCaptureEnable(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_CAPTURE_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveCaptureEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_CAPTURE_DONE at 0x6000a bits [5]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveCaptureDone(unsigned waveform) const =0 ;


    /**
     * Read field WAVE_CAPTURE_DONE at 0x6000a bits [5]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveCaptureDone(unsigned waveform) const =0 ;




    /**
     * Read field WAVE_START_AIRFRAME_LO at 0x6000c bits [15..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveStartAirframeLo(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_START_AIRFRAME_LO at 0x6000c bits [15..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveStartAirframeLo(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_START_AIRFRAME_LO at 0x6000c bits [15..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveStartAirframeLo(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_START_AIRFRAME_LO at 0x6000c bits [15..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveStartAirframeLo(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_START_AIRFRAME_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveStartAirframeLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_START_AIRFRAME_HI at 0x6000e bits [5..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveStartAirframeHi(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_START_AIRFRAME_HI at 0x6000e bits [5..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveStartAirframeHi(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_START_AIRFRAME_HI at 0x6000e bits [5..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveStartAirframeHi(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_START_AIRFRAME_HI at 0x6000e bits [5..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveStartAirframeHi(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_START_AIRFRAME_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveStartAirframeHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_CAPTURE_LEN_LO at 0x60010 bits [15..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveCaptureLenLo(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_CAPTURE_LEN_LO at 0x60010 bits [15..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveCaptureLenLo(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_CAPTURE_LEN_LO at 0x60010 bits [15..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveCaptureLenLo(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_CAPTURE_LEN_LO at 0x60010 bits [15..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveCaptureLenLo(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_CAPTURE_LEN_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveCaptureLenLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_CAPTURE_LEN_HI at 0x60012 bits [9..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveCaptureLenHi(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_CAPTURE_LEN_HI at 0x60012 bits [9..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveCaptureLenHi(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_CAPTURE_LEN_HI at 0x60012 bits [9..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveCaptureLenHi(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_CAPTURE_LEN_HI at 0x60012 bits [9..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveCaptureLenHi(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_CAPTURE_LEN_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveCaptureLenHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_PLAYBACK_READ_ERROR at 0x60014 bits [0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_wavePlaybackReadError(unsigned waveform) const =0 ;


    /**
     * Read field WAVE_PLAYBACK_READ_ERROR at 0x60014 bits [0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wavePlaybackReadError(unsigned waveform) const =0 ;




    /**
     * Read field WAVE_CAPTURE_WRITE_ERROR at 0x60014 bits [4]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveCaptureWriteError(unsigned waveform) const =0 ;


    /**
     * Read field WAVE_CAPTURE_WRITE_ERROR at 0x60014 bits [4]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveCaptureWriteError(unsigned waveform) const =0 ;




    /**
     * Read field WAVE_SAMPLE_RATE_N at 0x60016 bits [7..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveSampleRateN(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_SAMPLE_RATE_N at 0x60016 bits [7..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveSampleRateN(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_SAMPLE_RATE_N at 0x60016 bits [7..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveSampleRateN(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_SAMPLE_RATE_N at 0x60016 bits [7..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveSampleRateN(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_SAMPLE_RATE_N in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveSampleRateN(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_SAMPLE_RATE_A at 0x60018 bits [7..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveSampleRateA(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_SAMPLE_RATE_A at 0x60018 bits [7..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveSampleRateA(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_SAMPLE_RATE_A at 0x60018 bits [7..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveSampleRateA(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_SAMPLE_RATE_A at 0x60018 bits [7..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveSampleRateA(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_SAMPLE_RATE_A in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveSampleRateA(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_SAMPLE_RATE_B at 0x6001a bits [7..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_waveSampleRateB(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_SAMPLE_RATE_B at 0x6001a bits [7..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveSampleRateB(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_SAMPLE_RATE_B at 0x6001a bits [7..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveSampleRateB(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_SAMPLE_RATE_B at 0x6001a bits [7..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveSampleRateB(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_SAMPLE_RATE_B in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_waveSampleRateB(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WAVE_PLAYBACK_SCALING at 0x6001c bits [15..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_wavePlaybackScaling(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_PLAYBACK_SCALING at 0x6001c bits [15..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_wavePlaybackScaling(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Read field WAVE_PLAYBACK_SCALING at 0x6001c bits [15..0]
     * \param waveform
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wavePlaybackScaling(unsigned waveform) const =0 ;

    /**
     * Write field WAVE_PLAYBACK_SCALING at 0x6001c bits [15..0]
     * \param waveform
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_wavePlaybackScaling(unsigned waveform, FpgaVal value) =0 ;

    /**
     * Write field WAVE_PLAYBACK_SCALING in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_wavePlaybackScaling(FpgaVal* buff, FpgaVal value) =0 ;



    /**
     * Read combined register WAVEFORM_MEM_START_ADDR at 0x580 bits [25..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformMemStartAddr() const =0 ;






    /**
     * Write combined field WAVEFORM_MEM_START_ADDR at 0x580 bits [25..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformMemStartAddr(FpgaVal value) =0 ;






    /**
     * Read combined register WAVEFORM_MEM_START_ADDR at 0x580 bits [25..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformMemStartAddr() const =0 ;






    /**
     * Write combined field WAVEFORM_MEM_START_ADDR at 0x580 bits [25..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformMemStartAddr(FpgaVal value) =0 ;


    /**
     * Read combined register WAVEFORM_MEM_END_ADDR at 0x584 bits [25..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformMemEndAddr() const =0 ;






    /**
     * Write combined field WAVEFORM_MEM_END_ADDR at 0x584 bits [25..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformMemEndAddr(FpgaVal value) =0 ;






    /**
     * Read combined register WAVEFORM_MEM_END_ADDR at 0x584 bits [25..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformMemEndAddr() const =0 ;






    /**
     * Write combined field WAVEFORM_MEM_END_ADDR at 0x584 bits [25..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformMemEndAddr(FpgaVal value) =0 ;


    /**
     * Read combined register WAVEFORM_WRITE at 0x590 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformWrite() const =0 ;






    /**
     * Write combined field WAVEFORM_WRITE at 0x590 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveformWrite(FpgaVal value) =0 ;






    /**
     * Read combined register WAVEFORM_WRITE at 0x590 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformWrite() const =0 ;






    /**
     * Write combined field WAVEFORM_WRITE at 0x590 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveformWrite(FpgaVal value) =0 ;


    /**
     * Read combined register WAVEFORM_READ at 0x594 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_waveformRead() const =0 ;







    /**
     * Read combined register WAVEFORM_READ at 0x594 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveformRead() const =0 ;



    /**
     * Read combined register MASTER_PLAYBACK_CAPTURE_REG at 0x598 bits [4,0]
     * \return field value
     */
    virtual const FpgaVal read_masterPlaybackCaptureReg() const =0 ;






    /**
     * Write combined field MASTER_PLAYBACK_CAPTURE_REG at 0x598 bits [4,0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_masterPlaybackCaptureReg(FpgaVal value) =0 ;






    /**
     * Read combined register MASTER_PLAYBACK_CAPTURE_REG at 0x598 bits [4,0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_masterPlaybackCaptureReg() const =0 ;






    /**
     * Write combined field MASTER_PLAYBACK_CAPTURE_REG at 0x598 bits [4,0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_masterPlaybackCaptureReg(FpgaVal value) =0 ;


    /**
     * Read combined register DPDADC_CAPTURE_TRIGGER at 0x5a6 bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureTrigger() const =0 ;






    /**
     * Write combined field DPDADC_CAPTURE_TRIGGER at 0x5a6 bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureTrigger(FpgaVal value) =0 ;






    /**
     * Read combined register DPDADC_CAPTURE_TRIGGER at 0x5a6 bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureTrigger() const =0 ;






    /**
     * Write combined field DPDADC_CAPTURE_TRIGGER at 0x5a6 bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureTrigger(FpgaVal value) =0 ;


    /**
     * Read combined register DPDADC_CAPTURE_AVE_DEPTH at 0x5b0 bits [17..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureAveDepth() const =0 ;






    /**
     * Write combined field DPDADC_CAPTURE_AVE_DEPTH at 0x5b0 bits [17..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureAveDepth(FpgaVal value) =0 ;






    /**
     * Read combined register DPDADC_CAPTURE_AVE_DEPTH at 0x5b0 bits [17..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureAveDepth() const =0 ;






    /**
     * Write combined field DPDADC_CAPTURE_AVE_DEPTH at 0x5b0 bits [17..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureAveDepth(FpgaVal value) =0 ;


    /**
     * Read combined register DPDADC_CAPTURE_AVE_TRIGGER_WIDTH at 0x5b6 bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureAveTriggerWidth() const =0 ;






    /**
     * Write combined field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH at 0x5b6 bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureAveTriggerWidth(FpgaVal value) =0 ;






    /**
     * Read combined register DPDADC_CAPTURE_AVE_TRIGGER_WIDTH at 0x5b6 bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureAveTriggerWidth() const =0 ;






    /**
     * Write combined field DPDADC_CAPTURE_AVE_TRIGGER_WIDTH at 0x5b6 bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureAveTriggerWidth(FpgaVal value) =0 ;


    /**
     * Read combined register DPDADC_CAPTURE_AVE_TRIGGER at 0x5ba bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_dpdadcCaptureAveTrigger() const =0 ;






    /**
     * Write combined field DPDADC_CAPTURE_AVE_TRIGGER at 0x5ba bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdadcCaptureAveTrigger(FpgaVal value) =0 ;






    /**
     * Read combined register DPDADC_CAPTURE_AVE_TRIGGER at 0x5ba bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdadcCaptureAveTrigger() const =0 ;






    /**
     * Write combined field DPDADC_CAPTURE_AVE_TRIGGER at 0x5ba bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdadcCaptureAveTrigger(FpgaVal value) =0 ;


    /**
     * Read combined register WAVE_START_ADDR at 0x60004 bits [25..0]
     * \return field value
     */
    virtual const FpgaVal read_waveStartAddr(unsigned waveform) const =0 ;






    /**
     * Write combined field WAVE_START_ADDR at 0x60004 bits [25..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveStartAddr(unsigned waveform, FpgaVal value) =0 ;






    /**
     * Read combined register WAVE_START_ADDR at 0x60004 bits [25..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveStartAddr(unsigned waveform) const =0 ;






    /**
     * Write combined field WAVE_START_ADDR at 0x60004 bits [25..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveStartAddr(unsigned waveform, FpgaVal value) =0 ;


    /**
     * Read combined register WAVE_END_ADDR at 0x60008 bits [25..0]
     * \return field value
     */
    virtual const FpgaVal read_waveEndAddr(unsigned waveform) const =0 ;






    /**
     * Write combined field WAVE_END_ADDR at 0x60008 bits [25..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveEndAddr(unsigned waveform, FpgaVal value) =0 ;






    /**
     * Read combined register WAVE_END_ADDR at 0x60008 bits [25..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveEndAddr(unsigned waveform) const =0 ;






    /**
     * Write combined field WAVE_END_ADDR at 0x60008 bits [25..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveEndAddr(unsigned waveform, FpgaVal value) =0 ;


    /**
     * Read combined register WAVE_START_AIRFRAME at 0x6000e bits [21..0]
     * \return field value
     */
    virtual const FpgaVal read_waveStartAirframe(unsigned waveform) const =0 ;






    /**
     * Write combined field WAVE_START_AIRFRAME at 0x6000e bits [21..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveStartAirframe(unsigned waveform, FpgaVal value) =0 ;






    /**
     * Read combined register WAVE_START_AIRFRAME at 0x6000e bits [21..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveStartAirframe(unsigned waveform) const =0 ;






    /**
     * Write combined field WAVE_START_AIRFRAME at 0x6000e bits [21..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveStartAirframe(unsigned waveform, FpgaVal value) =0 ;


    /**
     * Read combined register WAVE_CAPTURE_LEN at 0x60012 bits [25..0]
     * \return field value
     */
    virtual const FpgaVal read_waveCaptureLen(unsigned waveform) const =0 ;






    /**
     * Write combined field WAVE_CAPTURE_LEN at 0x60012 bits [25..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_waveCaptureLen(unsigned waveform, FpgaVal value) =0 ;






    /**
     * Read combined register WAVE_CAPTURE_LEN at 0x60012 bits [25..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_waveCaptureLen(unsigned waveform) const =0 ;






    /**
     * Write combined field WAVE_CAPTURE_LEN at 0x60012 bits [25..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_waveCaptureLen(unsigned waveform, FpgaVal value) =0 ;



};


} /* namespace Mplane */

#endif /* _IWAVEFORM_REGS_DEF_H_ */
