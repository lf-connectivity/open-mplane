#ifndef _IANTENNA_REGS_DEF_H_
#define _IANTENNA_REGS_DEF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaAntennaRegs.h
 * \brief     FPGA Antenna registers virtual interface
 *
 *
 * \details   This file defines the FPGA Antenna registers.
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

class IFpgaAntennaRegs : public virtual IFpgaRegs
{
public:
	IFpgaAntennaRegs() {}
	virtual ~IFpgaAntennaRegs(void) {} ;

    /** \brief  Does FPGA have a ANTENNA registers block
     *
     *  \return true if the FPGA instance does actually support a Antenna registers block
     */
    virtual bool hasAntennaRegisters(void) =0 ;

    /*! \brief  Get base address
     *
     *  Get the base address of the Antenna registers (if supported)
     *
     *  \return base address of Antenna registers; 0 if not supported
     */
    virtual UINT32 getAntennaBlockAddr(void) =0 ;

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
     * Read field SRX_POWER_SEQ at 0x50000 bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerSeq(unsigned antenna) const =0 ;

    /**
     * Write field SRX_POWER_SEQ at 0x50000 bits [7..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srxPowerSeq(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field SRX_POWER_SEQ at 0x50000 bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerSeq(unsigned antenna) const =0 ;

    /**
     * Write field SRX_POWER_SEQ at 0x50000 bits [7..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srxPowerSeq(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field SRX_POWER_SEQ in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srxPowerSeq(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRX_POWER_ATTEN at 0x50002 bits [5..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerAtten(unsigned antenna) const =0 ;

    /**
     * Write field SRX_POWER_ATTEN at 0x50002 bits [5..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srxPowerAtten(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field SRX_POWER_ATTEN at 0x50002 bits [5..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerAtten(unsigned antenna) const =0 ;

    /**
     * Write field SRX_POWER_ATTEN at 0x50002 bits [5..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srxPowerAtten(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field SRX_POWER_ATTEN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srxPowerAtten(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRX_POWER_RSSI_FWD_LO at 0x50004 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerRssiFwdLo(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_RSSI_FWD_LO at 0x50004 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerRssiFwdLo(unsigned antenna) const =0 ;




    /**
     * Read field SRX_POWER_RSSI_FWD_HI at 0x50006 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerRssiFwdHi(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_RSSI_FWD_HI at 0x50006 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerRssiFwdHi(unsigned antenna) const =0 ;




    /**
     * Read field SRX_POWER_RSSI_REV_LO at 0x50008 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerRssiRevLo(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_RSSI_REV_LO at 0x50008 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerRssiRevLo(unsigned antenna) const =0 ;




    /**
     * Read field SRX_POWER_RSSI_REV_HI at 0x5000a bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerRssiRevHi(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_RSSI_REV_HI at 0x5000a bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerRssiRevHi(unsigned antenna) const =0 ;




    /**
     * Read field SRX_POWER_TSSI_FWD at 0x5000c bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerTssiFwd(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_TSSI_FWD at 0x5000c bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerTssiFwd(unsigned antenna) const =0 ;




    /**
     * Read field SRX_POWER_TSSI_REV at 0x5000e bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerTssiRev(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_TSSI_REV at 0x5000e bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerTssiRev(unsigned antenna) const =0 ;




    /**
     * Read field ADC_SCALER at 0x50010 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_adcScaler(unsigned antenna) const =0 ;

    /**
     * Write field ADC_SCALER at 0x50010 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_adcScaler(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field ADC_SCALER at 0x50010 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_adcScaler(unsigned antenna) const =0 ;

    /**
     * Write field ADC_SCALER at 0x50010 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_adcScaler(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field ADC_SCALER in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_adcScaler(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRX_POWER_TSSI_FWD_DECIMAL at 0x50012 bits [5..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerTssiFwdDecimal(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_TSSI_FWD_DECIMAL at 0x50012 bits [5..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerTssiFwdDecimal(unsigned antenna) const =0 ;




    /**
     * Read field SRX_POWER_TSSI_REV_DECIMAL at 0x50014 bits [5..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerTssiRevDecimal(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_TSSI_REV_DECIMAL at 0x50014 bits [5..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerTssiRevDecimal(unsigned antenna) const =0 ;




    /**
     * Read field SRX_POWER_TSSI_FPC_ATTEN_LO at 0x50016 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerTssiFpcAttenLo(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_TSSI_FPC_ATTEN_LO at 0x50016 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerTssiFpcAttenLo(unsigned antenna) const =0 ;




    /**
     * Read field SRX_POWER_TSSI_FPC_ATTEN_HI at 0x50018 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerTssiFpcAttenHi(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_TSSI_FPC_ATTEN_HI at 0x50018 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerTssiFpcAttenHi(unsigned antenna) const =0 ;




    /**
     * Read field SRX_POWER_TSSI_FPC_ATTEN_HI2 at 0x5001a bits [3..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxPowerTssiFpcAttenHi2(unsigned antenna) const =0 ;


    /**
     * Read field SRX_POWER_TSSI_FPC_ATTEN_HI2 at 0x5001a bits [3..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerTssiFpcAttenHi2(unsigned antenna) const =0 ;




    /**
     * Read field CWGEN_NCO_LO at 0x50020 bits [15..0]
     * \param cwgen
     * \return field value
     */
    virtual const FpgaVal read_cwgenNcoLo(unsigned cwgen) const =0 ;

    /**
     * Write field CWGEN_NCO_LO at 0x50020 bits [15..0]
     * \param cwgen
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cwgenNcoLo(unsigned cwgen, FpgaVal value) =0 ;

    /**
     * Read field CWGEN_NCO_LO at 0x50020 bits [15..0]
     * \param cwgen
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cwgenNcoLo(unsigned cwgen) const =0 ;

    /**
     * Write field CWGEN_NCO_LO at 0x50020 bits [15..0]
     * \param cwgen
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cwgenNcoLo(unsigned cwgen, FpgaVal value) =0 ;

    /**
     * Write field CWGEN_NCO_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cwgenNcoLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CWGEN_NCO_HI at 0x50022 bits [15..0]
     * \param cwgen
     * \return field value
     */
    virtual const FpgaVal read_cwgenNcoHi(unsigned cwgen) const =0 ;

    /**
     * Write field CWGEN_NCO_HI at 0x50022 bits [15..0]
     * \param cwgen
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cwgenNcoHi(unsigned cwgen, FpgaVal value) =0 ;

    /**
     * Read field CWGEN_NCO_HI at 0x50022 bits [15..0]
     * \param cwgen
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cwgenNcoHi(unsigned cwgen) const =0 ;

    /**
     * Write field CWGEN_NCO_HI at 0x50022 bits [15..0]
     * \param cwgen
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cwgenNcoHi(unsigned cwgen, FpgaVal value) =0 ;

    /**
     * Write field CWGEN_NCO_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cwgenNcoHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CWGEN_MULTI_I at 0x50024 bits [15..0]
     * \param cwgen
     * \return field value
     */
    virtual const FpgaVal read_cwgenMultiI(unsigned cwgen) const =0 ;

    /**
     * Write field CWGEN_MULTI_I at 0x50024 bits [15..0]
     * \param cwgen
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cwgenMultiI(unsigned cwgen, FpgaVal value) =0 ;

    /**
     * Read field CWGEN_MULTI_I at 0x50024 bits [15..0]
     * \param cwgen
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cwgenMultiI(unsigned cwgen) const =0 ;

    /**
     * Write field CWGEN_MULTI_I at 0x50024 bits [15..0]
     * \param cwgen
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cwgenMultiI(unsigned cwgen, FpgaVal value) =0 ;

    /**
     * Write field CWGEN_MULTI_I in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cwgenMultiI(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CWGEN_MULTI_Q at 0x50026 bits [15..0]
     * \param cwgen
     * \return field value
     */
    virtual const FpgaVal read_cwgenMultiQ(unsigned cwgen) const =0 ;

    /**
     * Write field CWGEN_MULTI_Q at 0x50026 bits [15..0]
     * \param cwgen
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cwgenMultiQ(unsigned cwgen, FpgaVal value) =0 ;

    /**
     * Read field CWGEN_MULTI_Q at 0x50026 bits [15..0]
     * \param cwgen
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cwgenMultiQ(unsigned cwgen) const =0 ;

    /**
     * Write field CWGEN_MULTI_Q at 0x50026 bits [15..0]
     * \param cwgen
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cwgenMultiQ(unsigned cwgen, FpgaVal value) =0 ;

    /**
     * Write field CWGEN_MULTI_Q in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cwgenMultiQ(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CFR_THRESHOLD at 0x50100 bits [15..0]
     * \param antenna
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_cfrThreshold(unsigned antenna, unsigned cfr) const =0 ;

    /**
     * Write field CFR_THRESHOLD at 0x50100 bits [15..0]
     * \param antenna
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrThreshold(unsigned antenna, unsigned cfr, FpgaVal value) =0 ;

    /**
     * Read field CFR_THRESHOLD at 0x50100 bits [15..0]
     * \param antenna
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrThreshold(unsigned antenna, unsigned cfr) const =0 ;

    /**
     * Write field CFR_THRESHOLD at 0x50100 bits [15..0]
     * \param antenna
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrThreshold(unsigned antenna, unsigned cfr, FpgaVal value) =0 ;

    /**
     * Write field CFR_THRESHOLD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cfrThreshold(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CFR_PEAK_DET_WINDOW at 0x50108 bits [9..0]
     * \param antenna
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_cfrPeakDetWindow(unsigned antenna, unsigned cfr) const =0 ;

    /**
     * Write field CFR_PEAK_DET_WINDOW at 0x50108 bits [9..0]
     * \param antenna
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrPeakDetWindow(unsigned antenna, unsigned cfr, FpgaVal value) =0 ;

    /**
     * Read field CFR_PEAK_DET_WINDOW at 0x50108 bits [9..0]
     * \param antenna
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrPeakDetWindow(unsigned antenna, unsigned cfr) const =0 ;

    /**
     * Write field CFR_PEAK_DET_WINDOW at 0x50108 bits [9..0]
     * \param antenna
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrPeakDetWindow(unsigned antenna, unsigned cfr, FpgaVal value) =0 ;

    /**
     * Write field CFR_PEAK_DET_WINDOW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cfrPeakDetWindow(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WCFR_THRESHOLD at 0x50110 bits [15..0]
     * \param antenna
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_wcfrThreshold(unsigned antenna, unsigned cfr) const =0 ;

    /**
     * Write field WCFR_THRESHOLD at 0x50110 bits [15..0]
     * \param antenna
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_wcfrThreshold(unsigned antenna, unsigned cfr, FpgaVal value) =0 ;

    /**
     * Read field WCFR_THRESHOLD at 0x50110 bits [15..0]
     * \param antenna
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wcfrThreshold(unsigned antenna, unsigned cfr) const =0 ;

    /**
     * Write field WCFR_THRESHOLD at 0x50110 bits [15..0]
     * \param antenna
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_wcfrThreshold(unsigned antenna, unsigned cfr, FpgaVal value) =0 ;

    /**
     * Write field WCFR_THRESHOLD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_wcfrThreshold(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CFR_PULSE_LENGTH at 0x50120 bits [10..0]
     * \param antenna
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_cfrPulseLength(unsigned antenna, unsigned cfr) const =0 ;

    /**
     * Write field CFR_PULSE_LENGTH at 0x50120 bits [10..0]
     * \param antenna
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrPulseLength(unsigned antenna, unsigned cfr, FpgaVal value) =0 ;

    /**
     * Read field CFR_PULSE_LENGTH at 0x50120 bits [10..0]
     * \param antenna
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrPulseLength(unsigned antenna, unsigned cfr) const =0 ;

    /**
     * Write field CFR_PULSE_LENGTH at 0x50120 bits [10..0]
     * \param antenna
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrPulseLength(unsigned antenna, unsigned cfr, FpgaVal value) =0 ;

    /**
     * Write field CFR_PULSE_LENGTH in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cfrPulseLength(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CFR_STATUS at 0x50128 bits [1..0]
     * \param antenna
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_cfrStatus(unsigned antenna, unsigned cfr) const =0 ;

    /**
     * Write field CFR_STATUS at 0x50128 bits [1..0]
     * \param antenna
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrStatus(unsigned antenna, unsigned cfr, FpgaVal value) =0 ;

    /**
     * Read field CFR_STATUS at 0x50128 bits [1..0]
     * \param antenna
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrStatus(unsigned antenna, unsigned cfr) const =0 ;

    /**
     * Write field CFR_STATUS at 0x50128 bits [1..0]
     * \param antenna
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrStatus(unsigned antenna, unsigned cfr, FpgaVal value) =0 ;

    /**
     * Write field CFR_STATUS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cfrStatus(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CLIP_LUT_ADDRESS at 0x50130 bits [9..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_clipLutAddress(unsigned antenna) const =0 ;

    /**
     * Write field CLIP_LUT_ADDRESS at 0x50130 bits [9..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_clipLutAddress(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field CLIP_LUT_ADDRESS at 0x50130 bits [9..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_clipLutAddress(unsigned antenna) const =0 ;

    /**
     * Write field CLIP_LUT_ADDRESS at 0x50130 bits [9..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_clipLutAddress(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field CLIP_LUT_ADDRESS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_clipLutAddress(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CLIP_LUT_VALUE at 0x50132 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_clipLutValue(unsigned antenna) const =0 ;

    /**
     * Write field CLIP_LUT_VALUE at 0x50132 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_clipLutValue(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field CLIP_LUT_VALUE at 0x50132 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_clipLutValue(unsigned antenna) const =0 ;

    /**
     * Write field CLIP_LUT_VALUE at 0x50132 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_clipLutValue(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field CLIP_LUT_VALUE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_clipLutValue(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ACL_SLEW_RATE_LIM_ENA at 0x50134 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_aclSlewRateLimEna(unsigned antenna) const =0 ;

    /**
     * Write field ACL_SLEW_RATE_LIM_ENA at 0x50134 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_aclSlewRateLimEna(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field ACL_SLEW_RATE_LIM_ENA at 0x50134 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_aclSlewRateLimEna(unsigned antenna) const =0 ;

    /**
     * Write field ACL_SLEW_RATE_LIM_ENA at 0x50134 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_aclSlewRateLimEna(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field ACL_SLEW_RATE_LIM_ENA in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_aclSlewRateLimEna(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRL_ALARM at 0x50134 bits [15]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srlAlarm(unsigned antenna) const =0 ;

    /**
     * Write field SRL_ALARM at 0x50134 bits [15]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srlAlarm(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field SRL_ALARM at 0x50134 bits [15]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srlAlarm(unsigned antenna) const =0 ;

    /**
     * Write field SRL_ALARM at 0x50134 bits [15]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srlAlarm(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field SRL_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srlAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field POP_THRESHOLD at 0x5016e bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_popThreshold(unsigned antenna) const =0 ;

    /**
     * Write field POP_THRESHOLD at 0x5016e bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_popThreshold(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field POP_THRESHOLD at 0x5016e bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_popThreshold(unsigned antenna) const =0 ;

    /**
     * Write field POP_THRESHOLD at 0x5016e bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_popThreshold(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field POP_THRESHOLD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_popThreshold(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field POP_TRIGGER at 0x50170 bits [9..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_popTrigger(unsigned antenna) const =0 ;

    /**
     * Write field POP_TRIGGER at 0x50170 bits [9..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_popTrigger(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field POP_TRIGGER at 0x50170 bits [9..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_popTrigger(unsigned antenna) const =0 ;

    /**
     * Write field POP_TRIGGER at 0x50170 bits [9..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_popTrigger(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field POP_TRIGGER in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_popTrigger(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field POP_ENABLE at 0x50170 bits [12]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_popEnable(unsigned antenna) const =0 ;

    /**
     * Write field POP_ENABLE at 0x50170 bits [12]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_popEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field POP_ENABLE at 0x50170 bits [12]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_popEnable(unsigned antenna) const =0 ;

    /**
     * Write field POP_ENABLE at 0x50170 bits [12]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_popEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field POP_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_popEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field POP_ALARM at 0x50170 bits [15]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_popAlarm(unsigned antenna) const =0 ;

    /**
     * Write field POP_ALARM at 0x50170 bits [15]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_popAlarm(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field POP_ALARM at 0x50170 bits [15]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_popAlarm(unsigned antenna) const =0 ;

    /**
     * Write field POP_ALARM at 0x50170 bits [15]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_popAlarm(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field POP_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_popAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PA_SYNC at 0x50200 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_paSync(unsigned antenna) const =0 ;

    /**
     * Write field PA_SYNC at 0x50200 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_paSync(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field PA_SYNC at 0x50200 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_paSync(unsigned antenna) const =0 ;

    /**
     * Write field PA_SYNC at 0x50200 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_paSync(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field PA_SYNC in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_paSync(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PA_ENABLE at 0x50200 bits [1]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_paEnable(unsigned antenna) const =0 ;

    /**
     * Write field PA_ENABLE at 0x50200 bits [1]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_paEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field PA_ENABLE at 0x50200 bits [1]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_paEnable(unsigned antenna) const =0 ;

    /**
     * Write field PA_ENABLE at 0x50200 bits [1]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_paEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field PA_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_paEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_ENABLE at 0x50200 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_tx_enable() const =0 ;

    /**
     * Write field TX_ENABLE at 0x50200 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tx_enable(FpgaVal value) =0 ;

    /**
     * Read field TX_ENABLE at 0x50200 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tx_enable() const =0 ;

    /**
     * Write field TX_ENABLE at 0x50200 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tx_enable(FpgaVal value) =0 ;

    /**
     * Write field TX_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tx_enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_ENABLE at 0x50200 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_rx_enable() const =0 ;

    /**
     * Write field RX_ENABLE at 0x50200 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rx_enable(FpgaVal value) =0 ;

    /**
     * Read field RX_ENABLE at 0x50200 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rx_enable() const =0 ;

    /**
     * Write field RX_ENABLE at 0x50200 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rx_enable(FpgaVal value) =0 ;

    /**
     * Write field RX_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rx_enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PA_SPARE1 at 0x50200 bits [4]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_paSpare1(unsigned antenna) const =0 ;

    /**
     * Write field PA_SPARE1 at 0x50200 bits [4]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_paSpare1(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field PA_SPARE1 at 0x50200 bits [4]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_paSpare1(unsigned antenna) const =0 ;

    /**
     * Write field PA_SPARE1 at 0x50200 bits [4]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_paSpare1(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field PA_SPARE1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_paSpare1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PA_SPARE2 at 0x50200 bits [5]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_paSpare2(unsigned antenna) const =0 ;

    /**
     * Write field PA_SPARE2 at 0x50200 bits [5]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_paSpare2(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field PA_SPARE2 at 0x50200 bits [5]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_paSpare2(unsigned antenna) const =0 ;

    /**
     * Write field PA_SPARE2 at 0x50200 bits [5]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_paSpare2(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field PA_SPARE2 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_paSpare2(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PA_TRIP_STATUS at 0x50200 bits [8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_paTripStatus(unsigned antenna) const =0 ;


    /**
     * Read field PA_TRIP_STATUS at 0x50200 bits [8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_paTripStatus(unsigned antenna) const =0 ;




    /**
     * Read field PA_TRIP_RESET at 0x50200 bits [9]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_paTripReset(unsigned antenna) const =0 ;

    /**
     * Write field PA_TRIP_RESET at 0x50200 bits [9]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_paTripReset(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field PA_TRIP_RESET at 0x50200 bits [9]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_paTripReset(unsigned antenna) const =0 ;

    /**
     * Write field PA_TRIP_RESET at 0x50200 bits [9]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_paTripReset(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field PA_TRIP_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_paTripReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LOW_PASS_FILTER at 0x50200 bits [11]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_lowPassFilter(unsigned antenna) const =0 ;

    /**
     * Write field LOW_PASS_FILTER at 0x50200 bits [11]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_lowPassFilter(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field LOW_PASS_FILTER at 0x50200 bits [11]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_lowPassFilter(unsigned antenna) const =0 ;

    /**
     * Write field LOW_PASS_FILTER at 0x50200 bits [11]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_lowPassFilter(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field LOW_PASS_FILTER in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_lowPassFilter(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field VVA_ENABLE at 0x50200 bits [12]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_vvaEnable(unsigned antenna) const =0 ;

    /**
     * Write field VVA_ENABLE at 0x50200 bits [12]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_vvaEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field VVA_ENABLE at 0x50200 bits [12]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vvaEnable(unsigned antenna) const =0 ;

    /**
     * Write field VVA_ENABLE at 0x50200 bits [12]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_vvaEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field VVA_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_vvaEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_QUAD_MOD_ENABLE at 0x50200 bits [13]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txQuadModEnable(unsigned antenna) const =0 ;

    /**
     * Write field TX_QUAD_MOD_ENABLE at 0x50200 bits [13]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txQuadModEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_QUAD_MOD_ENABLE at 0x50200 bits [13]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txQuadModEnable(unsigned antenna) const =0 ;

    /**
     * Write field TX_QUAD_MOD_ENABLE at 0x50200 bits [13]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txQuadModEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_QUAD_MOD_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txQuadModEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FEM_POWER_ENABLE at 0x50200 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_fem_power_enable() const =0 ;

    /**
     * Write field FEM_POWER_ENABLE at 0x50200 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fem_power_enable(FpgaVal value) =0 ;

    /**
     * Read field FEM_POWER_ENABLE at 0x50200 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fem_power_enable() const =0 ;

    /**
     * Write field FEM_POWER_ENABLE at 0x50200 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fem_power_enable(FpgaVal value) =0 ;

    /**
     * Write field FEM_POWER_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fem_power_enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DFEM_LOOPBACK_CONTROL at 0x50202 bits [1..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_dfemLoopbackControl(unsigned antenna) const =0 ;

    /**
     * Write field DFEM_LOOPBACK_CONTROL at 0x50202 bits [1..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dfemLoopbackControl(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field DFEM_LOOPBACK_CONTROL at 0x50202 bits [1..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dfemLoopbackControl(unsigned antenna) const =0 ;

    /**
     * Write field DFEM_LOOPBACK_CONTROL at 0x50202 bits [1..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dfemLoopbackControl(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field DFEM_LOOPBACK_CONTROL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dfemLoopbackControl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_VATTEN_RAW at 0x50204 bits [13..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txVattenRaw(unsigned antenna) const =0 ;

    /**
     * Write field TX_VATTEN_RAW at 0x50204 bits [13..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txVattenRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_VATTEN_RAW at 0x50204 bits [13..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txVattenRaw(unsigned antenna) const =0 ;

    /**
     * Write field TX_VATTEN_RAW at 0x50204 bits [13..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txVattenRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_VATTEN_RAW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txVattenRaw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RFSO_C_ADC_BLOCK_ID at 0x50208 bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_RFSoC_ADC_Block_ID(unsigned antenna) const =0 ;


    /**
     * Read field RFSO_C_ADC_BLOCK_ID at 0x50208 bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_RFSoC_ADC_Block_ID(unsigned antenna) const =0 ;




    /**
     * Read field RFSO_C_ADC_TILE_ID at 0x50208 bits [15..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_RFSoC_ADC_Tile_ID(unsigned antenna) const =0 ;


    /**
     * Read field RFSO_C_ADC_TILE_ID at 0x50208 bits [15..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_RFSoC_ADC_Tile_ID(unsigned antenna) const =0 ;




    /**
     * Read field RFSO_C_DAC_BLOCK_ID at 0x5020a bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_RFSoC_DAC_Block_ID(unsigned antenna) const =0 ;


    /**
     * Read field RFSO_C_DAC_BLOCK_ID at 0x5020a bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_RFSoC_DAC_Block_ID(unsigned antenna) const =0 ;




    /**
     * Read field RFSO_C_DAC_TILE_ID at 0x5020a bits [15..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_RFSoC_DAC_Tile_ID(unsigned antenna) const =0 ;


    /**
     * Read field RFSO_C_DAC_TILE_ID at 0x5020a bits [15..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_RFSoC_DAC_Tile_ID(unsigned antenna) const =0 ;




    /**
     * Read field DOWNLINK_POWER_RESULT at 0x50210 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_downlinkPowerResult(unsigned antenna) const =0 ;


    /**
     * Read field DOWNLINK_POWER_RESULT at 0x50210 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_downlinkPowerResult(unsigned antenna) const =0 ;




    /**
     * Read field DIGITAL_IQ at 0x50212 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_digitalIq(unsigned antenna) const =0 ;


    /**
     * Read field DIGITAL_IQ at 0x50212 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_digitalIq(unsigned antenna) const =0 ;




    /**
     * Read field MMO_SLAVE_DIGITAL_IQ at 0x50214 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_mmoSlaveDigitalIq(unsigned antenna) const =0 ;


    /**
     * Read field MMO_SLAVE_DIGITAL_IQ at 0x50214 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mmoSlaveDigitalIq(unsigned antenna) const =0 ;




    /**
     * Read field LNA_BIAS_SWITCH at 0x50222 bits [1]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_lnaBiasSwitch(unsigned antenna) const =0 ;

    /**
     * Write field LNA_BIAS_SWITCH at 0x50222 bits [1]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_lnaBiasSwitch(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field LNA_BIAS_SWITCH at 0x50222 bits [1]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_lnaBiasSwitch(unsigned antenna) const =0 ;

    /**
     * Write field LNA_BIAS_SWITCH at 0x50222 bits [1]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_lnaBiasSwitch(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field LNA_BIAS_SWITCH in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_lnaBiasSwitch(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_IF_ATTEN_RAW at 0x50230 bits [5..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxIfAttenRaw(unsigned antenna) const =0 ;

    /**
     * Write field RX_IF_ATTEN_RAW at 0x50230 bits [5..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxIfAttenRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_IF_ATTEN_RAW at 0x50230 bits [5..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxIfAttenRaw(unsigned antenna) const =0 ;

    /**
     * Write field RX_IF_ATTEN_RAW at 0x50230 bits [5..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxIfAttenRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_IF_ATTEN_RAW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxIfAttenRaw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_ATTEN_RAW at 0x50230 bits [13..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxAttenRaw(unsigned antenna) const =0 ;

    /**
     * Write field RX_ATTEN_RAW at 0x50230 bits [13..8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxAttenRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_ATTEN_RAW at 0x50230 bits [13..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxAttenRaw(unsigned antenna) const =0 ;

    /**
     * Write field RX_ATTEN_RAW at 0x50230 bits [13..8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxAttenRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_ATTEN_RAW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxAttenRaw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_WIDE_RSSI_LO at 0x50238 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxWideRssiLo(unsigned antenna) const =0 ;


    /**
     * Read field RX_WIDE_RSSI_LO at 0x50238 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxWideRssiLo(unsigned antenna) const =0 ;




    /**
     * Read field RX_WIDE_RSSI_HI at 0x5023a bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxWideRssiHi(unsigned antenna) const =0 ;


    /**
     * Read field RX_WIDE_RSSI_HI at 0x5023a bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxWideRssiHi(unsigned antenna) const =0 ;




    /**
     * Read field WIDE_RSSI_RX_FE_ATTEN at 0x5023c bits [2..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_wideRssiRxFeAtten(unsigned antenna) const =0 ;


    /**
     * Read field WIDE_RSSI_RX_FE_ATTEN at 0x5023c bits [2..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wideRssiRxFeAtten(unsigned antenna) const =0 ;




    /**
     * Read field PA_GAIN_MANUAL_CTRL_RAW at 0x50242 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_paGainManualCtrlRaw(unsigned antenna) const =0 ;

    /**
     * Write field PA_GAIN_MANUAL_CTRL_RAW at 0x50242 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_paGainManualCtrlRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field PA_GAIN_MANUAL_CTRL_RAW at 0x50242 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_paGainManualCtrlRaw(unsigned antenna) const =0 ;

    /**
     * Write field PA_GAIN_MANUAL_CTRL_RAW at 0x50242 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_paGainManualCtrlRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field PA_GAIN_MANUAL_CTRL_RAW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_paGainManualCtrlRaw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PA_GAIN_OVERRIDE_RAW at 0x50242 bits [15]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_paGainOverrideRaw(unsigned antenna) const =0 ;

    /**
     * Write field PA_GAIN_OVERRIDE_RAW at 0x50242 bits [15]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_paGainOverrideRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field PA_GAIN_OVERRIDE_RAW at 0x50242 bits [15]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_paGainOverrideRaw(unsigned antenna) const =0 ;

    /**
     * Write field PA_GAIN_OVERRIDE_RAW at 0x50242 bits [15]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_paGainOverrideRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field PA_GAIN_OVERRIDE_RAW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_paGainOverrideRaw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_RX_IF_ATTEN at 0x50244 bits [6..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_spi_rx_if_atten(unsigned antenna) const =0 ;

    /**
     * Write field SPI_RX_IF_ATTEN at 0x50244 bits [6..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi_rx_if_atten(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field SPI_RX_IF_ATTEN at 0x50244 bits [6..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi_rx_if_atten(unsigned antenna) const =0 ;

    /**
     * Write field SPI_RX_IF_ATTEN at 0x50244 bits [6..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi_rx_if_atten(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field SPI_RX_IF_ATTEN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi_rx_if_atten(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_RX_IF_ATTEN_DONE at 0x50244 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_spi_rx_if_atten_done() const =0 ;


    /**
     * Read field SPI_RX_IF_ATTEN_DONE at 0x50244 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi_rx_if_atten_done() const =0 ;




    /**
     * Read field SPI_RX_IF_ATTEN_UPDATE at 0x50244 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_spi_rx_if_atten_update() const =0 ;

    /**
     * Write field SPI_RX_IF_ATTEN_UPDATE at 0x50244 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi_rx_if_atten_update(FpgaVal value) =0 ;

    /**
     * Read field SPI_RX_IF_ATTEN_UPDATE at 0x50244 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi_rx_if_atten_update() const =0 ;

    /**
     * Write field SPI_RX_IF_ATTEN_UPDATE at 0x50244 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi_rx_if_atten_update(FpgaVal value) =0 ;

    /**
     * Write field SPI_RX_IF_ATTEN_UPDATE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi_rx_if_atten_update(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_RX_RF_ATTEN at 0x50246 bits [6..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_spi_rx_rf_atten(unsigned antenna) const =0 ;

    /**
     * Write field SPI_RX_RF_ATTEN at 0x50246 bits [6..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi_rx_rf_atten(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field SPI_RX_RF_ATTEN at 0x50246 bits [6..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi_rx_rf_atten(unsigned antenna) const =0 ;

    /**
     * Write field SPI_RX_RF_ATTEN at 0x50246 bits [6..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi_rx_rf_atten(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field SPI_RX_RF_ATTEN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi_rx_rf_atten(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_RX_RF_ATTEN_DONE at 0x50246 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_spi_rx_rf_atten_done() const =0 ;


    /**
     * Read field SPI_RX_RF_ATTEN_DONE at 0x50246 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi_rx_rf_atten_done() const =0 ;




    /**
     * Read field SPI_RX_RF_ATTEN_UPDATE at 0x50246 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_spi_rx_rf_atten_update() const =0 ;

    /**
     * Write field SPI_RX_RF_ATTEN_UPDATE at 0x50246 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi_rx_rf_atten_update(FpgaVal value) =0 ;

    /**
     * Read field SPI_RX_RF_ATTEN_UPDATE at 0x50246 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi_rx_rf_atten_update() const =0 ;

    /**
     * Write field SPI_RX_RF_ATTEN_UPDATE at 0x50246 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi_rx_rf_atten_update(FpgaVal value) =0 ;

    /**
     * Write field SPI_RX_RF_ATTEN_UPDATE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi_rx_rf_atten_update(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FPC_DSA_ATTEN_RAW at 0x50248 bits [5..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_fpcDsaAttenRaw(unsigned antenna) const =0 ;

    /**
     * Write field FPC_DSA_ATTEN_RAW at 0x50248 bits [5..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fpcDsaAttenRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field FPC_DSA_ATTEN_RAW at 0x50248 bits [5..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpcDsaAttenRaw(unsigned antenna) const =0 ;

    /**
     * Write field FPC_DSA_ATTEN_RAW at 0x50248 bits [5..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fpcDsaAttenRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field FPC_DSA_ATTEN_RAW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fpcDsaAttenRaw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FPC_ATTEN_COMP_ADDR_RAW at 0x5024a bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_fpcAttenCompAddrRaw(unsigned antenna) const =0 ;

    /**
     * Write field FPC_ATTEN_COMP_ADDR_RAW at 0x5024a bits [7..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fpcAttenCompAddrRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field FPC_ATTEN_COMP_ADDR_RAW at 0x5024a bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpcAttenCompAddrRaw(unsigned antenna) const =0 ;

    /**
     * Write field FPC_ATTEN_COMP_ADDR_RAW at 0x5024a bits [7..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fpcAttenCompAddrRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field FPC_ATTEN_COMP_ADDR_RAW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fpcAttenCompAddrRaw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FPC_ATTEN_COMP_DIGITAL_GAIN_RAW at 0x5024c bits [9..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_fpcAttenCompDigitalGainRaw(unsigned antenna) const =0 ;

    /**
     * Write field FPC_ATTEN_COMP_DIGITAL_GAIN_RAW at 0x5024c bits [9..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fpcAttenCompDigitalGainRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field FPC_ATTEN_COMP_DIGITAL_GAIN_RAW at 0x5024c bits [9..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpcAttenCompDigitalGainRaw(unsigned antenna) const =0 ;

    /**
     * Write field FPC_ATTEN_COMP_DIGITAL_GAIN_RAW at 0x5024c bits [9..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fpcAttenCompDigitalGainRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field FPC_ATTEN_COMP_DIGITAL_GAIN_RAW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fpcAttenCompDigitalGainRaw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FPC_ATTEN_COMP_BANK_RAW at 0x5024e bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_fpcAttenCompBankRaw(unsigned antenna) const =0 ;

    /**
     * Write field FPC_ATTEN_COMP_BANK_RAW at 0x5024e bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fpcAttenCompBankRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field FPC_ATTEN_COMP_BANK_RAW at 0x5024e bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpcAttenCompBankRaw(unsigned antenna) const =0 ;

    /**
     * Write field FPC_ATTEN_COMP_BANK_RAW at 0x5024e bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fpcAttenCompBankRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field FPC_ATTEN_COMP_BANK_RAW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fpcAttenCompBankRaw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FPC_ENABLE_RAW at 0x5024e bits [15]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_fpcEnableRaw(unsigned antenna) const =0 ;

    /**
     * Write field FPC_ENABLE_RAW at 0x5024e bits [15]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fpcEnableRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field FPC_ENABLE_RAW at 0x5024e bits [15]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpcEnableRaw(unsigned antenna) const =0 ;

    /**
     * Write field FPC_ENABLE_RAW at 0x5024e bits [15]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fpcEnableRaw(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field FPC_ENABLE_RAW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fpcEnableRaw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LOW_POWER_ALARM at 0x50250 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_lowPowerAlarm(unsigned antenna) const =0 ;

    /**
     * Write field LOW_POWER_ALARM at 0x50250 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_lowPowerAlarm(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field LOW_POWER_ALARM at 0x50250 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_lowPowerAlarm(unsigned antenna) const =0 ;

    /**
     * Write field LOW_POWER_ALARM at 0x50250 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_lowPowerAlarm(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field LOW_POWER_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_lowPowerAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field HIGH_POWER_ALARM at 0x50250 bits [1]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_highPowerAlarm(unsigned antenna) const =0 ;

    /**
     * Write field HIGH_POWER_ALARM at 0x50250 bits [1]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_highPowerAlarm(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field HIGH_POWER_ALARM at 0x50250 bits [1]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_highPowerAlarm(unsigned antenna) const =0 ;

    /**
     * Write field HIGH_POWER_ALARM at 0x50250 bits [1]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_highPowerAlarm(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field HIGH_POWER_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_highPowerAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SHUTDOWN_ALARM at 0x50250 bits [2]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_shutdownAlarm(unsigned antenna) const =0 ;

    /**
     * Write field SHUTDOWN_ALARM at 0x50250 bits [2]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_shutdownAlarm(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field SHUTDOWN_ALARM at 0x50250 bits [2]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_shutdownAlarm(unsigned antenna) const =0 ;

    /**
     * Write field SHUTDOWN_ALARM at 0x50250 bits [2]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_shutdownAlarm(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field SHUTDOWN_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_shutdownAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRX_ATTEN at 0x50258 bits [6..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxAtten(unsigned antenna) const =0 ;

    /**
     * Write field SRX_ATTEN at 0x50258 bits [6..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srxAtten(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field SRX_ATTEN at 0x50258 bits [6..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxAtten(unsigned antenna) const =0 ;

    /**
     * Write field SRX_ATTEN at 0x50258 bits [6..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srxAtten(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field SRX_ATTEN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srxAtten(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRX_ATTEN_DONE at 0x50258 bits [14]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxAttenDone(unsigned antenna) const =0 ;


    /**
     * Read field SRX_ATTEN_DONE at 0x50258 bits [14]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxAttenDone(unsigned antenna) const =0 ;




    /**
     * Read field SRX_ATTEN_UPDATE at 0x50258 bits [15]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxAttenUpdate(unsigned antenna) const =0 ;

    /**
     * Write field SRX_ATTEN_UPDATE at 0x50258 bits [15]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srxAttenUpdate(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field SRX_ATTEN_UPDATE at 0x50258 bits [15]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxAttenUpdate(unsigned antenna) const =0 ;

    /**
     * Write field SRX_ATTEN_UPDATE at 0x50258 bits [15]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srxAttenUpdate(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field SRX_ATTEN_UPDATE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srxAttenUpdate(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRX_PATH_SELECT at 0x5025a bits [0]
     * \return field value
     */
    virtual const FpgaVal read_srxPathSelect() const =0 ;

    /**
     * Write field SRX_PATH_SELECT at 0x5025a bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srxPathSelect(FpgaVal value) =0 ;

    /**
     * Read field SRX_PATH_SELECT at 0x5025a bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPathSelect() const =0 ;

    /**
     * Write field SRX_PATH_SELECT at 0x5025a bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srxPathSelect(FpgaVal value) =0 ;

    /**
     * Write field SRX_PATH_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srxPathSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRX_FWD_REV_SELECT at 0x5025a bits [8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_srxFwdRevSelect(unsigned antenna) const =0 ;

    /**
     * Write field SRX_FWD_REV_SELECT at 0x5025a bits [8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srxFwdRevSelect(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field SRX_FWD_REV_SELECT at 0x5025a bits [8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxFwdRevSelect(unsigned antenna) const =0 ;

    /**
     * Write field SRX_FWD_REV_SELECT at 0x5025a bits [8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srxFwdRevSelect(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field SRX_FWD_REV_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srxFwdRevSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ANTENNA_PROC_DELAY at 0x50260 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_antennaProcDelay(unsigned antenna) const =0 ;


    /**
     * Read field ANTENNA_PROC_DELAY at 0x50260 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_antennaProcDelay(unsigned antenna) const =0 ;




    /**
     * Read field ANT_DAC_TEST_MODE at 0x50480 bits [3..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_antDacTestMode(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_TEST_MODE at 0x50480 bits [3..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_antDacTestMode(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field ANT_DAC_TEST_MODE at 0x50480 bits [3..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_antDacTestMode(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_TEST_MODE at 0x50480 bits [3..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_antDacTestMode(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field ANT_DAC_TEST_MODE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_antDacTestMode(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ANT_DAC_CLKS_PER_SAMPLE at 0x50480 bits [11..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_antDacClksPerSample(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_CLKS_PER_SAMPLE at 0x50480 bits [11..8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_antDacClksPerSample(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field ANT_DAC_CLKS_PER_SAMPLE at 0x50480 bits [11..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_antDacClksPerSample(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_CLKS_PER_SAMPLE at 0x50480 bits [11..8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_antDacClksPerSample(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field ANT_DAC_CLKS_PER_SAMPLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_antDacClksPerSample(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ANT_DAC_SED_I0 at 0x50482 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_antDacSedI0(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_SED_I0 at 0x50482 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_antDacSedI0(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field ANT_DAC_SED_I0 at 0x50482 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_antDacSedI0(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_SED_I0 at 0x50482 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_antDacSedI0(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field ANT_DAC_SED_I0 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_antDacSedI0(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ANT_DAC_SED_Q0 at 0x50484 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_antDacSedQ0(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_SED_Q0 at 0x50484 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_antDacSedQ0(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field ANT_DAC_SED_Q0 at 0x50484 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_antDacSedQ0(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_SED_Q0 at 0x50484 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_antDacSedQ0(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field ANT_DAC_SED_Q0 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_antDacSedQ0(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ANT_DAC_SED_I1 at 0x50486 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_antDacSedI1(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_SED_I1 at 0x50486 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_antDacSedI1(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field ANT_DAC_SED_I1 at 0x50486 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_antDacSedI1(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_SED_I1 at 0x50486 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_antDacSedI1(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field ANT_DAC_SED_I1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_antDacSedI1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ANT_DAC_SED_Q1 at 0x50488 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_antDacSedQ1(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_SED_Q1 at 0x50488 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_antDacSedQ1(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field ANT_DAC_SED_Q1 at 0x50488 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_antDacSedQ1(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_SED_Q1 at 0x50488 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_antDacSedQ1(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field ANT_DAC_SED_Q1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_antDacSedQ1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ANT_DAC_IQ_SWAP at 0x5048a bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_antDacIqSwap(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_IQ_SWAP at 0x5048a bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_antDacIqSwap(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field ANT_DAC_IQ_SWAP at 0x5048a bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_antDacIqSwap(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_IQ_SWAP at 0x5048a bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_antDacIqSwap(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field ANT_DAC_IQ_SWAP in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_antDacIqSwap(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ANT_DAC_INPUT_SEL at 0x5048c bits [1..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_antDacInputSel(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_INPUT_SEL at 0x5048c bits [1..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_antDacInputSel(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field ANT_DAC_INPUT_SEL at 0x5048c bits [1..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_antDacInputSel(unsigned antenna) const =0 ;

    /**
     * Write field ANT_DAC_INPUT_SEL at 0x5048c bits [1..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_antDacInputSel(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field ANT_DAC_INPUT_SEL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_antDacInputSel(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_NUM_TAPS at 0x50500 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txNumTaps(unsigned antenna) const =0 ;


    /**
     * Read field TX_NUM_TAPS at 0x50500 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txNumTaps(unsigned antenna) const =0 ;




    /**
     * Read field TX_NUM_COEFF_BITS at 0x50502 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txNumCoeffBits(unsigned antenna) const =0 ;


    /**
     * Read field TX_NUM_COEFF_BITS at 0x50502 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txNumCoeffBits(unsigned antenna) const =0 ;




    /**
     * Read field TX_EQ_REAL_COEFF at 0x50504 bits [15..0]
     * \param antenna
     * \param tap
     * \return field value
     */
    virtual const FpgaVal read_txEqRealCoeff(unsigned antenna, unsigned tap) const =0 ;

    /**
     * Write field TX_EQ_REAL_COEFF at 0x50504 bits [15..0]
     * \param antenna
     * \param tap
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txEqRealCoeff(unsigned antenna, unsigned tap, FpgaVal value) =0 ;

    /**
     * Read field TX_EQ_REAL_COEFF at 0x50504 bits [15..0]
     * \param antenna
     * \param tap
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txEqRealCoeff(unsigned antenna, unsigned tap) const =0 ;

    /**
     * Write field TX_EQ_REAL_COEFF at 0x50504 bits [15..0]
     * \param antenna
     * \param tap
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txEqRealCoeff(unsigned antenna, unsigned tap, FpgaVal value) =0 ;

    /**
     * Write field TX_EQ_REAL_COEFF in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txEqRealCoeff(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_EQ_IMAG_COEFF at 0x50506 bits [15..0]
     * \param antenna
     * \param tap
     * \return field value
     */
    virtual const FpgaVal read_txEqImagCoeff(unsigned antenna, unsigned tap) const =0 ;

    /**
     * Write field TX_EQ_IMAG_COEFF at 0x50506 bits [15..0]
     * \param antenna
     * \param tap
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txEqImagCoeff(unsigned antenna, unsigned tap, FpgaVal value) =0 ;

    /**
     * Read field TX_EQ_IMAG_COEFF at 0x50506 bits [15..0]
     * \param antenna
     * \param tap
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txEqImagCoeff(unsigned antenna, unsigned tap) const =0 ;

    /**
     * Write field TX_EQ_IMAG_COEFF at 0x50506 bits [15..0]
     * \param antenna
     * \param tap
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txEqImagCoeff(unsigned antenna, unsigned tap, FpgaVal value) =0 ;

    /**
     * Write field TX_EQ_IMAG_COEFF in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txEqImagCoeff(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_ENABLE at 0x505a2 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureEnable(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_ENABLE at 0x505a2 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_ENABLE at 0x505a2 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureEnable(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_ENABLE at 0x505a2 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_DONE at 0x505a2 bits [1]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureDone(unsigned antenna) const =0 ;


    /**
     * Read field RXADC_CAPTURE_DONE at 0x505a2 bits [1]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureDone(unsigned antenna) const =0 ;




    /**
     * Read field RXADC_CAPTURE_READ_RESET at 0x505a2 bits [2]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureReadReset(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_READ_RESET at 0x505a2 bits [2]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureReadReset(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_READ_RESET at 0x505a2 bits [2]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureReadReset(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_READ_RESET at 0x505a2 bits [2]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureReadReset(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_READ_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureReadReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_STREAM_SINGLE at 0x505a2 bits [3]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcStreamSingle(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_STREAM_SINGLE at 0x505a2 bits [3]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcStreamSingle(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_STREAM_SINGLE at 0x505a2 bits [3]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcStreamSingle(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_STREAM_SINGLE at 0x505a2 bits [3]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcStreamSingle(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_STREAM_SINGLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcStreamSingle(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_STREAM_ENABLE at 0x505a2 bits [4]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureStreamEnable(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_STREAM_ENABLE at 0x505a2 bits [4]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureStreamEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_STREAM_ENABLE at 0x505a2 bits [4]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureStreamEnable(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_STREAM_ENABLE at 0x505a2 bits [4]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureStreamEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_STREAM_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureStreamEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_DATA at 0x505a4 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureData(unsigned antenna) const =0 ;


    /**
     * Read field RXADC_CAPTURE_DATA at 0x505a4 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureData(unsigned antenna) const =0 ;




    /**
     * Read field RXADC_CAPTURE_TRIGGER_LO at 0x505a6 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureTriggerLo(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_TRIGGER_LO at 0x505a6 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureTriggerLo(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_TRIGGER_LO at 0x505a6 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureTriggerLo(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_TRIGGER_LO at 0x505a6 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureTriggerLo(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_TRIGGER_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureTriggerLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_TRIGGER_HI at 0x505a8 bits [3..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureTriggerHi(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_TRIGGER_HI at 0x505a8 bits [3..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureTriggerHi(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_TRIGGER_HI at 0x505a8 bits [3..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureTriggerHi(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_TRIGGER_HI at 0x505a8 bits [3..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureTriggerHi(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_TRIGGER_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureTriggerHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_DEPTH at 0x505aa bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureDepth(unsigned antenna) const =0 ;


    /**
     * Read field RXADC_CAPTURE_DEPTH at 0x505aa bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureDepth(unsigned antenna) const =0 ;




    /**
     * Read field RXADC_CAPTURE1_KDEPTH at 0x505aa bits [15..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCapture1KDepth(unsigned antenna) const =0 ;


    /**
     * Read field RXADC_CAPTURE1_KDEPTH at 0x505aa bits [15..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCapture1KDepth(unsigned antenna) const =0 ;




    /**
     * Read field RXADC_CAPTURE_AVE_DEPTH_LO at 0x505b0 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureAveDepthLo(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_DEPTH_LO at 0x505b0 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureAveDepthLo(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_AVE_DEPTH_LO at 0x505b0 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureAveDepthLo(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_DEPTH_LO at 0x505b0 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureAveDepthLo(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_DEPTH_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureAveDepthLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_AVE_DEPTH_HI at 0x505b2 bits [1..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureAveDepthHi(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_DEPTH_HI at 0x505b2 bits [1..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureAveDepthHi(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_AVE_DEPTH_HI at 0x505b2 bits [1..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureAveDepthHi(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_DEPTH_HI at 0x505b2 bits [1..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureAveDepthHi(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_DEPTH_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureAveDepthHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_AVE_NUM_CAPT at 0x505b4 bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureAveNumCapt(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_NUM_CAPT at 0x505b4 bits [7..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureAveNumCapt(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_AVE_NUM_CAPT at 0x505b4 bits [7..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureAveNumCapt(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_NUM_CAPT at 0x505b4 bits [7..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureAveNumCapt(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_NUM_CAPT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureAveNumCapt(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_THROTTLE at 0x505b4 bits [11..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureThrottle(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_THROTTLE at 0x505b4 bits [11..8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureThrottle(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_THROTTLE at 0x505b4 bits [11..8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureThrottle(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_THROTTLE at 0x505b4 bits [11..8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureThrottle(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_THROTTLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureThrottle(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_DECIMATION at 0x505b4 bits [15..12]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureDecimation(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_DECIMATION at 0x505b4 bits [15..12]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureDecimation(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_DECIMATION at 0x505b4 bits [15..12]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureDecimation(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_DECIMATION at 0x505b4 bits [15..12]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureDecimation(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_DECIMATION in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureDecimation(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_AVE_TRIGGER_WIDTH_LO at 0x505b6 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureAveTriggerWidthLo(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_WIDTH_LO at 0x505b6 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureAveTriggerWidthLo(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_AVE_TRIGGER_WIDTH_LO at 0x505b6 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureAveTriggerWidthLo(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_WIDTH_LO at 0x505b6 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureAveTriggerWidthLo(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_WIDTH_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureAveTriggerWidthLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_AVE_TRIGGER_WIDTH_HI at 0x505b8 bits [3..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureAveTriggerWidthHi(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_WIDTH_HI at 0x505b8 bits [3..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureAveTriggerWidthHi(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_AVE_TRIGGER_WIDTH_HI at 0x505b8 bits [3..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureAveTriggerWidthHi(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_WIDTH_HI at 0x505b8 bits [3..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureAveTriggerWidthHi(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_WIDTH_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureAveTriggerWidthHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_AVE_TRIGGER_LO at 0x505ba bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureAveTriggerLo(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_LO at 0x505ba bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureAveTriggerLo(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_AVE_TRIGGER_LO at 0x505ba bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureAveTriggerLo(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_LO at 0x505ba bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureAveTriggerLo(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureAveTriggerLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RXADC_CAPTURE_AVE_TRIGGER_HI at 0x505bc bits [3..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureAveTriggerHi(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_HI at 0x505bc bits [3..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureAveTriggerHi(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RXADC_CAPTURE_AVE_TRIGGER_HI at 0x505bc bits [3..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureAveTriggerHi(unsigned antenna) const =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_HI at 0x505bc bits [3..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureAveTriggerHi(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RXADC_CAPTURE_AVE_TRIGGER_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxadcCaptureAveTriggerHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_NUM_TAPS at 0x50600 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxNumTaps(unsigned antenna) const =0 ;


    /**
     * Read field RX_NUM_TAPS at 0x50600 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxNumTaps(unsigned antenna) const =0 ;




    /**
     * Read field RX_NUM_COEFF_BITS at 0x50602 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxNumCoeffBits(unsigned antenna) const =0 ;


    /**
     * Read field RX_NUM_COEFF_BITS at 0x50602 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxNumCoeffBits(unsigned antenna) const =0 ;




    /**
     * Read field RX_EQ_REAL_COEFF at 0x50604 bits [15..0]
     * \param antenna
     * \param tap
     * \return field value
     */
    virtual const FpgaVal read_rxEqRealCoeff(unsigned antenna, unsigned tap) const =0 ;

    /**
     * Write field RX_EQ_REAL_COEFF at 0x50604 bits [15..0]
     * \param antenna
     * \param tap
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxEqRealCoeff(unsigned antenna, unsigned tap, FpgaVal value) =0 ;

    /**
     * Read field RX_EQ_REAL_COEFF at 0x50604 bits [15..0]
     * \param antenna
     * \param tap
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxEqRealCoeff(unsigned antenna, unsigned tap) const =0 ;

    /**
     * Write field RX_EQ_REAL_COEFF at 0x50604 bits [15..0]
     * \param antenna
     * \param tap
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxEqRealCoeff(unsigned antenna, unsigned tap, FpgaVal value) =0 ;

    /**
     * Write field RX_EQ_REAL_COEFF in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxEqRealCoeff(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_EQ_IMAG_COEFF at 0x50606 bits [15..0]
     * \param antenna
     * \param tap
     * \return field value
     */
    virtual const FpgaVal read_rxEqImagCoeff(unsigned antenna, unsigned tap) const =0 ;

    /**
     * Write field RX_EQ_IMAG_COEFF at 0x50606 bits [15..0]
     * \param antenna
     * \param tap
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxEqImagCoeff(unsigned antenna, unsigned tap, FpgaVal value) =0 ;

    /**
     * Read field RX_EQ_IMAG_COEFF at 0x50606 bits [15..0]
     * \param antenna
     * \param tap
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxEqImagCoeff(unsigned antenna, unsigned tap) const =0 ;

    /**
     * Write field RX_EQ_IMAG_COEFF at 0x50606 bits [15..0]
     * \param antenna
     * \param tap
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxEqImagCoeff(unsigned antenna, unsigned tap, FpgaVal value) =0 ;

    /**
     * Write field RX_EQ_IMAG_COEFF in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxEqImagCoeff(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_RESAMPLER_DIVIDE at 0x50800 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxResamplerDivide(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_DIVIDE at 0x50800 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxResamplerDivide(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_RESAMPLER_DIVIDE at 0x50800 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxResamplerDivide(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_DIVIDE at 0x50800 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxResamplerDivide(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_RESAMPLER_DIVIDE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxResamplerDivide(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_RESAMPLER_MULTIPLY at 0x50802 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxResamplerMultiply(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_MULTIPLY at 0x50802 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxResamplerMultiply(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_RESAMPLER_MULTIPLY at 0x50802 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxResamplerMultiply(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_MULTIPLY at 0x50802 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxResamplerMultiply(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_RESAMPLER_MULTIPLY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxResamplerMultiply(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_RESAMPLER_NCO_INC at 0x50804 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxResamplerNcoInc(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_NCO_INC at 0x50804 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxResamplerNcoInc(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_RESAMPLER_NCO_INC at 0x50804 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxResamplerNcoInc(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_NCO_INC at 0x50804 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxResamplerNcoInc(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_RESAMPLER_NCO_INC in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxResamplerNcoInc(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_RESAMPLER_CLOCKS_PER_SAMPLE at 0x50806 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxResamplerClocksPerSample(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_CLOCKS_PER_SAMPLE at 0x50806 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxResamplerClocksPerSample(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_RESAMPLER_CLOCKS_PER_SAMPLE at 0x50806 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxResamplerClocksPerSample(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_CLOCKS_PER_SAMPLE at 0x50806 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxResamplerClocksPerSample(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_RESAMPLER_CLOCKS_PER_SAMPLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxResamplerClocksPerSample(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_RESAMPLER_COEFF_ADDR at 0x50808 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxResamplerCoeffAddr(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_COEFF_ADDR at 0x50808 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxResamplerCoeffAddr(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_RESAMPLER_COEFF_ADDR at 0x50808 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxResamplerCoeffAddr(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_COEFF_ADDR at 0x50808 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxResamplerCoeffAddr(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_RESAMPLER_COEFF_ADDR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxResamplerCoeffAddr(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_RESAMPLER_COEFF_DATA at 0x5080c bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxResamplerCoeffData(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_COEFF_DATA at 0x5080c bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxResamplerCoeffData(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_RESAMPLER_COEFF_DATA at 0x5080c bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxResamplerCoeffData(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_COEFF_DATA at 0x5080c bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxResamplerCoeffData(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_RESAMPLER_COEFF_DATA in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxResamplerCoeffData(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_MMCM_MULTIPLY at 0x50810 bits [6..0]
     * \return field value
     */
    virtual const FpgaVal read_rxMmcmMultiply() const =0 ;

    /**
     * Write field RX_MMCM_MULTIPLY at 0x50810 bits [6..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxMmcmMultiply(FpgaVal value) =0 ;

    /**
     * Read field RX_MMCM_MULTIPLY at 0x50810 bits [6..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxMmcmMultiply() const =0 ;

    /**
     * Write field RX_MMCM_MULTIPLY at 0x50810 bits [6..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxMmcmMultiply(FpgaVal value) =0 ;

    /**
     * Write field RX_MMCM_MULTIPLY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxMmcmMultiply(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_MMCM_DIVIDE at 0x50812 bits [6..0]
     * \return field value
     */
    virtual const FpgaVal read_rxMmcmDivide() const =0 ;

    /**
     * Write field RX_MMCM_DIVIDE at 0x50812 bits [6..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxMmcmDivide(FpgaVal value) =0 ;

    /**
     * Read field RX_MMCM_DIVIDE at 0x50812 bits [6..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxMmcmDivide() const =0 ;

    /**
     * Write field RX_MMCM_DIVIDE at 0x50812 bits [6..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxMmcmDivide(FpgaVal value) =0 ;

    /**
     * Write field RX_MMCM_DIVIDE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxMmcmDivide(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_MMCM_UPDATE_BIT at 0x50812 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_rxMmcmUpdateBit() const =0 ;

    /**
     * Write field RX_MMCM_UPDATE_BIT at 0x50812 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxMmcmUpdateBit(FpgaVal value) =0 ;

    /**
     * Read field RX_MMCM_UPDATE_BIT at 0x50812 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxMmcmUpdateBit() const =0 ;

    /**
     * Write field RX_MMCM_UPDATE_BIT at 0x50812 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxMmcmUpdateBit(FpgaVal value) =0 ;

    /**
     * Write field RX_MMCM_UPDATE_BIT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxMmcmUpdateBit(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_MMCM_DONE_BIT at 0x50812 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_rxMmcmDoneBit() const =0 ;


    /**
     * Read field RX_MMCM_DONE_BIT at 0x50812 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxMmcmDoneBit() const =0 ;




    /**
     * Read field RX_SPECTRAL_INVERSION_BIT at 0x50814 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxSpectralInversionBit(unsigned antenna) const =0 ;

    /**
     * Write field RX_SPECTRAL_INVERSION_BIT at 0x50814 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxSpectralInversionBit(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_SPECTRAL_INVERSION_BIT at 0x50814 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxSpectralInversionBit(unsigned antenna) const =0 ;

    /**
     * Write field RX_SPECTRAL_INVERSION_BIT at 0x50814 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxSpectralInversionBit(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_SPECTRAL_INVERSION_BIT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxSpectralInversionBit(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_IBW_MHZ at 0x50816 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxIbwMhz(unsigned antenna) const =0 ;


    /**
     * Read field RX_IBW_MHZ at 0x50816 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxIbwMhz(unsigned antenna) const =0 ;




    /**
     * Read field RX_RESAMPLER_RESET_BIT at 0x50818 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxResamplerResetBit(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_RESET_BIT at 0x50818 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxResamplerResetBit(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_RESAMPLER_RESET_BIT at 0x50818 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxResamplerResetBit(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_RESET_BIT at 0x50818 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxResamplerResetBit(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_RESAMPLER_RESET_BIT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxResamplerResetBit(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_RESAMPLER_ENABLE at 0x50818 bits [8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_rxResamplerEnable(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_ENABLE at 0x50818 bits [8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxResamplerEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field RX_RESAMPLER_ENABLE at 0x50818 bits [8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxResamplerEnable(unsigned antenna) const =0 ;

    /**
     * Write field RX_RESAMPLER_ENABLE at 0x50818 bits [8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxResamplerEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field RX_RESAMPLER_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxResamplerEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RESAMPLER_DIVIDE at 0x50900 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txResamplerDivide(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_DIVIDE at 0x50900 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txResamplerDivide(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_RESAMPLER_DIVIDE at 0x50900 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txResamplerDivide(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_DIVIDE at 0x50900 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txResamplerDivide(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_RESAMPLER_DIVIDE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txResamplerDivide(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RESAMPLER_MULTIPLY at 0x50902 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txResamplerMultiply(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_MULTIPLY at 0x50902 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txResamplerMultiply(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_RESAMPLER_MULTIPLY at 0x50902 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txResamplerMultiply(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_MULTIPLY at 0x50902 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txResamplerMultiply(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_RESAMPLER_MULTIPLY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txResamplerMultiply(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RESAMPLER_NCO_INC at 0x50904 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txResamplerNcoInc(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_NCO_INC at 0x50904 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txResamplerNcoInc(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_RESAMPLER_NCO_INC at 0x50904 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txResamplerNcoInc(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_NCO_INC at 0x50904 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txResamplerNcoInc(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_RESAMPLER_NCO_INC in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txResamplerNcoInc(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RESAMPLER_CLOCKS_PER_SAMPLE at 0x50906 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txResamplerClocksPerSample(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_CLOCKS_PER_SAMPLE at 0x50906 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txResamplerClocksPerSample(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_RESAMPLER_CLOCKS_PER_SAMPLE at 0x50906 bits [4..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txResamplerClocksPerSample(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_CLOCKS_PER_SAMPLE at 0x50906 bits [4..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txResamplerClocksPerSample(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_RESAMPLER_CLOCKS_PER_SAMPLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txResamplerClocksPerSample(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RESAMPLER_COEFF_ADDR at 0x50908 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txResamplerCoeffAddr(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_COEFF_ADDR at 0x50908 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txResamplerCoeffAddr(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_RESAMPLER_COEFF_ADDR at 0x50908 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txResamplerCoeffAddr(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_COEFF_ADDR at 0x50908 bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txResamplerCoeffAddr(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_RESAMPLER_COEFF_ADDR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txResamplerCoeffAddr(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RESAMPLER_COEFF_DATA at 0x5090c bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txResamplerCoeffData(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_COEFF_DATA at 0x5090c bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txResamplerCoeffData(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_RESAMPLER_COEFF_DATA at 0x5090c bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txResamplerCoeffData(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_COEFF_DATA at 0x5090c bits [15..0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txResamplerCoeffData(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_RESAMPLER_COEFF_DATA in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txResamplerCoeffData(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_SPECTRAL_INVERSION_BIT at 0x50914 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txSpectralInversionBit(unsigned antenna) const =0 ;

    /**
     * Write field TX_SPECTRAL_INVERSION_BIT at 0x50914 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txSpectralInversionBit(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_SPECTRAL_INVERSION_BIT at 0x50914 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txSpectralInversionBit(unsigned antenna) const =0 ;

    /**
     * Write field TX_SPECTRAL_INVERSION_BIT at 0x50914 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txSpectralInversionBit(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_SPECTRAL_INVERSION_BIT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txSpectralInversionBit(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_IBW_MHZ at 0x50916 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txIbwMhz(unsigned antenna) const =0 ;


    /**
     * Read field TX_IBW_MHZ at 0x50916 bits [15..0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txIbwMhz(unsigned antenna) const =0 ;




    /**
     * Read field TX_RESAMPLER_RESET_BIT at 0x50918 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txResamplerResetBit(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_RESET_BIT at 0x50918 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txResamplerResetBit(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_RESAMPLER_RESET_BIT at 0x50918 bits [0]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txResamplerResetBit(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_RESET_BIT at 0x50918 bits [0]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txResamplerResetBit(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_RESAMPLER_RESET_BIT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txResamplerResetBit(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_RESAMPLER_ENABLE at 0x50918 bits [8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_txResamplerEnable(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_ENABLE at 0x50918 bits [8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txResamplerEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Read field TX_RESAMPLER_ENABLE at 0x50918 bits [8]
     * \param antenna
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txResamplerEnable(unsigned antenna) const =0 ;

    /**
     * Write field TX_RESAMPLER_ENABLE at 0x50918 bits [8]
     * \param antenna
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txResamplerEnable(unsigned antenna, FpgaVal value) =0 ;

    /**
     * Write field TX_RESAMPLER_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txResamplerEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field COMMON_CFR_EN_LOAD at 0x50f00 bits [3..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_commonCfrEnLoad(unsigned cfr) const =0 ;

    /**
     * Write field COMMON_CFR_EN_LOAD at 0x50f00 bits [3..0]
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_commonCfrEnLoad(unsigned cfr, FpgaVal value) =0 ;

    /**
     * Read field COMMON_CFR_EN_LOAD at 0x50f00 bits [3..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_commonCfrEnLoad(unsigned cfr) const =0 ;

    /**
     * Write field COMMON_CFR_EN_LOAD at 0x50f00 bits [3..0]
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_commonCfrEnLoad(unsigned cfr, FpgaVal value) =0 ;

    /**
     * Write field COMMON_CFR_EN_LOAD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_commonCfrEnLoad(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field COMMON_CFR_LOAD0OR1 at 0x50f08 bits [0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_commonCfrLoad0or1(unsigned cfr) const =0 ;

    /**
     * Write field COMMON_CFR_LOAD0OR1 at 0x50f08 bits [0]
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_commonCfrLoad0or1(unsigned cfr, FpgaVal value) =0 ;

    /**
     * Read field COMMON_CFR_LOAD0OR1 at 0x50f08 bits [0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_commonCfrLoad0or1(unsigned cfr) const =0 ;

    /**
     * Write field COMMON_CFR_LOAD0OR1 at 0x50f08 bits [0]
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_commonCfrLoad0or1(unsigned cfr, FpgaVal value) =0 ;

    /**
     * Write field COMMON_CFR_LOAD0OR1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_commonCfrLoad0or1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field COMMON_CFR_PULSE_I at 0x50f10 bits [15..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_commonCfrPulseI(unsigned cfr) const =0 ;

    /**
     * Write field COMMON_CFR_PULSE_I at 0x50f10 bits [15..0]
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_commonCfrPulseI(unsigned cfr, FpgaVal value) =0 ;

    /**
     * Read field COMMON_CFR_PULSE_I at 0x50f10 bits [15..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_commonCfrPulseI(unsigned cfr) const =0 ;

    /**
     * Write field COMMON_CFR_PULSE_I at 0x50f10 bits [15..0]
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_commonCfrPulseI(unsigned cfr, FpgaVal value) =0 ;

    /**
     * Write field COMMON_CFR_PULSE_I in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_commonCfrPulseI(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field COMMON_CFR_PULSE_Q at 0x50f18 bits [15..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_commonCfrPulseQ(unsigned cfr) const =0 ;

    /**
     * Write field COMMON_CFR_PULSE_Q at 0x50f18 bits [15..0]
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_commonCfrPulseQ(unsigned cfr, FpgaVal value) =0 ;

    /**
     * Read field COMMON_CFR_PULSE_Q at 0x50f18 bits [15..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_commonCfrPulseQ(unsigned cfr) const =0 ;

    /**
     * Write field COMMON_CFR_PULSE_Q at 0x50f18 bits [15..0]
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_commonCfrPulseQ(unsigned cfr, FpgaVal value) =0 ;

    /**
     * Write field COMMON_CFR_PULSE_Q in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_commonCfrPulseQ(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field COMMON_CFR_RESET at 0x50f20 bits [1..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_commonCfrReset(unsigned cfr) const =0 ;

    /**
     * Write field COMMON_CFR_RESET at 0x50f20 bits [1..0]
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_commonCfrReset(unsigned cfr, FpgaVal value) =0 ;

    /**
     * Read field COMMON_CFR_RESET at 0x50f20 bits [1..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_commonCfrReset(unsigned cfr) const =0 ;

    /**
     * Write field COMMON_CFR_RESET at 0x50f20 bits [1..0]
     * \param cfr
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_commonCfrReset(unsigned cfr, FpgaVal value) =0 ;

    /**
     * Write field COMMON_CFR_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_commonCfrReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field COMMON_SEL_ACTIVE_PULSE at 0x50f30 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_commonSelActivePulse() const =0 ;

    /**
     * Write field COMMON_SEL_ACTIVE_PULSE at 0x50f30 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_commonSelActivePulse(FpgaVal value) =0 ;

    /**
     * Read field COMMON_SEL_ACTIVE_PULSE at 0x50f30 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_commonSelActivePulse() const =0 ;

    /**
     * Write field COMMON_SEL_ACTIVE_PULSE at 0x50f30 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_commonSelActivePulse(FpgaVal value) =0 ;

    /**
     * Write field COMMON_SEL_ACTIVE_PULSE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_commonSelActivePulse(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CFR_STAGES at 0x50f80 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_cfrStages() const =0 ;


    /**
     * Read field CFR_STAGES at 0x50f80 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrStages() const =0 ;




    /**
     * Read field CFR_MAX_CPGS at 0x50f82 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_cfrMaxCpgs() const =0 ;


    /**
     * Read field CFR_MAX_CPGS at 0x50f82 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrMaxCpgs() const =0 ;




    /**
     * Read field FS_DIV at 0x50f90 bits [3..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_fsDiv(unsigned cfr) const =0 ;


    /**
     * Read field FS_DIV at 0x50f90 bits [3..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fsDiv(unsigned cfr) const =0 ;




    /**
     * Read field NUM_OF_CPGS at 0x50f92 bits [3..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_numOfCpgs(unsigned cfr) const =0 ;


    /**
     * Read field NUM_OF_CPGS at 0x50f92 bits [3..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_numOfCpgs(unsigned cfr) const =0 ;




    /**
     * Read field PEAK_DET_WINDOW at 0x50f94 bits [5..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_peakDetWindow(unsigned cfr) const =0 ;


    /**
     * Read field PEAK_DET_WINDOW at 0x50f94 bits [5..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_peakDetWindow(unsigned cfr) const =0 ;




    /**
     * Read field NUM_OF_POINTS at 0x50f96 bits [10..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_numOfPoints(unsigned cfr) const =0 ;


    /**
     * Read field NUM_OF_POINTS at 0x50f96 bits [10..0]
     * \param cfr
     * \return field value
     */
    virtual const FpgaVal read_nomutex_numOfPoints(unsigned cfr) const =0 ;




    /**
     * Read field SRX_PORT_SELECT at 0x5225a bits [0]
     * \return field value
     */
    virtual const FpgaVal read_srxPortSelect() const =0 ;

    /**
     * Write field SRX_PORT_SELECT at 0x5225a bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srxPortSelect(FpgaVal value) =0 ;

    /**
     * Read field SRX_PORT_SELECT at 0x5225a bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPortSelect() const =0 ;

    /**
     * Write field SRX_PORT_SELECT at 0x5225a bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srxPortSelect(FpgaVal value) =0 ;

    /**
     * Write field SRX_PORT_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srxPortSelect(FpgaVal* buff, FpgaVal value) =0 ;



    /**
     * Read combined register SRX_POWER_RSSI_FWD at 0x50006 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_srxPowerRssiFwd(unsigned antenna) const =0 ;







    /**
     * Read combined register SRX_POWER_RSSI_FWD at 0x50006 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerRssiFwd(unsigned antenna) const =0 ;



    /**
     * Read combined register SRX_POWER_RSSI_REV at 0x5000a bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_srxPowerRssiRev(unsigned antenna) const =0 ;







    /**
     * Read combined register SRX_POWER_RSSI_REV at 0x5000a bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxPowerRssiRev(unsigned antenna) const =0 ;



    /**
     * Read combined register CWGEN_NCO at 0x50022 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_cwgenNco(unsigned cwgen) const =0 ;






    /**
     * Write combined field CWGEN_NCO at 0x50022 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cwgenNco(unsigned cwgen, FpgaVal value) =0 ;






    /**
     * Read combined register CWGEN_NCO at 0x50022 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cwgenNco(unsigned cwgen) const =0 ;






    /**
     * Write combined field CWGEN_NCO at 0x50022 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cwgenNco(unsigned cwgen, FpgaVal value) =0 ;


    /**
     * Read combined register RX_WIDE_RSSI at 0x5023a bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_rxWideRssi(unsigned antenna) const =0 ;







    /**
     * Read combined register RX_WIDE_RSSI at 0x5023a bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxWideRssi(unsigned antenna) const =0 ;



    /**
     * Read combined register RXADC_CAPTURE_TRIGGER at 0x505a8 bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureTrigger(unsigned antenna) const =0 ;






    /**
     * Write combined field RXADC_CAPTURE_TRIGGER at 0x505a8 bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureTrigger(unsigned antenna, FpgaVal value) =0 ;






    /**
     * Read combined register RXADC_CAPTURE_TRIGGER at 0x505a8 bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureTrigger(unsigned antenna) const =0 ;






    /**
     * Write combined field RXADC_CAPTURE_TRIGGER at 0x505a8 bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureTrigger(unsigned antenna, FpgaVal value) =0 ;


    /**
     * Read combined register RXADC_CAPTURE_AVE_DEPTH at 0x505b2 bits [17..0]
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureAveDepth(unsigned antenna) const =0 ;






    /**
     * Write combined field RXADC_CAPTURE_AVE_DEPTH at 0x505b2 bits [17..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureAveDepth(unsigned antenna, FpgaVal value) =0 ;






    /**
     * Read combined register RXADC_CAPTURE_AVE_DEPTH at 0x505b2 bits [17..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureAveDepth(unsigned antenna) const =0 ;






    /**
     * Write combined field RXADC_CAPTURE_AVE_DEPTH at 0x505b2 bits [17..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureAveDepth(unsigned antenna, FpgaVal value) =0 ;


    /**
     * Read combined register RXADC_CAPTURE_AVE_TRIGGER_WIDTH at 0x505b8 bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureAveTriggerWidth(unsigned antenna) const =0 ;






    /**
     * Write combined field RXADC_CAPTURE_AVE_TRIGGER_WIDTH at 0x505b8 bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureAveTriggerWidth(unsigned antenna, FpgaVal value) =0 ;






    /**
     * Read combined register RXADC_CAPTURE_AVE_TRIGGER_WIDTH at 0x505b8 bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureAveTriggerWidth(unsigned antenna) const =0 ;






    /**
     * Write combined field RXADC_CAPTURE_AVE_TRIGGER_WIDTH at 0x505b8 bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureAveTriggerWidth(unsigned antenna, FpgaVal value) =0 ;


    /**
     * Read combined register RXADC_CAPTURE_AVE_TRIGGER at 0x505bc bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_rxadcCaptureAveTrigger(unsigned antenna) const =0 ;






    /**
     * Write combined field RXADC_CAPTURE_AVE_TRIGGER at 0x505bc bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxadcCaptureAveTrigger(unsigned antenna, FpgaVal value) =0 ;






    /**
     * Read combined register RXADC_CAPTURE_AVE_TRIGGER at 0x505bc bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxadcCaptureAveTrigger(unsigned antenna) const =0 ;






    /**
     * Write combined field RXADC_CAPTURE_AVE_TRIGGER at 0x505bc bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxadcCaptureAveTrigger(unsigned antenna, FpgaVal value) =0 ;



};


} /* namespace Mplane */

#endif /* _IANTENNA_REGS_DEF_H_ */
